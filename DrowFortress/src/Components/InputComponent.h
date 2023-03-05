#pragma once

enum InputState
{
	DISABLED,
	WORLD,
	UI
};

struct InputComponent
{
	InputState InputState;

	InputComponent() : InputState(DISABLED)
	{}
};