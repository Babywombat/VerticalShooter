#include "Player.h"
#include "Input.h"
#include "Defines.h"
#include "GameLogic.h"
#include "Utils.h"

using namespace vs;

/// <summary>
/// Constructor
/// </summary>
player::player(game_logic* logic) : 
	game_object			(0, 0, 50.0f, 25.0f),
	_logic				(logic),
	_time_since_bullet	(0.0f),
	_shooting_speed		(0.5f){}

/// <summary>
/// Destructor
/// </summary>
player::~player() = default;

/// <summary>
/// Updates the player's position
/// </summary>
/// <param name="delta_time">Time since last update</param>
void player::on_update(double delta_time) {
	if (is_dead()) return;

	//Decrease bullet cooldown
	if(_time_since_bullet > 0.0f) {
		_time_since_bullet -= delta_time;
	}

	const auto current_change = _speed * static_cast<float>(delta_time);

	//Left/Right
	if(input::get_instance().is_key_down(input::E_KEYS::A)) {
		_x -= current_change;
	} else if(input::get_instance().is_key_down(input::E_KEYS::D)) {
		_x += current_change;
	}

	//Up/Down
	if (input::get_instance().is_key_down(input::E_KEYS::W)) {
		_y -= current_change;
	} else if (input::get_instance().is_key_down(input::E_KEYS::S)) {
		_y += current_change;
	}

	if (_x < 0) _x = 0;
	if (_y < _height) _y = _height;
	if (_x > RESOLUTION_X - _width) _x = RESOLUTION_X - _width;
	if (_y > RESOLUTION_Y) _y = RESOLUTION_Y;

	if(input::get_instance().is_key_down(input::Space)) {
		//Create a bullet
		if(_time_since_bullet <= 0.0f) {
			_time_since_bullet = _shooting_speed;
			_logic->create_bullets(bullet::normal, _x + _width / 2, _y - _height);
		}
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

	//Calculate points for the visuals
	const auto point1 = D2D1::Point2F(_x, _y);
	const auto point2 = D2D1::Point2F(_x + _width / 2, _y - _height);
	const auto point3 = D2D1::Point2F(_x + _width, _y);


	//Specify the player's width
	const auto line_width = 3.0f;

	//Draw the lines
	render_target->DrawLine(point1, point2, brush, line_width);
	render_target->DrawLine(point2, point3, brush, line_width);
	//render_target->DrawRectangle(get_aabb(), brush);

	utils::safe_release(&brush);
}

/// <summary>
/// Initializes the player's variables
/// </summary>
void player::initialize() {
	_color = D2D1::ColorF(D2D1::ColorF::Green, 1.0f);
	_speed = 200.0f;
	_health = 5;
	_shooting_speed = 0.2f;
	set_layer(E_LAYER::player);
}

/// <summary>
/// Handles the collisions with other objects
/// </summary>
/// <param name="collided_object">Object that this object collided with</param>
void player::handle_collision(transform_2d* collided_object) {
	inflict_damage(1);
}
