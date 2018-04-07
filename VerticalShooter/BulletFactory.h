#ifndef VS_BULLET_FACTORY_HPP
#define VS_BULLET_FACTORY_HPP
#include "Bullet.h"
#include "Transform2d.h"
#include <vector>

namespace vs {
	class bullet_factory {
	private:
		const int				_multi_bullet_offset;

		bullet*					make_single_bullet(bullet::E_BULLET_TYPE type, float x, float y, transform_2d::E_LAYER layer = transform_2d::E_LAYER::player_bullet) const;
	public:
		bullet_factory();
		~bullet_factory();

		std::vector<bullet*>	make_bullets(bullet::E_BULLET_TYPE type, float x, float y, transform_2d::E_LAYER layer = transform_2d::E_LAYER::player_bullet) const;
	};
}

#endif //VS_BULLET_FACTORY_HPP
