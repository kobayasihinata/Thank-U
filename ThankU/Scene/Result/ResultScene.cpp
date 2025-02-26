#include "ResultScene.h"
#include "../../Utility/PadInput.h"
#include "../../Utility/KeyInput.h"
#include "../../Utility/Common.h"
#include "../../Utility/Data.h"

ResultScene::ResultScene() :
	bar_image(0),
	score_location{ 0 },
	winner_draw{ 0 },
	result_num(0),
	result_draw_flg(false),
	winner_draw_time(0),
	winner_num(0),
	ScoreDisplay_se(0),
	drum_se(0),
    winner_se(0),
	ovation_se(0),
	ovation_se_flg(0),
	result_bgm(0),
	return_title_flg(false)
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
		score_location[i] = { 100.f,300.f + (i * 120.f) };
	}
	//プレイヤーが2名以上ならマルチ用の吹き出し位置
	if (Data::player_num >= 2)
	{
		//800=吹き出しを含めたサイズ 400=下基準にした時の移動値
		winner_draw = { SCREEN_WIDTH - 800,SCREEN_HEIGHT - 280 };
	}
	//プレイヤーが1名以下ならソロ用の吹き出し位置
	else
	{
		//500=吹き出しを含めたサイズ 400=下基準にした時の移動値
		winner_draw = { SCREEN_WIDTH - 500,SCREEN_HEIGHT - 280 };
	}
	animation_image = LoadGraph("Rescurce/Image/result.png");
	bar_image = LoadGraph("Rescurce/Image/Line_Message.png");

	ScoreDisplay_se = LoadSoundMem("Rescurce/SE/ScoreDisplay.mp3");
	drum_se = LoadSoundMem("Rescurce/SE/ドラムロール.mp3");
	winner_se = LoadSoundMem("Rescurce/SE/Winner.mp3");
	ovation_se = LoadSoundMem("Rescurce/SE/Ovation.mp3");
	result_bgm = LoadSoundMem("Rescurce/BGM/ResultBGM.wav");

	ovation_se_flg = true;
}

void ResultScene::Finalize()
{
	//全てをリセット
	Data::player_num = 0;
	for (int i = 0; i < 4; i++)
	{
		Data::player_data[i] = { 0 };
	}
	//BGMを停止
	StopSoundMem(result_bgm);
	//SE、BGMを削除
	DeleteSoundMem(ScoreDisplay_se);
	DeleteSoundMem(drum_se);
	DeleteSoundMem(winner_se);
	DeleteSoundMem(result_bgm);
}

eSceneType ResultScene::Update()
{
	__super::Update();

	//キー入力取得
	KeyInput* key_input = KeyInput::Get();

	//プレイヤーが2名以上ならマルチ用の結果発表
	if (Data::player_num >= 2)
	{
		UpdateResultsMulti();
	}
	//プレイヤーが一名以下ならソロ用の結果発表
	else
	{
		UpdateResultsSolo();
	}

	//タイトルに戻って良い時にBボタンでタイトルへ
	if (return_title_flg && PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_B))
	{
		return E_TITLE;
	}
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

	//下のバー描画
	DrawGraph(0, 0, bar_image, true);

	//プレイヤーが2名以上ならマルチ用の結果発表
	if (Data::player_num >= 2)
	{
		DrawResultsmulti();
	}
	//プレイヤーが1名以下ならソロ用の結果発表
	else
	{
		DrawResultsSolo();
	}

	//タイトルに戻れる状態なら教える
	if (return_title_flg)
	{
		DrawString(SCREEN_WIDTH / 2,
			SCREEN_HEIGHT - 100,
			"Bでタイトルへ",
			0xffffff);
	}

	SetFontSize(old);
}

eSceneType ResultScene::GetNowScene() const
{
	return E_RESULT;
}

int ResultScene::CheckWinnerNum()const
{
	//とりあえずプレイヤー１格納
	int ret = Data::player_data[0].score;
	for (int i = 1; i < Data::player_num; i++)
	{
		//スコア比較して一番大きい物を取得
		if (ret < Data::player_data[i].score)
		{
			ret = Data::player_data[i].score;
		}
	}
	return ret;
}

void ResultScene::DrawWinner()const
{
	//勝者表示吹き出し
	Data::DrawSpeechBubble(winner_draw, 700, true);
	//勝者表示文字（前）
	DrawStringF(winner_draw.x,
		winner_draw.y,
		"Player",
		0xffffff
		);
	//勝利者を洗い出す
	int winner_list[4] = { false };
	int winner_count = 0;
	for (int i = 0; i < Data::player_num; i++)
	{
		//プレイヤーのスコアが一位なら
		if (Data::player_data[i].score == CheckWinnerNum())
		{
			//勝利者リストに加える
			winner_list[winner_count] = i;
			winner_count++;
		}
	}
	//勝者表示文字（同率一位も全員表示）
	for (int i = 0; i < winner_count; i++)
	{
		DrawFormatString(winner_draw.x + 220 + (60 * i),
			winner_draw.y,
			0xffffff, "%d",winner_list[i]+1);
	}
	//勝者表示文字（後ろ）
	DrawStringF(winner_draw.x + 220 + (60 * winner_count),
		winner_draw.y,
		"の勝ち！",
		0xffffff);

}

void ResultScene::UpdateResultsMulti()
{
	//60フレーム毎に描画を増やす
	if (frame % 60 == 0 && !result_draw_flg)
	{
		result_num++;
		PlaySoundMem(ScoreDisplay_se, DX_PLAYTYPE_BACK);
	}
	//プレイヤーの数だけ描画が完了したら結果発表に入る
	if (!result_draw_flg && result_num >= Data::player_num)
	{
		result_draw_flg = true;
	}
	//結果発表のカウントダウン
	if (result_draw_flg)
	{
		winner_draw_time++;
		//ドラムロールSE
		if (winner_draw_time == 60)
		{
			PlaySoundMem(drum_se, DX_PLAYTYPE_BACK);
		}
		//祝福SE
		if (winner_draw_time == WINNER_DRAW_TIME)
		{
			StopSoundMem(drum_se);
			PlaySoundMem(winner_se, DX_PLAYTYPE_BACK);
		}
	}
	//BGMが再生される
	if (winner_draw_time > WINNER_DRAW_TIME + 60)
	{
		//拍手SE再生
		if (ovation_se_flg)
		{
			PlaySoundMem(ovation_se, DX_PLAYTYPE_BACK);
			ovation_se_flg = false;
		}

		//リザルトBGM再生
		if (!CheckSoundMem(result_bgm))
		{
			PlaySoundMem(result_bgm, DX_PLAYTYPE_LOOP);
		}	
	}
	//タイトルに戻れるようになる
	if (winner_draw_time > WINNER_DRAW_TIME + 120)
	{
		return_title_flg = true;
	}
}

void ResultScene::DrawResultsmulti()const
{
	//スコア表示
	for (int i = 0; i < Data::player_num; i++)
	{
		//表示していい数以下の描画ならする
		if (result_num > i)
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
				i + 1,
				Data::player_data[i].score,
				Data::player_data[i].great,
				Data::player_data[i].bad);
		}
	}

	SetFontSize(70);
	//勝者表示
	if (winner_draw_time > WINNER_DRAW_TIME)
	{
		//勝者の描画
		DrawWinner();
	}
}

void ResultScene::UpdateResultsSolo()
{
	//60フレーム毎に描画を増やす
	if (frame % 60 == 0 && !result_draw_flg)
	{
		result_num++;
		PlaySoundMem(ScoreDisplay_se, DX_PLAYTYPE_BACK);
	}
	//項目の数だけ描画が完了したら結果発表に入る
	if (!result_draw_flg && result_num >= 2)
	{
		result_draw_flg = true;
	}
	//結果発表のカウントダウン
	if (result_draw_flg)
	{
		winner_draw_time++;
		//ドラムロールSE
		if (winner_draw_time == 60)
		{
			PlaySoundMem(drum_se, DX_PLAYTYPE_BACK);
		}
		//祝福SE
		if (winner_draw_time == WINNER_DRAW_TIME)
		{
			StopSoundMem(drum_se);
			PlaySoundMem(winner_se, DX_PLAYTYPE_BACK);
		}
	}
	//BGMが再生される
	if (winner_draw_time > WINNER_DRAW_TIME + 60)
	{
		//拍手SE再生
		if (Data::player_data->score > 0)
		{
			if (ovation_se_flg)
			{
				PlaySoundMem(ovation_se, DX_PLAYTYPE_BACK);
				ovation_se_flg = false;
			}
		}

		//リザルトBGM再生
		if (!CheckSoundMem(result_bgm))
		{
			PlaySoundMem(result_bgm, DX_PLAYTYPE_LOOP);
		}
	}
	//タイトルに戻れるようになる
	if (winner_draw_time > WINNER_DRAW_TIME + 120)
	{
		return_title_flg = true;
	}
}

void ResultScene::DrawResultsSolo()const
{
	//表示していい数以下の描画ならする
	//グレート獲得数表示
	if (result_num >= 1)
	{
		//横の幅を計算
		int data_width;
		GetDrawFormatStringSize(&data_width, 0, 0, "Great:%d",
			Data::player_data[0].great);
		//吹き出しの描画
		Data::DrawSpeechBubble(score_location[0], data_width, false);

		DrawFormatStringF(score_location[0].x, 
			score_location[0].y, 
			0xffffff,
			"Great:%d",
			Data::player_data[0].great);
	}

	//バッド数表示
	if (result_num >= 2)
	{
		//横の幅を計算
		int data_width;
		GetDrawFormatStringSize(&data_width, 0, 0, "Bad:%d",
			Data::player_data[0].bad);
		//吹き出しの描画
		Data::DrawSpeechBubble(score_location[1], data_width, false);

		DrawFormatStringF(score_location[1].x,
			score_location[1].y,
			0xffffff,
			"Bad:%d",
			Data::player_data[0].bad);
	}

	SetFontSize(70);
	//勝者表示
	if (winner_draw_time > WINNER_DRAW_TIME)
	{
		//スコア発表
		int data_width;
		GetDrawFormatStringSize(&data_width, 0, 0, "Score:%d",
			Data::player_data[0].score);
			//勝者表示吹き出し
		Data::DrawSpeechBubble(winner_draw, data_width, true);
		//勝者表示文字
		DrawFormatStringF(winner_draw.x,
			winner_draw.y,
			0xffffff,
			"Score:%d",
			Data::player_data[0].score);
	}
}