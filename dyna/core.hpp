#pragma once

#include <hmath.hpp>
#include <promote.hpp>
#include <cgeo/core.hpp>

namespace dyna
{
    template <typename T> class Particle : public cgeo::PointE3<T>
    {
    private:
        T _mass = 0;
        T _charge = 0;
        hmath::Vector3<T> _velocity;
    public:
        

        Particle() {}
        ~Particle() {}

        T& mass()
        {
            return this->_mass;
        }

        T& charge()
        {
            return this->_charge;
        }

        hmath::Vector3<T>& velocity()
        {
            return this->_velocity;
        }
    };

    template <typename T> class ParticleSystem
    {
    private:
        std::vector<Particle<T>> particles;
        
    public:
        ParticleSystem() {}
        ~ParticleSystem() {}

        ParticleSystem(std::vector<Particle<T>>& particles)
        {
            this->particles = particles;
        }

        void addPoint(Particle<T> particle)
        {
            this->particles.push_back(particle);
        }

        size_t cardinality()
        {
            return this->particles.size();
        }
    };

    template <typename T> class ParticleCloud
    {
    private:
        bool c_o_m_updated = false;
        Particle<T> c_o_m;
        std::vector<Particle<T>*> particles;
        hmath::Vector3<T> velocity;
        hmath::Quaternion<T> spin;
    public:
        ParticleCloud() {}
        ~ParticleCloud() {}

        void addPoint(Particle<T>* particle)
        {
            this->particles.push_back(particle);
        }

        size_t cardinality()
        {
            return this->particles.size();
        }

        Particle<T> getCoM()
        {
            if (this->c_o_m_updated)
            {
                return this->c_o_m;
            }
            
            else if (!this->c_o_m_updated)
            {
                hmath::Vector3<T> r_sum = { 0,0,0 };
                T m_sum = 0;

                for (Particle<T>* particle : particles)
                {
                    r_sum += { particle->a(),particle->b(),particle->c() };
                    m_sum += particle->getMass();
                }

                r_sum /= T(this->particles.size());
            }
        }
    };
}
