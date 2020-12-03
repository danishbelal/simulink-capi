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
    // Returns a pointer to the parameter.
    template <typename T>
    inline T* const ptr(const std::string& Name);
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
    return *ptr<T>(PathAndName);
}

template <typename WrappedElement>
template <typename T>
T* const CapiAccessor<WrappedElement>::ptr(const std::string& PathAndName)
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
            return db::simulink::GetDataAddress<T>(mAddrMap, AddrIndex);
        }
    }
    throw std::runtime_error("Couldn't find Parameter");
}

}
#endif