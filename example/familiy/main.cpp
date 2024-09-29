#include "fontconfig_check.h"
#include <iostream>

int main()
{
    fontconfigcheck::FontconfigCheck fontChecker;

    // 全フォントファミリを取得して表示
    std::vector<std::string> fontFamilies = fontChecker.getFontFamilies();
    std::cout << "Installed font families:" << std::endl;
    for (const auto &family : fontFamilies)
    {
        std::cout << " - " << family << std::endl;
    }

    return 0;
}
