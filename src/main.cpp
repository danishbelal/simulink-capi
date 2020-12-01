#include <iostream>
#include <string>

#include "CapiAccessor.hpp"
#include "Controller.h"
#include "icecream.hpp"

int main()
{

    ControllerModelClass Model;
    Model.initialize();

    auto RTM = Model.getRTM();
    rtwCAPI_ModelMappingInfo MMI = RTM->DataMapInfo.mmi;

    db::simulink::ModelParameters mp { MMI };
    db::simulink::BlockParameters bp { MMI };
    db::simulink::States states { MMI };
    db::simulink::Signals sigs { MMI };

    // retrieve a reference
    auto& Gain = bp.get<double>("Controller/Discrete-Time Integrator/gainval");
    auto& UnitDelayState = states.get<double>("Controller/Unit Delay/DSTATE");
    auto& Sum = sigs.get<double>("Controller/Sum/");
    auto& IntegratorState = states.get<double>("Controller/Unit Delay/DSTATE");

    Gain = 24.2;
    UnitDelayState = 12;
    IC(Gain);
    IC(UnitDelayState);

    // or write directly
    bp.get<double>("Controller/Discrete-Time Integrator/gainval") = 13.4;
    states.get<double>("Controller/Unit Delay/DSTATE") = 12.2;
    sigs.get<double>("Controller/Sum/") = 1.2;
    states.get<double>("Controller/Unit Delay/DSTATE") = 5.3;


    // Manuell gegenchecken.
    void* const* const AddrMap = rtwCAPI_GetDataAddressMap(&MMI);
    double* Gain2 { static_cast<double*>(rtwCAPI_GetDataAddress(AddrMap, 4)) };
    IC(*Gain2);

    Model.terminate();
    return 0;
}