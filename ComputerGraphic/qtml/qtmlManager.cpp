#include "qtmlManager.h"


qtmlManager::qtmlManager(void) : doc(NULL), program(NULL), environment(NULL), object(NULL)
{
}

qtmlManager::qtmlManager(const char* filename) : doc(NULL), program(NULL), environment(NULL), object(NULL)
{
	Load(filename);
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
				else if (String(pParent->Value()).toUpperCase().compareTo("object"))
					if (object) {
						//Exception: duplicate object
						return false;
					}
					else
						object = pParent;
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