#include "DB_Operate.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include<mysql/mysql.h> 
using namespace std;

DB_Operate::DB_Operate()
{
	db.initDB("localhost", "root", "root123", "driver"); 
}

bool DB_Operate::Show_User()
{
	int i, j;
	vector<string> SQL_ans;
	SQL_ans.clear();
	db.exeSQL_SELECT("select * from user", SQL_ans);
	for (i = 0; i < SQL_ans.size(); i += 3)
	{
		for (j = i; j < i+3; j ++)
			cout << SQL_ans[j] << " ";
		cout << endl;
	}
}
bool DB_Operate::Show_File()
{
	int i, j;
	vector<string> SQL_ans;
	SQL_ans.clear();
	db.exeSQL_SELECT("select * from file", SQL_ans);
	for (i = 0; i < SQL_ans.size(); i += 3)
	{
		for (j = i; j < i+3; j ++)
			cout << SQL_ans[j] << " ";
		cout << endl;
	}
}

//ɸѡ���ڵ�ǰĿ¼�µ��ļ��б�
vector<string> DB_Operate::Find_File_List(vector<string> s, string aim_s)
{
	int i, aim_len = aim_s.size(), pos, s_len;
//	cout << "aim_s_len = " << aim_len << endl;
	vector<string> ans;
	string ans_s;
	ans.clear();
	if (aim_s[aim_len-1] != '/')
	{
		cout << "your directory is illegal" << endl;
		return ans;
	}
	for (i = 0; i < s.size(); i ++)
		if (s[i].size() > aim_len)
		{
			s_len = s[i].size();
			pos = s[i].find("/", aim_len);
//			cout << s[i] << endl;
//			cout << pos << endl;
			if (pos == s[i].npos)
			{
				ans_s = s[i].substr(aim_len, s_len-aim_len);
//				cout << ans_s << endl;
				ans.push_back(ans_s);
			}
			else if (pos == s[i].size()-1)
			{
				ans_s = s[i].substr(aim_len, s_len-aim_len);
//				cout << ans_s << endl;
				ans.push_back(ans_s);
			}
		}
//	cout << ans.size() << endl;
	return ans;
};

bool DB_Operate::Show_Status()
{
	int i, j;
	vector<string> SQL_ans;
	SQL_ans.clear();
	db.exeSQL_SELECT("select * from status", SQL_ans);
	for (i = 0; i < SQL_ans.size(); i += 2)
	{
		for (j = i; j < i+2; j ++)
			cout << SQL_ans[j] << " ";
		cout << endl;
	}
}

//����һ���û������username�Ѿ������򷵻�false����������û�������true
bool DB_Operate::Insert_User(string Username, string Password)
{
	vector<string> SQL_ans;
	string DB_Command;
	cout << "���Username�Ƿ����" << endl;
	DB_Command = "SELECT * FROM user WHERE username = \"" + Username + "\"";
	cout << DB_Command << endl;
	SQL_ans.clear();
	db.exeSQL_SELECT(DB_Command, SQL_ans);
	if (SQL_ans.size() > 0)
	{	
		cout << "��username�Ѿ�����" << endl;
		return false;
	}
	cout << "���Ӹ��û������ݿ⵱��" << endl;
	DB_Command = "INSERT INTO user(username, password) VALUES(\"" + Username + "\", \"" + Password + "\")";
	cout << DB_Command << endl;
	SQL_ans.clear(); 
	if (db.exeSQL(DB_Command, SQL_ans) == true)
	{
		cout << "����û���Ϣ�ɹ�" << endl;
		return true;
	}
	else
	{
		cout << "����û���Ϣʧ��" << endl;
		return false;
	}
}

//��ѯһ���û����˺������Ƿ���ȷ
//�����ȷ�򷵻ظ��û�����Ӧid�����򷵻�-1
int DB_Operate::Check_User(string Username, string Password)
{
	int ans;
	stringstream ss;
	vector<string> SQL_ans;
	string DB_Command;
	cout << "������ݿ�����û�и�Username��Password" << endl;
	DB_Command = "SELECT id FROM user WHERE username = \"" + Username + "\" AND password = \"" + Password + "\""; 
	cout << DB_Command << endl;
	SQL_ans.clear();
	db.exeSQL_SELECT(DB_Command, SQL_ans);
	cout << "�õ����û���id" << endl;
	if (SQL_ans.size() == 0)
	{
//		cout << -1 << endl;
		return -1;
	}
	else
	{
//		cout << SQL_ans[0] << endl;
		ss << SQL_ans[0];
		ss >> ans;
		return ans;
	}
}

//��ѯ�ļ��б������û�uid����ǰ·������ȡ��ǰ·�����ļ��б�
vector<string> DB_Operate::Query_File_List(string User_Id, string Virtual_Path)
{
	vector<string> ans;
	vector<string> SQL_ans;
	string len;
	string DB_Command;
	stringstream ss;
	cout << "��ѯ���ļ��б�" << endl;
	ss << Virtual_Path.size();
	ss >> len;
//	cout << len << endl;
//	cout << Virtual_Path << endl;
	if (Virtual_Path[Virtual_Path.size()-1] != '/')
		return ans;
	DB_Command = "SELECT virtualpath FROM file WHERE userid = " + User_Id + " AND left(virtualpath, " + len + ") = \"" + Virtual_Path + "\"";
	cout << DB_Command << endl;
	SQL_ans.clear();
	db.exeSQL_SELECT(DB_Command, SQL_ans);
	ans = Find_File_List(SQL_ans, Virtual_Path);
	cout << "�õ��ļ�Ŀ¼" << endl;
	for (int i = 0; i < ans.size(); i ++)
		cout << ans[i] << endl;
	return ans;
}

//��ѯMD5��״̬������MD5��Ϣ����ѯ����Ӧ�ļ���״̬�����С������ϴ���û�У���û�и�MD5�򷵻�-1 
int DB_Operate::Query_Md5_Statu(string Md5)
{
	vector<string> SQL_ans;
	int ans;
	stringstream ss;
	cout << "��ѯMD5��״̬" << endl;
	string DB_Command;
	DB_Command = "SELECT status FROM status WHERE md5 = \"" + Md5 + "\"";
	cout << DB_Command << endl;
	SQL_ans.clear();
	db.exeSQL_SELECT(DB_Command, SQL_ans);
	cout << "��MD5��״̬Ϊ��" << endl;
	if (SQL_ans.size() == 0)
	{
		cout << -1 << endl;
		return -1;
	}
	else 
	{
		cout << SQL_ans[0] << endl;
		ss << SQL_ans[0];
		ss >> ans;
		return ans;
	}
}

//�޸�MD5��״̬������MD5��Ϣ����Ҫ���ĵ�״̬���޸����ݿ�����ӦMD5��״̬
//�޸ĳɹ��򷵻�true���Ѿ����ڸ�MD5����ʧ���򷵻�false�������ڸ�MD5�� 
bool DB_Operate::Update_Md5_Statu(string Md5, string statu)
{
	vector<string> SQL_ans;
	cout << "�޸�MD5��״̬" << endl;
	string DB_Command;
	DB_Command = "UPDATE status SET status = " + statu + " WHERE md5 = \"" + Md5 + "\"";
	cout << DB_Command << endl;
	SQL_ans.clear();
	if (db.exeSQL(DB_Command, SQL_ans) == true)
	{
		cout << "�޸�״̬�ɹ�" << endl;
		return true;
	}
	else
	{
		cout << "�޸�״̬ʧ��" << endl;
		return false; 
	}
} 

//���MD5��״̬������MD5��Ϣ����Ҫ��ӵ�״̬������һ��MD5��״̬��Ϣ
//��ӳɹ��򷵻�true�������ڸ�MD5����ʧ���򷵻�false���Ѿ����ڸ�MD5�� 
bool DB_Operate::Insert_Md5_Statu(string Md5, string statu = NULL)
{
	cout << "���MD5��״̬" << endl;
	string DB_Command;
	vector<string> SQL_ans;
	DB_Command = "INSERT INTO status(md5, status) VALUES(\"" + Md5 + "\", " + statu + ")"; 
	cout << DB_Command << endl;
	SQL_ans.clear();
	if (db.exeSQL(DB_Command, SQL_ans) == true)
	{
		cout << "���״̬�ɹ�" << endl;
		return true;
	}
	else 
	{
		cout << "���״̬ʧ��" << endl;
		return false;
	}
}

//��ѯ�ļ���MD5�ţ������û�uid���ļ�����·��������ļ�MD5�ţ���������򷵻�NULL 
string DB_Operate::Query_Md5(string User_Id, string Virtual_Path)
{
	vector<string> SQL_ans;
	cout << "��ѯ�ļ���MD5��" << endl;
	string DB_Command;
	DB_Command = "SELECT md5 FROM file WHERE userid = " + User_Id + " AND virtualpath = \"" + Virtual_Path + "\"";
	cout << DB_Command << endl;
	SQL_ans.clear();
	db.exeSQL_SELECT(DB_Command, SQL_ans);
	if (SQL_ans.size() > 0)
	{
		cout << "���ļ���MD��Ϊ��" << endl;
		cout << SQL_ans[0] << endl;
		return SQL_ans[0];
	}
	else
	{
		cout << "��ѯ�ļ�MD��ʧ�ܣ�����NULL" << endl;
		cout << "NULL" << endl;
		return "NULL";
	}
}

//�����ļ��������û�uid���ļ�����·����MD5, �����ݿ��в���һ����¼
//�ɹ�����true��ʧ�ܷ���false 
bool DB_Operate::Insert_File_Info(string User_Id, string Virtual_Path, string Md5 = "NULL")
{
	cout << "����һ���ļ���¼" << endl;
	string DB_Command;
	vector<string> ans;
	if (Md5 == "NULL")	
		DB_Command = "INSERT INTO file(userid, virtualpath, md5) VALUES(" + User_Id + ", \"" + Virtual_Path + "\", " + Md5 + ")";
	else DB_Command = "INSERT INTO file(userid, virtualpath, md5) VALUES(" + User_Id + ", \"" + Virtual_Path + "\", \"" + Md5 + "\")";
	cout << DB_Command << endl;
	ans.clear();
	if (db.exeSQL(DB_Command, ans) == false)
	{
		cout << "�����ļ���¼ʧ��" << endl;
		return false;
	}
	else 
	{
		cout << "�����ļ���¼�ɹ�" << endl;
		return true;
	}
}

//ɾ���ļ�/�ļ��У������û�uid���ļ�����·���������ݿ���ɾ��һ��/һϵ�м�¼
//�ļ�/�ļ��������ݿ��в����ڣ��򷵻�false,����ɾ����¼��������true
bool DB_Operate::Delete_File_Info(string User_Id, string Virtual_Path)
{
	cout << "ɾ���ļ�/�ļ���" << endl;
	string DB_Command, len;
	stringstream ss;
	vector<string> SQL_ans;
	ss << Virtual_Path.size();
	ss >> len;
	if (Virtual_Path[Virtual_Path.size()-1] == '/')
		DB_Command = "DELETE FROM file WHERE userid = " + User_Id + " AND left(virtualpath, " + len + ") = \"" + Virtual_Path + "\"";
	else DB_Command = "DELETE FROM file WHERE userid = " + User_Id + " AND virtualpath = \"" + Virtual_Path + "\"";
	cout << DB_Command << endl;
	SQL_ans.clear();
	if (db.exeSQL(DB_Command, SQL_ans) == true)
	{
		cout << "ɾ���ļ����ļ��гɹ�" << endl;
		return true;
	}
	else
	{
		cout << "ɾ���ļ����ļ���ʧ��" << endl;
		return false;
	}
} 
