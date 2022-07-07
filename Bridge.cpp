//
// Created by vladislav on 01.07.22.
//

// Идея паттерна: позволяет отделить абстракцию от реализации так, чтобы
// они обе могли развиваться по отдельности.

// В данном примере я буду использовать идею из книги GoF.
// Абстракция - разные виды окон приложения.
// Реализация - разные виды оконных систем

#include <iostream>
#include <string>
#include <memory>

// Implementation
class WindowAPI {
public:
    virtual ~WindowAPI() = default;
    virtual std::string create_window() = 0;
};

class WindowsWindowAPI : public WindowAPI {
public:
    std::string create_window() override {
        return "Windows";
    }
};

class MacOSWindowAPI : public WindowAPI {
public:
    std::string create_window() override {
        return "Mac OS";
    }
};

class XWindowSystemAPI : public WindowAPI {
public:
    std::string create_window() override {
        return "UNIX";
    }
};

// Abstraction
class Window {
public:
    explicit Window (WindowAPI* window_api)
        : _api(window_api) {}

    virtual ~Window() = default;
    virtual std::string draw_window() = 0;

protected:
    // Абстракция не зависит от деталей реализации
    WindowAPI* _api;
};

class Dialog : public Window {
public:
    using Window::Window;
    std::string draw_window() override {
        return "Dialog on system: " + _api->create_window();
    }
};

class Dashboard : public Window {
public:
    using Window::Window;
    std::string draw_window() override {
        return "Dashboard on system: " + _api->create_window();
    }
};

int main() {
    // Клиентский код должен работать с любой предварительно сконфигурированной
    // комбинацией абстракции и реализации. Таким образом, вместо создания классов
    // для каждой возможной комбинации абстракции и реализации (3 * 2 = 6) мы комбинируем
    // необходмые нам варинты (3 + 2 = 5). В итоге создано меньше классов

    WindowAPI* mac_os_window_api    = new MacOSWindowAPI();
    WindowAPI* windows_window_api   = new WindowsWindowAPI();
    WindowAPI* x_window_system_api  = new XWindowSystemAPI();

    Dialog dialog_macos {mac_os_window_api};
    Dialog dialog_windows {windows_window_api};

    std::cout << dialog_macos.draw_window() << '\n';        // Dialog on system: Mac OS
    std::cout << dialog_windows.draw_window() << '\n';      // Dialog on system: Windows

    Dashboard dashboard_windows {windows_window_api};
    Dashboard dashboard_xwindow {x_window_system_api};

    std::cout << dashboard_windows.draw_window() << '\n';   // Dashboard on system: Windows
    std::cout << dashboard_xwindow.draw_window() << '\n';   // Dashboard on system: UNIX

    delete mac_os_window_api, windows_window_api, x_window_system_api;
    return 0;
}