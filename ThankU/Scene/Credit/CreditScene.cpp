#include "CreditScene.h"
#include "../../Utility/PadInput.h"
#include "../../Utility/KeyInput.h"
#include "../../Utility/DebugInformation.h"

//�R���X�g���N�^
CreditScene::CreditScene() :count(150), scrollY(SCREEN_HEIGHT), move_frame(0),
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

	move_frame += 3;
	//����𒴂��Ȃ��悤�ɂ���
	if (move_frame > 240)
	{
		move_frame = 240;
	}
	//�L�[�{�[�h���͏����̃C���X�^���X���擾
	KeyInput* key_input = KeyInput::Get();

	//�X�N���[���ʂ����Z
	scrollY -= 2.0f;

	//�e�L�X�g����ʊO�ɍs������G���h�֑J�ڂ���
	if (scrollY < -1300) return E_TITLE;

	//�^�C�g���֑J�ڂ���
	if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_B) || key_input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		return E_TITLE;
	}

	//�f�o�b�O������
#if _DEBUG
	
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
	int old = GetFontSize();
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
	DrawString(startX, currentY += y, "���炷�Ƃ�l", 0xffffff);

	//�摜�̕`��
	DrawGraph(0, 0, object_image[0], true);
	DrawGraph(0, move_frame - 240, credit_logo, true);

	SetFontSize(70);
	DrawString(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, "B�Ń^�C�g����", 0xffffff);
	SetFontSize(old);

#if _DEBUG
	
#endif
}

//���݃V�[�������擾
eSceneType CreditScene::GetNowScene() const
{
	return E_CREDIT;
}

