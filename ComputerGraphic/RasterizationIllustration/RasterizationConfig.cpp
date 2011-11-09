#include "StdAfx.h"
#include "RasterizationConfig.h"


CRasterizationConfig::CRasterizationConfig(void)
	: m_width(0), m_height(0), m_scale(1)
{
}

CRasterizationConfig::CRasterizationConfig(int width, int height, float scale)
	: m_width(width), m_height(height), m_scale(scale)
{
}

CRasterizationConfig::~CRasterizationConfig(void)
{
}

void CRasterizationConfig::setResolution(int width, int height) {
	m_width = width;
	m_height = height;
}

void CRasterizationConfig::setScale(float scale) {
	m_scale = scale;
}

float CRasterizationConfig::getScale(void)
{
	return m_scale;
}

void CRasterizationConfig::modifyScale(float x) {
	float tmp = m_scale+x;
	if (tmp > 0.0000001) m_scale = tmp;
	CString err;
	err.Format(L"%f",tmp);
	//MessageBox(NULL, err, L"error", IDOK);
}

int CRasterizationConfig::getWidth(void)
{
	return m_width;
}


int CRasterizationConfig::getHeight(void)
{
	return m_height;
}
