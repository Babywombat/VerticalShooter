#ifndef VS_PLAYER_HPP
#define VS_PLAYER_HPP

#include "Actor.h"

class player : public actor{
public:
	explicit player();
	~player();

	void on_update(double delta_time) override;
	void on_render(ID2D1HwndRenderTarget* render_target) override;
	void initialize(double posX, double posY) override;
};

#endif //VS_PLAYER_HPP