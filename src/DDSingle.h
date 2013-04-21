
#ifndef DDS_SHAREDLIB_DDSINGLE_H
#define DDS_SHAREDLIB_DDSINGLE_H

#include <pthread.h>
#include <stdlib.h>

namespace DDS
{
namespace SharedLib
{

template <typename type>

class DDSingle
{
    public:
        static type& instance ()
        {
            pthread_once (&m_once, &DDSingle::initialize);
            return (*m_value);
        }

    private:
        DDSingle (void);
        ~DDSingle (void);

        static void initialize (void)
        {
            m_value = new type();
            ::atexit (destroy);
        }

        static void destroy (void)
        {
            if (m_value)
                delete m_value;
        }

    private:
        static pthread_once_t m_once;
        static type*          m_value;
};

template <typename type>
pthread_once_t DDSingle<type>::m_once = PTHREAD_ONCE_INIT;

template <typename type>
type* DDSingle<type>::m_value = NULL;

}
}
// Usage:
// Foo& foo = DDSingle<Foo>::instance();

#endif
