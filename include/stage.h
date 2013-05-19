#pragma once

#include <map>
#include <string>
#include <vector>
#include "all_objects.h"

using namespace std;

class Stage : public AllObjects {

public:
	Stage(const char* stageId, const int xPos, const int yPos, const int xSize, const int ySize);
	~Stage();
	
	virtual void Init() throw();
	virtual void Terminate();

	void RegisterObject(GameObject* gameObject);
	bool UnregisterObject(unsigned long gameObjectId);

	void GetMatrixRegion(const GameObject& object, int& xPosition, int& yPosition, int& xStop, int& yStop, const int xDiff = 2, const int yDiff = 2);

	bool LoopCheckForCollision(GameObject& gameObject);
	void HoldMeBack(AccelerableObject& other);
	bool AmIGrounded(const AccelerableObject& other);
	void TerminateObject(ObjectMap::iterator itDead);
	void HandleLogic();


	void PrepareFixedData();
	void SetBackground(const char* spriteId) throw();
	void SetHideGamePanel(const bool hideGamePanel);
	void SetNoViewPort(const bool noViewPort);
	void SetColor(const string& colorString);
	void SetPlayerStartPosition(const int x, const int y);
	void PositionPlayer();
	void Spawn();
	void Unspawn();
	
	void Render();
	
	GameObject* CreateObject(const string& objectClass, const string& objectFace,
							 const double x, const double y, const bool respawn);
	
	typedef map< char, string > Dictionary;
	Dictionary dictionary;
	
	friend class StageMap;
protected:
	class Spawned : public GameObject {

	public:
		Spawned(const string& objectClass, const string& objectFace);
		~Spawned();

		void Init() throw();
		void Terminate();

		void StageInit();
		void StageEnd();

		void Render();
		SpriteFace* CreateSpriteFace();

		bool CheckCollision(const GameObject& other);

		GameObject* object;
		string objectClass;
		string objectFace;
	};

	vector< Spawned* > spawnVector;

	class StageCell : public vector< GameObject* > {
	public:
		typedef StageCell* Ptr;
	};
	typedef StageCell::Ptr* StageRow;
	typedef StageRow* StageMatrix;

	StageMatrix stageMatrix;

	StageCell nonStationary;
	void AddToMatrix(GameObject* gameObject, int xPosition, int yPosition);
	void RemoveFromMatrix(GameObject* gameObject, int xPosition, int yPosition);

	sf::IntRect rect;
	sf::Color color;
	int xPos;
	int yPos;
	int xSize;
	int ySize;
	
	int playerStartX;
	int playerStartY;
	
	bool hideGamePanel;
	bool noViewPort;
	
	double viewWidth;
	double viewHeight;
	
	string stageId;
	Sprite* background;
	sf::Image cachedImage;
	sf::Texture cachedTexture;
};
