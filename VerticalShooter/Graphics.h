#ifndef VS_GRAPHICS_HPP
#define VS_GRAPHICS_HPP

#include <Windows.h>
#include <d2d1.h>

class graphics
{
	ID2D1Factory* _factory;
	ID2D1HwndRenderTarget* _renderTarget;

public:
	graphics();
	~graphics();

	bool init(HWND hwnd);

	void begin_draw();
	void end_draw();

	void clear_screen(float r, float g, float b);
	void draw_circle(float x, float y, float radius, float r, float g, float b, float a);
};

#endif //VS_GRAPHICS_HPP
