#include <string>

#include "Floor.h"


/* constructor / destructor */
Floor::Floor(){}
Floor::Floor(int floorNumber, std::string floorType):_floorNumber(floorNumber), _floorType(floorType) {}
Floor::~Floor(){}
/******************************************************************************/
/* setters */
void Floor::setFloorNumber(int floorNumber) {
  _floorNumber = floorNumber;
  return;
}
/******************************************************************************/
void Floor::setFloorType(std::string floorType) {
  _floorType = floorType;
  return;
}
/******************************************************************************/
/* getter */
int Floor::getFloorNumber() {
  return _floorNumber;
}
/******************************************************************************/
std::string Floor::getFloorType() {
  return _floorType;
}
/******************************************************************************/
