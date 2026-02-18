#include "ThreadPool.hpp"

namespace core {
    ThreadPool::ThreadPool(size_t numThreads) : stop(false) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back(&ThreadPool::workerThread, this);
        }
    }

    ThreadPool::~ThreadPool() {
        shutdown();
        for (std::thread& worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

    void ThreadPool::shutdown() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
    }

    void ThreadPool::wait() {
        std::unique_lock<std::mutex> lock(queueMutex);
        finishedCondition.wait(lock, [this] { return activeTasks == 0 && tasks.empty(); });
    }

    void ThreadPool::enqueue(std::function<void()> task) {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            if (stop) {
            throw std::runtime_error("Enqueue on stopped ThreadPool");
        }
            tasks.push(std::move(task));
        }
        condition.notify_one();
    }

    void ThreadPool::workerThread() {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                condition.wait(lock, [this] { return stop || !tasks.empty(); });
                if (stop && tasks.empty()) {
                    return;
                }
                task = std::move(tasks.front());
                tasks.pop();
                ++activeTasks;
            }
            task();
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                --activeTasks;
                if (activeTasks == 0 && tasks.empty()) {
                    finishedCondition.notify_all();
                }
            }
        }
    }
}//namespace core