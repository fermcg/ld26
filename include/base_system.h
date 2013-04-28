#pragma once
#include <string>

using namespace std;

class BaseSystem {
	public:
		BaseSystem(const char* name);
		virtual ~BaseSystem();

		virtual void Init();
		virtual void Terminate();

		string GetFullName() const;

	protected:
		string name;
		string objectId;

	private:
		bool initialized;
};
