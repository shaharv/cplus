#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include "thread_pool.h"

int main() {
    std::cout << "=== Simplified Thread Pool Example ===" << std::endl;
    std::cout << "Main thread ID: " << std::this_thread::get_id() << std::endl;

    // Create a thread pool with 4 worker threads
    ThreadPool pool(4);

    std::cout << "\n--- Enqueueing tasks ---" << std::endl;

    // Enqueue some simple tasks
    for(int i = 1; i <= 8; ++i) {
        pool.enqueue([i]() {
            std::cout << "Task " << i << " started on thread " << std::this_thread::get_id() << std::endl;

            // Simulate work
            int duration = 100 + (i * 50);
            std::this_thread::sleep_for(std::chrono::milliseconds(duration));

            int result = i * i;
            std::cout << "Task " << i << " completed with result: " << result << std::endl;
        });
    }

    // Enqueue some string processing tasks
    std::vector<std::string> inputs = {"Hello", "World", "Thread", "Pool", "Example"};
    for(const auto& input : inputs) {
        pool.enqueue([input]() {
            std::cout << "Processing string: " << input << " on thread " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << "Completed processing: " << input << std::endl;
        });
    }

    std::cout << "\n--- Demonstrating more complex lambda tasks ---" << std::endl;

    // Example with lambda that captures variables
    int x = 10, y = 20;
    pool.enqueue([x, y]() {
        std::cout << "Lambda task executing on thread " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::cout << "Lambda result: " << (x + y) << std::endl;
    });

    // Example with lambda that captures by reference (be careful with scope!)
    std::string message = "Shared message";
    pool.enqueue([&message]() {
        std::cout << "Accessing shared data on thread " << std::this_thread::get_id() << std::endl;
        std::cout << "Message: " << message << std::endl;
    });

    std::cout << "\n--- Waiting for all tasks to complete ---" << std::endl;

    // Sleep to let tasks complete (in real code, you might use other synchronization)
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "\n--- All tasks completed ---" << std::endl;

    // ThreadPool destructor will automatically wait for all threads to finish
    return 0;
}
