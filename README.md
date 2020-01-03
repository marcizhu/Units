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
any unit from a wide range of disciplines such as, but not limited to, physics, chemistry, engineering, medicine, optics, computing,
statistics, etc. This "single-type" philosophy helps using this library inside virtual functions where a type has to be
specified at compile time.

As mentioned earlier, the main type provided by this library (`Units::Unit`) was desired to be lightweight (ideally under 8
bytes) so that it could be passed by value easily without any kind of overhead. This type can represent a wide range of units
and convert between units at runtime. This library does **NOT** provide compile-time unit checks, although because it is fully
`constexpr`-capable, it can be used this way for some specific scenarios. This units library provides support for operations
with units and it is intended to be used in applications where many (if not all) of the units to be used are unknown at compile
time.

This library is an engineering library, created to represent as many units as possible in a simple data type. No templates.
No polymorphism. No `virtual` calls. That's it. Simple and fast. It supports mathematical operations on units and quantities,
and all of them are `constexpr` to allow running some (or all) operations at compile-time if possible.

## Install
The provided `CMakeLists.txt` file exports a `Units::Units` library, so if your build system is based on CMake, you can use
that. If not, just copy the `include/Units` folder to your `include`/`vendor` library and you're ready to go!

## Usage
The main type provided by this library is `Units::Unit`, which is defined inside `Units/Unit.h`. This type allows to hold
different units (for example, `m`, `m^3`, `m/s`, `W`, `J`...) but it does not allow to hold any magnitude associated with it.
For this reason, the type `Units::Quantity` is provided. It holds a unit plus a double, which will store the magnitude of the
measurement, allowing to represent, for example, `11.3 m`, `0.01 J`, `25.0 m/s` and so on.

The main objective of the library is to provide a transparent API for quantities. Therefore, a `Units::Quantity` can be
treated as if it was a `double`. The library provides addons to the `std` namespace to allow using `std::sin`, `std::abs`,
`std::pow`, `std::sqrt` and other functions. Quantities can also be compared (`>`, `<`, `>=`, `<=`, `==`, `!=`) and assigned
to an arbitrary value/unit combination.

The size of a `Units::Unit` is exactly 4 bytes, while the size of a `Units::Quantity` is 16 bytes (8 bytes for the double, 4
bytes for the unit, and 4 bytes due to alignment requirements). The last 4 bytes of a quantity can be used to store any
arbitrary 32-bit unsigned number, allowing to store some user data.

The following minimalistic snippet shows the use of `constexpr` quantities and how to use some of the provided physics
constants:
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
    std::cout << "Theoretical earth gravity: " << Constants::Physics::g0 << std::endl;
}
```

The following code showcases a more detailed use of units and quantities, as well as some of the `std` addons, comparison
operators, input and output:
```cpp
#include <iostream> // for std::cout

#include "Units/Units.h" // provides commonly used units and conversions
#include "Units/Unit.h" // for Units::Unit
#include "Units/Quantity.h" // for Units::Quantity
#include "Units/IO.h" // provides operator<< for units & quantities

int main()
{
    using namespace Units;
    
    // Units
    Unit velocity = meters / second; // Now velocity is a unit of "m/s"
    Unit vel = m / s; // same as before, but using short unit names
    Unit accel = m / (s^2); // accleration, in m/s^2
    Unit power1 = W; // Watt
    Unit power2 = J / s; // Same as W
    
    Unit input1, input2;
    std::cin >> input1; // Read unit from std::cin
    input2 = from_string("Sv"); // Read unit from string. input2 == Units::Sv (Sievert)
    
    std::cout << velocity << std::endl; // Will print "m/s"
    std::cout << accel << std::endl; // Will print "m/s²"
    std::cout << power << std::endl; // Will print "W"
    
    std::string formatted = to_string(accel); // formatted = "m/s²"
    
    // Quantities
    Quantity speed1 = 25.0 * m / s; // Represents 25 m/s
    Quantity speed2 = 25.0 * vel; // Same as above, but using a predefined unit
    Quantity speed3 = 60.0 * mile / h; // This will convert the 60.0 mph to m/s internally
    
    std::cout << speed1 << std::endl; // Will print "25.00 m/s"
    std::cout << speed2 << std::endl; // Will print "25.00 m/s"
    std::cout << speed3 << std::endl; // Will print "6.706 m/s"
    
    std::string formatted = to_string(speed1); // formatted == "25.00 m/s"
    
    Quantity input3, input4;
    std::cin >> input3; // Read quantity from std::cin
    input4 = from_string("100.3 kHz"); Read quantity from string. Represents 100.3 kilohertz
    
    // Comparison operators
    if(speed3 > speed1)
        std::cout << "60 mph > 25 m/s" << std::endl;
    
    // Arithmetic functions
    Quantity q1 = std::pow(speed1, 2); // 625 m²/s²
    Quantity q2 = speed1^2; // Same as above
    Quantity q3 = std::sqrt(q1); // 25 m/s again
}
```

## Benchmarks
Comming soon

## Alternatives
This library is intended to be usable in most scenarios requiring units and run-time type checking, but this might not be
enough for you. If that's the case, you might want to check the following libraries:
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
This library is licensed under the [MIT License](https://choosealicense.com/licenses/mit/). See
[LICENSE](https://github.com/marcizhu/Units/blob/master/LICENSE) for more details.
