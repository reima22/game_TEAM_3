//=============================================================================
//
// ���[�V�����Ǘ� [motion.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"
#include "scene.h"
#include "scene3D.h"

// �O���錾
class CModel;	// ���f���N���X
//class CShadow;	// �e�N���X
//class CShadowS;	// �X�e���V���V���h�E

// �}�N����`
#define MOVE_MOTION		(0.1f)		// �ړ����[�V�������s�����x�
#define RUN_MOTION		(2.0f)		// ���郂�[�V�������s�����x�

//==============================================================================
// ���[�V�����Ǘ��N���X
//==============================================================================
class CMotion
{
public:
	// �L�[�v�f
	typedef enum
	{
		KEY_POS_X = 0,	// posX
		KEY_POS_Y,		// posY
		KEY_POS_Z,		// posZ
		KEY_ROT_X,		// rotX
		KEY_ROT_Y,		// rotY
		KEY_ROT_Z,		// rotZ
		KEY_MAX
	}KEY;

	CMotion();
	~CMotion();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;

	// �t���[���J�E���g�̎擾�E�ݒ�
	int GetFrameCnt(void) { return m_nFrameCnt; }
	void SetFrameCnt(int nCnt) { m_nFrameCnt = nCnt; }

	// �L�[�J�E���g�̎擾�E�ݒ�
	int GetKeyCnt(void) { return m_nKeyCnt; }
	void SetKeyCnt(int nCnt) { m_nKeyCnt = nCnt; }

protected:
	// ���f�����
	int m_nNumParts;			// �p�[�c��

	CModel **m_apModel;			// ���f���ւ̃|�C���^
	int *m_aIndexParent;		// �e���f���̃C���f�b�N�X
	float **m_aOffset;			// �e���f������̃I�t�Z�b�g

	// ���[�V�������
	float ****m_aKey;			// �L�[�v�f
	int *m_nNumKey;				// �L�[�̐�
	bool m_bLoop;				// ���[�v���邩
	int **m_pFrame;				// �t���[����

	D3DXVECTOR3 *m_posMemo;		// �u�����h�ۑ��p�ʒu���
	D3DXVECTOR3 *m_rotMemo;		// �u�����h�ۑ��p�������

	bool m_bBlendMotion;		// ���[�V�����u�����h���N������

	int m_nKeyCnt;				// �L�[�̃J�E���^
	int m_nFrameCnt;			// �t���[����
};
#endif
