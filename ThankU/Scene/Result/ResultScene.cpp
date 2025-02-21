#include "ResultScene.h"
#include "../../Utility/PadInput.h"
#include "../../Utility/KeyInput.h"

ResultScene::ResultScene()
{

}

ResultScene::~ResultScene()
{

}

void ResultScene::Initialize()
{

}

void ResultScene::Finalize()
{

}

eSceneType ResultScene::Update()
{
	__super::Update();

	KeyInput* key_input = KeyInput::Get();

	//B�{�^�����X�y�[�X�L�[�Ń^�C�g����
	if (PadInput::GetButton(DX_INPUT_PAD1, XINPUT_BUTTON_B) || key_input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		return E_TITLE;
	}
	//���݂̃V�[����Ԃ�
	return GetNowScene();
}

void ResultScene::Draw() const
{
	DrawString(0, 0, "Result", 0xffffff);
	DrawString(0, 20, "Pad B  or  Space�Ń^�C�g��", 0xffffff);
}

eSceneType ResultScene::GetNowScene() const
{
	return E_RESULT;
}