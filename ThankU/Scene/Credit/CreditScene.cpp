#include "CreditScene.h"
#include "../../Utility/PadInput.h"
#include "../../Utility/KeyInput.h"
#include "../../Utility/DebugInformation.h"

CreditScene::CreditScene()
{
	count = 300;
}

CreditScene::~CreditScene(){}

//初期化
void CreditScene::Initialize(){}

//終了時処理
void CreditScene::Finalize(){}

//更新処理
eSceneType CreditScene::Update()
{
	//親クラスの更新処理を呼び出す
	__super::Update();

	//スクロール量を加算
	scrollY -= 1.5f; 

	//テキストが画面外に行ったらエンドへ遷移する
	if (scrollY < -1300) return E_END;

	//キーボード入力処理のインスタンスを取得
	KeyInput* key_input = KeyInput::Get();
	
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
	int currentY = scrollY; // 現在のY位置

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

#if _DEBUG
	DrawString(SCREEN_WIDTH / 1.5, SCREEN_HEIGHT/13, "Pad B or Spaceでタイトル", 0xffffff);
#endif
}

eSceneType CreditScene::GetNowScene() const
{
	return E_CREDIT;
}