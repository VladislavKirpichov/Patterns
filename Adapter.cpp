//
// Created by vladislav on 08.07.22.
//

// Идея паттерна: позволяет преобразовать интерфейс одного класса для работы с интерфейсом другого
// Иначе, позволяет объектам с несовместимыми интерфейсами работать вместе

#include <iostream>

class Target {
public:
    virtual void do_logic() {
        std::cout << "Some method" << '\n';
    }
};


class Adaptee {
public:
    void do_logic_another_way() {
        std::cout << "Some method" << '\n';
    }
};


class ClassAdapter : public Target, private Adaptee {
    void do_logic() { this->do_logic_another_way(); }
};


class ObjectAdapter : public Target {
public:
    explicit ObjectAdapter(Adaptee* adaptee)
        : _adaptee(adaptee) {}
    void do_logic() override { _adaptee->do_logic_another_way(); }

private:
    Adaptee* _adaptee;
};


void f(Target& value) {
    value.do_logic();
}

int main() {
    Adaptee adaptee;

    ClassAdapter class_adapter{};
    ObjectAdapter object_adapter{&adaptee};

    f(class_adapter);
    f(object_adapter);

    return 0;
}