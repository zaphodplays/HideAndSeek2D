#include "PlayerDisplayImage.hpp"
#include <iostream>
using namespace std;

PlayerDisplayImage::DISP_IMG DisplayImage::NOT_FOUND_IMG = DisplayImage::initDISPIMG();

PlayerDisplayImage::PlayerDisplayImage()
{
  playerAnimationMap = make_shared<PlayerDisplay, shared_ptr<vector<FRAME_SEQ_NUM> > >();
}

void PlayerDisplayImage::setPath(std::string p)
{
  path = p;
}

void PlayerDisplayImage::getPath()
{
  return path;
}

void PlayerDisplayImage::setName(std::string n)
{
  name = n;
}

void PlayerDisplayImage::getName()
{
  return name;
}

void PlayerDisplayImage::display(Engine *engine, shared_ptr<Point2d> point)
{
  std::cout<<"generate image"<<endl;
}
