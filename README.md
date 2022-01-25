# Udacity_C++_Nanodegree
Projects created along this Nanodegree

# 1 - A* Search Algorithm
- Contained in the folder 1-CppND-Route-Planning-Project.
- It was implemented an A* grid-based search algorithm.
- The searching behavior a BFS like algorithm is to visit priority of neighbor nodes w/ higher int f value, which is a dynamic value relate to its current node during the search process, that equals to the sum of int h (Heuristic) and int g value, i.e., f(n) = g(n) + h(n).
- A set of tests is provided by Udacity, that have been passed using this implementation.

# 2 - System Monitor Project
* Contained in the folder `1-Cpp-System-Monitor`
* In this project, a Linux System Monitor is built using C++ OOP topics, including *abstraction*, *inheritance*, *polymorphism* as well as templates and etc.
    * it implements similar functionalities as `htop`
    * the basic idea is to read and parse system file contents in `/proc` at the processor level and pid level as well as making several metrics calculations
      to access cpu performance.
    
