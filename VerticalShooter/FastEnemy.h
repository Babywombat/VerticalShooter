#ifndef VS_FAST_ENEMY_HPP
#define VS_FAST_ENEMY_HPP
#include "Enemy.h"

namespace vs {
	class fast_enemy : public enemy {
		ID2D1PathGeometry*					_geometry;
	public:
		fast_enemy(ID2D1PathGeometry* geometry);
		~fast_enemy();

		void								on_render(ID2D1HwndRenderTarget* render_target) override;
		void								initialize() override;
		E_ENEMY_TYPE						get_type() const override;
	};
}

#endif //VS_FAST_ENEMY_HPP
