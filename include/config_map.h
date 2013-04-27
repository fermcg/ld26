#pragma once

#include <map>
#include "config_section.h"

using namespace std;

class ConfigMap : public map<string, ConfigSection::Ptr> {
public:
	typedef ConfigMap* Ptr;
	
	ConfigMap();
	~ConfigMap();
};
