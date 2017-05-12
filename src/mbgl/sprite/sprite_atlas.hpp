#pragma once

#include <mbgl/gl/texture.hpp>
#include <mbgl/util/noncopyable.hpp>
#include <mbgl/util/optional.hpp>
#include <mbgl/style/image.hpp>

#include <mapbox/shelf-pack.hpp>

#include <string>
#include <set>
#include <unordered_map>
#include <array>
#include <memory>

namespace mbgl {

namespace gl {
class Context;
} // namespace gl

class SpriteAtlasElement {
public:
    SpriteAtlasElement(mapbox::Bin, const style::Image::Impl&, uint16_t padding);

    bool sdf;
    float pixelRatio;
    std::array<float, 2> size;
    std::array<uint16_t, 2> tl;
    std::array<uint16_t, 2> br;
};

using IconMap = std::unordered_map<std::string, SpriteAtlasElement>;
using IconDependencies = std::set<std::string>;

class IconRequestor {
public:
    virtual void onIconsAvailable(IconMap) = 0;
};

class SpriteAtlas : public util::noncopyable {
public:
    SpriteAtlas(float pixelRatio);
    ~SpriteAtlas();

    void onSpriteLoaded();

    bool isLoaded() const {
        return loaded;
    }

    void dumpDebugLogs() const;

    const style::Image::Impl* getImage(const std::string&) const;
    void addImage(Immutable<style::Image::Impl>);
    void removeImage(const std::string&);

    void getIcons(IconRequestor&, IconDependencies);
    void removeRequestor(IconRequestor&);

    optional<SpriteAtlasElement> getIcon(const std::string& name);
    optional<SpriteAtlasElement> getPattern(const std::string& name);

    // Binds the atlas texture to the GPU, and uploads data if it is out of date.
    void bind(bool linear, gl::Context&, gl::TextureUnit unit);

    // Uploads the texture to the GPU to be available when we need it. This is a lazy operation;
    // the texture is only bound when the data is out of date (=dirty).
    void upload(gl::Context&, gl::TextureUnit unit);

    Size getPixelSize() const;

    // Only for use in tests.
    const PremultipliedImage& getAtlasImage() const {
        return image;
    }

private:
    const uint16_t padding;
    bool loaded = false;

    struct Entry {
        Immutable<style::Image::Impl> image;

        // One sprite image might be used as both an icon image and a pattern image. If so,
        // it must have two distinct entries in the texture. The one for the icon image has
        // a single pixel transparent border, and the one for the pattern image has a single
        // pixel border wrapped from the opposite side.
        optional<mapbox::Bin> iconBin;
        optional<mapbox::Bin> patternBin;
    };

    optional<SpriteAtlasElement> getImage(const std::string& name, optional<mapbox::Bin> Entry::*bin);
    void copy(const Entry&, optional<mapbox::Bin> Entry::*bin);
    
    IconMap buildIconMap();

    std::unordered_map<std::string, Entry> entries;
    mapbox::ShelfPack shelfPack;
    PremultipliedImage image;
    mbgl::optional<gl::Texture> texture;
    bool dirty;
    
    std::set<IconRequestor*> requestors;
    IconMap icons;
};

} // namespace mbgl
