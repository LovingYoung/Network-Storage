#ifndef __DBOperate_H__
#define __DBOperate_H__
#include "DB_Info.h"
#include "MyDB.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class DB_Operate
{
	public:
		//�����������־����debug
		void Debug_Out(string s);
		//�������ݿ� 
		DB_Operate();
		//����һ���û���¼��¼
		void Insert_User_Log(string Userid, string Time, string Status);
		//������ݿ��е�User��
		bool Show_User();
		//����û���¼��¼��Log
		bool Show_Log();
		//������ݿ��е�File��
		bool Show_File();
		//ɸѡ����ǰĿ¼�µ��ļ��б�
		vector<string> Find_File_List(vector<string> s, string aim_s);
		//������ݿ��е�Status��
		bool Show_Status();
		//����һ���û������username�Ѿ������򷵻�false����������û�������true
		bool Insert_User(string Username, string Password);
		//��ѯһ���û����˺������Ƿ���ȷ
		//�����ȷ�򷵻ظ��û�����Ӧid�����򷵻�-1
		int Check_User(string Username, string Password);
		//��ѯ�ļ��б������û�uid����ǰ·������ȡ��ǰ·�����ļ��б�
		vector<string> Query_File_List(string User_Id, string Virtual_Path);
		//��ѯMD5��״̬������MD5��Ϣ����ѯ����Ӧ�ļ���״̬�����С������ϴ���û�У���û�и�MD5�򷵻�-1 
		int Query_Md5_Statu(string Md5); 
		//�޸�MD5��״̬������MD5��Ϣ����Ҫ���ĵ�״̬���޸����ݿ�����ӦMD5��״̬
		//�޸ĳɹ��򷵻�true���Ѿ����ڸ�MD5����ʧ���򷵻�false�������ڸ�MD5�� 
		bool Update_Md5_Statu(string Md5, string statu); 
		//���MD5��״̬������MD5��Ϣ����Ҫ��ӵ�״̬������һ��MD5��״̬��Ϣ
		//��ӳɹ��򷵻�true�������ڸ�MD5����ʧ���򷵻�false���Ѿ����ڸ�MD5�� 
		bool Insert_Md5_Statu(string Md5, string statu);
		//��ѯ�ļ���MD5�ţ������û�uid���ļ�����·��������ļ�MD5�ţ���������򷵻�NULL 
		string Query_Md5(string User_Id, string Virtual_Path); 
		//�����ļ��������û�uid���ļ�����·����MD5, �����ݿ��в���һ����¼
		//�ɹ�����true��ʧ�ܷ���false 
		bool Insert_File_Info(string User_Id, string Virtual_Path, string Md5);
		//ɾ���ļ�/�ļ��У������û�uid���ļ�����·���������ݿ���ɾ��һ��/һϵ�м�¼
		//�ļ�/�ļ��������ݿ��в����ڣ��򷵻�false,����ɾ����¼��������true
		bool Delete_File_Info(string User_Id, string Virtual_Path); 
		//�����ļ�/�ļ������ƣ������û�uid���ļ�����·�����޸ĺ���ļ�/�ļ����������ݿ����޸�һ��/һϵ�м�¼
		//����޸ĺ���ļ���/�ļ������Ѿ����ڣ����������ʧ�ܣ�����false
		//����޸ĺ���ļ���/�ļ����������ڡ���������ĳɹ�������true
		bool Update_File_Info(string User_Id, string Virtual_Path, string Aim_Path); 
		//�����ļ��л��ļ��������û�uid��Դ�ļ�·����Ŀ���ļ�·��������һϵ�м�¼		
		//����ļ����ڣ�����Ϊfilename(i)
		//�������ʧ�ܣ��򷵻�false
		//������Ƴɹ����򷵻�true
		bool Copy_File_Info(string User_Id, string Virtual_Path, string Aim_Path);
	private:
		MyDB db;
};
#endif
