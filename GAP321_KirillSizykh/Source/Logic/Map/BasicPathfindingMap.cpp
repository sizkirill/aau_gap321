#include "BasicPathfindingMap.h"
#include <Utils/Vector2.h>
#include <Utils/Math.h>
using yang::TiledMap;

std::array<std::optional<std::pair<size_t, float>>, BasicPathfindingMap::kNeighborsCount> BasicPathfindingMap::GetNeighbors(size_t tileIndex) const
{
    auto tileCoords = GetCoordsFromIndex(tileIndex);
    size_t neighborCount = 0;
    std::array<std::optional<std::pair<size_t, float>>, kNeighborsCount> retVal;

    for (int x = (int)(tileCoords.x) - 1; x < (int)(tileCoords.x) + 2; ++x)
    {
        for (int y = (int)(tileCoords.y) - 1; y < (int)(tileCoords.y) + 2; ++y)
        {
            if (x < 0 || y < 0 || x >= m_mapData.m_mapWidth || y >= m_mapData.m_mapHeight)
            {
                retVal[neighborCount] = {};
                ++neighborCount;
                continue;
            }

            if (x == tileCoords.x && y == tileCoords.y)
            {
                continue;
            }

            size_t tileIndex = GetIndexFromCoords(yang::IVec2(x, y));

            // Hardcoded 0. Base layer basically
            auto& maybeWeight = m_weights[GetTileIdFromIndex(m_groundLayerIndex, tileIndex)];

            if (maybeWeight)
            {
                float weight = *maybeWeight;

                if (x != tileCoords.x && y != tileCoords.y)
                {
                    weight *= kDiagonalWeightMultiplier;
                }

                retVal[neighborCount] = { tileIndex, weight };
            }
            else
            {
                retVal[neighborCount] = {};
            }
                
            ++neighborCount;
        }
    }

    return retVal;
}

void BasicPathfindingMap::SetDebugValue(size_t tileIndex, DebugValue value)
{
    // Hardcoded 2 for the Debug draw layer
    SetTileIdAtIndex(m_debugLayerIndex, tileIndex, m_debugTileIndices[static_cast<size_t>(value)]);
}

bool BasicPathfindingMap::LoadMap(const char* filepath)
{
    bool success = yang::TiledMap::LoadMap(filepath);

    if (!success)
    {
        return false;
    }

    for (auto& tileset : m_tilesetData)
    {
        for (int i = 0; i < tileset.GetTileCount(); ++i)
        {
            m_weights.push_back(tileset.GetProperty<float>(i, "weight"));
            
            auto maybeTileName = tileset.GetProperty<std::string>(i, "name");

            if (maybeTileName)
            {
                if (*maybeTileName == kClosedSetTileName)
                {
                    m_debugTileIndices[static_cast<size_t>(DebugValue::kClosedSet)] = static_cast<size_t>(i) + tileset.GetFirstGid();
                }
                else if (*maybeTileName == kOpenSetTileName)
                {
                    m_debugTileIndices[static_cast<size_t>(DebugValue::kOpenSet)] = static_cast<size_t>(i) + tileset.GetFirstGid();
                }
                else if (*maybeTileName == kPathTileName)
                {
                    m_debugTileIndices[static_cast<size_t>(DebugValue::kPath)] = static_cast<size_t>(i) + tileset.GetFirstGid();
                }
            }
        }
    }

    m_debugLayerIndex = GetLayerIndex(kDebugLayerName);
    m_groundLayerIndex = GetLayerIndex(kGroundLayerName);


    return true;

}

void BasicPathfindingMap::ResetDebugInfo()
{
    // Hardcoded 2 for debug draw layer
    for (auto& tile : m_mapData.m_layerData[m_debugLayerIndex].m_tileData)
    {
        tile.m_id = 0;
    }

}
