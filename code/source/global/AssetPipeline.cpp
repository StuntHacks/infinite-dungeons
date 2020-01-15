#include "global/AssetPipeline.hpp"
#include "global/Console.hpp"
#include "global/graphics/Font.hpp"
#include "global/graphics/Texture.hpp"
#include "global/graphics/drawables/Model.hpp"

namespace ta {
    // textures
    ta::graphics::Texture& AssetPipeline::getTexture(const std::string& assetpath, bool smoothTexture, GLenum wrapS, GLenum wrapT, bool recache) {
        const std::string smoothness = ":" + std::string(smoothTexture ? "smooth" : "rough");

        if (m_textureCache.count(assetpath + smoothness) == 0 || recache) {
            ta::Console::log(recache ?
                                "Recaching texture \"" + assetpath + smoothness + "\"..." :
                                "Texture \"" + assetpath + smoothness + "\" not cached. Loading...",
                            "AssetPipeline.cpp");
            m_textureCache[assetpath + smoothness] = ta::graphics::Texture(assetpath, smoothTexture, wrapS, wrapT, false);
        }

        return m_textureCache[assetpath + smoothness];
    }

    bool AssetPipeline::existsTexture(const std::string& assetpath, bool smoothTexture) {
        return m_textureCache.count(assetpath + ":" + std::string(smoothTexture ? "smooth" : "rough")) > 0;
    }

    bool AssetPipeline::insertTexture(const std::string& assetpath, ta::graphics::Texture& texture, bool smoothTexture, bool overwrite) {
        if (!existsTexture(assetpath, smoothTexture) || overwrite) {
            texture.setAutoDelete(false);
            m_textureCache[assetpath + ":" + std::string(smoothTexture ? "smooth" : "rough")] = texture;
            return true;
        }

        return false;
    }

    void AssetPipeline::clearTextureCache() {
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

} /* ta */
