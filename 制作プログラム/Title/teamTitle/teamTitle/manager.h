//--------------------------------------------------------------------------------
//
// �Q�[������[manager.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
//�O���錾
//--------------------------------------------------------------------------------
class CRenderer;
class CInputKeyBoard;
class CFade;
class CBg;
class CTitle;
class CTutorial;
class CSound;
class CLight;
class CCamera;

//================================================================================
//�I�u�W�F�N�g�N���X
//================================================================================
class CManager
{

public:

	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,													//�`���[�g���A�����[�h
		MODE_MAX
	}Mode;

	CManager();															//�R���X�g���N�^
	~CManager();														//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance,HWND hWnd, BOOL bWindow);			//����������
	void Uninit(void);													//�I������
	void Update(void);													//�X�V����
	void Draw(void);													//�`�揈��

	static CRenderer *GetRenderer(void);								//Renderer�N���X�̏��
	static CInputKeyBoard*GetInputKeyBoard(void);						//���͏��
	static CFade*GetFade(void) { return m_pFade; }						//�t�F�[�h���

	static void SetMode(Mode mode);
	static Mode GetMode(void) { return m_Mode; }						//���[�h�̎擾

	static void SetSound(CSound*sound) { m_pSound = sound; }			//�T�E���h�̎擾
	static CSound*GetSound(void) { return m_pSound; }					//�T�E���h�̏��

	static CCamera*GetCamera(void) { return m_pCamera; }				//�J�����̏��

private:

	static CTitle*m_pTitle;												// �^�C�g���̃|�C���^
	static CTutorial*m_pTutorial;										// �`���[�g���A���̃|�C���^
	static Mode m_Mode;													// ���[�h�̃|�C���^
	static CFade*m_pFade;												// �t�F�[�h�̃|�C���^
	static CRenderer*m_pRenderer;										// Renerer�̃|�C���^
	static CInputKeyBoard*m_pInputKeyBoard;								// �L�[�{�[�h�̃|�C���^
	static CSound*m_pSound;												// BGM�̃|�C���^
	static CLight*m_pLight;												// ���C�g�̃|�C���^
	static CCamera*m_pCamera;											// �J�����̃|�C���^

};

//--------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//--------------------------------------------------------------------------------
#endif
