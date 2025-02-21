#include "CreditScene.h"
#include "../../Utility/PadInput.h"

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

	//一定時間経過で終了
	if (--count < 0)
	{
		return E_END;
	}
	//現在のシーンを返す
	return GetNowScene();
}

void CreditScene::Draw() const
{
	DrawString(0, 0, "Result", 0xffffff);
	DrawFormatString(0, 20, 0xffffff, "あと%d秒でEnd画面へ", (int)(count / 60));
}

eSceneType CreditScene::GetNowScene() const
{
	return E_CREDIT;
}