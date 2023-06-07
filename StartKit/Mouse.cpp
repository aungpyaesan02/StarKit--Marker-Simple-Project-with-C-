#include "Mouse.h"
#include "lib/gb.h"

void Mouse::Update(void)
{
	l_button_press_prev = IsLButtonPress();
	r_button_press_prev = IsRButtonPress();
	
	gb_inputGet();

}

int Mouse::GetMouseX(void)
{
	return gb_inputGetMousePosX();
}

int Mouse::GetMouseY(void)
{
	return gb_inputGetMousePosY();
}

bool Mouse::IsLButtonTrigger(void)
{
	return !l_button_press_prev && IsLButtonPress();
}

bool Mouse::IsRButtonTrigger(void)
{
	return !r_button_press_prev && IsRButtonPress();
}

bool Mouse::IsLButtonRelease(void)
{
	return l_button_press_prev && !IsLButtonPress();
}

bool Mouse::IsRButtonRelease(void)
{
	return r_button_press_prev && !IsRButtonPress();
}

bool Mouse::IsLButtonPress(void)
{
	return gb_inputCheckMouseButton(0);
}

bool Mouse::IsRButtonPress(void)
{
	return gb_inputCheckMouseButton(1);
}


