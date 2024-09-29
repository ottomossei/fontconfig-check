#ifndef FONTCONFIG_CHECK_H
#define FONTCONFIG_CHECK_H

#include <string>
#include <vector>
#include <memory>
#include <fontconfig/fontconfig.h>

namespace fontconfigcheck
{

    class FontconfigCheck
    {
    public:
        FontconfigCheck();
        ~FontconfigCheck();
        // 指定したフォント名に対応するフォントファイルを検索
        std::string findFontFile(const std::string &fontName);

        // システムにインストールされている全てのフォントファミリ名を取得
        std::vector<std::string> getFontFamilies() const;

        // 特定の属性を持つフォントのリストを取得（例：太字、斜体など）
        std::vector<std::string> getFontsByAttributes(int weight = FC_WEIGHT_NORMAL, int slant = FC_SLANT_ROMAN) const;

        class Module
        {
        public:
            virtual ~Module() = default;
            virtual void execute() const = 0;
        };

        // モジュールを動的に追加できるようにする
        void addModule(std::unique_ptr<Module> module);
        void runModules() const;

    private:
        std::vector<std::unique_ptr<Module>> modules;
    };

} // namespace fontconfigcheck

#endif // FONTCONFIG_CHECK_H
