/*
 * Паттерн заместитель (proxy)
 *
 * Назначение: позволяет вместо реального объекта "подставить" объект-заместитель, который
 * может перехватывать доступ к реальному объекту.
 */

#include <iostream>
#include <string>

class IAccount {
public:
    virtual void print_user_info() = 0;
};


class AccountProxy;


class Account : public IAccount {
public:
    Account(const std::string& login, const std::string& password)
            : _login(login), _password(password) {}

    void print_user_info() override {
        std::cout << "Login: " << _login << "; "
                  << "Password: " << _password << '\n';
    }

    friend class AccountProxy;

private:
    std::string _login;
    std::string _password;
};


class AccountProxy : public IAccount {
public:
    AccountProxy(const std::string& login, const std::string& password) : _account(login, password) {}

    void print_user_info() override {
        if (check_user()) {
            std::cout << "Access accepted!" << '\n';
            _account.print_user_info();
        }
        else
            std::cout << "Access denied." << '\n';
    }

private:
    bool check_user() {
        std::string login, password;
        std::cout << "Input your login and password. Format: <login> <password>" << '\n';
        std::cin >> login >> password;

        if (login == _account._login && password == _account._password)
            return true;

        return false;
    }

private:
    Account _account;
};

int main() {
    AccountProxy account{"Alex", "123"};
    account.print_user_info();

    return 0;
}