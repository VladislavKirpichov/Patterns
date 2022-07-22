/*
 * State pattern
 *
 * Intent: Lets an object alter its behavior when internal state changes.
 * It appears as if an object changed it class.
 */

#include <iostream>
#include <memory>


// Context defines the interface of interest to clients.
class Context;


// State declares methods thar all States should implement and provide
// a backreference to context object. This backreference can be used by States to transition the
// Context to another State.
class State {
public:
    virtual ~State() = default;

    virtual void set_context(std::shared_ptr<Context> context) {
        _context = std::move(context);
    }

    virtual void handle() = 0;

protected:
    std::shared_ptr<Context> _context;
};


// Concrete states implements various of behavior.
class ConcreteStateA : public State {
public:
    void handle() override {
        std::cout << "A handler" << "\n";
    }
};


class ConcreteStateB : public State {
public:
    void handle() override {
        std::cout << "B handler" << "\n";
    }
};


class Context {
public:
    Context(State* state)
            : _state(state) {}

    void set_state(State* state) {
        _state.reset(state);
    }

    void request() {
        _state->handle();
    }

private:
    std::unique_ptr<State> _state;
};


void client() {
    Context context{new ConcreteStateA};
    context.request();  // A handler

    context.set_state(new ConcreteStateB);
    context.request();  // B handler
}

int main() {
    client();
    return 0;
}