//=============================================================================
//
// ���C������ [main.h]
// Author : Mare Horiai
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#pragma once
#include <windows.h>
#include "d3dx9.h"						// �`�揈���ɕK�v
#define DIRECTINPUT_VERSION	(0x0800)
#include "dinput.h"						// ���͏����ɕK�v
#include "xaudio2.h"					// �T�E���h�Đ��ɕK�v 
#include <time.h>
#include <vector>

//==============================================================================
// ���O���
//==============================================================================
using namespace std;

//==============================================================================
// ���C�u�����̃����N
//==============================================================================
#pragma comment(lib, "d3d9.lib")	// �`�揈���ɕK�v
#pragma comment(lib, "d3dx9.lib")	// �g�����C�u����
#pragma comment(lib, "dxguid.lib")	// �R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib, "dinput8.lib")	// ���͏����ɕK�v
#pragma comment(lib, "winmm.lib")

//==============================================================================
// �}�N����`
//==============================================================================
#define SCREEN_WIDTH	(1280)		// ��ʂ̕�
#define SCREEN_HEIGHT	(720)		// ��ʂ̍���
#define SCREEN_CENTER	(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f))	// ��ʂ̒���
#define SCREEN_SIZE		(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f))		// �������W����̉�ʃT�C�Y
#define COLOR_DEFAULT	(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))								// D3DXCOLOR�^�ϐ��̏����l
#define VECTOR2_NULL	(D3DXVECTOR2(0.0f, 0.0f))										// D3DXVECTOR2�^�ϐ���NULL�l
#define VECTOR3_NULL	(D3DXVECTOR3(0.0f, 0.0f, 0.0f))									// D3DXVECTOR3�^�ϐ���NULL�l
#define PI_DEFAULT		(D3DX_PI * 2.0f)
#define CNT_ONE_SECOND	(60)															// 1�b�Ԃ̃J�E���g��
	
//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
int GetFPSCnt(void);	// FPS�J�E���^�擾

#endif