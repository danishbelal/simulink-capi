#include <iostream>
#include <string>

#include "Accessor.hpp"
#include "Controller.h"
#include "Parameter.hpp"
#include "icecream.hpp"

void t(const rtwCAPI_ModelMappingInfo& MMI, const std::string Param)
{

    const std::size_t NumModelParameters = rtwCAPI_GetNumModelParameters(&MMI);
    const std::size_t NumBlockParameters = rtwCAPI_GetNumBlockParameters(&MMI);
    IC(NumModelParameters);
    IC(NumBlockParameters);

    const rtwCAPI_ModelParameters* const ModelParameters = rtwCAPI_GetModelParameters(&MMI);
    const rtwCAPI_BlockParameters* const BlockParameters = rtwCAPI_GetBlockParameters(&MMI);

    // Hier beginnt der schmutzige Weg mit ohne Typprüfung...
    const void* const* const AddrMap = rtwCAPI_GetDataAddressMap(&MMI);

    for (std::size_t i { 0 }; i < NumModelParameters; ++i)
    {
        IC(i);
        IC(rtwCAPI_GetModelParameterName(ModelParameters, i));
        IC(rtwCAPI_GetModelParameterDataTypeIdx(ModelParameters, i));
        IC(rtwCAPI_GetModelParameterDimensionIdx(ModelParameters, i));
        IC(rtwCAPI_GetModelParameterAddrIdx(ModelParameters, i));
        IC(rtwCAPI_GetModelParameterFixPtIdx(ModelParameters, i));
    }
    for (std::size_t i { 0 }; i < NumBlockParameters; ++i)
    {
        IC(i);
        IC(rtwCAPI_GetBlockParameterName(BlockParameters, i));
        IC(rtwCAPI_GetBlockParameterDataTypeIdx(BlockParameters, i));
        IC(rtwCAPI_GetBlockParameterDimensionIdx(BlockParameters, i));
        IC(rtwCAPI_GetBlockParameterAddrIdx(BlockParameters, i));
        IC(rtwCAPI_GetBlockParameterBlockPath(BlockParameters, i));
        IC(rtwCAPI_GetBlockParameterFixPtIdx(BlockParameters, i));

        const auto AddrIndex = rtwCAPI_GetBlockParameterAddrIdx(BlockParameters, i);
        IC(rtwCAPI_GetDataAddress(AddrMap, AddrIndex));
    }
}

int main()
{
    std::cout << "Hallo Welt" << std::endl;

    ControllerModelClass Model;
    Model.initialize();

    auto RTM = Model.getRTM();
    rtwCAPI_ModelMappingInfo MMI = RTM->DataMapInfo.mmi;
    // t(MMI, "");

    db::simulink::BlockParameters bp { MMI };
    auto& Gain = bp.get<double>("Controller/Discrete-Time Integrator/gainval");
    bp.get<double>("Controller/Discrete-Time Integrator/gainval") = 13.4;
    IC(Gain);
    Gain = 12.5;
    IC(Gain);

    // Manuell gegenchecken.
    void* const* const AddrMap = rtwCAPI_GetDataAddressMap(&MMI);
    double* Gain2 { static_cast<double*>(rtwCAPI_GetDataAddress(AddrMap, 4)) };
    IC(*Gain2);

    Model.terminate();
    return 0;
}