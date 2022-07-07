//
// Created by vladislav on 07.07.22.
//

#include <iostream>
#include <mutex>
#include <thread>

class Singleton {
protected:
    Singleton() = default;

public:
    static Singleton get_instance() {
        static Singleton singleton{};
        singleton.check++;
        return singleton;
    }

    int check = 0;
};

class SingletonWithCounter {
public:
    static SingletonWithCounter* get_instance() {
        if (count == 0) {
            singleton = new SingletonWithCounter();
            count++;
        }

        return singleton;
    }

    int test_counter = 0;

private:
    SingletonWithCounter() = default;

    static inline unsigned count = 0;
    static inline SingletonWithCounter* singleton = nullptr;
};


class SingletonWithMutex {
public:
    static SingletonWithMutex* get_instance() {
        mutex.lock();

        if (singleton == nullptr)
            singleton = new SingletonWithMutex();

        mutex.unlock();
        return singleton;
    }

    int test_counter = 0;

private:
    SingletonWithMutex() = default;

    static inline std::mutex mutex{};
    static inline SingletonWithMutex* singleton = nullptr;
};

void test_simple_singleton() {
    Singleton test_1 = Singleton::get_instance();
    Singleton test_2 = Singleton::get_instance();

    // Если бы создались 2 разных объекта, то вывелось 1 1
    std::cout << test_1.check << ' ' << test_2.check << '\n';   // 1 2
}

void test_counter_singleton() {
    SingletonWithCounter* test = SingletonWithCounter::get_instance();
    SingletonWithCounter* another_test = SingletonWithCounter::get_instance();

    test->test_counter++;
    another_test->test_counter++;
    another_test->test_counter++;

    // Если бы создались 2 разных объекта, то вывелось 1 2
    std::cout << test->test_counter << ' ' << another_test->test_counter << '\n';   // 3 3
}

void test_mutex() {
    SingletonWithMutex* test = SingletonWithMutex::get_instance();
    test->test_counter += 1;
}

void test_mutex_singleton() {
    SingletonWithMutex* test_mutex_1 = SingletonWithMutex::get_instance();
    SingletonWithMutex* test_mutex_2 = SingletonWithMutex::get_instance();

    std::thread thread1(test_mutex);
    std::thread thread2(test_mutex);
    std::thread thread3(test_mutex);
    std::thread thread4(test_mutex);
    std::thread thread5(test_mutex);
    thread5.join();
    thread4.join();
    thread3.join();
    thread2.join();
    thread1.join();

    std::cout << test_mutex_1->test_counter << ' ' << test_mutex_2->test_counter << '\n';   // 5 5
}

int main() {
    test_simple_singleton();
    test_counter_singleton();
    test_mutex_singleton();

    return 0;
}