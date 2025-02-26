#include "CreditScene.h"
#include "../../Utility/PadInput.h"
#include "../../Utility/KeyInput.h"
#include "../../Utility/DebugInformation.h"

//コンストラクタ
CreditScene::CreditScene() :count(150), scrollY(SCREEN_HEIGHT),
background_image(0), credit_logo(0), object_image()
{
}

//デストラクタ
CreditScene::~CreditScene() {}

//初期化
void CreditScene::Initialize()
{
	//タイトルBGM再生
	PlaySoundFile("Rescurce/BGM/CreditBGM.wav", DX_PLAYTYPE_LOOP);

	//背景画像
	background_image = LoadGraph("Rescurce/Image/background.png");
	//ロゴ
	credit_logo = LoadGraph("Rescurce/Image/CreditLogo.png");
	//各オブジェクト
	object_image[0] = LoadGraph("Rescurce/Image/Line_Message.png");

	//ここでエフェクトの初期化 --＞ 画像の読み込みとか
	//effect.Initialize();
}

//終了時処理
void CreditScene::Finalize()
{
	//BGMを止める
	StopSoundFile();
}

//更新処理
eSceneType CreditScene::Update()
{
	//親クラスの更新処理を呼び出す
	__super::Update();

	//キーボード入力処理のインスタンスを取得
	KeyInput* key_input = KeyInput::Get();

	/* * * * * * * * * * * * * * * * エフェクト関連　* * * * * * * * * * * */

	if (key_input->GetKeyState(KEY_INPUT_E) == eInputState::Pressed)
	{
		// Eキーが押されたらエフェクト
		//effect.Set(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, EFF_EXPLODE);
		DebugInfomation::Add("Effect Set", true); // デバッグ用
	}

	////大体３秒くらいエフェクトを出す＜---お試し
	//if (count > 0) {
	//	for (int i = 0; i < 5; ++i)
	//	{
	//		int randomX = std::rand() % SCREEN_WIDTH;
	//		int randomY = std::rand() % SCREEN_HEIGHT;
	//		effect.Set(randomX, randomY, EFF_EXPLODE);
	//	}
	//}
	//count--;

	// エフェクトを更新
	//effect.Update();

	/* * * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * */

	//スクロール量を加算
	scrollY -= 2.0f;

	//テキストが画面外に行ったらエンドへ遷移する
	if (scrollY < -1300) return E_TITLE;

	//デバッグ時処理
#if _DEBUG
	//タイトルへ遷移する(デバッグ用)
	if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_B) || key_input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		return E_TITLE;
	}

	//デバッグ用(Xキー)
	DebugInfomation::Add("count", count);
	DebugInfomation::Add("scrollY", scrollY);

#endif
	//現在のシーンを返す
	return GetNowScene();
}

//描画処理
void CreditScene::Draw() const
{
	int y = 50;	//文字間隔
	int startX = SCREEN_HEIGHT / 2; //真ん中ちょい左くらいの座標
	int currentY = scrollY - 200; // 現在のY位置

	//背景画像
	DrawGraph(0, 0, background_image, true);

	//枠

	//クレジット表記
	DrawString(startX, currentY += y * 2, "--Credit--", 0xffffff);
	DrawString(startX, currentY += y * 2, "◇ゲーム制作", 0xffffff);
	DrawString(startX, currentY += y, "Team Thank U", 0xffffff);
	DrawString(startX, currentY += y * 2, "◇メンバー", 0xffffff);
	DrawString(startX, currentY += y, "ひなた", 0xffffff);
	DrawString(startX, currentY += y, "まなと", 0xffffff);
	DrawString(startX, currentY += y, "としき", 0xffffff);
	DrawString(startX, currentY += y, "きょういちろう", 0xffffff);
	DrawString(startX, currentY += y * 2, "◇ツール", 0xffffff);
	DrawString(startX, currentY += y, "VisualStudio", 0xffffff);
	DrawString(startX, currentY += y * 2, "◇BGM", 0xffffff);
	DrawString(startX, currentY += y, "きょういちろう", 0xffffff);
	DrawString(startX, currentY += y * 2, "◇SE", 0xffffff);
	DrawString(startX, currentY += y, "効果音ラボ 様", 0xffffff);
	DrawString(startX, currentY += y * 2, "◇イラスト素材", 0xffffff);
	DrawString(startX, currentY += y, "ひなた", 0xffffff);
	DrawString(startX, currentY += y, "まなと", 0xffffff);

	//画像の描画
	DrawGraph(0, 0, object_image[0], true);
	DrawGraph(0, 0, credit_logo, true);

#if _DEBUG
	DrawString(SCREEN_WIDTH / 1.5, SCREEN_HEIGHT / 13, "Pad B or Spaceでタイトル", 0xffffff);
#endif

	//エフェクトの描画
	//effect.Draw();
}

//現在シーン情報を取得
eSceneType CreditScene::GetNowScene() const
{
	return E_CREDIT;
}

