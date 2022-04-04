#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <queue>
#include <fstream>
#include <fstream>
#include <map>

#include "Elevator.h"
#include "Floor.h"

class Scheduler {
public:
    /* constructor / destructor */
    Scheduler(std::ofstream &outFile);
    ~Scheduler();
    /* methods */

    /* this function makes the add_elevator command logic, in the end it just returns */
    void addElevatorCommand(const std::vector<double> &otherValues);

    /* this function makes the status command logic, in the end it just returns */
    void statusElevatorCommand(const std::vector<double> &otherValues);

    /* this function makes the call_elevator logic, in the end it just returns */
    void callElevatorCommand(const std::vector<double>  &otherValues);

    /* this function makes the implementation of the continue logic, in the end
    it just returns */
    void continueCommand(const std::vector<double> &otherValues);

    /* this function makes the implementation of the enter_elevator logic, in
    the end it just returns */
    void enterElevatorCommand(const std::vector<double> &otherValues);

    /* this function makes the implementation of the exit_elevator logic, in
    the end it just returns */
    void exitElevatorCommand(const std::vector<double> &otherValues);

    /* fields */
    std::vector<std::shared_ptr<Elevator>> _elevatorVector;
    std::map<int,std::shared_ptr<Elevator>> _converterIdElevator;
    std::ofstream &_outFile;
    std::vector<std::shared_ptr<Floor>> _floors;
    std::map<int,std::shared_ptr<Floor>> _converterIdFloor;
};

#endif
