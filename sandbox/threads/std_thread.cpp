#include <chrono>
#include <iostream>
#include <thread>
#include <string>

void func(const std::string& msg) {
    std::thread::id tid = std::this_thread::get_id();
    std::cout << "thread " << tid << ": " << msg << std::endl;
}

int main() {
    using namespace std::chrono_literals;

    std::cout << "start of main" << std::endl;
    std::thread t(func, "hello");
    std::cout << "joining thread" << std::endl;
    std::this_thread::sleep_for(1s);
    t.join();
    std::cout << "end of main" << std::endl;
    return 0;
}
