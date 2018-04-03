#include "Player.h"
#include "Input.h"

/// <summary>
/// Constructor
/// </summary>
player::player() : actor() {}

/// <summary>
/// Destructor
/// </summary>
player::~player() = default;

/// <summary>
/// Updates the player's position
/// </summary>
/// <param name="delta_time">Time since last update</param>
void player::on_update(double delta_time) {
	auto current_change = _speed * delta_time;

	//Left/Right
	if(input::get_instance().is_key_down(input::keys::A)) {
		_posX -= current_change;
	} else if(input::get_instance().is_key_down(input::keys::D)) {
		_posX += current_change;
	}

	//Up/Down
	if (input::get_instance().is_key_down(input::keys::W)) {
		_posY -= current_change;
	} else if (input::get_instance().is_key_down(input::keys::S)) {
		_posY += current_change;
	}
}

/// <summary>
/// Renders the player
/// </summary>
/// <param name="render_target">Target to render to</param>
void player::on_render(ID2D1HwndRenderTarget* render_target) {
	if (!render_target) return;

	//Drawing the player's visuals
	ID2D1SolidColorBrush* brush;
	render_target->CreateSolidColorBrush(_color, &brush);

	//D2D1_RECT_F rect = D2D1::RectF(_posX, _posY, _posX + 50, _posY + 50);
	D2D1_POINT_2F point1 = D2D1::Point2F(_posX, _posY);
	D2D1_POINT_2F point2 = D2D1::Point2F(_posX + 25, _posY - 25);
	D2D1_POINT_2F point3 = D2D1::Point2F(_posX + 50, _posY);


	//render_target->FillRectangle(&rect, brush);
	render_target->DrawLine(point1, point2, brush);
	render_target->DrawLine(point2, point3, brush);

	brush->Release();
}

/// <summary>
/// Initializes the player's variables
/// </summary>
void player::initialize(double posX, double posY) {
	_color = D2D1::ColorF(D2D1::ColorF::Green, 1.0f);
	_speed = 30.0f;
	_posX = posX;
	_posY = posY;
}
