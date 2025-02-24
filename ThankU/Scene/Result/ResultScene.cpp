#include "ResultScene.h"
#include "../../Utility/PadInput.h"
#include "../../Utility/KeyInput.h"
#include "../../Utility/Common.h"
#include "../../Utility/Data.h"

ResultScene::ResultScene():
	frame(0), 
	bar_image(0),
	score_location{0},
	winner_draw{0}
{
	
}

ResultScene::~ResultScene()
{

}

void ResultScene::Initialize()
{
	//初期化
	for (int i = 0; i < 4; i++)
	{
		score_location[i] = { 100.f,100.f + (i * 120.f) };
	}
	//400=吹き出しを含めたサイズ 200=下基準にした時の移動値
	winner_draw = { SCREEN_WIDTH - 500,SCREEN_HEIGHT - 200 };

	animation_image = LoadGraph("Rescurce/Image/result.png");
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
	int old = GetFontSize();
	SetFontSize(50);
	//背景画像
	DrawGraph(0, 0, animation_image, false);

	//スコア表示
	for (int i = 0; i < Data::player_num; i++)
	{
		//横の幅を計算
		int data_width;
		GetDrawFormatStringSize(&data_width, 0, 0, "Player%d  Score:%d Great:%d Bad:%d",
			i,
			Data::player_data[i].score,
			Data::player_data[i].great,
			Data::player_data[i].bad);
		//吹き出しの描画
		Data::DrawSpeechBubble(score_location[i], data_width, false);

		DrawFormatStringF(score_location[i].x, score_location[i].y, 0xffffff,
			"Player%d  Score:%d Great:%d Bad:%d",
			i,
			Data::player_data[i].score,
			Data::player_data[i].great,
			Data::player_data[i].bad);
	}

	//勝者表示
	Data::DrawSpeechBubble(winner_draw, 350, true);
	//勝者表示文字
	DrawFormatStringF(winner_draw.x,
		winner_draw.y, 
		0xffffff,
		"Winner:Player %d !",
		0);

	//下のバー描画
	DrawGraph(0, 0, bar_image, true);
#if _DEBUG
	DrawString(0, 0, "Result", 0x000000);
	DrawString(0, 20, "Pad B  or  Spaceでタイトル", 0x000000);
#endif

	SetFontSize(old);
}

eSceneType ResultScene::GetNowScene() const
{
	return E_RESULT;
}