#include "pch.h"
#include "PauseLayer.h"

void enableNoclip() {
    uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandle(0));
    
    WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(base + 0x20A1E5), "\xe9\xd0\x06\x00\x00", 5, NULL);
}

void disableNoclip() {
    uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandle(0));
    WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(base + 0x20A1E5), "\x0f\x85\xcf\x06\x00\x00", 6, NULL);
 }

bool noclipEnabled = false;

void PauseLayer::Callback::noclipButton(CCObject* random) {
    noclipEnabled = !noclipEnabled;
    if (noclipEnabled) {
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20A23C), "\xe9\x79\x06\x00\x00", 5, NULL);
    }
    else {
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20A23C), "\x6a\x14\x8b\xcb\xff", 5, NULL);
    }
    
}

auto testNoclip(CCSprite* toggleOn, CCSprite* toggleOff) {
    return (noclipEnabled) ? toggleOn : toggleOff;
}

bool __fastcall PauseLayer::hook(CCLayer* self) {
    std::cout << "Loaded PauseLayer" << std::endl;
    auto director = cocos2d::CCDirector::sharedDirector();
    auto size = director->getWinSize();
    bool result = PauseLayer::init(self);

    auto toggleOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
    auto toggleOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");

    auto noclipButton = gd::CCMenuItemToggler::create(testNoclip(toggleOn, toggleOff), testNoclip(toggleOff, toggleOn), self, menu_selector(PauseLayer::Callback::noclipButton));
    auto label = CCLabelBMFont::create("Noclip", "goldFont.fnt");
    noclipButton->setScale(0.5F);
    label->setScale(0.5f);
    label->setPositionX(45);
    auto menu = CCMenu::create();
    menu->setPosition({ 25, size.height - 50 });
    menu->addChild(noclipButton);
    menu->addChild(label);
    self->addChild(menu);
    return result;
}
