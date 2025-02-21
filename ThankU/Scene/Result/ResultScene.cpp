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

	//Bボタンかスペースキーでタイトルへ
	if (PadInput::GetButton(DX_INPUT_PAD1, XINPUT_BUTTON_B) || CheckHitKey(KEY_INPUT_SPACE))
	{
		return E_TITLE;
	}
	//現在のシーンを返す
	return GetNowScene();
}

void ResultScene::Draw() const
{
	DrawString(0, 0, "Result", 0xffffff);
	DrawString(0, 20, "Pad B  or  Spaceでタイトル", 0xffffff);
}

eSceneType ResultScene::GetNowScene() const
{
	return E_RESULT;
}