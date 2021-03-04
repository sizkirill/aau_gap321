#pragma once
#include <string>
#include <functional>
#include <unordered_map>
#include <vector>
#include <Utils/Vector2.h>
#include <Utils/Typedefs.h>
#include <Application/Graphics/Fonts/FontString.h>

namespace yang
{
    class IGraphics;

    class DebugPanel
    {
    public:
        using ValueGetter = std::function<std::string()>;
        using ComponentSection = std::vector<std::pair<FontString, ValueGetter>>;
        using ActorSection = std::vector<std::pair<FontString, ComponentSection>>;

        DebugPanel() = default;

        void Init(std::shared_ptr<IFont> pFont);

        void Render(IGraphics* pGraphics, yang::FVec2 location);
        ActorSection& AddActorSection(Id actorId);
        ComponentSection& AddSection(const std::string& componentName, ActorSection& actorVals);
        void AttachToDebugPanel(ComponentSection& compSection, const std::string& key, ValueGetter&& valueGetter);
        void RemoveActor(Id actorId);

        void Cleanup();

    private:
        std::unordered_map<Id, std::pair<FontString, ActorSection>> m_values;
        std::shared_ptr<IFont> m_pFont = nullptr;
    };
}