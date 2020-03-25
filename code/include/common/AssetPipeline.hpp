/**
 * @file common/AssetPipeline.hpp
 * @brief Defines the AssetPipeline-class
 */
#pragma once

#include <map>
#include "common/Console.hpp"
#include "common/Singleton.hpp"
#include "common/graphics/Font.hpp"
#include "common/graphics/Texture.hpp"
#include "common/graphics/drawables/Model.hpp"
#include "common/Lock.hpp"
#include "opengl.hpp"

namespace id {
    /**
     * @brief Loads and caches assets to allow for safe, centralized usage
     *
     * The AssetPipeline works by caching every currently loaded asset with a corresponding path or id. When loading an asset from the filesystem, this will automatically be set to the path of the loaded file. When adding an already loaded Asset manually, you should set this to a unique id you want to apply to that asset. When getting assets, you can then either provide a path on the filesystem, and the AssetPipeline will return a cached version of it or load it if it isn't yet cached, or an id to a manually added asset. This identifier is referred to as the `assetpath` in parameters.
     */
    class AssetPipeline: public id::Singleton<AssetPipeline> {
    friend class id::Singleton<AssetPipeline>;
    public:
        /**
         * @brief Defines the different asset-types
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
         * @brief Clears the entire asset cache
         */
        void clear();

        /**
         * @name Texture Texture asset methods
         * @{
         */
        /**
         * @brief Gets a texture asset. If the given assetpath isn't cached yet, it will load it from the filesystem
         * @param  assetpath  The assetpath. This should be either the "id" already used by another asset, or the path to the asset you want to load from the filesystem
         * @param  recache    Whether the asset should be loaded from the filesystem regardless whether it's cached
         * @tparam LoaderType the Loader-implementation to use
         * @return            The asset
         */
        template <class LoaderType>
        id::graphics::Texture& getTexture(const std::string& assetpath, bool recache = false)  {
            static_assert(std::is_base_of<id::loaders::TextureLoader, LoaderType>::value, "Wrong Loader-type provided. Make sure you use an implementation of TextureLoader.");

            if (m_textureCache.count(assetpath) == 0 || recache) {
                id::Console::log((recache ?
                                    "Recaching texture \"" : "Texture \"")
                                + assetpath +
                                (recache ?
                                    "\"..." : "\" not cached. Loading..."),
                                "AssetPipeline.hpp:" + std::to_string(__LINE__), id::Console::White);
                id::graphics::Texture texture = id::graphics::Texture(false);
                texture.loadFromFile<LoaderType>(assetpath);
                m_textureCache[assetpath] = texture;
            }

            return m_textureCache[assetpath];
        };

        /**
         * @brief Checks whether a texture asset is already cached
         * @param  assetpath The assetpath
         * @return           `true` if the asset is already cached, `false` otherwise
         */
        bool existsTexture(const std::string& assetpath);

        /**
         * @brief Inserts an already loaded texture asset into the cache
         * @param  assetpath The assetpath. This should be a unique id for your asset
         * @param  texture   The texture asset to insert
         * @param  overwrite Whether to overwrite the previous asset with the same id, if one exists
         * @return               `true` if the insertion succeeded, `false` otherwise
         */
        bool insertTexture(const std::string& assetpath, id::graphics::Texture& texture, bool overwrite = false);

        /**
         * @brief Deletes a cached texture asset
         * @param assetpath The assetpath
         */
        void deleteTexture(const std::string& assetpath);

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
         * @param  assetpath The assetpath. This should be either the "id" already used by another asset, or the path to the asset you want to load from the filesystem regardless whether it's cached
         * @return           The asset
         */
        id::graphics::Font& getFont(const std::string& assetpath);

        /**
         * @brief Checks whether a font asset is already cached
         * @param  assetpath The assetpath
         * @return           `true` if the asset is already cached, `false` otherwise
         */
        bool existsFont(const std::string& assetpath);

         /**
          * @brief Inserts an already loaded font asset into the cache
          * @param  assetpath The assetpath. This should be a unique id for your asset
          * @param  font      The font asset to insert
          * @param  overwrite Whether to overwrite the previous asset with the same id, if one exists
          * @return               `true` if the insertion succeeded, `false` otherwise
          */
        bool insertFont(const std::string& assetpath, id::graphics::Font& font, bool overwrite = false);

        /**
         * @brief Deletes a cached font asset
         * @param assetpath The assetpath
         */
        void deleteFont(const std::string& assetpath);

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
         * @param  assetpath The assetpath. This should be either the "id" already used by another asset, or the path to the asset you want to load from the filesystem
         * @param  recache    Whether the asset should be loaded from the filesystem regardless whether it's cached
         * @return           The asset
         */
        template <class LoaderType>
        id::graphics::Model& getModel(const std::string& assetpath, bool recache = false)  {
            static_assert(std::is_base_of<id::loaders::ModelLoader, LoaderType>::value, "Wrong Loader-type provided. Make sure you use an implementation of ModelLoader.");

            if (m_modelCache.count(assetpath) == 0 || recache) {
                id::Console::log((recache ?
                                    "Recaching model \"" : "Texture \"")
                                + assetpath +
                                (recache ?
                                    "\"..." : "\" not cached. Loading..."),
                                "AssetPipeline.hpp:" + std::to_string(__LINE__), id::Console::White);
                id::graphics::Model model = id::graphics::Texture(false);
                model.loadFromFile<LoaderType>(assetpath);
                m_modelCache[assetpath] = model;
            }

            return m_modelCache[assetpath];
        };

        /**
         * @brief Checks whether a model asset is already cached
         * @param  assetpath The assetpath
         * @return           `true` if the asset is already cached, `false` otherwise
         */
        bool existsModel(const std::string& assetpath);

         /**
          * @brief Inserts an already loaded model asset into the cache
          * @param  assetpath The assetpath. This should be a unique id for your asset
          * @param  model     The model asset to insert
          * @param  overwrite Whether to overwrite the previous asset with the same id, if one exists
          * @return           `true` if the insertion succeeded, `false` otherwise
          */
        bool insertModel(const std::string& assetpath, id::graphics::Model& model, bool overwrite = false);

        /**
         * @brief Deletes a cached model asset
         * @param assetpath The assetpath
         */
        void deleteModel(const std::string& assetpath);

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
         * @param  assetpath The assetpath. This should be either the "id" already used by another asset, or the path to the asset you want to load from the filesystem regardless whether it's cached
         * @return           The asset
         */
        std::string getFile(const std::string& assetpath);

        /**
         * @brief Checks whether a generic file asset is already cached
         * @param  assetpath The assetpath
         * @return           `true` if the asset is already cached, `false` otherwise
         */
        bool existsFile(const std::string& assetpath);

         /**
          * @brief Inserts an already loaded generic file asset into the cache
          * @param  assetpath The assetpath. This should be a unique id for your asset
          * @param  file      The generic file asset to insert
          * @param  overwrite Whether to overwrite the previous asset with the same id, if one exists
          * @return           `true` if the insertion succeeded, `false` otherwise
          */
        bool insertFile(const std::string& assetpath, const std::string& file, bool overwrite = false);

        /**
         * @brief Deletes a cached generic file asset
         * @param assetpath The assetpath
         */
        void deleteFile(const std::string& assetpath);

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
         * @param  assetpath The assetpath. This should be either the "id" already used by another asset, or the path to the asset you want to load from the filesystem regardless whether it's cached
         * @return           The asset
         */
        std::wstring getWideFile(const std::string& assetpath);

        /**
         * @brief Checks whether a generic unicode file asset is already cached
         * @param  assetpath The assetpath
         * @return           `true` if the asset is already cached, `false` otherwise
         */
        bool existsWideFile(const std::string& assetpath);

         /**
          * @brief Inserts an already loaded generic unicode file asset into the cache
          * @param  assetpath The assetpath. This should be a unique id for your asset
          * @param  file      The generic unicode file asset to insert
          * @param  overwrite Whether to overwrite the previous asset with the same id, if one exists
          * @return           `true` if the insertion succeeded, `false` otherwise
          */
        bool insertWideFile(const std::string& assetpath, const std::wstring& file, bool overwrite = false);

        /**
         * @brief Deletes a cached generic unicode file asset
         * @param assetpath The assetpath
         */
        void deleteWideFile(const std::string& assetpath);

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
        std::map<std::string, id::graphics::Texture> m_textureCache;
        std::map<std::string, id::graphics::Font> m_fontCache;
        std::map<std::string, id::graphics::Model> m_modelCache;
        std::map<std::string, std::string> m_fileCache;
        std::map<std::string, std::wstring> m_wideFileCache;
    };
} /* id */
