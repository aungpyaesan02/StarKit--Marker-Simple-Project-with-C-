// GB�w�b�_�̃C���N���[�h
#include "lib/gb.h"
#include "Mouse.h"
#include "marker.h"
#include "markerManager.h"

// �萔
#define SCREEN_WIDTH  (1024) // ��ʉ���
#define SCREEN_HEIGHT (768) // ��ʏc��
#define FRAME_RATE    (60)  // 1�b�Ԃɉ����ʂ�`�������邩


// Windows�v���O������main�֐�
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // GB�̏�����
	if( !gb_init(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_MODE, 1, "GBS...test", "GameBaseSystem...") ) {
		gb_errorMessage("GB�̏������Ɏ��s���܂���");
	}

	// �����ɃQ�[���̏�����
	gb_alphaBlendEnable(true);

	gb_fontInit(1, 1);
	gb_fontReadFile("font.fnt", 0);
	gb_fontSetKind(0);

	Mouse mouse;
	MarkerManager mm;

    // �Q�[�����[�v
    while( gb_processMessage() ){

        // �A�v���P�[�V�������A�N�e�B�u�łȂ��ꍇ�����|�[�Y
        if( !gb_getActive() ) {
            continue;
        }

        // ���Ԓ���
        if( !gb_wait(FRAME_RATE) ) {
            continue;
        }        

		// �����ɃQ�[���̍X�V����
		mouse.Update();

		float mx = static_cast<float>(mouse.GetMouseX());
		float my = static_cast<float>(mouse.GetMouseY());

		// ���{�^���N���b�N�����Ƃ�
		if (mouse.IsLButtonTrigger()){
			mm.CreateMarker(mx, my);
		}
		else if (mouse.IsLButtonPress()) { // ���{�^�����������ςȂ�
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

		// �����ɃQ�[���̕`�揈��

		// �`��̊J�n
		gb_drawBegin();

		// ��ʂ̏�����
		gb_clear(COLOR_ARGB(255, 80, 128, 255));

		mm.Draw();

		// �`��̏I��
		gb_drawEnd();
	}

	// �����ɃQ�[���̏I������
	gb_fontRelease();

    // GB�̏I������
    gb_end();

	return 0;
}
