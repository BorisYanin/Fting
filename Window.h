#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Window
{
public:
	Window(const char * title, int width, int height);
	~Window();

	enum class CurrWindow {
		mainMenu, game, help , select
	};

	void clear() const;
	void pollEvents(SDL_Event &event);
	void draw() const;

	inline bool isRunning() { return _running; }
	inline int getWidth() { return _width; }
	inline int getHeight() { return _height; }

	inline CurrWindow getCurWindow() { return _currWindow; }

	void setCurWindow(CurrWindow currWindow) {
		_currWindow = currWindow;
	}

	void setWindowTexture(const char * texture) {
		auto surface = IMG_Load(texture);
		_wTexture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}
	void Ttext(const char* hpbar);

	void terminate() {
		_running = false;
	}

	static SDL_Renderer * renderer;

private:
	bool init();


	

	const char * _title;
	int _width = 1920;
	int _height = 1080;

	bool _running;

	CurrWindow _currWindow = CurrWindow::mainMenu;
	SDL_Window * _window = nullptr;
	SDL_Texture * _wTexture = nullptr;
};