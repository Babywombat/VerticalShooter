#ifndef VS_BULLET_FACTORY_HPP
#define VS_BULLET_FACTORY_HPP
#include "Bullet.h"

namespace vs {
	class bullet_factory {
	public:
		enum E_BULLET_TYPE {
			normal = 0
		};

		bullet_factory();
		~bullet_factory();

		bullet* make_bullet(E_BULLET_TYPE type, float x, float y) const;
	};
}

#endif //VS_BULLET_FACTORY_HPP
