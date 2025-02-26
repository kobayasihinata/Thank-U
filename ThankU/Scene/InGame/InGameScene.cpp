#include "InGameScene.h"
#include "../../Utility/PadInput.h"
#include "../../Utility/KeyInput.h"


/// <summary>
///�@�C���X�g���N�^
/// </summary>
/// <param></param>
/// <returns></returns>
InGameScene::InGameScene():
	Anserd{ (false),(false),(false),(false) },
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
	SE_Correct = LoadSoundMem("Rescurce/SE/Correct.mp3");

	Timer = -1;

	for (int i = 0; i < Data::player_num; i++)
	{
		Collect[i] = true;
		Player_Anser[i] = agreement::none;
		Pagree[i] = agreement::none;
		Anserd[i] = false;
		ScoreValue[i] = 0;

		//switch (Data::player_data[i].use_controller)
		//{
		//case 1:
		//	PD1 = Data::player_data[i];
		//	break;
		//case 2:
		//	PD2 = Data::player_data[i];
		//	break;
		//case 3:
		//	PD3 = Data::player_data[i];
		//	break;
		//case 4:
		//	PD4 = Data::player_data[i];
		//	break;
		//}
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

	switch (Data::player_num)
	{
	case 4:
		TotalScore = 4000;
		break;
	case 3:
		TotalScore = 2500;
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

	Background_image	=	LoadGraph("Rescurce/Image/background.png")		;
	Border_Line			=	LoadGraph("Rescurce/Image/Line_Message.png")	;
	PlayerTextImage		=	LoadGraph("Rescurce/Image/MessageFrame_1.png")	;
	EnemyImage			=	LoadGraph("Rescurce/Image/MessageFrame_2.png")	;
	false_Message		=	LoadGraph("Rescurce/Image/MessageCancel.png")	;
	InGameHelp			=	LoadGraph("Rescurce/Image/InGameButton.png")	;

}

/// <summary>
/// �I��������
/// </summary>
/// <param></param>
/// <returns></returns>
void InGameScene::Finalize()
{
	StopSoundFile();
	//Data::player_data[0] = PD1;
	//Data::player_data[1] = PD2;
	//Data::player_data[2] = PD3;
	//Data::player_data[3] = PD4;
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
	Data::DrawSpeechBubble(Vector2D(50, 200), Question.length()*25, false);
	DrawFormatString(50, 200, 0xFFFFFF, "%s", Question.c_str());

	int P_X = 1700;
	int P_Y = 50;
  
 	DrawGraph(0, 0, Border_Line, true);
	DrawGraph(0, 500, InGameHelp, true);
	//�l���ɍ��킹�ĕ`��
	switch (Data::player_num)
	{
	case 4:
		if (Collect[3] == false)
		{
		DrawGraph(880, 750, false_Message, true);
		//DrawFormatString(880, 750, 0x000000, "<���b�Z�[�W���폜����܂���>");
		}else {
		DrawGraph(P_X, P_Y + 600, PlayerImage[3], true);
		DrawReverseGraph(P_X - 320, P_Y + 600, PlayerTextImage, true, 0);
		DrawFormatString(P_X - 220, P_Y + 700, 0x000000, "%s", PString[Pagree[3]].c_str());
		DrawFormatString(P_X + 100, P_Y + 700, 0x000000, "%d", Data::player_data[3].score);
		}
	case 3:
		if (Collect[2] == false)
		{
		DrawGraph(880, 550, false_Message, true);
		//DrawFormatString(880, 550, 0x000000, "<���b�Z�[�W���폜����܂���>");
		}else {
		DrawGraph(P_X, P_Y + 400, PlayerImage[2], true);
		DrawReverseGraph(P_X - 320, P_Y + 400, PlayerTextImage, true, 0);
		DrawFormatString(P_X - 220, P_Y + 500, 0x000000, "%s", PString[Pagree[2]].c_str());
		DrawFormatString(P_X + 100, P_Y + 500, 0x000000, "%d", Data::player_data[2].score);
		}
	case 2:
		if (Collect[1] == false)
		{
		DrawGraph(880, 350, false_Message, true);
		//DrawFormatString(880, 350, 0x000000, "<���b�Z�[�W���폜����܂���>");
		}else {
		DrawGraph(P_X, P_Y + 200, PlayerImage[1], true);
		DrawReverseGraph(P_X - 320, P_Y + 200, PlayerTextImage, true, 0);
		DrawFormatString(P_X - 220, P_Y + 300, 0x000000, "%s", PString[Pagree[1]].c_str());
		DrawFormatString(P_X + 100, P_Y + 300, 0x000000, "%d", Data::player_data[1].score);
		}
	case 1:
		if (Collect[0] == false)
		{
		DrawGraph(880, 150, false_Message, true);
		//DrawFormatString(880, 150, 0x000000, "<���b�Z�[�W���폜����܂���>");
		}else{
		DrawGraph(P_X, P_Y, PlayerImage[0], true);
		DrawReverseGraph(P_X - 320, P_Y, PlayerTextImage, true, 0);
		DrawFormatString(P_X - 220, P_Y + 100, 0x000000, "%s", PString[Pagree[0]].c_str());
		DrawFormatString(P_X + 100, P_Y + 100, 0x000000, "%d", Data::player_data[0].score);
		}
	}

	DrawFormatString(900, 0, 0x000000, "TimeCount:%d", Timer+1);
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
	if (Timer == -1)
	{
		//for (int i = 0; i < Data::player_num; i++)
		//{
		//}
	}
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
				Pagree[i] = agreement::none;
				Anserd[i] = false;
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
			Pagree[i] = agreement::none;
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
	int j = 1;
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
			if (PadInput::GetButtonDown(j, XINPUT_BUTTON_B))//�����u��
			{
				Player_Anser[i] = agreement::positive;
				Pagree[i] = 1;
				Anserd[i] = true;
				PlaySeter.push_back(i);
			}
			else if (PadInput::GetButtonDown(j, XINPUT_BUTTON_A))
			{
				Player_Anser[i] = agreement::negation;
				Pagree[i] = 2;
				Anserd[i] = true;
				PlaySeter.push_back(i);
			}
			else if (PadInput::GetButtonDown(j, XINPUT_BUTTON_X))
			{
				Player_Anser[i] = agreement::question;
				Pagree[i] = 3;
				Anserd[i] = true;
				PlaySeter.push_back(i);
			}
			else if (PadInput::GetButtonDown(j, XINPUT_BUTTON_Y))
			{
				Player_Anser[i] = agreement::excitement;
				Pagree[i] = 4;
				Anserd[i] = true;
				PlaySeter.push_back(i);
			}
		}
		j++;
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

		if (Player_Anser[i] == FatalAnser)
		{
			PlaySoundMem(SE_Correct, DX_PLAYTYPE_BACK);
			//�����̏ꍇ
			//score�𐳓������v���C���[�ɉ��Z
			switch (i)
			{
			case 0:
				Data::player_data[0].score += ScoreValue[i];
				TotalScore -= ScoreValue[i];
				Collect[0] = true;
				break;
			case 1:
				Data::player_data[1].score += ScoreValue[i];
				TotalScore -= ScoreValue[i];
				Collect[1] = true;
				break;
			case 2:
				Data::player_data[2].score += ScoreValue[i];
				TotalScore -= ScoreValue[i];
				Collect[2] = true;
				break;
			case 3:
				Data::player_data[3].score += ScoreValue[i];
				TotalScore -= ScoreValue[i];
				Collect[3] = true;
				break;
			}
		}
		else
		{
			switch (i)
			{
			case 0:
				Data::player_data[0].score -= ScoreValue[i];
				break;
			case 1:
				Data::player_data[1].score -= ScoreValue[i];
				break;
			case 2:
				Data::player_data[2].score -= ScoreValue[i];
				break;
			case 3:
				Data::player_data[3].score -= ScoreValue[i];
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
	switch (GetRand(4) + 1)
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

	QSet = false;
	EnemyAnser();

	Question = EnemyString[FatalAnserNum][GetRand(4)];
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