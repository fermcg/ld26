#include "config_section.h"

ConfigSection::ConfigSection(const char* sectionName) : name(sectionName) {

}

ConfigSection::~ConfigSection() {

}

bool ConfigSection::GetIfExists(const char* key, string& value) const {

	ConfigSection::const_iterator it = this->find(key);
	if(it == this->end()) {

		return false;
	}
	value = it->second;
	return true;
}
