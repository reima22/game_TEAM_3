
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
//#include "sceneBillboard.h"

//==============================================================================
// �G�t�F�N�g�N���X
//==============================================================================
class CEffect : public CScene
{
public:
	typedef enum
	{
		EFFECTTYPE_NORMAL = 0,		// �ʏ�
		EFFECTTYPE_SANDSMOKE,		// ����
		EFFECTTYPE_PARTICLE,		// �p�[�e�B�N���G�t�F�N�g
		EFFECTTYPE_MAX
	}EFFECTTYPE;

	CEffect(int nPriority = PRIORITY_EFFECT);
	~CEffect();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffect *Create(void);

	void SetEffect(void);
	void SetVertex(void);
	void EffectMove(void);

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

	// �e�N�X�`���̐ݒ�
	void SetTexture(char *pText);

	// ��ނ̐ݒ�
	void SetType(EFFECTTYPE effectType) { m_effectType = effectType; }

private:
	D3DXVECTOR3 m_pos;								// �ʒu
	D3DXVECTOR3 m_rot;								// ����
	D3DXVECTOR2 m_size;								// �傫��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// �o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;							// ���[���h�}�g���b�N�X
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;			// �e�N�X�`���ւ̃|�C���^

	D3DXVECTOR3 m_move;								// �ړ���
	D3DXCOLOR m_col;								// �F
	EFFECTTYPE m_effectType;						// �G�t�F�N�g�̎��
	float m_fAlphaDown;								// �G�t�F�N�g�̓����x�ቺ�̒l
	float m_fRadius;								// �G�t�F�N�g���a
	
	static int m_nNum;
	int m_nIdx;
};

//==============================================================================
// �����G�t�F�N�g
//==============================================================================
class CEffectSand : public CEffect
{
public:
	CEffectSand();
	~CEffectSand();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffectSand *Create(D3DXVECTOR3 pos);

private:
	CEffect *m_pEffect;
};

#endif