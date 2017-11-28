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

    class Test
    {
    private:
        int idx;

    public:
        Test() : idx(0) {}
        ~Test() { std::cout << "Call dtor Test" << std::endl; }

        void increment() { idx++; }

        int getIdx() {return idx; }
    };

    template class Singleton<Test>;
}

#endif //RUTILS_SINGLETON_HPP
