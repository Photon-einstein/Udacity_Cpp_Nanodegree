#ifndef FLOOR_H
#define FLOOR_H

#include <string>

class Floor {
public:
    /* constructor / destructor*/
    Floor();
    Floor(int floorNumber, std::string floorType);
    ~Floor();

    /* setters */
    void setFloorNumber(int floorNumber);
    void setFloorType(std::string floorType);

    /* getter */
    int getFloorNumber();
    std::string getFloorType();


private:
  int _floorNumber{};
  std::string _floorType{};
};

#endif
