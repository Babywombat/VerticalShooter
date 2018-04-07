#include "ShootingEnemy.h"
#include "Defines.h"
#include "Utils.h"
#include "Bullet.h"
#include "GameLogic.h"

using namespace vs;

/// <summary>
/// Constructor
/// </summary>
/// <param name="direct2d_factory">Direct2d factory</param>
/// <param name="game_logic">The game logic</param>
shooting_enemy::shooting_enemy(ID2D1PathGeometry* geometry, game_logic* logic) :
	_geometry				(geometry),
	_game_logic				(logic),
	_current_direction		(1),
	_shooting_speed			(2.0f),
	_time_since_bullet		(0.0f){}


/// <summary>
/// Destructor
/// </summary>
shooting_enemy::~shooting_enemy() = default;

/// <summary>
/// Updates the enemy
/// </summary>
/// <param name="delta_time">Time since last frame</param>
void shooting_enemy::on_update(double delta_time) {
	if (is_dead()) return;

	//Decrease bullet cooldown
	if (_time_since_bullet > 0.0f) {
		_time_since_bullet -= delta_time;
	}
	//Create a bullet
	if (_time_since_bullet <= 0.0f) {
		_time_since_bullet = _shooting_speed;
		_game_logic->create_bullets(bullet::multi, _x + _width / 2, _y, E_LAYER::enemy);
	}

	const auto current_change = _speed * static_cast<float>(delta_time);

	//Mover diagonally
	_y += current_change * 0.3f; // Slow down the y-movement
	_x += current_change * _current_direction;

	if(_x > RESOLUTION_X - _width || _x <= 0) {
		//Change direction when hitting the edge of screen
		_current_direction *= -1;
	}

	if (_y - _height >= RESOLUTION_Y) inflict_damage(1);
}

/// <summary>
/// Renders the enemies' visuals
/// </summary>
/// <param name="render_target">Target to render to</param>
void shooting_enemy::on_render(ID2D1HwndRenderTarget* render_target) {
	if (!render_target) return;

	//Drawing the enemies' visuals
	ID2D1SolidColorBrush* brush;
	render_target->CreateSolidColorBrush(_color, &brush);

	//Translate the geometry of this enemy by its position
	render_target->SetTransform(D2D1::Matrix3x2F::Translation(_x, _y - _height));

	//Draw the geometry
	render_target->FillGeometry(_geometry, brush);

	//Revert translation
	render_target->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));

	//render_target->DrawRectangle(get_aabb(), brush);

	utils::safe_release(&brush);
}

/// <summary>
/// Initializes the enemy
/// </summary>
void shooting_enemy::initialize() {
	_color = D2D1::ColorF(D2D1::ColorF::Purple, 1.0f);
	_speed = 30.0f;
	_health = 1;
	set_layer(E_LAYER::enemy);
	set_size(24, 24);
}

/// <summary>
/// Returns the enemies' type
/// </summary>
/// <returns>Enemy type</returns>
enemy::E_ENEMY_TYPE shooting_enemy::get_type() const {
	return shooting;
}
