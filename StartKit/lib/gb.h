//
// Windows ゲームプログラミング用ベースプログラム(GB)
//
// Copyright (C) 2004 - 2007 tiano(Youhei)
// All rights reserved.

#pragma once


// ライブラリのリンク指定
#ifndef _DEBUG
#pragma comment(lib, "gb.lib")
#else
#pragma comment(lib, "gbxd.lib")
#endif


/// ここは気にしない
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>


/// 新しい型
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

// 解放マクロ
#define SAFE_FREE(p)         { if(p) { free(p);        (p)=NULL; } }
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

/// ディスプレイモード
enum DISPLAY_MODE {
    WINDOW_MODE,		/// ウィンドウ
    FULL_SCREEN_MODE	/// フルスクリーン
};

// 整数座標指定
typedef struct Position_tag {
    int x; // x座標
    int y; // y座標
}Position;

// 2次元ベクトル
typedef struct Vector2_tag {
    float x; // x座標
    float y; // y座標
}Vector2;

// 3x3行列
typedef struct Matrix3x3_tag {
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;
}Matrix3x3;

// 角関連
#define PI          (3.141592654f) // 円周率
#define RAD_TO_DEG  (57.29577951f) // 1ラジアン→度
#define DEG_TO_RAD  (0.017453293f) // 1度→ラジアン

// 度→ラジアン
#define gb_toRadian(degree) ((degree) * DEG_TO_RAD)
// ラジアン→度
#define gb_toDegree(radian) ((radian) * RAD_TO_DEG)
// 角度の正規化(PI～-PI)
float gb_toPI(float radian);

// 色指定
#define COLOR_ARGB(a,r,g,b) \
    ((u32)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

// 色
#define COLOR_WHITE  (COLOR_ARGB(255, 255, 255, 255)) // 白
#define COLOR_BLACK  (COLOR_ARGB(255,   0,   0,   0)) // 黒
#define COLOR_RED    (COLOR_ARGB(255, 255,   0,   0)) // 赤
#define COLOR_GREEN  (COLOR_ARGB(255,   0, 255,   0)) // 緑
#define COLOR_BLUE   (COLOR_ARGB(255,   0,   0, 255)) // 青
#define COLOR_YELLOW (COLOR_ARGB(255, 255, 255,   0)) // 黄

// テクスチャ関連
#define INVALID_TEXTURE_INDEX (-1) // 無効テクスチャ番号
#define TEXTURE_LOAD_FAILED   (-1) // テクスチャーの読み込み失敗

// gb_spriteBegin()関数の引数へ設定するフラグ
#define SPRITE_DONOTSAVESTATE			(1 << 0) 
#define SPRITE_DONOTMODIFY_RENDERSTATE	(1 << 1) 
#define SPRITE_OBJECTSPACE				(1 << 2) 
#define SPRITE_BILLBOARD				(1 << 3) 
#define SPRITE_ALPHABLEND				(1 << 4)
#define SPRITE_SORT_TEXTURE				(1 << 5) 
#define SPRITE_SORT_DEPTH_FRONTTOBACK	(1 << 6) 
#define SPRITE_SORT_DEPTH_BACKTOFRONT	(1 << 7) 

// パネル関連
#define PANEL_INVALID_NUM (-1)


/// ライブラリの初期化
//
// 引数
//
// screenWidth   画面横幅
// screenHeight  画面縦幅
// mode          画面モード
// pWndClassName ウィンドウクラス名
// pAppName      アプリケーション名
//
// 戻り値
//
// 初期化に失敗した場合 false
//
bool gb_init(int screenWidth, int screenHeight, DISPLAY_MODE mode, u32 multiSampleLevel, const char* pWndClassName, const char* pAppName, void (*pDrawCallFunc)(void) = NULL);

/// ライブラリの終了処理
void gb_end(void);

/// メッセージループ処理
//
// 戻り値
//
// 終了メッセージを受け取った場合 false
//
bool gb_processMessage(void);

/// 時間調整
//
// 引数
//
// frameRate フレームレート(1秒間に何frame更新するかという単位)
//
// 戻り値
//
// 更新時間に達した場合 true
//
bool gb_wait(int frameRate);

/// アクティブかどうかの取得
bool gb_getActive(void);

/// マウスカーソルの有効・無効を設定する
//
// 引数
//
// enable マウスカーソルを有効にする場合 true
//
void gb_mouseCursorEnable(bool enable);

/// エラーメッセージダイアログの表示
//
// 引数
//
// pMessage メッセージ文字列の先頭アドレス
//
void gb_errorMessage(const char* pMessage);

/// なんらかの事態が起きたときに呼び出す関数の設定
//
// 引数
//
// pLostCallFunc  デバイスがなんらかの理由で消失した場合に呼び出す関数のアドレス
// pResetCallFunc デバイスを復帰するときに呼び出す関数のアドレス
//
void gb_setCallFunc(void (*pLostCallFunc)(void), bool (*pResetCallFunc)(void));



/// 描画命令開始
void gb_drawBegin(void);

/// 描画命令終了
void gb_drawEnd(void);

/// 画面のクリア
//
// 引数
// 
// color クリア色
//
void gb_clear(u32 color);

/// Zバッファのクリア
//
void gb_zclear(void);

// Zバッファの設定
//
// enable 有効にする場合 true
//
void gb_zbufferEnable(bool enable);

// アルファブレンドの設定
//
// enable 有効にする場合 true
//
void gb_alphaBlendEnable(bool enable);

/// 基本（図形）描画色の設定
//
// 引数
// 
// color 描画色
//
void gb_drawColor(u32 color);

/// 点の描画
//
// 引数
//
// x 点の描画座標x
// y 点の描画座標y
//
void gb_drawPoint(float x, float y);

/// 線の描画
//
// 引数
//
// x1 線の描画開始座標x
// y1 線の描画開始座標y
// x2 線の描画終端座標x
// y2 線の描画終端座標y
//
// ※終端座標の点は描画されない
//
void gb_drawLine(float x1, float y1, float x2, float y2);

/// 三角形の描画
//
// 引数
//
// x1 三角形の頂点1座標x
// y1 三角形の頂点1座標y
// x2 三角形の頂点2座標x
// y2 三角形の頂点2座標y
// x3 三角形の頂点3座標x
// y3 三角形の頂点3座標y
//
void gb_drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

/// 三角形の描画(塗り潰し)
//
// 引数
//
// x1 三角形の頂点1座標x
// y1 三角形の頂点1座標y
// x2 三角形の頂点2座標x
// y2 三角形の頂点2座標y
// x3 三角形の頂点3座標x
// y3 三角形の頂点3座標y
//
void gb_drawFillTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

/// 長方形の描画(塗り潰し)
//
// 引数
//
// x 左上座標x
// y 左上座標y
// width 幅
// height 高さ
//
void gb_drawFillRect(float x, float y, int width, int height);

/// 多角形の描画
//
// 引数
//
// vertex_num 頂点数
// vertex[] 頂点リスト
// 
void gb_drawPolygon(u32 vertex_num, Vector2 vertex[]);

// 高速円描画
//
// 引数
//
// x 円の中心座標x
// y 円の中心座標y
// d 円の直径(pixel)
//
void gb_drawFastCircle(int x, int y, int d);

// 円描画
//
// 引数
//
// x 円の中心座標x
// y 円の中心座標y
// r 円の半径(pixel)
//
void gb_drawCircle(float x, float y, float r);

// 円（塗り潰し）の描画
//
// 引数
//
// x 円の中心座標x
// y 円の中心座標y
// r 円の半径(pixel)
//
void gb_drawFillCircle(float x, float y, float r);


// 3x3単位行列の取得
//
// 引数
//
// pM 単位行列を代入する行列へのポインタ
//
// 戻り値
//
// 結果を格納した行列へのポインタ
//
Matrix3x3* gb_matrixIdentity(Matrix3x3* pM);

// 3x3移動行列の取得
//
// 引数
//
// pM 移動行列を代入する行列へのポインタ
// x 移動量x
// y 移動量y
//
// 戻り値
//
// 結果を格納した行列へのポインタ
//
Matrix3x3* gb_matrixTranslation(Matrix3x3* pM, float x, float y);

// 3x3回転行列の取得
//
// 引数
//
// pM 回転行列を代入する行列へのポインタ
// rad 回転角度(ラジアン)
//
// 戻り値
//
// 結果を格納した行列へのポインタ
//
Matrix3x3* gb_matrixRotation(Matrix3x3* pM, float rad);

// 3x3拡縮行列の取得
//
// 引数
//
// x 拡大率x
// y 拡大率y
//
// 戻り値
//
// 結果を格納した行列へのポインタ
//
Matrix3x3* gb_matrixScaling(Matrix3x3* pM, float x, float y);

// 3x3行列の合成（２つの行列の積）
//
// 引数
//
// pM 合成結果を代入する行列へのポインタ
// pM1 合成する行列1
// pM2 合成する行列2
//
// 戻り値
//
// 結果を格納した行列へのポインタ
//
Matrix3x3* gb_matrixMultiply(Matrix3x3* pM, const Matrix3x3* pM1, const Matrix3x3* pM2);

// 2次元ベクトルを3x3行列による座標変換をする
//
// 引数
//
// pVo 変換結果を代入する２次元ベクトルへのポインタ
// pV 変換する２次元ベクトルへのポインタ
// pM 変換行列へのポインタ
//
// 戻り値
//
// 結果を格納した２次元ベクトルへのポインタ
//
Vector2* gb_vector2Transform(Vector2* pVo, const Vector2* pV, const Matrix3x3* pM);


// 入力情報取得
void gb_inputGet(void);

// マウス位置情報取得（クライアントx座標の取得）
//
// 戻り値
//
// クライアントエリア（ウィンドウ）のx座標
//
int gb_inputGetMousePosX(void);

// マウス位置情報取得（クライアントy座標の取得）
//
// 戻り値
//
// クライアントエリア（ウィンドウ）のy座標
//
int gb_inputGetMousePosY(void);

// キー（マウスボタン）情報取得
//
// 引数
//
// key キー(マウスボタン)
//
// 戻り値
//
// キーが押されていたら true
//
bool gb_inputCheckKey(BYTE key);

// マウスボタン情報取得
//
// 引数
//
// buttonNum マウスボタン番号
//
// 戻り値
//
// ボタンが押されていたら true
//
bool gb_inputCheckMouseButton(int buttonNum);


// テクスチャ登録関数
// pFileName    ファイル名
// width        テクスチャ幅
// height       テクスチャ高さ
// 戻り値       インデックス番号
int gb_textureSetLoadFile(const char* pFileName);

// テクスチャロード関数
// 登録されているテクスチャでまだロードされていないものを一括ロードする
// 戻り値 ロードを試みて出来なかった回数
//        または関数の実行不具合の場合 TEXTURE_LOAD_FAILED
int gb_textureLoad(void);

// テクスチャの全解放
void gb_textureAllRelease(void);

// テクスチャの解放
// list[]   テクスチャインデックスのリスト
// count    テクスチャインデックス数
void gb_textureRelease(int list[], int count);



// スプライト描画の開始
//
// flags スプライト描画設定フラグ
void gb_spriteBegin(u32 flags);

// スプライト描画の終了(描画反映)
void gb_spriteEnd(void);

// スプライトベース色設定
//
// color 色
//
void gb_spriteSetColor(u32 color);

// スプライトのプライオリティ設定
//
// priority （前）0.0f ～ 1.0f（後）
//
void gb_spriteSetPriority(float priority);

// スプライトの変形
//
// pMatrix 変換行列の出力
// pScalingCenter 拡大中心座標
// scalingRotation 拡大回転係数(拡大率の縦横の比率が違う場合に作用する)
// pScaling 拡大率
// pRotationCenter 回転中心座標
// rotation 回転角度(ラジアン)
// pTranslation 移動量
//
Matrix3x3* gb_spriteSetTransform(Matrix3x3* pMatrix, const Vector2* pScalingCenter, float scalingRotation, const Vector2* pScaling, const Vector2* pRotationCenter, float rotation, const Vector2* pTranslation);

// スプライトの描画
// dx : 描画座標x
// dy : 描画座標y
// width : スプライト幅
// height : スプライト高さ
// sx : テクスチャ座標x
// sy : テクスチャ座標y
void gb_spriteDraw(int texId, float dx, float dy, int width, int height, int sx, int sy);



// パネルの読み込み
//
// pFileName ファイル名
//
// 戻り値 パネルインデックス
//
int gb_panelLoad(const char* pFileName);

// パネルの描画
//
// panelMapNum パネルインデックス
// dx 描画座標x
// dy 描画座標y
//
void gb_panelDraw(int panelMapNum, float dx, float dy);

// パネルの解放
//
// list パネルインデックスのリスト
// count リスト数
//
void gb_panelRelease(int list[], int count);

// すべてのパネルの解放
//
void gb_panelAllRelease(void);



// フォントの初期化
//
// 引数
//
// sheetMax フォントシートの最大枚数
// kindMax フォントデータの読み込み場所最大数
//
void gb_fontInit(u32 sheetMax, u32 kindMax);

// フォントシステムの終了処理
void gb_fontRelease(void);

// フォントの種類別解放
//
// 引数
//
// kind フォントデータの読み込みインデックス番号(フォント番号)
//
void gb_fontReleaseKind(u32 kind);

// フォントデータの読み込み
//
// 引数
//
// fileName フォントデータのファイル名
// kind フォントデータの読み込みインデックス番号(フォント番号)
//
bool gb_fontReadFile(const char* fileName, u32 kind);

// 文字列の横幅を取得
//
// 引数
//
// pStr 文字列の先頭アドレス
//
// 戻り値
//
// 文字列の横幅
//
int gb_fontGetStringWidth(const char* pStr);

// フォントの高さを取得
//
int gb_fontGetHeight(void);

// 文字列を描画する初期座標を設定
//
// 引数
//
// x 文字列描画開始座標x
// y 文字列描画開始座標y
//
void gb_fontSetPos(float x, float y);

// フォントの種類を変更
//
// 引数
//
// kind フォント番号
//
// 戻り値
//
// フォントの種類が何らかの理由で変更できなかったとき false
//
bool gb_fontSetKind(u32 kind);

// 文字列の描画
//
// 引数
//
// pStr : 文字列
//
void gb_fontDrawString(const char* pStr);


// サウンド最大登録数の取得
//
// 戻り値
//
// soundNumに登録できる最大数
//
int gb_soundGetMax(void);

// サウンドのロード
//
// 引数
// 
// soundNum : サウンド読み込み先ナンバー(0～gb_soundGetMax()-1)
// pFileName : ファイル名(wavファイル)
bool gb_soundLoad(int soundNum, const char* pFileName);

// サウンドの再生
//
// 引数
//
// soundNum : 再生するサウンドの読み込み先ナンバー
//
void gb_soundPlay(int soundNum);

// BGM(ループ再生用)データのロード
//
// 引数
//
// pFileName : ファイル名(ogg vorvis)
void gb_soundBgmLoad(const char* pFileName);

// BGMの再生
//
void gb_soundBgmPlay(void);

// BGMが再生されているかの確認
//
// 戻り値
//
// 再生されていた場合 true
//
bool gb_soundBgmIsPlay(void);

// BGMの停止
//
void gb_soundBgmStop(void);

// BGMのボリューム設定
//
// 引数
//
// volume ボリューム(どういう値かは現在不明。実験すべし)
//
void gb_soundBgmVolume(float volume);

// BGMのポーズ(一時停止)
//
void gb_soundBgmPause(void);

// BGMのレジューム(再開)
//
void gb_soundBgmResume(void);
