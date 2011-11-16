#pragma once

enum PIXELTYPE{PCANDIDATE, PCHOSEN, PNONE};
enum RASTERIZEALG{DDA, BRESENHAM};

#define swap(type, i, j) {type t = i; i = j; j = t;}

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

struct PIXEL{
	int x, y;
	COLOR color;
	PIXEL();

	PIXEL(int col, int row):
	x(col), y(row)
	{}

	PIXEL(int col, int row, COLOR &color):
	x(col), y(row)
	{
		this->color = color;
	}
};

class CRasterizationConfig
{
private:
	//screen resolution
	int m_width, m_height;
	RASTERIZEALG m_rasterizealg;
	/*scale ratio
	example: scale = 100: zoom a pixel 100 time
	*/
	float m_scale;
public:
	CRasterizationConfig(void);
	CRasterizationConfig(int width, int height, float scale, RASTERIZEALG alg);
	virtual ~CRasterizationConfig(void);

	void setResolution(int width, int height);
	void setScale(float scale);
	float getScale(void);
	//plus or minus the scale ratio by x
	void modifyScale(float x);
	int getWidth(void);
	int getHeight(void);
	RASTERIZEALG getAlgorithmRasterization(void);
	void setAlgorithmRasterization(RASTERIZEALG);
};

