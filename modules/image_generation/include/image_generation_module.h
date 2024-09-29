#pragma once
#include "fontconfig_check.h"
#include <string>

class ImageGenerationModule : public fontconfigcheck::FontconfigCheck::Module
{
public:
    ImageGenerationModule(const std::string &fontFile, const std::string &text, const std::string &outputImagePath);
    virtual void execute() const override;

private:
    std::string fontFile;
    std::string text;
    std::string outputImagePath;
};
