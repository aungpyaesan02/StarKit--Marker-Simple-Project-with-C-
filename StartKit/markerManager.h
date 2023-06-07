#pragma once

#include <list>

class Marker;

class MarkerManager 
{
private:
	std::list<Marker*> markers;
	int no = 0;

public:
	~MarkerManager();
	void CreateMarker(float x, float y);
	void Draw(void);
	bool DeleteMarker(const float& x,const float& y);
};