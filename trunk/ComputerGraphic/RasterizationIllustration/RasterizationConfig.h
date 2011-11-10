#pragma once

enum PIXELTYPE{PCANDIDATE, PCHOSEN, PNONE};
enum RASTERIZEALG{DDA, BRESENHAM};

struct PIXEL{
	int x, y;
	PIXEL();
	PIXEL(int col, int row):
	x(col), y(row)
	{}
};

struct COLOR {
	float red, green, blue, alpha;

	COLOR():
	red(1.0f), green(1.0f), blue(1.0f), alpha(1.0f)
	{}

	COLOR(float r, float g, float b):
	red(r), green(g), blue(b), alpha(1.0f)
	{};

	COLOR(float r, float g, float b, float a):
	red(r), green(g), blue(b), alpha(a)
	{}
};

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

