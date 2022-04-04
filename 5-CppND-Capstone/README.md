# CPPND: Capstone Repositoy

This is a repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

This Capstone Project aims to simulate an elevator system.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build and Run Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./capstone`.

## Description of the Project

This project consists of an simulator of an elevator system.
Users are able to add elevators to the system, as well as seen the status of a
given elevator.
Users also are able to call an elevator to a certain floor.
The floors and floor names were kept hard coded in the main.cpp file.

Here is an example of the input/output commands that the user can type to the
terminal:
add_elevator <elevator-id> <max-weight-supported-in-kgs>
status <elevator-id>
call_elevator <elevator-id> <floor id>
enter_elevator <elevator-id> <total-weight-in-kgs-entering> <floor id called>
exit_elevator <elevator-id> <weight-exiting>
continue <elevator-id>

-Example of the command add_elevator <elevator-id> <max-weight-supported-in-kgs>
Example command: add_elevator 1 200
This commands adds elevator id = 1, that supports a maximum of 200 kgs in it.
The elevators starts at the beginning in the lowest floor id.

  Response:
  success -> if the request is successful
  failure -> if the request fails

-Example of the command status <elevator_id>
Example Command: status 2
This requests for real time status of the elevator 2.

  Possible responses are:
  Status of Elevator id=2: movingUp, at floor = xxx, going to floor = xxx, curr.: xxx kg / max.: xxx kg.
  Status of Elevator id=2: movingDown, at floor = xxx, going to floor = xxx, curr.: xxx kg / max.: xxx kg.
  Status of Elevator id=2: stationary, at floor = xxx, going to floor = xxx, curr.: xxx kg / max.: xxx kg.

  it is also printed the content of the elevator in terms of call_elevator and
  enter_elevator commands, example of the content provided also with the status 2:
    Content of enter to elevator 2: Enter_elevator 2 400 3
    Content of enter to elevator 2: Enter_elevator 2 400 2
    Content of calls to elevator 2: Call_elevator 2 5

-Example of the command call_elevator <elevator-id> <floor id>
Example Command: call_elevator 2 5
This request call the elevator with the id=5 to the floor number 5.

  Possible responses are:
  success -> if the request is successful
  failure -> if the request fails

-Example of the command continue <elevator-id>
Example: continue 1
This request for the next action in elevator 1. If the elevator has is moving
then it will stop in the next call_elevator or enter_elevator action. If the
elevator is stationary and has some enter_elevator or call_elevator in storage
then it will pass to a moving state when continue is used.
(if the elevator is stationary and has no call_elevator in the system, if it
receives the first call_elevator it will automatically switch to a moving state,
in all the other cases it needs the continue commmand).

-Example of the command enter_elevator <elevator-id> <total-weight-in-kgs-entering> <floor id called>
Example: enter_elevator 2 80 3
This request for the elevator id=2 to a person with 80 kg to enter in the
elevator, to go to the floor id=3. If the elevator don´t admit this weight then
it will fail the command. This command can only be used when the elevator is at
a stationary state.

  Possible responses are:
  success -> if the request is successful
  failure -> if the request fails

-Example of the command exit_elevator <elevator-id> <total-weight-in-kgs-exiting>
Example_ exit_elevator 2 90
This request for a person to leave elevator 2, weighting 90 kg, it can only
leave the elevator if the elevator is stationary.

  Possible responses are:
  success -> if the request is successful
  failure -> if the request fails

-The command "out" is used to exit the program.

## File and class structure of the program

In the main.cpp it is initialized the output file "output.txt" that is going to
have all the commands inserted in the system with the replies as well as the
floors data. In this file there is a cycle that receives the input from the user
and then it uses a switch case to decide witch action to take.

In the class Floor (Floor.h/cpp) are stored the floor number and floor type,
with the getters and setters.

In the namespace CapstoneParser (CapstoneParser.h/cpp) are several utility
functions used in the main to print data to file and cout, to print commands
info in each cycle, to receive and parse the commands, to add the floor data to
the class scheduler as well as other data validations.

In the class Scheduler (Scheduler.h/cpp) there are several methods that implement
all the commands. There is in this class the vector of elevators and floors
present in the system and also mapping between then and the id of each one. The
Scheduler decides witch call_elevator or enter_elevator to serve using the
principle of FIFO (First In First Out) algorithm.

The the class Elevator (Elevator.h/cpp) has several methods that implement
the several commands at the elevator level, it is present all the data needed
for that effect namely the id, max and current weight, actual floor number, the
state of the elevator and the list of all the call_elevator and/or enter_elevator
to serve.

The program prints all the commands received as well as all the actions and
responses taken to the file "output.txt" at the build directory.

## Example of a output of the program, that was generated in the file "output.txt"

File "output.txt" opened sucessfully.
Scheduler created.

Elevator number		Elevator type

-2			Garage-Lower level
-1			Garage-Upper level
0			Restauration
1			Commerce-Lower level
2			Commerce-Upper level
3			Office-Lower level
4			Office-Mid level
5			Office-Upper level

Command: "add_elevator 2 1200"
Elevator created: id=2, maxWeight=1200 kg, stateElevator=stationary.

Command: "enter_elevator 2 400 3"
Sucess: Enter_elevator 2 400 3.

Command: "enter_elevator 2 400 2"
Sucess: Enter_elevator 2 400 2.

Command: "status" is not a valid command
Command: "status 2"
Status of Elevator id=2: stationary, at floor = -2, curr.: 800 kg / max.: 1200 kg.
	Content of enter to elevator 2: Enter_elevator 2 400 3
	Content of enter to elevator 2: Enter_elevator 2 400 2

Command: "call_elevator 2 5"
Sucess: Call_elevator 2 5.

Command: "status 2"
Status of Elevator id=2: movingUp, at floor = -2, going to floor = 3, curr.: 800 kg / max.: 1200 kg.
	Content of enter to elevator 2: Enter_elevator 2 400 3
	Content of enter to elevator 2: Enter_elevator 2 400 2
	Content of calls to elevator 2: Call_elevator 2 5

Command: "continue 2"
Sucess: Continue 2.

Command: "status 2"
Status of Elevator id=2: stationary, at floor = 3, curr.: 800 kg / max.: 1200 kg.
	Content of enter to elevator 2: Enter_elevator 2 400 2
	Content of calls to elevator 2: Call_elevator 2 5

Command: "exit_elevator 2 400"
Sucess: Exit_elevator 2 400.

Command: "status 2"
Status of Elevator id=2: stationary, at floor = 3, curr.: 400 kg / max.: 1200 kg.
	Content of enter to elevator 2: Enter_elevator 2 400 2
	Content of calls to elevator 2: Call_elevator 2 5

Command: "continue 2"
Sucess: Continue 2.

Command: "status 2"
Status of Elevator id=2: movingDown, at floor = 3, going to floor = 2, curr.: 400 kg / max.: 1200 kg.
	Content of enter to elevator 2: Enter_elevator 2 400 2
	Content of calls to elevator 2: Call_elevator 2 5

Command: "continue 2"
Sucess: Continue 2.

Command: "status 2"
Status of Elevator id=2: stationary, at floor = 2, curr.: 400 kg / max.: 1200 kg.
	Content of calls to elevator 2: Call_elevator 2 5

Command: "exit_elevator 2 400"
Sucess: Exit_elevator 2 400.

Command: "status 2"
Status of Elevator id=2: stationary, at floor = 2, curr.: 0 kg / max.: 1200 kg.
	Content of calls to elevator 2: Call_elevator 2 5

Command: "continue 2"
Sucess: Continue 2.

Command: "status 2"
Status of Elevator id=2: movingUp, at floor = 2, going to floor = 5, curr.: 0 kg / max.: 1200 kg.
	Content of calls to elevator 2: Call_elevator 2 5

Command: "continue 2"
Sucess: Continue 2.

Command: "status 2"
Status of Elevator id=2: stationary, at floor = 5, curr.: 0 kg / max.: 1200 kg.
	Content of calls to elevator 2: empty

Command: "out"
Closing file "output.txt"


## Rubric specifications addressing

Criteria 1: The project demonstrates an understanding of C++ functions and
control structures.

There are used control structures as whiles in the main.cpp (line 45), as well
as switch cases in main.cpp (line 53) or for loops in CapstoneParser.cpp (line
  156).

The code is divided in functions as we can observe in the CapstoneParser.h.

Criteria 2: The project reads data from a file and process the data, or the
program writes data to a file.

The code writes data to file "output.txt" in the build directory, for example in
Scheduler.cpp (line 35).

Criteria 3: The project accepts user input and processes the input.

It receives user input in CapstoneParser.cpp (line 149) and processes the input
int CapstoneParser.cpp (method CapstoneParser::commandParser line 91).

Criteria 4: The project uses Object Oriented Programming techniques.

This project uses OOP, with the Scheduler, Elevator and Floor classes.
Each class has data and methods that work on that data, example in Scheduler.cpp
(line 24).

Criteria 5: Classes use appropriate access specifiers for class members.

All data members use private specifiers in Elevator.h (line 66), Floor.h
(line 23) or public in Scheduler.h (line 41)

Criteria 6: Class constructors utilize member initialization lists.

At Floor.cpp (line 8), Scheduler.cpp (line 14) and Elevator.cpp (line 10 and 17)

Criteria 7: The project makes use of references in function declarations.

At Scheduler.h (lines 20 and 23).

Criteria 8: The project uses destructors appropriately.

At Scheduler.h (line 16).

Criteria 9: The project uses smart pointers instead of raw pointers.

The project uses shared_pt instead of raw pointers in all the project,
for example in Scheduler.h (line 41).
