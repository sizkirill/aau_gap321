#pragma once
#include <Logic/Map/TiledMap.h>
#include <Utils/Math.h>
#include <array>
#include <optional>
#include <vector>

class BasicPathfindingMap : public yang::TiledMap
{
public:
    enum class DebugValue
    {
        kPath,
        kOpenSet,
        kClosedSet,
        kMaxValues
    };

    static constexpr size_t kNeighborsCount = 8;
    static constexpr float kDiagonalWeightMultiplier = Math::Sqrt(2.f);

    std::array<std::optional<std::pair<size_t, float>>, kNeighborsCount> GetNeighbors(size_t tileIndex) const;
    void SetDebugValue(size_t tileIndex, DebugValue value);
    virtual bool LoadMap(const char* filepath) override final;
    void ResetDebugInfo();
private:
    static constexpr const char* kDebugLayerName = "DebugLayer";
    static constexpr const char* kGroundLayerName = "GroundLayer";

    static constexpr const char* kOpenSetTileName = "openSet";
    static constexpr const char* kClosedSetTileName = "closedSet";
    static constexpr const char* kPathTileName = "path";

    std::vector<std::optional<float>> m_weights;
    size_t m_debugLayerIndex;
    size_t m_groundLayerIndex;

    size_t m_debugTileIndices[static_cast<size_t>(DebugValue::kMaxValues)];
};