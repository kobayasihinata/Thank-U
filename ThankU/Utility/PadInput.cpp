#include "PadInput.h"
#include "DxLib.h"

//実態を定義
bool PadInput::now_button[5][16] = {};
bool PadInput::old_button[5][16] = {};
float PadInput::trigger[5][2] = {};
Vector2D PadInput::stick[5][2] = {};

void PadInput::Update()
{
	XINPUT_STATE input_state = {};
	for (int j = 1; j <= 4; j++)
	{
		GetJoypadXInputState(j, &input_state);

		//各ボタン更新
		for (int i = 0; i < 16; i++)
		{
			old_button[j][i] = now_button[j][i];
			now_button[j][i] = (bool)input_state.Buttons[i];
		}

		//各トリガー格納
		trigger[j][0] = (float)input_state.LeftTrigger / (float)UCHAR_MAX;
		trigger[j][1] = (float)input_state.RightTrigger / (float)UCHAR_MAX;

		//左スティック角度更新
		if (input_state.ThumbLX > 0.0f)
		{
			stick[j][0].x = (float)input_state.ThumbLX / (float)SHRT_MAX;
		}
		else
		{
			stick[j][0].x = -((float)input_state.ThumbLX / (float)SHRT_MIN);
		}
		if (input_state.ThumbLY > 0.0f)
		{
			stick[j][0].y = (float)input_state.ThumbLY / (float)SHRT_MAX;
		}
		else
		{
			stick[j][0].y = -((float)input_state.ThumbLY / (float)SHRT_MIN);
		}

		//右スティック更新
		if (input_state.ThumbRX > 0.0f)
		{
			stick[j][1].x = (float)input_state.ThumbRX / (float)SHRT_MAX;
		}
		else
		{
			stick[j][1].x = -((float)input_state.ThumbRX / (float)SHRT_MIN);
		}
		if (input_state.ThumbRY > 0.0f)
		{
			stick[j][1].y = (float)input_state.ThumbRY / (float)SHRT_MAX;
		}
		else
		{
			stick[j][1].y = -((float)input_state.ThumbRY / (float)SHRT_MIN);
		}
	}
}

bool PadInput::GetButton(int input_type, int button)
{
	return ChackButtonRange(button) && (now_button[input_type][button] && old_button[input_type][button]);
}

bool PadInput::GetButtonDown(int input_type, int button)
{
	return ChackButtonRange(button) && (now_button[input_type][button] && !old_button[input_type][button]);
}

bool PadInput::GetButtonUp(int input_type, int button)
{
	return ChackButtonRange(button) && (!now_button[input_type][button] && old_button[input_type][button]);
}

float PadInput::GetLeftTrigger(int input_type)
{
	return trigger[input_type][0];
}

float PadInput::GetRightTrigger(int input_type)
{
	return trigger[input_type][1];
}

Vector2D PadInput::GetLeftStick(int input_type)
{
	return stick[input_type][0];
}

Vector2D PadInput::GetRightStick(int input_type)
{
	return stick[input_type][1];
}

bool PadInput::ChackButtonRange(int button)
{
	return (0 <= button && button < 16);
}

