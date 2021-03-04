#include "RequestPathEvent.h"
#include <Logic/AI/Pathfinding/GraphSearcher.h>

RequestPathEvent::RequestPathEvent(yang::FVec2 start, yang::FVec2 end, uint32_t actorId)
    :pathStart(start)
    ,pathEnd(end)
    ,actorId(actorId)
{
}
