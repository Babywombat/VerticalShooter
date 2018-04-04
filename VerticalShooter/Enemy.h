#ifndef VS_ENEMY_HPP
#define VS_ENEMY_HPP

#include "Actor.h"
namespace vs {
	class player;

	class enemy : public actor {
	private:
		player*			_player;
	public:
		enemy();
		~enemy();

		void			on_update(double delta_time) override;
		void			on_render(ID2D1HwndRenderTarget* render_target) override;
		void			initialize() override;

		void			set_player(player* player);
	};
}

#endif //VS_ENEMY_HPP