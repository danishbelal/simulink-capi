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

using BlockParameters = db::simulink::BlockParameters<RT_MODEL_Controller_T>;
using ModelParameters = db::simulink::ModelParameters<RT_MODEL_Controller_T>;
using States = db::simulink::States<RT_MODEL_Controller_T>;
using Signals = db::simulink::Signals<RT_MODEL_Controller_T>;

/// Verify the internal GetAddrMapIndex Function against some
/// magic numbers.
TEST_F(TestCapiAccessor, InternalGetAddrMapIndex)
{
    auto& MMI { ModelStruct.DataMapInfo.mmi };

    // Signals
    auto S1 { GetAddrMapIndex<rtwCAPI_Signals>("Controller/Discrete-Time Integrator") };
    auto S2 { GetAddrMapIndex<rtwCAPI_Signals>("Controller/ModelRef1") };
    auto S3 { GetAddrMapIndex<rtwCAPI_Signals>("Controller/AlgLoop") };
    EXPECT_EQ(S1, 0);
    EXPECT_EQ(S2, 5);
    EXPECT_EQ(S3, 11);

    // Blockparameters
    auto BP1 { GetAddrMapIndex<rtwCAPI_BlockParameters>("Controller/Constant/Value") };
    auto BP2 { GetAddrMapIndex<rtwCAPI_BlockParameters>("Controller/Discrete-Time Integrator/gainval") };
    auto BP3 { GetAddrMapIndex<rtwCAPI_BlockParameters>("Controller/AlgLoop/InitialCondition") };
    EXPECT_EQ(BP1, 12);
    EXPECT_EQ(BP2, 13);
    EXPECT_EQ(BP3, 20);

    // Modelparameters
    auto MP1 { GetAddrMapIndex<rtwCAPI_ModelParameters>("mMatrix") };
    auto MP2 { GetAddrMapIndex<rtwCAPI_ModelParameters>("X3_DD") };
    EXPECT_EQ(MP1, 23);
    EXPECT_EQ(MP2, 24);

    // Blockstates
    auto BS1 { GetAddrMapIndex<rtwCAPI_States>("Controller/Discrete-Time\nIntegrator/DSTATE") };
    auto BS2 { GetAddrMapIndex<rtwCAPI_States>("Controller/AlgLoop/DSTATE") };
    EXPECT_EQ(BS1, 21);
    EXPECT_EQ(BS2, 22);
}

/// Test CapiAccessor::get<> for BlockParameters.
/// .
TEST_F(TestCapiAccessor, BlockParameterGet)
{
    using WrappedElement = rtwCAPI_BlockParameters;

    constexpr double SetValue { 123.456 };
    constexpr auto ElemPath { "Controller/Discrete-Time Integrator/gainval" };

    BlockParameters bp { ModelStruct };
    auto& Gain { bp.get<double>(ElemPath) };
    Gain = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&ModelStruct.DataMapInfo.mmi) };
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

    BlockParameters bp { ModelStruct };
    bp.get<double>(ElemPath) = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&ModelStruct.DataMapInfo.mmi) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ElemPath) };
    double* Gain2 { static_cast<double*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue, *Gain2) << "Parameter could not be set";
}

/// Test `CapiAccessor::opt` for BlockParameters.
/// .
TEST_F(TestCapiAccessor, BlockParameterOptional)
{
    using WrappedElement = rtwCAPI_BlockParameters;

    constexpr double SetValue { 123.456 };
    constexpr auto ElemPath { "Controller/Discrete-Time Integrator/gainval" };

    BlockParameters bp { ModelStruct };
    auto Opt { bp.opt<double>(ElemPath) };
    ASSERT_TRUE(Opt.has_value()) << "Element not found";
    Opt->get() = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&ModelStruct.DataMapInfo.mmi) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ElemPath) };
    double* Gain2 { static_cast<double*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue, *Gain2) << "Parameter could not be set";
}

/// Test `CapiAccessor::get` for invalid BlockParameters.
/// .
TEST_F(TestCapiAccessor, InvalidBlockParameterGet)
{

    BlockParameters bp { ModelStruct };
    EXPECT_THROW(auto& ref { bp.get<double>("does/not/exist") }, std::runtime_error);
}

/// Test `CapiAccessor::ptr` for invalid BlockParameters.
/// .
TEST_F(TestCapiAccessor, InvalidBlockParameterPtr)
{

    BlockParameters bp { ModelStruct };
    EXPECT_THROW(auto ptr { bp.ptr<double>("does/not/exist") }, std::runtime_error);
}

/// Test `CapiAccessor::opt` for invalid BlockParameters.
/// .
TEST_F(TestCapiAccessor, InvalidBlockParameterOpt)
{

    BlockParameters bp { ModelStruct };
    auto Opt { bp.opt<double>("does/not/exist") };
    EXPECT_FALSE(Opt.has_value());
    EXPECT_FALSE(Opt);
}

/// Test `CapiAccessor::get` for ModelParameters.
/// .
TEST_F(TestCapiAccessor, DISABLED_ModelParameterGet)
{
    using WrappedElement = rtwCAPI_ModelParameters;

    constexpr ConfigBus SetValue { 23.6, 12.3 };
    constexpr auto ElemName { "ModelConfig" };

    ModelParameters bp { ModelStruct };
    auto& Config { bp.get<ConfigBus>(ElemName) };
    Config = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&ModelStruct.DataMapInfo.mmi) };
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

    ModelParameters bp { ModelStruct };
    bp.get<ConfigBus>(ElemName) = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&ModelStruct.DataMapInfo.mmi) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ElemName) };
    auto* Actual { static_cast<ConfigBus*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue.Gain, Actual->Gain) << "Parameter could not be set";
    EXPECT_DOUBLE_EQ(SetValue.SomeOtherMember, Actual->SomeOtherMember) << "Parameter could not be set";
}

/// Test `CapiAccessor::opt` for ModelParameters.
/// .
TEST_F(TestCapiAccessor, DISABLED_ModelParameterOptional)
{
    using WrappedElement = rtwCAPI_ModelParameters;

    constexpr ConfigBus SetValue { 23.6, 12.3 };
    constexpr auto ElemName { "ModelConfig" };

    ModelParameters bp { ModelStruct };
    auto Opt { bp.opt<ConfigBus>(ElemName) };
    ASSERT_TRUE(Opt.has_value()) << "Element not found";
    Opt->get() = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&ModelStruct.DataMapInfo.mmi) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ElemName) };
    auto* Actual { static_cast<ConfigBus*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue.Gain, Actual->Gain) << "Parameter could not be set";
    EXPECT_DOUBLE_EQ(SetValue.SomeOtherMember, Actual->SomeOtherMember) << "Parameter could not be set";
}

/// Test `CapiAccessor::get` for invalid ModelParameters.
/// .
TEST_F(TestCapiAccessor, InvalidModelParameterGet)
{

    ModelParameters mp { ModelStruct };
    EXPECT_THROW(auto& ref { mp.get<double>("does-not-exist") }, std::runtime_error);
}

/// Test `CapiAccessor::ptr` for invalid ModelParameters.
/// .
TEST_F(TestCapiAccessor, InvalidModelParameterPtr)
{

    ModelParameters mp { ModelStruct };
    EXPECT_THROW(auto ptr { mp.ptr<double>("does-not-exist") }, std::runtime_error);
}

/// Test `CapiAccessor::opt` for invalid ModelParameters.
/// .
TEST_F(TestCapiAccessor, InvalidModelParameterOpt)
{

    ModelParameters mp { ModelStruct };
    auto Opt { mp.opt<double>("does-not-exist") };
    EXPECT_FALSE(Opt.has_value());
    EXPECT_FALSE(Opt);
}

/// Test `CapiAccessor::get` for Signals.
/// .
TEST_F(TestCapiAccessor, SignalGet)
{
    using WrappedElement = rtwCAPI_Signals;

    constexpr double SetValue { 5.4 };
    constexpr auto ElemPathAndName { "Controller/Sum" };

    Signals sigs { ModelStruct };
    auto& Sum { sigs.get<double>(ElemPathAndName) };
    Sum = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&ModelStruct.DataMapInfo.mmi) };
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

    Signals sigs { ModelStruct };
    sigs.get<double>(ElemPathAndName) = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&ModelStruct.DataMapInfo.mmi) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ElemPathAndName) };
    auto* Actual { static_cast<double*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue, *Actual) << "Parameter could not be set";
}

/// Test `CapiAccessor::opt` for Signals.
/// .
TEST_F(TestCapiAccessor, SignalOpt)
{
    using WrappedElement = rtwCAPI_Signals;

    constexpr double SetValue { 5.4 };
    constexpr auto ElemPathAndName { "Controller/Sum" };

    Signals sigs { ModelStruct };
    auto Sum { sigs.opt<double>(ElemPathAndName) };
    ASSERT_TRUE(Sum.has_value());
    Sum->get() = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&ModelStruct.DataMapInfo.mmi) };
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ElemPathAndName) };
    auto* Actual { static_cast<double*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue, *Actual) << "Parameter could not be set";
}

/// Test `CapiAccessor::get` for invalid Signals.
/// .
TEST_F(TestCapiAccessor, InvalidSignalGet)
{
    Signals sigs { ModelStruct };
    EXPECT_THROW(auto& ref { sigs.get<double>("does-not-exist") }, std::runtime_error);
}

/// Test `CapiAccessor::get` for invalid Signals.
/// .
TEST_F(TestCapiAccessor, InvalidSignalDirect)
{
    Signals sigs { ModelStruct };
    EXPECT_THROW(auto ptr { sigs.ptr<double>("does-not-exist") }, std::runtime_error);
}

/// Test `CapiAccessor::opt` for invalid Signals.
/// .
TEST_F(TestCapiAccessor, InvalidSignalOpt)
{
    Signals sigs { ModelStruct };
    auto Opt { sigs.opt<double>("does-not-exist") };
    EXPECT_FALSE(Opt.has_value());
    EXPECT_FALSE(Opt);
}