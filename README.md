<!-- SPDX-License-Identifier: BSD-3-Clause-Clear -->
![License](https://img.shields.io/github/license/danishbelal/simulink-capi)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/e42b17ddc7ea4b86a2d1e9a4af8bcc77)](https://app.codacy.com/gh/danishbelal/simulink-capi?utm_source=github.com&utm_medium=referral&utm_content=danishbelal/simulink-capi&utm_campaign=Badge_Grade)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/danishbelal/simulink-capi.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/danishbelal/simulink-capi/context:cpp)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/danishbelal/simulink-capi.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/danishbelal/simulink-capi/alerts/)
[![Build Status](https://travis-ci.com/danishbelal/simulink-capi.svg?branch=dev)](https://travis-ci.com/danishbelal/simulink-capi)
[![CircleCI](https://circleci.com/gh/danishbelal/simulink-capi.svg?style=shield)](https://circleci.com/gh/danishbelal/simulink-capi)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/std/the-standard )

# Simulink C-API Library
<i> Easy access to States, Parameters and Signals</i>

## Overview
```C++
using namespace db::simulink;
BlockParameters bp { MMI(ModelStruct) };

// retrieve a reference
auto& Gain = bp.get<double>("Controller/Discrete-Time Integrator/gainval");
Gain = 24.2;

// or write directly
bp.get<double>("Controller/Discrete-Time Integrator/gainval") = 13.4;
```

This works the same for Signals, States and ModelParameters.

## Member-wise Bus access
Members can be accessed without instantiating and writing the whole Bus at once.

The recommended way to write Busses is like follows:
```C++
using namespace db::simulink;
ModelParameters mp { MMI(ModelStruct) };

// create new value
ConfigBus config {};
config.Gain = 1.23;
config.SomeOtherMember = 12.3;

// write the value to the model.
mp.get<ConfigBus>("Controller/ModelRef1/SubmodelConfig") = config;
```

However, in some circumstances it can be beneficial to access it member wise like this:
```C++
using namespace db::simulink;
BlockParameterBusBuilder bb(MMI(ModelStruct), "Controller/ModelRef1/SubmodelConfig");
bb.get<double>("Gain") = 1.23;
bb.get<double>("SomeOtherMember") = 12.3;
```
This approach requires less type information. Therefore its easier to obtain
new parameter values through deserialization as no `ConfigBus` objects need
to be created.

## Roadmap
 - Enable access to nested bus members without explicit instantiation
 - Make the library work without a heap
 - Remove UB from `get()`