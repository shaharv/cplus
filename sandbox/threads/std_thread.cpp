#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <string>

using namespace std::chrono_literals;

std::mutex globalMutex;
std::condition_variable cv_thread1;
std::condition_variable cv_thread2;
std::condition_variable cv_main;

bool thread1_ready = false;
bool thread1_done = false;
bool thread2_done = false;

void work1() {
    std::unique_lock<std::mutex> lock(globalMutex);

    // Wait until main signals thread1 to start
    cv_thread1.wait(lock, []{ return thread1_ready; });

    std::thread::id tid = std::this_thread::get_id();
    std::cout << "thread " << tid << ": " << "Do some work..." << std::endl;
    std::this_thread::sleep_for(2s);
    std::cout << "thread " << tid << ": " << "Done working." << std::endl;

    // Signal that thread1 is done
    thread1_done = true;
    cv_thread2.notify_one(); // Wake up thread2
}

void work2(const std::string& msg) {
    std::unique_lock<std::mutex> lock(globalMutex);

    // Wait until thread1 is done
    cv_thread2.wait(lock, []{ return thread1_done; });

    std::thread::id tid = std::this_thread::get_id();
    std::cout << "thread " << tid << ": " << msg << std::endl;

    // Signal that thread2 is done
    thread2_done = true;
    cv_main.notify_one(); // Wake up main thread
}

int main() {
    std::cout << "start of main" << std::endl;

    std::thread t1(work1);
    std::thread t2(work2, "hello from 2nd thread (waited on condition_variable)");

    // Give threads time to reach their wait points
    std::this_thread::sleep_for(100ms);

    {
        std::unique_lock<std::mutex> lock(globalMutex);
        // Signal thread1 to start
        thread1_ready = true;
        cv_thread1.notify_one();

        // Wait for thread2 to complete before main continues
        cv_main.wait(lock, []{ return thread2_done; });
    }

    std::cout << "Both threads completed, main continuing..." << std::endl;

    t1.join();
    t2.join();
    std::cout << "end of main" << std::endl;
    return 0;
}
