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

#include "TestCapiAccessorBase.hpp"

TestCapiAccessorBase::TestCapiAccessorBase()
{
    ResetModel();
}

TestCapiAccessorBase::~TestCapiAccessorBase()
{
    Controller_terminate(&ModelStruct);
}

void TestCapiAccessorBase::ResetModel()
{
    std::memset(&ModelStruct, 0x00, sizeof(ModelStruct));
    std::memset(&BlockSignals, 0x00, sizeof(BlockSignals));
    std::memset(&ModelStates, 0x00, sizeof(ModelStates));
    ModelInstanceParameter.InstP_ModelRef1.SubmodelConfig.Gain = 2.3;
    ModelInstanceParameter.InstP_ModelRef1.SubmodelConfig.SomeOtherMember = 12.3;
    ModelInstanceParameter.InstP_ModelRef2.SubmodelConfig.Gain = 23.5;
    ModelInstanceParameter.InstP_ModelRef2.SubmodelConfig.SomeOtherMember = 355.1;

    ModelStruct.dwork = &ModelStates;
    ModelStruct.blockIO = &BlockSignals;
    ModelStruct.Controller_InstP_ref = &ModelInstanceParameter;

    Controller_initialize(&ModelStruct, &ModelInputs, &ModelOutputs);
}