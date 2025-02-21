#include "KeyInput.h"
#include "DxLib.h"
#include "DebugInformation.h"

//入力制御クラスのインスタンス取得する処理
KeyInput* KeyInput::Get()
{
	static KeyInput instance;
	//自分自身のポインタを返却する
	return &instance;
}

void KeyInput::Update()
{
	//前回入力値の更新
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));
	memcpy(old_mouse, now_mouse, (sizeof(char) * D_KEYCODE_MAX));

	//現在入力値の更新
	GetHitKeyStateAll(now_key);
	for (int i = 0; i < MOUSE_MAX; i++)
	{
		if (GetMouseInput() == i)
		{
			now_mouse[i] = 1;
		}
		else
		{
			now_mouse[i] = 0;
		}
	}

	//マウスカーソルの座標更新
	GetMousePoint(&cursor.x, &cursor.y);

}

eInputState KeyInput::GetKeyState(int keycode)const
{
	if (CheckKeyCodeRange(keycode))
	{
		if (old_key[keycode] == TRUE)
		{
			if (now_key[keycode] == TRUE)
			{
				return eInputState::Held;
			}
			else
			{
				return eInputState::Released;
			}
		}
		else
		{
			if (now_key[keycode] == TRUE)
			{
				return eInputState::Pressed;
			}
			else
			{
				return eInputState::None;
			}
		}
	}
	return eInputState::None;
}

eInputState KeyInput::GetMouseState(int mouse)const
{
	if (CheckMouseRange(mouse))
	{
		if (old_mouse[mouse] == TRUE)
		{
			if (now_mouse[mouse] == TRUE)
			{
				return eInputState::Held;
			}
			else
			{
				return eInputState::Released;
			}
		}
		else
		{
			if (now_mouse[mouse] == TRUE)
			{
				return eInputState::Pressed;
			}
			else
			{
				return eInputState::None;
			}
		}
	}
	return eInputState::None;
}

Cursor KeyInput::GetMouseCursor()
{
	return cursor;
}

bool KeyInput::CheckKeyCodeRange(int keycode)const
{
	return (0 <= keycode && keycode < D_KEYCODE_MAX);
}

bool KeyInput::CheckMouseRange(int mouse)const
{
	return (0 <= mouse && mouse < MOUSE_MAX);
}
