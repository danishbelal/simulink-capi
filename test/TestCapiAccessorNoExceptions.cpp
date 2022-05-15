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

class TestCapiAccessorNoExceptions : public TestCapiAccessorBase
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
TEST_F(TestCapiAccessorNoExceptions, InternalGetAddrMapIndex)
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

/// Test `CapiAccessor::ptr` for invalid BlockParameters.
/// .
TEST_F(TestCapiAccessorNoExceptions, InvalidBlockParameterPtr)
{
    BlockParameters bp { MMI() };
    db::simulink::CapiError Error;
    bp.ptr<double>("does/not/exist", Error);
    EXPECT_EQ(Error, db::simulink::CapiError::NotFound);
}

/// Test `CapiAccessor::ptr` for invalid ModelParameters.
/// .
TEST_F(TestCapiAccessorNoExceptions, InvalidModelParameterPtr)
{
    ModelParameters mp { MMI() };
    db::simulink::CapiError Error;
    mp.ptr<double>("does-not-exist", Error);
    EXPECT_EQ(Error, db::simulink::CapiError::NotFound);
}
