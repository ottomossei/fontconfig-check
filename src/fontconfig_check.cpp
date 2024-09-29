#include "fontconfig_check.h"
#include "logger.h" // ロガーを追加
#include <iostream>

fontconfigcheck::FontconfigCheck::FontconfigCheck()
{
    FcInit();
    LOG_INFO("FontconfigCheck initialized");
}

fontconfigcheck::FontconfigCheck::~FontconfigCheck()
{
    FcFini();
    LOG_INFO("FontconfigCheck finalized");
}

std::string fontconfigcheck::FontconfigCheck::findFontFile(const std::string &fontName)
{
    // 1. フォント名からフォントパターンを作成
    LOG_VERBOSE("Creating font pattern for: " + fontName);
    FcPattern *pattern = FcNameParse((const FcChar8 *)fontName.c_str());

    // 2. システムの設定に基づいてパターンを補完
    LOG_VERBOSE("Substituting configuration settings for the font pattern.");
    FcConfigSubstitute(nullptr, pattern, FcMatchPattern);
    FcDefaultSubstitute(pattern);

    FcResult result;
    // 3. 最も適合するフォントを検索
    LOG_VERBOSE("Matching font pattern for: " + fontName);
    FcPattern *match = FcFontMatch(nullptr, pattern, &result);
    std::string fontFile;

    // 4. マッチングの結果を確認
    if (result == FcResultMatch)
    {
        LOG_VERBOSE("Font matched successfully for: " + fontName);
    }
    else if (result == FcResultNoMatch)
    {
        LOG_ERROR("No matching font found for: " + fontName);
    }
    else if (result == FcResultTypeMismatch)
    {
        LOG_ERROR("Type mismatch during font matching for: " + fontName);
    }
    else if (result == FcResultNoId)
    {
        LOG_ERROR("No ID found during font matching for: " + fontName);
    }
    else
    {
        LOG_ERROR("Unknown error occurred during font matching for: " + fontName);
    }

    // パターンがマッチしなかった場合、処理を終了
    if (result != FcResultMatch)
    {
        FcPatternDestroy(pattern);
        return "";
    }

    // 5. マッチしたフォントが存在する場合、ファイルパスを取得
    if (match)
    {
        FcChar8 *file = nullptr;
        if (FcPatternGetString(match, FC_FILE, 0, &file) == FcResultMatch)
        {
            fontFile = (const char *)file;
            LOG_INFO("Font file found: " + fontFile);
        }
        else
        {
            LOG_ERROR("Could not retrieve font file path for: " + fontName);
        }
        FcPatternDestroy(match);
    }
    else
    {
        LOG_ERROR("No match found for font: " + fontName);
    }

    // 6. パターンを解放
    LOG_VERBOSE("Destroying font pattern.");
    FcPatternDestroy(pattern);

    // 7. フォントファイルが見つからなかった場合、エラーメッセージを表示
    if (fontFile.empty())
    {
        LOG_ERROR("Font file not found for: " + fontName);
    }

    return fontFile;
}

std::vector<std::string> fontconfigcheck::FontconfigCheck::getFontFamilies() const
{
    LOG_INFO("Retrieving all font families."); // 最小限のログとしてはこれだけ
    std::vector<std::string> families;
    FcPattern *pat = FcPatternCreate();
    FcObjectSet *os = FcObjectSetBuild(FC_FAMILY, nullptr);
    FcFontSet *fs = FcFontList(nullptr, pat, os);

    for (int i = 0; i < fs->nfont; ++i)
    {
        FcChar8 *family;
        if (FcPatternGetString(fs->fonts[i], FC_FAMILY, 0, &family) == FcResultMatch)
        {
            families.push_back((const char *)family);
            LOG_VERBOSE("Found font family: " + std::string((const char *)family)); // 詳細な追跡はVERBOSE
        }
        else
        {
            LOG_ERROR("Failed to retrieve font family for font index: " + std::to_string(i));
        }
    }

    FcObjectSetDestroy(os);
    FcFontSetDestroy(fs);
    FcPatternDestroy(pat);

    if (families.empty())
    {
        LOG_ERROR("No font families found.");
    }
    else
    {
        LOG_VERBOSE("Total font families found: " + std::to_string(families.size()));
    }

    return families;
}

std::vector<std::string> fontconfigcheck::FontconfigCheck::getFontsByAttributes(int weight, int slant) const
{
    LOG_INFO("Retrieving fonts by attributes: weight=" + std::to_string(weight) + ", slant=" + std::to_string(slant));
    std::vector<std::string> fonts;
    FcPattern *pat = FcPatternCreate();
    FcPatternAddInteger(pat, FC_WEIGHT, weight);
    FcPatternAddInteger(pat, FC_SLANT, slant);

    FcObjectSet *os = FcObjectSetBuild(FC_FAMILY, FC_STYLE, nullptr);
    FcFontSet *fs = FcFontList(nullptr, pat, os);

    for (int i = 0; i < fs->nfont; ++i)
    {
        FcChar8 *family;
        if (FcPatternGetString(fs->fonts[i], FC_FAMILY, 0, &family) == FcResultMatch)
        {
            fonts.push_back((const char *)family);
            LOG_VERBOSE("Found font with specified attributes: " + std::string((const char *)family));
        }
        else
        {
            LOG_ERROR("Failed to retrieve font with specified attributes for font index: " + std::to_string(i));
        }
    }

    FcObjectSetDestroy(os);
    FcFontSetDestroy(fs);
    FcPatternDestroy(pat);

    if (fonts.empty())
    {
        LOG_ERROR("No fonts found with the specified attributes.");
    }
    else
    {
        LOG_VERBOSE("Total fonts found with attributes: " + std::to_string(fonts.size()));
    }

    return fonts;
}

void fontconfigcheck::FontconfigCheck::addModule(std::unique_ptr<Module> module)
{
    if (module)
    {
        LOG_VERBOSE("Adding module.");
        modules.push_back(std::move(module));
    }
    else
    {
        LOG_ERROR("Failed to add module. Module is null.");
    }
}

void fontconfigcheck::FontconfigCheck::runModules() const
{
    if (modules.empty())
    {
        LOG_INFO("No modules to run.");
    }
    else
    {
        LOG_VERBOSE("Running modules. Total modules: " + std::to_string(modules.size()));
        for (const auto &module : modules)
        {
            module->execute();
        }
    }
}
