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
	TotalScore = 1000;
	
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
	EnemyString = {
		{"�|�W�e�B�u�Ȏ���1", "�|�W�e�B�u�Ȏ���2", "�|�W�e�B�u�Ȏ���3", "�|�W�e�B�u�Ȏ���4", "�|�W�e�B�u�Ȏ���5"},
		{"�l�K�e�B�u�Ȏ���1", "�l�K�e�B�u�Ȏ���2", "�l�K�e�B�u�Ȏ���3", "�l�K�e�B�u�Ȏ���4", "�l�K�e�B�u�Ȏ���5"},
		{"�^��n�̎���1", "�^��n�̎���2", "�^��n�̎���3", "�^��n�̎���4", "�^��n�̎���5"},
		{"����グ�鎿��1", "����グ�鎿��2", "����グ�鎿��3", "����グ�鎿��4", "����グ�鎿��5"}
	};
	Background_image = LoadGraph("Rescurce/Image/background.png");

	 PlayerImage = LoadGraph("Rescurce/Image/MessageFrame_1.png");
	 EnemyImage = LoadGraph("Rescurce/Image/MessageFrame_2.png");
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
	__super::Draw();

	//�w�i�摜
	DrawGraph(0, 0, Background_image, false);
	DrawGraph(100, 100, PlayerImage, true);
	DrawGraph(200, 200, EnemyImage, true);

#if _DEBUG
	DrawString(10, 10, "InGame", 0x000000);
	DrawFormatString(200, 200, 0x000000, "E:%s,",Question.c_str());
#endif
	//��X������܂���
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

	if (PadInput::GetButton(DX_INPUT_PAD1, PAD_INPUT_B)|| key_input->GetKeyState(KEY_INPUT_UP) == eInputState::Pressed)
	{
		/*������𗘗p����ƁA���U���g��ʂɕΈڂ���B*/
		return eSceneType::E_RESULT; 
	}
#endif // _DEBUG

	/*	Enemy�֘A(2�Ƃ��L�ڍς݂̂��߁A�֐��Ăяo���̂�)	*/
	{
		//Enemy����₢������Ⴄ
		EnemyAsk();


	}
	/*player�֘A^-_-^�����炭���[�v*/
	

	for (int TimeLimit = 600000; TimeLimit > 0;TimeLimit--) 
	{
		//���͂ɉ���������
		PlayerAnser();
		//�S�����͂��� �܂��� �w�莞�ԉ߂���(�v�׋�)
		DrawFormatString(250, 250, 0x000000, "P:%d,",PD1.score);

	}

	for (int i = 0; i < 4; i++)
	{
		//Enemy����󂯎����������player�炪�����Ă铚�����r����
		if (Player_Anser[i] == FatalAnser)
		{
			//�����̏ꍇ
			//score�𐳓������v���C���[�ɉ��Z
			switch (i)
			{
			case 0:
				PD1.score += 50;
				TotalScore -= 50;
				break;
			case 1:
				PD2.score += 50;
				TotalScore -= 50;
				break;
			case 2:
				PD3.score += 50;
				TotalScore -= 50;
				break;
			case 3:
				PD4.score += 50;
				TotalScore -= 50;
				break;
			}
		}
		else//�s�����̏ꍇ
		{
			//����͌듚�y�i���e�B�����݂��Ȃ��̂ŁA���M���ׂ������͖���

		}
	}
	
	
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
	for (int i = 0; i < 4; i++)
	{
		//player�̉������{�^���ɉ����ĉ񓚂𓖂Ă͂߂�
		if(PadInput::GetButton(i, PAD_INPUT_B))//�����u��
		{
			Player_Anser[i] = positive;
		}
		else if (PadInput::GetButton(i, PAD_INPUT_A))
		{
			Player_Anser[i] = agreement::negation;
		}
		else if (PadInput::GetButton(i, PAD_INPUT_X))
		{
			Player_Anser[i] = question;
		}
		else if (PadInput::GetButton(i, PAD_INPUT_Y))
		{
			Player_Anser[i] = excitement;
		}
	}
	return 0;
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
