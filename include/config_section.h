#pragma once

#include <map>
#include <string>

using namespace std;

class ConfigSection : public map<string, string> {
public:
	typedef ConfigSection* Ptr;
	
	ConfigSection(const char* sectionName);
	~ConfigSection();
	
	bool GetIfExists(const char* key, string& value) const;
	
	const string name;
};
