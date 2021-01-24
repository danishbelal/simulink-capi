// Simulink CAPI - C++ header only library to interface with code generated by Simulink.
// Copyright (C) 2020-2021  Danish Belal
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License Version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

// \file

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
    ModelInstanceParameter.InstP_ModelRef1.SubmodelConfig.Gain = 2.3;
    ModelInstanceParameter.InstP_ModelRef1.SubmodelConfig.SomeOtherMember = 12.3;
    ModelInstanceParameter.InstP_ModelRef2.SubmodelConfig.Gain = 23.5;
    ModelInstanceParameter.InstP_ModelRef2.SubmodelConfig.SomeOtherMember = 355.1;

    ModelStruct.dwork = &ModelStates;
    ModelStruct.blockIO = &BlockSignals;
    ModelStruct.Controller_InstP_ref = &ModelInstanceParameter;

    Controller_initialize(&ModelStruct, &ModelInputs, &ModelOutputs);
}
static void DestroyModel()
{
    Controller_terminate(&ModelStruct);
}

using BlockParameters = db::simulink::BlockParameters<RT_MODEL_Controller_T>;
using ModelParameters = db::simulink::ModelParameters<RT_MODEL_Controller_T>;
using States = db::simulink::States<RT_MODEL_Controller_T>;
using Signals = db::simulink::Signals<RT_MODEL_Controller_T>;

// All the tests need to compare the result of the provided accessor to
// the "actual" value.  Retrieving the actual value requires searching the
// ModelMappingInfo for the corresponding data entry.
//
// This function outsources the task of searching for the Address Index.
template <typename CapiElement>
static std::size_t GetAddrMapIndex(const rtwCAPI_ModelMappingInfo& MMI, const std::string& PathAndName)
{
    std::optional<std::size_t> AddrMapIdx;
    auto CapiInstance { db::simulink::GetRawData<CapiElement>(MMI) };
    const std::size_t NumElements { db::simulink::GetCount<CapiElement>(MMI) };
    for (std::size_t i {}; i < NumElements; ++i)
    {
        std::string CurrentName { db::simulink::GetName<CapiElement>(MMI, i) };
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

/// Verify the internal GetAddrMapIndex Function against some
/// magic numbers.
TEST(TestCapiAccessorInternal, GetAddrMapIndex)
{
    ResetModel();
    auto& MMI { ModelStruct.DataMapInfo.mmi };

    // Signals
    auto S1 { GetAddrMapIndex<rtwCAPI_Signals>(MMI, "Controller/Discrete-Time Integrator/") };
    auto S2 { GetAddrMapIndex<rtwCAPI_Signals>(MMI, "Controller/ModelRef1/") };
    auto S3 { GetAddrMapIndex<rtwCAPI_Signals>(MMI, "Controller/AlgLoop/") };
    EXPECT_EQ(S1, 0);
    EXPECT_EQ(S2, 5);
    EXPECT_EQ(S3, 11);

    // Blockparameters
    auto BP1 { GetAddrMapIndex<rtwCAPI_BlockParameters>(MMI, "Controller/Constant/Value") };
    auto BP2 { GetAddrMapIndex<rtwCAPI_BlockParameters>(MMI, "Controller/Discrete-Time Integrator/gainval") };
    auto BP3 { GetAddrMapIndex<rtwCAPI_BlockParameters>(MMI, "Controller/AlgLoop/InitialCondition") };
    EXPECT_EQ(BP1, 12);
    EXPECT_EQ(BP2, 13);
    EXPECT_EQ(BP3, 20);

    // Modelparameters
    auto MP1 { GetAddrMapIndex<rtwCAPI_ModelParameters>(MMI, "mMatrix") };
    auto MP2 { GetAddrMapIndex<rtwCAPI_ModelParameters>(MMI, "X3_DD") };
    EXPECT_EQ(MP1, 23);
    EXPECT_EQ(MP2, 24);

    // Blockstates
    auto BS1 { GetAddrMapIndex<rtwCAPI_States>(MMI, "Controller/Discrete-Time\nIntegrator/DSTATE") };
    auto BS2 { GetAddrMapIndex<rtwCAPI_States>(MMI, "Controller/AlgLoop/DSTATE") };
    EXPECT_EQ(BS1, 21);
    EXPECT_EQ(BS2, 22);
}

/// Test CapiAccessor::get<> for BlockParameters.
/// .
TEST(CapiAccessor, BlockParameterGet)
{
    using WrappedElement = rtwCAPI_BlockParameters;
    ResetModel();

    constexpr double SetValue { 123.456 };
    constexpr auto ElemPath { "Controller/Discrete-Time Integrator/gainval" };

    BlockParameters bp { ModelStruct };
    auto& Gain { bp.get<double>(ElemPath) };
    Gain = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&ModelStruct.DataMapInfo.mmi) };
    // Search for the AddressMap Index.
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ModelStruct.DataMapInfo.mmi, ElemPath) };
    double* Gain2 { static_cast<double*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue, *Gain2) << "Parameter could not be set";
}

/// Test `CapiAccessor::get` for BlockParameters.
/// .
TEST(CapiAccessor, BlockParameterDirect)
{
    using WrappedElement = rtwCAPI_BlockParameters;
    ResetModel();

    constexpr double SetValue { 123.456 };
    constexpr auto ElemPath { "Controller/Discrete-Time Integrator/gainval" };

    BlockParameters bp { ModelStruct };
    bp.get<double>(ElemPath) = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&ModelStruct.DataMapInfo.mmi) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ModelStruct.DataMapInfo.mmi, ElemPath) };
    double* Gain2 { static_cast<double*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue, *Gain2) << "Parameter could not be set";
}

/// Test `CapiAccessor::opt` for BlockParameters.
/// .
TEST(CapiAccessor, BlockParameterOptional)
{
    using WrappedElement = rtwCAPI_BlockParameters;
    ResetModel();

    constexpr double SetValue { 123.456 };
    constexpr auto ElemPath { "Controller/Discrete-Time Integrator/gainval" };

    BlockParameters bp { ModelStruct };
    auto Opt { bp.opt<double>(ElemPath) };
    ASSERT_TRUE(Opt.has_value()) << "Element not found";
    Opt->get() = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&ModelStruct.DataMapInfo.mmi) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ModelStruct.DataMapInfo.mmi, ElemPath) };
    double* Gain2 { static_cast<double*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue, *Gain2) << "Parameter could not be set";
}

/// Test `CapiAccessor::get` for invalid BlockParameters.
/// .
TEST(CapiAccessor, InvalidBlockParameterGet)
{
    ResetModel();

    BlockParameters bp { ModelStruct };
    EXPECT_THROW(auto& ref { bp.get<double>("does/not/exist") }, std::runtime_error);
}

/// Test `CapiAccessor::ptr` for invalid BlockParameters.
/// .
TEST(CapiAccessor, InvalidBlockParameterPtr)
{
    ResetModel();

    BlockParameters bp { ModelStruct };
    EXPECT_THROW(auto ptr { bp.ptr<double>("does/not/exist") }, std::runtime_error);
}

/// Test `CapiAccessor::opt` for invalid BlockParameters.
/// .
TEST(CapiAccessor, InvalidBlockParameterOpt)
{
    ResetModel();

    BlockParameters bp { ModelStruct };
    auto Opt { bp.opt<double>("does/not/exist") };
    EXPECT_FALSE(Opt.has_value());
    EXPECT_FALSE(Opt);
}

/// Test `CapiAccessor::get` for ModelParameters.
/// .
TEST(CapiAccessor, ModelParameterGet)
{
    using WrappedElement = rtwCAPI_ModelParameters;
    ResetModel();

    constexpr ConfigBus SetValue { 23.6, 12.3 };
    constexpr auto ElemName { "ModelConfig" };

    ModelParameters bp { ModelStruct };
    auto& Config { bp.get<ConfigBus>(ElemName) };
    Config = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&ModelStruct.DataMapInfo.mmi) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ModelStruct.DataMapInfo.mmi, ElemName) };
    auto* Actual { static_cast<ConfigBus*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue.Gain, Actual->Gain) << "Parameter could not be set";
    EXPECT_DOUBLE_EQ(SetValue.SomeOtherMember, Actual->SomeOtherMember) << "Parameter could not be set";
}

/// Test `CapiAccessor::get` for ModelParameters.
/// .
TEST(CapiAccessor, ModelParameterDirect)
{
    using WrappedElement = rtwCAPI_ModelParameters;
    ResetModel();

    constexpr ConfigBus SetValue { 23.6, 12.3 };
    constexpr auto ElemName { "ModelConfig" };

    ModelParameters bp { ModelStruct };
    bp.get<ConfigBus>(ElemName) = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&ModelStruct.DataMapInfo.mmi) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ModelStruct.DataMapInfo.mmi, ElemName) };
    auto* Actual { static_cast<ConfigBus*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue.Gain, Actual->Gain) << "Parameter could not be set";
    EXPECT_DOUBLE_EQ(SetValue.SomeOtherMember, Actual->SomeOtherMember) << "Parameter could not be set";
}

/// Test `CapiAccessor::opt` for ModelParameters.
/// .
TEST(CapiAccessor, ModelParameterOptional)
{
    using WrappedElement = rtwCAPI_ModelParameters;
    ResetModel();

    constexpr ConfigBus SetValue { 23.6, 12.3 };
    constexpr auto ElemName { "ModelConfig" };

    ModelParameters bp { ModelStruct };
    auto Opt { bp.opt<ConfigBus>(ElemName) };
    ASSERT_TRUE(Opt.has_value()) << "Element not found";
    Opt->get() = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&ModelStruct.DataMapInfo.mmi) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ModelStruct.DataMapInfo.mmi, ElemName) };
    auto* Actual { static_cast<ConfigBus*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue.Gain, Actual->Gain) << "Parameter could not be set";
    EXPECT_DOUBLE_EQ(SetValue.SomeOtherMember, Actual->SomeOtherMember) << "Parameter could not be set";
}

/// Test `CapiAccessor::get` for invalid ModelParameters.
/// .
TEST(CapiAccessor, InvalidModelParameterGet)
{
    ResetModel();

    ModelParameters mp { ModelStruct };
    EXPECT_THROW(auto& ref { mp.get<double>("does-not-exist") }, std::runtime_error);
}

/// Test `CapiAccessor::ptr` for invalid ModelParameters.
/// .
TEST(CapiAccessor, InvalidModelParameterPtr)
{
    ResetModel();

    ModelParameters mp { ModelStruct };
    EXPECT_THROW(auto ptr { mp.ptr<double>("does-not-exist") }, std::runtime_error);
}

/// Test `CapiAccessor::opt` for invalid ModelParameters.
/// .
TEST(CapiAccessor, InvalidModelParameterOpt)
{
    ResetModel();

    ModelParameters mp { ModelStruct };
    auto Opt { mp.opt<double>("does-not-exist") };
    EXPECT_FALSE(Opt.has_value());
    EXPECT_FALSE(Opt);
}

/// Test `CapiAccessor::get` for Signals.
/// .
TEST(CapiAccessor, SignalGet)
{
    using WrappedElement = rtwCAPI_Signals;
    ResetModel();

    constexpr double SetValue { 5.4 };
    constexpr auto ElemPathAndName { "Controller/Sum/" };

    Signals sigs { ModelStruct };
    auto& Sum { sigs.get<double>(ElemPathAndName) };
    Sum = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&ModelStruct.DataMapInfo.mmi) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ModelStruct.DataMapInfo.mmi, ElemPathAndName) };
    auto* Actual { static_cast<double*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue, *Actual) << "Parameter could not be set";
}

/// Test `CapiAccessor::get` for Signals.
/// .
TEST(CapiAccessor, SignalDirect)
{
    using WrappedElement = rtwCAPI_Signals;
    ResetModel();

    constexpr double SetValue { 5.4 };
    constexpr auto ElemPathAndName { "Controller/Sum/" };

    Signals sigs { ModelStruct };
    sigs.get<double>(ElemPathAndName) = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&ModelStruct.DataMapInfo.mmi) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ModelStruct.DataMapInfo.mmi, ElemPathAndName) };
    auto* Actual { static_cast<double*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue, *Actual) << "Parameter could not be set";
}

/// Test `CapiAccessor::opt` for Signals.
/// .
TEST(CapiAccessor, SignalOpt)
{
    using WrappedElement = rtwCAPI_Signals;
    ResetModel();

    constexpr double SetValue { 5.4 };
    constexpr auto ElemPathAndName { "Controller/Sum/" };

    Signals sigs { ModelStruct };
    auto Sum { sigs.opt<double>(ElemPathAndName) };
    ASSERT_TRUE(Sum.has_value());
    Sum->get() = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&ModelStruct.DataMapInfo.mmi) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ModelStruct.DataMapInfo.mmi, ElemPathAndName) };
    auto* Actual { static_cast<double*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue, *Actual) << "Parameter could not be set";
}

/// Test `CapiAccessor::get` for invalid Signals.
/// .
TEST(CapiAccessor, InvalidSignalGet)
{
    ResetModel();

    Signals sigs { ModelStruct };
    EXPECT_THROW(auto& ref { sigs.get<double>("does-not-exist") }, std::runtime_error);
}

/// Test `CapiAccessor::get` for invalid Signals.
/// .
TEST(CapiAccessor, InvalidSignalDirect)
{
    ResetModel();

    Signals sigs { ModelStruct };
    EXPECT_THROW(auto ptr { sigs.ptr<double>("does-not-exist") }, std::runtime_error);
}

/// Test `CapiAccessor::opt` for invalid Signals.
/// .
TEST(CapiAccessor, InvalidSignalOpt)
{
    ResetModel();

    Signals sigs { ModelStruct };
    auto Opt { sigs.opt<double>("does-not-exist") };
    EXPECT_FALSE(Opt.has_value());
    EXPECT_FALSE(Opt);
}