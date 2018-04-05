#include "BulletFactory.h"

using namespace vs;

/// <summary>
/// Constructor
/// </summary>
bullet_factory::bullet_factory() = default;


/// <summary>
/// Destructor
/// </summary>
bullet_factory::~bullet_factory() = default;

/// <summary>
/// Creates a new bullet of the specified type
/// </summary>
/// <param name="type">Type of the bullet</param>
/// <param name="x">x Position</param>
/// <param name="y">y Position</param>
/// <returns></returns>
bullet* bullet_factory::make_bullet(const E_BULLET_TYPE type, const float x, const float y) const {
	bullet* new_bullet = nullptr;
	switch(type) {
		case normal: {
			new_bullet = new bullet();
			break;
		}
		default: {
			return new_bullet;
		};
	}
	if(new_bullet) {
		new_bullet->initialize();
		new_bullet->set_position(x, y);
	}
	return new_bullet;
}
