#pragma once

#include "fontconfig_check.h"
#include <string>

class XterminalFont : public fontconfigcheck::FontconfigCheck::Module
{
public:
    XterminalFont(const std::string &fontName);
    virtual void execute() const override;

private:
    std::string fontName;
};
