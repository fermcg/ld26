#include <vector>
#include <iostream>

#include "stage_map.h"
#include "exceptions.h"
#include "macros.h"
#include "brick_object.h"
#include "sprite_face.h"
#include "ResourcePath.hpp"

#include <boost/lexical_cast.hpp>

using namespace std;

StageMap::StageMap() : BaseSystem("StageMap") {

	this->stage = NULL;
	this->lineNumber = 0;
}

StageMap::~StageMap() {

}

void StageMap::Init() {

	ifs.open(resourcePath() + "stages.txt");

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

Stage* StageMap::Get(const char* stageId) throw() {

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
	currentStageId = line.substr(0, posToken);

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

	int xPos = 0;
	int yPos = 0;
	int xSize = 0;
	int ySize = 0;

	try {

		xPos = boost::lexical_cast<int>(strX);
		yPos = boost::lexical_cast<int>(strY);
		xSize = boost::lexical_cast<int>(strW);
		ySize = boost::lexical_cast<int>(strH);
	} catch(bad_cast&) {

		cerr << "Bad line at stage file: [" << lineNumber << "]: [" << line << "]" << endl;
		THROW(Exception::BadConfig);				
	}

	stage = new Stage(currentStageId.c_str(), xPos, yPos, xSize, ySize);
	stage->Init();
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
	} else if(propertyName == "hideGamePanel") {

		stage->SetHideGamePanel(propertyValue == "1");
	} else if(propertyName == "noViewPort") {
		
		stage->SetNoViewPort(propertyValue == "1");
	} else if(propertyName == "color") {
		
		stage->SetColor(propertyValue);
	}
}

void StageMap::ReadDictionaryWord(const string& line) {

	if(line.size() < 4 || line[2] != '=') {

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

		if(line.size() != stage->xSize) {

			cerr << "Bad line at stage file: [" << lineNumber << "]: [" << line << "]" << endl;
			THROW(Exception::BadConfig);
		}
		strMap.push_back(line);
	}
	if(strMap.size() != stage->ySize) {

		cerr << "Bad count of lines at stage file: [" << lineNumber << "]" << endl;
		THROW(Exception::BadConfig);
	}

//	vector< vector< GameObject * > > objectMatrix;
//	objectMatrix.reserve(stage->h);

	GameObject*** objectMatrix;
	objectMatrix = new GameObject**[stage->ySize];

	int preMergeCount = 0;

	size_t i, j;
	for(j = 0; j < stage->ySize; j++) {

//		objectMatrix[j].reserve(stage->w);
		string nextColor;
		objectMatrix[j] = new GameObject*[stage->xSize];

		for(i = 0; i < stage->xSize; i++) {

			objectMatrix[j][i] = NULL;
			char c = strMap[j][i];

			bool respawn = false;
			switch(c) {
				case ' ':
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
				case 'P':
					stage->SetPlayerStartPosition(i, j);
					continue;
			}
			if(c >= 'a' && c <= 'z' && j > 0) {

				if(strMap[j - 1][i] == c - 'a' + 'A') {

					continue; // cosmetic stuff for 8x16 sprites.
				}
			}

			string objectClass;

			if(c >= '0' && c <= '9' && !nextColor.empty()) {

				objectClass = nextColor;
				objectClass.push_back(c);
				nextColor = "";
				respawn = true;
			} else {

				Stage::Dictionary::iterator it = stage->dictionary.find(c);
				if(it == stage->dictionary.end()) {

					cout << "StageMap::LoadStage - Unknown character [" << c << "]" << endl;
					continue;
				}
				if (it->second[0] == '<') {

					respawn = true;
					objectClass = it->second.substr(1);
				} else {

					objectClass = it->second;
				}
			}

			size_t extPos = objectClass.find(",");
			string objectSequence;
			if (extPos != string::npos) {
				objectSequence = objectClass.substr(extPos + 1);
				objectClass.erase(extPos);
			}
			
			GameObject *gameObject = stage->CreateObject(objectClass, objectSequence,
				stage->xPos * BrickObject::Width + i * BrickObject::Width,
				stage->yPos * BrickObject::Height + j * BrickObject::Height,
				respawn);
			

			objectMatrix[j][i] = gameObject;

			if(gameObject != NULL) {

				preMergeCount++;
//				gameObject->y = stage->yPos * BrickObject::Height + j * BrickObject::Height;
//				gameObject->x = stage->xPos * BrickObject::Width + i * BrickObject::Width;
				if (gameObject->mirrored) {
				
					if (j > 0 && strMap[j - 1][i] == ' ') {
					
						gameObject->spriteFace->ChangeFace(SpriteFace::up);
					} else {
					
						gameObject->spriteFace->ChangeFace(SpriteFace::down);
					}
				} else if (gameObject->smartBricks) {

					char mask = 0x00;
					SpriteFace::Facing facing;

					for (int jj = -1; jj <=1; jj++) {

						for (int ii = -1; ii <= 1; ii++) {

							if (jj == -1 && ii != 0 || jj == 1 && ii != 0 || ii == 0 && jj == 0) {

								// won't check corners or center.
								continue;
							}
							if (j + jj < 0 || j + jj >= stage->ySize || 
								i + ii < 0 || i + ii >= stage->xSize) {

								// empty map areas.
								continue;
							}

							if (strMap[j][i] == strMap[j + jj][i + ii]) {

								if (jj == -1) {

									mask = mask | 0x08;
								} else if (jj == 1) {

									mask = mask | 0x04;
								} else if (ii == -1) {

									mask = mask | 0x02;
								} else if (ii == 1) {

									mask = mask | 0x01;
								}
							}
						}
					}

					switch (mask) {

					case 0x00: // nothing
						facing = SpriteFace::full_front;
						break;

					case 0x01: // only right
						facing = SpriteFace::full_left;
						break;

					case 0x02: // only left
						facing = SpriteFace::full_right;
						break;

					case 0x03: // right and left
						facing = SpriteFace::horizontal;
						break;

					case 0x04: // only down
						facing = SpriteFace::full_up;
						break;

					case 0x05: // down and right
						facing = SpriteFace::top_left;
						break;

					case 0x06: // down and left
						facing = SpriteFace::top_right;
						break;

					case 0x07: // down right and left
						facing = SpriteFace::up;
						break;

					case 0x08: // only up
						facing = SpriteFace::full_down;
						break;

					case 0x09: // up and right
						facing = SpriteFace::bottom_left;
						break;

					case 0x0a: // up and left
						facing = SpriteFace::bottom_right;
						break;

					case 0x0b: // up right and left
						facing = SpriteFace::down;
						break;

					case 0x0c: // up and down
						facing = SpriteFace::vertical;
						break;

					case 0x0d: // up down and right
						facing = SpriteFace::left;
						break;

					case 0x0e: // up down and left
						facing = SpriteFace::right;
						break;

					case 0x0f: // up down right and left
						facing = SpriteFace::front;
						break;
					}

					gameObject->spriteFace->ChangeFace(facing);
				}
			}
		}
	}
#ifdef MERGE

	int postMergeCount = preMergeCount;
	// try to merge blocks on x axis.

	for(j = 0; j < stage->ySize; j++) {

		int last_merge = -1;
		for(i = 0; i < stage->xSize; i++) {

			GameObject* gameObject = objectMatrix[j][i];
			if(gameObject == NULL) {

				continue;
			}

			if(last_merge == -1) {

				last_merge = i;
				continue;
			}

			if(objectMatrix[j][last_merge]->Merge(gameObject)) {

				gameObject->Terminate();
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

	for(i = 0; i < stage->xSize; i++) {

		int last_merge = -1;
		for(j = 0; j < stage->ySize; j++) {

			GameObject* gameObject = objectMatrix[j][i];
			if(gameObject == NULL) {

				continue;
			}

			if(last_merge == -1) {

				last_merge = j;
				continue;
			}

			if(objectMatrix[last_merge][i]->Merge(gameObject)) {

				gameObject->Terminate();
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
#endif //MERGE

	for(j = 0; j < stage->ySize; j++) {

		delete[] objectMatrix[j];
	}
	delete[] objectMatrix;

	(*this)[currentStageId] = stage;
	stage->PrepareFixedData();
	stage = NULL;
}


