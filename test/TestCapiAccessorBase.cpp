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

#include "TestCapiAccessorBase.hpp"

TestCapiAccessorBase::TestCapiAccessorBase()
{
    ResetModel();
}

TestCapiAccessorBase::~TestCapiAccessorBase()
{
    Controller_terminate(&ModelStruct);
}

void TestCapiAccessorBase::ResetModel()
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
