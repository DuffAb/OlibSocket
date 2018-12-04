/************************************************************************************

PublicHeader:   n/a
Filename    :   OSocket.h
Content     :   Socket common data shared between all platforms.
Created     :   December 4, 2018
Authors     :   defeng.liang
************************************************************************************/

#ifndef _O_SOCKET_H_
#define _O_SOCKET_H_

#include <iostream>
#include <string>
#include "OTypes.h"

#ifdef _WIN32
#include <WinSock2.h>
#elif __linux__	// linux

#endif
using namespace std;
namespace OST {

	class OSockAddr;

#ifdef _WIN32
	typedef SOCKET SocketHandle;
#elif __linux__	// linux
	typedef int SocketHandle;
	static const SocketHandle INVALID_SOCKET = -1;
	static const int SOCKET_ERROR = -1;
#endif
	
	//-----------------------------------------------------------------------------
	// Types of network transport
	enum TransportType
	{
		TransportType_None,          // No transport (useful placeholder for invalid states)
		TransportType_Loopback,      // Loopback transport: Class talks to itself
		TransportType_TCP,           // TCP/IPv4/v6
		TransportType_UDP,           // UDP/IPv4/v6
		TransportType_PacketizedTCP  // Packetized TCP: Message framing is automatic
	};

	//-----------------------------------------------------------------------------
	// Abstraction for a network socket. Inheritance hierarchy		// �����׽��ֵĳ���㡣 �̳в�νṹ
	// modeled after RakNet so that future support can be added		// ��RakNetΪģ�ͣ��Ա�������δ����֧��
	// for Linux, Windows RT, consoles, etc.						// ������Linux��Windows RT��consoles ��
	class OSocket
	{
	public:
		OSocket();
		virtual void Close() = 0;// ���麯��

	public:
		TransportType Transport; // Type of transport
	};

	//-----------------------------------------------------------------------------
	// Bind parameters for Berkley sockets							// ��Berkeley�׽��ֵĲ���
	struct OBerkleyBindParameters
	{
	public:
		OBerkleyBindParameters();

	public:
		uint16_t Port;     // Port
		string Address;
		uint32_t blockingTimeout;
	};

	//-----------------------------------------------------------------------------
	// Berkley socket
	class OBerkleySocket : public OSocket
	{
	public:
		OBerkleySocket();
		virtual ~OBerkleySocket();

		virtual void    OClose();
		virtual int32_t OGetSockname(OSockAddr* pSockAddrOut);
		virtual void    OSetBlockingTimeout(int timeoutMs) // milliseconds
		{
			TimeoutSec = timeoutMs / 1000;
			TimeoutUsec = (timeoutMs % 1000) * 1000;
		}
		int             OGetBlockingTimeoutUsec() const
		{
			return TimeoutUsec;
		}
		int             OGetBlockingTimeoutSec() const
		{
			return TimeoutSec;
		}
		SocketHandle    OGetSocketHandle() const
		{
			return TheSocket;
		}

	protected:
		SocketHandle TheSocket;           // Socket handle
		int TimeoutUsec, TimeoutSec;
	};
}
#endif  /*_O_SOCKET_H_*/