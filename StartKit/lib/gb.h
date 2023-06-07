//
// Windows �Q�[���v���O���~���O�p�x�[�X�v���O����(GB)
//
// Copyright (C) 2004 - 2007 tiano(Youhei)
// All rights reserved.

#pragma once


// ���C�u�����̃����N�w��
#ifndef _DEBUG
#pragma comment(lib, "gb.lib")
#else
#pragma comment(lib, "gbxd.lib")
#endif


/// �����͋C�ɂ��Ȃ�
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>


/// �V�����^
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

// ����}�N��
#define SAFE_FREE(p)         { if(p) { free(p);        (p)=NULL; } }
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

/// �f�B�X�v���C���[�h
enum DISPLAY_MODE {
    WINDOW_MODE,		/// �E�B���h�E
    FULL_SCREEN_MODE	/// �t���X�N���[��
};

// �������W�w��
typedef struct Position_tag {
    int x; // x���W
    int y; // y���W
}Position;

// 2�����x�N�g��
typedef struct Vector2_tag {
    float x; // x���W
    float y; // y���W
}Vector2;

// 3x3�s��
typedef struct Matrix3x3_tag {
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;
}Matrix3x3;

// �p�֘A
#define PI          (3.141592654f) // �~����
#define RAD_TO_DEG  (57.29577951f) // 1���W�A�����x
#define DEG_TO_RAD  (0.017453293f) // 1�x�����W�A��

// �x�����W�A��
#define gb_toRadian(degree) ((degree) * DEG_TO_RAD)
// ���W�A�����x
#define gb_toDegree(radian) ((radian) * RAD_TO_DEG)
// �p�x�̐��K��(PI�`-PI)
float gb_toPI(float radian);

// �F�w��
#define COLOR_ARGB(a,r,g,b) \
    ((u32)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

// �F
#define COLOR_WHITE  (COLOR_ARGB(255, 255, 255, 255)) // ��
#define COLOR_BLACK  (COLOR_ARGB(255,   0,   0,   0)) // ��
#define COLOR_RED    (COLOR_ARGB(255, 255,   0,   0)) // ��
#define COLOR_GREEN  (COLOR_ARGB(255,   0, 255,   0)) // ��
#define COLOR_BLUE   (COLOR_ARGB(255,   0,   0, 255)) // ��
#define COLOR_YELLOW (COLOR_ARGB(255, 255, 255,   0)) // ��

// �e�N�X�`���֘A
#define INVALID_TEXTURE_INDEX (-1) // �����e�N�X�`���ԍ�
#define TEXTURE_LOAD_FAILED   (-1) // �e�N�X�`���[�̓ǂݍ��ݎ��s

// gb_spriteBegin()�֐��̈����֐ݒ肷��t���O
#define SPRITE_DONOTSAVESTATE			(1 << 0) 
#define SPRITE_DONOTMODIFY_RENDERSTATE	(1 << 1) 
#define SPRITE_OBJECTSPACE				(1 << 2) 
#define SPRITE_BILLBOARD				(1 << 3) 
#define SPRITE_ALPHABLEND				(1 << 4)
#define SPRITE_SORT_TEXTURE				(1 << 5) 
#define SPRITE_SORT_DEPTH_FRONTTOBACK	(1 << 6) 
#define SPRITE_SORT_DEPTH_BACKTOFRONT	(1 << 7) 

// �p�l���֘A
#define PANEL_INVALID_NUM (-1)


/// ���C�u�����̏�����
//
// ����
//
// screenWidth   ��ʉ���
// screenHeight  ��ʏc��
// mode          ��ʃ��[�h
// pWndClassName �E�B���h�E�N���X��
// pAppName      �A�v���P�[�V������
//
// �߂�l
//
// �������Ɏ��s�����ꍇ false
//
bool gb_init(int screenWidth, int screenHeight, DISPLAY_MODE mode, u32 multiSampleLevel, const char* pWndClassName, const char* pAppName, void (*pDrawCallFunc)(void) = NULL);

/// ���C�u�����̏I������
void gb_end(void);

/// ���b�Z�[�W���[�v����
//
// �߂�l
//
// �I�����b�Z�[�W���󂯎�����ꍇ false
//
bool gb_processMessage(void);

/// ���Ԓ���
//
// ����
//
// frameRate �t���[�����[�g(1�b�Ԃɉ�frame�X�V���邩�Ƃ����P��)
//
// �߂�l
//
// �X�V���ԂɒB�����ꍇ true
//
bool gb_wait(int frameRate);

/// �A�N�e�B�u���ǂ����̎擾
bool gb_getActive(void);

/// �}�E�X�J�[�\���̗L���E������ݒ肷��
//
// ����
//
// enable �}�E�X�J�[�\����L���ɂ���ꍇ true
//
void gb_mouseCursorEnable(bool enable);

/// �G���[���b�Z�[�W�_�C�A���O�̕\��
//
// ����
//
// pMessage ���b�Z�[�W������̐擪�A�h���X
//
void gb_errorMessage(const char* pMessage);

/// �Ȃ�炩�̎��Ԃ��N�����Ƃ��ɌĂяo���֐��̐ݒ�
//
// ����
//
// pLostCallFunc  �f�o�C�X���Ȃ�炩�̗��R�ŏ��������ꍇ�ɌĂяo���֐��̃A�h���X
// pResetCallFunc �f�o�C�X�𕜋A����Ƃ��ɌĂяo���֐��̃A�h���X
//
void gb_setCallFunc(void (*pLostCallFunc)(void), bool (*pResetCallFunc)(void));



/// �`�施�ߊJ�n
void gb_drawBegin(void);

/// �`�施�ߏI��
void gb_drawEnd(void);

/// ��ʂ̃N���A
//
// ����
// 
// color �N���A�F
//
void gb_clear(u32 color);

/// Z�o�b�t�@�̃N���A
//
void gb_zclear(void);

// Z�o�b�t�@�̐ݒ�
//
// enable �L���ɂ���ꍇ true
//
void gb_zbufferEnable(bool enable);

// �A���t�@�u�����h�̐ݒ�
//
// enable �L���ɂ���ꍇ true
//
void gb_alphaBlendEnable(bool enable);

/// ��{�i�}�`�j�`��F�̐ݒ�
//
// ����
// 
// color �`��F
//
void gb_drawColor(u32 color);

/// �_�̕`��
//
// ����
//
// x �_�̕`����Wx
// y �_�̕`����Wy
//
void gb_drawPoint(float x, float y);

/// ���̕`��
//
// ����
//
// x1 ���̕`��J�n���Wx
// y1 ���̕`��J�n���Wy
// x2 ���̕`��I�[���Wx
// y2 ���̕`��I�[���Wy
//
// ���I�[���W�̓_�͕`�悳��Ȃ�
//
void gb_drawLine(float x1, float y1, float x2, float y2);

/// �O�p�`�̕`��
//
// ����
//
// x1 �O�p�`�̒��_1���Wx
// y1 �O�p�`�̒��_1���Wy
// x2 �O�p�`�̒��_2���Wx
// y2 �O�p�`�̒��_2���Wy
// x3 �O�p�`�̒��_3���Wx
// y3 �O�p�`�̒��_3���Wy
//
void gb_drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

/// �O�p�`�̕`��(�h��ׂ�)
//
// ����
//
// x1 �O�p�`�̒��_1���Wx
// y1 �O�p�`�̒��_1���Wy
// x2 �O�p�`�̒��_2���Wx
// y2 �O�p�`�̒��_2���Wy
// x3 �O�p�`�̒��_3���Wx
// y3 �O�p�`�̒��_3���Wy
//
void gb_drawFillTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

/// �����`�̕`��(�h��ׂ�)
//
// ����
//
// x ������Wx
// y ������Wy
// width ��
// height ����
//
void gb_drawFillRect(float x, float y, int width, int height);

/// ���p�`�̕`��
//
// ����
//
// vertex_num ���_��
// vertex[] ���_���X�g
// 
void gb_drawPolygon(u32 vertex_num, Vector2 vertex[]);

// �����~�`��
//
// ����
//
// x �~�̒��S���Wx
// y �~�̒��S���Wy
// d �~�̒��a(pixel)
//
void gb_drawFastCircle(int x, int y, int d);

// �~�`��
//
// ����
//
// x �~�̒��S���Wx
// y �~�̒��S���Wy
// r �~�̔��a(pixel)
//
void gb_drawCircle(float x, float y, float r);

// �~�i�h��ׂ��j�̕`��
//
// ����
//
// x �~�̒��S���Wx
// y �~�̒��S���Wy
// r �~�̔��a(pixel)
//
void gb_drawFillCircle(float x, float y, float r);


// 3x3�P�ʍs��̎擾
//
// ����
//
// pM �P�ʍs���������s��ւ̃|�C���^
//
// �߂�l
//
// ���ʂ��i�[�����s��ւ̃|�C���^
//
Matrix3x3* gb_matrixIdentity(Matrix3x3* pM);

// 3x3�ړ��s��̎擾
//
// ����
//
// pM �ړ��s���������s��ւ̃|�C���^
// x �ړ���x
// y �ړ���y
//
// �߂�l
//
// ���ʂ��i�[�����s��ւ̃|�C���^
//
Matrix3x3* gb_matrixTranslation(Matrix3x3* pM, float x, float y);

// 3x3��]�s��̎擾
//
// ����
//
// pM ��]�s���������s��ւ̃|�C���^
// rad ��]�p�x(���W�A��)
//
// �߂�l
//
// ���ʂ��i�[�����s��ւ̃|�C���^
//
Matrix3x3* gb_matrixRotation(Matrix3x3* pM, float rad);

// 3x3�g�k�s��̎擾
//
// ����
//
// x �g�嗦x
// y �g�嗦y
//
// �߂�l
//
// ���ʂ��i�[�����s��ւ̃|�C���^
//
Matrix3x3* gb_matrixScaling(Matrix3x3* pM, float x, float y);

// 3x3�s��̍����i�Q�̍s��̐ρj
//
// ����
//
// pM �������ʂ�������s��ւ̃|�C���^
// pM1 ��������s��1
// pM2 ��������s��2
//
// �߂�l
//
// ���ʂ��i�[�����s��ւ̃|�C���^
//
Matrix3x3* gb_matrixMultiply(Matrix3x3* pM, const Matrix3x3* pM1, const Matrix3x3* pM2);

// 2�����x�N�g����3x3�s��ɂ����W�ϊ�������
//
// ����
//
// pVo �ϊ����ʂ�������Q�����x�N�g���ւ̃|�C���^
// pV �ϊ�����Q�����x�N�g���ւ̃|�C���^
// pM �ϊ��s��ւ̃|�C���^
//
// �߂�l
//
// ���ʂ��i�[�����Q�����x�N�g���ւ̃|�C���^
//
Vector2* gb_vector2Transform(Vector2* pVo, const Vector2* pV, const Matrix3x3* pM);


// ���͏��擾
void gb_inputGet(void);

// �}�E�X�ʒu���擾�i�N���C�A���gx���W�̎擾�j
//
// �߂�l
//
// �N���C�A���g�G���A�i�E�B���h�E�j��x���W
//
int gb_inputGetMousePosX(void);

// �}�E�X�ʒu���擾�i�N���C�A���gy���W�̎擾�j
//
// �߂�l
//
// �N���C�A���g�G���A�i�E�B���h�E�j��y���W
//
int gb_inputGetMousePosY(void);

// �L�[�i�}�E�X�{�^���j���擾
//
// ����
//
// key �L�[(�}�E�X�{�^��)
//
// �߂�l
//
// �L�[��������Ă����� true
//
bool gb_inputCheckKey(BYTE key);

// �}�E�X�{�^�����擾
//
// ����
//
// buttonNum �}�E�X�{�^���ԍ�
//
// �߂�l
//
// �{�^����������Ă����� true
//
bool gb_inputCheckMouseButton(int buttonNum);


// �e�N�X�`���o�^�֐�
// pFileName    �t�@�C����
// width        �e�N�X�`����
// height       �e�N�X�`������
// �߂�l       �C���f�b�N�X�ԍ�
int gb_textureSetLoadFile(const char* pFileName);

// �e�N�X�`�����[�h�֐�
// �o�^����Ă���e�N�X�`���ł܂����[�h����Ă��Ȃ����̂��ꊇ���[�h����
// �߂�l ���[�h�����݂ďo���Ȃ�������
//        �܂��͊֐��̎��s�s��̏ꍇ TEXTURE_LOAD_FAILED
int gb_textureLoad(void);

// �e�N�X�`���̑S���
void gb_textureAllRelease(void);

// �e�N�X�`���̉��
// list[]   �e�N�X�`���C���f�b�N�X�̃��X�g
// count    �e�N�X�`���C���f�b�N�X��
void gb_textureRelease(int list[], int count);



// �X�v���C�g�`��̊J�n
//
// flags �X�v���C�g�`��ݒ�t���O
void gb_spriteBegin(u32 flags);

// �X�v���C�g�`��̏I��(�`�攽�f)
void gb_spriteEnd(void);

// �X�v���C�g�x�[�X�F�ݒ�
//
// color �F
//
void gb_spriteSetColor(u32 color);

// �X�v���C�g�̃v���C�I���e�B�ݒ�
//
// priority �i�O�j0.0f �` 1.0f�i��j
//
void gb_spriteSetPriority(float priority);

// �X�v���C�g�̕ό`
//
// pMatrix �ϊ��s��̏o��
// pScalingCenter �g�咆�S���W
// scalingRotation �g���]�W��(�g�嗦�̏c���̔䗦���Ⴄ�ꍇ�ɍ�p����)
// pScaling �g�嗦
// pRotationCenter ��]���S���W
// rotation ��]�p�x(���W�A��)
// pTranslation �ړ���
//
Matrix3x3* gb_spriteSetTransform(Matrix3x3* pMatrix, const Vector2* pScalingCenter, float scalingRotation, const Vector2* pScaling, const Vector2* pRotationCenter, float rotation, const Vector2* pTranslation);

// �X�v���C�g�̕`��
// dx : �`����Wx
// dy : �`����Wy
// width : �X�v���C�g��
// height : �X�v���C�g����
// sx : �e�N�X�`�����Wx
// sy : �e�N�X�`�����Wy
void gb_spriteDraw(int texId, float dx, float dy, int width, int height, int sx, int sy);



// �p�l���̓ǂݍ���
//
// pFileName �t�@�C����
//
// �߂�l �p�l���C���f�b�N�X
//
int gb_panelLoad(const char* pFileName);

// �p�l���̕`��
//
// panelMapNum �p�l���C���f�b�N�X
// dx �`����Wx
// dy �`����Wy
//
void gb_panelDraw(int panelMapNum, float dx, float dy);

// �p�l���̉��
//
// list �p�l���C���f�b�N�X�̃��X�g
// count ���X�g��
//
void gb_panelRelease(int list[], int count);

// ���ׂẴp�l���̉��
//
void gb_panelAllRelease(void);



// �t�H���g�̏�����
//
// ����
//
// sheetMax �t�H���g�V�[�g�̍ő喇��
// kindMax �t�H���g�f�[�^�̓ǂݍ��ݏꏊ�ő吔
//
void gb_fontInit(u32 sheetMax, u32 kindMax);

// �t�H���g�V�X�e���̏I������
void gb_fontRelease(void);

// �t�H���g�̎�ޕʉ��
//
// ����
//
// kind �t�H���g�f�[�^�̓ǂݍ��݃C���f�b�N�X�ԍ�(�t�H���g�ԍ�)
//
void gb_fontReleaseKind(u32 kind);

// �t�H���g�f�[�^�̓ǂݍ���
//
// ����
//
// fileName �t�H���g�f�[�^�̃t�@�C����
// kind �t�H���g�f�[�^�̓ǂݍ��݃C���f�b�N�X�ԍ�(�t�H���g�ԍ�)
//
bool gb_fontReadFile(const char* fileName, u32 kind);

// ������̉������擾
//
// ����
//
// pStr ������̐擪�A�h���X
//
// �߂�l
//
// ������̉���
//
int gb_fontGetStringWidth(const char* pStr);

// �t�H���g�̍������擾
//
int gb_fontGetHeight(void);

// �������`�悷�鏉�����W��ݒ�
//
// ����
//
// x ������`��J�n���Wx
// y ������`��J�n���Wy
//
void gb_fontSetPos(float x, float y);

// �t�H���g�̎�ނ�ύX
//
// ����
//
// kind �t�H���g�ԍ�
//
// �߂�l
//
// �t�H���g�̎�ނ����炩�̗��R�ŕύX�ł��Ȃ������Ƃ� false
//
bool gb_fontSetKind(u32 kind);

// ������̕`��
//
// ����
//
// pStr : ������
//
void gb_fontDrawString(const char* pStr);


// �T�E���h�ő�o�^���̎擾
//
// �߂�l
//
// soundNum�ɓo�^�ł���ő吔
//
int gb_soundGetMax(void);

// �T�E���h�̃��[�h
//
// ����
// 
// soundNum : �T�E���h�ǂݍ��ݐ�i���o�[(0�`gb_soundGetMax()-1)
// pFileName : �t�@�C����(wav�t�@�C��)
bool gb_soundLoad(int soundNum, const char* pFileName);

// �T�E���h�̍Đ�
//
// ����
//
// soundNum : �Đ�����T�E���h�̓ǂݍ��ݐ�i���o�[
//
void gb_soundPlay(int soundNum);

// BGM(���[�v�Đ��p)�f�[�^�̃��[�h
//
// ����
//
// pFileName : �t�@�C����(ogg vorvis)
void gb_soundBgmLoad(const char* pFileName);

// BGM�̍Đ�
//
void gb_soundBgmPlay(void);

// BGM���Đ�����Ă��邩�̊m�F
//
// �߂�l
//
// �Đ�����Ă����ꍇ true
//
bool gb_soundBgmIsPlay(void);

// BGM�̒�~
//
void gb_soundBgmStop(void);

// BGM�̃{�����[���ݒ�
//
// ����
//
// volume �{�����[��(�ǂ������l���͌��ݕs���B�������ׂ�)
//
void gb_soundBgmVolume(float volume);

// BGM�̃|�[�Y(�ꎞ��~)
//
void gb_soundBgmPause(void);

// BGM�̃��W���[��(�ĊJ)
//
void gb_soundBgmResume(void);
