#include "InGameScene.h"
#include "../../Utility/PadInput.h"
#include "../../Utility/KeyInput.h"


/// <summary>
///�@�C���X�g���N�^
/// </summary>
/// <param></param>
/// <returns></returns>
InGameScene::InGameScene()
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
		break;
	}

	EnemyAnser();

	EnemyString = {
		{"�|�W�e�B�u�Ȏ���1", "�|�W�e�B�u�Ȏ���2", "�|�W�e�B�u�Ȏ���3", "�|�W�e�B�u�Ȏ���4", "�|�W�e�B�u�Ȏ���5"},
		{"�l�K�e�B�u�Ȏ���1", "�l�K�e�B�u�Ȏ���2", "�l�K�e�B�u�Ȏ���3", "�l�K�e�B�u�Ȏ���4", "�l�K�e�B�u�Ȏ���5"},
		{"�^��n�̎���1", "�^��n�̎���2", "�^��n�̎���3", "�^��n�̎���4", "�^��n�̎���5"},
		{"����グ�鎿��1", "����グ�鎿��2", "����グ�鎿��3", "����グ�鎿��4", "����グ�鎿��5"}
	};

	PString = { "�������ˁI","����Ȃ��ƂȂ���I","�����Ȃ́H","���ꂩ��H" };

	Question = EnemyString[FatalAnserNum][GetRand(4)];

	Background_image = LoadGraph("Rescurce/Image/background.png");

	 PlayerTextImage = LoadGraph("Rescurce/Image/MessageFrame_1.png");
	 EnemyImage		 = LoadGraph("Rescurce/Image/MessageFrame_2.png");
}

/// <summary>
/// �I��������
/// </summary>
/// <param></param>
/// <returns></returns>
void InGameScene::Finalize()
{
}

/// <summary>
/// �Q�[����ʂ̕`�������
/// </summary>
/// <param></param>
/// <returns></returns>
void InGameScene::Draw() const
{
	//�w�i�摜
	DrawGraph(0, 0, Background_image, false);

	//�G�l�~�[�֌W
	DrawGraph(800, 100, EnemyImage, true);
	DrawFormatString(800, 200, 0xFFFFFF, "%s", Question.c_str());

	//�l���ɍ��킹�ĕ`��
	switch (Data::player_num)
	{
	case 4:
		DrawGraph(50, 500, PlayerImage[3], true);
		if (Collect[3] == false)
		{
		DrawFormatString(180, 600, 0x000000, "<���b�Z�[�W���폜����܂���>");
		}else {
		DrawReverseGraph(80, 500, PlayerTextImage, true, 1);
		DrawFormatString(180,600, 0x000000, "%s", PString[Pagree[3]].c_str());
		}
	case 3:
		if (Collect[2] == false)
		{
		DrawFormatString(180, 450, 0x000000, "<���b�Z�[�W���폜����܂���>");
		}else {
		DrawGraph(50, 350, PlayerImage[2], true);
		DrawReverseGraph(80, 350, PlayerTextImage, true, 1);
		DrawFormatString(180,450, 0x000000, "%s", PString[Pagree[2]].c_str());

		}
	case 2:
		if (Collect[1] == false)
		{
		DrawFormatString(180, 300, 0x000000, "<���b�Z�[�W���폜����܂���>");
		}else {
		DrawGraph(50, 200, PlayerImage[1], true);
		DrawReverseGraph(80, 200, PlayerTextImage, true, 1);
		DrawFormatString(180,300, 0x000000, "%s", PString[Pagree[1]].c_str());

		}

	case 1:
		if (Collect[0] == false)
		{
		DrawFormatString(180, 150, 0x000000, "<���b�Z�[�W���폜����܂���>");
		}else{
		DrawGraph(50, 50, PlayerImage[0], true);
		DrawReverseGraph(80, 50, PlayerTextImage, true, 1);
		DrawFormatString(180, 150, 0x000000, "%s", PString[Pagree[0]].c_str());
		}
	}

	DrawFormatString(900, 0, 0x000000, "TimeCount:%d", Timer);
#if _DEBUG
	switch (Data::player_num)
	{
	case 4:
		DrawFormatString(50, 600, 0x000000, "%d", PD4.score);
	case 3:
		DrawFormatString(50, 450, 0x000000, "%d", PD3.score);
	case 2:
		DrawFormatString(50, 300, 0x000000, "%d", PD2.score);
	case 1:
		DrawFormatString(50, 150, 0x000000, "%d", PD1.score);
	}

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
	if (Timer == 2)
	{
		Collect[0] = true;
		Collect[1] = true;
		Collect[2] = true;
		Collect[3] = true;
	}
	while (Timer > 4)
	{
		//Enemy����󂯎����������player�炪�����Ă铚�����r����
		CheckAnser();
		//Enemy����₢������Ⴄ
		EnemyAsk();
		Timer = 0;
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
		//player�̉������{�^���ɉ����ĉ񓚂𓖂Ă͂߂�
		if(PadInput::GetButtonDown(j, XINPUT_BUTTON_B))//�����u��
		{
			Player_Anser[i] = agreement::positive;
			Pagree[i] = 0;
		}
		else if (PadInput::GetButtonDown(j, XINPUT_BUTTON_A))
		{
			Player_Anser[i] = agreement::negation;
			Pagree[i] = 1;

		}
		else if (PadInput::GetButtonDown(j, XINPUT_BUTTON_X))
		{
			Player_Anser[i] = agreement::question;
			Pagree[i] = 2;

		}
		else if (PadInput::GetButtonDown(j, XINPUT_BUTTON_Y))
		{
			Player_Anser[i] = agreement::excitement;
			Pagree[i] = 3;

		}
		j++;
	}

	return 0;
}

void InGameScene::CheckAnser()
{
	Collect[0] = false;
	Collect[1] = false;
	Collect[2] = false;
	Collect[3] = false;

	for (int i = 0; i < Data::player_num; i++)
	{
		if (Player_Anser[i] == FatalAnser)
		{
			//�����̏ꍇ
			//score�𐳓������v���C���[�ɉ��Z
			switch (i)
			{
			case 0:
				PD1.score += 50;
				TotalScore -= 50;
				Collect[0] = true;
				break;
			case 1:
				PD2.score += 50;
				TotalScore -= 50;
				Collect[1] = true;

				break;
			case 2:
				PD3.score += 50;
				TotalScore -= 50;
				Collect[2] = true;
				break;
			case 3:
				PD4.score += 50;
				TotalScore -= 50;
				Collect[3] = true;
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
