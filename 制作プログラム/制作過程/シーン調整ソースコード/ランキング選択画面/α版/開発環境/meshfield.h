//==============================================================================
//
// ���b�V���t�B�[���h�̕`��kmeshfield.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
#include "main.h"
#include "scene.h"

// �}�N����`
#define MESH_CHANGE	(1.0f)
#define MESH_CHANGE_MINI	(0.5f)

// ���b�V���t�B�[���h�N���X
class CMeshfield : public CScene
{
public:
	CMeshfield();
	~CMeshfield();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMeshfield *Create(int nIdx);

	// �@���̌v�Z
	void CalcuNormal(void);

	// �g�`
	void MeshWave(void);

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }

	// �ʒu�̎擾�E�ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetPostion(D3DXVECTOR3 pos) { m_pos = pos; }

	// �p�x�̎擾�E�ݒ�
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }

	// �ʂ̐��̎擾�E�ݒ�
	int GetWidthNum(void) { return m_nWidth; }
	void SetWidthNum(int nWidth) { m_nWidth = nWidth; }
	int GetDepthNum(void) { return m_nDepth; }
	void SetDepthNum(int nDepth) { m_nDepth = nDepth; }

	// �����̎擾�E�ݒ�
	float GetWidthSize(void) { return m_fWidth; }
	void SetWidthSize(float fWidth) { m_fWidth = fWidth; }
	float GetDepthSize(void) { return m_fDepth; }
	void SetDepthSize(float fDepth) { m_fDepth = fDepth; }

	// ���_���̎擾�E�ݒ�
	int GetWidthPoint(void) { return m_nWidthPoint; }
	void SetWidthPoint(int nWidthPoint) { m_nWidthPoint = nWidthPoint; }
	int GetDepthPoint(void) { return m_nDepthPoint; }
	void SetDepthPoint(int nDepthPoint) { m_nDepthPoint = nDepthPoint; }

	// �����_��
	int GetIdxPoint(void) { return m_nIdxPoint; }

	void SetIdx(int nIdx) { m_nIdx = nIdx; }			// ���b�V���C���f�b�N�X�ݒ�

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// �o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	int m_nIdx;

	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_rot;							// �p�x
	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X

	int m_nAllPoint;							// �����_��
	int m_nPolygon;								// �|���S����
	int m_nIdxPoint;							// �C���f�b�N�X�o�b�t�@�̕K�v�Ȋm�ې�

	float m_fWidth;								// �|���S���������̕�
	float m_fDepth;								// �|���S���������̉��s

	int m_nWidth;								// �����̖ʂ̐�
	int m_nDepth;								// ���s�̖ʂ̐�

	int m_nWidthPoint;							// �����̒��_��
	int m_nDepthPoint;							// ���s�̒��_��

	float m_fWidthMax;							// �����̍ő�T�C�Y
	float m_fDepthMax;							// ���s�̍ő�T�C�Y

	int m_nNor;									// �@�������߂�|���S����
	D3DXVECTOR3 *m_pNor;						// �@���̒l
	int m_nIdxNor;								// ���삷��C���f�b�N�X

	int m_nCntWave;								// �g�`�����̃J�E���g
};

#endif
