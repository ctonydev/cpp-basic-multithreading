#include <iostream>
#include <thread>
#include <mutex>

void work(int& count, int iterations, std::mutex& mtx)
{
    for(int i = 0; i < iterations; i++)
    {
        mtx.lock();
        ++count;
        mtx.unlock();
    }
}

void splitJobMultithreaded(void (*job)(int&, int, std::mutex&), int& count, int iterations, std::mutex& mtx, int numThreads)
{
    std::thread threads[numThreads];
    for(int i = 0; i < numThreads; i++)
    {
        threads[i] = std::thread(job, std::ref(count), iterations / numThreads, std::ref(mtx));
    }
    for(int i = 0; i < numThreads; i++)
    {
        threads[i].join();
    }
}

int main ()
{
    int count = 0;
    int iterations = 1E6;

    std::mutex mtx;

    // Create variable # threads that help each other to increment a shared variable with a mutex to prevent multithreading issues.
    splitJobMultithreaded(work, count, iterations, mtx, 5);

    std::cout << "Count: " << count << std::endl;
}