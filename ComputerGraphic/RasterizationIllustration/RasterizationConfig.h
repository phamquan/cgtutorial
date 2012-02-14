#pragma once

enum PIXELTYPE{PCANDIDATE, PCHOSEN, PNONE};
enum RASTERIZEALG{DDA, BRESENHAM};
enum RUNMODE{FAST, STEP, SMOOTH};

#define swap(type, i, j) {type t = i; i = j; j = t;}
#define RED COLOR(1.0f, 0.0f, 0.0f)
#define GREEN COLOR(0.0f, 1.0f, 0.0f)
#define BLUE COLOR(0.0f, 0.0f, 1.0f)
#define BLACK COLOR(0.0f, 0.0f, 0.0f)
#define WHITE COLOR(1.0f, 1.0f, 1.0f)

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

	COLOR operator+(const COLOR& op) {
		return COLOR(red+op.red, green+op.green, blue+op.blue);
	}
	COLOR operator-(const COLOR& op) {
		return COLOR(red-op.red, green-op.green, blue-op.blue);
	}
	COLOR operator*(const float& op) {
		return COLOR(red*op, green*op, blue*op);
	}
	COLOR& operator+=(const COLOR& op) {
		this->red += op.red;
		this->green += op.green;
		this->blue += op.blue;
		return *this;
	}
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
	COLOR m_backgroundColor;
public:
	CRasterizationConfig(void);
	CRasterizationConfig(int width, int height, float scale, RASTERIZEALG alg, COLOR &backgroundColor);
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
	const COLOR& getBackgroundColor(void);
	void setBackgroundColor(COLOR&);
};

