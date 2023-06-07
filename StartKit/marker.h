#ifndef MARKER_H_
#define MARKER_H_

#include "lib/gb.h"


class Marker
{
private:
	Vector2 position_;
	int number_;

protected:
	static const float MARKER_RADIUS;

public:
	Marker() : Marker(0) {}
	Marker(int n, float x, float y) {
		SetNumber(n);
		SetPosition(x, y); 
	}
	Marker(int n) { SetNumber(n); }
	void SetNumber(int n) { number_ = n; }
	void SetPosition(float x, float y) { position_.x = x; position_.y = y; }
	void SetPosition(const Vector2& position) { position_ = position; }
	const Vector2& GetPosition(void) const { return position_; }
	bool IsInRange(const Vector2& position) const;
	bool IsInRange(float x, float y) const {
		Vector2 position = { x, y };
		return IsInRange(position);
	}
	virtual void Draw(void) const;

	bool operator<(const Marker& m) { return position_.x < m.GetPosition().x; }
};
#endif // MARKER_H_
