//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"

#define GAME_WIDTH			640	//画面の横の大きさ
#define GAME_HEIGHT			480	//画面の縦の大きさ
#define GAME_COLOR			32	//画面のカラービット

#define GAME_WINDOW_BAR		0	//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME	"Dxlib_Movie"	//ウィンドウのタイトル

#define MOVIE_PATH ".\\MOVIE\\neko.mp4"/*".\\MOVIE\\MOV_0013.mp4"*/ //動画のパス

int handle = -1;

//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);				//log.txtを出力しない
	ChangeWindowMode(TRUE);								//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//指定の数値でウィンドウを表示する
	SetWindowStyleMode(GAME_WINDOW_BAR);				//タイトルバーはデフォルトにする
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//ウィンドウのタイトルの文字
	SetAlwaysRunFlag(TRUE);								//非アクティブでも実行する

	if (DxLib_Init() == -1) { return -1; }	//ＤＸライブラリ初期化処理

	handle = LoadGraph(MOVIE_PATH);

	//無限ループ
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーのとき、強制終了
		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		if (GetMovieStateToGraph(handle) == 0)
		{
			SeekMovieToGraph(handle, 0); //動画の再生バーリセット
			PlayMovieToGraph(handle);    //動画の再生状態

			SetMovieVolumeToGraph(5000, handle); //音量調節０が無～10000が動画初期設定の音
		}

		/*DrawGraph(0, 0, handle, FALSE);*/

		DrawExtendGraph(0, 0, GAME_WIDTH, GAME_HEIGHT, handle, FALSE); //画像サイズに合わせる

		DrawString(0, 0, "動画を再生しています・・・", GetColor(255, 255, 255));
		DrawString(0, 20, "猫の動画です", GetColor(255 ,255, 255)); //動画の説明

		ScreenFlip();		//モニタのリフレッシュレートの速さで裏画面を再描画
	}

	DxLib_End();	//ＤＸライブラリ使用の終了処理

	DeleteGraph(handle);

	return 0;
}
