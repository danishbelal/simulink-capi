// Copyright (c) 2020-2021, Danish Belal.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
// 3. Neither the name of the copyright holder nor the names of its contributors
//    may be used to endorse or promote products derived from this software without
//    specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

// \file

#include "CapiAccessor.hpp"
#include "TestCapiAccessorBase.hpp"
#include "gtest/gtest.h"

#include <cstring>
#include <optional>

extern "C"
{
#include "Controller.h"
}

class TestCapiAccessor : public TestCapiAccessorBase
{
protected:
    rtwCAPI_ModelMappingInfo& MMI() override
    {
        return ModelStruct.DataMapInfo.mmi;
    }
};

using BlockParameters = db::simulink::BlockParameters;
using ModelParameters = db::simulink::ModelParameters;
using States = db::simulink::States;
using Signals = db::simulink::Signals;

/// Verify the internal GetAddrMapIndex Function against some
/// magic numbers.
TEST_F(TestCapiAccessor, InternalGetAddrMapIndex)
{
    // Signals
    auto S1 { GetAddrMapIndex<rtwCAPI_Signals>("Controller/Discrete-Time Integrator") };
    auto S2 { GetAddrMapIndex<rtwCAPI_Signals>("Controller/ModelRef1") };
    auto S3 { GetAddrMapIndex<rtwCAPI_Signals>("Controller/AlgLoop") };
    EXPECT_EQ(S1, 0);
    EXPECT_EQ(S2, 6);
    EXPECT_EQ(S3, 13);

    // Blockparameters
    auto BP1 { GetAddrMapIndex<rtwCAPI_BlockParameters>("Controller/Constant/Value") };
    auto BP2 { GetAddrMapIndex<rtwCAPI_BlockParameters>("Controller/Discrete-Time Integrator/gainval") };
    auto BP3 { GetAddrMapIndex<rtwCAPI_BlockParameters>("Controller/AlgLoop/InitialCondition") };
    EXPECT_EQ(BP1, 14);
    EXPECT_EQ(BP2, 15);
    EXPECT_EQ(BP3, 22);

    // Modelparameters
    auto MP1 { GetAddrMapIndex<rtwCAPI_ModelParameters>("mMatrix") };
    auto MP2 { GetAddrMapIndex<rtwCAPI_ModelParameters>("X3_DD") };
    EXPECT_EQ(MP1, 25);
    EXPECT_EQ(MP2, 27);

    // Blockstates
    auto BS1 { GetAddrMapIndex<rtwCAPI_States>("Controller/Discrete-Time\nIntegrator/DSTATE") };
    auto BS2 { GetAddrMapIndex<rtwCAPI_States>("Controller/AlgLoop/DSTATE") };
    EXPECT_EQ(BS1, 23);
    EXPECT_EQ(BS2, 24);
}

/// Test CapiAccessor::get<> for BlockParameters.
/// .
TEST_F(TestCapiAccessor, BlockParameterGet)
{
    using WrappedElement = rtwCAPI_BlockParameters;

    constexpr double SetValue { 123.456 };
    constexpr auto ElemPath { "Controller/Discrete-Time Integrator/gainval" };

    BlockParameters bp { MMI() };
    auto& Gain { bp.get<double>(ElemPath) };
    Gain = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&MMI()) };
    // Search for the AddressMap Index.
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ElemPath) };
    double* Gain2 { static_cast<double*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue, *Gain2) << "Parameter could not be set";
}

/// Test `CapiAccessor::get` for BlockParameters.
/// .
TEST_F(TestCapiAccessor, BlockParameterDirect)
{
    using WrappedElement = rtwCAPI_BlockParameters;

    constexpr double SetValue { 123.456 };
    constexpr auto ElemPath { "Controller/Discrete-Time Integrator/gainval" };

    BlockParameters bp { MMI() };
    bp.get<double>(ElemPath) = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&MMI()) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ElemPath) };
    double* Gain2 { static_cast<double*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue, *Gain2) << "Parameter could not be set";
}

/// Test `CapiAccessor::get` for invalid BlockParameters.
/// .
TEST_F(TestCapiAccessor, InvalidBlockParameterGet)
{

    BlockParameters bp { MMI() };
    EXPECT_THROW(bp.get<double>("does/not/exist"), std::runtime_error);
}

/// Test `CapiAccessor::ptr` for invalid BlockParameters.
/// .
TEST_F(TestCapiAccessor, InvalidBlockParameterPtr)
{

    BlockParameters bp { MMI() };
    EXPECT_THROW(bp.ptr<double>("does/not/exist"), std::runtime_error);
}

/// Test `CapiAccessor::get` for ModelParameters.
/// .
TEST_F(TestCapiAccessor, DISABLED_ModelParameterGet)
{
    using WrappedElement = rtwCAPI_ModelParameters;

    constexpr ConfigBus SetValue { 23.6, 12.3 };
    constexpr auto ElemName { "ModelConfig" };

    ModelParameters bp { MMI() };
    auto& Config { bp.get<ConfigBus>(ElemName) };
    Config = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&MMI()) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ElemName) };
    auto* Actual { static_cast<ConfigBus*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue.Gain, Actual->Gain) << "Parameter could not be set";
    EXPECT_DOUBLE_EQ(SetValue.SomeOtherMember, Actual->SomeOtherMember) << "Parameter could not be set";
}

/// Test `CapiAccessor::get` for ModelParameters.
/// .
TEST_F(TestCapiAccessor, DISABLED_ModelParameterDirect)
{
    using WrappedElement = rtwCAPI_ModelParameters;

    constexpr ConfigBus SetValue { 23.6, 12.3 };
    constexpr auto ElemName { "ModelConfig" };

    ModelParameters bp { MMI() };
    bp.get<ConfigBus>(ElemName) = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&MMI()) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ElemName) };
    auto* Actual { static_cast<ConfigBus*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue.Gain, Actual->Gain) << "Parameter could not be set";
    EXPECT_DOUBLE_EQ(SetValue.SomeOtherMember, Actual->SomeOtherMember) << "Parameter could not be set";
}

/// Test `CapiAccessor::get` for invalid ModelParameters.
/// .
TEST_F(TestCapiAccessor, InvalidModelParameterGet)
{

    ModelParameters mp { MMI() };
    EXPECT_THROW(mp.get<double>("does-not-exist"), std::runtime_error);
}

/// Test `CapiAccessor::ptr` for invalid ModelParameters.
/// .
TEST_F(TestCapiAccessor, InvalidModelParameterPtr)
{

    ModelParameters mp { MMI() };
    EXPECT_THROW(mp.ptr<double>("does-not-exist"), std::runtime_error);
}

/// Test `CapiAccessor::get` for Signals.
/// .
TEST_F(TestCapiAccessor, SignalGet)
{
    using WrappedElement = rtwCAPI_Signals;

    constexpr double SetValue { 5.4 };
    constexpr auto ElemPathAndName { "Controller/Sum" };

    Signals sigs { MMI() };
    auto& Sum { sigs.get<double>(ElemPathAndName) };
    Sum = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&MMI()) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ElemPathAndName) };
    auto* Actual { static_cast<double*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue, *Actual) << "Parameter could not be set";
}

/// Test `CapiAccessor::get` for Signals.
/// .
TEST_F(TestCapiAccessor, SignalDirect)
{
    using WrappedElement = rtwCAPI_Signals;

    constexpr double SetValue { 5.4 };
    constexpr auto ElemPathAndName { "Controller/Sum" };

    Signals sigs { MMI() };
    sigs.get<double>(ElemPathAndName) = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&MMI()) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ElemPathAndName) };
    auto* Actual { static_cast<double*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue, *Actual) << "Parameter could not be set";
}

/// Test `CapiAccessor::get` for invalid Signals.
/// .
TEST_F(TestCapiAccessor, InvalidSignalGet)
{
    Signals sigs { MMI() };
    EXPECT_THROW(sigs.get<double>("does-not-exist"), std::runtime_error);
}

/// Test `CapiAccessor::get` for invalid Signals.
/// .
TEST_F(TestCapiAccessor, InvalidSignalDirect)
{
    Signals sigs { MMI() };
    EXPECT_THROW(sigs.ptr<double>("does-not-exist"), std::runtime_error);
}
