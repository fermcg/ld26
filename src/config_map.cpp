#include "config_map.h"

ConfigMap::ConfigMap() {
	
}

ConfigMap::~ConfigMap() {
	
	ConfigMap::iterator it;
	for(it = this->begin(); it != this->end(); it++) {
		
		if (it->second != NULL) {
			
			delete it->second;
			it->second = NULL;
		}
	}
}
