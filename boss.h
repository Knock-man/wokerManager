#pragma once
#include<iostream>
#include<string>
#include"worker.h"
using namespace std;
//�ϰ�������
class Boss :public worker {
public:
	//���캯��
	Boss(int id, string name, int did);
	//��ʾ��λ��Ϣ
	void showInfo();
	//��ȡ��λ����
	string getDeptName();
};