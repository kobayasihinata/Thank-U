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

	//��莞�Ԍo�߂ŏI��
	if (--count < 0)
	{
		return E_END;
	}
	//���݂̃V�[����Ԃ�
	return GetNowScene();
}

void CreditScene::Draw() const
{
	DrawString(0, 0, "Result", 0xffffff);
	DrawFormatString(0, 20, 0xffffff, "����%d�b��End��ʂ�", (int)(count / 60));
}

eSceneType CreditScene::GetNowScene() const
{
	return E_CREDIT;
}