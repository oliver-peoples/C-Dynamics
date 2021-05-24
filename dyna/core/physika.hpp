template <typename T> class dyna::Entity
{
public:
    dyna::StateVector<T> entity_state;

    Entity() {}
    ~Entity() {}
};
    