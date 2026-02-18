#pragma once

#include <string>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <vector>

namespace core {
    class ThreadPool {
    public:
        explicit ThreadPool(size_t numThreads);
        ~ThreadPool();

        void enqueue(std::function<void()> task);
        void shutdown();
        void wait();

    private:
        void workerThread();

        std::vector<std::thread> workers;
        std::queue<std::function<void()>> tasks;

        std::mutex queueMutex;
        std::condition_variable condition;
        bool stop;
        std::atomic<size_t> activeTasks{0};
        std::condition_variable finishedCondition;
    };
}//namespace core