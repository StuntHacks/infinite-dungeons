#pragma once

#include "global/AssetPipeline.hpp"

namespace id {
    class Asset {
    public:
        Asset(id::AssetPipeline::Type type, const std::string& assetpath);
        id::AssetPipeline::Type getType();
        std::string& getAssetpath();

    private:
        /* data */
        id::AssetPipeline::Type m_type;
        std::string m_assetpath;
    };
} /* id */
