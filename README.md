# HideAndSeek2D
# currently only supported on macosx with SDL2 installed
# install SDL2 on macosx 10.15 or higher
# use below compile instruction for building
# the data.json can be altered to change the parameters of game like player personalities, player images, rooms, room connections, player roles (Seeker/Hider) etc. 
# the data.json can be edited before every run without needing a rebuild
c++ -std=c++11 Point2d.cc Line.cc Circle.cc Polygon.cc TextObject.cc Engine.cc DisplayObject.cc AnimationSequence.cc Command.cc Thing.cc Chair.cc Tree.cc Door.cc Room.cc CommandParser.cc RoleState.cc EnteredState.cc HiddenState.cc JumpingState.cc PeekState.cc SequenceState.cc  Role.cc MovingState.cc AtDoorState.cc FoundState.cc SeekState.cc SeekerWaitState.cc Seeker.cc Hider.cc  Player.cc UserPlayer.cc AIPlayer.cc HideAndSeek.cpp -Wall -g -lSDL2 -lSDL2_image -lSDL2_ttf -fno-exceptions -o  ./HideAndSeek