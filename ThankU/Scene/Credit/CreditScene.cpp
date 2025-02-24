#include "CreditScene.h"
#include "../../Utility/PadInput.h"
#include "../../Utility/KeyInput.h"
#include "../../Utility/DebugInformation.h"

CreditScene::CreditScene()
{
	count = 300;
}

CreditScene::~CreditScene()
{

}

void CreditScene::Initialize()
{

}

void CreditScene::Finalize()
{

}

eSceneType CreditScene::Update()
{
	__super::Update();

	KeyInput* key_input = KeyInput::Get();

	//��莞�Ԍo�߂ŏI��
	//if (--count < 0)
	//{
	//	return E_END;
	//}
	
	//�f�o�b�O������
#if _DEBUG
	//B�{�^�����X�y�[�X�L�[�Ń^�C�g����
	if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_B) || key_input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		return E_TITLE;
	}
	//Add�g�p��
	DebugInfomation::Add("count", count);
#endif
	//���݂̃V�[����Ԃ�
	return GetNowScene();
}

void CreditScene::Draw() const
{
	DrawString(0, 0, "Credit", 0xffffff);
	//DrawFormatString(0, 20, 0xffffff, "����%d�b��End��ʂ�", (int)(count / 60));
#if _DEBUG
	DrawString(0, 20, "Pad B  or  Space�Ń^�C�g��", 0x000000);
#endif
}

eSceneType CreditScene::GetNowScene() const
{
	return E_CREDIT;
}