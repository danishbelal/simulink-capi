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

#ifndef _ACCESSOR_HPP_
#define _ACCESSOR_HPP_

#include "rtw_capi.h"
#include <cstddef>
#include <string>
#include <type_traits>

namespace db::simulink
{
template <typename CapiElement>
constexpr bool isCapiElement()
{
    constexpr bool ValidCapiElement = std::is_same_v<CapiElement, rtwCAPI_BlockParameters> || std::is_same_v<CapiElement, rtwCAPI_ModelParameters> || std::is_same_v<CapiElement, rtwCAPI_Signals> || std::is_same_v<CapiElement, rtwCAPI_States>;
    return ValidCapiElement;
}

// Some accessor macros are redundant and make code reusage
// unneccesary complicated.
//
// For example the following macros:
//
// #define rtwCAPI_GetSignalAddrIdx(bio, i)         ((bio)[(i)].addrMapIndex)
// #define rtwCAPI_GetBlockParameterAddrIdx(prm, i) ((prm)[(i)].addrMapIndex)
// #define rtwCAPI_GetModelParameterAddrIdx(prm, i) ((prm)[(i)].addrMapIndex)
//
// do the same thing.  I define the following functions to unify
// the access to some common members.
template <typename CapiElement>
constexpr std::size_t GetAddrIdx(const CapiElement* const BP, const std::size_t Index) noexcept
{
    static_assert(isCapiElement<CapiElement>(), "Incompatible C-API Element!");
    return BP[Index].addrMapIndex;
}
template <typename CapiElement>
constexpr std::size_t GetDataTypeIdx(const CapiElement* const Element, const std::size_t Index) noexcept
{
    static_assert(isCapiElement<CapiElement>(), "Incompatible C-API Element!");
    return Element[Index].dataTypeIndex;
}

template <typename CapiElement>
constexpr std::size_t GetDimensionIdx(const CapiElement* const Element, const std::size_t Index) noexcept
{
    static_assert(isCapiElement<CapiElement>(), "Incompatible C-API Element!");
    return Element[Index].dimIndex;
}

template <typename CapiElement>
constexpr std::string GetBlockPath(const CapiElement* const Element, const std::size_t Index) noexcept
{
    constexpr bool BlockPathAvailable
        = std::is_same_v<CapiElement, rtwCAPI_BlockParameters> || std::is_same_v<CapiElement, rtwCAPI_Signals> || std::is_same_v<CapiElement, rtwCAPI_States>;
    static_assert(BlockPathAvailable, "Block Path only available on BlockParameters, Signals and States");
    return Element[Index].blockPath;
}

template <typename CapiElement>
constexpr std::string GetName(const CapiElement* const Element, const std::size_t Index) noexcept
{
    static_assert(isCapiElement<CapiElement>(), "Incompatible C-API Element!");
    if constexpr (std::is_same_v<CapiElement, rtwCAPI_States>)
    {
        return Element[Index].stateName;
    }
    else if constexpr (std::is_same_v<CapiElement, rtwCAPI_BlockParameters>)
    {
        return Element[Index].paramName;
    }
    else if constexpr (std::is_same_v<CapiElement, rtwCAPI_ModelParameters>)
    {
        return Element[Index].varName;
    }
    else if constexpr (std::is_same_v<CapiElement, rtwCAPI_Signals>)
    {
        return Element[Index].signalName;
    }
}
template <typename T>
T* GetDataAddress(void* const* const AddrMap, std::size_t Index)
{
    return static_cast<T*>(AddrMap[Index]);
}
}

#endif