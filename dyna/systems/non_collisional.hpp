namespace dyna
{
    namespace system
    {
        // Construction is not even defined for anything other than negligible
        // radius bodies and bulk bodies, so don't even try making a non
        // collisional system with something wild like a string.

        template <typename entity_type> class NonCollisionalSystem
        {
        public:
            NonCollisionalSystem();
            ~NonCollisionalSystem();
        };

        // Specialization for point masses
        
        template <typename T> class NonCollisionalSystem<PointMass<T>>
        {
        public:
            std::vector<PointMass<T>> point_masses;
            T dt;

            NonCollisionalSystem() {}
            ~NonCollisionalSystem() {}

            void addPointMass(PointMass<T> point_mass)
            {
                this->point_masses.push_back(point_mass);
            }

            PointMass<T>& operator[](size_t idx)
            {
                return this->point_masses[idx];
            }

            void symplecticEulerPropagation()
            {
                for (size_t study_point_idx = 0; study_point_idx < this->point_masses.size(); study_point_idx++)
                {
                    hmath::Vector3<T> td2 = { 0,0,0 };

                    hmath::Vector3<T> study_point = this->point_masses[study_point_idx].state_vector.td0;

                    for (size_t influencing_point_idx = 0; influencing_point_idx < this->point_masses.size(); influencing_point_idx++)
                    {
                        if (influencing_point_idx != study_point_idx)
                        {
                            hmath::Vector3<T> r = study_point - this->point_masses[influencing_point_idx].state_vector.td0;

                            td2 += -(this->dt * dyna::unit::G * (r / pow(r.norm(), 3)));
                        } 
                    }

                    this->point_masses[study_point_idx].state_vector.td1 += td2;
                }
                
                for (PointMass<T>& point_mass : this->point_masses)
                {
                    point_mass.state_vector.td0 += this->dt * point_mass.state_vector.td1; 
                }
            }

            void symplecticEulerPropagation(T& timestep)
            {
                this->symplecticEulerPropagation();
                timestep += dt;
            }

            void classicEulerPropagation()
            {
                for (PointMass<T>& point_mass : this->point_masses)
                {
                    point_mass.state_vector.td0 += this->dt * point_mass.state_vector.td1; 
                }

                for (size_t study_point_idx = 0; study_point_idx < this->point_masses.size(); study_point_idx++)
                {
                    hmath::Vector3<T> td2 = { 0,0,0 };

                    hmath::Vector3<T> study_point = this->point_masses[study_point_idx].td0;

                    for (size_t influencing_point_idx = 0; influencing_point_idx < this->point_masses.size(); influencing_point_idx++)
                    {
                        if (influencing_point_idx != study_point_idx)
                        {
                            hmath::Vector3<T> r = study_point - this->point_masses[influencing_point_idx].td0;

                            td2 += -(this->dt * dyna::unit::G * (r / pow(r.norm(), 3)));
                        } 
                    }

                    this->point_masses[study_point_idx].state_vector.td1 += td2;
                }
            }

            void classicalEulerPropagation(T& timestep)
            {
                this->symplecticEulerPropagation();
                timestep += dt;
            }
        };

        template <typename T> class NonCollisionalSystem<PointCharge<T>>
        {
        public:
            std::vector<PointCharge<T>> point_charges;
            T dt;

            NonCollisionalSystem() {}
            ~NonCollisionalSystem() {}

            void addPointCharge(PointCharge<T> point_mass)
            {
                this->point_masses.push_back(point_mass);
            }

            PointCharge<T>& operator[](size_t idx)
            {
                return this->point_masses[idx];
            }
        };       
    }
}
