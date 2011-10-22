#include "qtmlManager.h"


qtmlManager::qtmlManager(void)
{
}


qtmlManager::~qtmlManager(void)
{
}

void qtmlManager::Clear() {
	if (!doc) {
		doc->Clear();
		delete doc;
		doc = NULL;
		environment = NULL;
		object = NULL;
	}
}

void qtmlManager::scanFile() {
	TiXmlNode* pChild=0;
	while (pChild = doc->IterateChildren(pChild)) {
		int t = pChild->Type();
		switch (t) {
		case TiXmlNode::ELEMENT:
			{
				
			}
			break;
		}
	}
}

bool qtmlManager::Load(const char* filename) {
	//clear all states
	Clear();
	doc = new TiXmlDocument(filename);
	if (doc->LoadFile()) {
		scanFile();
		return true;
	}
	else {
		Clear();
		return false;
	}
}