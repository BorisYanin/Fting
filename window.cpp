#include <iostream>

#include<SDL_ttf.h>

#include "Window.h"

SDL_Renderer * Window::renderer = nullptr;

Window::Window(const char * title, int width, int height)
	: _title(title), _width(width), _height(height), _running(init()) {}

Window::~Window()
{
	SDL_DestroyTexture(_wTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(_window);
	TTF_Quit();
	SDL_Quit;
}

bool Window::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialised" << std::endl;
	}
	else {
		std::cout << "Subsystems Failure: " << SDL_GetError() << std::endl;
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG) {
		std::cout << "SDL Image Initialised" << std::endl;
	}
	else {
		std::cout << "SDL Image Failure: " << SDL_GetError() << std::endl;
		return false;
	}

	_window = SDL_CreateWindow(
		_title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_width,
		_height,
		SDL_WINDOW_FULLSCREEN
	);

	if (_window == nullptr) {
		std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
		return false;
	}
	else {
		std::cout << "Window created" << std::endl;
	}
	
	renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
		return false;
	}
	else {
		std::cout << "Renderer created" << std::endl;
	}

	return true;
}

void Window::Ttext(const char* hpbar)
	{
		//std::cout << "text created" << std::endl;

		//this opens a font style and sets a size
		TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 200);

		// this is the color in rgb format,
		// maxing out all would give you the color white,
		// and it will be your text's color
		SDL_Color White = { 255, 255, 255 };

		// as TTF_RenderText_Solid could only be used on
		// SDL_Surface then you have to create the surface first
		SDL_Surface* surfaceMessage =
			TTF_RenderText_Solid(Sans,hpbar, White);

		// now you can convert it into a texture
		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

		SDL_Rect Message_rect; //create a rect
		Message_rect.x = 1000;  //controls the rect's x coordinate 
		Message_rect.y = 1000; // controls the rect's y coordinte
		Message_rect.w = 1000; // controls the width of the rect
		Message_rect.h = 1000; // controls the height of the rect

		// (0,0) is on the top left of the window/screen,
		// think a rect as the text's box,
		// that way it would be very simple to understand

		// Now since it's a texture, you have to put RenderCopy
		// in your game loop area, the area where the whole code executes

		// you put the renderer's name first, the Message,
		// the crop size (you can ignore this if you don't want
		// to dabble with cropping), and the rect which is the size
		// and coordinate of your texture
		SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

		// Don't forget to free your surface and texture
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(Message);
	}

	

void Window::clear() const
{
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 200, 255, 255);
	SDL_RenderClear(renderer);
}

void Window::pollEvents(SDL_Event &event)
{
	switch (event.type) {
	case SDL_QUIT:
		_running = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE: _running = false; break;
		case SDLK_p: _currWindow = CurrWindow::mainMenu; break;
		case SDLK_j: _currWindow = CurrWindow::select; break;
		default:
			break;
		}
	default:
		break;
	}
}

void Window::draw() const
{
	SDL_Rect srcrect { 0, 0, 1900, 1200 };
	SDL_Rect dstrect { 0, 0, _width, _height };
	SDL_RenderCopy(renderer, _wTexture, &srcrect, &dstrect);
}