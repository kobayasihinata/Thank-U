#include "ResultScene.h"
#include "../../Utility/PadInput.h"
#include "../../Utility/KeyInput.h"
#include "../../Utility/Common.h"
#include "../../Utility/Data.h"

ResultScene::ResultScene() :
	frame(0),
	bar_image(0),
	score_location{ 0 },
	winner_draw{ 0 },
	result_num(0),
	result_draw_flg(false),
	winner_draw_time(0),
	winner_num(0),
	talk_se(0),
	drum_se(0),
    winner_se(0),
	result_bgm(0)
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
	//400=�����o�����܂߂��T�C�Y 200=����ɂ������̈ړ��l
	winner_draw = { SCREEN_WIDTH - 800,SCREEN_HEIGHT - 400 };

	animation_image = LoadGraph("Rescurce/Image/result.png");
	bar_image = LoadGraph("Rescurce/Image/Line_Message.png");

	talk_se = LoadSoundMem("Rescurce/SE/Talking.mp3");
	drum_se = LoadSoundMem("Rescurce/SE/�h�������[��.mp3");
	winner_se = LoadSoundMem("Rescurce/SE/Winner.mp3");
	result_bgm = LoadSoundMem("Rescurce/BGM/ResultBGM.wav");
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
	DeleteSoundMem(talk_se);
	DeleteSoundMem(drum_se);
	DeleteSoundMem(winner_se);
	DeleteSoundMem(result_bgm);
}

eSceneType ResultScene::Update()
{
	__super::Update();

	//�t���[������
	frame++;

	KeyInput* key_input = KeyInput::Get();

	//60�t���[�����ɕ`��𑝂₷
	if (frame % 60 == 0 && !result_draw_flg)
	{
		result_num++;
		PlaySoundMem(talk_se, DX_PLAYTYPE_BACK);
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
		//���U���gBGM�Đ�
		if (!CheckSoundMem(result_bgm))
		{
			PlaySoundMem(result_bgm, DX_PLAYTYPE_LOOP);
		}
	}
	//�^�C�g���ɖ߂��悤�ɂȂ�
	if (winner_draw_time > WINNER_DRAW_TIME + 120)
	{

		//B�{�^�����X�y�[�X�L�[�Ń^�C�g����
		if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_B))
		{
			return E_TITLE;
		}
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
				i+1,
				Data::player_data[i].score,
				Data::player_data[i].great,
				Data::player_data[i].bad);
		}
	}

	//���̃o�[�`��
	DrawGraph(0, 0, bar_image, true);
	//�^�C�g���ɖ߂�鎖��������
	if (winner_draw_time > WINNER_DRAW_TIME + 120)
	{
		DrawString(SCREEN_WIDTH / 2 - GetDrawFormatStringSize(0, 0, 0, "B�Ń^�C�g����"),
			SCREEN_HEIGHT - 100,
			"B�Ń^�C�g����",
			0xffffff);
	}

	SetFontSize(70);
	//���ҕ\��
	if (winner_draw_time > WINNER_DRAW_TIME)
	{
		//���҂̕`��
		DrawWinner();
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
		if (Data::player_data[ret].score < Data::player_data[i].score)
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
	DrawFormatStringF(winner_draw.x,
		winner_draw.y,
		0xffffff,
		"Player",
		CheckWinnerNum());
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
	DrawFormatStringF(winner_draw.x + 220 + (60 * winner_count),
		winner_draw.y,
		0xffffff,
		"�̏����I",
		CheckWinnerNum());

}