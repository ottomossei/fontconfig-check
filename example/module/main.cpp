#include <iostream>
#include <memory> // std::unique_ptr
#include "fontconfig_check.h"

#ifdef WITH_IMAGE_GENERATION
#include "image_generation_module.h"
#endif

#ifdef WITH_XTERMINAL_FONT
#include "xterminal_font_module.h"
#endif

void setupModules(fontconfigcheck::FontconfigCheck &fontChecker, const std::string &fontFile)
{
#ifdef WITH_IMAGE_GENERATION
    std::cout << "Image generation enabled" << std::endl;

    // std::unique_ptrでImageGenerationModuleの管理を安全に行う
    auto imgGen = std::make_unique<ImageGenerationModule>(fontFile, "Hello, World!", "output.png");
    fontChecker.addModule(std::move(imgGen)); // モジュールを安全に管理
#endif

#ifdef WITH_XTERMINAL_FONT
    std::cout << "XterminalFont module enabled" << std::endl;

    // XterminalFontモジュールの追加
    auto xtermFont = std::make_unique<XterminalFont>(fontFile);
    fontChecker.addModule(std::move(xtermFont)); // モジュールを安全に管理
#endif
}

int main(int argc, char *argv[])
{
    // 引数が不足していればエラーメッセージを出して終了
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <font-name>" << std::endl;
        return 1;
    }

    // 実行時の第一引数をフォント名 (fontName) として使用
    std::string fontName = argv[1];

    fontconfigcheck::FontconfigCheck fontChecker;
    std::string fontFile = fontChecker.findFontFile(fontName);

    if (!fontFile.empty())
    {
        std::cout << "Font file found: " << fontFile << std::endl;

        // モジュールのセットアップ
        setupModules(fontChecker, fontFile);

        // モジュールの実行
        fontChecker.runModules();
    }
    else
    {
        std::cout << "Font file not found for " << fontName << std::endl;
    }

    return 0;
}
