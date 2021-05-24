template <typename T> class dyna::ParticleSystem
{
public:
    T dt = 0.001 * hmath::unit::second;
    std::vector<dyna::Particle<T>> particles;

    ParticleSystem() {}
    ~ParticleSystem() {}

    ParticleSystem(std::vector<dyna::Particle<T>>& particles)
    {
        this->particles = particles;
    }

    void addParticles(std::vector<dyna::Particle<T>> particles)
    {
        for (dyna::Particle<T>& particle : particles)
        {
            this->particles.push_back(particle);
        }
    }

    void addParticles(std::vector<dyna::Particle<T>>* particles_ptr)
    {
        for (dyna::Particle<T>& particle : *particles_ptr)
        {
            this->particles.push_back(particle);
        }
    }

    void addParticle(dyna::Particle<T> particle)
    {
        this->particles.push_back(particle);
    }

    void addParticle(dyna::Particle<T>* particle)
    {
        this->particles.push_back(*particle);
    }

    void _3DOF_SymplecticNewtonianPropagation(T* time_step)
    {
        size_t entity_count = this->particles.size();

        for (size_t e1_idx = 0; e1_idx < entity_count; e1_idx++)
        {
            dyna::Particle<T>* e1_ptr = &this->particles[e1_idx];

            for (size_t e2_idx = 0; e2_idx < entity_count; e2_idx++)
            {
                if (e1_idx != e2_idx)
                {
                    dyna::Particle<T>* e2_ptr = &this->particles[e2_idx];

                    dyna::KD2<T> a_e2;
                    a_e2 = e1_ptr->_3DOF_NewtonianKinematics(e2_ptr);
                    a_e2 *= this->dt;

                    e1_ptr->entity_state += a_e2;
                }
            }
        }

        for (dyna::Particle<T>& particle : this->particles)
        {
            dyna::KD1<T> v_T;
            v_T = particle.entity_state.KD1();
            v_T *= this->dt;
            particle.entity_state += v_T;
        }

        *time_step += this->dt;
    }
};