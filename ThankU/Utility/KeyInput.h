#pragma once

#include "Vector2D.h"

#define D_KEYCODE_MAX (256)		//�L�[�R�[�h�ő吔
#define MOUSE_MAX (256)			//�}�E�X�ő吔
//�L�[���͏��
enum class eInputState : unsigned char
{
	None,
	Pressed,
	Released,
	Held,
};

//�}�E�X�J�[�\��
struct Cursor
{
	int x;	//�����l
	int y;	//�c���l
};

class KeyInput
{
private:

	//�L�[�{�[�h���͒l
	char now_key[D_KEYCODE_MAX] = {};		//���݂̓��͊i�[
	char old_key[D_KEYCODE_MAX] = {};		//�O��̓��͊i�[
	int now_mouse[MOUSE_MAX] = {}; //����̓��̓}�E�X�{�^��
	int old_mouse[MOUSE_MAX] = {}; //�O��̓��̓}�E�X�{�^��

	Cursor cursor; //�J�[�\��
private:
	//�R���X�g���N�^��private�ɂ��邱�ƂŁA
	//���N���X�̃����o�֐��ŃC���X�^���X�𐶐��ł��Ȃ��悤�ɂ���
	KeyInput() = default;

	//�R�s�[�K�[�h
	//�N���X�O�ŃC���X�^���X�𐶐����ēn�����Ƃ��ł��Ȃ��悤�ɂ���
	KeyInput(KeyInput& v) = default;
	KeyInput& operator = (const KeyInput& v) = delete;
	~KeyInput() = default;

public:
	//�C���X�^���X���擾���鏈��
	static KeyInput* Get();
public:
	//���͍X�V
	void Update();
public:
	//���͏�Ԃ��擾����(�L�[�{�[�h)
	eInputState GetKeyState(int keycode)const;

	//���͏�Ԃ��擾����(�}�E�X)
	eInputState GetMouseState(int mouse)const;

	//�}�E�X�J�[�\���̍��W���擾����
	Cursor GetMouseCursor();
private:
	//�w�肵���������L�[�z��͈͓̔����m�F
	bool CheckKeyCodeRange(int key_code)const;
	//�w�肵���������L�[�z��͈͓̔����m�F
	bool CheckMouseRange(int mouse)const;
};






