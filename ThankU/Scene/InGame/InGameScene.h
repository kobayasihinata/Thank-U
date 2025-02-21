#pragma once
#include"DxLib.h"
#include"../SceneBase.h"

class InGameScene 
{
public://プロパティ(データ群)

public:	//メソッド(処理群)
	InGameScene();			//インストラクター
	~InGameScene();			//デストラクター

	void Initialize();		//起動時処理
	void Finalize();		//終了時処理
	void Update();			//恒常処理
	void Draw();			//描画処理


private:

};