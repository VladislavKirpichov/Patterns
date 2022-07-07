//
// Created by vladislav on 30.06.22.
//

#include <iostream>
#include <string>
#include <memory>

class Product {
public:
    virtual ~Product() = default;
    virtual std::string get_name_of_product() const  = 0;
};

class Smartphone : public Product {
public:
    std::string get_name_of_product() const override {
        return "Smartphone";
    }
};

class Laptop : public Product {
public:
    std::string get_name_of_product() const override {
        return "Laptop";
    }
};


class Creator {
public:
    virtual ~Creator() = default;

    // Factory Method
    virtual std::unique_ptr<Product> create_object() = 0;
};

class SmartphoneCreator : public Creator {
public:
    std::unique_ptr<Product> create_object() override {
        return std::make_unique<Smartphone>();
    }
};

class LaptopCreator : public Creator {
public:
    std::unique_ptr<Product> create_object() override {
        return std::make_unique<Laptop>();
    }
};

// creates laptop for every 2 smartphones
class FactoryLikeCreator : public Creator {
public:
    std::unique_ptr<Product> create_object() override {
        if (_counter == 2) {
            _counter = 0;
            return std::make_unique<Laptop>();
        }

        _counter++;
        return std::make_unique<Smartphone>();
    }

private:
    unsigned _counter = 0;
};

int main() {
    std::unique_ptr<Creator> factor_creator = std::make_unique<FactoryLikeCreator>();

    for (int i = 0; i < 10; ++i) {
        std::unique_ptr<Product> product = factor_creator->create_object();
        std::cout << "i = " << i << "; Product: " << product->get_name_of_product() << '\n';
    }

    return 0;
}

//  OUTPUT
//
//  i = 0; Product: Smartphone
//  i = 1; Product: Smartphone
//  i = 2; Product: Laptop
//  i = 3; Product: Smartphone
//  i = 4; Product: Smartphone
//  i = 5; Product: Laptop
//  i = 6; Product: Smartphone
//  i = 7; Product: Smartphone
//  i = 8; Product: Laptop
//  i = 9; Product: Smartphone