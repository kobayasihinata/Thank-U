#pragma once
#include "Vector2D.h"

#include <vector>

struct PlayerData {
	int number;				//���l�ڂ̃v���C���[��(0~3)
	int use_controller;		//�g�p���Ă���R���g���[���[��
	int score;				//�X�R�A
	int great;				//Great��
	int bad;				//bad��
};

class Data
{
public:
	static int player_num;					//�v���C���[���v�l��		
		
	static PlayerData player_data[4];		//�e�v���C���[���	

	static int frame_image[6];				//�����o���g


public:
	//��������
	static void Initialize();

	/// <summary>
	/// �����o����`�悷��
	/// </summary>
	/// <param name="_loc">�`����W</param>
	/// <param name="_size_x">����</param>
	/// <param name="_color">�����o���̐F false=�D true=��</param>
	static void DrawSpeechBubble(Vector2D _loc, int _size_x, bool _color);
};

