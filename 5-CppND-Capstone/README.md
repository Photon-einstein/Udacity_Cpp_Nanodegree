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
<br />
## Example of a output of the program, that was generated in the file "output.txt" <br />
<br />
File "output.txt" opened sucessfully. <br />
Scheduler created. <br />
<br />
Elevator number		Elevator type <br />
<br />
-2			Garage-Lower level <br />
-1			Garage-Upper level <br />
0			Restauration<br />
1			Commerce-Lower level<br />
2			Commerce-Upper level<br />
3			Office-Lower level<br />
4			Office-Mid level<br />
5			Office-Upper level<br />
<br />
#Command: "add_elevator 2 1200"<br />
Elevator created: id=2, maxWeight=1200 kg, stateElevator=stationary.<br />
<br />
#Command: "enter_elevator 2 400 3"<br />
Sucess: Enter_elevator 2 400 3.<br />
<br />
#Command: "enter_elevator 2 400 2"<br />
Sucess: Enter_elevator 2 400 2.<br />
<br />
#Command: "status" is not a valid command<br />
Command: "status 2"<br />
Status of Elevator id=2: stationary, at floor = -2, curr.: 800 kg / max.: 1200 kg.<br />
	Content of enter to elevator 2: Enter_elevator 2 400 3<br />
	Content of enter to elevator 2: Enter_elevator 2 400 2<br />
<br />
#Command: "call_elevator 2 5"<br />
Sucess: Call_elevator 2 5.<br />
<br />
#Command: "status 2"<br />
Status of Elevator id=2: movingUp, at floor = -2, going to floor = 3, curr.: 800 kg / max.: 1200 kg.<br />
	Content of enter to elevator 2: Enter_elevator 2 400 3<br />
	Content of enter to elevator 2: Enter_elevator 2 400 2<br />
	Content of calls to elevator 2: Call_elevator 2 5<br />
<br />
#Command: "continue 2"<br />
Sucess: Continue 2.<br />
<br />
#Command: "status 2"<br />
Status of Elevator id=2: stationary, at floor = 3, curr.: 800 kg / max.: 1200 kg.<br />
	Content of enter to elevator 2: Enter_elevator 2 400 2<br />
	Content of calls to elevator 2: Call_elevator 2 5<br />
<br />
#Command: "exit_elevator 2 400"<br />
Sucess: Exit_elevator 2 400.<br />
<br />
#Command: "status 2"<br />
Status of Elevator id=2: stationary, at floor = 3, curr.: 400 kg / max.: 1200 kg.<br />
	Content of enter to elevator 2: Enter_elevator 2 400 2<br />
	Content of calls to elevator 2: Call_elevator 2 5<br />
<br />	
#Command: "continue 2"<br />
Sucess: Continue 2.<br />
<br />
#Command: "status 2"<br />
Status of Elevator id=2: movingDown, at floor = 3, going to floor = 2, curr.: 400 kg / max.: 1200 kg.<br />
	Content of enter to elevator 2: Enter_elevator 2 400 2<br />
	Content of calls to elevator 2: Call_elevator 2 5<br />
<br />
#Command: "continue 2"<br />
Sucess: Continue 2.<br />
<br />
#Command: "status 2"<br />
Status of Elevator id=2: stationary, at floor = 2, curr.: 400 kg / max.: 1200 kg.<br />
	Content of calls to elevator 2: Call_elevator 2 5<br />
<br />
#Command: "exit_elevator 2 400"<br />
Sucess: Exit_elevator 2 400.<br />
<br />
#Command: "status 2"<br />
Status of Elevator id=2: stationary, at floor = 2, curr.: 0 kg / max.: 1200 kg.<br />
	Content of calls to elevator 2: Call_elevator 2 5<br />
<br />	
#Command: "continue 2"<br />
Sucess: Continue 2.<br />
<br />
#Command: "status 2"<br />
Status of Elevator id=2: movingUp, at floor = 2, going to floor = 5, curr.: 0 kg / max.: 1200 kg.<br />
	Content of calls to elevator 2: Call_elevator 2 5<br />
<br />
#Command: "continue 2"<br />
Sucess: Continue 2.<br />
<br />
#Command: "status 2"<br />
Status of Elevator id=2: stationary, at floor = 5, curr.: 0 kg / max.: 1200 kg.<br />
	Content of calls to elevator 2: empty<br />
<br />
#Command: "out"<br />
Closing file "output.txt"<br />
<br />
<br />
## Rubric specifications addressing<br />
<br />
#Criteria 1: The project demonstrates an understanding of C++ functions and<br />
control structures.<br />
<br />
#There are used control structures as whiles in the main.cpp (line 45), as well<br />
as switch cases in main.cpp (line 53) or for loops in CapstoneParser.cpp (line
  156).<br />
<br />
The code is divided in functions as we can observe in the CapstoneParser.h.<br />

#Criteria 2: The project reads data from a file and process the data, or the<br />
program writes data to a file.<br />
<br />
The code writes data to file "output.txt" in the build directory, for example in<br />
Scheduler.cpp (line 35).<br />
<br />
#Criteria 3: The project accepts user input and processes the input.<br />
<br />
It receives user input in CapstoneParser.cpp (line 149) and processes the input<br />
int CapstoneParser.cpp (method CapstoneParser::commandParser line 91).<br />
<br />
#Criteria 4: The project uses Object Oriented Programming techniques.<br />
<br />
This project uses OOP, with the Scheduler, Elevator and Floor classes.<br />
Each class has data and methods that work on that data, example in Scheduler.cpp<br />
(line 24).<br />
<br />
#Criteria 5: Classes use appropriate access specifiers for class members.<br />
<br />
All data members use private specifiers in Elevator.h (line 66), Floor.h<br />
(line 23) or public in Scheduler.h (line 41)<br />
<br />
#Criteria 6: Class constructors utilize member initialization lists.<br />
<br />
At Floor.cpp (line 8), Scheduler.cpp (line 14) and Elevator.cpp (line 10 and 17)<br />
<br />
#Criteria 7: The project makes use of references in function declarations.<br />
<br />
At Scheduler.h (lines 20 and 23).<br />
<br />
#Criteria 8: The project uses destructors appropriately.<br />
<br />	
At Scheduler.h (line 16).<br />
<br />
#Criteria 9: The project uses smart pointers instead of raw pointers.<br />
<br />
The project uses shared_pt instead of raw pointers in all the project,<br />
for example in Scheduler.h (line 41).<br />
