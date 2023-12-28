#include "concurrency/ThreadPoolConcurrency.h"

ThreadPoolConcurrency::ThreadPoolConcurrency(size_t threads) : stop(false) {
    for (size_t i = 0; i < threads; ++i) {
        workers.emplace_back(&ThreadPoolConcurrency::processTasks, this);
    }
}

ThreadPoolConcurrency::~ThreadPoolConcurrency() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread &worker : workers) {
        worker.join();
    }
}

void ThreadPoolConcurrency::execute(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        tasks.emplace(task);
    }
    condition.notify_one();
}

void ThreadPoolConcurrency::processTasks() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(this->queue_mutex);
            // Sleep and wake have task to do or must stop
            this->condition.wait(lock, [this] { return !this->tasks.empty() || this->stop; });
            // Graceful shutdown
            if (this->stop && this->tasks.empty()) return;
            // Extract the task from the queue
            task = std::move(this->tasks.front());
            this->tasks.pop();
        }
        // Execute the task
        task();
    }
}