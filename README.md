<!-- SPDX-License-Identifier: BSD-3-Clause-Clear -->
![License](https://img.shields.io/github/license/danishbelal/simulink-capi)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/e42b17ddc7ea4b86a2d1e9a4af8bcc77)](https://app.codacy.com/gh/danishbelal/simulink-capi?utm_source=github.com&utm_medium=referral&utm_content=danishbelal/simulink-capi&utm_campaign=Badge_Grade)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/danishbelal/simulink-capi.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/danishbelal/simulink-capi/context:cpp)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/danishbelal/simulink-capi.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/danishbelal/simulink-capi/alerts/)
[![Build Status](https://travis-ci.com/danishbelal/simulink-capi.svg?branch=beta)](https://travis-ci.com/danishbelal/simulink-capi)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/std/the-standard )

# Simulink C-API Library
<i> Easy access to States, Parameters and Signals</i>

## Overview
```C++
// Use Blockparameters with Exceptions enabled.
using BlockParameters = db::simulink::BlockParameters<decltype(ModelStruct)>;
BlockParameters bp { ModelStruct };

// retrieve a reference
auto& Gain = bp.get<double>("Controller/Discrete-Time Integrator/gainval");
Gain = 24.2;

// or write directly
bp.get<double>("Controller/Discrete-Time Integrator/gainval") = 13.4;
```

## Runtime type checking
Runtime type checking is supported. It can be enabled by `#define ENABLE_RUNTIME_TYPE_CHECKING`.
Using the wrong type leads to an exception being thrown.

Runtime type checking requires [cleantype](https://github.com/pthom/cleantype).
Make sure its in your include path.
```C++
using BlockParameters = db::simulink::BlockParameters<decltype(ModelStruct)>;
BlockParameters bp { ModelStruct };

// double is ok...
bp.get<double>("Controller/Discrete-Time Integrator/gainval") = 13.4;

// but int is not
bp.get<int>("Controller/Discrete-Time Integrator/gainval") = 13;
```
```console
terminate called after throwing an instance of 'std::runtime_error'
  what():  Type mismatch (double vs. int)
```