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

#ifndef _TESTCAPIACCESSORBASE_HPP_
#define _TESTCAPIACCESSORBASE_HPP_

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

    virtual const rtwCAPI_ModelMappingInfo& MMI() const = 0;

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
            std::string CurrentName { db::simulink::GetName<CapiElement>(MMI(), i) };
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