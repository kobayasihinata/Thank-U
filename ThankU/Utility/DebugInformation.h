#pragma once

/*******************小林陽向*************
* 事前準備
* 
* SceneManagerのUpdateなどの、常に更新されている所にDebugInfomationのUpdateも追加
* 同じくDrawも他の描画がされている所に追加（全描画の後に描画する）
* 
* 
* 使い方
* 
* DebugInfomation.hをインクルード
* 		↓
* Add関数に「表示したい文字 , 変数」を渡して呼び出し
*		↓
* 実行中にXキーで表示
*/
#include "Vector2D.h"										
#include "Dxlib.h"											
#include "PadInput.h"										
															
#include <unordered_map>									

#define DEBUG_X 10
#define DEBUG_Y 100

class DebugInfomation
{
private:
	static std::unordered_map<const char*, float>draw_list;	//描画するデバッグ表示の一覧
	static bool draw_flg;							//デバッグ表示を描画するかどうか
	static bool hit_once;							//キー入力に一回だけ反応する
public:
	//更新
	static void Update();
	//デバッグ表示の描画
	static void Draw();
	//デバッグ表示を追加する
	static void Add(const char* _c, float _num);
	static void Add(const char* _c, int _num);
	static void Add(const char* _c, bool _num);
};



