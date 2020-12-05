<!-- SPDX-License-Identifier: BSD-3-Clause-Clear -->
![License](https://img.shields.io/github/license/danishbelal/simulink-capi)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/e42b17ddc7ea4b86a2d1e9a4af8bcc77)](https://app.codacy.com/gh/danishbelal/simulink-capi?utm_source=github.com&utm_medium=referral&utm_content=danishbelal/simulink-capi&utm_campaign=Badge_Grade)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/std/the-standard )

# Simulink C-API Library
<i> Easy access to States, Parameters and Signals</i>

## Overview
```C++
db::simulink::BlockParameters bp { MMI };

// retrieve a reference
auto& Gain = bp.get<double>("Controller/Discrete-Time Integrator/gainval");
Gain = 24.2;

// or write directly
bp.get<double>("Controller/Discrete-Time Integrator/gainval") = 13.4;
```
### More Elements
The same approach can be used for other C-API Elements.
```C++
db::simulink::ModelParameters mp { MMI };
db::simulink::BlockParameters bp { MMI };
db::simulink::States states { MMI };
db::simulink::Signals sigs { MMI };
```

Internally these are defined as follows:
```C++
using BlockParameters = CapiAccessor<rtwCAPI_BlockParameters>;
using ModelParameters = CapiAccessor<rtwCAPI_ModelParameters>;
using States = CapiAccessor<rtwCAPI_States>;
using Signals = CapiAccessor<rtwCAPI_Signals>;
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
bp.get<int>("Controller/Discrete-Time Integrator/gainval") = 13.4;
```
```console
terminate called after throwing an instance of 'std::runtime_error'
  what():  Type mismatch (double vs. int)
```

## TODO
- [x] Basic scalar access is working.
- [ ] Write `Matrix` class to return non-scalars.
- [ ] Check feasibility of `std::optional<>`
- [x] Add runtime type checking through introspection using [cleantype](https://github.com/pthom/cleantype)
- [ ] Write CMake script to easily add generated sources to build.
- [ ] Check if referenced models cause problems.
- [ ] Add CMake interface target.
- [ ] Add `ModelPath` constexpr-class.