//=============================================================================
//
// ���͏��� [input.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INPUT_KEYSTATE (256)	// ���͏��

#define INPUT_L_CLICK (0)	// ���N���b�N
#define INPUT_R_CLICK (1)	// �E�N���b�N
#define INPUT_M_CLICK (2)	// �z�C�[���N���b�N
#define INPUT_MAX_CLICK (3)	// �ő�{�^����

//*****************************************************************************
// ���̓N���X ( ��{ )
//*****************************************************************************
class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;		// �C���v�b�g�̃I�u�W�F�N�g
	HWND m_hWnd;						// �E�B���h�E�̃n���h���ۑ��p
};

//*****************************************************************************
// �L�[�{�[�h���̓N���X ( �p����: ���̓N���X )
//*****************************************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRepeat(int nKey);
	bool GetRelease(int nKey);

private:
	LPDIRECTINPUTDEVICE8 m_pDevice;	// �L�[�{�[�h�p�f�o�C�X

	// �L�[���
	BYTE m_aKeyState[INPUT_KEYSTATE];
	BYTE m_aKeyStateTrigger[INPUT_KEYSTATE];
	BYTE m_aKeyStateRepeat[INPUT_KEYSTATE];
	BYTE m_aKeyStateRelease[INPUT_KEYSTATE];
	BYTE m_aCountRepeat[INPUT_KEYSTATE];
};

//*****************************************************************************
// �}�E�X���̓N���X ( �p����: ���̓N���X )
//*****************************************************************************
class CInputMouse : public CInput
{
public:
	typedef enum
	{
		MOUSESTATE_LCLICK = 0,
		MOUSESTATE_RCLICK,
		MOUSESTATE_WHEELCLICK,
		MOUSESTATE_MAX
	} MOUSESTATE;

	CInputMouse();
	~CInputMouse();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetPress(int nButton);
	bool GetTrigger(int nButton);
	bool GetRepeat(int nButton);
	bool GetRelease(int nButton);
	D3DXVECTOR2 GetPos(void);
	D3DXVECTOR2 GetVelocity(void);

private:
	LPDIRECTINPUTDEVICE8 m_pDevice;	// �}�E�X�p�f�o�C�X

	DIMOUSESTATE2 m_diMouseState;	// ���݂̏��
	DIMOUSESTATE2 m_diPrevState;	// �O��̏��
	int m_nRepeatCounter[INPUT_MAX_CLICK];			// ���s�[�g����̃J�E���^
};
#endif