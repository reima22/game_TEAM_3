//=============================================================================
//
// ���͏��� [input.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "Input.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//*****************************************************************************
// ���̓N���X ( ��{ )
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInput::CInput()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CInput::~CInput()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �n���h���ۑ�
	m_hWnd = hWnd;

	//DirectInput�I�u�W�F�N�g�̐���
	if (m_pInput == NULL)
	{
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CInput::Uninit(void)
{
	// DirectInput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CInput::Update(void)
{

}


//*****************************************************************************
// �L�[�{�[�h���̓N���X ( �p����: ���̓N���X )
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	// �L�[���̃N���A
	memset(&m_aKeyState[0], 0, sizeof(m_aKeyState));
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));
	memset(&m_aKeyStateRepeat[0], 0, sizeof(m_aKeyStateRepeat));
	memset(&m_aKeyStateRelease[0], 0, sizeof(m_aKeyStateRelease));
	memset(&m_aCountRepeat[0], 0, sizeof(m_aCountRepeat));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g�̐ݒ�i�L�[�{�[�h�j
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h�̐ݒ�i�L�[�{�[�h�j
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�A�N�Z�X���̎擾
	m_pDevice->Acquire();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	// �L�[�{�[�h�f�o�C�X�I�u�W�F�N�g�̊J��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	CInput::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[INPUT_KEYSTATE];

	//�f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nKey = 0; nKey < INPUT_KEYSTATE; nKey++)
		{
			m_aKeyStateTrigger[nKey] = aKeyState[nKey] & (m_aKeyState[nKey] ^ aKeyState[nKey]);
			m_aKeyStateRelease[nKey] = (~aKeyState[nKey]) & m_aKeyState[nKey];
			m_aKeyState[nKey] = aKeyState[nKey];
		}
	}
	else
	{
		//�A�N�Z�X���̎擾
		m_pDevice->Acquire();
	}
}

//=============================================================================
// �L�[�̃v���X�����擾
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�̃g���K�[�����擾
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�̃��s�[�g�����擾
//=============================================================================
bool CInputKeyboard::GetRepeat(int nKey)
{
	if (m_aKeyStateTrigger[nKey] & 0x80)
	{
		return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
	}
	if ((m_aKeyState[nKey] & 0x80))
	{
		m_aCountRepeat[nKey]++;
		if (m_aCountRepeat[nKey] > 20)
		{
			while (m_aKeyState[nKey] & 0x80)
			{
				return (m_aKeyState[nKey] & 0x80) ? true : false;
			}
		}
	}
	if (m_aKeyStateRelease[nKey] & 0x80)
	{
		m_aCountRepeat[nKey] = 0;
	}
	return NULL;
}

//=============================================================================
// �L�[�̃����[�X�����擾
//=============================================================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}


//*****************************************************************************
// �}�E�X���̓N���X ( �p����: ���̓N���X )
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInputMouse::CInputMouse()
{
	m_pDevice = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CInputMouse::~CInputMouse()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g�̐ݒ�i�L�[�{�[�h�j
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	//�������[�h�̐ݒ�i�L�[�{�[�h�j
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�A�N�Z�X���̎擾
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CInputMouse::Uninit(void)
{
	// �L�[�{�[�h�f�o�C�X�I�u�W�F�N�g�̊J��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	CInput::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CInputMouse::Update(void)
{
	// �X�V�O�Ɍ��݂̏���ۑ����Ă���
	m_diPrevState = m_diMouseState;

	// �l�X�V
	if (FAILED(m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &m_diMouseState)))
	{
		//�A�N�Z�X���̎擾
		m_pDevice->Acquire();
	}
}

//=============================================================================
// �}�E�X�̃v���X�����擾
//=============================================================================
bool CInputMouse::GetPress(int nButton)
{
	return (m_diMouseState.rgbButtons[nButton] & 0x80) ? true : false;
}
//=============================================================================
// �}�E�X�̃g���K�[�����擾
//=============================================================================
bool CInputMouse::GetTrigger(int nButton)
{
	if (!(m_diPrevState.rgbButtons[nButton] & 0x80) &&
		m_diMouseState.rgbButtons[nButton] & 0x80)
	{
		return true;
	}

	return false;
}

//=============================================================================
// �}�E�X�̃��s�[�g�����擾
//=============================================================================
bool CInputMouse::GetRepeat(int nButton)
{
	if (GetTrigger(nButton))
	{
		return true;
	}
	if ((m_diMouseState.rgbButtons[nButton] & 0x80))
	{
		m_nRepeatCounter[nButton]++;
		if (m_nRepeatCounter[nButton] > 20)
		{
			while (m_diMouseState.rgbButtons[nButton] & 0x80)
			{
				return (m_diMouseState.rgbButtons[nButton] & 0x80) ? true : false;
			}
		}
	}
	if (GetRelease(nButton))
	{
		m_nRepeatCounter[nButton] = 0;
	}
	return NULL;
}
//=============================================================================
// �}�E�X�̃����[�X�����擾
//=============================================================================
bool CInputMouse::GetRelease(int nButton)
{
	if (m_diPrevState.rgbButtons[nButton] & 0x80 &&
		!(m_diMouseState.rgbButtons[nButton] & 0x80))
	{
		return true;
	}

	return false;
}

//=============================================================================
// �}�E�X�̃J�[�\���ʒu���擾
//=============================================================================
D3DXVECTOR2 CInputMouse::GetPos(void)
{
	POINT point;

	// �}�E�X���W���擾
	GetCursorPos(&point);

	// �X�N���[�����W����N���C�A���g���W�i�E�B���h�E���W�j�ɕϊ�
	ScreenToClient(m_hWnd, &point);

	return D3DXVECTOR2(point.x, point.y);
}

//=============================================================================
// �}�E�X�̈ړ����擾
//=============================================================================
D3DXVECTOR2 CInputMouse::GetVelocity(void)
{
	return D3DXVECTOR2((float)m_diMouseState.lX, (float)m_diMouseState.lY);
}