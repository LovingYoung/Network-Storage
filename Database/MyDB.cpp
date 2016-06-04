#include <iostream>
#include <bitset>
#include <zconf.h>
#include <cstring>
#include <sys/stat.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <fstream>
#include <fcntl.h>
#include <poll.h>
#include <errno.h>
#include <sstream>
#include <cstdlib>
#include <string>
#include <mysql/mysql.h>
#include <string>
#include <vector>
#include "MyDB.h"
using namespace std;

MyDB::MyDB()
{
	connection = mysql_init(NULL); // ��ʼ�����ݿ����ӱ���
	if(connection == NULL)
	{
		cout << "Error:" << mysql_error(connection);
		exit(1);
	}
}

MyDB::~MyDB()
{
	if(connection != NULL)  // �ر����ݿ�����
	{
		mysql_close(connection);
	}
}

bool MyDB::initDB(string host, string user, string pwd, string db_name)
{
	// ����mysql_real_connect����һ�����ݿ�����
	// �ɹ�����MYSQL*���Ӿ����ʧ�ܷ���NULL
	connection = mysql_real_connect(connection, host.c_str(),
			user.c_str(), pwd.c_str(), db_name.c_str(), 0, NULL, 0);
	mysql_set_character_set(connection, "gbk");
	if(connection == NULL)
	{
		cout << "Error:" << mysql_error(connection);
		exit(1);
	}
	return true;
}

bool MyDB::exeSQL(string sql, vector<string> &SQL_ans)
{
	// mysql_query()ִ�гɹ�����0��ʧ�ܷ��ط�0ֵ����PHP�в�һ��
//	cout << "����sql����" << sql << endl;
	if(mysql_query(connection, sql.c_str()))
	{
		cout << "Query Error:" << mysql_error(connection);
//		exit(1);
		return false;
	}
	else
	{
		result = mysql_store_result(connection); // ��ȡ�����
		// mysql_field_count()����connection��ѯ������
		for(int i=0; i < mysql_field_count(connection); ++i)
		{
			// ��ȡ��һ��
			row = mysql_fetch_row(result);
			if (row == NULL)
				break;
			if(row <= 0)
			{
				break;
			}
			// mysql_num_fields()���ؽ�����е��ֶ���
			for(int j=0; j < mysql_num_fields(result); ++j)
			{
//				cout << row[j] << " ";
				SQL_ans.push_back(row[j]);
			}
//			cout << endl;
		}
		// �ͷŽ�������ڴ�
		mysql_free_result(result);
	}
	return true;
}

bool MyDB::exeSQL_SELECT(string sql, vector<string> &SQL_ans)
{
	// mysql_query()ִ�гɹ�����0��ʧ�ܷ��ط�0ֵ����PHP�в�һ��
//	cout << "����sql����" << sql << endl;
	if(mysql_query(connection, sql.c_str()))
	{
		cout << "Query Error:" << mysql_error(connection);
//		exit(1);
		return false;
	}
	else
	{
		result = mysql_store_result(connection); // ��ȡ�����
		// mysql_field_count()����connection��ѯ������
		int fieldcount = mysql_num_fields(result);
//		cout << "fieldcount is " << fieldcount << endl;
		while (row = mysql_fetch_row(result))
		{
			// mysql_num_fields()���ؽ�����е��ֶ���
			for(int j=0; j < fieldcount; ++j)
			{
				if (row[j] != NULL)
				{
//					cout << row[j] << " ";
					SQL_ans.push_back(row[j]);
				}
				else 
				{
//					cout << "NULL" << " ";
					SQL_ans.push_back("NULL");
				}
			}
//			cout << endl;
		}
		// �ͷŽ�������ڴ�
		mysql_free_result(result);
	}
	return true;
}
