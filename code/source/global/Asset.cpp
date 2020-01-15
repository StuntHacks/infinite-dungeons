#include "global/Asset.hpp"

namespace id {
    Asset::Asset(id::AssetPipeline::Type type, const std::string& assetpath) :
    m_type(type),
    m_assetpath(assetpath) { /* do nothing */ };

    id::AssetPipeline::Type Asset::getType() {
        return m_type;
    }

    std::string& Asset::getAssetpath() {
        return m_assetpath;
    }
} /* id */
