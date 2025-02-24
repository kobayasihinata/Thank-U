#pragma once
#include"DxLib.h"
#include"../SceneBase.h"
#include   "../../Utility/Common.h"

class CreditScene : public SceneBase
{
public://プロパティ(データ群)
	int count = 3600;	//一定時間経過で終了
	int scrollY = SCREEN_HEIGHT; // Starting Y position

private:
	int background_image;
	int object_image[5];

public:	//メソッド(処理群)
	CreditScene();													//インストラクター
	~CreditScene();													//デストラクター

	virtual void Initialize()	override;							//起動時処理
	virtual void Finalize()		override;							//終了時処理
	virtual eSceneType Update()	override;							//恒常処理
	virtual void Draw() const	override;							//描画処理


	//現在のシーン情報を取得
	virtual eSceneType GetNowScene() const override;
private:

};