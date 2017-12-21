# Energy

Provides players with an energy bar to represent energy from food and hunger. The energy level drops over time at a rate determined by animation.

Also contains a progress-bar above the health bar to represent current energy level. When the bar is full, the player is not hungry and has full energy and when the bar is empty, the player is starving.

This library does modify any player attributes such as health. It simply provides an API and the hunger rate mechanic. The rate can be modified via the API to speed up or slow down the rate of hunger - for example, via a mechanic that speeds up hunger rate based on player illness. The rate is a multiplier and can be set to 0.0 in order to completely stop energy from decreasing.

The default rate setting is 0.06. This means, every 1 second the player will lose a base of 0.06 energy multiplied by the following values based on the player's current action:

* x0.2 while Sitting
* x1.1 while Crouching
* x3.2 while Jumping
* x1.2 while Walking
* x2.2 while Sprinting
* x3.2 while Jumping
* x2.0 while Jogging

## Installation

Simply install to your project:

```bash
sampctl package install ScavengeSurvive/energy
```

Include in your code and begin using the library:

```pawn
#include <energy>
```

## Usage

### `GetPlayerEnergy(playerid, &Float:energy)`

Retrieves the player's energy as a value between 0.0 and 100.0, returns 0 on success and 1 if the player does not exist.

### `SetPlayerEnergy(playerid, Float:energy)`

Updates the player's energy level to the specified value, if the value is outside of the range 0.0 - 100.0, it will be truncated. Updates the progress bar if it is visible.

### `GetPlayerEnergyMultiplier(playerid, &Float:energy)`

Retrieves the player's energy rate multiplier, by default this is 1.0.

### `SetPlayerEnergyMultiplier(playerid, Float:energy)`

Updates the player's energy rate multiplier. Setting this to 0.0 will stop the player from losing energy completely.

### `TogglePlayerEnergyBar(playerid, bool:toggle)`

Toggles the visibility of the energy bar. Returns 1 if the player does not exist, otherwise returns the status of `ShowPlayerProgressBar` or `HidePlayerProgressBar`.

## Testing

To test, simply run the package:

```bash
sampctl package run
```

And connect to `localhost:7777` to test.

See the file `test.pwn` for commands to test features.
