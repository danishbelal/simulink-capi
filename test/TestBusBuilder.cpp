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

using BlockParameterBusBuilder = db::simulink::BlockParameterBusBuilder;

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