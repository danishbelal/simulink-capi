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

#include "BusBuilder.hpp"
#include "CapiAccessor.hpp"
#include "TestCapiAccessorBase.hpp"
#include "gtest/gtest.h"

#include <cstring>
#include <optional>
#include <vector>

extern "C"
{
#include "Controller.h"
}

using BlockParameterBusBuilder = db::simulink::BusBuilder<rtwCAPI_BlockParameters>;

class TestBusBuilder : public TestCapiAccessorBase
{
protected:
    rtwCAPI_ModelMappingInfo& MMI() override
    {
        return ModelStruct.DataMapInfo.mmi;
    }
};

TEST_F(TestBusBuilder, BlockParameterBusBuilder)
{
    constexpr ConfigBus SetValue { 1.1, 13.2 };
    constexpr char Path[] { "Controller/ModelRef1/SubmodelConfig" };

    BlockParameterBusBuilder bb(MMI(), Path);
    bb.get<double>("Gain") = SetValue.Gain;
    bb.get<double>("SomeOtherMember") = SetValue.SomeOtherMember;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&ModelStruct.DataMapInfo.mmi) };
    auto AddrMapIdx { GetAddrMapIndex<rtwCAPI_BlockParameters>(Path) };
    auto* Actual { static_cast<ConfigBus*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(Actual->Gain, SetValue.Gain);
    EXPECT_DOUBLE_EQ(Actual->SomeOtherMember, SetValue.SomeOtherMember);

    // Now read again using get()
    EXPECT_DOUBLE_EQ(Actual->Gain, bb.get<double>("Gain"));
    EXPECT_DOUBLE_EQ(Actual->SomeOtherMember, bb.get<double>("SomeOtherMember"));
}

TEST_F(TestBusBuilder, ForEach)
{
    constexpr char Path[] { "Controller/ModelRef1/SubmodelConfig" };
    BlockParameterBusBuilder bb(MMI(), Path);

    std::vector<std::string> MemberNames;

    for (auto& e : bb)
    {
        MemberNames.push_back(e.elementName);
    }

    // ConfigBus has two Members:
    // - Gain
    // - SomeOtherMember
    EXPECT_EQ(MemberNames.size(), 2);
    EXPECT_EQ(MemberNames.at(0), "Gain");
    EXPECT_EQ(MemberNames.at(1), "SomeOtherMember");
}