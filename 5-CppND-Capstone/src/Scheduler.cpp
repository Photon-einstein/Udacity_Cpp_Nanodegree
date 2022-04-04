#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <memory>

#include "Scheduler.h"
#include "Elevator.h"

static const char *commandFirstName_str[] = {"out", "add_elevator", "status", "call_elevator", "enter_elevator", "exit_elevator", "continue", "not_a_valid_command"};

/* constructor / destructor */
Scheduler::Scheduler(std::ofstream &outFile):_outFile(outFile) {
  std::cout<<"Scheduler created."<<std::endl;
  _outFile<<"Scheduler created."<<std::endl;
}
/******************************************************************************/
Scheduler::~Scheduler() {
  std::cout<<"Scheduler deleted."<<std::endl;
}
/******************************************************************************/
/* this function makes the add_elevator command logic, in the end it just returns */
void Scheduler::addElevatorCommand(const std::vector<double> &otherValues) {
  if (_converterIdElevator.find(static_cast<int>(otherValues[0])) == _converterIdElevator.end() && otherValues[1] > 0) {
    /* new elevator is created */
    _elevatorVector.emplace_back(std::make_shared<Elevator>(static_cast<int>(otherValues[0]), otherValues[1], _outFile));
    _converterIdElevator[static_cast<int>(otherValues[0])] = _elevatorVector[_elevatorVector.size()-1];
    /* set elevator in the lowest floor of the building at the start of the simulation */
    _elevatorVector[_elevatorVector.size()-1]->setFloorNumber(_floors[0]->getFloorNumber());
  } else {
    /* this id elevator already exists */
    if (otherValues[1] > 0) {
      std::cout<<"\t#### Elevator id = "<<static_cast<int>(otherValues[0])<<" already exists, it is not possible to create another one.\n"<<std::endl;
      _outFile<<"Elevator id = "<<static_cast<int>(otherValues[0])<<" already exists, it is not possible to create another one.\n"<<std::endl;
    } else {
      std::cout<<"\t#### Elevator id = "<<static_cast<int>(otherValues[0])<<" cannot have a weight less than 0 kg.\n"<<std::endl;
      _outFile<<"Elevator id = "<<static_cast<int>(otherValues[0])<<" cannot have a weight less than 0 kg.\n"<<std::endl;
    }
  }
  return;
}
/******************************************************************************/
/* this function makes the status command logic, in the end it just returns */
void Scheduler::statusElevatorCommand(const std::vector<double> &otherValues) {
  /* elevator id exists */
  if (_converterIdElevator.find(static_cast<int>(otherValues[0])) != _converterIdElevator.end()) {
    std::cout<<"\t#### Status of Elevator id = "<<static_cast<int>(otherValues[0])<<": "<<stateElevator_str[_converterIdElevator[static_cast<int>(otherValues[0])]->getStateElevator()]<<", at floor = "<<_converterIdElevator[static_cast<int>(otherValues[0])]->getFloorNumber();
    _outFile<<"Status of Elevator id="<<static_cast<int>(otherValues[0])<<": "<<stateElevator_str[_converterIdElevator[static_cast<int>(otherValues[0])]->getStateElevator()]<<", at floor = "<<_converterIdElevator[static_cast<int>(otherValues[0])]->getFloorNumber();
    if (_converterIdElevator[static_cast<int>(otherValues[0])]->getStateElevator() != StateElevator::stationary) {
      std::cout<<", going to floor = "<<_converterIdElevator[static_cast<int>(otherValues[0])]->getGoalFloorNumber();
      _outFile<<", going to floor = "<<_converterIdElevator[static_cast<int>(otherValues[0])]->getGoalFloorNumber();
    }
    std::cout<<", curr.: "<<_converterIdElevator[static_cast<int>(otherValues[0])]->getCurrWeight()<<" kg / max.: "<<_converterIdElevator[static_cast<int>(otherValues[0])]->getMaxWeight()<<" kg.";
    _outFile<<", curr.: "<<_converterIdElevator[static_cast<int>(otherValues[0])]->getCurrWeight()<<" kg / max.: "<<_converterIdElevator[static_cast<int>(otherValues[0])]->getMaxWeight()<<" kg.";
    /* print list of content in the list */
    _converterIdElevator[static_cast<int>(otherValues[0])]->printContentElevator();
    std::cout<<std::endl;
    _outFile<<std::endl;
  } else {
    /* elevator id dont exists */
    std::cout<<"\t#### Elevator id = "<<static_cast<int>(otherValues[0])<<" don't exists yet.\n"<<std::endl;
    _outFile<<"Elevator id = "<<static_cast<int>(otherValues[0])<<" don't exists yet.\n"<<std::endl;
  }
  return;
}
/******************************************************************************/
void Scheduler::callElevatorCommand(const std::vector<double>  &otherValues) {
  /* this function makes the call_elevator logic, in the end it just returns */
  /* test if elevator exists */
  actionData action;
  if (_converterIdElevator.find(static_cast<int>(otherValues[0])) == _converterIdElevator.end()) {
    /* this id elevator don´t exist */
    std::cout<<"\t#### Failure: Elevator id = "<<static_cast<int>(otherValues[0])<<" don´t exists.\n"<<std::endl;
    _outFile<<"Failure: Elevator id = "<<static_cast<int>(otherValues[0])<<" don´t exists.\n"<<std::endl;;
    return;
  } else if (_converterIdFloor.find(static_cast<int>(otherValues[1])) == _converterIdFloor.end()) {
    /* the id floor typed don´t exist */
    std::cout<<"\t#### Failure: Floor id = "<<static_cast<int>(otherValues[1])<<" don´t exists.\n"<<std::endl;
    _outFile<<"Failure: Floor id = "<<static_cast<int>(otherValues[1])<<" don´t exists.\n"<<std::endl;
    return;
  } else {
    std::cout<<"\t#### Sucess: Call_elevator "<<static_cast<int>(otherValues[0])<<" "<<static_cast<int>(otherValues[1])<<"\n"<<std::endl;
    _outFile<<"Sucess: Call_elevator "<<static_cast<int>(otherValues[0])<<" "<<static_cast<int>(otherValues[1])<<".\n"<<std::endl;
    /* data fulling */
    action.floorCalled = static_cast<int>(otherValues[1]);
    _converterIdElevator[static_cast<int>(otherValues[0])]->processCallElevator(action);
    return;
  }
}
/******************************************************************************/
void Scheduler::continueCommand(const std::vector<double> &otherValues) {
  /* this function makes the implementation of the continue logic, in the end
  it just returns */
  if (_converterIdElevator.find(static_cast<int>(otherValues[0])) == _converterIdElevator.end()) {
    /* this id elevator don´t exist */
    std::cout<<"\t#### Failure: Elevator id = "<<static_cast<int>(otherValues[0])<<" don´t exists.\n"<<std::endl;
    _outFile<<"Failure: Elevator id = "<<static_cast<int>(otherValues[0])<<" don´t exists.\n"<<std::endl;;
    return;
  } else {
    std::cout<<"\t#### Sucess: Continue "<<static_cast<int>(otherValues[0])<<".\n"<<std::endl;
    _outFile<<"Sucess: Continue "<<static_cast<int>(otherValues[0])<<".\n"<<std::endl;
    /* process continue for id = otherValues[0] */
    _converterIdElevator[static_cast<int>(otherValues[0])]->processContinue();
    return;
  }
}
/******************************************************************************/
void Scheduler::enterElevatorCommand(const std::vector<double> &otherValues) {
  /* this function makes the implementation of the enter_elevator logic, in
  the end it just returns */
  actionData action;
  if (_converterIdElevator.find(static_cast<int>(otherValues[0])) == _converterIdElevator.end()) {
    /* this id elevator don´t exist */
    std::cout<<"\t#### Failure: Elevator id = "<<static_cast<int>(otherValues[0])<<" don´t exists.\n"<<std::endl;
    _outFile<<"Failure: Elevator id = "<<static_cast<int>(otherValues[0])<<" don´t exists.\n"<<std::endl;
  } else if (_converterIdElevator[static_cast<int>(otherValues[0])]->getMaxWeight() - _converterIdElevator[static_cast<int>(otherValues[0])]->getCurrWeight() < otherValues[1]) {
    /* this weight that was going to enter the elevator is above the maximum allowed at the moment */
    std::cout<<"\t#### Failure: Elevator id = "<<static_cast<int>(otherValues[0])<<" don´t supports "<<otherValues[1]<<" kgs, maximum allowed is: "<<_converterIdElevator[static_cast<int>(otherValues[0])]->getMaxWeight() - _converterIdElevator[static_cast<int>(otherValues[0])]->getCurrWeight() <<" kgs."<<std::endl;
    _outFile<<"Failure: Elevator id = "<<static_cast<int>(otherValues[0])<<" don´t supports "<<otherValues[1]<<" kgs, maximum allowed is: "<<_converterIdElevator[static_cast<int>(otherValues[0])]->getMaxWeight() - _converterIdElevator[static_cast<int>(otherValues[0])]->getCurrWeight() <<" kgs."<<std::endl;
  } else if (_converterIdFloor.find(static_cast<int>(otherValues[2])) == _converterIdFloor.end()) {
    /* the id floor typed don´t exist */
    std::cout<<"\t#### Failure: Floor id = "<<static_cast<int>(otherValues[2])<<" don´t exists.\n"<<std::endl;
    _outFile<<"Failure: Floor id = "<<static_cast<int>(otherValues[2])<<" don´t exists.\n"<<std::endl;
  } else if (_converterIdElevator[static_cast<int>(otherValues[0])]->getFloorNumber() == static_cast<int>(otherValues[2]) ) {
    std::cout<<"\t#### Failure: Elevator id = "<<static_cast<int>(otherValues[0])<<" is on the same destination Floor id of the enter_elevator = "<<static_cast<int>(otherValues[2])<<".\n"<<std::endl;
    _outFile<<"\t#### Failure: Elevator id = "<<static_cast<int>(otherValues[0])<<" is on the same destination Floor id of the enter_elevator = "<<static_cast<int>(otherValues[2])<<".\n"<<std::endl;
  } else if (_converterIdElevator[static_cast<int>(otherValues[0])]->getStateElevator() != StateElevator::stationary) {
    std::cout<<"\t#### Failure: Elevator id = "<<static_cast<int>(otherValues[0])<<" is not stationary.\n"<<std::endl;
    _outFile<<"\t#### Failure: Elevator id = "<<static_cast<int>(otherValues[0])<<" is not stationary.\n"<<std::endl;
  } else {
    std::cout<<"\t#### Sucess: Enter_elevator "<<static_cast<int>(otherValues[0])<<" "<<static_cast<int>(otherValues[1])<<" "<<static_cast<double>(otherValues[2])<<".\n"<<std::endl;
    _outFile<<"Sucess: Enter_elevator "<<static_cast<int>(otherValues[0])<<" "<<static_cast<int>(otherValues[1])<<" "<<static_cast<double>(otherValues[2])<<".\n"<<std::endl;
    /* data fulling */
    action.weightEntering = static_cast<double>(otherValues[1]);
    action.floorCalled = static_cast<int>(otherValues[2]);
    action.flagEnterElevator = true;
    /* process valid enter_elevator action */
    _converterIdElevator[static_cast<int>(otherValues[0])]->processEnterElevator(action);
  }
  return;
}
/******************************************************************************/
void Scheduler::exitElevatorCommand(const std::vector<double> &otherValues) {
  /* this function makes the implementation of the exit_elevator logic, in
  the end it just returns */
  if (_converterIdElevator.find(static_cast<int>(otherValues[0])) == _converterIdElevator.end()) {
    /* this id elevator don´t exist */
    std::cout<<"\t#### Failure: Elevator id = "<<static_cast<int>(otherValues[0])<<" don´t exists.\n"<<std::endl;
    _outFile<<"Failure: Elevator id = "<<static_cast<int>(otherValues[0])<<" don´t exists.\n"<<std::endl;
  } else if (_converterIdElevator[static_cast<int>(otherValues[0])]->getCurrWeight() < otherValues[1]) {
    /* this weight that was going to enter the elevator is above the maximum allowed at the moment */
    std::cout<<"\t#### Failure: Elevator id = "<<static_cast<int>(otherValues[0])<<" wish to leave  "<<otherValues[1]<<" kgs, maximum currently allowed is: "<<_converterIdElevator[static_cast<int>(otherValues[0])]->getCurrWeight() <<" kgs."<<std::endl;
    _outFile<<"Failure: Elevator id = "<<static_cast<int>(otherValues[0])<<" wish to leave "<<otherValues[1]<<" kgs, maximum currently allowed is: "<<_converterIdElevator[static_cast<int>(otherValues[0])]->getCurrWeight() <<" kgs."<<std::endl;
  } else if (_converterIdElevator[static_cast<int>(otherValues[0])]->getStateElevator() != StateElevator::stationary) {
    std::cout<<"\t#### Failure: Elevator id = "<<static_cast<int>(otherValues[0])<<" is not stationary.\n"<<std::endl;
    _outFile<<"\t#### Failure: Elevator id = "<<static_cast<int>(otherValues[0])<<" is not stationary.\n"<<std::endl;
  }  else {
    /* command "exit_elevator" entered with sucess */
    std::cout<<"\t#### Sucess: Exit_elevator "<<static_cast<int>(otherValues[0])<<" "<<static_cast<double>(otherValues[1])<<"\n"<<std::endl;
    _outFile<<"Sucess: Exit_elevator "<<static_cast<int>(otherValues[0])<<" "<<static_cast<double>(otherValues[1])<<".\n"<<std::endl;
    /* discount _currWeight with otherValues[1] amount */
    _converterIdElevator[static_cast<int>(otherValues[0])]->subtractCurrWeight(static_cast<double>(otherValues[1]));
  }
  return;
}
/******************************************************************************/
