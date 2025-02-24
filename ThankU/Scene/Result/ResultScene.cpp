#include "ResultScene.h"
#include "../../Utility/PadInput.h"
#include "../../Utility/KeyInput.h"
#include "../../Utility/Common.h"
#include "../../Utility/Data.h"

ResultScene::ResultScene():frame(0)
{
	
}

ResultScene::~ResultScene()
{

}

void ResultScene::Initialize()
{
	animation_image = LoadGraph("Rescurce/Image/background.png");
	bar_image = LoadGraph("Rescurce/Image/Line_Message.png");
}

void ResultScene::Finalize()
{

}

eSceneType ResultScene::Update()
{
	__super::Update();

	//フレーム測定
	frame++;

	KeyInput* key_input = KeyInput::Get();

	//デバッグ時処理
#if _DEBUG

	//Bボタンかスペースキーでタイトルへ
	if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_B) || key_input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		return E_TITLE;
	}
#endif //  DEBUG
	//現在のシーンを返す
	return GetNowScene();
}

void ResultScene::Draw() const
{
	//背景画像
	DrawGraph(0, 0, animation_image, false);

	//スコア表示
	for (int i = 0; i < Data::player_num; i++)
	{
		DrawFormatString(100, 100 + (i * 50), 0x000000,
			"Player%d  Score:%d Great:%d Bad:%d",
			i,
			Data::player_data[i].score,
			Data::player_data[i].great,
			Data::player_data[i].bad);
	}
	//下のバー描画
	DrawGraph(0, 0, bar_image, true);
#if _DEBUG
	DrawString(0, 0, "Result", 0x000000);
	DrawString(0, 20, "Pad B  or  Spaceでタイトル", 0x000000);
#endif
}

eSceneType ResultScene::GetNowScene() const
{
	return E_RESULT;
}