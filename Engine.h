#pragma once
#include <string>
#include <memory>
#include "Point2d.hpp"
#include "Polygon.hpp"
#include "Line.hpp"
#include "Circle.hpp"



struct Engine
{
	// Canvas size in pixels
	static const int CanvasWidth   = 640;
	static const int CanvasHeight  = 700;

	
     
        

	

	// Elapsed time since this instance was created
	double getStopwatchElapsedSeconds();

	// Clear the canvas and sample player input.
	// Quit the application when false is returned.
	bool startFrame();

	
	
	// Draw a text message with top left corner of first character at x,y.
	// Spacing is determined by FontWidth and FontRowHeight
	void drawText(std::string message, int x, int y);

	void drawImage(std::string filename, int x1, int y1);

	
	std::string getPlayerInputText();

	bool isUserTyping();

	void resetInput();
	
	Engine();
	~Engine();

};

