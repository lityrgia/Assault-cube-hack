#include <GL/glew.h>

#include "DataTypes.h"
#include "Memory.h"
#include "offsets.h"
#include "math.h"
#include "visuals.h"
#include "options.h"
#include "globals.h"

ColorA* color = new ColorA;

ColorA colorHealth(0.0f, 0.0f, 1.0f, 0.5f);

void drawEsp(Memory& mem, uintptr_t& localPlayer, uintptr_t& entityList) {
	Matrix ViewMatrix = mem.Read<Matrix>(offsets::viewMatrix);
	Vec3 playerLocation = mem.Read<Vec3>(localPlayer + offsets::m_XPos);
	short playerTeam = mem.Read<short>(localPlayer + offsets::teamNum);

    short playerNumber = mem.Read<uintptr_t>(offsets::playersNumber);
    for (short i = 0; i < playerNumber; ++i) {
        uintptr_t entity = mem.Read<uintptr_t>(entityList + i * 0x4);
		int isEntityDead = mem.Read<uintptr_t>(entity + offsets::isDead);

        if (entity == NULL || isEntityDead) continue;

		short entityHealth = mem.Read<short>(entity + offsets::health);

        short entityTeam = mem.Read<short>(entity + offsets::teamNum);

        bool onSameTeam = (entityTeam == playerTeam);

        if (onSameTeam && !menu::bShowTeam) continue;

        Vec3 entityLocationHead = mem.Read<Vec3>(entity + offsets::m_XPos);
		Vec3 entityLocationFeet = mem.Read<Vec3>(entity + offsets::m_feetXPos);

        if (onSameTeam) {
            color->R = 0.0f;
			color->G = 0.0f;
            color->B = 1.0f;
			color->A = 0.7f;
        }
        else {
            color->R = 1.0f;
			color->G = 0.0f;
            color->B = 0.0f;
			color->A = 0.7f;
        }

        Vec2 screenCoordsHead;
        Vec2 screenCoordsFeet;

        if (!WorldToScreen(entityLocationHead, screenCoordsHead, ViewMatrix.VMatrix)) continue;
		if (!WorldToScreen(entityLocationFeet, screenCoordsFeet, ViewMatrix.VMatrix)) continue;

		ConvertToRange(screenCoordsHead);
		ConvertToRange(screenCoordsFeet);

		if (menu::bEnableLines) {
			drawLine(screenCoordsFeet, color);
		}
		if (menu::bEnableBoxes) {
			drawBox(screenCoordsHead, screenCoordsFeet, color);
		}
		if (menu::bEnableHealth) {
			drawHealth(screenCoordsHead, screenCoordsFeet, entityHealth);
		}
    }
}

void drawLine(Vec2& end, ColorA* color) {
	Vec2 lineOrigin;
	lineOrigin.X = 0.0f;
	lineOrigin.Y = -1.0f;

	glBegin(GL_LINES);
	glColor4f(color->R, color->G, color->B, color->A);
	glVertex2f(lineOrigin.X, lineOrigin.Y);
	glVertex2f(end.X, end.Y);
	glEnd();
};

void drawBox(Vec2& coordsHead, Vec2& coordsFeet, ColorA* color) {
	float boxHeight = coordsHead.Y - coordsFeet.Y;
	float boxWidth = boxHeight / 3.0f;

	float halfBoxWidth = boxWidth / 2.0f;

	glLineWidth(2.0f);
	glBegin(GL_LINE_LOOP);
	glColor4f(color->R, color->G, color->B, color->A - 1.0f);
	glVertex2f(coordsHead.X - halfBoxWidth, coordsFeet.Y);
	glVertex2f(coordsHead.X + halfBoxWidth, coordsFeet.Y); 
	glVertex2f(coordsHead.X + halfBoxWidth, coordsHead.Y);
	glVertex2f(coordsHead.X - halfBoxWidth, coordsHead.Y);
	glEnd();
}

void drawHealth(Vec2& coordsHead, Vec2& coordsFeet, short entityHealth) {
	if (entityHealth < 0) return;

	float boxHeight = coordsHead.Y - coordsFeet.Y;

	float halfBoxWidth = boxHeight / 6.0f;
	float halfBoxWidth2 = halfBoxWidth * 1.2f;

	float healthBarHeight = boxHeight * (entityHealth / 100.0f);
	float healthBarTopY = coordsFeet.Y + healthBarHeight;

	glBegin(GL_QUADS);
	glColor4f(colorHealth.R, colorHealth.G, colorHealth.B, colorHealth.A);
	glVertex2f(coordsHead.X - halfBoxWidth2, coordsFeet.Y);
	glVertex2f(coordsHead.X - halfBoxWidth, coordsFeet.Y); 
	glVertex2f(coordsHead.X - halfBoxWidth, healthBarTopY);
	glVertex2f(coordsHead.X - halfBoxWidth2, healthBarTopY); 
	glEnd();
}