#pragma once
#include <string>

using namespace std;

class BaseSystem {
public:
	BaseSystem(const char* name);
	virtual ~BaseSystem();
	
	virtual void Init();
	virtual void Terminate();
	
protected:
	string name;
	string objectId;
	
	string GetFullName() const;
private:
	bool initialized;
};