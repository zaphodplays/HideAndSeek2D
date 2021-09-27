#include "MovingState.hpp"
#include <math.h>
#include <cmath>

MovingState::MovingState(shared_ptr<Player> player)
{
	this->player = player;
  targetCenter = make_shared<Point2d>();
  originalCenter = make_shared<Point2d>();
  isDone = false;
  initAnimationSequence();
}

void MovingState::initState(int roomid, shared_ptr<Point2d> targetCenter, shared_ptr<Point2d> originalCenter)
{
  std::cout<<"MovingState::init"<<endl;
  setLocationID(roomid);
  this->targetCenter->x = targetCenter->x;
  this->targetCenter->y = targetCenter->y;
  this->originalCenter->x = originalCenter->x;
  this->originalCenter->y = originalCenter->y;
  calculateCollinearPoints();
}

shared_ptr<RoleState> MovingState::getRoleState()
{
  return shared_from_this();
}

std::string MovingState::printState()
{
	std::cout<<"MovingState::printState()"<<endl;
  std::string print = "Moving in room ";
  shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;
  print = print + location->getName();
  return print;
}

void MovingState::displayState(Engine *engine, shared_ptr<Player> player)
{
    sequence->display(engine);
}

void MovingState::update(shared_ptr<Command> cmd, shared_ptr<stack<shared_ptr<RoleState> > > stateStack, shared_ptr<Player> player)
{
  switch(cmd->commandType)
    {
    case CONTINUE:
      {
	std::cout<<"in MovingState Continue"<<endl;
	if(hasReached(player))
	  {
	    //next State
	    isDone = true;
	  }
	else
	  {
	    //keep moving
	    keepMoving(player);
	  }
	SequenceState::update(cmd, stateStack, player);
	break;
      }
    default:
      {
	std::cout<<"command logic unimplemented"<<endl;
	break;
      }

    }
    
}

bool MovingState::hasReached(shared_ptr<Player> player)
{
  shared_ptr<Point2d> plocation = player->getCenter();
  return ((*plocation == *targetCenter));
}

void MovingState::keepMoving(shared_ptr<Player> player)
{
  // Check if element exists in vector
  shared_ptr<Point2d> plocation = player->getCenter();
  //vector<shared_ptr<Point2d> >::iterator it = std::find(linepoints->begin(), linepoints->end(), plocation);
  int size = linepoints->size();
  std::cout<<player->getName()<<" is moving points = "<<size<<endl;
  int match = size;
  for(int i = 0; i < size; i++)
	{
		shared_ptr<Point2d> point = (*linepoints)[i];
		if(*plocation == *point)
		{
			match = i;
		}
	}

  if (match < size-1)
    {
      int index = match;//std::distance(linepoints->begin(), it);
      shared_ptr<Point2d> center = player->getCenter();
      shared_ptr<Point2d> nextpoint = (*linepoints)[index + 1];
      player->shiftDisplay(nextpoint->x - center->x, nextpoint->y - center->y);
    }
  else
    {
      isDone = true;
      shared_ptr<Point2d> center = player->getCenter();
      player->shiftDisplay(targetCenter->x - center->x, targetCenter->y - center->y);
      std::cout << "Element Not Found" << std::endl;
    }

}

void MovingState::calculateCollinearPoints()
{
  linepoints = getCollinearPointsBetween(originalCenter, targetCenter);
  std::cout<<"filled in line points"<<endl;
}

shared_ptr<vector<shared_ptr<Point2d> > > MovingState::getCollinearPointsBetween(shared_ptr<Point2d> point1, shared_ptr<Point2d> point2)
	{
	  int diffx = point2->x - point1->x;
	  int diffy = point2->y - point1->y;
	  
	  shared_ptr<vector<shared_ptr<Point2d> > > points = make_shared<vector<shared_ptr<Point2d> > >();
	  if(point1->x == point2->x)
	    {
	      int miny = (point1->y < point2->y) ? point1->y : point2->y;
	      int maxy = (point1->y < point2->y) ? point2->y : point1->y;
	      for(int y = miny; y <= maxy; y++)
		{
		  shared_ptr<Point2d> point = make_shared<Point2d>();
		  point->x = point1->x;
		  point->y = y;
		  points->push_back(point);
		}
	      return points;
	    }
	  if(point1->y == point2->y)
	    {
	      int minx = (point1->x < point2->x)? point1->x : point2->x;
	      int maxx = (point1->x < point2->x)? point2->x : point1->x;
	      for(int x = minx; x <=maxx; x++)
		{
		  shared_ptr<Point2d> point = make_shared<Point2d>();
		  point->x = x;
		  point->y = point1->y;
		  points->push_back(point);
		}
	      return points;
	    }
	  /**
	  double m = ((double)(point2->y - point1->y))/((double)(point2->x - point1->x));
	  double x1d = (double)point1->x;
	  double y1d = (double)point1->y;;
	  double c = (y1d - m*x1d);
	  double minx = (point1->x < point2->x) ? (double)point1->x : (double)point2->x;
	  double maxx = (point1->x < point2->x) ? (double)point2->x : (double)point1->x;
	  double miny = (point1->y < point2->y) ? (double)point1->y : (double)point2->y;
	  double maxy = (point1->y < point2->y) ? (double)point1->y : (double)point2->y;

	  //printf("x1 = %d, x2 = %d\n", point1->x, point2->x);
	  //printf("minx = %f, maxx = %f\n", minx, maxx);
	  for(double  x = minx; x <= maxx; x+= 2)
	    {
	      double y = m*x + c;
	      
	      //if(trunc(y) == y)
	      //{
		  shared_ptr<Point2d> point = make_shared<Point2d>();
		  point->x = x;
		  point->y = y;
		  points->push_back(point);
		  //}
	    }
	  **/
	  int signx = diffx > 0 ? 1 : -1;
	  int signy = diffy > 0 ? 1 : -1;
	  int absx = abs(diffx);
	  int absy = abs(diffy);
	  
	  if(absx < absy)
	    {
	      int y = 0;
	      for(int x = 0; x <= absx; x += 10, y += 10)
		{
		  shared_ptr<Point2d> point = make_shared<Point2d>();
		  point->x = point1->x + x*signx;
		  point->y += point1->y + y*signy;
		  points->push_back(point);
		}
	      for(int y = diffx; y <= diffy; y += 10)
		{
		  shared_ptr<Point2d> point = make_shared<Point2d>();
		  point->x += point1->x + diffx;
		  point->y += point1->y + y*signy;
		  points->push_back(point);
		}
	    }
	  else
	    {
	      int x = 0;
	      for(int y = 0; y <= diffy; y += 10, x += 10)
		{
		  shared_ptr<Point2d> point = make_shared<Point2d>();
		  point->x = point1->x + x*signx;
		  point->y = point1->y + y*signy;
		  points->push_back(point);
		}
	      for(int x = diffy; x <= diffx; x += 10)
		{
		  shared_ptr<Point2d> point = make_shared<Point2d>();
		  point->x = point1->x + x*signx;
		  point->y = point1->y + diffy;
		  points->push_back(point);
		}
	      
	    }
	  std::cout<<"size of linepoints is "<<points->size()<<endl;
	  return points;
	}

	void MovingState::initAnimationSequence()
	{
		sequence = initMoveAnimationSequence();
	}

	shared_ptr<AnimationSequence> MovingState::initMoveAnimationSequence()
	{
		

		shared_ptr<AnimationSequence> movingseq = make_shared<AnimationSequence>();
		
    	shared_ptr<DisplayObject> standingImage = make_shared<DisplayObject>(player->getFilename(), player->getCenter()->x, player->getCenter()->y);	
		movingseq->addImage(standingImage);
    	
    	return movingseq;
	}

