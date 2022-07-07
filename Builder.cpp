//
// Created by vladislav on 06.07.22.
//

#include <iostream>
#include <string>
#include <utility>


struct Engine {
public:
    enum Type { Undefined, Slow, Medium, Fast };

public:
    Engine()
        : type(Slow) {}

    explicit Engine(std::string manufacture, Type type = Undefined)
        : manufacturer(std::move(manufacture)), type(type) {}

    std::string manufacturer;
    Type type;
};


class CarBuilder;


class Car {
public:
    Car(std::string name)
        : name(std::move(name)), mileage(0) {}

public:
    friend class CarBuilder;
    friend std::ostream &operator <<(std::ostream &output, const Car& car);

private:
    std::string name;
    Engine engine;
    std::string owner;
    unsigned int mileage;
};


class CarBuilder {
public:
    explicit CarBuilder(const std::string& name = "undefined")
        : car(name) {}

    CarBuilder set_name(const std::string& name)    { car.name = name; return *this; }
    CarBuilder set_engine(const Engine& engine)     { car.engine = engine; return *this;}
    CarBuilder set_owner(const std::string& owner)  { car.owner = owner; return *this; }
    CarBuilder set_mileage(unsigned int mileage)    { car.mileage = mileage; return *this; }

    Car get_car() { return car; }

private:
    Car car;
};

std::ostream &operator<<(std::ostream &output, const Car &car) {
    output << "Name: " << car.name << "  |  "
           << "Engine: " << car.engine.type << "  |  "
           << "Owner: " << car.owner << "  |  "
           << "Mileage:" << car.mileage << '\n';

    return output;
}

int main() {
    Engine bmw_engine       = Engine("BMW", Engine::Fast);
    Engine mercedes_engine  = Engine("Mercedes", Engine::Medium);

    CarBuilder car_builder{"BMW"};

    Car bmw         = car_builder.set_engine(bmw_engine).set_mileage(10000).set_owner("Vladislav").get_car();
    Car mercedes    = car_builder.set_name("Mercedes").set_owner("Alex").set_mileage(15000).set_engine(mercedes_engine).get_car();
    Car kia         = car_builder.set_name("Kia").set_owner("Stan").set_mileage(50000).get_car();

    std::cout << bmw;       // Name: BMW  |  Engine: 3  |  Owner: Vladislav  |  Mileage:10000
    std::cout << mercedes;  // Name: Mercedes  |  Engine: 2  |  Owner: Alex  |  Mileage:15000
    std::cout << kia;       // Name: Kia  |  Engine: 3  |  Owner: Stan  |  Mileage:50000

    return 0;
}