#include "PauseLayer.h"

bool noclip = false;

CCSprite* toggle_texture(CCSprite* toggleOn, CCSprite* toggleOff) {
    // Determines the texture based on if noclip is enabled or not
    return (noclip) ? toggleOn : toggleOff;
}

void PauseLayer::noclip_button(CCObject*) {
    //{"addr": "0x20A23C", "on": "E9 79 06 00 00", "off": "6A 14 8B CB FF"}
    // 0x20A23C - Offset
    // E9 79 06 00 00 - Noclip On
    // 6A 14 8B CB FF - Noclip Off
    noclip = !noclip; // Toggles noclip
    if (noclip) {
        WriteProcessMemory(
            GetCurrentProcess(),
            reinterpret_cast<void*>(gd::base + 0x20A23C),
            //E9 79 06 00 00
            "\xe9\x79\x06\x00\x00",
            5, // Size of 5 due to 5 \x (Bytes)
            NULL
        );
    } else {
        WriteProcessMemory(
            GetCurrentProcess(),
            reinterpret_cast<void*>(gd::base + 0x20A23C),
            //6A 14 8B CB FF
            "\x6a\x14\x8b\xcb\xff",
            5, // Size of 5 due to 5 \x (Bytes)
            NULL
        );
    }
}

bool __fastcall PauseLayer::hook(CCLayer* self) {
    bool result = PauseLayer::init(self); // Calling trampoline
    auto director = CCDirector::sharedDirector();
    auto size = director->getWinSize();

    auto toggleOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
    auto toggleOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
    
    auto noclip_button = gd::CCMenuItemToggler::create(
        toggle_texture(toggleOn, toggleOff),
        toggle_texture(toggleOff, toggleOn),
        self,
        menu_selector(PauseLayer::noclip_button) // Null pointer for now until we create the function
    );
    auto label = CCLabelBMFont::create("Noclip", "goldFont.fnt"); // You can also use bigFont.fnt if you want a white font
    noclip_button->setScale(0.5F);
    label->setScale(0.5F);
    label->setPositionX(45);

    auto menu = CCMenu::create(); // CCMenus are required to make CCMenuItem buttons clickable
    menu->setPosition({ 25, size.height - 50 });
    menu->addChild(noclip_button);
    menu->addChild(label);

    self->addChild(menu);
    return result;
}