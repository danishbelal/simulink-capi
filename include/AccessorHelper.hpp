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

#ifndef _ACCESSOR_HELPER_HPP_
#define _ACCESSOR_HELPER_HPP_

#include "rtw_capi.h"
#include "rtw_modelmap.h"
#include <cstddef>
#include <string>
#include <type_traits>

#include "ModelTraits.hpp"

namespace db
{
namespace simulink
{
/// Typetrait to check if the given type is a C-API Element.
///
/// The following types are valid Elements (and thus return `true`):
/// - `rtwCAPI_BlockParameters`
/// - `rtwCAPI_ModelParameters`
/// - `rtwCAPI_Signals`
/// - `rtwCAPI_States`
///
/// all other types return `false`.
template <typename CapiElement>
constexpr bool is_capi_element()
{
    constexpr bool ValidCapiElement                             //
        = std::is_same_v<CapiElement, rtwCAPI_BlockParameters>  //
        || std::is_same_v<CapiElement, rtwCAPI_ModelParameters> //
        || std::is_same_v<CapiElement, rtwCAPI_Signals>         //
        || std::is_same_v<CapiElement, rtwCAPI_States>;         //
    return ValidCapiElement;
}

/// Typetrait to check if the given type is a C-API Map like type.
///
/// C-API Maps store metainformation about the API Elements (States,
/// Parameters and so on).  This permits type introspection but also
/// allows gathering information about array dimensions and other useful
/// stuff.
///
/// The following types are Map like types and thus return `true`:
/// - `rtwCAPI_DataTypeMap`
/// - `rtwCAPI_DimensionMap`
/// - `rtwCAPI_FixPtMap`
/// - `rtwCAPI_ElementMap`
/// - `rtwCAPI_SampleTimeMap`
///
/// all other types return `false`.
template <typename CapiElement>
constexpr bool is_capi_map()
{
    constexpr bool ValidCapiMap                                //
        = std::is_same_v<CapiElement, rtwCAPI_DataTypeMap>     //
        || std::is_same_v<CapiElement, rtwCAPI_DimensionMap>   //
        || std::is_same_v<CapiElement, rtwCAPI_FixPtMap>       //
        || std::is_same_v<CapiElement, rtwCAPI_ElementMap>     //
        || std::is_same_v<CapiElement, rtwCAPI_SampleTimeMap>; //
    return ValidCapiMap;
}

template <typename CapiElement>
constexpr bool has_blockpath()
{
    constexpr bool HasBlockPath                                //
        = std::is_same_v<CapiElement, rtwCAPI_BlockParameters> //
        || std::is_same_v<CapiElement, rtwCAPI_Signals>        //
        || std::is_same_v<CapiElement, rtwCAPI_States>;
    return HasBlockPath;
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
    static_assert(is_capi_element<CapiElement>(), "Incompatible C-API Element!");
    return BP[Index].addrMapIndex;
}

template <typename CapiElement>
constexpr std::size_t GetDataTypeIdx(const CapiElement* const Element, const std::size_t Index) noexcept
{
    static_assert(is_capi_element<CapiElement>(), "Incompatible C-API Element!");
    return Element[Index].dataTypeIndex;
}

template <typename CapiElement>
constexpr std::size_t GetDimensionIdx(const CapiElement* const Element, const std::size_t Index) noexcept
{
    static_assert(is_capi_element<CapiElement>(), "Incompatible C-API Element!");
    return Element[Index].dimIndex;
}

template <typename CapiElement>
constexpr std::string GetBlockPath(const CapiElement* const Element, const std::size_t Index) noexcept
{
    constexpr bool BlockPathAvailable = has_blockpath<CapiElement>();
    static_assert(BlockPathAvailable, "Block Path only available on BlockParameters, Signals and States");
    return Element[Index].blockPath;
}

template <typename CapiElement>
constexpr std::size_t GetCount(const rtwCAPI_ModelMappingInfo& MMI) noexcept
{
    static_assert(is_capi_element<CapiElement>(), "Incompatible C-API Element!");
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

template <typename CapiElement>
constexpr const CapiElement* GetRawData(rtwCAPI_ModelMappingInfo& MMI) noexcept
{
    constexpr bool ValidElement = is_capi_element<CapiElement>() || is_capi_map<CapiElement>();
    static_assert(ValidElement, "Incompatible C-API Element!");
    if constexpr (std::is_same_v<CapiElement, rtwCAPI_BlockParameters>)
    {
        return MMI.staticMap->Params.blockParameters;
    }
    else if constexpr (std::is_same_v<CapiElement, rtwCAPI_ModelParameters>)
    {
        return MMI.staticMap->Params.modelParameters;
    }
    else if constexpr (std::is_same_v<CapiElement, rtwCAPI_Signals>)
    {
        return MMI.staticMap->Signals.signals;
    }
    else if constexpr (std::is_same_v<CapiElement, rtwCAPI_States>)
    {
        return MMI.staticMap->States.states;
    }
    else if constexpr (std::is_same_v<CapiElement, rtwCAPI_DataTypeMap>)
    {
        return MMI.staticMap->Maps.dataTypeMap;
    }
    else if constexpr (std::is_same_v<CapiElement, rtwCAPI_DimensionMap>)
    {
        return MMI.staticMap->Maps.dimensionMap;
    }
    else if constexpr (std::is_same_v<CapiElement, rtwCAPI_FixPtMap>)
    {
        return MMI.staticMap->Maps.fixPtMap;
    }
    else if constexpr (std::is_same_v<CapiElement, rtwCAPI_ElementMap>)
    {
        return MMI.staticMap->Maps.elementMap;
    }
    else if constexpr (std::is_same_v<CapiElement, rtwCAPI_SampleTimeMap>)
    {
        return MMI.staticMap->Maps.sampleTimeMap;
    }
}

template <typename CapiElement>
constexpr std::string GetName(rtwCAPI_ModelMappingInfo& MMI, const std::size_t Index)
{
    static_assert(is_capi_element<CapiElement>(), "Incompatible C-API Element!");

    const CapiElement* const Element { GetRawData<CapiElement>(MMI) };

    std::string Path {};
    if constexpr (has_blockpath<CapiElement>())
    {
        if (MMI.InstanceMap.path)
        {
            Path = MMI.InstanceMap.path;
            Path.append("/");
        }

        Path.append(Element[Index].blockPath);
    }

    if constexpr (std::is_same_v<CapiElement, rtwCAPI_States>)
    {
        std::string StateName { Element[Index].stateName };
        return Path + "/" + StateName;
    }
    else if constexpr (std::is_same_v<CapiElement, rtwCAPI_BlockParameters>)
    {
        std::string ParamName { Element[Index].paramName };
        return Path += "/" + ParamName;
    }
    else if constexpr (std::is_same_v<CapiElement, rtwCAPI_ModelParameters>)
    {
        return Element[Index].varName;
    }
    else if constexpr (std::is_same_v<CapiElement, rtwCAPI_Signals>)
    {
        // Signals have no name, usually. Therefore the Name
        // and the prepending "/" are only appended if its nonempty.
        std::string SignalName { Element[Index].signalName };
        if (!SignalName.empty())
        {
            Path = "/" + SignalName;
        }
        return Path;
    }
}

template <typename T>
constexpr std::string GetTypeName(const rtwCAPI_DataTypeMap* const Map, const std::size_t Index)
{
    if constexpr (std::is_class_v<T>)
    {
        return Map[Index].mwDataName;
    }
    else
    {
        return Map[Index].cDataName;
    }
}

template <typename T>
constexpr T* GetDataAddress(void* const* const AddrMap, std::size_t Index) noexcept
{
    return static_cast<T*>(AddrMap[Index]);
}

template <typename ModelStruct>
constexpr rtwCAPI_ModelMappingInfo& MMI(ModelStruct& MS) noexcept
{
    static_assert(has_datamapinfo_v<ModelStruct>,
        "The Model Structure needs to have a DataMapInfo Member."
        "If it doesnt have one, its either not a Model Structure, "
        "or you didnt enable the C API.");
    return MS.DataMapInfo.mmi;
}
}
}
#endif