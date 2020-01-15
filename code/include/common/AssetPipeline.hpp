#pragma once

#include <map>
#include "common/Singleton.hpp"
#include "opengl.hpp"

namespace id {
    namespace graphics {
        class Font;
        class Model;
        class Texture;
    } /* graphics */

    class AssetPipeline: public id::Singleton<AssetPipeline> {
    friend class id::Singleton<AssetPipeline>;
    public:
        enum class Type {
            Texture,
            Font,
            Model,
            // Audio,
            File,
            WideFile
        };

        id::graphics::Texture& getTexture(const std::string& assetpath, bool smoothTexture = true, GLenum wrapS = GL_REPEAT, GLenum wrapT = GL_REPEAT, bool recache = false);
        bool existsTexture(const std::string& assetpath, bool smoothTexture = true);
        bool insertTexture(const std::string& assetpath, id::graphics::Texture& texture, bool smoothTexture = true, bool overwrite = false);
        void clearTextureCache();

        id::graphics::Font& getFont(const std::string& assetpath);
        bool existsFont(const std::string& assetpath);
        bool insertFont(const std::string& assetpath, id::graphics::Font& font, bool overwrite = false);
        void clearFontCache();

        id::graphics::Model& getModel(const std::string& assetpath);
        bool existsModel(const std::string& assetpath);
        bool insertModel(const std::string& assetpath, id::graphics::Model& model, bool overwrite = false);
        void clearModelCache();

        std::string getFile(const std::string& assetpath);
        bool existsFile(const std::string& assetpath);
        bool insertFile(const std::string& assetpath, const std::string& file, bool overwrite = false);
        void clearFileCache();

        std::wstring getWideFile(const std::string& assetpath);
        bool existsWideFile(const std::string& assetpath);
        bool insertWideFile(const std::string& assetpath, const std::wstring& file, bool overwrite = false);
        void clearWideFileCache();

    protected:
        virtual ~AssetPipeline();

    private:
        AssetPipeline();

        /* data */
             // "filepath:smooth|rough"
        std::map<std::string, id::graphics::Texture> m_textureCache;
        std::map<std::string, id::graphics::Font> m_fontCache;
        std::map<std::string, id::graphics::Model> m_modelCache;
        std::map<std::string, std::string> m_fileCache;
        std::map<std::string, std::wstring> m_wideFileCache;
    };
} /* id */
