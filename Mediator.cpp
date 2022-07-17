/*
 * Mediator pattern
 *
 * Intent: encapsulates dependencies between objects. The pattern forces objects
 * to communicate via mediator.
 */

#include <iostream>
#include <memory>

enum class Events { A, B };


class Component;


class Mediator {
public:
    virtual ~Mediator() = default;

    virtual void notify(Component& sender, Events event) const = 0;
};


class Component {
public:
    Component(Mediator* mediator = nullptr) : _mediator(mediator) {}


    void set_mediator(Mediator* mediator) {
        _mediator.reset(mediator);
    }

protected:
    std::unique_ptr<Mediator> _mediator;
};


// Component don't depend on other components. They also don't depend on concrete mediator class.
class ConcreteComponentA : public Component {
public:
    void do_logic() const {
        std::cout << "Concrete component A does some logic..." << '\n';
    }

    void do_b() {
        _mediator->notify(*this, Events::B);
    }
};


class ConcreteComponentB : public Component {
public:
    void do_logic() const {
        std::cout << "Concrete component B does some logic..." << '\n';
    }

    void do_a() {
        _mediator->notify(*this, Events::A);
    }
};


// Concrete Mediator implement concrete behavior by coordinating components
class ConcreteMediator : public Mediator {
public:
    ConcreteMediator(ConcreteComponentA& component_a, ConcreteComponentB& component_b)
            : _component_a(component_a),
              _component_b(component_b) {
        component_a.set_mediator(this);
        component_b.set_mediator(this);
    }

    void notify(Component& sender, Events event) const override {
        if (event == Events::A) {
            std::cout << "Mediator reacts on A and triggers component A:" << '\n';
            _component_a.do_logic();
        }
        else if (event == Events::B) {
            std::cout << "Mediator reacts on B and triggers component A:" << '\n';
            _component_b.do_logic();
        }
        else {
            std::cout << "Operation type undefined..." << '\n';
        }

        std::cout << '\n';
    }

private:
    ConcreteComponentA& _component_a;
    ConcreteComponentB& _component_b;
};


void client() {
    ConcreteComponentA component_a{};
    ConcreteComponentB component_b{};

    ConcreteMediator mediator{component_a, component_b};

    component_a.do_b();
    // Output:
    // Mediator reacts on B and triggers component A:
    // Concrete component B does some logic...

    component_b.do_a();
    // Output:
    // Mediator reacts on A and triggers component A:
    // Concrete component A does some logic...
}

int main() {
    client();

    return 0;
}
