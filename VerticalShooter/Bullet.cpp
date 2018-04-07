#include "Bullet.h"
#include "Defines.h"
#include "Utils.h"

/// <summary>
/// Constructor
/// </summary>
vs::bullet::bullet() :
	game_object	(0, 0, 5, 10),
	_direction	(-1){}

/// <summary>
/// Destructor
/// </summary>
vs::bullet::~bullet() = default;

/// <summary>
/// Updates the bullet
/// </summary>
/// <param name="delta_time">Time since last frame</param>
void vs::bullet::on_update(double delta_time) {
	if (is_dead()) return;

	const auto current_change = _speed * static_cast<float>(delta_time);
	//Move bullet straight up
	_y += current_change * _direction;

	//Destroy off screen bullets
	if (_y <= 0 || _y - _height >= RESOLUTION_Y) inflict_damage(1);
}

/// <summary>
/// Renders the bullets visuals
/// </summary>
/// <param name="render_target"></param>
void vs::bullet::on_render(ID2D1HwndRenderTarget* render_target) {
	if (!render_target) return;

	//Drawing the player's visuals
	ID2D1SolidColorBrush* brush;
	render_target->CreateSolidColorBrush(_color, &brush);

	//Calculate rect for the visuals
	const auto rect = D2D1::RectF(_x, _y - _height, _x + _width, _y);

	//Draw the lines
	render_target->FillRectangle(rect, brush);

	utils::safe_release(&brush);
}

/// <summary>
/// Initializes the bullet
/// </summary>
void vs::bullet::initialize() {
	_color = D2D1::ColorF(D2D1::ColorF::Gray, 1.0f);
	_speed = 100.0f;
	_health = 1;
	set_layer(player_bullet);
}

/// <summary>
/// Handles the collisions with other objects
/// </summary>
/// <param name="collided_object">Object that this object collided with</param>
void vs::bullet::handle_collision(transform_2d* collided_object) {
	inflict_damage(1);
}

/// <summary>
/// Sets the bullets moving direction on the y-axis
/// </summary>
/// <param name="direction">Direction to move, negative means up, position means down</param>
void vs::bullet::set_direction(const int direction) {
	_direction = direction;
}
