#pragma once

#include "tinyxml.h"
#include "String.h"

class qtmlManager
{
private:
	TiXmlDocument *doc;
	TiXmlNode *program;
	TiXmlNode* environment;
	TiXmlNode* object;

	void Clear();
	bool explore(TiXmlNode* pParent);
	bool scanFile();
public:
	qtmlManager(void);
	virtual ~qtmlManager(void);

	bool Load(const char* filename);
};

