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

	//一定時間経過で終了
	//if (--count < 0)
	//{
	//	return E_END;
	//}
	
	//デバッグ時処理
#if _DEBUG
	//Bボタンかスペースキーでタイトルへ
	if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_B) || key_input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		return E_TITLE;
	}
	//Add使用例
	DebugInfomation::Add("count", count);
#endif
	//現在のシーンを返す
	return GetNowScene();
}

void CreditScene::Draw() const
{
	DrawString(0, 0, "Credit", 0xffffff);
	//DrawFormatString(0, 20, 0xffffff, "あと%d秒でEnd画面へ", (int)(count / 60));
#if _DEBUG
	DrawString(0, 20, "Pad B  or  Spaceでタイトル", 0x000000);
#endif
}

eSceneType CreditScene::GetNowScene() const
{
	return E_CREDIT;
}