/************************************************************************************

PublicHeader:   n/a
Filename    :   OWin32Socket.cpp
Content     :   Windows-specific socket-based networking implementation
Created     :   December 4, 2018
Authors     :   defeng.liang
************************************************************************************/

#include "OWin32Socket.h"
#pragma comment(lib,"ws2_32.lib")

namespace OST {

	// WSAStartupSingleton
	class OWSAStartupSingleton
	{
	public:
		static void AddRef(void);
		static void DeRef(void);
	protected:
		static int RefCount;
	};

	// �����ʼ����̬���Ա����
	int OWSAStartupSingleton::RefCount = 0;

	// ʵ�־�̬���Ա����
	void OWSAStartupSingleton::AddRef()
	{
		if (++RefCount == 1)
		{
			WSADATA wsaData;
			const int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (err != 0)
			{
				std::cout << "[Socket] Unable to initialize Winsock " << err << std::endl;
			}
		}
	}

	void OWSAStartupSingleton::DeRef()
	{
		if (RefCount > 0)
		{
			if (--RefCount == 0)
			{
				WSACleanup();
				RefCount = 0;
			}
		}
	}
}