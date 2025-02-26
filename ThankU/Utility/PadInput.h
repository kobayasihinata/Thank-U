#pragma once

#include "Vector2D.h"

class PadInput
{
private:
	//[0]は何も入っていなくて、1~4を使用する
	static bool now_button[5][16]; //現在のボタン入力
	static bool old_button[5][16]; //ひとつ前のボタン入力
	static float trigger[5][2];    //左右トリガー
	static Vector2D stick[5][2];	//左右スティック

public:
	static void Update();	//入力更新

	//コントローラー名
	//DX_INPUT_PAD1　　　　: パッド１
	//DX_INPUT_PAD2　　　　 : パッド２
	//DX_INPUT_PAD3　　　　 : パッド３
	//DX_INPUT_PAD4　　　　 : パッド４
	
	//各ボタン取得
	//押している間 input_type=コントローラー名 button=取得したいボタン
	static bool GetButton(int input_type, int button);	
	//押した瞬間 input_type=コントローラー名 button=取得したいボタン
	static bool GetButtonDown(int input_type, int button);
	//離した瞬間 input_type=コントローラー名 button=取得したいボタン
	static bool GetButtonUp(int input_type, int button);	

	//トリガー
	//左トリガー取得(input_type=コントローラー名)
	static float GetLeftTrigger(int input_type);
	//右トリガー取得(input_type=コントローラー名)
	static float GetRightTrigger(int input_type);

	//スティック取得
	//左スティック取得(input_type=コントローラー名)
	static Vector2D GetLeftStick(int input_type);
	//左スティック取得(input_type=コントローラー名)
	static Vector2D GetRightStick(int input_type);	

private:
	//ボタン範囲測定
	static bool ChackButtonRange(int button);
};
