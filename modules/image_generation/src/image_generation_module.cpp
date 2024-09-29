#include "image_generation_module.h"
#include "logger.h"
#include <cairo/cairo.h>
#include <cairo/cairo-ft.h>
#include <ft2build.h>
#include FT_FREETYPE_H

ImageGenerationModule::ImageGenerationModule(const std::string &fontFile, const std::string &text, const std::string &outputImagePath)
    : fontFile(fontFile), text(text), outputImagePath(outputImagePath) {}

void ImageGenerationModule::execute() const
{
    LOG_INFO("Starting image generation.");
    FT_Library ftLibrary;
    FT_Face ftFace;

    // FreeTypeの初期化
    if (FT_Init_FreeType(&ftLibrary))
    {
        LOG_ERROR("Could not initialize FreeType library.");
        return;
    }
    else
    {
        LOG_VERBOSE("FreeType library initialized successfully.");
    }

    // フォントファイルのロード
    if (FT_New_Face(ftLibrary, fontFile.c_str(), 0, &ftFace))
    {
        LOG_ERROR("Could not load font: " + fontFile);
        FT_Done_FreeType(ftLibrary);
        return;
    }
    else
    {
        LOG_VERBOSE("Loaded font: " + fontFile);
    }

    // フォントサイズの設定
    FT_Set_Pixel_Sizes(ftFace, 0, 48);
    LOG_VERBOSE("Set font pixel size to 48.");

    // Cairoのサーフェスとコンテキストの作成
    int width = 400;
    int height = 100;
    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);

    if (cairo_surface_status(surface) != CAIRO_STATUS_SUCCESS)
    {
        LOG_ERROR("Failed to create Cairo surface.");
        FT_Done_Face(ftFace);
        FT_Done_FreeType(ftLibrary);
        return;
    }
    else
    {
        LOG_VERBOSE("Cairo surface created successfully.");
    }

    cairo_t *cr = cairo_create(surface);
    if (cairo_status(cr) != CAIRO_STATUS_SUCCESS)
    {
        LOG_ERROR("Failed to create Cairo context.");
        cairo_surface_destroy(surface);
        FT_Done_Face(ftFace);
        FT_Done_FreeType(ftLibrary);
        return;
    }
    else
    {
        LOG_VERBOSE("Cairo context created successfully.");
    }

    // 背景を白色に設定
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_paint(cr);
    LOG_VERBOSE("Set background color to white.");

    // フォントをCairoに設定
    cairo_font_face_t *cairoFtFontFace = cairo_ft_font_face_create_for_ft_face(ftFace, 0);
    cairo_set_font_face(cr, cairoFtFontFace);
    cairo_set_font_size(cr, 48);
    LOG_VERBOSE("Set Cairo font face and size.");

    // テキストを黒色で描画
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0); // 黒色
    cairo_move_to(cr, 50, 60);
    cairo_show_text(cr, text.c_str());
    LOG_VERBOSE("Rendered text: " + text);

    // 画像をPNGとして保存
    cairo_status_t status = cairo_surface_write_to_png(surface, outputImagePath.c_str());
    if (status == CAIRO_STATUS_SUCCESS)
    {
        LOG_INFO("Image saved to " + outputImagePath);
    }
    else
    {
        LOG_ERROR("Failed to save image to " + outputImagePath);
    }

    // リソースの解放
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    cairo_font_face_destroy(cairoFtFontFace);
    FT_Done_Face(ftFace);
    FT_Done_FreeType(ftLibrary);

    LOG_VERBOSE("Image generation process completed.");
}
