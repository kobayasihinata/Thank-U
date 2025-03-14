#pragma once
#include"DxLib.h"
#include"../SceneBase.h"
#include "../../Utility/Vector2D.h"

#define WINNER_DRAW_TIME 150

class ResultScene : public SceneBase
{
public://プロパティ(データ群)
	Vector2D score_location[4];	//スコア表示の座標	
	Vector2D winner_draw;		//勝者の描画位置
	int result_num;				//何人分描画中か
	bool result_draw_flg;		//スコアをすべて表示出来たか判断
	int winner_draw_time;		//結果発表までの貯め
	int winner_num;				//同率一位の人数
	bool return_title_flg;		//タイトルに戻れる状態か判断

	//画像用変数
	int bar_image;			//下のバー

	//音声用変数
	int ScoreDisplay_se;			//文字を出すときのSE
	int drum_se;			//ドラムロールSE
	int winner_se;			//勝者のSE
	int ovation_se;			//拍手のSE
	int ovation_se_flg;
	int result_bgm;			//BGM

public:	//メソッド(処理群)
	ResultScene();													//インストラクター
	~ResultScene();													//デストラクター

	virtual void Initialize()	override;							//起動時処理
	virtual void Finalize()		override;							//終了時処理
	virtual eSceneType Update()	override;							//恒常処理
	virtual void Draw() const	override;							//描画処理


	//現在のシーン情報を取得
	virtual eSceneType GetNowScene() const override;

private:
	void UpdateResultsMulti();		//結果発表更新（マルチ）

	void DrawResultsmulti()const;	//結果発表描画（マルチ）

	void UpdateResultsSolo();		//結果発表更新（ソロ）

	void DrawResultsSolo()const;	//結果発表描画（ソロ）

	int CheckWinnerNum()const;		//一番大きいスコアを検知

	void DrawWinner()const;			//勝者を描画
};