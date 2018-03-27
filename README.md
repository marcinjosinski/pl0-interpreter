[![Build Status](https://travis-ci.org/nnji/pl0-interpreter.svg?branch=master)](https://travis-ci.org/nnji/pl0-interpreter)

# PL0 Interpreter

https://en.wikipedia.org/wiki/PL/0

## Installation
To build PL0 Interpreter you need compiler with C++17 features support and at least CMake 3.2

```
mkdir build
cd build
cmake --build .
```

## Usage
```
./pl0 path_to_code.pl0
```
Example:
```
./pl0 ../../examples/ex1.pl0 
```
## To do

PL0 Virtual Machine and fix call_statement