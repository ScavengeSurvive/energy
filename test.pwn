#include <test-boilerplate>
#include <zcmd>
#include <YSI\y_timers>

#include "food.inc"


main() {
	//
}

ptask ShowEnergy[1000](playerid) {
	new
		Float:energy,
		Float:mult,
		str[128];
	
	GetPlayerEnergy(playerid, energy);
	GetPlayerEnergyMultiplier(playerid, mult);

	format(str, sizeof str, "Player Energy: %f Hunger Rate Multiplier: %f", energy, mult);
	SendClientMessage(playerid, -1, str);
}

CMD:togglebar(playerid, params[]) {
	return TogglePlayerEnergyBar(playerid, !IsPlayerEnergyBarShown(playerid));
}

CMD:setenergy(playerid, params[]) {
	new Float:energy = floatstr(params);

	SetPlayerEnergy(playerid, energy);

	return 1;
}

CMD:setmult(playerid, params[]) {
	new Float:mult = floatstr(params);

	SetPlayerEnergyMultiplier(playerid, mult);

	return 1;	
}
