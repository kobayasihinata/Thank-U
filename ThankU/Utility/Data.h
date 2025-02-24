#pragma once
#include <vector>

struct PlayerData {
	int number;				//何人目のプレイヤーか(0~3)
	int use_controller;		//使用しているコントローラー名
	int score;				//スコア
	int great;				//Great数
	int bad;				//bad数
};

class Data
{
public:
	static int player_num;					//プレイヤー合計人数		
		
	static PlayerData player_data[4];		//各プレイヤー情報	
};

