/**
 * @file common/AssetPipeline.hpp
 * @brief Defines the AssetPipeline-class
 */
#pragma once

#include <map>
#include "common/Singleton.hpp"
#include "switch/lock.hpp"
#include "opengl.hpp"

namespace id {
    /**
     * @brief Contains anything graphics-related
     */
    namespace graphics {
        class Font;
        class Model;
        class Texture;
    } /* graphics */

    /**
     * @brief Loads and caches assets to allow for safe, centralized usage
     */
    class AssetPipeline: public id::Singleton<AssetPipeline> {
    friend class id::Singleton<AssetPipeline>;
    public:
        /**
         * @brief Defines the different Asset-types
         */
        enum class Type {
            Texture, ///< Texture assets
            Font,    ///< Font assets
            Model,   ///< 3D-model assets
            // Audio,   ///< Audio assets
            File,    ///< Generic file assets
            WideFile ///< Generic unicode file assets
        };

        /**
         * @name Texture Texture asset methods
         * @{
         */
        /**
         * @brief Gets a texture asset. If the given assetpath isn't cached yet, it will load it from the filesystem
         * @param  assetpath     The assetpath. This should be either the "id" already used by another asset, or the path to the asset you want to load
         * @param  smoothTexture Whether to smooth the texture or not
         * @param  wrapS         The s-wrap of the texture
         * @param  wrapT         The t-wrap of the texture
         * @param  recache       Whether the asset should be loaded from the filesystem regardless whether it's cached
         * @return               The asset
         */
        id::graphics::Texture& getTexture(const std::string& assetpath, bool smoothTexture = true, GLenum wrapS = GL_REPEAT, GLenum wrapT = GL_REPEAT, bool recache = false);

        /**
         * @brief Checks whether a texture asset is already cached
         * @param  assetpath     The assetpath
         * @param  smoothTexture Whether to look for a smoothed texture or not
         * @return               `true` if the asset is already cached, `false` otherwise
         */
        bool existsTexture(const std::string& assetpath, bool smoothTexture = true);

        /**
         * @brief Inserts an already loaded texture asset into the cache
         * @param  assetpath     The assetpath. This should be a unique id for your asset
         * @param  texture       The texture asset to insert
         * @param  smoothTexture Whether the texture is smooth or not
         * @param  overwrite     Whether to overwrite the previous asset with the same id, if one exists
         * @return               `true` if the insertion succeeded, `false` otherwise
         */
        bool insertTexture(const std::string& assetpath, id::graphics::Texture& texture, bool smoothTexture = true, bool overwrite = false);

        /**
         * @brief Clears the texture asset cache
         */
        void clearTextureCache();
        /**@}*/

        /**
         * @name Font Font asset methods
         * @{
         */
        /**
         * @brief Gets a font file asset. If the given assetpath isn't cached yet, it will load it from the filesystem
         * @param  assetpath     The assetpath. This should be either the "id" already used by another asset, or the path to the asset you want to load from the filesystem regardless whether it's cached
         * @return               The asset
         */
        id::graphics::Font& getFont(const std::string& assetpath);

        /**
         * @brief Checks whether a font asset is already cached
         * @param  assetpath     The assetpath
         * @return               `true` if the asset is already cached, `false` otherwise
         */
        bool existsFont(const std::string& assetpath);

         /**
          * @brief Inserts an already loaded font asset into the cache
          * @param  assetpath     The assetpath. This should be a unique id for your asset
          * @param  font          The font asset to insert
          * @param  overwrite     Whether to overwrite the previous asset with the same id, if one exists
          * @return               `true` if the insertion succeeded, `false` otherwise
          */
        bool insertFont(const std::string& assetpath, id::graphics::Font& font, bool overwrite = false);

        /**
         * @brief Clears the font asset cache
         */
        void clearFontCache();
        /**@}*/

        /**
         * @name Model Model asset methods
         * @{
         */
        /**
         * @brief Gets a model asset. If the given assetpath isn't cached yet, it will load it from the filesystem
         * @param  assetpath     The assetpath. This should be either the "id" already used by another asset, or the path to the asset you want to load from the filesystem regardless whether it's cached
         * @return               The asset
         */
        id::graphics::Model& getModel(const std::string& assetpath);

        /**
         * @brief Checks whether a model asset is already cached
         * @param  assetpath     The assetpath
         * @return               `true` if the asset is already cached, `false` otherwise
         */
        bool existsModel(const std::string& assetpath);

         /**
          * @brief Inserts an already loaded model asset into the cache
          * @param  assetpath     The assetpath. This should be a unique id for your asset
          * @param  model         The model asset to insert
          * @param  overwrite     Whether to overwrite the previous asset with the same id, if one exists
          * @return               `true` if the insertion succeeded, `false` otherwise
          */
        bool insertModel(const std::string& assetpath, id::graphics::Model& model, bool overwrite = false);

        /**
         * @brief Clears the model asset cache
         */
        void clearModelCache();
        /**@}*/

        /**
         * @name File File asset methods
         * @{
         */
        /**
         * @brief Gets a generic file asset. If the given assetpath isn't cached yet, it will load it from the filesystem
         * @param  assetpath     The assetpath. This should be either the "id" already used by another asset, or the path to the asset you want to load from the filesystem regardless whether it's cached
         * @return               The asset
         */
        std::string getFile(const std::string& assetpath);

        /**
         * @brief Checks whether a generic file asset is already cached
         * @param  assetpath     The assetpath
         * @return               `true` if the asset is already cached, `false` otherwise
         */
        bool existsFile(const std::string& assetpath);

         /**
          * @brief Inserts an already loaded generic file asset into the cache
          * @param  assetpath     The assetpath. This should be a unique id for your asset
          * @param  file          The generic file asset to insert
          * @param  overwrite     Whether to overwrite the previous asset with the same id, if one exists
          * @return               `true` if the insertion succeeded, `false` otherwise
          */
        bool insertFile(const std::string& assetpath, const std::string& file, bool overwrite = false);

        /**
         * @brief Clears the generic file asset cache
         */
        void clearFileCache();
        /**@}*/

        /**
         * @name WideFile Generic unicode file asset methods
         * @{
         */
        /**
         * @brief Gets a generic unicode file asset. If the given assetpath isn't cached yet, it will load it from the filesystem
         * @param  assetpath     The assetpath. This should be either the "id" already used by another asset, or the path to the asset you want to load from the filesystem regardless whether it's cached
         * @return               The asset
         */
        std::wstring getWideFile(const std::string& assetpath);

        /**
         * @brief Checks whether a generic unicode file asset is already cached
         * @param  assetpath     The assetpath
         * @return               `true` if the asset is already cached, `false` otherwise
         */
        bool existsWideFile(const std::string& assetpath);

         /**
          * @brief Inserts an already loaded generic unicode file asset into the cache
          * @param  assetpath     The assetpath. This should be a unique id for your asset
          * @param  file          The generic unicode file asset to insert
          * @param  overwrite     Whether to overwrite the previous asset with the same id, if one exists
          * @return               `true` if the insertion succeeded, `false` otherwise
          */
        bool insertWideFile(const std::string& assetpath, const std::wstring& file, bool overwrite = false);

        /**
         * @brief Clears the generic unicode file asset cache
         */
        void clearWideFileCache();
        /**@}*/

    protected:
        /**
         * @brief Destructor
         */
        virtual ~AssetPipeline();

    private:
        AssetPipeline();

        /* data */
        id::Mutex m_mutex;
             // "filepath:smooth|rough"
        std::map<std::string, id::graphics::Texture> m_textureCache;
        std::map<std::string, id::graphics::Font> m_fontCache;
        std::map<std::string, id::graphics::Model> m_modelCache;
        std::map<std::string, std::string> m_fileCache;
        std::map<std::string, std::wstring> m_wideFileCache;
    };
} /* id */
