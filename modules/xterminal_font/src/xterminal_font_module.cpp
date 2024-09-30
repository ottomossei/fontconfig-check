#include "xterminal_font_module.h"
#include "logger.h"
#include <cstdlib>

XterminalFont::XterminalFont(const std::string &fontName)
    : fontName(fontName) {}

void XterminalFont::execute() const
{
    // 1. 指定されたフォント名が存在するか確認
    fontconfigcheck::FontconfigCheck fontChecker;
    std::string fontFile = fontChecker.findFontFile(fontName);

    if (!fontFile.empty())
    {
        LOG_INFO("Font found: " + fontName);

        // 2. Xresourcesを一時的に変更 (揮発的設定)
        std::string command = "xrdb -merge <<EOF\n"
                              "XTerm*faceName: " +
                              fontName + "\n"
                                         "XTerm*faceSize: 12\n"
                                         "EOF";

        LOG_INFO("Applying temporary font settings with xrdb.");
        int result = system(command.c_str()); // 一時的にXresourcesを更新
        if (result != 0)
        {
            std::cerr << "Failed to execute command: " << command << std::endl;
        }
    }
    else
    {
        LOG_ERROR("Font not found: " + fontName);
    }
}
