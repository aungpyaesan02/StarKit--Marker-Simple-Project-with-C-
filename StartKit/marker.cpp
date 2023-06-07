#include "marker.h"
#include <cstdio>

const float Marker::MARKER_RADIUS = 16.0f;


bool Marker::IsInRange(const Vector2& position) const
{
	float xlen = position.x - position_.x;
	float ylen = position.y - position_.y;
	float sqlen = xlen * xlen + ylen * ylen;

	return sqlen <= MARKER_RADIUS * MARKER_RADIUS;
}

void Marker::Draw(void) const
{
	char buf[4];
	sprintf(buf, "%d", number_);
	float offset_x = gb_fontGetStringWidth(buf) * 0.5f - 1;
	float offset_y = gb_fontGetHeight() * 0.5f - 1;
	gb_fontSetPos(position_.x - offset_x, position_.y - offset_y);
	gb_spriteBegin(SPRITE_ALPHABLEND);
	gb_fontDrawString(buf);
	gb_spriteEnd();
	gb_drawCircle(position_.x, position_.y, MARKER_RADIUS);
}
