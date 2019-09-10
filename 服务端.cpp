#include <iostream>
#include <windows.h>

using namespace std;

#pragma comment(lib,"ws2_32.lib")//���þ�̬���ӿ�

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested=MAKEWORD(2,2);
	
	err = WSAStartup( wVersionRequested,&wsaData);
	
	if(err!=0)
	{
		//tell the user we could nto find a usable
		//Winsock DLL;
		return 0;
	}
	
	if(LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion)!=2)
	{
		WSACleanup();
		return 0;
	}
	
	//The WinSock DLL is acceptable,Proceed windows�°汾��Э��
	///////////////////////////////////////////////////////////
	SOCKET sockSer;//�������׽���
	sockSer = socket(AF_INET,SOCK_STREAM,0);//�����׽��֣�AF_INET����IP���壬0��Ĭ�ϵķ�ʽ���� ����������ʽ �����������ݰ��׽���
	
	SOCKADDR_IN addrSer,addrCli;
	addrSer.sin_family = AF_INET;
	addrSer.sin_port = htons(5050);
	addrSer.sin_addr.S_un.S_addr = inet_addr("192.168.3.173");
	
	bind(sockSer,(SOCKADDR*)&addrSer,sizeof(SOCKADDR));//���׽��� ����������ص�ַ��Ϣ���а�
	
	listen(sockSer,5);//�����׽��� 5�Ƕ��д�С
	
	SOCKET sockConn;//��һ����Ӧ���׽���
	int len = sizeof(SOCKADDR);
	
	cout<<"Server wait Client Connect........"<<endl;
	sockConn = accept(sockSer,(SOCKADDR*)&addrCli,&len);//�����µ����� 3�������ֱ��Ƿ��������׽��ֺţ��ͻ��˵�ַ����Ӧ��ַ��ȵĵ�ַ�Ե�ַ��ʽ����
	
	
	if(sockConn == INVALID_SOCKET)//INVALID_SOCKET�Ƿ��׽���
	{  
		cout<<"Server Accept Client Connect Fail"<<endl;
		return 0;
	}
	else
	{
		cout<<"Server Accept Client Connect Success"<<endl;
		return 0;	
	}
	
	
	char sendbuf[256];
	char recvbuf[256];
	
	while(1)
	{
		cout<<"Ser: >";
		cin>>sendbuf;//������
		if(strcmp(sendbuf,"quit")==0)//��ȱ�ʾ�����������˳� 
		{
			break;
		}
		send(sockConn,sendbuf,strlen(sendbuf)+1,0);//���ͷ�����  +1��Ϊ���ַ�����/0  3�������ֱ���Ҫ���͵��׽��֣����壬���� 
		
		recv(sockConn,recvbuf,256,0);//����
		cout<<"Cli:>"<<recvbuf<<endl;
		 
	}
	
	closesocket(sockSer);//	
	WSACleanup();//����汾��Ϣ
	
	return 0;
}
 
