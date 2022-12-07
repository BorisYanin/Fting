#include "Hurtbox.h"

Hurtbox::Hurtbox(Character character, int playerID, int currXpos, int currYpos, SDL_RendererFlip flip)
{
	switch (character) {
	case Character::knight:
		switch (flip) {
		case SDL_FLIP_NONE:
			_xPos = currXpos ; break;
		case SDL_FLIP_HORIZONTAL:
			_xPos = currXpos; break;
		default: break;
		}
		_yPos = currYpos;
		_width = 0;
		_length = 0;
		break;
	case Character::samurai:
		switch (flip) {
		case SDL_FLIP_NONE:
			_xPos = currXpos ; break;
		case SDL_FLIP_HORIZONTAL:
			_xPos = currXpos ; break;
		default: break;
		}
		_yPos = currYpos;
		_width = 0;
		_length = 0;
		break;
	case Character::huntress:
		switch (flip) {
		case SDL_FLIP_NONE:
			_xPos = currXpos; break;
		case SDL_FLIP_HORIZONTAL:
			_xPos = currXpos; break;
		default: break;
		}
		_yPos = currYpos;
		_width = 0;
		_length =0;
	default: break;
	}

	//_hurtbox = SDL_Rect { _xPos, _yPos, _width, _length };
}

Hurtbox::~Hurtbox()
{}

void Hurtbox::Hudelete(Character character, int playerID, int currXpos, int currYpos, SDL_RendererFlip flip)
{
	switch (character) {
	case Character::knight:
		switch (flip) {
		case SDL_FLIP_NONE:
			_xPos = currXpos; break;
		case SDL_FLIP_HORIZONTAL:
			_xPos = currXpos; break;
		default: break;
		}
		_yPos = currYpos;
		_width = 0;
		_length = 0;
		break;
	case Character::samurai:
		switch (flip) {
		case SDL_FLIP_NONE:
			_xPos = currXpos; break;
		case SDL_FLIP_HORIZONTAL:
			_xPos = currXpos; break;
		default: break;
		}
		_yPos = currYpos;
		_width = 0;
		_length = 0;
		break;
	case Character::huntress:
		switch (flip) {
		case SDL_FLIP_NONE:
			_xPos = currXpos ; break;
		case SDL_FLIP_HORIZONTAL:
			_xPos = currXpos; break;
		default: break;
		}
		_yPos = currYpos;
		_width = 0;
		_length = 0;
	default: break;
	}

}

void Hurtbox::draw(Character character, int playerXpos)
{
	if (character == Character::knight)
		_xPos = playerXpos + 55;
	else if (character == Character::samurai)
		_xPos = playerXpos + 255;
	else if (character == Character::huntress)
		_xPos = playerXpos + 255;

	_hurtbox = SDL_Rect{ _xPos, _yPos, _width, _length };

	SDL_RenderDrawRect(Window::renderer, &_hurtbox);
	SDL_RenderFillRect(Window::renderer, &_hurtbox);
}

bool Hurtbox::collide(Hitbox hitbox)
{
	if (
		( _xPos >= hitbox.getXpos() && _xPos <= hitbox.getXpos() + hitbox.getWidth() )
		||
		( _xPos + _width >= hitbox.getXpos() && _xPos + _width <= hitbox.getXpos() + hitbox.getWidth() )
	   )
	{
		return true;
	}
	return false;
}