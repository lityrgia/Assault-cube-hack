#pragma once

void patchBytes(Memory& mem, uintptr_t hookAddr, BYTE bytes);
void noFireRate(Memory& mem, bool state);
void noRecoil(Memory& mem, bool state);
void infAmmo(Memory& mem, bool state);
void noGunKnockback(Memory& mem, bool state);
void trip(Memory& mem, bool state);