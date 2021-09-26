#include "Engine.h"
#include <string>
#include <stdlib.h>
#include <stdint.h>
#include <cmath>
using namespace std;
#define _USE_MATH_DEFINES
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#ifndef M_PIl
#define M_PIl (3.14159265358979323846264338327950288)
#endif


//////////////////////////////////////////////////////////////////////////////
// DO NOT ADD YOUR CODE IN THIS FILE!
//////////////////////////////////////////////////////////////////////////////

namespace engine
{

	void init();
	void deinit();
	
	
  	void drawText(std::string message, int x, int y);
	void drawImage(std::string filename, int x1, int y1);
	
}

namespace platform
{
	
    static std::string inputString;
    static bool userTyping = true;

	void init();
	void deinit();
	
	bool update(std::string filename, int x1, int y1, int x2, int y2);
	bool update(std::string filename);
	bool update();
	bool testUpdate();
	double getStopwatchElapsedSeconds();
	void addTextToTexture(const std::string message, int x, int y);
	void addImageToTexture(const std::string filename, int x, int y);
}


// PUBLIC API

//////////////////////////////////////////////////////////////////////////////
// DO NOT ADD YOUR CODE IN THIS FILE!
//////////////////////////////////////////////////////////////////////////////

Engine::Engine()
{
	platform::init();
	engine::init();
}

Engine::~Engine()
{
	engine::deinit();
	platform::deinit();
}

bool Engine::startFrame()
{
	//bool shouldKeepGoing = platform::update(engine::canvas);
	//bool shouldKeepGoing = platform::testUpdate();
	bool shouldKeepGoing = platform::update();
	//engine::clearCanvas();
	return shouldKeepGoing;
}




void Engine::drawText(std::string message, int x, int y)
{
	engine::drawText(message, x, y);
}

void Engine::drawImage(std::string filename, int x1, int y1)
{
	engine::drawImage(filename, x1, y1);
}

double Engine::getStopwatchElapsedSeconds()
{
	return platform::getStopwatchElapsedSeconds();
}

std::string Engine::getPlayerInputText()
{
  return platform::inputString;
}


bool Engine::isUserTyping()
{
  return platform::userTyping;
}

void Engine::resetInput()
{
  platform::inputString = "";
  platform::userTyping = true;
}

// IMPLEMENTATION



namespace engine
{
	
	
	void init()
	{

	}

	void deinit()
	{
		
	}
	

    void drawText(std::string msg, int x, int y)
	{
		platform::addTextToTexture(msg, x, y);
	}

	void drawImage(std::string filename, int x, int y)
	{
		platform::addImageToTexture(filename, x, y);
	}
        
  
}

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>
#include <list>
#include <string>
#include <time.h>

namespace platform
{

	SDL_Surface* loadImage(std::string path);
	SDL_Texture* getImgTexture(std::string filename);

	SDL_Window* gameWindow_;
	SDL_Renderer* renderer;
	SDL_Texture * texture_target;
	
	list<SDL_Texture*> imgTextureList;
	list<SDL_Rect*> imgsourcerectList;
	list<SDL_Texture*> textTextureList;
	list<SDL_Rect*> textsourcerectList;
	TTF_Font* apple; 

	unordered_map<std::string, SDL_Texture*> imagemap;
        

	void init()
	{
		gameWindow_ = SDL_CreateWindow("Hiders Vs Seekers", 100, 100, Engine::CanvasWidth, Engine::CanvasHeight, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(gameWindow_, -1, SDL_RENDERER_ACCELERATED);
		/* Creation of the target texture. */
    	texture_target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, Engine::CanvasWidth, Engine::CanvasHeight);
    	/* Blend mode defaults to NONE, but we want it to blend it with the blue background */
    	SDL_SetTextureBlendMode(texture_target, SDL_BLENDMODE_BLEND);
		//initialize font
		if ( TTF_Init() < 0 ) {
			printf("Error initializing SDL_ttf: %s\n",TTF_GetError());
		}
		
		//apple = TTF_OpenFont("/System/Library/Fonts/Apple Braille.ttf", 20);
		apple = TTF_OpenFont("/System/Library/Fonts/Supplemental/Microsoft Sans Serif.ttf", 15);
		if ( !apple ) {
			printf("Failed to load font: %s\n",TTF_GetError());
		}
		/* Direct the draw commands to the target texture. */
		SDL_SetRenderTarget(renderer, texture_target);
		printf("init ENDS\n");
	}

	void deinit()
	{
		TTF_CloseFont(apple);
		TTF_Quit();
		//imgTextureList.clear();
		
		list<SDL_Texture*>::iterator txitor = textTextureList.begin();
		while(txitor != textTextureList.end())
		{
			SDL_Texture* txt = *txitor;
			//delete txt;
			SDL_DestroyTexture(txt);
			
			
			printf("E: %s\n", SDL_GetError());	
			SDL_ClearError();
			printf("erasing text textures\n");
			++txitor;
		}

		//textTextureList.clear();
		
		//textsourcerectList.clear();
		
		list<SDL_Rect*>::iterator litor = imgsourcerectList.begin();
		while(litor != imgsourcerectList.end())
		{
			SDL_Rect* rect = *litor;
			delete rect;
			rect = 0;
			++litor;
			
			printf("E: %s\n", SDL_GetError());	
			SDL_ClearError();
			printf("erasing img rect sources\n");
			
		}

		list<SDL_Rect*>::iterator ttitor = textsourcerectList.begin();
		while(ttitor != textsourcerectList.end())
		{
			SDL_Rect* rect = *ttitor;
			delete rect;
			rect = 0;
			++ttitor;
			
			printf("E: %s\n", SDL_GetError());	
			SDL_ClearError();
			printf("erasing text rect sources\n");
			
		}
		
		//imgsourcerectList.clear();

		unordered_map<std::string, SDL_Texture*>::iterator itor = imagemap.begin();
		
		SDL_ClearError();
		while(itor != imagemap.end())
		{
			SDL_Texture* texture = itor->second;
			//delete texture;
			//itor = imagemap.erase(itor);
			SDL_DestroyTexture(texture);
			//texture = 0;
			printf("E: %s\n", SDL_GetError());	
			SDL_ClearError();
			printf("erasing img textures\n");
			itor = imagemap.erase(itor);
		}
		//imagemap.clear();
		SDL_SetRenderTarget(renderer, NULL);
		SDL_DestroyTexture(texture_target);
		printf("erased target textures\n");
		SDL_DestroyRenderer(renderer);
		printf("erased renderer\n");
		SDL_DestroyWindow(gameWindow_);
		printf("destroyed game window\n");
		printf("finally %s\n", SDL_GetError());
		SDL_Quit();
	}

	

	void addTextToTexture(const std::string message, int x, int y) 
	{
		printf("addText:: %s at %d,%d\n", message.c_str(), x, y);
		//this opens a font style and sets a size
		
		// this is the color in rgb format,
		// maxing out all would give you the color white,
		// and it will be your text's color
		SDL_Color Red = {255, 255, 255};

		// as TTF_RenderText_Solid could only be used on
		// SDL_Surface then you have to create the surface first
		SDL_Surface* surfaceMessage =
			TTF_RenderText_Blended(apple, message.c_str(), Red); 
		if(!surfaceMessage)
		{
			printf("%s\n", SDL_GetError());
		}	

		// now you can convert it into a texture
		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		
		SDL_Rect* Message_rect = new SDL_Rect(); //create a rect
		Message_rect->x = x;  //controls the rect's x coordinate 
		Message_rect->y = y; // controls the rect's y coordinte
		Message_rect->w = surfaceMessage->w; // controls the width of the rect
		Message_rect->h = surfaceMessage->h; // controls the height of the rect
		SDL_FreeSurface(surfaceMessage);
		printf("before inserting\n");
		if(!Message)
		{
			printf("%s\n", SDL_GetError());
		}
		if(Message)
		{
			textTextureList.push_back(Message);
			textsourcerectList.push_back(Message_rect);
			printf("after insertion\n");
		}
		
		// (0,0) is on the top left of the window/screen,
		// think a rect as the text's box,
		// that way it would be very simple to understand
		Message_rect = 0;
	}


	void addImageToTexture(const std::string filename, int x, int y) 
	{
		if(filename.compare("") == 0)
			return;
		if(!renderer)
		{
			//rendrer = SDL_CreateRenderer(gameWindow_, -1, SDL_RENDERER_ACCELERATED);
			printf("RENDERER IS NULL %s\n", SDL_GetError());
			return;
		}
		printf("addImage:: %s at %d,%d\n", filename.c_str(), x, y);
		unordered_map<std::string, SDL_Texture*>::iterator itor = imagemap.find(filename);
		SDL_Texture* imgTexture;
		//SDL_Renderer* renderer = SDL_GetRenderer(gameWindow_);
		
		if(itor == imagemap.end())
			{
				
				//imgTexture = IMG_LoadTexture(renderer, filename.c_str());
				imgTexture = getImgTexture(filename);
				printf("IMAGE LOADED %s\n", filename.c_str());
				if(imgTexture)
				{
					imagemap[filename] = imgTexture;
					printf("added to map for %s\n", filename.c_str());
					
				}
				else 
				{
					printf("img texture null for %s\n", filename.c_str());
					
				}
				
			}
		else 
		{
			printf("IMAGE IN CACHE\n");
			imgTexture = itor->second;
		}
		if (!imgTexture)
		{
			printf("texture is null for %s\n", filename.c_str());
			//SDL_DestroyTexture(imgTexture);
			return;
		}
		
		int w,h;
		
		SDL_QueryTexture(imgTexture, NULL, NULL, &w, &h); // get the width and height of the texture
		// put the location where we want the texture to be drawn into a rectangle
		// I'm also scaling the texture 2x simply by setting the width and height
		printf("for  %s, x is %d, y is %d, w is %d , h is %d\n", filename.c_str(), x, y, w, h);
		SDL_Rect* texr = new SDL_Rect(); 
		texr->x = x; texr->y = y; texr->w = w; texr->h = h; 
		
		
		printf("before insertion\n");
		if(imgTexture) 
		{
			imgTextureList.push_back(imgTexture);
			imgsourcerectList.push_back(texr);
			printf("after insertion list size is %d\n", imgTextureList.size());
		}
		texr = 0;
		// (0,0) is on the top left of the window/screen,
		// think a rect as the text's box,
		// that way it would be very simple to understand
	}

	
	double getStopwatchElapsedSeconds()
	{
		struct timespec t;
		clock_gettime(CLOCK_MONOTONIC, &t);
		return (double)(t.tv_sec) + (double)(t.tv_nsec) * 1e-9;
	}

	SDL_Texture* getImgTexture(std::string filename)
	{
		//Load image at specified path
		SDL_Texture* imgTexture = NULL;
		SDL_Surface* loadedSurface = IMG_Load(filename.c_str());
		if( loadedSurface == NULL )
		{
			printf( "Unable to load image %s! SDL_image Error: %s\n", filename.c_str());
			return imgTexture;
		}
		imgTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_SetTextureBlendMode(imgTexture, SDL_BLENDMODE_BLEND);
		SDL_FreeSurface(loadedSurface);
		return imgTexture;
        
	}

	SDL_Surface* loadImage(std::string path)
	{
		//The final optimized image
		SDL_Surface* optimizedSurface = NULL;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		SDL_Surface* screenSurface = SDL_GetWindowSurface(gameWindow_);
		if( loadedSurface == NULL )
		{
			printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str());
		}
		else
		{
			//Convert surface to screen format
			
			optimizedSurface = SDL_ConvertSurface( loadedSurface, screenSurface->format, 0 );
			if( optimizedSurface == NULL )
		{
				printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

			//Get rid of old loaded surface
			SDL_FreeSurface( loadedSurface );
		}

		return optimizedSurface;
	}

	bool testUpdate()
	{
		if (!gameWindow_ )
			return false;

		SDL_SetRenderTarget(renderer, texture_target);
		SDL_Texture* imgTexture = getImgTexture("bedroom1.png");
		SDL_SetTextureBlendMode(imgTexture, SDL_BLENDMODE_BLEND);
		int w,h;
		SDL_QueryTexture(imgTexture, NULL, NULL, &w, &h); // get the width and height of the texture
		SDL_Rect rect = {0, 0, w, h};
		SDL_RenderCopy(renderer, imgTexture, NULL, &rect);
		SDL_SetRenderTarget(renderer, NULL);
		
		
		SDL_RenderCopy(renderer, texture_target, NULL, NULL);
		
		SDL_RenderPresent(renderer);

		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				deinit();
				return false;
			}
			if(e.key.keysym.scancode != SDL_SCANCODE_RETURN)
			  {
			    
			  
			    if (e.type == SDL_TEXTINPUT)
			      {
				userTyping = true;
				inputString += e.text.text;
			      }

			  }
			else{
			  userTyping = false;
			  return true;
			}
		}

		const Uint8* keyboard = SDL_GetKeyboardState(0);

		if (keyboard[SDL_SCANCODE_ESCAPE])
		{
			deinit();
			return false;
		}

		
		
		return true;
	}

	bool update()
	{
		if (!gameWindow_ )
			return false;
		//SDL_Rect drect = {100, 100, Engine::CanvasWidth, Engine::CanvasHeight};
		
		// clear the screen
		/* It's always a good idea to clear the whole thing first. */
		
		
		SDL_SetRenderTarget(renderer, texture_target);
		/* It's always a good idea to clear the whole thing first. */
    	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		
    	SDL_RenderClear(renderer);
		
		SDL_SetRenderTarget(renderer, texture_target);

		list<SDL_Rect*>::iterator litor = imgsourcerectList.begin();
		list<SDL_Texture*>::iterator titor = imgTextureList.begin();
		while(litor != imgsourcerectList.end())
		{
			SDL_Rect* rect = *litor;
			SDL_Rect drect = {rect->x, rect->y, rect->w, rect->h};
			
			SDL_Rect srect = {rect->x, rect->y, rect->w, rect->h};
			SDL_Texture* txr = *titor;
			
			
			if(txr)
			{
				printf("drect is %d, %d, %d, %d\n", drect.x, drect.y, drect.w, drect.h);
    		/* Let's copy the other textures onto the target texture. */
			//SDL_ClearError();
				SDL_RenderCopy(renderer, txr,  NULL, &drect);
				printf("%s\n", SDL_GetError());
				SDL_ClearError();
			}
    		
    		

			litor = imgsourcerectList.erase(litor); 
			titor = imgTextureList.erase(titor);
			
		}	

		list<SDL_Texture*>::iterator textitor = textTextureList.begin();
		list<SDL_Rect*>::iterator textrectitor = textsourcerectList.begin();
		while(textitor !=  textTextureList.end())
		{
			SDL_Rect* rect = *textrectitor;
			SDL_Rect drect = {rect->x, rect->y, rect->w, rect->h};
			
			SDL_Rect srect = {rect->x, rect->y, rect->w, rect->h};
			SDL_Texture* txr = *textitor;
			
			
			if(txr)
			{
				printf(" textdrect is %d, %d, %d, %d\n", drect.x, drect.y, drect.w, drect.h);
    		/* Let's copy the other textures onto the target texture. */
			//SDL_ClearError();
				SDL_RenderCopy(renderer, txr,  NULL, &drect);
				SDL_DestroyTexture(txr);
				printf("%s\n", SDL_GetError());
				SDL_ClearError();
			}
    		
    		

			textitor = textTextureList.erase(textitor);
			textrectitor = textsourcerectList.erase(textrectitor);
			
		}

		SDL_SetRenderTarget(renderer, NULL);
		
		
		SDL_RenderCopy(renderer, texture_target, NULL, NULL);

		
			
		// flip the backbuffer
		// this means that everything that we prepared behind the screens is actually shown
		SDL_RenderPresent(renderer);

		//clear the image texture list
		
		/*
		list<SDL_Texture*>::iterator imgitor = imgTextureList.begin();
		while(imgitor != imgTextureList.end())
		{
			SDL_Texture* texture = *imgitor;
			//delete texture;
			//itor = imagemap.erase(itor);
			
			texture = 0;
			
			
			++imgitor;
		}
		
		imgTextureList.clear();
		
		//clear img rectangles
		list<SDL_Rect*>::iterator imgrectitor = imgsourcerectList.begin();
		while(imgrectitor != imgsourcerectList.end())
		{
			SDL_Rect* rect = *imgrectitor;
			delete rect;
			rect = 0;
			
			
			++imgrectitor;
		}
		imgsourcerectList.clear();
		*/
		/**
		list<SDL_Texture*>::iterator textitor1 = textTextureList.begin();
		while(textitor1 != textTextureList.end())
		{
			SDL_Texture* texture = *textitor1;
			//delete texture;
			//itor = imagemap.erase(itor);
			
			texture = 0;
			
			
			++textitor1;
		}
		
		textTextureList.clear();

		//clear img rectangles
		list<SDL_Rect*>::iterator textrectitor1 = textsourcerectList.begin();
		while(textrectitor1 != textsourcerectList.end())
		{
			SDL_Rect* rect = *textrectitor1;
			delete rect;
			rect = 0;
			
			
			++textrectitor1;
		}
		textsourcerectList.clear();
		**/
		//imgTextureList.clear();
		//imgsourcerectList.clear();
		//SDL_UpdateWindowSurface(gameWindow_);
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				deinit();
				return false;
			}
			if(e.key.keysym.scancode != SDL_SCANCODE_RETURN)
			  {
			    
			  
			    if (e.type == SDL_TEXTINPUT)
			      {
				userTyping = true;
				inputString += e.text.text;
			      }

			  }
			else{
			  userTyping = false;
			  return true;
			}
		}

		const Uint8* keyboard = SDL_GetKeyboardState(0);

		if (keyboard[SDL_SCANCODE_ESCAPE])
		{
			deinit();
			return false;
		}

		
		
		return true;
	}

	bool update(std::string filename, int x1, int y1, int x2, int y2)
	{
		if (!gameWindow_ )
			return false;

		//SDL_Rect rect = {0, 0, Engine::CanvasWidth, Engine::CanvasHeight};
		//SDL_Surface* canvasSurface = SDL_CreateRGBSurfaceFrom(canvas, rect.w, rect.h, 32, rect.w * 4, 0xff0000, 0xff00,  0xff, 0);
		unordered_map<std::string, SDL_Texture*>::iterator itor = imagemap.find(filename);
		SDL_Texture* imgTexture;
		//SDL_Renderer* renderer = SDL_GetRenderer(gameWindow_);
		if(!renderer)
		{
			//rendrer = SDL_CreateRenderer(gameWindow_, -1, SDL_RENDERER_ACCELERATED);
			printf("RENDERER IS NULL %s\n", SDL_GetError());
			return false;
		}
		
		if(itor == imagemap.end())
			{
				imgTexture = IMG_LoadTexture(renderer, filename.c_str());
				printf("LOADING IMAGE CALLED %s\n", filename.c_str());
				imagemap[filename] = imgTexture;
			}
		else {
			printf("IMAGE IN CACHE\n");
			imgTexture = itor->second;
		}
		if (!imgTexture)
		{
			printf("texture is null for %s\n", filename.c_str());
			SDL_DestroyTexture(imgTexture);
			return false;
		}
		
		int w,h;
		SDL_Rect drect = {x1, y1, x2, y2};
		SDL_QueryTexture(imgTexture, NULL, NULL, &w, &h); // get the width and height of the texture
		// put the location where we want the texture to be drawn into a rectangle
		// I'm also scaling the texture 2x simply by setting the width and height
		printf("for  %s, w is %d , h is %d\n", filename.c_str(), w, h);
		SDL_Rect texr; texr.x = 0; texr.y = 0; texr.w = w; texr.h = h; 
		
	
		

		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				deinit();
				return false;
			}
			if(e.key.keysym.scancode != SDL_SCANCODE_RETURN)
			  {
			    
			  
			    if (e.type == SDL_TEXTINPUT)
			      {
				userTyping = true;
				inputString += e.text.text;
			      }

			  }
			else{
			  userTyping = false;
			  return true;
			}
		}

		const Uint8* keyboard = SDL_GetKeyboardState(0);

		if (keyboard[SDL_SCANCODE_ESCAPE])
		{
			deinit();
			return false;
		}

		
		// clear the screen
		SDL_RenderClear(renderer);
		// copy the texture to the rendering context
		SDL_RenderCopy(renderer, imgTexture, NULL, &texr);
		// flip the backbuffer
		// this means that everything that we prepared behind the screens is actually shown
		SDL_RenderPresent(renderer);
		//SDL_UpdateWindowSurface(gameWindow_);
		return true;
	}


	bool update(std::string filename)
	{
		if (!gameWindow_ )
			return false;

		//SDL_Rect rect = {0, 0, Engine::CanvasWidth, Engine::CanvasHeight};
		//SDL_Surface* canvasSurface = SDL_CreateRGBSurfaceFrom(canvas, rect.w, rect.h, 32, rect.w * 4, 0xff0000, 0xff00,  0xff, 0);
		
		SDL_Surface* imgSurface = loadImage(filename);
		printf("LOAD IMAGE CALLED");
		if (!imgSurface)
		{
			SDL_FreeSurface(imgSurface);
			return false;
		}

		SDL_Surface* screenSurface = SDL_GetWindowSurface(gameWindow_);
		SDL_BlitSurface(imgSurface, 0, screenSurface, 0);
		SDL_UpdateWindowSurface(gameWindow_);

		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				deinit();
				return false;
			}
			if(e.key.keysym.scancode != SDL_SCANCODE_RETURN)
			  {
			    
			  
			    if (e.type == SDL_TEXTINPUT)
			      {
				userTyping = true;
				inputString += e.text.text;
			      }

			  }
			else{
			  userTyping = false;
			  return true;
			}
		}

		const Uint8* keyboard = SDL_GetKeyboardState(0);

		if (keyboard[SDL_SCANCODE_ESCAPE])
		{
			deinit();
			return false;
		}

		
		
		return true;
	}
  

        
}

int main()
{
	extern void EngineMain();
	EngineMain();
	return 0;
}



