#include <iostream>
#include <vector>
#include <ostream>
#include <fstream>
#include <chrono>
#include <hmath/core.hpp>
#include <dyna/core.hpp>
#include <dyna/systems.hpp>

// Define some important constants

long double d_em = 4.6e10 * hmath::unit::meter;
long double v_em = 59.050e3 * hmath::unit::meter / hmath::unit::second;
long double m_sun = 1.989e30 * hmath::unit::kilogram;
long double m_mercury = 3.301e23 * hmath::unit::kilogram;

int main()
{
    // Define simulation paramters

    long double t_n = 270 * hmath::unit::day_ephemerides;

    std::vector<long double> dts;
    
    dts.push_back(0.1 * hmath::unit::day_ephemerides);
    dts.push_back(0.01 * hmath::unit::day_ephemerides);
    dts.push_back(0.001 * hmath::unit::day_ephemerides);

    for (long double dt : dts)
    {
        // Tell the user what timestep is being simulated

        std::cout << "Simulating for timestep dt = " << dt << std::endl;

        // Sun definition

        dyna::Particle<long double> m1;
        
        m1.mass = m_sun;

        // Mercury definition

        dyna::Particle<long double> m2;

        m2.mass = m_mercury;
        m2.entity_state(dyna::KD0<long double>(d_em,0,0));
        m2.entity_state(dyna::KD1<long double>(0,v_em,0));

         // Probe definition

        dyna::Particle<long double> m3;

        m3.mass = 500 * hmath::unit::kilogram;
        m3.entity_state(dyna::KD0<long double>(d_em + 50000000,0,0));
        m3.entity_state(dyna::KD1<long double>(0,v_em + 700,0));

        // System definition

        dyna::ParticleSystem<long double> env;
        env.dt = dt;

        env.addParticle(m1);
        env.addParticle(m2);
        env.addParticle(m3);

        // Set up csv to record m1, m2 data

        std::ofstream m1_csv, m2_csv, m3_csv;

        m1_csv.open("../three_body/m1_" + std::to_string(dt) + "_.csv");
        m2_csv.open("../three_body/m2_" + std::to_string(dt) + "_.csv");
        m3_csv.open("../three_body/m3_" + std::to_string(dt) + "_.csv");

        std::string header = "t_stamp,x,y,z,x_dot,y_dot,z_dot\n";

        m1_csv << header;
        m2_csv << header;
        m3_csv << header;

        // Set simulation start time

        long double t_0 = 0 * hmath::unit::day_ephemerides;

        while (t_0 < t_n)
        {
            env._3DOF_SymplecticNewtonianPropagation(&t_0);

            hmath::Vector3<long double> m1_kd0, m2_kd0, m3_kd0;
            hmath::Vector3<long double> m1_kd1, m2_kd1, m3_kd1;

            m1_kd0 = env.particles[0].entity_state.KD0();
            m2_kd0 = env.particles[1].entity_state.KD0();
            m3_kd0 = env.particles[2].entity_state.KD0();

            m1_kd1 = env.particles[0].entity_state.KD1();
            m2_kd1 = env.particles[1].entity_state.KD1();
            m3_kd1 = env.particles[2].entity_state.KD1();

            m1_csv << std::to_string(t_0) << ",";
            m2_csv << std::to_string(t_0) << ",";
            m3_csv << std::to_string(t_0) << ",";

            m1_csv << std::to_string(m1_kd0.i) << ",";
            m1_csv << std::to_string(m1_kd0.j) << ",";
            m1_csv << std::to_string(m1_kd0.k) << ",";

            m2_csv << std::to_string(m2_kd0.i) << ",";
            m2_csv << std::to_string(m2_kd0.j) << ",";
            m2_csv << std::to_string(m2_kd0.k) << ",";

            m3_csv << std::to_string(m3_kd0.i) << ",";
            m3_csv << std::to_string(m3_kd0.j) << ",";
            m3_csv << std::to_string(m3_kd0.k) << ",";

            m1_csv << std::to_string(m1_kd1.i) << ",";
            m1_csv << std::to_string(m1_kd1.j) << ",";
            m1_csv << std::to_string(m1_kd1.k) << "\n";

            m2_csv << std::to_string(m2_kd1.i) << ",";
            m2_csv << std::to_string(m2_kd1.j) << ",";
            m2_csv << std::to_string(m2_kd1.k) << "\n";

            m3_csv << std::to_string(m3_kd1.i) << ",";
            m3_csv << std::to_string(m3_kd1.j) << ",";
            m3_csv << std::to_string(m3_kd1.k) << "\n";
        }

        m1_csv.close();
        m2_csv.close();
        m3_csv.close();
    }
        
    return 0;
}