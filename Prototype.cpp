//
// Created by vladislav on 07.07.22.
//

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

class Prototype {
public:
    Prototype() = default;
    explicit Prototype(std::string prototype_name)
        : _prototype_name(std::move(prototype_name)) {}
    virtual ~Prototype() = default;

    virtual std::unique_ptr<Prototype> clone() const = 0;

protected:
    std::string _prototype_name;
};

int main() {


    return 0;
}