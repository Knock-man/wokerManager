#pragma once
#include<iostream>
#include"worker.h"
#include<fstream>//�ļ�����
const string FILENAME = "empFile.txt";
using namespace std;
//ְ��������(��ӡ�˵����˳�����)
class WokerManager {
public:
	WokerManager();
	~WokerManager();
	void MenuPrint();//��ӡ�˵�����
	void exitSystem();//�˳�����
	void Add_Emp();//���Ա������
	void save();//�����ļ�����
	int get_EmpNum();//ͳ���ļ��е�����
	void init_Emp();//��ʼ��Ա��
	void Show_emp();//��ʾְ��
	void Del_emp();//ɾ��ְ��
	int IsExist(int id);//�ж�ְ���Ƿ����
	void Mod_Emp();//�޸�ְ��
	void Find_Emp();//����
	void Sort_Emp();//����
	void Clean_File();//���

	int m_EmpNum;//ά��ְ����Ŀ
	worker** m_EmpArray;
	bool m_FilesIsEmpty;//�ж��ļ��Ƿ�Ϊ��
};
