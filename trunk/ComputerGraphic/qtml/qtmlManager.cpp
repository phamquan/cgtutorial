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
		projection = NULL;
		lightsource.clear();
	}
}

bool qtmlManager::exploreDoc(TiXmlNode* pParent) {
	TiXmlNode* pChild=0;
	while (pChild = pParent->IterateChildren(pChild)) {
		int t = pChild->Type();
		String v = String(pChild->Value()).toUpperCase();
		switch (t) {
		case TiXmlNode::ELEMENT:
			{
				if (!v.compareTo("WATERMELON"))
					if (program) {
						//Exception: duplicate program
						return false;
					}
					else
						program = pChild;
				else if (!v.compareTo("ENVIRONMENT"))
					if (environment) {
						//Exception: duplicate environment
						return false;
					}
					else
						environment = pChild;
				else if (!v.compareTo("OBJECT"))
					if (object) {
						//Exception: duplicate object
						return false;
					}
					else
						object = pChild;
			}
			break;
		case TiXmlNode::COMMENT:
		case TiXmlNode::TEXT:
			break;
		case TiXmlNode::UNKNOWN:
			return false;
		default:
			return false;
		}
	}
	return true;
}

bool qtmlManager::exploreEnvironment(TiXmlNode *pParent) {
	TiXmlNode* pChild=0;
	while (pChild = pParent->IterateChildren(pChild)) {
		int t = pChild->Type();
		String v = String(pChild->Value()).toUpperCase();
		switch (t) {
		case TiXmlNode::ELEMENT:
			{
				if (!v.compareTo("PROJECTION"))
					if (projection) {
						//Exception dupplicate projection
						return false;
					}
					else
						projection = pChild;
				else if (!v.compareTo("LIGHTSOURCE"))
					lightsource.push_back(pChild);
			}
			break;
		case TiXmlNode::COMMENT:
		case TiXmlNode::TEXT:
			break;
		case TiXmlNode::UNKNOWN:
			return false;
		default:
			return false;
		}
	}
	return true;
}


bool qtmlManager::explore() {
	if (exploreDoc(doc)) {
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
		if (explore())
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