#include <iostream>
#include "aux_functions.h"

using namespace std;

namespace Aux {

	void PrintRect(const SDL_Rect& rect) {

		cout << "[x:" << rect.x << " y:" << rect.y
			<< " w:" << rect.w << " h:" << rect.h << "]";
	}
}
