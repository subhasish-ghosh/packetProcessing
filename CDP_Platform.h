/**
* @file CDP_Platform.h
* @brief Generic Header for Windows or Linux based compilation
* @author Subhasish Ghosh
*/
#ifndef CODINGTEST_CDP_PLATFORM_H
#define CODINGTEST_CDP_PLATFORM_H

#include <algorithm>
#include <array>
#include <chrono>

#ifdef __GNUC__

#include <netinet/in.h>

#define cdp_ntohl(a)    be32toh(a)
#define cdp_ntohll(a)    be64toh(a)
#define PACK(__Declaration__) __Declaration__ __attribute__((__packed__))
#else
#include <winsock2.h>
#include <BaseTsd.h>
#pragma comment(lib, "Ws2_32.lib")
#define cdp_ntohl(a)	ntohl(a)
#define cdp_ntohll(a)	ntohll(a)
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))
typedef SSIZE_T ssize_t;
#endif


#endif
