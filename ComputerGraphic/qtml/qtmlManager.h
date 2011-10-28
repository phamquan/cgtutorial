#pragma once

#include "tinyxml.h"
#include "String.h"
#include <vector>
using namespace std;

class qtmlManager
{
private:
	TiXmlDocument *doc;
	TiXmlNode *program;

	TiXmlNode *environment;
	TiXmlNode *projection;
	vector<TiXmlNode*> lightsource;

	TiXmlNode *object;

	void Clear();
	bool exploreDoc(TiXmlNode *pParent);
	bool exploreProgram(TiXmlNode *pParent);
	bool exploreEnvironment(TiXmlNode *pParent);
	bool exploreObject(TiXmlNode *pParent);
	bool explore();
public:
	qtmlManager(void);
	qtmlManager(const char*);
	virtual ~qtmlManager(void);

	bool Load(const char* filename);
};

