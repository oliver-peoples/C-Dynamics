namespace dyna
{
    // For point mass/charge systems, radius of the point is necessarily...negligible.
    // This leads to the concept of a negligible radius body, an abstract container
    // for the idea of a point _____. It carries the important information, then lets
    // further development occur in classes which inherit the NRB characteristics

    template <typename T> class NRB
    {
    public:
        td_chain::StateVectorNO<T> state_vector;

        NRB() {}
        ~NRB() {}

        NRB(td_chain::StateVectorNO<T> state_vector)
        {
            this->state_vector = state_vector;
        }

        NRB(T td0_i, T td0_j, T td0_k, T td1_i, T td1_j, T td1_k)
        {
            this->state_vector.td0 = { td0_i,td0_j,td0_k };
            this->state_vector.td1 = { td1_i,td1_j,td1_k };
        }

        hmath::Vector3<T>& position()
        {
            return this->state_vector.td0;
        }

        hmath::Vector3<T>& velocity()
        {
            return this->state_vector.td1;
        }
    };

    template <typename T> class PointMass : public NRB<T>
    {
    public:
        T mass;

        using NRB<T>::NRB;

        PointMass() {}
        ~PointMass() {}

        PointMass(T td0_i, T td0_j, T td0_k, T td1_i, T td1_j, T td1_k, T mass)
        {
            this->state_vector.td0 = { td0_i,td0_j,td0_k };
            this->state_vector.td1 = { td1_i,td1_j,td1_k };
            this->mass = mass;
        }
    };

    template <typename T> class PointCharge : public NRB<T>
    {
    public:
        T charge;

        using NRB<T>::NRB;

        PointCharge() {}
        ~PointCharge() {}

        PointCharge(T td0_i, T td0_j, T td0_k, T td1_i, T td1_j, T td1_k, T charge)
        {
            this->state_vector.td0 = { td0_i,td0_j,td0_k };
            this->state_vector.td1 = { td1_i,td1_j,td1_k };
            this->charge = charge;
        }
    };  
}
