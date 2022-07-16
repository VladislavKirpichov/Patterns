/*
 * Chain of responsibility pattern
 *
 * Intent: let you pass request along the chain of handlers. Each handler decides, will
 * he process this request or pass it to the next handler.
 */

#include <iostream>

class Request {
public:
    Request() : _priority(0) {}

    explicit Request(int priority) : _priority(priority) {}

    int get_priority() const { return _priority; }

private:
    int _priority;
};


class IHandler {
public:
    IHandler() : _next_handler(nullptr) {}

    virtual void process_request(const Request& request) const = 0;

    IHandler* set_handler(IHandler* handler) {
        _next_handler = handler;
        return handler;
    }

protected:
    IHandler* _next_handler;
};


// All handlers either handle request or pass it to next handler
class HighPriorityHandler : public IHandler {
public:
    using IHandler::IHandler;

    void process_request(const Request& request) const override {
        if (request.get_priority() == 2) {
            std::cout << "Handling a high priority request..." << '\n';
        } else {
            _next_handler->process_request(request);
        }
    }
};


class MediumPriorityHandler : public IHandler {
public:
    using IHandler::IHandler;

    void process_request(const Request& request) const override {
        if (request.get_priority() == 1) {
            std::cout << "Handling a medium priority request..." << '\n';
        } else {
            _next_handler->process_request(request);
        }
    }
};


class LowPriorityHandler : public IHandler {
public:
    using IHandler::IHandler;

    void process_request(const Request& request) const override {
        if (request.get_priority() == 0) {
            std::cout << "Handling a low priority request..." << '\n';
        } else {
            _next_handler->process_request(request);
        }
    }
};


class UndefinedPriorityHandler : public IHandler {
public:
    using IHandler::IHandler;

    void process_request(const Request& request) const override {
        std::cout << "Error! Request priority undefined." << '\n';
    }
};


void client(IHandler& handler) {
    Request low_priority{0};
    Request medium_priority{1};
    Request high_priority{2};
    Request undefined_priority{5};

    // Client just sends request to handler
    handler.process_request(high_priority);         // Handling a high priority request...
    handler.process_request(medium_priority);       // Handling a medium priority request...
    handler.process_request(low_priority);          // Handling a low priority request...
    handler.process_request(undefined_priority);    // Error! Request priority undefined.
}

int main() {
    UndefinedPriorityHandler undefined_priority_handler{};
    LowPriorityHandler low_priority_handler{};
    MediumPriorityHandler medium_priority_handler{};
    HighPriorityHandler high_priority_handler{};

    high_priority_handler.set_handler(&medium_priority_handler)->set_handler(&low_priority_handler)->set_handler(
            &undefined_priority_handler);

    client(high_priority_handler);

    return 0;
}