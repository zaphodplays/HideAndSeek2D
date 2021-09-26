#ifndef _PLAYERDISPLAYIMAGE_HPP
#define _PLAYERDISPLAYIMAGE_HPP
#include "Engine.h"
#include "Point2d.hpp"
/**
 * Image class that is used to display images and animations by invoking the Engine
 * perhaps this can have a subclass called SpriteImage which has frames
 * 
 **/
class PlayerDisplayImage
{
  std::string path;
  std::string name;
  typedef uint32_t FRAME_SEQ_NUM;
  FRAME_SEQ_NUM frameSeqNum;
  PlayerDisplay displayType;
  shared_ptr<PlayerDisplay, shared_ptr<vector<FRAME_SEQ_NUM> > > playerAnimationMap;
  
public:

  void setPath(std::string path);
  std::string getPath();

  void setName(std::string name);
  std::string getName();

    
  typedef shared_ptr<PlayerDisplayImage> DISP_IMG;
  static DISP_IMG NOT_FOUND_IMG;

  DISP_IMG initDISPIMG()
  {
    DISP_IMG dpimg = make_shared<DisplayImage>();
    dpimg->setPath("./images/");
    dpimg->setName("NOTFOUND.png");
    return dpimg;
  }
};
#endif
