/*
 * Command pattern
 *
 * Intent: turns request into object, so this object that contains all request data.
 * This transformation lets you pass this object to request handlers as an argument.
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

// Receiver contains come some complex business logic. Receiver perform all kinds of operations.
class Receiver {
public:
    explicit Receiver(std::string str) :  _str(std::move(str)) {}

    std::size_t get_hash() {
        std::hash<std::string> str_hash{};
        return str_hash(_str);
    }

private:
    std::string _str;
};


class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
};


class SimpleCommand : public ICommand {
public:
    explicit SimpleCommand(std::string str) : _str(std::move(str)) {}

    void execute() override {
        std::cout << "Executing simple command. This simple command just prints string: " << _str << '\n';
    }

private:
    std::string _str;
};


class ComplexCommand : public ICommand {
public:
    explicit ComplexCommand(const std::string& str) : _str(str), _receiver(str) {}

    void execute() override {
        std::cout << "Executing complex command:" << '\n'
                  << "Request string:" << _str << '\n'
                  << "Hash for this string = " << _receiver.get_hash() << '\n';
    }

private:
    std::string _str;
    Receiver _receiver;
};


// Invoker sends request to the command. It associated with one or several commands.
class Invoker {
public:
    Invoker() : _start_command(nullptr), _end_command(nullptr) {}

    void set_on_start_command(ICommand* command) {
        _start_command.reset(command);
    }

    void set_on_end_command(ICommand* command) {
        _end_command.reset(command);
    }

    void start() { _start_command->execute(); }
    void end() { _end_command->execute(); }

private:
    std::unique_ptr<ICommand> _start_command;
    std::unique_ptr<ICommand> _end_command;
};


void client() {
    Invoker invoker{};

    // Client can parameterize an invoker by any command
    invoker.set_on_start_command(new SimpleCommand{"Hello world!"});
    invoker.set_on_end_command(new ComplexCommand{"Hello world!"});

    invoker.start();    // Executing simple command. This simple command just prints string: Hello world!
    invoker.end();      // Executing complex command...
}


int main() {
    client();

    return 0;
}