#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "config.h"
#include "exceptions.h"
#include "macros.h"
#include "ResourcePath.hpp"


using namespace std;

Config::Config(const string& fileName) : BaseSystem("Config") {

	this->configMap = NULL;
	this->fileName = fileName;

	this->name += " ['";
	this->name += this->fileName;
	this->name += "']";	
}
Config::~Config() {

	DELETENULL(configMap);
}
void Config::Init() throw() {

	Load();
	this->BaseSystem::Init();	
}
void Config::Terminate() {

	DELETENULL(configMap);
	this->BaseSystem::Terminate();
}
void Config::Load() throw() {

	ifstream fin;
	fin.open(resourcePath() + fileName);

	if (!fin.good()) {

		cerr << "Error opening config file." << endl;
		THROW(Exception::BadConfig);
	}

	// fill a local map - if it works - replace the old one.
	ConfigMap::Ptr configMap = new ConfigMap();
	ConfigSection::Ptr configSection = NULL;

	for(int line_number = 0;fin.good(); line_number++) {

		string line;

		getline(fin, line);

		boost::algorithm::trim(line);

		if (line.empty() || line[0] == '#') {

			continue;
		}

		if (line[0] ==  '[') {

			string section;
			if (line[line.size() - 1] != ']') {

				cerr << "Unexpected line at config file: [" << line_number << "]: [" << line << "]" << endl;
				DELETENULL(configMap);
				THROW(Exception::BadConfig);				
			}

			section = line.substr(1, line.size() - 2);
			boost::algorithm::trim(section);
			boost::algorithm::to_upper(section);

			if (section.empty()) {

				cerr << "Bad section line at config file: [" << line_number << "]: [" << line << "]" << endl;
				DELETENULL(configMap);
				THROW(Exception::BadConfig);				
			}

			if (configMap->find(section) != configMap->end()) {

				cerr << "Section duplicated [" << section << "] at config file: [" << line_number << "]: [" << line << "]" << endl;
				DELETENULL(configMap);
				THROW(Exception::BadConfig);
			}

			configSection = new ConfigSection(section.c_str());
			(*configMap)[section] = configSection;

			continue;
		}
		size_t pos = line.find('=');

		if (pos == string::npos) {

			cerr << "Unexpected line at config file: [" << line_number << "]: [" << line << "]" << endl;
			DELETENULL(configMap);
			THROW(Exception::BadConfig);			
		}

		string key = line.substr(0, pos);
		string value = line.substr(pos);

		boost::algorithm::trim(key);

		if (key.empty()) {

			cerr << "Empty key at config file: [" << line_number << "]: [" << line << "]" << endl;
			DELETENULL(configMap);
			THROW(Exception::BadConfig);
		}

		// A section must exist
		if (configSection == NULL) {

			cerr << "No config section at line: [" << line_number << "]: [" << line << "]" << endl;
			DELETENULL(configMap);
			THROW(Exception::BadConfig);			
		}

		boost::algorithm::to_lower(key);
		if (configSection->find(key) != configSection->end()) {

			cerr << "Duplicate key at line: [" << line_number << "]: [" << line << "]" << endl;
			DELETENULL(configMap);
			THROW(Exception::BadConfig);
		}

		boost::algorithm::trim(value);		
		(*configSection)[key] = value;
	}
	DELETENULL(this->configMap);
	this->configMap = configMap;
}

template <typename T>
bool ReadOrThrowFunction(const bool throwOnFail, const ConfigMap::Ptr& configMap, const char* section, const char* key, T& value) throw() {

	string strSection = section;
	string strKey = key;

	boost::algorithm::trim(strSection);
	boost::algorithm::trim(strKey);
	boost::algorithm::to_upper(strSection);
	boost::algorithm::to_lower(strKey);

	ConfigMap::const_iterator it = configMap->find(strSection);
	if (it == configMap->end()) {

		if (throwOnFail) {

			THROWINFO(Exception::ConfigSectionNotFound, strSection.c_str());
		}
		return false;
	}

	ConfigSection::const_iterator jt = it->second->find(strKey);
	if (jt == it->second->end()){

		if (throwOnFail) {

			THROWINFO(Exception::ConfigKeyNotFound, strKey.c_str());
		}
		return false;
	}

	try {

		value = boost::lexical_cast<T>(jt->second);
	} catch(boost::bad_lexical_cast&) {

		if(throwOnFail) {

			THROWINFO(Exception::BadConfigValue, jt->second.c_str());
		}
		return false;
	}
	return true;
}

void Config::ReadOrThrow(const char* section, const char* key, int& value) const throw() {

	ReadOrThrowFunction<int>(true, configMap, section, key, value);
}

void Config::Read(const char* section, const char* key, int& value, const int defaultValue) const {

	if (!ReadOrThrowFunction<int>(false, configMap, section, key, value)) {

		value = defaultValue;
	}
}

void Config::ReadOrThrow(const char* section, const char* key, string& value) const throw() {

	ReadOrThrowFunction<string>(true, configMap, section, key, value);	
}
void Config::Read(const char* section, const char* key, string& value, const string& defaultValue) const {

	if (!ReadOrThrowFunction<string>(false, configMap, section, key, value)) {

		value = defaultValue;
	}
}

const ConfigMap& Config::Map() const throw() {

	if (configMap == NULL) {
		THROWINFO(Exception::BadObject, "Config");
	}
	return *configMap;
}
