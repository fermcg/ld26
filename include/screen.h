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
		void TempZoomOut();
		void HandleZoom();

		sf::RenderWindow* window;	
		sf::View *view;

	private:

		double zoomOutSpeed;
		double zoomInSpeed;
		double zoomFactor;
		double maxZoomFactor;
		bool fullScreen;
		sf::Image icon;
		sf::VideoMode videoMode;
		string gameTitle;
};
