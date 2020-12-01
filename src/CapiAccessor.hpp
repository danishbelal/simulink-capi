// The Clear BSD License
//
// Copyright (c) 2020 Danish Belal
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted (subject to the limitations in the disclaimer
// below) provided that the following conditions are met:
//
//      * Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//      * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//      * Neither the name of the copyright holder nor the names of its
//      contributors may be used to endorse or promote products derived from this
//      software without specific prior written permission.
//
// NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
// THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
// CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
// BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
// IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef _PARAMETER_HPP_
#define _PARAMETER_HPP_

#include <exception>
#include <string>

#include "AccessorHelper.hpp"

#ifdef ENABLE_RUNTIME_TYPE_CHECKING
#include "cleantype.hpp"
#include <sstream>
#include <type_traits>
#endif

namespace db::simulink
{

template <typename WrappedElement>
class CapiAccessor;

using BlockParameters = CapiAccessor<rtwCAPI_BlockParameters>;
using ModelParameters = CapiAccessor<rtwCAPI_ModelParameters>;
using States = CapiAccessor<rtwCAPI_States>;
using Signals = CapiAccessor<rtwCAPI_Signals>;

template <typename WrappedElement>
class CapiAccessor
{
    const std::size_t mNumParams;
    const WrappedElement* const mWE;
    void* const* const mAddrMap;
    const rtwCAPI_ModelMappingInfo& mMMI;

public:
    CapiAccessor(const rtwCAPI_ModelMappingInfo& MMI);

    // Returns a reference to the Parameter.
    template <typename T>
    inline T& get(const std::string Name);
}; // end of class CapiAccessor.

template <typename WrappedElement>
CapiAccessor<WrappedElement>::CapiAccessor(const rtwCAPI_ModelMappingInfo& MMI)
    : mNumParams(db::simulink::GetCount<WrappedElement>(MMI))
    , mWE(db::simulink::GetRawData<WrappedElement>(MMI))
    , mAddrMap(rtwCAPI_GetDataAddressMap(&MMI))
    , mMMI(MMI)
{
}

template <typename WrappedElement>
template <typename T>
T& CapiAccessor<WrappedElement>::get(const std::string PathAndName)
{
    // Search for the Parameter given its and Name.
    for (std::size_t i { 0 }; i < mNumParams; ++i)
    {
        std::string CurrentParameter { db::simulink::GetName(mWE, i) };
        if (CurrentParameter == PathAndName)
        {
#ifdef ENABLE_RUNTIME_TYPE_CHECKING
            std::size_t DataTypeIndex { db::simulink::GetDataTypeIdx(mWE, i) };
            auto DataTypeMap { db::simulink::GetRawData<rtwCAPI_DataTypeMap>(mMMI) };
            std::string ActualType { DataTypeMap[DataTypeIndex].cDataName };
            std::string DeducedType { cleantype::clean<std::remove_reference_t<T>>() };

            if (ActualType != DeducedType)
            {
                std::ostringstream os;
                os << "Type mismatch "
                   << "(" << ActualType
                   << " vs. " << DeducedType << ")\n";
                throw std::runtime_error(os.str());
            }

#endif
            const std::size_t AddrIndex { db::simulink::GetAddrIdx(mWE, i) };
            return *db::simulink::GetDataAddress<T>(mAddrMap, AddrIndex);
        }
    }
    throw std::runtime_error("Couldn't find Parameter");
}

}
#endif