#pragma once

#include <Logic/Event/IEvent.h>
#include <Utils/StringHash.h>
#include <Utils/Vector2.h>
#include <Logic/AI/Pathfinding/GraphSearcher.h>


class ReceivePathEvent : public yang::IEvent
{
public:
    static constexpr const char* kEventName = "ReceivePath";
    static constexpr EventId kEventId = StringHash32(kEventName);

    ReceivePathEvent(Path&& _path, uint32_t _actorId);

    /// Get the Event ID
    EventId GetEventId() const override final { return kEventId; }

    /// Get the name of the event
    /// \return "RequestPath"
    const char* GetName() const override final { return kEventName; }
public:
    const uint32_t actorId;
    Path path;
};