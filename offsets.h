#pragma once

namespace offsets {
	constexpr uintptr_t moduleAddr = 0x00400000;

	constexpr uintptr_t localPlayer = 0x0018AC00;
	constexpr uintptr_t viewMatrix = 0x57DFD0; //static
	constexpr uintptr_t entityList = 0x0018AC04;

	constexpr uintptr_t playersNumber = 0x58AC0C; //static

	constexpr uintptr_t health = 0xEC;
	constexpr uintptr_t isDead = 0x318;
	constexpr uintptr_t teamNum = 0x30C;

	constexpr uintptr_t m_XPos = 0x4;
	constexpr uintptr_t m_YPos = 0x8;
	constexpr uintptr_t m_ZPos = 0xC;

	constexpr uintptr_t m_feetXPos = 0x28;
	constexpr uintptr_t m_feetYPos = 0x2C;
	constexpr uintptr_t m_feetZPos = 0x30;

	constexpr uintptr_t yaw = 0x34;
	constexpr uintptr_t pitch = 0x38;
}

namespace instructions {
	constexpr uintptr_t gunAmmo = 0x004C73EF; //FF08
	constexpr uintptr_t gunRecoil = 0x004C2EC3; //F3:0F1156 38
	constexpr uintptr_t gunFireRate = 0x004C73E3; //0FBF48 54
	constexpr uintptr_t gunKnockBack = 0x004C66A5; //0FBF70 54
	constexpr uintptr_t trip = 0x004BB224;
	constexpr uintptr_t flyHack = 0x004C223D;
}	