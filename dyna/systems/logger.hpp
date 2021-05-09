namespace dyna
{
    namespace system
    {
        template <typename T> class PositionalLogger
        {
        public:
            std::vector<NRB<T>*> nrb_ptrs;
            std::vector<std::vector<hmath::Vector3<T>>> positions;
            
            PositionalLogger() {}
            ~PositionalLogger() {}
        };
    }    
}
