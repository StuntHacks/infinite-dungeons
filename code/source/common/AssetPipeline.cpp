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
            texture.second.deleteTexture();
        }

        m_textureCache.clear();
    }

    // protected methods
    AssetPipeline::~AssetPipeline() {
        clearTextureCache();
    }

    // private methods
    AssetPipeline::AssetPipeline() { /* do nothing */ }

} /* id */
