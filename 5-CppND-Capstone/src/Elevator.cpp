#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#include "Elevator.h"


/* constructor / destructor */
Elevator::Elevator(std::ofstream &outFile): _outFile(outFile) {
  std::cout<<"\tDefault elevator created: id="<<_idElevator<<", maxWeight="<<
  _maxWeight<<" kg, floorNumber="<<_floorNumber<<std::endl<<", stateElevator="<<stateElevator_str[_stateElevator]<<".\n"<<std::endl;
  outFile<<"\tDefault elevator created: id="<<_idElevator<<", maxWeight="<<
  _maxWeight<<" kg, floorNumber="<<_floorNumber<<std::endl<<", stateElevator="<<stateElevator_str[_stateElevator]<<".\n"<<std::endl;
}
/******************************************************************************/
Elevator::Elevator(int idElevator, double maxWeight, std::ofstream &outFile): _idElevator(idElevator), _maxWeight(maxWeight), _outFile(outFile) {
  std::cout<<"\t#### Elevator created: id="<<_idElevator<<", maxWeight="<<_maxWeight<<
  " kg, stateElevator="<<stateElevator_str[_stateElevator]<<".\n"<<std::endl;
  outFile<<"Elevator created: id="<<_idElevator<<", maxWeight="<<_maxWeight<<
  " kg, stateElevator="<<stateElevator_str[_stateElevator]<<".\n"<<std::endl;
}
/******************************************************************************/
Elevator::~Elevator() {}
/******************************************************************************/
/* setters */
void Elevator::setIdElevator(int idElevator) {
  _idElevator = idElevator;
}
/******************************************************************************/
void Elevator::setMaxWeight(double maxWeight) {
  _maxWeight = maxWeight;
}
/******************************************************************************/
void Elevator::setFloorNumber(int floorNumber) {
  _floorNumber = floorNumber;
}
/******************************************************************************/
void Elevator::setStateElevator(StateElevator stateElevator) {
  _stateElevator = stateElevator;
}
/******************************************************************************/
void Elevator::addCurrWeight(double weightEntering) {
  _currWeight+=weightEntering;
  return;
}
/******************************************************************************/
void Elevator::subtractCurrWeight(double weightLeaving) {
  _currWeight-=weightLeaving;
  return;
}
/******************************************************************************/
/* getter */
int Elevator::getIdElevator() {
  return _idElevator;
}
/******************************************************************************/
double Elevator::getMaxWeight() {
  return _maxWeight;
}
/******************************************************************************/
double Elevator::getCurrWeight() {
  return _currWeight;
}
/******************************************************************************/
int Elevator::getFloorNumber() {
  return _floorNumber;
}
/******************************************************************************/
StateElevator Elevator::getStateElevator() {
  return _stateElevator;
}
/******************************************************************************/
int Elevator::getGoalFloorNumber() {
  return _floorNumberCalls.front().floorCalled;
}
/******************************************************************************/
void Elevator::processCallElevator(actionData floorNumberCall) {
  /* this method makes the processing of the state machine of the elevator for
  the call_elevator <id elevator> <floorNumberCall> action, in the end if
  just returns */
  /* next state definition */
  if (_stateMachineElevator == StateMachineElevator::stationaryNoCalls) {
    /* action taken */
    _floorNumberCalls.emplace_back(floorNumberCall);
    /* new state provided */
    _stateMachineElevator = StateMachineElevator::moving;
    _stateElevator = (_floorNumber < floorNumberCall.floorCalled) ? StateElevator::movingUp : StateElevator::movingDown;
  } else if (_stateMachineElevator == StateMachineElevator::moving || _stateMachineElevator == StateMachineElevator::stationaryWithCalls) {
    /* action taken */
    _floorNumberCalls.emplace_back(floorNumberCall);
  }
  return;
}
/******************************************************************************/
void Elevator::processContinue() {
  /* this method makes the processing of the state machine of the elevator for
  the continue <elevator id> action, in the end if just returns */
  if (_stateMachineElevator == StateMachineElevator::stationaryNoCalls && _floorNumberCalls.size() > 0) {
    /* one or more "enter_elevator" actions already in the system, state of the elevator must be updated */
    _stateMachineElevator = StateMachineElevator::moving;
    _stateElevator = (_floorNumber < _floorNumberCalls.front().floorCalled) ? StateElevator::movingUp : StateElevator::movingDown;
  } else if (_stateMachineElevator == StateMachineElevator::moving && _floorNumberCalls.size() == 1) {
    /* only one call in the process */
    /* actualization of the floor number */
    _floorNumber = _floorNumberCalls.front().floorCalled;
    /* extraction of the call from the system */
    _floorNumberCalls.pop_front();
    /* actualization of the state */
    _stateMachineElevator = StateMachineElevator::stationaryNoCalls;
    _stateElevator = StateElevator::stationary;
  } else if (_stateMachineElevator == StateMachineElevator::moving && _floorNumberCalls.size() > 1) {
    /* more than one call in the system */
    /* actualization of the floor number */
    _floorNumber = _floorNumberCalls.front().floorCalled;
    /* extraction of the call from the system */
    extractionOfCallsAtPresentFloor(_floorNumberCalls.front());
    /* actualization of the state of the _stateMachineElevator */
    _stateMachineElevator = (_floorNumberCalls.size() == 0) ? StateMachineElevator::stationaryNoCalls : _stateMachineElevator = StateMachineElevator::stationaryWithCalls;
    _stateElevator = StateElevator::stationary;
  } else if (_stateMachineElevator == StateMachineElevator::stationaryWithCalls) {
    /* system with some calls waiting to be served */
    /* actualization of the state */
    _stateMachineElevator = StateMachineElevator::moving;
    _stateElevator = (_floorNumber < _floorNumberCalls.front().floorCalled) ? StateElevator::movingUp : StateElevator::movingDown;
  }
  return;
}
/******************************************************************************/
void Elevator::extractionOfCallsAtPresentFloor(const actionData &floorNumberCall) {
  /* this method makes the extraction of all the call_elevator calls from the
  _floorNumberCalls list that were called to the floor = floorNumberCall, in
  the end if just returns */
  std::list<actionData>::iterator it;
  for (it = _floorNumberCalls.begin(); it != _floorNumberCalls.end(); ++it) {
    if (it->floorCalled == floorNumberCall.floorCalled) {
      _floorNumberCalls.erase(it);
      it = _floorNumberCalls.begin();
    }
  }
  return;
}
/******************************************************************************/
void Elevator::printContentElevator() {
  /* this method makes the print of the _floorNumberCalls to std::cout and
  also to _outFile, and then it just returns */
  std::list<actionData>::iterator it;
  std::cout<<std::endl;
  _outFile<<std::endl;
  if (_floorNumberCalls.empty()) {
    std::cout<<"\t\t#### Content of calls to elevator "<<_idElevator<<": empty "<<std::endl;
    _outFile<<"\tContent of calls to elevator "<<_idElevator<<": empty "<<std::endl;
    return;
  }
  for (it = _floorNumberCalls.begin(); it != _floorNumberCalls.end(); ++it) {
    if (it->flagEnterElevator == false) {
      /* content of the actionData is a "call_elevator" action */
      std::cout<<"\t\t#### Content of calls to elevator "<<_idElevator<<": Call_elevator "<<_idElevator<<" "<<it->floorCalled<<std::endl;
      _outFile<<"\tContent of calls to elevator "<<_idElevator<<": Call_elevator "<<_idElevator<<" "<<it->floorCalled<<std::endl;
    } else {
      /* content of the actionData is a "enter_elevator" action */
      std::cout<<"\t\t#### Content of enter to elevator "<<_idElevator<<": Enter_elevator "<<_idElevator<<" "<<it->weightEntering<<" "<<it->floorCalled<<std::endl;
      _outFile<<"\tContent of enter to elevator "<<_idElevator<<": Enter_elevator "<<_idElevator<<" "<<it->weightEntering<<" "<<it->floorCalled<<std::endl;
    }
  }
  return;
}
/******************************************************************************/
void Elevator::processEnterElevator(actionData floorNumberCall) {
  /* this method makes the processing of the state machine of the elevator for
  the enter_elevator <id elevator> <weight entering> <floorNumberCall> action,
  in the end if just returns */
  addCurrWeight(floorNumberCall.weightEntering);
  /* action taken */
  _floorNumberCalls.emplace_back(floorNumberCall);
  return;
}
/******************************************************************************/
