//=============================================================================
//
// �����_�����O���� [renderer.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

// �����_�����O�N���X
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRenderer *Create(HWND hWnd, BOOL bWindow);					// ��������
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

	void SetBSColor(D3DXCOLOR col);								// �匳�̔w�i�F�̐ݒ�

private:
	void DrawFPS(void);

	LPDIRECT3D9 m_pD3D = NULL;					// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice = NULL;		// Direct3D�f�o�C�X�ւ̃|�C���^
	LPD3DXFONT m_pFont = NULL;					// �t�H���g�ւ̃|�C���^

	D3DXCOLOR m_colBackScreen;			// �w�i�̃J���[
};

#endif