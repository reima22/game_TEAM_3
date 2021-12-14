//==============================================================================
//
// �Q�[���p�b�h���͏����kgamepad.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_
#include "main.h"
#include "input.h"

//==============================================================================
// �p�b�h����
//==============================================================================
class CGamepad : public CInput
{
public:
	// �Q�[���p�b�h�f�o�C�X�̍쐬-�f�o�C�X�񋓂̌��ʂ��󂯎��\����
	typedef struct
	{
		LPDIRECTINPUTDEVICE8* GamePadDevice;
		int FindCount;
	}DeviceEnumParameter;

	// �{�^���̏��
	typedef enum
	{
		ButtonStateNone = 0,
		ButtonStateDown,
		ButtonStatePush,
		ButtonStateUp,
		ButtonStateMax,
	} ButtonState;

	CGamepad();
	~CGamepad();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// �p�b�h���͂̏���������
	void Uninit(void);								// �p�b�h���͂̏I������
	void Update(void);								// �p�b�h���͂̍X�V����

	static CGamepad *Create(HINSTANCE hInstance, HWND hWnd);

	static BOOL CALLBACK DeviceFindCallBack(
		LPCDIDEVICEINSTANCE ipddi,
		LPVOID pvRef);

	bool GetPress(KEYINFO button);
	bool GetRelease(KEYINFO button);
	bool GetTrigger(KEYINFO button);

	// �X�e�B�b�N�̓|�������̐��l�擾
	int GetPadlX(void) { return m_nlX; }
	int GetPadlY(void) { return m_nlY; }

private:
	static LPDIRECTINPUT8 m_InputInterface;
	static LPDIRECTINPUTDEVICE8 m_Device;
	static ButtonState m_ButtonStates[KEYINFO::KEYINFO_MAX];

	// �X�e�B�b�N��|�����l
	int m_nlX;
	int m_nlY;
};

// �f�o�C�X�̗�
typedef enum
{
	DIDEVTYPE_MOUSE = 0,	// �}�E�X
	DIDEVTYPE_KEYBOARD,		// �L�[�{�[�h
	DIDEVTYPE_JOYSTICK,		// �W���C�X�e�B�b�N
	DIDEVTYPE_DEVICE,		// ���̑�
	DIDEVTYPE_MAX
} DIDEVTYPE;

#endif
