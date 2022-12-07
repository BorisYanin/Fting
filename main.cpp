#include <iostream>
#include <SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>
#include <windows.h>
//#include<SFML/Graphics.hpp>

#include "Window.h"
#include "Hero.h"
#include "Knight.h"
#include "Samurai.h"
#include "Button.h"
#include "ArrowButton.h"
#include "Player.h"
#include "Hitbox.h"
#include "Hurtbox.h"
#include "Charbackground.h"
//#include "LifeBar.h"

//using namespace sf;
using namespace std;


SDL_Event event;

Window window("DEMO", 1920, 1080);

/*void Ttext(const char* hpbar) {
	//this opens a font style and sets a size
	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 2000);
	//cout << "text created" << endl;
	// this is the color in rgb format,
	// maxing out all would give you the color white,
	// and it will be your text's color
	SDL_Color White = { 255, 255, 255 };

	// as TTF_RenderText_Solid could only be used on
	// SDL_Surface then you have to create the surface first
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, hpbar, White);

	// now you can convert it into a texture
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Window::renderer, surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 110;  //controls the rect's x coordinate 
	Message_rect.y = 110; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect

	// (0,0) is on the top left of the window/screen,
	// think a rect as the text's box,
	// that way it would be very simple to understand

	// Now since it's a texture, you have to put RenderCopy
	// in your game loop area, the area where the whole code executes

	// you put the renderer's name first, the Message,
	// the crop size (you can ignore this if you don't want
	// to dabble with cropping), and the rect which is the size
	// and coordinate of your texture
	SDL_RenderCopy(Window ::renderer, Message, NULL, &Message_rect);

	// Don't forget to free your surface and texture
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
	TTF_Quit();
	
}*/

int mainMenu(int argc, char** argv); //forward declaration
int helpScreen(int argc, char** argv); //forward declaration
int characterSelection(int argc, char** argv);


int gameLoop(int argc, char** argv, Character playerOneSel, Character playerTwoSel)
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	//cout << frameDelay << endl;
	int dm = 0;

	Uint32 frameStart;
	int frameTime;
	
	window.setWindowTexture("Assets/backgroundGameScene1.png");

	PlaySound(TEXT("Assets/devatka.wav"), NULL, SND_ASYNC);

	int sInitial = 0; //120;

	int kx = 60; //90-21; //initial x for knight sprite
	int sx = sInitial; //initial x for samurai sprite
	int hx = 0; //initial x for huntress sprite
	int kAnimDel = 0; //animation delay: knight
	int sAnimDel = 0; //animation delay: samurai

	const char* knightTexture = "Assets/knight.png";
	const char* samuraiTexture = "Assets/samurai.png";
	const char* huntressTexture = "Assets/huntress.png";

	const char* playerOneTexture = "";
	int pOneXPos = 0;
	int pOneYPos = 0;
	int pOneInX = 0;
	int pOneAnimDel = 0;

	const char* playerTwoTexture = "";
	int pTwoXpos = 0;
	int pTwoYPos = 0;
	int pTwoInX = 0;
	int pTwoAnimDel = 0;

	switch (playerOneSel) {
	case Character::knight:
		playerOneTexture = knightTexture;
		pOneXPos = 200;
		pOneYPos = window.getHeight() - 350;
		pOneInX = kx;
		pOneAnimDel = kAnimDel;
		break;
	case Character::samurai:
		playerOneTexture = samuraiTexture;
		pOneXPos = 50;
		pOneYPos = window.getHeight() - 550;
		pOneInX = sx;
		pOneAnimDel = sAnimDel;
		break;
	case Character::huntress:
		playerOneTexture = huntressTexture;
		pOneXPos = 50;
		pOneYPos = window.getHeight() - 550;
		pOneInX = hx;
		pOneAnimDel = sAnimDel;
		break;
	default: break;
	}

	switch (playerTwoSel) {
	case Character::knight:
		playerTwoTexture = knightTexture;
		pTwoXpos = window.getWidth() - 400;
		pTwoYPos = window.getHeight() - 350;
		pTwoInX = kx;
		pTwoAnimDel = kAnimDel;
		break;
	case Character::samurai:
		playerTwoTexture = samuraiTexture;
		pTwoXpos = window.getWidth() - 600;
		pTwoYPos = window.getHeight() - 550;
		pTwoInX = sx;
		pTwoAnimDel = sAnimDel;
		break;
	case Character::huntress:
		playerTwoTexture = huntressTexture;
		pTwoXpos = window.getWidth() - 600;
		pTwoYPos = window.getHeight() - 550;
		pTwoInX = hx;
		pTwoAnimDel = sAnimDel;
		break;
	default: break;
	}
	int hitmark = 0;
	Player playerOne(pOneXPos, pOneYPos, playerOneTexture, SDL_FLIP_NONE, playerOneSel, 0);
	Player playerTwo(pTwoXpos, pTwoYPos, playerTwoTexture, SDL_FLIP_HORIZONTAL, playerTwoSel, 1);

	const char* health1 = (const char *)playerOne.getHealth();
	const char* health2 = (const char*)playerTwo.getHealth();

	Hurtbox hurtBoxPlayerOne(playerOneSel, 0, playerOne.getXpos(), playerOne.getYpos(), playerOne.getFlip());
	Hurtbox hurtBoxPlayerTwo(playerTwoSel, 1, playerTwo.getXpos(), playerTwo.getYpos(), playerTwo.getFlip());

	std::cout << hurtBoxPlayerOne.getXpos() << std::endl;
	std::cout << hurtBoxPlayerTwo.getXpos() << std::endl;

	Event pOneSaveEvent = playerOne.getEventID(); //Save player 1's last event
	Event pTwoSaveEvent = playerTwo.getEventID(); //Save player 2's last event



	//Hitbox hitbox(playerOneSel, 0);

	//int health1 = playerOne.getHealth();

	//int health2 = playerTwo.getHealth();


	while (window.isRunning()) {
		frameStart = SDL_GetTicks();

		window.draw();
		window.Ttext(health1);
		window.Ttext(health2);
		if ((playerOne.getEventID() == Event::attack)) {
			//cout << hitmark<< endl;
			Hitbox hitbox1(playerOneSel, 0, playerOne.getXpos(), playerOne.getYpos(), playerOne.getFlip());
			hitbox1.draw();
			if (hurtBoxPlayerTwo.collide(hitbox1) && (hitmark % 30 == 0))
			{

				playerTwo.takeHit(playerTwoSel, playerOne.getDamage(), playerTwo, hitmark, dm);
				hurtBoxPlayerTwo.Hudelete(playerTwoSel, 1, playerTwo.getXpos(), playerTwo.getYpos(), playerTwo.getFlip());
				//hitmark += 1;

			}

		}

		if ((playerTwo.getEventID() == Event::attack)) {
			Hitbox hitbox2(playerTwoSel, 1, playerTwo.getXpos(), playerTwo.getYpos(), playerTwo.getFlip());
			hitbox2.draw();
			if (hurtBoxPlayerOne.collide(hitbox2) && (hitmark % 30 == 0)) {

				//hitbox2.Hdelete(playerTwo.getXpos(), playerTwo.getYpos());
				playerOne.takeHit(playerOneSel, playerTwo.getDamage(), playerOne, hitmark, dm);
				//hitbox2.Hdelete(playerTwo.getXpos(), playerTwo.getYpos());
				hurtBoxPlayerOne.Hudelete(playerOneSel, 0, playerOne.getXpos(), playerOne.getYpos(), playerOne.getFlip());
				//hitmark += 1;
				//cout << "228";

			}
			//if (hitmark >0)
			//playerOne.takeHit(playerOneSel, playerTwo.getDamage(), playerOne, hitmark);
		}

		hurtBoxPlayerOne.draw(playerOneSel, playerOne.getXpos());
		hurtBoxPlayerTwo.draw(playerTwoSel, playerTwo.getXpos());

		playerOne.move(window);
		playerOne.draw(pOneInX, pOneSaveEvent, pOneAnimDel);

		playerTwo.move(window);
		playerTwo.draw(pTwoInX, pTwoSaveEvent, pTwoAnimDel);

		//playerOne.takeHit(playerOneSel, playerTwo.getDamage(), playerOne);
		//playerTwo.takeHit(playerTwoSel, playerOne.getDamage(), playerTwo);

		//if (playerOne.getEventID() == 3) {
		//	Hitbox hitbox(playerOneSel, 0, playerOne.getXpos(), playerOne.getYpos(), playerOne.getFlip());
		//	hitbox.draw();
		//	//hitbox.~Hitbox();
		//}
		//if (playerTwo.getEventID() == 3) {
		//	Hitbox hitbox(playerTwoSel, 1, playerTwo.getXpos(), playerTwo.getYpos(), playerTwo.getFlip());
		//	hitbox.draw();
		//}

		if (SDL_PollEvent(&event)) {
			if (!playerOne.attack() && playerOne.getEventID() != Event::death) {
				playerOne.pollEventsP1(event);
			}

			if (!playerTwo.attack() && playerTwo.getEventID() != Event::death) {
				playerTwo.pollEventsP2(event);
			}
			window.pollEvents(event);
		}
		window.clear();
		kAnimDel++;
		sAnimDel++;

		frameTime = SDL_GetTicks() - frameStart;

		if (window.getCurWindow() == Window::CurrWindow::select)
			return characterSelection(argc, argv);

		if (window.getCurWindow() == Window::CurrWindow::mainMenu)
			return mainMenu(argc, argv);
		/*if (dm>0) {
			int buttonCentrePos = window.getWidth() / 2 - 128;

			Button buttonBack(buttonCentrePos, 600, "Assets/ButtonBack.png");
			while (window.isRunning()) {
				window.draw();
				buttonBack.draw();
				window.clear();

				if (SDL_PollEvent(&event)) {
					window.pollEvents(event);
					if (buttonBack.pollEvents(event))
						window.setCurWindow(Window::CurrWindow::mainMenu);
				}

				if (window.getCurWindow() == Window::CurrWindow::mainMenu)
					break;
			}

			buttonBack.~Button();

			return mainMenu(argc, argv);
		}*/
		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
		//cout << frameDelay << endl;
		hitmark += 1;
	}
	
	window.~Window();
	playerOne.~Player();
	playerTwo.~Player();
	return 0;
}

int characterSelection(int argc, char** argv)
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	int buttonCentrePos = window.getWidth() / 2 - 128;

	window.setWindowTexture("Assets/backgroundCharSel.png");

	Button char1(buttonCentrePos, 200, "Assets/ButtonStart.png");
	Button char2(buttonCentrePos, 400, "Assets/ButtonHelp.png");
	Button buttonSelect(buttonCentrePos, 600, "Assets/ButtonSelect.png");
	Button buttonBack(buttonCentrePos, 800, "Assets/ButtonBack.png");

	ArrowButton arrBtnR(window.getWidth() - 400 - 59 * 6, 350, "Assets/swordArrow.png", false);
	ArrowButton arrBtnL(400, 350, "Assets/swordArrow.png", true);

	//Knight knight(window.getWidth() / 2, window.getHeight() / 2, "Assets/knight.png");
	//Samurai samurai(window.getWidth() / 2, window.getHeight() / 2, "Assets/samurai.png");

	CharBG charBG(window.getWidth() / 2 - 32 * 6, 120);

	Player knight(window.getWidth() / 2 - 180 - 20, window.getHeight() / 2 - 400,
		"Assets/knight.png", SDL_FLIP_NONE, Character::knight, 0);
	Player samurai(window.getWidth() / 2 - 600, window.getHeight() / 2 - 787,
		"Assets/samurai.png", SDL_FLIP_NONE, Character::samurai, 0);
	Player huntress(window.getWidth() / 2 - 600, window.getHeight() / 2 - 791,
		"Assets/huntress.png", SDL_FLIP_NONE, Character::huntress, 0);

	knight.setSize(2);
	samurai.setSize(2);
	huntress.setSize(2);

	int playerSelecting = 0;
	Character playerOne = Character::knight;
	Character playerTwo = Character::knight;

	int scroll = 0;
	Character characters[] = { Character::knight, Character::samurai, Character::huntress };
	int numberOfElems = sizeof(characters) / sizeof(characters[0]) - 1;

	//---------// - PLACEHOLDER
	int kInitial = 60; //initial x position of every frame: knight
	int kAnimDel = 5; //animation delay: knight
	int sInitial = 0; //initial x position of every frame: samurai
	int sAnimDel = 8; //animation delay: samurai
	int hInitial = 0;
	int hAnimDel = 6;
	//---------// - PLACEHOLDER
	Event idle = Event::idle;

	while (window.isRunning()) {
		frameStart = SDL_GetTicks();

		window.draw();

		//char1.draw();
		//char2.draw();

		charBG.draw();

		buttonSelect.draw();
		buttonBack.draw();

		Character currChar = characters[scroll];

		if (currChar == Character::knight)
			knight.drawKnight(kInitial, idle, kAnimDel);
		else if (currChar == Character::samurai)
			samurai.drawSamurai(sInitial, idle, sAnimDel);
		else if (currChar == Character::huntress)
			huntress.drawHuntress(hInitial, idle, hAnimDel);

		//knight.drawKnight(kInitial, idle, kAnimDel);
		//samurai.drawSamurai(sInitial, idle, sAnimDel);
		//huntress.drawHuntress(hInitial, idle, hAnimDel);

		arrBtnL.draw();
		arrBtnR.draw();

		if (SDL_PollEvent(&event)) {
			if (buttonBack.pollEvents(event)) {
				window.setCurWindow(Window::CurrWindow::mainMenu);
				return mainMenu(argc, argv);
			}
			if (arrBtnL.pollEvents(event)) {
				if (scroll <= 0)
					scroll = numberOfElems;
				else
					scroll--;
			}
			if (arrBtnR.pollEvents(event)) {
				if (scroll >= numberOfElems)
					scroll = 0;
				else
					scroll++;
			}
			if (buttonSelect.pollEvents(event)) {
				if (playerSelecting == 0) {
					playerOne = currChar;
					playerSelecting++;
				}
				else {
					playerTwo = currChar;
					playerSelecting++;
				}
			}
		}
		window.clear();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
		if (playerSelecting >= 2)
			break;

	}
	char1.~Button();
	char2.~Button();

	return gameLoop(argc, argv, playerOne, playerTwo);
}

int mainMenu(int argc, char** argv)
{
	PlaySound(TEXT("Assets/dora.wav"), NULL, SND_ASYNC);
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	int buttonCentrePos = window.getWidth() / 2 - 128;

	Button buttonStart(buttonCentrePos, 200, "Assets/ButtonStart.png");
	Button buttonHelp(buttonCentrePos, 400, "Assets/ButtonHelp.png");
	Button buttonQuit(buttonCentrePos, 600, "Assets/ButtonQuit.png");

	window.setWindowTexture("Assets/backgroundMenu.png");
	//PlaySound(TEXT("Assets/devatka.wav"), NULL, SND_SYNC);
	while (window.isRunning()) {
		frameStart = SDL_GetTicks();

		window.draw();
		buttonStart.draw();
		buttonHelp.draw();
		buttonQuit.draw();

		window.clear();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);

		if (SDL_PollEvent(&event)) {
			if (buttonStart.pollEvents(event))
				window.setCurWindow(Window::CurrWindow::game);
			else if (buttonHelp.pollEvents(event))
				window.setCurWindow(Window::CurrWindow::help);
			else if (buttonQuit.pollEvents(event))
				window.terminate();
		}

		if (window.getCurWindow() != Window::CurrWindow::mainMenu)
			break;
	}

	buttonStart.~Button();
	buttonHelp.~Button();
	buttonQuit.~Button();


	if (window.getCurWindow() == Window::CurrWindow::game)
		return characterSelection(argc, argv);
	else if (window.getCurWindow() == Window::CurrWindow::help)
		return helpScreen(argc, argv);
	return 0;
}

int helpScreen(int argc, char** argv)
{
	int buttonCentrePos = window.getWidth() / 2 - 128;

	Button buttonBack(buttonCentrePos, 600, "Assets/ButtonBack.png");

	while (window.isRunning()) {
		window.draw();
		buttonBack.draw();
		window.clear();

		if (SDL_PollEvent(&event)) {
			window.pollEvents(event);
			if (buttonBack.pollEvents(event))
				window.setCurWindow(Window::CurrWindow::mainMenu);
		}

		if (window.getCurWindow() == Window::CurrWindow::mainMenu)
			break;
	}

	buttonBack.~Button();

	return mainMenu(argc, argv);
}

int main(int argc, char** argv)
{
	mainMenu(argc, argv);
	return 0;
}