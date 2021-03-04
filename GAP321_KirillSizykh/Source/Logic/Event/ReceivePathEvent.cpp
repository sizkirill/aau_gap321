#include "ReceivePathEvent.h"

ReceivePathEvent::ReceivePathEvent(Path&& _path, uint32_t _actorId)
    :path(std::move(_path))
    ,actorId(_actorId)
{
}
