/*
 * Intent: defines the skeleton of an algorithm in the superclass
 * but lets subclasses define specific steps of the algorithm
 */

#include <iostream>
#include <memory>


class AbstractClass {
public:
    virtual ~AbstractClass() = default;

    // Abstract class defines the skeleton of an algorithm
    virtual void operation() {
        step1();
        hook();
        step2();
    }

protected:
    virtual void step1() = 0;
    virtual void step2() = 0;

    // Subclasses may override hooks, but it's not mandatory since the hooks have default implementation.
    // They are empty by default, but can be used in subclasses to extend algorithm in crucial places.
    virtual void hook() {}
};


// Concrete class have to implement all abstract methods of the base class.
class ConcreteClass1 : public AbstractClass {
private:
    void step1() override {
        std::cout << "Step 1 from ConcreteClass1" << '\n';
    }

    void step2() override {
        std::cout << "Step 2 from ConcreteClass1" << '\n';
    }

    // Concrete class can also override some hooks.
    void hook() override {
        std::cout << "Hook from ConcreteClass1" << '\n';
    }
};


class ConcreteClass2 : public AbstractClass {
private:
    void step1() override {
        std::cout << "Step 1 from ConcreteClass2" << '\n';
    }

    void step2() override {
        std::cout << "Step 2 from ConcreteClass2" << '\n';
    }
};


class ClientClass {
public:
    explicit ClientClass(AbstractClass* abstract_class)
            : _abstract_class(abstract_class) {}

    void set_abstract_class(AbstractClass* abstract_class) {
        _abstract_class.reset(abstract_class);
    };

    void operation() {
        _abstract_class->operation();
    }

private:
    std::unique_ptr<AbstractClass> _abstract_class;
};


void client() {
    ClientClass client_class(new ConcreteClass1);
    client_class.operation();

    client_class.set_abstract_class(new ConcreteClass2);
    client_class.operation();
}

int main() {
    client();

    return 0;
}