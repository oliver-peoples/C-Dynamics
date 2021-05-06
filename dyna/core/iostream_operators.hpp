template <typename sv_T> std::ostream& operator<<(std::ostream& os, dyna::td_chain::StateVectorNO<sv_T> sv)
{
    os << "{ " << sv.td0.i << ", " << sv.td0.j << ", " << sv.td0.k << ", " << sv.td1.i << ", " << sv.td1.j << sv.td1.k << " }";
    return os;
}

template <typename nrb_T> std::ostream& operator<<(std::ostream& os, dyna::NRB<nrb_T> nrb)
{
    os << "{ " << nrb.position().i << ", " << nrb.position().j << ", " << nrb.position().k << ", " << nrb.velocity().i << ", " << nrb.velocity().j << nrb.velocity().k << " }";
    return os;
}