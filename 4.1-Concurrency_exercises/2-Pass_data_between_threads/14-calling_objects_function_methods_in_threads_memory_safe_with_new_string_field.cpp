#include <iostream>
#include <thread>
#include <string>
#include <memory>

class Vehicle
{
public:
    Vehicle() : _id(0) {}
    void addID(int id) { _id = id; }
    void printID()
    {
        std::cout << "Vehicle ID=" << _id << std::endl;
    }
    // TODO: Modify the Vehicle class as indicated in the instructions on the left.
    void setName(std::string name) {
        _name = name;
    }
    void printName () {
        std::cout<<"Name= '"<<_name<<"'"<<std::endl;
    }
private:
    int _id;
    std::string _name;
};

int main()
{
    // create thread 1
    std::shared_ptr<Vehicle> v(new Vehicle);
    std::thread t1 = std::thread(&Vehicle::addID, v, 1); 

    // create thread 2
    std::thread t2 = std::thread(&Vehicle::setName, v, "MyVehicle"); 

    // wait for thread to finish
    t1.join();
    t2.join();

    // print Vehicle id
    v->printID();
    v->printName();
}