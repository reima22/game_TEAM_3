//=============================================================================
//
// 3D�I�u�W�F�N�g�Ǘ� [object.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "scene.h"
#include "scene3D.h"

// �}�N����`
#define MOVE_POWER	(0.1f)
#define MOVE_RADIUS	(2.0f)

// �O���錾
class CModel;			// ���f���N���X
class CShadow;			// �e�N���X
class CObjectSccaford;	// ����I�u�W�F�N�g�N���X

//==============================================================================
// �I�u�W�F�N�g�Ǘ��N���X
//==============================================================================
class CObject : public CScene
{
public:
	// �I�u�W�F�N�g�̑���
	typedef enum
	{
		OBJATTRIBUTE_NONE = 0,			// �w��Ȃ�
		OBJATTRIBUTE_SCAFFORD,			// ����
		OBJATTRIBUTE_SAVE,				// ���Ԓn�_
		OBJATTRIBUTE_START,				// �X�^�[�g�n�_
		OBJATTRIBUTE_GOAL,				// �S�[���n�_
		OBJATTRIBUTE_PHANTOM,			// �����蔻�薳��(���e)
		OBJATTRIBUTE_SCAFFORD_NODROP,	// �������Ȃ�����
		OBJATTRIBUTE_MAX
	}OBJATTRIBUTE;

	// �I�u�W�F�N�g�̈ړ��̎��
	typedef enum
	{
		MOVETYPE_NONE = 0,	// �ړ�����
		MOVETYPE_SIDE,		// ���ړ�
		MOVETYPE_DEPTH,		// �O��ړ�
		MOVETYPE_UPDOWN,	// �㉺�ړ�
		MOVETYPE_MAX
	}MOVETYPE;

	CObject();
	~CObject();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObject *Create(
		D3DXVECTOR3 pos,
		D3DXVECTOR3 rot,
		char *pFileName,
		D3DXVECTOR2 shadowSize,
		MOVETYPE moveType,
		float movePower,
		OBJATTRIBUTE objAttribute);

	HRESULT InitFromData(void);
	static CObject *CreateFromData(int nIdx);

	void MoveObject(void);
	void DropObject(void);
	void ResetObject(void);

	void PhantomObject(void);	// �I�u�W�F�N�g�̌��e��


	// �C���f�b�N�X�̎擾�E�ݒ�
	int GetIdx(void) { return m_nIdx; }
	void SetIdx(int nIdx) { m_nIdx = nIdx; }

	// �ʒu�̎擾�E�ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

	// �p�x�̎擾�E�ݒ�
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }

	// ��ނ̎擾�E�ݒ�
	int GetType(void) { return m_nType; }
	void SetType(int nType) { m_nType = nType; }

	void SetShadowSize(D3DXVECTOR2 shadowSize) { m_shadowSize = shadowSize; }

	CModel *GetModel(void) { return m_pModel; }

	// �t�@�C�����p�X�̎擾�E�ݒ�
	char *GetFileName(void) { return m_pFileName; }
	void SetFileName(char *pFileName) { m_pFileName = pFileName; }
	
	// �I�u�W�F�N�g�̑����̎擾�E�ݒ�
	OBJATTRIBUTE GetObjAttribute(void) { return m_objAttribute; }
	void SetObjAttribute(OBJATTRIBUTE objAttribute) { m_objAttribute = objAttribute; }

	// �ړ��p�^�[���̎擾�ݒ�
	MOVETYPE GetMoveType(void) { return m_moveType; }
	void SetMoveType(MOVETYPE moveType) { m_moveType = moveType; }

	// �ړ������̎擾�E�ݒ�
	D3DXVECTOR3 GetMoveRot(void) { return m_moveRot; }
	void SetMoveRot(D3DXVECTOR3 moveRot) { m_moveRot = moveRot; }

	// �ړ��͂̎擾�E�ݒ�
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

	// �ړ��͂̊����̎擾�E�ݒ�
	float SetMovePower(void) { return m_fMovePower; }
	void SetMovePower(float fMovePower) { m_fMovePower = fMovePower; }

	// ��������
	bool GetDropOut(void) { return m_bDropOut; }
	void SetDropOut(bool bDropOut) { m_bDropOut = bDropOut; }

	// ��x���񂾔���
	bool GetBonus(void) { return m_bBonus; }
	void SetBonus(bool bBonus) { m_bBonus = bBonus; }

private:
	int m_nIdx;						// �I�u�W�F�N�g�̃C���f�b�N�X
	D3DXMATRIX m_mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;				// �ʒu
	D3DXVECTOR3 m_rot;				// ����

	int m_nType;					// ���

	char *m_pFileName;				// �t�@�C�����p�X�̃|�C���^
	CModel *m_pModel;				// ���f���|�C���^

	MOVETYPE m_moveType;			// �ړ��p�^�[��
	D3DXVECTOR3 m_move;				// �ړ���
	D3DXVECTOR3 m_moveRot;			// �ړ��͂̊p�x
	float m_fMovePower;				// �ړ��͂̊���

	OBJATTRIBUTE m_objAttribute;	// �I�u�W�F�N�g�̎��

	CShadow *m_pShadow;				// �e�|�C���^
	D3DXVECTOR2 m_shadowSize;		// �e�̑傫��

	bool m_bDropOut;				// ��������
	int m_nDropCnt;					// �����܂ł̃J�E���g

	bool m_bBonus;					// �{�[�i�X�擾�p���񂾔���
};
#endif