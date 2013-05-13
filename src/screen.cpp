#include <iostream>

#include "screen.h"
#include "singletons.h"
#include "exceptions.h"
#include "macros.h"
#include "ResourcePath.hpp"

using namespace std;

Screen::Screen() : BaseSystem("Screen") {

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

	Singleton::config->Read(windowSection, "width", width, 768);
	Singleton::config->Read(windowSection, "height", height, 432);

	videoMode.width = width;
	videoMode.height = height;
	
	// Configure the view
	view.setSize(width, height);
	view.setViewport(sf::FloatRect(0.0,0.0,1.0,1.0));

	// Configure the non zoomign view
	noZoomView.setSize(width, height);
	noZoomView.setCenter(width / 2.0, height / 2.0);
	noZoomView.setViewport(sf::FloatRect(0.0,0.0,1.0,1.0));

	// Create the main window
	window = new sf::RenderWindow(videoMode, gameTitle);

	// Set the Icon
	if (!icon.loadFromFile(resourcePath() + "icon.png")) {
		THROW(Exception::InitializationFailure);
	}
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(true);

	this->BaseSystem::Init();	
}
void Screen::Terminate() {

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
		window->setFramerateLimit(60);
		window->setVerticalSyncEnabled(true);
	} else {
		
		window->create(videoMode, gameTitle, sf::Style::Close);
		window->setFramerateLimit(60);
		window->setVerticalSyncEnabled(true);
	}
	
	window->setView(view);
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
	view.zoom(zoomFactor);
}