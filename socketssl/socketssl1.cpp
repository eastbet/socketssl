// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//
//openssl req - x509 - newkey rsa : 4096 - sha256 - nodes - keyout example.key - out example.crt - subj "/CN=localhost" - days 365

#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>  
#include <stdlib.h> 
#include <iostream>
#include <openssl/bio.h>
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "rapidxml-1.13/rapidxml.hpp"
//#include "rapidjson/document.h" 
//#include "rapidjson/writer.h" 
//#include "rapidjson/reader.h" 
//#include "rapidjson/stringbuffer.h" 
#include <fstream>
#include <vector>
#include "windows.h"
#include <stdint.h>
#include <amqp_ssl_socket.h>
#include <amqp_framing.h>
#include <assert.h>

#ifndef librabbitmq_examples_utils_h
#define librabbitmq_examples_utils_h
#endif

//#define CERTF  "/cert.pem"
//#define KEYF  "/key.pem"
#define CERTF  "/passionbet.crt"
#define KEYF  "/passionbet.key"
#define DEFAULT_BUFLEN 67108864
#define NAME_LENTGH 124
#define SPORT_LENTGH 200
#define TOURNAMENT_LENTGH 10000
#define CATEGORY_LENTGH 10000
#define SUMMARY_EVERY_US 1000000
// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")
char* recvbuf;
class Sport{
public:
Sport();
~Sport() { delete[] name; };
int id;
int sort;
char *name;
void operator = (const Sport&);
};
void Sport:: operator = (const Sport & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	sort = rhs.sort;
	strcpy(name, rhs.name);
}
Sport::Sport() {
id = 0;
sort = 0;
name = new char[NAME_LENTGH];
};
class Tournament {
public:
	Tournament();
	~Tournament() { delete[] name; };
	int id;
	int idSport;
	int idCategory;
	int sort;
	char *name;
	void operator = (const Tournament&);
};
void Tournament:: operator = (const Tournament & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	idCategory = rhs.idCategory;
	idSport = rhs.idSport;
	sort = rhs.sort;
	strcpy(name, rhs.name);
}
Tournament::Tournament() {
	id = 0;
	idCategory = 0;
	idSport = 0;
	sort = 0;
	name = new char[NAME_LENTGH];
};
class Category {
public:
	Category();
	~Category() { delete[] name; };
	int id;
	int idSport;
	int sort;
	char *name;
	void operator = (const Category&);
};
void Category:: operator = (const Category & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	idSport = rhs.idSport;
	sort = rhs.sort;
	strcpy(name, rhs.name);
}
Category::Category() {
	id = 0;
	idSport = 0;
	sort = 0;
	name = new char[NAME_LENTGH];
};

Sport* sports = new Sport[SPORT_LENTGH];
int sports_l = 0;
Tournament* tournaments = new Tournament[TOURNAMENT_LENTGH];
int tournaments_l = 0;
Category* categories = new Category[CATEGORY_LENTGH];
int categories_l = 0;
void createSports();
void createCategoriesTournaments();
int httpsRequest(char*, char*, char*, int);
int httpsServer();
void sdkSocket();
void createRecovery();
void die(const char *, ...);
void die_on_error(int, char const*);
void die_on_amqp_error(amqp_rpc_reply_t, char const *);
void amqp_dump(void const *, size_t);
uint64_t now_microseconds(void);
void microsleep(int);
void rabbitmqssl();
static void run(amqp_connection_state_t);
static int rows_eq(int *, int *);
static void dump_row(long, int, int *);



int main()
{
	//char* domain = "api.betradar.com";
	//char* path = "/v1/sports/en/sports.xml";//" / v1 / sports / en / tournaments.xml";
	int recvbuflen = DEFAULT_BUFLEN; 
	recvbuf = new char[DEFAULT_BUFLEN];
	//sdkSocket();
	createRecovery();
	//httpsRequest(domain, path, recvbuf, 0);
	createSports();
	createCategoriesTournaments();
	rabbitmqssl();
	//sdkSocket();
	//httpsServer();
	return 0;
}
void createRecovery() {
	httpsRequest("api.betradar.com", "/v1/pre/recovery/initiate_request?request_id=1", recvbuf, 1);
	//printf(recvbuf);
	printf("Start recovery\r\n");


}
void createCategoriesTournaments() {
	httpsRequest("api.betradar.com", "/v1/sports/en/tournaments.xml", recvbuf, 0);
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;
	using namespace std;
	int i = 0;
	int j = 0;
	int temp = 0;
	int temp2 = CATEGORY_LENTGH;
	int* find = new int[CATEGORY_LENTGH];
	for (i = 0; i < temp2; i++) find[i] = 0;
	for (i = 0; i < 1000; i++) if (recvbuf[i] == '\r' && recvbuf[i + 1] == '\n' && recvbuf[i + 2] == '\r' && recvbuf[i + 3] == '\n') break;
	doc.parse<0>((char*)((char*)recvbuf + i + 4));
	root_node = doc.first_node("tournaments");
	i = 0;
	for (xml_node<> * tournament_node = root_node->first_node("tournament"); tournament_node; tournament_node = tournament_node->next_sibling())
	{
		strcpy(tournaments[i].name, tournament_node->first_attribute("name")->value());
		tournaments[i].id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 14));
		if (tournaments[i].id == 0) tournaments[i].id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 19));
		//printf("tournamentId=%d Name=%s", tournaments[i].id, tournaments[i].name);
		temp = atoi((char*)((char*)tournament_node->first_node("category")->first_attribute("id")->value() + 12));
		temp2 = atoi((char*)((char*)tournament_node->first_node("sport")->first_attribute("id")->value() + 9));
		if (find[temp] != 1) {
			strcpy(categories[j].name, tournament_node->first_node("category")->first_attribute("name")->value());
			categories[j].id = temp;
			categories[j].idSport = temp2;
			//printf("categoriesid=%d categoriesName=%s", categories[j].id, categories[j].name);
			//cout << endl;
			find[temp] = 1;
			j++;
		}
		tournaments[i].idSport = temp2;
		tournaments[i].idCategory = temp;

		//printf("tournamentId=%d Name=%s tournamentIdSport=%d tournamentIdCategory=%d", tournaments[i].id, tournaments[i].name, tournaments[i].idSport, tournaments[i].idCategory);
		//cout << endl;
		i++;

		//cout << endl;
	}

	tournaments_l = i;
	categories_l = j;
	printf("Create tournament successful. Number of tournaments: %d\r\n", tournaments_l);
	printf("Create categories successful. Number of categories: %d\r\n", categories_l);
	delete[] find;
}
void createSports() {
httpsRequest("api.betradar.com", "/v1/sports/en/sports.xml", recvbuf, 0);
using namespace rapidxml;
xml_document<> doc;
xml_node<> * root_node;
using namespace std;
int i = 0;
for (i = 0; i < 1000; i++) if (recvbuf[i] == '\r' && recvbuf[i + 1] == '\n' && recvbuf[i + 2] == '\r' && recvbuf[i + 3] == '\n') break;
doc.parse<0>((char*)((char*)recvbuf + i+4));
root_node = doc.first_node("sports");
i = 0;

for (xml_node<> * sport_node = root_node->first_node("sport"); sport_node; sport_node = sport_node->next_sibling())
{       
	strcpy(sports[i].name, sport_node->first_attribute("name")->value());
	sports[i].id = atoi((char*)((char*)sport_node->first_attribute("id")->value()+9));


	//printf("sportId=%d Name=%s", sports[i].id, sports[i].name);
	i++;
	//sport_node->first_attribute("name")->value();
	//cout << endl;
}

sports_l = i;
printf("Create sports successful. Number of sports: %d\r\n", sports_l);

}
void sdkSocket() {
	// Initialize Winsock
	WSADATA wsaData;
	int iResult = 0;
	int recvbuflen = DEFAULT_BUFLEN;
	char *sendBuf = new char[recvbuflen];
	char *recvbuf = new char[recvbuflen];
	int i = 0;
	SOCKET sdkSocket;
	sockaddr_in sdkService;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		wprintf(L"WSAStartup() failed with error: %d\n", iResult);
		return ;
	}

	sdkSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sdkSocket == INVALID_SOCKET) {
		wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return;
	}

	sdkService.sin_family = AF_INET;
	sdkService.sin_addr.s_addr = inet_addr("137.74.195.97");
	sdkService.sin_port = htons(8080);

	iResult = connect(sdkSocket, (SOCKADDR *)& sdkService, sizeof(sdkService));
	if (iResult == SOCKET_ERROR) {
		wprintf(L"connect function failed with error: %ld\n", WSAGetLastError());
		iResult = closesocket(sdkSocket);
		if (iResult == SOCKET_ERROR)
			wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return ;
	}

	wprintf(L"Connected to server.\n");
	//createRecovery();
//	iResult = send(sdkSocket, sendBuf, (int)strlen(sendBuf), 0);

	i = 0;
	do {
		i++;
	
		iResult = recv(sdkSocket, recvbuf, recvbuflen, 0);
		//printf("length: %d\n", iResult);

		//if(i==200) createRecovery();

		if (iResult > 0) {
			//if(iResult > 200000)
			printf("Bytes received: %d\n", iResult);

			//json.Parse<0>(recvbuf);
			recvbuf[100] = '\0';
			printf("%s", recvbuf);

		}
		else if (iResult == -1)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());
	//	iResult = -2;
		
	} while (iResult > -1);




};
int httpsServer() {
	WSADATA wsaData;
	int iResult = 0;
	X509*  cert;
	SSL_CTX *ctx;
	SSL *ssl;
	SOCKET ListenSocket = INVALID_SOCKET;
	sockaddr_in service;
	int recvbuflen = DEFAULT_BUFLEN;
	char *sendBody1 = "<title>Test C++ HTTP Server</title>\n<h1>Test page</h1>\n<p>This is body of the test page...</p>\n<h2>Request headers</h2>\n<pre>";
	char *sendBody2 = "</pre>\n<em><small>Test C++ Http Server</small></em>\n";
	char *sendHeader = "HTTP/1.1 200 OK\r\nVersion: HTTP/1.1\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: ";
	char *sendTail = "\r\n\r\n";
	char *sendBuf1 = new char[recvbuflen];
	char *sendBuf2 = new char[recvbuflen];
	char *sendBuf = new char[recvbuflen];
	char* str;
	DWORD dwError;
	char* recvbuf = new char[recvbuflen];

	int i = 0;
	SSL_load_error_strings();
	SSL_library_init();
	OpenSSL_add_all_algorithms();
	ctx = SSL_CTX_new(SSLv23_server_method());
	if (!ctx) { wprintf(L"Error init ssl\n"); return 1; }
	iResult = SSL_CTX_use_certificate_file(ctx, CERTF, SSL_FILETYPE_PEM);
	if (iResult <= 0) { wprintf(L"Error ssl certificate file %d\n", iResult); SSL_CTX_free(ctx); return 1; }
	iResult = SSL_CTX_use_PrivateKey_file(ctx, KEYF, SSL_FILETYPE_PEM);
	if (iResult <= 0) { wprintf(L"Error Private Key file %d\n", iResult); SSL_CTX_free(ctx); return 1; }
	iResult = SSL_CTX_check_private_key(ctx);
	if (!iResult) { wprintf(L"Private key does not match the certificate public key %d\n", iResult); SSL_CTX_free(ctx); return 1; }
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) { wprintf(L"WSAStartup() failed with error: %d\n", iResult); SSL_CTX_free(ctx); return 1; }

	//----------------------
	// Create a SOCKET for listening for incoming connection requests.
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET) {
		wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	//----------------------
	// The sockaddr_in structure specifies the address family,
	// IP address, and port for the socket that is being bound.
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(443);
	iResult = bind(ListenSocket, (SOCKADDR *)& service, sizeof(service));
	if (iResult == SOCKET_ERROR) {
		wprintf(L"bind function failed with error %d\n", WSAGetLastError());
		iResult = closesocket(ListenSocket);
		if (iResult == SOCKET_ERROR)
			wprintf(L"closesocket function failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	//----------------------
	// Listen for incoming connection requests 
	// on the created socket
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		wprintf(L"listen function failed with error: %d\n", WSAGetLastError());
		return 1;
	}

	printf("TCP connection is ready. Do server side SSL Connection");


	for (;;) {

		SOCKET clientSocket = accept(ListenSocket, NULL, NULL);
		if (clientSocket == INVALID_SOCKET) {
			wprintf(L"accept failed: %d\n", WSAGetLastError());
			closesocket(clientSocket);
			WSACleanup();
			return 1;
		}

		ssl = SSL_new(ctx);
		SSL_set_fd(ssl, clientSocket);
		iResult = SSL_accept(ssl);


		if (!iResult) {
			wprintf(L"SSL connect error\nretval: %d\n", iResult);
			iResult = closesocket(clientSocket);
			if (iResult == SOCKET_ERROR)
				wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;

			iResult = SSL_get_error(ssl, iResult);
			wprintf(L"SSL error: %d\n", iResult);
			return 1;
		}

		cert = SSL_get_peer_certificate(ssl);
		if (cert != NULL) {
			printf("Client certificate:\n");

			str = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
			printf("\t subject: %s\n", str);
			OPENSSL_free(str);

			str = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
			printf("\t issuer: %s\n", str);
			OPENSSL_free(str);

			/* We could do all sorts of certificate verification stuff here before
			deallocating the certificate. */

			X509_free(cert);
		}
		else
			printf("Client does not have certificate.\n");

		/* DATA EXCHANGE - Receive message and send reply. */

		iResult = SSL_read(ssl, recvbuf, recvbuflen);
		recvbuf[iResult] = '\0';
		printf("Got %d chars:'%s'\n", iResult, recvbuf);
		strcpy(sendBuf, sendHeader);
		strcpy(sendBuf1, sendBody1);
		strcat(sendBuf1, recvbuf);
		strcat(sendBuf1, sendBody2);
		_itoa(strlen(sendBuf1), sendBuf2, 10);
		strcat(sendBuf, sendBuf2);
		strcat(sendBuf, sendTail);
		strcat(sendBuf, sendBuf1);


		iResult = SSL_write(ssl, sendBuf, strlen(sendBuf));



		wprintf(L"Listening on socket...\n");





	};

	iResult = closesocket(ListenSocket);
	if (iResult == SOCKET_ERROR) {
		wprintf(L"closesocket function failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	SSL_shutdown(ssl);  /* send SSL/TLS close_notify */

						/* Clean up. */

	SSL_free(ssl);
	SSL_CTX_free(ctx);
	delete[] sendBuf;
	delete[] sendBuf1;
	delete[] sendBuf2;
	delete[] recvbuf;



	WSACleanup();
	return 0;
}
int httpsRequest(char* domain, char* path, char* recv, int mode) { 
	WSADATA wsaData;
	int iResult = 0;
	SSL_CTX *ctx;
	SSL *ssl;
	X509*  cert;
	SOCKET sdkSocket;
	sockaddr_in sdkService;
	char *sendBuf;
	DWORD dwError;
	int i = 0;
	struct hostent *remoteHost;
	char *host_name;
	struct in_addr addr;
	char **pAlias;
	char* str;
	int buflen = DEFAULT_BUFLEN;
	int readBytes = 0;

	//vps426791.ovh.net

	SSL_load_error_strings();
	SSL_library_init();
	OpenSSL_add_all_algorithms();

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) { wprintf(L"WSAStartup() failed with error: %d\n", iResult); return -1; }
	

	remoteHost = gethostbyname(domain);
	if (remoteHost == NULL) {
		dwError = WSAGetLastError(); if (dwError != 0) {
			if (dwError == WSAHOST_NOT_FOUND) { printf("Host not found\n");  WSACleanup(); return -1; }
			else if (dwError == WSANO_DATA) { printf("No data record found\n");  WSACleanup(); return -1; }
			else {
				printf("Function failed with error: %ld\n", dwError);
				 return -1;
			}
		}
	}
	/*else {
		printf("Function returned:\n"); printf("\tOfficial name: %s\n", remoteHost->h_name); 
		
		for (pAlias = remoteHost->h_aliases; *pAlias != 0; pAlias++) {
			printf("\tAlternate name #%d: %s\n", ++i, *pAlias);
		} printf("\tAddress type: ");
		
		
		switch (remoteHost->h_addrtype) {
		case AF_INET:
			printf("AF_INET\n");
			break;
		case AF_NETBIOS:
			printf("AF_NETBIOS\n");
			break;
		default:
			printf(" %d\n", remoteHost->h_addrtype);
			break;
		}
		printf("\tAddress length: %d\n", remoteHost->h_length);

		i = 0;
		if (remoteHost->h_addrtype == AF_INET)
		{
			while (remoteHost->h_addr_list[i] != 0) {
				addr.s_addr = *(u_long *)remoteHost->h_addr_list[i++];
				printf("\tIP Address #%d: %s\n", i, inet_ntoa(addr));
			}
		}
		else if (remoteHost->h_addrtype == AF_NETBIOS)
		{
			printf("NETBIOS address was returned\n");
		}
	}*/


	sdkSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sdkSocket == INVALID_SOCKET) { wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());   WSACleanup(); return -1; }
	sdkService.sin_family = AF_INET;
	sdkService.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list));
	sdkService.sin_port = htons(443);
	iResult = connect(sdkSocket, (SOCKADDR *)& sdkService, sizeof(sdkService));
	if (iResult == SOCKET_ERROR) {
		wprintf(L"connect function failed with error: %ld\n", WSAGetLastError()); iResult = closesocket(sdkSocket);
		if (iResult == SOCKET_ERROR) wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());  WSACleanup(); return -1;}
	ctx = SSL_CTX_new(SSLv23_client_method()); ssl = SSL_new(ctx);
	if (!ssl) {
		wprintf(L"SSL creation error\n"); iResult = closesocket(sdkSocket); if (iResult == SOCKET_ERROR) wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
		 WSACleanup(); return 1;
	}
	SSL_set_fd(ssl, sdkSocket);
	iResult = SSL_connect(ssl);
	if (!iResult) {
		wprintf(L"SSL connect error\nretval: %d\n", iResult); iResult = closesocket(sdkSocket);
		if (iResult == SOCKET_ERROR) { SSL_CTX_free(ctx);  wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError()); WSACleanup(); return -1; }
		iResult = SSL_get_error(ssl, iResult); wprintf(L"SSL error: %d\n", iResult); return 1;
	}
	cert = SSL_get_peer_certificate(ssl);
	str = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
	//printf("\t subject: %s\n", str);
	OPENSSL_free(str);
	str = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
	//printf("\t issuer: %s\n", str);
	OPENSSL_free(str);
	X509_free(cert);
	sendBuf = new char[1024];
	if(mode==0) strcpy(sendBuf, "GET ");
	else strcpy(sendBuf, "POST ");
	strcat(sendBuf, path);
	strcat(sendBuf," HTTP/1.0\nHost: ");
	strcat(sendBuf, domain);
	strcat(sendBuf, "\r\nx-access-token: YaNJ9uwq8GHe953XQD\r\nUser-Agent: Webclient\r\nAccept:*/*\r\n\r\n");
	iResult = SSL_write(ssl, sendBuf, strlen(sendBuf));
	do {
		iResult = SSL_read(ssl, (char*) recv +readBytes , buflen- readBytes);
		if (iResult > 0) {
			readBytes = readBytes + iResult;
			recv[readBytes] = '\0';
		}
	} while (iResult > 0);

	//printf(recv);

	delete[] sendBuf;
	closesocket(sdkSocket);
	SSL_shutdown(ssl); 
	SSL_free(ssl);
	SSL_CTX_free(ctx);
	
	WSACleanup();
	return 0;
	
};
uint64_t now_microseconds(void)
{
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	return (((uint64_t)ft.dwHighDateTime << 32) | (uint64_t)ft.dwLowDateTime)
		/ 10;
}
void microsleep(int usec)
{
	Sleep(usec / 1000);
}
void die(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
	exit(1);
}
void die_on_error(int x, char const *context)
{
	if (x < 0) {
		fprintf(stderr, "%s: %s\n", context, amqp_error_string2(x));
		exit(1);
	}
}
void die_on_amqp_error(amqp_rpc_reply_t x, char const *context)
{
	switch (x.reply_type) {
	case AMQP_RESPONSE_NORMAL:
		return;

	case AMQP_RESPONSE_NONE:
		fprintf(stderr, "%s: missing RPC reply type!\n", context);
		break;

	case AMQP_RESPONSE_LIBRARY_EXCEPTION:
		fprintf(stderr, "%s: %s\n", context, amqp_error_string2(x.library_error));
		break;

	case AMQP_RESPONSE_SERVER_EXCEPTION:
		switch (x.reply.id) {
		case AMQP_CONNECTION_CLOSE_METHOD: {
			amqp_connection_close_t *m = (amqp_connection_close_t *)x.reply.decoded;
			fprintf(stderr, "%s: server connection error %uh, message: %.*s\n",
				context,
				m->reply_code,
				(int)m->reply_text.len, (char *)m->reply_text.bytes);
			break;
		}
		case AMQP_CHANNEL_CLOSE_METHOD: {
			amqp_channel_close_t *m = (amqp_channel_close_t *)x.reply.decoded;
			fprintf(stderr, "%s: server channel error %uh, message: %.*s\n",
				context,
				m->reply_code,
				(int)m->reply_text.len, (char *)m->reply_text.bytes);
			break;
		}
		default:
			fprintf(stderr, "%s: unknown server error, method id 0x%08X\n", context, x.reply.id);
			break;
		}
		break;
	}

	exit(1);
}
static void dump_row(long count, int numinrow, int *chs)
{
	int i;

	printf("%08lX:", count - numinrow);

	if (numinrow > 0) {
		for (i = 0; i < numinrow; i++) {
			if (i == 8) {
				printf(" :");
			}
			printf(" %02X", chs[i]);
		}
		for (i = numinrow; i < 16; i++) {
			if (i == 8) {
				printf(" :");
			}
			printf("   ");
		}
		printf("  ");
		for (i = 0; i < numinrow; i++) {
			if (isprint(chs[i])) {
				printf("%c", chs[i]);
			}
			else {
				printf(".");
			}
		}
	}
	printf("\n");
}
static int rows_eq(int *a, int *b)
{
	int i;

	for (i = 0; i<16; i++)
		if (a[i] != b[i]) {
			return 0;
		}

	return 1;
}
void amqp_dump(void const *buffer, size_t len)
{
	unsigned char *buf = (unsigned char *)buffer;
	long count = 0;
	int numinrow = 0;
	int chs[16];
	int oldchs[16] = { 0 };
	int showed_dots = 0;
	size_t i;

	for (i = 0; i < len; i++) {
		int ch = buf[i];

		if (numinrow == 16) {
			int j;

			if (rows_eq(oldchs, chs)) {
				if (!showed_dots) {
					showed_dots = 1;
					printf("          .. .. .. .. .. .. .. .. : .. .. .. .. .. .. .. ..\n");
				}
			}
			else {
				showed_dots = 0;
				dump_row(count, numinrow, chs);
			}

			for (j = 0; j<16; j++) {
				oldchs[j] = chs[j];
			}

			numinrow = 0;
		}

		count++;
		chs[numinrow++] = ch;
	}

	dump_row(count, numinrow, chs);

	if (numinrow != 0) {
		printf("%08lX:\n", count);
	}
}
static void run(amqp_connection_state_t conn)
{
	uint64_t start_time = now_microseconds();
	int received = 0;
	int previous_received = 0;
	uint64_t previous_report_time = start_time;
	uint64_t next_summary_time = start_time + SUMMARY_EVERY_US;

	amqp_frame_t frame;

	uint64_t now;

	for (;;) {
		amqp_rpc_reply_t ret;
		amqp_envelope_t envelope;
		int i = 0;

		now = now_microseconds();
		if (now > next_summary_time) {
			int countOverInterval = received - previous_received;
			double intervalRate = countOverInterval / ((now - previous_report_time) / 1000000.0);
			printf("%d ms: Received %d - %d since last report (%d Hz)\n",
				(int)(now - start_time) / 1000, received, countOverInterval, (int)intervalRate);

			previous_received = received;
			previous_report_time = now;
			next_summary_time += SUMMARY_EVERY_US;
		}

		amqp_maybe_release_buffers(conn);
		ret = amqp_consume_message(conn, &envelope, NULL, 0);
		//envelope.message.body.bytes
		printf("message length= %d",(int)envelope.message.body.len);
		//if(i<4) printf((char*)envelope.message.body.bytes);
		//i++;



		if (AMQP_RESPONSE_NORMAL != ret.reply_type) {
			if (AMQP_RESPONSE_LIBRARY_EXCEPTION == ret.reply_type &&
				AMQP_STATUS_UNEXPECTED_STATE == ret.library_error) {
				if (AMQP_STATUS_OK != amqp_simple_wait_frame(conn, &frame)) {
					return;
				}

				if (AMQP_FRAME_METHOD == frame.frame_type) {
					switch (frame.payload.method.id) {
					case AMQP_BASIC_ACK_METHOD:
						/* if we've turned publisher confirms on, and we've published a message
						* here is a message being confirmed
						*/

						break;
					case AMQP_BASIC_RETURN_METHOD:
						/* if a published message couldn't be routed and the mandatory flag was set
						* this is what would be returned. The message then needs to be read.
						*/
					{
						amqp_message_t message;
						ret = amqp_read_message(conn, frame.channel, &message, 0);
						if (AMQP_RESPONSE_NORMAL != ret.reply_type) {
							return;
						}

						amqp_destroy_message(&message);
					}

					break;

					case AMQP_CHANNEL_CLOSE_METHOD:
						/* a channel.close method happens when a channel exception occurs, this
						* can happen by publishing to an exchange that doesn't exist for example
						*
						* In this case you would need to open another channel redeclare any queues
						* that were declared auto-delete, and restart any consumers that were attached
						* to the previous channel
						*/
						return;

					case AMQP_CONNECTION_CLOSE_METHOD:
						/* a connection.close method happens when a connection exception occurs,
						* this can happen by trying to use a channel that isn't open for example.
						*
						* In this case the whole connection must be restarted.
						*/
						return;

					default:
						fprintf(stderr, "An unexpected method was received %u\n", frame.payload.method.id);
						return;
					}
				}
			}

		}
		else {
			amqp_destroy_envelope(&envelope);
		}


		received++;
	}
}
void rabbitmqssl() {
	using namespace rapidxml;
	using namespace std;
	char const *hostname;
	int port, status;
	char const *exchange;
	char *bindingkey;
	amqp_socket_t *socket;
	amqp_connection_state_t conn;
	amqp_bytes_t queuename;
	xml_document<> doc;
	xml_node<> * root_node;


	/*	if (argc < 3) {
	fprintf(stderr, "Usage: amqps_consumer host port "
	"[cacert.pem [verifypeer] [verifyhostname] [key.pem cert.pem]]\n");
	return 1;
	}*/



	hostname = "mq.betradar.com";// argv[1];
	port = 5671;//atoi(argv[2]);
	exchange = "unifiedfeed";// "amq.direct"; /* argv[3]; */
	bindingkey = "#"; /* argv[4]; */
	conn = amqp_new_connection();
	socket = amqp_ssl_socket_new(conn);
	if (!socket) {
		die("creating SSL/TLS socket");
	}

	amqp_ssl_socket_set_verify_peer(socket, 0);
	amqp_ssl_socket_set_verify_hostname(socket, 0);
	/*
	if (argc > 3) {
	int nextarg = 4;
	status = amqp_ssl_socket_set_cacert(socket, argv[3]);
	if (status) {
	die("setting CA certificate");
	}
	if (argc > nextarg && !strcmp("verifypeer", argv[nextarg])) {
	amqp_ssl_socket_set_verify_peer(socket, 1);
	nextarg++;
	}
	if (argc > nextarg && !strcmp("verifyhostname", argv[nextarg])) {
	amqp_ssl_socket_set_verify_hostname(socket, 1);
	nextarg++;
	}
	if (argc > nextarg + 1) {
	status =
	amqp_ssl_socket_set_key(socket, argv[nextarg + 1], argv[nextarg]);
	if (status) {
	die("setting client key");
	}
	}
	}

	*/

	status = amqp_socket_open(socket, hostname, port);
	if (status) {
		die("opening SSL/TLS connection");
	}

	die_on_amqp_error(amqp_login(conn, "/unifiedfeed/19751", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "YaNJ9uwq8GHe953XQD", ""),
		"Logging in");

	amqp_channel_open(conn, 1);

	die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel");

	{
		amqp_queue_declare_ok_t *r = amqp_queue_declare(conn, 1, amqp_empty_bytes, 0, 0, 0, 1,
			amqp_empty_table);
		die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring queue");
		queuename = amqp_bytes_malloc_dup(r->queue);

		//printf("%d", queuename.len);

		if (queuename.bytes == NULL) {
			fprintf(stderr, "Out of memory while copying queue name");
			return;
		}
	}

	amqp_queue_bind(conn, 1, queuename, amqp_cstring_bytes(exchange), amqp_cstring_bytes(bindingkey),
		amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Binding queue");

	amqp_basic_consume(conn, 1, queuename, amqp_empty_bytes, 0, 1, 0, amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Consuming");

	run(conn);

	die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
	die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
	die_on_error(amqp_destroy_connection(conn), "Ending connection");

	return;
}












