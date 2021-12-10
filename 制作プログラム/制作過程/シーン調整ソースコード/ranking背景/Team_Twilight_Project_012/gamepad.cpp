//==============================================================================
//
// �Q�[���p�b�h���͏����kgamepad.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "input.h"
#include "gamepad.h"

// �ÓI�����o�ϐ��錾
LPDIRECTINPUT8 CGamepad::m_InputInterface;
LPDIRECTINPUTDEVICE8 CGamepad::m_Device;
CGamepad::ButtonState CGamepad::m_ButtonStates[KEYINFO::KEYINFO_MAX];

// �R���X�g���N�^
CGamepad::CGamepad()
{
}

// �f�X�g���N�^
CGamepad::~CGamepad()
{
}

//==============================================================================
// �p�b�h���͂̏���������
//==============================================================================
HRESULT CGamepad::Init(HINSTANCE hInstance, HWND hWnd)
{
	// IDirectInput8�C���^�[�t�F�[�X�̍쐬
	if(FAILED(DirectInput8Create(
		hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_InputInterface,
		NULL)))
	{
		return E_FAIL;
	}

	DeviceEnumParameter parameter;

	parameter.FindCount = 0;
	parameter.GamePadDevice = &m_Device;

	if (FAILED(m_InputInterface->EnumDevices(
		DI8DEVTYPE_GAMEPAD,
		DeviceFindCallBack,
		&parameter,
		DIEDFL_ATTACHEDONLY)))
	{
		return E_FAIL;
	}

	if (FAILED(m_InputInterface->EnumDevices(
		DI8DEVTYPE_JOYSTICK,
		DeviceFindCallBack,
		&parameter,
		DIEDFL_ATTACHEDONLY)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X�̐���
	if (FAILED(m_InputInterface->CreateDevice(
		GUID_Joystick,
		&m_Device,
		NULL)))
	{
		return E_FAIL;
	}

	// ���͏��̏�����
	for (int nCnt = 0; nCnt < KEYINFO::KEYINFO_MAX; nCnt++)
	{
		m_ButtonStates[nCnt] = ButtonState::ButtonStateNone;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(m_Device->SetDataFormat(
		&c_dfDIJoystick)))
	{
		return E_FAIL;
	}

	// �����[�h���Βl���[�h�Ƃ��Đݒ�
	DIPROPDWORD diprop;
	ZeroMemory(&diprop, sizeof(diprop));
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.diph.dwObj = 0;
	diprop.dwData = DIPROPAXISMODE_ABS;	// ��Βl���[�h�̎w��(DPROPAXISMODE_REL�ɂ����瑊�Βl)
	
	// �����[�h��ύX
	if (FAILED(m_Device->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return false;
	}

	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwHow = DIPH_BYOFFSET;
	diprg.diph.dwObj = DIJOFS_X;
	diprg.lMin = -2000;
	diprg.lMax = 2000;
	if (FAILED(m_Device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	diprg.diph.dwObj = DIJOFS_Y;
	if (FAILED(m_Device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	// �������[�h�̐ݒ�
	if (FAILED(m_Device->SetCooperativeLevel(
		hWnd,
		(DISCL_FOREGROUND | DISCL_EXCLUSIVE))))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==============================================================================
// �p�b�h���͂̏I������
//==============================================================================
void CGamepad::Uninit(void)
{
	if (m_Device != NULL)
	{
		// �A�N�Z�X���̔j��
		m_Device->Unacquire();

		m_Device->Release();
		m_Device = NULL;
	}

	if (m_InputInterface != NULL)
	{
		m_InputInterface->Release();
		m_InputInterface = NULL;
	}
}

//==============================================================================
// �p�b�h���͂̍X�V����
//==============================================================================
void CGamepad::Update(void)
{
	if (m_Device == nullptr)
	{
		return;
	}

	DIJOYSTATE pad_data;

	HRESULT hr = m_Device->GetDeviceState(sizeof(DIJOYSTATE), &pad_data);
	if (FAILED(hr))
	{
		if (FAILED(m_Device->Acquire()))
		{
			//for (int nCnt = 0; nCnt < KEYINFO::KEYINFO_MAX; nCnt++)
			//{
			//	//if (m_ButtonStates[nCnt] == )
			//	{
			//		m_ButtonStates[nCnt] = ButtonState::ButtonStateNone;
			//	}
			//}
			m_Device->Poll();
		}
		return;
	}
	
	// �������
	bool is_push[KEYINFO::KEYINFO_MAX] = {};

	int unresponsive_range = 200;
	int nWalkRange = 1500;

	if (pad_data.lX < -unresponsive_range && pad_data.lX > -nWalkRange)
	{// ���ɏ����X����
		is_push[KEYINFO::KEYINFO_WALK_LEFT] = true;
	}
	else if (pad_data.lX > unresponsive_range && pad_data.lX < nWalkRange)
	{// �E�ɌX����
		is_push[KEYINFO::KEYINFO_WALK_RIGHT] = true;
	}

	if (pad_data.lY < -unresponsive_range && pad_data.lY > -nWalkRange)
	{// ��ɏ����X����
		is_push[KEYINFO::KEYINFO_WALK_UP] = true;
	}
	else if (pad_data.lY > unresponsive_range && pad_data.lY < nWalkRange)
	{// ���ɏ����X����
		is_push[KEYINFO::KEYINFO_WALK_DOWN] = true;
	}

	if (pad_data.lX < -nWalkRange)
	{// ���ɌX����
		is_push[KEYINFO::KEYINFO_LEFT] = true;
	}
	else if (pad_data.lX > nWalkRange)
	{// �E�ɌX����
		is_push[KEYINFO::KEYINFO_RIGHT] = true;
	}

	if (pad_data.lY < -nWalkRange)
	{// ��ɌX����
		is_push[KEYINFO::KEYINFO_UP] = true;
	}
	else if (pad_data.lY > nWalkRange)
	{// ���ɌX����
		is_push[KEYINFO::KEYINFO_DOWN] = true;
	}

	// �l�̐ݒ�
	m_nlX = pad_data.lX;
	m_nlY = pad_data.lY;

	if (pad_data.rgdwPOV[0] != 0xFFFFFFFF)
	{
		// 8�����ł̐���
		switch (pad_data.rgdwPOV[0])
		{
			// ��
		case 0:
			is_push[KEYINFO::KEYINFO_UP] = true;
			break;
			// �E��
		case 4500:
			is_push[KEYINFO::KEYINFO_UP] = true;
			is_push[KEYINFO::KEYINFO_RIGHT] = true;
			break;
			// �E
		case 9000:
			is_push[KEYINFO::KEYINFO_RIGHT] = true;
			break;
			// �E��
		case 13500:
			is_push[KEYINFO::KEYINFO_DOWN] = true;
			is_push[KEYINFO::KEYINFO_RIGHT] = true;
			break;
			// ��
		case 18000:
			is_push[KEYINFO::KEYINFO_DOWN] = true;
			break;
			// ����
		case 22500:
			is_push[KEYINFO::KEYINFO_DOWN] = true;
			is_push[KEYINFO::KEYINFO_LEFT] = true;
			break;
			// ��
		case 27000:
			is_push[KEYINFO::KEYINFO_LEFT] = true;
			break;
			// ����
		case 31500:
			is_push[KEYINFO::KEYINFO_UP] = true;
			is_push[KEYINFO::KEYINFO_LEFT] = true;
			break;
		}
	}
	
	for (int nCnt = 0; nCnt < 32; nCnt++)
	{
		if (!(pad_data.rgbButtons[nCnt] & 0x80))
		{
			continue;
		}
		
		switch (nCnt)
		{
		case 2:
			is_push[KEYINFO::KEYINFO_OK] = true;
			break;

		case 3:
			is_push[KEYINFO::KEYINFO_TUTO_BACK] = true;
			break;

		case 4:
			is_push[KEYINFO::KEYINFO_TURN_LEFT] = true;
			break;

		case 5:
			is_push[KEYINFO::KEYINFO_TURN_RIGHT] = true;
			break;

		case 11:
			is_push[KEYINFO::KEYINFO_PAUSE] = true;
			break;
		}
	}

	// ���͏�񂩂�{�^���̏�Ԃ��X�V����
	for (int nCnt = 0; nCnt < KEYINFO::KEYINFO_MAX; nCnt++)
	{
		if (is_push[nCnt] == true)
		{
			if (m_ButtonStates[nCnt] == ButtonState::ButtonStateNone)
			{// ����
				m_ButtonStates[nCnt] = ButtonState::ButtonStateDown;
			}
			else
			{// ����������
				m_ButtonStates[nCnt] = ButtonState::ButtonStatePush;
			}
		}
		else
		{
			if (m_ButtonStates[nCnt] == ButtonState::ButtonStatePush)
			{// �����Ă���Ƃ��납�痣��
				m_ButtonStates[nCnt] = ButtonState::ButtonStateUp;
			}
			else
			{// �����Ă��Ȃ�
				m_ButtonStates[nCnt] = ButtonState::ButtonStateNone;
			}
		}
	}
}

// �Q�[���p�b�h����
CGamepad *CGamepad::Create(HINSTANCE hInstance, HWND hWnd)
{
	// ���[�J���ϐ��錾
	CGamepad *pGamepad;
	pGamepad = new CGamepad;

	// ������
	if (pGamepad != NULL)
	{
		pGamepad->Init(hInstance, hWnd);
	}

	return pGamepad;
}

// �f�o�C�X�񋓃R�[���o�b�N�֐�
BOOL CALLBACK CGamepad::DeviceFindCallBack(
	LPCDIDEVICEINSTANCE ipddi,
	LPVOID pvRef)
{
	DeviceEnumParameter* parameter = (DeviceEnumParameter*)pvRef;
	LPDIRECTINPUTDEVICE8 device = nullptr;

	// ���ɔ������Ă���Ȃ�I��
	if (parameter->FindCount >= 1)
	{
		return DIENUM_STOP;
	}

	// ���������J�E���g
	parameter->FindCount++;

	return DIENUM_CONTINUE;
}

// �v���X
bool CGamepad::GetPress(KEYINFO button)
{
	if (m_ButtonStates[button] == ButtonState::ButtonStatePush || m_ButtonStates[button] == ButtonState::ButtonStateDown)
	{
		return true;
	}

	return false;
}

// �����[�X
bool CGamepad::GetRelease(KEYINFO button)
{
	if (m_ButtonStates[button] == ButtonState::ButtonStateUp)
	{
		return true;
	}

	return false;
}

// �g���K�[
bool CGamepad::GetTrigger(KEYINFO button)
{
	if (m_ButtonStates[button] == ButtonState::ButtonStateDown)
	{
		return true;
	}

	return false;
}