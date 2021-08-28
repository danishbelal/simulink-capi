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

/// \file

#include "CapiAccessor.hpp"
#include "TestCapiAccessorBase.hpp"
#include "gtest/gtest.h"

#include <cstring>
#include <optional>

extern "C"
{
#include "Controller.h"
}

class TestCapiAccessorRef : public TestCapiAccessorBase
{
protected:
    rtwCAPI_ModelMappingInfo& MMI() override
    {
        assert(ModelStruct.DataMapInfo.mmi.InstanceMap.childMMIArrayLen > 0);
        return *ModelStruct.DataMapInfo.mmi.InstanceMap.childMMIArray[0];
    }
};

using BlockParameters = db::simulink::BlockParameters<>;
using ModelParameters = db::simulink::ModelParameters<>;
using States = db::simulink::States<>;
using Signals = db::simulink::Signals<>;

TEST_F(TestCapiAccessorRef, BlockParameterGet)
{
    using WrappedElement = rtwCAPI_BlockParameters;

    constexpr double SetValue { 123.456 };
    constexpr auto ElemPath { "Controller/ModelRef1/ControllerRef/NormalGain/Gain" };

    BlockParameters bp { ModelStruct.DataMapInfo.mmi };
    auto& Gain { bp.get<double>(ElemPath) };
    Gain = SetValue;

    // Check if the parameter was actually written
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&MMI()) };
    // Search for the AddressMap Index.
    auto AddrMapIdx { GetAddrMapIndex<WrappedElement>(ElemPath) };
    double* Gain2 { static_cast<double*>(rtwCAPI_GetDataAddress(AddrMap, AddrMapIdx)) };

    EXPECT_DOUBLE_EQ(SetValue, *Gain2) << "Parameter could not be set";
}