# Simulink C-API Library
<i> Easy access to States, Parameters and Signals</i>

<b> Work in Progress</b>

## Example
```C++
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
```

## TODO
- [x] Basic scalar access is working.
- [ ] Allow access to non-scalars.
- [ ] Check feasibility of `std::optional<>`
- [ ] Add runtime type checking through introspection using [cleantype](https://github.com/pthom/cleantype)
- [ ] Write CMake script to easily add generated sources to build.
- [ ] Check if referenced models cause problems.

## Ideas
- change `bp.get<>()` to `bp.ref<>`
- introduce `bp.ptr<>`
- somehow allow non-scalars to be returned as `std::array<>`
