//
// Created by vladislav on 12.07.22.
//

/*
 * Паттерн Фасад
 *
 * Назначение: предоставляет простой интерфейс к сложной системе.
 */

#include <iostream>
#include <memory>

class Subsystem1 {
public:
    void _subsystem1_get_ready() const {
        std::cout << "Subsystem1: Ready!" << '\n';
    }

    void _subsystem1_run() const {
        std::cout << "Subsystem1 is currently running..." << '\n';
    }
};


class Subsystem2 {
public:
    void _subsystem2_get_ready() const {
        std::cout << "Subsystem2: Ready!" << '\n';
    }

    void _subsystem2_run() const {
        std::cout << "Subsystem2 is currently running..." << '\n';
    }
};


class Facade {
public:
    Facade()
        : _subsystem_1(), _subsystem_2() {}

    // Фасад выполняет всю настройку системы. Клиенту достаточно вызвать всего один метод фасада.
    void setup_system() {
        _subsystem_1->_subsystem1_get_ready();
        _subsystem_2->_subsystem2_get_ready();

        _subsystem_1->_subsystem1_run();
        _subsystem_2->_subsystem2_run();
    }

protected:
    std::unique_ptr<Subsystem1> _subsystem_1;
    std::unique_ptr<Subsystem2> _subsystem_2;
};

int main() {
    Facade facade;

    // Клиентский код работает с подсистемами через удобный интерфейс который предоставляет фасад
    facade.setup_system();
    return 0;
}