#pragma once

#include "stdafx.h"
#include "tinyxml.h"

class CCGTXParser
{
public:
	TiXmlDocument *doc;
	TiXmlNode *program;
	TiXmlNode *object;
	TiXmlNode *environment;
	TiXmlElement *camera;
	TiXmlElement *projection;
	TiXmlElement *viewport;
	CString error;

	CCGTXParser(void)
	{
		doc = NULL;
		Clear();
	}

	virtual ~CCGTXParser(void)
	{
		Clear();
	}

	bool Load(const char* filename)
	{
		Clear();
		doc = new TiXmlDocument(filename);
		if (doc->LoadFile()) {
			if (explore())
				return true;
			else {
				Clear();
				return false;
			}
		} else {
			error.Format("Error reading file %s",filename);
			Clear();
			return false;
		}
	}
	
	void Clear()
	{
		if (doc != NULL) {
			doc->Clear();
			delete doc;
		}
		doc = NULL;
		program = NULL;
		object = NULL;
		environment = NULL;
		camera = NULL;
		projection = NULL;
		viewport = NULL;
	}

	bool exploreDoc(TiXmlNode *pParent)
	{
		TiXmlNode* pChild=0;
		while (pChild = pParent->IterateChildren(pChild)) {
			int t = pChild->Type();
			CString v = CString(pChild->Value()).MakeUpper();
			switch (t) {
			case TiXmlNode::ELEMENT:
				if (v == "WATERMELON") {
					if (program != NULL) {
						error = "Duplicate Watermelon tag";
						return false;
					} else {
						program = pChild;
					}
				} else {
					error = "Unknown tag";
					return false;
				}
			case TiXmlNode::COMMENT:
			case TiXmlNode::TEXT:
			case TiXmlNode::DECLARATION:
				break;
			default:
				error = "Unknown tag";
				return false;
			}
		}

		if(program == NULL) {
			error = "Missing Watermelon tag";
			return false;
		}

		return true;
	}

	bool exploreProgram(TiXmlNode *pParent)
	{
		TiXmlNode* pChild=0;
		while (pChild = pParent->IterateChildren(pChild)) {
			int t = pChild->Type();
			CString v = CString(pChild->Value()).MakeUpper();
			switch (t) {
			case TiXmlNode::ELEMENT:
				if (v == "ENVIRONMENT") {
					if (environment != NULL) {
						error = "Duplicate Environment tag";
						return false;
					} else {
						environment = pChild;
					}
				} else if (v == "OBJECT") {
					if (object != NULL) {
						error = "Duplicate Object tag";
						return false;
					} else {
						object = pChild;
					}
				} else {
					error = "Unknown tag";
					return false;
				}
			case TiXmlNode::COMMENT:
			case TiXmlNode::TEXT:
			case TiXmlNode::DECLARATION:
				break;
			default:
				error = "Unknown tag";
				return false;
			}
		}

		if(environment == NULL) {
			error = "Missing Environment tag";
			return false;
		} 
		if(object == NULL) {
			error = "Missing Object tag";
			return false;
		}

		return true;
	}

	bool exploreEnvironment(TiXmlNode *pParent)
	{
		TiXmlNode* pChild=0;
		while (pChild = pParent->IterateChildren(pChild)) {
			int t = pChild->Type();
			CString v = CString(pChild->Value()).MakeUpper();
			switch (t) {
			case TiXmlNode::ELEMENT:
				if (v == "PROJECTION") {
					if (projection != NULL) {
						error = "Duplicate Projection tag";
						return false;
					} else {
						projection = (TiXmlElement*)pChild;
					}
				} else if (v == "CAMERA") {
					if (camera != NULL) {
						error = "Duplicate Camera tag";
						return false;
					} else {
						camera = (TiXmlElement*)pChild;
					}
				} else if (v == "VIEWPORT") {
					if (viewport != NULL) {
						error = "Duplicate Viewport tag";
						return false;
					} else {
						viewport = (TiXmlElement*)pChild;
					}
				} else {
					error = "Unknown tag";
					return false;
				}
			case TiXmlNode::COMMENT:
			case TiXmlNode::TEXT:
			case TiXmlNode::DECLARATION:
				break;
			default:
				error = "Unknown tag";
				return false;
			}
		}

		if(projection == NULL) {
			error = "Missing Projection tag";
			return false;
		}
		if(camera == NULL) {
			error = "Missing Camera tag";
			return false;
		}
		if(viewport == NULL) {
			error = "Missing Viewport tag";
			return false;
		}

		return true;
	}

	//bool exploreObject(TiXmlNode *pParent);
	
	bool explore()
	{
		if (exploreDoc(doc))
			return exploreProgram(program) && exploreEnvironment(environment);// && exploreObject(object);
		else {
			Clear();
			return false;
		}
	}
};

