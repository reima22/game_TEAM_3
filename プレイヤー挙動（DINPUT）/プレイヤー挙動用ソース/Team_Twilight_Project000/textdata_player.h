//=============================================================================
//
// �e�L�X�g�f�[�^�i�v���C���[�j�Ǘ� [textdata_player.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTDATA_PLAYER_H_
#define _TEXTDATA_PLAYER_H_

#include "main.h"
#include "player.h"
#include "textdata.h"

//==============================================================================
// �e�L�X�g�Ǘ��i�v���C���[�j�N���X
//==============================================================================
class CTextDataPlayer : public CTextData
{
public:
	// �v���C���[�f�[�^�̎��
	typedef enum
	{
		PLAYERDATA_MAX
	}PLAYERDATA;

	typedef enum
	{
		INFO_POS_X = 0, // posX
		INFO_POS_Y,		// posY
		INFO_POS_Z,		// posZ
		INFO_ROT_X,		// rotX
		INFO_ROT_Y,		// rotY
		INFO_ROT_Z,		// rotZ
		INFOMAX
	}INFO;

	CTextDataPlayer();
	~CTextDataPlayer();

	// �e�L�X�g�̓ǂݍ���
	void LoadData(void);
	void Uninit(void);
	
	// �v���C���[�f�[�^�̐���
	static CTextDataPlayer *Create(void);

	// �ǂݍ��񂾒l�̎擾
	char *GetFileName(int nIdx) { return m_pFileModelName[nIdx]; }			// �t�@�C����
	int GetPartsNum(void) { return m_nNumParts; }							// �p�[�c��
	int GetIndex(int nIdx) { return m_pIdx[nIdx]; }							// �C���f�b�N�X
	int GetParent(int nIdx) { return m_pParentIdx[nIdx]; }					// �e�̃C���f�b�N�X
	float GetOffset(int nIdx, int nInfo) { return m_pOffset[nIdx][nInfo]; }	// �I�t�Z�b�g���

	// ���[�V�������
	bool GetLoop(CPlayer::MOTIONTYPE motionType) { return m_bLoop[motionType]; }
	int GetNumKey(CPlayer::MOTIONTYPE motionType) { return m_nNumKey[motionType]; }
	
	float GetKeyInfo(CPlayer::MOTIONTYPE motionType,
		int nKey, int nParts, CPlayer::KEY keyInfo) { return m_pKey[motionType][nKey][nParts][keyInfo]; }
	
	int GetFrame(CPlayer::MOTIONTYPE motionType,int nKey) { return m_pFrame[motionType][nKey]; }

private:
	int m_nNumModel;			// ���f����
	
	char **m_pFileModelName;	// X�t�@�C�����|�C���^
	char **m_aFileName;			// �t�@�C�����ϐ�

	int m_nNumParts;			// �p�[�c��

	int *m_pIdx;				// �C���f�b�N�X
	int *m_pParentIdx;			// �e�̃C���f�b�N�X
	float **m_pOffset;			// �I�t�Z�b�g���

	int m_nModelCnt;			// ���f���t�@�C�����J�E���^
	int m_nPartsCnt;			// �ǂݍ��񂾃p�[�c�̐��J�E���^

	// ���[�V�������
	int m_nNumKey[CPlayer::MOTIONTYPE_MAX];		// �L�[��
	float ***m_pKey[CPlayer::MOTIONTYPE_MAX];		// �L�[�v�f
	bool m_bLoop[CPlayer::MOTIONTYPE_MAX];		// ���[�V���������[�v���邩
	int *m_pFrame[CPlayer::MOTIONTYPE_MAX];		// ���[�V�����t���[��		
												
	int m_nKeyCnt;								// �ǂݎ��L�[���J�E���g
	int m_nMotionCnt;							// �ǂݎ�郂�[�V�����J�E���g
};

#endif
