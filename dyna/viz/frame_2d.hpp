namespace dyna
{
    namespace viz
    {
        typedef size_t CARTESIAN_AXES;

        constexpr CARTESIAN_AXES X_AXIS = 0;
        constexpr CARTESIAN_AXES Y_AXIS = 1;
        constexpr CARTESIAN_AXES Z_AXIS = 2;

        template<typename T> class Frame2D
        {
        private:
            cv::Mat canvas;

        public:
            Frame2D() {}
            ~Frame2D() {}

            void draw(std::vector<hmath::Vector3<T>> positions, CARTESIAN_AXES axis_slice[2])
            {
                T min_0 = std::numeric_limits<T>::max();
                T min_1 = std::numeric_limits<T>::max();
                T max_0 = std::numeric_limits<T>::min();
                T max_1 = std::numeric_limits<T>::min();

                for (hmath::Vector3<T>& position : positions)
                {
                    hmath::Vector2<T> axes_of_interest = { position[axis_slice[0]],position[axis_slice[1]] };

                    if (axes_of_interest.i > max_0)
                    {
                        max_0 = axes_of_interest.i;
                    }

                    if (axes_of_interest.i < min_0)
                    {
                        min_0 = axes_of_interest.i;
                    }
                    
                    if (axes_of_interest.j > max_1)
                    {
                        max_1 = axes_of_interest.j;
                    }

                    if (axes_of_interest.j < min_1)
                    {
                        min_1 = axes_of_interest.j;
                    }                   
                }
                
                hmath::Vector3<T> bl = { min_0,min_1 };
                hmath::Vector3<T> tr = { max_0,max_1 };
            }
        };
    }    
}
