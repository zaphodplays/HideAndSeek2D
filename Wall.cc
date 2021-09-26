#include "Wall.hpp"

void Wall::setWallType(DoorType dtype)
{
  wallType = dtype;
}

DoorType Wall::getWallType()
{
  return wallType;
}

void Wall::setDirection(Direction dir)
{
  this->dir = dir;
}

Direction Wall::getDirection()
{
  return direction;
}

void Wall::setDoor(shared_ptr<Door> d)
{
  door = d;
}

shared_ptr<Door> Wall::getDoor()
{
  return door;
}

shared_ptr<Wall> Wall::getWall()
{
  return shared_from_this();
}
