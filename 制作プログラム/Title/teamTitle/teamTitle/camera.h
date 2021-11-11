//--------------------------------------------------------------------------------
//
// �Q�[������[camera.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"
#include "dinput_keyboard.h"

//--------------------------------------------------------------------------------
//�}�N����`
//--------------------------------------------------------------------------------
#define	MAX_POSV_Z		(10)										//�J�����̉��s��
#define	MAX_POSV_Y		(150)										//�J�����̍���
#define SCREEN_WIDTH		(1280)									//�X�N���[���̕�
#define SCREEN_HEIGHT		(720)									//�X�N���[���̍���
#define SCREEN_GAMEWIDTH	(830)									//�Q�[����ʒ��̃X�N���[���̕�
#define SCREEN_GAMEHEIGHT	(720)									//�Q�[����ʒ��̃X�N���[���̍���
#define SCREEN_CENTER_X		(SCREEN_WIDTH/2)						//�X�N���[�����SX���W
#define SCREEN_CENTER_Y		(SCREEN_HEIGHT/2)						//�X�N���[�����SY���W

//--------------------------------------------------------------------------------
//�J�����̍\����
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 posV;			//���݂̎��_
	D3DXVECTOR3 posVDest;		//�ړI�̎��_
	D3DXVECTOR3	posR;			//���݂̒����_
	D3DXVECTOR3	posRDest;		//�ړI�̒����_
	D3DXVECTOR3	posU;			//������x�N�g��
	D3DXVECTOR3 rot;			//�J�����̌���
	D3DXMATRIX	mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX	mtxView;		//�r���[�}�g���b�N�X
}CAMERA;

//================================================================================
//�I�u�W�F�N�g�N���X(�J����)
//================================================================================
class CCamera
{
public:
	CCamera();
	~CCamera();

	void InitCamera(void);
	void UninitCamera(void);
	void UpdateCamera(void);

	CAMERA GetCamera(void) { return m_apCamera; }
	void SetCamera(void);

private:

	CAMERA m_apCamera;	//�J�����̏��
};
#endif
