#pragma once
#include"DxLib.h"
#include   "../../Utility/Common.h"
#include   "../../Utility/Vector2D.h"
#include"../SceneBase.h"

//タイトルシーンクラス
class TitleScene : public SceneBase
{
private:
	class EffectManager* e_manager;		//マネージャー情報
	int cursor;							//メニューカーソル
	bool player_button_flg[4];			//各プレイヤーのABXYいずれかのボタンを押したかを格納(描画用)
	float cursor_size;					//カーソルの表示サイズ
	bool game_start_flg;				//ゲーム開始演出中か判断
	int game_start_timer;				//ゲーム開始演出測定

	//各画像
	int title_image;					//タイトル背景
	int title_logo;						//タイトルロゴ
	int object_image[13];				//オブジェクト
	int message_image[10];				//メッセージ画像

	//SE
	int SE_Cursor;
	int SE_Decision;

	int random_image_timer = 0; // タイマー変数の初期化
	int current_image_index = rand() % 9; // ランダムな画像の初期選択

private:
	//オブジェクト管理用変数
	float message_x;		//メッセージアイコンの X 位置
	float scale;			//大きさ
	bool scaling_up;		//スケールを大きくするか小さくするかのフラグ ＜-- 多分使わない
	Vector2D obj_location;	//オブジェクトの座標

private: //＜--参加人数をここで決めるのあればパブリックの方がいいかもしれない

	float player_icon_x[4]; //参加者アイコンの X 位置
	bool player_join[4];	//参加フラグ
	int join_flag;	//描画用フラグ

private:
	//エフェクト用	＜--エフェクト同様、パーティクルのクラスももしかしたら必要になるかも

	int alpha;				// フェードイン用のアルファ値
	int fadein_timer;		// フェードインのタイマー

public:	//メソッド(処理群)
	TitleScene();													//インストラクター
	~TitleScene();													//デストラクター

	virtual void Initialize()	override;	//初期化処理
	virtual void Finalize()		override;	//終了時処理
	virtual eSceneType Update()	override;	//更新処理
	virtual void Draw() const	override;	//描画処理

	//現在のシーン情報を取得
	virtual eSceneType GetNowScene() const override;

private:
	//オブジェクトの演出処理
	void ObjectMove();

	//そのコントローラーが既にゲームに参加しているか取得 
	//_pad=確認するコントローラー 戻り値 使っているプレイヤー(-1は誰も使っていない)
	int CheckUseController(int _pad);

	//星が弾けるエフェクトを出す
	void StarBurst(Vector2D _loc)const;
};