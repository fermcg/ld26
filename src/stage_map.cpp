#include <vector>

#include "stage_map.h"
#include "exceptions.h"
#include "macros.h"

#include <boost/lexical_cast.hpp>

using namespace std;

StageMap::StageMap(const char* fileName) : BaseSystem("StageMap") {

	this->fileName = fileName;
	this->stage = NULL;
	this->lineNumber = 0;
}

StageMap::~StageMap() {

}

void StageMap::Init() {

	ifs.open("stages.txt");

	lineNumber = -1;
	while(ifs.good()) {

		string line;
		getline(ifs, line);

		lineNumber++;
		if(line.empty()) {

			continue;
		}

		if(stage == NULL) {

			ReadStageLine(line);
		} else {

			switch(line[0]) {
				case '@':
					ReadProperty(line);
					break;
				case '!':
					ReadDictionaryWord(line);
					break;
				case '[':
					LoadStage();
					break;
			}
		}
	}
}

void StageMap::Terminate() {

	StageMap::iterator it;
	for(it = this->begin(); it != this->end(); it++) {

		it->second->Terminate();    
		delete it->second;
	}
	this->clear();
	this->BaseSystem::Terminate();

}

Stage* StageMap::Get(const char* stageId) {

	StageMap::iterator it;
	it = this->find(stageId);
	if(it == this->end()) {

		cerr << "Error getting [" << stageId << "] stage" << endl;
		THROWINFO(Exception::StageNotFound, stageId);
	}

	return it->second;
}

void StageMap::ReadStageLine(const string& line) {

	//MENU:10,10-10x10
	size_t posBegin;
	size_t posToken;
   
	// MENU:10,10-10x10
	//[     ]
	posToken = line.find(':');

	if(posToken == string::npos) {

		cerr << "Bad line at stage file: [" << lineNumber << "]: [" << line << "]" << endl;
		THROW(Exception::BadConfig);				
	}
	currentStageId = line.substr(0, posToken - 1);

	StageMap::iterator it = this->find(currentStageId);
	if(it != this->end()) {

		cerr << "Invalid stage object -> [" << currentStageId << "] stage already loaded.";
		THROWINFO(Exception::BadObject, currentStageId.c_str());
	}
	// MENU:10,10-10x10
	//     [  ]
	posBegin = posToken + 1;
	posToken = line.find(',', posBegin);

	if(posToken == string::npos) {

		cerr << "Bad line at stage file: [" << lineNumber << "]: [" << line << "]" << endl;
		THROW(Exception::BadConfig);				
	}

	string strX = line.substr(posBegin, posToken - posBegin);

	// MENU:10,10-10x10
	//        [  ]
	posBegin = posToken + 1;
	posToken = line.find('-', posBegin);

	if(posToken == string::npos) {

		cerr << "Bad line at stage file: [" << lineNumber << "]: [" << line << "]" << endl;
		THROW(Exception::BadConfig);				
	}
	string strY = line.substr(posBegin, posToken - posBegin);

	// MENU:10,10-10x10
	//           [  ]
	posBegin = posToken + 1;
	posToken = line.find('x', posBegin);

	if(posToken == string::npos) {

		cerr << "Bad line at stage file: [" << lineNumber << "]: [" << line << "]" << endl;
		THROW(Exception::BadConfig);				
	}
	string strW = line.substr(posBegin, posToken - posBegin);
	// MENU:10,10-10x10
	//           [  ]
	string strH = line.substr(posToken + 1);

	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;

	try {

		x = boost::lexical_cast<int>(strX);
		y = boost::lexical_cast<int>(strY);
		w = boost::lexical_cast<int>(strW);
		h = boost::lexical_cast<int>(strH);
	} catch(bad_cast& e) {

		cerr << "Bad line at stage file: [" << lineNumber << "]: [" << line << "]" << endl;
		THROW(Exception::BadConfig);				
	}

	stage = new Stage(currentStageId.c_str(), x, y, w, h);
}

void StageMap::ReadProperty(const string& line) {

	size_t pos = line.find('=', 1);

	if(pos == string::npos) {

		cerr << "Bad line at stage file: [" << lineNumber << "]: [" << line << "]" << endl;
		THROW(Exception::BadConfig);
	}

	string propertyName = line.substr(1, pos - 1);
	string propertyValue = line.substr(pos + 1);

	if(propertyName == "bg") {

		stage->SetBackground(propertyValue.c_str());
	}
}

void StageMap::ReadDictionaryWord(const string& line) {

	if(line.size() < 4 || line[3] != '=') {

		cerr << "Bad line at stage file: [" << lineNumber << "]: [" << line << "]" << endl;
		THROW(Exception::BadConfig);
	}

	char dicKey = line[1];
	stage->dictionary[dicKey] = line.substr(3);
}

void StageMap::LoadStage() {
	
	vector<string> strMap;

	while(ifs.good()) {

		string line;
		getline(ifs, line);

		lineNumber++;
		if(line.empty()) {

			continue;
		}

		if(line[0] == ']') {

			break;
		}

		if(line.size() != stage->rect.w) {

			cerr << "Bad line at stage file: [" << lineNumber << "]: [" << line << "]" << endl;
			THROW(Exception::BadConfig);
		}
		strMap.push_back(line);
	}
	if(strMap.size() != stage->rect.h) {

		cerr << "Bad count of lines at stage file: [" << lineNumber << "]" << endl;
		THROW(Exception::BadConfig);
	}

	vector< vector< GameObject * > > objectMatrix;
	int preMergeCount = 0;

	size_t i, j;
	for(j = 0; j < stage->rect.h; j++) {

		string nextColor;

		for(i = 0; i < stage->rect.w; i++) {

			objectMatrix[j][i] = NULL;
			char c = strMap[j][i];

			switch(c) {
				case ' ':
				case 'p':
				case 'd':
					continue;
				case 'b':
					nextColor = "B.NUMBER>";
					continue;
				case 'r':
					nextColor = "R.NUMBER>";
					continue;
				case 'g':
					nextColor = "G.NUMBER>";
					continue;
			}

			string objectClass;

			if(c >= '1' && c <= '9' && !nextColor.empty()) {

				objectClass = nextColor;
				objectClass.push_back(c);
				nextColor = "";
			} else {
				
				Stage::Dictionary::iterator it = stage->dictionary.find(c);
				if(it == stage->dictionary.end()) {

					cout << "StageMap::LoadStage - Unknown character [" << c << "]" << endl;
					continue;
				}
				objectClass = it->second;
			}

			GameObject *gameObject = AllObjects::CreateObject(objectClass);
			
			objectMatrix[j][i] = gameObject;

			if(gameObject != NULL) {

				preMergeCount++;
			}
		}
	}

	int postMergeCount = preMergeCount;
	// try to merge blocks on x axis.

	for(j = 0; j < stage->rect.h; j++) {

		int last_merge = -1;
		for(i = 0; i < stage->rect.w; i++) {

			GameObject* gameObject = objectMatrix[j][i];
			if(gameObject == NULL) {
				
				continue;
			}

			if(last_merge == -1) {

				last_merge = i;
				continue;
			}

			if(objectMatrix[j][last_merge]->Merge(gameObject)) {

				delete gameObject;
				objectMatrix[j][i] = NULL;
				postMergeCount--;
				continue;
			}
			// No merge. This will be the next merge candidate.
			last_merge = i;
		}
	}
			
	// try to merge blocks on y axis.

	for(i = 0; i < stage->rect.w; i++) {

		int last_merge = -1;
		for(j = 0; j < stage->rect.h; j++) {

			GameObject* gameObject = objectMatrix[j][i];
			if(gameObject == NULL) {
				
				continue;
			}

			if(last_merge == -1) {

				last_merge = j;
				continue;
			}

			if(objectMatrix[last_merge][i]->Merge(gameObject)) {

				delete gameObject;
				objectMatrix[j][i] = NULL;
				postMergeCount--;
				continue;
			}
			// No merge. This will be the next merge candidate.
			last_merge = j;
		}
	}

	cout << "Merge result: [" << preMergeCount << "] > [" << postMergeCount << "]" << endl;

	for(j = 0; j < stage->rect.h; j++) {

		for(i = 0; i < stage->rect.w; i++) {

			stage->RegisterObject(objectMatrix[j][i]);
			objectMatrix[j][i] = NULL;
		}
	}

	(*this)[currentStageId] = stage;
}


