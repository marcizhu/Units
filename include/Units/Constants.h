#pragma once

#include "Units.h"

namespace Units
{
	namespace Constants
	{
		namespace Physics
		{
			/** @brief Planck length */
			const Quantity lP    = 1.61625518e-35 * m;
			/** @brief Planck mass */
			const Quantity mP    = 2.17643524e-8 * kg;
			/** @brief Planck time */
			const Quantity tP    = 5.39124760e-44 * s;
			/** @brief Planck charge */
			const Quantity qP    = 1.8755460377814e-18 * C;
			/** @brief Planck temperature */
			const Quantity TP    = 1.41678516e32 * K;
			/** @brief Avogadros constant (2019 redefinition) */
			const Quantity Na    = 6.02214076e23 * one / mol;
			/** @brief Elementary Charge (2019 redefinition) */
			const Quantity e     = 1.602176634e-19 * C;
			/** @brief Gravitational Constant */
			const Quantity G     = 6.67430e-11 * (m^3) * (kg^-1) * (s^-2);
			/** @brief Planck constant (2019 redefinition) */
			const Quantity h     = 6.62607015e-34 * J * s;
			/** @brief Reduced Planck constant */
			const Quantity hbar  = 1.054571817e-34 * J * s;
			/** @brief Speed of light */
			const Quantity c     = 299792458.0 * m / s;
			/** @brief Vacuum electric permittivity */
			const Quantity eps0  = 8.8541878128e-12 * F / m;
			/** @brief Permeability of free space */
			const Quantity mu0   = 1.25663706212e-6 * N / (A^2);
			/** @brief Electron rest mass */
			const Quantity m_e   = 9.1093837015e-31 * kg;
			/** @brief Proton rest mass */
			const Quantity m_p   = 1.67262192369e-27 * kg;
			/** @brief Neutron rest mass */
			const Quantity m_n   = 1.67492749804e-27 * kg;
			/** @brief Coulomb's constant */
			const Quantity ke    = 8.9875517887e9 * N * (m^2) * (C^-2);
			/** @brief Fine-structure constant */
			const Quantity alpha = 1.0 / 137.03599971096;
			/** @brief Hyperfine structure transition frequency of the caesium-133 atom */
			const Quantity fCs   = 9192631770.0 * Hz;
			/** @brief Boltzman constant (2019 redefinition) */
			const Quantity k     = 1.380649e-23 * J / K;
			/** @brief Luminous efficiency */
			const Quantity Kcd   = 683.0 * lm / W;
			/** @brief Molar gas constant (2019 redefinition) */
			const Quantity R     = 8.31446261815324 * J / (mol * K);
			/** @brief Stephan-Boltzmann constant */
			const Quantity sigma = 5.67036713e-8 * W / ((m^2) * (K^4));
			/** @brief Standard gravity on Earth */
			const Quantity g     = 9.80665 * m / (s^2);
			/** @brief Proton-to-electron mass ratio */
			const double PtoEmr  = 1836.15267343;
			/** @brief W-to-Z boson mass ratio */
			const double WtoZmr  = 0.88153;
			/** @brief Molar mass of Carbon-12 */
			const Quantity mC12  = 11.9999999958e-3 * kg / mol;
			/** @brief Faraday's constant */
			const Quantity F     = 9.64853321233100184e4 * C / mol;
		}

		namespace Maths
		{
			/** @brief Zero */
			const double zero   = 0.0;
			/** @brief One */
			const double one    = 1.0;
			/** @brief Imaginary unit */
			const Unit   i      = iflag;
			/** @brief tau */
			const double tau    = 6.28318530717958647692528676655900576;
			/** @brief tau/2 (also known as pi) */
			const double pi     = 3.14159265358979323846264338327950288;
			/** @brief Euler's number */
			const double e      = 2.71828182845904523536028747135266249;
			/** @brief Square root of 2 */
			const double sqrt2  = 1.41421356237309504880168872420969807;
			/** @brief Square root of 3 */
			const double sqrt3  = 1.73205080756887729352744634150587236;
			/** @brief Square root of 5 */
			const double sqrt5  = 2.23606797749978969640917366873127623;
			/** @brief Euler-Mascheroni constant */
			const double gamma  = 0.57721566490153286060651209008240243;
			/** @brief Golden ratio */
			const double phi    = 1.61803398874989484820458683436563811;
			/** @brief Meissel-Mertens constant */
			const double M1     = 0.26149721284764278375542683860869585;
			/** @brief Bernstein's constant */
			const double beta   = 0.28016949902386913303;
			/** @brief Gauss-Kuzmin-Wirsing constant */
			const double lambda = 0.30366300289873265859744812190155623;
			/** @brief Hafner-Sarnak-McCurley constant */
			const double sigma  = 0.35323637185499598454351655043268201;
			/** @brief Omega constant */
			const double omega  = 0.56714329040978387299996866221035554;
			/** @brief Golomb-Dickman constant */
			const double mu     = 0.62432998854355087099293638310083724;
			/** @brief Twin prime constant */
			const double C2     = 0.66016181584686957392781211001455577;
			/** @brief Landau-Ramanujan constant */
			const double K      = 0.76422365358922066299069873125009232;
			/** @brief Apéry's constant */
			const double zeta3  = 1.20205690315959428539973816151144999;
			/** @brief Sierpinski's constant */
			const double K_     = 2.58498175957925321706589358738317116;
		}
	}
}
