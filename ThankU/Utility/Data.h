#pragma once
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
};

