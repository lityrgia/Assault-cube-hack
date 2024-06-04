#pragma once

#include "DataTypes.h"
#include "Memory.h"

void drawEsp(Memory& mem, uintptr_t& localPlayer, uintptr_t& entityList);
void drawLine(Vec2& end, ColorA* color);
void drawBox(Vec2& coordsHead, Vec2& coordsFeet, ColorA* color);
void drawHealth(Vec2& coordsHead, Vec2& coordsFeet, short entityHealth);