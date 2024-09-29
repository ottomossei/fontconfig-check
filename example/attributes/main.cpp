#include "fontconfig_check.h"
#include <iostream>

int main()
{
    fontconfigcheck::FontconfigCheck fontChecker;

    // 太字かつ斜体のフォントを取得して表示
    std::vector<std::string> boldItalicFonts = fontChecker.getFontsByAttributes(FC_WEIGHT_BOLD, FC_SLANT_ITALIC);
    std::cout << "Bold and Italic fonts:" << std::endl;
    for (const auto &font : boldItalicFonts)
    {
        std::cout << " - " << font << std::endl;
    }

    return 0;
}
