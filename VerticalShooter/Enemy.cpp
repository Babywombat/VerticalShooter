#include "Enemy.h"
#include "Player.h"
#include "Defines.h"
#include "Utils.h"

using namespace vs;

/// <summary>
/// Constructor
/// </summary>
enemy::enemy(): 
	game_object	(0, 0, 25, 25) {
	
}

/// <summary>
/// Destructor
/// </summary>
enemy::~enemy() = default;

/// <summary>
/// Updates the enemy
/// </summary>
/// <param name="delta_time">Time since last frame</param>
void enemy::on_update(double delta_time) {
	if (is_dead()) return;
	const auto current_change = _speed * static_cast<float>(delta_time);

	_y += current_change;

	if (_y - _height >= RESOLUTION_Y) inflict_damage(1);
}

/// <summary>
/// Renders the enemies' visuals
/// </summary>
/// <param name="render_target">Target to render to</param>
void enemy::on_render(ID2D1HwndRenderTarget* render_target) {
	if (!render_target) return;

	//Drawing the enemies' visuals
	ID2D1SolidColorBrush* brush;
	render_target->CreateSolidColorBrush(_color, &brush);

	//Calculate points for the visuals
	const auto center = D2D1::Point2F(_x + _width / 2, _y - _height / 2);

	//Draw the lines
	render_target->FillEllipse(D2D1::Ellipse(center, _width / 2, _height / 2), brush);
	//render_target->DrawRectangle(get_aabb(), brush);

	utils::safe_release(&brush);
}

/// <summary>
/// Initializes the enemy
/// </summary>
void enemy::initialize() {
	_color = D2D1::ColorF(D2D1::ColorF::CadetBlue, 1.0f);
	_speed = 20.0f;
	_health = 1;
	set_layer(E_LAYER::enemy);
}

/// <summary>
/// Handles the collisions with other objects
/// </summary>
/// <param name="collided_object">Object that this object collided with</param>
void enemy::handle_collision(transform_2d* collided_object) {
	inflict_damage(1);
}

/// <summary>
/// Returns the enemies' type
/// </summary>
/// <returns>Enemy type</returns>
enemy::E_ENEMY_TYPE enemy::get_type() const {
	return normal;
}
