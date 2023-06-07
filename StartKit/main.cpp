// GBヘッダのインクルード
#include "lib/gb.h"
#include "Mouse.h"
#include "marker.h"
#include "markerManager.h"

// 定数
#define SCREEN_WIDTH  (1024) // 画面横幅
#define SCREEN_HEIGHT (768) // 画面縦幅
#define FRAME_RATE    (60)  // 1秒間に何回画面を描きかえるか


// Windowsプログラムのmain関数
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // GBの初期化
	if( !gb_init(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_MODE, 1, "GBS...test", "GameBaseSystem...") ) {
		gb_errorMessage("GBの初期化に失敗しました");
	}

	// ここにゲームの初期化
	gb_alphaBlendEnable(true);

	gb_fontInit(1, 1);
	gb_fontReadFile("font.fnt", 0);
	gb_fontSetKind(0);

	Mouse mouse;
	MarkerManager mm;

    // ゲームループ
    while( gb_processMessage() ){

        // アプリケーションがアクティブでない場合強制ポーズ
        if( !gb_getActive() ) {
            continue;
        }

        // 時間調整
        if( !gb_wait(FRAME_RATE) ) {
            continue;
        }        

		// ここにゲームの更新処理
		mouse.Update();

		float mx = static_cast<float>(mouse.GetMouseX());
		float my = static_cast<float>(mouse.GetMouseY());

		// 左ボタンクリックしたとき
		if (mouse.IsLButtonTrigger()){
			mm.CreateMarker(mx, my);
		}
		else if (mouse.IsLButtonPress()) { // 左ボタンを押しっぱなし
		}

		if (mouse.IsLButtonRelease()) {
		}

		if (mouse.IsLButtonRelease()) {
		}

        if (mouse.IsRButtonTrigger()) {
			mm.DeleteMarker(mx, my);
        }

        if (mouse.IsRButtonPress()) {
        }

        if (mouse.IsRButtonRelease()) {
        }

		// ここにゲームの描画処理

		// 描画の開始
		gb_drawBegin();

		// 画面の初期化
		gb_clear(COLOR_ARGB(255, 80, 128, 255));

		mm.Draw();

		// 描画の終了
		gb_drawEnd();
	}

	// ここにゲームの終了処理
	gb_fontRelease();

    // GBの終了処理
    gb_end();

	return 0;
}
