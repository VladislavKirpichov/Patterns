//
// Created by vladislav on 07.07.22.
//

#include <memory>
#include <iostream>

class PrototypeFactory {
public:
    template <typename T>
    requires std::is_copy_constructible_v<T>
    decltype(auto) clone(T& object) {
        return std::make_unique<T>(object);
    }
};

struct Checker {
    static inline int count = 1;

    Checker() = default;
    Checker(const Checker& checker) { count++; }

    friend std::ostream& operator<< (std::ostream& output, Checker& checker) {
        output << count << '\n';
        return output;
    }
};

int main() {
    Checker checker{};

    PrototypeFactory factory;
    std::cout << checker;       // 1

    auto new_checker = factory.clone<Checker>(checker);
    std::cout << *new_checker;  // 2

    return 0;
}