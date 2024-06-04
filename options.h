#pragma once

namespace menu {
	inline bool bMenuVisible{ true };
	inline bool bShowTeam{ false };
	inline bool bEnableLines{ false };
	inline bool bEnableBoxes{ false };
	inline bool bEnableHealth{ false };
	inline bool bEnableAim{ false };
	inline bool bEnableBang{ false };
	inline bool bFriendlyFire{ false };
	inline bool bSmooth{ false };
	inline bool bNoRecoil{ false };
	inline bool bFireRate{ false };
	inline bool bInfiniteAmmo{ false };
	inline bool bFOV{ false };
	inline bool bNoGunKnockback{ false };
	inline bool bFlyHack{ false };
	inline bool bTrip{ false };
}

namespace options {
	inline short oldFireRate{ 0 };
	inline short originalFireRate{ 0 };
	inline float fovCircle{ 1.0f };
	inline float smoothness{ 1.0f };
	inline int oldRecoil{ 0 };
	inline int oldClipAmmo{ 0 };
	inline int oldKnockBack{ 0 };
}

namespace toggled {
	inline bool trip{ false };
	inline bool flyHack{ false };
	inline bool noFireRate{ false };
	inline bool noRecoil{ false };
	inline bool infiniteAmmo{ false };
	inline bool noGunKnockback{ false };
}