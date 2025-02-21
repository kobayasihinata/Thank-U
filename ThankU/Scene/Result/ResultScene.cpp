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
	result_image = LoadGraph("Rescurce/Image/Result/Result_kari.png");
}

void ResultScene::Finalize()
{

}

eSceneType ResultScene::Update()
{
	__super::Update();

	KeyInput* key_input = KeyInput::Get();

	//Bボタンかスペースキーでタイトルへ
	if (PadInput::GetButton(DX_INPUT_PAD1, XINPUT_BUTTON_B) || key_input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Released)
	{
		return E_TITLE;
	}
	//現在のシーンを返す
	return GetNowScene();
}

void ResultScene::Draw() const
{
	//背景画像
	DrawGraph(0, 0, result_image, false);

	DrawString(0, 0, "Result", 0x000000);
	DrawString(0, 20, "Pad B  or  Spaceでタイトル", 0x000000);
}

eSceneType ResultScene::GetNowScene() const
{
	return E_RESULT;
}