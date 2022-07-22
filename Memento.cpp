/*
 * Memento pattern
 *
 * Intent: Lets you save and restore previous state of object without revealing
 * the details of its implementation.
 */

#include <iostream>
#include <memory>
#include <string>

struct State {
    int state_number = 0;
    std::string state_name = "Unknown";
    std::string data = "Undefined";
};


// Mement provides a way to retrieve memento's data.
// However, it doesn't expose the Originator's state.
class Memento {
protected:
    virtual void set_state(State& state) = 0;
    virtual State get_state() = 0;
};


class Orignator;


class MementoOriginator : public Memento {
public:
    MementoOriginator() = default;
    explicit MementoOriginator(const State& state) : _state(state) {}
    explicit MementoOriginator(State&& state) : _state(std::move(state)) {}

    friend class Orignator;

private:
    void set_state(State& state) override {
        _state = state;
    }

    State get_state() override {
        return _state;
    }

private:
    State _state;
};


class Originator {
private:
    std::unique_ptr<MementoOriginator> _memento;
    State _state;

public:
    friend class MementoOriginator;

    explicit Originator(State& state) : _state(state), _memento() {}

    std::unique_ptr<MementoOriginator> get_memento() {
        return std::make_unique<MementoOriginator>(_state);
    }

    void set_memento(MementoOriginator* memento) {
        _state = memento.;
    }
};


int main() {

    return 0;
}