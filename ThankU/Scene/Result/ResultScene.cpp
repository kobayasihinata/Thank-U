#include "ResultScene.h"
#include "../../Utility/PadInput.h"

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

	//B�{�^�����X�y�[�X�L�[�Ń^�C�g����
	if (PadInput::GetButton(DX_INPUT_PAD1, XINPUT_BUTTON_B) || CheckHitKey(KEY_INPUT_SPACE))
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