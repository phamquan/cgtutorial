#pragma once

enum PIXELTYPE{PCANDIDATE, PCHOSEN, PNONE};
enum RASTERIZEALG{DDA, BRESENHAM};

class CRasterizationConfig
{
private:
	//screen resolution
	int m_width, m_height;
	/*scale ratio
	example: scale = 100: zoom a pixel 100 time
	*/
	float m_scale;
public:
	CRasterizationConfig(void);
	CRasterizationConfig(int width, int height, float scale);
	virtual ~CRasterizationConfig(void);

	void setResolution(int width, int height);
	void setScale(float scale);
	float getScale(void);
	//plus or minus the scale ratio by x
	void modifyScale(float x);
	int getWidth(void);
	int getHeight(void);
};

