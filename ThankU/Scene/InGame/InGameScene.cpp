#include "InGameScene.h"
#include "../../Utility/PadInput.h"
#if _DEBUG
#include "../../Utility/KeyInput.h"
#endif // _DEBUG


//�v���C���[��x���W(���L)
#define P_X 1700
//�v���C���[��y���W(���L)
#define P_Y  50

/// <summary>
///�@�C���X�g���N�^
/// </summary>
/// <param></param>
/// <returns></returns>
InGameScene::InGameScene():
	Anserd{ (true),(true),(true),(true) },
	Background_image(NULL),
	Border_Line(NULL),
	Collect{ (false),(false),(false),(false)},
	EnemyImage(NULL),
	FatalAnser(none),
	FatalAnserNum(NULL),
	InGameHelp(NULL),
	Pagree{ NULL,NULL,NULL,NULL },
	PlayerImage{ NULL,NULL,NULL,NULL },
	Player_Anser{none,none,none,none},
	PlayerScore{ NULL,NULL,NULL,NULL },
	QSet(true),
	SE_Correct(NULL),
	ScoreValue{ NULL,NULL,NULL,NULL }
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
/// <param></param>
/// <returns></returns>
InGameScene::~InGameScene()
{
}

/// <summary>
/// �J�n������
/// </summary>
/// <param></param>
/// <returns></returns>
void InGameScene::Initialize()
{
	PlaySoundFile("Rescurce/BGM/InGameBGM.wav", DX_PLAYTYPE_LOOP);
	SE_Correct			= LoadSoundMem("Rescurce/SE/Correct.mp3");
	SE_Talk				= LoadSoundMem("Rescurce/SE/Talking.mp3");
	SE_MessageDelete	= LoadSoundMem("Rescurce/SE/MessageDelete.mp3");

	Timer = -1;

	for (int i = 0; i < Data::player_num; i++)
	{
		Collect[i] = true;
		Pagree[i] = 0;
		right[i] = -1;
	}

	switch (Data::player_num)
	{
	case 4:
		PlayerImage[3] = LoadGraph("Rescurce/Image/Player4.png");
	case 3:
		PlayerImage[2] = LoadGraph("Rescurce/Image/Player3.png");
	case 2:
		PlayerImage[1] = LoadGraph("Rescurce/Image/Player2.png");
	case 1:
		PlayerImage[0] = LoadGraph("Rescurce/Image/Player1.png");
	}
	PlayerTextImage = LoadGraph("Rescurce/Image/MessageFrame_1.png");

	switch (Data::player_num)
	{
	case 4:
		TotalScore = 2500;
		break;
	case 3:
		TotalScore = 2000;
		break;
	case 2:
		TotalScore = 1000;
		break;
	case 1:
		TotalScore = 500;
		break;
	}

	EnemyString = read_csv("Rescurce/EnemyVoice.csv");

	/*EnemyString = {
		{"�|�W�e�B�u�Ȏ���1", "�|�W�e�B�u�Ȏ���2", "�|�W�e�B�u�Ȏ���3", "�|�W�e�B�u�Ȏ���4", "�|�W�e�B�u�Ȏ���5"},
		{"�l�K�e�B�u�Ȏ���1", "�l�K�e�B�u�Ȏ���2", "�l�K�e�B�u�Ȏ���3", "�l�K�e�B�u�Ȏ���4", "�l�K�e�B�u�Ȏ���5"},
		{"�^��n�̎���1", "�^��n�̎���2", "�^��n�̎���3", "�^��n�̎���4", "�^��n�̎���5"},
		{"����グ�鎿��1", "����グ�鎿��2", "����グ�鎿��3", "����グ�鎿��4", "����グ�鎿��5"}
	};*/

	PString = { "�E�@�E�@�E","�������ˁI","����Ȃ��ƂȂ���I","�����Ȃ́H","���ꂩ��H"};
	Question =  "�E �E �E";

	Background_image	=	LoadGraph("Rescurce/Image/background.png")		;
	Border_Line			=	LoadGraph("Rescurce/Image/Line_Message.png")	;
	EnemyTextImage		=	LoadGraph("Rescurce/Image/MessageFrame_2.png")	;
	EnemyImage			=	LoadGraph("Rescurce/Image/Icon.png")			;
	false_Message		=	LoadGraph("Rescurce/Image/MessageCancel.png")	;
	InGameHelp			=	LoadGraph("Rescurce/Image/InGameButton.png")	;
	Collect1st_Image	=	LoadGraph("Rescurce/Image/Great_1.png")			;
	Collect2nd_Image	=	LoadGraph("Rescurce/Image/Great_2.png")			;
	Bad_Image			=	LoadGraph("Rescurce/Image/Bad.png")				;
}

/// <summary>
/// �I��������
/// </summary>
/// <param></param>
/// <returns></returns>
void InGameScene::Finalize()
{
	StopSoundFile();
}

/// <summary>
/// �Q�[����ʂ̕`�������
/// </summary>
/// <param></param>
/// <returns></returns>
void InGameScene::Draw() const
{
	//�w�i�摜
	DrawReverseGraph(0, 0, Background_image, false,1);

	//�G�l�~�[�֌W 800 100
	//DrawReverseGraph(50, 100, EnemyImage, true,1);
	DrawGraph(50, 50, EnemyImage, true);
	DrawFormatString(180, 70, 0xFFFFFF, "�e�F�|�C���g�c��:%d", TotalScore);
	Data::DrawSpeechBubble(Vector2D(50, 200), Question.length()*25, false);
	DrawFormatString(50, 200, 0xFFFFFF, "%s", Question.c_str());

 	DrawGraph(0, 0, Border_Line, true);
	DrawGraph(50, 500, InGameHelp, true);
	//�l���ɍ��킹�ĕ`��
	switch (Data::player_num)
	{
	case 4:
		if (Collect[3] == false)
		{
			DrawGraph(880, 750, false_Message, true);
			//DrawFormatString(880, 750, 0x000000, "<���b�Z�[�W���폜����܂���>");
		}
		else {
			DrawGraph(P_X, P_Y + 600, PlayerImage[3], true);
			if (Pagree[3] == 2)//�����p����
			{
				Data::DrawSpeechBubble(Vector2D(P_X - 450, P_Y + 700), PString[Pagree[3]].length() * 20, true);
				DrawFormatString(P_X - 450, P_Y + 700, 0x000000, "%s", PString[Pagree[3]].c_str());
			}
			else
			{
				Data::DrawSpeechBubble(Vector2D(P_X - 250, P_Y + 700), PString[Pagree[3]].length() * 20, true);
				DrawFormatString(P_X - 260, P_Y + 700, 0x000000, "%s", PString[Pagree[3]].c_str());
			}
		}
		if (Data::player_data[3].score < 0)//�X�R�A�̕\��
		{
			DrawFormatString(P_X + 100, P_Y + 700, 0xFF0000, "%d", Data::player_data[3].score);
		}
		else {
			DrawFormatString(P_X + 100, P_Y + 700, 0x000000, "%d", Data::player_data[3].score);
		}
		if (right[3] == 1)
		{
			DrawRotaGraph(P_X - 200, P_Y + 700, 1.0, (-45 / 180 + 1), Collect1st_Image, true);
		}
		else if (right[3] == 0)
		{
			DrawRotaGraph(P_X - 200, P_Y + 700, 1.0, (-45 / 180 + 1), Bad_Image, true);
		}

	case 3:
		if (Collect[2] == false)
		{
			DrawGraph(880, 550, false_Message, true);
			//DrawFormatString(880, 550, 0x000000, "<���b�Z�[�W���폜����܂���>");
		}
		else {
			DrawGraph(P_X, P_Y + 400, PlayerImage[2], true);
			if (Pagree[2] == 2)//�����p����
			{
				Data::DrawSpeechBubble(Vector2D(P_X - 450, P_Y + 500), PString[Pagree[2]].length() * 20, true);
				DrawFormatString(P_X - 450, P_Y + 500, 0x000000, "%s", PString[Pagree[2]].c_str());
			}
			else
			{
				Data::DrawSpeechBubble(Vector2D(P_X - 250, P_Y + 500), PString[Pagree[2]].length() * 20, true);
				DrawFormatString(P_X - 260, P_Y + 500, 0x000000, "%s", PString[Pagree[2]].c_str());
			}
		}
		if (Data::player_data[3].score < 0)//�X�R�A�̕\��
		{
			DrawFormatString(P_X + 100, P_Y + 500, 0xFF0000, "%d", Data::player_data[2].score);
		}
		else {
			DrawFormatString(P_X + 100, P_Y + 500, 0x000000, "%d", Data::player_data[2].score);
		}
		if (right[2] == 1)
		{
			DrawRotaGraph(P_X - 200, P_Y + 500, 1.0, (-45 / 180 + 1), Collect1st_Image, true);
		}
		else if (right[2] == 0)
		{
			DrawRotaGraph(P_X - 200, P_Y + 500, 1.0, (-45 / 180 + 1), Bad_Image, true);
		}

	case 2:
		if (Collect[1] == false)
		{
			DrawGraph(880, 350, false_Message, true);
			//DrawFormatString(880, 350, 0x000000, "<���b�Z�[�W���폜����܂���>");
		}
		else {
			DrawGraph(P_X, P_Y + 200, PlayerImage[1], true);
			if (Pagree[1] == 2)//�����p����
			{
				Data::DrawSpeechBubble(Vector2D(P_X - 450, P_Y + 300), PString[Pagree[1]].length() * 20, true);
				DrawFormatString(P_X - 450, P_Y + 300, 0x000000, "%s", PString[Pagree[1]].c_str());
			}
			else
			{
				Data::DrawSpeechBubble(Vector2D(P_X - 250, P_Y + 300), PString[Pagree[1]].length() * 20, true);
				DrawFormatString(P_X - 260, P_Y + 300, 0x000000, "%s", PString[Pagree[1]].c_str());
			}
		}
		if (Data::player_data[1].score < 0)//�X�R�A�̕\��
		{
			DrawFormatString(P_X + 100, P_Y + 300, 0xFF0000, "%d", Data::player_data[1].score);
		}
		else {
			DrawFormatString(P_X + 100, P_Y + 300, 0x000000, "%d", Data::player_data[1].score);
		}
		if (right[1] == 1)
		{
			DrawRotaGraph(P_X - 200, P_Y + 300, 1.0, (-45 / 180 + 1), Collect1st_Image, true);
		}
		else if (right[1] == 0)
		{
			DrawRotaGraph(P_X - 200, P_Y + 300, 1.0, (-45 / 180 + 1), Bad_Image, true);
		}

	case 1:
		if (Collect[0] == false)
		{
			DrawGraph(880, 150, false_Message, true);
			//DrawFormatString(880, 150, 0x000000, "<���b�Z�[�W���폜����܂���>");
		}
		else {
			DrawGraph(P_X, P_Y, PlayerImage[0], true);
			if (Pagree[0] == 2)//�����p����
			{
				Data::DrawSpeechBubble(Vector2D(P_X - 450, P_Y + 100), PString[Pagree[0]].length() * 20, true);
				DrawFormatString(P_X - 450, P_Y + 100, 0x000000, "%s", PString[Pagree[0]].c_str());
			}
			else
			{
				Data::DrawSpeechBubble(Vector2D(P_X - 250, P_Y + 100), PString[Pagree[0]].length() * 20, true);
				DrawFormatString(P_X - 260, P_Y + 100, 0x000000, "%s", PString[Pagree[0]].c_str());
			}
		}
		if (Data::player_data[0].score < 0)//�X�R�A�̕\��
		{
			DrawFormatString(P_X + 100, P_Y + 100, 0xFF0000, "%d", Data::player_data[0].score);
		}
		else {
			DrawFormatString(P_X + 100, P_Y + 100, 0x000000, "%d", Data::player_data[0].score);
		}	
		if (right[0] == 1)
		{
			DrawRotaGraph(P_X - 200, P_Y + 100, 1.0, (-45 / 180 + 1), Collect1st_Image, true);
		}
		else if (right[0] == 0)
		{
			DrawRotaGraph(P_X - 200, P_Y + 100, 1.0, (-45 / 180 + 1), Bad_Image, true);
		}

	}
	DrawFormatString(900, 0, 0x000000, "TimeCount:%d", Timer + 1);
#if _DEBUG
	DrawString(10, 10, "InGame", 0x000000);
#endif
}

/// <summary>
/// �P�폈��
/// </summary>
/// <param></param>
/// <returns>���݂̃V�[����ԋp</returns>
eSceneType InGameScene::Update()
{
	__super::Update();
#if _DEBUG
	KeyInput* key_input = KeyInput::Get();
#endif // _DEBUG

	/*	Enemy�֘A(2�Ƃ��L�ڍς݂̂��߁A�֐��Ăяo���̂�)	*/
	if (Timer == 0)
	{
		if (QSet)
		{
			//Enemy����₢������Ⴄ
			EnemyAsk();
			for (int i = 0; i < Data::player_num; i++)
			{
				Collect[i] = true;
				Player_Anser[i] = agreement::none;
				Pagree[i] = 0;
				Anserd[i] = false;
				right[i] = -1;
				ScoreValue[i] = 0;
			}
		}
	}
	while (Timer > 4)
	{
		SetPoint();
		//Enemy����󂯎����������player�炪�����Ă铚�����r����
		CheckAnser();
		Timer = -1;
		for (int i = 0; i < Data::player_num; i++)
		{
			Player_Anser[i] = agreement::none;
			Pagree[i] = 0;
		}
		QSet = true;
		Question = "�E �E �E";
		PlaySeter.clear();
	}
	/*player�֘A^-_-^�����炭���[�v*/
	TimerCount();
	//���͂ɉ���������
	PlayerAnser();
	//�S�����͂��� �܂��� �w�莞�ԉ߂���(�v�׋�)


	//�w��|�C���g���z����������
	if (TotalScore <= 0)
	{
		return eSceneType::E_RESULT;
	}
	return eSceneType::E_INGAME;
}

/// <summary>
/// ���݂̃V�[������ԋp
/// </summary>
/// <param></param>
/// <returns>���݂̃V�[�����</returns>
eSceneType InGameScene::GetNowScene() const
{
	return eSceneType::E_INGAME;
}

int InGameScene::PlayerAnser()
{
	for (int i = 0; i < Data::player_num; i++)
	{
		if (Anserd[i] != true)
		{
#ifdef _DEBUG
			//player�̉������{�^���ɉ����ĉ񓚂𓖂Ă͂߂�
			if (CheckHitKey(KEY_INPUT_W))//�����u��
			{
				Player_Anser[0] = agreement::positive;
				Pagree[0] = 1;
				Anserd[0] = true;
				PlaySeter.push_back(0);
			}
			else if (CheckHitKey(KEY_INPUT_A))
			{
				Player_Anser[0] = agreement::negation;
				Pagree[0] = 2;
				Anserd[0] = true;
				PlaySeter.push_back(0);
			}
			else if (CheckHitKey(KEY_INPUT_S))
			{
				Player_Anser[0] = agreement::question;
				Pagree[0] = 3;
				Anserd[0] = true;
				PlaySeter.push_back(0);
			}
			else if (CheckHitKey(KEY_INPUT_D))
			{
				Player_Anser[0] = agreement::excitement;
				Pagree[0] = 4;
				Anserd[0] = true;
				PlaySeter.push_back(0);
			}
#endif // _DEBUG
			//player�̉������{�^���ɉ����ĉ񓚂𓖂Ă͂߂�
			if (PadInput::GetButtonDown(Data::player_data[i].use_controller, XINPUT_BUTTON_B))//�����u��
			{
				Player_Anser[i] = agreement::positive;
				Pagree[i] = 1;
				Anserd[i] = true;
				PlaySeter.push_back(i);
				PlaySoundMem(SE_Talk, DX_PLAYTYPE_BACK);
			}
			else if (PadInput::GetButtonDown(Data::player_data[i].use_controller, XINPUT_BUTTON_A))
			{
				Player_Anser[i] = agreement::negation;
				Pagree[i] = 2;
				Anserd[i] = true;
				PlaySeter.push_back(i);
				PlaySoundMem(SE_Talk, DX_PLAYTYPE_BACK);
			}
			else if (PadInput::GetButtonDown(Data::player_data[i].use_controller, XINPUT_BUTTON_X))
			{
				Player_Anser[i] = agreement::question;
				Pagree[i] = 3;
				Anserd[i] = true;
				PlaySeter.push_back(i);
				PlaySoundMem(SE_Talk, DX_PLAYTYPE_BACK);
			}
			else if (PadInput::GetButtonDown(Data::player_data[i].use_controller, XINPUT_BUTTON_Y))
			{
				Player_Anser[i] = agreement::excitement;
				Pagree[i] = 4;
				Anserd[i] = true;
				PlaySeter.push_back(i);
				PlaySoundMem(SE_Talk, DX_PLAYTYPE_BACK);
			}
		}
	}
	return 0;
}

void InGameScene::SetPoint()
{
	switch (PlaySeter.size())
	{
	case 4:
		ScoreValue[PlaySeter[3]] = 0;
	case 3:
		ScoreValue[PlaySeter[2]] = 25;
	case 2:
		ScoreValue[PlaySeter[1]] = 50;
	case 1:
		ScoreValue[PlaySeter[0]] = 100;
	}
}

void InGameScene::CheckAnser()
{

	for (int i = 0; i < Data::player_num; i++)
	{
		Collect[i] = false;
		right[i] = -1;

		if (Player_Anser[i] == FatalAnser)
		{
			PlaySoundMem(SE_Correct, DX_PLAYTYPE_BACK);
			//�����̏ꍇ
			//score�𐳓������v���C���[�ɉ��Z
			switch (i)
			{
			case 0:
				Data::player_data[0].score += ScoreValue[i];
				Data::player_data[0].great++;
				TotalScore -= ScoreValue[i];
				Collect[0] = true;
				right[0] = 1;
				break;
			case 1:
				Data::player_data[1].score += ScoreValue[i];
				Data::player_data[1].great++;
				TotalScore -= ScoreValue[i];
				Collect[1] = true;
				right[1] = 1;
				break;
			case 2:
				Data::player_data[2].score += ScoreValue[i];
				Data::player_data[2].great++;
				TotalScore -= ScoreValue[i];
				Collect[2] = true;
				right[2] = 1;
				break;
			case 3:
				Data::player_data[3].score += ScoreValue[i];
				Data::player_data[3].great++;
				TotalScore -= ScoreValue[i];
				Collect[3] = true;
				right[3] = 1;
				break;
			}
		}
		else
		{
			PlaySoundMem(SE_MessageDelete, DX_PLAYTYPE_BACK);

			switch (i)
			{
			case 0:
				Data::player_data[0].score -= ScoreValue[i];
				Data::player_data[0].bad++;
				right[0] = 0;
				break;
			case 1:
				Data::player_data[1].score -= ScoreValue[i];
				Data::player_data[1].bad++;
				right[1] = 0;
				break;
			case 2:
				Data::player_data[2].score -= ScoreValue[i];
				Data::player_data[2].bad++;
				right[2] = 0;
				break;
			case 3:
				Data::player_data[3].score -= ScoreValue[i];
				Data::player_data[3].bad++;
				right[3] = 0;
				break;
			}
		}
	}
}

///--		*	*	*	*	*	Enemy�֘A	*	*	*	*	*	--///

/// <summary>
/// Enemy�̓�������
/// </summary>
/// <param></param>
/// <returns></returns>
void InGameScene::EnemyAnser()
{
	switch (GetRand(3) + 1)
	{
	case 1:
		FatalAnser = agreement::positive;
		FatalAnserNum = 0;
		break;
	case 2:
		FatalAnser = agreement::negation;
		FatalAnserNum = 1;
		break;
	case 3:
		FatalAnser = agreement::question;
		FatalAnserNum = 2;
		break;
	case 4:
		FatalAnser = agreement::excitement;
		FatalAnserNum = 3;
		break;
	}
}

/// <summary>
/// Enemy�̎��⌈��
/// </summary>
void InGameScene::EnemyAsk()
{
	PlaySoundMem(SE_Talk, DX_PLAYTYPE_BACK);

	QSet = false;
	EnemyAnser();

	Question = EnemyString[FatalAnserNum][GetRand(6)];
}

/// <summary>
/// CSV�t�@�C����ǂݎ��
/// </summary>
/// <param name ="filename">�J���t�@�C���̖��O</param>
/// <returns>vector�̒���vector�̒��ɂ���string</returns>
vector<vector<string>> InGameScene::read_csv(const string& filename)
{
	vector<vector<string>> data;
	ifstream file(filename);
	if (!file) {
		cerr << "Error: �t�@�C�����J���܂���ł����B" << endl;
		return data;
	}

	string line;
	while (getline(file, line)) { // 1�s���ǂݍ���
		vector<string> row;
		stringstream ss(line);
		string cell;

		while (getline(ss, cell, ',')) { // �J���}��؂�ŕ���
			row.push_back(cell);
		}
		data.push_back(row);
	}
	return data;
}

void InGameScene::TimerCount()
{
	TimeCountUp += 1.0f;

	if (TimeCountUp > 60.0f)
	{
		TimeCountUp = 0.0f;
		Timer ++;
	}
}