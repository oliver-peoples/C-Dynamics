#include <dyna/core.hpp>
#include <dyna/systems.hpp>

int main()
{
    long double dt = 1e-10 * hmath::unit::second;

    dyna::Particle<long double> particle_1, particle_2, particle_3;

    particle_1.mass = 0.1 * hmath::unit::kilogram;
    // particle_1.charge = 2000 * hmath::unit::coulomb;

    particle_2 = particle_1;
    particle_3 = particle_1;
    
    particle_1.entity_state.kd0.ei = 100;
    particle_2.entity_state.kd0.ei = -100;
    particle_3.entity_state.kd0.ej = 173.20508;

    particle_1.entity_state.kd1.ek = 10;
    particle_2.entity_state.kd1.ek = 10;
    particle_3.entity_state.kd1.ek = 10;

    particle_2.charge *= -1;
    particle_3.charge *= -1;

    dyna::ParticleSystem<long double> particle_system;

    particle_system.addParticle(&particle_1);
    particle_system.addParticle(&particle_2);
    particle_system.addParticle(&particle_3);

    long double time_step = 0;

    while (time_step < 20 * hmath::unit::day_ephemerides)
    {
        particle_system._3DOF_SymplecticNewtonianPropagation(&time_step);
    }
    
    return 0;
}