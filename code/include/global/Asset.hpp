#pragma once

#include "global/AssetPipeline.hpp"

namespace ta {
    class Asset {
    public:
        Asset(ta::AssetPipeline::Type type, const std::string& assetpath);
        ta::AssetPipeline::Type getType();
        std::string& getAssetpath();

    private:
        /* data */
        ta::AssetPipeline::Type m_type;
        std::string m_assetpath;
    };
} /* ta */
