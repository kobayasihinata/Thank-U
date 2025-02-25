#include "TitleScene.h"

//Utility
#include"../../Utility/PadInput.h"
#include "../../Utility/KeyInput.h"
#include "../../Utility/Vector2D.h"
#include "../../Utility/Data.h"
#include "../../Utility/DebugInformation.h"
#include "../../Utility/EffectManager.h"

//�R���X�g���N�^   --���������Ăяo�����̂ł����ŏ��������܂���
TitleScene::TitleScene() : 
cursor(0),scale(0), alpha(0), fadein_timer(0), 
obj_location(0), message_x(0),
title_image(NULL),title_logo(NULL), scaling_up(true), 
object_image(),player_icon_x(),player_join(),join_flag(0)
{
}

//�f�X�g���N�^(�j�����鎞) --���V�[���Ǘ��@�\�N���X�����邩�璆�g�͖����Ă����v�B����
TitleScene::~TitleScene()
{
}

//����������
void TitleScene::Initialize()
{
    //�^�C�g��BGM�Đ�
    PlaySoundFile("Rescurce/BGM/TitleBGM.wav", DX_PLAYTYPE_LOOP);

    //�G�t�F�N�g�Ǘ��N���X�擾
    e_manager = EffectManager::Get();

    //�w�i�摜
    title_image = LoadGraph("Rescurce/Image/background.png");
    title_logo = LoadGraph("Rescurce/Image/TitleLogo.png");

    //�e�I�u�W�F�N�g�̉摜
    object_image[0] = LoadGraph("Rescurce/Image/MessageFrame.png");
    object_image[1] = LoadGraph("Rescurce/Image/Menu.png");
    object_image[2] = LoadGraph("Rescurce/Image/Cursor.png");
    object_image[3] = LoadGraph("Rescurce/Image/Line_Message.png");
    object_image[4] = LoadGraph("Rescurce/Image/Menu.png");

    //�G�l�~�[�p
    object_image[5] = LoadGraph("Rescurce/Image/EnemyMessage.png");
    object_image[6] = LoadGraph("Rescurce/Image/Icon.png");
    
    message_image[0] = LoadGraph("Rescurce/Image/Title/TitleImages/EnemyMessage_1.png");
    message_image[1] = LoadGraph("Rescurce/Image/Title/TitleImages/EnemyMessage_2.png");
    message_image[2] = LoadGraph("Rescurce/Image/Title/TitleImages/EnemyMessage_3.png");
    message_image[3] = LoadGraph("Rescurce/Image/Title/TitleImages/EnemyMessage_4.png");
    message_image[4] = LoadGraph("Rescurce/Image/Title/TitleImages/EnemyMessage_5.png");
    message_image[5] = LoadGraph("Rescurce/Image/Title/TitleImages/EnemyMessage_6.png");
    message_image[6] = LoadGraph("Rescurce/Image/Title/TitleImages/EnemyMessage_7.png");
    message_image[7] = LoadGraph("Rescurce/Image/Title/TitleImages/EnemyMessage_8.png");
    message_image[8] = LoadGraph("Rescurce/Image/Title/TitleImages/EnemyMessage_9.png");

   //�Q����
   object_image[7] = LoadGraph("Rescurce/Image/Player1.png");
   object_image[8] = LoadGraph("Rescurce/Image/Player2.png");
   object_image[9] = LoadGraph("Rescurce/Image/Player3.png");
   object_image[10] = LoadGraph("Rescurce/Image/Player4.png");
   object_image[11] = LoadGraph("Rescurce/Image/Button.png");

   //�I�u�W�F�N�g�̊�ƂȂ�ʒu
    obj_location.x = SCREEN_WIDTH;  //1920
    obj_location.y = SCREEN_HEIGHT; //1080  
    message_x = SCREEN_WIDTH / 1.2f; // ���b�Z�[�W�A�C�R���̏����ʒu����ʉE���ɐݒ�

    //�Q���҂̏�����
    for (int i = 0; i < 4; i++) {
        player_icon_x[i] = SCREEN_WIDTH; // �����ʒu����ʉE���ɐݒ�
        player_join[i] = false; // �Q���t���O��������
    }

    //�R���g���[���[1�͋����I�Ƀv���C���[1
    if (Data::player_data[0].use_controller == 0)
    {
        Data::player_data[0].use_controller = DX_INPUT_PAD1;
        Data::player_num++;
        player_join[0] = true;
        join_flag++;    //�Q�����܂����B
    }

    random_image_timer = 0; // �^�C�}�[�ϐ��̏�����
    current_image_index = rand() % 9; // �����_���ȉ摜�̏����I��
}

//�I��������
void TitleScene::Finalize()
{
    //BGM���~�߂�
    StopSoundFile();
}

//�X�V����(���݃V�[��)
eSceneType TitleScene::Update()
{
    //�I�u�W�F�N�g�̉��o����
    ObjectMove();

    //�L�[�{�[�h�̃C���X�^���X�擾(Singleton)
    KeyInput* key_input = KeyInput::Get();

    /* --- �J�[�\���̑��� --- */
    if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_Y) || 
        key_input->GetKeyState(KEY_INPUT_UP) == eInputState::Pressed)
    {
        cursor--;
        // 1�ԏ�ɓ��B������A��ԉ��ɂ���
        if (cursor < 0)  cursor = 2;
    }
    if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_A) || 
        key_input->GetKeyState(KEY_INPUT_DOWN) == eInputState::Pressed)
    {
        cursor++;
        // 1�ԉ��ɓ��B������A��ԏ�ɂ���
        if (cursor > 2) cursor = 0;
    }
    if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_B) || key_input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
    {
        //�J�[�\������(���肵����ʂɑJ�ڂ���)
        switch (cursor)
        {
        case 0:
            return eSceneType::E_INGAME;
        case 1:
            return eSceneType::E_CREDIT;
        default:
            return eSceneType::E_END;
        }
    }

    //�R���g���[���[��1�`4�Ȃ̂�for�����킷
    for (int i = 1; i <= 4; i++)
    {
        //�{�^���������ꂽ���ɎQ��
        if (PadInput::GetButtonDown(i, XINPUT_BUTTON_X))
        {
            //�Q��
            if (CheckUseController(i) == -1)
            {
                Data::player_data[Data::player_num].use_controller = i;
                Data::player_data[Data::player_num].number = Data::player_num;
                Data::player_num++;
            }
        }
    }

    //Data���Q�Ƃ��ăA�C�R���̉��o
    for (int i = 0; i < 4; i++)
    {
        //�R���g���[���[�����蓖�Ă��Ă��遁�v���C���[������Ɣ��f
        if (Data::player_data[i].use_controller != 0 && !player_join[i])
        {
            //���o�̊J�n
            player_join[i] = true;
            join_flag++;
        }
    }

    // �^�C�}�[���C���N�������g
    random_image_timer++;
    // ���Ԋu (�Ⴆ��60�t���[�� = 1�b) ���ƂɃ����_���ȉ摜��I��
    if (random_image_timer >= 60 * 3)   //��--60�~3�Ȃ̂ł�������3�b
    {
        random_image_timer = 0; // �^�C�}�[�����Z�b�g
        current_image_index = rand() % 9; // �����_���ȉ摜��I��
    }

#ifdef _DEBUG
    //�f�o�b�O�p(���U���g���)
    if (PadInput::GetButtonDown(DX_INPUT_PAD1, XINPUT_BUTTON_START) ||key_input->GetKeyState(KEY_INPUT_R) == eInputState::Pressed)
    {
        return eSceneType::E_RESULT;
    }
    //�f�o�b�O�p��--�@A�L�[ �ŎQ�� ���ЂƂ�p
    if (key_input->GetKeyState(KEY_INPUT_A) == eInputState::Pressed)
    {
        //�R���g���[���[��1�`�S�Ȃ̂�for��
        for (int i = 1; i <= 4; i++)
        {
            //�Q��
            if (CheckUseController(i) == -1)
            {
                Data::player_data[Data::player_num].use_controller = i;
                Data::player_data[Data::player_num].number = Data::player_num;
                Data::player_num++;
                break;
            }
        }
    }
    //�G�t�F�N�g�e�X�g(����)
    if (key_input->GetKeyState(KEY_INPUT_1) == eInputState::Pressed)
    {
        e_manager->SpawnEffect({ (float)GetRand(SCREEN_WIDTH),(float)GetRand(SCREEN_HEIGHT) }, eEffectList::eExplosion);
    }
    //�G�t�F�N�g�e�X�g(�ׂ�������)
    if (key_input->GetKeyState(KEY_INPUT_2) == eInputState::Pressed)
    {
        e_manager->SpawnEffect({ (float)GetRand(SCREEN_WIDTH),(float)GetRand(SCREEN_HEIGHT) }, eEffectList::ePuffAndStar);
    }
    //�G�t�F�N�g�e�X�g(Anima)
    if (key_input->GetKeyState(KEY_INPUT_3) == eInputState::Pressed)
    {
        e_manager->SpawnEffect({ (float)GetRand(SCREEN_WIDTH),(float)GetRand(SCREEN_HEIGHT) }, eEffectList::eAnima);
    }
    //�G�t�F�N�g�e�X�g(BigHit)
    if (key_input->GetKeyState(KEY_INPUT_4) == eInputState::Pressed)
    {
        e_manager->SpawnEffect({ (float)GetRand(SCREEN_WIDTH),(float)GetRand(SCREEN_HEIGHT) }, eEffectList::eBighit);
    }
    //�G�t�F�N�g�e�X�g(BigHit)
    if (key_input->GetKeyState(KEY_INPUT_5) == eInputState::Pressed)
    {
        e_manager->SpawnEffect({ (float)GetRand(SCREEN_WIDTH),(float)GetRand(SCREEN_HEIGHT) }, eEffectList::eBloodImpact);
    }
#endif // _DEBUG
    DebugInfomation::Add("cont1", PadInput::GetButton(DX_INPUT_PAD1, XINPUT_BUTTON_A));
    DebugInfomation::Add("cont2", PadInput::GetButton(DX_INPUT_PAD2, XINPUT_BUTTON_A));
    DebugInfomation::Add("cont3", PadInput::GetButton(DX_INPUT_PAD3, XINPUT_BUTTON_A));
    DebugInfomation::Add("cont4", PadInput::GetButton(DX_INPUT_PAD4, XINPUT_BUTTON_A));
    // ���݂̃V�[���^�C�v��Ԃ�
    return GetNowScene();
}

//�`�揈��
void TitleScene::Draw() const
{
    DrawGraph(0, 0, title_image, true);         //�w�i�摜�̕`��
    DrawGraph(0.0f, 0.0f, title_logo, true);    //�^�C�g�����S
    DrawGraph(0, 0, object_image[3], true);     //���b�Z�[�W�o�[(���̘g�݂����Ȃ��)
    DrawGraph(10, 500, object_image[11], true); //�������

    //�G���̃��b�Z�[�W
   // DrawRotaGraph(500, 400, scale, 0.0f, object_image[5], true); //���b�Z�[�W(������Ƙb�����Ăق�����)
    DrawRotaGraph(75, 340, 1.0f, 0.0f, object_image[6], true);   //�A�C�R��
    // �����_���摜��`��
    DrawRotaGraph(500, 400, scale, 0.0f, message_image[current_image_index], true);

    //���b�Z�[�W�A�C�R��(���j���[�g)
    DrawRotaGraph(message_x, obj_location.y / 1.65f, (scale - 0.2), 0.0f, object_image[0], true);

    //�t�F�[�h�C�����ĕ`�� ----�G�t�F�N�g�J�n
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

    //���j���[(����)
    DrawRotaGraph(message_x, obj_location.y / 1.65f, (scale - 0.2), 0.0f, object_image[1], true);
    //�J�[�\��(���M�{�^��)
    DrawRotaGraph(SCREEN_WIDTH / 1.45f, (obj_location.y / 2.2) + cursor * 155.0f, 1.8f, 0.0, object_image[2], true);

    //�u�����h���[�h������ ----�G�t�F�N�g�I��
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    // �Q���҃A�C�R����`��
    for (int i = 0; i < 4; i++) {
        //�����̃R���g���[���[���������甽������
        //�R���g���[���[�����蓖�Ă��Ă��邩�Ŕ��f
        if (Data::player_data[i].use_controller > 0)
        {
            int use = Data::player_data[i].use_controller;
            if (PadInput::GetButton(use, XINPUT_BUTTON_A) ||
                PadInput::GetButton(use, XINPUT_BUTTON_B) ||
                PadInput::GetButton(use, XINPUT_BUTTON_X) ||
                PadInput::GetButton(use, XINPUT_BUTTON_Y))
            {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
                //�����`��
                for (int j = 0; j < 5; j++)
                {
                    DrawCircleAA(player_icon_x[i] + i * 130 + 60, obj_location.y / 4.2f + 60, 60 + (j * 5), 20, 0xffffff, true);
                }
                SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
            }
            DrawGraph(player_icon_x[i] + i * 130, obj_location.y / 4.2f, object_image[7 + i], true);
        }
    }

    SetFontSize(50); //�t�H���g�T�C�Y��ݒ�
    DrawFormatString(SCREEN_WIDTH / 1.8, obj_location.y / 1.25f, GetColor(0, 0, 0), "����", true);    //UI

    // ���Ǐ�Ԃ̕`��
    DrawFormatString(SCREEN_WIDTH / 1.8 + 105, obj_location.y / 1.25f, GetColor(0, 0, 0), "%d", join_flag, false);
 }

//���݃V�[�������擾
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType();
}

//�I�u�W�F�N�g�̉��o����
void TitleScene::ObjectMove()
{
    //���X�ɑ傫���Ȃ�I�Ȃ��
    if (scaling_up){
       scale += 0.05f;
        if (scale >= 1.0f){
            scale = 1.0f;
            scaling_up = false;
        }
    }
    // �t�F�[�h�C���̏���
    if (fadein_timer < 60) {  alpha = fadein_timer * 5; // �A���t�@�l�𑝉�
                              fadein_timer++;   }
    else {   alpha = 255; }    

    // �Q���҃A�C�R���̃X���C�h����
    for (int i = 0; i < 4; i++) {
        if (player_join[i] && player_icon_x[i] > SCREEN_WIDTH / 1.5f) {
            player_icon_x[i] -= 10; // �X���C�h���x�𒲐�
        }
    }
}

int TitleScene::CheckUseController(int _pad)
{
    //Player�̐�����
    for (int i = 0; i < 4; i++)
    {
        //�R���g���[���[�����Ɋ��蓖�Ă��Ă���Ȃ�g���Ă���v���C���[�̈ʒu���擾
        if (Data::player_data[i].use_controller == _pad)
        {
            return i;
        }
    }
    //�ǂ��ɂ����蓖�Ă��ĂȂ��Ȃ�-1
    return -1;
}
