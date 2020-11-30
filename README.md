# Simulink C-API Library
<i> Easy access to States, Parameters and Signals</i>

<b> Work in Progress</b>

## Example
Assuming a BlockParameter *gainval* exists at *Controller/Discrete-Time Integrator*, it can be accessed like this.
```C++
db::simulink::BlockParameters bp { MMI };

// retrieve a reference
auto& Gain = bp.get<double>("Controller/Discrete-Time Integrator/gainval");
Gain = 24.2;

// or write directly
bp.get<double>("Controller/Discrete-Time Integrator/gainval") = 13.4;
```

## TODO
- [ ] Check feasibility of `std::optional<>`

## Ideas
- change `bp.get<>()` to `bp.ref<>`
- introduce `bp.ptr<>`
- somehow allow non-scalars to be returned as `std::array<>`
