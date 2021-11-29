//=============================================================================
//
// �f�o�b�O�\������ [debugproc.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "main.h"

// �}�N����`
#define DEBUG_TEXT_NUM	(1024)	// ������̒���

//==============================================================================
// �f�o�b�O�\���N���X
//==============================================================================
class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();
	void Init(void);
	void Uninit(void);

	static void Print(const char *fmt, ...);
	static void Draw(void);

	static CDebugProc *Create(void);

private:
	static LPD3DXFONT m_pFont;		// �t�H���g�̃|�C���^
	static char m_aStr[DEBUG_TEXT_NUM];	// ��������i�[����o�b�t�@
};

#endif
