#pragma once

#include "Vector2D.h"

class InputControl
{
private:
	static bool now_button[4][16]; //現在のボタン入力
	static bool old_button[4][16]; //�ߋ��t���[�����͒l
	static float trigger[4][2];    //���E�g���K�[���͒l
	static Vector2D stick[4][2];	//���E�X�e�B�b�N���͒l

public:
	static void Update();	//�X�V����

	//�{�^�����͎擾����
	static bool GetButton(int input_type, int button);	//���������Ă����
	static bool GetButtonDown(int input_type, int button);	//�������u��
	static bool GetButtonUp(int input_type, int button);	//�������u��

	//�g���K�[���͎擾����
	static float GetLeftTrigger(int input_type);			//���g���K�[
	static float GetRightTrigger(int input_type);			//�E�g���K�[

	//�X�e�B�b�N���͎擾����
	static Vector2D GetLeftStick(int input_type);			//���X�e�B�b�N
	static Vector2D GetRightStick(int input_type);		//�E�X�e�B�b�N

private:
	//�{�^���z��͈̓`�F�b�N
	static bool ChackButtonRange(int button);
};
