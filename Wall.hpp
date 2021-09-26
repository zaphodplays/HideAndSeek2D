#ifndef _WALL_HPP
#define _WALL_HPP

class Wall : public enable_shared_from_this
{
  shared_ptr<Polygon> wall;
  DoorType wallType;
  Direction direction;
  shared_ptr<Door> door;

public:
  void setWall(DoorType dtype);
  void setDirection(Direction dir);
  shared_ptr<Wall> getWall();
  DoorType getWallType();
  Direction getDirection();
  void setDoor(shared_ptr<Door> door);
  shared_ptr<Door> getDoor();
};
#endif
