#pragma once

#include <SFML/Graphics.hpp>
#include "base_system.h"

class Screen : public BaseSystem {
	public:
		Screen();
		~Screen();

		void Init() throw();
		void Terminate();

		void ToogleFullScreen();

		sf::RenderWindow* window;	
		sf::View *view;

	private:

		bool fullScreen;
		sf::Image icon;
		sf::VideoMode videoMode;
		string gameTitle;
};
