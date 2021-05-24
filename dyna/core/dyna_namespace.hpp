namespace dyna
{
    // The state vector foundations of this physics engine

    template <typename T> class KD0;
    template <typename T> class KD1;
    template <typename T> class KD2;
    template <typename T> class StateVector;

    // The base physics object which has a state vector and id

    template <typename T> class Entity;

    // The base physics objects which have mass and charge

    template <typename T> class Particle;
    template <typename T> class Volume;
}