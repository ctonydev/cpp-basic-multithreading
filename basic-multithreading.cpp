#include <iostream>
#include <thread>
#include <chrono>

void work(int delay = 0)
{
    for(int i = 0; i < 10; i++)
    {
        std::cout << i << ". Hello from thread " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

int main()
{
    std::thread t1(work, 500);
    std::thread t2(work, 500);

    t1.join();
    t2.join();

    return 0;
}