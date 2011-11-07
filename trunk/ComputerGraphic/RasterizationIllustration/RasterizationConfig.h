#pragma once

enum PIXELTYPE{PCANDIDATE, PCHOSEN, PNONE};

class CRasterizationConfig
{
private:
	//screen resolution
	int m_width, m_height;
	/*scale ratio
	example: scale = 100: zoom a pixel 100 time
	*/
	int m_scale;
	PIXELTYPE *m_pixelState;
public:
	CRasterizationConfig(void);
	CRasterizationConfig(int width, int height, int scale);
	virtual ~CRasterizationConfig(void);

	void setResolution(int width, int height);
	void setScale(int scale);
};

