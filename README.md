# HideAndSeek2D
# This is currently a single player game with multiple AI characters supported. 
# It is based on the simple children game of Hide and Seek
# The game world comprises of multiple rooms that are connected to each other
# The players can navigate to these rooms and hide in the objects in the rooms
# currently this is a keyboard command based game.
# currently only supported on macosx with SDL2 installed
# install SDL2 on macosx 10.15 or higher
# use below compile instruction for building
# the data.json can be altered to change the parameters of game like player personalities, player images, rooms, room connections, player roles (Seeker/Hider) etc. 
# the data.json can be edited before every run without needing a rebuild
# -------------------------------------------------------------HOW TO BUILD--------------------------------------
#
c++ -std=c++11 Point2d.cc Line.cc Circle.cc Polygon.cc TextObject.cc Engine.cc DisplayObject.cc AnimationSequence.cc Command.cc Thing.cc Chair.cc Tree.cc Door.cc Room.cc CommandParser.cc RoleState.cc EnteredState.cc HiddenState.cc JumpingState.cc PeekState.cc SequenceState.cc  Role.cc MovingState.cc AtDoorState.cc FoundState.cc SeekState.cc SeekerWaitState.cc Seeker.cc Hider.cc  Player.cc UserPlayer.cc AIPlayer.cc HideAndSeek.cpp -Wall -g -lSDL2 -lSDL2_image -lSDL2_ttf -fno-exceptions -o  ./HideAndSeek
# ----------------------------------------------------------------------------------------------------------------

# --------------------------------------------------------------HOW TO PLAY---------------------------------------
# Edit the data.json to configure any game related changes like players, rooms, roles etc. 
# start the game by invoking on command line  ./HideAndSeek 
# The game will start with an initial wait (10 seconds), while the players can run and hide 
# If you are a seeker, you are restricted and waiting at this time
# If you are a hider, you have to move and hide somewhere
# general commands -   
# 1. move north/south/west/east  
# 2. hide in Tree/Chair
# 3. peek
# 4. unhide
# 5. jump
# special command for seeker to find the hiders
# check Chair/Tree
# The game goes on until the seeker has found all the hiders