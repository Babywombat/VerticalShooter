#include "Graphics.h"



/// <summary>
/// Constructor
/// </summary>
graphics::graphics() : _factory(nullptr), _renderTarget(nullptr) {
	
}


/// <summary>
/// Destructor
/// </summary>
graphics::~graphics() {
	if(_factory) {
		_factory->Release();
	}
	if(_renderTarget) {
		_renderTarget->Release();
	}
}

/// <summary>
/// Init the graphics instance
/// </summary>
/// <param name="hwnd"></param>
/// <returns></returns>
bool graphics::init(HWND hwnd) {
	//Create the factory
	auto result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_factory);
	if(result != S_OK) {
		return false;
	}

	//Get the area to draw on
	RECT rect;
	GetClientRect(hwnd, &rect);

	D2D1_SIZE_U size = D2D1::SizeU(
		rect.right - rect.left,
		rect.bottom - rect.top
	);

	//Create the rendertarget
	result = _factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hwnd, size),
		&_renderTarget);

	return result == S_OK;
}

/// <summary>
/// Begin drawing
/// </summary>
void graphics::begin_draw() {
	_renderTarget->BeginDraw();
}

/// <summary>
/// End drawing
/// </summary>
void graphics::end_draw() {
	_renderTarget->EndDraw();
}

/// <summary>
/// Clear the screen with the specified rgb-color
/// </summary>
/// <param name="r">red of the color</param>
/// <param name="g">green of the color</param>
/// <param name="b">blue of the color</param>
void graphics::clear_screen(float r, float g, float b) {
	_renderTarget->Clear(D2D1::ColorF(r, g, b));
}

/// <summary>
/// Draws a circle at the specified position with the specified rgba-color
/// </summary>
/// <param name="x">x-Position</param>
/// <param name="y">y-Position</param>
/// <param name="radius">Radius of the circle</param>
/// <param name="r">red of the color</param>
/// <param name="g">green of the color</param>
/// <param name="b">blue of the color</param>
/// <param name="a">alpha of the color</param>
void graphics::draw_circle(float x, float y, float radius, float r, float g, float b, float a) {
	//Create a brush to draw with
	ID2D1SolidColorBrush* brush;
	_renderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);

	//Draw the circle
	_renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 1.0f);

	brush->Release();
}
