#pragma once

#include <Logic/Event/IEvent.h>
#include <Utils/StringHash.h>
#include <Utils/Vector2.h>


class RequestPathEvent : public yang::IEvent
{
public:
    static constexpr const char* kEventName = "RequestPath";
    static constexpr EventId kEventId = StringHash32(kEventName);

    RequestPathEvent(yang::FVec2 start, yang::FVec2 end, uint32_t actorId);

    /// Get the Event ID
    EventId GetEventId() const override final { return kEventId; }

    /// Get the name of the event
    /// \return "RequestPath"
    const char* GetName() const override final { return kEventName; }
public:
    const yang::FVec2 pathStart;
    const yang::FVec2 pathEnd;
    const uint32_t actorId;
};