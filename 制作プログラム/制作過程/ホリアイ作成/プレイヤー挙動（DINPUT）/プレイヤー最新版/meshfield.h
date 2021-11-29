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

// ���b�V���t�B�[���h�N���X
class CMeshField : public CScene
{
public:
	CMeshField();
	~CMeshField();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMeshField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nWidth, int nDepth, float fWidth, float fDepth);

	// �l�̐ݒ�
	void SetPostion(D3DXVECTOR3 pos) { m_pos = pos; }		// �ʒu
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }		// �p�x
	void SetWidthNum(int nWidth) { m_nWidth = nWidth; }		// ���̖ʂ̐�
	void SetDepthNum(int nDepth) { m_nDepth = nDepth; }		// ���s�̖ʂ̐�
	void SetWidthSize(float fWidth) { m_fWidth = fWidth; }	// 1��������̕�
	void SetDepthSize(float fDepth) { m_fDepth = fDepth; }	// 1��������̉��s

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// �o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
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
};

#endif
