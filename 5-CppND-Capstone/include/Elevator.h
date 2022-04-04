#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <list>

typedef struct {
   int floorCalled{};
   double weightEntering{};
   bool flagEnterElevator{}; /* 0 if "call_elevator" comand, 1 if "enter_elevator" command */
} actionData;

enum StateElevator {stationary=0, movingUp, movingDown};
enum StateMachineElevator {stationaryNoCalls=0, moving, stationaryWithCalls};

static const char *stateElevator_str[] = { "stationary", "movingUp", "movingDown"};

class Elevator {
public:
    /* constructor / destructor */
    Elevator(std::ofstream &outFile);
    Elevator(int idElevator, double maxWeight, std::ofstream &outFile);
    ~Elevator();

    /* setters */
    void setIdElevator(int idElevator);
    void setMaxWeight(double maxWeight);
    void setFloorNumber(int floorNumber);
    void setStateElevator(StateElevator stateElevator);
    void addCurrWeight(double weightEntering);
    void subtractCurrWeight(double weightLeaving);

    /* getter */
    int getIdElevator();
    double getMaxWeight();
    double getCurrWeight();
    int getFloorNumber();
    int getGoalFloorNumber();
    StateElevator getStateElevator();

    /* other methods */

    /* this method makes the processing of the state machine of the elevator for
    the call_elevator <id elevator> <floorNumberCall> action, in the end if
    just returns */
    void processCallElevator(actionData floorNumberCall);

    /* this method makes the processing of the state machine of the elevator for
    the continue <elevator id> action, in the end if just returns */
    void processContinue();

    /* this method makes the extraction of all the call_elevator calls from the
    _floorNumberCalls list that were called to the floor = floorNumberCall, in
    the end if just returns */
    void extractionOfCallsAtPresentFloor(const actionData &floorNumberCall);

    /* this method makes the print of the _floorNumberCalls to std::cout and
    also to _outFile, and then it just returns */
    void printContentElevator();

    /* this method makes the processing of the state machine of the elevator for
    the enter_elevator <id elevator> <weight entering> <floorNumberCall> action,
    in the end if just returns */
    void processEnterElevator(actionData floorNumberCall);


private:
  int _idElevator{};
  double _maxWeight{500};
  double _currWeight{};
  int _floorNumber{};
  StateElevator _stateElevator{StateElevator::stationary};
  std::ofstream &_outFile;
  std::list<actionData> _floorNumberCalls{};
  StateMachineElevator _stateMachineElevator{StateMachineElevator::stationaryNoCalls};
};

#endif
