//=============================================================================
//
// ���f���Ǘ� [model.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//==============================================================================
// ���f���Ǘ��N���X
//==============================================================================
class CModel
{
public:
	// ���f���̎��
	typedef enum
	{
		MODELTYPE_PLAYER_BODY = 0,		// �v���C���[�̃p�[�c�i�́j
		MODELTYPE_PLAYER_HEAD,			// �v���C���[�̃p�[�c�i���j
		MODELTYPE_PLAYER_ARM_TOP_R,		// �v���C���[�̃p�[�c�i�E��r�j
		MODELTYPE_PLAYER_ARM_UNDER_R,	// �v���C���[�̃p�[�c�i�E���r�j
		MODELTYPE_PLAYER_HAND_R,		// �v���C���[�̃p�[�c�i�E��j
		MODELTYPE_PLAYER_ARM_TOP_L,		// �v���C���[�̃p�[�c�i����r�j
		MODELTYPE_PLAYER_ARM_UNDER_L,	// �v���C���[�̃p�[�c�i�����r�j
		MODELTYPE_PLAYER_HAND_L,		// �v���C���[�̃p�[�c�i����j
		MODELTYPE_PLAYER_LEG_TOP_R,		// �v���C���[�̃p�[�c�i�E�ځj
		MODELTYPE_PLAYER_LEG_UNDER_R,	// �v���C���[�̃p�[�c�i�E���j
		MODELTYPE_PLAYER_FOOT_R,		// �v���C���[�̃p�[�c�i�E����j
		MODELTYPE_PLAYER_LEG_TOP_L,		// �v���C���[�̃p�[�c�i���ځj
		MODELTYPE_PLAYER_LEG_UNDER_L,	// �v���C���[�̃p�[�c�i�����j
		MODELTYPE_PLAYER_FOOT_L,		// �v���C���[�̃p�[�c�i������j
		MODELTYPE_MAX					// �ő吔
	}MODELTYPE;

	CModel();
	~CModel();
	HRESULT Init(char *pFileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CModel *Create(char *pFileName,D3DXVECTOR3 pos,D3DXVECTOR3 rot);

	void SetParent(CModel *pModel) { m_pParent = pModel; }	// �e�|�C���^�̐ݒ�
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }		// �}�g���b�N�X�̎擾

	// �ʒu�̐ݒ�
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

	// �p�x�̐ݒ�
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

	// ���f���t�@�C�����擾
	//static char *GetFileName(int nType) { return m_pFileName[nType]; }

private:
	LPD3DXMESH m_pMesh;				// ���b�V���|�C���^
	LPD3DXBUFFER m_pBuffMat;		// �}�e���A���o�b�t�@
	DWORD m_nNumMat;				// �}�e���A����

	D3DXMATRIX m_mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;				// �ʒu
	D3DXVECTOR3 m_rot;				// ����
	CModel *m_pParent;				// �e���f���ւ̃|�C���^

	LPDIRECT3DTEXTURE9 *m_pTexture;	// �e�N�X�`���_�u���|�C���^

	//static char *m_pFileName[MODELTYPE_MAX];	// �ǂݍ��ރt�@�C�����p�X
};

#endif