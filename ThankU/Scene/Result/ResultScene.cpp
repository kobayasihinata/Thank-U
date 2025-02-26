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
	//������
	for (int i = 0; i < 4; i++)
	{
		score_location[i] = { 100.f,300.f + (i * 120.f) };
	}
	//�v���C���[��2���ȏ�Ȃ�}���`�p�̐����o���ʒu
	if (Data::player_num >= 2)
	{
		//800=�����o�����܂߂��T�C�Y 400=����ɂ������̈ړ��l
		winner_draw = { SCREEN_WIDTH - 800,SCREEN_HEIGHT - 280 };
	}
	//�v���C���[��1���ȉ��Ȃ�\���p�̐����o���ʒu
	else
	{
		//500=�����o�����܂߂��T�C�Y 400=����ɂ������̈ړ��l
		winner_draw = { SCREEN_WIDTH - 500,SCREEN_HEIGHT - 280 };
	}
	animation_image = LoadGraph("Rescurce/Image/result.png");
	bar_image = LoadGraph("Rescurce/Image/Line_Message.png");

	ScoreDisplay_se = LoadSoundMem("Rescurce/SE/ScoreDisplay.mp3");
	drum_se = LoadSoundMem("Rescurce/SE/�h�������[��.mp3");
	winner_se = LoadSoundMem("Rescurce/SE/Winner.mp3");
	ovation_se = LoadSoundMem("Rescurce/SE/Ovation.mp3");
	result_bgm = LoadSoundMem("Rescurce/BGM/ResultBGM.wav");

	ovation_se_flg = true;
}

void ResultScene::Finalize()
{
	//�S�Ă����Z�b�g
	Data::player_num = 0;
	for (int i = 0; i < 4; i++)
	{
		Data::player_data[i] = { 0 };
	}
	//BGM���~
	StopSoundMem(result_bgm);
	//SE�ABGM���폜
	DeleteSoundMem(ScoreDisplay_se);
	DeleteSoundMem(drum_se);
	DeleteSoundMem(winner_se);
	DeleteSoundMem(result_bgm);
}

eSceneType ResultScene::Update()
{
	__super::Update();

	//�L�[���͎擾
	KeyInput* key_input = KeyInput::Get();

	//�v���C���[��2���ȏ�Ȃ�}���`�p�̌��ʔ��\
	if (Data::player_num >= 2)
	{
		UpdateResultsMulti();
	}
	//�v���C���[���ꖼ�ȉ��Ȃ�\���p�̌��ʔ��\
	else
	{
		UpdateResultsSolo();
	}

	//�^�C�g���ɖ߂��ėǂ�����B�{�^���Ń^�C�g����
	if (return_title_flg && PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_B))
	{
		return E_TITLE;
	}
	//�f�o�b�O������
#if _DEBUG

	//B�{�^�����X�y�[�X�L�[�Ń^�C�g����
	if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_B) || key_input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		return E_TITLE;
	}
#endif //  DEBUG
	//���݂̃V�[����Ԃ�
	return GetNowScene();
}

void ResultScene::Draw() const
{
	int old = GetFontSize();
	SetFontSize(50);
	//�w�i�摜
	DrawGraph(0, 0, animation_image, false);

	//���̃o�[�`��
	DrawGraph(0, 0, bar_image, true);

	//�v���C���[��2���ȏ�Ȃ�}���`�p�̌��ʔ��\
	if (Data::player_num >= 2)
	{
		DrawResultsmulti();
	}
	//�v���C���[��1���ȉ��Ȃ�\���p�̌��ʔ��\
	else
	{
		DrawResultsSolo();
	}

	//�^�C�g���ɖ߂���ԂȂ狳����
	if (return_title_flg)
	{
		DrawString(SCREEN_WIDTH / 2,
			SCREEN_HEIGHT - 100,
			"B�Ń^�C�g����",
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
	//�Ƃ肠�����v���C���[�P�i�[
	int ret = Data::player_data[0].score;
	for (int i = 1; i < Data::player_num; i++)
	{
		//�X�R�A��r���Ĉ�ԑ傫�������擾
		if (ret < Data::player_data[i].score)
		{
			ret = Data::player_data[i].score;
		}
	}
	return ret;
}

void ResultScene::DrawWinner()const
{
	//���ҕ\�������o��
	Data::DrawSpeechBubble(winner_draw, 700, true);
	//���ҕ\�������i�O�j
	DrawStringF(winner_draw.x,
		winner_draw.y,
		"Player",
		0xffffff
		);
	//�����҂�􂢏o��
	int winner_list[4] = { false };
	int winner_count = 0;
	for (int i = 0; i < Data::player_num; i++)
	{
		//�v���C���[�̃X�R�A����ʂȂ�
		if (Data::player_data[i].score == CheckWinnerNum())
		{
			//�����҃��X�g�ɉ�����
			winner_list[winner_count] = i;
			winner_count++;
		}
	}
	//���ҕ\�������i������ʂ��S���\���j
	for (int i = 0; i < winner_count; i++)
	{
		DrawFormatString(winner_draw.x + 220 + (60 * i),
			winner_draw.y,
			0xffffff, "%d",winner_list[i]+1);
	}
	//���ҕ\�������i���j
	DrawStringF(winner_draw.x + 220 + (60 * winner_count),
		winner_draw.y,
		"�̏����I",
		0xffffff);

}

void ResultScene::UpdateResultsMulti()
{
	//60�t���[�����ɕ`��𑝂₷
	if (frame % 60 == 0 && !result_draw_flg)
	{
		result_num++;
		PlaySoundMem(ScoreDisplay_se, DX_PLAYTYPE_BACK);
	}
	//�v���C���[�̐������`�悪���������猋�ʔ��\�ɓ���
	if (!result_draw_flg && result_num >= Data::player_num)
	{
		result_draw_flg = true;
	}
	//���ʔ��\�̃J�E���g�_�E��
	if (result_draw_flg)
	{
		winner_draw_time++;
		//�h�������[��SE
		if (winner_draw_time == 60)
		{
			PlaySoundMem(drum_se, DX_PLAYTYPE_BACK);
		}
		//�j��SE
		if (winner_draw_time == WINNER_DRAW_TIME)
		{
			StopSoundMem(drum_se);
			PlaySoundMem(winner_se, DX_PLAYTYPE_BACK);
		}
	}
	//BGM���Đ������
	if (winner_draw_time > WINNER_DRAW_TIME + 60)
	{
		//����SE�Đ�
		if (ovation_se_flg)
		{
			PlaySoundMem(ovation_se, DX_PLAYTYPE_BACK);
			ovation_se_flg = false;
		}

		//���U���gBGM�Đ�
		if (!CheckSoundMem(result_bgm))
		{
			PlaySoundMem(result_bgm, DX_PLAYTYPE_LOOP);
		}	
	}
	//�^�C�g���ɖ߂��悤�ɂȂ�
	if (winner_draw_time > WINNER_DRAW_TIME + 120)
	{
		return_title_flg = true;
	}
}

void ResultScene::DrawResultsmulti()const
{
	//�X�R�A�\��
	for (int i = 0; i < Data::player_num; i++)
	{
		//�\�����Ă������ȉ��̕`��Ȃ炷��
		if (result_num > i)
		{

			//���̕����v�Z
			int data_width;
			GetDrawFormatStringSize(&data_width, 0, 0, "Player%d  Score:%d Great:%d Bad:%d",
				i,
				Data::player_data[i].score,
				Data::player_data[i].great,
				Data::player_data[i].bad);
			//�����o���̕`��
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
	//���ҕ\��
	if (winner_draw_time > WINNER_DRAW_TIME)
	{
		//���҂̕`��
		DrawWinner();
	}
}

void ResultScene::UpdateResultsSolo()
{
	//60�t���[�����ɕ`��𑝂₷
	if (frame % 60 == 0 && !result_draw_flg)
	{
		result_num++;
		PlaySoundMem(ScoreDisplay_se, DX_PLAYTYPE_BACK);
	}
	//���ڂ̐������`�悪���������猋�ʔ��\�ɓ���
	if (!result_draw_flg && result_num >= 2)
	{
		result_draw_flg = true;
	}
	//���ʔ��\�̃J�E���g�_�E��
	if (result_draw_flg)
	{
		winner_draw_time++;
		//�h�������[��SE
		if (winner_draw_time == 60)
		{
			PlaySoundMem(drum_se, DX_PLAYTYPE_BACK);
		}
		//�j��SE
		if (winner_draw_time == WINNER_DRAW_TIME)
		{
			StopSoundMem(drum_se);
			PlaySoundMem(winner_se, DX_PLAYTYPE_BACK);
		}
	}
	//BGM���Đ������
	if (winner_draw_time > WINNER_DRAW_TIME + 60)
	{
		//����SE�Đ�
		if (Data::player_data->score > 0)
		{
			if (ovation_se_flg)
			{
				PlaySoundMem(ovation_se, DX_PLAYTYPE_BACK);
				ovation_se_flg = false;
			}
		}

		//���U���gBGM�Đ�
		if (!CheckSoundMem(result_bgm))
		{
			PlaySoundMem(result_bgm, DX_PLAYTYPE_LOOP);
		}
	}
	//�^�C�g���ɖ߂��悤�ɂȂ�
	if (winner_draw_time > WINNER_DRAW_TIME + 120)
	{
		return_title_flg = true;
	}
}

void ResultScene::DrawResultsSolo()const
{
	//�\�����Ă������ȉ��̕`��Ȃ炷��
	//�O���[�g�l�����\��
	if (result_num >= 1)
	{
		//���̕����v�Z
		int data_width;
		GetDrawFormatStringSize(&data_width, 0, 0, "Great:%d",
			Data::player_data[0].great);
		//�����o���̕`��
		Data::DrawSpeechBubble(score_location[0], data_width, false);

		DrawFormatStringF(score_location[0].x, 
			score_location[0].y, 
			0xffffff,
			"Great:%d",
			Data::player_data[0].great);
	}

	//�o�b�h���\��
	if (result_num >= 2)
	{
		//���̕����v�Z
		int data_width;
		GetDrawFormatStringSize(&data_width, 0, 0, "Bad:%d",
			Data::player_data[0].bad);
		//�����o���̕`��
		Data::DrawSpeechBubble(score_location[1], data_width, false);

		DrawFormatStringF(score_location[1].x,
			score_location[1].y,
			0xffffff,
			"Bad:%d",
			Data::player_data[0].bad);
	}

	SetFontSize(70);
	//���ҕ\��
	if (winner_draw_time > WINNER_DRAW_TIME)
	{
		//�X�R�A���\
		int data_width;
		GetDrawFormatStringSize(&data_width, 0, 0, "Score:%d",
			Data::player_data[0].score);
			//���ҕ\�������o��
		Data::DrawSpeechBubble(winner_draw, data_width, true);
		//���ҕ\������
		DrawFormatStringF(winner_draw.x,
			winner_draw.y,
			0xffffff,
			"Score:%d",
			Data::player_data[0].score);
	}
}