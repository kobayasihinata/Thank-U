#pragma once
#include"DxLib.h"
#include"../SceneBase.h"

class InGameScene  : public SceneBase
{
public://プロパティ(データ群)
	class Player* Player[4];					

public:	//メソッド(処理群)
	InGameScene();								//インストラクター
	~InGameScene();								//デストラクター

	virtual void Initialize()	override;		//起動時処理
	virtual void Finalize()		override;		//終了時処理
	virtual eSceneType Update()	override;		//恒常処理
	virtual void Draw() const	override;		//描画処理


	//現在のシーン情報を取得
	virtual eSceneType GetNowScene() const override;
private:

};