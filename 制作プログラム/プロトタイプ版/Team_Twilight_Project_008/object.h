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

class CModel;
class CShadow;

//==============================================================================
// �I�u�W�F�N�g�Ǘ��N���X
//==============================================================================
class CObject : public CScene3D
{
public:
	CObject();
	~CObject();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, D3DXVECTOR2 shadowSize, bool bSavePoint);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }

	// ��ނ̎擾�E�ݒ�
	int GetType(void) { return m_nType; }
	void SetType(int nType) { m_nType = nType; }

	void SetShadowSize(D3DXVECTOR2 shadowSize) { m_shadowSize = shadowSize; }

	CModel *GetModel(void) { return m_pModel; }

	// ���Ԓn�_�ۂ̎擾�E�ݒ�
	bool GetSavePoint(void) { return m_bSavePoint; }
	void SetSavePoint(bool bSavePoint) { m_bSavePoint = bSavePoint; }

private:
	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_rot;			// ����
	int m_nType;				// ���
	bool m_bSavePoint;			// ���Ԓn�_�ł��邩

	char *m_pFileName;			// �t�@�C�����̃|�C���^
	CModel *m_pModel;			// ���f���|�C���^
	CShadow *m_pShadow;			// �e�|�C���^

	D3DXVECTOR2 m_shadowSize;	// �e�̑傫��
};
#endif

