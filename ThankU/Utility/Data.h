#pragma once
#include "Vector2D.h"

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

	static int frame_image[6];				//吹き出し枠


public:
	//初期処理
	static void Initialize();

	/// <summary>
	/// 吹き出しを描画する
	/// </summary>
	/// <param name="_loc">描画座標</param>
	/// <param name="_size_x">横幅</param>
	/// <param name="_color">吹き出しの色 false=灰 true=緑</param>
	static void DrawSpeechBubble(Vector2D _loc, int _size_x, bool _color);
};

