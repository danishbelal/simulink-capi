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
#include <functional>
#include <optional>
#include <sstream>
#include <string>

#include "AccessorHelper.hpp"
#include "ModelTraits.hpp"

#ifdef ENABLE_RUNTIME_TYPE_CHECKING
#include "cleantype.hpp"
#include <type_traits>
#endif

namespace db::simulink
{

template <typename WrappedElement, typename ModelStruct>
class CapiAccessor;

template <typename ModelStruct>
using BlockParameters = CapiAccessor<rtwCAPI_BlockParameters, ModelStruct>;
template <typename ModelStruct>
using ModelParameters = CapiAccessor<rtwCAPI_ModelParameters, ModelStruct>;
template <typename ModelStruct>
using States = CapiAccessor<rtwCAPI_States, ModelStruct>;
template <typename ModelStruct>
using Signals = CapiAccessor<rtwCAPI_Signals, ModelStruct>;

template <typename WrappedElement, typename ModelStruct>
class CapiAccessor
{
    static_assert(has_datamapinfo_v<ModelStruct>,
        "The Model Structure needs to have a DataMapInfo Member."
        "If it doesnt have one, its either not a Model Structure, "
        "or you didnt enable the C API.");

    const ModelStruct& mMS;

public:
    CapiAccessor(const ModelStruct& MS);

    /// Returns a reference to the element.
    ///
    /// If you want to write the element, you \b must make sure to capture
    /// a reference to the value. Otherwise you might accidentally copy
    /// it - writes to a copy have no effect on the model!
    ///
    /// Writing to a BlockParameter of type double will looks like this:
    /// \code{.cpp}
    /// db::simulink::BlockParameters bp { ModelStruct };
    /// auto& Gain { bp.get<double>("Controller/Discrete-Time Integrator/gainval") };
    /// Gain = 23.35;
    /// \endcode
    ///
    /// It is also possible to not store the reference, but rather write
    /// directly to it. This is not recommended when repeatedly writing the
    /// element, due to increased lookup overhead.
    /// \code{.cpp}
    /// db::simulink::BlockParameters bp { ModelStruct };
    /// bp.get<double>("Controller/Discrete-Time Integrator/gainval") = 23.35;
    /// \endcode
    ///
    /// \throws std::runtime_error if a type mismatch is detected (only when
    /// type checking is enabled).
    /// \see ptr()
    /// \see opt()
    template <typename T>
    inline T& get(const std::string& Name);

    /// Returns a pointer to the element.
    ///
    /// Not very spectacular - it does what you expect.
    ///
    /// You can use it like this:
    /// \code{.cpp}
    /// db::simulink::BlockParameters bp { ModelStruct };
    /// auto GainPtr { bp.ptr<double>("Controller/Discrete-Time Integrator/gainval") };
    /// *GainPtr = 23.35;
    /// \endcode
    /// \throws std::runtime_error if a type mismatch is detected (only when
    /// type checking is enabled).
    /// \see get().
    /// \see opt()
    template <typename T>
    inline T* const ptr(const std::string& Name);

    /// Returns an `optional` that might contain a reference to the desired
    /// element.
    ///
    /// This does not throw an exception if the denoted element does not exist.
    /// In this case an empty `std::optional` will be returned. This must be
    /// explicitly checked by using `has_value()` (see example below).
    /// \code{.cpp}
    /// db::simulink::BlockParameters bp { ModelStruct };
    /// auto Opt { bp.opt<double>("Controller/Discrete-Time Integrator/gainval") };
    /// ASSERT(Opt.has_value());
    /// Opt->get() = 23.35;
    /// \endcode
    /// \see get()
    /// \see ptr()
    template <typename T>
    std::optional<std::reference_wrapper<T>> opt(const std::string& PathAndName);

    /// \internal
    template <typename T>
    std::optional<std::reference_wrapper<T>> FindInMMI(const rtwCAPI_ModelMappingInfo& MMI, const std::string& PathAndName);
}; // end of class CapiAccessor.

template <typename WrappedElement, typename ModelStruct>
CapiAccessor<WrappedElement, ModelStruct>::CapiAccessor(const ModelStruct& MS)
    : mMS(MS)
{
}

template <typename WrappedElement, typename ModelStruct>
template <typename T>
T& CapiAccessor<WrappedElement, ModelStruct>::get(const std::string& PathAndName)
{
    return *ptr<T>(PathAndName);
}

template <typename WrappedElement, typename ModelStruct>
template <typename T>
std::optional<std::reference_wrapper<T>> CapiAccessor<WrappedElement, ModelStruct>::opt(const std::string& PathAndName)
{
    std::optional<std::reference_wrapper<T>> Result;

    Result = FindInMMI<T>(mMS.DataMapInfo.mmi, PathAndName);
    if constexpr (has_childmmi_v<ModelStruct>)
    {
        // Number of submodels on this level
        const std::size_t NumModels { mMS.DataMapInfo.mmi.InstanceMap.childMMIArrayLen };
        if (!Result.has_value() && NumModels > 0)
        {
            for (std::size_t i {}; !Result.has_value() && i < NumModels; ++i)
            {
                Result = FindInMMI(mMS.DataMapInfo.childMMI[i], PathAndName);
            }
        }
    }

    return Result;
}

template <typename WrappedElement, typename ModelStruct>
template <typename T>
T* const CapiAccessor<WrappedElement, ModelStruct>::ptr(const std::string& PathAndName)
{
    auto E { opt<T>(PathAndName) };
    if (!E.has_value())
    {
        std::ostringstream os;
        os << "Couldn't find Parameter '"
           << PathAndName << "'";
        throw std::runtime_error(os.str());
    }

    return &E.value().get();
}

template <typename WrappedElement, typename ModelStruct>
template <typename T>
std::optional<std::reference_wrapper<T>> CapiAccessor<WrappedElement, ModelStruct>::FindInMMI(const rtwCAPI_ModelMappingInfo& MMI, const std::string& PathAndName)
{
    std::optional<std::reference_wrapper<T>> Result;

    const auto NumElements { db::simulink::GetCount<WrappedElement>(MMI) };
    const auto Data { db::simulink::GetRawData<WrappedElement>(MMI) };
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&MMI) };

    // TODO: replace with std search algorithm
    for (std::size_t i {}; i < NumElements; ++i)
    {
        std::string CurrentParameter { db::simulink::GetName<WrappedElement>(MMI, i) };
        if (CurrentParameter == PathAndName)
        {
#ifdef ENABLE_RUNTIME_TYPE_CHECKING
            std::size_t DataTypeIndex { db::simulink::GetDataTypeIdx(Data, i) };
            auto DataTypeMap { db::simulink::GetRawData<rtwCAPI_DataTypeMap>(MMI) };
            std::string ActualType { db::simulink::GetTypeName<T>(DataTypeMap, DataTypeIndex) };
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
            const std::size_t AddrIndex { db::simulink::GetAddrIdx(Data, i) };
            Result = *db::simulink::GetDataAddress<T>(AddrMap, AddrIndex);
        }
    }
    return Result;
}

}
#endif