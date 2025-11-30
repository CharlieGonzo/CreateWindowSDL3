/*
* This project follows the tutorial for a basic SDL3 app. This directions can be found at this website
* https://lazyfoo.net/tutorials/SDL3/01-hello-sdl3/index2.php
*/

/*
* Headers
*/

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include <iostream>

/*
* Constants
*/

constexpr int kScreenWidth{ 640 };
constexpr int kScreenHeight{ 480 };

// Starts SDL and creates window.
bool init();

// Loads media.
bool loadMedia();


// Frees media and shuts down SDL.
void close();

/* Global Variables */
// the windows
SDL_Window* gWindow{ nullptr };

// sruface contained by the window
SDL_Surface* gScreenSurface{ nullptr };

// the image we wll load anf show on the screen
SDL_Surface* gHelloWorld{ nullptr };

bool init()
{

	//Initialization flag
	bool success{ true };

	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO)  == false)
	{
		success =  false;
	}

	// create window and check if it was created
if(gWindow = SDL_CreateWindow("SDL3 Tutorial: Hello SDL3", // title
	kScreenWidth, // Width
	kScreenHeight, // Height
	0); // default window behavior
	gWindow == nullptr)
	{
		SDL_Log("We goofed up");
		success = false;
}
else {
	// get window surface
	gScreenSurface = SDL_GetWindowSurface(gWindow);
}

	return true;
}

bool loadMedia() {
	 //File loading flag
	bool success{ true };

	// load splash image
	std::string imagePath{ "01-hello-sdl3/hello_world.bmp" };
	if (gHelloWorld = SDL_LoadBMP(imagePath.c_str()); gHelloWorld == nullptr)
	{
		success = false;
	}

	return success;
}

void close() {

	//Clean up surface
	SDL_DestroySurface(gHelloWorld);
	gHelloWorld = nullptr;

	// Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	//Quit SDL subsystems
	SDL_Quit();
}

int main() {
	//Final exit code
	int exitCode{ 0 };

	if (init() == false) {
		SDL_Log("Unable to initalize program...");
		exitCode = 1;
	}
	else {
		if (loadMedia() == false) {
			SDL_Log("Unable to load media...");
			exitCode = 2;
		}
		else {
			bool quit{ false };

			SDL_Event e;
			SDL_zero(e);

			//The main loop
			while (quit == false) {
				//get event data
				while (SDL_PollEvent(&e) == true) { //Poll events check if any user action happened in this frame.
					//If event is quit type
					if (e.type = SDL_EVENT_QUIT) {
						quit = true; //End the loop
					}

					//Fill the surface white to clear the window every frame
					SDL_FillSurfaceRect(
						gScreenSurface, // surface we want to draw to
						nullptr, // area to fill (nullptr fills entire surface)
						SDL_MapSurfaceRGB(gScreenSurface,
							0xFF,
							0xFF,
							0xFF
						) //What you want to fil it with (white in this case)
					);

					//Render image on screen
					SDL_BlitSurface(
						gHelloWorld, // what image to blit
						nullptr, //what part of the image to blit (nullptr for entire image)
						gScreenSurface, // the sruface we want to blit to.
						nullptr // destination on the surface (nullptr for top left corner) x = 0 y = 0
					);

					//Update the surface
					SDL_UpdateWindowSurface(gWindow);


				}
			}
		}
	} 




}
