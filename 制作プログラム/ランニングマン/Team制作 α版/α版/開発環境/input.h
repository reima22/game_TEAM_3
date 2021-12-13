//==============================================================================
//
// ���͏����kinput.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define KEY_STATE	(256)	// ���͏��

// ���̓N���X
class CInput
{
public:
	typedef enum 
	{
		KEYINFO_OK = 0,				// ����
		KEYINFO_UP,					// ��
		KEYINFO_DOWN,				// ��
		KEYINFO_LEFT,				// ��
		KEYINFO_RIGHT,				// �E
		KEYINFO_WALK_UP,			// ��(�k��)
		KEYINFO_WALK_DOWN,			// ��(�k��)
		KEYINFO_WALK_LEFT,			// ��(�k��)
		KEYINFO_WALK_RIGHT,			// �E(�k��)
		KEYINFO_JUMP,				// �W�����v
		KEYINFO_PAUSE,				// �|�[�Y
		KEYINFO_TUTO_BACK,			// �`���[�g���A���y�[�W�߂�
		KEYINFO_TURN_LEFT,			// �J��������
		KEYINFO_TURN_RIGHT,			// �J��������E
		KEYINFO_TURN_PLAYER_LEFT,	// �v���C���[����
		KEYINFO_TURN_PLAYER_RIGHT,	// �v���C���[����E
		KEYINFO_MINUS_MOTION,		// ���[�V�������ڋt�s(��)
		KEYINFO_PLUS_MOTION,		// ���[�V�������ڏ��s(�i)
		KEYINFO_CAMERA_UP,			// �J�����㏸
		KEYINFO_CAMERA_DOWN,		// �J�������~
		KEYINFO_FOGSTART_PLUS,
		KEYINFO_FOGSTART_MINUS,
		KEYINFO_FOGEND_PLUS,
		KEYINFO_FOGEND_MINUS,
		KEYINFO_MAX
	}KEYINFO;

	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;	// �������z�֐���

protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;		// �f�o�C�X�|�C���^
	static LPDIRECTINPUT8 m_pInput;		// �S�̂ň�ŗǂ�(static:�ÓI�����o�ϐ�)	
	static int m_aKeyInfo[KEYINFO_MAX];	// ���̓L�[���
};

class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	static CInputKeyboard *Create(HINSTANCE hInstance, HWND hWnd);

	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey);

private:
	BYTE m_aKeyState[KEY_STATE];			// �L�[�v���X���
	BYTE m_aKeyStateTrigger[KEY_STATE];		// �L�[�g���K�[���
	BYTE m_aKeyStateRelease[KEY_STATE];		// �L�[�����[�X���
	BYTE m_aKeyStateRepeat[KEY_STATE];		// �L�[���s�[�g���

	int m_nCountRepeat;						// ���s�[�g�J�E���g
};

#endif
