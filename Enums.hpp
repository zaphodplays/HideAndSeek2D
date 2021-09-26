#ifndef _ENUMS_H
#define _ENUMS_H

typedef enum
  {
   NORMALTIME,
   FASTTIME,
   GAMETIMECount
  } GameTimeType;


typedef enum {
  CAREFUL,
  FUN,
  RISKY,
  NUTTY,
  PersonalityCount
} AIPersonalityType;

typedef enum {
	      STANDING,
	      STANDINGHANDSUP,
	      STANDINGHANDSDOWN,
	      JUMPING,
	      JUMPINGPOSEONE,
	      JUMPINGPOSETWO,
	      WALKING,
	      WALKINGPOSEONE,
	      WALKINGPOSETWO,
	      HIDDEN,
	      PEEKING,
	      PEEKINGPOSEONE,
	      PEEKINGPOSETWO,
	      CLIMBING,
	      CLIMBINGPOSEONE,
	      CLIMBINGPOSETWO,
	      PlayerDisplayCount
	   
} PlayerDisplay;

typedef enum {
	      INVALID,
	      CONTINUE,
	      LIST,
	      LOOK,
	      LIGHTS,
	      HIDE,
	      UNHIDE,
	      PEEK,
	      RUN,
	      CHECK,
	      MOVE,
	      JUMP,
	      CMDCount
} CommandType;

typedef enum {
	      WEST,
	      NORTH,
	      EAST,
	      SOUTH,
	      UP,
	      DOWN,
	      DIRECTIONCount
} Direction;


typedef enum {

  BEDROOM,
  LIVINGROOM,
  CENTRALHALL,
  DININGROOM,
  KITCHEN,
  BATHROOM,
  STAIRCASE,
  GARDEN,
  GYM,
  PLAYGROUND,
  OFFICE,
  LIBRARY,
  TERRACE,
  BASEMENT,
  ATTIC,
  BALCONY,
  ROOMTYPECount

} ROOMTYPE;

typedef enum {
  ON,
  OFF,
  IN,
  OVER,
  UNDER,
  BEHIND,
  RELATIONCount
} RELATION;

typedef enum {
  NONE,
  CHAIR,
  BED,
  TABLE,
  TREE,
  BUSH,
  DOOR,
  SOFA,
  WARDROBE,
  LARGEBOX,
  TRAMPOLINE,
  THINGTYPECount

} ThingType;

typedef enum {
  LEFT,
  FRONT,
  RIGHT,
  BACK,
  TOP,
  BOTTOM,
  DoorCount
} DoorType;
//871323
//T 582313
//old 583231 or 853231
#endif
