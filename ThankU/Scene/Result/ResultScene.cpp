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

	//B�{�^���Ń^�C�g����
	if (PadInput::GetButton(DX_INPUT_PAD1, XINPUT_BUTTON_B))
	{
		return E_TITLE;
	}
	//���݂̃V�[����Ԃ�
	return GetNowScene();
}

void ResultScene::Draw() const
{
	DrawString(0, 0, "Result", 0xffffff);
}

eSceneType ResultScene::GetNowScene() const
{
	return E_RESULT;
}