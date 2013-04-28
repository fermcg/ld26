#include <SDL.h>
#include <iostream>

#include "exit_codes.h"
#include "singletons.h"
#include "exceptions.h"

using namespace std;

extern "C" int main(int argc, char* argv[]) {

	// Initializing
	try {

		Singleton::Init();
	} catch(Exception::Base& e) {

		cerr << "Exception at initialization: " << e.what() << endl;

		if (Singleton::broken) {

			cerr << "Trying to clean mess" << endl;

			try {

				Singleton::Terminate();
			} catch(Exception::Base& e) {

				cerr << "Trouble cleaning mess... reason: " << e.what() << endl;
			}
			if (Singleton::broken) {

				cerr << "Could not clean mess after all..." << endl;
			} else {

				cerr << "Terminated" << endl;
			}
		}
		exit(ExitCodes::fail_init);
	}

	try {

		Singleton::gameLoop->Loop();
	} catch(Exception::Base& e) {

		cerr << "Game loop exception. reason: " << e.what() << endl;
	}

	try {

		Singleton::Terminate();
	} catch(Exception::Base& e) {

		cerr << "Exception at termination:" << e.what() << endl;
		exit(ExitCodes::fail_init);
	}

	return 0;
}
