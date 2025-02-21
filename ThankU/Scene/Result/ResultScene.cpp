#include "ResultScene.h"

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

	//åªç›ÇÃÉVÅ[ÉìÇï‘Ç∑
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