#include "CreditScene.h"
#include "../../Utility/PadInput.h"
#include "../../Utility/KeyInput.h"
#include "../../Utility/DebugInformation.h"

CreditScene::CreditScene()
{
	count = 300;
}

CreditScene::~CreditScene(){}

//������
void CreditScene::Initialize(){}

//�I��������
void CreditScene::Finalize(){}

//�X�V����
eSceneType CreditScene::Update()
{
	//�e�N���X�̍X�V�������Ăяo��
	__super::Update();

	//�X�N���[���ʂ����Z
	scrollY -= 1.5f; 

	//�e�L�X�g����ʊO�ɍs������G���h�֑J�ڂ���
	if (scrollY < -1300) return E_END;

	//�L�[�{�[�h���͏����̃C���X�^���X���擾
	KeyInput* key_input = KeyInput::Get();
	
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
	int currentY = scrollY; // ���݂�Y�ʒu

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

#if _DEBUG
	DrawString(SCREEN_WIDTH / 1.5, SCREEN_HEIGHT/13, "Pad B or Space�Ń^�C�g��", 0xffffff);
#endif
}

eSceneType CreditScene::GetNowScene() const
{
	return E_CREDIT;
}