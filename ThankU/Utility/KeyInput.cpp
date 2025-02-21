#include "KeyInput.h"
#include "DxLib.h"
#include "DebugInformation.h"

//���͐���N���X�̃C���X�^���X�擾���鏈��
KeyInput* KeyInput::Get()
{
	static KeyInput instance;
	//�������g�̃|�C���^��ԋp����
	return &instance;
}

void KeyInput::Update()
{
	//�O����͒l�̍X�V
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));
	memcpy(old_mouse, now_mouse, (sizeof(char) * D_KEYCODE_MAX));

	//���ݓ��͒l�̍X�V
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

	//�}�E�X�J�[�\���̍��W�X�V
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
