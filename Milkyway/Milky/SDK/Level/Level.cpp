#include "Level.h"

std::vector<Actor*> Level::getRuntimeActorList() {
	std::vector<Actor*> listOut;
	if (this) CallVFunc<278, decltype(&listOut)>(this, &listOut);
	return listOut;
}