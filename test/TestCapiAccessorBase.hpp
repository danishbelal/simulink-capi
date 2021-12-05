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

#ifndef TESTCAPIACCESSORBASE_HPP
#define TESTCAPIACCESSORBASE_HPP

#include "CapiAccessor.hpp"
#include "gtest/gtest.h"

#include <cstring>
#include <optional>

extern "C"
{
#include "Controller.h"
}

class TestCapiAccessorBase : public ::testing::Test
{
public:
    RT_MODEL_Controller_T ModelStruct;
    BlockIO_Controller_T BlockSignals;
    D_Work_Controller_T ModelStates;
    InstP_Controller_T ModelInstanceParameter;

    ExternalInputs_Controller_T ModelInputs;
    ExternalOutputs_Controller_T ModelOutputs;

protected:
    TestCapiAccessorBase();
    virtual ~TestCapiAccessorBase();
    void ResetModel();

    virtual rtwCAPI_ModelMappingInfo& MMI() = 0;

    // All the tests need to compare the result of the provided accessor to
    // the "actual" value.  Retrieving the actual value requires searching the
    // ModelMappingInfo for the corresponding data entry.
    //
    // This function outsources the task of searching for the Address Index.
    template <typename CapiElement>
    std::size_t GetAddrMapIndex(const std::string& PathAndName)
    {
        std::optional<std::size_t> AddrMapIdx;
        auto CapiInstance { db::simulink::GetRawData<CapiElement>(MMI()) };
        const std::size_t NumElements { db::simulink::GetCount<CapiElement>(MMI()) };
        for (std::size_t i {}; i < NumElements; ++i)
        {
            auto& CurrentElement { CapiInstance[i] };
            std::string CurrentName { db::simulink::GetName<CapiElement>(MMI(), CurrentElement) };
            if (CurrentName == PathAndName)
            {
                AddrMapIdx = db::simulink::GetAddrIdx(CapiInstance, i);
                break;
            }
        }
        if (!AddrMapIdx.has_value())
        {
            std::string msg { "Could not find " };
            msg.append(PathAndName);
            throw std::runtime_error(msg);
        }
        return *AddrMapIdx;
    }
};

#endif