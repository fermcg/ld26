#include <iostream>
#include "aux_functions.h"

using namespace std;

namespace Aux {

	void PrintRect(const sf::IntRect& rect) {

		cout << "[x:" << rect.left << " y:" << rect.top
			<< " w:" << rect.width << " h:" << rect.height << "]";
	}
}
