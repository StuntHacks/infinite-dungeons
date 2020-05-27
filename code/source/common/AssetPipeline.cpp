#include "common/AssetPipeline.hpp"

namespace id {
    void AssetPipeline::clear() {
        // clearModelCache();
        clearTextureCache();
        // clearFontCache();
        // // clearAudioCache();
        // clearFileCache();
        // clearWideFileCache();
    }

    // textures
    bool AssetPipeline::existsTexture(const std::string& assetpath) {
        return m_textureCache.count(assetpath) > 0;
    }

    bool AssetPipeline::insertTexture(const std::string& assetpath, id::graphics::Texture& texture, bool overwrite) {
        if (!existsTexture(assetpath) || overwrite) {
            id::Lock lock(m_mutex);
            texture.setAutoDelete(false);
            m_textureCache[assetpath] = texture;
            return true;
        }

        return false;
    }

    void AssetPipeline::deleteTexture(const std::string& assetpath) {
        if (existsTexture(assetpath)) {
            id::Lock lock(m_mutex);
            m_textureCache[assetpath].setAutoDelete(true);
            m_textureCache.erase(assetpath);
        }
    }

    void AssetPipeline::clearTextureCache() {
        id::Lock lock(m_mutex);
        for (auto& texture: m_textureCache) {
            texture.second.deleteThis();
        }

        m_textureCache.clear();
    }

    // models
    bool AssetPipeline::existsModel(const std::string& assetpath) {
        return m_textureCache.count(assetpath) > 0;
    }

    bool AssetPipeline::insertModel(const std::string& assetpath, id::graphics::Model& model, bool overwrite) {
        if (!existsModel(assetpath) || overwrite) {
            id::Lock lock(m_mutex);
            model.setAutoDelete(false);
            m_modelCache[assetpath] = model;
            return true;
        }

        return false;
    }

    void AssetPipeline::deleteModel(const std::string& assetpath) {
        if (existsTexture(assetpath)) {
            id::Lock lock(m_mutex);
            m_modelCache[assetpath].setAutoDelete(true);
            m_modelCache.erase(assetpath);
        }
    }

    void AssetPipeline::clearModelCache() {
        id::Lock lock(m_mutex);
        for (auto& model: m_modelCache) {
            model.second.deleteThis();
        }

        m_textureCache.clear();
    }

    // protected methods
    AssetPipeline::~AssetPipeline() {
        clearTextureCache();
        clearModelCache();
    }

    // private methods
    AssetPipeline::AssetPipeline() { /* do nothing */ }

} /* id */
