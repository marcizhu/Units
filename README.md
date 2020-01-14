# Units :straight_ruler:
[![CodeFactor](https://www.codefactor.io/repository/github/marcizhu/units/badge)](https://www.codefactor.io/repository/github/marcizhu/units)
[![License](https://img.shields.io/github/license/marcizhu/units)](https://github.com/marcizhu/Units/blob/master/LICENSE)
[![Stability: Experimental](https://masterminds.github.io/stability/experimental.svg)](https://masterminds.github.io/stability/experimental.html)

A small, lightweight, fully `constexpr` C++14 library that allows to work with units and measurements at runtime, possibly
from user input or generated from real devices.

This library was designed to be intuitive, easy to use, portable and lightweight. The project is still under development,
and functions, type names, namespaces and others are subject to change in the near future. Any kind of input/feedback is
always welcome!

## Table of contents
- [Background](#background)
- [Install](#install)
- [Usage](#usage)
- [Limitations](#limitations)
- [Benchmarks](#benchmarks)
- [Alternatives](#alternatives)
- [Maintainer](#maintainer)
- [Credits](#credits)
- [Contributing](#contributing)
- [License](#license)

## Background
While working on another project of mine, I needed a library to be able to represent units of different kinds and be able to
use them in numerical calculations. The main objective of this library is to convert most used units to a standardized set
(the SI system) and to provide a single, lightweight type (instead of a bunch of different data types) that can represent
any unit from a wide range of disciplines such as, but not limited to, physics, chemistry, engineering, medicine, optics, 
computing, statistics, etc. This "single-type" philosophy helps using this library inside virtual functions where a type has 
to be specified at compile time.

As mentioned earlier, the main type provided by this library (`Units::Unit`) was desired to be lightweight (ideally under 8
bytes) so that it could be passed by value easily without any kind of overhead. This type can represent a wide range of units
and convert between units at runtime. This library does **NOT** provide compile-time unit checks, although because it is fully
`constexpr`-capable, it can be used this way for some specific scenarios. This units library provides support for operations
with units and it is intended to be used in applications where many (if not all) of the units to be used are unknown at
compile time.

This library is an engineering library, created to represent as many units as possible in a simple data type. No templates.
No polymorphism. No `virtual` calls. That's it. Simple and fast. It supports mathematical operations on units and quantities,
and all of them are `constexpr` to allow running some (or all) operations at compile-time if possible.

## Install
The provided `CMakeLists.txt` file exports a `Units::Units` library, so if your build system is based on CMake, you can use
that. If not, just copy the `include/Units` folder to your `include`/`vendor` folder and you're ready to go!

## Usage
The main type provided by this library is `Units::Unit`, which is defined inside `Units/Unit.h`. This type allows to hold
different units (for example, `m`, `m^3`, `m/s`, `W`, `J`...) but it does not allow to hold any magnitude associated with it.
For this reason, the type `Units::Quantity` is provided. It holds a unit plus a double, which will store the magnitude of the
measurement, allowing to represent, for example, `11.3 m`, `0.01 J`, `25.0 m/s` and so on.

The main objective of the library is to provide a transparent API for quantities. Therefore, a `Units::Quantity` can be
treated as if it was a `double`. The library provides addons to the `std` namespace to allow using `std::sin`, `std::abs`,
`std::pow`, `std::sqrt` and other functions. Quantities can also be compared (`>`, `<`, `>=`, `<=`, `==`, `!=`), assigned
to an arbitrary value/unit combination, read from `std::cin`/`std::string` and written to `std::cout`/`std::string`.

The size of a `Units::Unit` is exactly 4 bytes, while the size of a `Units::Quantity` is 16 bytes (8 bytes for the double, 4
bytes for the unit, and 4 bytes due to alignment requirements). The last 4 bytes of a quantity can be used to store any
arbitrary 32-bit unsigned number, allowing to store some user data.

The following minimalistic example shows the use of `constexpr` quantities and how to use some of the provided physics
constants and units:
```cpp
#include <iostream> // for std::cout

#include "Units/Constants.h"
#include "Units/Units.h"
#include "Units/IO.h"

int main()
{
    using namespace Units;
  
    constexpr Quantity earth_mass   = 5.972e24 * kg;
    constexpr Quantity earth_radius = 6371.0   * km;

    constexpr Quantity gravity = Constants::Physics::G * earth_mass / (earth_radius^2);
  
    std::cout << "Calculated earth gravity:  " << gravity << std::endl;
    std::cout << "Theoretical earth gravity: " << Constants::Physics::g << std::endl;
    
    // Output would be:
    // Calculated earth gravity:  9.820 m/s²
    // Theoretical earth gravity: 9.807 m/s²
}
```

For more examples, please take a look at the [examples/](https://github.com/marcizhu/Units/tree/master/examples) folder.

## Limitations
- Any unit is represented using the seven SI units + currency + count + radians. Any unit not representable using a combination of the units stated earlier is not representable using this library.
- Due to the small size of the `Units::Unit` type, the powers that can be represented by units are limited:
    - meters: [-8, +7]
    - kilogram: [-4, +3]
    - seconds: [-8, +7]
    - ampere: [-4, +3]
    - kelvin: [-8, +7]
    - mole: [-2, +1]
    - radians: [-4, +3]
    - candela: [-2, +1]
    - currency: [-2, +1]
    - count: [-2, +1]

    Exceeding this range for the exponents of their respective unit is undefined behavior. So, for example, `m^10` or `kg^-5`
    is UB. Please, be careful when the exponent of a unit is near the specified limit or when executing long formulas.
    
- The library uses a `double` to store real values, which should suffice in most cases but may lead to loss of precission on really long calculations.
- Currency is supported to allow basic financial calculations (like representing `$/Wh` or anything similar to that). This library is not recommended for economic or financial calculations.
- Fractional units are not supported. An exception to this is √Hz, which can be represented and is used for measuring amplitude spectral density (`V/√Hz`) and other similar units. √Hz can be obtained using `std::sqrt(Hz)`.

## Benchmarks
Comming soon

## Alternatives
This library is intended to be usable in most scenarios requiring units and run-time type checking, but this might not be
enough for you. If that's the case, you might want to check out the following libraries:
- [LLNL/units](https://github.com/LLNL/units): A run-time C++ library for working with units of measurement and conversions between them.
- [Boost.Units](https://www.boost.org/doc/libs/1_69_0/doc/html/boost_units.html): Zero-overhead dimensional analysis and unit/quantity manipulation and conversion in C++.
- [nholthaus/units](https://github.com/nholthaus/units): A compile-time, header-only, dimensional analysis and unit conversion library built on C++14 with no dependencies.
- [martinmoene/PhysUnits-RT](https://github.com/martinmoene/PhysUnits-RT): A C++ header-only library for run-time dimensional analysis and unit/quantity manipulation and conversion.
- [martinmoene/PhysUnits-CT](https://github.com/martinmoene/PhysUnits-CT): A C++ header-only library for compile-time dimensional analysis and unit/quantity manipulation and conversion.
- [unitscpp](https://code.google.com/archive/p/unitscpp/): A lightweight C++ library for physical calculation with units.
- [mpusz/units](https://github.com/mpusz/units): A Physical Units Library for C++ providing compile-time dimensional analysis and unit/quantity manipulation.

## Maintainer
This library was created and is currently maintained by [marcizhu](https://github.com/marcizhu).
If you find any issue with the library, you can either [open an issue](https://github.com/marcizhu/Units/issues) or e-mail me at marcizhu@gmail.com.

## Credits
The main idea and the list of unit conversions came from [LLNL/units](https://github.com/LLNL/units), although both libraries
have some major differences.

The list of constants provided by this library came from [this](https://en.wikipedia.org/wiki/List_of_physical_constants)
Wikipedia page, so thank you to anyone that contributed there too, as it really helped when it came to adding some
commonly-used physical constants to this library.

## Contributing
Does this library miss any feature you'd like to have? Have you spotted any bug? PRs are always welcome! Alternatively, you
can open an issue [here](https://github.com/marcizhu/Units/issues) or e-mail me at marcizhu@gmail.com and I'll try to
respond and/or fix it as soon as possible :D

## License
Copyright (c) 2019-2020 Marc Izquierdo  
This library is licensed under the [MIT License](https://choosealicense.com/licenses/mit/). See
[LICENSE](https://github.com/marcizhu/Units/blob/master/LICENSE) for more details.
