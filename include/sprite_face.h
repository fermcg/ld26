#pragma once

#include <map>
#include <SFML/Graphics.hpp>

#include "base_system.h"
#include "sprite_sequence.h"

using namespace std;

class SpriteFace : public BaseSystem {
public:
	enum Facing {
		front = 0,
		left,
		right,
		up,
		down,
		top_left,
		top_right,
		bottom_left,
		bottom_right,
		full_left,
		full_right,
		full_up,
		full_down,
		full_front,
		horizontal,
		vertical,
		alt_front,
		alt_left,
		alt_right,
		dying,
		opened,
		closed,
		top,
		junction,
		trunk,
		root
	};
	SpriteFace(const char* objectId, bool* blinker = NULL);
	~SpriteFace();
	
	void Init();
	void Terminate();
	
	void RenderCopy(const sf::IntRect* destinyRect) throw();
	void RenderToImage(sf::Image& destinyImage, const int x,
					   const int y) throw();
		
	SpriteSequence* GetSequence() throw();
		
	void RegisterFace(const Facing facing, const char* spriteId) throw();
	//SpriteSequence* spriteSequence);
	void ChangeFace(const Facing facing);

	void SetBlinker(bool* blinker);

	
	typedef map<Facing, SpriteSequence*> MapOfFaces;
		
protected:
	MapOfFaces faces;
	Facing facing;
	bool* blinker;
};
