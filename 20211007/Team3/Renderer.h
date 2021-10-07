//===================================================================
//HeaderFile: Renderer.h
//Author : Yo jitaku
//===================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"
#include "d3dx9.h"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")//D3DXCreateTextureFromFile

//*******************************************************************
//����錾
//*******************************************************************
class CSceneManager;
//*******************************************************************
//�����_�����O�X�N���[���̃N���X
//*******************************************************************
class CRenderer
{
public:
	static CRenderer* GetInstance() //singleton�C���^�t�F�[�X
	{
		static CRenderer Instance;
		return &Instance;
	}
	HRESULT Init(HWND hWnd, bool bWindow);		//������
	HRESULT Uninit();							//���
	void Draw();								//�`��
	LPDIRECT3DDEVICE9 GetDevice() {
		return m_pD3DDevice;
	}											//�f�o�C�X�����
private:
	CRenderer() {};
	~CRenderer() {};

	LPDIRECT3D9				  m_pD3D;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		  m_pD3DDevice;		// Device�I�u�W�F�N�g(�`��ɕK�v)											
	LPD3DXFONT				  m_pFont;			// �t�H���g�ւ̃|�C���^
	CSceneManager*			  m_pSceneManager;	// �V�[���}�l�[�W���[�̃|�C���^
#ifdef _DEBUG
	void DrawDebugInfo();						// debug���[�h
#endif
};
#endif