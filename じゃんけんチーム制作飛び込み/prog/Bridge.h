#pragma once

#ifndef _BRIDGE_H_
#define _BRIDGE_H_



#include "DxLib.h"
#include"Player.h"

class Bridge
{
public:
	Bridge();
	virtual ~Bridge();

	void Draw(const VECTOR player_x);
	void Update();

private:

	// ���̃|�W�V����
	VECTOR pos;
	// �Q�[�g�̃|�W�V����
	VECTOR gPos;
	// �X�^�[�g�̃|�W�V����
	VECTOR sPos;
	VECTOR velocity;	//�ړ���	VECTOR velocity;	

	float move;	        //�ړ���
	int    bridgeModelHandle;
	int    gateModelHandle;    // �S�[���Q�[�g
	int    startModelHandle;   // �X�^�[�g�n�_
	int background;
	int backPrintx;
}; 
#endif // !_BRIDGE_H_