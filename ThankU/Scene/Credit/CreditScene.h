#pragma once
#include"DxLib.h"
#include"../SceneBase.h"
#include "../../Utility/Common.h"
#include "../../Utility/Effect.h"

class CreditScene : public SceneBase
{
private://エフェクト関連
	//ここにエフェクトのランダム計算とかカウントに使う変数とかを宣言

public://プロパティ(データ群)

	int count;	//一定時間経過で終了
	int scrollY; //スクロール初期位置

public:
	//エフェクトを使用する際必要
	Effect effect;

private:
	int background_image;	//背景
	int credit_logo;		//ロゴ
	int object_image[5];	//各オブジェクト

public:	//メソッド(処理群)
	CreditScene();			//インストラクター
	~CreditScene();			//デストラクター

	virtual void Initialize()	override;	//起動時処理
	virtual void Finalize()		override;	//終了時処理
	virtual eSceneType Update()	override;	//恒常処理
	virtual void Draw() const	override;	//描画処理


	//現在のシーン情報を取得
	virtual eSceneType GetNowScene() const override;
private:

};