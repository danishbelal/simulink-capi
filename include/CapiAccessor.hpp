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
#include <iterator>
#include <string>
#include <type_traits>

#include "AccessorHelper.hpp"
#include "CapiError.hpp"
#include "ModelTraits.hpp"

#ifdef ENABLE_RUNTIME_TYPE_CHECKING
#include "cleantype.hpp"
#endif

namespace db
{
namespace simulink
{

constexpr auto ENABLE_EXCEPTIONS = true;
constexpr auto DISABLE_EXCEPTIONS = false;

constexpr auto ENABLE_TYPECHECKING = true;
constexpr auto DISABLE_TYPECHECKING = false;

template <typename WrappedElement, bool ExceptionsEnabled, bool TypeCheckingEnabled>
class CapiAccessor;

template <bool ExceptionsEnabled = ENABLE_EXCEPTIONS, bool TypeCheckingEnabled = ENABLE_TYPECHECKING>
using BlockParameters = CapiAccessor<rtwCAPI_BlockParameters, ExceptionsEnabled, TypeCheckingEnabled>;
template <bool ExceptionsEnabled = ENABLE_EXCEPTIONS, bool TypeCheckingEnabled = ENABLE_TYPECHECKING>
using ModelParameters = CapiAccessor<rtwCAPI_ModelParameters, ExceptionsEnabled, TypeCheckingEnabled>;
template <bool ExceptionsEnabled = ENABLE_EXCEPTIONS, bool TypeCheckingEnabled = ENABLE_TYPECHECKING>
using States = CapiAccessor<rtwCAPI_States, ExceptionsEnabled, TypeCheckingEnabled>;
template <bool ExceptionsEnabled = ENABLE_EXCEPTIONS, bool TypeCheckingEnabled = ENABLE_TYPECHECKING>
using Signals = CapiAccessor<rtwCAPI_Signals, ExceptionsEnabled, TypeCheckingEnabled>;

template <typename WrappedElement, bool ExceptionsEnabled, bool TypeCheckingEnabled>
class CapiAccessor
{
    rtwCAPI_ModelMappingInfo& mMMI;

public:
    CapiAccessor(rtwCAPI_ModelMappingInfo& MMI);

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

    template <typename T>
    inline T& get(const std::string& Name, CapiError& Error);

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
    inline T* ptr(const std::string& Name);

    template <typename T>
    inline T* ptr(const std::string& Name, CapiError& Error);

    /// \internal
    template <typename T>
    T* FindInMMI(rtwCAPI_ModelMappingInfo& MMI, const std::string& PathAndName, CapiError& Error);
    /// \internal
    template <typename T>
    T* FindInStaticMMI(rtwCAPI_ModelMappingInfo& MMI, const std::string& PathAndName, CapiError& Error);
}; // end of class CapiAccessor.

template <typename WrappedElement, bool ExceptionsEnabled, bool TypeCheckingEnabled>
CapiAccessor<WrappedElement, ExceptionsEnabled, TypeCheckingEnabled>::CapiAccessor(rtwCAPI_ModelMappingInfo& MMI)
    : mMMI(MMI)
{
}

template <typename WrappedElement, bool ExceptionsEnabled, bool TypeCheckingEnabled>
template <typename T>
T& CapiAccessor<WrappedElement, ExceptionsEnabled, TypeCheckingEnabled>::get(const std::string& PathAndName)
{
    static_assert(ExceptionsEnabled, "CapiAccessor::get() is only available with Exceptions disabled.");
    return *ptr<T>(PathAndName);
}

template <typename WrappedElement, bool ExceptionsEnabled, bool TypeCheckingEnabled>
template <typename T>
T& CapiAccessor<WrappedElement, ExceptionsEnabled, TypeCheckingEnabled>::get(const std::string& PathAndName, CapiError& Error)
{
    return *ptr<T>(PathAndName, Error);
}

template <typename WrappedElement, bool ExceptionsEnabled, bool TypeCheckingEnabled>
template <typename T>
T* CapiAccessor<WrappedElement, ExceptionsEnabled, TypeCheckingEnabled>::ptr(const std::string& PathAndName)
{
    CapiError Error;
    auto E { ptr<T>(PathAndName, Error) };
    if (Error != CapiError::None)
    {
        throw std::runtime_error("capi element not found");
    }

    return E;
}

template <typename WrappedElement, bool ExceptionsEnabled, bool TypeCheckingEnabled>
template <typename T>
T* CapiAccessor<WrappedElement, ExceptionsEnabled, TypeCheckingEnabled>::ptr(const std::string& PathAndName, CapiError& Error)
{
    auto E { FindInMMI<T>(mMMI, PathAndName, Error) };
    if (E == nullptr)
    {
        Error = CapiError::NotFound;
        return nullptr;
    }
    return E;
}

template <typename WrappedElement, bool ExceptionsEnabled, bool TypeCheckingEnabled>
template <typename T>
T* CapiAccessor<WrappedElement, ExceptionsEnabled, TypeCheckingEnabled>::FindInMMI(rtwCAPI_ModelMappingInfo& MMI, const std::string& PathAndName, CapiError& Error)
{
    auto Result { FindInStaticMMI<T>(MMI, PathAndName, Error) };

    const std::size_t NumModels { MMI.InstanceMap.childMMIArrayLen };
    for (std::size_t i {}; Result == nullptr && i < NumModels; ++i)
    {
        Result = FindInMMI<T>(*MMI.InstanceMap.childMMIArray[i], PathAndName, Error);
    }

    return Result;
}

template <typename WrappedElement, bool ExceptionsEnabled, bool TypeCheckingEnabled>
template <typename T>
T* CapiAccessor<WrappedElement, ExceptionsEnabled, TypeCheckingEnabled>::FindInStaticMMI(rtwCAPI_ModelMappingInfo& MMI, const std::string& PathAndName, CapiError& Error)
{
    const auto NumElements { db::simulink::GetCount<WrappedElement>(MMI) };
    const auto Data { db::simulink::GetRawData<WrappedElement>(MMI) };
    void* const* const AddrMap { rtwCAPI_GetDataAddressMap(&MMI) };

    // TODO: replace with std search algorithm
    for (std::size_t i {}; i < NumElements; ++i)
    {
        std::string CurrentParameter { db::simulink::GetName<WrappedElement>(MMI, i) };
        if (CurrentParameter == PathAndName)
        {
            if constexpr (TypeCheckingEnabled)
            {
                std::size_t DataTypeIndex { db::simulink::GetDataTypeIdx(Data, i) };
                auto DataTypeMap { db::simulink::GetRawData<rtwCAPI_DataTypeMap>(MMI) };
                std::string ActualType { db::simulink::GetTypeName<T>(DataTypeMap, DataTypeIndex) };
                std::string DeducedType { cleantype::clean<std::remove_reference_t<T>>() };

                if (ActualType != DeducedType)
                {
                    Error = CapiError::TypeMismatch;
                    return nullptr;
                }
            }
            Error = CapiError::None;
            const std::size_t AddrIndex { db::simulink::GetAddrIdx(Data, i) };
            return db::simulink::GetDataAddress<T>(AddrMap, AddrIndex);
        }
    }
    return nullptr;
}
}
}
#endif