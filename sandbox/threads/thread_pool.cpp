#include "thread_pool.h"

ThreadPool::ThreadPool(size_t num_threads) : stop(false) {
    // Create worker threads
    for(size_t i = 0; i < num_threads; ++i) {
        workers.emplace_back([this] {
            // Worker thread loop
            for(;;) {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(this->queue_mutex);

                    // Wait until there's a task or the pool is stopped
                    this->condition.wait(lock, [this]{
                        return this->stop || !this->tasks.empty();
                    });

                    // If we're stopping and there are no more tasks, exit
                    if(this->stop && this->tasks.empty())
                        return;

                    // Get the next task
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }

                // Execute the task
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }

    // Notify all worker threads to wake up and check the stop condition
    condition.notify_all();

    // Wait for all worker threads to finish
    for(std::thread &worker: workers)
        worker.join();
}

void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        // Don't allow enqueueing after stopping the pool
        if(stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        tasks.emplace(std::move(task));
    }

    condition.notify_one();
}
