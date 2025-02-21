#include "ResultScene.h"
#include "../../Utility/PadInput.h"
#include "../../Utility/KeyInput.h"

ResultScene::ResultScene():
	result_image(0)
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

	//デバッグ時処理
#if _DEBUG

	//Bボタンかスペースキーでタイトルへ
	if (PadInput::GetButton(DX_INPUT_PAD1, XINPUT_BUTTON_B) || key_input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Released)
	{
		return E_TITLE;
	}
#endif //  DEBUG
	//現在のシーンを返す
	return GetNowScene();
}

void ResultScene::Draw() const
{
	//背景画像
	DrawGraph(0, 0, result_image, false);

#if _DEBUG
	DrawString(0, 0, "Result", 0x000000);
	DrawString(0, 20, "Pad B  or  Spaceでタイトル", 0x000000);
#endif
}

eSceneType ResultScene::GetNowScene() const
{
	return E_RESULT;
}