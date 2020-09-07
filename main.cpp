//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"

#define GAME_WIDTH			640	//��ʂ̉��̑傫��
#define GAME_HEIGHT			480	//��ʂ̏c�̑傫��
#define GAME_COLOR			32	//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_BAR		0	//�^�C�g���o�[�̓f�t�H���g�ɂ���
#define GAME_WINDOW_NAME	"Dxlib_Movie"	//�E�B���h�E�̃^�C�g��

#define MOVIE_PATH ".\\MOVIE\\neko.mp4"/*".\\MOVIE\\MOV_0013.mp4"*/ //����̃p�X

int handle = -1;

//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);				//log.txt���o�͂��Ȃ�
	ChangeWindowMode(TRUE);								//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//�w��̐��l�ŃE�B���h�E��\������
	SetWindowStyleMode(GAME_WINDOW_BAR);				//�^�C�g���o�[�̓f�t�H���g�ɂ���
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//�E�B���h�E�̃^�C�g���̕���
	SetAlwaysRunFlag(TRUE);								//��A�N�e�B�u�ł����s����

	if (DxLib_Init() == -1) { return -1; }	//�c�w���C�u��������������

	handle = LoadGraph(MOVIE_PATH);

	//�������[�v
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��
		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		if (GetMovieStateToGraph(handle) == 0)
		{
			SeekMovieToGraph(handle, 0); //����̍Đ��o�[���Z�b�g
			PlayMovieToGraph(handle);    //����̍Đ����

			SetMovieVolumeToGraph(5000, handle); //���ʒ��߂O�����`10000�����揉���ݒ�̉�
		}

		/*DrawGraph(0, 0, handle, FALSE);*/

		DrawExtendGraph(0, 0, GAME_WIDTH, GAME_HEIGHT, handle, FALSE); //�摜�T�C�Y�ɍ��킹��

		DrawString(0, 0, "������Đ����Ă��܂��E�E�E", GetColor(255, 255, 255));

		ScreenFlip();		//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��
	}

	DxLib_End();	//�c�w���C�u�����g�p�̏I������

	DeleteGraph(handle);

	return 0;
}