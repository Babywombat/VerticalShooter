#ifndef VS_ENEMY_FACTORY
#define VS_ENEMY_FACTORY
#include "Enemy.h"

namespace vs {
	class enemy_factory {
	public:
		enum E_ENEMY_TYPE {
			normal = 0
		};

		enemy_factory();
		~enemy_factory();

		enemy* make_enemy(E_ENEMY_TYPE type, float x, float y) const;
	};
}

#endif //VS_ENEMY_FACTORY