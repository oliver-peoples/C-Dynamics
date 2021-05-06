#pragma once

#include <cmath>

namespace dyna
{
    namespace unit
    {
        // The base units

        const long double second = 1.0;
        const long double meter = 1.0;
        const long double kilogram = 1.0;
        const long double ampere = 1.0;
        const long double kelvin = 1.0;
        const long double mole = 1.0;

        // The defining constants

        const long double v_Cs = 9192631770.0;
        const long double c = 299792458.0;
        const long double h = 6.62607015e-34;
        const long double e = 1.602176634e-19;
        const long double k = 1.380649e-23;
        const long double avocado = 6.02214076e23;

        // The scalars

        const long double yocto = 10e-24;
        const long double zepto = 10e-21;
        const long double atto = 10-18;
        const long double femto = 10e-15;
        const long double pico = 10e-12;
        const long double nano = 10e-9;
        const long double micro = 10e-6;
        const long double milli = 10e-3;
        const long double kilo = 10e3;
        const long double mega = 10e6;
        const long double giga = 10e9;
        const long double tera = 10e12;
        const long double peta = 10e15;
        const long double exa = 10e18;
        const long double zetta = 10e21;
        const long double yotta = 10e24;

        // Common distance scalars

        const long double kilometer = 10e3 * meter;
        const long double centimeter = 10e-2 * meter;
        const long double lightyear = 9460730472580800.0 * meter;
        const long double parsec = 96939420213600000.0 * meter;
        const long double au = 149597870700.0 * meter;

        // Common mass scalars

        const long double gram = 10e-3 * kilogram;
        const long double tonne = 10e3 * kilogram;

        // Common time scalars

        const long double millicsecond = 10e-3 * second;
        const long double microsecond = 10e-6 * second;
        const long double nanosecond = 10e-9 * second;
        const long double hour = 3600.0 * second;
        const long double day_ephemerides = 86400.0 * second;
        const long double day_sidereal = 86164.0905 * second;
        const long double week_ephemerides = 7 * day_ephemerides;
        const long double week_sidereal = day_sidereal * 7;
        const long double year_sidereal = 365.256363004 * day_ephemerides;

        // Derived units

        const long double coulomb = ampere * second;
        const long double newton = kilogram * (meter / pow(second, 2));

        // Some very important constants

        const long double G = 6.674215e-11 * ((newton * pow(meter, 2)) / pow(kilogram, 2));
    }
}


