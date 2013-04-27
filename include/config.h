#pragma once

#include <string>

#include "base_system.h"
#include "config_map.h"

using namespace std;

class Config : public BaseSystem {
public:
	Config(const char* fileName);
	~Config();
	
	void Init() throw();
	void Terminate();
	void Load() throw();
	
	void ReadOrThrow(const char* section, const char* key, int& value) const throw();
	void Read(const char* section, const char* key, int& value, const int defaultValue) const;
	
	void ReadOrThrow(const char* section, const char* key, string& value) const throw();
	void Read(const char* section, const char* key, string& value, const string& defaultValue) const;
	
	const ConfigMap& Map() const throw();

private:
	string fileName;
	ConfigMap::Ptr configMap;
	
};
