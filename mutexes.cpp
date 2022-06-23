#include <iostream>
#include <thread>
#include <mutex>

int main ()
{
    int count = 0;
    int iterations = 1E6;

    std::mutex mtx;

    // Create two threads that increment a shared variable with a mutex to prevent multithreading issues.
    auto func = [&](){
        for(int i = 0; i < iterations; i++)
        {
            mtx.lock();
            ++count;
            mtx.unlock();
        }
    };

    std::thread t1(func);
    std::thread t2(func);

    t1.join();
    t2.join();

    std::cout << "Count: " << count << std::endl;
}