#ifndef VS_ACTOR_HPP
#define VS_ACTOR_HPP

#include <d2d1.h>

class actor {
protected:
	ID2D1SolidColorBrush* _brush;
	D2D1::ColorF _color;
	double _speed;
	double _posX, _posY;

public:
	actor();
	virtual ~actor();

	virtual void on_update(double delta_time) = 0;
	virtual void on_render(ID2D1HwndRenderTarget* render_target) = 0;
	virtual void initialize(double posX, double posY) = 0;
};

#endif //VS_ACTOR_HPP