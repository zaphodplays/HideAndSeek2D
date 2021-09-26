#include "MovingState.hpp"
#include <math.h>
#include <cmath>

MovingState::MovingState()
{
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
		shared_ptr<AnimationSequence> moveseq = make_shared<AnimationSequence>();

		shared_ptr<DisplayObject> standingWithHandsUp = make_shared<DisplayObject>();
		shared_ptr<Line> hand1 = make_shared<Line>();
		hand1->addPoints(347, 342, 364, 348);
		hand1->setColour(0x000000u);

		shared_ptr<Line> hand2 = make_shared<Line>();
		hand2->addPoints(379, 345, 394, 334);
		hand2->setColour(0x000000u);

		shared_ptr<Line> leg1 = make_shared<Line>();
		leg1->addPoints(365, 364, 359, 381);
		leg1->setColour(0x000000u);

		shared_ptr<Line> leg2 = make_shared<Line>();
		leg2->addPoints(375, 365, 383, 381);
		leg2->setColour(0x000000u);

		shared_ptr<Polygon> polygon = make_shared<Polygon>();
		polygon->addPoint2d(367,341);
		polygon->addPoint2d(377, 341);
		polygon->addPoint2d(384, 364);
		polygon->addPoint2d(359, 364);
		polygon->addPoint2d(367, 341);

		shared_ptr<Circle> circle = make_shared<Circle>();
		circle->addParameters(371,332, 10, 0x00ccbbu);

		shared_ptr<Circle> eye1 = make_shared<Circle>();
		eye1->addParameters(368,330, 2, 0x000000u);

		shared_ptr<Circle> eye2 = make_shared<Circle>();
		eye2->addParameters(375,330,2, 0x000000u);

		shared_ptr<Line> mouth = make_shared<Line>();
		mouth->addPoints(368,335, 374, 335);
		mouth->linecolour = 0x000000u;

		
		standingWithHandsUp->setCenter(polygon->getCenter()->x, polygon->getCenter()->y);
		

		shared_ptr<DisplayObject> standingWithHandsDown = make_shared<DisplayObject>();
		shared_ptr<Line> hp_hand1 = make_shared<Line>();
		hp_hand1->addPoints(347, 352, 364, 348);
		hp_hand1->setColour(0x000000u);

		shared_ptr<Line> hp_hand2 = make_shared<Line>();
		hp_hand2->addPoints(379, 345, 394, 354);
		hp_hand2->setColour(0x000000u);

		shared_ptr<Line> hp_leg1 = make_shared<Line>();
		hp_leg1->addPoints(365, 364, 359, 381);
		hp_leg1->setColour(0x000000u);

		shared_ptr<Line> hp_leg2 = make_shared<Line>();
		hp_leg2->addPoints(375, 365, 383, 381);
		hp_leg2->setColour(0x000000u);

		shared_ptr<Polygon> hp_polygon = make_shared<Polygon>();
		hp_polygon->addPoint2d(367,341);
		hp_polygon->addPoint2d(377, 341);
		hp_polygon->addPoint2d(384, 364);
		hp_polygon->addPoint2d(359, 364);
		hp_polygon->addPoint2d(367, 341);

		shared_ptr<Circle> hp_circle = make_shared<Circle>();
		hp_circle->addParameters(371,332, 10, 0x00ccbbu);
		
		shared_ptr<Circle> hp_eye1 = make_shared<Circle>();
		hp_eye1->addParameters(368,330, 2, 0x000000u);

		shared_ptr<Circle> hp_eye2 = make_shared<Circle>();
		hp_eye2->addParameters(375,330,2, 0x000000u);

		shared_ptr<Line> hp_mouth = make_shared<Line>();
		hp_mouth->addPoints(368,335, 374, 335);
		hp_mouth->linecolour = 0x000000u;

		
		standingWithHandsDown->setCenter(hp_polygon->getCenter()->x, hp_polygon->getCenter()->y);

		moveseq->addImage(standingWithHandsUp);
		moveseq->addImage(standingWithHandsDown);
		return moveseq;	
	}

