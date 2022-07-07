//
// Created by vladislav on 07.07.22.
//

#include <iostream>

class Singleton {
public:
    Singleton() = default;

    static Singleton get_instance() {
        static Singleton singleton{};
        singleton.check++;
        return singleton;
    }

    int check = 0;
};

int main() {
    Singleton test_1 = Singleton::get_instance();
    Singleton test_2 = Singleton::get_instance();

    // Если бы создались 2 разных объекта, то вывелось 1 1
    std::cout << test_1.check << ' ' << test_2.check << '\n';   // 1 2
}