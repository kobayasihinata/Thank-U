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

	//���݂̃V�[����Ԃ�
	return GetNowScene();
}

void ResultScene::Draw() const
{

}

eSceneType ResultScene::GetNowScene() const
{
	return E_RESULT;
}