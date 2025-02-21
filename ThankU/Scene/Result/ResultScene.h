#pragma once
#include"DxLib.h"
#include"../SceneBase.h"

class ResultScene : public SceneBase
{
public://プロパティ(データ群)
	int result_image;	//タイトル画像格納
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

};