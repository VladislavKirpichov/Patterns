/*
 * Observer pattern
 *
 * Intent: defines a subscription mechanism to notify multiple objects
 * about changes that happens in object they're observing.
 */

#include <iostream>
#include <unordered_set>
#include <string>

struct State {
    std::string name;
    std::string type;
};


class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update(const std::string& message) = 0;
};


// Subject notifies observers via messages.
class Subject {
public:
    Subject() = default;
    explicit Subject(const State& state) : _state(state) {}
    explicit Subject(State&& state) : _state(std::move(state)) {}

    // Subscription management methods
    Subject& attach(IObserver* observer) {
        _observers.insert(observer);
        return *this;
    }

    void detach(IObserver* observer) {
        _observers.erase(observer);
    }

    void notify() {
        std::string str = "New state: " + _state.type;

        for (auto& i : _observers)
            i->update(str);
    }

    // Subject do some business logic and then notifies all observers about changes.
    void change_subject(std::string type, std::string name) {
        change_state_values(std::move(type), std::move(name));
        notify();
    }

protected:
    void change_state_values(std::string&& type, std::string&& name) {
        _state.type = std::move(type);
        _state.name = std::move(name);
    }

private:
    std::unordered_set<IObserver*> _observers;
    State _state;
};


class SimpleObserver : public IObserver {
public:
    void update(const std::string& message) override {
        _message_from_subject = message;
    }

    void print_message() {
        std::cout << _message_from_subject << '\n';
    }

private:
    std::string _message_from_subject;
};


void client() {
    Subject subject;

    SimpleObserver observer1;
    SimpleObserver observer2;

    subject.attach(&observer1).attach(&observer2);

    subject.change_subject("New type", "Subject");

    observer1.print_message();  // New state: New type
    observer2.print_message();  // New state: New type
}


int main() {
    client();

    return 0;
}