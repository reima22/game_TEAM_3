//==============================================================================
//
// �f�o�b�O�\�������kdebugproc.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include "debugproc.h"
#include "game.h"
#include "gamepad.h"
#include "fog.h"
#include "main.h"
#include "manager.h"
#include "player.h"
#include "renderer.h"
#include "scene.h"

// �ÓI�����o�ϐ��錾
LPD3DXFONT CDebugProc::m_pFont = NULL;
char CDebugProc::m_aStr[DEBUG_TEXT_NUM];

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CDebugProc::CDebugProc()
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CDebugProc::~CDebugProc()
{
}

//==============================================================================
// ����������
//==============================================================================
void CDebugProc::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �t�H���g�̍쐬
	D3DXCreateFont(
		pDevice, 20, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&m_pFont);

	// ������o�b�t�@�̏�����
	memset(&m_aStr[0], 0, sizeof(m_aStr));
}

//==============================================================================
// �I������
//==============================================================================
void CDebugProc::Uninit(void)
{
	// �t�H���g���̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

//==============================================================================
// �v�����g����
//==============================================================================
void CDebugProc::Print(const char *fmt,...)
{
	// ���[�J���ϐ��錾
	const char *pText = fmt;
	char aStr[DEBUG_TEXT_NUM];
	memset(&aStr[0], 0, sizeof(aStr));

	// �ό�����
	va_list args;

	// �J�n
	va_start(args, fmt);

	for (int nCnt = 0; *pText != '\0'; pText++) 
	{
		// �؂�o���Ə���
		switch (*pText)
		{
		case '%':

			pText++;

			switch (*pText)
			{
			case 'd':	// ����
				nCnt += wsprintf(&aStr[nCnt], "%d", va_arg(args, int));
				break;

			case 'f':	// ��������
				nCnt += sprintf(&aStr[nCnt], "%.3f", va_arg(args, double));
				break;

			case 'c':	// ����
				nCnt += wsprintf(&aStr[nCnt], "%c", va_arg(args, char));
				break;

			case 's':	// ������
				nCnt += wsprintf(&aStr[nCnt], "%s", va_arg(args, const char*));
				break;
				
			default:
				break;
			}
			break;

		default:	// ��O
			nCnt += wsprintf(&aStr[nCnt], "%c", (char*)pText[0]);
			break;
		}
	}

	va_end(args);

	// ������̘A��
	strcat(m_aStr,aStr);
}

//==============================================================================
// �`�揈��
//==============================================================================
void CDebugProc::Draw(void)
{
	// ���[�J���ϐ��錾
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	CPlayer *pPlayer = CGame::GetPlayer();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	int nCountFPS = GetFPSCnt();		// FPS�J�E���g�̎擾
	int nNumAll = CScene::GetNumAll();
	int nMotion = 0;
	int nFrame = 0;
	int nKeyCnt = 0;
	D3DXVECTOR3 movePlayer;
	D3DXVECTOR3 posPlayer;
	D3DXVECTOR3 posSave;		// ���X�|�[���|�C���g

	// NULL�`�F�b�N
	if (pPlayer != NULL)
	{
		posPlayer = pPlayer->GetPosition();
		movePlayer = pPlayer->GetMove();
		posSave = pPlayer->GetPosSave();
	}

	int nlX = gamepad->GetPadlX();
	int nlY = gamepad->GetPadlY();

	CFog *pFog = CGame::GetFog();

	float fFogStart = 0.0f;
	float fFogEnd = 0.0f;
	
	if (pFog != NULL)
	{
		fFogStart = pFog->GetFogStart();
		fFogEnd = pFog->GetFogEnd();
	}

	Print("\n\n\n\n\n\nFPS:%d\n�I�u�W�F�N�g��:%d\n", nCountFPS,nNumAll);
	Print("���X�e�B�b�N�X���F lX:%d lY:%d\n", nlX, nlY);
	Print("�v���C���[�̈ʒu�FX %f,Y %f,Z %f\n", posPlayer.x, posPlayer.y, posPlayer.z);
	Print("���X�|�[���|�C���g�ʒu�FX %f,Y %f,Z %f\n", posSave.x, posSave.y, posSave.z);
	Print("�v���C���[�̈ړ��́F%f %f %f\n", movePlayer.x, movePlayer.y, movePlayer.z);
	Print("�t�H�O�̊J�n�_�F%f \n", fFogStart);
	Print("�t�H�O�̏I���_�F%f \n", fFogEnd);

	// �e�L�X�g�̕`��
	m_pFont->DrawText(NULL, &m_aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 255, 255));

	// ������o�b�t�@�̏�����
	memset(&m_aStr[0], 0, sizeof(m_aStr));
}

//==============================================================================
// ��������
//==============================================================================
CDebugProc *CDebugProc::Create(void)
{
	// �C���X�^���X����
	CDebugProc *pDebugProc;
	pDebugProc = new CDebugProc;

	// ������
	if (pDebugProc != NULL)
	{
		pDebugProc->Init();
	}

	return pDebugProc;
}