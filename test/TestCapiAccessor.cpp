// The Clear BSD License
//
// Copyright (c) 2020 Danish Belal
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted (subject to the limitations in the disclaimer
// below) provided that the following conditions are met:
//
//      * Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//      * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//      * Neither the name of the copyright holder nor the names of its
//      contributors may be used to endorse or promote products derived from this
//      software without specific prior written permission.
//
// NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
// THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
// CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
// BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
// IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#define ENABLE_RUNTIME_TYPE_CHECKING

#include "CapiAccessor.hpp"
#include "gtest/gtest.h"

#include <cstring>
#include <optional>

extern "C"
{
#include "Controller.h"
}

// In order to prevent side effects from one test file to another,
// the model and all of its data is redefined statically in each
// compilation unit.
//
// This does not eliminate all side effects, as there is statically
// allocated data in other files, which the model refers to.
//
// This should be outsourced (todo).
static RT_MODEL_Controller_T ModelStruct;
static BlockIO_Controller_T BlockSignals;
static D_Work_Controller_T ModelStates;
static InstP_Controller_T ModelInstanceParameter = { { { 2.3, 12.3 } } };

static ExternalInputs_Controller_T ModelInputs;
static ExternalOutputs_Controller_T ModelOutputs;

static void ResetModel()
{
    std::memset(&ModelStruct, 0x00, sizeof(ModelStruct));
    std::memset(&BlockSignals, 0x00, sizeof(BlockSignals));
    std::memset(&ModelStates, 0x00, sizeof(ModelStates));
    ModelInstanceParameter.InstP_Model.SubmodelConfig.Gain = 2.3;
    ModelInstanceParameter.InstP_Model.SubmodelConfig.SomeOtherMember = 12.3;

    ModelStruct.dwork = &ModelStates;
    ModelStruct.blockIO = &BlockSignals;
    ModelStruct.Controller_InstP_ref = &ModelInstanceParameter;

    Controller_initialize(&ModelStruct, &ModelInputs, &ModelOutputs);
}
static void DestroyModel()
{
    Controller_terminate(&ModelStruct);
}

// All the tests need to compare the result of the provided accessor to
// the "actual" value.  Retrieving the actual value requires searching the
// ModelMappingInfo for the corresponding data entry.
//
// This function outsources the task of searching for the Address Index.
template <typename CapiElement>
static std::size_t GetAddrMapIndex(const rtwCAPI_ModelMappingInfo& MMI, std::string PathAndName)
{
    std::optional<std::size_t> AddrMapIdx;
    auto CapiInstance { db::simulink::GetRawData<CapiElement>(MMI) };
    const std::size_t NumElements { db::simulink::GetCount<CapiElement>(MMI) };
    for (std::size_t i {}; i < NumElements; ++i)
    {
        std::string CurrentName { db::simulink::GetName<CapiElement>(CapiInstance, i) };
        if (CurrentName == PathAndName)
        {
            AddrMapIdx = db::simulink::GetAddrIdx(CapiInstance, i);
            break;
        }
    }
    if (!AddrMapIdx.has_value())
    {
        throw std::runtime_error("Could not find Parameter");
    }
    return *AddrMapIdx;
}

TEST(CapiAccessor, BlockParameterGet)
{
    using WrappedElement = rtwCAPI_BlockParameters;
    ResetModel();

    constexpr double SetValue { 123.456 };
    constexpr auto ElemPath { "Controller/Discrete-Time Integrator/gainval" };

    auto& MMI { ModelStruct.DataMapInfo.mmi };
    db::simulink::BlockParameters bp { MMI };
    auto& Gain { bp.get<double>(ElemPath) };
    Gain = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&MMI) };
    // Search for the AddressMap Index.
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(MMI, ElemPath) };
    double* Gain2 { static_cast<double*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue, *Gain2) << "Parameter could not be set";
}

TEST(CapiAccessor, BlockParameterDirect)
{
    using WrappedElement = rtwCAPI_BlockParameters;
    ResetModel();

    constexpr double SetValue { 123.456 };
    constexpr auto ElemPath { "Controller/Discrete-Time Integrator/gainval" };

    auto& MMI { ModelStruct.DataMapInfo.mmi };
    db::simulink::BlockParameters bp { MMI };
    bp.get<double>(ElemPath) = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&MMI) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(MMI, ElemPath) };
    double* Gain2 { static_cast<double*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue, *Gain2) << "Parameter could not be set";
}

TEST(CapiAccessor, ModelParameterGet)
{
    using WrappedElement = rtwCAPI_ModelParameters;
    ResetModel();

    constexpr ConfigBus SetValue { 23.6, 12.3 };
    constexpr auto ElemName { "ModelConfig" };

    auto& MMI { ModelStruct.DataMapInfo.mmi };
    db::simulink::ModelParameters bp { MMI };
    auto& Config { bp.get<ConfigBus>(ElemName) };
    Config = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&MMI) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(MMI, ElemName) };
    auto* Actual { static_cast<ConfigBus*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue.Gain, Actual->Gain) << "Parameter could not be set";
    EXPECT_DOUBLE_EQ(SetValue.SomeOtherMember, Actual->SomeOtherMember) << "Parameter could not be set";
}

TEST(CapiAccessor, ModelParameterDirect)
{
    using WrappedElement = rtwCAPI_ModelParameters;
    ResetModel();

    constexpr ConfigBus SetValue { 23.6, 12.3 };
    constexpr auto ElemName { "ModelConfig" };

    auto& MMI { ModelStruct.DataMapInfo.mmi };
    db::simulink::ModelParameters bp { MMI };
    bp.get<ConfigBus>(ElemName) = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&MMI) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(MMI, ElemName) };
    auto* Actual { static_cast<ConfigBus*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue.Gain, Actual->Gain) << "Parameter could not be set";
    EXPECT_DOUBLE_EQ(SetValue.SomeOtherMember, Actual->SomeOtherMember) << "Parameter could not be set";
}