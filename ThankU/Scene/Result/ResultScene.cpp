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

	//Bボタンでタイトルへ
	if(PadInput::GetButton()
	//現在のシーンを返す
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