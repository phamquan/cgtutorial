#include "StdAfx.h"
#include "Environment.h"

CEnvironment::CEnvironment() : COpenGLNode("environment",NODE_ENVIRONMENT)
{
}

CEnvironment::~CEnvironment()
{
}

CCamera* CEnvironment::GetCamera()
{
	return (CCamera*)m_listChild.GetAt(1);
}

CProjection* CEnvironment::GetProjection()
{
	return (CProjection*)m_listChild.GetAt(0);
}