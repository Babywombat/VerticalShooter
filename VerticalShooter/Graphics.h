#ifndef VS_GRAPHICS_HPP
#define VS_GRAPHICS_HPP

#include <Windows.h>
#include <d2d1.h>

class Graphics
{
private:
	ID2D1Factory* _factory;
	ID2D1HwndRenderTarget* _renderTarget;

public:
	Graphics();
	~Graphics();

	bool init(HWND hwnd);

	void beginDraw();
};

#endif //VS_GRAPHICS_HPP
