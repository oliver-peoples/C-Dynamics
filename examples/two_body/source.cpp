#include "../includes.hpp"

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

    dts.push_back(0.1 * dyna::unit::day_ephemerides);
    dts.push_back(0.01 * dyna::unit::day_ephemerides);
    dts.push_back(0.001 * dyna::unit::day_ephemerides);
    dts.push_back(1 * dyna::unit::second);

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

        std::cout << "test" << std::endl;
    }

    //     // Keep track of timesteps

    //     std::vector<long double> t_steps;

    //     // Set t = 0

    //     long double t = t_0;

    //     // Seed and keep track of epoch time steps

    //     std::vector<long double> t_stamps;
    //     t_stamps.push_back(0);

    //     auto t_stamp_0 = std::chrono::high_resolution_clock::now();

    //     // Main simulation loop

    //     for (t; t < t_n; t += dt)
    //     {
    //         hmath::Vector3<long double> r = m1.position - m2.position;

    //         long double r3 = powf128(powf128(r.i, 2) + powf128(r.j, 2) + powf128(r.k, 2), 1.5);

    //         m1.position += dt * m1.velocity;
    //         m2.position += dt * m2.velocity;

    //         m1.velocity += (-dt * dyna::unit::G * m2.mass * (r / r3));
    //         m2.velocity += (-dt * dyna::unit::G * m1.mass * ((-r) / r3));

    //         t_steps.push_back(t);

    //         auto t_stamp = std::chrono::high_resolution_clock::now();
    //         auto ns_int = std::chrono::duration_cast<std::chrono::nanoseconds>(t_stamp - t_stamp_0);

    //         t_stamps.push_back(ns_int.count() * 0.000000001);
    //     }

    //     // Save these results to a csv
    // }    

    // return 0;
}