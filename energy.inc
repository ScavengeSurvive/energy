// built-in include guard removal
// just in case the user has a local dependency with the same file name
#if defined _inc_energy
	#undef _inc_energy
#endif
// custom include-guard to ensure we don't duplicate
#if defined _energy_included
	#endinput
#endif
#define _energy_included


#include <a_samp>
#include <YSI\y_timers>
#include <progress2>

#include <YSI\y_hooks>


// HUNGER_RATE_BASE controls the base rate at which players gain hunger over time
#if !defined HUNGER_RATE_BASE
	#define HUNGER_RATE_BASE (0.06)
#endif

static
	// the level of energy (opposite of hunger) a player has - 100.0 is not hungry, 0.0 is starving
	Float:Energy[MAX_PLAYERS],
	// a UI element that displays the player's current hunger
	PlayerBar:EnergyBar[MAX_PLAYERS],
	bool:ShowEnergyBar[MAX_PLAYERS],
	// a modifier that can be applied to players to slow or speed the rate of hunger
	Float:HungerRateMultiplier[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
	EnergyBar[playerid] = CreatePlayerProgressBar(playerid, 548.000000, 36.000000, 62.000000, 3.200000, 536354815, 100.0000, 0);
	Energy[playerid] = 100.0;
	HungerRateMultiplier[playerid] = 1.0;
}

ptask _energy_update[1000](playerid) {
	new
		animidx = GetPlayerAnimationIndex(playerid),
		k,
		ud,
		lr,
		Float:adjustment;

	GetPlayerKeys(playerid, k, ud, lr);

	if(animidx == 43) {
		adjustment = HUNGER_RATE_BASE * 0.2; // Sitting
	} else if(animidx == 1159) {
		adjustment = HUNGER_RATE_BASE * 1.1; // Crouching
	} else if(animidx == 1195) {
		adjustment = HUNGER_RATE_BASE * 3.2; // Jumping
	} else if(animidx == 1231) {
		if(k & KEY_WALK) {
			adjustment = HUNGER_RATE_BASE * 1.2; // Walking
		} else if(k & KEY_SPRINT) {
			adjustment = HUNGER_RATE_BASE * 2.2; // Sprinting
		} else if(k & KEY_JUMP) {
			adjustment = HUNGER_RATE_BASE * 3.2; // Jumping
		} else {
			adjustment = HUNGER_RATE_BASE * 2.0; // Jogging
		}
	} else {
		adjustment = HUNGER_RATE_BASE;
	}

	adjustment *= HungerRateMultiplier[playerid];

	_energy_mustSetPlayerEnergy(playerid, Energy[playerid] - adjustment);

	return;
}

stock GetPlayerEnergy(playerid, &Float:energy) {
	if(!IsPlayerConnected(playerid)) {
		return 1;
	}

	energy = Energy[playerid];

	return 0;
}

stock SetPlayerEnergy(playerid, Float:energy) {
	if(!IsPlayerConnected(playerid)) {
		return 1;
	}

	_energy_mustSetPlayerEnergy(playerid, energy);

	return 0;
}

stock GetPlayerEnergyMultiplier(playerid, &Float:energy) {
	if(!IsPlayerConnected(playerid)) {
		return 1;
	}

	energy = HungerRateMultiplier[playerid];

	return 0;
}

stock SetPlayerEnergyMultiplier(playerid, Float:energy) {
	if(!IsPlayerConnected(playerid)) {
		return 1;
	}

	HungerRateMultiplier[playerid] = energy;

	return 0;
}

stock TogglePlayerEnergyBar(playerid, bool:toggle) {
	if(!IsPlayerConnected(playerid)) {
		return 1;
	}

	ShowEnergyBar[playerid] = toggle;

	if(toggle) {
		return ShowPlayerProgressBar(playerid, EnergyBar[playerid]);
	} else {
		return HidePlayerProgressBar(playerid, EnergyBar[playerid]);
	}
}

stock bool:IsPlayerEnergyBarShown(playerid) {
	if(!IsPlayerConnected(playerid)) {
		return false;
	}

	return ShowEnergyBar[playerid];
}

_energy_mustSetPlayerEnergy(playerid, Float:energy) {
	Energy[playerid] = energy;

	if(Energy[playerid] > 100.0) {
		Energy[playerid] = 100.0;
	} else if(Energy[playerid] < 0.0) {
		Energy[playerid] = 0.0;
	}

	if(ShowEnergyBar[playerid]) {
		SetPlayerProgressBarValue(playerid, EnergyBar[playerid], Energy[playerid]);
	}
}

// Todo: move to health package
// if(food < 20.0) {
// 	SetPlayerHP(playerid, GetPlayerHP(playerid) - (20.0 - food) / 30.0);
// }

// Todo: Move to drug FX package
// if(!IsPlayerUnderDrugEffect(playerid, drug_Morphine) && !IsPlayerUnderDrugEffect(playerid, drug_Air)) {
// 	if(food < 30.0)
// 	{
// 		if(!IsPlayerUnderDrugEffect(playerid, drug_Adrenaline))
// 		{
// 			if(intensity == 0)
// 				SetPlayerDrunkLevel(playerid, 0);
// 		}
// 		else
// 		{
// 			SetPlayerDrunkLevel(playerid, 2000 + floatround((31.0 - food) * 300.0));
// 		}
// 	}
// 	else
// 	{
// 		if(intensity == 0)
// 			SetPlayerDrunkLevel(playerid, 0);
// 	}
// }
