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

#include "Accessor.hpp"
#include "join.hpp"
#include "split.hpp"

namespace db::simulink
{
class BlockParameters
{
    const std::size_t mNumParams;
    const rtwCAPI_BlockParameters* const mBP;
    void* const* const mAddrMap;

public:
    using WrappedElement = rtwCAPI_BlockParameters;
    BlockParameters(const rtwCAPI_ModelMappingInfo& MMI);

    // Returns a reference to the Parameter.
    template <typename T>
    inline T& get(const std::string Name);
    template <typename T>
    inline T& get(const std::string& BlockPath, const std::string& Name);
}; // end of class BlockParameters

BlockParameters::BlockParameters(const rtwCAPI_ModelMappingInfo& MMI)
    : mNumParams(db::simulink::GetCount<WrappedElement>(MMI))
    , mBP(db::simulink::GetRawData<WrappedElement>(MMI))
    , mAddrMap(rtwCAPI_GetDataAddressMap(&MMI))
{
}

template <typename T>
T& BlockParameters::get(const std::string PathAndName)
{
    auto PathElems = db::utils::split(PathAndName, '/');
    if (PathElems.size() < 2)
    {
        throw std::runtime_error("Invalid path");
    }
    std::string Name = PathElems.back();
    PathElems.pop_back();

    auto Path = db::utils::join(PathElems, '/');

    return get<T>(Path, Name);
}

template <typename T>
T& BlockParameters::get(const std::string& BlockPath, const std::string& Name)
{
    // Search for the Parameter given its Block Path and Name.
    for (std::size_t i { 0 }; i < mNumParams; ++i)
    {
        std::string CurrentParameter { db::simulink::GetName(mBP, i) };
        std::string CurrentPath { db::simulink::GetBlockPath(mBP, i) };
        if ((CurrentParameter == Name) && (CurrentPath == BlockPath))
        {
            const std::size_t AddrIndex { db::simulink::GetAddrIdx(mBP, i) };
            return *db::simulink::GetDataAddress<T>(mAddrMap, AddrIndex);
        }
    }
    throw std::runtime_error("Couldn't find Parameter");
}
}
#endif