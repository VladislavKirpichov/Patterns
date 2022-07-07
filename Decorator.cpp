//
// Created by vladislav on 30.06.22.
//

// https://github.com/RefactoringGuru/design-patterns-cpp/blob/main/src/Decorator/Conceptual/main.cc

#include <iostream>
#include <string>
#include <memory>


// Base abstract component
class Component {
public:
    virtual ~Component() = default;
    virtual std::string operator()() const = 0;
};


class ConcreteComponent : public Component {
    std::string operator()() const override {
        return "Concrete Component";
    }
};


class NewCoolConcreteComponent : public Component {
    std::string operator()() const override {
        return "New Cool Concrete Component!";
    }
};


// Base Decorator class. The primary purpose of this class is to define the wrapping
// interface for all concrete decorators
class Decorator : public Component {
public:
    explicit Decorator(Component* component)
        : _component(component) {}

    // Decorator delegates all work to the wrapped component
    std::string operator()() const override {
        return (*_component)();
    }

protected:
    // By default, store a wrapped component
    std::unique_ptr<Component> _component;
};


class DecoratorA : public Decorator {
public:
    explicit DecoratorA(Component* component)
        : Decorator(component) {}

    // Decorators may call parent implementation of the operation, instead
    // of calling the wrapped object directly. This approach simplifies
    // extension of decorator classes.
    std::string operator()() const override {
        return "Decorator A(" + Decorator::operator()() + ")";
    }
};


class DecoratorB : public Decorator {
public:
    explicit DecoratorB(Component* component)
        : Decorator(component) {}

    // Decorators may call parent implementation of the operation, instead
    // of calling the wrapped object directly. This approach simplifies
    // extension of decorator classes.
    std::string operator()() const override {
        return "Decorator B(" + Decorator::operator()() + ")";
    }
};


int main() {
    ConcreteComponent component{};
    NewCoolConcreteComponent new_cool_concrete_component{};

    Component* decorator1 = new DecoratorA(&component);
    Component* decorator2 = new DecoratorB(&new_cool_concrete_component);
    Component* decorator3 = new DecoratorA(decorator2);

    std::cout << (*decorator1)() << '\n';   // Decorator A(Concrete Component)
    std::cout << (*decorator2)() << '\n';   // Decorator B(New Cool Concrete Component!)
    std::cout << (*decorator3)() << '\n';   // Decorator A(Decorator B(New Cool Concrete Component!))
}
