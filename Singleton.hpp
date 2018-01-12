//
// Created by Dowwind on 28/11/2017.
//

#ifndef RUTILS_SINGLETON_HPP
#define RUTILS_SINGLETON_HPP

#include <memory>
#include <iostream>

namespace rutils
{
    template <typename T>
    class Singleton
    {
    private:
        static T *singleton;
        Singleton() = default;

    public:
        Singleton& operator=(Singleton const &) = delete;
        Singleton(Singleton const &) = delete;

        ~Singleton() {
            std::cout << "Call dtor" << std::endl;
            reset();
        }

        static T &getSingleton()
        {
            if (singleton == nullptr)
                singleton = new T();
            return *singleton;
        }

        static void reset()
        {
            delete singleton;
            singleton = nullptr;
        }
    };
}

#endif //RUTILS_SINGLETON_HPP
