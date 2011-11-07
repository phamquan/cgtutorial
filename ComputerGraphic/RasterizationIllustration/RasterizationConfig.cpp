#include "StdAfx.h"
#include "RasterizationConfig.h"


CRasterizationConfig::CRasterizationConfig(void)
	: m_width(0), m_height(0), m_scale(1), m_pixelState(NULL)
{
}

CRasterizationConfig::CRasterizationConfig(int width, int height, int scale)
	: m_width(width), m_height(height), m_scale(scale)
	, m_pixelState(new PIXELTYPE[width*height])
{
}

CRasterizationConfig::~CRasterizationConfig(void)
{
}

void CRasterizationConfig::setResolution(int width, int height) {
	m_width = width;
	m_height = height;
}

void CRasterizationConfig::setScale(int scale) {
	m_scale = scale;
}