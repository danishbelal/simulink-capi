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

#ifndef _ACCESSOR_HPP_
#define _ACCESSOR_HPP_

#include "rtw_capi.h"
#include "rtw_modelmap.h"
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

template <typename CapiElement>
constexpr std::size_t GetCount(const rtwCAPI_ModelMappingInfo& MMI)
{
    static_assert(isCapiElement<CapiElement>(), "Incompatible C-API Element!");
    if constexpr (std::is_same_v<CapiElement, rtwCAPI_BlockParameters>)
    {
        return MMI.staticMap->Params.numBlockParameters;
    }
    else if constexpr (std::is_same_v<CapiElement, rtwCAPI_ModelParameters>)
    {
        return MMI.staticMap->Params.numModelParameters;
    }
    else if constexpr (std::is_same_v<CapiElement, rtwCAPI_Signals>)
    {
        return MMI.staticMap->Signals.numSignals;
    }
    else if constexpr (std::is_same_v<CapiElement, rtwCAPI_States>)
    {
        return MMI.staticMap->States.numStates;
    }
}

template <typename T>
constexpr T* GetDataAddress(void* const* const AddrMap, std::size_t Index)
{
    return static_cast<T*>(AddrMap[Index]);
}
}

#endif