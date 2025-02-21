#include "TitleScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
}

void TitleScene::Finalize()
{
}

eSceneType TitleScene::Update()
{
	return eSceneType();
}

void TitleScene::Draw() const
{
	DrawFormatString(10, 10, GetColor(255, 255, 255), "ƒ^ƒCƒgƒ‹‰æ–Ê‚Å‚·");
}

eSceneType TitleScene::GetNowScene() const
{
	return eSceneType();
}
