#include "CreditScene.h"
#include "../../Utility/PadInput.h"
#include "../../Utility/KeyInput.h"
#include "../../Utility/DebugInformation.h"

//�R���X�g���N�^
CreditScene::CreditScene() :count(150), scrollY(SCREEN_HEIGHT),
background_image(0), credit_logo(0), object_image()
{
}

//�f�X�g���N�^
CreditScene::~CreditScene() {}

//������
void CreditScene::Initialize()
{
	//�^�C�g��BGM�Đ�
	PlaySoundFile("Rescurce/BGM/CreditBGM.wav", DX_PLAYTYPE_LOOP);

	//�w�i�摜
	background_image = LoadGraph("Rescurce/Image/background.png");
	//���S
	credit_logo = LoadGraph("Rescurce/Image/CreditLogo.png");
	//�e�I�u�W�F�N�g
	object_image[0] = LoadGraph("Rescurce/Image/Line_Message.png");

	//�����ŃG�t�F�N�g�̏����� --�� �摜�̓ǂݍ��݂Ƃ�
	//effect.Initialize();
}

//�I��������
void CreditScene::Finalize()
{
	//BGM���~�߂�
	StopSoundFile();
}

//�X�V����
eSceneType CreditScene::Update()
{
	//�e�N���X�̍X�V�������Ăяo��
	__super::Update();

	//�L�[�{�[�h���͏����̃C���X�^���X���擾
	KeyInput* key_input = KeyInput::Get();

	/* * * * * * * * * * * * * * * * �G�t�F�N�g�֘A�@* * * * * * * * * * * */

	if (key_input->GetKeyState(KEY_INPUT_E) == eInputState::Pressed)
	{
		// E�L�[�������ꂽ��G�t�F�N�g
		//effect.Set(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, EFF_EXPLODE);
		DebugInfomation::Add("Effect Set", true); // �f�o�b�O�p
	}

	////��̂R�b���炢�G�t�F�N�g���o����---������
	//if (count > 0) {
	//	for (int i = 0; i < 5; ++i)
	//	{
	//		int randomX = std::rand() % SCREEN_WIDTH;
	//		int randomY = std::rand() % SCREEN_HEIGHT;
	//		effect.Set(randomX, randomY, EFF_EXPLODE);
	//	}
	//}
	//count--;

	// �G�t�F�N�g���X�V
	//effect.Update();

	/* * * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * */

	//�X�N���[���ʂ����Z
	scrollY -= 2.0f;

	//�e�L�X�g����ʊO�ɍs������G���h�֑J�ڂ���
	if (scrollY < -1300) return E_TITLE;

	//�f�o�b�O������
#if _DEBUG
	//�^�C�g���֑J�ڂ���(�f�o�b�O�p)
	if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_B) || key_input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		return E_TITLE;
	}

	//�f�o�b�O�p(X�L�[)
	DebugInfomation::Add("count", count);
	DebugInfomation::Add("scrollY", scrollY);

#endif
	//���݂̃V�[����Ԃ�
	return GetNowScene();
}

//�`�揈��
void CreditScene::Draw() const
{
	int y = 50;	//�����Ԋu
	int startX = SCREEN_HEIGHT / 2; //�^�񒆂��傢�����炢�̍��W
	int currentY = scrollY - 200; // ���݂�Y�ʒu

	//�w�i�摜
	DrawGraph(0, 0, background_image, true);

	//�g

	//�N���W�b�g�\�L
	DrawString(startX, currentY += y * 2, "--Credit--", 0xffffff);
	DrawString(startX, currentY += y * 2, "���Q�[������", 0xffffff);
	DrawString(startX, currentY += y, "Team Thank U", 0xffffff);
	DrawString(startX, currentY += y * 2, "�������o�[", 0xffffff);
	DrawString(startX, currentY += y, "�ЂȂ�", 0xffffff);
	DrawString(startX, currentY += y, "�܂Ȃ�", 0xffffff);
	DrawString(startX, currentY += y, "�Ƃ���", 0xffffff);
	DrawString(startX, currentY += y, "���傤�����낤", 0xffffff);
	DrawString(startX, currentY += y * 2, "���c�[��", 0xffffff);
	DrawString(startX, currentY += y, "VisualStudio", 0xffffff);
	DrawString(startX, currentY += y * 2, "��BGM", 0xffffff);
	DrawString(startX, currentY += y, "���傤�����낤", 0xffffff);
	DrawString(startX, currentY += y * 2, "��SE", 0xffffff);
	DrawString(startX, currentY += y, "���ʉ����{ �l", 0xffffff);
	DrawString(startX, currentY += y * 2, "���C���X�g�f��", 0xffffff);
	DrawString(startX, currentY += y, "�ЂȂ�", 0xffffff);
	DrawString(startX, currentY += y, "�܂Ȃ�", 0xffffff);

	//�摜�̕`��
	DrawGraph(0, 0, object_image[0], true);
	DrawGraph(0, 0, credit_logo, true);

#if _DEBUG
	DrawString(SCREEN_WIDTH / 1.5, SCREEN_HEIGHT / 13, "Pad B or Space�Ń^�C�g��", 0xffffff);
#endif

	//�G�t�F�N�g�̕`��
	//effect.Draw();
}

//���݃V�[�������擾
eSceneType CreditScene::GetNowScene() const
{
	return E_CREDIT;
}

