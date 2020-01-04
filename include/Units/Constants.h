#pragma once

#include "Units.h"

namespace Units
{
	namespace Constants
	{
		namespace Physics
		{
			// Planck length
			constexpr Quantity lP    = 1.61625518e-35 * m;
			// Planck mass
			constexpr Quantity mP    = 2.17643524e-8 * kg;
			// Planck time
			constexpr Quantity tP    = 5.39124760e-44 * s;
			// Planck charge
			constexpr Quantity qP    = 1.8755460377814e-18 * C;
			// Planck temperature
			constexpr Quantity TP    = 1.41678516e32 * K;
			// Avogadros constant (2019 redefinition)
			constexpr Quantity Na    = 6.02214076e23 * one / mol;
			// Elementary Charge (2019 redefinition)
			constexpr Quantity e     = 1.602176634e-19 * C;
			// Gravitational Constant
			constexpr Quantity G     = 6.67430e-11 * (m^3) * (kg^-1) * (s^-2);
			// Planck constant (2019 redefinition)
			constexpr Quantity h     = 6.62607015e-34 * J * s;
			// Reduced Planck constant
			constexpr Quantity h_    = 1.054571817e-34 * J * s;
			// Speed of light
			constexpr Quantity c     = 299792458.0 * m / s;
			// Vacuum electric permittivity
			constexpr Quantity eps0  = 8.8541878128e-12 * F / m;
			// Permeability of free space
			constexpr Quantity mu0   = 1.25663706212e-6 * N / (A^2);
			// Electron rest mass
			constexpr Quantity me    = 9.1093837015e-31 * kg;
			// Proton rest mass
			constexpr Quantity mp    = 1.67262192369e-27 * kg;
			// Neutron rest mass
			constexpr Quantity mn    = 1.67492749804e-27 * kg;
			// Coulomb's constant
			constexpr Quantity ke    = 8.9875517887e9 * N * (m^2) * (C^-2);
			// Fine-structure constant
			constexpr Quantity alpha = (e^2) / (2 * eps0 * h * c);
			// Hyperfine structure transition frequency of the caesium-133 atom
			constexpr Quantity fCs   = 9192631770.0 * Hz;
			// Boltzman constant (2019 redefinition)
			constexpr Quantity k     = 1.380649e-23 * J / K;
			// Luminous efficiency
			constexpr Quantity Kcd   = 683.0 * lm / W;
			// Molar gas constant (2019 redefinition)
			constexpr Quantity R     = 8.31446261815324 * J / (mol * K);
			// Stephan Boltzmann constant
			constexpr Quantity sigma = 5.67036713e-8 * W / ((m^2) * (K^4));
			// Standard gravity on Earth
			constexpr Quantity g0    = 9.80665 * m / (s^2);
			// Proton-to-electron mass ratio
			constexpr double PtoEmr  = 1836.15267343;
			// W-to-Z boson mass ratio
			constexpr double WtoZmr  = 0.88153;
			// Molar mass of Carbon-12
			constexpr Quantity mC12  = 11.9999999958e-3 * kg / mol;
		}

		namespace Maths
		{
			// Zero
			constexpr double zero   = 0.0;
			// One
			constexpr double one    = 1.0;
			// Imaginary unit
			constexpr Unit   i      = iflag;
			// tau
			constexpr double tau    = 6.28318530717958647692528676655900576;
			// tau/2 (also known as pi)
			constexpr double pi     = 3.14159265358979323846264338327950288;
			// Euler's number
			constexpr double e      = 2.71828182845904523536028747135266249;
			// Square root of 2
			constexpr double sqrt2  = 1.41421356237309504880168872420969807;
			// Square root of 3
			constexpr double sqrt3  = 1.73205080756887729352744634150587236;
			// Square root of 5
			constexpr double sqrt5  = 2.23606797749978969640917366873127623;
			// Euler-Mascheroni constant
			constexpr double gamma  = 0.57721566490153286060651209008240243;
			// Golden ratio
			constexpr double phi    = 1.61803398874989484820458683436563811;
			// Meissel-Mertens constant
			constexpr double M1     = 0.26149721284764278375542683860869585;
			// Bernstein's constant
			constexpr double beta   = 0.28016949902386913303;
			// Gauss-Kuzmin-Wirsing constant
			constexpr double lambda = 0.30366300289873265859744812190155623;
			// Hafner-Sarnak-McCurley constant
			constexpr double sigma  = 0.35323637185499598454351655043268201;
			// Omega constant
			constexpr double omega  = 0.56714329040978387299996866221035554;
			// Golomb-Dickman constant
			constexpr double mu     = 0.62432998854355087099293638310083724;
			// Twin prime constant
			constexpr double C2     = 0.66016181584686957392781211001455577;
			// Landau-Ramanujan constant
			constexpr double K      = 0.76422365358922066299069873125009232;
			// Apéry's constant
			constexpr double zeta3  = 1.20205690315959428539973816151144999;
			// Sierpinski's constant
			constexpr double K_     = 2.58498175957925321706589358738317116;
		}
	}
}
