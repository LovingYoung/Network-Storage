#include "DB_Operate.cpp"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	int Type_num;
	string username, password;
	string userid, virtualpath, md5;
	string statu;
//	freopen("output.txt","w",stdout);
	DB_Operate DB_OPT;
	while (1)
	{
		cout << "0.��ʾ���е��û���Ϣ" << endl;
		cout << "1.����һ���û���Ϣ" << endl;
		cout << "2.��ѯһ���û���Ϣ" << endl;
		cout << "3.��ʾ���е��ļ���Ϣ" << endl;
		cout << "4.����һ���ļ���Ϣ" << endl;
		cout << "5.��ʾ���е��ļ�״̬��Ϣ" << endl;
		cout << "6.��ѯһ���ļ���״̬" << endl;
		cout << "7.�޸�һ���ļ���״̬" << endl;
		cout << "8.���һ���ļ���״̬" << endl;
		cout << "9.��ѯһ���ļ���md5" << endl;
		cout << "10.��ѯһ��Ŀ¼�µ������ļ�" << endl;
		cout << "11.ɾ��һ���ļ�����һ���ļ���" << endl;
		cin >> Type_num;
		if (Type_num == 0)
		{
			DB_OPT.Show_User();
		}
		else if (Type_num == 1)
		{
			cout << "�������û���������" << endl;
//			cin >> username >> password;
//			cout << username << endl;
			cout << password << endl;
			DB_OPT.Insert_User(username,password); 
		}
		else if (Type_num == 2)
		{
			cout << "�������û���������" << endl;
			cin >> username >> password;
			DB_OPT.Check_User(username, password);
		}
		else if (Type_num == 3)
		{
			DB_OPT.Show_File();
		}
		else if (Type_num == 4)
		{
			cout << "�������û�id���û�����·����md5" << endl;
			cin >> userid >> virtualpath >> md5;
			DB_OPT.Insert_File_Info(userid, virtualpath, md5);
		}
		else if (Type_num == 5)
		{
			DB_OPT.Show_Status();
		}
		else if (Type_num == 6)
		{
			cout << "������md5��" << endl;
			cin >> md5;
			DB_OPT.Query_Md5_Statu(md5);
		}
		else if (Type_num == 7)
		{
			cout << "������md5�ź��ļ�״̬" << endl;
			cin >> md5 >> statu;
			DB_OPT.Update_Md5_Statu(md5, statu);
		}
		else if (Type_num == 8)
		{
			cout << "������md5�ź��ļ�״̬" << endl;
			cin >> md5 >> statu;
			DB_OPT.Insert_Md5_Statu(md5, statu);
		}
		else if (Type_num == 9)
		{
			cout << "�������û�id���û�����·��" << endl;
			cin >> userid >> virtualpath;
			DB_OPT.Query_Md5(userid, virtualpath);
		}
		else if (Type_num == 10)
		{
			cout << "�������û�id���û�����·��" << endl;
//			cout << "Query_File_List" << endl;
			cin >> userid >> virtualpath;
			DB_OPT.Query_File_List(userid, virtualpath);
		}
		else if (Type_num == 11)
		{
			cout << "�������û�id���û�����·��" << endl;
			cin >> userid >> virtualpath;
			DB_OPT.Delete_File_Info(userid, virtualpath);
		}
	}
//	DB_OPT.Check_User("123","456"); 
//	DB_OPT.Query_File_List("1", "\\a\\");
//	DB_OPT.Query_Md5_Statu("MD555555");
//	DB_OPT.Update_Md5_Statu("MD555555", "1");
//	DB_OPT.Insert_Md5_Statu("MD444444", "2");
//	DB_OPT.Query_Md5("1", "\\a");
//	DB_OPT.Insert_File_Info("1", "\\b", "MD333333");
//	DB_OPT.Delete_File_Info("1", "\\a");  
	return 0;
}
