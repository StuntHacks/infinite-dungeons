#include "common/AssetPipeline.hpp"
#include "common/loaders/implementations/ImageLoader.hpp"

namespace id {
    void AssetPipeline::clear() {
        clearTextureCache();
        // clearFontCache();
        clearModelCache();
        // // clearAudioCache();
        clearFileCache();
        clearWideFileCache();
        clearShaderCache();
    }

    // textures
    id::graphics::Texture& AssetPipeline::getTexture(const std::string& assetpath, bool recache) {
        return getTexture<id::loaders::ImageLoader>(assetpath, recache);
    }

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
        return m_modelCache.count(assetpath) > 0;
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
        if (existsModel(assetpath)) {
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

        m_modelCache.clear();
    }

    // files
    std::string AssetPipeline::getFile(const std::string& assetpath, bool recache) {
        if (m_fileCache.count(assetpath) == 0 || recache) {
            id::Console::log((recache ?
                                "Recaching file \"" : "File \"")
                            + assetpath +
                            (recache ?
                                "\"..." : "\" not cached. Loading..."),
                            "AssetPipeline.hpp:" + std::to_string(__LINE__), id::Console::White);

            #if defined(__SWITCH__)
                std::ifstream file("romfs:/" + assetpath);
            #elif defined(__PC__)
                std::ifstream file("./romfs/" + assetpath);
            #endif
            std::string buffer((std::istreambuf_iterator<char>(file)),
                                std::istreambuf_iterator<char>());
            m_fileCache[assetpath] = buffer;
        }

        return m_fileCache[assetpath];
    }

    bool AssetPipeline::existsFile(const std::string& assetpath) {
        return m_fileCache.count(assetpath) > 0;
    }

    bool AssetPipeline::insertFile(const std::string& assetpath, const std::string& file, bool overwrite) {
        if (!existsFile(assetpath) || overwrite) {
            id::Lock lock(m_mutex);
            m_fileCache[assetpath] = file;
            return true;
        }

        return false;
    }

    void AssetPipeline::deleteFile(const std::string& assetpath) {
        if (existsFile(assetpath)) {
            id::Lock lock(m_mutex);
            m_fileCache.erase(assetpath);
        }
    }

    void AssetPipeline::clearFileCache() {
        id::Lock lock(m_mutex);
        m_fileCache.clear();
    }

    // wide files
    std::wstring AssetPipeline::getWideFile(const std::string& assetpath, bool recache) {
        if (m_wideFileCache.count(assetpath) == 0 || recache) {
            id::Console::log((recache ?
                                "Recaching wide file \"" : "Wide file \"")
                            + assetpath +
                            (recache ?
                                "\"..." : "\" not cached. Loading..."),
                            "AssetPipeline.hpp:" + std::to_string(__LINE__), id::Console::White);
            #if defined(__SWITCH__)
                std::wifstream file("romfs:/" + assetpath);
            #elif defined(__PC__)
                std::wifstream file("./romfs/" + assetpath);
            #endif

            std::wstring buffer((std::istreambuf_iterator<wchar_t>(file)),
                                std::istreambuf_iterator<wchar_t>());
            m_wideFileCache[assetpath] = buffer;
        }

        return m_wideFileCache[assetpath];
    }

    bool AssetPipeline::existsWideFile(const std::string& assetpath) {
        return m_wideFileCache.count(assetpath) > 0;
    }

    bool AssetPipeline::insertWideFile(const std::string& assetpath, const std::wstring& file, bool overwrite) {
        if (!existsWideFile(assetpath) || overwrite) {
            id::Lock lock(m_mutex);
            m_wideFileCache[assetpath] = file;
            return true;
        }

        return false;
    }

    void AssetPipeline::deleteWideFile(const std::string& assetpath) {
        if (existsWideFile(assetpath)) {
            id::Lock lock(m_mutex);
            m_wideFileCache.erase(assetpath);
        }
    }

    void AssetPipeline::clearWideFileCache() {
        id::Lock lock(m_mutex);
        m_wideFileCache.clear();
    }

    // shaders
    id::graphics::ShaderProgram& AssetPipeline::getShader(const std::string& path, bool recache) {

    }

    bool AssetPipeline::existsShader(const std::string& path) {
        return m_shaderCache.count(path) > 0;
    }

    bool AssetPipeline::insertShader(const std::string& path, id::graphics::ShaderProgram& shader, bool overwrite) {
        if (!existsShader(path) || overwrite) {
            id::Lock lock(m_mutex);
            shader.setAutoDelete(false);
            m_shaderCache[path] = shader;
            return true;
        }

        return false;
    }

    void AssetPipeline::deleteShader(const std::string& path) {
        if (existsShader(path)) {
            id::Lock lock(m_mutex);
            m_shaderCache[path].setAutoDelete(true);
            m_shaderCache.erase(path);
        }
    }

    void AssetPipeline::clearShaderCache() {
        id::Lock lock(m_mutex);
        for (auto& shader: m_shaderCache) {
            shader.second.deleteThis();
        }

        m_shaderCache.clear();
    }

    // protected methods
    AssetPipeline::~AssetPipeline() {
        clear();
    }

    // private methods
    AssetPipeline::AssetPipeline() { /* do nothing */ }

} /* id */
