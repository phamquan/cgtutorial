#pragma once

#include "tinyxml.h"
#include "String.h"

class qtmlManager
{
private:
	TiXmlDocument *doc;
	TiXmlNode *program;

	TiXmlNode *environment;
	TiXmlNode *projection;
	TiXmlNode *lightsource;

	TiXmlNode *object;

	void Clear();
	bool exploreDoc(TiXmlNode *pParent);
	bool exploreProgram(TiXmlNode *pParent);
	bool exploreEnvironment(TiXmlNode *pParent);
	bool exploreObject(TiXmlNode *pParent);
	bool scanFile();
public:
	qtmlManager(void);
	qtmlManager(const char*);
	virtual ~qtmlManager(void);

	bool Load(const char* filename);
};

