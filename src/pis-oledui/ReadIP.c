#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

struct ifaddrs *ifAddrStruct = NULL;
int MAX_SIZE = 128;
struct in_addr tmpAddrPtr;

char * GetIP()
{
    char IPInfo[MAX_SIZE];
	while (ifAddrStruct != NULL)
	{
		if (ifAddrStruct->ifa_addr->sa_family == AF_INET)
		{ // check it is IP4 is a valid IP4 Address
			tmpAddrPtr = &((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
			char addressBuffer[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);

			if (strcmp(ifAddrStruct->ifa_name, "eth0") == 0)
			{
				sprintf(IPInfo, "eth0:IP:%s", addressBuffer);
				break;
			}
			else if (strcmp(ifAddrStruct->ifa_name, "wlan0") == 0)
			{
				sprintf(IPInfo, "wlan0:%s", addressBuffer);
				break;
			}
        }
		ifAddrStruct = ifAddrStruct->ifa_next;
	}
    return IPInfo;
}