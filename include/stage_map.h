#pragma once

#include <SDL.h>
#include <map>
#include <fstream>
#include <string>

#include "base_system.h"
#include "stage.h"

using namespace std;

class StageMap : public BaseSystem, map< string, Stage* > {

public:
	StageMap(const char* fileName);
	~StageMap();

	void Init();
	void Terminate();
	
	Stage* Get(const char* stageId);


	void ReadStageLine(const string& line);
	void ReadProperty(const string& line);
	void ReadDictionaryWord(const string& line);

private:
	void LoadStage();

	int lineNumber;
	string fileName;
	string currentStageId;
	ifstream ifs;
	Stage* stage;
};
