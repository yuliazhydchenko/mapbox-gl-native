#pragma once

#include <mbgl/sprite/sprite_atlas.hpp>
#include <mbgl/style/layer_impl.hpp>
#include <mbgl/style/layers/symbol_layer.hpp>
#include <mbgl/style/layers/symbol_layer_properties.hpp>

namespace mbgl {
namespace style {

class SymbolLayer::Impl : public Layer::Impl {
public:
    using Layer::Impl::Impl;

    void stringifyLayout(rapidjson::Writer<rapidjson::StringBuffer>&) const override;

    SymbolLayoutProperties layout;
    SymbolPaintProperties::Cascading cascading;
};

} // namespace style
} // namespace mbgl
