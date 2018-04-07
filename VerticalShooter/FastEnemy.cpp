#include "FastEnemy.h"
#include "Utils.h"

using namespace vs;

/// <summary>
/// Constructor
/// </summary>
/// <param name="direct2d_factory">Direct2d factory</param>
fast_enemy::fast_enemy(ID2D1PathGeometry* geometry) :
	_geometry	(geometry){}


/// <summary>
/// Destructor
/// </summary>
fast_enemy::~fast_enemy() = default;

/// <summary>
/// Renders the enemies' visuals
/// </summary>
/// <param name="render_target">Target to render to</param>
void fast_enemy::on_render(ID2D1HwndRenderTarget* render_target) {
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
void fast_enemy::initialize() {
	_color = D2D1::ColorF(D2D1::ColorF::Yellow, 1.0f);
	_speed = 120.0f;
	_health = 1;
	set_layer(E_LAYER::enemy);
	set_size(20, 20);
}

/// <summary>
/// Returns the enemies' type
/// </summary>
/// <returns>Enemy type</returns>
enemy::E_ENEMY_TYPE fast_enemy::get_type() const {
	return fast;
}
