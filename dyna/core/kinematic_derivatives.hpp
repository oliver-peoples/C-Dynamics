template <typename T> class dyna::KD0 : public hmath::Vector3<T>
{
public:
    using hmath::Vector3<T>::Vector3;

    KD0() {}
    ~KD0() {}

    KD0(hmath::Vector3<T> v)
    {
        this->i = v.i;
        this->j = v.j;
        this->k = v.k;
    }
};

template <typename T> class dyna::KD1 : public hmath::Vector3<T>
{
public:
    using hmath::Vector3<T>::Vector3;

    KD1() {}
    ~KD1() {}

    KD1(hmath::Vector3<T> v)
    {
        this->i = v.i;
        this->j = v.j;
        this->k = v.k;
    }
};

template <typename T> class dyna::KD2 : public hmath::Vector3<T>
{
public:
    using hmath::Vector3<T>::Vector3;
    
    KD2() {}
    ~KD2() {}

    KD2(hmath::Vector3<T> v)
    {
        this->i = v.i;
        this->j = v.j;
        this->k = v.k;
    }
};

template <typename T> class dyna::StateVector
{
public:
    hmath::DualQuaternion<T> kd0 = { 1,0,0,0,0,0,0,0 };
    hmath::DualQuaternion<T> kd1 = { 1,0,0,0,0,0,0,0 };

    StateVector() {}
    ~StateVector() {}

    StateVector(hmath::DualQuaternion<T> q0, hmath::DualQuaternion<T> q1)
    {
        this->kd0 = q0;
        this->kd1 = q1;
    }

    dyna::KD0<T> KD0()
    {
        dyna::KD0<T> kd0;

        kd0.i = this->kd0.ei;
        kd0.j = this->kd0.ej;
        kd0.k = this->kd0.ek;

        return kd0;
    }

    dyna::KD1<T> KD1()
    {
        dyna::KD1<T> kd1;

        kd1.i = this->kd1.ei;
        kd1.j = this->kd1.ej;
        kd1.k = this->kd1.ek;

        return kd1;
    }

    void operator()(dyna::KD0<T> kd0)
    {
        this->kd0.ei = kd0.i;
        this->kd0.ej = kd0.j;
        this->kd0.ek = kd0.k;
    }

    void operator()(dyna::KD1<T> kd1)
    {
        this->kd1.ei = kd1.i;
        this->kd1.ej = kd1.j;
        this->kd1.ek = kd1.k;
    }

    void operator+=(dyna::KD1<T> kd1)
    {
        this->kd0.ei += kd1.i;
        this->kd0.ej += kd1.j;
        this->kd0.ek += kd1.k;
    }

    void operator+=(dyna::KD2<T> kd2)
    {
        this->kd1.ei += kd2.i;
        this->kd1.ej += kd2.j;
        this->kd1.ek += kd2.k;
    }
};