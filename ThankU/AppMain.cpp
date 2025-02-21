#include "DxLib.h"
#include   "Utility/Common.h"

#include"Scene/SceneManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    if (DxLib_Init() == -1)  // ＤＸライブラリ初期化処理
    {
        return -1;           // エラーが起きたら直ちに終了
    }

    //例外処理(異常が発生したら、catch文に飛びます)
    try
    {
        //シーンマネージャー機能の生成
        SceneManager manager;

        //シーンマネージャー機能の初期化処理
        manager.Initialize();

        //シーンマネージャー機能の更新処理
        manager.Update();

        //シーンマネージャー機能の終了処理
        manager.Finalize();
    }
    catch (const char* err_log)
    {
        //エラー発生内容の出力
        OutputDebugString(err_log);

        //エラー終了を通知
        return -1;
    }

    DxLib_End();             // ＤＸライブラリ使用の終了処理

    return 0;                // ソフトの終了
}