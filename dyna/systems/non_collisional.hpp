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
                for (PointMass<T>& point_mass : this->point_masses)
                {
                    /* code */
                }
                
                for (PointMass<T>& point_mass : this->point_masses)
                {
                    /* code */
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
                    /* code */
                }
                
                for (PointMass<T>& point_mass : this->point_masses)
                {
                    /* code */
                }
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
