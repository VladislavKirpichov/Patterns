//
// Created by vladislav on 12.07.22.
//

/*
 * Паттерн приспособленец
 *
 * Назначение: уменьшение использования памяти за счет вынесения совместного использования
 */

#include <string>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <unordered_map>

enum class CarClass { Comfort, Buisness, Premium, Luxury };

// Shared state
struct CarType {
    explicit CarType(std::string model = "", std::string manufacturer = "", CarClass car_class = CarClass::Comfort,
            char ISO_type = 'A', int max_speed = 220)
            : model(std::move(model)),
              manufacturer(std::move(manufacturer)),
              car_class(car_class),
              ISO_type(ISO_type),
              max_speed(max_speed) {}

    std::string model;
    std::string manufacturer;
    CarClass car_class;
    char ISO_type;
    int max_speed;
};


// Приспособленец хранит общую часть состояния объектов.
class Flyweight {
public:
    Flyweight() = default;

    explicit Flyweight(CarType car_type)
            : _car_type(std::move(car_type)) {}

    Flyweight& operator=(const CarType& car_type) { _car_type = car_type; return *this; }
    CarType& get_car_type() { return _car_type; }
    [[nodiscard]] const CarType& get_car_type() const { return _car_type; }

private:
    CarType _car_type;
};


class FlyweightFactory {
public:
    FlyweightFactory(std::initializer_list<CarType> types) {
        for (auto& i : types) {
            _hash_table[hash_car_type(i)] = i;
        }
    }

    // Если такого типа нет, то фабрика создаст его
    Flyweight& get_flyweight(const CarType& car_type) { return _hash_table[hash_car_type(car_type)]; }

    void print_hash_table_size() const { std::cout << _hash_table.size() << '\n'; }

private:
    std::string hash_car_type(const CarType& car_type) const {
        return car_type.model + "_" + car_type.manufacturer;
    }

    std::unordered_map<std::string, Flyweight> _hash_table{};
};


// Unique state
class Car {
public:
    Car(std::string owner, Flyweight& flyweight)
        : _owner(std::move(owner)),
          _flyweight(flyweight) {}

    friend std::ostream &operator<<(std::ostream& os, const Car& car) {
        return os << "Owner: " << car._owner << '\n'
                  << "Info: " << car._flyweight.get_car_type().manufacturer
                  << ' ' << car._flyweight.get_car_type().model;
    }

protected:
    std::string _owner;

    // Хранить в каждом объекте машины отдельную структуру для ее типа не оптимально,
    // т.к. машин может быть очень много, а кол-во типов ограниченно.
    // CarType type;

    // Мы сэкономим много памяти если будем просто хранить ссылку на объект, который имеет доступ
    // к информации и типе машины.
    Flyweight& _flyweight;
};



int main() {
    CarType premium{"S-Class", "Mercedes-Benz", CarClass::Premium};
    CarType buisness{"E-Class", "Mercedes-Benz", CarClass::Buisness};
    CarType comfort{"A-Class", "Mercedes-Benz", CarClass::Comfort};

    FlyweightFactory factory{premium, buisness, comfort};

    std::vector<Car> cars;
    for (int i = 0; i < 100; ++i) {
        cars.emplace_back("John", factory.get_flyweight(premium));
        cars.emplace_back("Alex", factory.get_flyweight(buisness));
        cars.emplace_back("Rick", factory.get_flyweight(comfort));
    }

    for (auto& i : cars)
        std::cout << i << '\n';

    // Проверим сколько объектов CarType мы храним на данный момент. Всего было создано
    // 3 объекта CarType, хотя кол-во всех машин = 300
    factory.print_hash_table_size();

    return 0;
}