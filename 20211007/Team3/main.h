//===================================================================
//HeaderFile: main.h
//Author : Yo jitaku
//===================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*******************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*******************************************************************
#include <Windows.h>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <list>
#include <unordered_map>
#include <string>
#include <thread>
#include <memory>
#include "d3dx9.h"
#include "d3dx9math.h"
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include "xaudio2.h"


//*******************************************************************
//���O���
//*******************************************************************
using namespace std;

//*******************************************************************
// ���C�u�����t�@�C���̃����N
//*******************************************************************
#pragma comment(lib, "d3d9.lib")	// �`�揈���ɕK�v
#pragma comment(lib, "d3dx9.lib")	// �g�����C�u����
#pragma comment(lib, "dxguid.lib")	// �R���|�[�l���g�g�p�ɕK�v
#pragma comment(lib, "dinput8.lib")	// ���͏����ɕK�v
#pragma comment(lib, "winmm.lib")

//******************************************************************
// �}�N����`
//******************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)				// ���_�t�H�[�}�b�g
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// ���_�t�H�[�}�b�g3D
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define WINDOW_POS_X (1)			// �E�B���h�E����X���W
#define WINDOW_POS_Y (1)			// �E�B���h�E����Y���W
#define VECTOR3_ZERO (D3DXVECTOR3(0,0,0))

//******************************************************************
// �v���g�^�C�v�錾
//******************************************************************
#ifdef _DEBUG	
int GetFps();
#endif

#endif