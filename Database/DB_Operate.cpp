#include "DB_Operate.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include<mysql/mysql.h> 
using namespace std;

void DB_Operate::Debug_Out(string s)
{
	cout << s << endl;
}
DB_Operate::DB_Operate()
{
	db.initDB("localhost", "root", "root123", "driver"); 
}

void DB_Operate::Insert_User_Log(string Userid, string Time, string Status)
{
	vector<string> SQL_ans;
	string DB_Command;
	Debug_Out("������һ���û���¼��¼");
	DB_Command = "INSERT INTO log(userid, time, status) VALUES(" + Userid + ", \"" + Time + "\", " + Status + ")";
	Debug_Out(DB_Command);
	SQL_ans.clear(); 
	if (db.exeSQL(DB_Command, SQL_ans) == true)
	{
		Debug_Out("����һ���û���¼��¼�ɹ�");
	}
	return;
}

bool DB_Operate::Show_User()
{
	Debug_Out("Show_User");
	int i, j;
	vector<string> SQL_ans;
	SQL_ans.clear();
	db.exeSQL_SELECT("select * from user order by id", SQL_ans);
	for (i = 0; i < SQL_ans.size(); i += 3)
	{
		Debug_Out(SQL_ans[i]+" "+SQL_ans[i+1]+" "+SQL_ans[i+2]);
	}
}
bool DB_Operate::Show_Log()
{
	Debug_Out("Show_Log");
	int i, j;
	vector<string> SQL_ans;
	SQL_ans.clear();
	db.exeSQL_SELECT("select * from log order by logid", SQL_ans);
	for (i = 0; i < SQL_ans.size(); i += 4)
	{
		Debug_Out(SQL_ans[i]+" "+SQL_ans[i+1]+" "+SQL_ans[i+2]+" "+SQL_ans[i+3]);
	}
}
bool DB_Operate::Show_File()
{
	int i, j;
	vector<string> SQL_ans;
	SQL_ans.clear();
	db.exeSQL_SELECT("select * from file order by userid, virtualpath", SQL_ans);
	for (i = 0; i < SQL_ans.size(); i += 3)
	{
		Debug_Out(SQL_ans[i]+" "+SQL_ans[i+1]+" "+SQL_ans[i+2]);
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
//		cout << "your directory is illegal" << endl;
		Debug_Out("your directory is illegal");
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
//	cout << "���Username�Ƿ����" << endl;
	Debug_Out("���Username�Ƿ����");
	
	DB_Command = "SELECT * FROM user WHERE username = \"" + Username + "\"";
//	cout << DB_Command << endl;
	Debug_Out(DB_Command);
	SQL_ans.clear();
	db.exeSQL_SELECT(DB_Command, SQL_ans);
	if (SQL_ans.size() > 0)
	{	
//		cout << "��username�Ѿ�����" << endl;
		Debug_Out("��username�Ѿ�����");
		return false;
	}
//	cout << "���Ӹ��û������ݿ⵱��" << endl;
	Debug_Out("���Ӹ��û������ݿ⵱��");
	DB_Command = "INSERT INTO user(username, password) VALUES(\"" + Username + "\", \"" + Password + "\")";
//	cout << DB_Command << endl;
	Debug_Out(DB_Command);
	SQL_ans.clear(); 
	if (db.exeSQL(DB_Command, SQL_ans) == true)
	{
//		cout << "����û���Ϣ�ɹ�" << endl;
		Debug_Out("����û���Ϣ�ɹ�");
		return true;
	}
	else
	{
//		cout << "����û���Ϣʧ��" << endl;
		Debug_Out("����û���Ϣʧ��");
		return false;
	}
}

//��ѯһ���û����˺������Ƿ���ȷ
//�����ȷ�򷵻ظ��û�����Ӧid�����򷵻�-1
int DB_Operate::Check_User(string Username, string Password)
{
	time_t now_time;
	now_time = time(NULL);
    	char tmp[64]; 
    	strftime( tmp, sizeof(tmp), "%Y/%m/%d %X",localtime(&now_time) ); 
    	string time;
    	time = tmp;
	cout << time << endl;
	int ans;
	stringstream ss;
	vector<string> SQL_ans;
	string DB_Command;
//	cout << "������ݿ�����û�и�Username��Password" << endl;
	Debug_Out("������ݿ�����û�и�Username��Password");
	DB_Command = "SELECT id FROM user WHERE username = \"" + Username + "\" AND password = \"" + Password + "\""; 
//	cout << DB_Command << endl;
	Debug_Out(DB_Command);
	SQL_ans.clear();
	db.exeSQL_SELECT(DB_Command, SQL_ans);
//	cout << "�õ����û���id" << endl;
	Debug_Out("�õ����û���id");
	if (SQL_ans.size() == 0)
	{
//		cout << -1 << endl;
		DB_Command = "SELECT id FROM user WHERE username = \"" + Username + "\""; 
//		cout << DB_Command << endl;
		Debug_Out(DB_Command);
		SQL_ans.clear();
		db.exeSQL_SELECT(DB_Command, SQL_ans);
		if (SQL_ans.size() != 0)
		{
			Insert_User_Log(SQL_ans[0], time, "0");
		}
		return -1;
	}
	else
	{
//		cout << SQL_ans[0] << endl;
		Insert_User_Log(SQL_ans[0], time, "1");
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
//	cout << "��ѯ���ļ��б�" << endl;
	Debug_Out("��ѯ���ļ��б�");
	ss << Virtual_Path.size();
	ss >> len;
//	cout << len << endl;
//	cout << Virtual_Path << endl;
	if (Virtual_Path[Virtual_Path.size()-1] != '/')
		return ans;
	DB_Command = "SELECT virtualpath FROM file WHERE userid = " + User_Id + " AND left(virtualpath, " + len + ") = \"" + Virtual_Path + "\"";
	cout << DB_Command << endl;
	Debug_Out(DB_Command);
	SQL_ans.clear();
	db.exeSQL_SELECT(DB_Command, SQL_ans);
	ans = Find_File_List(SQL_ans, Virtual_Path);
//	cout << "�õ��ļ�Ŀ¼" << endl;
	Debug_Out("�õ��ļ�Ŀ¼");
	for (int i = 0; i < ans.size(); i ++)
//		cout << ans[i] << endl;
		Debug_Out(ans[i]);
	return ans;
}

//��ѯMD5��״̬������MD5��Ϣ����ѯ����Ӧ�ļ���״̬�����С������ϴ���û�У���û�и�MD5�򷵻�-1 
int DB_Operate::Query_Md5_Statu(string Md5)
{
	vector<string> SQL_ans;
	int ans;
	stringstream ss;
	Debug_Out("��ѯMD5��״̬");
//	cout << "��ѯMD5��״̬" << endl;
	string DB_Command;
	DB_Command = "SELECT status FROM status WHERE md5 = \"" + Md5 + "\"";
//	cout << DB_Command << endl;
	Debug_Out(DB_Command);
	SQL_ans.clear();
	db.exeSQL_SELECT(DB_Command, SQL_ans);
//	cout << "��MD5��״̬Ϊ��" << endl;
	Debug_Out("��MD5��״̬Ϊ��");
	if (SQL_ans.size() == 0)
	{
//		cout << -1 << endl;
		Debug_Out("-1");
		return -1;
	}
	else 
	{
//		cout << SQL_ans[0] << endl;
		Debug_Out(SQL_ans[0]);
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
	Debug_Out("�޸�MD5��״̬");
	string DB_Command;
	DB_Command = "UPDATE status SET status = " + statu + " WHERE md5 = \"" + Md5 + "\"";
	Debug_Out(DB_Command);
	SQL_ans.clear();
	if (db.exeSQL(DB_Command, SQL_ans) == true)
	{
		Debug_Out("�޸�״̬�ɹ�");
		return true;
	}
	else
	{
		Debug_Out("�޸�״̬ʧ��");
		return false; 
	}
} 

//���MD5��״̬������MD5��Ϣ����Ҫ��ӵ�״̬������һ��MD5��״̬��Ϣ
//��ӳɹ��򷵻�true�������ڸ�MD5����ʧ���򷵻�false���Ѿ����ڸ�MD5�� 
bool DB_Operate::Insert_Md5_Statu(string Md5, string statu = NULL)
{
	Debug_Out("���MD5��״̬");
	string DB_Command;
	vector<string> SQL_ans;
	DB_Command = "INSERT INTO status(md5, status) VALUES(\"" + Md5 + "\", " + statu + ")"; 
	Debug_Out(DB_Command);
	SQL_ans.clear();
	if (db.exeSQL(DB_Command, SQL_ans) == true)
	{
		Debug_Out("���״̬�ɹ�");
		return true;
	}
	else 
	{
		Debug_Out("���״̬ʧ��");
		return false;
	}
}

//��ѯ�ļ���MD5�ţ������û�uid���ļ�����·��������ļ�MD5�ţ���������򷵻�NULL 
string DB_Operate::Query_Md5(string User_Id, string Virtual_Path)
{
	vector<string> SQL_ans;
	Debug_Out("��ѯ�ļ���MD5��");
	string DB_Command;
	DB_Command = "SELECT md5 FROM file WHERE userid = " + User_Id + " AND virtualpath = \"" + Virtual_Path + "\"";
	Debug_Out(DB_Command);
	SQL_ans.clear();
	db.exeSQL_SELECT(DB_Command, SQL_ans);
	if (SQL_ans.size() > 0)
	{
		Debug_Out("���ļ���MD��Ϊ��");
		Debug_Out(SQL_ans[0]);
		return SQL_ans[0];
	}
	else
	{
		Debug_Out("��ѯ�ļ�MD��ʧ�ܣ�����NULL");
		Debug_Out("NULL");
		return "NULL";
	}
}

//�����ļ��������û�uid���ļ�����·����MD5, �����ݿ��в���һ����¼
//�ɹ�����true��ʧ�ܷ���false 
bool DB_Operate::Insert_File_Info(string User_Id, string Virtual_Path, string Md5 = "NULL")
{
	Debug_Out("����һ���ļ���¼");
	string DB_Command;
	vector<string> ans;
	if (Md5 == "NULL")	
		DB_Command = "INSERT INTO file(userid, virtualpath, md5) VALUES(" + User_Id + ", \"" + Virtual_Path + "\", " + Md5 + ")";
	else DB_Command = "INSERT INTO file(userid, virtualpath, md5) VALUES(" + User_Id + ", \"" + Virtual_Path + "\", \"" + Md5 + "\")";
	Debug_Out(DB_Command);
	ans.clear();
	if (db.exeSQL(DB_Command, ans) == false)
	{
		Debug_Out("�����ļ���¼ʧ��");
		return false;
	}
	else 
	{
		Debug_Out("�����ļ���¼�ɹ�");
		return true;
	}
}

//ɾ���ļ�/�ļ��У������û�uid���ļ�����·���������ݿ���ɾ��һ��/һϵ�м�¼
//�ļ�/�ļ��������ݿ��в����ڣ��򷵻�false,����ɾ����¼��������true
bool DB_Operate::Delete_File_Info(string User_Id, string Virtual_Path)
{
	Debug_Out("ɾ���ļ�/�ļ���");
	string DB_Command, len;
	stringstream ss;
	vector<string> SQL_ans;
	ss << Virtual_Path.size();
	ss >> len;
	if (Virtual_Path[Virtual_Path.size()-1] == '/')
		DB_Command = "DELETE FROM file WHERE userid = " + User_Id + " AND left(virtualpath, " + len + ") = \"" + Virtual_Path + "\"";
	else DB_Command = "DELETE FROM file WHERE userid = " + User_Id + " AND virtualpath = \"" + Virtual_Path + "\"";
	Debug_Out(DB_Command);
	SQL_ans.clear();
	if (db.exeSQL(DB_Command, SQL_ans) == true)
	{
		Debug_Out("ɾ���ļ����ļ��гɹ�");
		return true;
	}
	else
	{
		Debug_Out("ɾ���ļ����ļ���ʧ��");
		return false;
	}
} 

//�����ļ��л��ļ��������û�uid��Դ�ļ�·����Ŀ���ļ�·��������һϵ�м�¼		
//����ļ����ڣ�����Ϊfilename(i)
//�������ʧ�ܣ��򷵻�false
//������Ƴɹ����򷵻�true
//һ���ļ����²���ͬʱ����filename��filename/
bool DB_Operate::Copy_File_Info(string User_Id, string Virtual_Path, string Aim_Path)
{
	Debug_Out("�����ļ�/�ļ���");
	stringstream ss;
	string DB_Command, len;
	int i, j;
	int virtual_path_len = Virtual_Path.size();
	int aim_path_len = Aim_Path.size();
	vector<string> SQL_ans;
	vector<File_Info> Copy_File_Info;
	ss.clear();
	ss.str("");
	ss << Virtual_Path.size();
	ss >> len;
	if (Virtual_Path[Virtual_Path.size()-1] == '/')
		DB_Command = "SELECT * FROM file WHERE userid = " + User_Id + " AND left(virtualpath, " + len + ") = \"" + Virtual_Path + "\"";
	else DB_Command = "SELECT * FROM file WHERE userid = " + User_Id + " AND virtualpath = \"" + Virtual_Path + "\"";
	Debug_Out(DB_Command);
	SQL_ans.clear();
	if (db.exeSQL_SELECT(DB_Command, SQL_ans) == false)
		return false;
	if (SQL_ans.size() == 0)
	{
		Debug_Out("���ļ�/�ļ��в�����");
		return false;
	}
	Copy_File_Info.clear();
	for (i = 0; i < SQL_ans.size(); i += 3)
	{
		Debug_Out(SQL_ans[i] + " " + SQL_ans[i+1] + " " + SQL_ans[i+2]);
		Copy_File_Info.push_back(File_Info(SQL_ans[i], SQL_ans[i+1], SQL_ans[i+2]));
	}
	for (i = 0; i < Copy_File_Info.size(); i ++)
	{
		Copy_File_Info[i].Virtual_Path.replace(0, virtual_path_len, Aim_Path);	
	}
	if (Copy_File_Info[0].Md5 != "NULL")
		DB_Command = "INSERT INTO file(userid, virtualpath, md5) Values(" + Copy_File_Info[0].User_Id + ", \"" + Copy_File_Info[0].Virtual_Path + "\", \"" + Copy_File_Info[0].Md5 + "\")";
	else
		DB_Command = "INSERT INTO file(userid, virtualpath, md5) Values(" + Copy_File_Info[0].User_Id + ", \"" + Copy_File_Info[0].Virtual_Path + "\", " + Copy_File_Info[0].Md5 + ")";
	for (i = 1; i < Copy_File_Info.size(); i ++)
	{
		if (Copy_File_Info[i].Md5 != "NULL")
			DB_Command += ",(" + Copy_File_Info[i].User_Id + ", \"" + Copy_File_Info[i].Virtual_Path + "\", \"" + Copy_File_Info[i].Md5 + "\")";
		else
			DB_Command += ",(" + Copy_File_Info[i].User_Id + ", \"" + Copy_File_Info[i].Virtual_Path + "\", " + Copy_File_Info[i].Md5 + ")";
	}
	DB_Command += ";";
	Debug_Out(DB_Command);
	SQL_ans.clear();
	if (db.exeSQL(DB_Command, SQL_ans) == false)
		return false;
	return true;
}

//�����ļ�/�ļ������ƣ������û�uid���ļ�����·�����޸ĺ���ļ�/�ļ���·���������ݿ����޸�һ��/һϵ�м�¼
//��Ҫ��֤�޸ĺ���ļ���/�ļ�����������
bool DB_Operate::Update_File_Info(string User_Id, string Virtual_Path, string Aim_Path)
{
	if (Virtual_Path.size() <= 1)
		return false;
	Debug_Out("�������ļ�/�ļ���");
	stringstream ss;
	string DB_Command, len;
	int i, j;
	int virtual_path_len = Virtual_Path.size();
	int aim_path_len = Aim_Path.size();
	vector<string> SQL_ans;
	vector<File_Info> Copy_File_Info;
	ss.clear();
	ss.str("");
	ss << Virtual_Path.size();
	ss >> len;
	if (Virtual_Path[Virtual_Path.size()-1] == '/')
		DB_Command = "SELECT * FROM file WHERE userid = " + User_Id + " AND left(virtualpath, " + len + ") = \"" + Virtual_Path + "\"";
	else DB_Command = "SELECT * FROM file WHERE userid = " + User_Id + " AND virtualpath = \"" + Virtual_Path + "\"";
	Debug_Out(DB_Command);
	SQL_ans.clear();
	if (db.exeSQL_SELECT(DB_Command, SQL_ans) == false)
		return false;
	if (SQL_ans.size() == 0)
	{
		Debug_Out("���ļ�/�ļ��в�����");
		return false;
	}
	Copy_File_Info.clear();
	for (i = 0; i < SQL_ans.size(); i += 3)
	{
		Debug_Out(SQL_ans[i] + " " + SQL_ans[i+1] + " " + SQL_ans[i+2]);
		Copy_File_Info.push_back(File_Info(SQL_ans[i], SQL_ans[i+1], SQL_ans[i+2]));
	}
	for (i = 0; i < Copy_File_Info.size(); i ++)
	{
		Copy_File_Info[i].Virtual_Path.replace(0, virtual_path_len, Aim_Path);	
	}
	if (Copy_File_Info[0].Md5 != "NULL")
		DB_Command = "INSERT INTO file(userid, virtualpath, md5) Values(" + Copy_File_Info[0].User_Id + ", \"" + Copy_File_Info[0].Virtual_Path + "\", \"" + Copy_File_Info[0].Md5 + "\")";
	else
		DB_Command = "INSERT INTO file(userid, virtualpath, md5) Values(" + Copy_File_Info[0].User_Id + ", \"" + Copy_File_Info[0].Virtual_Path + "\", " + Copy_File_Info[0].Md5 + ")";
	for (i = 1; i < Copy_File_Info.size(); i ++)
	{
		if (Copy_File_Info[i].Md5 != "NULL")
			DB_Command += ",(" + Copy_File_Info[i].User_Id + ", \"" + Copy_File_Info[i].Virtual_Path + "\", \"" + Copy_File_Info[i].Md5 + "\")";
		else
			DB_Command += ",(" + Copy_File_Info[i].User_Id + ", \"" + Copy_File_Info[i].Virtual_Path + "\", " + Copy_File_Info[i].Md5 + ")";
	}
	DB_Command += ";";
	Debug_Out(DB_Command);
	SQL_ans.clear();
	if (db.exeSQL(DB_Command, SQL_ans) == false)
		return false;
//=================ɾ�����ݿ���ԭ�ļ�/�ļ��е���Ϣ==========================
	if (Virtual_Path[Virtual_Path.size()-1] == '/')
		DB_Command = "DELETE FROM file WHERE userid = " + User_Id + " AND left(virtualpath, " + len + ") = \"" + Virtual_Path + "\"";
	else DB_Command = "DELETE FROM file WHERE userid = " + User_Id + " AND virtualpath = \"" + Virtual_Path + "\"";
	Debug_Out(DB_Command);
	SQL_ans.clear();
	if (db.exeSQL(DB_Command, SQL_ans) == false)
		return false;
//=================ɾ�����ݿ���ԭ�ļ�/�ļ��е���Ϣ==========================
	return true;
}



