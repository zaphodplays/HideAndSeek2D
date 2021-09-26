#include "AnimationSequence.hpp"

using namespace std;

AnimationSequence::AnimationSequence()
{
  animation = make_shared<vector<shared_ptr<DisplayObject> > >();
  index = 0;
}

void AnimationSequence::setName(const std::string &name)
{
  this->name = name;
  int size = animation->size();
  for(int i = 0; i < size; i++)
    {
      (*animation)[i]->setText(name, 371,312);
    }
}

void AnimationSequence::addImage(shared_ptr<DisplayObject> dp)
{
  animation->push_back(dp);
}

shared_ptr<DisplayObject> AnimationSequence::getDisplayObject(int pos)
  {
    if(!animation->empty())
      {
	      int size = animation->size();
	      int r = pos % size;
	      return (*animation)[r];
      }
    return make_shared<DisplayObject>();
  }

  shared_ptr<Point2d> AnimationSequence::getCenter()
  {
    if(!animation->empty())
      {
	      
	      return (*animation)[0]->getCenter();
      }
    shared_ptr<Point2d> dummyCtr = make_shared<Point2d>();
    dummyCtr->set(-1,-1);
    return dummyCtr;
  }



void AnimationSequence::shiftDisplays(int x, int y)
{
  std::cout<<"AnimationSequence::shiftDisplays"<<endl;
  int size = animation->size();
  for(int i = 0; i < size; i++)
    {
      shared_ptr<DisplayObject> dp = (*animation)[i];
      dp->shift(x,y);
    }
  std::cout<<"AnimationSequence::shiftDisplays end"<<endl;
}

void AnimationSequence::display(Engine* engine)
{
  
      if(animation->empty())
        return;
      shared_ptr<DisplayObject> dp = (*animation)[index];
      if(index<animation->size()-1)
        index = index + 1;
      else
          index = 0;
      dp->display(engine);

     
}

void AnimationSequence::setColour(uint32_t dresscolour)
{
  std::cout<<"in animation set colour"<<endl;
  this->colour  = dresscolour;
  int size = animation->size();
  for(int i = 0; i < size; i++)
    {
      std::cout << "NOT setting colour"<<endl;
      /*
      if(  (*animation)[i] && (*animation)[i]->getPolygons() && (*(*animation)[i]->getPolygons())[0])
      {
        std::cout<<"within null condition check"<<endl;
        (*(*animation)[i]->getPolygons())[0]->incolour = dresscolour;
        std::cout<<"after null conditional check"<<endl;
      }
      */
    }
}

int AnimationSequence::getSize()
{
  return animation->size();
}





