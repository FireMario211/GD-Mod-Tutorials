#pragma once
#include "pch.h"
using namespace cocos2d;

namespace PauseLayer {
	inline bool(__thiscall* init)(CCLayer* self);
	bool __fastcall hook(CCLayer* self);

	class Callback {
	public:
		void noclipButton(CCObject*);
	};
}