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

#ifndef CAPI_ACCESSOR_HPP
#define CAPI_ACCESSOR_HPP

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
#define ENABLE_RUNTIME_TYPE_CHECKING_VALUE true
#else
#define ENABLE_RUNTIME_TYPE_CHECKING_VALUE false
#endif

namespace db
{
namespace simulink
{

constexpr auto ENABLE_TYPECHECKING = true;
constexpr auto DISABLE_TYPECHECKING = false;

template <typename WrappedElement, bool TypeCheckingEnabled>
class CapiAccessor;

template <bool TypeCheckingEnabled = ENABLE_TYPECHECKING>
using BlockParameters = CapiAccessor<rtwCAPI_BlockParameters, TypeCheckingEnabled>;
template <bool TypeCheckingEnabled = ENABLE_TYPECHECKING>
using ModelParameters = CapiAccessor<rtwCAPI_ModelParameters, TypeCheckingEnabled>;
template <bool TypeCheckingEnabled = ENABLE_TYPECHECKING>
using States = CapiAccessor<rtwCAPI_States, TypeCheckingEnabled>;
template <bool TypeCheckingEnabled = ENABLE_TYPECHECKING>
using Signals = CapiAccessor<rtwCAPI_Signals, TypeCheckingEnabled>;

template <typename WrappedElement, bool TypeCheckingEnabled>
class CapiAccessor
{
    static_assert(TypeCheckingEnabled ? ENABLE_RUNTIME_TYPE_CHECKING_VALUE : true, "To use typechecking the preprocessor flag ENABLE_RUNTIME_TYPE_CHECKING must be set.");
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

template <typename WrappedElement, bool TypeCheckingEnabled>
CapiAccessor<WrappedElement, TypeCheckingEnabled>::CapiAccessor(rtwCAPI_ModelMappingInfo& MMI)
    : mMMI(MMI)
{
}

template <typename WrappedElement, bool TypeCheckingEnabled>
template <typename T>
T& CapiAccessor<WrappedElement, TypeCheckingEnabled>::get(const std::string& PathAndName)
{
    return *ptr<T>(PathAndName);
}

template <typename WrappedElement, bool TypeCheckingEnabled>
template <typename T>
T& CapiAccessor<WrappedElement, TypeCheckingEnabled>::get(const std::string& PathAndName, CapiError& Error)
{
    return *ptr<T>(PathAndName, Error);
}

template <typename WrappedElement, bool TypeCheckingEnabled>
template <typename T>
T* CapiAccessor<WrappedElement, TypeCheckingEnabled>::ptr(const std::string& PathAndName)
{
    CapiError Error;
    auto E { ptr<T>(PathAndName, Error) };
    if (Error != CapiError::None)
    {
        throw std::runtime_error("capi element not found");
    }

    return E;
}

template <typename WrappedElement, bool TypeCheckingEnabled>
template <typename T>
T* CapiAccessor<WrappedElement, TypeCheckingEnabled>::ptr(const std::string& PathAndName, CapiError& Error)
{
    auto E { FindInMMI<T>(mMMI, PathAndName, Error) };
    if (E == nullptr)
    {
        Error = CapiError::NotFound;
        return nullptr;
    }
    return E;
}

template <typename WrappedElement, bool TypeCheckingEnabled>
template <typename T>
T* CapiAccessor<WrappedElement, TypeCheckingEnabled>::FindInMMI(rtwCAPI_ModelMappingInfo& MMI, const std::string& PathAndName, CapiError& Error)
{
    auto Result { FindInStaticMMI<T>(MMI, PathAndName, Error) };

    const std::size_t NumModels { MMI.InstanceMap.childMMIArrayLen };
    for (std::size_t i {}; Result == nullptr && i < NumModels; ++i)
    {
        Result = FindInMMI<T>(*MMI.InstanceMap.childMMIArray[i], PathAndName, Error);
    }

    return Result;
}

template <typename WrappedElement, bool TypeCheckingEnabled>
template <typename T>
T* CapiAccessor<WrappedElement, TypeCheckingEnabled>::FindInStaticMMI(rtwCAPI_ModelMappingInfo& MMI, const std::string& PathAndName, CapiError& Error)
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
#ifdef ENABLE_RUNTIME_TYPE_CHECKING
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
#endif
            Error = CapiError::None;
            const std::size_t AddrIndex { db::simulink::GetAddrIdx(Data, i) };
            return db::simulink::GetDataAddress<T>(AddrMap, AddrIndex);
        }
    }
    return nullptr;
}
} // namespace simulink
} // namespace db
#endif