#pragma once

class Mouse
{
private:
	bool l_button_press_prev = false;
	bool r_button_press_prev = false;

public:
	void Update(void);
	
	int GetMouseX(void);
	int GetMouseY(void);

	bool IsLButtonTrigger(void);
	bool IsRButtonTrigger(void);
	bool IsLButtonRelease(void);
	bool IsRButtonRelease(void);
	bool IsLButtonPress(void);
	bool IsRButtonPress(void);
};

