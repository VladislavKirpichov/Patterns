/*
 * Facade pattern
 *
 * Intent: provides simplified interface to complex system
 */

#include <iostream>
#include <memory>

class Subsystem1 {
public:
    void subsystem1_get_ready() const {
        std::cout << "Subsystem1: Ready!" << '\n';
    }

    void subsystem1_run() const {
        std::cout << "Subsystem1 is currently running..." << '\n';
    }
};


class Subsystem2 {
public:
    void subsystem2_get_ready() const {
        std::cout << "Subsystem2: Ready!" << '\n';
    }

    void subsystem2_run() const {
        std::cout << "Subsystem2 is currently running..." << '\n';
    }
};


class Facade {
public:
    Facade() : _subsystem_1(), _subsystem_2() {}

    // Facade does all setup of the system. Client only needs to call one method of facade to setup system.
    void setup_system() {
        _subsystem_1->subsystem1_get_ready();
        _subsystem_2->subsystem2_get_ready();

        _subsystem_1->subsystem1_run();
        _subsystem_2->subsystem2_run();
    }

protected:
    std::unique_ptr<Subsystem1> _subsystem_1;
    std::unique_ptr<Subsystem2> _subsystem_2;
};

int main() {
    Facade facade;

    // Client works with system through one convenient method
    facade.setup_system();
    return 0;
}