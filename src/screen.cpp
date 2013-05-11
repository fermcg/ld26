#include <iostream>

#include "screen.h"
#include "singletons.h"
#include "exceptions.h"
#include "macros.h"
#include "ResourcePath.hpp"

using namespace std;

Screen::Screen() : BaseSystem("Screen") {

	view = NULL;
	window = NULL;
	fullScreen = false;
	gameTitle = "Pato Loco";
	zoomOutSpeed = 0.0;
	zoomInSpeed = 0.01;
	zoomFactor = 1.0;
	maxZoomFactor = 1.5;
}
Screen::~Screen() {

}
void Screen::Init() throw() {

	const char* windowSection = "WINDOW";

	int width = 0;
	int height = 0;

	Singleton::config->Read(windowSection, "width", width, 704);
	Singleton::config->Read(windowSection, "height", height, 480);

	videoMode.width = width;
	videoMode.height = height;
	
	// Create the view
	view = new sf::View(sf::FloatRect(0.0,0.0, (float)width, (float)height));
	view->setViewport(sf::FloatRect(0.0,0.0,1.0,1.0));
	// Create the main window
	window = new sf::RenderWindow(videoMode, gameTitle);

	// Set the Icon
	if (!icon.loadFromFile(resourcePath() + "icon.png")) {
		THROW(Exception::InitializationFailure);
	}
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	window->setFramerateLimit(90);

	this->BaseSystem::Init();	
}
void Screen::Terminate() {

	if (view != NULL) {
		
		delete view;
		view = NULL;
	}
	if (window != NULL) {

		delete window;
		window = NULL;
	}

	this->BaseSystem::Terminate();
}
void Screen::ToogleFullScreen() {

	fullScreen = !fullScreen;

	if (fullScreen) {
		
		window->create(videoMode, gameTitle, sf::Style::Fullscreen);
		window->setMouseCursorVisible(false);
	} else {
		
		window->create(videoMode, gameTitle, sf::Style::Close);
	}
	
	window->setView(*view);
}

void Screen::TempZoomOut() {

	zoomOutSpeed = 0.01;
}

void Screen::HandleZoom() {

	if (zoomOutSpeed == 0.0) {

		return;
	}
	if (zoomFactor < 1.0) {

		zoomFactor = 1.0;
		zoomOutSpeed = 0.0;
	} else {

		if (Singleton::player->ySpeed < 0.0) {

			zoomFactor += zoomOutSpeed;
		} else {

			zoomFactor -= zoomInSpeed;
		}
	}
	if (zoomFactor >= maxZoomFactor) {

		zoomFactor = maxZoomFactor;
	}
	view->zoom(zoomFactor);
}