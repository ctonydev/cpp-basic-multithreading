#include <iostream>
#include <thread>
#include <atomic>

int main()
{
    int count = 0;
    std::atomic<int> atomic_count(0); // Prevent multithreading issues with shared data.
    int iterations = 900;

    std::thread t1([&count, iterations, &atomic_count](){
        for(int i = 0; i < iterations; i++)
        {
            ++count;
            ++atomic_count;
        }
    });

    std::thread t2([&count, iterations, &atomic_count](){
        for (int i = 0; i < iterations; i++)
        {
            ++count;
            ++atomic_count;
        }
    });

    t1.join();
    t2.join();

    std::cout << "Count: " << count << std::endl;
    std::cout << "Atomic count: " << atomic_count << std::endl;

    return 0;
}
