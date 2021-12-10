//=============================================================================
//
// �v���C���[�N���X [player.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "player.h"
#include "Manager.h"
#include "Model.h"
#include "Input.h"

//*****************************************************************************
// �v���C���[�N���X (�h�����F�I�u�W�F�N�g�N���X�j
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// ��������ݒ�
	SetPos(pos);
	SetRot(rot);
	SetSize(VECTOR3_ZERO);

	// �e���f���̐e���f���C���f�b�N�X��ݒ�
	m_nIndexParent[0] = -1;
	m_nIndexParent[1] = 0;
	m_nIndexParent[2] = 0;
	m_nIndexParent[3] = 2;
	m_nIndexParent[4] = 0;
	m_nIndexParent[5] = 4;
	m_nIndexParent[6] = 0;
	m_nIndexParent[7] = 6;
	m_nIndexParent[8] = 0;
	m_nIndexParent[9] = 8;

	// �e���f���̈ʒu�I�t�Z�b�g��ݒ�
	m_aOffset[0][0] = 0.0f;	// pos x
	m_aOffset[0][1] = 15.0f;	//     y
	m_aOffset[0][2] = 0.0f;	//     z
	m_aOffset[0][3] = 0.0f;	// rot x
	m_aOffset[0][4] = 0.0f;	//     y
	m_aOffset[0][5] = 0.0f;	//     z

	m_aOffset[1][0] = 0.0f;	// pos x
	m_aOffset[1][1] = 15.0f;	//     y
	m_aOffset[1][2] = 0.0f;	//     z
	m_aOffset[1][3] = 0.0f;	// rot x
	m_aOffset[1][4] = 0.0f;	// rot y
	m_aOffset[1][5] = 0.0f;	// rot z

	m_aOffset[2][0] = -7.5f;	// pos x
	m_aOffset[2][1] = 12.0f;	//     y
	m_aOffset[2][2] = 0.0f;	//     z
	m_aOffset[2][3] = 0.0f;	// rot x
	m_aOffset[2][4] = 0.0f;	// rot y
	m_aOffset[2][5] = 0.0f;	// rot z

	m_aOffset[3][0] = -10.0f;	// pos x
	m_aOffset[3][1] = 0.0f;	//     y
	m_aOffset[3][2] = 0.0f;	//     z
	m_aOffset[3][3] = 0.0f;	// rot x
	m_aOffset[3][4] = 0.0f;	// rot y
	m_aOffset[3][5] = 0.0f;	// rot z

	m_aOffset[4][0] = 7.5f;	// pos x
	m_aOffset[4][1] = 12.0f;	//     y
	m_aOffset[4][2] = 0.0f;	//     z
	m_aOffset[4][3] = 0.0f;	// rot x
	m_aOffset[4][4] = 0.0f;	// rot y
	m_aOffset[4][5] = 0.0f;	// rot z

	m_aOffset[5][0] = 10.0f;	// pos x
	m_aOffset[5][1] = 0.0f;	//     y
	m_aOffset[5][2] = 0.0f;	//     z
	m_aOffset[5][3] = 0.0f;	// rot x
	m_aOffset[5][4] = 0.0f;	// rot y
	m_aOffset[5][5] = 0.0f;	// rot z

	m_aOffset[6][0] = -4.0f;	// pos x
	m_aOffset[6][1] = 0.0f;	//     y
	m_aOffset[6][2] = 0.0f;	//     z
	m_aOffset[6][3] = 0.0f;	// rot x
	m_aOffset[6][4] = 0.0f;	// rot y
	m_aOffset[6][5] = 0.0f;	// rot z

	m_aOffset[7][0] = 0.0f;	// pos x
	m_aOffset[7][1] = -10.0f;	//     y
	m_aOffset[7][2] = 0.0f;	//     z
	m_aOffset[7][3] = 0.0f;	// rot x
	m_aOffset[7][4] = 0.0f;	// rot y
	m_aOffset[7][5] = 0.0f;	// rot z

	m_aOffset[8][0] = 4.0f;	// pos x
	m_aOffset[8][1] = 0.0f;	//     y
	m_aOffset[8][2] = 0.0f;	//     z
	m_aOffset[8][3] = 0.0f;	// rot x
	m_aOffset[8][4] = 0.0f;	// rot y
	m_aOffset[8][5] = 0.0f;	// rot z

	m_aOffset[9][0] = 0.0f;	// pos x
	m_aOffset[9][1] = -10.0f;	//     y
	m_aOffset[9][2] = 0.0f;	//     z
	m_aOffset[9][3] = 0.0f;	// rot x
	m_aOffset[9][4] = 0.0f;	// rot y
	m_aOffset[9][5] = 0.0f;	// rot z

	// ���f���̃t�@�C���p�X��ݒ�
	strcpy(&m_aFilePath[0][0], "Data/Model/Robot/00_robot_body.x");
	strcpy(&m_aFilePath[1][0], "Data/Model/Robot/01_robot_head.x");
	strcpy(&m_aFilePath[2][0], "Data/Model/Robot/02_robot_armR.x");
	strcpy(&m_aFilePath[3][0], "Data/Model/Robot/03_robot_handR.x");
	strcpy(&m_aFilePath[4][0], "Data/Model/Robot/04_robot_armL.x");
	strcpy(&m_aFilePath[5][0], "Data/Model/Robot/05_robot_handL.x");
	strcpy(&m_aFilePath[6][0], "Data/Model/Robot/06_robot_legR.x");
	strcpy(&m_aFilePath[7][0], "Data/Model/Robot/07_robot_footR.x");
	strcpy(&m_aFilePath[8][0], "Data/Model/Robot/08_robot_legL.x");
	strcpy(&m_aFilePath[9][0], "Data/Model/Robot/09_robot_footL.x");

	// �e���f���̐���
	for (int nCntParts = 0; nCntParts < PLAYER_MODEL_COUNT; nCntParts++) {
		D3DXVECTOR3 posOff;
		posOff.x = m_aOffset[nCntParts][0];
		posOff.y = m_aOffset[nCntParts][1];
		posOff.z = m_aOffset[nCntParts][2];

		D3DXVECTOR3 rotOff;
		rotOff.x = m_aOffset[nCntParts][3];
		rotOff.y = m_aOffset[nCntParts][4];
		rotOff.z = m_aOffset[nCntParts][5];

		m_apModel[nCntParts] = CModel::Create(posOff, rotOff, &m_aFilePath[nCntParts][0]);
		if (m_nIndexParent[nCntParts] < 0) {
			m_apModel[nCntParts]->SetParent(NULL);
		}
		else {
			m_apModel[nCntParts]->SetParent(m_apModel[m_nIndexParent[nCntParts]]);
		}
		
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	// ���f���̔j��
	for (auto pModel : m_apModel) {
		pModel->Uninit();
		pModel = NULL;
	}

	// �C���X�^���X�j��
	this->Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
#ifdef _DEBUG

	// �ړ��A��]�m�F�p
	CInputKeyboard *pKey = CManager::GetInputKeyboard();
	D3DXVECTOR3 rot = GetRot();
	if (pKey->GetPress(DIK_Q)) {
		rot.y -= 0.05f;
	}
	else if (pKey->GetPress(DIK_E)) {
		rot.y += 0.05f;
	}
	SetRot(rot);

	D3DXVECTOR3 pos = GetPos();
	if (pKey->GetPress(DIK_UP)) {
		pos.z++;
	}
	else if (pKey->GetPress(DIK_DOWN)) {
		pos.z--;
	}
	if (pKey->GetPress(DIK_LEFT)) {
		pos.x--;
	}
	else if (pKey->GetPress(DIK_RIGHT)) {
		pos.x++;
	}
	SetPos(pos);
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// Device
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			// ���݂̃}�e���A���ۑ��p

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXVECTOR3 rot = GetRot();
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXVECTOR3 pos = GetPos();
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A����ۑ�
	pDevice->GetMaterial(&matDef);

	// �p�[�c���f���̃}�g���b�N�X�ݒ�ƕ`��
	for (int nCntParts = 0; nCntParts < PLAYER_MODEL_COUNT; nCntParts++) {
		m_apModel[nCntParts]->Draw();
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �����֐�
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	if (pPlayer != NULL)
	{
		pPlayer->Init(pos, rot, VECTOR3_ZERO);
	}

	return pPlayer;
}