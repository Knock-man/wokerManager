#pragma once
#include<iostream>
#include<string>
#include"worker.h"
using namespace std;
//����������
class Manager:public worker {
public:
	//���캯��
	Manager(int id, string name, int did);
	//��ʾ��λ��Ϣ
	void showInfo();
	//��ȡ��λ����
	string getDeptName();
};