#include "BulletFactory.h"

using namespace vs;

/// <summary>
/// Constructor
/// </summary>
bullet_factory::bullet_factory():
	_multi_bullet_offset	(15) {
	
}

/// <summary>
/// Destructor
/// </summary>
bullet_factory::~bullet_factory() = default;

/// <summary>
/// Creates a single bullet of the specified type
/// </summary>
/// <param name="type">Type of the bullet</param>
/// <param name="x">x Position</param>
/// <param name="y">y Position</param>
/// <param name="layer">Layer of the bullet (standard is player_bullet, meaning the bullet will hit enemies) </param>
/// <returns></returns>
bullet* bullet_factory::make_single_bullet(const bullet::E_BULLET_TYPE type,
	const float x,
	const float y,
	const transform_2d::E_LAYER layer) const {
	bullet* new_bullet = nullptr;

	switch (type) {
	case bullet::normal: {
		new_bullet = new bullet();
		break;
	}
	default: {
		return new_bullet;
	};
	}
	if (new_bullet) {
		new_bullet->initialize();
		new_bullet->set_position(x, y);
		new_bullet->set_layer(layer);

		if (layer != transform_2d::player_bullet) {
			//Change bullet color if the bullet is not from the player
			new_bullet->set_color(D2D1::ColorF(D2D1::ColorF::Crimson));
			//Move the bullet downwards
			new_bullet->set_direction(1);
		}
	}
	return new_bullet;
}

/// <summary>
/// Creates bullets of the specified type, may be a single or multiple bullets, returns them in a vector
/// </summary>
/// <param name="type">Type of the bullet</param>
/// <param name="x">x Position</param>
/// <param name="y">y Position</param>
/// <param name="layer">Layer of the bullet (standard is player_bullet, meaning the bullet will hit enemies) </param>
/// <returns>Vector of created bullets</returns>
std::vector<bullet*> bullet_factory::make_bullets(const bullet::E_BULLET_TYPE type, const float x, const float y, transform_2d::E_LAYER layer) const {
	bullet* new_bullet = nullptr;
	std::vector<bullet*> bullet_vec;

	switch(type) {
		case bullet::normal: {
			//Make a single normal bullet
			new_bullet = make_single_bullet(bullet::normal, x, y, layer);
			if(new_bullet) {
				bullet_vec.push_back(new_bullet);
			}
			break;
		}
		case bullet::multi: {
			//Make multiple normal bullets (3) and return them in a list
			//Each bullet has a specific offset so that they spawn next to each other
 			for (auto i = -1; i < 2; i++) {
				new_bullet = make_single_bullet(bullet::normal, x + (i * _multi_bullet_offset), y, layer);
				if (new_bullet) {
					bullet_vec.push_back(new_bullet);
				}
			}
			break;
		}
		default: {
			return bullet_vec;
		};
	}
	return bullet_vec;
}
