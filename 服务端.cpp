#include "winsock2.h"
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
    const int BUF_SIZE = 64;
    WSADATA         wsd;            //WSADATA����
    SOCKET          sServer;        //�������׽���
    SOCKET          sClient;        //�ͻ����׽���
    SOCKADDR_IN     addrServ;;      //��������ַ
    char            buf[BUF_SIZE];  //�������ݻ�����
    char            sendBuf[BUF_SIZE];//���ظ��ͻ��˵�����
    int             retVal;         //����ֵ
								   //��ʼ���׽��ֶ�̬��
    if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
    {
        cout << "WSAStartup failed!" << endl;
        return 1;
    }

    //�����׽���
    sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == sServer)
    {
        cout << "socket failed!" << endl;
        WSACleanup();//�ͷ��׽�����Դ;
        return  -1;
    }

    //�������׽��ֵ�ַ 
    addrServ.sin_family = AF_INET;
    addrServ.sin_port = htons(4999);
    addrServ.sin_addr.s_addr = INADDR_ANY;
    //���׽���
    
    retVal = bind(sServer, (LPSOCKADDR)&addrServ, sizeof(SOCKADDR_IN));
    if (SOCKET_ERROR == retVal)
    {
        cout << "bind failed!" << endl;
        closesocket(sServer);   //�ر��׽���
        WSACleanup();           //�ͷ��׽�����Դ;
        return -1;
    }

    //��ʼ���� 
    
    retVal = listen(sServer, 1);
    if (SOCKET_ERROR == retVal)
    {
        cout << "listen failed!" << endl;
        closesocket(sServer);   //�ر��׽���
        WSACleanup();           //�ͷ��׽�����Դ;
        return -1;
    }

    //���ܿͻ�������
    sockaddr_in addrClient;
    int addrClientlen = sizeof(addrClient);
    sClient = accept(sServer, (sockaddr FAR*)&addrClient, &addrClientlen);
    if (INVALID_SOCKET == sClient)
    {
        cout << "accept failed!" << endl;
        closesocket(sServer);   //�ر��׽���
        WSACleanup();           //�ͷ��׽�����Դ;
        return -1;
    }

    while (true)
    {
        //���տͻ�������
        ZeroMemory(buf, BUF_SIZE);
        retVal = recv(sClient, buf, BUF_SIZE, 0);
        if (SOCKET_ERROR == retVal)
        {
            cout << "recv failed!" << endl;
            closesocket(sServer);   //�ر��׽���
            closesocket(sClient);   //�ر��׽���     
            WSACleanup();           //�ͷ��׽�����Դ;
            return -1;
        }
        if (buf[0] == '0')
            break;
        cout << "�ͻ��˷��͵�����: " << buf << endl;

        cout << "��ͻ��˷�������: ";
        cin >> sendBuf;

        send(sClient, sendBuf, strlen(sendBuf), 0);
    }

    //�˳�
    closesocket(sServer);   //�ر��׽���
    closesocket(sClient);   //�ر��׽���
    WSACleanup();           //�ͷ��׽�����Դ;

    return 0;
}
 
