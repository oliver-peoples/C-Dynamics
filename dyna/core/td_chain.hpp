namespace dyna
{
    namespace td_chain
    {
        // The non-oriented state vector implies no orientation for the object it
        // describes. This kind of restricted description of state is most useful
        // on point masses/charges.

        template <typename T> class StateVectorNO
        {
        public:
            hmath::Vector3<T> td0, td1;

            StateVectorNO() {}
            ~StateVectorNO() {}

            StateVectorNO(hmath::Vector3<T> position, hmath::Vector3<T> velocity)
            {
                this->td0 = position;
                this->td1 = velocity;
            }
        };

        // The orientable state vector implies that the object described has
        // significant orientation, that is, it's larger than a point and thus
        // it can have properties dependent on its orientation, rate of change
        // of orienation (spin), etc. The best way to represent orientation
        // and position, and their time derivatives, velocity and spin, is to
        // use the Dual Quaternion algebra.

        template <typename T> class StateVectorOB
        {
        public:
            hmath::DualQuaternion<T> td0, td1;

            StateVectorOB() {}
            ~StateVectorOB() {}

            StateVectorOB(StateVectorNO<T> state_vector, hmath::Quaternion<T> orientation, hmath::Quaternion<T> spin)
            {
                this->td0.R3_implication(state_vector.td0);
                this->td1.R3_implication(state_vector.td1);
                this->td0.S03_implication(orientation);
                this->td1.S03_implication(spin);
            }
        };
    }
}