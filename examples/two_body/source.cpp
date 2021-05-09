#include <iostream>
#include <vector>
#include <ostream>
#include <fstream>
#include <chrono>
#include <hmath.hpp>
#include <dyna/core.hpp>
#include <dyna/systems.hpp>
#include <dyna/viz.hpp>

std::vector<long double> dts;

int main()
{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // User editable variables
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Define simulation temporal domain

    long double t_0 = 0 * dyna::unit::day_ephemerides;
    long double t_n = 270 * dyna::unit::day_ephemerides;

    // The list of timesteps to run the simulation for

    dts.push_back(1.0e-1 * dyna::unit::day_ephemerides);
    dts.push_back(1.0e-2 * dyna::unit::day_ephemerides);
    dts.push_back(1.0e-3 * dyna::unit::day_ephemerides);
    dts.push_back(1.0e-4 * dyna::unit::day_ephemerides);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // That's it, nothing else you can edit!
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Define start parameters

    long double d_em = 4.6e10 * dyna::unit::meter;
    long double v_em = 59.050e3 * dyna::unit::meter / dyna::unit::second;
    long double m_sun = 1.989e30 * dyna::unit::kilogram;
    long double m_mercury = 3.301e23 * dyna::unit::kilogram;

    // For loop which we will run simulation variants in

    for (long double dt : dts)
    {
        // Tell the user what timestep is being simulated

        std::cout << "Simulating for timestep dt = " << dt << std::endl;

        // Sun definition (its m1)

        dyna::PointMass<long double> m1;
        
        m1.mass = m_sun;
        m1.position() = { 0,0,0 };
        m1.velocity() = { 0,0,0 };

        // Mercury definition (its m2)

        dyna::PointMass<long double> m2;

        m2.mass = m_mercury;
        m2.position() = { d_em,0,0 };
        m2.velocity() = { 0,v_em,0 };

        // Add these to a non collisional system

        dyna::system::NonCollisionalSystem<dyna::PointMass<long double>> system;

        system.dt = dt;

        system.addPointMass(m1);
        system.addPointMass(m2);

        // Set the origin of the epoch for the system

        long double epoch = t_0;

        // We are going to want to keep track of the positions of the orbiting bodies
        // so let's create a list of lists of points

        while (epoch < t_n)
        {
            system.symplecticEulerPropagation(epoch);
        }
    }
    
    return 0;
}