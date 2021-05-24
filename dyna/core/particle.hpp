template <typename T> class dyna::Particle : public dyna::Entity<T>
{
public:
    T mass = 1 * hmath::unit::kilogram;
    T charge = 0 * hmath::unit::coulomb;

    Particle() {}
    ~Particle() {}

    Particle(T mass, T charge)
    {
        this->mass = mass;
        this->charge = charge;
    }

    Particle(T mass, T charge, dyna::StateVector<T> entity_state)
    {
        this->mass = mass;
        this->charge = charge;
        this->entity_state = entity_state;
    }

    Particle(hmath::DualQuaternion<T> kd0, hmath::DualQuaternion<T> kd1)
    {
        this->entity_state.kd0 = kd0;
        this->entity_state.kd1 = kd1;
    }

    Particle(T mass, T charge, hmath::DualQuaternion<T> kd0, hmath::DualQuaternion<T> kd1)
    {
        this->mass = mass;
        this->charge = charge;
        this->entity_state.kd0 = kd0;
        this->entity_state.kd1 = kd1;
    }

    // 3 degree of freedom calculation of relevant forces, and thus acceleration

    hmath::Vector3<T> _3DOF_NewtonianKinematics(dyna::Particle<T>* p2)
    {
        if (p2->mass > 0 && this->mass > 0)
        {
            // force due to charge

            long double q1, q2;

            q1 = this->charge;
            q2 = p2->charge;

            hmath::Vector3<T> r1, r2;

            r1.i = this->entity_state.kd0.ei;
            r1.j = this->entity_state.kd0.ej;
            r1.k = this->entity_state.kd0.ek;

            r2.i = p2->entity_state.kd0.ei;
            r2.j = p2->entity_state.kd0.ej;
            r2.k = p2->entity_state.kd0.ek;

            hmath::Vector3<T> r12 = r1 - r2;

            hmath::Vector3<T> f_c;

            f_c = r12.normed() / powf128(r12.norm(), 2);

            f_c *= (q1 * q2) / (4 * hmath::H_PI * hmath::unit::vaccuum_permittivity);

            // Acceleration due to charge

            hmath::Vector3<T> a_c = f_c / this->mass;

            // Force due to gravity

            T m1, m2;

            m1 = this->mass;
            m2 = p2->mass;

            hmath::Vector3<T> f_g;

            f_g = (-(hmath::unit::G * m1 * m2) / powf128(r12.norm(), 2)) * r12.normed();

            // Acceleration due to gravity

            hmath::Vector3<T> a_g = f_g / this->mass;

            // Totale acceleration = 

            hmath::Vector3<T> a_T = a_g + a_c;

            return a_T;
        }

        else
        {
            return { 0,0,0 };
        }
    }
};