#include "markerManager.h"
#include "marker.h"
#include <algorithm>

MarkerManager::~MarkerManager()
{
	for (Marker *m : markers)
	{
		delete m;
	}
}

void MarkerManager::CreateMarker(float x, float y)
{
	markers.emplace_back(new Marker(no++, x, y));
}

void MarkerManager::Draw(void)
{
	for (Marker *m : markers)
	{
		m->Draw();
	}

}

bool MarkerManager::DeleteMarker(const float & x, const float & y)
{
	auto it = std::find_if(markers.begin(), markers.end(),
		[=](const Marker *m) { return m->IsInRange(x, y); });

	if (it != markers.end())
	{	
		delete *it;
		markers.erase(it);
		return true;
	}

	return false;
}
