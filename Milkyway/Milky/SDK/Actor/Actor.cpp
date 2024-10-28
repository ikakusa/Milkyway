#include "Actor.h"
#include "../../GameData.h"

float Actor::getBlocksPerSecond() {
    return getTicksPerSecond() * *g_Data.getClientInstance()->minecraft->timer;
}
