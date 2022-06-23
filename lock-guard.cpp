#include <iostream>
#include <thread>
#include <mutex>

void work(int& count, int iterations, std::mutex& mtx)
{
    for(int i = 0; i < iterations; i++)
    {
        // Handle automatic unlocking of mutexes when the scope of the lock ends.
        std::lock_guard<std::mutex> lock(mtx);
        ++count;
    }
}

void workUniqueGuard(int& count, int iterations, std::mutex& mtx)
{
    for(int i = 0; i < iterations; i++)
    {
        std::unique_lock<std::mutex> lock(mtx);
        ++count;
    }
}

int main()
{
    int count = 0;
    int iterations = 1E6;

    std::mutex mtx;

    std::thread t1(work, std::ref(count), iterations, std::ref(mtx));
    std::thread t2(workUniqueGuard, std::ref(count), iterations, std::ref(mtx));

    t1.join();
    t2.join();

    std::cout << "Count: " << count << std::endl;
    return 0;
}