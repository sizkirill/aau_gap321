#include "DebugPanel.h"

#include <Application/Graphics/Fonts/IFont.h>
#include <Application/Graphics/IGraphics.h>
#include <cassert>

#include <Application/Graphics/Textures/ITexture.h>
#include <Application/Resources/ResourceCache.h>


void yang::DebugPanel::Init(std::shared_ptr<IFont> pFont)
{
    m_pFont = pFont;
}

void yang::DebugPanel::Render(IGraphics* pGraphics, yang::FVec2 location)
{
    FVec2 position = location;
    float offsetX = 0;
    float offsetY = 0;
    int textHeight = m_pFont->GetTextSize(std::string_view("A")).y;

    //pGraphics->SetDrawColor({ 0,0,0,127 });
    pGraphics->FillRect(yang::FRect{ location.x, location.y, 480.f, 600.f }, yang::IColor{0,0,0,127});

    for (auto& [actorId, actorComponentsPair] : m_values)
    {
        auto& [actorString, components] = actorComponentsPair;
        actorString.Render(pGraphics, position + FVec2(offsetX, offsetY), yang::IColor::kWhite);
        offsetX += 10;
        offsetY += textHeight + 2;

        for (auto& [componentName, componentValues] : components)
        {
            componentName.Render(pGraphics, position + FVec2(offsetX, offsetY), yang::IColor::kWhite);
            offsetX += 10;
            offsetY += textHeight + 2;

            for (auto& [valueName, valueGetter] : componentValues)
            {
                valueName.Render(pGraphics, position + FVec2(offsetX, offsetY), yang::IColor::kWhite);
                int localOffsetX = (int)offsetX + m_pFont->GetTextSize(valueName.m_string).x + 2;
                auto value = m_pFont->CreateFontString(valueGetter());
                value.Render(pGraphics, position + FVec2(offsetX + localOffsetX, offsetY), yang::IColor::kWhite);
                offsetY += textHeight + 2;
            }
            offsetX -= 10;
            offsetY += textHeight + 2;
        }

        offsetX -= 10;
        offsetY += textHeight + 2;
    }
}

yang::DebugPanel::ActorSection& yang::DebugPanel::AddActorSection(Id actorId)
{
    assert(m_pFont);
    return m_values.emplace(actorId, std::make_pair(m_pFont->CreateFontString("ActorID: " + std::to_string(actorId) + ": "), ActorSection())).first->second.second;
}

yang::DebugPanel::ComponentSection& yang::DebugPanel::AddSection(const std::string& componentName, ActorSection& actorVals)
{
    assert(m_pFont);
    return actorVals.emplace_back(m_pFont->CreateFontString(componentName + ": "), ComponentSection()).second;
}

void yang::DebugPanel::AttachToDebugPanel(ComponentSection& compSection, const std::string& key, ValueGetter&& valueGetter)
{
    assert(m_pFont);
    compSection.emplace_back(m_pFont->CreateFontString(key + ": "), std::move(valueGetter));
}

void yang::DebugPanel::RemoveActor(Id actorId)
{
    for (auto& [actorName, actorSection] : m_values.at(actorId).second)
    {
        actorSection.clear();
    }
    m_values.erase(actorId);
}

void yang::DebugPanel::Cleanup()
{
    m_pFont = nullptr;
    for (auto& [actorId, actorSection] : m_values)
    {
        for (auto& [fontString, componentSection] : actorSection.second)
        {
            componentSection.clear();
        }
        actorSection.second.clear();
    }
    m_values.clear();
}
