#pragma once

#include "tinyxml.h"

class qtmlManager
{
private:
	TiXmlDocument *doc;
	TiXmlNode* environment;
	TiXmlNode* object;

	void Clear();
	void scanFile();
public:
	qtmlManager(void);
	virtual ~qtmlManager(void);

	bool Load(const char* filename);
};

