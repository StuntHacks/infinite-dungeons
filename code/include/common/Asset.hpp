/**
 * @file common/Asset.hpp
 * @brief Defines the Asset-class
 */
#pragma once

#include "common/AssetPipeline.hpp"

namespace id {
    /**
     * @brief Contains data about an Asset
     */
    class Asset {
    public:
        /**
         * @brief Constructs the Asset given it's type and assetpath
         * @param type      The type of the Asset
         * @param assetpath The assetpath. This should be either the "id" already used by another asset, or the path to the asset you want to load
         */
        Asset(id::AssetPipeline::Type type, const std::string& assetpath);

        /**
         * @brief Returns the type of the Asset
         * @return The type
         */
        id::AssetPipeline::Type getType();

        /**
         * @brief Returns the assetpath
         * @return The assetpath or id
         */
        std::string& getAssetpath();

    private:
        /* data */
        id::AssetPipeline::Type m_type;
        std::string m_assetpath;
    };
} /* id */
