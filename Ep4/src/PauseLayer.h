#pragma once
#include "pch.h"

class PauseLayer : public CCLayer { // or cocos2d::CCLayer if you didn't add "using namespace cocos2d" in pch.h
    public:
        static inline bool(__thiscall* init)(CCLayer* self); // PauseLayer::init (Func in GD)
        static bool __fastcall hook(CCLayer* self); // What will run after PauseLayer::init
        void noclip_button(CCObject*); // CCObject due to creating a CCMenuItem
};