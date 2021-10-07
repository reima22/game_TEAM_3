//===================================================================
//HeaderFile: ResourceManager.h
//Author : Yo jitaku
//===================================================================
#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_
#include "main.h"
//#include "Sound.h"
#define KEY_NUM_MAX 10
#define MODEL_PARTS_MAX 10

//*******************************************************************
//����錾
//*******************************************************************
class CRenderer;
//*******************************************************************
//Sound��Data�N���X
//*******************************************************************
//class CSoundData
//{
//public:
//	CSoundData() : m_pSourceVoice(nullptr), m_pDataAudio(nullptr), m_SizeAudio(NULL) {};
//	IXAudio2SourceVoice* m_pSourceVoice;
//	BYTE* m_pDataAudio;
//	DWORD m_SizeAudio;
//};

//*******************************************************************
//Model��Data�N���X
//*******************************************************************
class CModelData
{
public:
	CModelData() :
		Xfile_Mesh(nullptr),
		Xfile_Materials(nullptr),
		Xfile_MaterialNum(0),
		m_nPartIndex(0),
		m_nPartParent(0),
		m_sName(""),
		m_nPartPos(D3DXVECTOR3(0, 0, 0)),
		m_nPartRot(D3DXVECTOR3(0, 0, 0)) {}

	LPD3DXMESH Xfile_Mesh;						//mesh
	LPD3DXBUFFER Xfile_Materials;				//�ގ�buffer
	DWORD Xfile_MaterialNum;					//�ގ�num
	LPDIRECT3DTEXTURE9 g_Textures[10] = {};		//UV�摜

												//MODEL_PLUS
	int m_nPartIndex;							//�p�[�c�̔ԍ�
	int m_nPartParent;							//�e�p�[�c�̔ԍ�
	char m_sName[128];							//�p�[�c�̖��O
	D3DXVECTOR3 m_nPartPos;						//�p�[�c�̑��΍��W
	D3DXVECTOR3 m_nPartRot;						//�p�[�c�̑��Ίp�x
	D3DXMATRIX m_MtxWorldParts;					//�p�[�c�̐��E�}�g���b�N�X
};

//*******************************************************************
//Motion��Data�N���X
//*******************************************************************
class CMotionData
{
public:
	typedef struct
	{
		//�ʒu
		float fPosX;
		float fPosY;
		float fPosZ;
		//����
		float fRotX;
		float fRotY;
		float fRotZ;
	}KEY;								//�L�[�̍\����

	typedef struct
	{
		int nFrameSpeed;				//motion���x
		KEY akey[MODEL_PARTS_MAX];		//�p�[�c��
	}KEY_INFO;							//�L�[�t���[��

	bool m_bLoop;						//Motion�z�Đ�
	int m_nNumKey;						//�L�[�t���[���̔ԍ�
	int m_nMaxKey;						//�L�[�t���[���̑���
	KEY_INFO m_aKeyInfo[KEY_NUM_MAX];	//�L�[����ۑ����Ă���z��
};

//*******************************************************************
//ModelPlus��Data�N���X (Motion����model)
//*******************************************************************
class CModelDataPlus
{
public:
	CModelDataPlus() :
		m_nParts(0) {}
	CModelData m_PartsData;							//�p�[�c�̃��[�h���
	CMotionData m_MotionData;						//�p�[�c�̃��[�V�������
	int m_nParts;									//�p�[�c�̑���
	unordered_map<int, CModelData> m_Parts_Map;		//�p�[�c�̃��[�h����ۑ����Ă���map
	unordered_map<string, CMotionData> m_Motion_Map;//�p�[�c�̃��[�V��������ۑ����Ă���map
};

//*******************************************************************
//ResourceManager�N���X�̐錾
//*******************************************************************
class CResourceManager
{
public:
	static CResourceManager* GetInstance()			//singleton�C���^�t�F�[�X
	{
		static CResourceManager Instance;
		return &Instance;
	}
	HRESULT Init();									//������
	HRESULT Uninit();								//���
	HRESULT TextureLoader(string filename);			//Texture���O���t�@�C������ǂݍ��Ə������̊֐�
	//HRESULT SoundLoader(string filename);			//Sound���O���t�@�C������ǂݍ��Ə������̊֐�
	HRESULT ModelLoader(string filename);			//3DModel���O���t�@�C������ǂݍ��Ə������̊֐�
	HRESULT ModelLoaderPlus(string filename);		//�K�w�L��XFile�̓ǂݍ��������̊֐�

													//�����������ϐ���pointer��ۑ�����Map�R���e�i
	unordered_map<string, LPDIRECT3DTEXTURE9> m_Texture_Map;//�摜��ۑ����Ă���map
	//unordered_map<string, CSoundData*> m_Sound_Map;			//������ۑ����Ă���map
	unordered_map<string, CModelData*> m_Model_Map;			//���[�h��ۑ����Ă���map
	unordered_map<string, CModelDataPlus*> m_PartsModel_Map;//���[�V���������[�h��ۑ����Ă���map
private:
	CResourceManager() {};
	~CResourceManager() {};

	CRenderer* m_pRender;
	LPDIRECT3DDEVICE9 m_pDevice;

	//�����蔻��{�b�N�X�����
	//Sound�����������Ɋւ���֐�
	//HRESULT CheckSoundChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	//HRESULT ReadSoundChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
};
#endif#pragma once
