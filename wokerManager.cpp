#pragma once
#include<ios>
#include"wokerManager.h"
#include"worker.h"
#include"employee.h"
#include"boss.h"
#include"manager.h"
using namespace std;
//ְ�������ʼ�����캯��
WokerManager::WokerManager(){
    //1.�ļ�������
    ifstream ifs;
    ifs.open(FILENAME, ios::in);//���ļ�
    if (!ifs.is_open()) {
        cout << "                   �ļ������� " << endl;
        //��ʼ������
        //��ʼ����¼��
        this->m_EmpNum = 0;
        //��ʼ������ָ��
        this->m_EmpArray = NULL;
        //��ʼ���ļ�Ϊ��
        this->m_FilesIsEmpty = true;
        ifs.close();
        return;
    }
    //2.�ļ����ڵ�����Ϊ��
    char ch;
    ifs >> ch;//��һ���ַ�
    if (ifs.eof()) {//����ַ���β����־
        //�ļ�Ϊ��
        cout << "                   �ļ�Ϊ��" << endl;
        //��ʼ������
        //��ʼ����¼��
        this->m_EmpNum = 0;
        //��ʼ������ָ��
        this->m_EmpArray = NULL;
        //��ʼ���ļ�Ϊ��
        this->m_FilesIsEmpty = true;
        ifs.close();
        return;
    }
    //3.�ļ�����,���Ҽ�¼����
    int num = this->get_EmpNum();
    //cout << "ְ������Ϊ��" << num << endl;
    this->m_EmpNum = num;

    //���ٿռ�
    this->m_EmpArray = new worker*[this->m_EmpNum];
    //���ļ��е����ݣ��浽������
    this->init_Emp();
    ////���Դ���
    //for (int i = 0; i < this->m_EmpNum; i++) {
    //    cout << this->m_EmpArray[i]->m_Id << " " << this->m_EmpArray[i]->m_Name << " " << this->m_EmpArray[i]->m_DeptId << endl;
    //}
    
    
}
//��д��������
WokerManager::~WokerManager() {
    if (this->m_EmpArray != NULL) {
        for (int i = 0; i < this->m_EmpNum; i++) {
            if (this->m_EmpArray != NULL) {
                delete this->m_EmpArray[i];
            }
        }
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}
//ְ������ɾ��ְ��
void WokerManager::Del_emp() {
    if (this->m_FilesIsEmpty) {
        cout << "�ļ������ڻ��¼Ϊ��" << endl;
        return;
    }
    cout <<endl<< "                     ������ɾ��ְ�����";
    int id;
    cin >> id;
    int index = IsExist(id);
    if (index == -1) {
        cout <<endl<< "                     ɾ��ְ��������" << endl;
    }
    else {
        for (int i = index; i < this->m_EmpNum; i++) {
            this->m_EmpArray[i-1] = this->m_EmpArray[i];
        }
        this->m_EmpNum--;
        this->save();//���浽�ļ�
        cout <<endl<< "                     ɾ���ɹ�!" << endl;
    }
    cin.get();
    cin.get();

}
//ʵ���޸�ְ������
void WokerManager::Mod_Emp() {
    if (this->m_FilesIsEmpty) {
        cout << endl << "                     �ļ������ڻ��¼Ϊ�գ�" << endl;
    }
    else {
        cout <<endl<< "                     �������޸�ְ�����";
        int id;
        cin >> id;
        int index = this->IsExist(id);//�鿴ְ���Ƿ����
        if (index == -1) {
            cout << endl << "                     �޸�ְ��������" << endl;
        }
        else {
            cout << "                     ��ѡ���޸�ְ��������Ϣ��1.��� 2.���� 3.��λ"<< endl;
            int choice;
            cout << "                     ";
            cin >> choice;
            switch (choice)
            {
            case 1: {
                int ID;
                cout << "                     �������µı�ţ�";
                cin >> ID;
                this->m_EmpArray[index]->m_Id = ID;
                break;
            }
            case 2: {
                string Name;
                cout << "                     �������µ�������";
                cin >> Name;
                this->m_EmpArray[index]->m_Name = Name;
                break;
            }
            case 3: {
                int DID;
                cout <<endl<< "                     �������µĸ�λ��ţ�1.��ͨԱ�� 2.����Ա 3.�ܲ�   :" << endl;
                cin >> DID;
                this->m_EmpArray[index]->m_DeptId = DID;
                break;
            }
            default:
                cout << "���������޸�ʧ��" << endl;
                cin.get();
                cin.get();
                return;
            }
        }
        cout << "                     �޸ĳɹ���" << endl;
        this->save();
    }
    cin.get();
    cin.get();
}
//ְ������ʵ��ְ���Ƿ�����жϺ���
int WokerManager::IsExist(int id) {
    int index = -1;
    for (int i = 0; i < this->m_EmpNum; i++) {
        if (this->m_EmpArray[i]->m_Id == id) {
            index = i;
            break;
        }
    }
    return index;
}
//ְ��������ʾԱ��
void WokerManager::Show_emp() {
    if (this->m_FilesIsEmpty) {
        cout << "                     �ļ������ڻ��ļ�Ϊ��" << endl;
    }
    else {
        for (int i = 0; i < this->m_EmpNum; i++) {
            //���ö�̬������ʾ�Ľӿ�
            this->m_EmpArray[i]->showInfo();
        }
    }
    cin.get();
    cin.get();
    system("cls");
}

//ְ�������ʼ��Ա��
void WokerManager::init_Emp() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int id;
    string name;
    int dId;
    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> dId) {
        worker* woker = NULL;
        //���ݲ�ͬ���Ŵ�������
        if (dId == 1) {//1��ͨԱ��
            woker = new Employee(id, name, dId);
        }
        else if (dId == 2) {//2����
            woker = new Manager(id, name, dId);
        }
        else {//3�ܲ�
            woker = new Boss(id, name, dId);
        }
        //����������
        this->m_EmpArray[index++] = woker;
        this->m_EmpNum = index;
    }
}
//ְ������ʵ��ͳ���ļ��е�����
int WokerManager::get_EmpNum() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);//���ļ�
    int id;
    string name;
    int dId;
    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> dId) {
        num++;//ͳ����������
    }
    return num;
}
//ְ������ʵ���˳�����
void WokerManager::exitSystem() {
	cout << "                       ��ӭ�´�ʹ��" << endl;
	exit(0);
}
//ְ������ʵ�ִ�ӡ�˵�����
void WokerManager::MenuPrint() {
	printf("************************* ְ������ϵͳ ***********************************\n");
	printf("                         1.����ְ����Ϣ\n");
	printf("                         2.��ʾְ����Ϣ\n");
	printf("                         3.�޸�ְ����Ϣ\n");
	printf("                         4.����ְ����Ϣ\n");
	printf("                         5.ɾ��ְ����Ϣ\n");
	printf("                         6.���ձ������\n");
	printf("                         7.���ְ����Ϣ\n");
	printf("                         8.�˳�ϵͳ\n");
	printf("************************* ************** ***********************************\n\n");
}
//ְ������ʵ�����ְ������
void WokerManager::Add_Emp() {
    cout <<endl<< "                   ���������ְ��������" ;
    int addNum = 0;
    cin >> addNum;
    if (addNum > 0) {
        int newSize = m_EmpNum + addNum; // ��������
        // �����¿ռ�
        worker** newSpace = new worker * [newSize];
        // ��ԭ���ռ��µ����ݣ��������¿ռ���
        if (m_EmpNum != NULL) {
            for (int i = 0; i < m_EmpNum; i++) {
                newSpace[i] = m_EmpArray[i];
            }
        }
        // �������������
        for (int i = 0; i < addNum; i++) {
            int id;
            string name;
            cout <<endl<<"                   �������" << i + 1 << "����ְ����ţ�" ;
            cin >> id;
            cout <<endl<< "                   �������" << i + 1 << "����ְ��������" ;
            cin >> name;
            
            cout <<endl<< "                    <��λ>" << endl;
            cout << "                   1.��ͨԱ��" << endl;
            cout << "                   2.����" << endl;
            cout << "                   3.�ϰ�" << endl;
            int dselect; // ����ѡ��
            cout << endl << "                   ��ѡ��ְ����λ��";
            cin >> dselect;
            worker* worker =NULL;
            switch (dselect) {
            case 1: {
                worker = new Employee(id, name, dselect);
                break;
            }
            case 2: {
                worker = new Manager(id, name, dselect);
                break;
            }
            case 3: {
                worker = new Boss(id, name, dselect);
                break; // ���ȱʧ��break���
            }
            default:
                cout << "�������� ���ʧ��!";
                cin.get(); cin.get();
                return;
            }
            newSpace[m_EmpNum + i] = worker;
        }
        // �ͷ�ԭ���Ŀռ�
        delete[] this->m_EmpArray;
        // �����¿ռ�ָ��
       this->m_EmpArray = newSpace;
        // �����µ�ְ������
        m_EmpNum = newSize;
        // �ɹ�����ӵ��ļ�
        this->save();
        // ��ʾ�ɹ�
        this->m_FilesIsEmpty = false;//����ְ����Ϊ��
        cout << "                           �ɹ����" << addNum << "����Ա��" << endl;
    }
    else {
        cout << "                           ������������" << endl;
    }
    //��������������ص��ϼ�Ŀ¼
    cin.get();
    cin.get();
    system("cls");
}
//����Ա��
void WokerManager::Find_Emp() {
    if (this->m_FilesIsEmpty) {
        cout << "                         �ļ������ڻ��߼�¼Ϊ�գ�" << endl;
    }
    else {
        cout << "                         1.����Ų���" << endl;
        cout << "                         2.����������" << endl;
        cout << "                         ��������ҷ�ʽ��";
        int select;
        cin >> select;

        if (select == 1) {//���ձ�Ų���
            cout << "                         ��������ұ�ţ�";
            int Id;
            cin >> Id;
            int index = this->IsExist(Id);
            if (index == -1)
                cout << "                         ���ұ�Ų�����" << endl;
            else {
                cout << "                         ���ҳɹ�����ְ����Ϣ���£�"; this->m_EmpArray[index]->showInfo();
            }
        }
        else if(select==2){//������������
            string name;
            cout << "                         ���������������";
            cin >> name;
            bool flag = false;//���ҳɹ���־
            for (int i = 0; i < this->m_EmpNum; i++) {
                if (this->m_EmpArray[i]->m_Name == name) {
                    cout << "                         ���ҳɹ�ְ����Ϣ���£�"; this->m_EmpArray[i]->showInfo();
                    flag = true;
                }
            }
            if (!flag) {
                cout << "                         ����ʧ�ܣ�Ա��������" << endl;
            }
        }
        else {
            cout << "                         ��������" << endl;
            cin.get();
            return;
        }
    }
    cin.get();
    cin.get();
}
//����
void WokerManager::Sort_Emp() {
    if (this->m_FilesIsEmpty) {
        cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
    }
    else {
        cout << "1.��ְ������������" << endl;
        cout << "2.��ְ���Ž�������" << endl;
        cout << "��ѡ������ʽ��";
        int select;
        cin >> select;
        //ð������
        if (select == 1) {//����ð������
            for (int i = 0; i < this->m_EmpNum - 1; i++) {
                for (int j = 0; j < this->m_EmpNum - i - 1; j++) {
                    if (this->m_EmpArray[j]->m_Id > this->m_EmpArray[j + 1]->m_Id) {
                        swap(this->m_EmpArray[j], this->m_EmpArray[j + 1]);
                    }
                }
            }
        }
        else if (select == 2) {//����ð������
            for (int i = 0; i < this->m_EmpNum - 1; i++) {
                for (int j = 0; j < this->m_EmpNum - i - 1; j++) {
                    if (this->m_EmpArray[j]->m_Id < this->m_EmpArray[j + 1]->m_Id) {
                        swap(this->m_EmpArray[j], this->m_EmpArray[j + 1]);
                    }
                }
            }
        }
        else {
            cout << "ѡ������" << endl;
            cin.get();
            return;
        }
    }
    cout << "����ɹ�" << endl;
    cin.get();
    cin.get();
}
//����ļ�
void WokerManager::Clean_File() {
    cout << "ȷ�����?" << endl;
    cout << "1.ȷ��" << endl;
    cout << "2.����" << endl;
    int select;
    cin >> select;
    if (select == 1) {
        //��ģʽ ios::trunc �������ɾ���ļ������´���
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();

        //���ά����ָ��
        if (this->m_EmpArray != NULL) {
            for (int i = 0; i < this->m_EmpNum; i++) {
                if (this->m_EmpArray != NULL) {
                    delete this->m_EmpArray[i];
                }
            }
            this->m_EmpNum = 0;
            delete[] this->m_EmpArray;
            cout << "��ճɹ���" << endl;
            cin.get();
        }
    }
    else {
        return;
    }
}
//ְ������ʵ�ֱ����ļ�
void WokerManager::save() {
    ofstream ofs;
    ofs.open(FILENAME, ios::out);//д�ķ�ʽ���ļ�
    //����forѭ��������д���ļ�
    for (int i = 0; i < this->m_EmpNum; i++) {
        ofs << this->m_EmpArray[i]->m_Id << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptId << endl;
    }
    ofs.close();//�ر��ļ�
}