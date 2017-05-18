#include <mbgl/geometry/anchor.hpp>
#include <mbgl/style/image_impl.hpp>
#include <mbgl/test/util.hpp>
#include <mbgl/text/quads.hpp>
#include <mbgl/text/shaping.hpp>
#include <mbgl/text/glyph.hpp>
#include <mbgl/style/layers/symbol_layer_properties.hpp>

using namespace mbgl;
using namespace mbgl::style;

TEST(getIconQuads, normal) {
    SymbolLayoutProperties::Evaluated layout;
    Anchor anchor(2.0, 3.0, 0.0, 0.5f, 0);
    SpriteAtlasElement image = {
        Rect<uint16_t>( 0, 0, 15, 11 ),
        style::Image::Impl("test", PremultipliedImage({1,1}), 1.0),
        1
    };

    auto shapedIcon = PositionedIcon::shapeIcon(image, {{ -6.5f, -4.5f }}, 0);

    GeometryCoordinates line;
    Shaping shapedText;

    SymbolQuad quad =
        getIconQuad(anchor, shapedIcon, line, layout, 16.0f, SymbolPlacementType::Point, shapedText, 1.0);

    EXPECT_EQ(quad.anchorPoint.x, 2);
    EXPECT_EQ(quad.anchorPoint.y, 3);
    EXPECT_EQ(quad.tl.x, -8);
    EXPECT_EQ(quad.tl.y, -6);
    EXPECT_EQ(quad.tr.x, -5);
    EXPECT_EQ(quad.tr.y, -6);
    EXPECT_EQ(quad.bl.x, -8);
    EXPECT_EQ(quad.bl.y, -3);
    EXPECT_EQ(quad.br.x, -5);
    EXPECT_EQ(quad.br.y, -3);
    EXPECT_EQ(quad.anchorAngle, 0.0f);
    EXPECT_EQ(quad.glyphAngle, 0.0f);
    EXPECT_EQ(quad.minScale, 0.5f);
}

TEST(getIconQuads, style) {
    Anchor anchor(0.0, 0.0, 0.0, 0.5f, 0);
    SpriteAtlasElement image = {
        Rect<uint16_t>( 0, 0, 20, 20 ),
        style::Image::Impl("test", PremultipliedImage({1,1}), 1.0),
        1
    };

    auto shapedIcon = PositionedIcon::shapeIcon(image, {{ -9.5f, -9.5f }}, 0);

    GeometryCoordinates line;
    Shaping shapedText;
    shapedText.top = -10.0f;
    shapedText.bottom = 30.0f;
    shapedText.left = -60.0f;
    shapedText.right = 20.0f;
    shapedText.positionedGlyphs.emplace_back(PositionedGlyph(32, 0.0f, 0.0f, 0));

    // none
    {
        SymbolLayoutProperties::Evaluated layout;
        SymbolQuad quad =
            getIconQuad(anchor, shapedIcon, line, layout, 12.0f, SymbolPlacementType::Point, shapedText, 1.0);

        EXPECT_EQ(quad.anchorPoint.x, 0);
        EXPECT_EQ(quad.anchorPoint.y, 0);
        EXPECT_EQ(quad.tl.x, -11);
        EXPECT_EQ(quad.tl.y, -11);
        EXPECT_EQ(quad.tr.x, -8);
        EXPECT_EQ(quad.tr.y, -11);
        EXPECT_EQ(quad.bl.x, -11);
        EXPECT_EQ(quad.bl.y, -8);
        EXPECT_EQ(quad.br.x, -8);
        EXPECT_EQ(quad.br.y, -8);
        EXPECT_EQ(quad.anchorAngle, 0.0f);
        EXPECT_EQ(quad.glyphAngle, 0.0f);
        EXPECT_EQ(quad.minScale, 0.5f);
    }

    // width
    {
        SymbolLayoutProperties::Evaluated layout;
        layout.get<TextSize>() = 24.0f;
        layout.get<IconTextFit>() = IconTextFitType::Width;
        SymbolQuad quad =
            getIconQuad(anchor, shapedIcon, line, layout, 24.0f, SymbolPlacementType::Point, shapedText, 1.0);

        EXPECT_EQ(quad.tl.x, -60);
        EXPECT_EQ(quad.tl.y, 8.5);
        EXPECT_EQ(quad.tr.x, 20);
        EXPECT_EQ(quad.tr.y, 8.5);
        EXPECT_EQ(quad.bl.x, -60);
        EXPECT_EQ(quad.bl.y, 11.5);
        EXPECT_EQ(quad.br.x, 20);
        EXPECT_EQ(quad.br.y, 11.5);
    }

    // width x textSize
    {
        SymbolLayoutProperties::Evaluated layout;
        layout.get<TextSize>() = 12.0f;
        layout.get<IconTextFit>() = IconTextFitType::Width;
        SymbolQuad quad =
            getIconQuad(anchor, shapedIcon, line, layout, 12.0f, SymbolPlacementType::Point, shapedText, 1.0);

        EXPECT_EQ(quad.tl.x, -30);
        EXPECT_EQ(quad.tl.y, 3.5);
        EXPECT_EQ(quad.tr.x, 10);
        EXPECT_EQ(quad.tr.y, 3.5);
        EXPECT_EQ(quad.bl.x, -30);
        EXPECT_EQ(quad.bl.y, 6.5);
        EXPECT_EQ(quad.br.x, 10);
        EXPECT_EQ(quad.br.y, 6.5);
    }

    // width x textSize + padding
    {
        SymbolLayoutProperties::Evaluated layout;
        layout.get<TextSize>() = 12.0f;
        layout.get<IconTextFit>() = IconTextFitType::Width;
        layout.get<IconTextFitPadding>()[0] = 5.0f;
        layout.get<IconTextFitPadding>()[1] = 10.0f;
        layout.get<IconTextFitPadding>()[2] = 5.0f;
        layout.get<IconTextFitPadding>()[3] = 10.0f;
        SymbolQuad quad =
            getIconQuad(anchor, shapedIcon, line, layout, 12.0f, SymbolPlacementType::Point, shapedText, 1.0);

        EXPECT_EQ(quad.tl.x, -40);
        EXPECT_EQ(quad.tl.y, -1.5);
        EXPECT_EQ(quad.tr.x, 20);
        EXPECT_EQ(quad.tr.y, -1.5);
        EXPECT_EQ(quad.bl.x, -40);
        EXPECT_EQ(quad.bl.y, 11.5);
        EXPECT_EQ(quad.br.x, 20);
        EXPECT_EQ(quad.br.y, 11.5);
    }

    // height
    {
        SymbolLayoutProperties::Evaluated layout;
        layout.get<TextSize>() = 24.0f;
        layout.get<IconTextFit>() = IconTextFitType::Height;
        SymbolQuad quad =
            getIconQuad(anchor, shapedIcon, line, layout, 24.0f, SymbolPlacementType::Point, shapedText, 1.0);

        EXPECT_EQ(quad.tl.x, -21.5);
        EXPECT_EQ(quad.tl.y, -10);
        EXPECT_EQ(quad.tr.x, -18.5);
        EXPECT_EQ(quad.tr.y, -10);
        EXPECT_EQ(quad.bl.x, -21.5);
        EXPECT_EQ(quad.bl.y, 30);
        EXPECT_EQ(quad.br.x, -18.5);
        EXPECT_EQ(quad.br.y, 30);
    }

    // height x textSize
    {
        SymbolLayoutProperties::Evaluated layout;
        layout.get<TextSize>() = 12.0f;
        layout.get<IconTextFit>() = IconTextFitType::Height;
        SymbolQuad quad =
            getIconQuad(anchor, shapedIcon, line, layout, 12.0f, SymbolPlacementType::Point, shapedText, 1.0);

        EXPECT_EQ(quad.tl.x, -11.5);
        EXPECT_EQ(quad.tl.y, -5);
        EXPECT_EQ(quad.tr.x, -8.5);
        EXPECT_EQ(quad.tr.y, -5);
        EXPECT_EQ(quad.bl.x, -11.5);
        EXPECT_EQ(quad.bl.y, 15);
        EXPECT_EQ(quad.br.x, -8.5);
        EXPECT_EQ(quad.br.y, 15);
    }

    // height x textSize + padding
    {
        SymbolLayoutProperties::Evaluated layout;
        layout.get<TextSize>() = 12.0f;
        layout.get<IconTextFit>() = IconTextFitType::Height;
        layout.get<IconTextFitPadding>()[0] = 5.0f;
        layout.get<IconTextFitPadding>()[1] = 10.0f;
        layout.get<IconTextFitPadding>()[2] = 5.0f;
        layout.get<IconTextFitPadding>()[3] = 10.0f;
        SymbolQuad quad =
            getIconQuad(anchor, shapedIcon, line, layout, 12.0f, SymbolPlacementType::Point, shapedText, 1.0);

        EXPECT_EQ(quad.tl.x, -21.5);
        EXPECT_EQ(quad.tl.y, -10);
        EXPECT_EQ(quad.tr.x, 1.5);
        EXPECT_EQ(quad.tr.y, -10);
        EXPECT_EQ(quad.bl.x, -21.5);
        EXPECT_EQ(quad.bl.y, 20);
        EXPECT_EQ(quad.br.x, 1.5);
        EXPECT_EQ(quad.br.y, 20);
    }

    // both
    {
        SymbolLayoutProperties::Evaluated layout;
        layout.get<TextSize>() = 24.0f;
        layout.get<IconTextFit>() = IconTextFitType::Both;
        SymbolQuad quad =
            getIconQuad(anchor, shapedIcon, line, layout, 24.0f, SymbolPlacementType::Point, shapedText, 1.0);

        EXPECT_EQ(quad.tl.x, -60);
        EXPECT_EQ(quad.tl.y, -10);
        EXPECT_EQ(quad.tr.x, 20);
        EXPECT_EQ(quad.tr.y, -10);
        EXPECT_EQ(quad.bl.x, -60);
        EXPECT_EQ(quad.bl.y, 30);
        EXPECT_EQ(quad.br.x, 20);
        EXPECT_EQ(quad.br.y, 30);
    }

    // both x textSize
    {
        SymbolLayoutProperties::Evaluated layout;
        layout.get<TextSize>() = 12.0f;
        layout.get<IconTextFit>() = IconTextFitType::Both;
        SymbolQuad quad =
            getIconQuad(anchor, shapedIcon, line, layout, 12.0f, SymbolPlacementType::Point, shapedText, 1.0);

        EXPECT_EQ(quad.tl.x, -30);
        EXPECT_EQ(quad.tl.y, -5);
        EXPECT_EQ(quad.tr.x, 10);
        EXPECT_EQ(quad.tr.y, -5);
        EXPECT_EQ(quad.bl.x, -30);
        EXPECT_EQ(quad.bl.y, 15);
        EXPECT_EQ(quad.br.x, 10);
        EXPECT_EQ(quad.br.y, 15);
    }

    // both x textSize + padding
    {
        SymbolLayoutProperties::Evaluated layout;
        layout.get<TextSize>() = 12.0f;
        layout.get<IconTextFit>() = IconTextFitType::Both;
        layout.get<IconTextFitPadding>()[0] = 5.0f;
        layout.get<IconTextFitPadding>()[1] = 10.0f;
        layout.get<IconTextFitPadding>()[2] = 5.0f;
        layout.get<IconTextFitPadding>()[3] = 10.0f;
        SymbolQuad quad =
            getIconQuad(anchor, shapedIcon, line, layout, 12.0f, SymbolPlacementType::Point, shapedText, 1.0);

        EXPECT_EQ(quad.tl.x, -40);
        EXPECT_EQ(quad.tl.y, -10);
        EXPECT_EQ(quad.tr.x, 20);
        EXPECT_EQ(quad.tr.y, -10);
        EXPECT_EQ(quad.bl.x, -40);
        EXPECT_EQ(quad.bl.y, 20);
        EXPECT_EQ(quad.br.x, 20);
        EXPECT_EQ(quad.br.y, 20);
    }

    // both x textSize + padding t/r/b/l
    {
        SymbolLayoutProperties::Evaluated layout;
        layout.get<TextSize>() = 12.0f;
        layout.get<IconTextFit>() = IconTextFitType::Both;
        layout.get<IconTextFitPadding>()[0] = 0.0f;
        layout.get<IconTextFitPadding>()[1] = 5.0f;
        layout.get<IconTextFitPadding>()[2] = 10.0f;
        layout.get<IconTextFitPadding>()[3] = 15.0f;
        SymbolQuad quad =
            getIconQuad(anchor, shapedIcon, line, layout, 12.0f, SymbolPlacementType::Point, shapedText, 1.0);

        EXPECT_EQ(quad.tl.x, -45);
        EXPECT_EQ(quad.tl.y, -5);
        EXPECT_EQ(quad.tr.x, 15);
        EXPECT_EQ(quad.tr.y, -5);
        EXPECT_EQ(quad.bl.x, -45);
        EXPECT_EQ(quad.bl.y, 25);
        EXPECT_EQ(quad.br.x, 15);
        EXPECT_EQ(quad.br.y, 25);
    }
}

