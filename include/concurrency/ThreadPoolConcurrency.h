#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include "concurrency/IConcurrencyModel.h"

class ThreadPoolConcurrency : public IConcurrencyModel {
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;

public:
    explicit ThreadPoolConcurrency(size_t threads);
    ~ThreadPoolConcurrency();

    void execute(std::function<void()> task) override;
};