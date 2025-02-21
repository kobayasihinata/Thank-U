#include "CreditScene.h"
#include "../../Utility/PadInput.h"
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

	//一定時間経過で終了
	if (--count < 0)
	{
		return E_END;
	}
	DebugInfomation::Add("count", 300);
	//現在のシーンを返す
	return GetNowScene();
}

void CreditScene::Draw() const
{
	DrawString(0, 0, "Credit", 0xffffff);
	DrawFormatString(0, 20, 0xffffff, "あと%d秒でEnd画面へ", (int)(count / 60));
}

eSceneType CreditScene::GetNowScene() const
{
	return E_CREDIT;
}