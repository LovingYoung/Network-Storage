#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <windows.h>
#include <sstream>
#include <map>
#include <time.h>
#include <mysql.h>

#define BUFSIZE 10240
#define SOCKET_NUM 500

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libmysql.lib")

using namespace std;

DWORD WINAPI myThread(LPVOID lpParameter);

struct Data{
    u_long pid;
    string time;
    string randStr;
};

int main(){
    //Read From file
    ifstream fin("winsock_server.cfg");
    ofstream fout("output.txt");
    string s;
    int bind_port;
    string mysql_ip;
    string mysql_user;
    string mysql_password;
    string mysql_dbname;
    string mysql_tbname1;
    string mysql_tbname2;
    string mysql_tbname3;
    string mysql_tbname4;
    while (fin >> s){
        if (s == "bind_port"){
            fin >> s;
            fin >> bind_port;
        }
        else if (s == "mysql_ip"){
            fin >> s;
            fin >> mysql_ip;
        }
        else if (s == "mysql_user"){
            fin >> s;
            fin >> mysql_user;
        }
        else if (s == "mysql_password"){
            fin >> s;
            fin >> mysql_password;
        }
        else if (s == "mysql_dbname"){
            fin >> s;
            fin >> mysql_dbname;
        }
        else if (s == "mysql_tbname1"){
            fin >> s;
            fin >> mysql_tbname1;
        }
        else if (s == "mysql_tbname2"){
            fin >> s;
            fin >> mysql_tbname2;
        }
        else if (s == "mysql_tbname3"){
            fin >> s;
            fin >> mysql_tbname3;
        }
        else if (s == "mysql_tbname4"){
            fin >> s;
            fin >> mysql_tbname4;
        }
    }
    //cout << bind_port << endl << mysql_ip << endl << mysql_user << endl << mysql_password << endl << mysql_dbname << endl << mysql_tbname1 << endl << mysql_tbname2 << endl << mysql_tbname3 << endl << mysql_tbname4 << endl;

    SOCKET soc;
    sockaddr_in server, si_other;
    int slen, recv_len;
    char buf[BUFSIZE];
    WSADATA wsa;

    slen = sizeof(si_other);

    cout << "Initialising Winsock... " << endl;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
        cout << "Failed. Error Code: " << WSAGetLastError() << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Initialised." << endl;

    if ((soc = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET){
        cout << "Could not create a soc" << endl;
        exit(0);
    }
    cout << "Socket Created" << endl;

    u_long iMode = 1;
    int iResult = ioctlsocket(soc, FIONBIO, &iMode);
    if (iResult != NO_ERROR){
        cout << "ioctlsocket failed because " << iResult;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(bind_port);

    if (bind(soc, (sockaddr *)&server, sizeof(server)) == SOCKET_ERROR){
        cout << "Bind failed with error code" << WSAGetLastError() << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Bind Done" << endl;

    map<unsigned short, Data*> datamap;
    srand(time(0));
    int finish = 0;

    FD_SET ReadSet;
    FD_SET WriteSet;

    while (true){
        FD_ZERO(&ReadSet);
        FD_SET(soc, &ReadSet);
        int recv_len;

        int total = select(soc + 1, &ReadSet, NULL, NULL, NULL);
        if (total > 0 && FD_ISSET(soc, &ReadSet)){
            if ((recv_len = recvfrom(soc, buf, BUFSIZE, 0, (sockaddr *)&si_other, &slen)) == SOCKET_ERROR){
                cout << "Recvfrom with error code " << WSAGetLastError() << endl;
                exit(EXIT_FAILURE);
            }
            if (recv_len == 4){
                Data * newData = new Data();
                u_long * getInteger = (u_long*)buf;
                *getInteger = ntohl(*getInteger);
                newData->pid = *getInteger;
                datamap[si_other.sin_port] = newData;
            }
            else if (recv_len == 19){
                buf[recv_len] = '\0';
                datamap[si_other.sin_port]->time = buf;
                while (true){
                    FD_ZERO(&WriteSet);
                    FD_SET(soc, &WriteSet);
                    total = select(soc + 1, NULL, &WriteSet, NULL, NULL);
                    if (total > 0 && FD_ISSET(soc, &WriteSet)){
                        stringstream ss("");
                        ss << "str" << rand() % 5000 + 5000;
                        if (sendto(soc, ss.str().c_str(), 7, 0, (sockaddr*)&si_other, slen) == SOCKET_ERROR){
                            cout << "Sendto() failed with error code : " << WSAGetLastError() << endl;
                            exit(EXIT_FAILURE);
                        }
                        break;
                    }
                    else continue;
                }
            }
            else if (recv_len > 500){
                buf[recv_len] = '\0';
                datamap[si_other.sin_port]->randStr = buf;
                finish += 1;
                while (true){
                    FD_ZERO(&WriteSet);
                    FD_SET(soc, &WriteSet);
                    total = select(soc + 1, NULL, &WriteSet, NULL, NULL);
                    if (total > 0 && FD_ISSET(soc, &WriteSet)){
                        if (sendto(soc, "end", 3, 0, (sockaddr*)&si_other, slen) == SOCKET_ERROR){
                            cout << "Sendto() failed with error code : " << WSAGetLastError() << endl;
                            exit(EXIT_FAILURE);
                        }
                        break;
                    }
                    else continue;
                }
            }
            if (finish >= 500) break;
        }
        else continue;
    }

    MYSQL * mysql;
    if ((mysql = mysql_init(NULL)) == NULL){
        fout << "mysql_init failed" << endl;
        exit(-1);
    }
    mysql_set_character_set(mysql, "gbk");

    if (mysql_real_connect(mysql, mysql_ip.c_str(), mysql_user.c_str(), mysql_password.c_str(), mysql_dbname.c_str(), 0, NULL, 0) == NULL){
        fout << "mysql_real_connect failed(" << mysql_error(mysql) << ")" << endl;
        exit(-1);
    }
    stringstream ss("");
    for (auto it = datamap.begin(); it != datamap.end(); it++){
        ss.str("");
        ss << "insert into " << mysql_tbname4 <<" values (" << it->second->pid << ", '" << it->second->time << "', '" << it->second->randStr << "')";
        if (mysql_query(mysql, ss.str().c_str())){
            fout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        }
    }
    mysql_close(mysql);

    closesocket(soc);
    WSACleanup();
    fout.close();
    return 0;
}