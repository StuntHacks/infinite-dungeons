#include "global/Asset.hpp"

namespace ta {
    Asset::Asset(ta::AssetPipeline::Type type, const std::string& assetpath) :
    m_type(type),
    m_assetpath(assetpath) { /* do nothing */ };

    ta::AssetPipeline::Type Asset::getType() {
        return m_type;
    }

    std::string& Asset::getAssetpath() {
        return m_assetpath;
    }
} /* ta */
