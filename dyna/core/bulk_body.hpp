namespace dyna
{
    template <typename T> class BB
    {
    public:
        dyna::td_chain::StateVectorOB<T> state_vector;

        BB() {}
        ~BB() {}
    };

    template <typename T> class SphericallyBoundedBody : public BB<T>
    {
    public:
        T radius;
        T mass;

        SphericallyBoundedBody() {}
        ~SphericallyBoundedBody() {}
    };
}
