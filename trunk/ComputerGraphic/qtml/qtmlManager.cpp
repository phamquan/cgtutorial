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

bool qtmlManager::explore(TiXmlNode* pParent) {
	TiXmlNode* pChild=0;
	while (pChild = pParent->IterateChildren(pChild)) {
		int t = pChild->Type();
		switch (t) {
		case TiXmlNode::ELEMENT:
			{
				if (String(pParent->Value()).toUpperCase().compareTo("watermelon"))
					if (program) {
						//Exception: duplicate program
						return false;
					}
					else
						program = pParent;
				else if (String(pParent->Value()).toUpperCase().compareTo("environment"))
					if (environment) {
						//Exception: duplicate environment
						return false;
					}
					else
						environment = pParent;
			}
			break;
		default:
			return false;
		}
	}
}

bool qtmlManager::scanFile() {
	if (explore(doc)) {
		Clear();
		return false;
	}
	else
		return true;
}

bool qtmlManager::Load(const char* filename) {
	//clear all states
	Clear();
	doc = new TiXmlDocument(filename);
	if (doc->LoadFile()) {
		if (scanFile())
			return true;
		else {
			Clear();
			return false;
		}
	}
	else {
		Clear();
		return false;
	}
}