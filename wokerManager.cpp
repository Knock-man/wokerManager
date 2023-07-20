#pragma once
#include<ios>
#include"wokerManager.h"
#include"worker.h"
#include"employee.h"
#include"boss.h"
#include"manager.h"
using namespace std;
//职工管理初始化构造函数
WokerManager::WokerManager(){
    //1.文件不存在
    ifstream ifs;
    ifs.open(FILENAME, ios::in);//读文件
    if (!ifs.is_open()) {
        cout << "                   文件不存在 " << endl;
        //初始化属性
        //初始化记录数
        this->m_EmpNum = 0;
        //初始化数组指针
        this->m_EmpArray = NULL;
        //初始化文件为空
        this->m_FilesIsEmpty = true;
        ifs.close();
        return;
    }
    //2.文件存在但数据为空
    char ch;
    ifs >> ch;//读一个字符
    if (ifs.eof()) {//这个字符是尾部标志
        //文件为空
        cout << "                   文件为空" << endl;
        //初始化属性
        //初始化记录数
        this->m_EmpNum = 0;
        //初始化数组指针
        this->m_EmpArray = NULL;
        //初始化文件为空
        this->m_FilesIsEmpty = true;
        ifs.close();
        return;
    }
    //3.文件存在,并且记录数据
    int num = this->get_EmpNum();
    //cout << "职工人数为：" << num << endl;
    this->m_EmpNum = num;

    //开辟空间
    this->m_EmpArray = new worker*[this->m_EmpNum];
    //讲文件中的数据，存到数组中
    this->init_Emp();
    ////测试代码
    //for (int i = 0; i < this->m_EmpNum; i++) {
    //    cout << this->m_EmpArray[i]->m_Id << " " << this->m_EmpArray[i]->m_Name << " " << this->m_EmpArray[i]->m_DeptId << endl;
    //}
    
    
}
//重写析构函数
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
//职工管理删除职工
void WokerManager::Del_emp() {
    if (this->m_FilesIsEmpty) {
        cout << "文件不存在或记录为空" << endl;
        return;
    }
    cout <<endl<< "                     请输入删除职工编号";
    int id;
    cin >> id;
    int index = IsExist(id);
    if (index == -1) {
        cout <<endl<< "                     删除职工不存在" << endl;
    }
    else {
        for (int i = index; i < this->m_EmpNum; i++) {
            this->m_EmpArray[i-1] = this->m_EmpArray[i];
        }
        this->m_EmpNum--;
        this->save();//保存到文件
        cout <<endl<< "                     删除成功!" << endl;
    }
    cin.get();
    cin.get();

}
//实现修改职工函数
void WokerManager::Mod_Emp() {
    if (this->m_FilesIsEmpty) {
        cout << endl << "                     文件不存在或记录为空！" << endl;
    }
    else {
        cout <<endl<< "                     请输入修改职工编号";
        int id;
        cin >> id;
        int index = this->IsExist(id);//查看职工是否存在
        if (index == -1) {
            cout << endl << "                     修改职工不存在" << endl;
        }
        else {
            cout << "                     请选择修改职工哪项信息：1.编号 2.姓名 3.岗位"<< endl;
            int choice;
            cout << "                     ";
            cin >> choice;
            switch (choice)
            {
            case 1: {
                int ID;
                cout << "                     请输入新的编号：";
                cin >> ID;
                this->m_EmpArray[index]->m_Id = ID;
                break;
            }
            case 2: {
                string Name;
                cout << "                     请输入新的姓名：";
                cin >> Name;
                this->m_EmpArray[index]->m_Name = Name;
                break;
            }
            case 3: {
                int DID;
                cout <<endl<< "                     请输入新的岗位编号：1.普通员工 2.管理员 3.总裁   :" << endl;
                cin >> DID;
                this->m_EmpArray[index]->m_DeptId = DID;
                break;
            }
            default:
                cout << "输入有误修改失败" << endl;
                cin.get();
                cin.get();
                return;
            }
        }
        cout << "                     修改成功！" << endl;
        this->save();
    }
    cin.get();
    cin.get();
}
//职工管理实现职工是否存在判断函数
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
//职工管理显示员工
void WokerManager::Show_emp() {
    if (this->m_FilesIsEmpty) {
        cout << "                     文件不存在或文件为空" << endl;
    }
    else {
        for (int i = 0; i < this->m_EmpNum; i++) {
            //利用多态调用显示的接口
            this->m_EmpArray[i]->showInfo();
        }
    }
    cin.get();
    cin.get();
    system("cls");
}

//职工管理初始化员工
void WokerManager::init_Emp() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int id;
    string name;
    int dId;
    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> dId) {
        worker* woker = NULL;
        //根据不同部门创建对象
        if (dId == 1) {//1普通员工
            woker = new Employee(id, name, dId);
        }
        else if (dId == 2) {//2经理
            woker = new Manager(id, name, dId);
        }
        else {//3总裁
            woker = new Boss(id, name, dId);
        }
        //存入数组中
        this->m_EmpArray[index++] = woker;
        this->m_EmpNum = index;
    }
}
//职工管理实现统计文件中的人数
int WokerManager::get_EmpNum() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);//打开文件
    int id;
    string name;
    int dId;
    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> dId) {
        num++;//统计人数变量
    }
    return num;
}
//职工管理实现退出方法
void WokerManager::exitSystem() {
	cout << "                       欢迎下次使用" << endl;
	exit(0);
}
//职工管理实现打印菜单方法
void WokerManager::MenuPrint() {
	printf("************************* 职工管理系统 ***********************************\n");
	printf("                         1.增加职工信息\n");
	printf("                         2.显示职工信息\n");
	printf("                         3.修改职工信息\n");
	printf("                         4.查找职工信息\n");
	printf("                         5.删除职工信息\n");
	printf("                         6.按照编号排序\n");
	printf("                         7.清空职工信息\n");
	printf("                         8.退出系统\n");
	printf("************************* ************** ***********************************\n\n");
}
//职工管理实现添加职工方法
void WokerManager::Add_Emp() {
    cout <<endl<< "                   请输入添加职工数量：" ;
    int addNum = 0;
    cin >> addNum;
    if (addNum > 0) {
        int newSize = m_EmpNum + addNum; // 更新人数
        // 开辟新空间
        worker** newSpace = new worker * [newSize];
        // 将原来空间下的数据，拷贝到新空间下
        if (m_EmpNum != NULL) {
            for (int i = 0; i < m_EmpNum; i++) {
                newSpace[i] = m_EmpArray[i];
            }
        }
        // 批量添加新数据
        for (int i = 0; i < addNum; i++) {
            int id;
            string name;
            cout <<endl<<"                   请输入第" << i + 1 << "个新职工编号：" ;
            cin >> id;
            cout <<endl<< "                   请输入第" << i + 1 << "个新职工姓名：" ;
            cin >> name;
            
            cout <<endl<< "                    <岗位>" << endl;
            cout << "                   1.普通员工" << endl;
            cout << "                   2.经理" << endl;
            cout << "                   3.老板" << endl;
            int dselect; // 部门选择
            cout << endl << "                   请选择职工岗位：";
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
                break; // 添加缺失的break语句
            }
            default:
                cout << "输入有误 添加失败!";
                cin.get(); cin.get();
                return;
            }
            newSpace[m_EmpNum + i] = worker;
        }
        // 释放原来的空间
        delete[] this->m_EmpArray;
        // 更新新空间指向
       this->m_EmpArray = newSpace;
        // 更新新的职工人数
        m_EmpNum = newSize;
        // 成功后添加到文件
        this->save();
        // 提示成功
        this->m_FilesIsEmpty = false;//更新职工不为空
        cout << "                           成功添加" << addNum << "名新员工" << endl;
    }
    else {
        cout << "                           输入数据有误！" << endl;
    }
    //按任意键清屏，回到上级目录
    cin.get();
    cin.get();
    system("cls");
}
//查找员工
void WokerManager::Find_Emp() {
    if (this->m_FilesIsEmpty) {
        cout << "                         文件不存在或者记录为空！" << endl;
    }
    else {
        cout << "                         1.按编号查找" << endl;
        cout << "                         2.按姓名查找" << endl;
        cout << "                         请输入查找方式：";
        int select;
        cin >> select;

        if (select == 1) {//按照编号查找
            cout << "                         请输入查找编号：";
            int Id;
            cin >> Id;
            int index = this->IsExist(Id);
            if (index == -1)
                cout << "                         查找编号不存在" << endl;
            else {
                cout << "                         查找成功！该职工信息如下："; this->m_EmpArray[index]->showInfo();
            }
        }
        else if(select==2){//按照姓名查找
            string name;
            cout << "                         请输入查找姓名：";
            cin >> name;
            bool flag = false;//查找成功标志
            for (int i = 0; i < this->m_EmpNum; i++) {
                if (this->m_EmpArray[i]->m_Name == name) {
                    cout << "                         查找成功职工信息如下："; this->m_EmpArray[i]->showInfo();
                    flag = true;
                }
            }
            if (!flag) {
                cout << "                         查找失败，员工不存在" << endl;
            }
        }
        else {
            cout << "                         输入有误" << endl;
            cin.get();
            return;
        }
    }
    cin.get();
    cin.get();
}
//排序
void WokerManager::Sort_Emp() {
    if (this->m_FilesIsEmpty) {
        cout << "文件不存在或者记录为空" << endl;
    }
    else {
        cout << "1.按职工号升序排序" << endl;
        cout << "2.按职工号降序排序" << endl;
        cout << "请选择排序方式：";
        int select;
        cin >> select;
        //冒泡排序
        if (select == 1) {//升序冒泡排序
            for (int i = 0; i < this->m_EmpNum - 1; i++) {
                for (int j = 0; j < this->m_EmpNum - i - 1; j++) {
                    if (this->m_EmpArray[j]->m_Id > this->m_EmpArray[j + 1]->m_Id) {
                        swap(this->m_EmpArray[j], this->m_EmpArray[j + 1]);
                    }
                }
            }
        }
        else if (select == 2) {//降序冒泡排序
            for (int i = 0; i < this->m_EmpNum - 1; i++) {
                for (int j = 0; j < this->m_EmpNum - i - 1; j++) {
                    if (this->m_EmpArray[j]->m_Id < this->m_EmpArray[j + 1]->m_Id) {
                        swap(this->m_EmpArray[j], this->m_EmpArray[j + 1]);
                    }
                }
            }
        }
        else {
            cout << "选择有误" << endl;
            cin.get();
            return;
        }
    }
    cout << "排序成功" << endl;
    cin.get();
    cin.get();
}
//清空文件
void WokerManager::Clean_File() {
    cout << "确认清空?" << endl;
    cout << "1.确认" << endl;
    cout << "2.返回" << endl;
    int select;
    cin >> select;
    if (select == 1) {
        //打开模式 ios::trunc 如果存在删除文件并重新创建
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();

        //清空维护的指针
        if (this->m_EmpArray != NULL) {
            for (int i = 0; i < this->m_EmpNum; i++) {
                if (this->m_EmpArray != NULL) {
                    delete this->m_EmpArray[i];
                }
            }
            this->m_EmpNum = 0;
            delete[] this->m_EmpArray;
            cout << "清空成功！" << endl;
            cin.get();
        }
    }
    else {
        return;
    }
}
//职工管理实现保存文件
void WokerManager::save() {
    ofstream ofs;
    ofs.open(FILENAME, ios::out);//写的方式打开文件
    //利用for循环将数据写入文件
    for (int i = 0; i < this->m_EmpNum; i++) {
        ofs << this->m_EmpArray[i]->m_Id << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptId << endl;
    }
    ofs.close();//关闭文件
}