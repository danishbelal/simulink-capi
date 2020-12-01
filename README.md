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

## Runtime type checking
Runtime type checking is supported. It can be enabled by `#define ENABLE_RUNTIME_TYPE_CHECKING`.
Using the wrong type leads to an exception being thrown.

Runtime type checking requires [cleantype](https://github.com/pthom/cleantype).
Make sure its in your include path.
```C++
db::simulink::BlockParameters bp { MMI };

// double is ok...
bp.get<double>("Controller/Discrete-Time Integrator/gainval") = 13.4;

// but float is not
bp.get<float>("Controller/Discrete-Time Integrator/gainval") = 13.4;
```
```console
terminate called after throwing an instance of 'std::runtime_error'
  what():  Type mismatch (double vs. float)
```

## TODO
- [x] Basic scalar access is working.
- [ ] Allow access to non-scalars.
- [ ] Check feasibility of `std::optional<>`
- [x] Add runtime type checking through introspection using [cleantype](https://github.com/pthom/cleantype)
- [ ] Write CMake script to easily add generated sources to build.
- [ ] Check if referenced models cause problems.

## Ideas
- change `bp.get<>()` to `bp.ref<>`
- introduce `bp.ptr<>`
- somehow allow non-scalars to be returned as `std::array<>`
