#include <iostream>
#include <thread>

class Vehicle
{
public:
    Vehicle(int id) : _id(id) {}
    void operator()()
    {
        std::cout << "Vehicle #" << _id << " has been created" << std::endl;
    }

private:
    int _id;
};

int main()
{
    // create thread
    std::thread t1 = std::thread(Vehicle(1)); // Use copy initialization
    std::thread t2 = std::thread(Vehicle(2)); // Use copy initialization
    std::thread t3 = std::thread(Vehicle(3)); // Use copy initialization
    // do something in main()
    std::cout << "Finished work in main \n";

    // wait for thread to finish
    t1.join();
    t2.join();
    t3.join();
    return 0;
}