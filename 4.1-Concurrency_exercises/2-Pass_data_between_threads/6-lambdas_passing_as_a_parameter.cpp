#include <iostream>

int main()
{
    int id = 0; // Define an integer variable

    // create lambda
    auto f = [](int &id) { std::cout << "ID = " << ++id << std::endl; }; // ID is passed as a parameter

    // execute function object and pass the parameter
    f(id);
    std::cout << "ID (outside main) = " << id << std::endl; 
    return 0;
}