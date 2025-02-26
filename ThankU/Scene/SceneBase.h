#pragma once

//シーン情報
enum eSceneType
{
	E_TITLE,	//タイトル画面
	E_INGAME,	//インゲーム画面
	E_RESULT,	//リザルト画面
	E_CREDIT,	//クレジット画面
	E_END		//エンド
};

//基底シーンクラス
class SceneBase
{
public:
	SceneBase() {}	//コンストラクタ
	virtual ~SceneBase() {}	//デストラクタ

	int frame;				//フレーム計測
	int animation_image;	//アニメーション画像格納
public:
	//初期化処理
	virtual void Initialize() {}

	//更新処理
	virtual eSceneType Update()
	{
		//フレーム計測
		if (++frame > 6000)
		{
			frame = 0;
		}
		return GetNowScene();
	}

	//描画処理
	virtual void Draw() const {}

	//終了時処理
	virtual void Finalize() {}

	//現在のシーン情報を取得
	virtual eSceneType GetNowScene() const = 0;
};