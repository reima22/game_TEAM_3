//=============================================================================
//
// �G�t�F�N�g�̐ݒ� [effect.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "scene.h"

class CScene2D;

//==============================================================================
// �G�t�F�N�g�N���X
//==============================================================================
class CEffect : public CScene
{
public:
	CEffect(int nPriority = CScene::PRIORITY_EFFECT);
	~CEffect();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffect *Create(void);

	//void SetEffect(void);
	void SetVertex(void);
	//void EffectMove(void);

	// �ʒu�̎擾�E�ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

	// �p�x�̎擾�E�ݒ�
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }

	// �F�̎擾�E�ݒ�
	D3DXCOLOR GetColor(void) { return m_col; }
	void SetColor(D3DXCOLOR col) { m_col = col; }

	// �T�C�Y�̎擾�E�ݒ�
	D3DXVECTOR2 GetSize(void) { return m_size; }
	void SetSize(D3DXVECTOR2 size) { m_size = size; }

	// �����x�ቺ�l�̐ݒ�
	float GetAlphaDown(void) { return m_fAlphaDown; }
	void SetAlphaDown(float fAlphaDown) { m_fAlphaDown = fAlphaDown; }

	// �ړ��͎擾�E�ݒ�
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

	float GetMovePower(void) { return m_fMove; }
	void SetMovePower(float fMove) { m_fMove = fMove; }

	// �e�N�X�`���̐ݒ�
	void SetTexture(char *pText);

private:
	D3DXVECTOR3 m_pos;								// �ʒu
	D3DXVECTOR3 m_rot;								// ����
	D3DXVECTOR2 m_size;								// �傫��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// �o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;							// ���[���h�}�g���b�N�X
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;			// �e�N�X�`���ւ̃|�C���^

	D3DXVECTOR3 m_move;								// �ړ���
	D3DXCOLOR m_col;								// �F
	float m_fAlphaDown;								// �G�t�F�N�g�̓����x�ቺ�̒l

	D3DXVECTOR3 m_rotMove;							// �ړ�����
	float m_fMove;									// �ړ��͊
};

//==============================================================================
// �G�t�F�N�g�ڍ�
//==============================================================================
class CEffectDetail : public CEffect
{
public:
	typedef enum
	{
		EFFECTTYPE_NORMAL = 0,		// �ʏ�
		EFFECTTYPE_SANDSMOKE,		// ����
		EFFECTTYPE_LANDING,			// ���n
		EFFECTTYPE_DIVE_WATER,		// �����֗�����
		EFFECTTYPE_DIVE_LAVA,		// �n��֗�����
		EFFECTTYPE_PARTICLE,		// �p�[�e�B�N���G�t�F�N�g
		EFFECTTYPE_GAMECLEAR,		// �Q�[���N���A���o
		EFFECTTYPE_MAX
	}EFFECTTYPE;

	CEffectDetail(int nPriority = CScene::PRIORITY_EFFECT);
	~CEffectDetail();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffectDetail *Create(EFFECTTYPE effectType, D3DXVECTOR3 pos);

	// �ʒu�ݒ�
	void SetPositionMain(D3DXVECTOR3 pos) { m_posMain = pos; }

	// ��ނ̐ݒ�
	void SetType(EFFECTTYPE effectType) { m_effectType = effectType; }

private:
	CEffect **m_ppEffect;		// �G�t�F�N�g�N���X
	CScene2D *m_pClearEffect;	// 2D�|���S���N���X

	D3DXVECTOR3 m_move;			// �ړ���
	D3DXVECTOR3 m_posMain;		// �ʒu
	int m_nNumEffect;			// �G�t�F�N�g�̌�
	EFFECTTYPE m_effectType;	// �G�t�F�N�g�̎��
};

#endif