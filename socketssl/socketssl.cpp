
#define WIN32_LEAN_AND_MEAN
#undef _UNICODE
#undef UNICODE
#include "stdafx.h"
#include <cstdint>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/options/index.hpp>
#include <mongocxx/options/insert.hpp>
#include <mongocxx/options/update.hpp>

#pragma execution_character_set("utf-8") 
#pragma warning(disable : 4996)


#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#include <mutex>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>  
#include <stdlib.h> 
#include <stdint.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <conio.h>
#include <time.h>
#include <ctime>
#include <vector>
#include "windows.h"
#include <assert.h>
#include <fcntl.h>
#include <map>
#include <math.h>
#include <iphlpapi.h>
#include <openssl/bio.h>
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include "zlib/zlib.h"
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include <iostream>
#include <amqp_ssl_socket.h>
#include <amqp_framing.h>
#include <unordered_map>
#include <unordered_set>
#include <atomic>
#include <boost/algorithm/string.hpp>  

#define ZLIB_WINAPI   // actually actually needed (for linkage)

#pragma comment(lib, "zlibwapi.lib") // for access to the DLL

int GetMaxCompressedLen(int);
int CompressData(const BYTE*, int, BYTE*, int);
int UncompressData(const BYTE*, int, BYTE*, int);
int gzip(char*, int, char* &, int);
string getTournamentKey(int, int);
int64_t timestamp();
int DMYtoSeconds(int, int, int);

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")
#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))



using namespace std;

typedef void(*nullCallback)();
typedef void(*defaultCallback)(int);
typedef void(*messageCallback)(int, string);

#define WS_FIN 128
#define WS_MASK 128

#define WS_OPCODE_CONTINUATION 0
#define WS_OPCODE_TEXT         1
#define WS_OPCODE_BINARY       2
#define WS_OPCODE_CLOSE        8
#define WS_OPCODE_PING         9
#define WS_OPCODE_PONG         10

#define WS_PAYLOAD_LENGTH_16 126
#define WS_PAYLOAD_LENGTH_63 127

#define WS_READY_STATE_CONNECTING 0
#define WS_READY_STATE_OPEN       1
#define WS_READY_STATE_CLOSING    2
#define WS_READY_STATE_CLOSED     3
#define HTTPS_STATE_OPEN          5
#define HTTPS_STATE_READ          6
#define HTTPS_STATE_WRITE         7
#define WS_READY_STATE_DATA_ERROR 8

#define WS_STATUS_NORMAL_CLOSE             1000
#define WS_STATUS_GONE_AWAY                1001
#define WS_STATUS_PROTOCOL_ERROR           1002
#define WS_STATUS_UNSUPPORTED_MESSAGE_TYPE 1003
#define WS_STATUS_MESSAGE_TOO_BIG          1004

#define WS_STATUS_TIMEOUT 3000

#define JUMP_PROCESS 15
#define WS_TIMEOUT_RECV 10
#define WS_TIMEOUT_PONG 5
#define MAX_OAM 100
#define MAX_PATH 255
#define EXTRA 67108864
#define LARGE 16777216
#define SMALL 4096
#define MAX_HTTPS_READ_BUFFER 8388608 
#define PLAYERS_LENTGH 300000
#define COMPETITORS_LENTGH 150000
#define NAME_LENTGH 127
#define MAX_OUTCOME 700
#define MAX_OUTCOME_NAME 256
#define SPORTS_LENTGH 200
#define BETSTOPS_LENTGH 200
#define VOIDREASONS_LENTGH 200
#define MATCHSTATUS_LENTGH 1000
#define TOURNAMENTS_LENTGH 10000
#define EVENTS_LENTGH 100000
#define LINES_LENTGH 10000000
#define CATEGORIES_LENTGH 10000
#define SUMMARY_EVERY_US 1000000
#define MARKETS_LENGTH 10000	
#define BET_TIMEOUT_REPORTING 3
#define BET_TIMEOUT 7
#define MAX_EVENTS 20000000
#define MAX_LINES 10000000
#define MAX_COEFF_SYSTEM 5000
#define MAX_TOURNAMENTS 1000000
#define MAX_CATEGORIES 10000
#define MAX_COMPETITORS 1000000
#define MAX_PLAYERS 10000000
#define MAX_SPORTS 1000
#define MAX_MARKETS 7000
#define MAX_MARKETS_IN 5000
#define MAX_BETSTOPS 200
#define MAX_VOIDREASONS 200
#define MAX_MATCHSTATUS 1000
#define QUEUE_LENGTH 2000
#define RECV_MAX_CLIENT_QUEUE 10 
#define RECV_MAX_TICKET_QUEUE 10 
#define STEP_QUEUE 100
#define AMQP_QUEUE 5000
#define AMQP_BUFLEN 262144
#define DEBUG_OUTPUT false
#define PRINT false
#define PROBABILITIES 0
#define VIRTUAL 0
#define USER 0
#define REPLAY 0
#define WRITE_NEW_DATA_TO_MONGO  true

#if USER == 0
#define MTS_FLAG 2
#define MONGO_URI "mongodb://bet:38998716@192.168.44.23:27017/?authSource=betdb"
#define CERTF  "/passionbet.crt"
#define KEYF  "/passionbet.key"
#define BOOKMAKERID 19751
#define TOKEN "YaNJ9uwq8GHe953XQD"
#define UOF_URL "/unifiedfeed/19751"
#define MTS_NAME "passionbettest_19751"
#define MTS_URL "/passionbettest_19751"
#define MTS_HOSTNAME "integration-mts.betradar.com"
#define MTS_TOKEN "7IdKP1jwq1"
#define SMS_REQUEST "/sys/send.php?login=Atajan&psw=Qwaszx654&sender=PassionBet&phones="
#endif
#if USER == 1
#define MTS_FLAG 1
#define MONGO_URI "mongodb://bet:38998716@192.168.44.24:27017/?authSource=betdb"
#define CERTF  "/passionbet.crt"
#define KEYF  "/passionbet.key"
#define BOOKMAKERID 19751
#define TOKEN "YaNJ9uwq8GHe953XQD"
#define UOF_URL "/unifiedfeed/19751"
#define MTS_NAME "passionbettest_19751"
#define MTS_URL "/passionbettest_19751"
#define MTS_HOSTNAME "integration-mts.betradar.com"
#define MTS_TOKEN "7IdKP1jwq1"
#define SMS_REQUEST "/sys/send.php?login=Atajan&psw=Qwaszx654&sender=PassionBet&phones="
#endif
#if USER == 2
#define MTS_FLAG 2
#define MONGO_URI "mongodb://bet:38998716@192.168.18.123:27017/?authSource=betdb"
#define CERTF  "/gbpremiumcom.crt"
#define KEYF  "/gbpremiumcom.key"
#define BOOKMAKERID 6521
#define TOKEN "poHzp01TAHOWHzeHfz"
#define UOF_URL "/unifiedfeed/6521"
#define MTS_NAME "passionbettest_19751"
#define MTS_URL "/passionbettest_19751"
#define MTS_HOSTNAME "integration-mts.betradar.com"
#define MTS_TOKEN "7IdKP1jwq1"
#define SMS_REQUEST "/sys/send.php?login=greenbet.ru&psw=159874GHwfged&sender=GreenBet&phones="
#endif

#define UPDATE_AND_TRANSLATE 0 // 0 - server mode ; 1 - translate Mongo sports ; 2 - get24HoursFixture ; 3 - translate Mongo tournaments ; 4 - translate Mongo markets ; 5 - translate Mongo competitors; 6 - translate Mongo players; 7 - add new markets to Mongo ; 8 - add new sports to Mongo ; 9 - add new categories/tournamnets to Mongo ; 10 - add new events to Mongo

#define BOOKING 0


#pragma pack(push, 8)
//#pragma pack(pop)
#define LANG_NUM 18;

//zh Chinese(simplified) hr Croatian cz Czech en English fr French ka Georgian de German el Greek it Italian Ja Japanese no Norwegian pl Polish pt Portuguese ro Romanian ru Russian sr Serbian se Swedish tr Turkish



HANDLE hThread7;
DWORD dwThreadID7;
DWORD ExitCode7;
DWORD WINAPI StateFullEvent(LPVOID);



HANDLE hThread2;
DWORD dwThreadID2;
DWORD ExitCode2;
DWORD WINAPI BetradarProcessThread(LPVOID);
DWORD WINAPI SMSProcessThread(LPVOID);
char* generateSmsCode();
char* generatePasswordCode();

HANDLE hThread1;
DWORD dwThreadID1;
DWORD ExitCode1;
DWORD WINAPI BetradarGetThread(LPVOID);

HANDLE hThread5;
DWORD dwThreadID5;
DWORD ExitCode5;
DWORD WINAPI BetsProcessThread(LPVOID);

HANDLE hThread8;
DWORD dwThreadID8;
DWORD ExitCode8;
DWORD WINAPI ClientSMSProcessThread(LPVOID);


HANDLE* hThread3;
DWORD* dwThreadID3;
DWORD ExitCode3;
DWORD WINAPI MTSPublishThread(LPVOID);

HANDLE* hThread9;
DWORD* dwThreadID9;
DWORD ExitCode9;
DWORD WINAPI MTSConsumeThread(LPVOID);



atomic_int run_mts_num = 0;
atomic_int run_num = 0;
atomic_int mts_error[20];
atomic_int64_t recovery_state = -1;
int64_t recovery_timestamp = 0;
//int64_t thread_timestamp;
atomic_int64_t recovery_state_timestamp = 0;
atomic_int64_t https_request_status = 0;
atomic_int mts_disconnect = 0;
void GenerateBigStep();
int* data_step_len_1 = new int[STEP_QUEUE];
int* data_step_len_2 = new int[STEP_QUEUE];
char** array_data_step_1 = new char*[STEP_QUEUE];
char** array_data_step_2 = new char*[STEP_QUEUE];
char** AMQP_message = new char*[AMQP_QUEUE];
atomic_int64_t process_index = 0;
atomic_int64_t bprocess_index = 0;
atomic_int64_t rabbit_index = 0;

volatile atomic_int64_t current_data_step_1 = -1;
volatile atomic_int64_t current_data_step_2 = -1;
volatile int64_t current_data_step_temp_1 = -1;
volatile int64_t current_data_step_temp_2 = -1;

using namespace std;
#ifndef librabbitmq_examples_utils_h
#define librabbitmq_examples_utils_h
#endif


//char* recvbuf;



class Sport {
public:
	Sport();
	~Sport() {
		delete[] name; for (int i = 0; i < translation_num; i++) {
			if (translation_name != nullptr) { if (translation_name[i] != nullptr) delete[] translation_name[i]; translation_name[i] = nullptr; }
		}

		if (translation_name != nullptr) { delete[] translation_name; translation_name = nullptr; }
	};
	int id;
	int sort;
	char *name;
	int translation_num;
	char **translation_name;
	void operator = (const Sport&);
};
void Sport:: operator = (const Sport & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	sort = rhs.sort;
	std::strcpy(name, rhs.name);

	for (int i = 0; i < translation_num; i++) {
		if (translation_name != nullptr) { if (translation_name[i] != nullptr) delete[] translation_name[i]; translation_name[i] = nullptr; }
	}
	if (translation_name != nullptr) { delete[] translation_name; translation_name = nullptr; }
	translation_num = rhs.translation_num;
	if (translation_num > 0) {
		translation_name = new char*[translation_num];
		for (int i = 0; i < translation_num; i++) {
			if (rhs.translation_name[i] != nullptr) { translation_name[i] = new char[strlen(rhs.translation_name[i]) + 1];std::strcpy(translation_name[i], rhs.translation_name[i]); }
			else translation_name[i] = nullptr;

		}

	}
}
Sport::Sport() {
	id = 0;
	sort = 0;
	name = new char[NAME_LENTGH];
	translation_num = LANG_NUM;
	translation_name = new char*[translation_num];
	for (int i = 0; i < translation_num; i++) {
		translation_name[i] = nullptr;
	}
};
class Player {
public:
	Player();
	~Player() {
		if (name != nullptr) delete[] name; if (full_name != nullptr) delete[] full_name; if (type != nullptr) delete[] type; if (nationality != nullptr) delete[] nationality;
		if (country_code != nullptr) delete[] country_code;
		for (int i = 0; i < translation_num; i++) {
			if (translation_type != nullptr) { if (translation_type[i] != nullptr) delete[] translation_type[i]; translation_type[i] = nullptr; }
			if (translation_name != nullptr) { if (translation_name[i] != nullptr) delete[] translation_name[i]; translation_name[i] = nullptr; }
			if (translation_nationality != nullptr) { if (translation_nationality[i] != nullptr) delete[] translation_nationality[i]; translation_nationality[i] = nullptr; }
		}

		if (translation_nationality != nullptr) { delete[] translation_nationality; translation_nationality = nullptr; }
		if (translation_name != nullptr) { delete[] translation_name; translation_name = nullptr; }
		if (translation_type != nullptr) { delete[] translation_type; translation_type = nullptr; }



	};
	int id;
	int translation_num;
	char *name;
	char ** translation_name;
	char ** translation_full_name;
	int date_of_birth;
	int height;
	int weight;
	char* full_name;
	char* type;
	char** translation_type;
	char* nationality;
	char** translation_nationality;
	char* country_code;
	int competitor_id;
	int manager;
	int number;

	void operator = (const Player&);
};
void Player:: operator = (const Player & rhs) {
	int i = 0;
	if (this == &rhs) return;
	id = rhs.id;
	number = rhs.number;
	date_of_birth = rhs.date_of_birth;
	height = rhs.height;
	weight = rhs.weight;
	manager = rhs.manager;
	competitor_id = rhs.competitor_id;
	if (name != nullptr) {
		delete[] name; name = nullptr;
	}
	if (rhs.name != nullptr) {
		i = strlen(rhs.name) + 1;
		name = new char[i]; std::strcpy(name, rhs.name);
	}


	if (full_name != nullptr) {
		delete[] full_name; full_name = nullptr;
	}
	if (rhs.full_name != nullptr) {
		i = strlen(rhs.full_name) + 1;
		full_name = new char[i]; std::strcpy(full_name, rhs.full_name);
	}


	if (type != nullptr) {
		delete[] type; type = nullptr;
	}
	if (rhs.type != nullptr) {
		i = strlen(rhs.type) + 1;
		type = new char[i]; std::strcpy(type, rhs.type);
	}


	if (nationality != nullptr) {
		delete[] nationality; nationality = nullptr;
	}
	if (rhs.nationality != nullptr) {
		i = strlen(rhs.nationality) + 1;
		nationality = new char[i]; std::strcpy(nationality, rhs.nationality);
	}


	if (country_code != nullptr) {
		delete[] country_code; country_code = nullptr;
	}
	if (rhs.country_code != nullptr) {
		i = strlen(rhs.country_code) + 1;
		country_code = new char[i]; std::strcpy(country_code, rhs.country_code);
	}

	for (int i = 0; i < translation_num; i++) {
		if (translation_nationality != nullptr) { if (translation_nationality[i] != nullptr) delete[] translation_nationality[i]; translation_nationality[i] = nullptr; }
		if (translation_type != nullptr) { if (translation_type[i] != nullptr) delete[] translation_type[i]; translation_type[i] = nullptr; }
		if (translation_name != nullptr) { if (translation_name[i] != nullptr) delete[] translation_name[i]; translation_name[i] = nullptr; }
		if (translation_full_name != nullptr) { if (translation_full_name[i] != nullptr) delete[] translation_full_name[i]; translation_full_name[i] = nullptr; }
	}

	if (translation_name != nullptr) { delete[] translation_name; translation_name = nullptr; }
	if (translation_full_name != nullptr) { delete[] translation_full_name; translation_full_name = nullptr; }
	if (translation_type != nullptr) { delete[] translation_type; translation_type = nullptr; }
	if (translation_nationality != nullptr) { delete[] translation_nationality; translation_nationality = nullptr; }

	translation_num = rhs.translation_num;

	if (rhs.translation_num > 0) {
		translation_nationality = new char*[translation_num];
		translation_type = new char*[translation_num];
		translation_name = new char*[translation_num];
		translation_full_name = new char*[translation_num];

		for (int i = 0; i < translation_num; i++) {
			if (rhs.translation_name[i] != nullptr) { translation_name[i] = new char[strlen(rhs.translation_name[i]) + 1];std::strcpy(translation_name[i], rhs.translation_name[i]); }
			else translation_name[i] = nullptr;

			if (rhs.translation_full_name[i] != nullptr) { translation_full_name[i] = new char[strlen(rhs.translation_full_name[i]) + 1];std::strcpy(translation_full_name[i], rhs.translation_full_name[i]); }
			else translation_full_name[i] = nullptr;

			if (rhs.translation_type[i] != nullptr) { translation_type[i] = new char[strlen(rhs.translation_type[i]) + 1];std::strcpy(translation_type[i], rhs.translation_type[i]); }
			else translation_type[i] = nullptr;

			if (rhs.translation_nationality[i] != nullptr) { translation_nationality[i] = new char[strlen(rhs.translation_nationality[i]) + 1];std::strcpy(translation_nationality[i], rhs.translation_nationality[i]); }
			else translation_nationality[i] = nullptr;


		}

	}

}
Player::Player() {
	id = 0;
	name = nullptr;
	date_of_birth = 0;
	height = 0;
	weight = 0;
	full_name = nullptr;
	type = nullptr;
	nationality = nullptr;
	country_code = nullptr;
	competitor_id = 0;
	manager = 0;
	number = 0;
	translation_num = LANG_NUM;
	translation_nationality = new char*[translation_num];
	translation_type = new char*[translation_num];
	translation_name = new char*[translation_num];
	translation_full_name = new char*[translation_num];
	for (int i = 0; i < translation_num; i++) {
		translation_name[i] = nullptr;
		translation_full_name[i] = nullptr;
		translation_type[i] = nullptr;
		translation_nationality[i] = nullptr;
	}

};
class Competitor {
public:
	Competitor();
	~Competitor() {
		if (name != nullptr) delete[] name; if (country_name != nullptr) delete[] country_name;

		for (int i = 0; i < translation_num; i++) {
			if (translation_country_name != nullptr) { if (translation_country_name[i] != nullptr) delete[] translation_country_name[i]; translation_country_name[i] = nullptr; }
			if (translation_name != nullptr) { if (translation_name[i] != nullptr) delete[] translation_name[i]; translation_name[i] = nullptr; }
		}

		if (translation_name != nullptr) { delete[] translation_name; translation_name = nullptr; }
		if (translation_country_name != nullptr) { delete[] translation_country_name; translation_country_name = nullptr; }


	};
	int id;
	int translation_num;
	int sport_id;
	int category_id;
	char *name;
	char** translation_name;
	char *country_name;
	char** translation_country_name;
	int reference_id;
	void operator = (const Competitor&);
};
void Competitor:: operator = (const Competitor & rhs) {
	int i = 0;
	if (this == &rhs) return;
	id = rhs.id;
	sport_id = rhs.sport_id;
	if (rhs.reference_id != 0) reference_id = rhs.reference_id;

	category_id = rhs.category_id;
	if (name != nullptr) {
		delete[] name; name = nullptr;
	}
	if (rhs.name != nullptr) {
		i = strlen(rhs.name) + 1;
		name = new char[i]; std::strcpy(name, rhs.name);
	}

	if (country_name != nullptr) {
		delete[] country_name; country_name = nullptr;
	}
	if (rhs.country_name != nullptr) {
		i = strlen(rhs.country_name) + 1;
		country_name = new char[i]; std::strcpy(country_name, rhs.country_name);
	}

	for (int i = 0; i < translation_num; i++) {
		if (translation_country_name != nullptr) { if (translation_country_name[i] != nullptr) delete[] translation_country_name[i]; translation_country_name[i] = nullptr; }
		if (translation_name != nullptr) { if (translation_name[i] != nullptr) delete[] translation_name[i]; translation_name[i] = nullptr; }
	}

	if (translation_name != nullptr) { delete[] translation_name; translation_name = nullptr; }
	if (translation_country_name != nullptr) { delete[] translation_country_name; translation_country_name = nullptr; }

	translation_num = rhs.translation_num;

	if (rhs.translation_num > 0) {
		translation_country_name = new char*[translation_num];
		translation_name = new char*[translation_num];
		for (int i = 0; i < translation_num; i++) {
			if (rhs.translation_name[i] != nullptr) { translation_name[i] = new char[strlen(rhs.translation_name[i]) + 1];std::strcpy(translation_name[i], rhs.translation_name[i]); }
			else translation_name[i] = nullptr;

			if (rhs.translation_country_name[i] != nullptr) { translation_country_name[i] = new char[strlen(rhs.translation_country_name[i]) + 1];std::strcpy(translation_country_name[i], rhs.translation_country_name[i]); }
			else translation_country_name[i] = nullptr;
		}
	}
}
Competitor::Competitor() {
	id = 0;
	name = nullptr;
	category_id = 0;
	sport_id = 0;
	country_name = nullptr;
	reference_id = 0;
	translation_num = LANG_NUM;
	translation_country_name = new char*[translation_num];
	translation_name = new char*[translation_num];
	for (int i = 0; i < translation_num; i++) {
		translation_name[i] = nullptr;
		translation_country_name[i] = nullptr;
	}

};
class Tournament {
public:
	Tournament();
	~Tournament() {
		if (name != nullptr) delete[] name; if (season_name != nullptr) delete[] season_name; if (next_season_name != nullptr) delete[] next_season_name;
		for (int i = 0; i < translation_num; i++) {
			if (translation_season_name != nullptr) { if (translation_season_name[i] != nullptr) delete[] translation_season_name[i]; translation_season_name[i] = nullptr; }
			if (translation_next_season_name != nullptr) { if (translation_next_season_name[i] != nullptr) delete[] translation_next_season_name[i]; translation_next_season_name[i] = nullptr; }
			if (translation_name != nullptr) { if (translation_name[i] != nullptr) delete[] translation_name[i]; translation_name[i] = nullptr; }
		}

		if (translation_name != nullptr) { delete[] translation_name; translation_name = nullptr; }
		if (translation_season_name != nullptr) { delete[] translation_season_name; translation_season_name = nullptr; }


	};
	int id;
	int season_id;
	int next_season_id;
	int type_radar = 0;//0 sr:tournament //1 sr:race_tournament: //2 sr:simple_tournament: //3 vf:tournament: 
	int sport_id;
	int category_id;
	int sort;
	int translation_num;
	char** translation_name;
	char *name;
	char *season_name;
	char *next_season_name;
	char** translation_season_name;
	char** translation_next_season_name;
	int start_date;
	int end_date;
	void operator = (const Tournament&);
	string getCatKey();
	string getSeasonKey();
	string getNextSeasonKey();
};
void Tournament:: operator = (const Tournament & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	season_id = rhs.season_id;
	next_season_id = rhs.next_season_id;
	start_date = rhs.start_date;
	end_date = rhs.end_date;
	category_id = rhs.category_id;
	sport_id = rhs.sport_id;
	sort = rhs.sort;
	type_radar = rhs.type_radar;
	if (name != nullptr) {
		delete[] name; name = nullptr;
	}
	if (rhs.name != nullptr) {
		name = new char[strlen(rhs.name) + 1];
		std::strcpy(name, rhs.name);
	}
	if (season_name != nullptr) {
		delete[] season_name; season_name = nullptr;
	}
	if (rhs.season_name != nullptr) {
		season_name = new char[strlen(rhs.season_name) + 1];
		std::strcpy(season_name, rhs.season_name);
	}
	if (next_season_name != nullptr) {
		delete[] next_season_name; next_season_name = nullptr;
	}
	if (rhs.next_season_name != nullptr) {
		next_season_name = new char[strlen(rhs.next_season_name) + 1];
		std::strcpy(next_season_name, rhs.next_season_name);
	}

	if (rhs.translation_num > 0) {
		translation_season_name = new char*[translation_num];
		translation_next_season_name = new char*[translation_num];
		translation_name = new char*[translation_num];
		for (int i = 0; i < translation_num; i++) {
			if (rhs.translation_name[i] != nullptr) { translation_name[i] = new char[strlen(rhs.translation_name[i]) + 1];std::strcpy(translation_name[i], rhs.translation_name[i]); }
			else translation_name[i] = nullptr;

			if (rhs.translation_season_name[i] != nullptr) { translation_season_name[i] = new char[strlen(rhs.translation_season_name[i]) + 1];std::strcpy(translation_season_name[i], rhs.translation_season_name[i]); }
			else translation_season_name[i] = nullptr;

			if (rhs.translation_next_season_name[i] != nullptr) { translation_next_season_name[i] = new char[strlen(rhs.translation_next_season_name[i]) + 1]; std::strcpy(translation_next_season_name[i], rhs.translation_next_season_name[i]); }
			else translation_next_season_name[i] = nullptr;
		}
	}

}

Tournament::Tournament() {
	id = 0;
	type_radar = 0;
	category_id = 0;
	sport_id = 0;
	sort = 0;
	next_season_id = 0;
	season_id = 0;
	start_date = 0;
	end_date = 0;
	translation_num = LANG_NUM;
	translation_season_name = new char*[translation_num];
	translation_next_season_name = new char*[translation_num];
	translation_name = new char*[translation_num];
	for (int i = 0; i < translation_num; i++) {
		translation_name[i] = nullptr;
		translation_season_name[i] = nullptr;
		translation_next_season_name[i] = nullptr;
	}

	name = nullptr;
	season_name = nullptr;
};
string Tournament::getCatKey() {

	return to_string(type_radar) + to_string(id);

}

string Tournament::getSeasonKey() {
	return to_string(type_radar) + to_string(season_id);
	
}

string Tournament::getNextSeasonKey() {
	return to_string(type_radar) + to_string(next_season_id);
}


class Category {
public:
	Category();
	~Category() {
		if (name != nullptr) delete[] name; outrights_id.clear();
		for (int i = 0; i < translation_num; i++) {
			if (translation_name != nullptr) { if (translation_name[i] != nullptr) delete[] translation_name[i]; translation_name[i] = nullptr; }
		}

		if (translation_name != nullptr) { delete[] translation_name; translation_name = nullptr; }

	};
	int id;
	int sport_id;
	int sort;
	int translation_num;
	int outrights;
	vector<int> outrights_id;
	char *name;
	char **translation_name;
	void operator = (const Category&);
};
void Category:: operator = (const Category & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	sport_id = rhs.sport_id;
	sort = rhs.sort;
	outrights = rhs.outrights;
	if (name != nullptr) {
		delete[] name; name = nullptr;
	}
	if (rhs.name != nullptr) {
		name = new char[strlen(rhs.name) + 1];
		std::strcpy(name, rhs.name);
	}

	for (int i = 0; i < translation_num; i++) {
		if (translation_name != nullptr) { if (translation_name[i] != nullptr) delete[] translation_name[i]; translation_name[i] = nullptr; }
	}
	if (translation_name != nullptr) { delete[] translation_name; translation_name = nullptr; }
	translation_num = rhs.translation_num;
	if (rhs.translation_num > 0) {
		translation_name = new char*[translation_num];
		for (int i = 0; i < translation_num; i++) {
			if (rhs.translation_name[i] != nullptr) { translation_name[i] = new char[strlen(rhs.translation_name[i]) + 1];std::strcpy(translation_name[i], rhs.translation_name[i]); }
			else translation_name[i] = nullptr;

		}

	}
};
Category::Category() {
	id = 0;
	sport_id = 0;
	sort = 0;
	outrights = 0;
	name = nullptr;
	translation_num = LANG_NUM;
	translation_name = new char*[translation_num];
	for (int i = 0; i < translation_num; i++) {
		translation_name[i] = nullptr;
	}
};
class Event {
public:
	Event();
	~Event() {
		if (home_name != nullptr) delete[] home_name; if (tv_channels != nullptr) delete[] tv_channels; if (venue != nullptr) delete[] venue; if (away_name != nullptr) delete[] away_name;
		if (set_scores != nullptr) delete[] set_scores;  if (match_time != nullptr) delete[] match_time; if (remaining_time != nullptr) delete[] remaining_time; if (remaining_time_in_period != nullptr) delete[] remaining_time_in_period; if (bases != nullptr) delete[] bases;
		if (stoppage_time != nullptr) delete[] stoppage_time; if (stoppage_time_announced != nullptr) delete[] stoppage_time_announced; if (delayed_description != nullptr) delete[] delayed_description;



		for (int i = 0; i < translation_num; i++) {
			if (translation_tv_channels != nullptr) { if (translation_tv_channels[i] != nullptr) delete[] translation_tv_channels[i]; translation_tv_channels[i] = nullptr; }
			if (translation_home_name != nullptr) { if (translation_home_name[i] != nullptr) delete[] translation_home_name[i]; translation_home_name[i] = nullptr; }
			if (translation_away_name != nullptr) { if (translation_away_name[i] != nullptr) delete[] translation_away_name[i]; translation_away_name[i] = nullptr; }
		}

		if (translation_away_name != nullptr) { delete[] translation_away_name; translation_away_name = nullptr; }
		if (translation_home_name != nullptr) { delete[] translation_home_name; translation_home_name = nullptr; }
		if (translation_tv_channels != nullptr) { delete[] translation_tv_channels; translation_tv_channels = nullptr; }
	


	};

	string key;
	int id;
	int position;
	int bo;
	int sport_id;
	int category_id;
	int tournament_id;
	int simple_id;
	int home_id;
	int away_id;
	int winner_id;
	int home_reference_id = 0;
	int away_reference_id = 0;
	int status; //0(not started) / 1(live) / 2(suspended) /	3(ended) / 4(closed) / abandoned - only one of these 6 is possible
	int show;
	int reporting;//
	float home_score;
	float away_score;
	int home_gamescore;
	int away_gamescore;
	char* set_scores;
	char* bases;
	int match_status;
	char* match_time;
	char* remaining_time;
	char* venue;
	char* remaining_time_in_period;
	char* stoppage_time;
	char* stoppage_time_announced;
	int stopped;
	int home_yellowcards;
	int away_yellowcards;
	int home_corners;
	int away_corners;
	int home_yellow_red_cards;
	int away_yellow_red_cards;
	int home_redcards;
	int away_redcards;
	int remaining_reds;
	int current_server;
	int tiebreak;
	int expedite_mode;
	int home_suspend;
	int away_suspend;
	int strikes;
	int balls;
	int outs;
	int home_batter;
	int away_batter;
	int possession;
	int try_num;
	int yards;
	int visit;
	char* tv_channels;
	char** translation_tv_channels;
	int home_legscore;
	int away_legscore;
	int throw_num;
	int delivery;
	int current_ct_team;
	int home_remaining_bowls;
	int away_remaining_bowls;
	int current_end;
	int home_dismissals;
	int away_dismissals;
	int home_penalty_runs;
	int away_penalty_runs;
	int innings;
	int over;
	int translation_num;
	char *home_name;
	char *away_name;
	char ** translation_home_name;
	char ** translation_away_name;
    char* delayed_description;
	int timestamp;
	int start_time;
	int next_live_time;
	int neutral_ground;
	int period_length;
	int overtime_length;
	int austrian_district;
	int booked;
	int type_radar;//0 sr:match// 1 race(sr:stage) // 2 sr:match (simple tournament)//3 vf:match
	int parent_id;
	int delayed_id;
	int bet_stop;
	void operator = (const Event&);
	string getCatKey();
	string getTournamentKey();

};
void Event:: operator = (const Event & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	position = rhs.position;
	match_status = rhs.match_status;
	home_id = rhs.home_id;
	bo = rhs.bo;
	show = rhs.show;
	winner_id = rhs.winner_id;
	away_id = rhs.away_id;
	home_reference_id = rhs.home_reference_id;
	away_reference_id = rhs.away_reference_id;
	status = rhs.status; //0(not started) / 1(live) / 2(suspended) /	3(ended) / 4(closed) / abandoned - only one of these 6 is possible
	reporting = rhs.reporting;//
	home_score = rhs.home_score;
	away_score = rhs.away_score;
	delayed_id = rhs.delayed_id;
	home_corners = rhs.home_corners;
	simple_id = rhs.simple_id;
	away_corners = rhs.away_corners;
	home_yellow_red_cards = rhs.home_yellow_red_cards;
	away_yellow_red_cards = rhs.away_yellow_red_cards;

	home_gamescore = rhs.home_gamescore;
	away_gamescore = rhs.away_gamescore;
	home_legscore = rhs.home_legscore;
	away_legscore = rhs.away_legscore;
	key = rhs.key;

	if (tv_channels != nullptr) {
		delete[] tv_channels; tv_channels = nullptr;
	}
	if (rhs.tv_channels != nullptr) {
		tv_channels = new char[strlen(rhs.tv_channels) + 1];
		std::strcpy(tv_channels, rhs.tv_channels);
	}

	if (delayed_description != nullptr) {
		delete[] delayed_description; delayed_description = nullptr;
	}
	if (rhs.delayed_description != nullptr) {
		delayed_description = new char[strlen(rhs.delayed_description) + 1];
		std::strcpy(delayed_description, rhs.delayed_description);
	}
	if (venue != nullptr) {
		delete[] venue; venue = nullptr;
	}
	if (rhs.venue != nullptr) {
		venue = new char[strlen(rhs.venue) + 1];
		std::strcpy(venue, rhs.venue);
	}

	if (set_scores != nullptr) {
		delete[] set_scores; set_scores = nullptr;
	}
	if (rhs.set_scores != nullptr) {
		set_scores = new char[strlen(rhs.set_scores) + 1];
		std::strcpy(set_scores, rhs.set_scores);
	}

	if (bases != nullptr) {
		delete[] bases; bases = nullptr;
	}
	if (rhs.bases != nullptr) {
		bases = new char[strlen(rhs.bases) + 1];
		std::strcpy(bases, rhs.bases);
	}


	if (match_time != nullptr) {
		delete[] match_time; match_time = nullptr;
	}
	if (rhs.match_time != nullptr) {
		match_time = new char[strlen(rhs.match_time) + 1];
		std::strcpy(match_time, rhs.match_time);
	}

	if (stoppage_time != nullptr) {
		delete[] stoppage_time; stoppage_time = nullptr;
	}
	if (rhs.stoppage_time != nullptr) {
		stoppage_time = new char[strlen(rhs.stoppage_time) + 1];
		std::strcpy(stoppage_time, rhs.stoppage_time);
	}

	if (stoppage_time_announced != nullptr) {
		delete[] stoppage_time_announced; stoppage_time_announced = nullptr;
	}
	if (rhs.stoppage_time_announced != nullptr) {
		stoppage_time_announced = new char[strlen(rhs.stoppage_time_announced) + 1];
		std::strcpy(stoppage_time_announced, rhs.stoppage_time_announced);
	}





	if (remaining_time != nullptr) {
		delete[] remaining_time; remaining_time = nullptr;
	}
	if (rhs.remaining_time != nullptr) {
		remaining_time = new char[strlen(rhs.remaining_time) + 1];
		std::strcpy(remaining_time, rhs.remaining_time);
	}

	if (remaining_time_in_period != nullptr) {
		delete[] remaining_time_in_period; remaining_time_in_period = nullptr;
	}
	if (rhs.remaining_time_in_period != nullptr) {
		remaining_time_in_period = new char[strlen(rhs.remaining_time_in_period) + 1];
		std::strcpy(remaining_time_in_period, rhs.remaining_time_in_period);
	}


	if (away_name != nullptr) {
		delete[] away_name; away_name = nullptr;
	}
	if (rhs.away_name != nullptr) {
		away_name = new char[strlen(rhs.away_name) + 1];
		std::strcpy(away_name, rhs.away_name);
	}


	if (home_name != nullptr) {
		delete[] home_name; home_name = nullptr;
	}
	if (rhs.home_name != nullptr) {
		home_name = new char[strlen(rhs.home_name) + 1];
		std::strcpy(home_name, rhs.home_name);
	}

	for (int i = 0; i < translation_num; i++) {
		if (translation_tv_channels != nullptr) { if (translation_tv_channels[i] != nullptr) delete[] translation_tv_channels[i]; translation_tv_channels[i] = nullptr; }
		if (translation_home_name != nullptr) { if (translation_home_name[i] != nullptr) delete[] translation_home_name[i]; translation_home_name[i] = nullptr; }
		if (translation_away_name != nullptr) { if (translation_away_name[i] != nullptr) delete[] translation_away_name[i]; translation_away_name[i] = nullptr; }
	}

	if (translation_away_name != nullptr) { delete[] translation_away_name; translation_away_name = nullptr; }
	if (translation_home_name != nullptr) { delete[] translation_home_name; translation_home_name = nullptr; }
	if (translation_tv_channels != nullptr) { delete[] translation_tv_channels; translation_tv_channels = nullptr; }

	translation_num = rhs.translation_num;

	if (rhs.translation_num > 0) {
		translation_tv_channels = new char*[translation_num];
		translation_home_name = new char*[translation_num];
		translation_away_name = new char*[translation_num];
		for (int i = 0; i < translation_num; i++) {
			if (rhs.translation_away_name[i] != nullptr) { translation_away_name[i] = new char[strlen(rhs.translation_away_name[i]) + 1];std::strcpy(translation_away_name[i], rhs.translation_away_name[i]); }
			else translation_away_name[i] = nullptr;

			if (rhs.translation_home_name[i] != nullptr) { translation_home_name[i] = new char[strlen(rhs.translation_home_name[i]) + 1];std::strcpy(translation_home_name[i], rhs.translation_home_name[i]); }
			else translation_home_name[i] = nullptr;

			if (rhs.translation_tv_channels[i] != nullptr) { translation_tv_channels[i] = new char[strlen(rhs.translation_tv_channels[i]) + 1];std::strcpy(translation_tv_channels[i], rhs.translation_tv_channels[i]); }
			else translation_tv_channels[i] = nullptr;


		}
	}






	stopped = rhs.stopped;
	home_yellowcards = rhs.home_yellowcards;
	away_yellowcards = rhs.away_yellowcards;
	home_redcards = rhs.home_redcards;
	away_redcards = rhs.away_redcards;
	remaining_reds = rhs.remaining_reds;
	current_server = rhs.current_server;
	tiebreak = rhs.tiebreak;
	expedite_mode = rhs.expedite_mode;
	home_suspend = rhs.home_suspend;
	away_suspend = rhs.away_suspend;
	strikes = rhs.strikes;
	balls = rhs.balls;
	outs = rhs.outs;
	home_batter = rhs.home_batter;
	away_batter = rhs.away_batter;
	possession = rhs.possession;
	try_num = rhs.try_num;
	yards = rhs.yards;
	visit = rhs.visit;
	throw_num = rhs.throw_num;
	delivery = rhs.delivery;
	current_ct_team = rhs.current_ct_team;
	home_remaining_bowls = rhs.home_remaining_bowls;
	away_remaining_bowls = rhs.away_remaining_bowls;
	current_end = rhs.current_end;
	home_dismissals = rhs.home_dismissals;
	away_dismissals = rhs.away_dismissals;
	home_penalty_runs = rhs.home_penalty_runs;
	away_penalty_runs = rhs.away_penalty_runs;
	innings = rhs.innings;
	over = rhs.over;
	booked = rhs.booked;
	timestamp = rhs.timestamp;
	start_time = rhs.start_time;
	next_live_time = rhs.next_live_time;
	type_radar = rhs.type_radar;
	parent_id = rhs.parent_id;
	sport_id = rhs.sport_id;
	category_id = rhs.category_id;
	tournament_id = rhs.tournament_id;
	neutral_ground = rhs.neutral_ground;
	period_length = rhs.period_length;
	overtime_length = rhs.overtime_length;
	austrian_district = rhs.austrian_district;
	bet_stop = rhs.bet_stop;
}
Event::Event() {
	id = 0;
	bo = 0;
	sport_id = 0;
	key = "";
	position = 0;
	category_id = 0;
	tournament_id = 0;
	away_name = nullptr;// new char[NAME_LENTGH];
	home_name = nullptr;// new char[NAME_LENTGH];
	status = -1; //0(not started) / 1(live) / 2(suspended) /	3(ended) / 4(closed) / abandoned - only one of these 6 is possible
	show = 0;
	reporting = 0;//
	home_score = 0;
	away_score = 0;
	home_gamescore = 0;
	away_gamescore = 0;
	away_reference_id = 0;
	home_reference_id = 0;
	away_id = 0;
	home_id = 0;
	bases = nullptr;
	set_scores = nullptr;// new char[MAX_PATH];
	match_status = 0;// new char[64];
	match_time = nullptr;// new char[16];
	remaining_time = nullptr;// new char[16];
	remaining_time_in_period = nullptr;// new char[16];
	stoppage_time = nullptr;
	stoppage_time_announced = nullptr;
	remaining_reds = 0;
	stopped = 0;;
	winner_id = 0;
	home_yellowcards = 0;;
	away_yellowcards = 0;
	home_redcards = 0;
	away_redcards = 0;
	home_corners = 0;
	away_corners = 0;
	home_yellow_red_cards = 0;
	away_yellow_red_cards = 0;
	current_server = 0;
	tiebreak = 0;
	expedite_mode = 0;
	home_suspend = 0;
	away_suspend = 0;
	strikes = 0;
	balls = 0;
	outs = 0;
	home_batter = 0;
	away_batter = 0;
	possession = 0;
	try_num = 0;
	yards = 0;
	visit = 0;
	home_legscore = 0;
	away_legscore = 0;
	throw_num = 0;
	delivery = 0;
	current_ct_team = 0;
	home_remaining_bowls = 0;
	away_remaining_bowls = 0;
	current_end = 0;
	home_dismissals = 0;
	away_dismissals = 0;
	home_penalty_runs = 0;
	away_penalty_runs = 0;
	innings = 0;
	over = 0;
	simple_id = 0;
	timestamp = 0;
	start_time = 0;
	next_live_time = 0;
	neutral_ground = 0;
	period_length = 0;
	overtime_length = 0;
	austrian_district = 0;
	booked = 0;
	type_radar = 0;
	parent_id = 0;
	tv_channels = nullptr;
	venue = nullptr;
	delayed_id = 0;
	delayed_description = nullptr;
	bet_stop = 0;
	translation_num = LANG_NUM;
	translation_tv_channels = new char*[translation_num];
	translation_home_name = new char*[translation_num];
	translation_away_name = new char*[translation_num];
	for (int i = 0; i < translation_num; i++) {
		translation_away_name[i] = nullptr;
		translation_home_name[i] = nullptr;
		translation_tv_channels[i] = nullptr;
	}


};
string Event::getCatKey() {
	if (key.length() == 0) {
		switch (type_radar) {
		case 0:
			key = "0" + to_string(id);
			break;
		case 1:
			key = "1" + to_string(id);
			break;
		case 2:
			key = "0" + to_string(id);
			break;
		case 3:
			key = "3" + to_string(id);
			break;

		};
	}
	return key;
	
}
string Event::getTournamentKey() {
	return to_string(type_radar) + to_string(tournament_id);
}



class Market {
public:
	Market();
	~Market() {
		if (name != nullptr) delete[] name; if (outcome_number > 0) { for (int i = 0; i < outcome_number; i++) if (outcome_name[i] != nullptr) delete[] outcome_name[i]; };
		if (outcome_id != nullptr) delete[] outcome_id; if (outcome_name != nullptr) delete[] outcome_name;
		if (specifier_number > 0) { for (int i = 0; i < specifier_number; i++) if (specifier_name[i] != nullptr) delete[] specifier_name[i]; for (int i = 0; i < specifier_number; i++) if (specifier_description[i] != nullptr) delete[] specifier_description[i]; } if (specifier_type != nullptr) delete[] specifier_type; if (specifier_name != nullptr) delete[] specifier_name;
		if (specifier_description != nullptr) delete[] specifier_description; if (variable_text != nullptr) delete[] variable_text;

		if (translation_name != nullptr) {
			for (int i = 0; i < translation_num; i++) {
				{ if (translation_name[i] != nullptr) delete[] translation_name[i]; translation_name[i] = nullptr; }
			}
			delete[] translation_name; translation_name = nullptr;
		}

		if (translation_outcome_name != nullptr) {
			for (int i = 0; i < translation_num; i++) {
				if (translation_outcome_name[i] != nullptr) {
					for (int j = 0; j < outcome_number; j++) { if (translation_outcome_name[i][j] != nullptr) delete[] translation_outcome_name[i][j]; translation_outcome_name[i][j] = nullptr; }
					delete[] translation_outcome_name[i]; translation_outcome_name[i] = nullptr;
				}
			}
			delete[] translation_outcome_name; translation_outcome_name = nullptr;
		}


	};

	int id;
	//int site_id;
	char* variable_text;
	int variant;
	int translation_num;
	int type;//0 -normal//1-sr:player liveodds:outcometext lo:cricet //2-sr:competitor//3 pre:outcometext 4:// pre:playerprops
	int line_type;//ID_TIP_EVENT SITE
	char* name;
	char** translation_name;
	int outcome_number;
	char** outcome_name;
	char*** translation_outcome_name;
	int* outcome_id;
	char** specifier_name;
	char** specifier_description;
	int* specifier_type;//0 null //1 int //2 string 3://decimal 4//variable	
	int specifier_number;
	void operator = (const Market&);
};
void Market:: operator = (const Market & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	//site_id = rhs.site_id;

	if (outcome_name != nullptr) {
		for (int i = 0; i < outcome_number; i++) if (outcome_name[i] != nullptr) { delete[] outcome_name[i]; outcome_name[i] = nullptr; }
		delete[] outcome_name; outcome_name = nullptr;
	}
	if (outcome_id != nullptr) { delete[] outcome_id; outcome_id = nullptr; }

	if (variable_text != nullptr) {
		delete[] variable_text; variable_text = nullptr;
	}
	if (rhs.variable_text != nullptr) {
		variable_text = new char[strlen(rhs.variable_text) + 1];
		std::strcpy(variable_text, rhs.variable_text);
	}
	outcome_number = rhs.outcome_number;
	type = rhs.type;
	line_type = rhs.line_type;
	variant = rhs.variant;
	if (name != nullptr) {
		delete[] name; name = nullptr;
	}
	if (rhs.name != nullptr) {
		name = new char[strlen(rhs.name) + 1];
		std::strcpy(name, rhs.name);

	}
	outcome_name = new char*[outcome_number];
	outcome_id = new int[outcome_number];

	for (int i = 0; i < outcome_number; i++) {
		outcome_name[i] = new char[strlen(rhs.outcome_name[i]) + 1];
		std::strcpy(outcome_name[i], rhs.outcome_name[i]);
		outcome_id[i] = rhs.outcome_id[i];
	}

	for (int i = 0; i < specifier_number; i++) { if (specifier_name[i] != nullptr) { delete[] specifier_name[i]; specifier_name[i] = nullptr; } if (specifier_description[i] != nullptr) { delete[] specifier_description[i]; specifier_description[i] = nullptr; } }
	if (specifier_name != nullptr) { delete[] specifier_name; specifier_name = nullptr; }
	if (specifier_description != nullptr) { delete[] specifier_description; specifier_description = nullptr; }
	if (specifier_type != nullptr) {
		delete[] specifier_type; specifier_type = nullptr;
	}

	specifier_number = rhs.specifier_number;
	std::strcpy(name, rhs.name);
	specifier_name = new char*[specifier_number];
	specifier_description = new char*[specifier_number];
	specifier_type = new int[specifier_number];

	for (int i = 0; i < specifier_number; i++) {
		if (rhs.specifier_name[i] != nullptr) {
			specifier_name[i] = new char[strlen(rhs.specifier_name[i]) + 1]; std::strcpy(specifier_name[i], rhs.specifier_name[i]);
		}
		else specifier_name[i] = nullptr;
		if (rhs.specifier_description[i] != nullptr) { specifier_description[i] = new char[strlen(rhs.specifier_description[i]) + 1]; std::strcpy(specifier_description[i], rhs.specifier_description[i]); }
		else specifier_description[i] = nullptr;


		specifier_type[i] = rhs.specifier_type[i];
	}

	if (translation_name != nullptr) {
		for (int i = 0; i < translation_num; i++) {
			{ if (translation_name[i] != nullptr) delete[] translation_name[i]; translation_name[i] = nullptr; }
		}
		delete[] translation_name; translation_name = nullptr;
	}

	if (translation_outcome_name != nullptr) {
		for (int i = 0; i < translation_num; i++) {
			if (translation_outcome_name[i] != nullptr) {
				for (int j = 0; j < outcome_number; j++) { if (translation_outcome_name[i][j] != nullptr) delete[] translation_outcome_name[i][j]; translation_outcome_name[i][j] = nullptr; }
				delete[] translation_outcome_name[i]; translation_outcome_name[i] = nullptr;
			}
		}
		delete[] translation_outcome_name; translation_outcome_name = nullptr;
	}

	translation_num = rhs.translation_num;

	if (rhs.translation_num > 0) {
		translation_outcome_name = new char**[translation_num];
		translation_name = new char*[translation_num];
		for (int i = 0; i < translation_num; i++) {
			if (rhs.translation_name[i] != nullptr) { 
				translation_name[i] = new char[strlen(rhs.translation_name[i]) + 1];std::strcpy(translation_name[i], rhs.translation_name[i]);
			
			}
			else translation_name[i] = nullptr;

			if (rhs.translation_outcome_name[i] != nullptr) {
				translation_outcome_name[i] = new char*[outcome_number];
				for (int j = 0; j < outcome_number; j++) if (rhs.translation_outcome_name[i][j] != nullptr) { 
					translation_outcome_name[i][j] = new char[strlen(rhs.translation_outcome_name[i][j]) + 1];std::strcpy(translation_outcome_name[i][j], rhs.translation_outcome_name[i][j]);
				
				}
				else {
					translation_outcome_name[i][j] = nullptr;
				}
			}
			else translation_outcome_name[i] = nullptr;

		}
	}



}
Market::Market() {
	id = 0;
	type = 0;
	line_type = 0;
	variant = -1;
	name = nullptr;
	outcome_number = 0;
	outcome_id = nullptr;
	outcome_name = nullptr;
	specifier_name = nullptr;
	specifier_description = nullptr;
	specifier_type = nullptr;
	specifier_number = 0;
	variable_text = nullptr;
	translation_num = LANG_NUM;
	translation_name = new char*[translation_num];
	translation_outcome_name = new char**[translation_num];
	for (int i = 0; i < translation_num; i++) {
		translation_name[i] = nullptr;
		translation_outcome_name[i] = nullptr;
	}






};
class Line {
public:
	Line();
	~Line() {
		
		if (name != nullptr) delete[] name;  if (outcome_number > 0) { for (int i = 0; i < outcome_number; i++) if (outcome_name[i] != nullptr) delete[] outcome_name[i]; };

		if (outcome_id != nullptr) delete[] outcome_id; if (outcome_active != nullptr) delete[] outcome_active; if (outcome_team != nullptr) delete[] outcome_team; if (outcome_odds != nullptr) delete[] outcome_odds;

		if (outcome_probabilities != nullptr) delete[] outcome_probabilities; if (outcome_name != nullptr) delete[] outcome_name;

		if (specifier_number > 0) { for (int i = 0; i < specifier_number; i++) { if (specifier[i] != nullptr) delete[] specifier[i];  if (specifier_value[i] != nullptr) delete[] specifier_value[i]; } }


		if (extended_specifier_number > 0) { for (int i = 0; i < extended_specifier_number; i++) { if (extended_specifier[i] != nullptr) delete[] extended_specifier[i];  if (extended_specifier_value[i] != nullptr) delete[] extended_specifier_value[i]; } }

		if (specifier != nullptr) delete[] specifier; if (specifier_value != nullptr) delete[] specifier_value;
		if (extended_specifier != nullptr) delete[] extended_specifier; if (extended_specifier_value != nullptr) delete[] extended_specifier_value;


	};
	int id;
	int betstop_reason;
	int tournament_id;
	int season_id;
	int market_id;
	int event_id;
	string key;
	int team;
	int status; //0 (inactive)// 1 (active) //-1(suspended) //- 3 (cleared, settled) //- 4 (cancelled)	//handed_over(-2)
	int favourite;
	int type;//0 -normal liveodds:outcometext //1-sr:player//2-sr:competitor//3 pre:outcometext // 4: pre:playerprops  
	int type_radar;//0 sr:match://1 sr:race_event(sr:stage) //2 sr:simple_tournament://3 sr:tournament://4 sr:race_tournament://5 vf:match  6 //vf:tournament:
	int event_type_radar;
	int variant;
	char* name;
	int outcome_number;
	char** outcome_name;
	int* outcome_id;
	int* outcome_active;
	int* outcome_team;
	float* outcome_probabilities;
	float* outcome_odds;
	char** specifier;
	char** specifier_value;
	char** extended_specifier;
	char** extended_specifier_value;
	int specifier_number;
	int extended_specifier_number;
	int next_betstop;
	void operator = (const Line&);
	string getCatKey();
	string getEventKey();
	string getTournamentKey();
	string getCompoundKey();
};
void Line:: operator = (const Line & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	betstop_reason = rhs.betstop_reason;
	market_id = rhs.market_id;
	event_id = rhs.event_id;
	status = rhs.status;
	favourite = rhs.favourite;
	type = rhs.type;
	type_radar = rhs.type_radar;
	tournament_id = rhs.tournament_id;
	season_id = rhs.season_id;
	variant = rhs.variant;
	next_betstop = rhs.next_betstop;
	for (int i = 0; i < outcome_number; i++) if (outcome_name[i] != nullptr) delete[] outcome_name[i];
	if (outcome_name != nullptr) { delete[] outcome_name; outcome_name = nullptr; }
	if (outcome_id != nullptr) { delete[] outcome_id; outcome_id = nullptr; }
	if (outcome_active != nullptr) { delete[] outcome_active; outcome_active = nullptr; }
	if (outcome_team != nullptr) { delete[] outcome_team; outcome_team = nullptr; }
	if (outcome_probabilities != nullptr) { delete[] outcome_probabilities; outcome_probabilities = nullptr; }
	if (outcome_odds != nullptr) { delete[] outcome_odds; outcome_odds = nullptr; }


	outcome_number = rhs.outcome_number;
	type = rhs.type;
	key = rhs.key;
	if (name != nullptr) {
		delete[] name; name = nullptr;
	}
	if (rhs.name != nullptr) {
		name = new char[strlen(rhs.name) + 1];
		std::strcpy(name, rhs.name);

	}
	outcome_name = new char*[outcome_number];
	outcome_id = new int[outcome_number];
	outcome_active = new int[outcome_number];
	outcome_team = new int[outcome_number];
	outcome_odds = new float[outcome_number];
	outcome_probabilities = new float[outcome_number];

	for (int i = 0; i < outcome_number; i++) {
		outcome_name[i] = new char[strlen(rhs.outcome_name[i]) + 1];
		std::strcpy(outcome_name[i], rhs.outcome_name[i]);
		outcome_id[i] = rhs.outcome_id[i];
		outcome_team[i] = rhs.outcome_team[i];
		outcome_active[i] = rhs.outcome_active[i];
		outcome_probabilities[i] = rhs.outcome_probabilities[i];
		outcome_odds[i] = rhs.outcome_odds[i];
	}

	for (int i = 0; i < specifier_number; i++) { if (specifier[i] != nullptr) delete[] specifier[i]; if (specifier_value[i] != nullptr) delete[] specifier_value[i]; }
	if (specifier != nullptr) { delete[] specifier; specifier = nullptr; }
	if (specifier_value != nullptr) { delete[] specifier_value; specifier_value = nullptr; }



	specifier_number = rhs.specifier_number;
	std::strcpy(name, rhs.name);
	specifier = new char*[specifier_number];
	specifier_value = new char*[specifier_number];

	for (int i = 0; i < specifier_number; i++) {
		if (rhs.specifier[i] != nullptr) {
			specifier[i] = new char[strlen(rhs.specifier[i]) + 1]; std::strcpy(specifier[i], rhs.specifier[i]);
		}
		else specifier[i] = nullptr;
		if (rhs.specifier_value[i] != nullptr) { specifier_value[i] = new char[strlen(rhs.specifier_value[i]) + 1]; std::strcpy(specifier_value[i], rhs.specifier_value[i]); }
		else specifier_value[i] = nullptr;
	}


	extended_specifier_number = rhs.extended_specifier_number;
	std::strcpy(name, rhs.name);
	extended_specifier = new char*[extended_specifier_number];
	extended_specifier_value = new char*[extended_specifier_number];

	for (int i = 0; i < extended_specifier_number; i++) {
		if (rhs.extended_specifier[i] != nullptr) {
			extended_specifier[i] = new char[strlen(rhs.extended_specifier[i]) + 1]; std::strcpy(extended_specifier[i], rhs.extended_specifier[i]);
		}
		else extended_specifier[i] = nullptr;
		if (rhs.extended_specifier_value[i] != nullptr) { extended_specifier_value[i] = new char[strlen(rhs.extended_specifier_value[i]) + 1]; std::strcpy(extended_specifier_value[i], rhs.extended_specifier_value[i]); }
		else extended_specifier_value[i] = nullptr;
	}


}
Line::Line() {
	id = 0;
	betstop_reason = 0;
	tournament_id = 0;
	season_id = 0;
	event_id = 0;
	status = 0;
	favourite = 0;
	type = 0;
	type_radar = 0;
	event_type_radar = 0;
	variant = -1;
	name = nullptr;
	key = "";
	outcome_number = 0;
	outcome_id = nullptr;
	outcome_active = nullptr;
	outcome_team = nullptr;
	outcome_name = nullptr;
	outcome_probabilities = nullptr;
	outcome_odds = nullptr;
	specifier = nullptr;
	extended_specifier = nullptr;
	specifier_value = nullptr;
	extended_specifier_value = nullptr;
	specifier_number = 0;
	extended_specifier_number = 0;
	next_betstop = 0;
	

};
string Line::getCatKey() {
	if (key.length() == 0) {
		//0 sr:match://1 sr:race_event(sr:stage) //2 sr:simple_tournament://3 sr:tournament://4 sr:race_tournament://5 vf:match  6 //vf:tournament:
	switch (type_radar) {

	case 0:	
    	key = "0" + to_string(event_id);
	break;
		
	case 1:
		key = "1" + to_string(event_id);
	break;

	case 2:
		key = "2" + to_string(tournament_id);
	break;

	case 3:
		key = "3" + to_string(tournament_id);
	break;

	case 4:
		key = "4" + to_string(tournament_id);
	break;

	case 5:
		key = "5" + to_string(event_id);
	break;
		
	case 6:
		key = "6" +to_string(tournament_id);
	break;
		
		}
	}
	return  key;
}
string Line::getEventKey() {
		//0 sr:match://1 sr:race_event(sr:stage) //2 sr:simple_tournament://3 sr:tournament://4 sr:race_tournament://5 vf:match  6 //vf:tournament:
		switch (type_radar) {
		case 0:
			return "0" + to_string(event_id);
			break;
		case 1:
			return "1" + to_string(event_id);
			break;
		case 5:
			return "3" + to_string(event_id);
			break;
	}

		std::printf("Error getEventKey in Line::getEventKey type_radar=%d\r\n", type_radar);
	return  "";
}
string Line::getTournamentKey() {
	//0 sr:match://1 sr:race_event(sr:stage) //2 sr:simple_tournament://3 sr:tournament://4 sr:race_tournament://5 vf:match  6 //vf:tournament:
	switch (type_radar) {
	case 0:
		if (event_type_radar == 2 ) return "2" + to_string(tournament_id);
		else return "0" + to_string(tournament_id);
		break;
	case 1:
		return "1" + to_string(tournament_id);
		break;
	case 2:
		return "2" + to_string(tournament_id);
		break;

	case 3:
		return "0" + to_string(tournament_id);
		break;
	
	case 4:
		return "1" + to_string(tournament_id);
		break;
	
	case 5:
		return "3" + to_string(tournament_id);
		break;
	
	case 6:
		return "3" + to_string(tournament_id);
		break;

	}
	return  "";
}
string Line::getCompoundKey() {
	ostringstream key_oss;
	key_oss.str("");  // reset our stream
	key_oss << getCatKey() << ";" << market_id;
	if (specifier_number > 0) {
		key_oss << ";";  // add this only if there are specifiers for the line
		for (int i = 0; i < specifier_number; i++) {
			if (i != 0) key_oss << "&";
			key_oss << specifier_value[i];
		}
	}
	return key_oss.str();
}

class Betstop {
public:
	Betstop();
	~Betstop() { if (description != nullptr) delete[] description; };
	int id;
	char *description;
	void operator = (const Betstop&);
};
void Betstop:: operator = (const Betstop & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	if (description != nullptr) {
		delete[] description; description = nullptr;
	}
	if (rhs.description != nullptr) {
		description = new char[strlen(rhs.description) + 1];
		std::strcpy(description, rhs.description);
	}


}
Betstop::Betstop() {
	id = 0;
	description = nullptr;
};
class Voidreason {
public:
	Voidreason();
	~Voidreason() { if (description != nullptr) delete[] description; };
	int id;
	char *description;
	void operator = (const Voidreason&);
};
void Voidreason:: operator = (const Voidreason & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	if (description != nullptr) {
		delete[] description; description = nullptr;
	}
	if (rhs.description != nullptr) {
		description = new char[strlen(rhs.description) + 1];
		std::strcpy(description, rhs.description);
	}


}
Voidreason::Voidreason() {
	id = 0;
	description = nullptr;
};
class Matchstatus {
public:
	Matchstatus();
	~Matchstatus() { if (description != nullptr) delete[] description; };
	int id;
	char *description;
	void operator = (const Matchstatus&);
};
void Matchstatus:: operator = (const Matchstatus & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	if (description != nullptr) {
		delete[] description; description = nullptr;
	}
	if (rhs.description != nullptr) {
		description = new char[strlen(rhs.description) + 1];
		std::strcpy(description, rhs.description);
	}


}
Matchstatus::Matchstatus() {
	id = 0;
	description = nullptr;
};

#if USER == 0
enum Currency { TMT = 1, RUB = 2, EUR = 3, USD = 4, TRY = 5, VM = 6 };
string currency_name[] = { "TMT", "RUB", "EUR", "USD", "TRY", "VM" };
#endif

#if USER == 1
enum Currency { TMT = 1, RUB = 2, EUR = 3, USD = 4, TRY = 5, VM = 6 };
string currency_name[] = { "TMT", "RUB", "EUR", "USD", "TRY", "VM" };
#endif

#if USER == 2
enum Currency { RUB = 1, EUR = 2, USD = 3, GBP = 4, JPY = 5, CNY = 6, RON = 7, BGN = 8, HUF = 9, TRY = 10, KRW = 11, CZK = 12, KZT = 13, BYN = 14, TMT = 15, INR = 16, PLN = 17, UZS = 18, TJS = 19, KGS = 20, VM = 21 };
string currency_name[] = { "RUB", "EUR", "USD", "GBP", "JPY", "CNY", "RON", "BGN", "HUF", "TRY", "KRW", "CZK", "KZT", "BYN", "TMT", "INR", "PLN", "UZS", "TJS", "KGS", "VM" };
#endif



Event* bevents = new Event[EVENTS_LENTGH];
int bevents_l = 0;
Line* blines = new Line[LINES_LENTGH];
int blines_l = 0;
Sport* bsports = new Sport[SPORTS_LENTGH];
int bsports_l = 0;
Tournament* btournaments = new Tournament[TOURNAMENTS_LENTGH];
int btournaments_l = 0;
Category* bcategories = new Category[CATEGORIES_LENTGH];
int bcategories_l = 0;
Market* bmarkets = new Market[MARKETS_LENGTH];
int bmarkets_l = 0;
Player* bplayers = new Player[PLAYERS_LENTGH];
int bplayers_l = 0;
Competitor* bcompetitors = new Competitor[COMPETITORS_LENTGH];
int bcompetitors_l = 0;
//Event** bevents_id = new Event*[MAX_EVENTS];
Event** bevents_show = new Event*[EVENTS_LENTGH];
unordered_map<string, Event*> bevents_id;
//unordered_map<char*, Event*> bevents_show;
int bevents_show_l = 0;
Line** blines_id = new Line*[MAX_LINES];
//Tournament** btournaments_id = new Tournament*[MAX_TOURNAMENTS];
unordered_map<string, Tournament*> btournaments_id;
unordered_map<string, Tournament*> bseasons_id;
//Tournament** bseasons_id = new Tournament*[MAX_TOURNAMENTS];
//Tournament** bsimples_id = new Tournament*[MAX_TOURNAMENTS];
Category** bcategories_id = new Category*[MAX_CATEGORIES];
Sport** bsports_id = new Sport*[MAX_SPORTS];
Competitor** bcompetitors_id = new Competitor*[MAX_COMPETITORS];
Player** bplayers_id = new Player*[MAX_PLAYERS];
Market*** bmarkets_id = new Market**[MAX_MARKETS];
int *bmax_markets_in = new int[MAX_MARKETS];




int i = 0;


Event* events = new Event[EVENTS_LENTGH];
int events_l = 0;
Line* lines = new Line[LINES_LENTGH];
int lines_l = 0;
Sport* sports = new Sport[SPORTS_LENTGH];
int sports_l = 0;
Tournament* tournaments = new Tournament[TOURNAMENTS_LENTGH];
int tournaments_l = 0;
Category* categories = new Category[CATEGORIES_LENTGH];
int categories_l = 0;
Market* markets = new Market[MARKETS_LENGTH];
int markets_l = 0;
Player* players = new Player[PLAYERS_LENTGH];
int players_l = 0;
Competitor* competitors = new Competitor[COMPETITORS_LENTGH];
int competitors_l = 0;
int matchstatus_l = 0;
//Event** events_id = new Event*[MAX_EVENTS];
unordered_map<string, Event*> events_id;
//unordered_map<char*, Event*> events_show;
Event** events_show = new Event*[EVENTS_LENTGH];
int events_show_l = 0;
Line** lines_id = new Line*[MAX_LINES];
//Tournament** tournaments_id = new Tournament*[MAX_TOURNAMENTS];
unordered_map<string, Tournament*> tournaments_id;
unordered_map<string, Tournament*> seasons_id;
//Tournament** seasons_id = new Tournament*[MAX_TOURNAMENTS];
//Tournament** simples_id = new Tournament*[MAX_TOURNAMENTS];
Category** categories_id = new Category*[MAX_CATEGORIES];
Sport** sports_id = new Sport*[MAX_SPORTS];
Competitor** competitors_id = new Competitor*[MAX_COMPETITORS];
Player** players_id = new Player*[MAX_PLAYERS];
Market*** markets_id = new Market**[MAX_MARKETS];
int *max_markets_in = new int[MAX_MARKETS];

Betstop* betstops = new Betstop[BETSTOPS_LENTGH];
int betstops_l = 0;
Voidreason* voidreasons = new Voidreason[VOIDREASONS_LENTGH];
int voidreasons_l = 0;

Matchstatus* matchstatus = new Matchstatus[MATCHSTATUS_LENTGH];
Betstop** betstops_id = new Betstop*[MAX_BETSTOPS];
Voidreason** voidreasons_id = new Voidreason*[MAX_VOIDREASONS];
Matchstatus** matchstatus_id = new Matchstatus*[MAX_MATCHSTATUS];
string lang[] = { "en", "ru", "ro", "tr", "fr", "it", "de", "pt", "cz", "ja", "zh", "hr", "ka", "el" ,"no", "pl", "sr", "se" };
//string currency[] = { "TMT", "RUB", "EUR", "USD", "TRY", "VM" };

class Bet {
public:
	Bet();
	Bet(Line* line, int bet_outcome_id, float bet_odd);
	~Bet() {

		if (init == 0) return;
	
		if (name != nullptr) delete[] name;  if (outcome_number > 0) { for (int i = 0; i < outcome_number; i++) if (outcome_name[i] != nullptr) delete[] outcome_name[i]; };

		if (outcome_id != nullptr) delete[] outcome_id; if (outcome_active != nullptr) delete[] outcome_active; if (outcome_team != nullptr) delete[] outcome_team; if (outcome_odds != nullptr) delete[] outcome_odds;

		if (outcome_probabilities != nullptr) delete[] outcome_probabilities; if (outcome_name != nullptr) delete[] outcome_name;
		if (outcome_result != nullptr) delete[] outcome_result;
		if (outcome_void_factor != nullptr) delete[] outcome_void_factor;
		if (outcome_dead_heat_factor != nullptr) delete[] outcome_dead_heat_factor;

		if (specifier_number > 0) { for (int i = 0; i < specifier_number; i++) { if (specifier[i] != nullptr) delete[] specifier[i];  if (specifier_value[i] != nullptr) delete[] specifier_value[i]; } }


		if (extended_specifier_number > 0) { for (int i = 0; i < extended_specifier_number; i++) { if (extended_specifier[i] != nullptr) delete[] extended_specifier[i];  if (extended_specifier_value[i] != nullptr) delete[] extended_specifier_value[i]; } }

		if (specifier != nullptr) delete[] specifier; if (specifier_value != nullptr) delete[] specifier_value;
		if (extended_specifier != nullptr) delete[] extended_specifier; if (extended_specifier_value != nullptr) delete[] extended_specifier_value;
		if (tournament_name != nullptr) delete[] tournament_name;
		if (category_name != nullptr) delete[] category_name;
		if (season_name != nullptr) delete[] season_name;
		if (sport_name != nullptr) delete[] sport_name;
		if (event_away_name != nullptr) delete[] event_away_name;
		if (event_home_name != nullptr) delete[] event_home_name;
		if (event_match_time != nullptr) delete[] event_match_time;
		if (event_match_status_description != nullptr) delete[] event_match_status_description;
		if (event_remaining_time != nullptr) delete[] event_remaining_time;
		if (event_remaining_time_in_period != nullptr) delete[] event_remaining_time_in_period;
		if (event_score != nullptr) delete[] event_score;
		if (event_set_scores != nullptr) delete[] event_set_scores;
		if (event_game_score != nullptr) delete[] event_game_score;
		if (summary != nullptr) delete[] summary;
	};
	string id;
	int timeout;
	int status;
	int init;
	int language;
	int counter;
	int line_id;
	int timestamp;
	string ticket_id;
	int selected_outcome_id;
	float place_odd;
	float accept_odd;
	float settlement_odd;
	int tournament_id;
	int season_id;
	int market_id;
	int event_id;
	string key;
	int sport_id;
	int category_id;
	int event_home_id;
	int event_away_id;
	int home_score;
	int away_score;
	int home_gamescore;
	int away_gamescore;
	int team;
	int favourite;
	int type;//0 -normal liveodds:outcometext //1-sr:player//2-sr:competitor//3 pre:outcometext   //4: pre:playerprops   
	int type_radar;//0 sr:match://1 sr:race_event //2 sr:simple_tournament:://3 sr:season: 4//sr:race_tournament
	int event_type_radar;//0 sr:match://1 sr:race_event //2 sr:simple_tournament:://3 sr:season: 4//sr:race_tournament
	int variant;
	char* name;
	int void_reason;
	int certainy;
	int bet_cancel;
	int rollback_bet_cancel;
	int rollback_bet_settlement;
	int start_time;
	int end_time;
	int superceded_by;
	int outcome_number;
	char** outcome_name;
	int* outcome_id;
	int* outcome_active;
	int* outcome_result;
	int* outcome_void_factor;
	int* outcome_dead_heat_factor;
	int* outcome_team;
	float* outcome_probabilities;
	float* outcome_odds;
	char** specifier;
	char** specifier_value;
	char** extended_specifier;
	char** extended_specifier_value;
	int specifier_number;
	int extended_specifier_number;
	char* tournament_name;
	char* category_name;
	char* season_name;
	char* sport_name;
	char* event_away_name;

	char* event_home_name;
	char* event_match_time;
	char* event_remaining_time;
	char* event_remaining_time_in_period;
	char* event_score;
	char* event_set_scores;
	char* event_game_score;
	char* event_match_status_description;
	char* summary;
	int event_match_status;
	int event_status;
	int event_start_time;
	int event_period_length;
	int event_overtime_length;
	int event_bo;
	int event_current_server;
	void operator = (const Bet&);
	void setHistoryData();
	string getCatKey();
	string getEventKey();
	string getTournamentKey();
	string getCompoundKey();
};
void Bet:: operator = (const Bet & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	timeout = rhs.timeout;
	status = rhs.status;
	init = rhs.init;
	if (rhs.init == 0) return;
	market_id = rhs.market_id;
	counter = rhs.counter;
	event_id = rhs.event_id;
	favourite = rhs.favourite;
	timestamp = rhs.timestamp;
	type = rhs.type;
	place_odd = rhs.place_odd;
	tournament_id = rhs.tournament_id;
	variant = rhs.variant;
	outcome_number = rhs.outcome_number;
	void_reason = rhs.void_reason;
	certainy = rhs.certainy;
	bet_cancel = rhs.bet_cancel;
	rollback_bet_settlement = rhs.rollback_bet_settlement;
	rollback_bet_cancel = rhs.rollback_bet_cancel;
	start_time = rhs.start_time;
	end_time = rhs.end_time;
	superceded_by = rhs.superceded_by;
	type_radar = rhs.type_radar;
	event_type_radar = rhs.event_type_radar;
	line_id = rhs.line_id;
	ticket_id = rhs.ticket_id;
	selected_outcome_id = rhs.selected_outcome_id;
	accept_odd = rhs.accept_odd;
	settlement_odd = rhs.settlement_odd;
	season_id = rhs.season_id;
	sport_id = rhs.sport_id;
	category_id = rhs.category_id;
	event_home_id = rhs.event_home_id;
	event_away_id = rhs.event_away_id;
	language = rhs.language;
	event_match_status = rhs.event_match_status;
	event_status = rhs.event_status;
	event_start_time = rhs.event_start_time;
	event_period_length = rhs.event_period_length;
	event_overtime_length = rhs.event_overtime_length;
	event_current_server = rhs.event_current_server;
	event_bo = rhs.event_bo;
	home_score = rhs.home_score;
	away_score = rhs.away_score;
	home_gamescore = rhs.home_gamescore;
	away_gamescore = rhs.away_gamescore;
	key = rhs.key;
	if (name != nullptr) {
		delete[] name; name = nullptr;
	}
	if (rhs.name != nullptr) {
		name = new char[strlen(rhs.name) + 1];
		std::strcpy(name, rhs.name);

	}
	if (tournament_name != nullptr) {
		delete[] tournament_name; tournament_name = nullptr;
	}
	if (rhs.tournament_name != nullptr) {
		tournament_name = new char[strlen(rhs.tournament_name) + 1];
		std::strcpy(tournament_name, rhs.tournament_name);

	}
	if (category_name != nullptr) {
		delete[] category_name; category_name = nullptr;
	}
	if (rhs.category_name != nullptr) {
		category_name = new char[strlen(rhs.category_name) + 1];
		std::strcpy(category_name, rhs.category_name);

	}
	if (season_name != nullptr) {
		delete[] season_name; season_name = nullptr;
	}
	if (rhs.season_name != nullptr) {
		season_name = new char[strlen(rhs.season_name) + 1];
		std::strcpy(season_name, rhs.season_name);

	}
	if (sport_name != nullptr) {
		delete[] sport_name; sport_name = nullptr;
	}
	if (rhs.sport_name != nullptr) {
		sport_name = new char[strlen(rhs.sport_name) + 1];
		std::strcpy(sport_name, rhs.sport_name);

	}
	if (event_away_name != nullptr) {
		delete[] event_away_name; event_away_name = nullptr;
	}
	if (rhs.event_away_name != nullptr) {
		event_away_name = new char[strlen(rhs.event_away_name) + 1];
		std::strcpy(event_away_name, rhs.event_away_name);

	}
	if (event_home_name != nullptr) {
		delete[] event_home_name; event_home_name = nullptr;
	}
	if (rhs.event_home_name != nullptr) {
		event_home_name = new char[strlen(rhs.event_home_name) + 1];
		std::strcpy(event_home_name, rhs.event_home_name);

	}
	if (event_match_time != nullptr) {
		delete[] event_match_time; event_match_time = nullptr;
	}
	if (rhs.event_match_time != nullptr) {
		event_match_time = new char[strlen(rhs.event_match_time) + 1];
		std::strcpy(event_match_time, rhs.event_match_time);

	}
	if (event_remaining_time != nullptr) {
		delete[] event_remaining_time; event_remaining_time = nullptr;
	}
	if (rhs.event_remaining_time != nullptr) {
		event_remaining_time = new char[strlen(rhs.event_remaining_time) + 1];
		std::strcpy(event_remaining_time, rhs.event_remaining_time);

	}
	if (event_remaining_time_in_period != nullptr) {
		delete[] event_remaining_time_in_period; event_remaining_time_in_period = nullptr;
	}
	if (rhs.event_remaining_time_in_period != nullptr) {
		event_remaining_time_in_period = new char[strlen(rhs.event_remaining_time_in_period) + 1];
		std::strcpy(event_remaining_time_in_period, rhs.event_remaining_time_in_period);

	}
	if (event_score != nullptr) {
		delete[] event_score; event_score = nullptr;
	}
	if (rhs.event_score != nullptr) {
		event_score = new char[strlen(rhs.event_score) + 1];
		std::strcpy(event_score, rhs.event_score);

	}
	if (event_set_scores != nullptr) {
		delete[] event_set_scores; event_set_scores = nullptr;
	}
	if (rhs.event_set_scores != nullptr) {
		event_set_scores = new char[strlen(rhs.event_set_scores) + 1];
		std::strcpy(event_set_scores, rhs.event_set_scores);

	}
	if (event_game_score != nullptr) {
		delete[] event_game_score; event_game_score = nullptr;
	}
	if (rhs.event_game_score != nullptr) {
		event_game_score = new char[strlen(rhs.event_game_score) + 1];
		std::strcpy(event_game_score, rhs.event_game_score);

	}
	if (event_match_status_description != nullptr) {
		delete[] event_match_status_description; event_match_status_description = nullptr;
	}
	if (rhs.event_match_status_description != nullptr) {
		event_match_status_description = new char[strlen(rhs.event_match_status_description) + 1];
		std::strcpy(event_match_status_description, rhs.event_match_status_description);

	}
	if (summary != nullptr) {
		delete[] summary; summary = nullptr;
	}
	if (rhs.summary != nullptr) {
		summary = new char[strlen(rhs.summary) + 1];
		std::strcpy(summary, rhs.summary);

	}

	for (int i = 0; i < outcome_number; i++) if (outcome_name[i] != nullptr) delete[] outcome_name[i];
	if (outcome_name != nullptr) { delete[] outcome_name; outcome_name = nullptr; }
	if (outcome_id != nullptr) { delete[] outcome_id; outcome_id = nullptr; }
	if (outcome_result != nullptr) { delete[] outcome_result; outcome_result = nullptr; }
	if (outcome_void_factor != nullptr) { delete[] outcome_void_factor; outcome_void_factor = nullptr; }
	if (outcome_dead_heat_factor != nullptr) { delete[] outcome_dead_heat_factor; outcome_dead_heat_factor = nullptr; }
	if (outcome_active != nullptr) { delete[] outcome_active; outcome_active = nullptr; }
	if (outcome_team != nullptr) { delete[] outcome_team; outcome_team = nullptr; }
	if (outcome_probabilities != nullptr) { delete[] outcome_probabilities; outcome_probabilities = nullptr; }
	if (outcome_odds != nullptr) { delete[] outcome_odds; outcome_odds = nullptr; }


	outcome_name = new char*[outcome_number];
	outcome_id = new int[outcome_number];
	outcome_active = new int[outcome_number];
	outcome_team = new int[outcome_number];
	outcome_odds = new float[outcome_number];
	outcome_probabilities = new float[outcome_number];
	outcome_result = new int[outcome_number];
	outcome_void_factor = new int[outcome_number];
	outcome_dead_heat_factor = new int[outcome_number];


	for (int i = 0; i < outcome_number; i++) {
		outcome_name[i] = new char[strlen(rhs.outcome_name[i]) + 1];
		std::strcpy(outcome_name[i], rhs.outcome_name[i]);
		outcome_id[i] = rhs.outcome_id[i];
		outcome_team[i] = rhs.outcome_team[i];
		outcome_active[i] = rhs.outcome_active[i];
		outcome_probabilities[i] = rhs.outcome_probabilities[i];
		outcome_odds[i] = rhs.outcome_odds[i];
		outcome_result[i] = rhs.outcome_result[i];
		outcome_void_factor[i] = rhs.outcome_void_factor[i];
		outcome_dead_heat_factor[i] = rhs.outcome_dead_heat_factor[i];
	}


	for (int i = 0; i < specifier_number; i++) { if (specifier[i] != nullptr) delete[] specifier[i]; if (specifier_value[i] != nullptr) delete[] specifier_value[i]; }
	if (specifier != nullptr) { delete[] specifier; specifier = nullptr; }
	if (specifier_value != nullptr) { delete[] specifier_value; specifier_value = nullptr; }



	specifier_number = rhs.specifier_number;
	std::strcpy(name, rhs.name);
	specifier = new char*[specifier_number];
	specifier_value = new char*[specifier_number];

	for (int i = 0; i < specifier_number; i++) {
		if (rhs.specifier[i] != nullptr) {
			specifier[i] = new char[strlen(rhs.specifier[i]) + 1]; std::strcpy(specifier[i], rhs.specifier[i]);
		}
		else specifier[i] = nullptr;
		if (rhs.specifier_value[i] != nullptr) { specifier_value[i] = new char[strlen(rhs.specifier_value[i]) + 1]; std::strcpy(specifier_value[i], rhs.specifier_value[i]); }
		else specifier_value[i] = nullptr;
	}


	extended_specifier_number = rhs.extended_specifier_number;
	std::strcpy(name, rhs.name);
	extended_specifier = new char*[extended_specifier_number];
	extended_specifier_value = new char*[extended_specifier_number];

	for (int i = 0; i < extended_specifier_number; i++) {
		if (rhs.extended_specifier[i] != nullptr) {
			extended_specifier[i] = new char[strlen(rhs.extended_specifier[i]) + 1]; std::strcpy(extended_specifier[i], rhs.extended_specifier[i]);
		}
		else extended_specifier[i] = nullptr;
		if (rhs.extended_specifier_value[i] != nullptr) { extended_specifier_value[i] = new char[strlen(rhs.extended_specifier_value[i]) + 1]; std::strcpy(extended_specifier_value[i], rhs.extended_specifier_value[i]); }
		else extended_specifier_value[i] = nullptr;
	}


}
void Bet::setHistoryData() {
	Event* _event = nullptr;
	Tournament* _tournament = nullptr;
	char buff[MAX_PATH];
	char buff_[MAX_PATH];
    switch (type_radar) {

	case 0://sr:match
	case 1://sr:race_event
	case 5://vf:match

		if (bevents_id.find(getEventKey()) == bevents_id.end()) {
			std::printf("event_id=%d  not found in  setHistoryData\r\n", event_id); status = -2;  return;
		}
		_event = bevents_id[getEventKey()];

		if (_event->bet_stop == 1) {
			status = -2;  return;
		}
		if (_event->home_name != nullptr) {
			if (event_home_name != nullptr) { delete[] event_home_name; event_home_name = nullptr; }
			event_home_name = new char[strlen(_event->home_name) + 1];
			std::strcpy(event_home_name, _event->home_name);
		}
		if (_event->away_name != nullptr) {
			if (event_away_name != nullptr) { delete[] event_away_name; event_away_name = nullptr; }
			event_away_name = new char[strlen(_event->away_name) + 1];
			std::strcpy(event_away_name, _event->away_name);
		}
		event_home_id = _event->home_id;
		event_away_id = _event->away_id;
		if (_event->type_radar == 0) {

			if (event_home_id >= MAX_COMPETITORS) std::printf("event_home_id out of MAX_COMPETITORS in setHistoryData %d\r\n", event_home_id);
			else if (bcompetitors_id[event_home_id] == nullptr) {
				std::printf("event_home_id not found in competitors in setHistoryData %d\r\n", event_home_id);


			}
			else {

				if (bcompetitors_id[event_home_id]->name != nullptr) {
					if (event_home_name != nullptr) { delete[] event_home_name; event_home_name = nullptr; }
					event_home_name = new char[strlen(bcompetitors_id[event_home_id]->name) + 1];
					std::strcpy(event_home_name, bcompetitors_id[event_home_id]->name);
				}


			}
			if (event_away_id >= MAX_COMPETITORS) std::printf("event_away_id out of MAX_COMPETITORS in setHistoryData %d\r\n", event_away_id);
			else if (bcompetitors_id[event_away_id] == nullptr) printf("event_away_id not found in competitors in setHistoryData %d\r\n", event_away_id);
			else {

				if (bcompetitors_id[event_away_id]->name != nullptr) {
					if (event_away_name != nullptr) { delete[] event_away_name; event_away_name = nullptr; }
					event_away_name = new char[strlen(bcompetitors_id[event_away_id]->name) + 1];
					std::strcpy(event_away_name, bcompetitors_id[event_away_id]->name);
				}


			}

		}
		
		tournament_id = _event->tournament_id;
		event_type_radar = _event->type_radar;
		event_status = _event->status;
		event_start_time = _event->start_time;
		event_period_length = _event->period_length;
		event_overtime_length = _event->overtime_length;
		event_current_server = _event->current_server;
		event_bo = _event->bo;
		if (event_status > 0) {
			event_match_status = _event->match_status;
			if (matchstatus_id[event_match_status] == nullptr) std::printf("match_status=%d not found in matchstatus_id\r\n", event_match_status); else {
				if (matchstatus_id[event_match_status]->description != nullptr) {
					if (event_match_status_description != nullptr) {
						delete[] event_match_status_description; event_match_status_description = nullptr;
					}
					event_match_status_description = new char[strlen(matchstatus_id[event_match_status]->description) + 1];
					std::strcpy(event_match_status_description, matchstatus_id[event_match_status]->description);
				}
			}


			if (_event->match_time != nullptr) {
				if (event_match_time != nullptr) {
					delete[] event_match_time; event_match_time = nullptr;
				}
				event_match_time = new char[strlen(_event->match_time) + 1];
				std::strcpy(event_match_time, _event->match_time);
			}


			if (_event->remaining_time != nullptr) {
				if (event_remaining_time != nullptr) {
					delete[] event_remaining_time; event_remaining_time = nullptr;
				}
				event_remaining_time = new char[strlen(_event->remaining_time) + 1];
				std::strcpy(event_remaining_time, _event->remaining_time);
			}

			if (_event->remaining_time_in_period != nullptr) {
				if (event_remaining_time_in_period != nullptr) {
					delete[] event_remaining_time_in_period; event_remaining_time_in_period = nullptr;
				}
				event_remaining_time_in_period = new char[strlen(_event->remaining_time_in_period) + 1];
				std::strcpy(event_remaining_time_in_period, _event->remaining_time_in_period);
			}

			home_score = _event->home_score;
			away_score = _event->away_score;

			_itoa(_event->home_score, buff, 10);
			strcpy(buff_, buff);
			strcat(buff_, ":");
			_itoa(_event->away_score, buff, 10);
			strcat(buff_, buff);
			if (event_score != nullptr) {
				delete[] event_score; event_score = nullptr;
			}

			event_score = new char[strlen(buff_) + 1];
			strcpy(event_score, buff_);

			if (_event->set_scores != nullptr) {
				if (event_set_scores != nullptr) { delete[] event_set_scores; event_set_scores = nullptr; }
				event_set_scores = new char[strlen(_event->set_scores) + 1];
				strcpy(event_set_scores, _event->set_scores);
			}

			if (_event->sport_id == 5) {
				home_gamescore = _event->home_gamescore;
				away_gamescore = _event->away_gamescore;

				_itoa(_event->home_gamescore, buff, 10);
				strcpy(buff_, buff);
				strcat(buff_, ":");
				_itoa(_event->away_gamescore, buff, 10);
				strcat(buff_, buff);
				if (event_game_score != nullptr) {
					delete[] event_game_score; event_game_score = nullptr;
				}

				event_game_score = new char[strlen(buff_) + 1];
				strcpy(event_game_score, buff_);
			}


		}
		

    case 2://sr:simple_tournament
	case 3://sr:tournament
	case 4://sr:race_tournament
	case 6://vf:tournament

			//printf("setHistoryData1\r\n");
				
			if (btournaments_id.find(getTournamentKey()) == btournaments_id.end()) printf("tournament_id=%d  type_radar =%d not found in in setHistoryData \r\n", tournament_id, type_radar);
			else {
				_tournament = btournaments_id[getTournamentKey()];
				if (type_radar == 2 || type_radar == 3 || type_radar == 4 || type_radar == 6) {
					event_start_time = _tournament->end_date;
					event_id = tournament_id;
				}
				if (_tournament->category_id >= MAX_CATEGORIES) printf("category_id=%d out of  MAX_CATEGORIES in in setHistoryData\r\n", _tournament->category_id);
				else if (bcategories_id[_tournament->category_id] == nullptr) printf("tournament_id=%d  not found in in setHistoryData\r\n", _tournament->category_id);
				else {
					category_id = _tournament->category_id;
					if (bcategories_id[category_id]->name != nullptr) {
						if (category_name != nullptr) { delete[] category_name; category_name = nullptr; }
						category_name = new char[strlen(bcategories_id[category_id]->name) + 1];
						std::strcpy(category_name, bcategories_id[category_id]->name);
					}

				}
				if (_tournament->name != nullptr) {
					if (tournament_name != nullptr) { delete[] tournament_name; tournament_name = nullptr; }
					tournament_name = new char[strlen(_tournament->name) + 1];
					std::strcpy(tournament_name, _tournament->name);
				}
				if (season_id == 0) season_id = _tournament->season_id;
				if (season_id != 0 && season_id == _tournament->season_id && _tournament->season_name != nullptr) {
					if (season_name != nullptr) { delete[] season_name; season_name = nullptr; }
					season_name = new char[strlen(_tournament->season_name) + 1];
					std::strcpy(season_name, _tournament->season_name);
				}


				if (_tournament->sport_id >= MAX_SPORTS) printf("sport_id=%d out of MAX_SPORTS in in setHistoryData\r\n", _tournament->sport_id);
				else if (bsports_id[_tournament->sport_id] == nullptr) printf("sport_id=%d  not found in in setHistoryData\r\n", _tournament->sport_id);
				else {
					sport_id = _tournament->sport_id;
					if (bsports_id[sport_id]->name != nullptr) {
						if (sport_name != nullptr) { delete[] sport_name; sport_name = nullptr; }
						sport_name = new char[strlen(bsports_id[sport_id]->name) + 1];
						std::strcpy(sport_name, bsports_id[sport_id]->name);
					}
				};
			}


			break;


	

	default:

		std::printf("error in type_radar=%d setHistoryData", type_radar);

		break;


	}


};
Bet::Bet() {
	id = "";
	init = 1;
	timeout = 0;
	status = 0;
	language = 0;
	event_bo = 0;
	home_score = 0;
	away_score = 0;
	home_gamescore = 0;
	away_gamescore = 0;
	line_id = 0;
	ticket_id = "";
	counter = 0;
	timestamp = 0;
	selected_outcome_id = -1;
	tournament_id = 0;
	simple_id = 0;
	season_id = 0;
	market_id = 0;
	event_id = 0;
	sport_id = 0;
	category_id = 0;
	event_home_id = 0;
	event_away_id = 0;
	place_odd = 0;
	accept_odd = 0;
	settlement_odd = 0;
	team = 0;
	favourite = 0;
	type = 0;//0 -normal liveodds:outcometext //1-sr:player//2-sr:competitor//3 pre:outcometext //4: pre:playerprops 
	type_radar = 0;//0 sr:match://1 sr:race_event //2 sr:simple_tournament:://3 sr:season:
	variant = 0;
	void_reason = 0;
	certainy = 0;
	bet_cancel = 0;
	rollback_bet_cancel = 0;
	rollback_bet_settlement = 0;
	start_time = 0;
	end_time = 0;
	superceded_by = 0;
	key = "";
	name = nullptr;
	outcome_number = 0;
	outcome_name = nullptr;
	outcome_id = nullptr;
	outcome_active = nullptr;
	outcome_team = nullptr;
	outcome_probabilities = nullptr;
	outcome_odds = nullptr;
	outcome_result = nullptr;
	outcome_void_factor = nullptr;
	outcome_dead_heat_factor = nullptr;
	specifier = nullptr;
	specifier_value = nullptr;
	extended_specifier = nullptr;
	extended_specifier_value = nullptr;
	specifier_number = 0;
	extended_specifier_number = 0;
	tournament_name = nullptr;
	category_name = nullptr;
	season_name = nullptr;
	sport_name = nullptr;
	event_away_name = nullptr;
	event_home_name = nullptr;
	event_match_time = nullptr;
	event_remaining_time = nullptr;
	event_remaining_time_in_period = nullptr;
	event_score = nullptr;
	event_set_scores = nullptr;
	event_game_score = nullptr;
	event_match_status_description = nullptr;
	summary = nullptr;
	event_match_status = 0;
	event_status = 0;
	event_start_time = 0;
	event_period_length = 0;
	event_overtime_length = 0;
	event_current_server = 0;


};
Bet::Bet(Line* line, int  bet_outcome_id, float bet_odd) {
	init = 0;
	outcome_name = nullptr;
	outcome_id = nullptr;
	outcome_active = nullptr;
	outcome_team = nullptr;
	outcome_probabilities = nullptr;
	outcome_odds = nullptr;
	outcome_result = nullptr;
	outcome_void_factor = nullptr;
	outcome_dead_heat_factor = nullptr;
	tournament_name = nullptr;;
	category_name = nullptr;;
	season_name = nullptr;;
	sport_name = nullptr;
	event_away_name = nullptr;
	event_home_name = nullptr;
	event_match_time = nullptr;
	event_remaining_time = nullptr;
	event_remaining_time_in_period = nullptr;;
	event_score = nullptr;
	event_set_scores = nullptr;;
	event_game_score = nullptr;
	event_match_status_description = nullptr;
	summary = nullptr;
	specifier = nullptr;
	specifier_value = nullptr;

	if (line == nullptr) { std::printf("error line is null\r\n"); status = -1; return; }
	if (line->status != 1) { std::printf("error line status is=%d\r\n", line->status); status = -2; return; }
	id = "";
	ticket_id = "";
	selected_outcome_id = -1;
	line_id = line->id;
	status = 0;
	timeout = 0;
	timestamp = 0;
	settlement_odd = 0;
	home_score = 0;
	away_score = 0;
	home_gamescore = 0;
	away_gamescore = 0;
	counter = 0;
	place_odd = bet_odd;
	market_id = line->market_id;
	event_id = line->event_id;
	//if (event_id >= MAX_EVENTS) { std::printf("event_id out of MAX_EVENTS in build Bet event_id =%d\r\n", event_id); status = -2; return; }
	if (market_id >= MAX_MARKETS) { std::printf("market_id out of MAX_MARKETS in build Bet market_id =%d\r\n", market_id); status = -2; return; }
	init = 1;
	favourite = line->favourite;
	type = line->type;
	tournament_id = line->tournament_id;
	variant = line->variant;
	simple_id = line->simple_id;
	outcome_number = line->outcome_number;
	type_radar = line->type_radar;
	season_id = line->season_id;
	sport_id = 0;
	category_id = 0;
	event_home_id = 0;
	event_away_id = 0;
	event_match_status = 0;
	event_status = 0;
	event_start_time = 0;
	event_period_length = 0;
	event_overtime_length = 0;
	event_bo = 0;
	void_reason = 0;
	certainy = 0;
	bet_cancel = 0;
	rollback_bet_cancel = 0;
	rollback_bet_settlement = 0;
	start_time = 0;
	end_time = 0;
	superceded_by = 0;
	key = line->key;
	
	if (line->name != nullptr) {
		name = new char[strlen(line->name) + 1];
		std::strcpy(name, line->name);
	}
	else name = nullptr;

	//for (int i = 0; i < outcome_number; i++) if (outcome_name[i] != nullptr) delete[] outcome_name[i];
	

	outcome_name = new char*[outcome_number];
	outcome_id = new int[outcome_number];
	outcome_active = new int[outcome_number];
	outcome_team = new int[outcome_number];
	outcome_odds = new float[outcome_number];
	outcome_probabilities = new float[outcome_number];
	outcome_result = new int[outcome_number];
	outcome_void_factor = new int[outcome_number];
	outcome_dead_heat_factor = new int[outcome_number];;

	for (int i = 0; i < outcome_number; i++) {
		outcome_name[i] = new char[strlen(line->outcome_name[i]) + 1];
		std::strcpy(outcome_name[i], line->outcome_name[i]);
		outcome_id[i] = line->outcome_id[i];
		if (outcome_id[i] == bet_outcome_id) { selected_outcome_id = i; accept_odd = line->outcome_odds[i]; }
		outcome_team[i] = line->outcome_team[i];
		outcome_active[i] = line->outcome_active[i];
		outcome_probabilities[i] = line->outcome_probabilities[i];
		outcome_odds[i] = line->outcome_odds[i];
		outcome_dead_heat_factor[i] = 0;
		outcome_void_factor[i] = 0;
		outcome_result[i] = 0;

	}





	specifier_number = line->specifier_number;
	std::strcpy(name, line->name);
	specifier = new char*[specifier_number];
	specifier_value = new char*[specifier_number];

	for (int i = 0; i < specifier_number; i++) {
		if (line->specifier[i] != nullptr) {
			specifier[i] = new char[strlen(line->specifier[i]) + 1]; std::strcpy(specifier[i], line->specifier[i]);
		}
		else specifier[i] = nullptr;
		if (line->specifier_value[i] != nullptr) { specifier_value[i] = new char[strlen(line->specifier_value[i]) + 1]; std::strcpy(specifier_value[i], line->specifier_value[i]); }
		else specifier_value[i] = nullptr;
	}



	extended_specifier_number = line->extended_specifier_number;
	std::strcpy(name, line->name);
	extended_specifier = new char*[extended_specifier_number];
	extended_specifier_value = new char*[extended_specifier_number];

	for (int i = 0; i < extended_specifier_number; i++) {
		if (line->extended_specifier[i] != nullptr) {
			extended_specifier[i] = new char[strlen(line->extended_specifier[i]) + 1]; std::strcpy(extended_specifier[i], line->extended_specifier[i]);
		}
		else extended_specifier[i] = nullptr;
		if (line->extended_specifier_value[i] != nullptr) { extended_specifier_value[i] = new char[strlen(line->extended_specifier_value[i]) + 1]; std::strcpy(extended_specifier_value[i], line->extended_specifier_value[i]); }
		else extended_specifier_value[i] = nullptr;
	}
	if (selected_outcome_id == -1) { std::printf("error bet_outcome_id =%d not found in this line\r\n", bet_outcome_id); status = -5; return; }
	if (place_odd > accept_odd) status = -6;
	if (place_odd < accept_odd) status = -7;
	setHistoryData();
}

string Bet::getCatKey() {
	if (key.length() == 0) {
		//0 sr:match://1 sr:race_event(sr:stage) //2 sr:simple_tournament://3 sr:season(tournament): //4 sr:race_tournament://5 vf:match 6 //vf:tournament:
		switch (type_radar) {

		case 0:
			key = "0" + to_string(event_id);
			break;

		case 1:
			key = "1" + to_string(event_id);
			break;

		case 2:
			key = "2" + to_string(simple_id);
			break;

		case 3:
			key = "3" + to_string(tournament_id);
			break;

		case 4:
			key = "4" + to_string(tournament_id);
			break;

		case 5:
			key = "5" + to_string(event_id);
			break;

		case 6:
			key = "6" + to_string(tournament_id);
			break;

		}
	}
	return  key;
}
string Bet::getEventKey() {
	//0 sr:match://1 sr:race_event(sr:stage) //2 sr:simple_tournament://3 sr:tournament://4 sr:race_tournament://5 vf:match  6 //vf:tournament:
	switch (type_radar) {
	case 0:
		return "0" + to_string(event_id);
		break;
	case 1:
		return "1" + to_string(event_id);
		break;
	case 5:
		return "3" + to_string(event_id);
		break;
	}

	std::printf("Error getEventKey in Line::getEventKey type_radar=%d\r\n", type_radar);
	return  "";
}
string Bet::getTournamentKey() {
	//0 sr:match://1 sr:race_event(sr:stage) //2 sr:simple_tournament://3 sr:tournament://4 sr:race_tournament://5 vf:match  6 //vf:tournament:
	switch (type_radar) {
	case 0:
		if (event_type_radar == 2) return "2" + to_string(tournament_id);
		else return "0" + to_string(tournament_id);
		break;
	case 1:
		return "1" + to_string(tournament_id);
		break;
	case 2:
		return "2" + to_string(tournament_id);
		break;

	case 3:
		return "0" + to_string(tournament_id);
		break;

	case 4:
		return "1" + to_string(tournament_id);
		break;

	case 5:
		return "3" + to_string(tournament_id);
		break;

	case 6:
		return "3" + to_string(tournament_id);
		break;

	}
	return  "";
}
string Bet::getCompoundKey() {
	ostringstream key_oss;
	key_oss.str("");  // reset our stream
	key_oss << getCatKey() << ";" << market_id;
	if (specifier_number > 0) {
		key_oss << ";";  // add this only if there are specifiers for the line
		for (int i = 0; i < specifier_number; i++) {
			if (i != 0) key_oss << "&";
			key_oss << specifier_value[i];
		}
	}
	return key_oss.str();
}
// izzet: test commmit
class Ticket {
public:
	Ticket();
	~Ticket() {
		if (bets_id != nullptr) delete bets_id;  if (bets != nullptr) { for (int i = 0; i < bets_number; i++)  if (bets[i] != nullptr) delete bets[i]; delete[] bets; }
		if (mts_message != nullptr) delete[] mts_message;
	};
	string id;
	string mts_id;
	string domain;
	int client_id;
	int currency;
	int freebet;
	int counter;
	int contact_oam;
	int device;
	bool is_live;
	int timeout;
	int status;// 0 initiate //1 accepted //calculated 
	int action;//0 cupon //1 expressday //2 expresslife //3 freebet
	int64_t timestamp;
	int bets_number;
	int* bets_id;
	Bet** bets;
	int system_selected;
	int type;//1 ordinar //2 express //3 system
	double coeff;//1 ordinar //2 express coef //3 system coef
	double coeff_settlement;//1 ordinar //2 express сoef //3 system coef
	double stake;
	int alternative_stake;
	atomic_int alternative_process;
	int reoffer_stake;
	int reoffer_count;
	int alternative_count;
	double payout;
	double returned;
	double bonus;
	double coeff_bonus;
	bool any_coeff;
	bool alternative;
	int accept_code;//-3 баланс //- 6 -7 - odds change //-1 mts published error
	int mts;
	int language;
	char* mts_message;
	void operator = (const Ticket&);
	void generateId(int, int, int);
};
void Ticket:: operator = (const Ticket & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	is_live = rhs.is_live;
	contact_oam = rhs.contact_oam;
	counter = rhs.counter;
	mts_id = rhs.mts_id;
	currency = rhs.currency;
	domain = rhs.domain;
	language = rhs.language;
	client_id = rhs.client_id;
	mts = rhs.mts;
	timeout = rhs.timeout;
	freebet = rhs.freebet;
	status = rhs.status;// 0 initiate //1 accepted //calculated 
	timestamp = rhs.timestamp;
	for (int i = 0; i< bets_number; i++)  if (bets[i] != nullptr) delete bets[i]; if (bets != nullptr) delete[] bets;
	bets_number = rhs.bets_number;
	if (mts_message != nullptr) delete[] mts_message;
	mts_message = nullptr;
	if (rhs.mts_message != nullptr) {
		mts_message = new char[strlen(rhs.mts_message) + 1];
		strcpy(mts_message, rhs.mts_message);
	}

	if (bets_id != nullptr) delete[] bets_id;
	if (bets_number > 0) bets_id = new int[bets_number];
	for (int i = 0; i < bets_number; i++) bets_id[i] = rhs.bets_id[i];
	if (bets_number > 0) bets = new Bet*[bets_number];
	for (int i = 0; i < bets_number; i++) bets[i] = rhs.bets[i];
	system_selected = rhs.system_selected;
	type = rhs.type;//1 ordinar //2 express //3 system
	coeff = rhs.coeff;//1 ordinar //2 express сoef //3 system сoef
	coeff_settlement = rhs.coeff_settlement;//1 ordinar //2 express сoef //3 system сoef
	stake = rhs.stake;
	alternative_stake = rhs.alternative_stake;
	alternative_count = rhs.alternative_count;
	reoffer_stake = rhs.reoffer_stake;
	reoffer_count = rhs.reoffer_count;
	payout = rhs.payout;
	returned = rhs.returned;
	bonus = rhs.bonus;
	coeff_bonus = rhs.coeff_bonus;
	any_coeff = rhs.any_coeff;
	action = rhs.action;
	accept_code = rhs.accept_code;
}
Ticket::Ticket() {
	id = "";
	client_id = 0;
	is_live = false;
	counter = 0;
	contact_oam = 0;
	timeout = 0;
	currency = 0;
	freebet = 0;
	status = 0;
	alternative_process = 0;
	timestamp = 0;
	bets_number = 0;
	bets_id = nullptr;
	bets = nullptr;
	system_selected = 0;
	type = 0;
	coeff = 0;
	coeff_settlement = 0;
	stake = 0;
	alternative_stake = 0;
	alternative_count = 0;
	reoffer_stake = 0;
	reoffer_count = 0;
	payout = 0;
	returned = 0;
	bonus = 0;
	coeff_bonus = 0;
	domain = "";
	language = 0;
	any_coeff = false;
	alternative = true;
	action = 0;
	accept_code = 0;
	mts = 0;
	mts_id = "";
	mts_message = nullptr;
};
void Ticket::generateId(int socket, int user, int index) {
	char* mtsid = new char[MAX_PATH];
	char* time_buf = new char[65];
	//strcpy(mtsid, "c");
	//_itoa(client_id, time_buf, 10);
	//strcat(mtsid, time_buf);
	strcpy(mtsid, "t");
	_i64toa(timestamp, time_buf, 10);
	strcat(mtsid, time_buf);
	strcat(mtsid, "s");
	_itoa(socket, time_buf, 10);
	strcat(mtsid, time_buf);
	strcat(mtsid, "r");
	_itoa(user, time_buf, 10);
	strcat(mtsid, time_buf);
	strcat(mtsid, "i");
	_itoa(index, time_buf, 10);
	strcat(mtsid, time_buf);

	mts_id = mtsid;
	delete[] mtsid;
	delete[] time_buf;
}

Ticket** tickets_contact_oam = new Ticket*[MAX_OAM];
atomic_int tickets_contact_oam_count = 0;
atomic_int tickets_contact_oam_count_read = 0;
class wsClient {
public:
	wsClient(int _socket, SSL* _ssl, in_addr _addr) {
		socket = _socket;
		ssl = _ssl;
		init = 0;
		sms_counter = 0;
		message_buffer.clear();
		ready_state = WS_READY_STATE_CONNECTING;
		last_recv_time = time(nullptr);
		ping_sent_time = 0;
		close_status = 0;
		addr = _addr;
		https_buffer_length = 0;
		https_write_buffer_length = 0;
		frame_payload_data_length = 0;
		frame_bytes_read = 0;
		frame_buffer.clear();
		message_opcode = 0;
		message_buffer_length = 0;
		message_queue = new char*[QUEUE_LENGTH];
		message_queue_length = new int[QUEUE_LENGTH];
		for (int i = 0; i < QUEUE_LENGTH; i++) { message_queue[i] = nullptr; message_queue_length[i] = 0; }

		bet_message_queue = new char*[QUEUE_LENGTH];
		bet_message_queue_length = new int[QUEUE_LENGTH];
		for (int i = 0; i < QUEUE_LENGTH; i++) { bet_message_queue[i] = nullptr; bet_message_queue_length[i] = 0; }

		mts_process = 0;
		mts_send_process = 0;
		message_ping = nullptr;
		message_pong = nullptr;
		message_close = nullptr;
		https_buffer = nullptr;
		options = nullptr;
		https_write_buffer = nullptr;
		https_write_buffer_length = 0;
		https_time = 0;
		message_ping_length = 0;
		message_pong_length = 0;
		message_close_length = 0;
		plus_message_length = 0;
		outright_message_length = 0;
		outright = 0;
		outright_request_id = 0;
		outright_create = false;
		outright_send = false;
		outright_message = nullptr;
		plus = "";
		plus_request_id = 0;
		handshake_message = nullptr;
		plus_message = nullptr;
		last_message_queue = 0;
		last_message_queue_socket = 0;
		last_bet_message_queue = 0;
		last_bet_message_queue_socket = 0;
		step_buffer_1 = nullptr;
		step_buffer_2 = nullptr;
		current1 = -1;
		current2 = -1;
		step_buffer_len_2 = -1;
		step_buffer_len_1 = -1;
		plus_create = false;
		plus_send = false;
		timestamp = 0;
		client_send = false;
		client_id = -1;
		send_client_message = nullptr;
		recv_client_message_queue = 0;
		recv_client_message_thread_queue = 0;
		send_client_message_length = 0;
		recv_client_message = new char*[RECV_MAX_CLIENT_QUEUE];
		recv_client_message_length = new int[RECV_MAX_CLIENT_QUEUE];
		for (int i = 0; i < RECV_MAX_CLIENT_QUEUE; i++) { recv_client_message[i] = nullptr; recv_client_message_length[i] = 0; }
		send_ticket_message = nullptr;;
		recv_ticket_message = nullptr;
		recv_ticket_message_length = 0;
		send_ticket_message_length = 0;
		tickets = nullptr;
		ticket_send = false;
		ticket_process = false;
		tickets_number = 0;
		ticket_request_id = 0;


		//flag = 0;

	}
	~wsClient() {
		for (int i = 0; i < RECV_MAX_CLIENT_QUEUE; i++)  if (recv_client_message[i] != nullptr) delete[] recv_client_message[i];
		delete[] recv_client_message; delete[] recv_client_message_length;
		if (send_client_message != nullptr) delete[] send_client_message;
		for (int i = 0; i < QUEUE_LENGTH; i++)  if (message_queue[i] != nullptr) delete[] message_queue[i];
		delete[] message_queue; delete[] message_queue_length;
		for (int i = 0; i < QUEUE_LENGTH; i++)  if (bet_message_queue[i] != nullptr) delete[] bet_message_queue[i];
		delete[] bet_message_queue; delete[] bet_message_queue_length;
		if (message_ping != nullptr) delete[] message_ping;  if (message_pong != nullptr) delete[] message_pong;
		if (message_close != nullptr) delete[] message_close;
		if (https_buffer != nullptr) delete[] https_buffer;
		if (https_write_buffer != nullptr) delete[] https_write_buffer;
		if (handshake_message != nullptr) delete[] handshake_message;
		if (options != nullptr) delete[] options;
		if (plus_message != nullptr) delete[] plus_message;
		if (outright_message != nullptr) delete[] outright_message;
		if (send_ticket_message != nullptr) delete[] send_ticket_message;
		if (recv_ticket_message != nullptr) delete[] recv_ticket_message;
		if (tickets != nullptr) { for (int i = 0; i < tickets_number; i++)  if (tickets[i] != nullptr) delete tickets[i];  delete tickets; }
		//step_buffer_1 = nullptr;
		//step_buffer_2 = nullptr;
		//if (step_buffer_1 != nullptr) delete[] step_buffer_1;
		//if (step_buffer_2 != nullptr) delete[] step_buffer_2;

	}

	int socket;                            // client socket
	SSL* ssl;                              //client ssl 
	string message_buffer;                  // a blank string when there's no incoming frames
	int ready_state;                        // between 0 and 3
	time_t last_recv_time;                   // set to time() when the client is added
	time_t ping_sent_time;                   // 0 when the server is not waiting for a pong
	int close_status;                       // close status that wsOnClose() will be called with
	in_addr addr;
	size_t frame_payload_data_length;         // length of a frame's payload data.
	int frame_bytes_read;                    // amount of bytes read for a frame, reset to 0 when all frame data has been read
	string frame_buffer;                    // joined onto end as a frame's data comes in, reset to blank string when all frame data has been read
	unsigned char message_opcode;           // stored by the first frame for fragmented messages, default value is 0
	size_t message_buffer_length;            // the payload data length of message_buffer
	int* message_queue_length;
	char** message_queue;
	int* bet_message_queue_length;
	char** bet_message_queue;
	string sms;
	int https_buffer_length;
	atomic_int https_write_buffer_length;
	int sms_counter;
	atomic_int64_t init;
	atomic_int64_t last_message_queue;
	atomic_int64_t last_message_queue_socket;
	atomic_int64_t last_bet_message_queue;
	atomic_int64_t last_bet_message_queue_socket;
	string plus;
	int plus_request_id;
	std::atomic<bool> plus_create;
	std::atomic<bool> plus_send;
	atomic_int mts_process;
	int mts_send_process;
	atomic_int64_t timestamp;
	int https_time;
	char* message_ping;
	char* message_pong;
	char* message_close;
	char* options;
	int message_ping_length;
	int message_pong_length;
	int message_close_length;
	int plus_message_length;
	char* handshake_message;
	char* plus_message;
	char* https_buffer;
	char* https_write_buffer;
	char* step_buffer_1;
	char* step_buffer_2;
	int step_buffer_len_1;
	int step_buffer_len_2;
	int current1;
	int current2;
	int outright_message_length;
	int outright = 0;
	int outright_request_id = 0;
	int ticket_request_id = 0;
	std::atomic<bool> outright_create;
	std::atomic<bool> outright_send;
	char* outright_message;

	char* send_client_message;
	char** recv_client_message;
	int* recv_client_message_length;
	int send_client_message_length;


	int client_id;
	std::atomic<bool> client_send;
	atomic_int64_t recv_client_message_queue;
	atomic_int64_t recv_client_message_thread_queue;


	char* send_ticket_message;
	char* recv_ticket_message;
	int recv_ticket_message_length;
	int send_ticket_message_length;
	Ticket** tickets;
	int tickets_number;
	//int type;
	std::atomic<bool> ticket_send;
	std::atomic<bool> ticket_process;




	//int flag;
	//std::mutex mutex;





};
class Client {
public:
	~Client() {
		if (documents_type != nullptr) delete[] documents_type;
		if (documents_serial_number != nullptr) delete[] documents_serial_number;
		if (documents_verification_timestamp != nullptr) delete[] documents_verification_timestamp;
		wsclients.clear();
	};
	Client();
	void operator = (const Client&);
	// vector<time_t> getAllTicketDates();
	// unordered_set<Ticket*> getTicketsOnDate(int, int, int);
	vector<wsClient*> wsclients;
	int client_id;
	string name;
	string surname;
	int date_of_birth;//timestamp in seconds UNIX 1970
	int anonymous;
	int country_id;
	int region_id;
	int city_id;
	int group;
	int language;
	int last_timezone;
	int documents_number;
	int* documents_type;
	string* documents_serial_number;
	int* documents_verification_timestamp;//in seconds
	string last_domain;
	string country;
	string domain;
	string region;
	string city;
	string email;
	string phone;
	string login;
	string password;
	Currency currency;
	string postal_code;
	string address;
	double balance;      // Money in the account(balance)
	double bets_amount;  // Money in the game(in bets)
	int timezone;
	int email_newsletter;
	string getPersonKey();
};
void Client::operator = (const Client & rhs) {
	if (this == &rhs) return;
	client_id = rhs.client_id;
	name = rhs.name;
	region = rhs.region;
	anonymous = rhs.anonymous;
	surname = rhs.surname;
	date_of_birth = rhs.date_of_birth;
	country = rhs.country;
	domain = rhs.domain;
	city = rhs.city;
	email = rhs.email;
	country_id = rhs.country_id;
	region_id = rhs.region_id;
	city_id = rhs.city_id;
	email_newsletter = rhs.email_newsletter;
	phone = rhs.phone;
	login = rhs.login;
	password = rhs.password;
	currency = rhs.currency;
	postal_code = rhs.postal_code;
	address = rhs.address;
	balance = rhs.balance;
	bets_amount = rhs.bets_amount;
	timezone = rhs.timezone;
	wsclients = rhs.wsclients;
	group = rhs.group;
	language = rhs.language;
	last_timezone = rhs.last_timezone;
	last_domain = rhs.last_domain;
	if (documents_type != nullptr) { delete[] documents_type; documents_type = nullptr; }
	if (documents_serial_number != nullptr) { delete[] documents_serial_number; documents_serial_number = nullptr; }
	if (documents_verification_timestamp != nullptr) { delete[] documents_verification_timestamp; documents_verification_timestamp = nullptr; }
	documents_number = rhs.documents_number;
	if (documents_number > 0) {
		documents_type = new int[documents_number]; documents_verification_timestamp = new int[documents_number]; documents_serial_number = new string[documents_number];
	}

	for (int i = 0; i < documents_number; i++) {
		documents_type[i] = rhs.documents_type[i];
		documents_verification_timestamp[i] = rhs.documents_verification_timestamp[i];
		documents_serial_number[i] = rhs.documents_serial_number[i];
	}






}
Client::Client() {
	client_id = 0;
	name = "";
	region = "";
	anonymous = 1;
	surname = "";
	date_of_birth = 0;
	country = "";
	domain = "";
	city = "";
	email = "";
	email_newsletter = 1;
	phone = "";
	login = "";
	password = "";
	currency = Currency::TMT;
	postal_code = "";
	address = "";
	balance = 0;
	bets_amount = 0;
	timezone = 0;
	country_id = 0;
	region_id = 0;
	city_id = 0;
	group = 0;
	language = 0;
	last_timezone = 0;
	documents_number = 0;
	documents_type = nullptr;
	documents_serial_number = nullptr;
	documents_verification_timestamp = nullptr;//in seconds
	last_domain = "";
}
string Client::getPersonKey() {
	char date[64];
	_itoa(date_of_birth, date, 10);
	return  name + surname + date;

}




unordered_map<int, Client*> client_id_hash = {};
unordered_map<string, Client*> client_login_hash = {};
unordered_map<string, Client*> client_email_hash = {};
unordered_map<string, Client*> client_person_hash = {};
unordered_map<string, Client*> client_phone_hash = {};


class webSocket {
public:
	webSocket() {
		callOnOpen = nullptr;
		callOnClose = nullptr;
		callOnMessage = nullptr;
		callPeriodic = nullptr;
	}

	void setOpenHandler(defaultCallback callback);
	void setCloseHandler(defaultCallback callback);
	void setMessageHandler(messageCallback callback);
	void setPeriodicHandler(nullCallback callback);
	void startServer(int port);
	void stopServer();
	bool wsSend(int clientID, char* message, size_t messageLen, bool binary = true);
	void wsClose(int clientID);
	bool wsSendBetMessage(wsClient*, char*, int);
	vector<int> getClientIDs();
	string getClientIP(int clientID);
	string getClientIP(wsClient*);
	vector<wsClient *> wsClients;
	//vector<atomic_flag*> wsFlags;
	//atomic_flag ws_clients_flag = ATOMIC_FLAG_INIT;
	map<int, int> socketIDmap;

private:

	fd_set r_fds;
	fd_set w_fds;
	fd_set e_fds;
	int fdmax;
	int ListenSocket;
	SSL_CTX *ctx;
	void wsCheckIdleClients();
	bool wsSendClientMessage(int clientID, unsigned char opcode, char*, int);
	bool wsEncodeClientMessage(int clientID, unsigned char opcode, char*, size_t, char* &, size_t &);
	void wsSendClientClose(int clientID, unsigned short status = -1);
	bool wsCheckSizeClientFrame(int clientID);
	void wsRemoveClient(int clientID);
	void wsDeleteClient(int clientID);
	bool wsProcessClientMessage(int clientID, unsigned char opcode, string data, int dataLength);
	bool wsProcessClientFrame(int clientID);
	bool wsBuildClientFrame(int clientID, char *buffer, int buffer_length);
	bool wsProcessClientHandshake(int clientID, char *buffer);
	bool wsProcessClient(int clientID, char *buffer, int buffer_length);
	int wsGetNextClientID();
	void wsAddClient(int socket, SSL*, in_addr ip);

	defaultCallback callOnOpen;
	defaultCallback callOnClose;
	messageCallback callOnMessage;
	nullCallback callPeriodic;
};

size_t calcDecodeLength(const char*);
int Base64Decode(char*, unsigned char**, size_t*);
void Base64Encode(const std::uint8_t*, std::size_t, char*&, std::size_t&);
void writeInteger(char*, size_t &, int, int);
void writeString(char*, size_t &, char*);
void writeDouble(char*, size_t &, double);
void writeFloat(char*, size_t &, float);
int readInteger(char*, size_t &, int*, int, size_t);
int readString(char*, size_t &, char* &, size_t);
int readDouble(char*, size_t &, double*, size_t);



void showAvailableIP() {

	/* Variables used by GetIpAddrTable */
	PMIB_IPADDRTABLE pIPAddrTable;
	DWORD dwSize = 0;
	DWORD dwRetVal = 0;
	IN_ADDR IPAddr;

	/* Variables used to return error message */
	LPVOID lpMsgBuf;

	// Before calling AddIPAddress we use GetIpAddrTable to get
	// an adapter to which we can add the IP.
	pIPAddrTable = (MIB_IPADDRTABLE *)MALLOC(sizeof(MIB_IPADDRTABLE));

	if (pIPAddrTable) {
		// Make an initial call to GetIpAddrTable to get the
		// necessary size into the dwSize variable
		if (GetIpAddrTable(pIPAddrTable, &dwSize, 0) ==
			ERROR_INSUFFICIENT_BUFFER) {
			FREE(pIPAddrTable);
			pIPAddrTable = (MIB_IPADDRTABLE *)MALLOC(dwSize);

		}
		if (pIPAddrTable == nullptr) {
			std::printf("Memory allocation failed for GetIpAddrTable\n");
			return;
		}
	}
	// Make a second call to GetIpAddrTable to get the
	// actual data we want
	if ((dwRetVal = GetIpAddrTable(pIPAddrTable, &dwSize, 0)) != NO_ERROR) {
		printf("GetIpAddrTable failed with error %d\n", dwRetVal);
		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, dwRetVal, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),       // Default language
			(LPTSTR)& lpMsgBuf, 0, nullptr)) {
			printf("\tError: %s", lpMsgBuf);
			LocalFree(lpMsgBuf);
		}
		return;
	}

	cout << "Available IP:" << endl;

	for (int i = 0; i < (int)pIPAddrTable->dwNumEntries; i++) {
		IPAddr.S_un.S_addr = (u_long)pIPAddrTable->table[i].dwAddr;
		cout << "    " << i << ": " << inet_ntoa(IPAddr) << endl;
	}

	if (pIPAddrTable) {
		FREE(pIPAddrTable);
		pIPAddrTable = nullptr;
	}


}
vector<int> webSocket::getClientIDs() {
	vector<int> clientIDs;
	for (int i = 0; i < wsClients.size(); i++) {
		if (wsClients[i] != nullptr && wsClients[i]->timestamp == 0)
			clientIDs.push_back(i);
	}

	return clientIDs;
}
string webSocket::getClientIP(int clientID) {
	return string(inet_ntoa(wsClients[clientID]->addr));
}
string webSocket::getClientIP(wsClient* wsClient) {
	return string(inet_ntoa(wsClient->addr));
}
void webSocket::wsCheckIdleClients() {

	time_t current = time(nullptr);
	for (int i = 0; i < wsClients.size(); i++) {
		if (wsClients[i] != nullptr && wsClients[i]->timestamp == 0 && wsClients[i]->ready_state != WS_READY_STATE_CLOSED && wsClients[i]->ready_state != WS_READY_STATE_CLOSING) {
			if (wsClients[i]->ping_sent_time != 0) {
				if (difftime(current, wsClients[i]->ping_sent_time) >= WS_TIMEOUT_PONG) {
					wsSendClientClose(i, WS_STATUS_TIMEOUT);
					//wsRemoveClient(i);
				}
			}
			else if (difftime(current, wsClients[i]->last_recv_time) != WS_TIMEOUT_RECV) {
				if (wsClients[i]->ready_state != WS_READY_STATE_CONNECTING) {
					wsClients[i]->ping_sent_time = time(nullptr);
					wsSendClientMessage(i, WS_OPCODE_PING, "", 0);
				}
				else
					wsRemoveClient(i);
			}
		}
	}
}
bool webSocket::wsSendClientMessage(int clientID, unsigned char opcode, char* message, int messageLen) {
	// check if client ready state is already closing or closed
	if (clientID >= wsClients.size())
		return false;

	if (wsClients[clientID]->ready_state == WS_READY_STATE_CLOSING || wsClients[clientID]->ready_state == WS_READY_STATE_CLOSED || wsClients[clientID]->timestamp > 0)
		return false;

	// fetch message length


	char *buf = nullptr;
	size_t totalLength;

	if (opcode == WS_OPCODE_PING || opcode == WS_OPCODE_PONG || opcode == WS_OPCODE_CLOSE) {

		// set max payload length per frame
		int bufferSize = EXTRA;

		// work out amount of frames to send, based on $bufferSize
		int frameCount = ceil((float)messageLen / bufferSize);
		if (frameCount == 0)
			frameCount = 1;

		// set last frame variables
		int maxFrame = frameCount - 1;
		int lastframe_buffer_length = (messageLen % bufferSize) != 0 ? (messageLen % bufferSize) : (messageLen != 0 ? bufferSize : 0);

		// loop around all frames to send



		for (int i = 0; i < frameCount; i++) {
			// fetch fin, opcode and buffer length for frame
			unsigned char fin = i != maxFrame ? 0 : WS_FIN;
			opcode = i != 0 ? WS_OPCODE_CONTINUATION : opcode;

			size_t buffer_length = i != maxFrame ? bufferSize : lastframe_buffer_length;



			// set payload length variables for frame
			if (buffer_length <= 125) {
				// int payloadLength = buffer_length;
				totalLength = buffer_length + 2;
				buf = new char[totalLength];
				buf[0] = fin | opcode;
				buf[1] = buffer_length;
				memcpy(buf + 2, message, messageLen);
			}
			else if (buffer_length <= 65535) {
				// int payloadLength = WS_PAYLOAD_LENGTH_16;
				totalLength = buffer_length + 4;
				buf = new char[totalLength];
				buf[0] = fin | opcode;
				buf[1] = WS_PAYLOAD_LENGTH_16;
				buf[2] = buffer_length >> 8;
				buf[3] = buffer_length;
				memcpy(buf + 4, message, messageLen);
			}
			else {
				// int payloadLength = WS_PAYLOAD_LENGTH_63;
				totalLength = buffer_length + 10;
				buf = new char[totalLength];
				buf[0] = fin | opcode;
				buf[1] = WS_PAYLOAD_LENGTH_63;
				buf[2] = 0;
				buf[3] = 0;
				buf[4] = 0;
				buf[5] = 0;
				buf[6] = buffer_length >> 24;
				buf[7] = buffer_length >> 16;
				buf[8] = buffer_length >> 8;
				buf[9] = buffer_length;
				memcpy(buf + 10, message, messageLen);
			}

		}

		if (opcode == WS_OPCODE_PING && wsClients[clientID]->ready_state != HTTPS_STATE_OPEN && wsClients[clientID]->ready_state != HTTPS_STATE_READ && wsClients[clientID]->ready_state != HTTPS_STATE_WRITE) { if (wsClients[clientID]->message_ping != nullptr) delete[] wsClients[clientID]->message_ping; wsClients[clientID]->message_ping = buf; wsClients[clientID]->message_ping_length = totalLength; }
		else
			if (opcode == WS_OPCODE_PONG && wsClients[clientID]->ready_state != HTTPS_STATE_OPEN && wsClients[clientID]->ready_state != HTTPS_STATE_READ && wsClients[clientID]->ready_state != HTTPS_STATE_WRITE) { if (wsClients[clientID]->message_pong != nullptr) delete[] wsClients[clientID]->message_pong; wsClients[clientID]->message_pong = buf; wsClients[clientID]->message_pong_length = totalLength; }
			else
				if (opcode == WS_OPCODE_CLOSE && wsClients[clientID]->ready_state != HTTPS_STATE_OPEN && wsClients[clientID]->ready_state != HTTPS_STATE_READ && wsClients[clientID]->ready_state != HTTPS_STATE_WRITE) { if (wsClients[clientID]->message_close != nullptr) delete[] wsClients[clientID]->message_close; wsClients[clientID]->message_close = buf; wsClients[clientID]->message_close_length = totalLength; }

	}


	else

	{

		totalLength = messageLen;
		buf = new char[totalLength];
		memcpy(buf, message, messageLen);

		//wsClients[clientID]->mutex.lock();

		wsClients[clientID]->message_queue_length[wsClients[clientID]->last_message_queue % QUEUE_LENGTH] = totalLength;
		wsClients[clientID]->message_queue[wsClients[clientID]->last_message_queue  % QUEUE_LENGTH] = buf;
		wsClients[clientID]->last_message_queue++;

		if (wsClients[clientID]->last_message_queue - QUEUE_LENGTH >= wsClients[clientID]->last_message_queue_socket) wsSendClientClose(clientID, WS_STATUS_PROTOCOL_ERROR);


		//wsClients[clientID]->mutex.unlock(); 


	}



	return true;
}
bool webSocket::wsSendBetMessage(wsClient* wsclient, char* message, int messageLen) {
	// check if client ready state is already closing or closed

	if (wsclient == nullptr || wsclient->ready_state == WS_READY_STATE_CLOSING || wsclient->ready_state == WS_READY_STATE_CLOSED || wsclient->timestamp > 0)
		return false;

	char *buf = nullptr;
	size_t totalLength;

	totalLength = messageLen;
	buf = new char[totalLength];
	memcpy(buf, message, messageLen);

	//wsClients[clientID]->mutex.lock();

	wsclient->bet_message_queue_length[wsclient->last_bet_message_queue % QUEUE_LENGTH] = totalLength;
	wsclient->bet_message_queue[wsclient->last_bet_message_queue  % QUEUE_LENGTH] = buf;
	wsclient->last_bet_message_queue++;



	if (wsclient->last_bet_message_queue - QUEUE_LENGTH >= wsclient->last_bet_message_queue_socket) wsSendClientClose(socketIDmap[wsclient->socket], WS_STATUS_PROTOCOL_ERROR);






	return true;
}
bool webSocket::wsEncodeClientMessage(int clientID, unsigned char opcode, char* message, size_t messageLength, char* &writeBuffer, size_t &writeBufferLen) {
	// check if client ready state is already closing or closed
	if (clientID >= wsClients.size())
		return false;
	if (wsClients[clientID]->timestamp > 0) return false;

	//opcode = WS_OPCODE_BINARY; //printf("HAHAHAHAH");

	if (wsClients[clientID]->ready_state == WS_READY_STATE_CLOSING || wsClients[clientID]->ready_state == WS_READY_STATE_CLOSED)
		return true;

	// fetch message length
	//int messageLength = message.size();


	// set max payload length per frame
	int bufferSize = EXTRA;

	// work out amount of frames to send, based on $bufferSize
	int frameCount = ceil((float)messageLength / bufferSize);
	if (frameCount == 0)
		frameCount = 1;

	// set last frame variables
	int maxFrame = frameCount - 1;
	int lastframe_buffer_length = (messageLength % bufferSize) != 0 ? (messageLength % bufferSize) : (messageLength != 0 ? bufferSize : 0);

	// loop around all frames to send

	if (writeBuffer != nullptr) delete[] writeBuffer;
	writeBuffer = nullptr;


	for (int i = 0; i < frameCount; i++) {
		// fetch fin, opcode and buffer length for frame
		unsigned char fin = i != maxFrame ? 0 : WS_FIN;
		opcode = i != 0 ? WS_OPCODE_CONTINUATION : opcode;

		size_t buffer_length = i != maxFrame ? bufferSize : lastframe_buffer_length;

		//size_t totalLength;

		// set payload length variables for frame
		if (buffer_length <= 125) {
			// int payloadLength = buffer_length;
			writeBufferLen = buffer_length + 2;
			writeBuffer = new char[writeBufferLen];
			writeBuffer[0] = fin | opcode;
			writeBuffer[1] = buffer_length;
			memcpy(writeBuffer + 2, message, messageLength);
		}
		else if (buffer_length <= 65535) {
			// int payloadLength = WS_PAYLOAD_LENGTH_16;
			writeBufferLen = buffer_length + 4;
			writeBuffer = new char[writeBufferLen];
			writeBuffer[0] = fin | opcode;
			writeBuffer[1] = WS_PAYLOAD_LENGTH_16;
			writeBuffer[2] = buffer_length >> 8;
			writeBuffer[3] = buffer_length;
			memcpy(writeBuffer + 4, message, messageLength);
		}
		else {
			// int payloadLength = WS_PAYLOAD_LENGTH_63;
			writeBufferLen = buffer_length + 10;
			writeBuffer = new char[writeBufferLen];
			writeBuffer[0] = fin | opcode;
			writeBuffer[1] = WS_PAYLOAD_LENGTH_63;
			writeBuffer[2] = 0;
			writeBuffer[3] = 0;
			writeBuffer[4] = 0;
			writeBuffer[5] = 0;
			writeBuffer[6] = buffer_length >> 24;
			writeBuffer[7] = buffer_length >> 16;
			writeBuffer[8] = buffer_length >> 8;
			writeBuffer[9] = buffer_length;
			memcpy(writeBuffer + 10, message, messageLength);
		}



	}

	return true;
}
bool webSocket::wsSend(int clientID, char* message, size_t messageLen, bool binary) {
	return wsSendClientMessage(clientID, binary ? WS_OPCODE_BINARY : WS_OPCODE_TEXT, message, messageLen);
}
void webSocket::wsSendClientClose(int clientID, unsigned short status) {
	// check if client ready state is already closing or closed
	if (wsClients[clientID]->timestamp > 0 || wsClients[clientID]->ready_state == WS_READY_STATE_CLOSING || wsClients[clientID]->ready_state == WS_READY_STATE_CLOSED)
		return;

	// store close status
	//	wsClients[clientID]->ready_state = status;

	// send close frame to client
	wsSendClientMessage(clientID, WS_OPCODE_CLOSE, "", 0);

	// set client ready state to closing
	//printf("clientId=%d set WS_READY_STATE_CLOSING(2)\r\n", clientID);
	wsClients[clientID]->ready_state = WS_READY_STATE_CLOSING;


}
void webSocket::wsClose(int clientID) {
	wsSendClientClose(clientID, WS_STATUS_NORMAL_CLOSE);
}
bool webSocket::wsCheckSizeClientFrame(int clientID) {
	wsClient *client = wsClients[clientID];
	// check if at least 2 bytes have been stored in the frame buffer
	if (client->frame_bytes_read > 1) {
		// fetch payload length in byte 2, max will be 127
		size_t payloadLength = (unsigned char)client->frame_buffer.at(1) & 127;

		if (payloadLength <= 125) {
			// actual payload length is <= 125
			client->frame_payload_data_length = payloadLength;
		}
		else if (payloadLength == 126) {
			// actual payload length is <= 65,535
			if (client->frame_buffer.size() >= 4) {
				std::vector<unsigned char> length_bytes;
				length_bytes.resize(2);
				memcpy((char*)&length_bytes[0], client->frame_buffer.substr(2, 2).c_str(), 2);

				size_t length = 0;
				int num_bytes = 2;
				for (int c = 0; c < num_bytes; c++)
					length += length_bytes[c] << (8 * (num_bytes - 1 - c));
				client->frame_payload_data_length = length;
			}
		}
		else {
			if (client->frame_buffer.size() >= 10) {
				std::vector<unsigned char> length_bytes;
				length_bytes.resize(8);
				memcpy((char*)&length_bytes[0], client->frame_buffer.substr(2, 8).c_str(), 8);

				size_t length = 0;
				int num_bytes = 8;
				for (int c = 0; c < num_bytes; c++)
					length += length_bytes[c] << (8 * (num_bytes - 1 - c));
				client->frame_payload_data_length = length;
			}
		}

		return true;
	}

	return false;
}
void webSocket::wsRemoveClient(int clientID) {

	//if (callOnClose != nullptr)
	//callOnClose(clientID);

	wsClient* wsclient = wsClients[clientID];
	if (wsclient == nullptr) return;
	if (wsclient->timestamp > 0) return;
	// fetch close status (which could be false), and call wsOnClose
	//int64_t closeStatus = wsClients[clientID]->close_status;
	//int64_t flag = 0;
	//
	//SSL_shutdown(client->ssl);
	//SSL_CTX_free(client->ssl);
	//while (ws_clients_flag.test_and_set(std::memory_order_acquire));


	if (wsclient->client_id > -1) {
		auto client_it = client_id_hash.find(wsclient->client_id);
		if (client_it == client_id_hash.end()) {}
		else {
			for (auto it = client_it->second->wsclients.begin(); it != client_it->second->wsclients.end(); ++it)
				if (*it == wsclient) {
					client_it->second->wsclients.erase(it); break;
				}
		}


	}
	wsclient->client_id = -1;
	wsclient->sms_counter = 0;
	wsclient->timestamp = timestamp();
	FD_CLR(wsclient->socket, &r_fds);
	FD_CLR(wsclient->socket, &w_fds);

	//closesocket(client->socket);
	//SSL_set_shutdown(client->ssl, SSL_RECEIVED_SHUTDOWN);
	//SSL_free(client->ssl);
	//socketIDmap.erase(client->socket);
	//wsClients[clientID] = nullptr;
	//delete client;
	//ws_clients_flag.clear(std::memory_order_release);
}
void webSocket::wsDeleteClient(int clientID) {
	wsClient * wsclient = wsClients[clientID];
	wsClients[clientID] = nullptr;
	if (wsclient == nullptr) return;
	socketIDmap.erase(wsclient->socket);
	closesocket(wsclient->socket);
	SSL_set_shutdown(wsclient->ssl, SSL_RECEIVED_SHUTDOWN);
	SSL_free(wsclient->ssl);
	delete wsclient;
}
bool webSocket::wsProcessClientMessage(int clientID, unsigned char opcode, string data, int dataLength) {

	unsigned char* recv_buf = nullptr;
	size_t recv_offset;
	size_t size;
	int response;

	wsClient *wsclient = wsClients[clientID];
	// check opcodes

	if (opcode == WS_OPCODE_PING) {
		// received ping message
		return wsSendClientMessage(clientID, WS_OPCODE_PONG, (char*)data.c_str(), data.size());
	}
	else if (opcode == WS_OPCODE_PONG) {
		// received pong message (it's valid if the server did not send a ping request for this pong message)
		if (wsclient->ping_sent_time != 0) {
			wsclient->ping_sent_time = 0;
		}
	}
	else if (opcode == WS_OPCODE_CLOSE) {
		// received close message
		if (wsclient->ready_state == WS_READY_STATE_CLOSING) {
			// the server already sent a close frame to the client, this is the client's close frame reply
			// (no need to send another close frame to the client)
			wsclient->ready_state = WS_READY_STATE_CLOSED;
			//wsRemoveClient(clientID);
		}
		else {
			// the server has not already sent a close frame to the client, send one now
			//wsRemoveClient(clientID);
			//wsSendClientClose(clientID, WS_STATUS_NORMAL_CLOSE);

		}
		wsRemoveClient(clientID);

	}
	else if (opcode == WS_OPCODE_TEXT || opcode == WS_OPCODE_BINARY) {
		//if(data.substr(0, dataLength)=="recovery" ) hThread4 = CreateThread(nullptr, 0, &startRecoveryThread, 0, THREAD_TERMINATE, &dwThreadID4);
		//if (callOnMessage != nullptr)	callOnMessage(clientID, data.substr(0, dataLength));
		//std::strncmp(data, "rospis@", 7) == 0)

		if (dataLength > 10 && data.substr(0, 10) == "extralines") {
			response = 0;
			Base64Decode((char*)((char*)data.c_str() + 10), &recv_buf, &size);
			//int event_id;
			int request_id;
			char* event_key = new char[48];

			recv_offset = 0;
			//if (readInteger((char*)recv_buf, recv_offset, &event_id, 4, size) == -1) response = -1; else
			if (readString((char*)recv_buf, recv_offset, event_key, size) == -1)  response = -1; else
				if (readInteger((char*)recv_buf, recv_offset, &request_id, 1, size) == -1) response = -1;
			//if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; }

			if (response == 0 && wsclient->plus_send == false && wsclient->plus_create == false && wsclient->plus.length() == 0 ) {
				wsclient->plus_request_id = request_id;
				wsclient->plus = string(event_key);
				
				wsclient->plus_create = true;
			}
			delete[] event_key;
			
			if (recv_buf != nullptr) delete[] recv_buf;
		}
		else

			if (dataLength > 8 && data.substr(0, 8) == "outright") //&& std::strncmp(data, "outright@", 9) == 0)
			{

				response = 0;
				Base64Decode((char*)((char*)data.c_str() + 8), &recv_buf, &size);

				int category_id;
				int request_id;
				recv_offset = 0;
				if (readInteger((char*)recv_buf, recv_offset, &category_id, 4, size) == -1) response = -1; else
					if (readInteger((char*)recv_buf, recv_offset, &request_id, 1, size) == -1) response = -1;
				if (response == 0 && category_id != 0 && category_id < MAX_CATEGORIES && categories_id[category_id] != nullptr && wsclient->outright_send == false && wsclient->outright_create == false) { wsclient->outright = category_id; wsclient->outright_request_id = request_id; wsclient->outright_create = true; }
				if (recv_buf != nullptr) delete[] recv_buf;
			}

			else if (dataLength > 6 && data.substr(0, 6) == "client") //std::strncmp(data, "client", 6) == 0)
			{

				if (wsclient->recv_client_message[wsclient->recv_client_message_queue % RECV_MAX_CLIENT_QUEUE] != nullptr) delete[] wsclient->recv_client_message[wsclient->recv_client_message_queue % RECV_MAX_CLIENT_QUEUE];
				wsclient->recv_client_message_length[wsclient->recv_client_message_queue % RECV_MAX_CLIENT_QUEUE] = data.size();
				wsclient->recv_client_message[wsclient->recv_client_message_queue % RECV_MAX_CLIENT_QUEUE] = new char[data.size() + 1];
				memcpy(wsclient->recv_client_message[wsclient->recv_client_message_queue % RECV_MAX_CLIENT_QUEUE], (char*)data.c_str(), data.size());
				wsclient->recv_client_message[wsclient->recv_client_message_queue % RECV_MAX_CLIENT_QUEUE][data.size()] = 0;
				wsclient->recv_client_message_queue++;

			}

			else if (dataLength > 6 && data.substr(0, 6) == "ticket")
			{
				if (wsclient->ticket_process == false && wsclient->ticket_send == false) {

					if (wsclient->tickets != nullptr) {
						for (int i = 0; i < wsclient->tickets_number; i++) if (wsclient->tickets[i] != nullptr) delete wsclient->tickets[i];  delete[] wsclient->tickets;
						wsclient->tickets = nullptr;
					}

					wsclient->tickets_number = 0;
					if (wsclient->recv_ticket_message != nullptr) delete[] wsclient->recv_ticket_message;
					wsclient->recv_ticket_message = new char[data.size() + 1];
					wsclient->recv_ticket_message_length = data.size();
					memcpy(wsclient->recv_ticket_message, (char*)data.c_str(), data.size());
					wsclient->recv_ticket_message[data.size()] = 0;
					wsclient->ticket_process = true;

				};
			}



	}
	else {
		// unknown opcode

		return false;
	}


	return true;
}
bool webSocket::wsProcessClientFrame(int clientID) {
	wsClient *client = wsClients[clientID];
	// store the time that data was last received from the client
	client->last_recv_time = time(nullptr);

	// check at least 6 bytes are set (first 2 bytes and 4 bytes for the mask key)
	if (client->frame_buffer.size() < 6)
		return false;

	// fetch first 2 bytes of header
	unsigned char octet0 = client->frame_buffer.at(0);
	unsigned char octet1 = client->frame_buffer.at(1);

	unsigned char fin = octet0 & WS_FIN;
	unsigned char opcode = octet0 & 0x0f;

	//unsigned char mask = octet1 & WS_MASK;
	if (octet1 < 128)
		return false; // close socket, as no mask bit was sent from the client

					  // fetch byte position where the mask key starts
	int seek = client->frame_bytes_read <= 125 ? 2 : (client->frame_bytes_read <= 65535 ? 4 : 10);

	// read mask key
	char maskKey[4];
	memcpy(maskKey, client->frame_buffer.substr(seek, 4).c_str(), 4);

	seek += 4;

	// decode payload data
	string data;
	for (int i = seek; i < client->frame_buffer.size(); i++) {
		//data.append((char)(((int)client->frame_buffer.at(i)) ^ maskKey[(i - seek) % 4]));
		char c = client->frame_buffer.at(i);
		c = c ^ maskKey[(i - seek) % 4];
		data += c;
	}

	// check if this is not a continuation frame and if there is already data in the message buffer
	if (opcode != WS_OPCODE_CONTINUATION && client->message_buffer_length > 0) {
		// clear the message buffer
		client->message_buffer_length = 0;
		client->message_buffer.clear();
	}

	// check if the frame is marked as the final frame in the message
	if (fin == WS_FIN) {
		// check if this is the first frame in the message
		if (opcode != WS_OPCODE_CONTINUATION) {
			// process the message
			//if (opcode == WS_OPCODE_CLOSE) printf("gggggggg1\r\n");
			return wsProcessClientMessage(clientID, opcode, data, client->frame_payload_data_length);
		}
		else {
			// increase message payload data length
			client->message_buffer_length += client->frame_payload_data_length;

			// push frame payload data onto message buffer
			client->message_buffer.append(data);

			// process the message

			bool result = wsProcessClientMessage(clientID, client->message_opcode, client->message_buffer, client->message_buffer_length);

			// check if the client wasn't removed, then reset message buffer and message opcode
			if (wsClients[clientID] != nullptr) {
				client->message_buffer.clear();
				client->message_opcode = 0;
				client->message_buffer_length = 0;
			}

			return result;
		}
	}
	else {
		// check if the frame is a control frame, control frames cannot be fragmented
		if (opcode & 8)
			return false;

		// increase message payload data length
		client->message_buffer_length += client->frame_payload_data_length;

		// push frame payload data onto message buffer
		client->message_buffer.append(data);

		// if this is the first frame in the message, store the opcode
		if (opcode != WS_OPCODE_CONTINUATION) {
			client->message_opcode = opcode;
		}
	}

	return true;
}
bool webSocket::wsBuildClientFrame(int clientID, char *buffer, int buffer_length) {
	wsClient *client = wsClients[clientID];
	// increase number of bytes read for the frame, and join buffer onto end of the frame buffer
	client->frame_bytes_read += buffer_length;
	client->frame_buffer.append(buffer, buffer_length);

	// check if the length of the frame's payload data has been fetched, if not then attempt to fetch it from the frame buffer


	if (wsCheckSizeClientFrame(clientID) == true) {

		// work out the header length of the frame
		int headerLength = (client->frame_payload_data_length <= 125 ? 0 : (client->frame_payload_data_length <= 65535 ? 2 : 8)) + 6;

		// check if all bytes have been received for the frame
		int frameLength = client->frame_payload_data_length + headerLength;
		if (client->frame_bytes_read >= frameLength) {
			char *nextFrameBytes = nullptr;
			// check if too many bytes have been read for the frame (they are part of the next frame)
			int nextFrameBytesLength = client->frame_bytes_read - frameLength;
			if (nextFrameBytesLength > 0) {
				client->frame_bytes_read -= nextFrameBytesLength;
				nextFrameBytes = buffer + frameLength;
				client->frame_buffer = client->frame_buffer.substr(0, frameLength);
			}

			// process the frame

			bool result = wsProcessClientFrame(clientID);


			// check if the client wasn't removed, then reset frame data
			if (wsClients[clientID] != nullptr) {
				client->frame_payload_data_length = -1;
				client->frame_bytes_read = 0;
				client->frame_buffer.clear();
			}

			// if there's no extra bytes for the next frame, or processing the frame failed, return the result of processing the frame
			if (nextFrameBytesLength <= 0 || !result)
			{

				return result;
			}

			// build the next frame with the extra bytes
			return wsBuildClientFrame(clientID, nextFrameBytes, nextFrameBytesLength);
		}
	}

	return true;
}
bool webSocket::wsProcessClientHandshake(int clientID, char *buffer) {

	bool find_handshake = false;
	bool find_content_length = false;
	uint32_t index = 0;
	char handshakeTest[] = "Sec-WebSocket-Key: ";
	char content_string[] = "Content-Length: ";
	char* handshakeHash = new char[120];
	char* handshake_buffer = new char[MAX_PATH];
	char* base64EncodeOutput = nullptr;
	char* int_buf = new char[64];
	char* options = new char[MAX_PATH];
	int_buf[0] = 0;
	int j = 0;;
	int l = 0;
	//ZeroMemory(base64_hash, sizeof(base64_hash));
	int handshake_test_len = strlen(handshakeTest);
	int content_string_length = strlen(content_string);
	int content_length = 0;

	unsigned char* digest = new unsigned char[SHA_DIGEST_LENGTH];
	int buffer_len = strlen(buffer);

	for (int i = 0; i < buffer_len - handshake_test_len - 20; i++)
		if (strncmp((char*)((char*)buffer + i), handshakeTest, handshake_test_len) == 0)
		{
			for (int j = 0; j < 100; j++) if (buffer[j + i + handshake_test_len] == '\r' && buffer[j + i + handshake_test_len + 1] == '\n')
			{
				strncpy(handshakeHash, (char*)((char*)buffer + i + handshake_test_len), j);
				handshakeHash[j] = 0;
				//strcpy(handshakeHash, "lpRgKO1IAsqpPeIgIIbpfA==");

				strcat(handshakeHash, "258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
				find_handshake = true;
				//	printf(handshakeHash);
				//printf("\r\n");
				break;
			}


			break;
		}



	size_t handshakelen = 0;
	if (find_handshake == true) {
		SHA1((unsigned char*)handshakeHash, strlen(handshakeHash), digest);
		//printf("Output (sha1): %d\n", strlen(digest));
		Base64Encode(digest, 20, base64EncodeOutput, handshakelen);
		base64EncodeOutput[handshakelen] = 0;
		// printf("Output (base64): %s\r\n", base64EncodeOutput);
		//printf("handshakelen: %d\r\n", handshakelen);
		strcpy(handshake_buffer, "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: ");
		if (base64EncodeOutput != nullptr)	strcat(handshake_buffer, base64EncodeOutput);
		strcat(handshake_buffer, "\r\n\r\n");
		//printf(handshake_buffer);
		wsClients[clientID]->handshake_message = handshake_buffer;// new char[left];


	}
	else {


		int key_end = 0;
		for (int i = 0; i < buffer_len - content_string_length - 5; i++) if (strncmp((char*)((char*)buffer + i), content_string, content_string_length) == 0)
		{
			key_end = i + content_string_length;
			for (j = key_end; j < buffer_len - 1; j++) {
				if (j > key_end + 30) break;
				if (buffer[j] == '\r' && buffer[j + 1] == '\n') { find_content_length = true; break; }
				int_buf[j - key_end] = buffer[j];
				int_buf[j - key_end + 1] = 0;
			}

			if (find_content_length == true)
			{
				content_length = atoi(int_buf);


			}

		} if (content_length > 10000000 || content_length < 0) find_content_length = false;  else { content_length = 0; find_content_length = true; }


		if (find_content_length == true)
		{
			i = 0;
			l = 0;
			while (buffer[i] != '/' && i < buffer_len - 10) { i++; }
			if (i < buffer_len - 10)
				do {
					i++;
					options[l] = buffer[i];
					l++;
					if (buffer[i] == ' ' && buffer[i + 1] == 'H' && buffer[i + 2] == 'T' && buffer[i + 3] == 'T'&& buffer[i + 4] == 'P') break;

				} while (i < buffer_len - 10 && l < MAX_PATH - 1);
				if (i < buffer_len - 10 && l < MAX_PATH - 1) {
					options[l] = 0;
					if (wsClients[clientID]->options != nullptr) delete[] wsClients[clientID]->options;
					wsClients[clientID]->options = new char[strlen(options) + 1];
					strcpy(wsClients[clientID]->options, options);
					//printf("wsClients[clientID]->options=%s\r\n", wsClients[clientID]->options);

				}



				//	printf(buffer);



				key_end = j + 1;
				find_content_length = false;
				for (j = key_end; j < buffer_len - 3; j++) if (buffer[j] == '\r' && buffer[j + 1] == '\n' && buffer[j + 2] == '\r' && buffer[j + 3] == '\n')
				{

					find_content_length = true;
					key_end = j + 4;
					if (wsClients[clientID]->https_buffer != nullptr) delete[] wsClients[clientID]->https_buffer; wsClients[clientID]->https_buffer = nullptr;
					wsClients[clientID]->https_buffer = new char[MAX_HTTPS_READ_BUFFER];
					if (key_end < buffer_len)std::strcpy(wsClients[clientID]->https_buffer, (char*)((char*)buffer + key_end));
					else wsClients[clientID]->https_buffer[0] = 0;
					//wsClients[clientID]->https_status = 1;
					wsClients[clientID]->https_buffer_length = content_length;
					//printf("strlen(wsClients[clientID]->https_buffer)=%d\r\n", strlen(wsClients[clientID]->https_buffer));
					//printf("wsClients[clientID]->https_buffer_length=%d\r\n", wsClients[clientID]->https_buffer_length);
					//printf("\r\n");

					if (wsClients[clientID]->https_buffer_length < strlen(wsClients[clientID]->https_buffer)) find_content_length = false;
					else if (wsClients[clientID]->https_buffer_length == strlen(wsClients[clientID]->https_buffer)) wsClients[clientID]->ready_state = HTTPS_STATE_READ;
					else  wsClients[clientID]->ready_state = HTTPS_STATE_OPEN;

					wsClients[clientID]->https_time = time(nullptr);

					//printf("wsClients[clientID]->https_buffer=%s\r\n", wsClients[clientID]->https_buffer);
					//printf("wsClients[clientID]->https_buffer_length=%d\r\n", wsClients[clientID]->https_buffer_length);
					break;
				}

		}













	}

	delete[] handshakeHash;
	if (base64EncodeOutput != nullptr) delete[] base64EncodeOutput;
	delete[] int_buf;

	if (find_content_length == true || find_handshake == true)
		return true; else return false;
}
bool webSocket::wsProcessClient(int clientID, char *buffer, int buffer_length) {

	buffer[buffer_length] = 0;
	bool result;

	if (clientID >= wsClients.size() || wsClients[clientID] == nullptr)
		return false;


	if (wsClients[clientID]->ready_state == HTTPS_STATE_READ) return false;
	if (wsClients[clientID]->ready_state == HTTPS_STATE_OPEN) {
		result = false;
		int https_buffer_length = strlen(wsClients[clientID]->https_buffer);
		if (buffer_length + https_buffer_length >= MAX_HTTPS_READ_BUFFER) return false;
		strcat(wsClients[clientID]->https_buffer, buffer);
		//printf("https_buffer_length=%d\r\n", https_buffer_length);
		//printf("wsClients[clientID]->https_buffer_length=%d\r\n", wsClients[clientID]->https_buffer_length);

		if (https_buffer_length == wsClients[clientID]->https_buffer_length) {
			wsClients[clientID]->ready_state = HTTPS_STATE_READ;
			// printf(wsClients[clientID]->https_buffer);
			result = true;
		}
		if (https_buffer_length < wsClients[clientID]->https_buffer_length) result = true;
		if (https_buffer_length > wsClients[clientID]->https_buffer_length) result = false;

	}
	else if (wsClients[clientID]->ready_state == WS_READY_STATE_OPEN) {
		// handshake completed

		result = wsBuildClientFrame(clientID, buffer, buffer_length);

	}
	else if (wsClients[clientID]->ready_state == WS_READY_STATE_CONNECTING) {
		// handshake not completed

		result = wsProcessClientHandshake(clientID, buffer);
		/*	if (result) {
		if (callOnOpen != nullptr)
		callOnOpen(clientID);

		wsClients[clientID]->ready_state = WS_READY_STATE_OPEN;
		}*/
	}
	else {
		// ready state is set to closed
		result = false;
	}

	return result;
}
int webSocket::wsGetNextClientID() {
	int i;
	int64_t current_time = timestamp();
	for (i = 0; i < wsClients.size(); i++) {
		if (wsClients[i] != nullptr && wsClients[i]->timestamp > 0 && wsClients[i]->timestamp + 100000 < current_time)
			wsDeleteClient(i);
		if (wsClients[i] == nullptr)
			break;
	}
	return i;
}
void webSocket::wsAddClient(int socket, SSL* ssl, in_addr ip) {

	FD_SET(socket, &r_fds);
	FD_SET(socket, &w_fds);
	if (socket > fdmax)
		fdmax = socket;
	int clientID = wsGetNextClientID();
	wsClient *newClient = new wsClient(socket, ssl, ip);
	if (clientID >= wsClients.size()) {

		wsClients.push_back(newClient);

	}
	else {
		wsClients[clientID] = newClient;
	}
	socketIDmap[socket] = clientID;

}
void webSocket::setOpenHandler(defaultCallback callback) {
	callOnOpen = callback;
}
void webSocket::setCloseHandler(defaultCallback callback) {
	callOnClose = callback;
}
void webSocket::setMessageHandler(messageCallback callback) {
	callOnMessage = callback;
}
void webSocket::setPeriodicHandler(nullCallback callback) {
	callPeriodic = callback;
}
void webSocket::startServer(int port) {
	showAvailableIP();
	int yes = 1;
	char buf[SMALL];
	char* writeBuffer = nullptr;
	size_t writeBufferLen = 0;
	int iResult = 0;
	atomic_int64_t current = 0;
	int i = 0;
	struct sockaddr_in serv_addr, cli_addr;

	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(&cli_addr, '0', sizeof(cli_addr));
	serv_addr.sin_family = AF_INET;
	//serv_addr.sin_addr.s_addr = inet_addr(ip);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	X509*  cert;
	SSL *ssl = nullptr;
	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;
	char* str;
	DWORD dwError;
	SSL_load_error_strings();
	SSL_library_init();
	OpenSSL_add_all_algorithms();
	ctx = SSL_CTX_new(SSLv23_server_method());
	SSL_CTX_set_mode(ctx, SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER);
	if (!ctx) { wprintf(L"Error init ssl\n"); exit(1); }
	iResult = SSL_CTX_use_certificate_file(ctx, CERTF, SSL_FILETYPE_PEM);
	if (iResult <= 0) { wprintf(L"Error ssl certificate file %d\n", iResult); SSL_CTX_free(ctx); exit(1); }
	iResult = SSL_CTX_use_PrivateKey_file(ctx, KEYF, SSL_FILETYPE_PEM);
	if (iResult <= 0) { wprintf(L"Error Private Key file %d\n", iResult); SSL_CTX_free(ctx); exit(1); }
	iResult = SSL_CTX_check_private_key(ctx);
	if (!iResult) { wprintf(L"Private key does not match the certificate public key %d\n", iResult); SSL_CTX_free(ctx); exit(1); }
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) { wprintf(L"WSAStartup() failed with error: %d\n", iResult); SSL_CTX_free(ctx); exit(1); }




	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET)
	{
		WSACleanup();
		std::printf("failed socket %d", WSAGetLastError());
		exit(1);
	}

	iResult = setsockopt(ListenSocket, SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(int));



	if (iResult == SOCKET_ERROR) {
		closesocket(ListenSocket);
		WSACleanup();
		std::printf("failed setsockopt %d", WSAGetLastError());
		exit(1);
	}



	u_long ulBlock = 1;
	if (ioctlsocket(ListenSocket, FIONBIO, &ulBlock) == SOCKET_ERROR)
	{
		std::printf("could not fcntl\n");
		closesocket(ClientSocket);
		WSACleanup();
		exit(1);


	}




	iResult = ::bind(ListenSocket, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if (iResult == SOCKET_ERROR)
	{
		closesocket(ListenSocket);
		WSACleanup();
		std::printf("failed bind %d", WSAGetLastError());
		exit(1);
	}



	iResult = listen(ListenSocket, SOMAXCONN);

	if (iResult == SOCKET_ERROR)
	{
		closesocket(ListenSocket);
		WSACleanup();
		std::printf(0, "failed listen %d", WSAGetLastError());
		exit(1);
	}

	//int retValue;
	fdmax = ListenSocket;
	int type_of_write_data = 0;
	fd_set read_fds;
	fd_set write_fds;
	fd_set except_fds;
	FD_ZERO(&r_fds);
	FD_ZERO(&w_fds);
	FD_ZERO(&e_fds);
	FD_SET(ListenSocket, &r_fds);
	FD_SET(ListenSocket, &w_fds);
	FD_SET(ListenSocket, &e_fds);
	FD_ZERO(&read_fds);
	FD_ZERO(&write_fds);
	FD_ZERO(&except_fds);
	//std::printf(" ListenSocket=%d\r\n", ListenSocket);
	struct timeval timeout;
	time_t nextPingTime = time(nullptr) + 20;
	int mts_time_disconnect = 0;
	int mts_disconnect_process = 0;
	vector<int> clientIDs;

	while (FD_ISSET(ListenSocket, &r_fds) || FD_ISSET(ListenSocket, &w_fds)) {
		read_fds = r_fds;
		write_fds = w_fds;
		except_fds = e_fds;
		timeout.tv_sec = 0;
		timeout.tv_usec = 100;
		if (MTS_FLAG == 1 && mts_error[run_mts_num % 10] == 1) {
			printf("MTS DISCONNECT\r\n");
			mts_disconnect = 0;
			run_mts_num++;
			mts_error[run_mts_num % 10] = 0;
			mts_disconnect_process = 1;
			mts_time_disconnect = time(nullptr);
		}


		if (MTS_FLAG == 1 && mts_disconnect_process == 1 && (time(nullptr) - mts_time_disconnect > 10)) {
			mts_disconnect_process = 0;
			clientIDs.clear();
			clientIDs = getClientIDs();
			for (int i = 0; i < clientIDs.size(); i++) {
				if (wsClients[clientIDs[i]] == nullptr || wsClients[clientIDs[i]]->timestamp > 0)  continue;
				wsClient* wsclient = wsClients[clientIDs[i]];
				if (wsclient->mts_process == 1 && wsclient->ticket_process == true) {
					for (int j = 0; j < wsclient->tickets_number; j++) {
						if (wsclient->tickets[j]->accept_code < 0) continue;
						if (wsclient->tickets[j]->mts == 1) continue;
						wsclient->tickets[j]->accept_code = -102;
					}
					wsclient->mts_process = 3;
				}
			}


			hThread3[run_mts_num % 10] = CreateThread(nullptr, 16777216, &MTSPublishThread, 0, THREAD_TERMINATE, &dwThreadID3[run_mts_num % 10]);
			hThread9[run_mts_num % 10] = CreateThread(nullptr, 16777216, &MTSConsumeThread, 0, THREAD_TERMINATE, &dwThreadID9[run_mts_num % 10]);

		}




		if (select(fdmax + 1, &read_fds, &write_fds, nullptr, &timeout) != SOCKET_ERROR)
		{
			if (recovery_state == 0)
				for (int i = 0; i <= fdmax; i++) {
					//FD_CLR(i, &read_fds);


					//|| (socketIDmap.find(i) != socketIDmap.end() &&SSL_pending(wsClients[socketIDmap[i]]->ssl))
					if (FD_ISSET(i, &read_fds)) {

						//printf("dddd\r\n");
						if (i == ListenSocket) {

							socklen_t addrlen = sizeof(cli_addr);
							int ClientSocket = accept(ListenSocket, (struct sockaddr*)&cli_addr, &addrlen);
							if (ClientSocket != INVALID_SOCKET) {
								/* add new client */
								ssl = SSL_new(ctx);
								SSL_set_fd(ssl, ClientSocket);
								SSL_set_accept_state(ssl);

								/*							cert = SSL_get_peer_certificate(ssl);
								if (cert != nullptr) {
								std::printf("Client certificate:\n");

								str = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
								std::printf("\t subject: %s\n", str);
								OPENSSL_free(str);

								str = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
								std::printf("\t issuer: %s\n", str);
								OPENSSL_free(str);

								//We could do all sorts of certificate verification stuff here before
								//deallocating the certificate.

								X509_free(cert);
								}
								else {
								//printf("Client does not have certificate.\n");
								}
								*/
								wsAddClient(ClientSocket, ssl, cli_addr.sin_addr);
								//ssl = nullptr;
								//std::printf("New connection from %s on socket %d\n", inet_ntoa(cli_addr.sin_addr), ClientSocket);
							}

						}
						else {
							//retValue = 0;

							if (socketIDmap.find(i) != socketIDmap.end()) {
								//std::printf("start read from socket %d\r\n", i);
								int nbytes = SSL_read(wsClients[socketIDmap[i]]->ssl, buf, sizeof(buf));

								//printf("Read Cicle wsClients[%d]->ready_state=%d last_message_queue=%d nbytes=%d ssl_error=%d\r\n", socketIDmap[i], wsClients[socketIDmap[i]]->ready_state, wsClients[socketIDmap[i]]->last_message_queue, nbytes, SSL_get_error(ssl, nbytes));
								//std::printf("read from socket %d %d bytes \r\n", i, nbytes);
								if (nbytes == 0) {


									int ssl_error = SSL_get_error(ssl, nbytes);
									if (ssl_error == SSL_ERROR_WANT_WRITE) {
										//std::printf("SSL_read wants write (returned 0)\n");
										continue;
									}

									if (ssl_error == SSL_ERROR_WANT_READ) {
										//std::printf("SSL_read wants read (returned 0)\n");
										// wants_tcp_read is always 1;
										continue;
									}

									if (ssl_error == SSL_ERROR_SYSCALL) {
										//std::printf("SSL_read syscall error (returned 0)\r\n");

										//if(wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CLOSING && wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CLOSED) 
										//if (wsClients[socketIDmap[i]]->ready_state == WS_READY_STATE_CONNECTING) continue;
									}
									/*		else {

									long error = ERR_get_error();
									const char* error_str = ERR_error_string(error, nullptr);
									delete[] error_str;
									//std::printf("could not SSL_read (returned 0): %s\n", error_str);
									}*/

								}
								else if (nbytes < 0) {
									int ssl_error = SSL_get_error(ssl, nbytes);
									if (ssl_error == SSL_ERROR_WANT_WRITE) {
										//std::printf("SSL_read wants write (returned -1)\n");
										continue;
									}

									if (ssl_error == SSL_ERROR_WANT_READ) {
										//std::printf("SSL_read wants read (returned -1)\n");
										// wants_tcp_read is always 1;
										continue;
									}

									if (ssl_error == SSL_ERROR_SYSCALL) {
										//std::printf("SSL_read syscall error (returned -1)\r\n");

										if (wsClients[socketIDmap[i]]->ready_state == WS_READY_STATE_CONNECTING) continue;
										//printf("clientID=%d\r\n", socketIDmap[i]);
										//printf("wsClients[socketIDmap[i]]->ready_state=%d\r\n", wsClients[socketIDmap[i]]->ready_state);
										//if (wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CLOSING && wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CLOSED)
										//	if (wsClients[socketIDmap[i]]->ready_state == WS_READY_STATE_CONNECTING)
										//	continue;
										//continue;
									}
									else {

										std::printf("could not SSL_read (returned -1) socketIDmap[%d]=%d\n", i, socketIDmap[i]);
										wsRemoveClient(socketIDmap[i]);
										long error = ERR_get_error();
										const char* error_str = ERR_error_string(error, nullptr);
										std::printf("could not SSL_read (returned -1) %s\n", error_str);
										//delete[] error_str;
										continue;

									}


								}

								if (nbytes < 0) {


									if (wsClients[socketIDmap[i]]->ready_state == WS_READY_STATE_CLOSING || wsClients[socketIDmap[i]]->ready_state == WS_READY_STATE_CLOSED)
										wsRemoveClient(socketIDmap[i]); else
										wsSendClientClose(socketIDmap[i], WS_STATUS_PROTOCOL_ERROR);

									//wsRemoveClient(socketIDmap[i]);
								}
								else if (nbytes == 0) {
									wsRemoveClient(socketIDmap[i]);

								}
								else {
									if (!wsProcessClient(socketIDmap[i], buf, nbytes))
									{
										wsSendClientClose(socketIDmap[i], WS_STATUS_PROTOCOL_ERROR);
									}

								}
							}
						}

					}




					if (FD_ISSET(i, &write_fds)) {

						if (i == ListenSocket) {
							/**/
						}
						else {

							if (socketIDmap.find(i) != socketIDmap.end()) {
								type_of_write_data = 0;


								int nbytes = 0;


								if (wsClients[socketIDmap[i]]->ready_state == WS_READY_STATE_DATA_ERROR || wsClients[socketIDmap[i]]->ready_state == HTTPS_STATE_OPEN || wsClients[socketIDmap[i]]->ready_state == HTTPS_STATE_READ || wsClients[socketIDmap[i]]->ready_state == HTTPS_STATE_WRITE) {
									if (wsClients[socketIDmap[i]]->ready_state == WS_READY_STATE_DATA_ERROR || time(nullptr) - wsClients[socketIDmap[i]]->https_time > 20) {
										wsRemoveClient(socketIDmap[i]);
										//closesocket(i);
										continue;

									}
									else if (wsClients[socketIDmap[i]]->ready_state == HTTPS_STATE_WRITE && wsClients[socketIDmap[i]]->https_write_buffer_length > 0) {
										type_of_write_data = 13;
										nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->https_write_buffer, wsClients[socketIDmap[i]]->https_write_buffer_length);

									}
								}

								else if (wsClients[socketIDmap[i]]->message_close != nullptr) {
									type_of_write_data = 2;
									nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->message_close, wsClients[socketIDmap[i]]->message_close_length);

								}
								else if (wsClients[socketIDmap[i]]->ready_state == WS_READY_STATE_CONNECTING && wsClients[socketIDmap[i]]->handshake_message != nullptr) {
									type_of_write_data = 1;

									nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->handshake_message, strlen(wsClients[socketIDmap[i]]->handshake_message));

								}

								else if (wsClients[socketIDmap[i]]->step_buffer_len_1 == -1 && wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CONNECTING) {
									if (current_data_step_1 != -1) {
										type_of_write_data = 6;
										current = current_data_step_1.load();
										wsClients[socketIDmap[i]]->step_buffer_1 = array_data_step_1[current];
										wsClients[socketIDmap[i]]->step_buffer_len_1 = data_step_len_1[current];


										nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->step_buffer_1, wsClients[socketIDmap[i]]->step_buffer_len_1);
									}


								}
								else if (wsClients[socketIDmap[i]]->step_buffer_len_1 > 0 && wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CONNECTING) {
									type_of_write_data = 6;
									nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->step_buffer_1, wsClients[socketIDmap[i]]->step_buffer_len_1);
								}
								else if (wsClients[socketIDmap[i]]->step_buffer_len_2 == -1 && wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CONNECTING) {
									if (current_data_step_2 != -1) {
										type_of_write_data = 7;
										current = current_data_step_2.load();
										wsClients[socketIDmap[i]]->step_buffer_2 = array_data_step_2[current];
										wsClients[socketIDmap[i]]->step_buffer_len_2 = data_step_len_2[current];
										nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->step_buffer_2, wsClients[socketIDmap[i]]->step_buffer_len_2);
									}


								}
								else if (wsClients[socketIDmap[i]]->step_buffer_len_2 > 0 && wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CONNECTING) {
									type_of_write_data = 7;
									nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->step_buffer_2, wsClients[socketIDmap[i]]->step_buffer_len_2);
								}

								else if (wsClients[socketIDmap[i]]->ticket_send == true && wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CONNECTING) {
									type_of_write_data = 11;
									nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->send_ticket_message, wsClients[socketIDmap[i]]->send_ticket_message_length);
								}
								else if (wsClients[socketIDmap[i]]->plus_send == true && wsClients[socketIDmap[i]]->plus_create == false && wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CONNECTING) {
									type_of_write_data = 8;
									nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->plus_message, wsClients[socketIDmap[i]]->plus_message_length);
								}
								else if (wsClients[socketIDmap[i]]->outright_send == true && wsClients[socketIDmap[i]]->outright_create == false && wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CONNECTING) {
									type_of_write_data = 9;
									nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->outright_message, wsClients[socketIDmap[i]]->outright_message_length);
								}
								else if (wsClients[socketIDmap[i]]->last_message_queue > wsClients[socketIDmap[i]]->last_message_queue_socket && wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CONNECTING) {
									type_of_write_data = 5;
									nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->message_queue[wsClients[socketIDmap[i]]->last_message_queue_socket % QUEUE_LENGTH], wsClients[socketIDmap[i]]->message_queue_length[wsClients[socketIDmap[i]]->last_message_queue_socket % QUEUE_LENGTH]);
								}
								else if (wsClients[socketIDmap[i]]->client_send == true && wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CONNECTING) {
									type_of_write_data = 10;
									nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->send_client_message, wsClients[socketIDmap[i]]->send_client_message_length);
								}
								else if (wsClients[socketIDmap[i]]->last_bet_message_queue > wsClients[socketIDmap[i]]->last_bet_message_queue_socket && wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CONNECTING) {
									type_of_write_data = 12;

									nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->bet_message_queue[wsClients[socketIDmap[i]]->last_bet_message_queue_socket % QUEUE_LENGTH], wsClients[socketIDmap[i]]->bet_message_queue_length[wsClients[socketIDmap[i]]->last_bet_message_queue_socket % QUEUE_LENGTH]);
								}
								else if (wsClients[socketIDmap[i]]->message_pong != nullptr) {
									type_of_write_data = 3;
									nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->message_pong, wsClients[socketIDmap[i]]->message_pong_length);

								}
								else if (wsClients[socketIDmap[i]]->message_ping != nullptr) {
									type_of_write_data = 4;
									nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->message_ping, wsClients[socketIDmap[i]]->message_ping_length);

								}

								if (type_of_write_data == 0) continue;
								//if (type_of_write_data == 12)
								//printf("type_of_write_data=%d\r\n", type_of_write_data);
								///	printf("wsClients[%d]->ready_state=%d last_message_queue=%d last_message_queue_socket=%d nbytes=%d type_of_write_data=%d ssl_error=%d\r\n", socketIDmap[i], wsClients[socketIDmap[i]]->ready_state, wsClients[socketIDmap[i]]->last_bet_message_queue % QUEUE_LENGTH, wsClients[socketIDmap[i]]->last_bet_message_queue_socket % QUEUE_LENGTH, nbytes, type_of_write_data, SSL_get_error(ssl, nbytes));


								if (nbytes == 0) {
									int ssl_error = SSL_get_error(ssl, nbytes);
									if (ssl_error == SSL_ERROR_WANT_WRITE) {
										//std::printf("SSL_write wants write (returned 0)\r\n");
										continue;
									}

									if (ssl_error == SSL_ERROR_WANT_READ) {
										//std::printf("SSL_write 0 wants read (returned 0)\r\n");
										// wants_tcp_read is always 1;

										continue;
									}

									/*if (ssl_error == SSL_ERROR_SYSCALL) {
									//std::printf("SSL_write syscall error (returned 0)\r\n");
									//wsClients[socketIDmap[i]]->flag = false;

									}
									else {


									long error = ERR_get_error();
									const char* error_str = ERR_error_string(error, nullptr);
									delete[] error_str;
									}
									//std::printf("could not SSL_write (returned 0): %s\n", error_str);
									*/


								}
								else if (nbytes < 0) {
									//printf("wsClients[socketIDmap[i]]->message_queue_length[0]=%d\r\n", wsClients[socketIDmap[i]]->message_queue_length[0]);
									int ssl_error = SSL_get_error(ssl, nbytes);
									if (ssl_error == SSL_ERROR_WANT_WRITE) {
										//std::printf("SSL_write wants write (returned -1)\r\n");
										continue;
									}

									if (ssl_error == SSL_ERROR_WANT_READ) {
										//std::printf("SSL_write wants read (returned -1)\r\n");
										//wants_tcp_read is always 1;
										continue;
									}

									if (ssl_error == SSL_ERROR_SYSCALL) {
										//std::printf("SSL_write syscall error (returned -1)\r\n");
										if (type_of_write_data < 2 && type_of_write_data > 4) continue;


									}
									/*
									if (type_of_write_data != 5 && type_of_write_data != 6 && type_of_write_data != 7 && type_of_write_data != 8 && type_of_write_data != 9) {
									long error = ERR_get_error();
									const char* error_str = ERR_error_string(error, nullptr);
									//std::printf("could not SSL_write (returned -1): %s\n", error_str);
									delete[] error_str;

									}*/




								}


								if (nbytes < 0) {

									if (type_of_write_data == 2)
										wsRemoveClient(socketIDmap[i]);
									else {
										wsSendClientClose(socketIDmap[i], WS_STATUS_PROTOCOL_ERROR);
									}
									//wsClients[socketIDmap[i]]->flag = false;

								}
								else if (nbytes == 0) {
									if (type_of_write_data == 2) wsRemoveClient(socketIDmap[i]);
									else {
										wsSendClientClose(socketIDmap[i], WS_STATUS_PROTOCOL_ERROR);
									}

									//wsClients[socketIDmap[i]]->flag = false;

								}
								else {

									if (type_of_write_data == 1) {
										wsClients[socketIDmap[i]]->ready_state = WS_READY_STATE_OPEN;
										delete[] wsClients[socketIDmap[i]]->handshake_message;
										wsClients[socketIDmap[i]]->handshake_message = nullptr;
										if (current_data_step_1 != -1) {
											current = current_data_step_1.load();
											wsClients[socketIDmap[i]]->step_buffer_1 = array_data_step_1[current];
											wsClients[socketIDmap[i]]->step_buffer_len_1 = data_step_len_1[current];
										}
										if (callOnOpen != nullptr) callOnOpen(socketIDmap[i]);
									}

									if (type_of_write_data == 2) {
										delete[] wsClients[socketIDmap[i]]->message_close; wsClients[socketIDmap[i]]->message_close = nullptr;
										wsClients[socketIDmap[i]]->message_close_length = 0;
										wsRemoveClient(socketIDmap[i]);

									}

									if (type_of_write_data == 3) {
										delete[] wsClients[socketIDmap[i]]->message_pong; wsClients[socketIDmap[i]]->message_pong = nullptr;
										wsClients[socketIDmap[i]]->message_pong_length = 0;

									}
									if (type_of_write_data == 4) {
										delete[] wsClients[socketIDmap[i]]->message_ping; wsClients[socketIDmap[i]]->message_ping = nullptr;
										wsClients[socketIDmap[i]]->message_ping_length = 0;

									}


									if (type_of_write_data == 5) {
										if (wsClients[socketIDmap[i]]->message_queue[wsClients[socketIDmap[i]]->last_message_queue_socket % QUEUE_LENGTH] != nullptr)
											delete[] wsClients[socketIDmap[i]]->message_queue[wsClients[socketIDmap[i]]->last_message_queue_socket % QUEUE_LENGTH];
										wsClients[socketIDmap[i]]->message_queue[wsClients[socketIDmap[i]]->last_message_queue_socket % QUEUE_LENGTH] = nullptr;
										wsClients[socketIDmap[i]]->message_queue_length[wsClients[socketIDmap[i]]->last_message_queue_socket % QUEUE_LENGTH] = 0;
										wsClients[socketIDmap[i]]->last_message_queue_socket++;
									}

									if (type_of_write_data == 12) {
										if (wsClients[socketIDmap[i]]->bet_message_queue[wsClients[socketIDmap[i]]->last_bet_message_queue_socket % QUEUE_LENGTH] != nullptr)
											delete[] wsClients[socketIDmap[i]]->bet_message_queue[wsClients[socketIDmap[i]]->last_bet_message_queue_socket % QUEUE_LENGTH];
										wsClients[socketIDmap[i]]->bet_message_queue[wsClients[socketIDmap[i]]->last_bet_message_queue_socket % QUEUE_LENGTH] = nullptr;
										wsClients[socketIDmap[i]]->bet_message_queue_length[wsClients[socketIDmap[i]]->last_bet_message_queue_socket % QUEUE_LENGTH] = 0;
										wsClients[socketIDmap[i]]->last_bet_message_queue_socket++;
									}

									if (type_of_write_data == 6) {
										wsClients[socketIDmap[i]]->step_buffer_1 = nullptr;
										wsClients[socketIDmap[i]]->step_buffer_len_1 = 0;
										if (current_data_step_2 != -1) {
											current = current_data_step_2.load();
											wsClients[socketIDmap[i]]->step_buffer_2 = array_data_step_2[current];
											wsClients[socketIDmap[i]]->step_buffer_len_2 = data_step_len_2[current];
										}

									}

									if (type_of_write_data == 7) {
										wsClients[socketIDmap[i]]->step_buffer_2 = nullptr;
										wsClients[socketIDmap[i]]->step_buffer_len_2 = 0;
									}

									if (type_of_write_data == 8) {
										//printf("wsClients[%d]->plus=%d clean\r\n", socketIDmap[i], wsClients[socketIDmap[i]]->plus);
										if (wsClients[socketIDmap[i]]->plus_message != nullptr) delete[] wsClients[socketIDmap[i]]->plus_message;
										wsClients[socketIDmap[i]]->plus = "";
										wsClients[socketIDmap[i]]->plus_message = nullptr;
										wsClients[socketIDmap[i]]->plus_message_length = 0;
										wsClients[socketIDmap[i]]->plus_send = false;

									}

									if (type_of_write_data == 9) {
										//printf("wsClients[%d]->outright=%d clean\r\n", socketIDmap[i], wsClients[socketIDmap[i]]->outright);
										if (wsClients[socketIDmap[i]]->outright_message != nullptr) delete[] wsClients[socketIDmap[i]]->outright_message;
										wsClients[socketIDmap[i]]->outright = 0;
										wsClients[socketIDmap[i]]->outright_message = nullptr;
										wsClients[socketIDmap[i]]->outright_message_length = 0;
										wsClients[socketIDmap[i]]->outright_send = false;

									}
									if (type_of_write_data == 10) {

										//printf("wsClients[%d]->outright=%d clean\r\n", socketIDmap[i], wsClients[socketIDmap[i]]->outright);
										if (wsClients[socketIDmap[i]]->send_client_message != nullptr) delete[] wsClients[socketIDmap[i]]->send_client_message;
										wsClients[socketIDmap[i]]->send_client_message = nullptr;
										wsClients[socketIDmap[i]]->send_client_message_length = 0;
										wsClients[socketIDmap[i]]->client_send = false;



									}

									if (type_of_write_data == 11) {
										//printf("wsClients[%d]->outright=%d clean\r\n", socketIDmap[i], wsClients[socketIDmap[i]]->outright);
										if (wsClients[socketIDmap[i]]->send_ticket_message != nullptr) delete[] wsClients[socketIDmap[i]]->send_ticket_message;
										wsClients[socketIDmap[i]]->send_ticket_message = nullptr;
										wsClients[socketIDmap[i]]->send_ticket_message_length = 0;
										wsClients[socketIDmap[i]]->ticket_send = false;

									}


									if (type_of_write_data == 13) {
										if (wsClients[socketIDmap[i]]->https_write_buffer != nullptr) delete[] wsClients[socketIDmap[i]]->https_write_buffer; wsClients[socketIDmap[i]]->https_write_buffer = nullptr;
										wsClients[socketIDmap[i]]->https_write_buffer_length = 0;
										wsRemoveClient(socketIDmap[i]);
										//closesocket(i);

									}








								}


							}
						}

					}

				}
		}
		else printf("ListenSocket SOCKET_ERROR\r\n");


		if (time(nullptr) >= nextPingTime) {
			if (recovery_state == 0) wsCheckIdleClients();
			nextPingTime = time(nullptr) + 20;
		}

		/*if (callPeriodic != nullptr)
		callPeriodic();*/
	}


}
void webSocket::stopServer() {
	for (int i = 0; i < wsClients.size(); i++) {
		if (wsClients[i] != nullptr) {
			if (wsClients[i]->ready_state != WS_READY_STATE_CONNECTING)
				wsSendClientClose(i, WS_STATUS_GONE_AWAY);
			closesocket(wsClients[i]->socket);
			SSL_shutdown(wsClients[i]->ssl);
			SSL_free(wsClients[i]->ssl);


		}
	}

	closesocket(ListenSocket);
	SSL_CTX_free(ctx);
	wsClients.clear();
	socketIDmap.clear();
	FD_ZERO(&r_fds);
	FD_ZERO(&w_fds);
	fdmax = 0;
	WSACleanup();
}






char* CreateStep_1(int&);
char* CreateStep_2(int&);

void CreatePlus_2(wsClient*);
void CreateOutright_2(wsClient*);
void getSports(bool = false);
void getSportsTranslate(int);

void getEvents(time_t, int);
void getCategoriesTournaments();
void getCategoriesTournamentsTranslate(int);
int getTournament(Tournament*, bool, bool = false);
int getTournamentTranslate(Tournament*, int);
int getEventFixture(Event*, bool = false);
int get24HoursEventsFixture();
int getEventSummary(Event*);
int startRecovery();
void getMarkets();
void getMarketsTranslate(int);
void postBooked(int);
int getPlayer(Player*, bool = false);
int getPlayerTranslate(Player*, int);
int getCompetitor(Competitor*, bool = false);
int getCompetitorTranslate(Competitor*, int);
int getBetstops();
int  getVoidreasons();
int getMatchstatus();
int getVariantMarket(Market*, char*, bool = false, bool = false);
int getVariantMarketTranslate(Market*, int);
int httpsRequest(char*, char*, char*, int);
int httpRequest(char*, char*, char*, int);
int httpsRequestExtern(char*, char*, char*, int);
int httpsServer();
char** split(char*, char*);
void replace(char* &, char*, char*, bool = false);
void replace_competitor(char* &);
void replace_player(char* &);
void replace_substr(char* &, char*, char*);
void saveEventToDB(Event*, bool = false);
void loadEventsFromDB();
void saveMarketToDB(Market*, bool = false);
void deleteMarketFromDB(Market*);
void deleteTournamentFromDB(Tournament*);
void loadMarketsFromDB();
void saveTournamentToDB(Tournament*, bool = false);
void saveSportToDB(Sport*, bool = false);
void loadTournamentsFromDB();
void saveCategoryToDB(Category*, bool = false);
void loadCategoriesFromDB();
void saveCompetitorToDB(Competitor*, bool = false);
void loadCompetitorsFromDB();
void loadSportsFromDB();
void savePlayerToDB(Player*, bool = false);
void loadPlayersFromDB();
void loadClientsFromDB();
int saveClientToDB(Client*);
int updateClientToDB(Client*);
void addClientToHash(Client*);
void removeClientFromHash(Client*);
char* SendframeEncode(char*, int, int &);
void openHandler(int);
void closeHandler(int);
void messageHandler(int, string);
void radarMessageHandler(char*, int);
void periodicHandler();
void die(const char *, ...);
int die_on_error(int, char const*);
int die_on_amqp_error(amqp_rpc_reply_t, char const *);
void amqp_dump(void const *, size_t);
uint64_t now_microseconds(void);
//void microsleep(int);
void rabbitmqssl();
static void run(amqp_connection_state_t);

void rabbitmqssl_mts();
static void run_mts();
static void send_batch(amqp_connection_state_t, char const *, int, int);
static int rows_eq(int *, int *);
static void dump_row(long, int, int *);
inline void HistoryTicket(char* buffer, size_t& offset, Ticket* ticket) {
	writeInteger(buffer, offset, ticket->counter, 4);
	writeInteger(buffer, offset, ticket->action, 1);
	writeInteger(buffer, offset, ticket->status, 1);
	writeInteger(buffer, offset, ticket->timestamp / 1000, 4);
	writeInteger(buffer, offset, (int)(ticket->payout * 100 + 0.5), 4);
	writeInteger(buffer, offset, (int)(ticket->stake * 100 + 0.5), 4);
	writeInteger(buffer, offset, (int)(ticket->bonus * 100 + 0.5), 4);
	writeInteger(buffer, offset, (int)(ticket->returned * 100 + 0.5), 4);
	writeInteger(buffer, offset, ticket->type, 1);
	writeInteger(buffer, offset, ticket->system_selected, 1);
	writeInteger(buffer, offset, ticket->bets_number, 1);
	for (int m = 0; m < ticket->bets_number; m++) {
		writeInteger(buffer, offset, ticket->bets[m]->counter, 4);
		writeInteger(buffer, offset, ticket->bets[m]->event_status, 1);
		writeInteger(buffer, offset, ticket->bets[m]->selected_outcome_id, 1);
		writeInteger(buffer, offset, ticket->bets[m]->market_id, 4);
		writeInteger(buffer, offset, ticket->bets[m]->event_start_time, 4);
		writeInteger(buffer, offset, ticket->bets[m]->sport_id, 2);
		writeFloat(buffer, offset, ticket->bets[m]->accept_odd);
		writeString(buffer, offset, ticket->bets[m]->event_score);
		writeString(buffer, offset, ticket->bets[m]->event_set_scores);
		writeString(buffer, offset, ticket->bets[m]->event_game_score);
		writeString(buffer, offset, ticket->bets[m]->event_match_status_description);
		writeString(buffer, offset, ticket->bets[m]->event_match_time);
		writeString(buffer, offset, ticket->bets[m]->event_home_name);
		writeString(buffer, offset, ticket->bets[m]->event_away_name);
		writeString(buffer, offset, ticket->bets[m]->tournament_name);
		writeFloat(buffer, offset, ticket->bets[m]->settlement_odd);
		writeString(buffer, offset, ticket->bets[m]->summary);
		writeInteger(buffer, offset, ticket->bets[m]->status, 1);
		writeInteger(buffer, offset, ticket->bets[m]->type_radar, 1);
		writeInteger(buffer, offset, ticket->bets[m]->event_id, 4);
		writeInteger(buffer, offset, ticket->bets[m]->tournament_id, 4);
		writeInteger(buffer, offset, ticket->bets[m]->category_id, 4);
		writeInteger(buffer, offset, ticket->bets[m]->simple_id, 4);
		writeString(buffer, offset, ticket->bets[m]->outcome_name[ticket->bets[m]->selected_outcome_id]);
		writeString(buffer, offset, ticket->bets[m]->name);
		writeInteger(buffer, offset, ticket->bets[m]->specifier_number, 1);
		for (int j = 0; j < ticket->bets[m]->specifier_number; j++)
			writeString(buffer, offset, ticket->bets[m]->specifier_value[j]);


	}

}
inline void HistoryCalculationBet(char* buffer, size_t& offset, Bet* bet) {
	writeInteger(buffer, offset, 0, 1);//sistem request_id
	writeInteger(buffer, offset, bet->counter, 4);
	writeFloat(buffer, offset, bet->settlement_odd);
	writeString(buffer, offset, bet->summary);
	writeInteger(buffer, offset, bet->status, 1);
}
inline void HistoryCalculationTicket(char* buffer, size_t& offset, Ticket* ticket, double balance, double bets_amount) {
	writeInteger(buffer, offset, 0, 1);//sistem request_id
	writeInteger(buffer, offset, ticket->counter, 4);
	writeInteger(buffer, offset, (int)(ticket->payout * 100 + 0.5), 4);
	writeInteger(buffer, offset, ticket->status, 1);
	writeInteger(buffer, offset, (int)(balance * 100 + 0.5), 4);
	writeInteger(buffer, offset, (int)(bets_amount * 100 + 0.5), 4);
}
webSocket server;



// izzet: Reverse Lookup hash tables for Line objects

// we supply an id (market,event,tournament or simple) and return all the lines. so key is an int (id) and values is a vector of Line object ptrs.

//typedef unordered_map<int, unordered_set<int>*> id2lines_index;
enum LineCat { LC_EVENT, LC_TOURN, LC_SIMPLE };

void test_delete();
void delete_line(Line &);
void delete_line_cat(int, LineCat);
void btest_delete();
void bdelete_line(Line &);
void bdelete_line_cat(int, LineCat);


unordered_map<int, unordered_set<int>*> market2lines, bmarket2lines;   // lookup based on market_id
																	   // lookups based on event_id | tournament_id | simple_id
unordered_map<string, unordered_set<int>*> event2lines, bevent2lines;
//unordered_map<string, unordered_set<int>*> tourn2lines, btourn2lines;
//unordered_map<int, unordered_set<int>*> simple2lines, bsimple2lines;
unordered_map<string, int> compound2line_index, bcompound2line_index;    // (event_id | tournament_id | simple_id) + market_id + specifiers_value
																		 // whenever a new Line is created call this function to update reverse lookup tables
void insert_line(Line* line, const int line_index) {
	// hash table for case1: market_id. for all Line categories we update market2lines
	const int market_id = line->market_id;
	auto it = market2lines.find(market_id);   // market_id is the key
	if (it == market2lines.end()) {   // key not found, we are seeing this market_id the first time.
		market2lines[market_id] = new unordered_set<int>();  // so create an empty vector
	}
	market2lines[market_id]->insert(line_index);   // insert new line's index to the set
    auto cat_it = event2lines.find(line->getCatKey());   // cat_id is the key
	if (cat_it == event2lines.end()) {   // key not found, we are seeing this cat_id the first time.
		event2lines[line->getCatKey()] = new unordered_set<int>();  // so create an empty set
	}
	event2lines[line->getCatKey()]->insert(line_index);   // insert new line to the set
	compound2line_index[line->getCompoundKey()] = line_index;   // insert new line's index as value
	return;
}
void binsert_line(Line* line, const int line_index) {
	// hash table for case1: market_id. for all Line categories we update market2lines
	const int market_id = line->market_id;
	auto it = bmarket2lines.find(market_id);   // market_id is the key
	if (it == bmarket2lines.end()) {   // key not found, we are seeing this market_id the first time.
		bmarket2lines[market_id] = new unordered_set<int>();  // so create an empty vector
	}
	bmarket2lines[market_id]->insert(line_index);   // insert new line's index to the set
	auto cat_it = bevent2lines.find(line->getCatKey());   // cat_id is the key
	if (cat_it == bevent2lines.end()) {   // key not found, we are seeing this cat_id the first time.
		bevent2lines[line->getCatKey()] = new unordered_set<int>();  // so create an empty set
	}
	bevent2lines[line->getCatKey()]->insert(line_index);   // insert new line to the set
	bcompound2line_index[line->getCompoundKey()] = line_index;   // insert new line's index as value
	return;
}

/*
void test_delete() {
	auto t1 = chrono::high_resolution_clock::now();
	auto t2 = chrono::high_resolution_clock::now();
	uint64_t time_diff;
	int idx1 = rand() % lines_l;
	int idx2 = rand() % lines_l;
	Line* line1 = &(lines[idx1]);
	Line* line2 = &(lines[idx2]);
	int event_id = line2->event_id;
	if (idx1 == idx2 || event_id == 0 ||
		event2lines.find(event_id) == event2lines.end() || event2lines.find(line1->event_id) == event2lines.end()) {
		test_delete();
		return;
	}
	// cout << idx1 << " " << idx2 << " " << event_id << endl;
	cout << "Testing delete line(" << line1->name << ") ..." << endl;
	cout << "\t Its market(" << line1->market_id << ") has " << market2lines[line1->market_id]->size() << " lines now." << endl;
	cout << "\t Its event(" << line1->event_id << ") has " << event2lines[line1->event_id]->size() << " lines now." << endl;
	cout << "\t Deleting the line..." << endl;
	t1 = chrono::high_resolution_clock::now();
	delete_line(*line1);
	t2 = chrono::high_resolution_clock::now();
	time_diff = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
	cout << "\t Deletion took: " << (time_diff / 1e6) << " milliseconds" << endl;
	cout << "\t Its market has " << market2lines[line1->market_id]->size() << " lines now." << endl;
	cout << "\t Its event has " << event2lines[line1->event_id]->size() << " lines now." << endl;


	cout << endl << "Testing delete event_id(" << event_id << ") ..." << endl;
	t1 = chrono::high_resolution_clock::now();
	delete_line_cat(event_id, LC_EVENT);
	t2 = chrono::high_resolution_clock::now();
	time_diff = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
	cout << "\t Deletion took: " << (time_diff / 1e6) << " milliseconds" << endl;
	cout << "\t Testing if event's Line object are also deleted." << endl;
	auto it = compound2line_index.find(line2->getCompoundKey());
	if (it == compound2line_index.end()) {
		cout << "\t SUCCESS. Lines are also deleted." << endl;
	}
	else {
		cout << "\t FAILED. Lines are still in hash." << endl;
	}
	return;
}
void delete_line_cat(int cat_id, LineCat cat = LC_EVENT) {
	unordered_map<int, unordered_set<int>*>* cat2lines;
	string compound_key;
	// determine which hash we should update
	switch (cat) {
	case LC_EVENT:
		cat2lines = &event2lines;
		break;
	case LC_TOURN:
		cat2lines = &tourn2lines;
		break;
	case LC_SIMPLE:
		cat2lines = &simple2lines;
		break;
	default:
		cout << "Wrong value for LineCat used." << endl;
		return;
	}
	// delete from markets all Lines related to this category
	auto cat_it = cat2lines->find(cat_id);
	if (cat_it == cat2lines->end()) {
		cout << "Not existing in hash: " << cat_id << endl;
		return;
	}
	for (auto set_it = cat_it->second->begin(); set_it != cat_it->second->end(); set_it++) {
		int line_index = *set_it;
		Line* line_to_delete = &(lines[line_index]);
		market2lines[line_to_delete->market_id]->erase(line_index);
		// delete individual lines as well
		compound_key = line_to_delete->getCompoundKey();
		compound2line_index.erase(compound_key);
	}
	// delete the whole entry from related hash table  -- ASK: Shall we keep the index and only clear set?
	delete cat_it->second; // we created set with new so let's delete it
						   // cat2lines[cat_id] = nullptr;
	cat2lines->erase(cat_id);
	return;
}
// Just construct a Line object as in insert and call this function with that Line object 
// to delete the original one from hash tables 
void delete_line(Line &line) {
	int cat_id;
	string compound_key = line.getCompoundKey();

	auto line_it = compound2line_index.find(compound_key);
	if (line_it == compound2line_index.end()) {
		cout << "Line to be deleted not found.";
		return;
	}
	const int line_index = line_it->second;
	// hash table for case1: market_id. for all Line categories we update market2lines
	int market_id = line.market_id;
	auto market_it = market2lines.find(market_id);
	if (market_it != market2lines.end()) {   // key found
		market_it->second->erase(line_index); // delete from set
											  // if (market_it->second.size() == 0) {  // no more Lines for this market
											  // market2lines.erase(market_it);   // remove the whole market as well -- ASK: Shall we do this?
											  // }
	}

	// now let's determine the line category and the related lookup tables that should be updated
	unordered_map<int, unordered_set<int>*>* cat2lines;
	if (line.event_id > 0) {
		cat_id = line.event_id;
		cat2lines = &event2lines;
	}
	else if (line.tournament_id > 0) {
		cat_id = line.tournament_id;
		cat2lines = &tourn2lines;
	}
	else if (line.simple_id > 0) {
		cat_id = line.simple_id;
		cat2lines = &simple2lines;
	}
	else {
		cout << "Something wrong with this line (all ids 0): " << line.name << endl;
		return;
	}

	// update hash table for cases 2,3,4:  event, tournament or simple
	auto cat_it = cat2lines->find(cat_id);   // cat_id is the key
	if (cat_it != cat2lines->end()) {   // key found
		cat_it->second->erase(line_index);
		// if (cat_it->second.size() == 0) { // No more Lines for this event_id (tourn_id, simple_id)  
		// (*cat2lines).erase(cat_it);   // erase the hash entry as well -- ASK: Shall we do this?
		// }
	}

	// update hash table for cases 5,6,7:  market_id + (event_id | tournament_id | simple_id) + specifiers_value 
	// cout << "Deleted: " << line_it->first << " " << line_it->second << endl;
	compound2line_index.erase(line_it);
	// compound2line_index.erase(line.getCompoundKey());
	return;
}
void btest_delete() {
	auto t1 = chrono::high_resolution_clock::now();
	auto t2 = chrono::high_resolution_clock::now();
	uint64_t time_diff;
	int idx1 = rand() % lines_l;
	int idx2 = rand() % lines_l;
	Line* line1 = &(lines[idx1]);
	Line* line2 = &(lines[idx2]);
	int event_id = line2->event_id;
	if (idx1 == idx2 || event_id == 0 ||
		bevent2lines.find(event_id) == bevent2lines.end() || bevent2lines.find(line1->event_id) == bevent2lines.end()) {
		btest_delete();
		return;
	}
	// cout << idx1 << " " << idx2 << " " << event_id << endl;
	cout << "Testing delete line(" << line1->name << ") ..." << endl;
	cout << "\t Its market(" << line1->market_id << ") has " << bmarket2lines[line1->market_id]->size() << " lines now." << endl;
	cout << "\t Its event(" << line1->event_id << ") has " << bevent2lines[line1->event_id]->size() << " lines now." << endl;
	cout << "\t Deleting the line..." << endl;
	t1 = chrono::high_resolution_clock::now();
	bdelete_line(*line1);
	t2 = chrono::high_resolution_clock::now();
	time_diff = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
	cout << "\t Deletion took: " << (time_diff / 1e6) << " milliseconds" << endl;
	cout << "\t Its market has " << bmarket2lines[line1->market_id]->size() << " lines now." << endl;
	cout << "\t Its event has " << bevent2lines[line1->event_id]->size() << " lines now." << endl;


	cout << endl << "Testing delete event_id(" << event_id << ") ..." << endl;
	t1 = chrono::high_resolution_clock::now();
	bdelete_line_cat(event_id, LC_EVENT);
	t2 = chrono::high_resolution_clock::now();
	time_diff = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
	cout << "\t Deletion took: " << (time_diff / 1e6) << " milliseconds" << endl;
	cout << "\t Testing if event's Line object are also deleted." << endl;
	auto it = bcompound2line_index.find(line2->getCompoundKey());
	if (it == bcompound2line_index.end()) {
		cout << "\t SUCCESS. Lines are also deleted." << endl;
	}
	else {
		cout << "\t FAILED. Lines are still in hash." << endl;
	}
	return;
}
void bdelete_line_cat(int cat_id, LineCat cat = LC_EVENT) {
	unordered_map<int, unordered_set<int>*>* cat2lines;
	string compound_key;
	// determine which hash we should update
	switch (cat) {
	case LC_EVENT:
		cat2lines = &bevent2lines;
		break;
	case LC_TOURN:
		cat2lines = &btourn2lines;
		break;
	case LC_SIMPLE:
		cat2lines = &bsimple2lines;
		break;
	default:
		cout << "Wrong value for LineCat used." << endl;
		return;
	}
	// delete from markets all Lines related to this category
	auto cat_it = cat2lines->find(cat_id);
	if (cat_it == cat2lines->end()) {
		cout << "Not existing in hash: " << cat_id << endl;
		return;
	}
	for (auto set_it = cat_it->second->begin(); set_it != cat_it->second->end(); set_it++) {
		int line_index = *set_it;
		Line* line_to_delete = &(lines[line_index]);
		bmarket2lines[line_to_delete->market_id]->erase(line_index);
		// delete individual lines as well
		compound_key = line_to_delete->getCompoundKey();
		bcompound2line_index.erase(compound_key);
	}
	// delete the whole entry from related hash table  -- ASK: Shall we keep the index and only clear set?
	delete cat_it->second; // we created set with new so let's delete it
						   // cat2lines[cat_id] = nullptr;
	cat2lines->erase(cat_id);
	return;
}
// Just construct a Line object as in insert and call this function with that Line object 
// to delete the original one from hash tables 
void bdelete_line(Line &line) {
	int cat_id;
	string compound_key = line.getCompoundKey();

	auto line_it = bcompound2line_index.find(compound_key);
	if (line_it == bcompound2line_index.end()) {
		cout << "Line to be deleted not found.";
		return;
	}
	const int line_index = line_it->second;
	// hash table for case1: market_id. for all Line categories we update bmarket2lines
	int market_id = line.market_id;
	auto market_it = bmarket2lines.find(market_id);
	if (market_it != bmarket2lines.end()) {   // key found
		market_it->second->erase(line_index); // delete from set
											  // if (market_it->second.size() == 0) {  // no more Lines for this market
											  // bmarket2lines.erase(market_it);   // remove the whole market as well -- ASK: Shall we do this?
											  // }
	}

	// now let's determine the line category and the related lookup tables that should be updated
	unordered_map<int, unordered_set<int>*>* cat2lines;
	if (line.event_id > 0) {
		cat_id = line.event_id;
		cat2lines = &bevent2lines;
	}
	else if (line.tournament_id > 0) {
		cat_id = line.tournament_id;
		cat2lines = &btourn2lines;
	}
	else if (line.simple_id > 0) {
		cat_id = line.simple_id;
		cat2lines = &bsimple2lines;
	}
	else {
		cout << "Something wrong with this line (all ids 0): " << line.name << endl;
		return;
	}

	// update hash table for cases 2,3,4:  event, tournament or simple
	auto cat_it = cat2lines->find(cat_id);   // cat_id is the key
	if (cat_it != cat2lines->end()) {   // key found
		cat_it->second->erase(line_index);
		// if (cat_it->second.size() == 0) { // No more Lines for this event_id (tourn_id, simple_id)  
		// (*cat2lines).erase(cat_it);   // erase the hash entry as well -- ASK: Shall we do this?
		// }
	}

	// update hash table for cases 5,6,7:  market_id + (event_id | tournament_id | simple_id) + specifiers_value 
	// cout << "Deleted: " << line_it->first << " " << line_it->second << endl;
	bcompound2line_index.erase(line_it);
	// bcompound2line_index.erase(line.getCompoundKey());
	return;
}

*/



int reload_step_1 = 1;
int booking = 0;
//std::mutex _mutex;

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::sub_document;
using bsoncxx::builder::basic::sub_array;

mongocxx::instance instance{}; // This should be done only once.
							   //mongocxx::uri mongo_uri("mongodb://localhost:27017");

mongocxx::uri mongo_uri(MONGO_URI);
mongocxx::client mongo_client(mongo_uri);



void writeCategoriesDB();
void writeMarketsDB();
void writeTournamentsDB();
void writeSportsDB();
void writeCompetitorsDB();
void writePlayersDB();
void writeEventsDB();

// make this true if you want to populate MongoDB from scratch with the data in HDD (i.e. BetRadar directory)
const bool POPULATE_MONGO = false;
// when this is true each saveXXXToDB() function saves new XXX data to Mongo in addition to [instead of] file.

// when this is true each loadXXXFromFile() function loads data from Mongo. There is also a bool argument for such functions but
// this makes testing easier.
//const bool LOAD_FROM_MONGO = true;

//auto db = mongo_client["passion_bet"]; // SQL:  USE db
auto db = mongo_client["betdb"];

// to be called first time when creating clients collection in Mongo or to reset it
void createClientsCollection() {
	using namespace bsoncxx::builder;

	auto coll = db["clients"];
	coll.drop();

	// create unique indexes 
	mongocxx::options::index index_opt{};
	index_opt.unique(false);
	coll.create_index(stream::document{} << "name" << 1 << "surname" << 1 << "date_of_birth" << 1 << stream::finalize, index_opt);
	coll.create_index(stream::document{} << "email" << 1 << stream::finalize, index_opt);
	coll.create_index(stream::document{} << "login" << 1 << stream::finalize, index_opt);
	index_opt.unique(true);
	coll.create_index(stream::document{} << "phone" << 1 << stream::finalize, index_opt);

}
string registerErrorCodes[] = {
	"Success",                                          // 0
	"Login is in use by another client.",               // 1
	"Phone number was registered before.",              // 2
	"Email was registered before.",                     // 3
	"Name-Surname-Date_of_Birth was registered before.", // 4
	"phone number SMS verification error", // 5
	"age under 18" // 6

};


// To be implemented?
string encryptPassword(string passwd) {
	return passwd;
}
int max_client_id = 0;
int generateClientID(Currency currency, mongocxx::collection clientCollection) {
	max_client_id++;
	//return max_client_id;

	short first_digit = (short)currency;
	int client_id = first_digit * 1000000 + (rand() % 100000);
	bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result;
	try {
		bsoncxx::document::view_or_value query = bsoncxx::builder::stream::document{} << "_id" << client_id << bsoncxx::builder::stream::finalize;
		maybe_result = clientCollection.find_one(query);
		while (maybe_result) {  // search for a client_id that is not already used
			client_id = first_digit * 1000000 + (rand() % 100000);
			query = bsoncxx::builder::stream::document{} << "_id" << client_id << bsoncxx::builder::stream::finalize;
			maybe_result = clientCollection.find_one(query);
		}
	}
	catch (const mongocxx::exception& e) {
		cout << "A Mongo exception occurred in generateClientID: " << e.what() << endl;
	}

	return client_id;
}
bsoncxx::document::value buildClientDoc(Client* c) {
	bsoncxx::builder::basic::document builder{};
	builder.append(kvp("_id", c->client_id),
		kvp("phone", c->phone),
		kvp("anonymous", c->anonymous),
		kvp("domain", c->domain),
		kvp("last_domain", c->domain),
		kvp("password", c->password),
		kvp("currency", c->currency),
		kvp("balance", c->balance),
		kvp("bets_amount", c->bets_amount),
		kvp("email_newsletter", c->email_newsletter),
		kvp("timezone", c->timezone),
		kvp("last_timezone", c->timezone),
		kvp("name", c->name),
		kvp("surname", c->surname),
		kvp("date_of_birth", c->date_of_birth),
		kvp("country", c->country),
		kvp("country_id", c->country_id),
		kvp("region_id", c->region_id),
		kvp("city_id", c->city_id),
		kvp("region", c->region),
		kvp("city", c->city),
		kvp("email", c->email),
		kvp("login", c->login),
		kvp("postal_code", c->postal_code),
		kvp("address", c->address),
		kvp("group", c->group),
		kvp("language", c->language)
	);

	auto documents = bsoncxx::builder::basic::array{};
	for (int j = 0; j < c->documents_number; j++) {
		bsoncxx::document::value subdoc = bsoncxx::builder::stream::document{}
			<< "type" << c->documents_type[j] << "serial_number" << c->documents_serial_number[j] << "verification_timestamp" << c->documents_verification_timestamp[j]
			<< bsoncxx::builder::stream::finalize;
		documents.append(std::move(subdoc));
	}
	builder.append(kvp("documents", std::move(documents)));





	return builder.extract();

}
int saveClientToDB(Client* c) {

	auto coll = db["clients"];
	try {

		bool unique = false;
		while (unique == false) {
			c->client_id = generateClientID(c->currency, coll);
			unique = true;
			{   auto it = client_login_hash.find(to_string(c->client_id));
			if (it == client_login_hash.end()) {}
			else unique = false; }

		}

		coll.insert_one(buildClientDoc(c));
		addClientToHash(c);
	}
	catch (const mongocxx::exception& e) {
		cout << "An exception occurred in inserting a new Client into Mongo: " << e.what() << endl;
		return -1;
	}

	return 0;
}
int updateClientToDB(Client* c) {
	int ret_value = 0;
	auto coll = db["clients"];

	mongocxx::options::update* update = new mongocxx::options::update();
	update->upsert(true);

	try {

		coll.update_one(bsoncxx::builder::stream::document{} << "_id" << c->client_id << bsoncxx::builder::stream::finalize,
			bsoncxx::builder::stream::document{} << "$set" << buildClientDoc(c) << bsoncxx::builder::stream::finalize, *update);
	}


	catch (const mongocxx::exception& e) {
		delete update;
		std::cout << "An exception occurred in update_one client: " << e.what() << std::endl;
		return -1;
	}

	delete update;
	return 0;

	// return;
}
void updateClientBalanceToDB(Client* c) {
	auto coll = db["clients"];
	mongocxx::options::update* update = new mongocxx::options::update();
	update->upsert(true);
	try {
		coll.update_one(bsoncxx::builder::stream::document{} << "_id" << c->client_id << bsoncxx::builder::stream::finalize,
			bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document << "balance" << c->balance << "bets_amount" << c->bets_amount << bsoncxx::builder::stream::close_document << bsoncxx::builder::stream::finalize, *update);
	}
	catch (const mongocxx::exception& e) {
		cout << "An exception occurred in inserting a new Client into Mongo: " << e.what() << endl;
	}

	delete update;

}
void updateClientDomainAndTimezoneToDB(Client* c) {
	auto coll = db["clients"];
	mongocxx::options::update* update = new mongocxx::options::update();
	update->upsert(true);
	try {
		coll.update_one(bsoncxx::builder::stream::document{} << "_id" << c->client_id << bsoncxx::builder::stream::finalize,
			bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document << "last_timezone" << c->last_timezone << "last_domain" << c->last_domain << bsoncxx::builder::stream::close_document << bsoncxx::builder::stream::finalize, *update);
	}
	catch (const mongocxx::exception& e) {
		cout << "An exception occurred in inserting a new Client into Mongo: " << e.what() << endl;
	}

	delete update;

}
int updateClientPasswordToDB(Client* c) {
	auto coll = db["clients"];
	mongocxx::options::update* update = new mongocxx::options::update();
	update->upsert(true);
	try {
		coll.update_one(bsoncxx::builder::stream::document{} << "_id" << c->client_id << bsoncxx::builder::stream::finalize,
			bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document << "password" << c->password << bsoncxx::builder::stream::close_document << bsoncxx::builder::stream::finalize, *update);
	}
	catch (const mongocxx::exception& e) {
		cout << "An exception occurred in inserting a new Client into Mongo: " << e.what() << endl;
		delete update;	return -1;
	}

	delete update;
	return 0;

}
int updateClientRegistrationToDB(Client* c) {
	auto coll = db["clients"];
	mongocxx::options::update* update = new mongocxx::options::update();
	update->upsert(true);
	int ret_value = 0;
	bsoncxx::builder::basic::document builder{};
	if (c->anonymous == 1)
		builder.append(
			kvp("name", c->name),
			kvp("surname", c->surname),
			kvp("date_of_birth", c->date_of_birth)
		);
	c->anonymous = 0;
	builder.append(kvp("anonymous", c->anonymous),
		kvp("country", c->country),
		kvp("country_id", c->country_id),
		kvp("region_id", c->region_id),
		kvp("city_id", c->city_id),
		kvp("region", c->region),
		kvp("city", c->city),
		kvp("email", c->email),
		kvp("login", c->login),
		kvp("postal_code", c->postal_code),
		kvp("address", c->address),
		kvp("timezone", c->timezone)
	);

	try {
		coll.update_one(bsoncxx::builder::stream::document{} << "_id" << c->client_id << bsoncxx::builder::stream::finalize,
			bsoncxx::builder::stream::document{} << "$set" << builder.extract() << bsoncxx::builder::stream::finalize, *update);


	}

	catch (const mongocxx::exception& e) {
		cout << "An exception occurred in a update Client into Mongo: " << e.what() << endl;
		ret_value = -1;
	}


	delete update;
	return ret_value;

}
void updateMultiClientsBalanceDB(vector<Client*> clients) {
	using namespace bsoncxx::builder::stream;
	auto coll = db["clients"];
	mongocxx::bulk_write bulk{};
	try {
		for (auto c : clients) {
			mongocxx::model::update_one update_op{
				document{} << "_id" << c->client_id << finalize,
				document{} << "$set" << open_document << "balance" << c->balance << "bets_amount" << c->bets_amount
				<< close_document << finalize
			};
			bulk.append(update_op);
		}
		coll.bulk_write(bulk);
	}
	catch (const mongocxx::exception& e) {
		cout << "An exception occurred in updateMultiClientsBalanceDB: " << e.what() << endl;
	}
}
void createRandomClients() {
	int64_t start = timestamp();
	int num = 100000000;
	char* log = new char[20];
	client_login_hash.reserve(4 * num);
	for (int i = 0; i < num; i++) {
		Client* c = new Client();
		c->currency = Currency::EUR;// static_cast<Currency>(int)1;
		c->name = "Alexander";
		c->surname = "Cernavain";
		c->country = "Russia";
		c->region = "Penza";
		c->city = "Penza";
		c->balance = 1000000;
		_itoa(i, log, 10);
		c->login = log;
		c->password = "555555";
		c->postal_code = "2060";
		c->bets_amount = 0;
		c->domain = "bettest.passion.bet";
		c->date_of_birth = 546728000;
		c->address = "Talbuhina 4/5 ap. 50";
		c->phone = "+37379467317";
		c->email = "acernavn@sarki.pro";
		c->client_id = 5;
		c->timezone = 3;
		client_login_hash[c->login] = c;
	}



	printf("create %d clients time elapsed = %I64d ms\r\n ", num, (timestamp() - start));
	char* key = new char[20];
	start = timestamp();
	int x = 0;
	int y = 0;
	int random = 0;
	for (int j = 0; j < 100000; j++) {
		random = num * rand() / 1000;
		_itoa(random, key, 10);
		auto it = client_login_hash.find(key);
		if (it == client_login_hash.end()) { x++; }
		else { y++; };
	}

	printf("find =%d and nofind %d in %d clients time elapsed = %I64d ms\r\n", y, x, num, (timestamp() - start));
}
void addClientToHash(Client* c) {
	client_id_hash[c->client_id] = c;
	client_phone_hash[c->phone] = c;
	if (c->anonymous == 0) {
		if (c->login.length() > 0) client_login_hash[c->login] = c;
		if (c->email.length() > 0) client_email_hash[c->email] = c;
		if (c->name.length() > 0 && c->surname.length() > 0 && c->date_of_birth > 0) client_person_hash[c->getPersonKey()] = c;
	}

}
void removeClientFromHash(Client* c) {
	client_id_hash.erase(c->client_id);;
	client_phone_hash.erase(c->phone);
	if (c->anonymous == 0) {
		if (c->login.length() > 0) client_login_hash.erase(c->login);
		if (c->email.length() > 0) client_email_hash.erase(c->email);
		if (c->name.length() > 0 && c->surname.length() > 0 && c->date_of_birth > 0) client_person_hash.erase(c->getPersonKey());
	}

}
int registerClient(string name, string surname, int day, int month, int year, string country, string domain, string region, string city, string email, int email_newsletter, string phone,
	string login, string password, int currency, string postal_code, string address, string sms, int timezone, int step, wsClient* wsclient, int country_id, int region_id, int city_id) {

	Client* client = nullptr;;
	char date[64];
	switch (step) {

	case 1: {
		if (((timestamp() / 1000 - DMYtoSeconds(day, month, year)) / (18 * 365 * 24 * 60 * 60)) < 1) return 6;
		if (name.length() < 2 || surname.length() < 2) return 4;
		{	auto it = client_person_hash.find(name + surname + _itoa(DMYtoSeconds(day, month, year), date, 10));
		if (it == client_person_hash.end()) {}
		else return 4; }

		{ auto it = client_phone_hash.find(phone);
		if (it == client_phone_hash.end()) {}
		else return 2; }

		return 0;

		break; }
	case 2: {
		if (login.length() < 6) return 1;
		if (email.length() < 4 || email.length() < 4) return 3;

		{    auto it = client_email_hash.find(email);
		if (it == client_email_hash.end()) {}
		else return 3; }

		{   auto it = client_login_hash.find(login);
		if (it == client_login_hash.end()) {}
		else return 1; }


		{   auto it = client_phone_hash.find(login);
		if (it == client_phone_hash.end()) {}
		else return 1; }

		int client_id = atoi(login.c_str());
		if (client_id > 0)
		{
			auto it = client_phone_hash.find(login);
			if (it == client_phone_hash.end()) {}
			else return 1;
		}

		return 0;

		break; }
	case 3: {

		if (login.length() < 6 || login.length() > 25) return 1;
		if (email.length() < 4 || email.length() < 25) return 3;
		if (name.length() < 2 || surname.length() < 2) return 4;

		if (((timestamp() / 1000 - DMYtoSeconds(day, month, year)) / (18 * 365 * 24 * 60 * 60)) < 1) return 6;
		{	auto it = client_person_hash.find(name + surname + _itoa(DMYtoSeconds(day, month, year), date, 10));
		if (it == client_person_hash.end()) {}
		else return 4; }

		{	auto it = client_phone_hash.find(phone);
		if (it == client_phone_hash.end()) {}
		else return 2; }


		{	auto it = client_email_hash.find(email);
		if (it == client_email_hash.end()) {}
		else return 3; }

		{auto it = client_login_hash.find(login);
		if (it == client_login_hash.end()) {}
		else return 1;
		}

		{auto it = client_phone_hash.find(login);
		if (it == client_phone_hash.end()) {}
		else return 1;
		}

		int client_id = atoi(login.c_str());
		if (client_id > 0)
		{
			auto it = client_id_hash.find(client_id);
			if (it == client_id_hash.end()) {}
			else return 1;
		}

		if (sms.length() < 2) return 5;
		if (sms != wsclient->sms) return 5;

		break; }
	case 4: {

		auto it = client_phone_hash.find(phone);
		if (it == client_phone_hash.end()) {}
		else return 2;
		char* param = new char[sizeof(char*) + sizeof(char*) + 1];
		char* client_phone = new char[strlen(phone.c_str()) + 1];
		strcpy(client_phone, phone.c_str());
		memcpy(param, &client_phone, sizeof(char*));
		char* client_password = generatePasswordCode();
		memcpy(param + sizeof(char*), &client_password, sizeof(char*));
		password = client_password;
		DWORD dw;
		CreateThread(nullptr, 200000, &SMSProcessThread, (LPVOID)param, THREAD_TERMINATE, &dw);

		break; }
	case 5: {

		auto it = client_phone_hash.find(phone);
		if (it == client_phone_hash.end())  return 2;
		char* param = new char[sizeof(char*) + sizeof(char*) + 1];
		char* client_phone = new char[strlen(phone.c_str()) + 1];
		strcpy(client_phone, phone.c_str());
		memcpy(param, &client_phone, sizeof(char*));
		char* client_password = new char[strlen(it->second->password.c_str()) + 1];
		strcpy(client_password, it->second->password.c_str());
		memcpy(param + sizeof(char*), &client_password, sizeof(char*));
		DWORD dw;
		CreateThread(nullptr, 200000, &SMSProcessThread, (LPVOID)param, THREAD_TERMINATE, &dw);
		return 0;

		break; }
	case 6: {


		if (wsclient->client_id == -1) return 1;
		{auto it = client_id_hash.find(wsclient->client_id);
		if (it == client_id_hash.end()) { wsclient->client_id = -1; return 1; }
		client = it->second; }



		if (client->password != password) return 1;
		if (client->phone != phone) return 2;


		if (login.length() < 6 || login.length() > 25) return 1;
		if (email.length() < 4 || email.length() > 25) return 3;


		if (client->anonymous == 1) {
			if (name.length() < 2 || surname.length() < 2) return 4;
			if (((timestamp() / 1000 - DMYtoSeconds(day, month, year)) / (18 * 365 * 24 * 60 * 60)) < 1) return 6;
			auto it = client_person_hash.find(name + surname + _itoa(DMYtoSeconds(day, month, year), date, 10));
			if (it == client_person_hash.end()) {}
			else return 4;
		}

		if (client->email != email) {
			auto it = client_email_hash.find(email);
			if (it == client_email_hash.end()) {}
			else return 3;

		}

		if (client->login != login) {

			{auto it = client_login_hash.find(login);
			if (it == client_login_hash.end()) {}
			else return 1; }

			{auto it = client_phone_hash.find(login);
			if (it == client_phone_hash.end()) {}
			else return 1;
			}

			int client_id = atoi(login.c_str());
			if (client_id > 0)
			{
				auto it = client_id_hash.find(client_id);
				if (it == client_id_hash.end()) {}
				else return 1;
			}



		}



		if (sms.length() < 2) return 5;
		if (sms != wsclient->sms) return 5;
		break;
	}


	}


	Client* c = new Client();
	if (step == 6) *c = *client;
	if (step == 6 && c->anonymous == 1 || step != 6) {
		c->name = name;
		c->surname = surname;
		c->date_of_birth = DMYtoSeconds(day, month, year);
	}
	c->country = country;
	if (step != 6)	c->domain = domain;
	c->city = city;
	c->email = email;
	if (step != 6)	c->phone = phone;
	if (step != 6) { if (step == 4)	c->anonymous = 1; else c->anonymous = 0; }
	c->login = login;
	c->region = region;
	if (step != 6) c->password = encryptPassword(password);
	if (step != 6) c->currency = static_cast<Currency>(currency);
	c->postal_code = postal_code;
	c->address = address;
	if (step != 6) c->balance = 0;
	c->city_id = city_id;
	c->region_id = region_id;
	c->country_id = country_id;
	if (step != 6) c->bets_amount = 0;
	c->timezone = timezone;
	//if (step != 6) c->client_id = generateClientID(c->currency, coll);
	if (step == 6) {
		if (updateClientRegistrationToDB(c) == -1) {
			delete c;
			return 1;
		}
		removeClientFromHash(client); delete client; client = nullptr;
		addClientToHash(c); delete client; client = nullptr;
		return 0;
	}
	if (saveClientToDB(c) == -1) { delete c; return 1; }
	else return 0;
}

// Betradar data to Mongo docs

bsoncxx::document::value buildCategoryDoc(Category* c, bool translate = false) {
	bsoncxx::builder::basic::document builder{};
	builder.append(kvp("_id", c->id),
		kvp("sport_id", c->sport_id),
		kvp("sort", c->sort),
		kvp("name", c->name)
	);
	if (translate == true) {
		bsoncxx::builder::basic::document translations{};
		for (int j = 0; j < c->translation_num; j++) {
			bool create_language_field = false;
			bsoncxx::builder::basic::document language{};
			if (c->translation_name != nullptr && c->translation_name[j] != nullptr)
			{
				language.append(kvp("name", c->translation_name[j])), create_language_field = true;
			}
			if (create_language_field == true) translations.append(kvp(lang[j], std::move(language)));
		}
		builder.append(kvp("translations", std::move(translations)));
	}

	return builder.extract();
}
void writeCategoriesDB() {
	try {
		if (db.has_collection("categories")) {
			db["categories"].drop();  // clear collection
		}
		auto coll = db["categories"];

		vector<bsoncxx::document::value> docs;
		for (int i = 0; i < categories_l; i++) {
			docs.push_back(buildCategoryDoc(&categories[i]));
		}
		coll.insert_many(docs);
		cout << docs.size() << " category docs created..." << endl;
	}
	catch (const mongocxx::exception& e) {
		std::cout << "An exception occurred in writeMarketsDB: " << e.what() << std::endl;
	}
	return;
}
bsoncxx::document::value buildMarketDoc(Market* m, bool translate = false) {
	bsoncxx::builder::basic::document builder{};
	builder.append(kvp("market_id", m->id),
		kvp("type", m->type),
		kvp("line_type", m->line_type),
		kvp("name", m->name),
		kvp("variant", m->variant)
	);

	string variable_text = m->variable_text == nullptr ? "" : m->variable_text;

	builder.append(kvp("variable_text", variable_text));

	if (translate == true) {
		bsoncxx::builder::basic::document translations{};
		for (int j = 0; j < m->translation_num; j++) {
			bool create_language_field = false;
			bsoncxx::builder::basic::document language{};
			if (m->translation_name != nullptr && m->translation_name[j] != nullptr)
			{
				language.append(kvp("name", m->translation_name[j])), create_language_field = true;
			}

			if (m->translation_outcome_name != nullptr && m->translation_outcome_name[j] != nullptr)
			{
				auto outcomes_name = bsoncxx::builder::basic::array{};
				for (int l = 0; l < m->outcome_number; l++) {
					if (m->translation_outcome_name[j][l] != nullptr) outcomes_name.append(m->translation_outcome_name[j][l]);
					else outcomes_name.append(m->outcome_name[l]);
				};

				language.append(kvp("outcomes_name", std::move(outcomes_name)));
				create_language_field = true;

			}

			if (create_language_field == true) translations.append(kvp(lang[j], std::move(language)));
		}
		builder.append(kvp("translations", std::move(translations)));
	}


	auto outcomes = bsoncxx::builder::basic::array{};
	for (int j = 0; j < m->outcome_number; j++) {
		bsoncxx::document::value subdoc = bsoncxx::builder::stream::document{}
			<< "id" << m->outcome_id[j] << "name" << m->outcome_name[j]
			<< bsoncxx::builder::stream::finalize;
		// cout << j << ":::" << bsoncxx::to_json(subdoc.view()) << endl;
		outcomes.append(std::move(subdoc));
		// cout << j << ":::" << markets[i].outcome_id[j] << "," << markets[i].outcome_name[j] << endl;
		// cout << bsoncxx::to_json(outcomes.view()) << endl;
	}
	builder.append(kvp("outcomes", std::move(outcomes)));
	auto specifiers = bsoncxx::builder::basic::array{};
	for (int j = 0; j < m->specifier_number; j++) {
		auto subdoc = bsoncxx::builder::stream::document{}
		<< "name" << m->specifier_name[j] << "type" << m->specifier_type[j];
		if (m->specifier_description[j] != nullptr) {
			subdoc = subdoc << "description" << m->specifier_description[j];
		}
		auto subdoc_val = subdoc << bsoncxx::builder::stream::finalize;
		// cout << j << ":::" << bsoncxx::to_json(subdoc.view()) << endl;
		specifiers.append(std::move(subdoc_val));
	}
	builder.append(kvp("specifiers", std::move(specifiers)));
	return builder.extract();
}
void writeMarketsDB() {
	using namespace bsoncxx::builder;
	try {
		if (db.has_collection("markets")) {
			db["markets"].drop();  // clear collection
		}
		auto coll = db["markets"];

		mongocxx::options::index index_opt{};
		index_opt.unique(true);
		coll.create_index(stream::document{} << "market_id" << 1 << "variable_text" << 1 << stream::finalize, index_opt);

		vector<bsoncxx::document::value> docs;
		for (int i = 0; i < markets_l; i++) {
			bsoncxx::builder::basic::document builder{};
			docs.push_back(buildMarketDoc(&markets[i]));
		}
		// cout << docs.size() << " market docs ready to write ..." << endl;
		coll.insert_many(docs);
		cout << docs.size() << " market docs created ..." << endl;
	}
	catch (const mongocxx::exception& e) {
		std::cout << "An exception occurred in writeMarketsDB: " << e.what() << std::endl;
	}
	return;
}
bsoncxx::document::value buildTournamentDoc(Tournament *t, bool translate = false) {
	bsoncxx::builder::basic::document builder{};
	string name = t->name == nullptr ? "" : t->name;
	string season_name = t->season_name == nullptr ? "" : t->season_name;

	builder.append(kvp("type_radar", t->type_radar),
		kvp("tournament_id", t->id),
		kvp("season_id", t->season_id),
		kvp("simple_id", t->simple_id),
		kvp("sport_id", t->sport_id),
		kvp("category_id", t->category_id),
		kvp("sort", t->sort),
		kvp("start_date", t->start_date),
		kvp("end_date", t->end_date),
		kvp("name", name),
		kvp("season_name", season_name)
	);

	if (translate == true) {
		bsoncxx::builder::basic::document translations{};
		for (int j = 0; j < t->translation_num; j++) {
			bool create_language_field = false;
			bsoncxx::builder::basic::document language{};
			if (t->translation_name != nullptr && t->translation_name[j] != nullptr)
			{
				language.append(kvp("name", t->translation_name[j])), create_language_field = true;
			}

			if (t->translation_season_name != nullptr && t->translation_season_name[j] != nullptr)
			{
				language.append(kvp("season_name", t->translation_season_name[j])), create_language_field = true;
			}

			if (create_language_field == true) translations.append(kvp(lang[j], std::move(language)));

		}
		builder.append(kvp("translations", std::move(translations)));
	}
	return builder.extract();
}
void writeTournamentsDB() {
	using namespace bsoncxx::builder;
	try {
		if (db.has_collection("tournaments")) {
			db["tournaments"].drop();  // clear collection
		}
		auto coll = db["tournaments"];

		// create unique index for ids
		mongocxx::options::index index_opt{};
		index_opt.unique(true);
		coll.create_index(stream::document{} << "tournament_id" << 1 << "simple_id" << 1 << stream::finalize, index_opt);

		vector<bsoncxx::document::value> docs;
		for (int i = 0; i < tournaments_l; i++) {
			docs.push_back(buildTournamentDoc(&tournaments[i]));
		}
		coll.insert_many(docs);
		cout << docs.size() << " tournament docs created..." << endl;
	}
	catch (const mongocxx::exception& e) {
		std::cout << "An exception occurred in writeTournamentsDB: " << e.what() << std::endl;
	}
	return;
}
bsoncxx::document::value buildSportDoc(Sport* s, bool translate = false) {
	bsoncxx::builder::basic::document builder{};
	string name = s->name == nullptr ? "" : s->name;
	builder.append(kvp("_id", s->id),
		kvp("sort", s->sort),
		kvp("name", name)
	);

	if (translate == true) {
		bsoncxx::builder::basic::document translations{};
		for (int j = 0; j < s->translation_num; j++) {
			bool create_language_field = false;
			bsoncxx::builder::basic::document language{};
			if (s->translation_name != nullptr && s->translation_name[j] != nullptr)
			{
				language.append(kvp("name", s->translation_name[j])), create_language_field = true;
			}
			if (create_language_field == true) translations.append(kvp(lang[j], std::move(language)));
		}
		builder.append(kvp("translations", std::move(translations)));
	}
	return builder.extract();
}
void writeSportsDB() {
	try {
		if (db.has_collection("sports")) {
			db["sports"].drop();  // clear collection
		}
		auto coll = db["sports"];
		vector<bsoncxx::document::value> docs;
		for (int i = 0; i < sports_l; i++) {
			//printf("i=%d\r\n", i);
			docs.push_back(buildSportDoc(&sports[i]));
		}
		coll.insert_many(docs);
		cout << docs.size() << " sports docs created..." << endl;
	}
	catch (const mongocxx::exception& e) {
		std::cout << "An exception occurred in writeSportsDB: " << e.what() << std::endl;
	}
	return;
}
bsoncxx::document::value buildCompetitorDoc(Competitor *c, bool translate = false) {
	bsoncxx::builder::basic::document builder{};
	string country_name = c->country_name == nullptr ? "" : c->country_name;
	string name = c->name == nullptr ? "" : c->name;
	builder.append(kvp("_id", c->id),
		kvp("sport_id", c->sport_id),
		kvp("category_id", c->category_id),
		kvp("name", name),
		kvp("country_name", country_name),
		kvp("reference_id", c->reference_id)
	);

	if (translate == true) {
		bsoncxx::builder::basic::document translations{};
		for (int j = 0; j < c->translation_num; j++) {
			bool create_language_field = false;
			bsoncxx::builder::basic::document language{};
			if (c->translation_name != nullptr && c->translation_name[j] != nullptr)
			{
				language.append(kvp("name", c->translation_name[j])), create_language_field = true;
			}

			if (c->translation_country_name != nullptr && c->translation_country_name[j] != nullptr)
			{
				language.append(kvp("country_name", c->translation_country_name[j])), create_language_field = true;
			}

			if (create_language_field == true) translations.append(kvp(lang[j], std::move(language)));

		}
		builder.append(kvp("translations", std::move(translations)));
	}

	return builder.extract();
}
void writeCompetitorsDB() {
	try {
		/*	if (db.has_collection("competitors")) {
		db["competitors"].drop();  // clear collection
		}*/

		auto coll = db["competitors2"];

		vector<bsoncxx::document::value> docs;
		for (int i = 0; i < competitors_l; i++) {
			docs.push_back(buildCompetitorDoc(&competitors[i], true));
		}
		coll.insert_many(docs);
		cout << docs.size() << " competitor docs created..." << endl;
	}
	catch (const mongocxx::exception& e) {
		std::cout << "An exception occurred in writeCompetitorsDB: " << e.what() << std::endl;
	}
	return;
}
// TODO: Research if shorter field names in Mongo effects disk space used
bsoncxx::document::value buildPlayerDoc(Player* p, bool translate = false) {
	bsoncxx::builder::basic::document builder{};
	string name = p->name == nullptr ? "" : p->name;
	string full_name = p->full_name == nullptr ? "" : p->full_name;
	string type = p->type == nullptr ? "" : p->type;
	string nationality = p->nationality == nullptr ? "" : p->nationality;
	string country_code = p->country_code == nullptr ? "" : p->country_code;
	builder.append(kvp("_id", p->id),
		kvp("name", name),
		kvp("full_name", full_name),
		kvp("type", type),
		kvp("nationality", nationality),
		kvp("country_code", country_code),
		kvp("date_of_birth", p->date_of_birth),
		kvp("height", p->height),
		kvp("weight", p->weight),
		kvp("competitor_id", p->competitor_id),
		kvp("manager", p->manager),
		kvp("number", p->number)
	);

	if (translate == true) {
		bsoncxx::builder::basic::document translations{};
		for (int j = 0; j < p->translation_num; j++) {
			bool create_language_field = false;
			bsoncxx::builder::basic::document language{};
			if (p->translation_name != nullptr && p->translation_name[j] != nullptr)
			{
				language.append(kvp("name", p->translation_name[j])), create_language_field = true;
			}

			if (p->translation_full_name != nullptr && p->translation_full_name[j] != nullptr)
			{
				language.append(kvp("full_name", p->translation_full_name[j])), create_language_field = true;
			}

			if (p->translation_nationality != nullptr && p->translation_nationality[j] != nullptr)
			{
				language.append(kvp("nationality", p->translation_nationality[j])), create_language_field = true;
			}


			if (p->translation_type != nullptr && p->translation_type[j] != nullptr)
			{
				language.append(kvp("type", p->translation_type[j])), create_language_field = true;
			}


			if (create_language_field == true) translations.append(kvp(lang[j], std::move(language)));

		}
		builder.append(kvp("translations", std::move(translations)));
	}

	return builder.extract();
}
void writePlayersDB() {
	try {
		if (db.has_collection("players")) {
			db["players"].drop();  // clear collection
		}
		auto coll = db["players"];

		vector<bsoncxx::document::value> docs;
		for (int i = 0; i < players_l; i++) {
			docs.push_back(buildPlayerDoc(&players[i]));
		}
		coll.insert_many(docs);
		cout << docs.size() << " player docs created..." << endl;
	}
	catch (const mongocxx::exception& e) {
		std::cout << "An exception occurred in writePlayersDB: " << e.what() << std::endl;
	}
	return;
}
// for a given Event object builds a MongoDB doc representation (i.e. for saving into the DB)
bsoncxx::document::value buildEventDoc(Event* e, bool translate = false) {

	bsoncxx::builder::basic::document builder{};
	builder.append(kvp("_id", e->id),
		kvp("type_radar", e->type_radar),
		kvp("sport_id", e->sport_id),
		kvp("category_id", e->category_id),
		kvp("simple_id", e->simple_id),
		kvp("tournament_id", e->tournament_id),
		kvp("home_id", e->home_id),
		kvp("away_id", e->away_id),
		kvp("home_reference_id", e->home_reference_id),
		kvp("away_reference_id", e->away_reference_id),
		kvp("winner_id", e->winner_id),
		kvp("bo", e->bo),
		kvp("parent_id", e->parent_id),
		kvp("start_time", e->start_time),
		kvp("period_length", e->period_length),
		kvp("overtime_length", e->overtime_length),
		kvp("status", e->status),
		kvp("timestamp", e->timestamp),
		kvp("neutral_ground", e->neutral_ground),
		kvp("austrian_district", e->austrian_district),
		kvp("booked", e->booked),
		kvp("delayed_id", e->delayed_id),
		kvp("current_server", e->current_server),
		kvp("next_live_time", e->next_live_time)
	);


	string normalized;
	normalized = e->home_name == nullptr ? "" : e->home_name;
	builder.append(kvp("home_name", normalized));
	normalized = e->away_name == nullptr ? "" : e->away_name;
	builder.append(kvp("away_name", normalized));
	normalized = e->delayed_description == nullptr ? "" : e->delayed_description;
	builder.append(kvp("delayed_description", normalized));
	normalized = e->venue == nullptr ? "" : e->venue;
	builder.append(kvp("venue", normalized));
	normalized = e->tv_channels == nullptr ? "" : e->tv_channels;
	builder.append(kvp("tv_channels", normalized));
	if (translate == true) {
		bsoncxx::builder::basic::document translations{};
		for (int j = 0; j < e->translation_num; j++) {
			bool create_language_field = false;
			bsoncxx::builder::basic::document language{};
			if (e->translation_home_name != nullptr && e->translation_home_name[j] != nullptr)
			{
				language.append(kvp("home_name", e->translation_home_name[j])), create_language_field = true;
			}
			if (e->translation_away_name != nullptr && e->translation_away_name[j] != nullptr)
			{
				language.append(kvp("away_name", e->translation_away_name[j])), create_language_field = true;
			}
			if (e->translation_tv_channels != nullptr && e->translation_tv_channels[j] != nullptr)
			{
				language.append(kvp("tv_channels", e->translation_tv_channels[j])), create_language_field = true;
			}

			if (create_language_field == true) translations.append(kvp(lang[j], std::move(language)));

		}
		builder.append(kvp("translations", std::move(translations)));
	}
	// store string valued properties after normalization

	return builder.extract();
}
void writeEventsDB() {
	try {
		if (db.has_collection("events")) {
			db["events"].drop();  // clear collection
		}
		auto coll = db["events"];
		// create index for start_time
		bsoncxx::builder::basic::document index_doc{};
		index_doc.append(kvp("start_time", -1));  // -1 for descending index
		coll.create_index(std::move(index_doc.extract()));

		vector<bsoncxx::document::value> docs;
		for (int i = 0; i < events_l; i++) {
			docs.push_back(buildEventDoc(&events[i]));
		}
		coll.insert_many(docs);
		cout << docs.size() << " event docs created..." << endl;
	}
	catch (const mongocxx::exception& e) {
		std::cout << "An exception occurred in writeEventsDB: " << e.what() << std::endl;
	}
	return;
}
inline void mongo_str_to_buffer(bsoncxx::document::element str_field, char* &buffer) {
	string str_value;
	if (buffer != nullptr) { delete[] buffer; buffer = nullptr; }
	str_value = str_field.get_utf8().value.to_string();
	if (str_value.length() == 0) return;   // in case, field doesn't exist	
	buffer = new char[str_value.length() + 1];
	strncpy(buffer, str_value.c_str(), str_value.length());
	buffer[str_value.length()] = '\0';
	// cout << "DEBUG: " << *buffer << endl;
}
inline void mongo_str_to_buffer(bsoncxx::array::element str_field, char* &buffer) {
	string str_value;
	if (buffer != nullptr) { delete[] buffer; buffer = nullptr; }
	str_value = str_field.get_utf8().value.to_string();
	if (str_value.length() == 0) return;   // in case, field doesn't exist	
	buffer = new char[str_value.length() + 1];
	strncpy(buffer, str_value.c_str(), str_value.length());
	buffer[str_value.length()] = '\0';
	// cout << "DEBUG: " << *buffer << endl;
}


unordered_map<string, Ticket*> tickets = {};   // Key: ticket_id
unordered_map<string, Ticket*> tickets_oam = {}; //Key: mts_id
unordered_map<int, unordered_map<time_t, unordered_set<Ticket*>>> client_tickets = {};    // Key: client_id -> Value: hash (key : ticket date timestamp, value: ticket set)
unordered_map<int, unordered_set<Ticket*>> client_open_tickets = {};
unordered_map<string, unordered_set<Bet*>> bets = {};   // Key: bet.getCompoundKey() -> Value: Bet set
unordered_map<string, unordered_set<Bet*>> bets_ticket = {};   // Key: ticket_id


															   //unordered_set<Bet*> open_bets{};
															   //unordered_map<string, unordered_set<Bet*>> open_bets = {};
															   //vector<int*> unsettleds;
namespace std
{
	template<>
	struct hash<pair<int, int>>
	{
		size_t operator()(pair<int, int> const& p) const
		{
			//return hash<int>()(p.second);

			return hash<int>()(p.second) ^ hash<int>()(p.first);

			//return hash<long long>()(((long long)x.first) ^ (((long long)x.second) << 32));
		}
	};
}


unordered_set<pair<int, int>> recovery_statefull;
unordered_set<Bet*> open_bets = {};

int bets_counter = 0;
int tickets_counter = 0;

void changeTicketStatus(Ticket* ticket) {
	if (ticket->status == 1) {
		client_open_tickets[ticket->client_id].erase(ticket);
	}
	else {
		auto client_it = client_open_tickets.find(ticket->client_id);
		if (client_it == client_open_tickets.end()) {
			client_open_tickets[ticket->client_id] = {};
		}
		client_open_tickets[ticket->client_id].insert(ticket);
	}
}
void changeBetStatus(Bet* bet) {
	if (bet->status == 1)  open_bets.erase(bet);
	else  open_bets.insert(bet);

}
void recoveryStatefull() {
	recovery_statefull.clear();
	Bet* bet;

	for (unordered_set<Bet*>::iterator bet_it = open_bets.begin(); bet_it != open_bets.end(); ++bet_it)
	{
		bet = (*bet_it);
		if (bet->start_time > time(nullptr)) continue;
		int first;
		int second;

		if (bet->type_radar < 2) first = bet->event_id; else
			if (bet->type_radar == 2) first = bet->simple_id; else
				if (bet->type_radar == 3) first = bet->season_id; else
					if (bet->type_radar == 4) first = bet->tournament_id;
		second = bet->type_radar;
		//vec.push_back(make_pair(first, second));
		if (recovery_statefull.find(make_pair(first, second)) == recovery_statefull.end())
			recovery_statefull.insert(make_pair(first, second));

	}


};
vector<int64_t> clientGetAllTicketDates(Client* c) {
	vector<int64_t> dates = {};
	for (auto element : client_tickets[c->client_id]) {
		dates.push_back(static_cast<int64_t> (element.first));   // key is date of ticket
	}
	return dates;
}
unordered_set<Ticket*> clientGetTicketsOnDate(Client* c, time_t date_key) {
	/*tm ticket_date;
	ticket_date.tm_year = year - 1900;
	ticket_date.tm_mon = month - 1;
	ticket_date.tm_mday = day;
	time_t date_key = mktime(&ticket_date);*/
	return client_tickets[c->client_id][date_key];
}
vector<Ticket*> dynamicClientGetOpenTickets(Client* c) {
	vector<Ticket*> tickets = {};
	auto hash = client_tickets[c->client_id];
	for (auto pair : hash) {
		for (auto ticket : pair.second) {
			if (ticket->status == 0) {
				tickets.push_back(ticket);
			}
		}
	}
	return tickets;






}
unordered_set<Ticket*> clientGetOpenTickets(Client* c) {
	return client_open_tickets[c->client_id];
}
void insertTicketIntoHashes(Ticket* ticket, bool newTicket = false) {
	tickets[ticket->id] = ticket;
	time_t t = (time_t)ticket->timestamp / 1000;
	t += client_id_hash[ticket->client_id]->timezone * 3600;   // adjust for client's timezone
	struct tm ticket_time;
	localtime_s(&ticket_time, &t);
	ticket_time.tm_hour = 0;
	ticket_time.tm_min = 0;
	ticket_time.tm_sec = 0;
	time_t date_key = mktime(&ticket_time);


	auto client_it = client_tickets.find(ticket->client_id);
	if (client_it == client_tickets.end()) {
		client_tickets[ticket->client_id] = {};
		client_open_tickets[ticket->client_id] = {};
	}
	if (ticket->status == 0) {   // ticket may be a new one or loaded from db
		client_open_tickets[ticket->client_id].insert(ticket);
	}

	auto date_it = client_tickets[ticket->client_id].find(date_key);
	if (date_it == client_tickets[ticket->client_id].end()) {
		client_tickets[ticket->client_id][date_key] = {};
	}
	client_tickets[ticket->client_id][date_key].insert(ticket);
	string bet_key;
	for (int i = 0; i < ticket->bets_number; i++) {
		bet_key = ticket->bets[i]->getCompoundKey();
		auto bet_it = bets.find(bet_key);
		if (bet_it == bets.end()) {
			bets[bet_key] = {};
		}

		if (newTicket == true) open_bets.insert(ticket->bets[i]);

		bets[bet_key].insert(ticket->bets[i]);
	}
}
void populateBetFromMongo(Bet* bet, string bet_id) {
	using namespace bsoncxx::builder;
	auto coll = db["bets"];
	auto query_doc = stream::document{} << "_id" << bsoncxx::oid(bet_id) << stream::finalize;
	bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
		coll.find_one(query_doc.view());

	if (maybe_result) {
		auto bet_doc = maybe_result.get().view();
		// std::cout << bsoncxx::to_json(bet_doc) << std::endl;
		bet->id = bet_id;
		bet->counter = bet_doc["counter"].get_int32();
		bet->status = bet_doc["status"].get_int32();
		bet->language = bet_doc["language"].get_int32();
		bet->void_reason = bet_doc["void_reason"].get_int32();
		bet->certainy = bet_doc["certainy"].get_int32();
		bet->superceded_by = bet_doc["superceded_by"].get_int32();
		bet->bet_cancel = bet_doc["bet_cancel"].get_int32();
		bet->rollback_bet_cancel = bet_doc["rollback_bet_cancel"].get_int32();
		bet->rollback_bet_settlement = bet_doc["rollback_bet_settlement"].get_int32();
		bet->start_time = bet_doc["start_time"].get_int32();
		bet->end_time = bet_doc["end_time"].get_int32();
		//bet->line_id = bet_doc["line_id"].get_int32();
		bet->selected_outcome_id = bet_doc["selected_outcome_id"].get_int32();
		bet->tournament_id = bet_doc["tournament_id"].get_int32();
		bet->simple_id = bet_doc["simple_id"].get_int32();
		bet->season_id = bet_doc["season_id"].get_int32();
		bet->market_id = bet_doc["market_id"].get_int32();
		bet->event_id = bet_doc["event_id"].get_int32();
		bet->sport_id = bet_doc["sport_id"].get_int32();
		bet->category_id = bet_doc["category_id"].get_int32();
		bet->team = bet_doc["team"].get_int32();
		bet->favourite = bet_doc["favourite"].get_int32();
		bet->type = bet_doc["type"].get_int32();
		bet->type_radar = bet_doc["type_radar"].get_int32();
		bet->variant = bet_doc["variant"].get_int32();
		bet->place_odd = bet_doc["place_odd"].get_double();
		bet->accept_odd = bet_doc["accept_odd"].get_double();
		bet->settlement_odd = bet_doc["settlement_odd"].get_double();
		mongo_str_to_buffer(bet_doc["summary"], bet->summary);
		// string properties
		bet->ticket_id = bet_doc["ticket_id"].get_utf8().value.to_string();
		mongo_str_to_buffer(bet_doc["name"], bet->name);
		mongo_str_to_buffer(bet_doc["tournament_name"], bet->tournament_name);
		mongo_str_to_buffer(bet_doc["category_name"], bet->category_name);
		mongo_str_to_buffer(bet_doc["season_name"], bet->season_name);
		mongo_str_to_buffer(bet_doc["sport_name"], bet->sport_name);

		// fill outcomes
		{  // scoped not to carry variables
			bsoncxx::document::element mongo_arr = bet_doc["outcomes"];
			bsoncxx::array::view outcomes{ mongo_arr.get_array().value };
			if (!outcomes.empty()) {
				auto num_outcomes = std::distance(std::begin(outcomes), std::end(outcomes));
				bet->outcome_number = num_outcomes;
				bet->outcome_name = new char*[num_outcomes];
				bet->outcome_id = new int[num_outcomes];
				bet->outcome_active = new int[num_outcomes];
				bet->outcome_team = new int[num_outcomes];
				bet->outcome_odds = new float[num_outcomes];
				bet->outcome_probabilities = new float[num_outcomes];

				int outcome_index = 0;
				for (auto elt : outcomes) {
					bsoncxx::document::view subdoc = elt.get_document().value;
					bet->outcome_name[outcome_index] = nullptr;
					mongo_str_to_buffer(subdoc["name"], bet->outcome_name[outcome_index]);
					bet->outcome_id[outcome_index] = subdoc["id"].get_int32();
					bet->outcome_active[outcome_index] = subdoc["active"].get_int32();
					bet->outcome_team[outcome_index] = subdoc["team"].get_int32();
					bet->outcome_odds[outcome_index] = subdoc["odds"].get_double();
					bet->outcome_probabilities[outcome_index] = subdoc["probabilities"].get_double();
					outcome_index++;
				}
			}
			else {
				bet->outcome_number = 0;
			}
		}

		{
			bsoncxx::document::element mongo_arr = bet_doc["resultes"];
			bsoncxx::array::view resultes{ mongo_arr.get_array().value };
			if (!resultes.empty()) {
				auto num_resultes = std::distance(std::begin(resultes), std::end(resultes));
				bet->outcome_result = new int[num_resultes];
				bet->outcome_dead_heat_factor = new int[num_resultes];
				bet->outcome_void_factor = new int[num_resultes];

				int resulte_index = 0;
				for (auto elt : resultes) {
					bsoncxx::document::view subdoc = elt.get_document().value;
					bet->outcome_result[resulte_index] = subdoc["result"].get_int32();
					bet->outcome_void_factor[resulte_index] = subdoc["void_factor"].get_int32();
					bet->outcome_dead_heat_factor[resulte_index] = subdoc["dead_heat_factor"].get_int32();
					resulte_index++;
				}
			}











		}
		;
		// fill specifiers
		{  // scoped not to carry variables
			bsoncxx::document::element mongo_arr = bet_doc["specifiers"];
			bsoncxx::array::view specifiers{ mongo_arr.get_array().value };
			if (!specifiers.empty()) {
				auto num_specifiers = std::distance(std::begin(specifiers), std::end(specifiers));
				bet->specifier_number = num_specifiers;
				bet->specifier = new char*[num_specifiers];
				bet->specifier_value = new char*[num_specifiers];
				int specifier_index = 0;
				for (auto elt : specifiers) {
					bsoncxx::document::view subdoc = elt.get_document().value;
					bet->specifier[specifier_index] = nullptr;
					bet->specifier_value[specifier_index] = nullptr;
					mongo_str_to_buffer(subdoc["specifier"], bet->specifier[specifier_index]);
					mongo_str_to_buffer(subdoc["value"], bet->specifier_value[specifier_index]);
					specifier_index++;
				}
			}
			else {
				bet->specifier_number = 0;
			}
		}
		// fill extended specifiers
		{  // scoped not to carry variables
			bsoncxx::document::element mongo_arr = bet_doc["extended_specifiers"];
			bsoncxx::array::view extended_specifiers{ mongo_arr.get_array().value };
			if (!extended_specifiers.empty()) {
				auto num_specifiers = std::distance(std::begin(extended_specifiers), std::end(extended_specifiers));
				bet->extended_specifier_number = num_specifiers;
				bet->extended_specifier = new char*[num_specifiers];
				bet->extended_specifier_value = new char*[num_specifiers];
				int specifier_index = 0;
				for (auto elt : extended_specifiers) {
					bsoncxx::document::view subdoc = elt.get_document().value;
					bet->extended_specifier[specifier_index] = nullptr;
					bet->extended_specifier_value[specifier_index] = nullptr;
					mongo_str_to_buffer(subdoc["extended_specifier"], bet->extended_specifier[specifier_index]);
					mongo_str_to_buffer(subdoc["value"], bet->extended_specifier_value[specifier_index]);
					specifier_index++;
				}
			}
			else {
				bet->extended_specifier_number = 0;
			}
		}
		// fill event info
		auto event_doc = bet_doc["event_info"];
		bet->event_home_id = event_doc["home_id"].get_int32();
		bet->event_away_id = event_doc["away_id"].get_int32();
		bet->event_match_status = event_doc["match_status"].get_int32();
		bet->event_status = event_doc["status"].get_int32();
		bet->event_start_time = event_doc["start_time"].get_int32();
		bet->event_period_length = event_doc["period_length"].get_int32();
		bet->event_overtime_length = event_doc["overtime_length"].get_int32();
		bet->event_bo = event_doc["bo"].get_int32();
		mongo_str_to_buffer(event_doc["away_name"], bet->event_away_name);
		mongo_str_to_buffer(event_doc["home_name"], bet->event_home_name);
		mongo_str_to_buffer(event_doc["match_time"], bet->event_match_time);
		mongo_str_to_buffer(event_doc["remaining_time"], bet->event_remaining_time);
		mongo_str_to_buffer(event_doc["remaining_time_in_period"], bet->event_remaining_time_in_period);
		mongo_str_to_buffer(event_doc["score"], bet->event_score);
		mongo_str_to_buffer(event_doc["set_scores"], bet->event_set_scores);
		mongo_str_to_buffer(event_doc["game_score"], bet->event_game_score);
		mongo_str_to_buffer(event_doc["match_status_description"], bet->event_match_status_description);



	}
	else {
		throw std::runtime_error("Bet not found in Mongo: " + bet_id);
	}
	return;
}
void loadBetsFromDB() {
	using namespace bsoncxx::builder;
	try {
		auto coll = db["bets"];
		mongocxx::cursor cursor = coll.find(bsoncxx::builder::stream::document{} << bsoncxx::builder::stream::finalize);  // get all docs

		for (auto bet_doc : cursor) {
			Bet* bet = new Bet();
			// std::cout << bsoncxx::to_json(bet_doc) << std::endl;
			bet->id = bet_doc["_id"].get_oid().value.to_string();
			bet->counter = bet_doc["counter"].get_int32();
			bet->status = bet_doc["status"].get_int32();
			bet->language = bet_doc["language"].get_int32();
			bet->void_reason = bet_doc["void_reason"].get_int32();
			bet->certainy = bet_doc["certainy"].get_int32();
			bet->superceded_by = bet_doc["superceded_by"].get_int32();
			bet->bet_cancel = bet_doc["bet_cancel"].get_int32();
			bet->rollback_bet_cancel = bet_doc["rollback_bet_cancel"].get_int32();
			bet->rollback_bet_settlement = bet_doc["rollback_bet_settlement"].get_int32();
			bet->start_time = bet_doc["start_time"].get_int32();
			bet->end_time = bet_doc["end_time"].get_int32();
			//bet->line_id = bet_doc["line_id"].get_int32();
			bet->selected_outcome_id = bet_doc["selected_outcome_id"].get_int32();
			bet->tournament_id = bet_doc["tournament_id"].get_int32();
			bet->simple_id = bet_doc["simple_id"].get_int32();
			bet->season_id = bet_doc["season_id"].get_int32();
			bet->market_id = bet_doc["market_id"].get_int32();
			bet->event_id = bet_doc["event_id"].get_int32();
			bet->sport_id = bet_doc["sport_id"].get_int32();
			bet->category_id = bet_doc["category_id"].get_int32();
			bet->team = bet_doc["team"].get_int32();
			bet->favourite = bet_doc["favourite"].get_int32();
			bet->type = bet_doc["type"].get_int32();
			bet->type_radar = bet_doc["type_radar"].get_int32();
			bet->variant = bet_doc["variant"].get_int32();
			bet->place_odd = bet_doc["place_odd"].get_double();
			bet->accept_odd = bet_doc["accept_odd"].get_double();
			bet->settlement_odd = bet_doc["settlement_odd"].get_double();
			mongo_str_to_buffer(bet_doc["summary"], bet->summary);
			// string properties
			bet->ticket_id = bet_doc["ticket_id"].get_utf8().value.to_string();
			mongo_str_to_buffer(bet_doc["name"], bet->name);
			mongo_str_to_buffer(bet_doc["tournament_name"], bet->tournament_name);
			mongo_str_to_buffer(bet_doc["category_name"], bet->category_name);
			mongo_str_to_buffer(bet_doc["season_name"], bet->season_name);
			mongo_str_to_buffer(bet_doc["sport_name"], bet->sport_name);

			// fill outcomes
			{  // scoped not to carry variables
				bsoncxx::document::element mongo_arr = bet_doc["outcomes"];
				bsoncxx::array::view outcomes{ mongo_arr.get_array().value };
				if (!outcomes.empty()) {
					auto num_outcomes = std::distance(std::begin(outcomes), std::end(outcomes));
					bet->outcome_number = num_outcomes;
					bet->outcome_name = new char*[num_outcomes];
					bet->outcome_id = new int[num_outcomes];
					bet->outcome_active = new int[num_outcomes];
					bet->outcome_team = new int[num_outcomes];
					bet->outcome_odds = new float[num_outcomes];
					bet->outcome_probabilities = new float[num_outcomes];

					int outcome_index = 0;
					for (auto elt : outcomes) {
						bsoncxx::document::view subdoc = elt.get_document().value;
						bet->outcome_name[outcome_index] = nullptr;
						mongo_str_to_buffer(subdoc["name"], bet->outcome_name[outcome_index]);
						bet->outcome_id[outcome_index] = subdoc["id"].get_int32();
						bet->outcome_active[outcome_index] = subdoc["active"].get_int32();
						bet->outcome_team[outcome_index] = subdoc["team"].get_int32();
						bet->outcome_odds[outcome_index] = subdoc["odds"].get_double();
						bet->outcome_probabilities[outcome_index] = subdoc["probabilities"].get_double();
						outcome_index++;
					}
				}
				else {
					bet->outcome_number = 0;
				}
			}

			{
				bsoncxx::document::element mongo_arr = bet_doc["resultes"];
				bsoncxx::array::view resultes{ mongo_arr.get_array().value };
				if (!resultes.empty()) {
					auto num_resultes = std::distance(std::begin(resultes), std::end(resultes));
					bet->outcome_result = new int[num_resultes];
					bet->outcome_dead_heat_factor = new int[num_resultes];
					bet->outcome_void_factor = new int[num_resultes];

					int resulte_index = 0;
					for (auto elt : resultes) {
						bsoncxx::document::view subdoc = elt.get_document().value;
						bet->outcome_result[resulte_index] = subdoc["result"].get_int32();
						bet->outcome_void_factor[resulte_index] = subdoc["void_factor"].get_int32();
						bet->outcome_dead_heat_factor[resulte_index] = subdoc["dead_heat_factor"].get_int32();
						resulte_index++;
					}
				}











			}
			;


			// fill specifiers
			{  // scoped not to carry variables
				bsoncxx::document::element mongo_arr = bet_doc["specifiers"];
				bsoncxx::array::view specifiers{ mongo_arr.get_array().value };
				if (!specifiers.empty()) {
					auto num_specifiers = std::distance(std::begin(specifiers), std::end(specifiers));
					bet->specifier_number = num_specifiers;
					bet->specifier = new char*[num_specifiers];
					bet->specifier_value = new char*[num_specifiers];
					int specifier_index = 0;
					for (auto elt : specifiers) {
						bsoncxx::document::view subdoc = elt.get_document().value;
						bet->specifier[specifier_index] = nullptr;
						bet->specifier_value[specifier_index] = nullptr;
						mongo_str_to_buffer(subdoc["specifier"], bet->specifier[specifier_index]);
						mongo_str_to_buffer(subdoc["value"], bet->specifier_value[specifier_index]);
						specifier_index++;
					}
				}
				else {
					bet->specifier_number = 0;
				}
			}
			// fill extended specifiers
			{  // scoped not to carry variables
				bsoncxx::document::element mongo_arr = bet_doc["extended_specifiers"];
				bsoncxx::array::view extended_specifiers{ mongo_arr.get_array().value };
				if (!extended_specifiers.empty()) {
					auto num_specifiers = std::distance(std::begin(extended_specifiers), std::end(extended_specifiers));
					bet->extended_specifier_number = num_specifiers;
					bet->extended_specifier = new char*[num_specifiers];
					bet->extended_specifier_value = new char*[num_specifiers];
					int specifier_index = 0;
					for (auto elt : extended_specifiers) {
						bsoncxx::document::view subdoc = elt.get_document().value;
						bet->extended_specifier[specifier_index] = nullptr;
						bet->extended_specifier_value[specifier_index] = nullptr;
						mongo_str_to_buffer(subdoc["extended_specifier"], bet->extended_specifier[specifier_index]);
						mongo_str_to_buffer(subdoc["value"], bet->extended_specifier_value[specifier_index]);
						specifier_index++;
					}
				}
				else {
					bet->extended_specifier_number = 0;
				}
			}
			// fill event info
			auto event_doc = bet_doc["event_info"];
			bet->event_home_id = event_doc["home_id"].get_int32();
			bet->event_away_id = event_doc["away_id"].get_int32();
			bet->event_match_status = event_doc["match_status"].get_int32();
			bet->event_status = event_doc["status"].get_int32();
			bet->event_start_time = event_doc["start_time"].get_int32();
			bet->event_period_length = event_doc["period_length"].get_int32();
			bet->event_overtime_length = event_doc["overtime_length"].get_int32();
			if (!event_doc["current_server"]) {}
			else bet->event_current_server = event_doc["current_server"].get_int32();

			bet->event_bo = event_doc["bo"].get_int32();
			mongo_str_to_buffer(event_doc["away_name"], bet->event_away_name);
			mongo_str_to_buffer(event_doc["home_name"], bet->event_home_name);
			mongo_str_to_buffer(event_doc["match_time"], bet->event_match_time);
			mongo_str_to_buffer(event_doc["remaining_time"], bet->event_remaining_time);
			mongo_str_to_buffer(event_doc["remaining_time_in_period"], bet->event_remaining_time_in_period);
			mongo_str_to_buffer(event_doc["score"], bet->event_score);
			mongo_str_to_buffer(event_doc["set_scores"], bet->event_set_scores);
			mongo_str_to_buffer(event_doc["game_score"], bet->event_game_score);
			mongo_str_to_buffer(event_doc["match_status_description"], bet->event_match_status_description);


			auto bet_it = bets_ticket.find(bet->ticket_id);
			if (bet_it == bets_ticket.end()) {
				bets_ticket[bet->ticket_id] = {};
			}
			bets_ticket[bet->ticket_id].insert(bet);

		}

	}

	catch (const mongocxx::exception& e) {
		cout << "An exception occurred in loading Bets from Mongo: " << e.what() << endl;
	}


	return;
}
void loadTicketsFromDB() {
	int current_time = time(nullptr);
	int* unsettled = nullptr;

	try {
		auto coll = db["tickets"];
		mongocxx::cursor cursor = coll.find(bsoncxx::builder::stream::document{} << bsoncxx::builder::stream::finalize);  // get all docs
		for (auto doc : cursor) {
			if (!doc["Contact OAM"]) {}
			else if (doc["Contact OAM"].get_int32() == 1) continue;
			Ticket* ticket = new Ticket();
			//int id = doc["_id"].get_int32();
			ticket->id = doc["_id"].get_oid().value.to_string();
			//if (client_id == 1000041) continue;
			ticket->client_id = doc["client_id"].get_int32();
			//if (!doc["mts_id"]) {} else  ticket->mts_id = doc["mts_id"].get_utf8().value.to_string();


			ticket->freebet = doc["freebet"].get_int32();
			ticket->status = doc["status"].get_int32();
			ticket->counter = doc["counter"].get_int32();
			ticket->timestamp = doc["timestamp"].get_int64();
			ticket->system_selected = doc["system_selected"].get_int32();
			ticket->type = doc["type"].get_int32();
			ticket->coeff = doc["coeff"].get_double();
			ticket->coeff_settlement = doc["coeff_settlement"].get_double();
			ticket->stake = doc["stake"].get_double();
			//	if (ticket->mts_id == "t1521729745232s628r0i0") printf("ticket->status=%d\r\n", ticket->status);
			ticket->payout = doc["payout"].get_double();
			ticket->returned = doc["returned"].get_double();
			ticket->bonus = doc["bonus"].get_double();
			ticket->coeff_bonus = doc["coeff_bonus"].get_double();
			// bets array
			bsoncxx::document::element bets_elem = doc["bet_ids"];
			bsoncxx::array::view bet_ids{ bets_elem.get_array().value };
			if (bet_ids.empty()) {
				throw std::runtime_error("Ticket has no bets: " + ticket->id);
			}
			else {
				auto num_bets = std::distance(std::begin(bet_ids), std::end(bet_ids));

				ticket->bets_number = num_bets;
				ticket->bets = new Bet*[num_bets];
				int bet_index = 0;

				auto bet_it = bets_ticket.find(ticket->id);
				if (bet_it == bets_ticket.end()) {
					throw std::runtime_error("Ticket has no bets in bets_ticket map: " + ticket->id);
				}

				else for (auto it = bets_ticket[ticket->id].begin(); it != bets_ticket[ticket->id].end(); ++it)
				{
					ticket->bets[bet_index] = (*it);
					if ((*it)->status == 0) open_bets.insert((*it));
					bet_index++;
					bets_counter++;
				}

				/*
				for (auto elt : bet_ids) {
				string bet_id = elt.get_utf8().value.to_string();
				Bet* bet = new Bet();
				populateBetFromMongo(bet, bet_id);
				ticket->bets[bet_index] = bet;
				if (bet->status == 0) open_bets.insert(bet);
				bet_index++;
				}*/








			}

			insertTicketIntoHashes(ticket);

		}
		tickets_counter = tickets.size();

		printf("Tickets loaded from Mongo succes. Number of loaded tickets: %d  Number of loaded bets: %d\r\n", tickets.size(), bets_counter);
	}
	catch (const mongocxx::exception& e) {
		cout << "An exception occurred in loading Tickets from Mongo: " << e.what() << endl;
	}
	return;
}
bsoncxx::document::value buildBetDoc(Bet* bet) {
	bsoncxx::builder::basic::document builder{};
	builder.append(
		kvp("status", bet->status),
		kvp("language", bet->language),
		kvp("void_reason", bet->void_reason),
		kvp("certainy", bet->certainy),
		kvp("rollback_bet_cancel", bet->rollback_bet_cancel),
		kvp("bet_cancel", bet->bet_cancel),
		kvp("rollback_bet_settlement", bet->rollback_bet_settlement),
		kvp("start_time", bet->start_time),
		kvp("end_time", bet->end_time),
		kvp("superceded_by", bet->superceded_by),
		kvp("ticket_id", bet->ticket_id),
		kvp("counter", bet->counter),
		kvp("selected_outcome_id", bet->selected_outcome_id),
		kvp("place_odd", bet->place_odd),
		kvp("accept_odd", bet->accept_odd),
		kvp("settlement_odd", bet->settlement_odd),
		kvp("summary", bet->summary == nullptr ? "" : bet->summary),
		kvp("tournament_id", bet->tournament_id),
		kvp("simple_id", bet->simple_id),
		kvp("season_id", bet->season_id),
		kvp("market_id", bet->market_id),
		kvp("event_id", bet->event_id),
		kvp("sport_id", bet->sport_id),
		kvp("category_id", bet->category_id),
		kvp("team", bet->team),
		kvp("favourite", bet->favourite),
		kvp("type", bet->type),
		kvp("type_radar", bet->type_radar),
		kvp("variant", bet->variant),
		kvp("name", bet->name == nullptr ? "" : bet->name),
		kvp("tournament_name", bet->tournament_name == nullptr ? "" : bet->tournament_name),
		kvp("category_name", bet->category_name == nullptr ? "" : bet->category_name),
		kvp("season_name", bet->season_name == nullptr ? "" : bet->season_name),
		kvp("sport_name", bet->sport_name == nullptr ? "" : bet->sport_name)
	);
	auto outcomes = bsoncxx::builder::basic::array{};
	for (int j = 0; j < bet->outcome_number; j++) {
		bsoncxx::document::value subdoc = bsoncxx::builder::stream::document{}
			<< "id" << bet->outcome_id[j] << "name" << bet->outcome_name[j]
			<< "active" << bet->outcome_active[j] << "team" << bet->outcome_team[j]
			<< "probabilities" << bet->outcome_probabilities[j] << "odds" << bet->outcome_odds[j]
			<< bsoncxx::builder::stream::finalize;
		outcomes.append(std::move(subdoc));
	}
	builder.append(kvp("outcomes", std::move(outcomes)));


	auto resultes = bsoncxx::builder::basic::array{};
	for (int j = 0; j < bet->outcome_number; j++) {
		bsoncxx::document::value subdoc = bsoncxx::builder::stream::document{}
			<< "result" << bet->outcome_result[j] << "void_factor" << bet->outcome_void_factor[j]
			<< "dead_heat_factor" << bet->outcome_dead_heat_factor[j]
			<< bsoncxx::builder::stream::finalize;
		resultes.append(std::move(subdoc));
	}
	builder.append(kvp("resultes", std::move(resultes)));




	auto specifiers = bsoncxx::builder::basic::array{};
	for (int j = 0; j < bet->specifier_number; j++) {
		bsoncxx::document::value subdoc = bsoncxx::builder::stream::document{}
			<< "specifier" << bet->specifier[j] << "value" << bet->specifier_value[j]
			<< bsoncxx::builder::stream::finalize;
		specifiers.append(std::move(subdoc));
	}
	builder.append(kvp("specifiers", std::move(specifiers)));

	auto extended_specifiers = bsoncxx::builder::basic::array{};
	for (int j = 0; j < bet->extended_specifier_number; j++) {
		bsoncxx::document::value subdoc = bsoncxx::builder::stream::document{}
			<< "extended_specifier" << bet->extended_specifier[j] << "value" << bet->extended_specifier_value[j]
			<< bsoncxx::builder::stream::finalize;
		extended_specifiers.append(std::move(subdoc));
	}
	builder.append(kvp("extended_specifiers", std::move(extended_specifiers)));

	bsoncxx::builder::basic::document event_doc{};
	event_doc.append(
		kvp("home_id", bet->event_home_id),
		kvp("away_id", bet->event_away_id),
		kvp("away_name", bet->event_away_name == nullptr ? "" : bet->event_away_name),
		kvp("home_name", bet->event_home_name == nullptr ? "" : bet->event_home_name),
		kvp("match_time", bet->event_match_time == nullptr ? "" : bet->event_match_time),
		kvp("remaining_time", bet->event_remaining_time == nullptr ? "" : bet->event_remaining_time),
		kvp("remaining_time_in_period", bet->event_remaining_time_in_period == nullptr ? "" : bet->event_remaining_time_in_period),
		kvp("score", bet->event_score == nullptr ? "" : bet->event_score),
		kvp("set_scores", bet->event_set_scores == nullptr ? "" : bet->event_set_scores),
		kvp("game_score", bet->event_game_score == nullptr ? "" : bet->event_game_score),
		kvp("match_status_description", bet->event_match_status_description == nullptr ? "" : bet->event_match_status_description),
		kvp("match_status", bet->event_match_status),
		kvp("status", bet->event_status),
		kvp("start_time", bet->event_start_time),
		kvp("period_length", bet->event_period_length),
		kvp("overtime_length", bet->event_overtime_length),
		kvp("current_server", bet->event_current_server),
		kvp("bo", bet->event_bo)
	);
	builder.append(kvp("event_info", std::move(event_doc)));
	return builder.extract();
}
bsoncxx::document::value updateBetDoc(Bet* bet) {
	bsoncxx::builder::basic::document builder{};
	builder.append(
		kvp("status", bet->status),
		kvp("void_reason", bet->void_reason),
		kvp("certainy", bet->certainy),
		kvp("rollback_bet_cancel", bet->rollback_bet_cancel),
		kvp("bet_cancel", bet->bet_cancel),
		kvp("rollback_bet_settlement", bet->rollback_bet_settlement),
		kvp("start_time", bet->start_time),
		kvp("end_time", bet->end_time),
		kvp("superceded_by", bet->superceded_by),
		kvp("settlement_odd", bet->settlement_odd),
		kvp("summary", bet->summary == nullptr ? "" : bet->summary)

	);
	auto resultes = bsoncxx::builder::basic::array{};
	for (int j = 0; j < bet->outcome_number; j++) {
		bsoncxx::document::value subdoc = bsoncxx::builder::stream::document{}
			<< "result" << bet->outcome_result[j] << "void_factor" << bet->outcome_void_factor[j]
			<< "dead_heat_factor" << bet->outcome_dead_heat_factor[j]
			<< bsoncxx::builder::stream::finalize;
		resultes.append(std::move(subdoc));
	}
	builder.append(kvp("resultes", std::move(resultes)));

	return builder.extract();
}

// returns Bet's mongo id
string saveBetToDB(Bet* bet) {
	auto coll = db["bets"];
	string bet_id;
	try {
		bsoncxx::stdx::optional<mongocxx::result::insert_one> result = coll.insert_one(buildBetDoc(bet));
		bet_id = result.get().inserted_id().get_oid().value.to_string();
		bet->id = bet_id;
	}
	catch (const mongocxx::exception& e) {
		cout << "An exception occurred in inserting a new Bet into Mongo: " << e.what() << endl;
	}
	return bet_id;
}

void updateBetToDB(Bet* bet) {
	auto coll = db["bets"];
	mongocxx::options::update* update = new mongocxx::options::update();
	update->upsert(true);
	try {
		coll.update_one(bsoncxx::builder::stream::document{} << "_id" << bsoncxx::oid(bet->id) << bsoncxx::builder::stream::finalize,
			bsoncxx::builder::stream::document{} << "$set" << updateBetDoc(bet) << bsoncxx::builder::stream::finalize, *update);
	}
	catch (const mongocxx::exception& e) {
		cout << "An exception occurred in updating Bet into Mongo: " << e.what() << endl;
	}

	delete update;

}
void updateTicketToDB(Ticket* ticket) {
	auto coll = db["tickets"];
	mongocxx::options::update* update = new mongocxx::options::update();
	update->upsert(true);
	try {
		coll.update_one(bsoncxx::builder::stream::document{} << "_id" << bsoncxx::oid(ticket->id) << bsoncxx::builder::stream::finalize,
			bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document << "status" << ticket->status << "payout" << ticket->payout << "coeff_settlement" << ticket->coeff_settlement << "returned" << ticket->returned << "bonus" << ticket->bonus << "coeff_bonus" << ticket->coeff_bonus << bsoncxx::builder::stream::close_document << bsoncxx::builder::stream::finalize, *update);

	}
	catch (const mongocxx::exception& e) {
		cout << "An exception occurred in updating Ticket into Mongo: " << e.what() << endl;
	}

	delete update;

}
void createTicketBetCollections() {
	using namespace bsoncxx::builder;
	db.create_collection("tickets");
	db.create_collection("bets");
	auto tickets_coll = db["tickets"];
	auto bets_coll = db["bets"];
	// indexes
	tickets_coll.create_index(stream::document{} << "client_id" << 1 << stream::finalize);
	bets_coll.create_index(stream::document{} << "ticket_id" << 1 << stream::finalize);
	// If we don't need this let's drop it since it is a complicated index
	bets_coll.create_index(stream::document{}
		<< "event_id" << 1 << "tournament_id" << 1 << "simple_id" << 1
		<< "market_id" << 1 << "specifiers" << 1 << stream::finalize);
}
void processNewTicket(Ticket* ticket) {
	using namespace bsoncxx::builder;
	string bet_id;
	string ticket_id;
	if (!db.has_collection("tickets")) {
		createTicketBetCollections();
	}
	auto coll = db["tickets"];
	bsoncxx::builder::basic::document builder{};
	ticket->counter = tickets_counter;
	builder.append(
		kvp("client_id", ticket->client_id),
		kvp("mts_id", ticket->mts_id),
		kvp("domain", ticket->domain),
		kvp("freebet", ticket->freebet),
		kvp("status", ticket->status),
		kvp("counter", ticket->counter),
		kvp("timestamp", ticket->timestamp),
		kvp("system_selected", ticket->system_selected),
		kvp("type", ticket->type),
		kvp("coeff", ticket->coeff),
		kvp("coeff_settlement", ticket->coeff_settlement),
		kvp("stake", ticket->stake),
		kvp("payout", ticket->payout),
		kvp("returned", ticket->returned),
		kvp("bonus", ticket->bonus),
		kvp("coeff_bonus", ticket->coeff_bonus)
	);
	if (ticket->contact_oam == 1) builder.append(kvp("Contact OAM", ticket->contact_oam));

	bsoncxx::types::b_oid oid;
	try {

		bsoncxx::stdx::optional<mongocxx::result::insert_one> result = coll.insert_one(builder.extract());
		oid = result.get().inserted_id().get_oid();
		ticket_id = oid.value.to_string();
		ticket->id = ticket_id;
		tickets_counter++;
		//printf("ticket->id=%s\r\n", ticket->id.c_str());

	}
	catch (const mongocxx::exception& e) {
		cout << "An exception occurred in inserting a new Ticket into Mongo: " << e.what() << endl;
	}
	auto bet_ids = bsoncxx::builder::basic::array{};
	for (int i = 0; i < ticket->bets_number; i++) {
		ticket->bets[i]->ticket_id = ticket_id;
		ticket->bets[i]->counter = bets_counter;
		bets_counter++;
		bet_id = saveBetToDB(ticket->bets[i]);
		bet_ids.append(bet_id);
	}
	coll.update_one(
		stream::document{} << "_id" << oid << stream::finalize,
		stream::document{} << "$set" << stream::open_document <<
		"bet_ids" << bet_ids << stream::close_document << stream::finalize);

	if (ticket->contact_oam == 0)	insertTicketIntoHashes(ticket, true);

}

int64_t* combin[20];
double** ARS[20];



int64_t Combin(int n, int k) {
	if (k > n || k < 1 || n < 1) return 0;
	if (combin[n][k] != -1) return combin[n][k];
	int64_t i = 0;
	int64_t m = 1;
	int64_t l = 1;
	for (i = 2; i < k + 1; i++) m = m * i;
	for (i = 2; i < n - k + 1; i++) m = m * i;
	for (i = 2; i < n + 1; i++) l = l * i;
	combin[n][k] = l / m;
	return combin[n][k];
}
double* getAllExpressCoeffs(int n, int k, Ticket* ticket) {
	if (ARS[n][k] != nullptr) return ARS[n][k];
	int i = 0;
	double* A = nullptr;
	if (k == 1) { A = new double[n];  for (i = 0; i < n; i++) A[i] = ticket->bets[i]->settlement_odd; return A; };
	if (k == n) { A = new double[1];  A[0] = 1; for (i = 0; i < n; i++) A[0] = A[0] * ticket->bets[i]->settlement_odd; return A; };
	int64_t m = 0;
	int64_t l = 0;
	double* A1 = getAllExpressCoeffs(n - 1, k - 1, ticket);
	double* A2 = getAllExpressCoeffs(n - 1, k, ticket);
	m = Combin(n - 1, k - 1);
	l = Combin(n - 1, k);
	A = new double[m + l];
	for (i = 0; i < l; i++) A[i] = A2[i];
	for (i = 0; i < m; i++) A[i + l] = A1[i] * ticket->bets[n - 1]->settlement_odd;
	ARS[n][k] = A;
	return A;
}
void calculateSystemCoeffAndPayout(Ticket* ticket) {
	int n = ticket->bets_number;
	int k = ticket->system_selected;
	int64_t m = Combin(n, k);
	double* A = getAllExpressCoeffs(n, k, ticket);
	ticket->coeff_settlement = 0;
	int i = 0;
	for (i = 0; i < m; i++) { if (A[i] > MAX_COEFF_SYSTEM) A[i] = MAX_COEFF_SYSTEM;   ticket->coeff_settlement = ticket->coeff_settlement + A[i]; } //printf("A[i]=%g\r\n", A[i]);
	ticket->payout = ticket->coeff_settlement * ticket->stake / m;
	for (int i = 0; i < 20; i++) for (int j = 0; j < 20; j++) { if (ARS[i][j] != nullptr) delete[] ARS[i][j]; ARS[i][j] = nullptr; }

}
void calculationTicket(Ticket* ticket) {
	double old_payout = ticket->payout;
	int old_status = ticket->status;
	Client* client = nullptr;
	char* buffer = nullptr;
	size_t offset = 0;
	char* zip_message = nullptr;
	int zip_len = 0;
	char* encode_message = nullptr;// = SendframeEncode(zip_message, zip_len, len);
	int encode_message_len = 0;
	int lose_status = 0;

	if (ticket->type < 3) {
		ticket->status = 1;
		ticket->coeff_settlement = 1;
		ticket->coeff = 1;

		for (int i = 0; i < ticket->bets_number; i++) {
			ticket->coeff_settlement = ticket->bets[i]->settlement_odd * ticket->coeff_settlement;
			ticket->coeff = ticket->bets[i]->accept_odd * ticket->coeff;
			ticket->status = ticket->status * ticket->bets[i]->status;
			if (ticket->bets[i]->status == 1 && ticket->bets[i]->settlement_odd == 0) lose_status = 1;
		}
		if (lose_status == 1) ticket->status = 1;
		if (ticket->status == 1)  ticket->payout = ticket->stake*ticket->coeff_settlement;
		else ticket->payout = 0;
		if (ticket->coeff_settlement > MAX_COEFF_SYSTEM) ticket->coeff_settlement = MAX_COEFF_SYSTEM;
	}

	if (ticket->type == 3) {
		ticket->status = 1;
		ticket->coeff_settlement = 0;
		ticket->payout = 0;
		ticket->coeff = 0;

		for (int i = 0; i < ticket->bets_number; i++) {
			if (ticket->bets[i]->status == 1 && ticket->bets[i]->settlement_odd == 0) lose_status++;
			ticket->status = ticket->status * ticket->bets[i]->status;
		}
		if (lose_status > ticket->bets_number - ticket->system_selected) {
			ticket->coeff_settlement = 0; ticket->payout = 0; ticket->status = 1;
		}
		else
			if (ticket->status == 1) calculateSystemCoeffAndPayout(ticket);

	}




	if (old_payout != ticket->payout || old_status != ticket->status) {
		auto client_it = client_id_hash.find(ticket->client_id);
		if (client_it == client_id_hash.end()) printf("erorr in calculationTicket. client id=%d not found in ticket id=%s\r\n", ticket->client_id, ticket->id);
		else {
			client = client_it->second;
			client->balance = client->balance + ticket->payout - old_payout;
			if (old_status == 0 && ticket->status == 1) client->bets_amount = client->bets_amount - ticket->stake;
			if (old_status == 1 && ticket->status == 0) client->bets_amount = client->bets_amount + ticket->stake;
			updateClientBalanceToDB(client);
			i = 0;

			for (auto it = client->wsclients.begin(); it != client->wsclients.end(); ++it) {
				if (i == 0) {
					buffer = new char[SMALL];
					HistoryCalculationTicket(buffer, offset, ticket, client->balance, client->bets_amount);
					zip_len = gzip(buffer, offset, zip_message, 7);
					if (zip_len < 1) {
						delete[] zip_message; zip_message = nullptr; break;
						//wsclient->recv_client_message_thread_queue++; continue;
					}
					encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
					delete[] zip_message; zip_message = nullptr;
				}

				i++;
				server.wsSendBetMessage(*it, encode_message, encode_message_len);

			}

			if (encode_message != nullptr) delete[] encode_message;  encode_message = nullptr;
			if (buffer != nullptr) delete[] buffer;  buffer = nullptr;










		}

		updateTicketToDB(ticket);

	}


	if (old_status != ticket->status)	changeTicketStatus(ticket);









}
void calculationBet(Bet* bet, Bet* _bet, int type) {


	int old_status = bet->status;
	int old_settlement_odd = bet->settlement_odd;
	char* buffer = nullptr;
	size_t offset = 0;
	char* zip_message = nullptr;
	int zip_len = 0;
	char* encode_message = nullptr;// = SendframeEncode(zip_message, zip_len, len);
	int encode_message_len = 0;
	int i = 0;
	int l = 0;
	char* summary = new char[SMALL];
	summary[0] = 0;
	if (type == 0) {

		/*	if (bet->outcome_number != _bet->outcome_number) {
		printf("ERROR in calculationBet: bet->outcome_number=%d _bet->outcome_number=%d bet->market_id=%d bet->event_id=%d bet->type=%d bet->type_radr=%d", bet->outcome_number, _bet->outcome_number, bet->market_id, bet->event_id, bet->type, bet->type_radar); return;
		}*/


		//if (bet->outcome_result != nullptr)	delete[] bet->outcome_result;
		//if (bet->outcome_void_factor != nullptr) delete[] bet->outcome_void_factor;
		//if (bet->outcome_dead_heat_factor != nullptr) delete[] bet->outcome_dead_heat_factor;
		bet->certainy = _bet->certainy;
		bet->void_reason = _bet->void_reason;
		bet->superceded_by = _bet->superceded_by;
		bet->void_reason = _bet->void_reason;
		//bet->outcome_result = new int[bet->outcome_number];
		//bet->outcome_dead_heat_factor = new int[bet->outcome_number];
		//bet->outcome_void_factor = new int[bet->outcome_number];
		if (bet->summary != nullptr) delete[] bet->summary; bet->summary = nullptr;


		for (int i = 0; i < bet->outcome_number; i++) for (int j = 0; j < _bet->outcome_number; j++) if (_bet->outcome_id[j] == bet->outcome_id[i]) {
			bet->outcome_result[i] = _bet->outcome_result[j];
			bet->outcome_void_factor[i] = _bet->outcome_void_factor[j];

			if (bet->outcome_result[i] == 1 && bet->outcome_name[i] != nullptr) {

				//bet->summary = new char[strlen(bet->outcome_name[i]) + 1];
				if (l == 0)std::strcpy(summary, bet->outcome_name[i]);
				else { strcat(summary, " , "); strcat(summary, bet->outcome_name[i]); }
				l++;
			}
			bet->outcome_dead_heat_factor[i] = _bet->outcome_dead_heat_factor[j];

		}
		if (l > 0) { bet->summary = new char[strlen(summary) + 1];std::strcpy(bet->summary, summary); }



		bet->status = 1;
		if (bet->outcome_result[bet->selected_outcome_id] == 0 && bet->outcome_void_factor[bet->selected_outcome_id] == 0) bet->settlement_odd = 0; else
			if (bet->outcome_result[bet->selected_outcome_id] == 0 && bet->outcome_void_factor[bet->selected_outcome_id] == 1) {
				bet->settlement_odd = 1;
				if (bet->summary == nullptr) {
					strcpy(summary, "Returned");  bet->summary = new char[strlen(summary) + 1];std::strcpy(bet->summary, summary);
				}
			}
			else
				if (bet->outcome_result[bet->selected_outcome_id] == 0 && bet->outcome_void_factor[bet->selected_outcome_id] == 2) bet->settlement_odd = (bet->accept_odd - 1) / 2; else
					if (bet->outcome_result[bet->selected_outcome_id] == 1 && bet->outcome_void_factor[bet->selected_outcome_id] == 0) bet->settlement_odd = bet->accept_odd; else
						if (bet->outcome_result[bet->selected_outcome_id] == 1 && bet->outcome_void_factor[bet->selected_outcome_id] == 1) bet->settlement_odd = bet->accept_odd; else
							if (bet->outcome_result[bet->selected_outcome_id] == 1 && bet->outcome_void_factor[bet->selected_outcome_id] == 2) bet->settlement_odd = (bet->accept_odd + 1) / 2;


	}

	if (type == 1) {
		bet->rollback_bet_settlement = 1;
		if (bet->summary != nullptr) delete[] bet->summary; bet->summary = nullptr;



		for (int i = 0; i < bet->outcome_number; i++) {
			bet->outcome_result[i] = 0;
			bet->outcome_void_factor[i] = 0;
			bet->outcome_dead_heat_factor[i] = 0;
		}

		bet->status = 0;
		bet->settlement_odd = 0;

	}

	if (type == 2) {
		if ((_bet->start_time > 0 && (bet->timestamp / 1000) < _bet->start_time) || (_bet->end_time > 0 && (bet->timestamp / 1000) > _bet->end_time)) return;
		bet->bet_cancel = 1;
		if (bet->summary != nullptr) delete[] bet->summary; bet->summary = nullptr;
		strcpy(summary, "Bet cancel");
		bet->summary = new char[strlen(summary) + 1];
		strcpy(bet->summary, summary);
		bet->status = 1;
		bet->settlement_odd = 1;

	}

	if (type == 3) {
		bet->rollback_bet_cancel = 1;
		if (bet->summary != nullptr) delete[] bet->summary; bet->summary = nullptr;
		bet->status = 0;
		bet->settlement_odd = 0;
	}


	updateBetToDB(bet);


	if (old_status != bet->status) changeBetStatus(bet);


	if (tickets.find(bet->ticket_id) == tickets.end()) printf("error! ticket id=%s not found in bet id=%s in calculationBet\r\n", bet->ticket_id.c_str(), bet->id.c_str()); else {
		if (old_status != bet->status || old_settlement_odd != bet->settlement_odd) {
			auto client_it = client_id_hash.find(tickets[bet->ticket_id]->client_id);
			if (client_it == client_id_hash.end()) {}
			else {
				for (auto it = client_it->second->wsclients.begin(); it != client_it->second->wsclients.end(); ++it) {
					if (i == 0) {
						buffer = new char[SMALL];
						HistoryCalculationBet(buffer, offset, bet);
						zip_len = gzip(buffer, offset, zip_message, 6);
						if (zip_len < 1) {
							delete[] zip_message; zip_message = nullptr; break;
							//wsclient->recv_client_message_thread_queue++; continue;
						}
						encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
						delete[] zip_message; zip_message = nullptr;
					}

					i++;
					server.wsSendBetMessage(*it, encode_message, encode_message_len);

				}

				if (encode_message != nullptr) delete[] encode_message;  encode_message = nullptr;
				if (buffer != nullptr) delete[] buffer;  buffer = nullptr;



			}
		}


		calculationTicket(tickets[bet->ticket_id]);


	}





	delete[] summary;


}



int replay_list[] = { 11962040,11868382,12715758,11962042,11868386,11797616,11933360,11871710,11872432,11868378,12007276,12707224,12007280,12008172,11962038,11873002,12007262,12707230,11872492,11868388,11962044,12749220,11872204,11962048,11872074,11988690,11872086,12008176,11868392,11872122,11962052,11962046,11873722,11873144,11933362,11873798,11868390,11873670,11962056,11874034,11962054,11873816,12913328,11830102,12438642,11837780,11882056,12976102,12199364,11830478,11830650,11830704,12008180,11882062,11882066,11885304,11885298,11885292,12246576,12246586,11830432,11880880,11933358,12570518,11933354,11868374,13045492,12008188,11809932,12060550,11830080,11933356,11933352,12136728,11868370,12119542,12379784,12032178,12318938,12119538,12055304,12622452,11809926,11942522,11833166,12999226,12808148,11809934,12976124,11865580,11880882,12199382,11988678,11880884,12246584,13045040,13045302,12029826,11988684,11880886 };



int addToReplayList(int, int);


int main() {


	hThread3 = new HANDLE[20];
	dwThreadID3 = new DWORD[20];
	hThread9 = new HANDLE[20];
	dwThreadID9 = new DWORD[20];

	SetConsoleOutputCP(CP_UTF8);

	/*
	printf("seconds=%d/r/n", DMYtoSeconds(1, 11, 1969));
	printf("seconds=%d/r/n", DMYtoSeconds(1, 11, 2039));
	return 0;
	char* phone = nullptr;
	char* param = nullptr;
	char* sms = nullptr;
	param = new char[sizeof(char*) + sizeof(char*) + 1];
	phone = new char[20];
	strcpy(phone, "+98746352344444");
	memcpy(param, &phone, sizeof(char*));
	sms = generateSmsCode();
	memcpy(param + sizeof(char*), &sms, sizeof(char*));
	DWORD dw;
	CreateThread(nullptr, 200000, &SMSProcessThread, (LPVOID)param, THREAD_TERMINATE, &dw);
	_getch();
	return 0;
	*/
	//printf(generatePasswordCode());
	//return 0;

	/*
	for (int i = 0; i < 100; i++) addToReplayList(replay_list[i], 0);
	_getch();
	return 0;
	*/

	/*createRandomClients();
	_getch();
	return 0;
	*/

	for (int i = 0; i < 20; i++) { combin[i] = new int64_t[20]; for (int j = 0; j < 20; j++) combin[i][j] = -1; }
	for (int i = 0; i < 20; i++) { ARS[i] = new double*[20]; for (int j = 0; j < 20; j++) ARS[i][j] = nullptr; }


	/*
	loadCompetitorsFromDB();

	HANDLE File;
	DWORD l = 0;
	char buf[20];
	int i = 0;
	char file_path[MAX_PATH];
	char https_path[MAX_PATH];
	char* recvbuf = new char[EXTRA];
	int len = 0;
	printf(" competitors_l=%d\r\n", competitors_l);
	for (int j = 0; j < competitors_l; j++) {
	std::strcpy(https_path, "/ls/crest/big/");
	_itoa(competitors[j].id, buf, 10);
	strcat(https_path, buf);
	strcat(https_path, ".png");

	std::strcpy(file_path, "D://Logo//");
	_itoa(competitors[j].id, buf, 10);
	strcat(file_path, buf);
	strcat(file_path, ".png");

	printf("process competitors=%s\r\n", competitors[j].name);
	printf("https:/ls.betradar.com/%s\r\n",https_path);

	len = httpsRequest("ls.betradar.com", https_path, recvbuf, 0);
	if (len < 1000) { printf("competitors[j].id=%d no logo\r\n", competitors[j].id); continue; }

	File = CreateFile(file_path, GENERIC_WRITE, 0, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	l = SetFilePointer(File, 0, 0, FILE_BEGIN);

	for (i = 0; i < len - 4; i++) if (recvbuf[i] == '\r' && recvbuf[i + 1] == '\n' && recvbuf[i + 2] == '\r' && recvbuf[i + 3] == '\n') break;

	WriteFile(File, ((char*)((char*)recvbuf + i + 4)), (len - i - 4), &l, nullptr);
	CloseHandle(File);

	}

	delete recvbuf;
	return 0;

	*/

	
	for (int i = 0; i < EVENTS_LENTGH; i++) events_show[i] = bevents_show[i] = nullptr;
	for (int i = 0; i < MAX_LINES; i++) lines_id[i] = blines_id[i] = nullptr;
	for (int i = 0; i < MAX_TOURNAMENTS; i++) tournaments_id[i] = btournaments_id[i] = nullptr;
	for (int i = 0; i < MAX_TOURNAMENTS; i++) seasons_id[i] = bseasons_id[i] = nullptr;
	for (int i = 0; i < MAX_TOURNAMENTS; i++) simples_id[i] = bsimples_id[i] = nullptr;
	for (int i = 0; i < MAX_CATEGORIES; i++) categories_id[i] = bcategories_id[i] = nullptr;
	for (int i = 0; i < MAX_SPORTS; i++) sports_id[i] = bsports_id[i] = nullptr;
	for (int i = 0; i < MAX_COMPETITORS; i++) competitors_id[i] = bcompetitors_id[i] = nullptr;
	for (int i = 0; i < MAX_PLAYERS; i++) players_id[i] = bplayers_id[i] = nullptr;
	for (int i = 0; i < MAX_MARKETS; i++) markets_id[i] = bmarkets_id[i] = nullptr;
	for (int i = 0; i < MAX_MARKETS; i++) max_markets_in[i] = bmax_markets_in[i] = 2;
	for (int i = 0; i < MAX_BETSTOPS; i++) betstops_id[i] = nullptr;
	for (int i = 0; i < MAX_VOIDREASONS; i++) voidreasons_id[i] = nullptr;
	for (int i = 0; i < MAX_MATCHSTATUS; i++) matchstatus_id[i] = nullptr;
	for (int j = 0; j < STEP_QUEUE; j++) {
		array_data_step_2[j] = nullptr;
		array_data_step_1[j] = nullptr;
		data_step_len_1[j] = 0;
		data_step_len_2[j] = 0;
	}
	for (int j = 0; j < AMQP_QUEUE; j++) AMQP_message[j] = new char[AMQP_BUFLEN];


#if BOOKING > 0
	booking = BOOKING;
	getEvents(0, 10);
	return 0;
#endif


#if UPDATE_AND_TRANSLATE == 8
	getSports();
	for (int i = 0; i < sports_l; i++) saveSportToDB(&sports[i]);
	return 0;
#endif

	loadSportsFromDB();

#if UPDATE_AND_TRANSLATE == 1

	int lang_num = LANG_NUM; for (int l = 0; l < lang_num; l++) getSportsTranslate(l); for (int i = 0; i < sports_l; i++) saveSportToDB(&sports[i], true); return 0;
#endif
	if (getBetstops() != -1) std::printf("Load betstops success. Numbers of betstops : %d\r\n", betstops_l);
	if (getVoidreasons() != -1) std::printf("Load voidreasons success. Numbers of voidreasons : %d\r\n", voidreasons_l);
	if (getMatchstatus() != -1) std::printf("Load matchstatus success. Numbers of matchstatus : %d\r\n", matchstatus_l);

#if UPDATE_AND_TRANSLATE == 7
	getMarkets();
	return 0;
#endif
	loadMarketsFromDB();
	//getVariantMarket(markets_id[534][0], "pre:markettext:46330");


	/*for (int j = 0; j < markets_l; j++) { if(markets[j].id > 758 && markets[j].id < 797 && markets[j].variable_text != nullptr ) deleteMarketFromDB(&markets[j]); }
	_getch();
	return 0;*/
	




#if UPDATE_AND_TRANSLATE == 4

	int lang_num = LANG_NUM; for (int l = 0; l < lang_num; l++) { printf("start lang=%s\r\n", lang[l].c_str()); getMarketsTranslate(l);	printf("start2 lang=%s\r\n", lang[l].c_str());  for (int j = 0; j < markets_l; j++) getVariantMarketTranslate(&markets[j], l); } 	for (int j = 0; j < markets_l; j++) { printf("save market %d in total %d\r\n", j, markets_l); saveMarketToDB(&markets[j], true); } return 0;
#endif

#if UPDATE_AND_TRANSLATE == 9

	int lang_num = LANG_NUM; for (int l = 0; l < lang_num; l++) { std::printf("start lang=%s\r\n", lang[l].c_str()); getCategoriesTournamentsTranslate(l); }
	for (int j = 0; j < tournaments_l; j++) { std::printf("save tourn id=%d\r\n", tournaments[j].id); saveTournamentToDB(&tournaments[j], true); }
	for (int j = 0; j < categories_l; j++) { std::printf("save category_id=%d\r\n", categories[j].id); saveCategoryToDB(&categories[j], true); }
	return 0;
#endif

	loadCategoriesFromDB();
	loadTournamentsFromDB();

	//for (int i = 0; i < tournaments_l; i++) { if (tournaments[i].simple_id == 0 && tournaments[i].id == 0) { deleteTournamentFromDB(&tournaments[i]); printf("delete\r\n");} }

#if UPDATE_AND_TRANSLATE == 3
	int lang_num = LANG_NUM; for (int j = 0; j < tournaments_l; j++) { printf("process tornament %d in total %d\r\n", j, tournaments_l); for (int l = 0; l < lang_num; l++) getTournamentTranslate(&tournaments[j], l); saveTournamentToDB(&tournaments[j], true); } return 0;
#endif



#if UPDATE_AND_TRANSLATE == 10
	getEvents(0, 180);
	return 0;
#endif

	loadEventsFromDB();
	loadCompetitorsFromDB();

#if UPDATE_AND_TRANSLATE == 5
	int lang_num = LANG_NUM; for (int j = 0; j < competitors_l; j++) { std::printf("translate competitor nr =%d in total\r\n", j, competitors_l); for (int l = 0; l < lang_num; l++)getCompetitorTranslate(&competitors[j], l); saveCompetitorToDB(&competitors[j], true); } return 0;
#endif

	loadPlayersFromDB();
#if UPDATE_AND_TRANSLATE == 6
	int lang_num = LANG_NUM; for (int j = 0; j < players_l; j++) { std::printf("translate player nr =%d in total\r\n", j, players_l); for (int l = 0; l < lang_num; l++) getPlayerTranslate(&players[j], l); savePlayerToDB(&players[j], true); } return 0;
#endif

	loadClientsFromDB();
	loadBetsFromDB();
	loadTicketsFromDB();




#if UPDATE_AND_TRANSLATE == 2
	get24HoursEventsFixture();
#endif		

	//return 0;


	/*
	if (POPULATE_MONGO) {
	writeSportsDB();
	writeMarketsDB();
	writeCategoriesDB();
	writeEventsDB();
	writeTournamentsDB();
	writeCompetitorsDB();
	writePlayersDB();
	std::printf("Mongo populate finished succes");
	return 0;
	}

	*/

	/*
	Event* stage = new Event();
	stage->id = 350097;
	stage->type_radar = 1;
	getEventFixture(stage);
	stage->id = 342299;
	stage->type_radar = 1;
	getEventFixture(stage);
	_getch();
	return 0;
	*/


	/*
	for (int i = 0; i < 100; i++) addToReplayList(replay_list[i], 0);
	_getch();
	return 0;*/

	hThread1 = CreateThread(nullptr, 67108864, &BetradarGetThread, 0, THREAD_TERMINATE, &dwThreadID1);
	hThread2 = CreateThread(nullptr, 67108864, &BetradarProcessThread, 0, THREAD_TERMINATE, &dwThreadID2);
	hThread5 = CreateThread(nullptr, 67108864, &BetsProcessThread, 0, THREAD_TERMINATE, &dwThreadID5);
	if (MTS_FLAG == 1) {
		mts_error[run_mts_num % 10] = 0;
		hThread3[run_mts_num % 10] = CreateThread(nullptr, 67108864, &MTSPublishThread, 0, THREAD_TERMINATE, &dwThreadID3[run_mts_num % 10]);
		hThread9[run_mts_num % 10] = CreateThread(nullptr, 67108864, &MTSConsumeThread, 0, THREAD_TERMINATE, &dwThreadID9[run_mts_num % 10]);
	}
	//hThread8 = CreateThread(nullptr, 16777216, &ClientSMSProcessThread, 0, THREAD_TERMINATE, &dwThreadID8);

	int port = 1443;
	//while (port == 1443) Sleep(10000);

	//server.setOpenHandler(openHandler);
	//server.setCloseHandler(closeHandler);
	//server.setMessageHandler(messageHandler);
	//server.setPeriodicHandler(periodicHandler);

	//while (port == 1443) Sleep(1);
	//_getch();
	server.startServer(port);

	return 0;


}


char* generateSmsCode() {
	char* sms = new char[10];
	char* int_buf = new char[10];
	SYSTEMTIME st;
	memset(&st, 0, sizeof(st));
	GetSystemTime(&st);
	_itoa(st.wMilliseconds, int_buf, 10);
	strcpy(sms, int_buf);
	_itoa(st.wSecond, int_buf, 10);
	strcat(sms, int_buf);
	return sms;
}
char* generatePasswordCode() {
	SYSTEMTIME st;
	char* password = new char[9];
	memset(&st, 0, sizeof(st));
	GetSystemTime(&st);
	int indexchar[62];
	for (int i = 0; i < 10; i++) indexchar[i] = 48 + i;
	for (int i = 10; i < 36; i++) indexchar[i] = 65 + i - 10;
	for (int i = 36; i < 62; i++) indexchar[i] = 97 + i - 36;
	password[8] = 0;
	for (int i = 0; i < 8; i++) {
		if (i == 0)	password[i] = indexchar[(st.wMilliseconds) % 62]; else
			if (i % 5 == 0)	password[i] = indexchar[(st.wMilliseconds / i) % 62];
			else if (i % 3 == 0)	password[i] = indexchar[((st.wSecond - i) * st.wMilliseconds) % 62];
			else if (i % 4 == 0)	password[i] = indexchar[(st.wMinute * st.wMilliseconds / 100) % 62];
			else if (i % 2 == 0)	password[i] = indexchar[(st.wSecond * st.wMilliseconds / i) % 62];
			else password[i] = indexchar[((st.wMilliseconds*i + st.wDay + st.wYear + st.wMonth + st.wHour) / (st.wSecond + 1)) % 62];
	}
	return password;
};



DWORD WINAPI ClientSMSProcessThread(LPVOID lparam) {

	int init_count = 0;
	int sleep_time = 1500;;
	string input_message;
	int select_sender = 0;
	cout << "Выберите отправителя (1)Sportliga (2)PassionBet (3)TM.Bet (4)Starbet.tm  (5)Marathonbet" << endl;
	cin >> select_sender;
	cout << "Введите текст сообщения для отправки клиентам:" << endl;
	cin.ignore();
	getline(cin, input_message);
	//printf(input_message.c_str());
	cout << "\r\nВведите задержку между отправкой сообщений в милисекундах: " << endl;
	cin >> sleep_time;
	cout << "\r\nВведите c какого по счету номера телефона начинать( 0 с начала списка): " << endl;
	cin >> init_count;
	if (select_sender < 1 || select_sender > 5) select_sender = 2;


	char* file_path = new char[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, file_path);
	strcat(file_path, "//tel.txt");
	//printf(file_path);
	//C://Users//andrei//Documents//Visual Studio 2015//Projects//socketssl//x64//Release//tel.txt
	HANDLE File = CreateFile(file_path, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == File) {
		std::printf("ERROR OPEN FILE tel.txt");
		CloseHandle(File);
		return 0;
	}
	DWORD size = SetFilePointer(File, 0, 0, FILE_END);
	DWORD l = SetFilePointer(File, 0, 0, FILE_BEGIN);
	char* phoneList = new char[size + 1];
	ReadFile(File, phoneList, size, &l, nullptr);
	int num_of_phone = (size + 2) / 13;
	//printf("num_of_phone=%d", num_of_phone);
	//printf("size=%I64d", size);
	CloseHandle(File);


	char* message = new char[MAX_PATH];
	strcpy(message, input_message.c_str());
	//strcpy(message, "Pri popolnenii s pomoshch'yu WebMoney ili VISA, Vy poluchite bonus 15% ot depozita. sportliga.bet");

	char* recv = new char[SMALL];
	char* request = new char[MAX_PATH];
	char* phone = new char[64];


	for (int i = init_count; i < num_of_phone; i++) {
		Sleep(sleep_time);
		phone[0] = 0;
		strncpy(phone, (char*)((char*)phoneList + 13 * i), 11);
		phone[12] = 0;
		switch (select_sender) {
		case 1:
			strcpy(request, "/sys/send.php?login=Atajan&psw=Qwaszx654&sender=Sportliga&phones=");
			break;
		case 2:
			strcpy(request, "/sys/send.php?login=Atajan&psw=Qwaszx654&sender=PassionBet&phones=");
			break;
		case 3:
			strcpy(request, "/sys/send.php?login=Atajan&psw=Qwaszx654&sender=TM.Bet&phones=");
			break;
		case 4:
			strcpy(request, "/sys/send.php?login=Atajan&psw=Qwaszx654&sender=Starbet.tm&phones=");
			break;
		case 5:
			strcpy(request, "/sys/send.php?login=Atajan&psw=Qwaszx654&sender=Marathonbet&phones=");
			break;

		}
		strcat(request, phone);
		strcat(request, "&mes=");
		strcat(request, message);
		httpsRequestExtern("smsc.ru", request, recv, 0);
		printf(request);
		printf("\r\n");
		printf(recv);
		printf("\r\n");
		printf("Отправленно %d клиентам, осталось еще %d\r\n", i, (num_of_phone - i));

	}

	delete[] recv;
	delete[] message;
	delete[] request;
	delete[] phone;
	phone = nullptr;
	message = nullptr;
	request = nullptr;
	recv = nullptr;

	return 0;
}
DWORD WINAPI SMSProcessThread(LPVOID lparam) {
	char* phone = nullptr;;
	char* sms = nullptr; ;
	char* recv = new char[SMALL];
	char* request = new char[MAX_PATH];
	memcpy(&phone, ((char*)lparam), sizeof(char*));
	memcpy(&sms, ((char*)lparam + sizeof(char*)), sizeof(char*));
	strcpy(request, SMS_REQUEST);
	strcat(request, phone);
	strcat(request, "&mes=");
	strcat(request, sms);
	httpsRequestExtern("smsc.ru", request, recv, 0);
	printf(request);
	printf("\r\n");
	printf(recv);
	printf("\r\n");
	delete[] recv;
	delete[] sms;
	delete[] request;
	delete[] lparam;
	delete[] phone;
	phone = nullptr;
	sms = nullptr;
	request = nullptr;
	recv = nullptr;
	return 0;
}
DWORD WINAPI StateFullEvent(LPVOID lparam) {

	recoveryStatefull();

	char* recvbuf = new char[EXTRA];
	char* request = new char[MAX_PATH];
	char* int_buf = new char[MAX_PATH];
	int type_radar;
	bool failed_recovery = false;


	for (auto it = recovery_statefull.begin(); it != recovery_statefull.end(); ++it) {
		std::strcpy(request, "/v1/pre/stateful_messages/events/");
		_itoa(it->first, int_buf, 10);
		if (it->second == 0) std::strcat(request, "sr:match:"); else
			if (it->second == 1) std::strcat(request, "sr:race_event:"); else
				if (it->second == 2) std::strcat(request, "sr:simple_tournament:"); else
					if (it->second == 3) std::strcat(request, "sr:season:"); else
						if (it->second == 4) std::strcat(request, "sr:race_tournament:");
		std::strcat(request, int_buf); std::strcat(request, "/initiate_request?request_id=1");
		//printf("request = %s\r\n", request);
		while (httpsRequest("api.betradar.com", request, recvbuf, 1) == -1)  Sleep(1000);

	}

	for (auto it = recovery_statefull.begin(); it != recovery_statefull.end(); ++it) {
		std::strcpy(request, "/v1/liveodds/stateful_messages/events/");
		_itoa(it->first, int_buf, 10);

		if (it->second == 0) std::strcat(request, "sr:match:"); else
			continue;
		std::strcat(request, int_buf); std::strcat(request, "/initiate_request?request_id=1");
		while (httpsRequest("api.betradar.com", request, recvbuf, 1) == -1)  Sleep(1000);

	}

	//if (counter > 9) failed_recovery = true;

	delete[] request;
	delete[] recvbuf;
	delete[] int_buf;


	return 0;
}
DWORD WINAPI BetradarGetThread(LPVOID lparam) {
	if (startRecovery() == -1) {
		return 0;
	}
	rabbitmqssl();
	return 0;
}
DWORD WINAPI BetradarProcessThread(LPVOID lparam)
{
	using namespace rapidxml;
	using namespace std;
	xml_document<> doc;
	HANDLE File;
	DWORD l = 0;
	amqp_frame_t frame;
	uint64_t now;
	char* name = new char[MAX_PATH];
	char* buf = new char[MAX_PATH];
	char set_scores[1024];
	char* maxbuf = new char[200000];
	char* specifier_value = new char[MAX_PATH];

	Event* _event = nullptr;
	Tournament* _tournament = nullptr;
	int i = 0;
	int k = 0;
	int j = 0;
	int m = 0;
	int n = 0;
	int q = 0;
	int z = 0;
	int u = 0;
	int write_count_file = 0;
	//bool DEBUG_OUTPUT = false;
	int event_id = 0;
	string key = "";
	string tournament_key;
	string season_key;
	string event_key;
	string line_key;
	int type_radar = 0;
	int status = 0;
	int betstop_reason = 0;
	int index_separator[100];
	int index_equally[100];
	int outcome_number;
	char** outcome_name = new char*[500];
	int* outcome_id = new int[500];
	int* outcome_active = new int[500];
	int* outcome_team = new int[500];
	float* outcome_probabilities = new float[500];
	float* outcome_odds = new float[500];
	for (int i = 0; i < 500; i++) outcome_name[i] = nullptr;
	Line* _line = new Line();
	Market* _market = nullptr;
	//char* socket_message_big = new char[145000];
	char* buffer = new char[145000];
	size_t offset = 0;
	size_t retry_offset = 0;
	int jump = -1;
	size_t t_offset = 0;
	int event_lines_l = 0;
	char* zip_message = nullptr;
	char** jump_buf = new char*[JUMP_PROCESS + 150];
	int* jump_buf_len = new int[JUMP_PROCESS + 150];
	for (i = 0; i < JUMP_PROCESS + 150; i++) jump_buf[i] = nullptr;
	int zip_len = 0;
	char* encode_message = nullptr;;// = SendframeEncode(zip_message, zip_len, len);
	int encode_message_len = 0;
	//char* socket_message_little = new char[4096];
	int outcomeNameError = 0;
	int ret_fixture = 0;
	bool new_message_arrived = false;
	vector<int> clientIDs;
	int64_t last_recovery_timestamp = timestamp();
	int64_t last_recovery_message_timestamp = 0;
	int request_id = 0;
	int recovery_timestamp_integer;
	int counter_snapshot = 0;
	bool radar_message = true;
	bool new_variant = false;
	int props_player_id = 0;

	for (;;) {


		if (recovery_state == 0) {

			//if (new_message_arrived == true)  GenerateBigStep();
			if (jump > JUMP_PROCESS || jump == -1)  GenerateBigStep();

			clientIDs.clear();
			clientIDs = server.getClientIDs();
			for (i = 0; i < clientIDs.size(); i++) {
				if (server.wsClients[clientIDs[i]] == nullptr || server.wsClients[clientIDs[i]]->timestamp > 0)  continue;
				if (server.wsClients[clientIDs[i]]->plus_create == true && server.wsClients[clientIDs[i]]->plus_send == false)
					CreatePlus_2(server.wsClients[clientIDs[i]]);
				if (server.wsClients[clientIDs[i]]->outright_create == true && server.wsClients[clientIDs[i]]->outright_send == false)
					CreateOutright_2(server.wsClients[clientIDs[i]]);
				if (server.wsClients[clientIDs[i]]->init == 0) {
					for (int j = 0; j < jump; j++) server.wsSend(clientIDs[i], jump_buf[j], jump_buf_len[j]);
					server.wsClients[clientIDs[i]]->init = 1;

				}

			}

			if (jump > JUMP_PROCESS || jump == -1)  jump = 0;

		}



		//if(timestamp()- alive_timestamp > 40000)

		if (recovery_timestamp > last_recovery_timestamp) last_recovery_timestamp = recovery_timestamp;
		if (last_recovery_message_timestamp > last_recovery_timestamp) last_recovery_timestamp = last_recovery_message_timestamp;

		if (REPLAY == 0 && (timestamp() - last_recovery_timestamp > 15000))
		{
			recovery_state_timestamp = -1;

			if (recovery_state == 0) {
				offset = 0;
				writeInteger(buffer, offset, 0, 1);//sistem request_id
				writeInteger(buffer, offset, 1, 1);
				zip_len = gzip(buffer, offset, zip_message, 9);
				encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
				radarMessageHandler(encode_message, encode_message_len);
				if (jump_buf[jump] != nullptr) delete[] jump_buf[jump];
				jump_buf[jump] = encode_message;
				jump_buf_len[jump] = encode_message_len;
				//jump++;
				//delete[] encode_message;
				encode_message = nullptr;
				delete[] zip_message;
				zip_message = nullptr;
				offset = 0;
			}
			TerminateProcess(hThread1, 0);
			Sleep(15000);
			last_recovery_timestamp = timestamp();

			//recoveryStatefull(); 
			hThread1 = CreateThread(nullptr, 16777216, &BetradarGetThread, 0, THREAD_TERMINATE, &dwThreadID1);

		}

		status = 0;

		offset = 0;
		if (process_index >= rabbit_index) { new_message_arrived = false; continue; }
		if (DEBUG_OUTPUT == true) std::printf("process_index=%d\r\n", process_index);
		if (DEBUG_OUTPUT == true) std::printf("rabbit_index=%d\r\n", rabbit_index);


		//int p1 = timestamp();
		//printf("process_index=%d rabbit_index=%d events_show_l=%d\r\n", process_index, rabbit_index, events_show_l);

		new_variant = false;
		new_message_arrived = true;
		if (DEBUG_OUTPUT == true) std::printf("doc.parse<0>\r\n");
		std::strcpy(maxbuf, AMQP_message[process_index%AMQP_QUEUE]);
		if (DEBUG_OUTPUT == true) std::printf("doc.parse<0> end length=%d\r\n", strlen(AMQP_message[process_index%AMQP_QUEUE]));
		doc.parse<0>(maxbuf);// (AMQP_message[process_index%AMQP_QUEUE]);
		process_index++;
		//new_message_arrived = false;

		//printf("doc2.parse<0>\r\n");

		if (doc.first_node() == nullptr) {
			if (DEBUG_OUTPUT == true) std::printf("doc null\r\n");
			new_message_arrived = false; continue;
		}

		//new_message_arrived = true;
		last_recovery_timestamp = timestamp();
		//printf("doc3.parse<0>\r\n");

		radar_message = true;


		//recovery_state_timestamp = 0;
		//printf("xml = %s", AMQP_message[(process_index - 1) % AMQP_QUEUE]);

		ret_fixture = 0;
		if (std::strcmp("fixture_change", doc.first_node()->name()) == 0) {

			if (recovery_state_timestamp != 0 || recovery_state != 0) {
				request_id = -1;
				if (doc.first_node()->first_attribute("request_id")) request_id = atoi(doc.first_node()->first_attribute("request_id")->value());
				if (request_id == recovery_timestamp_integer && doc.first_node()->first_attribute("timestamp")) last_recovery_message_timestamp = _atoi64((char*)((char*)doc.first_node()->first_attribute("timestamp")->value()));

			}

			if (DEBUG_OUTPUT == true) std::printf("fixture_change\r\n");
			type_radar = 0;
			event_id = 0;
		//	if (VIRTUAL == 0 && doc.first_node()->first_attribute("event_id")->value()[0] == 'v') continue;// { printf("\r\n\r\n%s\r\n\r\n", AMQP_message[(process_index - 1) % AMQP_QUEUE]); continue; }

			
			if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:match:", 9) == 0)
			{ event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9)); type_radar = 0;
			event_key = "0" + to_string(event_id);}
			else if(strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:season:", 10) == 0)
			{event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 10)); type_radar = 3; season_key = "0" + to_string(event_id);}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:simple_tournament:", 21) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 21)); type_radar = 2; tournament_key = "2" + to_string(event_id);
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:race_tournament:", 19) == 0)
			{event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 19)); type_radar = 4; tournament_key = "1" + to_string(event_id);}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:match:", 9) == 0)
			{event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9)); type_radar = 5; event_key = "3" + to_string(event_id);}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:season:", 10) == 0)
			{event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 10)); type_radar = 6; season_key = "3" + to_string(event_id);}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:tournament:", 14) == 0) {
			event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 14)); type_radar = 7; continue;}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:stage:", 9) == 0)
			{ type_radar = 1; event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
				 key ="1"+ string((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
				 if (events_id.find(key) != events_id.end() && tournaments_id.find(key) == tournaments_id.end()) { type_radar = 1; event_key = "1" + to_string(event_id); }
				else if (events_id.find(key) == events_id.end() && tournaments_id.find(key) != tournaments_id.end()) { type_radar = 4; tournament_key = "1" + to_string(event_id); }
				else {
					type_radar = -1;
					tournaments[tournaments_l].id = event_id;
					tournaments[tournaments_l].type_radar = 1;
					tournaments[tournaments_l].season_id = 0;
				if (getTournament(&tournaments[tournaments_l], false) == -1) {
                    	tournaments[tournaments_l].id = 0; tournaments[tournaments_l].type_radar = 0;
						events[events_l].id = event_id; events[events_l].type_radar = 1;
						ret_fixture = getEventFixture(&events[events_l]);
						if (ret_fixture == -1) {
							events[events_l].id = 0; events[events_l].type_radar = 0;
						}
						else { events_l++; type_radar = 1; event_key = "1" + to_string(event_id); }
					}
					else { type_radar = 4;  tournaments_l++; tournament_key = "1" + to_string(event_id); }
				}
				if (type_radar == -1) continue; }

			else { std::printf("Unknown type radar in fixture_change =%s", (char*)doc.first_node()->first_attribute("event_id")->value()); continue; };


			//	if(type_radar == 1) printf("fixture_message= = %s\r\n", AMQP_message[(process_index - 1) % AMQP_QUEUE]);

			//0 sr:match://1 sr:race_event(sr:stage) //2 sr:simple_tournament://3 sr:season://4 sr:race_tournament://5 vf:match //6 sr:season: 7 //vf:tournament:


			if (DEBUG_OUTPUT == true) std::printf("fixture_change type_radar=%d\r\n", type_radar);

			
			if (type_radar == 2 || type_radar == 4) {
				if (tournaments_id.find(tournament_key) == tournaments_id.end()) {
					std::printf("Simple or race tournament not found. Run getTournament(). tournament_id=%d type_radar=%d\r\n", event_id, type_radar);
					tournaments[tournaments_l].id = event_id;
					if (type_radar == 2) tournaments[tournaments_l].type_radar = 2;
					else if (type_radar == 2) tournaments[tournaments_l].type_radar = 1;
					if (getTournament(&tournaments[tournaments_l], false) == -1) { std::printf("ERROR!\r\nTournaments  id not found in run fixture change tournament_id= %d type_radar=%d\r\n", event_id, type_radar); continue; }
					tournaments_l++;
					if (recovery_state == 0) {
						t_offset = 0;
						writeInteger(buffer, t_offset, 0, 1);//sistem request_id
						writeInteger(buffer, t_offset, 0, 2);
						writeInteger(buffer, t_offset, 0, 2);
						writeInteger(buffer, t_offset, 1, 2);
						writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].type_radar, 1);
						writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].id, 4);
						writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].season_id, 4);
						//writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].id, 4);
						writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].sport_id, 2);
						writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].category_id, 2);
						writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].sort, 2);
						writeString(buffer, t_offset, tournaments[tournaments_l - 1].name);
						writeInteger(buffer, t_offset, 0, 2);
						zip_len = gzip(buffer, t_offset, zip_message, 1);
						if (zip_len > 1)
						{
							encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
							radarMessageHandler(encode_message, encode_message_len);
							if (jump_buf[jump] != nullptr) delete[] jump_buf[jump];
							jump_buf[jump] = encode_message;
							jump_buf_len[jump] = encode_message_len;
							jump++;
							//delete[] encode_message;
							encode_message = nullptr;

						}
						delete[] zip_message;
						zip_message = nullptr;
						if (DEBUG_OUTPUT == true) printf("new simple tournament  in fixture change radarmessagehandler\r\n");


						t_offset = 0;
					}

				}

				else if (getTournament(tournaments_id[tournament_key], false) == -1) { std::printf("ERROR!\r\nTournaments id not found in run fixture = %d type_radar=%d\r\n", event_id, type_radar); continue; }
				std::printf("fixture_change succes for tournamnet  id=%d type_radar=%d\r\n", event_id, type_radar);


			}
			if (type_radar == 3 || type_radar == 6) {
				if (seasons_id.find(season_key) == seasons_id.end()) {
					std::printf("Tournament not found in run fixture change. Run getTournament(). season_id=%d type_radar=%d\r\n", event_id, type_radar);
					tournaments[tournaments_l].id = 0;
					tournaments[tournaments_l].season_id = event_id;
					if (type_radar == 3) tournaments[tournaments_l].type_radar = 0;
					else if (type_radar == 6) tournaments[tournaments_l].type_radar = 3;
					if (getTournament(&tournaments[tournaments_l], false) == -1) { std::printf("ERROR!\r\nTournament season id not found in run %d type_radar=%d\r\n", event_id, type_radar); continue; }
					else {
						if (seasons_id.find(season_key) == seasons_id.end()) {
							std::printf("ERROR!\r\nTournament season id not found after succes in getTournament run %d\r\n", event_id);

							continue;
						}
						tournaments_l++;
						if (recovery_state == 0) {
							t_offset = 0;
							writeInteger(buffer, t_offset, 0, 1);//sistem request_id
							writeInteger(buffer, t_offset, 0, 2);
							writeInteger(buffer, t_offset, 0, 2);
							writeInteger(buffer, t_offset, 1, 2);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].type_radar, 1);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].id, 4);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].season_id, 4);
							//writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].simple_id, 4);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].sport_id, 2);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].category_id, 2);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].sort, 2);
							writeString(buffer, t_offset, tournaments[tournaments_l - 1].name);
							writeInteger(buffer, t_offset, 0, 2);
							zip_len = gzip(buffer, t_offset, zip_message, 1);
							if (zip_len > 1)
							{
								encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
								radarMessageHandler(encode_message, encode_message_len);
								if (jump_buf[jump] != nullptr) delete[] jump_buf[jump];
								jump_buf[jump] = encode_message;
								jump_buf_len[jump] = encode_message_len;
								jump++;
								//delete[] encode_message;
								encode_message = nullptr;

							}
							delete[] zip_message;
							zip_message = nullptr;
							if (DEBUG_OUTPUT == true) printf("new season tournament  in fixture change radarmessagehandler\r\n");


							t_offset = 0;
						}



						std::printf("fixture_change succes for tournamnet season id=%d\r\n", event_id);




					}
				}
				else if (getTournament(seasons_id[event_id], false) == -1) { std::printf("ERROR!\r\n getTournament in fixture_change season id =%d type_radar=%d\r\n", event_id, type_radar); continue; }

				std::printf("fixture_change succes for tournamnet season id=%d type_radar=%d\r\n", event_id, type_radar);

			}
	
			if (type_radar == 0 || type_radar == 1 || type_radar == 5) {
				//	if (event_id >= MAX_EVENTS) { std::printf("ERROR DATA!\r\nsevent id out of MAX_EVENTS in run %d\r\n", event_id); continue; }
				if (events_id.find(event_key) == events_id.end()) {
					std::printf("Event not found in fixture_change. %d type_radar=%d\r\n", event_id);
					events[events_l].id = event_id; 
					if (type_radar == 0 || type_radar == 1) events[events_l].type_radar = type_radar; else 
						if (type_radar == 5 ) events[events_l].type_radar = 3;
					ret_fixture = getEventFixture(&events[events_l]);
					if (ret_fixture == -1) { std::printf("fixture_change error. %d type_radar=%d\r\n", event_id, type_radar); events[events_l].id = 0; events[events_l].type_radar = 0; continue; }
					else events_l++;
				}
				else ret_fixture = getEventFixture(events_id[event_key]);

				if (ret_fixture == -1) { std::printf("fixtur_change error. %d\r\n", event_id);  continue; }

				if (recovery_state == 0 && ret_fixture == 1) {
					t_offset = 0;
					writeInteger(buffer, t_offset, 0, 1);//sistem request_id
					writeInteger(buffer, t_offset, 0, 2);
					writeInteger(buffer, t_offset, 0, 2);
					writeInteger(buffer, t_offset, 1, 2);
					writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].type_radar, 1);
					writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].id, 4);
					writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].season_id, 4);
					writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].sport_id, 2);
					writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].category_id, 2);
					writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].sort, 2);
					writeString(buffer, t_offset, tournaments[tournaments_l - 1].name);
					writeInteger(buffer, t_offset, 0, 2);
					zip_len = gzip(buffer, t_offset, zip_message, 1);
					if (zip_len > 1)
					{
						encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
						radarMessageHandler(encode_message, encode_message_len);
						if (jump_buf[jump] != nullptr) delete[] jump_buf[jump];
						jump_buf[jump] = encode_message;
						jump_buf_len[jump] = encode_message_len;
						jump++;
						//delete[] encode_message;
						encode_message = nullptr;

					}
					delete[] zip_message;
					zip_message = nullptr;
					if (DEBUG_OUTPUT == true) std::printf("new simple tournament  in fixture change radarmessagehandler\r\n");


					t_offset = 0;
				}
				std::printf("fixture_change success. event_id=%d event_key=%s\r\n", event_id, event_key);
                
				_event = events_id[event_key];

				 if (recovery_state == 0 && _event->status != -1 && _event->bet_stop == 0) {
					offset = 0;
					writeInteger(buffer, offset, 0, 1);//request_id
					writeInteger(buffer, offset, 1, 2);
					writeInteger(buffer, offset, type_radar, 1);
					writeInteger(buffer, offset, _event->id, 4);
					writeInteger(buffer, offset, _event->home_id, 4);
					writeInteger(buffer, offset, _event->away_id, 4);

					writeInteger(buffer, offset, _event->type_radar, 1);
					writeInteger(buffer, offset, _event->status, 1);
					writeInteger(buffer, offset, _event->sport_id, 2);
					writeInteger(buffer, offset, _event->category_id, 2);
					if (_event->type_radar<2) writeInteger(buffer, offset, _event->tournament_id, 4);
					else writeInteger(buffer, offset, _event->simple_id, 4);
					writeInteger(buffer, offset, _event->start_time, 4);
					writeInteger(buffer, offset, _event->period_length, 1);
					writeInteger(buffer, offset, _event->overtime_length, 1);
					if (_event->sport_id == 5) writeInteger(buffer, offset, _event->bo, 1);
					writeString(buffer, offset, _event->home_name);
					writeString(buffer, offset, _event->away_name);
					writeString(buffer, offset, _event->tv_channels);
					if (_event->status > 0) {

						writeInteger(buffer, offset, (int)(_event->home_score * 100), 2);
						writeInteger(buffer, offset, (int)(_event->away_score * 100), 2);
						writeString(buffer, offset, _event->set_scores);
						writeString(buffer, offset, _event->match_time);
						writeString(buffer, offset, _event->remaining_time);
						writeString(buffer, offset, _event->remaining_time_in_period);
						writeString(buffer, offset, matchstatus_id[_event->match_status]->description);
						writeInteger(buffer, offset, _event->stopped, 1);
						//writeInteger(buffer, offset, _event->stopped, 1); 
						if (_event->sport_id == 1) {
							writeInteger(buffer, offset, _event->home_redcards, 1);
							writeInteger(buffer, offset, _event->home_yellowcards, 1);
							writeInteger(buffer, offset, _event->away_redcards, 1);
							writeInteger(buffer, offset, _event->away_yellowcards, 1);
							writeString(buffer, offset, _event->stoppage_time);
							writeString(buffer, offset, _event->stoppage_time_announced);
							writeInteger(buffer, offset, _event->home_corners, 1);
							writeInteger(buffer, offset, _event->away_corners, 1);
							writeInteger(buffer, offset, _event->home_yellow_red_cards, 1);
							writeInteger(buffer, offset, _event->away_yellow_red_cards, 1);
						}

						if (_event->sport_id == 5) {
							writeInteger(buffer, offset, _event->home_gamescore, 1);
							writeInteger(buffer, offset, _event->away_gamescore, 1);
							writeInteger(buffer, offset, _event->tiebreak, 1);
						}

						if (_event->sport_id == 20) writeInteger(buffer, offset, _event->expedite_mode, 1);


						if (_event->sport_id == 4 || _event->sport_id == 6 || _event->sport_id == 29) {
							writeInteger(buffer, offset, _event->home_suspend, 1); writeInteger(buffer, offset, _event->away_suspend, 1);
						}


						if (_event->sport_id == 5 || _event->sport_id == 20 || _event->sport_id == 34 || _event->sport_id == 19 || _event->sport_id == 23 || _event->sport_id == 22 || _event->sport_id == 31)
							writeInteger(buffer, offset, _event->current_server, 1);


						if (_event->sport_id == 3) {
							writeInteger(buffer, offset, _event->home_batter, 1);
							writeInteger(buffer, offset, _event->away_batter, 1);
							writeInteger(buffer, offset, _event->outs, 1);
							writeInteger(buffer, offset, _event->balls, 1);
							writeInteger(buffer, offset, _event->strikes, 1);
							writeString(buffer, offset, _event->bases);
						}

						if (_event->sport_id == 16) {
							writeInteger(buffer, offset, _event->possession, 1);
							writeInteger(buffer, offset, _event->try_num, 1);
							writeInteger(buffer, offset, _event->yards, 1);
						}




						if (_event->sport_id == 19) {
							writeInteger(buffer, offset, _event->visit, 1);
							writeInteger(buffer, offset, _event->remaining_reds, 1);
						}


						if (_event->sport_id == 22) {
							writeInteger(buffer, offset, _event->home_legscore, 1);
							writeInteger(buffer, offset, _event->away_legscore, 1);
							writeInteger(buffer, offset, _event->throw_num, 1);
							writeInteger(buffer, offset, _event->visit, 1);
						}

						if (_event->sport_id == 32) {
							writeInteger(buffer, offset, _event->delivery, 1);
							writeInteger(buffer, offset, _event->home_remaining_bowls, 1);
							writeInteger(buffer, offset, _event->away_remaining_bowls, 1);
							writeInteger(buffer, offset, _event->current_end, 1);
						}

						if (_event->sport_id == 21) {
							writeInteger(buffer, offset, _event->home_dismissals, 1);
							writeInteger(buffer, offset, _event->away_dismissals, 1);
							writeInteger(buffer, offset, _event->home_penalty_runs, 1);
							writeInteger(buffer, offset, _event->away_penalty_runs, 1);
							writeInteger(buffer, offset, _event->innings, 1);
							writeInteger(buffer, offset, _event->over, 1);
							writeInteger(buffer, offset, _event->delivery, 1);

						}

						if (_event->sport_id == 109) writeInteger(buffer, offset, _event->current_ct_team, 1);

						writeInteger(buffer, offset, _event->position, 1);

					}
					else writeInteger(buffer, offset, _event->booked, 1);


					if (event2lines.find(_event->getCatKey()) == event2lines.end()) writeInteger(buffer, offset, 0, 2);
					else writeInteger(buffer, offset, event2lines[_event->getCatKey()]->size(), 2);


					//retry_offset = offset;
					//offset += 2;
					event_lines_l = 0;
					writeInteger(buffer, offset, event_lines_l, 2);


					if (DEBUG_OUTPUT == true) std::printf("fixture radarmessagehandler\r\n");

					zip_len = gzip(buffer, offset, zip_message, 2);
					//delete[] buffer;
					if (zip_len > 1)
					{
						encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
						//while (server.ws_clients_flag.test_and_set(std::memory_order_acquire));
						radarMessageHandler(encode_message, encode_message_len);
						if (jump_buf[jump] != nullptr) delete[] jump_buf[jump];
						jump_buf[jump] = encode_message;
						jump_buf_len[jump] = encode_message_len;
						jump++;
						//server.ws_clients_flag.clear(std::memory_order_release);
						//printf("encode_message_len=%d\r\n", encode_message_len);
						//delete[] encode_message;
						encode_message = nullptr;

					}
					delete[] zip_message;
					zip_message = nullptr;
					if (DEBUG_OUTPUT == true) std::printf("fixture end radarmessagehandler\r\n");




				}
			}

		}
		else if (std::strcmp("odds_change", doc.first_node()->name()) == 0) {
			if (recovery_state_timestamp != 0 || recovery_state != 0) {
				request_id = -1;
				if (doc.first_node()->first_attribute("request_id")) request_id = atoi(doc.first_node()->first_attribute("request_id")->value());
				if (request_id == recovery_timestamp_integer && doc.first_node()->first_attribute("timestamp")) last_recovery_message_timestamp = _atoi64((char*)((char*)doc.first_node()->first_attribute("timestamp")->value()));

			}

			type_radar = 0;
			event_id = 0;
			//printf("\r\n\r\n%s\r\n\r\n", AMQP_message[(process_index - 1) % AMQP_QUEUE]); continue;
			
			
			if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:season:", 10) == 0)
			{event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 10)); type_radar = 3;}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:match:", 9) == 0)
			{event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9)); type_radar = 0;}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:simple_tournament:", 21) == 0)
			{event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 21)); type_radar = 2;}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:race_tournament:", 19) == 0)
			{event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 19)); type_radar = 4;}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:match:", 9) == 0)
			{event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9)); type_radar = 5; 
			 continue;}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:season:", 10) == 0)
			{event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 10)); type_radar = 6; continue;}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:tournament:", 14) == 0) 
			{event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 14)); type_radar = 7; continue;}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:stage:", 9) == 0)
			{	type_radar = 1; event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
				key = "1"+string((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
				if (events_id.find(key) != events_id.end() && (event_id >= MAX_TOURNAMENTS || tournaments_id[event_id] == nullptr)) type_radar = 1;
				else if (events_id.find(key) == events_id.end() && event_id < MAX_TOURNAMENTS && tournaments_id[event_id] != nullptr) type_radar = 4;
				else if (events_id.find(key) == events_id.end() && (event_id >= MAX_TOURNAMENTS || tournaments_id[event_id] == nullptr)) {
					type_radar = -1;
					tournaments[tournaments_l].id = event_id;
					tournaments[tournaments_l].type_radar = 1;
					tournaments[tournaments_l].season_id = 0;
					tournaments[tournaments_l].simple_id = 0;
					if (event_id >= MAX_TOURNAMENTS || getTournament(&tournaments[tournaments_l], false) == -1) {

						tournaments[tournaments_l].id = 0; tournaments[tournaments_l].type_radar = 0;
						events[events_l].id = event_id; events[events_l].type_radar = 1;
						ret_fixture = getEventFixture(&events[events_l]);
						if (ret_fixture == -1) {
							events[events_l].id = 0; events[events_l].type_radar = 0;
						}
						else { events_l++; type_radar = 1; }
					}
					else { type_radar = 4;  tournaments_l++; }
				}
				if (type_radar == -1) continue;
			}

			else { std::printf("Unknown type radar in odds_change =%s", (char*)doc.first_node()->first_attribute("event_id")->value()); continue; };
			//0 sr:match://1 sr:race_event(sr:stage) //2 sr:simple_tournament://3 sr:season://4 sr:race_tournament://5 vf:match //6 sr:season: 7 //vf:tournament:

			key = to_string(type_radar) + to_string(event_id);

			_line->type_radar = type_radar;
			_line->key = key;
		
			//if (event_id == 14122909|| event_id == 14093243) printf("\r\r\n\nodds_message =  %s\r\n\r\n", AMQP_message[(process_index - 1) % AMQP_QUEUE]);


			if (event_id == 0) {
				std::printf("event_id error=0 %s\r\n", doc.first_node()->first_attribute("event_id")->value()); std::printf(doc.first_node()->first_attribute("event_id")->value());
				continue;
			}

			//if(event_id== 13941305 || event_id == 12152088 || event_id == 12152088 || event_id == 14125087) printf("\r\n\odds_message= %s\r\n", AMQP_message[(process_index - 1) % AMQP_QUEUE]);

			if (DEBUG_OUTPUT == true) std::printf("odds_change type_radar=%d\r\n", type_radar);

			if (type_radar == 2) {

				if (event_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nssimple id out of MAX_TOURNAMENTS in run odds_change %d\r\n", event_id); continue; }
				if (simples_id[event_id] == nullptr) {
					std::printf("Simple tournament not found. Run getTournament(). simple_id=%d\r\n", event_id);
					tournaments[tournaments_l].id = 0;
					tournaments[tournaments_l].simple_id = event_id;
					tournaments[tournaments_l].type_radar = 2;
					if (getTournament(&tournaments[tournaments_l], false) == -1) { std::printf("ERROR!\r\nTournaments simple id not found in run simple %d\r\n", event_id); continue; }
					tournaments_l++;
					if (recovery_state == 0) {
						t_offset = 0;
						writeInteger(buffer, t_offset, 0, 1);//sistem request_id 
						writeInteger(buffer, t_offset, 0, 2);
						writeInteger(buffer, t_offset, 0, 2);
						writeInteger(buffer, t_offset, 1, 2);
						writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].type_radar, 1);
						writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].id, 4);
						writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].season_id, 4);
						writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].simple_id, 4);
						writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].sport_id, 2);
						writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].category_id, 2);
						writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].sort, 2);
						writeString(buffer, t_offset, tournaments[tournaments_l - 1].name);
						writeInteger(buffer, t_offset, 0, 2);
						zip_len = gzip(buffer, t_offset, zip_message, 1);
						if (zip_len > 1)
						{
							encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
							radarMessageHandler(encode_message, encode_message_len);
							if (jump_buf[jump] != nullptr) delete[] jump_buf[jump];
							jump_buf[jump] = encode_message;
							jump_buf_len[jump] = encode_message_len;
							jump++;
							//delete[] encode_message;
							encode_message = nullptr;

						}
						delete[] zip_message;
						zip_message = nullptr;
						if (DEBUG_OUTPUT == true) printf("new simple tournament  in odds change radarmessagehandler\r\n");


						t_offset = 0;
					}



				}

				if (simples_id[event_id] == nullptr) { std::printf("ERROR!\r\nTournaments simple id not found after succes in getTournament run simple %d\r\n", event_id); continue; }
				_tournament = simples_id[event_id];

				if (_tournament->end_date == 0) {
					if (getTournament(_tournament, false) == -1)  std::printf("ERROR!\r\nTournaments simple id not found in run simple for change end_date %d\r\n", event_id);
					else std::printf("\r\nTournaments simple id change end_date succes%d\r\n", event_id);
				}


				if (_tournament->sport_id >= MAX_SPORTS) { std::printf("ERROR DATA!\r\nstournament sport_id out of MAX_SPORTS in run simple%d\r\n", _tournament->sport_id); continue; }

				if (sports_id[_tournament->sport_id] == nullptr) { std::printf("Sport not found in run simple. Run getSports. sport_id=%d\r\n", _tournament->sport_id); getSports(); }

				if (recovery_state == 0) {
					writeInteger(buffer, offset, 0, 1); //0 sistem request_id
					writeInteger(buffer, offset, 1, 2);
					writeInteger(buffer, offset, type_radar, 1);
					writeInteger(buffer, offset, event_id, 4);
					writeInteger(buffer, offset, _tournament->end_date, 4);
					retry_offset = offset;
					offset += 2;
					event_lines_l = 0;
				}

				if (PRINT == true) {
					std::printf("\r\n***************************************************\r\n");
					std::printf("Simple id: %d\r\n", event_id);
					std::printf("NAME:"); std::printf(_tournament->name);
					std::printf("\r\n");
				}

				//std::sprintf(socket_message_little, "\r\n***************************************************\r\n");
				/*
				std::strcat(socket_message_big, socket_message_little);
				std::sprintf(socket_message_little, "Simple id: %d\r\n", event_id);
				std::strcat(socket_message_big, socket_message_little);
				std::sprintf(socket_message_little, "NAME:");
				std::strcat(socket_message_big, socket_message_little);
				std::sprintf(socket_message_little, "\r\n");
				*/




				if (PRINT == true) {
					std::printf(sports_id[_tournament->sport_id]->name); std::printf("\r\n");
				}
				//std::strcat(socket_message_big, sports_id[_tournament->sport_id]->name);
				//std::strcat(socket_message_big, "\r\n");



				if (_tournament->category_id >= MAX_CATEGORIES) { std::printf("ERROR DATA!\r\ntournament category_id out of MAX_CATEGORIES in run simple %d\r\n", _tournament->category_id); continue; }
				if (categories_id[_tournament->category_id] == nullptr) {
					std::printf("Category not found. Run getTournament(). category_id=%d\r\n", _tournament->category_id);
					if (getTournament(simples_id[_tournament->simple_id], false) == -1);  continue;
				}
				categories_id[_tournament->category_id]->outrights = 1;
				if (PRINT == true) {
					std::printf(categories_id[_tournament->category_id]->name); std::printf("\r\n");
					std::printf("\r\n***************************************************\r\n");
				}
				////std::sprintf(socket_message_little, "\r\n***************************************************\r\n");
				//std::strcat(socket_message_big, categories_id[_tournament->category_id]->name);
				//std::strcat(socket_message_big, "\r\n\r\n***************************************************\r\n");




				xml_node<> * odds = doc.first_node()->first_node("odds");

				if (odds != nullptr) {
					betstop_reason = 0;
					if (odds->first_attribute("betstop_reason")) betstop_reason = atoi(odds->first_attribute("betstop_reason")->value());
					_line->tournament_id = 0;
					_line->event_id = 0;
					_line->season_id = 0;
					_line->simple_id = _tournament->simple_id;
					//_line->betstop_reason = betstop_reason;

					for (xml_node<> * market_node = odds->first_node("market"); market_node; market_node = market_node->next_sibling())
					{
						outcomeNameError = 0;
						if (market_node->first_attribute("next_betstop")) _line->next_betstop = atoi(market_node->first_attribute("next_betstop")->value());
						if (market_node->first_node("market_metadata") && market_node->first_node("market_metadata")->first_attribute("next_betstop")) _line->next_betstop = atoi(market_node->first_node("market_metadata")->first_attribute("next_betstop")->value());
						//printf("_line->next_betstop=%d\r\n", _line->next_betstop);


						if (market_node->first_attribute("favourite")) _line->favourite = atoi(market_node->first_attribute("favourite")->value());
						if (market_node->first_attribute("status")) _line->status = atoi(market_node->first_attribute("status")->value());
						if (market_node->first_attribute("id")) _line->market_id = atoi(market_node->first_attribute("id")->value());
						if (_line->market_id >= MAX_MARKETS) {
							std::printf("ERROR DATA!\r\nmarket id out of MAX_MARKETS in run%d\r\n", _line->market_id); continue;
						}
						if (markets_id[_line->market_id] == nullptr) {
							std::printf("ERROR DATA!\r\nmarket id not found in run%d\r\n", _line->market_id); continue;
						};
						if (markets_id[_line->market_id][0] == nullptr) {
							std::printf("ERROR DATA!\r\nmarket id 0 not found in run%d\r\n", _line->market_id); continue;
						};
						_line->variant = markets_id[_line->market_id][0]->variant;
						_line->type = markets_id[_line->market_id][0]->type;
						if (_line->specifier_number > 0) for (q = 0; q < _line->specifier_number; q++) {
							if (_line->specifier[q] != nullptr) delete[] _line->specifier[q]; _line->specifier[q] = nullptr;
							if (_line->specifier_value[q] != nullptr)  delete[] _line->specifier_value[q]; _line->specifier_value[q] = nullptr;
						}
						if (_line->specifier != nullptr) { delete[] _line->specifier; _line->specifier = nullptr; }
						if (_line->specifier_value != nullptr) { delete[] _line->specifier_value; _line->specifier_value = nullptr; }
						_line->specifier_number = 0;
						if (_line->extended_specifier_number > 0) for (q = 0; q < _line->extended_specifier_number; q++) {
							if (_line->extended_specifier[q] != nullptr) delete[] _line->extended_specifier[q];
							if (_line->extended_specifier_value[q] != nullptr)  delete[] _line->extended_specifier_value[q];
						}
						if (_line->extended_specifier != nullptr) { delete[] _line->extended_specifier; _line->extended_specifier = nullptr; }
						if (_line->extended_specifier_value != nullptr) { delete[] _line->extended_specifier_value; _line->extended_specifier_value = nullptr; }
						_line->extended_specifier_number = 0;
						if (market_node->first_attribute("specifiers")) {
							n = 0;
							m = market_node->first_attribute("specifiers")->value_size();
							for (q = 0; q < m; q++) {
								if (market_node->first_attribute("specifiers")->value()[q] == '=')
									index_equally[n] = q;

								if (market_node->first_attribute("specifiers")->value()[q] == '|') {
									index_separator[n] = q; n++;
								}

							}
							index_separator[n] = q; n++;




							_line->specifier_number = n;
							if (_line->specifier_number > 0) {
								_line->specifier_value = new char*[_line->specifier_number];
								_line->specifier = new char*[_line->specifier_number];


								for (q = 0; q < _line->specifier_number; q++) {
									if (q > 0) {
										_line->specifier[q] = new char[index_equally[q] - index_separator[q - 1]];
										strncpy(_line->specifier[q], (char*)((char*)market_node->first_attribute("specifiers")->value() + index_separator[q - 1]) + 1, index_equally[q] - index_separator[q - 1] - 1);
										_line->specifier[q][index_equally[q] - index_separator[q - 1] - 1] = 0;
									}
									else {
										_line->specifier[q] = new char[index_equally[q] + 1]; strncpy(_line->specifier[q], market_node->first_attribute("specifiers")->value(), index_equally[q]); _line->specifier[q][index_equally[q]] = 0;


									}

									_line->specifier_value[q] = new char[index_separator[q] - index_equally[q]];
									strncpy(_line->specifier_value[q], (char*)((char*)market_node->first_attribute("specifiers")->value() + index_equally[q]) + 1, index_separator[q] - index_equally[q] - 1);
									_line->specifier_value[q][index_separator[q] - index_equally[q] - 1] = 0;



								}
							}
						}
						if (market_node->first_attribute("extended_specifiers")) {
							n = 0;
							m = market_node->first_attribute("extended_specifiers")->value_size();
							for (q = 0; q < m; q++) {
								if (market_node->first_attribute("extended_specifiers")->value()[q] == '=')
									index_equally[n] = q;

								if (market_node->first_attribute("extended_specifiers")->value()[q] == '|') {
									index_separator[n] = q; n++;
								}

							}
							index_separator[n] = q; n++;



							_line->extended_specifier_number = n;
							if (_line->extended_specifier_number > 0) {
								_line->extended_specifier_value = new char*[_line->extended_specifier_number];
								_line->extended_specifier = new char*[_line->extended_specifier_number];


								for (q = 0; q < _line->extended_specifier_number; q++) {
									if (q > 0) {
										_line->extended_specifier[q] = new char[index_equally[q] - index_separator[q - 1]];
										strncpy(_line->extended_specifier[q], (char*)((char*)market_node->first_attribute("extended_specifiers")->value() + index_separator[q - 1]) + 1, index_equally[q] - index_separator[q - 1] - 1);
										_line->extended_specifier[q][index_equally[q] - index_separator[q - 1] - 1] = 0;
									}
									else {
										_line->extended_specifier[q] = new char[index_equally[q] + 1]; strncpy(_line->extended_specifier[q], market_node->first_attribute("extended_specifiers")->value(), index_equally[q]); _line->extended_specifier[q][index_equally[q]] = 0;


									}

									_line->extended_specifier_value[q] = new char[index_separator[q] - index_equally[q]];
									strncpy(_line->extended_specifier_value[q], (char*)((char*)market_node->first_attribute("extended_specifiers")->value() + index_equally[q]) + 1, index_separator[q] - index_equally[q] - 1);
									_line->extended_specifier_value[q][index_separator[q] - index_equally[q] - 1] = 0;
									//printf(_line->extended_specifier[q]);std::printf("\r\n");std::printf(_line->extended_specifier_value[q]);std::printf("\r\n");


								}
							}
						}
					outcomeNameError1:



						if (_line->variant > -1) {
							z = strlen(_line->specifier_value[_line->variant]) + 1; if (strcmp(_line->specifier[_line->variant], "variant") != 0) { std::printf(_line->specifier[_line->variant]); std::printf("\r\n"); }


							for (u = 0; u < max_markets_in[_line->market_id]; u++) if (markets_id[_line->market_id][u] != nullptr && markets_id[_line->market_id][u]->variable_text != nullptr && std::strcmp(_line->specifier_value[_line->variant], markets_id[_line->market_id][u]->variable_text) == 0) break;
							if (outcomeNameError == 1 || u == max_markets_in[_line->market_id]) {
								std::printf("Variant market1 not found in run market_id=%d variant=", _line->market_id);  std::printf(_line->specifier_value[_line->variant]);  std::printf(" getVariantMarket\r\n"); if (getVariantMarket(markets_id[_line->market_id][0], _line->specifier_value[_line->variant]) == -1) { std::printf("variant market not found "); continue; }
								else new_variant = true;
								for (u = 0; u < max_markets_in[_line->market_id]; u++) if (markets_id[_line->market_id][u] != nullptr && markets_id[_line->market_id][u]->variable_text != nullptr && std::strcmp(_line->specifier_value[_line->variant], markets_id[_line->market_id][u]->variable_text) == 0) break;
							}
							_market = markets_id[_line->market_id][u];

							if (new_variant == true && recovery_state == 0 && _market->type < 3) {
								t_offset = 0;
								writeInteger(buffer, t_offset, 0, 1);//sistem request_id 
								writeInteger(buffer, t_offset, 0, 2);// step 1 num of sports = 0;
								writeInteger(buffer, t_offset, 0, 2);// step 1 num of categories = 0;
								writeInteger(buffer, t_offset, 0, 2);// step 1 num of tournaments = 0;
								writeInteger(buffer, t_offset, 1, 2);// step 1 num of markets = 0;

								writeInteger(buffer, t_offset, _market->id, 2);
								writeInteger(buffer, t_offset, _market->type, 1);
								writeInteger(buffer, t_offset, _market->line_type, 1);
								writeString(buffer, t_offset, _market->name);
								writeInteger(buffer, t_offset, _market->variant, 1);
								if (_market->variant>-1) writeString(buffer, t_offset, _market->variable_text);
								//if(_market->variant>-1 && _market->variable_text!=nullptr)
								//writeString(buffer, t_offset, _market->variable_text);
								writeInteger(buffer, t_offset, _market->outcome_number, 2);
								for (j = 0; j < _market->outcome_number; j++) {
									writeInteger(buffer, t_offset, _market->outcome_id[j], 4);
									writeString(buffer, t_offset, _market->outcome_name[j]);
								}

								writeInteger(buffer, t_offset, _market->specifier_number, 1);
								for (j = 0; j < _market->specifier_number; j++) 	writeString(buffer, t_offset, _market->specifier_name[j]);

								zip_len = gzip(buffer, t_offset, zip_message, 1);
								if (zip_len > 1)
								{
									encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
									radarMessageHandler(encode_message, encode_message_len);
									if (jump_buf[jump] != nullptr) delete[] jump_buf[jump];
									jump_buf[jump] = encode_message;
									jump_buf_len[jump] = encode_message_len;
									jump++;
									//delete[] encode_message;
									encode_message = nullptr;

								}
								delete[] zip_message;
								zip_message = nullptr;
								if (DEBUG_OUTPUT == true) printf("new variant market  radarmessagehandler\r\n");


								t_offset = 0;
							}

							if (outcomeNameError == 1)outcomeNameError = 2;

							if (_line->type == 3) z = 16;
						}
						else { _market = markets_id[_line->market_id][0]; if (_line->type == 0) z = 0; else if (_line->type == 1) z = 10; else if (_line->type == 2) z = 14; else if (_line->type == 3) z = 16; }
						outcome_number = 0;


						if (_line->outcome_number > 0) { for (int i = 0; i < _line->outcome_number; i++) if (_line->outcome_name[i] != nullptr) delete[] _line->outcome_name[i]; };
						_line->outcome_number = 0;

						if (_line->outcome_id != nullptr) delete[] _line->outcome_id; if (_line->outcome_active != nullptr) delete[] _line->outcome_active; if (_line->outcome_team != nullptr) delete[] _line->outcome_team; if (_line->outcome_odds != nullptr) delete[] _line->outcome_odds;
						if (_line->outcome_probabilities != nullptr) delete[] _line->outcome_probabilities; if (_line->outcome_name != nullptr) delete[] _line->outcome_name;
						_line->outcome_probabilities = nullptr; _line->outcome_name = nullptr; _line->outcome_id = nullptr; _line->outcome_odds = nullptr; _line->outcome_active = nullptr;
						_line->outcome_team = nullptr;


						if (_line->name != nullptr) delete[] _line->name;


						_line->name = new char[strlen(_market->name) + 1];
						std::strcpy(_line->name, _market->name);
						for (int i = 0; i < _line->specifier_number; i++) {
							if (i == _line->variant) continue;

							replace(_line->name, _line->specifier[i], _line->specifier_value[i]);
						}
						if (simples_id[_line->simple_id]->name != nullptr) replace(_line->name, "$event", simples_id[_line->simple_id]->name);

						for (xml_node<> * outcome_node = market_node->first_node("outcome"); outcome_node; outcome_node = outcome_node->next_sibling()) {


							if (outcome_node->first_attribute("active")) outcome_active[outcome_number] = atoi(outcome_node->first_attribute("active")->value());
							else outcome_active[outcome_number] = 0;
							if (outcome_node->first_attribute("team")) outcome_team[outcome_number] = atoi(outcome_node->first_attribute("team")->value());
							else outcome_team[outcome_number] = 0;
							if (outcome_node->first_attribute("id")) {
								outcome_id[outcome_number] = atoi((char*)((char*)outcome_node->first_attribute("id")->value() + z));
								if (outcome_id[outcome_number] == 0 && z > 0) {
									outcome_id[outcome_number] = atoi(outcome_node->first_attribute("id")->value());
									if (outcome_id[outcome_number] > 0) outcome_team[outcome_number] = 3;
									else {
										std::printf("_line->type=%d line->market_id=%d  _tournament->type_radar=%d  _line->simple_id =%d \r\n", _line->type, _line->market_id, _tournament->type_radar, _line->simple_id); std::printf(outcome_node->first_attribute("id")->value());

									}
								}

							}
							else outcome_id[outcome_number] = 0;


							if (outcome_node->first_attribute("odds")) outcome_odds[outcome_number] = atof(outcome_node->first_attribute("odds")->value());
							else outcome_odds[outcome_number] = 0;
							if (outcome_node->first_attribute("probabilities")) outcome_probabilities[outcome_number] = atof(outcome_node->first_attribute("probabilities")->value());
							else outcome_probabilities[outcome_number] = 0;
							if (outcome_name[outcome_number] != nullptr) delete[] outcome_name[outcome_number]; outcome_name[outcome_number] = nullptr;
							if (outcome_node->first_attribute("name")) {
								outcome_name[outcome_number] = new char[strlen(outcome_node->first_attribute("name")->value()) + 1];
								std::strcpy(outcome_name[outcome_number], outcome_node->first_attribute("name")->value());

							}

							outcome_number++;

						}







						if (PRINT == true) {

							std::printf("\r\n"); std::printf(_line->name); std::printf("\r\n"); std::printf("------------------------------------------------------------------------------\r\n");
						}

						////std::sprintf(socket_message_little, "\r\n***************************************************\r\n");
						//std::strcat(socket_message_big, "\r\n");
						//std::strcat(socket_message_big, _line->name);
						//std::strcat(socket_message_big, "\r\n------------------------------------------------------------------------------\r\n");





						_line->outcome_number = outcome_number;
						if (_line->outcome_number > 0) {
							_line->outcome_name = new char*[_line->outcome_number];
							_line->outcome_id = new int[_line->outcome_number];
							_line->outcome_team = new int[_line->outcome_number];
							_line->outcome_active = new int[_line->outcome_number];
							_line->outcome_probabilities = new float[_line->outcome_number];
							_line->outcome_odds = new float[_line->outcome_number];






							for (int i = 0; i < _line->outcome_number; i++) {
								_line->outcome_name[i] = nullptr;
								_line->outcome_id[i] = outcome_id[i];
								_line->outcome_active[i] = outcome_active[i];
								_line->outcome_odds[i] = outcome_odds[i];
								_line->outcome_team[i] = outcome_team[i];
								_line->outcome_probabilities[i] = outcome_probabilities[i];


								if (_line->type == 0) {
									if (_line->outcome_id[i] == _market->outcome_id[i]) u = i;
									else
										for (u = 0; u < _market->outcome_number; u++) if (_line->outcome_id[i] == _market->outcome_id[u]) break;

									if (u < _market->outcome_number) {
										_line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
										std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);

									}
									else {
										std::printf("Eror. Outcome name not found. market_id=%d _line->outcome_id[i]=%d GoTo GetVarianMarket \r\n", _line->market_id, _line->outcome_id[i]);
										_line->outcome_name[i] = new char[2];
										std::strcpy(_line->outcome_name[i], " ");
										if (_market->variant > -1) printf("_market->variant=%s\r\n", _market->variable_text);
										if (outcomeNameError == 0) outcomeNameError = 1;


									}

									for (int j = 0; j < _line->specifier_number; j++) {
										if (j == _line->variant) continue;

										replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
									}

									if (simples_id[_line->simple_id]->name != nullptr) replace(_line->outcome_name[i], "$event", simples_id[_line->simple_id]->name);



									if (PRINT == true) {

										std::printf(_line->outcome_name[i]); std::printf("\t");
										std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
										std::printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									}
									////std::sprintf(socket_message_little, "\r\n***************************************************\r\n");
									/*
									std::strcat(socket_message_big, _line->outcome_name[i]);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
									std::strcat(socket_message_big, socket_message_little);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									std::strcat(socket_message_big, socket_message_little);*/




								}

								if (_line->type == 1) {
									if (_line->outcome_id[i] >= MAX_PLAYERS) {
										std::printf("ERROR in run. player_id out of MAX_PLAYERS. _line->outcome_id[i]=%d  _line->market_id=%d simple_id=%d\r\n", _line->outcome_id[i], _line->market_id, _line->simple_id);
										continue;

									}
									if (_line->outcome_team[i] != 3) {
										if (players_id[_line->outcome_id[i]] == nullptr) {
											std::printf("Player2 id=%d not found in market id=%d in simple_id=%d  in run function . getPlayer\r\n", _line->outcome_id[i], _line->market_id, _line->simple_id);
											players[players_l].id = _line->outcome_id[i]; if (getPlayer(&players[players_l]) == -1)
											{
												std::printf("error player id=%d  not found \r\n ", _line->outcome_id[i]); //continue;
												_line->outcome_name[i] = new char[2];
												std::strcpy(_line->outcome_name[i], " ");
											}
											else players_l++;
										}

										if (_line->outcome_name[i] == nullptr && players_id[_line->outcome_id[i]]->full_name != nullptr) {
											_line->outcome_name[i] = new char[strlen(players_id[_line->outcome_id[i]]->full_name) + 1];
											std::strcpy(_line->outcome_name[i], players_id[_line->outcome_id[i]]->full_name);
										}
										else if (_line->outcome_name[i] == nullptr && players_id[_line->outcome_id[i]]->name != nullptr) {
											_line->outcome_name[i] = new char[strlen(players_id[_line->outcome_id[i]]->name) + 1];
											std::strcpy(_line->outcome_name[i], players_id[_line->outcome_id[i]]->name);
										}



									}

									if (_line->outcome_team[i] == 3) {

										for (u = 0; u < _market->outcome_number; u++) if (_market->outcome_id[u] == _line->outcome_id[i]) break;
										if (u < _market->outcome_number) {
											_line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
											std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);

											for (int j = 0; j < _line->specifier_number; j++) {
												if (j == _line->variant) continue;
												replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
											}

											if (simples_id[_line->simple_id]->name != nullptr)	replace(_line->outcome_name[i], "$event", simples_id[_line->simple_id]->name);




										}
										else {
											_line->outcome_name[i] = new char[2];
											std::strcpy(_line->outcome_name[i], " ");
										}



									}





									if (PRINT == true) {



										std::printf(_line->outcome_name[i]); std::printf("\t");
										std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
										std::printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									}
									/*
									std::strcat(socket_message_big, _line->outcome_name[i]);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
									std::strcat(socket_message_big, socket_message_little);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									std::strcat(socket_message_big, socket_message_little);*/






								}

								if (_line->type == 2) {
									if (_line->outcome_team[i] != 3) {
										if (_line->outcome_id[i] >= MAX_COMPETITORS) {
											std::printf("ERROR in run. competitor_id out of MAX_COMPETITORS. _line->outcome_id[i]=%d  _line->market_id=%d simple_id=%d\r\n", _line->outcome_id[i], _line->market_id, _tournament->simple_id);
											continue;
										}
										if (competitors_id[_line->outcome_id[i]] == nullptr) {
											std::printf("Competitor id=%d not found in market id=%d in tournament_simple_id=%d  in run simple. getTournament\r\n", _line->outcome_id[i], _line->market_id, _tournament->simple_id);
											if (getTournament(simples_id[_tournament->simple_id], false) == -1)
												std::printf("ERROR!\r\nTournaments not found in run simple %d \r\n", _tournament->simple_id);
										}

										if (competitors_id[_line->outcome_id[i]] == nullptr) {
											std::printf("\r\nCompetitors id=%d not found in tournament simple_id=%d after getTournament . Run getCompetitor\r\n", _line->outcome_id[i], _tournament->simple_id);
											competitors[competitors_l].id = _line->outcome_id[i];
											if (getCompetitor(&competitors[competitors_l]) == -1) {
												std::printf(" Error getCompetitor in run simple. line type= 2 id competitor=%d \r\n", _line->outcome_id[i]);
												_line->outcome_name[i] = new char[2];
												std::strcpy(_line->outcome_name[i], " ");
											}
											else competitors_l++;
										}

										if (competitors_id[_line->outcome_id[i]] != nullptr) { _line->outcome_name[i] = new char[strlen(competitors_id[_line->outcome_id[i]]->name) + 1]; std::strcpy(_line->outcome_name[i], competitors_id[_line->outcome_id[i]]->name); }

									}
									else
									{
										for (u = 0; u < _market->outcome_number; u++) if (_market->outcome_id[u] == _line->outcome_id[i]) break;
										if (u < _market->outcome_number) {
											_line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
											std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);
											for (int j = 0; j < _line->specifier_number; j++) {
												if (j == _line->variant) continue;
												replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
											}

											if (_tournament->name != nullptr) replace(_line->outcome_name[i], "$event", simples_id[_line->simple_id]->name);
										}
										else { _line->outcome_name[i] = new char[2]; std::strcpy(_line->outcome_name[i], " "); }
									}
									if (PRINT == true) {
										std::printf(_line->outcome_name[i]); std::printf("\t");
										std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
										printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									}
									/*
									std::strcat(socket_message_big, _line->outcome_name[i]);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
									std::strcat(socket_message_big, socket_message_little);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									std::strcat(socket_message_big, socket_message_little);*/




								}

								if (_line->type == 3 || _line->type == 4) {

									if (_line->outcome_id[i] == _market->outcome_id[i]) u = i;
									else
										for (u = 0; u < _market->outcome_number; u++) {


											if (_line->outcome_id[i] == _market->outcome_id[u]) break;
										}

									if (u < _market->outcome_number) {

										_line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
										std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);

									}
									else {
										std::printf("Eror. Outcome name not found. market_id=%d _line->outcome_id[i]=%d\r\n", _line->market_id, _line->outcome_id[i]);

										_line->outcome_name[i] = new char[2];
										std::strcpy(_line->outcome_name[i], " ");
										if (outcomeNameError == 0) outcomeNameError = 1;
										if (_market->variant > -1)
											printf("_market->variant=%s\r\n", _market->variable_text);

									}

									for (int j = 0; j < _line->specifier_number; j++) {
										if (j == _line->variant) continue;

										replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
									}

									if (_tournament->name) replace(_line->outcome_name[i], "$event", simples_id[_line->simple_id]->name);


									//if (_line->market_id == 188 || _line->market_id == 224 || _line->market_id == 485 || _line->market_id == 231 || _line->market_id == 65 || _line->market_id == 383 || _line->market_id == 66) 

									if (PRINT == true) {

										std::printf(_line->outcome_name[i]); std::printf("\t");
										std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
										printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									}
									/*
									std::strcat(socket_message_big, _line->outcome_name[i]);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
									std::strcat(socket_message_big, socket_message_little);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									std::strcat(socket_message_big, socket_message_little);*/
								}
							}


							if (outcomeNameError == 1 && _market->variant > -1) goto outcomeNameError1;
						}



						if (DEBUG_OUTPUT == true) printf("insertLine _line->type ==%d\r\n", _line->type);

						auto it = compound2line_index.find(_line->getCompoundKey());
						if (DEBUG_OUTPUT == true) {
							printf(_line ->getCompoundKey().c_str());
							printf("\r\n");
						}
						if (it == compound2line_index.end()) {
							if (DEBUG_OUTPUT == true) printf("new line add");
							_line->id = lines_l;
							if (DEBUG_OUTPUT == true) printf("new line add1");
							lines[lines_l] = (*_line);
							lines_id[_line->id] = &lines[lines_l];
							if (DEBUG_OUTPUT == true) printf("new line add2");
							insert_line(_line, lines_l);
							if (DEBUG_OUTPUT == true) printf("new line add3");
							lines_l++;
							categories_id[_tournament->category_id]->outrights_id.push_back(_line->id);
							if (DEBUG_OUTPUT == true) printf("new line add finish");

						}
						else {
							if (DEBUG_OUTPUT == true) printf("line update");
							_line->id = it->second;
							if (DEBUG_OUTPUT == true) printf("line update1");
							lines[it->second] = (*_line);
							if (DEBUG_OUTPUT == true) printf("line finish");

							//printf("Line Update\r\n");
						}









						if (DEBUG_OUTPUT == true) printf("end insertLine _line->type ==%d\r\n", _line->type);

						if (recovery_state == 0) {

							if (DEBUG_OUTPUT == true) printf("write buffer data\r\n");

							//if (markets_id[_line->market_id][0]->line_type == 0 && events[i].status == 0) continue;
							//if (_line->status == 0 || _line->status == -3) continue;
							event_lines_l++;
							writeInteger(buffer, offset, _line->id, 4);
							//writeInteger(buffer, offset, _line->betstop_reason, 1);
							//writeInteger(buffer, offset, _line->next_betstop, 4);
							writeInteger(buffer, offset, _line->market_id, 2);
							writeInteger(buffer, offset, _line->type, 1);
							writeInteger(buffer, offset, _line->favourite, 1);
							writeInteger(buffer, offset, _line->status, 1);
							//if (_line->outcome_number == 0) printf("_line->outcome_number=0 _line->id=%d  _line->market_id=%d\r\n", _line->id, _line->market_id);
							if (_line->type == 3) writeString(buffer, offset, _line->name);
							writeInteger(buffer, offset, _line->outcome_number, 2);
							for (int j = 0; j < _line->outcome_number; j++) {
								writeInteger(buffer, offset, _line->outcome_id[j], 4);
								writeInteger(buffer, offset, _line->outcome_active[j], 1);
								if (_line->type == 1 || _line->type == 2 || _line->type == 4) writeInteger(buffer, offset, _line->outcome_team[j], 1);
								//if ((_line->type == 1 || _line->type == 2) && _line->outcome_team[j] != 3)
								//if (_line->type == 1 || _line->type == 2 || _line->type == 4)
								if (_line->type > 0) writeString(buffer, offset, _line->outcome_name[j]);
								//writeInteger(buffer, offset, (int)(_line->outcome_odds[j] * 10000), 4);
								writeFloat(buffer, offset, _line->outcome_odds[j]);
								if (PROBABILITIES == 1) writeInteger(buffer, offset, (int)(_line->outcome_probabilities[j] * 100000 + 0.5), 4);
							}

							writeInteger(buffer, offset, _line->specifier_number, 1);
							//for (int j = 0; j < _line->specifier_number; j++) writeString(buffer, offset, _line->specifier_value[j]);
							for (j = 0; j < _line->specifier_number; j++) {
								if (_line->market_id == 215 && j == 2) {
									strcpy(specifier_value, _line->specifier_value[j]); replace_competitor(specifier_value);
									writeString(buffer, offset, specifier_value);
								}
								else 	if (_line->market_id == 882 && j == 0) {
									strcpy(specifier_value, _line->specifier_value[j]); replace_player(specifier_value);
									writeString(buffer, offset, specifier_value);
								}
								else 	writeString(buffer, offset, _line->specifier_value[j]);


							}




							if (DEBUG_OUTPUT == true) printf("end write buffer data\r\n");
						}













					}
				}
				if (recovery_state == 0) writeInteger(buffer, retry_offset, event_lines_l, 2);

			}
			if (type_radar == 3 || type_radar == 4) {
				if (event_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nsseason id out of MAX_TOURNAMENTS in run %d\r\n", event_id); continue; }
				if (type_radar == 3)
					if ((type_radar == 3 && (seasons_id[event_id] == nullptr || seasons_id[event_id]->id == 0)) || (type_radar == 4 && tournaments_id[event_id] == nullptr)) {
						if (type_radar == 3) {
							std::printf("Tournament not found. Run getTournament(). season_id=%d\r\n", event_id);
							tournaments[tournaments_l].id = 0;
							tournaments[tournaments_l].season_id = event_id;
							tournaments[tournaments_l].type_radar = 0;
							tournaments[tournaments_l].simple_id = 0;
						}

						if (type_radar == 4) {
							std::printf("Tournament not found. Run getTournament(). race_tournamnet_id=%d\r\n", event_id);
							tournaments[tournaments_l].id = event_id;
							tournaments[tournaments_l].season_id = 0;
							tournaments[tournaments_l].type_radar = 1;
							tournaments[tournaments_l].simple_id = 0;

						}


						if (getTournament(&tournaments[tournaments_l], false) == -1) { std::printf("ERROR!\r\nTournaments season/race_tournamnet  id not found in run season/race_tournamnet %d typr_radar %d\r\n", event_id, type_radar); continue; }
						else tournaments_l++;
						if (recovery_state == 0) {
							t_offset = 0;
							writeInteger(buffer, t_offset, 0, 1);//sistem request_id 
							writeInteger(buffer, t_offset, 0, 2);
							writeInteger(buffer, t_offset, 0, 2);
							writeInteger(buffer, t_offset, 1, 2);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].type_radar, 1);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].id, 4);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].season_id, 4);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].simple_id, 4);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].sport_id, 2);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].category_id, 2);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].sort, 2);
							writeString(buffer, t_offset, tournaments[tournaments_l - 1].name);
							writeInteger(buffer, t_offset, 0, 2);
							zip_len = gzip(buffer, t_offset, zip_message, 1);
							if (zip_len > 1)
							{
								encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
								radarMessageHandler(encode_message, encode_message_len);
								if (jump_buf[jump] != nullptr) delete[] jump_buf[jump];
								jump_buf[jump] = encode_message;
								jump_buf_len[jump] = encode_message_len;
								jump++;
								//delete[] encode_message;
								encode_message = nullptr;

							}
							delete[] zip_message;
							zip_message = nullptr;
							if (DEBUG_OUTPUT == true) printf("new season tournament  in odds change radarmessagehandler\r\n");


							t_offset = 0;
						}


					}
				if (type_radar == 3) {
					if (seasons_id[event_id] == nullptr) { std::printf("ERROR!\r\nTournaments season id not found after succes in getTournament run season %d\r\n", event_id); continue; }
					_tournament = seasons_id[event_id];
				}
				if (type_radar == 4) _tournament = tournaments_id[event_id];



				if (_tournament->end_date == 0) {
					if (getTournament(_tournament, false) == -1)  std::printf("ERROR!\r\nTournaments simple id not found in run simple for change end_date %d\r\n", event_id);
					else std::printf("\r\nTournaments simple id change end_date succes%d\r\n", event_id);
				}

				if (_tournament->sport_id >= MAX_SPORTS) { std::printf("ERROR DATA!\r\nstournament sport_id out of MAX_SPORTS in run season%d\r\n", _tournament->sport_id); continue; }

				if (sports_id[_tournament->sport_id] == nullptr) { std::printf("Sport not found in run season. Run getSports. sport_id=%d\r\n", _tournament->sport_id); getSports(); }


				if (recovery_state == 0) {
					writeInteger(buffer, offset, 0, 1);//sistem request id
					writeInteger(buffer, offset, 1, 2);
					writeInteger(buffer, offset, type_radar, 1);
					writeInteger(buffer, offset, _tournament->id, 4);
					writeInteger(buffer, offset, _tournament->end_date, 4);
					retry_offset = offset;
					offset += 2;
					event_lines_l = 0;
				}



				if (PRINT == true) {
					std::printf("\r\n***************************************************\r\n");
					std::printf("Season id: %d\r\n", event_id);
					std::printf("Tournament id:%d\r\n", _tournament->id);
					std::printf("NAME:"); std::printf(_tournament->name);
					std::printf("\r\nSEASON:"); if (_tournament->season_name != nullptr) std::printf(_tournament->season_name); else std::printf(_tournament->name);
					std::printf("\r\n");
				}

				//std::strcat(socket_message_big, "\r\n***************************************************\r\n");
				/*
				std::sprintf(socket_message_little, "Season id: %d\r\n", event_id);
				std::strcat(socket_message_big, socket_message_little);
				std::sprintf(socket_message_little, "Tournament id:%d\r\n", _tournament->id);
				std::strcat(socket_message_big, socket_message_little);
				std::strcat(socket_message_big, "NAME:");
				std::strcat(socket_message_big, _tournament->name);
				std::strcat(socket_message_big, "\r\nSEASON:");
				if (_tournament->season_name != nullptr) std::strcat(socket_message_big, _tournament->season_name);
				else std::strcat(socket_message_big, _tournament->name);
				std::strcat(socket_message_big, "\r\n");*/



				if (PRINT == true) {
					std::printf(sports_id[_tournament->sport_id]->name); std::printf("\r\n");
				}
				////std::strcat(socket_message_big, sports_id[_tournament->sport_id]->name);
				////std::strcat(socket_message_big, "\r\n");



				if (_tournament->category_id >= MAX_CATEGORIES) { std::printf("ERROR DATA!\r\ntournament category_id out of MAX_CATEGORIES in run season %d\r\n", _tournament->category_id); continue; }
				if (categories_id[_tournament->category_id] == nullptr) {
					std::printf("Category not found. Run getTournament(). category_id=%d\r\n", _tournament->category_id);
					if (getTournament(tournaments_id[_tournament->id], false) == -1);  continue;

				}
				categories_id[_tournament->category_id]->outrights = 1;
				if (PRINT == true) {
					std::printf(categories_id[_tournament->category_id]->name); std::printf("\r\n");
					std::printf("\r\n***************************************************\r\n");
				}

				////std::sprintf(socket_message_little, "Season id: %d\r\n", event_id);
				//std::strcat(socket_message_big, categories_id[_tournament->category_id]->name);
				//std::strcat(socket_message_big, "\r\n");





				xml_node<> * odds = doc.first_node()->first_node("odds");

				if (odds != nullptr) {
					betstop_reason = 0;

					if (odds->first_attribute("betstop_reason")) betstop_reason = atoi(odds->first_attribute("betstop_reason")->value());
					_line->tournament_id = _tournament->id;
					_line->event_id = 0;
					_line->simple_id = 0;
					if (type_radar == 3) _line->season_id = event_id;
					//_line->betstop_reason = betstop_reason;

					for (xml_node<> * market_node = odds->first_node("market"); market_node; market_node = market_node->next_sibling())
					{
						outcomeNameError = 0;
						if (market_node->first_attribute("next_betstop")) _line->next_betstop = atoi(market_node->first_attribute("next_betstop")->value());
						if (market_node->first_node("market_metadata") && market_node->first_node("market_metadata")->first_attribute("next_betstop")) _line->next_betstop = atoi(market_node->first_node("market_metadata")->first_attribute("next_betstop")->value());
						if (market_node->first_attribute("favourite")) _line->favourite = atoi(market_node->first_attribute("favourite")->value());
						if (market_node->first_attribute("status")) _line->status = atoi(market_node->first_attribute("status")->value());
						if (market_node->first_attribute("id")) _line->market_id = atoi(market_node->first_attribute("id")->value());
						if (_line->market_id >= MAX_MARKETS) {
							std::printf("ERROR DATA!\r\nmarket id out of MAX_MARKETS in run%d\r\n", _line->market_id); continue;
						}
						if (markets_id[_line->market_id] == nullptr) {
							std::printf("ERROR DATA!\r\nmarket id not found in run%d\r\n", _line->market_id); continue;
						};
						if (markets_id[_line->market_id][0] == nullptr) {
							std::printf("ERROR DATA!\r\nmarket id 0 not found in run%d\r\n", _line->market_id); continue;
						};
						_line->variant = markets_id[_line->market_id][0]->variant;
						_line->type = markets_id[_line->market_id][0]->type;

						if (DEBUG_OUTPUT == true) {
							std::printf("_line->type=%d _line->variant=%d\r\n", _line->type, _line->variant);
						}
						if (_line->specifier_number > 0) for (q = 0; q < _line->specifier_number; q++) {
							if (_line->specifier[q] != nullptr) delete[] _line->specifier[q]; _line->specifier[q] = nullptr;;
							if (_line->specifier_value[q] != nullptr)  delete[] _line->specifier_value[q]; _line->specifier_value[q] = nullptr;
						}
						if (_line->specifier != nullptr) { delete[] _line->specifier; _line->specifier = nullptr; }
						if (_line->specifier_value != nullptr) { delete[] _line->specifier_value; _line->specifier_value = nullptr; }
						_line->specifier_number = 0;
						if (_line->extended_specifier_number > 0) for (q = 0; q < _line->extended_specifier_number; q++) {
							if (_line->extended_specifier[q] != nullptr) delete[] _line->extended_specifier[q];
							if (_line->extended_specifier_value[q] != nullptr)  delete[] _line->extended_specifier_value[q];
						}
						if (_line->extended_specifier != nullptr) { delete[] _line->extended_specifier; _line->extended_specifier = nullptr; }
						if (_line->extended_specifier_value != nullptr) { delete[] _line->extended_specifier_value; _line->extended_specifier_value = nullptr; }
						_line->extended_specifier_number = 0;


						if (market_node->first_attribute("specifiers")) {
							n = 0;
							m = market_node->first_attribute("specifiers")->value_size();
							for (q = 0; q < m; q++) {
								if (market_node->first_attribute("specifiers")->value()[q] == '=')
									index_equally[n] = q;

								if (market_node->first_attribute("specifiers")->value()[q] == '|') {
									index_separator[n] = q; n++;
								}

							}
							index_separator[n] = q; n++;




							_line->specifier_number = n;
							if (_line->specifier_number > 0) {
								_line->specifier_value = new char*[_line->specifier_number];
								_line->specifier = new char*[_line->specifier_number];


								for (q = 0; q < _line->specifier_number; q++) {
									if (q > 0) {
										_line->specifier[q] = new char[index_equally[q] - index_separator[q - 1]];
										strncpy(_line->specifier[q], (char*)((char*)market_node->first_attribute("specifiers")->value() + index_separator[q - 1]) + 1, index_equally[q] - index_separator[q - 1] - 1);
										_line->specifier[q][index_equally[q] - index_separator[q - 1] - 1] = 0;

									}
									else {
										_line->specifier[q] = new char[index_equally[q] + 1]; strncpy(_line->specifier[q], market_node->first_attribute("specifiers")->value(), index_equally[q]); _line->specifier[q][index_equally[q]] = 0;


									}


									_line->specifier_value[q] = new char[index_separator[q] - index_equally[q]];
									strncpy(_line->specifier_value[q], (char*)((char*)market_node->first_attribute("specifiers")->value() + index_equally[q]) + 1, index_separator[q] - index_equally[q] - 1);
									_line->specifier_value[q][index_separator[q] - index_equally[q] - 1] = 0;


								}
							}
						}
						if (market_node->first_attribute("extended_specifiers")) {
							n = 0;
							m = market_node->first_attribute("extended_specifiers")->value_size();
							for (q = 0; q < m; q++) {
								if (market_node->first_attribute("extended_specifiers")->value()[q] == '=')
									index_equally[n] = q;

								if (market_node->first_attribute("extended_specifiers")->value()[q] == '|') {
									index_separator[n] = q; n++;
								}

							}
							index_separator[n] = q; n++;

							if (DEBUG_OUTPUT == true) {

							}

							_line->extended_specifier_number = n;
							if (_line->extended_specifier_number > 0) {
								_line->extended_specifier_value = new char*[_line->extended_specifier_number];
								_line->extended_specifier = new char*[_line->extended_specifier_number];


								for (q = 0; q < _line->extended_specifier_number; q++) {
									if (q > 0) {
										_line->extended_specifier[q] = new char[index_equally[q] - index_separator[q - 1]];
										strncpy(_line->extended_specifier[q], (char*)((char*)market_node->first_attribute("extended_specifiers")->value() + index_separator[q - 1]) + 1, index_equally[q] - index_separator[q - 1] - 1);
										_line->extended_specifier[q][index_equally[q] - index_separator[q - 1] - 1] = 0;
									}
									else {
										_line->extended_specifier[q] = new char[index_equally[q] + 1]; strncpy(_line->extended_specifier[q], market_node->first_attribute("extended_specifiers")->value(), index_equally[q]); _line->extended_specifier[q][index_equally[q]] = 0;


									}

									_line->extended_specifier_value[q] = new char[index_separator[q] - index_equally[q]];
									strncpy(_line->extended_specifier_value[q], (char*)((char*)market_node->first_attribute("extended_specifiers")->value() + index_equally[q]) + 1, index_separator[q] - index_equally[q] - 1);
									_line->extended_specifier_value[q][index_separator[q] - index_equally[q] - 1] = 0;
									//printf(_line->extended_specifier[q]);std::printf("\r\n");std::printf(_line->extended_specifier_value[q]);std::printf("\r\n");


								}
							}
						}




					outcomeNameError2:


						if (_line->variant > -1) {
							z = strlen(_line->specifier_value[_line->variant]) + 1; if (strcmp(_line->specifier[_line->variant], "variant") != 0) { std::printf(_line->specifier[_line->variant]); std::printf("\r\n"); }
							for (u = 0; u < max_markets_in[_line->market_id]; u++) if (markets_id[_line->market_id][u] != nullptr && markets_id[_line->market_id][u]->variable_text != nullptr && std::strcmp(_line->specifier_value[_line->variant], markets_id[_line->market_id][u]->variable_text) == 0) break;
							if (outcomeNameError == 1 || u == max_markets_in[_line->market_id]) {
								std::printf("Variant market2 not found in run market_id=%d variant=", _line->market_id);  std::printf(_line->specifier_value[_line->variant]);  std::printf("  getVariantMarket\r\n"); if (getVariantMarket(markets_id[_line->market_id][0], _line->specifier_value[_line->variant]) == -1) { std::printf("variant market not found "); continue; }
								else new_variant = true;
								for (u = 0; u < max_markets_in[_line->market_id]; u++) if (markets_id[_line->market_id][u] != nullptr && markets_id[_line->market_id][u]->variable_text != nullptr && std::strcmp(_line->specifier_value[_line->variant], markets_id[_line->market_id][u]->variable_text) == 0) break;
							}
							_market = markets_id[_line->market_id][u];
							if (new_variant == true && recovery_state == 0 && _market->type < 3) {
								t_offset = 0;
								writeInteger(buffer, t_offset, 0, 1);// sistem request_id
								writeInteger(buffer, t_offset, 0, 2);// step 1 num of sports = 0;
								writeInteger(buffer, t_offset, 0, 2);// step 1 num of categories = 0;
								writeInteger(buffer, t_offset, 0, 2);// step 1 num of tournaments = 0;
								writeInteger(buffer, t_offset, 1, 2);// step 1 num of markets = 0;

								writeInteger(buffer, t_offset, _market->id, 2);
								writeInteger(buffer, t_offset, _market->type, 1);
								writeInteger(buffer, t_offset, _market->line_type, 1);
								writeString(buffer, t_offset, _market->name);
								writeInteger(buffer, t_offset, _market->variant, 1);
								if (_market->variant>-1) writeString(buffer, t_offset, _market->variable_text);
								//if(_market->variant>-1 && _market->variable_text!=nullptr)
								//writeString(buffer, t_offset, _market->variable_text);
								writeInteger(buffer, t_offset, _market->outcome_number, 2);
								for (j = 0; j < _market->outcome_number; j++) {
									writeInteger(buffer, t_offset, _market->outcome_id[j], 4);
									writeString(buffer, t_offset, _market->outcome_name[j]);
								}

								writeInteger(buffer, t_offset, _market->specifier_number, 1);
								for (j = 0; j < _market->specifier_number; j++) 	writeString(buffer, t_offset, _market->specifier_name[j]);

								zip_len = gzip(buffer, t_offset, zip_message, 1);
								if (zip_len > 1)
								{
									encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
									radarMessageHandler(encode_message, encode_message_len);
									if (jump_buf[jump] != nullptr) delete[] jump_buf[jump];
									jump_buf[jump] = encode_message;
									jump_buf_len[jump] = encode_message_len;
									jump++;
									//delete[] encode_message;
									encode_message = nullptr;

								}
								delete[] zip_message;
								zip_message = nullptr;
								if (DEBUG_OUTPUT == true) printf("new variant market  radarmessagehandler\r\n");


								t_offset = 0;
							}

							if (outcomeNameError == 1) outcomeNameError = 2;




							if (_line->type == 3) z = 16;
						}
						else { _market = markets_id[_line->market_id][0]; if (_line->type == 0) z = 0; else if (_line->type == 1) z = 10; else if (_line->type == 2) z = 14; else if (_line->type == 3) z = 16; }
						outcome_number = 0;

						if (_line->outcome_number > 0) { for (int i = 0; i < _line->outcome_number; i++) if (_line->outcome_name[i] != nullptr) delete[] _line->outcome_name[i]; };
						_line->outcome_number = 0;

						if (_line->outcome_id != nullptr) delete[] _line->outcome_id; if (_line->outcome_active != nullptr) delete[] _line->outcome_active; if (_line->outcome_team != nullptr) delete[] _line->outcome_team; if (_line->outcome_odds != nullptr) delete[] _line->outcome_odds;
						if (_line->outcome_probabilities != nullptr) delete[] _line->outcome_probabilities; if (_line->outcome_name != nullptr) delete[] _line->outcome_name;
						_line->outcome_probabilities = nullptr; _line->outcome_name = nullptr; _line->outcome_id = nullptr; _line->outcome_odds = nullptr; _line->outcome_active = nullptr;
						_line->outcome_team = nullptr;


						if (_line->name != nullptr) delete[] _line->name;



						_line->name = new char[strlen(_market->name) + 1];
						std::strcpy(_line->name, _market->name);



						for (int i = 0; i < _line->specifier_number; i++) {
							if (i == _line->variant) continue;
							replace(_line->name, _line->specifier[i], _line->specifier_value[i]);
						}




						if (tournaments_id[_line->tournament_id]->season_name != nullptr) replace(_line->name, "$event", tournaments_id[_line->tournament_id]->season_name); else if (tournaments_id[_line->tournament_id]->name != nullptr) replace(_line->name, "$event", tournaments_id[_line->tournament_id]->name);




						for (xml_node<> * outcome_node = market_node->first_node("outcome"); outcome_node; outcome_node = outcome_node->next_sibling()) {


							if (outcome_node->first_attribute("active")) outcome_active[outcome_number] = atoi(outcome_node->first_attribute("active")->value());
							else outcome_active[outcome_number] = 0;
							if (outcome_node->first_attribute("team")) outcome_team[outcome_number] = atoi(outcome_node->first_attribute("team")->value());
							else outcome_team[outcome_number] = 0;
							if (outcome_node->first_attribute("id")) {
								outcome_id[outcome_number] = atoi((char*)((char*)outcome_node->first_attribute("id")->value() + z));
								if (outcome_id[outcome_number] == 0 && z > 0) {
									outcome_id[outcome_number] = atoi(outcome_node->first_attribute("id")->value());
									if (outcome_id[outcome_number] > 0) outcome_team[outcome_number] = 3;
									else {
										std::printf("_line->type=%d line->market_id=%d  _tournament->type_radar=%d  _line->tournament_id =%d \r\n", _line->type, _line->market_id, _tournament->type_radar, _line->tournament_id); std::printf(outcome_node->first_attribute("id")->value());

									}
								}

							}
							else outcome_id[outcome_number] = 0;


							if (outcome_node->first_attribute("odds")) outcome_odds[outcome_number] = atof(outcome_node->first_attribute("odds")->value());
							else outcome_odds[outcome_number] = 0;
							if (outcome_node->first_attribute("probabilities")) outcome_probabilities[outcome_number] = atof(outcome_node->first_attribute("probabilities")->value());
							else outcome_probabilities[outcome_number] = 0;
							if (outcome_name[outcome_number] != nullptr) delete[] outcome_name[outcome_number]; outcome_name[outcome_number] = nullptr;
							if (outcome_node->first_attribute("name")) {
								outcome_name[outcome_number] = new char[strlen(outcome_node->first_attribute("name")->value()) + 1];
								std::strcpy(outcome_name[outcome_number], outcome_node->first_attribute("name")->value());

							}

							outcome_number++;

						}






						if (PRINT == true) {

							std::printf("\r\n"); std::printf(_line->name); std::printf("\r\n"); std::printf("------------------------------------------------------------------------------\r\n");
						}


						////std::sprintf(socket_message_little, "Season id: %d\r\n", event_id);
						/*
						std::strcat(socket_message_big, "\r\n");
						std::strcat(socket_message_big, _line->name);
						std::strcat(socket_message_big, "\r\n");
						std::strcat(socket_message_big, "------------------------------------------------------------------------------\r\n");
						*/




						_line->outcome_number = outcome_number;
						if (_line->outcome_number > 0) {
							_line->outcome_name = new char*[_line->outcome_number];
							_line->outcome_id = new int[_line->outcome_number];
							_line->outcome_team = new int[_line->outcome_number];
							_line->outcome_active = new int[_line->outcome_number];
							_line->outcome_probabilities = new float[_line->outcome_number];
							_line->outcome_odds = new float[_line->outcome_number];







							for (int i = 0; i < _line->outcome_number; i++) {
								_line->outcome_name[i] = nullptr;
								_line->outcome_id[i] = outcome_id[i];
								_line->outcome_active[i] = outcome_active[i];
								_line->outcome_odds[i] = outcome_odds[i];
								_line->outcome_team[i] = outcome_team[i];
								_line->outcome_probabilities[i] = outcome_probabilities[i];


								if (_line->type == 0) {
									if (_line->outcome_id[i] == _market->outcome_id[i]) u = i;
									else
										for (u = 0; u < _market->outcome_number; u++) if (_line->outcome_id[i] == _market->outcome_id[u]) break;

									if (u < _market->outcome_number) {
										_line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
										std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);

									}
									else {
										std::printf("Eror. Outcome name not found. market_id=%d _line->outcome_id[i]=%d\r\n", _line->market_id, _line->outcome_id[i]);
										_line->outcome_name[i] = new char[2];
										std::strcpy(_line->outcome_name[i], " ");

										if (_market->variant > -1) printf("_market->variant=%s\r\n", _market->variable_text);
										if (outcomeNameError == 0) outcomeNameError = 1;

									}

									for (int j = 0; j < _line->specifier_number; j++) {
										if (j == _line->variant) continue;

										replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
									}
									if (tournaments_id[_line->tournament_id]->season_name != nullptr) replace(_line->outcome_name[i], "$event", tournaments_id[_line->tournament_id]->season_name); else if (tournaments_id[_line->tournament_id]->name != nullptr) replace(_line->outcome_name[i], "$event", tournaments_id[_line->tournament_id]->name);



									if (PRINT == true) {

										std::printf(_line->outcome_name[i]); std::printf("\t");
										std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
										std::printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									}
									/*
									std::strcat(socket_message_big, _line->outcome_name[i]);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
									std::strcat(socket_message_big, socket_message_little);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									std::strcat(socket_message_big, socket_message_little);
									*/





								}

								if (_line->type == 1) {
									if (_line->outcome_id[i] >= MAX_PLAYERS) {
										std::printf("ERROR in run. player_id out of MAX_PLAYERS. _line->outcome_id[i]=%d  _line->market_id=%d tournament_id=%d\r\n", _line->outcome_id[i], _line->market_id, _line->tournament_id);
										continue;

									}
									if (_line->outcome_team[i] != 3) {
										if (players_id[_line->outcome_id[i]] == nullptr) {
											std::printf("Player3 id=%d not found in market id=%d in tournament_id=%d  in run function . getPlayer\r\n", _line->outcome_id[i], _line->market_id, _line->tournament_id);
											players[players_l].id = _line->outcome_id[i]; if (getPlayer(&players[players_l]) == -1)
											{
												std::printf("error player id=%d  not found \r\n ", _line->outcome_id[i]); //continue;
												_line->outcome_name[i] = new char[2];
												std::strcpy(_line->outcome_name[i], " ");
											}
											else players_l++;
										}

										if (_line->outcome_name[i] == nullptr && players_id[_line->outcome_id[i]]->full_name != nullptr) {
											_line->outcome_name[i] = new char[strlen(players_id[_line->outcome_id[i]]->full_name) + 1];
											std::strcpy(_line->outcome_name[i], players_id[_line->outcome_id[i]]->full_name);
										}
										else if (_line->outcome_name[i] == nullptr && players_id[_line->outcome_id[i]]->name != nullptr) {
											_line->outcome_name[i] = new char[strlen(players_id[_line->outcome_id[i]]->name) + 1];
											std::strcpy(_line->outcome_name[i], players_id[_line->outcome_id[i]]->name);
										}

									}

									if (_line->outcome_team[i] == 3) {

										for (u = 0; u < _market->outcome_number; u++) if (_market->outcome_id[u] == _line->outcome_id[i]) break;
										if (u < _market->outcome_number) {
											_line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
											std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);

											for (int j = 0; j < _line->specifier_number; j++) {
												if (j == _line->variant) continue;
												replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
											}

											if (tournaments_id[_line->tournament_id]->season_name != nullptr)	replace(_line->outcome_name[i], "$event", tournaments_id[_line->tournament_id]->season_name); else 	if (tournaments_id[_line->tournament_id]->name != nullptr)	replace(_line->outcome_name[i], "$event", tournaments_id[_line->tournament_id]->name);

										}
										else {
											_line->outcome_name[i] = new char[2];
											std::strcpy(_line->outcome_name[i], " ");
										}



									}





									if (PRINT == true) {



										std::printf(_line->outcome_name[i]); std::printf("\t");
										std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
										printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									}

									/*std::strcat(socket_message_big, _line->outcome_name[i]);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
									std::strcat(socket_message_big, socket_message_little);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									std::strcat(socket_message_big, socket_message_little);

									*/




								}

								if (_line->type == 2) {
									if (_line->outcome_team[i] != 3) {
										if (_line->outcome_id[i] >= MAX_COMPETITORS) {
											std::printf("ERROR in run. competitor_id out of MAX_COMPETITORS. _line->outcome_id[i]=%d  _line->market_id=%d tournament_id=%d\r\n", _line->outcome_id[i], _line->market_id, _tournament->id);
											continue;
										}
										if (competitors_id[_line->outcome_id[i]] == nullptr) {
											std::printf("Competitor id=%d not found in market id=%d in tournament_id=%d  in run season/race_tournament. getTournament\r\n", _line->outcome_id[i], _line->market_id, _tournament->id);
											if (getTournament(tournaments_id[_tournament->id], false) == -1)
												std::printf("ERROR!\r\nTournaments not found in run season/race_tournament %d \r\n", _tournament->id);
										}

										if (competitors_id[_line->outcome_id[i]] == nullptr) {
											std::printf("\r\nCompetitors id=%d not found in tournament id=%d after getTournament . Run getCompetitor\r\n", _line->outcome_id[i], _tournament->id);
											competitors[competitors_l].id = _line->outcome_id[i];
											if (getCompetitor(&competitors[competitors_l]) == -1) {
												std::printf(" Error getCompetitor in run season/race_tournament. line type= 2 id competitor=%d \r\n", _line->outcome_id[i]);
												_line->outcome_name[i] = new char[2];
												std::strcpy(_line->outcome_name[i], " ");
											}
											else competitors_l++;
										}

										if (competitors_id[_line->outcome_id[i]] != nullptr) { _line->outcome_name[i] = new char[strlen(competitors_id[_line->outcome_id[i]]->name) + 1]; std::strcpy(_line->outcome_name[i], competitors_id[_line->outcome_id[i]]->name); }

									}
									else
									{
										for (u = 0; u < _market->outcome_number; u++) if (_market->outcome_id[u] == _line->outcome_id[i]) break;
										if (u < _market->outcome_number) {
											_line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
											std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);
											for (int j = 0; j < _line->specifier_number; j++) {
												if (j == _line->variant) continue;
												replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
											}

											if (_tournament->season_name != nullptr) replace(_line->outcome_name[i], "$event", tournaments_id[_line->tournament_id]->season_name); else if (_tournament->name != nullptr) replace(_line->outcome_name[i], "$event", tournaments_id[_line->tournament_id]->name);
										}
										else { _line->outcome_name[i] = new char[2]; std::strcpy(_line->outcome_name[i], " "); }
									}
									if (PRINT == true) {
										std::printf(_line->outcome_name[i]); std::printf("\t");
										std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
										printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									}

									/*std::strcat(socket_message_big, _line->outcome_name[i]);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
									std::strcat(socket_message_big, socket_message_little);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									std::strcat(socket_message_big, socket_message_little);*/


								}

								if (_line->type == 3 || _line->type == 4) {

									if (_line->outcome_id[i] == _market->outcome_id[i]) u = i;
									else
										for (u = 0; u < _market->outcome_number; u++) {


											if (_line->outcome_id[i] == _market->outcome_id[u]) break;
										}

									if (u < _market->outcome_number) {

										_line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
										std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);

									}
									else {
										std::printf("Eror. Outcome name not found. market_id=%d _line->outcome_id[i]=%d\r\n", _line->market_id, _line->outcome_id[i]);
										_line->outcome_name[i] = new char[2];
										std::strcpy(_line->outcome_name[i], " ");

										if (_market->variant > -1)
											printf("_market->variant=%s\r\n", _market->variable_text);
										if (outcomeNameError == 0) outcomeNameError = 1;

									}

									for (int j = 0; j < _line->specifier_number; j++) {
										if (j == _line->variant) continue;

										replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
									}

									if (_tournament->season_name) replace(_line->outcome_name[i], "$event", tournaments_id[_line->tournament_id]->season_name); else 	if (_tournament->name) replace(_line->outcome_name[i], "$event", tournaments_id[_line->tournament_id]->name);


									//if (_line->market_id == 188 || _line->market_id == 224 || _line->market_id == 485 || _line->market_id == 231 || _line->market_id == 65 || _line->market_id == 383 || _line->market_id == 66) 

									if (PRINT == true) {

										std::printf(_line->outcome_name[i]); std::printf("\t");
										std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
										printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									}
									/*	std::strcat(socket_message_big, _line->outcome_name[i]);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
									std::strcat(socket_message_big, socket_message_little);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									std::strcat(socket_message_big, socket_message_little);

									*/


								}


							}

							if (outcomeNameError == 1 && _market->variant > -1) goto outcomeNameError2;
						}


						if (DEBUG_OUTPUT == true) printf("insertLine _line->type ==%d\r\n", _line->type);
						auto it = compound2line_index.find(_line ->getCompoundKey());
						if (DEBUG_OUTPUT == true) {
							printf(_line ->getCompoundKey().c_str());
							printf("\r\n");
						}
						if (it == compound2line_index.end()) {
							if (DEBUG_OUTPUT == true) printf("new line add");
							_line->id = lines_l;
							if (DEBUG_OUTPUT == true) printf("new line add1");
							lines[lines_l] = (*_line);
							lines_id[_line->id] = &lines[lines_l];
							if (DEBUG_OUTPUT == true) printf("new line add2");
							insert_line(_line, lines_l);
							if (DEBUG_OUTPUT == true) printf("new line add3");
							lines_l++;
							categories_id[_tournament->category_id]->outrights_id.push_back(_line->id);
							if (DEBUG_OUTPUT == true) printf("new line add finish");

						}
						else {
							if (DEBUG_OUTPUT == true) printf("line update");
							_line->id = it->second;
							if (DEBUG_OUTPUT == true) printf("line update1");
							lines[it->second] = (*_line);
							if (DEBUG_OUTPUT == true) printf("line finish");

							//printf("Line Update\r\n");
						}


						if (DEBUG_OUTPUT == true) printf("end insertLine _line->type ==%d\r\n", _line->type);

						if (recovery_state == 0) {

							if (DEBUG_OUTPUT == true) printf("write buffer data\r\n");

							//if (markets_id[_line->market_id][0]->line_type == 0 && events[i].status == 0) continue;
							//if (_line->status == 0 || _line->status == -3) continue;
							event_lines_l++;
							writeInteger(buffer, offset, _line->id, 4);
							//writeInteger(buffer, offset, _line->betstop_reason, 1);
							//writeInteger(buffer, offset, _line->next_betstop, 1);
							writeInteger(buffer, offset, _line->market_id, 2);
							writeInteger(buffer, offset, _line->type, 1);
							writeInteger(buffer, offset, _line->favourite, 1);
							writeInteger(buffer, offset, _line->status, 1);
							//if (_line->outcome_number == 0) printf("_line->outcome_number=0 _line->id=%d  _line->market_id=%d\r\n", _line->id, _line->market_id);
							writeString(buffer, offset, _line->name);
							if (_line->type == 3) writeInteger(buffer, offset, _line->outcome_number, 2);
							for (int j = 0; j < _line->outcome_number; j++) {
								writeInteger(buffer, offset, _line->outcome_id[j], 4);
								writeInteger(buffer, offset, _line->outcome_active[j], 1);
								if (_line->type == 1 || _line->type == 2 || _line->type == 4) writeInteger(buffer, offset, _line->outcome_team[j], 1);
								//if ((_line->type == 1 || _line->type == 2) && _line->outcome_team[j] != 3)
								//if (_line->type == 1 || _line->type == 2 || _line->type == 4) 
								if (_line->type > 0)  writeString(buffer, offset, _line->outcome_name[j]);
								writeFloat(buffer, offset, _line->outcome_odds[j]);
								if (PROBABILITIES == 1) writeInteger(buffer, offset, (int)(_line->outcome_probabilities[j] * 100000 + 0.5), 4);
								//writeInteger(buffer, offset, (int)(_line->outcome_odds[j] * 10000), 4);
							}

							writeInteger(buffer, offset, _line->specifier_number, 1);
							//for (int j = 0; j < _line->specifier_number; j++) writeString(buffer, offset, _line->specifier_value[j]);
							for (j = 0; j < _line->specifier_number; j++) {
								if (_line->market_id == 215 && j == 2) {
									strcpy(specifier_value, _line->specifier_value[j]); replace_competitor(specifier_value);
									writeString(buffer, offset, specifier_value);
								}
								else  if (_line->market_id == 882 && j == 0) {
									strcpy(specifier_value, _line->specifier_value[j]); replace_player(specifier_value);
									writeString(buffer, offset, specifier_value);
								}
								else 	writeString(buffer, offset, _line->specifier_value[j]);


							}


							if (DEBUG_OUTPUT == true) printf("end write buffer data\r\n");

						}






					}
				}
				if (recovery_state == 0) writeInteger(buffer, retry_offset, event_lines_l, 2);
			}
			if (type_radar == 0 || type_radar == 1 || type_radar == 5) {
				  if (events_id.find(key) == events_id.end()) {
					std::printf("Event not found. Run getFixture to get event_id=%d type_radar=%d\r\n", event_id, type_radar);
					events[events_l].id = event_id;
					events[events_l].type_radar = type_radar;
					ret_fixture = getEventFixture(&events[events_l]);
					if (ret_fixture == -1) {
						std::printf("ERROR!\r\n getEventFixture1 error return in run %d .\r\n", event_id); events[events_l].id = 0;
						events[events_l].type_radar = 0; continue;
					}

					if (recovery_state == 0 && ret_fixture == 1) {
						t_offset = 0;
						writeInteger(buffer, t_offset, 0, 1);//sistem request_id
						writeInteger(buffer, t_offset, 0, 2);
						writeInteger(buffer, t_offset, 0, 2);
						writeInteger(buffer, t_offset, 1, 2);
						writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].type_radar, 1);
						writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].id, 4);
						writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].season_id, 4);
						writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].simple_id, 4);
						writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].sport_id, 2);
						writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].category_id, 2);
						writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].sort, 2);
						writeString(buffer, t_offset, tournaments[tournaments_l - 1].name);
						writeInteger(buffer, t_offset, 0, 2);
						zip_len = gzip(buffer, t_offset, zip_message, 1);
						if (zip_len > 1)
						{
							encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
							radarMessageHandler(encode_message, encode_message_len);
							if (jump_buf[jump] != nullptr) delete[] jump_buf[jump];
							jump_buf[jump] = encode_message;
							jump_buf_len[jump] = encode_message_len;
							jump++;
							//delete[] encode_message;
							encode_message = nullptr;

						}
						delete[] zip_message;
						zip_message = nullptr;
						if (DEBUG_OUTPUT == true) printf("new simple tournament  in fixture change radarmessagehandler\r\n");


						t_offset = 0;
					}
					events_l++;
					
				}
				
				  _event = events_id[key];

				if (DEBUG_OUTPUT == true) std::printf("event from hash _event->id=%d\r\n" , _event->id);

				if (_event->show == 0) {
					events_show[events_show_l] = _event; events_show_l++;
				}
				_event->show = 1;

				if (DEBUG_OUTPUT == true) std::printf("event from hash _event->tournament_id=%d\r\n", _event->tournament_id);
                
				//_event->bet_stop = 0;

				//if (DEBUG_OUTPUT == true) std::printf("odds_change _line->event_key=%s\r\n", _line->event_key);

				if (PRINT == true) {
					std::printf("\r\n***************************************************\r\n");
					std::printf("%d\r\n", _event->id);
					std::printf(_event->home_name); if (_event->away_name != nullptr) { std::printf(" - ");  std::printf(_event->away_name); }
					std::printf("\r\n");
				}

				//std::strcat(socket_message_big, "\r\n***************************************************\r\n");
				//std::sprintf(socket_message_little, "%d\r\n", _event->id);
				//std::strcat(socket_message_big, socket_message_little);
				//std::strcat(socket_message_big, _event->home_name);
				//if (_event->away_name != nullptr) {std::strcat(socket_message_big, " - ");  std::strcat(socket_message_big, _event->away_name);}

				if (_event->sport_id >= MAX_SPORTS) { std::printf("ERROR DATA!\r\nsevent sport_id out of MAX_SPORTS in run %d\r\n", _event->sport_id); continue; }
				if (sports_id[_event->sport_id] == nullptr) { std::printf("Sport not found. Run getSports. sport_id=%d\r\n", _event->sport_id); getSports(); }
				if (PRINT == true) {
					std::printf(sports_id[_event->sport_id]->name); std::printf("\r\n");
				}
				//	std::strcat(socket_message_big, sports_id[_event->sport_id]->name);
				//	std::strcat(socket_message_big, "\r\n");

				if (_event->type_radar < 2 && _event->tournament_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nsevent tournament_id out of MAX_TOURNAMENTS in run %d\r\n", _event->tournament_id); continue; }
				if (_event->type_radar == 2 && _event->simple_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nsevent tournament_id out of MAX_TOURNAMENTS in run %d\r\n", _event->simple_id); continue; }
				if (_event->type_radar == 0 && tournaments_id[_event->tournament_id] == nullptr) {
					std::printf("Tournament not found. Run getTournament(). tournament_id=%d\r\n", _event->tournament_id);
					tournaments[tournaments_l].id = _event->tournament_id;
					tournaments[tournaments_l].type_radar = _event->type_radar;
					if (getTournament(&tournaments[tournaments_l], true) == -1) { std::printf("ERROR!\r\nTournaments not found in run %d . Run getEventFixture\r\n", _event->tournament_id); if (getEventFixture(_event) == -1) { std::printf("ERROR!\r\n getEventFixture2 error return in run %d .\r\n", _event->id); continue; } }
					else {
						tournaments_l++;

						if (recovery_state == 0) {
							t_offset = 0;
							writeInteger(buffer, t_offset, 0, 1);//sistem request_id 
							writeInteger(buffer, t_offset, 0, 2);
							writeInteger(buffer, t_offset, 0, 2);
							writeInteger(buffer, t_offset, 1, 2);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].type_radar, 1);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].id, 4);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].season_id, 4);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].simple_id, 4);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].sport_id, 2);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].category_id, 2);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].sort, 2);
							writeString(buffer, t_offset, tournaments[tournaments_l - 1].name);
							writeInteger(buffer, t_offset, 0, 2);
							zip_len = gzip(buffer, t_offset, zip_message, 1);
							if (zip_len > 1)
							{
								encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
								radarMessageHandler(encode_message, encode_message_len);
								if (jump_buf[jump] != nullptr) delete[] jump_buf[jump];
								jump_buf[jump] = encode_message;
								jump_buf_len[jump] = encode_message_len;
								jump++;
								//delete[] encode_message;
								encode_message = nullptr;

							}
							delete[] zip_message;
							zip_message = nullptr;
							if (DEBUG_OUTPUT == true) printf("new tournament  radarmessagehandler\r\n");


							t_offset = 0;
						}


					}


				}
				if (_event->type_radar == 2 && simples_id[_event->simple_id] == nullptr) {
					std::printf("Simple Tournament not found. Run getTournament(). simples_id=%d _event_id=%d\r\n ", _event->simple_id, _event->id);
					tournaments[tournaments_l].simple_id = _event->simple_id;
					tournaments[tournaments_l].id = 0;
					tournaments[tournaments_l].type_radar = _event->type_radar;
					if (getTournament(&tournaments[tournaments_l], true) == -1) { std::printf("ERROR!\r\nSimple Tournaments not found in run %d . Run getEventFixture\r\n", _event->tournament_id); if (getEventFixture(_event) == -1) { std::printf("ERROR!\r\n getEventFixture3 error return in run %d .\r\n", _event->id); continue; } }
					else {
						tournaments_l++;

						if (recovery_state == 0) {
							t_offset = 0;
							writeInteger(buffer, t_offset, 0, 1);//sistem request_id
							writeInteger(buffer, t_offset, 0, 2);
							writeInteger(buffer, t_offset, 0, 2);
							writeInteger(buffer, t_offset, 1, 2);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].type_radar, 1);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].id, 4);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].season_id, 4);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].simple_id, 4);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].sport_id, 2);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].category_id, 2);
							writeInteger(buffer, t_offset, tournaments[tournaments_l - 1].sort, 2);
							writeString(buffer, t_offset, tournaments[tournaments_l - 1].name);
							writeInteger(buffer, t_offset, 0, 2);
							zip_len = gzip(buffer, t_offset, zip_message, 1);
							if (zip_len > 1)
							{
								encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
								radarMessageHandler(encode_message, encode_message_len);
								if (jump_buf[jump] != nullptr) delete[] jump_buf[jump];
								jump_buf[jump] = encode_message;
								jump_buf_len[jump] = encode_message_len;
								jump++;
								//delete[] encode_message;
								encode_message = nullptr;

							}
							delete[] zip_message;
							zip_message = nullptr;
							if (DEBUG_OUTPUT == true) printf("new simple tournament  in odds change event simple radarmessagehandler\r\n");


							t_offset = 0;
						}


					}


				}


				if (PRINT == true) {
					if (_event->type_radar == 0) std::printf(tournaments_id[_event->tournament_id]->name);
					if (_event->type_radar == 2) std::printf(simples_id[_event->simple_id]->name);
					std::printf("\r\n");
				}

				//if (_event->type_radar == 0) std::strcat(socket_message_big, tournaments_id[_event->tournament_id]->name);
				//if (_event->type_radar == 2) std::strcat(socket_message_big, simples_id[_event->simple_id]->name);
				//std::strcat(socket_message_big, "\r\n");







				if (_event->category_id >= MAX_CATEGORIES) { std::printf("ERROR DATA!\r\nsevent category_id out of MAX_CATEGORIES in run %d\r\n", _event->category_id); continue; }
				if (categories_id[_event->category_id] == nullptr) {
					std::printf("Category not found. Run getTournament(). category_id=%d\r\n", _event->category_id);
					if (_event->type_radar == 0) {
						if (getTournament(tournaments_id[_event->tournament_id], false) == -1) if (getEventFixture(_event) == -1) continue;;
					}
					if (_event->type_radar == 2) {
						if (getTournament(simples_id[_event->simple_id], false) == -1) if (getEventFixture(_event) == -1) continue;;
					}


				}
				if (PRINT == true) {
					std::printf(categories_id[_event->category_id]->name); std::printf("\r\n");
					std::printf("\r\n***************************************************\r\n");
				}
				//std::strcat(socket_message_big, categories_id[_event->category_id]->name);
				//std::strcat(socket_message_big, "\r\n\r\n***************************************************\r\n");




				if (doc.first_node()->first_attribute("timestamp")) _event->timestamp = atoi(doc.first_node()->first_attribute("timestamp")->value());

				xml_node<> * sport_event_status = doc.first_node()->first_node("sport_event_status");
				if (sport_event_status != nullptr) {

					xml_node<> * statistics = sport_event_status->first_node("statistics");

					if (statistics != nullptr) {

						if (statistics->first_node("yellow_cards")) {
							_event->home_yellowcards = atoi(statistics->first_node("yellow_cards")->first_attribute("home")->value());
							_event->away_yellowcards = atoi(statistics->first_node("yellow_cards")->first_attribute("away")->value());
						}

						if (statistics->first_node("red_cards")) {
							_event->home_redcards = atoi(statistics->first_node("red_cards")->first_attribute("home")->value());
							_event->away_redcards = atoi(statistics->first_node("red_cards")->first_attribute("away")->value());
						}
						if (statistics->first_node("yellow_red_cards")) {
							_event->home_yellow_red_cards = atoi(statistics->first_node("yellow_red_cards")->first_attribute("home")->value());
							_event->away_yellow_red_cards = atoi(statistics->first_node("yellow_red_cards")->first_attribute("away")->value());
						}

						if (statistics->first_node("corners")) {
							_event->home_corners = atoi(statistics->first_node("corners")->first_attribute("home")->value());
							_event->away_corners = atoi(statistics->first_node("corners")->first_attribute("away")->value());
						}

					}


					if (sport_event_status->first_attribute("status")) _event->status = atoi(sport_event_status->first_attribute("status")->value());
					if (sport_event_status->first_attribute("possession")) _event->possession = atoi(sport_event_status->first_attribute("possession")->value());
					if (sport_event_status->first_attribute("try")) _event->try_num = atoi(sport_event_status->first_attribute("try")->value());
					if (sport_event_status->first_attribute("throw")) _event->throw_num = atoi(sport_event_status->first_attribute("throw")->value());
					if (sport_event_status->first_attribute("delivery")) _event->delivery = atoi(sport_event_status->first_attribute("delivery")->value());
					if (sport_event_status->first_attribute("current_ct_team")) _event->delivery = atoi(sport_event_status->first_attribute("current_ct_team")->value());
					if (sport_event_status->first_attribute("yards")) _event->yards = atoi(sport_event_status->first_attribute("yards")->value());
					if (sport_event_status->first_attribute("innings")) _event->innings = atoi(sport_event_status->first_attribute("innings")->value());
					if (sport_event_status->first_attribute("over")) _event->over = atoi(sport_event_status->first_attribute("over")->value());
					if (sport_event_status->first_attribute("current_end")) _event->current_end = atoi(sport_event_status->first_attribute("current_end")->value());
					if (sport_event_status->first_attribute("position")) _event->position = atoi(sport_event_status->first_attribute("position")->value());
					if (sport_event_status->first_attribute("away_yellowcards"))
						_event->away_yellowcards = atoi(sport_event_status->first_attribute("away_yellowcards")->value());
					if (sport_event_status->first_attribute("home_yellowcards")) _event->home_yellowcards = atoi(sport_event_status->first_attribute("home_yellowcards")->value());
					if (sport_event_status->first_attribute("away_yellow_cards"))
						_event->away_yellowcards = atoi(sport_event_status->first_attribute("away_yellow_cards")->value());
					if (sport_event_status->first_attribute("home_yellow_cards"))
						_event->home_yellowcards = atoi(sport_event_status->first_attribute("home_yellow_cards")->value());
					if (sport_event_status->first_attribute("away_redcards")) _event->away_redcards = atoi(sport_event_status->first_attribute("away_redcards")->value());
					if (sport_event_status->first_attribute("home_redcards")) _event->home_redcards = atoi(sport_event_status->first_attribute("home_redcards")->value());
					if (sport_event_status->first_attribute("away_dismissals")) _event->away_dismissals = atoi(sport_event_status->first_attribute("away_dismissals")->value());
					if (sport_event_status->first_attribute("home_dismissals")) _event->home_dismissals = atoi(sport_event_status->first_attribute("home_dismissals")->value());
					if (sport_event_status->first_attribute("away_penalty_runs")) _event->away_penalty_runs = atoi(sport_event_status->first_attribute("away_penalty_runs")->value());
					if (sport_event_status->first_attribute("home_penalty_runs")) _event->home_penalty_runs = atoi(sport_event_status->first_attribute("home_penalty_runs")->value());
					if (sport_event_status->first_attribute("away_score")) _event->away_score = atof(sport_event_status->first_attribute("away_score")->value());
					if (sport_event_status->first_attribute("home_score")) _event->home_score = atof(sport_event_status->first_attribute("home_score")->value());
					if (sport_event_status->first_attribute("away_gamescore")) _event->away_gamescore = atoi(sport_event_status->first_attribute("away_gamescore")->value());
					if (sport_event_status->first_attribute("home_gamescore")) _event->home_gamescore = atoi(sport_event_status->first_attribute("home_gamescore")->value());
					if (sport_event_status->first_attribute("away_legscore")) _event->away_legscore = atoi(sport_event_status->first_attribute("away_legscore")->value());
					if (sport_event_status->first_attribute("home_legscore")) _event->home_legscore = atoi(sport_event_status->first_attribute("home_legscore")->value());
					if (sport_event_status->first_attribute("visit")) _event->visit = atoi(sport_event_status->first_attribute("visit")->value());
					if (sport_event_status->first_attribute("reporting")) _event->reporting = atoi(sport_event_status->first_attribute("reporting")->value());
					if (sport_event_status->first_attribute("remaining_reds")) _event->remaining_reds = atoi(sport_event_status->first_attribute("remaining_reds")->value());
					if (sport_event_status->first_attribute("match_status")) _event->match_status = atoi(sport_event_status->first_attribute("match_status")->value());
					if (sport_event_status->first_attribute("home_suspend")) _event->home_suspend = atoi(sport_event_status->first_attribute("home_suspend")->value());
					if (sport_event_status->first_attribute("away_suspend")) _event->away_suspend = atoi(sport_event_status->first_attribute("away_suspend")->value());
					if (sport_event_status->first_attribute("current_server")) _event->current_server = atoi(sport_event_status->first_attribute("current_server")->value());
					if (sport_event_status->first_attribute("winner_id")) _event->winner_id = atoi(sport_event_status->first_attribute("winner_id")->value());
					if (sport_event_status->first_attribute("home_batter")) _event->home_batter = atoi(sport_event_status->first_attribute("home_batter")->value());
					if (sport_event_status->first_attribute("away_batter")) _event->away_batter = atoi(sport_event_status->first_attribute("away_batter")->value());
					if (sport_event_status->first_attribute("away_remaining_bowls")) _event->away_remaining_bowls = atoi(sport_event_status->first_attribute("away_remaining_bowls")->value());
					if (sport_event_status->first_attribute("home_remaining_bowls")) _event->home_remaining_bowls = atoi(sport_event_status->first_attribute("home_remaining_bowls")->value());
					if (sport_event_status->first_attribute("outs")) _event->outs = atoi(sport_event_status->first_attribute("outs")->value());
					if (sport_event_status->first_attribute("strikes")) _event->strikes = atoi(sport_event_status->first_attribute("strikes")->value());
					if (sport_event_status->first_attribute("balls")) _event->balls = atoi(sport_event_status->first_attribute("balls")->value());
					if (sport_event_status->first_attribute("bases")) {
						if (_event->bases != nullptr) { delete[] _event->bases; _event->bases = nullptr; }
						_event->bases = new char[strlen(sport_event_status->first_attribute("bases")->value()) + 1];
						std::strcpy(_event->bases, sport_event_status->first_attribute("bases")->value());

					}




					if (sport_event_status->first_attribute("tiebreak") && sport_event_status->first_attribute("tiebreak")->value()[0] == 't' && sport_event_status->first_attribute("tiebreak")->value()[1] == 'r')  _event->tiebreak = 1;
					if (sport_event_status->first_attribute("tiebreak") && sport_event_status->first_attribute("tiebreak")->value()[0] == 'f' && sport_event_status->first_attribute("tiebreak")->value()[1] == 'a')  _event->tiebreak = 0;

					if (sport_event_status->first_attribute("expedite_mode") && sport_event_status->first_attribute("expedite_mode")->value()[0] == 't' && sport_event_status->first_attribute("expedite_mode")->value()[1] == 'r')  _event->expedite_mode = 1;
					if (sport_event_status->first_attribute("expedite_mode") && sport_event_status->first_attribute("expedite_mode")->value()[0] == 'f' && sport_event_status->first_attribute("expedite_mode")->value()[1] == 'a')  _event->expedite_mode = 0;




					xml_node<> * period_scores = sport_event_status->first_node("period_scores");

					j = 0;
					if (period_scores != nullptr) {


						for (xml_node<> * period_score = period_scores->first_node("period_score"); period_score; period_score = period_score->next_sibling())
						{
							if (j == 0)std::strcpy(set_scores, period_score->first_attribute("home_score")->value());
							if (j > 0) {
								std::strcat(set_scores, "-");
								std::strcat(set_scores, period_score->first_attribute("home_score")->value());
							}
							std::strcat(set_scores, ":");
							std::strcat(set_scores, period_score->first_attribute("away_score")->value());
							j++;
						}

						//printf(set_scores);
						//printf("\r\n");
						if (_event->set_scores != nullptr) { delete[] _event->set_scores; _event->set_scores = nullptr; }
						_event->set_scores = new char[strlen(set_scores) + 1];std::strcpy(_event->set_scores, set_scores);
					}




					xml_node<> * clock = sport_event_status->first_node("clock");
					if (clock != nullptr) {

						if (clock->first_attribute("stopped") && clock->first_attribute("stopped")->value()[0] == 't' && clock->first_attribute("stopped")->value()[1] == 'r')  _event->stopped = 1;

						if (clock->first_attribute("stopped") && clock->first_attribute("stopped")->value()[0] == 'f' && clock->first_attribute("stopped")->value()[1] == 'a')  _event->stopped = 0;

						if (clock->first_attribute("remaining_time_in_period")) {
							if (_event->remaining_time_in_period != nullptr) delete[] _event->remaining_time_in_period;
							_event->remaining_time_in_period = new char[strlen(clock->first_attribute("remaining_time_in_period")->value()) + 1];
							std::strcpy(_event->remaining_time_in_period, clock->first_attribute("remaining_time_in_period")->value());
						}
						else {
							if (_event->remaining_time_in_period != nullptr) {
								delete[] _event->remaining_time_in_period; _event->remaining_time_in_period = nullptr;
							}
							//_event->remaining_time_in_period = new char[1]; _event->remaining_time_in_period[0] = 0;


						}

						if (clock->first_attribute("stoppage_time")) {
							if (_event->stoppage_time != nullptr) delete[] _event->stoppage_time;
							_event->stoppage_time = new char[strlen(clock->first_attribute("stoppage_time")->value()) + 1];
							std::strcpy(_event->stoppage_time, clock->first_attribute("stoppage_time")->value());
						}
						else {

							if (_event->stoppage_time != nullptr) {
								delete[] _event->stoppage_time; _event->stoppage_time = nullptr;
							}
							//_event->stoppage_time = new char[1]; _event->stoppage_time[0] = 0;

						}


						if (clock->first_attribute("stoppage_time_announced")) {
							if (_event->stoppage_time_announced != nullptr) delete[] _event->stoppage_time_announced;
							_event->stoppage_time_announced = new char[strlen(clock->first_attribute("stoppage_time_announced")->value()) + 1];
							std::strcpy(_event->stoppage_time_announced, clock->first_attribute("stoppage_time_announced")->value());
						}
						else {
							if (_event->stoppage_time_announced != nullptr) {
								delete[] _event->stoppage_time_announced; _event->stoppage_time_announced = nullptr;
							}
							//_event->stoppage_time_announced = new char[1]; _event->stoppage_time_announced[0] = 0;
						}


						if (clock->first_attribute("remaining_time")) {
							if (_event->remaining_time != nullptr) delete[] _event->remaining_time;
							_event->remaining_time = new char[strlen(clock->first_attribute("remaining_time")->value()) + 1];
							std::strcpy(_event->remaining_time, clock->first_attribute("remaining_time")->value());
						}
						else {
							if (_event->remaining_time != nullptr) { delete[] _event->remaining_time; _event->remaining_time = nullptr; }
							//_event->remaining_time = new char[1]; _event->remaining_time[0] = 0;

						}


						if (clock->first_attribute("match_time")) {
							if (_event->match_time != nullptr) delete[] _event->match_time;
							_event->match_time = new char[strlen(clock->first_attribute("match_time")->value()) + 1];
							std::strcpy(_event->match_time, clock->first_attribute("match_time")->value());
						}
						else {

							if (_event->match_time != nullptr) {
								delete[] _event->match_time; _event->match_time = nullptr;
							}
							//_event->match_time = new char[1]; _event->match_time[0] = 0;			

						}


					}


				}

				//	if (_event->status > 0) PRINT= true; else PRINT= false;

				if (PRINT == true) {
					if (_event->set_scores != nullptr) { std::printf("set_scores="); std::printf(_event->set_scores); }
					if (_event->match_time != nullptr) { std::printf("match_time="); std::printf(_event->match_time); std::printf(" "); }
					if (_event->remaining_time != nullptr) { std::printf("remaining_time="); std::printf(_event->remaining_time); std::printf(" "); }
					if (_event->remaining_time_in_period != nullptr) { std::printf("remaining_time_in_period="); std::printf(_event->remaining_time_in_period); std::printf(" "); }
					if (_event->bases != nullptr) { std::printf("bases="); std::printf(_event->bases); std::printf(" "); }


					std::printf("stopped=%d ", _event->stopped);
					std::printf("period_length=%d ", _event->period_length);
					std::printf("numbers of set=%d ", _event->bo);
					std::printf("status=%d ", _event->status); std::printf("possession=%d ", _event->possession); std::printf("home_score=%g ", _event->away_score);
					std::printf("away_score=%g ", _event->away_score); std::printf("home_yellowcards=%d ", _event->home_yellowcards); std::printf("away_yellowcards=%d ", _event->away_yellowcards); std::printf("home_redcards=%d ", _event->home_redcards); std::printf("away_redcards=%d ", _event->away_redcards); std::printf("expedite_mode=%d ", _event->expedite_mode); std::printf("tiebreak=%d ", _event->tiebreak); std::printf("outs=%d ", _event->outs); std::printf("strikes=%d ", _event->strikes); std::printf("balls=%d ", _event->balls);  std::printf("home_remaining_bowls=%d ", _event->home_remaining_bowls);
					std::printf("away_remaining_bowls=%d ", _event->away_remaining_bowls); std::printf("home_batter=%d ", _event->home_batter); std::printf("away_batter=%d ", _event->away_batter); std::printf("winner_id=%d ", _event->winner_id); std::printf("home_suspend=%d ", _event->home_suspend); std::printf("away_suspend=%d ", _event->away_suspend); std::printf("match_status=%d ", _event->match_status); std::printf("remaining_reds=%d ", _event->remaining_reds); std::printf("reporting=%d ", _event->reporting); std::printf("position=%d ", _event->position); std::printf("home_gamescore=%d ", _event->home_gamescore); std::printf("away_gamescore=%d ", _event->away_gamescore); std::printf("visit=%d ", _event->visit); std::printf("home_dismissals=%d ", _event->home_dismissals); std::printf("away_dismissals=%d ", _event->away_dismissals); std::printf("home_penalty_runs=%d ", _event->home_penalty_runs);	std::printf("away_penalty_runs=%d ", _event->away_penalty_runs);
					std::printf("over=%d ", _event->over); std::printf("try_num=%d ", _event->try_num); std::printf("trow_num=%d ", _event->throw_num);
					std::printf("delivery=%d ", _event->delivery); std::printf("yards=%d ", _event->yards); std::printf("current_server=%d ", _event->current_server);
					std::printf("innings=%d ", _event->innings);
					std::printf("\r\n\r\n");
				}

				xml_node<> * odds = doc.first_node()->first_node("odds");


				if (recovery_state == 0) {
					offset = 0;
					writeInteger(buffer, offset, 0, 1);
					writeInteger(buffer, offset, 1, 2);
					writeInteger(buffer, offset, type_radar, 1);
					writeInteger(buffer, offset, _event->id, 4);
					writeInteger(buffer, offset, _event->home_id, 4);
					writeInteger(buffer, offset, _event->away_id, 4);

					writeInteger(buffer, offset, _event->type_radar, 1);
					writeInteger(buffer, offset, _event->status, 1);
					writeInteger(buffer, offset, _event->sport_id, 2);
					writeInteger(buffer, offset, _event->category_id, 2);
					if (_event->type_radar<2) writeInteger(buffer, offset, _event->tournament_id, 4);
					else writeInteger(buffer, offset, _event->simple_id, 4);
					writeInteger(buffer, offset, _event->start_time, 4);
					writeInteger(buffer, offset, _event->period_length, 1);
					writeInteger(buffer, offset, _event->overtime_length, 1);
					if (_event->sport_id == 5) writeInteger(buffer, offset, _event->bo, 1);
					writeString(buffer, offset, _event->home_name);
					writeString(buffer, offset, _event->away_name);
					writeString(buffer, offset, _event->tv_channels);
					if (_event->status == 0)  writeInteger(buffer, offset, _event->booked, 1);
					if (_event->status > 0) {

						writeInteger(buffer, offset, (int)(_event->home_score * 100), 2);
						writeInteger(buffer, offset, (int)(_event->away_score * 100), 2);
						writeString(buffer, offset, _event->set_scores);
						writeString(buffer, offset, _event->match_time);
						writeString(buffer, offset, _event->remaining_time);
						writeString(buffer, offset, _event->remaining_time_in_period);
						writeString(buffer, offset, matchstatus_id[_event->match_status]->description);
						writeInteger(buffer, offset, _event->stopped, 1);
						//writeInteger(buffer, offset, _event->stopped, 1); 
						if (_event->sport_id == 1) {
							writeInteger(buffer, offset, _event->home_redcards, 1);
							writeInteger(buffer, offset, _event->home_yellowcards, 1);
							writeInteger(buffer, offset, _event->away_redcards, 1);
							writeInteger(buffer, offset, _event->away_yellowcards, 1);
							writeString(buffer, offset, _event->stoppage_time);
							writeString(buffer, offset, _event->stoppage_time_announced);
							writeInteger(buffer, offset, _event->home_corners, 1);
							writeInteger(buffer, offset, _event->away_corners, 1);
							writeInteger(buffer, offset, _event->home_yellow_red_cards, 1);
							writeInteger(buffer, offset, _event->away_yellow_red_cards, 1);
						}

						if (_event->sport_id == 5) {
							writeInteger(buffer, offset, _event->home_gamescore, 1);
							writeInteger(buffer, offset, _event->away_gamescore, 1);
							writeInteger(buffer, offset, _event->tiebreak, 1);
						}

						if (_event->sport_id == 20) writeInteger(buffer, offset, _event->expedite_mode, 1);


						if (_event->sport_id == 4 || _event->sport_id == 6 || _event->sport_id == 29) {
							writeInteger(buffer, offset, _event->home_suspend, 1); writeInteger(buffer, offset, _event->away_suspend, 1);
						}


						if (_event->sport_id == 5 || _event->sport_id == 20 || _event->sport_id == 34 || _event->sport_id == 19 || _event->sport_id == 23 || _event->sport_id == 22 || _event->sport_id == 31)
							writeInteger(buffer, offset, _event->current_server, 1);


						if (_event->sport_id == 3) {
							writeInteger(buffer, offset, _event->home_batter, 1);
							writeInteger(buffer, offset, _event->away_batter, 1);
							writeInteger(buffer, offset, _event->outs, 1);
							writeInteger(buffer, offset, _event->balls, 1);
							writeInteger(buffer, offset, _event->strikes, 1);
							writeString(buffer, offset, _event->bases);
						}

						if (_event->sport_id == 16) {
							writeInteger(buffer, offset, _event->possession, 1);
							writeInteger(buffer, offset, _event->try_num, 1);
							writeInteger(buffer, offset, _event->yards, 1);
						}




						if (_event->sport_id == 19) {
							writeInteger(buffer, offset, _event->visit, 1);
							writeInteger(buffer, offset, _event->remaining_reds, 1);
						}


						if (_event->sport_id == 22) {
							writeInteger(buffer, offset, _event->home_legscore, 1);
							writeInteger(buffer, offset, _event->away_legscore, 1);
							writeInteger(buffer, offset, _event->throw_num, 1);
							writeInteger(buffer, offset, _event->visit, 1);
						}

						if (_event->sport_id == 32) {
							writeInteger(buffer, offset, _event->delivery, 1);
							writeInteger(buffer, offset, _event->home_remaining_bowls, 1);
							writeInteger(buffer, offset, _event->away_remaining_bowls, 1);
							writeInteger(buffer, offset, _event->current_end, 1);
						}

						if (_event->sport_id == 21) {
							writeInteger(buffer, offset, _event->home_dismissals, 1);
							writeInteger(buffer, offset, _event->away_dismissals, 1);
							writeInteger(buffer, offset, _event->home_penalty_runs, 1);
							writeInteger(buffer, offset, _event->away_penalty_runs, 1);
							writeInteger(buffer, offset, _event->innings, 1);
							writeInteger(buffer, offset, _event->over, 1);
							writeInteger(buffer, offset, _event->delivery, 1);

						}

						if (_event->sport_id == 0) writeInteger(buffer, offset, _event->current_ct_team, 1);

						writeInteger(buffer, offset, _event->position, 1);

					}

					if (event2lines.find(_event->getCatKey()) == event2lines.end()) writeInteger(buffer, offset, 0, 2);
					else writeInteger(buffer, offset, event2lines[_event->getCatKey()]->size(), 2);
					retry_offset = offset;
					writeInteger(buffer, offset, 0, 2);
					//offset += 2;
					event_lines_l = 0;
				}





				if (odds != nullptr) {
					betstop_reason = 0;
					if (odds->first_attribute("betstop_reason")) betstop_reason = atoi(odds->first_attribute("betstop_reason")->value());
					//_line->betstop_reason = betstop_reason;
					_line->event_id = event_id;
					_line->tournament_id = 0;
					_line->simple_id = 0;
					_line->season_id = 0;
					for (xml_node<> * market_node = odds->first_node("market"); market_node; market_node = market_node->next_sibling())
					{
						if (DEBUG_OUTPUT == true) printf("start parse market\r\n");
						outcomeNameError = 0;
						if (market_node->first_attribute("next_betstop")) _line->next_betstop = atoi(market_node->first_attribute("next_betstop")->value());
						if (market_node->first_node("market_metadata") && market_node->first_node("market_metadata")->first_attribute("next_betstop")) _line->next_betstop = atoi(market_node->first_node("market_metadata")->first_attribute("next_betstop")->value());
						if (market_node->first_attribute("favourite")) _line->favourite = atoi(market_node->first_attribute("favourite")->value());
						if (market_node->first_attribute("status")) _line->status = atoi(market_node->first_attribute("status")->value());
						if (market_node->first_attribute("id")) _line->market_id = atoi(market_node->first_attribute("id")->value());

						//if (_line->market_id == 1) printf(" markets_id[_line->market_id][0]->line_type=%d\r\n", markets_id[_line->market_id][0]->line_type);
						if (_line->market_id >= MAX_MARKETS) {
							std::printf("ERROR DATA!\r\nmarket id out of MAX_MARKETS in run%d\r\n", _line->market_id); continue;
						}
						if (markets_id[_line->market_id] == nullptr) {
							std::printf("ERROR DATA!\r\nmarket id not found in run%d\r\n", _line->market_id); continue;
						};
						if (markets_id[_line->market_id][0] == nullptr) {
							std::printf("ERROR DATA!\r\nmarket id [0] not found in run%d\r\n", _line->market_id); continue;
						};
						_line->variant = markets_id[_line->market_id][0]->variant;
						_line->type = markets_id[_line->market_id][0]->type;
						//if (_line->type == 4) {printf(AMQP_message[process_index-1 % AMQP_QUEUE]);	printf("\r\n"); printf("\r\n");}

						if (_line->specifier_number > 0) for (q = 0; q < _line->specifier_number; q++) {
							if (_line->specifier[q] != nullptr) delete[] _line->specifier[q]; _line->specifier[q] = nullptr;
							if (_line->specifier_value[q] != nullptr)  delete[] _line->specifier_value[q]; _line->specifier_value[q] = nullptr;
						}
						if (_line->specifier != nullptr) { delete[] _line->specifier; _line->specifier = nullptr; }
						if (_line->specifier_value != nullptr) { delete[] _line->specifier_value; _line->specifier_value = nullptr; }
						_line->specifier_number = 0;
						if (_line->extended_specifier_number > 0) for (q = 0; q < _line->extended_specifier_number; q++) {
							if (_line->extended_specifier[q] != nullptr) delete[] _line->extended_specifier[q];
							if (_line->extended_specifier_value[q] != nullptr)  delete[] _line->extended_specifier_value[q];
						}
						if (_line->extended_specifier != nullptr) { delete[] _line->extended_specifier; _line->extended_specifier = nullptr; }
						if (_line->extended_specifier_value != nullptr) { delete[] _line->extended_specifier_value; _line->extended_specifier_value = nullptr; }
						_line->extended_specifier_number = 0;
						if (market_node->first_attribute("specifiers")) {
							n = 0;
							m = market_node->first_attribute("specifiers")->value_size();
							for (q = 0; q < m; q++) {
								if (market_node->first_attribute("specifiers")->value()[q] == '=')
									index_equally[n] = q;

								if (market_node->first_attribute("specifiers")->value()[q] == '|') {
									index_separator[n] = q; n++;
								}

							}
							index_separator[n] = q; n++;




							_line->specifier_number = n;
							if (_line->specifier_number > 0) {
								_line->specifier_value = new char*[_line->specifier_number];
								_line->specifier = new char*[_line->specifier_number];


								for (q = 0; q < _line->specifier_number; q++) {
									if (q > 0) {
										_line->specifier[q] = new char[index_equally[q] - index_separator[q - 1]];
										strncpy(_line->specifier[q], (char*)((char*)market_node->first_attribute("specifiers")->value() + index_separator[q - 1]) + 1, index_equally[q] - index_separator[q - 1] - 1);
										_line->specifier[q][index_equally[q] - index_separator[q - 1] - 1] = 0;
									}
									else {
										_line->specifier[q] = new char[index_equally[q] + 1]; strncpy(_line->specifier[q], market_node->first_attribute("specifiers")->value(), index_equally[q]); _line->specifier[q][index_equally[q]] = 0;


									}

									_line->specifier_value[q] = new char[index_separator[q] - index_equally[q]];
									strncpy(_line->specifier_value[q], (char*)((char*)market_node->first_attribute("specifiers")->value() + index_equally[q]) + 1, index_separator[q] - index_equally[q] - 1);
									_line->specifier_value[q][index_separator[q] - index_equally[q] - 1] = 0;



								}
							}
						}
						if (market_node->first_attribute("extended_specifiers")) {
							n = 0;
							m = market_node->first_attribute("extended_specifiers")->value_size();
							for (q = 0; q < m; q++) {
								if (market_node->first_attribute("extended_specifiers")->value()[q] == '=')
									index_equally[n] = q;

								if (market_node->first_attribute("extended_specifiers")->value()[q] == '|') {
									index_separator[n] = q; n++;
								}

							}
							index_separator[n] = q; n++;



							_line->extended_specifier_number = n;
							if (_line->extended_specifier_number > 0) {
								_line->extended_specifier_value = new char*[_line->extended_specifier_number];
								_line->extended_specifier = new char*[_line->extended_specifier_number];


								for (q = 0; q < _line->extended_specifier_number; q++) {
									if (q > 0) {
										_line->extended_specifier[q] = new char[index_equally[q] - index_separator[q - 1]];
										strncpy(_line->extended_specifier[q], (char*)((char*)market_node->first_attribute("extended_specifiers")->value() + index_separator[q - 1]) + 1, index_equally[q] - index_separator[q - 1] - 1);
										_line->extended_specifier[q][index_equally[q] - index_separator[q - 1] - 1] = 0;
									}
									else {
										_line->extended_specifier[q] = new char[index_equally[q] + 1]; strncpy(_line->extended_specifier[q], market_node->first_attribute("extended_specifiers")->value(), index_equally[q]); _line->extended_specifier[q][index_equally[q]] = 0;


									}

									_line->extended_specifier_value[q] = new char[index_separator[q] - index_equally[q]];
									strncpy(_line->extended_specifier_value[q], (char*)((char*)market_node->first_attribute("extended_specifiers")->value() + index_equally[q]) + 1, index_separator[q] - index_equally[q] - 1);
									_line->extended_specifier_value[q][index_separator[q] - index_equally[q] - 1] = 0;
									//printf(_line->extended_specifier[q]);std::printf("\r\n");std::printf(_line->extended_specifier_value[q]);std::printf("\r\n");


								}
							}
						}
					outcomeNameError3: if (_line->variant > -1 && _line->type != 4) {
						z = strlen(_line->specifier_value[_line->variant]) + 1; if (strcmp(_line->specifier[_line->variant], "variant") != 0) { std::printf(_line->specifier[_line->variant]); std::printf("\r\n"); continue; }
						for (u = 0; u < max_markets_in[_line->market_id]; u++) if (markets_id[_line->market_id][u] != nullptr && markets_id[_line->market_id][u]->variable_text != nullptr && std::strcmp(_line->specifier_value[_line->variant], markets_id[_line->market_id][u]->variable_text) == 0) break;
						if (outcomeNameError == 1 || u == max_markets_in[_line->market_id]) {
							std::printf("Variant market3 not found in run market_id=%d variant=", _line->market_id);  std::printf(_line->specifier_value[_line->variant]);  std::printf("  getVariantMarket\r\n"); if (getVariantMarket(markets_id[_line->market_id][0], _line->specifier_value[_line->variant]) == -1) { std::printf("variant market not found "); continue; }
							else new_variant = true;
							for (u = 0; u < max_markets_in[_line->market_id]; u++) if (markets_id[_line->market_id][u] != nullptr && markets_id[_line->market_id][u]->variable_text != nullptr && std::strcmp(_line->specifier_value[_line->variant], markets_id[_line->market_id][u]->variable_text) == 0) break;
						}
						_market = markets_id[_line->market_id][u];
						if (DEBUG_OUTPUT == true) printf("start parse market01\r\n");
						if (new_variant == true && recovery_state == 0 && _market->type < 3) {
							t_offset = 0;
							writeInteger(buffer, t_offset, 0, 1);// sistem request_id
							writeInteger(buffer, t_offset, 0, 2);// step 1 num of sports = 0;
							writeInteger(buffer, t_offset, 0, 2);// step 1 num of categories = 0;
							writeInteger(buffer, t_offset, 0, 2);// step 1 num of tournaments = 0;
							writeInteger(buffer, t_offset, 1, 2);// step 1 num of markets = 0;

							writeInteger(buffer, t_offset, _market->id, 2);
							writeInteger(buffer, t_offset, _market->type, 1);
							writeInteger(buffer, t_offset, _market->line_type, 1);
							writeString(buffer, t_offset, _market->name);
							writeInteger(buffer, t_offset, _market->variant, 1);
							if (_market->variant>-1) writeString(buffer, t_offset, _market->variable_text);
							//if(_market->variant>-1 && _market->variable_text!=nullptr)
							//writeString(buffer, t_offset, _market->variable_text);
							writeInteger(buffer, t_offset, _market->outcome_number, 2);
							for (j = 0; j < _market->outcome_number; j++) {
								writeInteger(buffer, t_offset, _market->outcome_id[j], 4);
								writeString(buffer, t_offset, _market->outcome_name[j]);
							}


							writeInteger(buffer, t_offset, _market->specifier_number, 1);
							for (j = 0; j < _market->specifier_number; j++) 	writeString(buffer, t_offset, _market->specifier_name[j]);

							zip_len = gzip(buffer, t_offset, zip_message, 1);
							if (zip_len > 1)
							{
								encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
								radarMessageHandler(encode_message, encode_message_len);
								if (jump_buf[jump] != nullptr) delete[] jump_buf[jump];
								jump_buf[jump] = encode_message;
								jump_buf_len[jump] = encode_message_len;
								jump++;
								//delete[] encode_message;
								encode_message = nullptr;

							}
							delete[] zip_message;
							zip_message = nullptr;


							t_offset = 0;
						}
						if (DEBUG_OUTPUT == true) std::printf("start parse market02\r\n");
						if (outcomeNameError == 1) outcomeNameError = 2;
						if (_line->type == 3) z = 16;
					}
									   else {
										   _market = markets_id[_line->market_id][0]; if (_line->type == 0) z = 0; else if (_line->type == 1) z = 10; else if (_line->type == 2) z = 14; else if (_line->type == 3) z = 16; else if (_line->type == 4) {

											   z = strlen(_line->specifier_value[_line->variant]) + 1;
											   int in_dot = 0;
											   for (int q = 0; q < z - 2; q++) {
												   if (_line->specifier_value[_line->variant][q] == ':') in_dot++;
												   if (in_dot == 3) {
													   props_player_id = atoi((char*)((char*)_line->specifier_value[_line->variant] + q + 1)); break;
												   }
											   }

											   if (props_player_id >= MAX_PLAYERS) {
												   std::printf("ERROR props_player_id out of MAX_PLAYERS props_player_id=%d\r\n", props_player_id); continue;
											   }

											   if (players_id[props_player_id] == nullptr) {
												   std::printf("props_player_id=%d  not found . getPlayer\r\n ", props_player_id);
												   players[players_l].id = props_player_id; if (getPlayer(&players[players_l]) == -1)
												   {
													   std::printf("error props_player_id=%d  in getPlayer returned -1 \r\n ", props_player_id); continue;
												   }

												   else players_l++;
											   }

										   }

									   }
									   outcome_number = 0;
									   if (DEBUG_OUTPUT == true) printf("start parse market2\r\n");


									   if (_line->outcome_number > 0) { for (int i = 0; i < _line->outcome_number; i++) if (_line->outcome_name[i] != nullptr) delete[] _line->outcome_name[i]; };
									   _line->outcome_number = 0;

									   if (_line->outcome_id != nullptr) delete[] _line->outcome_id; if (_line->outcome_active != nullptr) delete[] _line->outcome_active; if (_line->outcome_team != nullptr) delete[] _line->outcome_team; if (_line->outcome_odds != nullptr) delete[] _line->outcome_odds;
									   if (_line->outcome_probabilities != nullptr) delete[] _line->outcome_probabilities; if (_line->outcome_name != nullptr) delete[] _line->outcome_name;
									   _line->outcome_probabilities = nullptr; _line->outcome_name = nullptr; _line->outcome_id = nullptr; _line->outcome_odds = nullptr; _line->outcome_active = nullptr;
									   _line->outcome_team = nullptr;


									   if (DEBUG_OUTPUT == true) std::printf("start parse market4\r\n");
									   if (_line->name != nullptr) delete[] _line->name;
									   _line->name = new char[strlen(_market->name) + 1];
									   std::strcpy(_line->name, _market->name);

									   for (int i = 0; i < _line->specifier_number; i++) {
										   if (i == _line->variant) continue;

										   replace(_line->name, _line->specifier[i], _line->specifier_value[i]);
									   }


									   replace(_line->name, "$competitor1", _event->home_name);
									   if (_event->away_name != nullptr) replace(_line->name, "$competitor2", _event->away_name);
									   if (_event->type_radar > 0) replace(_line->name, "$event", _event->home_name);

									   for (xml_node<> * outcome_node = market_node->first_node("outcome"); outcome_node; outcome_node = outcome_node->next_sibling()) {


										   if (outcome_node->first_attribute("active")) outcome_active[outcome_number] = atoi(outcome_node->first_attribute("active")->value());
										   else outcome_active[outcome_number] = 0;
										   if (outcome_node->first_attribute("team")) outcome_team[outcome_number] = atoi(outcome_node->first_attribute("team")->value());
										   else outcome_team[outcome_number] = 0;
										   if (outcome_node->first_attribute("id")) {
											   outcome_id[outcome_number] = atoi((char*)((char*)outcome_node->first_attribute("id")->value() + z));
											   if (outcome_id[outcome_number] == 0 && z > 0) {
												   outcome_id[outcome_number] = atoi(outcome_node->first_attribute("id")->value());
												   if (outcome_id[outcome_number] > 0) outcome_team[outcome_number] = 3;
												   else {
													   std::printf("_line->type=%d line->market_id=%d  _event->type_radar=%d  _line->event_id =%d \r\n", _line->type, _line->market_id, _event->type_radar, _line->event_id); std::printf(outcome_node->first_attribute("id")->value());

												   }
											   }

										   }
										   else outcome_id[outcome_number] = 0;


										   if (outcome_node->first_attribute("odds")) outcome_odds[outcome_number] = atof(outcome_node->first_attribute("odds")->value());
										   else outcome_odds[outcome_number] = 0;
										   if (outcome_node->first_attribute("probabilities")) outcome_probabilities[outcome_number] = atof(outcome_node->first_attribute("probabilities")->value());
										   else outcome_probabilities[outcome_number] = 0;
										   if (outcome_name[outcome_number] != nullptr) delete[] outcome_name[outcome_number]; outcome_name[outcome_number] = nullptr;
										   if (outcome_node->first_attribute("name")) {
											   outcome_name[outcome_number] = new char[strlen(outcome_node->first_attribute("name")->value()) + 1];
											   std::strcpy(outcome_name[outcome_number], outcome_node->first_attribute("name")->value());

										   }

										   outcome_number++;

									   }
									   if (DEBUG_OUTPUT == true) std::printf("start parse market3\r\n");




									   if (PRINT == true) {

										   std::printf("\r\n"); std::printf(_line->name); std::printf("\r\n"); std::printf("------------------------------------------------------------------------------\r\n");
									   }


									   /*std::strcat(socket_message_big, "\r\n");
									   std::strcat(socket_message_big, _line->name);
									   std::strcat(socket_message_big, "\r\n------------------------------------------------------------------------------\r\n");
									   */



									   _line->outcome_number = outcome_number;
									   if (_line->outcome_number > 0) {
										   _line->outcome_name = new char*[_line->outcome_number];
										   _line->outcome_id = new int[_line->outcome_number];
										   _line->outcome_team = new int[_line->outcome_number];
										   _line->outcome_active = new int[_line->outcome_number];
										   _line->outcome_probabilities = new float[_line->outcome_number];
										   _line->outcome_odds = new float[_line->outcome_number];
										   if (DEBUG_OUTPUT == true) std::printf("start parse market5 %d\r\n", _market->id);


										   if (DEBUG_OUTPUT == true) std::printf("_line->outcome_number= %d\r\n", _line->outcome_number);

										   for (int i = 0; i < _line->outcome_number; i++) {
											   _line->outcome_name[i] = nullptr;
											   _line->outcome_id[i] = outcome_id[i];
											   _line->outcome_active[i] = outcome_active[i];
											   _line->outcome_odds[i] = outcome_odds[i];
											   _line->outcome_team[i] = outcome_team[i];
											   _line->outcome_probabilities[i] = outcome_probabilities[i];


											   if (_line->type == 0) {
												   if (_line->outcome_id[i] == _market->outcome_id[i]) u = i;
												   else   for (u = 0; u < _market->outcome_number; u++) if (_line->outcome_id[i] == _market->outcome_id[u]) break;

												   if (DEBUG_OUTPUT == true) printf("_line->outcome_id[i]= %d\r\n", _line->outcome_id[i]);

												   if (u < _market->outcome_number) {
													   _line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
													   std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);

												   }
												   else {
													   std::printf("Eror. Outcome name not found. market_id=%d _line->outcome_id[i]=%d\r\n", _line->market_id, _line->outcome_id[i]);

													   _line->outcome_name[i] = new char[2];
													   std::strcpy(_line->outcome_name[i], " ");
													   if (_market->variant > -1) printf("_market->variant=%s\r\n", _market->variable_text);
													   if (outcomeNameError == 0) outcomeNameError = 1;


												   }

												   if (DEBUG_OUTPUT == true)	   printf("_line->specifier_number= %d\r\n", _line->specifier_number);

												   for (int j = 0; j < _line->specifier_number; j++) {
													   if (j == _line->variant) continue;

													   replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
												   }

												   replace(_line->outcome_name[i], "$competitor1", _event->home_name);
												   if (_event->away_name != nullptr) replace(_line->outcome_name[i], "$competitor2", _event->away_name);
												   if (_event->type_radar > 0) replace(_line->outcome_name[i], "$event", _event->home_name);



												   if (PRINT == true) {

													   std::printf(_line->outcome_name[i]); std::printf("\t");
													   std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
													   std::printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
												   }
												   /*std::strcat(socket_message_big, _line->outcome_name[i]);
												   std::strcat(socket_message_big, "\t");
												   std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
												   std::strcat(socket_message_big, socket_message_little);
												   std::strcat(socket_message_big, "\t");
												   std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
												   std::strcat(socket_message_big, socket_message_little);
												   */





											   }

											   if (_line->type == 1) {
												   if (_line->outcome_id[i] >= MAX_PLAYERS) {
													   std::printf("ERROR in run. player_id out of MAX_PLAYERS. _line->outcome_id[i]=%d  _line->market_id=%d event_id=%d\r\n", _line->outcome_id[i], _line->market_id, _line->event_id);
													   continue;

												   }


												   if (DEBUG_OUTPUT == true) std::printf("_line->outcome_id[i]= %d\r\n", _line->outcome_id[i]);
												   if (DEBUG_OUTPUT == true) std::printf("_line->outcome_team[i]= %d\r\n", _line->outcome_team[i]);


												   if (players_id[_line->outcome_id[i]] == nullptr && _line->outcome_team[i] == 0) {
													   std::printf("Player4 id=%d not found in market id=%d in event_id=%d  in run function team 0 \r\n", _line->outcome_id[i], _line->market_id, _line->event_id);


													   if (getCompetitor(competitors_id[_event->away_id]) == -1) {
														   std::printf(" Error get competitors away_id=%d \r\n", _event->away_id); //continue;
													   }

													   if (getCompetitor(competitors_id[_event->home_id]) == -1) {
														   std::printf(" Error get competitors home_id=%d \r\n", _event->home_id); //continue;
													   }

													   if (players_id[_line->outcome_id[i]] == nullptr) {
														   players[players_l].id = _line->outcome_id[i]; if (getPlayer(&players[players_l]) == -1)
														   {
															   std::printf("error player id=%d  not found \r\n ", _line->outcome_id[i]); //continue;
															   _line->outcome_team[i] = 1;
														   }
														   else    players_l++;
													   }

												   
												   
												   }

												   if (players_id[_line->outcome_id[i]] != nullptr && _line->outcome_team[i] == 0) {
													   if (players_id[_line->outcome_id[i]]->competitor_id ==_event->away_id) _line->outcome_team[i] = 2;  
													   else if (players_id[_line->outcome_id[i]]->competitor_id == _event->home_id) _line->outcome_team[i] = 1;  else {
														   std::printf("eror competitor_id in player  player_id=%d  event_id=%d  home_id=%d  away_id=%d run getCompetitor\r\n", _line->outcome_id[i], _line->event_id, _event->home_id, _event->away_id);
														   if (getCompetitor(competitors_id[_event->away_id]) == -1) {
															   std::printf(" Error get competitors away_id=%d \r\n", _event->away_id); //continue;
														   }

														   if (getCompetitor(competitors_id[_event->home_id]) == -1) {
															   std::printf(" Error get competitors away_id=%d \r\n", _event->home_id); //continue;
														   }


														   if (players_id[_line->outcome_id[i]]->competitor_id == _event->away_id) _line->outcome_team[i] = 2;
														   else  _line->outcome_team[i] = 1; 
													   }
												   }


												   if (players_id[_line->outcome_id[i]] == nullptr && _line->outcome_team[i] == 2) {
													   std::printf("Player4 id=%d not found in market id=%d in event_id=%d  in run function team 2 \r\n", _line->outcome_id[i], _line->market_id, _line->event_id);
													   if (_event->away_id >= MAX_COMPETITORS) {
														   std::printf("ERROR in run. away_id out of MAX_COMPETITORS. away_id=%d event_id=%d\r\n", _event->away_id, _line->event_id);
														   continue;
													   }

													   if (competitors_id[_event->away_id] == nullptr) {
														   std::printf("Competitor id %d not found in team 2 run. getCompetitor\r\n", _event->away_id);
														   competitors[competitors_l].id = _event->away_id;
														   if (getCompetitor(&competitors[competitors_l]) == -1) {
															   std::printf(" Error get competitors id=%d \r\n", _event->away_id); //continue;
														   }
														   else competitors_l++;


													   }
												   }

												   if (players_id[_line->outcome_id[i]] == nullptr && _line->outcome_team[i] == 1) {
													   std::printf("Player5 id=%d not found in market id=%d in event_id=%d  in run function team 1 \r\n", _line->outcome_id[i], _line->market_id, _line->event_id);
													   if (_event->home_id >= MAX_COMPETITORS) {
														   std::printf("ERROR in run. home_id out of MAX_COMPETITORS. home_id=%d event_id=%d\r\n", _event->home_id, _line->event_id);
														   continue;
													   }

													   if (competitors_id[_event->home_id] == nullptr) {
														   std::printf("Competitor id %d not found in team 1 run. getCompetitor\r\n", _event->home_id);
														   competitors[competitors_l].id = _event->home_id;
														   if (getCompetitor(&competitors[competitors_l]) == -1) {
															   std::printf(" Error get competitors id=%d \r\n", _event->home_id); //continue;
														   }
														   else competitors_l++;


													   }
												   }


												   if (_line->outcome_team[i] < 3 && players_id[_line->outcome_id[i]] == nullptr) {
													   std::printf("Player6 id=%d  not found in run after get competitor. getPlayer\r\n ", _line->outcome_id[i]);
													   players[players_l].id = _line->outcome_id[i]; if (getPlayer(&players[players_l]) == -1)
													   {
														   std::printf("error player id=%d  not found \r\n ", _line->outcome_id[i]); //continue;
														   _line->outcome_name[i] = new char[2];
														   std::strcpy(_line->outcome_name[i], " ");
													   }
													   else players_l++;
												   }

												   if (_line->outcome_team[i] < 3 && _line->outcome_name[i] == nullptr) {
													   if (_line->outcome_team[i] == 1) {
														   if (players_id[_line->outcome_id[i]]->full_name != nullptr) {
															   _line->outcome_name[i] = new char[strlen(players_id[_line->outcome_id[i]]->full_name) + strlen(_event->home_name) + 4];
															   std::strcpy(_line->outcome_name[i], players_id[_line->outcome_id[i]]->full_name);

														   }
														   else {
															   _line->outcome_name[i] = new char[strlen(players_id[_line->outcome_id[i]]->name) + strlen(_event->home_name) + 4];
															   std::strcpy(_line->outcome_name[i], players_id[_line->outcome_id[i]]->name);
														   }




														   std::strcat(_line->outcome_name[i], " (");
														   std::strcat(_line->outcome_name[i], _event->home_name);
														   std::strcat(_line->outcome_name[i], ")");

													   }
													   if (_line->outcome_team[i] == 2) {


														   if (players_id[_line->outcome_id[i]]->full_name != nullptr) {
															   if (_event->away_name != nullptr) _line->outcome_name[i] = new char[strlen(players_id[_line->outcome_id[i]]->full_name) + strlen(_event->away_name) + 4]; else _line->outcome_name[i] = new char[strlen(players_id[_line->outcome_id[i]]->full_name) + 1];
															   std::strcpy(_line->outcome_name[i], players_id[_line->outcome_id[i]]->full_name);

														   }
														   else {
															   if (_event->away_name != nullptr) _line->outcome_name[i] = new char[strlen(players_id[_line->outcome_id[i]]->name) + strlen(_event->away_name) + 4]; else _line->outcome_name[i] = new char[strlen(players_id[_line->outcome_id[i]]->name) + 1];
															   std::strcpy(_line->outcome_name[i], players_id[_line->outcome_id[i]]->name);
														   }



														   if (_event->away_name != nullptr) {
															   std::strcat(_line->outcome_name[i], " (");
															   std::strcat(_line->outcome_name[i], _event->away_name);
															   std::strcat(_line->outcome_name[i], ")");
														   }

													   }

												   }

												   if (_line->outcome_team[i] == 3) {

													   for (u = 0; u < _market->outcome_number; u++) if (_market->outcome_id[u] == _line->outcome_id[i]) break;
													   if (u < _market->outcome_number) {
														   _line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
														   std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);

														   for (int j = 0; j < _line->specifier_number; j++) {
															   if (j == _line->variant) continue;

															   replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
														   }

														   replace(_line->outcome_name[i], "$competitor1", _event->home_name);
														   replace(_line->outcome_name[i], "$competitor2", _event->away_name);
														   if (_event->type_radar > 0) replace(_line->outcome_name[i], "$event", _event->home_name);



													   }
													   else {
														   _line->outcome_name[i] = new char[2];
														   std::strcpy(_line->outcome_name[i], " ");
													   }



												   }





												   if (PRINT == true) {



													   std::printf(_line->outcome_name[i]); std::printf("\t");
													   std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
													   printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
												   }
												   /*
												   std::strcat(socket_message_big, _line->outcome_name[i]);
												   std::strcat(socket_message_big, "\t");
												   std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
												   std::strcat(socket_message_big, socket_message_little);
												   std::strcat(socket_message_big, "\t");
												   std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
												   std::strcat(socket_message_big, socket_message_little);


												   */

											   }

											   if (_line->type == 2) {
												   if (_line->outcome_team[i] != 3) {
													   if (_line->outcome_id[i] >= MAX_COMPETITORS) {
														   std::printf("ERROR in run. competitor_id out of MAX_COMPETITORS. _line->outcome_id[i]=%d  _line->market_id=%d event_id=%d\r\n", _line->outcome_id[i], _line->market_id, _line->event_id);
														   continue;
													   }
													   if (competitors_id[_line->outcome_id[i]] == nullptr) {
														   std::printf("Competitor id=%d not found in market id=%d in event_id=%d  in run function. getTournament\r\n", _line->outcome_id[i], _line->market_id, _line->event_id);
														   //tournaments[tournaments_l].id = _event->tournament_id;
														   //tournaments[tournaments_l].type_radar = _event->type_radar;

														   if (_event->type_radar == 0 && getTournament(tournaments_id[_event->tournament_id], false) == -1)
															   std::printf("ERROR!\r\nTournaments not found in run %d \r\n", _event->tournament_id);

														   if (_event->type_radar == 2 && getTournament(simples_id[_event->simple_id], false) == -1)
															   std::printf("ERROR!\r\nSimples Tournaments not found in run %d \r\n", _event->simple_id);

													   }

													   if (competitors_id[_line->outcome_id[i]] == nullptr) {
														   std::printf("\r\nCompetitors id=%d not found in tournament id=%d . Run getCompetitor\r\n", _line->outcome_id[i], _event->tournament_id);
														   competitors[competitors_l].id = _line->outcome_id[i];
														   if (getCompetitor(&competitors[competitors_l]) == -1) {
															   std::printf(" Error get competitors in run function line type= 2 id=%d \r\n", _line->outcome_id[i]);
															   _line->outcome_name[i] = new char[2];
															   std::strcpy(_line->outcome_name[i], " ");
														   }
														   else competitors_l++;
													   }

													   if (competitors_id[_line->outcome_id[i]] != nullptr) { _line->outcome_name[i] = new char[strlen(competitors_id[_line->outcome_id[i]]->name) + 1]; std::strcpy(_line->outcome_name[i], competitors_id[_line->outcome_id[i]]->name); }

												   }
												   else
												   {
													   for (u = 0; u < _market->outcome_number; u++) if (_market->outcome_id[u] == _line->outcome_id[i]) break;
													   if (u < _market->outcome_number) {
														   _line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
														   std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);
														   for (int j = 0; j < _line->specifier_number; j++) {
															   if (j == _line->variant) continue;
															   replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
														   }
														   replace(_line->outcome_name[i], "$competitor1", _event->home_name);
														   replace(_line->outcome_name[i], "$competitor2", _event->away_name);
														   if (_event->type_radar > 0) replace(_line->outcome_name[i], "$event", _event->home_name);
													   }
													   else { _line->outcome_name[i] = new char[2]; std::strcpy(_line->outcome_name[i], " "); }
												   }
												   if (PRINT == true) {
													   std::printf(_line->outcome_name[i]); std::printf("\t");
													   std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
													   printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
												   }
												   /*
												   std::strcat(socket_message_big, _line->outcome_name[i]);
												   std::strcat(socket_message_big, "\t");
												   std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
												   std::strcat(socket_message_big, socket_message_little);
												   std::strcat(socket_message_big, "\t");
												   std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
												   std::strcat(socket_message_big, socket_message_little);
												   */

											   }

											   if (_line->type == 3) {

												   if (_line->outcome_id[i] == _market->outcome_id[i]) u = i;
												   else
													   for (u = 0; u < _market->outcome_number; u++) {


														   if (_line->outcome_id[i] == _market->outcome_id[u]) break;
													   }

												   if (u < _market->outcome_number) {

													   _line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
													   std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);

												   }
												   else {
													   std::printf("Eror. Outcome name not found. market_id=%d _line->outcome_id[i]=%d\r\n", _line->market_id, _line->outcome_id[i]);
													   _line->outcome_name[i] = new char[2];
													   std::strcpy(_line->outcome_name[i], " ");
													   if (_market->variant > -1) std::printf("_market->variant=%s\r\n", _market->variable_text);
													   if (outcomeNameError == 0) outcomeNameError = 1;
												   }

												   for (int j = 0; j < _line->specifier_number; j++) {
													   if (j == _line->variant) continue;

													   replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
												   }

												   replace(_line->outcome_name[i], "$competitor1", _event->home_name);
												   replace(_line->outcome_name[i], "$competitor2", _event->away_name);
												   if (_event->type_radar > 0) replace(_line->outcome_name[i], "$event", _event->home_name);


												   //if (_line->market_id == 188 || _line->market_id == 224 || _line->market_id == 485 || _line->market_id == 231 || _line->market_id == 65 || _line->market_id == 383 || _line->market_id == 66) 

												   if (PRINT == true) {

													   std::printf(_line->outcome_name[i]); std::printf("\t");
													   std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
													   printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
												   }
												   /*
												   std::strcat(socket_message_big, _line->outcome_name[i]);
												   std::strcat(socket_message_big, "\t");
												   std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
												   std::strcat(socket_message_big, socket_message_little);
												   std::strcat(socket_message_big, "\t");
												   std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
												   std::strcat(socket_message_big, socket_message_little);*/




											   }

											   if (_line->type == 4) {

												   if (_line->outcome_team[i] == 2) _line->outcome_name[i] = new char[strlen(players_id[props_player_id]->full_name) + 14 + strlen(_event->away_name)];
												   else  _line->outcome_name[i] = new char[strlen(players_id[props_player_id]->full_name) + 14 + strlen(_event->home_name)];

												  std::strcpy(_line->outcome_name[i], players_id[props_player_id]->full_name);
												   //strcat(_line->outcome_name[i], " (");
												   //if (_line->outcome_team[i] == 2) strcat(_line->outcome_name[i], _event->away_name);
												   //else strcat(_line->outcome_name[i], _event->home_name);
												   //strcat(_line->outcome_name[i], ") ");
												   strcat(_line->outcome_name[i], " ");
												   _itoa(_line->outcome_id[i], buf, 10);
												   strcat(_line->outcome_name[i], buf);
												   strcat(_line->outcome_name[i], ".0+");

												   if (PRINT == true) {

													   std::printf(_line->outcome_name[i]); std::printf("\t");
													   std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
													   printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
												   }
												   /*
												   std::strcat(socket_message_big, _line->outcome_name[i]);
												   std::strcat(socket_message_big, "\t");
												   std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
												   std::strcat(socket_message_big, socket_message_little);
												   std::strcat(socket_message_big, "\t");
												   std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
												   std::strcat(socket_message_big, socket_message_little);*/




											   }


										   }



										   if (outcomeNameError == 1 && _market->variant > -1) goto outcomeNameError3;
									   }
									   if (DEBUG_OUTPUT == true) std::printf("start parse market6\r\n");

									   if (DEBUG_OUTPUT == true) std::printf("insertLine _line->type ==%d\r\n", _line->type);
									   if (DEBUG_OUTPUT == true) {
										   std::printf(_line->getCompoundKey().c_str());
										   std::printf("\r\n");
									   }
									   auto it = compound2line_index.find(_line->getCompoundKey());
									   if (DEBUG_OUTPUT == true) std::printf("auto it\r\n");

									   if (it == compound2line_index.end()) {
										   if (DEBUG_OUTPUT == true) std::printf("new line add ");
										   _line->id = lines_l;
										   if (DEBUG_OUTPUT == true) std::printf("new line add1 ");
										   lines[lines_l] = (*_line);
										   lines_id[_line->id] = &lines[lines_l];
										   if (DEBUG_OUTPUT == true) std::printf("new line add2 ");
										   insert_line(_line, lines_l);

										   if (DEBUG_OUTPUT == true) std::printf("new line add3 ");
										   lines_l++;
										   if (DEBUG_OUTPUT == true) std::printf("new line add finish\r\n");

									   }
									   else {
										   if (DEBUG_OUTPUT == true) std::printf("line update");
										   _line->id = it->second;
										   if (DEBUG_OUTPUT == true) std::printf("line update1");
										   lines[it->second] = (*_line);
										   if (DEBUG_OUTPUT == true) std::printf("line finish\r\n");

										   //printf("Line Update\r\n");
									   }

									   if (DEBUG_OUTPUT == true) std::printf("end insertLine _line->type ==%d\r\n", _line->type);

									   if (recovery_state == 0) {

										   if (DEBUG_OUTPUT == true) std::printf("write buffer data\r\n");

										   //if (markets_id[_line->market_id][0]->line_type == 0 && events[i].status == 0) continue;
										   //if (_line->status == 0 || _line->status == -3) continue;
										   event_lines_l++;
										   writeInteger(buffer, offset, _line->id, 4);
										   //writeInteger(buffer, offset, _line->betstop_reason, 1);
										   writeInteger(buffer, offset, _line->market_id, 2);
										   writeInteger(buffer, offset, _line->type, 1);
										   writeInteger(buffer, offset, _line->favourite, 1);
										   // if (_event->bet_stop == 1 && _line->status == 0) writeInteger(buffer, offset, -1, 1); else
										   writeInteger(buffer, offset, _line->status, 1);
										   //if (_line->outcome_number == 0) printf("_line->outcome_number=0 _line->id=%d  _line->market_id=%d\r\n", _line->id, _line->market_id);
										   if (_line->type == 3) writeString(buffer, offset, _line->name);
										   writeInteger(buffer, offset, _line->outcome_number, 2);
										   for (int j = 0; j < _line->outcome_number; j++) {
											   writeInteger(buffer, offset, _line->outcome_id[j], 4);
											   writeInteger(buffer, offset, _line->outcome_active[j], 1);
											   if (_line->type == 1 || _line->type == 2 || _line->type == 4) writeInteger(buffer, offset, _line->outcome_team[j], 1);
											   //if ((_line->type == 1 || _line->type == 2) && _line->outcome_team[j] != 3)
											   //if (_line->type == 1 || _line->type == 2 || _line->type == 4)
											   if (_line->type > 0) writeString(buffer, offset, _line->outcome_name[j]);
											   //writeInteger(buffer, offset, (int)(_line->outcome_odds[j] * 10000), 4);
											   writeFloat(buffer, offset, _line->outcome_odds[j]);
											   if (PROBABILITIES == 1) writeInteger(buffer, offset, (int)(_line->outcome_probabilities[j] * 100000 + 0.5), 4);
										   }

										   writeInteger(buffer, offset, _line->specifier_number, 1);
										   //for (int j = 0; j < _line->specifier_number; j++) writeString(buffer, offset, _line->specifier_value[j]);
										   for (j = 0; j < _line->specifier_number; j++) {
											   if (_line->market_id == 215 && j == 2) {
												  std::strcpy(specifier_value, _line->specifier_value[j]); replace_competitor(specifier_value);
												   writeString(buffer, offset, specifier_value);
											   }
											   else    if (_line->market_id == 882 && j == 0) {
												  std::strcpy(specifier_value, _line->specifier_value[j]); replace_player(specifier_value);
												   writeString(buffer, offset, specifier_value);
											   }
											   else  writeString(buffer, offset, _line->specifier_value[j]);


										   }



										   if (DEBUG_OUTPUT == true) printf("end write buffer data\r\n");

									   }


					}
				}
				if (recovery_state == 0) writeInteger(buffer, retry_offset, event_lines_l, 2);

				if (_event->status > 0) _event->bet_stop = 0;
				else  if (_event->status == 0 && _event->bet_stop == 1) {
					int active_lines_counter = 0;
					if (event2lines.find(_event->getCatKey()) == event2lines.end()) {}
					else for (unordered_set<int>::iterator it = event2lines[_event->getCatKey()]->begin(); it != event2lines[_event->getCatKey()]->end(); ++it)
						if (lines[*(it)].status == 1) active_lines_counter++;
					if (active_lines_counter > 0) _event->bet_stop = 0; else radar_message = false;

				}


			}

			if (DEBUG_OUTPUT == true) std::printf("end parse type_radar=%d\r\n", type_radar);

			//bool radar_message = true;
			//int active_lines_counter = 0;

			if (recovery_state == 0 && radar_message == true) {
				if (DEBUG_OUTPUT == true) printf("radarmessagehandler\r\n");
				zip_len = gzip(buffer, offset, zip_message, 2);
				//delete[] buffer;
				if (zip_len > 1)
				{
					encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
					//while (server.ws_clients_flag.test_and_set(std::memory_order_acquire));
					radarMessageHandler(encode_message, encode_message_len);
					if (jump_buf[jump] != nullptr) delete[] jump_buf[jump];
					jump_buf[jump] = encode_message;
					jump_buf_len[jump] = encode_message_len;
					jump++;
					//server.ws_clients_flag.clear(std::memory_order_release);
					//printf("encode_message_len=%d\r\n", encode_message_len);
					//delete[] encode_message;
					encode_message = nullptr;


				}
				delete[] zip_message;
				zip_message = nullptr;
				if (DEBUG_OUTPUT == true) printf("end radarmessagehandler\r\n");
			}
			//delete[] zip_message;


		}
		else if (std::strcmp("snapshot_complete", doc.first_node()->name()) == 0) {
			request_id = -1;
			if (doc.first_node()->first_attribute("request_id")) request_id = atoi(doc.first_node()->first_attribute("request_id")->value());
			if (recovery_timestamp_integer == request_id) counter_snapshot++;
			std::printf("request_id=%d counter_snapshot=%d recovery_timestamp_integer=%d \r\n", request_id, counter_snapshot, recovery_timestamp_integer);


			if ((counter_snapshot == 2) || (counter_snapshot == 1 && recovery_timestamp == 0)) {

				//if (recovery_timestamp == 0) 
				if (recovery_timestamp == 0)	hThread7 = CreateThread(nullptr, 16777216, &StateFullEvent, 0, THREAD_TERMINATE, &dwThreadID7);
				counter_snapshot = 0;
				if (recovery_state_timestamp != 0) {
					offset = 0;
					writeInteger(buffer, offset, 0, 1);//sistem request_id
					writeInteger(buffer, offset, 0, 1);
					zip_len = gzip(buffer, offset, zip_message, 9);
					encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
					radarMessageHandler(encode_message, encode_message_len);
					printf("BET_STOP 0\r\n");
					if (jump_buf[jump] != nullptr) delete[] jump_buf[jump];
					jump_buf[jump] = encode_message;
					jump_buf_len[jump] = encode_message_len;
					jump++;
					//delete[] encode_message;
					encode_message = nullptr;
					delete[] zip_message;
					zip_message = nullptr;
					offset = 0;
				}
				recovery_state = 0;
				recovery_state_timestamp = 0;
			}

		}
		else  if (std::strcmp("bet_stop", doc.first_node()->name()) == 0) {
			//printf(doc.first_node()->name()); std::printf("\r\n");
			//printf("bet_stop = %s\r\n", AMQP_message[(process_index - 1) % AMQP_QUEUE]);

			type_radar = 0;
			event_id = 0;
			if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:season:", 10) == 0)
			{event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 10)); type_radar = 3;}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:match:", 9) == 0)
			{event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
			type_radar = 0;}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:simple_tournament:", 21) == 0)
			{event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 21)); type_radar = 2;}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:race_tournament:", 19) == 0)
			{event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 19)); type_radar = 4;}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:match:", 9) == 0)
			{event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9)); type_radar = 5; continue; }
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:season:", 10) == 0)
			{event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 10)); type_radar = 6; continue;}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:tournament:", 14) == 0)
			{event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 14)); type_radar = 7; continue;}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:stage:", 9) == 0)
			{   type_radar = 1; event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
				key = "1"+string((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
				if (events_id.find(key) != events_id.end() && (event_id >= MAX_TOURNAMENTS || tournaments_id[event_id] == nullptr)) type_radar = 1;
				else if (events_id.find(key) == events_id.end() && event_id < MAX_TOURNAMENTS && tournaments_id[event_id] != nullptr) type_radar = 4;
				else if (events_id.find(key) == events_id.end() && (event_id >= MAX_TOURNAMENTS || tournaments_id[event_id] == nullptr)) {
					type_radar = -1;
					tournaments[tournaments_l].id = event_id;
					tournaments[tournaments_l].type_radar = 1;
					tournaments[tournaments_l].season_id = 0;
					tournaments[tournaments_l].simple_id = 0;
					if (event_id >= MAX_TOURNAMENTS || getTournament(&tournaments[tournaments_l], false) == -1) {

						tournaments[tournaments_l].id = 0; tournaments[tournaments_l].type_radar = 0;
						events[events_l].id = event_id; events[events_l].type_radar = 1;
						ret_fixture = getEventFixture(&events[events_l]);
						if (ret_fixture == -1) {
							events[events_l].id = 0; events[events_l].type_radar = 0;
						}
						else { events_l++; type_radar = 1; }
					}
					else { type_radar = 4;  tournaments_l++; }
				}
				if (type_radar == -1) continue;
			}

			else { std::printf("Unknown type radar in bet_stop =%s", (char*)doc.first_node()->first_attribute("event_id")->value()); continue; };
			//0 sr:match://1 sr:race_event(sr:stage) //2 sr:simple_tournament://3 sr:season://4 sr:race_tournament://5 vf:match //6 sr:season: 7 //vf:tournament:

			key = to_string(type_radar) + to_string(event_id);

			if (type_radar == 0 || type_radar == 1 || type_radar == 5) {
				if (events_id.find(key) == events_id.end()) {
					std::printf("Event not found in bet_stop. event_id=%d type_radar=%d\r\n", event_id, type_radar); continue;
				}
				_event = events_id[key];
				_event->bet_stop = 1;

				if (event2lines.find(_event->getCatKey()) == event2lines.end()) {}
				else for (unordered_set<int>::iterator it = event2lines[key]->begin(); it != event2lines[key]->end(); ++it) if (lines[*(it)].status == 1) lines[*(it)].status = -1;



				if (recovery_state == 0) {
					t_offset = 0;
					writeInteger(buffer, t_offset, 0, 1);//sistem request_id
					writeInteger(buffer, t_offset, _event->id, 4);
					zip_len = gzip(buffer, t_offset, zip_message, 8);
					if (zip_len > 1)
					{
						encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
						radarMessageHandler(encode_message, encode_message_len);
						if (jump_buf[jump] != nullptr) delete[] jump_buf[jump];
						jump_buf[jump] = encode_message;
						jump_buf_len[jump] = encode_message_len;
						jump++;
						//delete[] encode_message;
						encode_message = nullptr;

					}
					delete[] zip_message;
					zip_message = nullptr;
					if (DEBUG_OUTPUT == true) printf("bet_stop radarmessagehandler\r\n");


					t_offset = 0;
				}
			}

		}
		else  if (std::strcmp("alive", doc.first_node()->name()) == 0) {
			//printf("alive = %s\r\n", AMQP_message[(process_index - 1) % AMQP_QUEUE]);

			//alive_timestamp = _atoi64((char*)((char*)doc.first_node()->first_attribute("timestamp")->value()));
			//if (recovery_state_timestamp + recovery_state == 0) recovery_timestamp = alive_timestamp;// _atoi64((char*)((char*)doc.first_node()->first_attribute("timestamp")->value
			//if (recovery_state_timestamp != -1 && recovery_state != -1) alive_timestamp = _atoi64((char*)((char*)doc.first_node()->first_attribute("timestamp")->value()));
			if (recovery_state_timestamp == 0 && recovery_state == 0) {
				recovery_timestamp = _atoi64((char*)((char*)doc.first_node()->first_attribute("timestamp")->value()));
				recovery_timestamp_integer = recovery_timestamp / 1000;
			};
			//recovery_timestamp = last_recovery_timestamp;
			//std::printf("alive_timestamp=%I64d\r\n", alive_timestamp);
			//std::printf("server_timestamp=%I64d\r\n", timestamp());

		}
		else {
			//printf(doc.first_node()->name()); std::printf("\r\n");
		}



		//int p2 = timestamp();
		//	printf("time = %dms\r\n ",(p2 - p1));


		/*	if (recovery_state == 0) {
		int p1 = timestamp();
		for (int i = 0; i < events_l; i++) {

		_line[0] = lines[i];


		auto it = compound2line_index.find(_line ->getCompoundKey());
		if (it == compound2line_index.end()) {
		_line->id = lines_l;
		lines[lines_l] = (*_line);
		lines_id[_line->id] = &lines[lines_l];
		insert_line(_line, lines_l);
		lines_l++;

		}
		else {
		_line->id = it->second;
		lines[it->second] = (*_line);

		}




		}

		int p2 = timestamp();












		printf("Copy all lines =%d , time = %dms\r\n ", events_l, (p2 - p1));
		}
		*/

		//printf("lines_l=%d\r\n",lines_l);
		//string String(socket_message_big);

		//radarMessageHandler(socket_message_big, strlen(socket_message_big));


		/*

		root_node = doc.first_node("odds_change");
		if (root_node && root_node->first_node("sport_event_status") && root_node->first_node("sport_event_status")->first_attribute("status")) {

		//	printf(root_node->first_node("sport_event_status")->first_attribute("status")->value());

		status=atoi(root_node->first_node("sport_event_status")->first_attribute("status")->value());

		}

		*/

		//if (i < 100 && _event->sport_id == 21 && (envelope.message.body.len > 8000 || status == 1))

		//printf("ff=%d\r\n", strlen(AMQP_message[(process_index - 1) % AMQP_QUEUE]));

		/*
		write_count_file++;
		std::strcpy(name, "C://Betradar//Logo//replay_message");
		_itoa(write_count_file, buf, 10);
		strcat(name, buf);
		strcat(name, ".xml");
		///DeleteFile(name);
		File = CreateFile(name, GENERIC_WRITE, 0, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		l = SetFilePointer(File, 0, 0, FILE_BEGIN);
		//printf(name);
		//printf("\r\n");
		//printf("message length= %d\r\n", strlen(AMQP_message[(process_index-1)%AMQP_QUEUE]));
		WriteFile(File, AMQP_message[(process_index - 1) % AMQP_QUEUE], strlen(AMQP_message[(process_index - 1) % AMQP_QUEUE]), &l, nullptr);
		CloseHandle(File);


		if (std::strcmp("bet_stop", doc.first_node()->name()) == 0 && _event != nullptr && (_event->id == 12113906 || _event->id == 12534700 || _event->id == 13359427 || _event->id == 13578201)) {

		write_count_file++; std::strcpy(name, "D://passionbet//XML//MTS//bet_stop_");
		_itoa(_event->id, buf, 10);
		strcat(name, buf);
		strcat(name, "_");
		_itoa(write_count_file, buf, 10);
		strcat(name, buf);
		strcat(name, ".xml");
		DeleteFile(name);
		File = CreateFile(name, GENERIC_WRITE, 0, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		l = SetFilePointer(File, 0, 0, FILE_BEGIN);
		printf(name);
		printf("\r\n");
		printf("message length= %d\r\n", strlen(AMQP_message[(process_index - 1) % AMQP_QUEUE]));
		WriteFile(File, AMQP_message[(process_index - 1) % AMQP_QUEUE], strlen(AMQP_message[(process_index - 1) % AMQP_QUEUE]), &l, nullptr);
		CloseHandle(File);
		}

		*/

		doc.clear();

		//WriteFile(File, "<endmessage></endmessage>", strlen("<endmessage></endmessage>"), &l, nullptr);

		//if (i > 50) return;

		//if(i<4)std::printf((char*)envelope.message.body.bytes);
		//i++;

		//	if (_line != nullptr) {
		//			delete _line; _line = nullptr;
		//		}




	}

	delete[] outcome_team;
	delete[] outcome_name;
	delete[] outcome_id;
	delete[] outcome_active;
	delete[] outcome_probabilities;
	delete[] outcome_odds;
	delete[] name;
	delete[] buf;
	delete _line;
	delete[] specifier_value;
	//delete[] maxbuf;
	//delete[] socket_message_big;
	//delete[] socket_message_little;
	delete[] buffer;
	clientIDs.clear();
	std::printf("Exit BetradarProcessThread");
	return 0;

}
DWORD WINAPI BetsProcessThread(LPVOID lparam)
{
	using namespace rapidxml;
	using namespace std;
	xml_document<> doc;
	HANDLE File;
	DWORD l = 0;
	amqp_frame_t frame;
	uint64_t now;
	char* name = new char[MAX_PATH];
	char* buf = new char[MAX_PATH];
	char set_scores[1024];
	char* maxbuf = new char[200000];
	Event* _event = nullptr;
	string key = "";
	Tournament* _tournament = nullptr;
	int i = 0;
	int k = 0;
	int j = 0;
	int m = 0;
	int n = 0;
	int q = 0;
	int z = 0;
	int u = 0;
	int write_count_file = 0;
	int event_id = 0;
	int type_radar = 0;
	int status = 0;
	int betstop_reason = 0;
	int index_separator[100];
	int index_equally[100];
	int outcome_number;
	char** outcome_name = new char*[500];
	int* outcome_id = new int[500];
	int* outcome_active = new int[500];
	int* outcome_result = new int[500];
	int* outcome_void_factor = new int[500];
	int* outcome_dead_heat_factor = new int[500];
	int* outcome_team = new int[500];
	float* outcome_probabilities = new float[500];
	float* outcome_odds = new float[500];
	for (int i = 0; i < 500; i++) outcome_name[i] = nullptr;
	Line* _line = new Line();
	Bet* _bet = new Bet();
	Market* _market = nullptr;
	//char* socket_message_big = new char[145000];
	char* buffer = new char[145000];
	char* reg_buf = nullptr;
	size_t offset = 0;
	size_t retry_offset = 0;
	int event_lines_l = 0;
	char* zip_message = nullptr;
	int zip_len = 0;
	char* encode_message = nullptr;// = SendframeEncode(zip_message, zip_len, len);
	int encode_message_len = 0;
	//char* socket_message_little = new char[4096];
	int outcomeNameError = 0;
	int settlementError = 0;
	bool new_message_arrived = false;
	vector<int> clientIDs;
	char* data;
	unsigned char* recv_buf = nullptr;
	size_t size;
	size_t recv_offset;
	int ret_value;
	Client* client = nullptr;
	wsClient* wsclient = nullptr;
	//char* buffer = new char[LARGE];
	int len = 0;
	int bet_line_id;
	double bet_odd;
	double bet_stake;
	int bet_outcome_id;
	int accept_code = 0;
	Ticket* ticket;
	Bet* bet;
	int type;
	bool any_coeff;
	bool alternative;
	bool betradar_data_logs = false;
	int system_selected;
	double stake;
	int action;
	//int tickets_number = 0;;
	int bets_number;
	int device;
	time_t start;
	SYSTEMTIME st;
	struct tm tm;
	std::memset(&st, 0, sizeof(st));
	std::memset(&tm, 0, sizeof(tm));
	int settlement_type = 0;
	char* userlogin = nullptr;
	char* userpass = nullptr;
	char* last_domain = nullptr;
	int last_timezone = 0;
	int request_id = 0;
	char* newpass = nullptr;
	vector<Ticket*> dynamic_unplayed_tickets;
	unordered_set<Ticket*> unplayed_tickets;
	unordered_set<Ticket*> date_tickets;
	vector<int64_t> client_dates;
	int date_bets;
	bool get_unsettleds = false;
	int ret_fixture = 0;
	string* options = new string[10];
	options[0] = "eastbet/search";
	options[1] = "eastbet/user";
	options[2] = "eastbet/cashbox";
	options[3] = "eastbet/transaction";
	options[4] = "eastbet/transaction/approve";
	options[5] = "eastbet/transaction/info";
	options[6] = "eastbet/auth/user";
	int request_select = 0;
	int ws_opt_len = 0;
	int opt_len = 0;
	int props_player_id = 0;
	for (;;) {

		if (recovery_state == 0) {


			while (tickets_contact_oam_count_read < tickets_contact_oam_count) {

				processNewTicket(tickets_contact_oam[tickets_contact_oam_count_read % MAX_OAM]);
				tickets_contact_oam[tickets_contact_oam_count_read % MAX_OAM] = nullptr;
				tickets_contact_oam_count_read++;
			}





			clientIDs.clear();
			clientIDs = server.getClientIDs();

			for (i = 0; i < clientIDs.size(); i++) {
				int response = 0;
				if (server.wsClients[clientIDs[i]] == nullptr || server.wsClients[clientIDs[i]]->timestamp > 0)  continue;
				wsclient = server.wsClients[clientIDs[i]];
				if (wsclient->client_send == false && wsclient->recv_client_message_thread_queue < wsclient->recv_client_message_queue) {
					data = wsclient->recv_client_message[wsclient->recv_client_message_thread_queue %  RECV_MAX_CLIENT_QUEUE];

					if (std::strlen(data) > 14 && std::strncmp(data, "clientregister", 14) == 0) {


						string name = ""; string surname = ""; int day = 1; int month = 0; int year = 1900; string country = ""; string domain = ""; string region = ""; string city; string email = "";
						string sms = ""; string phone = "";	string login = ""; string password = ""; int currency = 0; string postal_code = ""; string address = ""; int timezone = 0; int step = 0; int email_newsletter = 0; int country_id = 0; int region_id = 0; int city_id = 0;
						Base64Decode((char*)((char*)data + 14), &recv_buf, &size);
						recv_offset = 0;
						offset = 0;
						response = 0;
						if (readInteger((char*)recv_buf, recv_offset, &step, 1, size) == -1)  response = -1;
						else switch (step) {

						case 1:
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; }
							surname = reg_buf;
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; }
							name = reg_buf;
							if (readInteger((char*)recv_buf, recv_offset, &day, 2, size) == -1) { response = -1; break; };
							if (readInteger((char*)recv_buf, recv_offset, &month, 2, size) == -1) { response = -1; break; };
							if (readInteger((char*)recv_buf, recv_offset, &year, 2, size) == -1) { response = -1; break; };
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							phone = reg_buf;
							break;

						case 2:
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							email = reg_buf;
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							login = reg_buf;
							break;





						case 3:
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							surname = reg_buf;
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							name = reg_buf;
							if (readInteger((char*)recv_buf, recv_offset, &day, 2, size) == -1) { response = -1; break; };
							if (readInteger((char*)recv_buf, recv_offset, &month, 2, size) == -1) { response = -1; break; };
							if (readInteger((char*)recv_buf, recv_offset, &year, 2, size) == -1) { response = -1; break; };
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							country = reg_buf;
							if (readInteger((char*)recv_buf, recv_offset, &country_id, 4, size) == -1) { response = -1; break; };
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							phone = reg_buf;
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							city = reg_buf;
							if (readInteger((char*)recv_buf, recv_offset, &city_id, 4, size) == -1) { response = -1; break; };
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							postal_code = reg_buf;
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							region = reg_buf;
							if (readInteger((char*)recv_buf, recv_offset, &region_id, 4, size) == -1) { response = -1; break; };
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							address = reg_buf;
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							email = reg_buf;
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							login = reg_buf;
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							password = reg_buf;
							if (readInteger((char*)recv_buf, recv_offset, &currency, 1, size) == -1) { response = -1; break; };
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							sms = reg_buf;
							if (readInteger((char*)recv_buf, recv_offset, &email_newsletter, 1, size) == -1) { response = -1; break; };
							if (readInteger((char*)recv_buf, recv_offset, &timezone, 1, size) == -1) { response = -1; break; };
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							domain = reg_buf;
							break;




						case 4:
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							phone = reg_buf;
							if (readInteger((char*)recv_buf, recv_offset, &currency, 1, size) == -1) { response = -1; break; };
							if (readInteger((char*)recv_buf, recv_offset, &email_newsletter, 1, size) == -1) { response = -1; break; };
							if (readInteger((char*)recv_buf, recv_offset, &timezone, 1, size) == -1) { response = -1; break; };
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							domain = reg_buf;
							break;

						case 5:
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							phone = reg_buf;
							break;


						case 6:
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							surname = reg_buf;
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							name = reg_buf;
							if (readInteger((char*)recv_buf, recv_offset, &day, 2, size) == -1) { response = -1; break; };
							if (readInteger((char*)recv_buf, recv_offset, &month, 2, size) == -1) { response = -1; break; };
							if (readInteger((char*)recv_buf, recv_offset, &year, 2, size) == -1) { response = -1; break; };
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							country = reg_buf;
							if (readInteger((char*)recv_buf, recv_offset, &country_id, 4, size) == -1) { response = -1; break; };
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							phone = reg_buf;
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							city = reg_buf;
							if (readInteger((char*)recv_buf, recv_offset, &city_id, 4, size) == -1) { response = -1; break; };
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							postal_code = reg_buf;
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							region = reg_buf;
							if (readInteger((char*)recv_buf, recv_offset, &region_id, 4, size) == -1) { response = -1; break; };
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							address = reg_buf;
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							email = reg_buf;
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							login = reg_buf;
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							password = reg_buf;
							if (readInteger((char*)recv_buf, recv_offset, &currency, 1, size) == -1) { response = -1; break; };
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							sms = reg_buf;
							if (readInteger((char*)recv_buf, recv_offset, &email_newsletter, 1, size) == -1) { response = -1; break; };
							if (readInteger((char*)recv_buf, recv_offset, &timezone, 1, size) == -1) { response = -1; break; };
							if (readString((char*)recv_buf, recv_offset, reg_buf, size) == -1) { response = -1; break; };
							domain = reg_buf;
							break;

						}

						if (response == 0) { if (readInteger((char*)recv_buf, recv_offset, &request_id, 1, size) == -1)  response = -1; }

						if (recv_buf != nullptr) delete[] recv_buf; recv_buf = nullptr;
						if (response == -1) { wsclient->ready_state = WS_READY_STATE_DATA_ERROR; continue; }

						if (step == 6 && wsclient->client_id == -1) response = 1;
						else if (step != 6 && wsclient->client_id > -1)  response = 1; else
							response = registerClient(name, surname, day, month, year, country, domain, region, city, email, email_newsletter, phone, login, password, currency, postal_code, address, sms, timezone, step, wsclient, country_id, region_id, city_id);


						writeInteger(buffer, offset, request_id, 1);
						writeInteger(buffer, offset, response, 1);
						zip_len = gzip(buffer, offset, zip_message, 10);
						if (zip_len < 1) {
							delete[] zip_message; zip_message = nullptr;
							wsclient->recv_client_message_thread_queue++; continue;
						}
						encode_message = SendframeEncode(zip_message, zip_len, len);
						delete[] zip_message; zip_message = nullptr;
						wsclient->send_client_message = encode_message;
						encode_message = nullptr;
						wsclient->send_client_message_length = len;
						wsclient->client_send = true;
					}

					else if (std::strlen(data) > 11 && std::strncmp(data, "clientlogin", 11) == 0) {
						Base64Decode((char*)((char*)data + 11), &recv_buf, &size);
						recv_offset = 0;
						offset = 0;
						if (readString((char*)recv_buf, recv_offset, userlogin, size) == -1) response = -1; else
							if (readString((char*)recv_buf, recv_offset, userpass, size) == -1)  response = -1; else
								if (readString((char*)recv_buf, recv_offset, last_domain, size) == -1)  response = -1; else
									if (readInteger((char*)recv_buf, recv_offset, &last_timezone, 1, size) == -1)  response = -1;
						if (readInteger((char*)recv_buf, recv_offset, &request_id, 1, size) == -1)  response = -1;
						if (recv_buf != nullptr) delete[] recv_buf; recv_buf = nullptr;
						if (response == -1) { wsclient->ready_state = WS_READY_STATE_DATA_ERROR; continue; }
						//string userlog = userlogin;
						bool logged = false;
						auto it = client_login_hash.find(userlogin);
						if (it == client_login_hash.end()) {
							it = client_phone_hash.find(userlogin);
							if (it == client_phone_hash.end()) {
								auto client_it = client_id_hash.find(atoi(userlogin)); if (client_it == client_id_hash.end()) logged = false; else { logged = true; client = client_it->second; };
							}
							else { logged = true; client = it->second; }
						}
						else { logged = true; client = it->second; }


						//printf("it->second->password =%s\r\n", it->second->password.c_str());
						//printf("userpass =%s\r\n", userpass);

						if (logged == true && client->password != userpass) logged = false;

						if (logged == false) {
							writeInteger(buffer, offset, request_id, 1);
							writeInteger(buffer, offset, -1, 1);

							if (wsclient->client_id > -1) {
								auto client_it = client_id_hash.find(wsclient->client_id);
								if (client_it == client_id_hash.end()) {}
								else {
									for (auto it = client_it->second->wsclients.begin(); it != client_it->second->wsclients.end(); ++it)
										if (*it == wsclient) {
											client_it->second->wsclients.erase(it); break;
										}
								}


							}



							wsclient->client_id = -1;

						}


						else {
							writeInteger(buffer, offset, request_id, 1);
							writeInteger(buffer, offset, 0, 1);
							client->wsclients.push_back(wsclient);
							client_dates = clientGetAllTicketDates(client);
							writeInteger(buffer, offset, client_dates.size(), 2);
							for (int k = 0; k < client_dates.size(); k++) {
								writeInteger(buffer, offset, client_dates[k], 4);
							}
							wsclient->client_id = client->client_id;
							writeInteger(buffer, offset, client->anonymous, 1);
							writeInteger(buffer, offset, client->currency, 1);
							writeString(buffer, offset, (char*)client->name.c_str());
							writeString(buffer, offset, (char*)client->surname.c_str());
							writeString(buffer, offset, (char*)client->country.c_str());
							writeInteger(buffer, offset, client->country_id, 4);
							writeString(buffer, offset, (char*)client->city.c_str());
							writeInteger(buffer, offset, client->city_id, 4);
							writeString(buffer, offset, (char*)client->region.c_str());
							writeInteger(buffer, offset, client->region_id, 4);
							writeString(buffer, offset, (char*)client->email.c_str());
							writeInteger(buffer, offset, client->date_of_birth, 4);
							writeString(buffer, offset, (char*)client->login.c_str());
							writeString(buffer, offset, (char*)client->postal_code.c_str());
							writeString(buffer, offset, (char*)client->phone.c_str());
							writeInteger(buffer, offset, client->client_id, 4);
							writeString(buffer, offset, (char*)client->address.c_str());
							writeInteger(buffer, offset, (int)(client->balance * 100 + 0.5), 4);
							writeInteger(buffer, offset, (int)(client->bets_amount * 100 + 0.5), 4);
							//printf("client4\r\n");
							/*	dynamic_unplayed_tickets = dynamicClientGetOpenTickets(client);
							writeInteger(buffer, offset, dynamic_unplayed_tickets.size(), 2);
							for (int k = dynamic_unplayed_tickets.size() - 1; k > -1; k--) HistoryTicket(buffer, offset, dynamic_unplayed_tickets[k]);*/

							unplayed_tickets = clientGetOpenTickets(client);
							if (unplayed_tickets.size() > 0) {
								writeInteger(buffer, offset, unplayed_tickets.size(), 2);
								for (auto ticket_it = unplayed_tickets.begin(); ticket_it != unplayed_tickets.end(); ++ticket_it)
									HistoryTicket(buffer, offset, (*ticket_it));
							}
							else  writeInteger(buffer, offset, 0, 2);
							client->last_domain = last_domain;
							client->last_timezone = last_timezone;
							updateClientDomainAndTimezoneToDB(client);
						}

						zip_len = gzip(buffer, offset, zip_message, 3);
						if (zip_len < 1) {
							delete[] zip_message; zip_message = nullptr;
							wsclient->recv_client_message_thread_queue++; continue;
						}
						encode_message = SendframeEncode(zip_message, zip_len, len);
						delete[] zip_message; zip_message = nullptr;
						wsclient->send_client_message = encode_message;
						encode_message = nullptr;
						wsclient->send_client_message_length = len;
						wsclient->client_send = true;
					}

					else if (std::strlen(data) > 13 && std::strncmp(data, "clientnewpass", 13) == 0) {
						int response = 11;
						Base64Decode((char*)((char*)data + 13), &recv_buf, &size);
						recv_offset = 0;
						offset = 0;
						if (readString((char*)recv_buf, recv_offset, userpass, size) == -1) response = -1;
						else if (readString((char*)recv_buf, recv_offset, newpass, size) == -1)  response = -1;
						else if (readInteger((char*)recv_buf, recv_offset, &request_id, 1, size) == -1)  response = -1;
						if (recv_buf != nullptr) delete[] recv_buf; recv_buf = nullptr;
						if (response == -1) { wsclient->ready_state = WS_READY_STATE_DATA_ERROR; continue; }
						//string userlog = userlogin;
						if (wsclient->client_id > -1) {
							auto it = client_id_hash.find(wsclient->client_id);
							if (it == client_id_hash.end()) { wsclient->client_id = -1; response = 11; }
							else {
								client = it->second;
								if (strcmp(userpass, client->password.c_str()) != 0 || strlen(newpass) > 25 || strlen(newpass) < 6) response = 11; else
								{
									client->password = newpass;
									string password = client->password;
									if (updateClientPasswordToDB(client) != -1) response = 10; else { response = 11; client->password = password; }


								}
							}
						}
						else response = 11;

						writeInteger(buffer, offset, request_id, 1);
						writeInteger(buffer, offset, response, 1);

						zip_len = gzip(buffer, offset, zip_message, 10);
						if (zip_len < 1) {
							delete[] zip_message; zip_message = nullptr;
							wsclient->recv_client_message_thread_queue++; continue;
						}
						encode_message = SendframeEncode(zip_message, zip_len, len);
						delete[] zip_message; zip_message = nullptr;
						wsclient->send_client_message = encode_message;
						encode_message = nullptr;
						wsclient->send_client_message_length = len;
						wsclient->client_send = true;
					}

					else if (std::strlen(data) > 11 && std::strncmp(data, "clientlogout", 11) == 0) {

						if (wsclient->client_id > -1) {
							auto client_it = client_id_hash.find(wsclient->client_id);
							if (client_it == client_id_hash.end()) {}
							else {
								for (auto it = client_it->second->wsclients.begin(); it != client_it->second->wsclients.end(); ++it)
									if (*it == wsclient) {
										client_it->second->wsclients.erase(it); break;
									}
							}

						}





						wsclient->client_id = -1;
					}

					else if (std::strlen(data) > 11 && std::strncmp(data, "clientsms", 9) == 0) {
						char* phone = nullptr;
						char* param = nullptr;
						char* sms = nullptr;
						if (wsclient->sms_counter > 5) continue;
						wsclient->sms_counter++;
						Base64Decode((char*)((char*)data + 9), &recv_buf, &size);
						recv_offset = 0;

						if (readString((char*)recv_buf, recv_offset, phone, size) == -1) response = -1;
						if (recv_buf != nullptr) delete[] recv_buf; recv_buf = nullptr;
						if (response == -1) { wsclient->ready_state = WS_READY_STATE_DATA_ERROR; continue; }

						if (wsclient->client_id > -1) {
							auto it = client_id_hash.find(wsclient->client_id);
							if (it == client_id_hash.end()) { wsclient->client_id = -1; delete[] phone; phone = nullptr; continue; }
							else {
								client = it->second;
								if (strcmp(phone, client->phone.c_str()) != 0) {
									delete[] phone; phone = nullptr; continue;
								}
							}
						}

						param = new char[sizeof(char*) + sizeof(char*) + 1];
						memcpy(param, &phone, sizeof(char*));
						sms = generateSmsCode();
						memcpy(param + sizeof(char*), &sms, sizeof(char*));
						wsclient->sms = sms;
						DWORD dw;
						CreateThread(nullptr, 200000, &SMSProcessThread, (LPVOID)param, THREAD_TERMINATE, &dw);

					}

					else if (std::strlen(data) > 13 && std::strncmp(data, "clienthistory", 13) == 0) {
						Base64Decode((char*)((char*)data + 13), &recv_buf, &size);
						recv_offset = 0;
						offset = 0;
						if (readInteger((char*)recv_buf, recv_offset, &date_bets, 4, size) == -1) response = -1; else
							if (readInteger((char*)recv_buf, recv_offset, &request_id, 1, size) == -1) response = -1;
						if (recv_buf != nullptr) delete[] recv_buf; recv_buf = nullptr;
						if (response == -1) { wsclient->ready_state = WS_READY_STATE_DATA_ERROR; continue; }
						//string userlog = userlogin;
						if (wsclient->client_id > -1) {
							auto it = client_id_hash.find(wsclient->client_id);
							if (it == client_id_hash.end()) wsclient->client_id = -1;
							else client = it->second;
						}

						if (wsclient->client_id > -1) {
							date_tickets = clientGetTicketsOnDate(client, (time_t)date_bets);
							if (date_tickets.size() > 0) {
								writeInteger(buffer, offset, request_id, 1);
								writeInteger(buffer, offset, date_tickets.size(), 2);
								for (auto ticket_it = date_tickets.begin(); ticket_it != date_tickets.end(); ++ticket_it)
									HistoryTicket(buffer, offset, (*ticket_it));
								zip_len = gzip(buffer, offset, zip_message, 5);
								if (zip_len < 1) {
									delete[] zip_message; zip_message = nullptr;
									server.wsClients[clientIDs[i]]->recv_client_message_thread_queue++; continue;
								}
								char* encode_message = SendframeEncode(zip_message, zip_len, len);
								delete[] zip_message; zip_message = nullptr;
								server.wsClients[clientIDs[i]]->send_client_message = encode_message;
								encode_message = nullptr;
								server.wsClients[clientIDs[i]]->send_client_message_length = len;
								server.wsClients[clientIDs[i]]->client_send = true;
							}
						}
					}

					wsclient->recv_client_message_thread_queue++;

				}
				if (wsclient->ticket_send == false && wsclient->ticket_process == true && wsclient->mts_process == 0) {
					data = wsclient->recv_ticket_message;
					if (std::strlen(data) > 6 && std::strncmp(data, "ticket", 6) == 0) {
						accept_code = 0;
						if (wsclient->client_id == -1)  accept_code = -8;
						auto it = client_id_hash.find(wsclient->client_id);
						if (it == client_id_hash.end()) {
							wsclient->client_id == -1;
							accept_code = -8;
						}
						else client = it->second;

						if (recovery_state_timestamp != 0 || https_request_status == -1 || (MTS_FLAG == 1 && mts_disconnect != 2)) accept_code = -10;
						if (accept_code < 0) goto ticket_response;

						Base64Decode((char*)((char*)data + 6), &recv_buf, &size);
						recv_offset = 0;
						offset = 0;
						if (readInteger((char*)recv_buf, recv_offset, &type, 1, size) == -1) response = -1; else //1 ordinar //2 express //3 system
							if (readInteger((char*)recv_buf, recv_offset, &device, 1, size) == -1) response = -1; else //mobile internet
								if (readInteger((char*)recv_buf, recv_offset, &bets_number, 1, size) == -1) response = -1;


						if (response == -1 || bets_number > 20 || bets_number < 1) { accept_code = -9; goto ticket_response; }
						if (type == 1 && bets_number > 1) wsclient->tickets_number = bets_number;
						else wsclient->tickets_number = 1;
						if (readInteger((char*)recv_buf, recv_offset, &system_selected, 1, size) == -1)  response = -1; else
							if (readDouble((char*)recv_buf, recv_offset, &stake, size) == -1)  response = -1; else
								if (readInteger((char*)recv_buf, recv_offset, (int*)&any_coeff, 1, size) == -1)  response = -1; else
									if (readInteger((char*)recv_buf, recv_offset, (int*)&alternative, 1, size) == -1)  response = -1; else
										if (readInteger((char*)recv_buf, recv_offset, &action, 1, size) == -1)  response = -1;

						if (response == -1) { accept_code = -9; wsclient->tickets_number = 0; goto ticket_response; }
						//wsclient->ticket_request_id = request_id;
						wsclient->tickets = new Ticket*[wsclient->tickets_number];
						for (int i = 0; i < wsclient->tickets_number; i++) wsclient->tickets[i] = nullptr;
						for (int i = 0; i < wsclient->tickets_number; i++) {
							wsclient->tickets[i] = new Ticket();
							ticket = wsclient->tickets[i];
							if (type == 3 && (system_selected > bets_number - 1 || system_selected < 2 || bets_number < 3)) type = 2;
							ticket->type = type;
							ticket->device = device;
							ticket->any_coeff = any_coeff;
							ticket->alternative = alternative;
							ticket->action = action;
							ticket->system_selected = system_selected;
							ticket->stake = stake;
							ticket->coeff = 1;
							if (type == 1 && bets_number > 1) ticket->bets_number = 1; else ticket->bets_number = bets_number;
							ticket->bets = new Bet*[ticket->bets_number];
							for (int j = 0; j < ticket->bets_number; j++) ticket->bets[j] = nullptr;
							for (int j = 0; j < ticket->bets_number; j++) {
								if (readInteger((char*)recv_buf, recv_offset, &bet_line_id, 4, size) == -1) { response = -1; break; };
								if (readInteger((char*)recv_buf, recv_offset, &bet_outcome_id, 4, size) == -1) { response = -1; break; };
								if (readDouble((char*)recv_buf, recv_offset, &bet_odd, size) == -1) { response = -1; break; };

								if (type == 1 && bets_number > 1) { if (readDouble((char*)recv_buf, recv_offset, &ticket->stake, size) == -1) { response = -1; break; }; }
								else if (readDouble((char*)recv_buf, recv_offset, &bet_stake, size) == -1) { response = -1; break; };
								ticket->bets[j] = new Bet(blines_id[bet_line_id], bet_outcome_id, bet_odd);
								//printf("bet bet_line_id=%d\r\n", bet_line_id);
								//printf("bet bet_outcome_id=%d\r\n", bet_outcome_id);
								//printf("blines_id[bet_line_id]->market_id=%d\r\n", blines_id[bet_line_id]->market_id);

								if (ticket->type < 3) ticket->coeff = ticket->coeff*ticket->bets[j]->accept_odd;
								bet = ticket->bets[j];
								if (bet->status >= 0 && bet->event_status > 0) ticket->is_live = true;
								if (ticket->accept_code == 0) {
									if (bet->status == -6 || bet->status == -7) { if (ticket->any_coeff == false) ticket->accept_code = bet->status; }
									else ticket->accept_code = bet->status;
								}
							}



							if (response == -1) {
								printf("response=%d\r\n", response);
								for (int i = 0; i < wsclient->tickets_number; i++) wsclient->tickets[i] = nullptr;
								if (wsclient->tickets != nullptr) {
									for (int i = 0; i < wsclient->tickets_number; i++) if (wsclient->tickets[i] != nullptr) { delete wsclient->tickets[i]; wsclient->tickets[i] = nullptr; }
									delete[] wsclient->tickets;
								}
								wsclient->tickets = nullptr;
								wsclient->tickets_number = 0;
								wsclient->ready_state = WS_READY_STATE_DATA_ERROR;
								accept_code = -9; break;
							}


							if (ticket->accept_code == 0) {
								if (ticket->stake > client->balance) ticket->accept_code = -3; else {
									ticket->timestamp = timestamp(); ticket->generateId(wsclient->socket, USER, i);
									ticket->client_id = client->client_id;
									ticket->domain = client->last_domain;
									ticket->currency = (int)client->currency;
									ticket->language = client->language;
									if (MTS_FLAG == 0) {
										client->balance = client->balance - ticket->stake; client->bets_amount = client->bets_amount + ticket->stake;
										processNewTicket(ticket);
									}

								}
							}



						}

						if (response == 0) readInteger((char*)recv_buf, recv_offset, &request_id, 1, size);
						wsclient->ticket_request_id = request_id;

					ticket_response:

						if (MTS_FLAG == 0 || accept_code < 0) {
							writeInteger(buffer, offset, wsclient->ticket_request_id, 1);
							writeInteger(buffer, offset, accept_code, 1);
							if (accept_code >= 0) {
								writeInteger(buffer, offset, (int)(client->balance * 100 + 0.5), 4);
								writeInteger(buffer, offset, (int)(client->bets_amount * 100 + 0.5), 4);
								updateClientBalanceToDB(client);
								writeInteger(buffer, offset, wsclient->tickets_number, 1);
								for (int i = 0; i < wsclient->tickets_number; i++) {
									ticket = wsclient->tickets[i];
									writeInteger(buffer, offset, ticket->accept_code, 2);
									if (ticket->accept_code < 0) { delete wsclient->tickets[i]; wsclient->tickets[i] = nullptr; continue; }
									writeInteger(buffer, offset, ticket->counter, 4);
									writeInteger(buffer, offset, ticket->timestamp / 1000, 4);
									writeInteger(buffer, offset, (int)(ticket->bonus * 100 + 0.5), 4);
									writeInteger(buffer, offset, (int)(ticket->stake * 100 + 0.5), 4);
									for (int j = 0; j < ticket->bets_number; j++) {
										bet = ticket->bets[j];
										writeInteger(buffer, offset, bet->counter, 4);
										//writeString(buffer, offset, (char*)ticket->bets[j]->id.c_str());
										writeFloat(buffer, offset, bet->accept_odd);
										writeString(buffer, offset, bet->event_score);
										writeString(buffer, offset, bet->event_set_scores);
										writeString(buffer, offset, bet->event_game_score);
										writeString(buffer, offset, bet->event_match_status_description);
										writeString(buffer, offset, bet->event_match_time);

									}
									wsclient->tickets[i] = nullptr;
								}
								delete[] wsclient->tickets;
								wsclient->tickets = nullptr;
								wsclient->tickets_number = 0;
							}



							zip_len = gzip(buffer, offset, zip_message, 4);
							if (zip_len < 1) {
								delete[] zip_message; zip_message = nullptr;
								delete[] wsclient->recv_ticket_message; wsclient->recv_ticket_message = nullptr;  wsclient->ticket_process = false; continue;
							}
							encode_message = SendframeEncode(zip_message, zip_len, len);
							delete[] zip_message; zip_message = nullptr;
							wsclient->send_ticket_message = encode_message;
							encode_message = nullptr;
							wsclient->send_ticket_message_length = len;
							delete[] wsclient->recv_ticket_message; wsclient->recv_ticket_message = nullptr;
							wsclient->ticket_send = true;
							wsclient->ticket_process = false;
						}
						else {
							delete[] wsclient->recv_ticket_message; wsclient->recv_ticket_message = nullptr;
							wsclient->mts_send_process = 0; wsclient->mts_process = 1;
						}

						if (recv_buf != nullptr) delete[] recv_buf; recv_buf = nullptr;

					}

				}
				if (MTS_FLAG == 2 && wsclient->ticket_send == false && wsclient->ticket_process == true && wsclient->mts_process == 1) {
					int ticket_ready_counter = 0;
					int bet_ready_counter = 0;
					Line* bline;
					Event* bevent;
					for (int i = 0; i < wsclient->tickets_number; i++) {
						ticket = wsclient->tickets[i];
						if (ticket->accept_code < 0 || ticket->is_live == false) { ticket_ready_counter++; continue; }
						if (ticket->timeout == 1) { ticket_ready_counter++; continue; }

						bet_ready_counter = 0;
						for (int j = 0; j < ticket->bets_number; j++) {
							bet = ticket->bets[j];
							if (bet->event_status == 0) { bet_ready_counter++; continue; }
							if (bet->timeout == 1) { bet_ready_counter++; continue; }
							bevent = bevents_id[bet->getCatKey()];
							if (bevent == nullptr || bevent->status > 2 || bevent->reporting == -1) { ticket->accept_code = -12;  ticket_ready_counter++; break; }
							if (bevent->reporting == 1 && (time(nullptr) - ticket->timestamp / 1000  < BET_TIMEOUT_REPORTING)) break;
							if (bevent->reporting == 0 && (time(nullptr) - ticket->timestamp / 1000  < BET_TIMEOUT)) break;

							if (bevent->home_score != bet->home_score || bevent->away_score != bet->away_score || bevent->away_gamescore != bet->away_gamescore || bevent->home_gamescore != bet->home_gamescore || (bevent->set_scores != nullptr && bet->event_set_scores != nullptr && strcmp(bet->event_set_scores, bevent->set_scores) != 0))
							{
								ticket->accept_code = -11; ticket_ready_counter++; break;
							}



							bline = blines_id[bet->line_id];
							if (bline == nullptr || bline->status != 1 || bline->outcome_active[bet->selected_outcome_id] == 0 || (bline->outcome_odds[bet->selected_outcome_id] != bet->accept_odd && ticket->any_coeff == false)) { ticket->accept_code = -12; ticket_ready_counter++; break; }
							bet->accept_odd = bline->outcome_odds[bet->selected_outcome_id];
							bet_ready_counter++;
							bet->timeout = 1;
						}
						if (bet_ready_counter == ticket->bets_number) { ticket_ready_counter++; ticket->timeout = 1; }

					}

					if (ticket_ready_counter == wsclient->tickets_number) wsclient->mts_process = 3;




				}
				if (wsclient->ticket_send == false && wsclient->ticket_process == true && wsclient->mts_process == 3) {
					//if (wsclient->client_id == -1)  accept_code = -8;
					client = client_id_hash[wsclient->tickets[0]->client_id];
					accept_code = 0;
					for (int i = 0; i < wsclient->tickets_number; i++) {
						ticket = wsclient->tickets[i];
						if (ticket->accept_code >= 0) {
							if (ticket->stake > client->balance) ticket->accept_code = -3; else {
								client->balance = client->balance - ticket->stake; client->bets_amount = client->bets_amount + ticket->stake;
								processNewTicket(ticket);
							}
						}

					}

					if (wsclient->client_id == wsclient->tickets[0]->client_id) {
						offset = 0;
						writeInteger(buffer, offset, wsclient->ticket_request_id, 1);
						writeInteger(buffer, offset, accept_code, 1);
						if (accept_code >= 0) {
							writeInteger(buffer, offset, (int)(client->balance * 100 + 0.5), 4);
							writeInteger(buffer, offset, (int)(client->bets_amount * 100 + 0.5), 4);
							updateClientBalanceToDB(client);
							writeInteger(buffer, offset, wsclient->tickets_number, 1);
							for (int i = 0; i < wsclient->tickets_number; i++) {
								ticket = wsclient->tickets[i];
								writeInteger(buffer, offset, ticket->accept_code, 2);
								if (wsclient->tickets[i]->accept_code < 0) { if (wsclient->tickets[i]->contact_oam == 0) delete wsclient->tickets[i]; wsclient->tickets[i] = nullptr; continue; }
								writeInteger(buffer, offset, ticket->counter, 4);
								//writeString(buffer, offset, (char*)wsclient->tickets[i]->id.c_str());
								writeInteger(buffer, offset, ticket->timestamp / 1000, 4);
								writeInteger(buffer, offset, (int)(ticket->bonus * 100 + 0.5), 4);
								writeInteger(buffer, offset, (int)(ticket->stake * 100 + 0.5), 4);


								for (int j = 0; j < ticket->bets_number; j++) {
									bet = ticket->bets[j];
									//printf(" bet->event_id=%d\r\n", bet->event_id);
									writeInteger(buffer, offset, bet->counter, 4);
									//writeString(buffer, offset, (char*)ticket->bets[j]->id.c_str());
									writeFloat(buffer, offset, bet->accept_odd);
									writeString(buffer, offset, bet->event_score);
									writeString(buffer, offset, bet->event_set_scores);
									writeString(buffer, offset, bet->event_game_score);
									writeString(buffer, offset, bet->event_match_status_description);
									writeString(buffer, offset, bet->event_match_time);

								}


								wsclient->tickets[i] = nullptr;


							}
							delete[] wsclient->tickets;
							wsclient->tickets = nullptr;
							wsclient->tickets_number = 0;

						}
						zip_len = gzip(buffer, offset, zip_message, 4);

						if (zip_len < 1) {
							delete[] zip_message; zip_message = nullptr;
							delete[] wsclient->recv_ticket_message; wsclient->recv_ticket_message = nullptr;  wsclient->ticket_process = false; continue;
						}
						encode_message = SendframeEncode(zip_message, zip_len, len);
						delete[] zip_message; zip_message = nullptr;

						wsclient->send_ticket_message = encode_message;
						encode_message = nullptr;
						wsclient->send_ticket_message_length = len;
						wsclient->ticket_send = true;
						wsclient->ticket_process = false;
						wsclient->mts_process = 0;
						wsclient->mts_send_process = 0;

					}
					else {
						for (int i = 0; i < wsclient->tickets_number; i++) { if (wsclient->tickets[i]->accept_code < 0)  delete wsclient->tickets[i]; wsclient->tickets[i] = nullptr; }
						delete[] wsclient->tickets;
						wsclient->tickets = nullptr;
						wsclient->tickets_number = 0;
						wsclient->mts_process = 0;
						wsclient->mts_send_process = 0;
						wsclient->ticket_process = false;

					}






				}
				if (wsclient->ready_state == HTTPS_STATE_READ) {
					if (wsclient->options == nullptr) ws_opt_len = 0;
					else  ws_opt_len = strlen(wsclient->options);
					request_select = 0;
					for (int j = 0; j < 6; j++) {
						opt_len = options[j].length();
						if ((ws_opt_len == opt_len || ws_opt_len == opt_len + 1) && (strncmp(wsclient->options, options[j].c_str(), opt_len) == 0)) { request_select = j + 1; break; };
					};

					using namespace rapidjson;
					Document document;
					Document response;
					GenericStringBuffer<UTF8<>> buffer;
					Writer<GenericStringBuffer<UTF8<>>> writer(buffer);
					Value objUser;
					Value objInformation;
					Value arrayUsers(kArrayType);
					time_t now_t;
					time(&now_t);
					string id = "";
					string secret = "";
					string search = "";
					string playerId = "";
					string type = "";
					string transactionId = "";
					string action = "";
					string authcode = "";
					double amount = 0;



					char* json = wsclient->https_buffer;
					if (request_select > 0) {
						if (wsclient->https_buffer_length == 0) request_select = 0; else
						{
							document.Parse(json);
							if (document.IsObject() == 0) request_select = 0;
						}
					};



					switch (request_select) {

					case 1:
					{
						if (document.HasMember("id") && document["id"].IsString()) id = document["id"].GetString();
						if (document.HasMember("secret") == 0 || document["secret"].IsString() == 0) { request_select = 0; break; }
						secret = document["secret"].GetString();
						if (document.HasMember("search") == 0 || document["search"].IsString() == 0) { request_select = 0; break; }
						search = document["search"].GetString();

						bool logged = false;
						auto it = client_login_hash.find(search);
						if (it == client_login_hash.end()) {
							it = client_phone_hash.find(search);
							if (it == client_phone_hash.end()) { logged = false; }
							else  logged = true;
						}
						else logged = true;
						if (logged == true) client = it->second;
						else {
							auto  it = client_id_hash.find(atoi(search.c_str()));
							if (it == client_id_hash.end()) { logged = false; }
							else { logged = true; client = it->second; }
						}

						if (logged == true) {

							response.SetObject();
							response.AddMember("success", true, response.GetAllocator());
							objUser.SetObject();
							_itoa(client->client_id, buf, 10);
							objUser.AddMember("userId", StringRef(buf), response.GetAllocator());
							objUser.AddMember("username", StringRef(client->login.c_str()), response.GetAllocator());
							objUser.AddMember("email", StringRef(client->email.c_str()), response.GetAllocator());
							objUser.AddMember("isTest", false, response.GetAllocator());
							objUser.AddMember("balance", client->balance, response.GetAllocator());
							objInformation.SetObject();
							objInformation.AddMember("gender", "Not specified", response.GetAllocator());
							objInformation.AddMember("firstName", StringRef(client->name.c_str()), response.GetAllocator());
							objInformation.AddMember("lastName", StringRef(client->surname.c_str()), response.GetAllocator());
							objInformation.AddMember("country", StringRef(client->country.c_str()), response.GetAllocator());
							objInformation.AddMember("phone", StringRef(client->phone.c_str()), response.GetAllocator());
							strftime(buf, 80, "%Y-%m-%dT%H:%M:%S.000Z", gmtime(&now_t));
							string rfc = buf;
							objInformation.AddMember("create_at", StringRef(rfc.c_str()), response.GetAllocator());
							_itoa(client->client_id, buf, 10);
							objInformation.AddMember("id", StringRef(buf), response.GetAllocator());
							objInformation.AddMember("currency", StringRef(currency_name[client->currency - 1].c_str()), response.GetAllocator());
							objInformation.AddMember("isBlocked", false, response.GetAllocator());
							objUser.AddMember("information", objInformation, response.GetAllocator());
							arrayUsers.SetArray();
							arrayUsers.PushBack(objUser, response.GetAllocator());
							response.AddMember("users", arrayUsers, response.GetAllocator());
							response.Accept(writer);
							//printf("%s", buffer.GetString());


						}
						else {
							response.SetObject();
							response.AddMember("success", false, response.GetAllocator());
							response.Accept(writer);
							//printf("%s", buffer.GetString());

						}




					}

					break;

					case 2:
					{
						if (document.HasMember("id") && document["id"].IsString()) id = document["id"].GetString();
						if (document.HasMember("secret") == 0 || document["secret"].IsString() == 0) { request_select = 0; break; }
						secret = document["secret"].GetString();
						if (document.HasMember("playerId") == 0 || document["playerId"].IsString() == 0) { request_select = 0; break; }
						playerId = document["playerId"].GetString();



						bool logged = false;
						auto it = client_login_hash.find(playerId);
						if (it == client_login_hash.end()) {
							it = client_phone_hash.find(playerId);
							if (it == client_phone_hash.end()) { logged = false; }
							else  logged = true;
						}
						else logged = true;
						if (logged == true) client = it->second;
						else {
							auto  it = client_id_hash.find(atoi(playerId.c_str()));
							if (it == client_id_hash.end()) { logged = false; }
							else { logged = true; client = it->second; }
						}

						if (logged == true) {

							response.SetObject();
							response.AddMember("success", true, response.GetAllocator());
							objUser.SetObject();
							_itoa(client->client_id, buf, 10);
							objUser.AddMember("userId", StringRef(buf), response.GetAllocator());
							objUser.AddMember("username", StringRef(client->login.c_str()), response.GetAllocator());
							objUser.AddMember("email", StringRef(client->email.c_str()), response.GetAllocator());
							objUser.AddMember("locale", "en", response.GetAllocator());
							objUser.AddMember("balance", client->balance, response.GetAllocator());
							objInformation.SetObject();
							objInformation.AddMember("gender", "Not specified", response.GetAllocator());
							objInformation.AddMember("firstName", StringRef(client->name.c_str()), response.GetAllocator());
							objInformation.AddMember("lastName", StringRef(client->surname.c_str()), response.GetAllocator());
							objInformation.AddMember("country", StringRef(client->country.c_str()), response.GetAllocator());
							objInformation.AddMember("phoneNumber", StringRef(client->phone.c_str()), response.GetAllocator());
							objInformation.AddMember("phone", StringRef(client->phone.c_str()), response.GetAllocator());
							strftime(buf, 80, "%Y-%m-%dT%H:%M:%S.000Z", gmtime(&now_t));
							string rfc = buf;
							objInformation.AddMember("create_at", StringRef(rfc.c_str()), response.GetAllocator());
							_itoa(client->client_id, buf, 10);
							objInformation.AddMember("id", StringRef(buf), response.GetAllocator());
							objInformation.AddMember("currency", StringRef(currency_name[client->currency - 1].c_str()), response.GetAllocator());
							objInformation.AddMember("isBlocked", false, response.GetAllocator());
							objUser.AddMember("information", objInformation, response.GetAllocator());
							//arrayUsers.SetObject();
							//arrayUsers.PushBack(objUser, response.GetAllocator());
							response.AddMember("user", objUser, response.GetAllocator());
							response.Accept(writer);
							//printf("%s", buffer.GetString());


						}
						else {
							response.SetObject();
							response.AddMember("success", false, response.GetAllocator());
							response.Accept(writer);
							//printf("%s", buffer.GetString());

						}




					}

					break;

					case 3:
					{
						if (document.HasMember("id") && document["id"].IsString()) id = document["id"].GetString();
						if (document.HasMember("secret") == 0 || document["secret"].IsString() == 0) { request_select = 0; break; }
						secret = document["secret"].GetString();
						if (document.HasMember("playerId") == 0 || document["playerId"].IsString() == 0) { request_select = 0; break; }
						playerId = document["playerId"].GetString();
						if (document.HasMember("type") == 0 || document["type"].IsString() == 0) { request_select = 0; break; }
						type = document["type"].GetString();		//DEPOSIT, WITHDRAWAL, CASHBACKOUT
						if (document.HasMember("amount") == 0 || document["amount"].IsDouble() == 0) { request_select = 0; break; }
						amount = document["amount"].GetDouble();


						bool logged = false;
						auto it = client_login_hash.find(playerId);
						if (it == client_login_hash.end()) {
							it = client_phone_hash.find(playerId);
							if (it == client_phone_hash.end()) { logged = false; }
							else  logged = true;
						}
						else logged = true;
						if (logged == true) client = it->second;
						else {
							auto  it = client_id_hash.find(atoi(playerId.c_str()));
							if (it == client_id_hash.end()) { logged = false; }
							else { logged = true; client = it->second; }
						}

						if (logged == true) {

							response.SetObject();
							response.AddMember("success", true, response.GetAllocator());
							response.AddMember("confirm", true, response.GetAllocator());
							objUser.SetObject();
							strftime(buf, 80, "%Y-%m-%dT%H:%M:%S.000Z", gmtime(&now_t));
							string rfc = buf;
							objUser.AddMember("complete_at", StringRef(rfc.c_str()), response.GetAllocator());
							objUser.AddMember("paymentInfo", StringRef("Туркменистан, Ашхабад, Кинотеатр «Туркменистан», (Каликат центр)"), response.GetAllocator());
							objUser.AddMember("description", StringRef("Cashbox_deposit"), response.GetAllocator());
							objUser.AddMember("type", StringRef(type.c_str()), response.GetAllocator());
							objUser.AddMember("state", StringRef("Success"), response.GetAllocator());
							objUser.AddMember("currency", StringRef(currency_name[client->currency - 1].c_str()), response.GetAllocator());
							objUser.AddMember("processType", StringRef("no"), response.GetAllocator());
							objUser.AddMember("ip", StringRef(client->last_domain.c_str()), response.GetAllocator());

							objInformation.SetObject();
							objInformation.AddMember("manual", true, response.GetAllocator());
							objInformation.AddMember("currentBalance", client->balance, response.GetAllocator());
							objInformation.AddMember("updatedBalance", client->balance + amount, response.GetAllocator());
							objUser.AddMember("info", objInformation, response.GetAllocator());
							strftime(buf, 80, "%Y-%m-%dT%H:%M:%S.000Z", gmtime(&now_t));
							rfc = buf;
							objUser.AddMember("create_at", StringRef(rfc.c_str()), response.GetAllocator());
							objUser.AddMember("finalAmount", amount, response.GetAllocator());
							objUser.AddMember("amount", amount, response.GetAllocator());
							objUser.AddMember("fee", 0, response.GetAllocator());
							if (client->anonymous == 0) objUser.AddMember("username", StringRef(client->login.c_str()), response.GetAllocator());
							else objUser.AddMember("username", StringRef(client->phone.c_str()), response.GetAllocator());
							strftime(buf, 80, "%Y-%m-%dT%H:%M:%S.000Z", gmtime(&now_t));
							rfc = buf;
							objUser.AddMember("id", StringRef((to_string(time(nullptr)) + client->phone).c_str()), response.GetAllocator());
							response.AddMember("transaction", objUser, response.GetAllocator());
							response.Accept(writer);
							//printf("%s", buffer.GetString());


						}
						else {
							response.SetObject();
							response.AddMember("success", false, response.GetAllocator());
							response.Accept(writer);
							//printf("%s", buffer.GetString());

						}










					}

					break;


					case 4:
					{
						if (document.HasMember("id") && document["id"].IsString()) id = document["id"].GetString();
						if (document.HasMember("secret") == 0 || document["secret"].IsString() == 0) { request_select = 0; break; }
						secret = document["secret"].GetString();
						if (document.HasMember("transactionId") == 0 || document["transactionId"].IsString() == 0) { request_select = 0; break; }
						transactionId = document["transactionId"].GetString();
						if (document.HasMember("action") == 0 || document["action"].IsString() == 0) { request_select = 0; break; }
						action = document["action"].GetString(); //complete, cancel

						bool logged = false;
						auto it = client_login_hash.find(playerId);
						if (it == client_login_hash.end()) {
							it = client_phone_hash.find(playerId);
							if (it == client_phone_hash.end()) { logged = false; }
							else  logged = true;
						}
						else logged = true;
						if (logged == true) client = it->second;
						else {
							auto  it = client_id_hash.find(atoi(playerId.c_str()));
							if (it == client_id_hash.end()) { logged = false; }
							else { logged = true; client = it->second; }
						}

						if (logged == true) {

							amount = 1000;
							response.SetObject();
							response.AddMember("success", true, response.GetAllocator());
							objUser.SetObject();
							strftime(buf, 80, "%Y-%m-%dT%H:%M:%S.000Z", gmtime(&now_t));
							string rfc = buf;
							objUser.AddMember("complete_at", StringRef(rfc.c_str()), response.GetAllocator());
							objUser.AddMember("paymentInfo", StringRef("Туркменистан, Ашхабад, Кинотеатр «Туркменистан», (Каликат центр)"), response.GetAllocator());
							objUser.AddMember("description", StringRef("Setreet adress"), response.GetAllocator());
							objUser.AddMember("cashboxApproved", false, response.GetAllocator());
							objUser.AddMember("cashboxId", StringRef("5811dc83e39fe82034da0da4"), response.GetAllocator());
							objUser.AddMember("type", StringRef("WITHDRAWAL"), response.GetAllocator());
							objUser.AddMember("state", StringRef("Success"), response.GetAllocator());
							objUser.AddMember("currency", StringRef(currency_name[client->currency - 1].c_str()), response.GetAllocator());
							objUser.AddMember("processType", StringRef("no"), response.GetAllocator());
							objUser.AddMember("ip", StringRef(client->last_domain.c_str()), response.GetAllocator());

							objInformation.SetObject();
							objInformation.AddMember("noReferral", true, response.GetAllocator());
							objInformation.AddMember("currentBalance", client->balance, response.GetAllocator());
							objInformation.AddMember("updatedBalance", client->balance + amount, response.GetAllocator());
							objUser.AddMember("info", objInformation, response.GetAllocator());
							strftime(buf, 80, "%Y-%m-%dT%H:%M:%S.000Z", gmtime(&now_t));
							rfc = buf;
							objUser.AddMember("create_at", StringRef(rfc.c_str()), response.GetAllocator());
							objUser.AddMember("finalAmount", amount, response.GetAllocator());
							objUser.AddMember("amount", amount, response.GetAllocator());
							objUser.AddMember("fee", 0, response.GetAllocator());
							if (client->anonymous == 0) objUser.AddMember("username", StringRef(client->login.c_str()), response.GetAllocator());
							else objUser.AddMember("username", StringRef(client->phone.c_str()), response.GetAllocator());
							strftime(buf, 80, "%Y-%m-%dT%H:%M:%S.000Z", gmtime(&now_t));
							rfc = buf;
							objUser.AddMember("id", StringRef((to_string(time(nullptr)) + client->phone).c_str()), response.GetAllocator());
							response.AddMember("transaction", objUser, response.GetAllocator());
							response.Accept(writer);
							//printf("%s", buffer.GetString());


						}
						else {
							response.SetObject();
							response.AddMember("success", false, response.GetAllocator());
							response.Accept(writer);
							//printf("%s", buffer.GetString());

						}







					}

					break;



					case 5: {
						if (document.HasMember("transactionId") == 0 || document["transactionId"].IsString() == 0) { request_select = 0; break; }
						transactionId = document["transactionId"].GetString();

						response.SetObject();
						response.AddMember("success", true, response.GetAllocator());
						response.Accept(writer);



					}
							break;

					case 6:
					{

						if (document.HasMember("id") && document["id"].IsString()) id = document["id"].GetString();
						if (document.HasMember("secret") == 0 || document["secret"].IsString() == 0) { request_select = 0; break; }
						secret = document["secret"].GetString();
						if (document.HasMember("transactionId") == 0 || document["transactionId"].IsString() == 0) { request_select = 0; break; }
						transactionId = document["transactionId"].GetString();


						amount = 1000;
						response.SetObject();
						response.AddMember("success", true, response.GetAllocator());
						objUser.SetObject();
						strftime(buf, 80, "%Y-%m-%dT%H:%M:%S.000Z", gmtime(&now_t));
						string rfc = buf;
						objUser.AddMember("description", StringRef("Setreet adress"), response.GetAllocator());
						objUser.AddMember("cashboxId", StringRef("5811dc83e39fe82034da0da4"), response.GetAllocator());
						objUser.AddMember("type", StringRef("WITHDRAWAL"), response.GetAllocator());
						objUser.AddMember("state", StringRef("Cancelled"), response.GetAllocator());
						objUser.AddMember("currency", StringRef(currency_name[client->currency - 1].c_str()), response.GetAllocator());
						objUser.AddMember("processType", StringRef("no"), response.GetAllocator());
						strftime(buf, 80, "%Y-%m-%dT%H:%M:%S.000Z", gmtime(&now_t));
						rfc = buf;
						objUser.AddMember("create_at", StringRef(rfc.c_str()), response.GetAllocator());
						objUser.AddMember("amount", amount, response.GetAllocator());
						objUser.AddMember("id", StringRef(transactionId.c_str()), response.GetAllocator());
						response.AddMember("transaction", objUser, response.GetAllocator());
						response.Accept(writer);
						//printf("%s", buffer.GetString());



					}
					break;

					case 7:
					{

						if (document.HasMember("id") && document["id"].IsString()) id = document["id"].GetString();
						if (document.HasMember("secret") == 0 || document["secret"].IsString() == 0) { request_select = 0; break; }
						secret = document["secret"].GetString();
						if (document.HasMember("authcode") == 0 || document["authcode"].IsString() == 0) { request_select = 0; break; }
						authcode = document["authcode"].GetString();
						bool logged = false;
						auto it = client_login_hash.find(id);
						if (it == client_login_hash.end()) {
							it = client_phone_hash.find(id);
							if (it == client_phone_hash.end()) { logged = false; }
							else  logged = true;
						}
						else logged = true;
						if (logged == true) client = it->second;
						else {
							auto  it = client_id_hash.find(atoi(id.c_str()));
							if (it == client_id_hash.end()) { logged = false; }
							else { logged = true; client = it->second; }
						}

						if (logged == true) {
							if (client->password != authcode) logged = false;
						}


						if (logged == true) {

							response.SetObject();
							response.AddMember("success", true, response.GetAllocator());
							objUser.SetObject();
							_itoa(client->client_id, buf, 10);
							objUser.AddMember("userId", StringRef(buf), response.GetAllocator());
							response.AddMember("info", objUser, response.GetAllocator());
							response.Accept(writer);
							//printf("%s", buffer.GetString());


						}
						else {
							response.SetObject();
							response.AddMember("success", false, response.GetAllocator());
							response.Accept(writer);
							//printf("%s", buffer.GetString());

						}

					}
					break;

					}





					wsclient->https_write_buffer = new char[2000];
					char* content_html = new char[2000];
					char* headers = new char[500];

					if (request_select == 0) {
						client = client_id_hash.begin()->second;
						response.SetObject();
						response.AddMember("success", true, response.GetAllocator());
						objUser.SetObject();
						_itoa(client->client_id, buf, 10);
						objUser.AddMember("userId", StringRef(buf), response.GetAllocator());
						objUser.AddMember("username", StringRef(client->login.c_str()), response.GetAllocator());
						objUser.AddMember("email", StringRef(client->email.c_str()), response.GetAllocator());
						objUser.AddMember("isTest", false, response.GetAllocator());
						objUser.AddMember("balance", client->balance, response.GetAllocator());
						objInformation.SetObject();
						objInformation.AddMember("gender", "Not specified", response.GetAllocator());
						objInformation.AddMember("firstName", StringRef(client->name.c_str()), response.GetAllocator());
						objInformation.AddMember("lastName", StringRef(client->surname.c_str()), response.GetAllocator());
						objInformation.AddMember("country", StringRef(client->country.c_str()), response.GetAllocator());
						objInformation.AddMember("phone", StringRef(client->phone.c_str()), response.GetAllocator());
						strftime(buf, 80, "%Y-%m-%dT%H:%M:%S.00Z", gmtime(&now_t));
						string rfc = buf;
						objInformation.AddMember("create_at", StringRef(rfc.c_str()), response.GetAllocator());
						_itoa(client->client_id, buf, 10);
						objInformation.AddMember("userId", StringRef(buf), response.GetAllocator());
						objInformation.AddMember("currency", StringRef(currency_name[client->currency - 1].c_str()), response.GetAllocator());
						objInformation.AddMember("isBlocked", false, response.GetAllocator());
						objUser.AddMember("information", objInformation, response.GetAllocator());
						arrayUsers.SetArray();
						arrayUsers.PushBack(objUser, response.GetAllocator());
						response.AddMember("users", arrayUsers, response.GetAllocator());
						response.Accept(writer);
						request_select = 1;
					}


					if (request_select > 0) {
						strcpy(content_html, "\r\n\r\n"); strcat(content_html, buffer.GetString());
						strcpy(headers, "HTTP/1.1 200 OK\r\nVersion: HTTP/1.1\r\nContent-Type: application/json\r\nConnection: close\r\nContent-Length: ");
					}
					else {
						strcpy(content_html, "\r\n\r\n<!DOCTYPE html><html lang = 'en' xmlns = 'http://www.w3.org/1999/xhtml'><head><meta charset = 'utf-8'/><title>Test C++ HTTPS / WebSocket Server</title></head><body><h1>Test C++ HTTPS / WebSocket ServerTest C++ HTTPS / WebSocket ServerTest C++ HTTPS / WebSocket ServerTest C++ HTTPS / WebSocket Server</h1><h2>Test C++ HTTPS / WebSocket ServerTest C++ HTTPS / WebSocket ServerTest C++ HTTPS / WebSocket ServerTest C++ HTTPS / WebSocket Server</h2></body></html>");
						strcpy(headers, "HTTP/1.1 200 OK\r\nVersion: HTTP/1.1\r\nContent-Type: text/html; charset=utf-8\r\nConnection: close\r\nContent-Length: ");
					}
					char* content_length = new char[32];
					_itoa(strlen(content_html) - 4, content_length, 10);
					strcpy(wsclient->https_write_buffer, headers);
					strcat(wsclient->https_write_buffer, content_length);
					strcat(wsclient->https_write_buffer, content_html);
					delete[] content_length;
					delete[] headers;
					delete[] content_html;
					wsclient->https_write_buffer_length = strlen(wsclient->https_write_buffer);

					document.Clear();
					response.Clear();
					objUser.Clear();
					objInformation.Clear();
					arrayUsers.Clear();
					buffer.Clear();

					//if (wsclient->https_buffer != nullptr) delete[] wsclient->https_buffer; 
					wsclient->https_buffer = nullptr;
					if (wsclient->options != nullptr) delete[] wsclient->options; wsclient->options = nullptr;

					wsclient->ready_state = HTTPS_STATE_WRITE;


				}

			}

		}



		status = 0;
		offset = 0;


		if (bprocess_index >= rabbit_index) { new_message_arrived = false; continue; }
		if (DEBUG_OUTPUT == true) std::printf("bprocess_index=%d\r\n", bprocess_index);
		if (DEBUG_OUTPUT == true) std::printf("rabbit_index=%d\r\n", rabbit_index);

		new_message_arrived = true;
		if (DEBUG_OUTPUT == true) std::printf("doc.parse<0>\r\n");
		std::strcpy(maxbuf, AMQP_message[bprocess_index%AMQP_QUEUE]);
		if (DEBUG_OUTPUT == true) std::printf("doc.parse<0> end length=%d\r\n", strlen(AMQP_message[bprocess_index%AMQP_QUEUE]));
		doc.parse<0>(maxbuf); //(AMQP_message[bprocess_index%AMQP_QUEUE]);
		bprocess_index++;
		if (doc.first_node() == nullptr) {
			if (DEBUG_OUTPUT == true) printf("doc null\r\n");
			new_message_arrived = false; continue;
		}

		if (betradar_data_logs == true) {
			write_count_file++;
			std::strcpy(name, "C://Betradar//Sports//");
			_itoa(write_count_file, buf, 10);
			strcat(name, buf);
			strcat(name, doc.first_node()->name());
			_itoa(timestamp() / 1000, buf, 10);
			strcat(name, buf);
			strcat(name, ".xml");
			File = CreateFile(name, GENERIC_WRITE, 0, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
			l = SetFilePointer(File, 0, 0, FILE_BEGIN);
			WriteFile(File, AMQP_message[(bprocess_index - 1) % AMQP_QUEUE], strlen(AMQP_message[(bprocess_index - 1) % AMQP_QUEUE]), &l, nullptr);
			CloseHandle(File);
		}

		ret_fixture = 0;
		if (std::strcmp("fixture_change", doc.first_node()->name()) == 0) {
			if (DEBUG_OUTPUT == true) std::printf("fixture_change\r\n");
			type_radar = 0;
			event_id = 0;
			if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:season:", 10) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 10)); type_radar = 3;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:match:", 9) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
				type_radar = 0;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:simple_tournament:", 21) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 21)); type_radar = 2;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:race_tournament:", 19) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 19)); type_radar = 4;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:match:", 9) == 0) { event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9)); type_radar = 5; continue; }
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:season:", 10) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 10)); type_radar = 6; continue;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:tournament:", 14) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 14)); type_radar = 7; continue;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:stage:", 9) == 0)
			{
				type_radar = 1; event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
				key = "1"+string((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
				if (bevents_id.find(key) != bevents_id.end() && (event_id >= MAX_TOURNAMENTS || btournaments_id[event_id] == nullptr)) type_radar = 1;
				else if (bevents_id.find(key) == bevents_id.end() && event_id < MAX_TOURNAMENTS && btournaments_id[event_id] != nullptr) type_radar = 4;
				else if (bevents_id.find(key) == bevents_id.end() && (event_id >= MAX_TOURNAMENTS || btournaments_id[event_id] == nullptr)) {
					type_radar = -1;
					btournaments[btournaments_l].id = event_id;
					btournaments[btournaments_l].type_radar = 1;
					btournaments[btournaments_l].season_id = 0;
					btournaments[btournaments_l].simple_id = 0;
					if (event_id >= MAX_TOURNAMENTS || getTournament(&btournaments[btournaments_l], false, true) == -1) {

						btournaments[btournaments_l].id = 0; btournaments[btournaments_l].type_radar = 0;
						bevents[bevents_l].id = event_id; bevents[bevents_l].type_radar = 1;
						ret_fixture = getEventFixture(&bevents[bevents_l], true);
						if (ret_fixture == -1) {
							bevents[bevents_l].id = 0; bevents[bevents_l].type_radar = 0;
						}
						else { bevents_l++; type_radar = 1; }
					}
					else { type_radar = 4;  btournaments_l++; }
				}
				if (type_radar == -1) continue;
			}

			else { std::printf("Unknown type radar in fixture_change =%s", (char*)doc.first_node()->first_attribute("event_id")->value()); continue; };
			//0 sr:match://1 sr:race_event(sr:stage) //2 sr:simple_tournament://3 sr:season://4 sr:race_tournament://5 vf:match //6 sr:season: 7 //vf:tournament:
			key = to_string(type_radar) + to_string(event_id);

			if (type_radar == 2) {
				if (event_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nssimple id out of MAX_TOURNAMENTS in run fixture_change %d\r\n", event_id); continue; }
				if (bsimples_id[event_id] == nullptr) {
					std::printf("Simple tournament not found. Run getTournament(). simple_id=%d\r\n", event_id);
					btournaments[btournaments_l].id = 0;
					btournaments[btournaments_l].simple_id = event_id;
					btournaments[btournaments_l].type_radar = 2;
					if (getTournament(&btournaments[btournaments_l], false, true) == -1) { std::printf("ERROR!\r\nTournaments simple id not found in run fixture change simple %d\r\n", event_id); continue; }
					btournaments_l++;

				}
				else if (getTournament(bsimples_id[event_id], false, true) == -1) { std::printf("ERROR!\r\nTournaments simple id not found in run fixture %d\r\n", event_id); continue; }
				std::printf("fixture_change succes for tournamnet simple id=%d\r\n", event_id);


			}
			if (type_radar == 3) {
				if (event_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nsseason id out of MAX_TOURNAMENTS in run fixture change %d\r\n", event_id); continue; }
				if (bseasons_id[event_id] == nullptr || bseasons_id[event_id]->id == 0) {
					std::printf("Tournament not found in run fixture change. Run getTournament(). season_id=%d\r\n", event_id);
					btournaments[btournaments_l].id = 0;
					btournaments[btournaments_l].season_id = event_id;
					btournaments[btournaments_l].type_radar = 0;
					if (getTournament(&btournaments[btournaments_l], false, true) == -1) { std::printf("ERROR!\r\nTournament season id not found in run %d\r\n", event_id); continue; }
					else {
						if (bseasons_id[event_id] == nullptr) {
							std::printf("ERROR!\r\nTournament season id not found after succes in getTournament run %d\r\n", event_id);

							continue;
						}
						btournaments_l++; std::printf("fixture_change succes for tournamnet season id=%d\r\n", event_id);
					}
				}
				else if (getTournament(bseasons_id[event_id], false, true) == -1) { std::printf("ERROR!\r\n getTournament in fixture_change season id =%d\r\n", event_id); continue; }

				std::printf("fixture_change succes for tournamnet season id=%d\r\n", event_id);

			}
			if (type_radar == 4) {
				if (event_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nrace_tournamnet id out of MAX_TOURNAMENTS in run fixture change %d\r\n", event_id); continue; }
				if (btournaments_id[event_id] == nullptr) {
					std::printf("Tournament not found in run fixture change. Run getTournament(). _id=%d\r\n", event_id);
					btournaments[btournaments_l].id = event_id;
					btournaments[btournaments_l].type_radar = 1;
					btournaments[btournaments_l].season_id = 0;
					btournaments[btournaments_l].simple_id = 0;
					if (getTournament(&btournaments[btournaments_l], false, true) == -1) { std::printf("ERROR!\r\nTournament race id not found in run %d\r\n", event_id); continue; }
					else {

						btournaments_l++;
						std::printf("fixture_change succes for race_tournamnet id=%d\r\n", event_id);




					}
				}
				else if (getTournament(btournaments_id[event_id], false, true) == -1) { std::printf("ERROR!\r\n getTournament in fixture_change race_tournamnet id =%d\r\n", event_id); continue; }

				std::printf("fixture_change succes for race_tournamnet id=%d\r\n", event_id);

			}
			if (type_radar == 0 || type_radar ==1 || type_radar == 5) {
				if (bevents_id.find(key) == bevents_id.end()) {
					std::printf("Event not found in fixture_change. %d\r\n", event_id);
					bevents[bevents_l].id = event_id; bevents[bevents_l].type_radar = type_radar;
					ret_fixture = getEventFixture(&bevents[bevents_l], true);
					if (ret_fixture == -1) { std::printf("fixtur_change error. %d\r\n", event_id); bevents[bevents_l].id = 0; bevents[bevents_l].type_radar = 0; continue; }
					else bevents_l++;

				}
				else  ret_fixture = getEventFixture(bevents_id[key], true);
				if (ret_fixture == -1) { std::printf("fixtur_change error. %d\r\n", event_id);  continue; }




				std::printf("fixture_change success. event_id=%d \r\n", event_id);

				//bevents_id[event_key]->bet_stop = 0;







			}

		}
		else if (std::strcmp("odds_change", doc.first_node()->name()) == 0) {
			type_radar = 0;
			event_id = 0;
			type_radar = 0;
			event_id = 0;
			if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:season:", 10) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 10)); type_radar = 3;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:match:", 9) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
				type_radar = 0;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:simple_tournament:", 21) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 21)); type_radar = 2;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:race_tournament:", 19) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 19)); type_radar = 4;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:match:", 9) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9)); type_radar = 5;	
				continue;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:season:", 10) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 10)); type_radar = 6; continue;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:tournament:", 14) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 14)); type_radar = 7; continue;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:stage:", 9) == 0)
			{
				type_radar = 1; event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
				key = "1"+ string((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
				if (bevents_id.find(key) != bevents_id.end() && (event_id >= MAX_TOURNAMENTS || btournaments_id[event_id] == nullptr)) type_radar = 1;
				else if (bevents_id.find(key) == bevents_id.end() && event_id < MAX_TOURNAMENTS && btournaments_id[event_id] != nullptr) type_radar = 4;
				else if (bevents_id.find(key) == bevents_id.end() && (event_id >= MAX_TOURNAMENTS || btournaments_id[event_id] == nullptr)) {
					type_radar = -1;
					btournaments[btournaments_l].id = event_id;
					btournaments[btournaments_l].type_radar = 1;
					btournaments[btournaments_l].season_id = 0;
					btournaments[btournaments_l].simple_id = 0;
					if (event_id >= MAX_TOURNAMENTS || getTournament(&btournaments[btournaments_l], false, true) == -1) {

						btournaments[btournaments_l].id = 0; btournaments[btournaments_l].type_radar = 0;
						bevents[bevents_l].id = event_id; bevents[bevents_l].type_radar = 1;
						ret_fixture = getEventFixture(&bevents[bevents_l], true);
						if (ret_fixture == -1) {
							bevents[bevents_l].id = 0; bevents[bevents_l].type_radar = 0;
						}
						else { bevents_l++; type_radar = 1; }
					}
					else { type_radar = 4;  btournaments_l++; }
				}
				if (type_radar == -1) continue;
			}

			else { std::printf("Unknown type radar in odds_change =%s", (char*)doc.first_node()->first_attribute("event_id")->value()); continue; };

			key = to_string(type_radar) + to_string(event_id);
			_line->type_radar = type_radar;
			_line->key = key;
			//if (_line->event_key != nullptr) delete[] _line->event_key; _line->event_key = nullptr;

			if (event_id == 0) {
				std::printf("event_id error=0\r\n"); std::printf(doc.first_node()->first_attribute("event_id")->value());
				continue;
			}

			if (DEBUG_OUTPUT == true) std::printf("odds_change type_radar=%d\r\n", type_radar);

			if (type_radar == 2) {

				if (event_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nssimple id out of MAX_TOURNAMENTS in run odds_change %d\r\n", event_id); continue; }
				if (bsimples_id[event_id] == nullptr) {
					std::printf("Simple tournament not found. Run getTournament(). simple_id=%d\r\n", event_id);
					btournaments[btournaments_l].id = 0;
					btournaments[btournaments_l].simple_id = event_id;
					btournaments[btournaments_l].type_radar = 2;
					if (getTournament(&btournaments[btournaments_l], false, true) == -1) { std::printf("ERROR!\r\nTournaments simple id not found in run simple %d\r\n", event_id); continue; }
					btournaments_l++;

				}

				if (bsimples_id[event_id] == nullptr) { std::printf("ERROR!\r\nTournaments simple id not found after succes in getTournament run simple %d\r\n", event_id); continue; }
				_tournament = bsimples_id[event_id];

				if (_tournament->end_date == 0) {
					if (getTournament(_tournament, false, true) == -1)  std::printf("ERROR!\r\nTournaments simple id not found in run simple for change end_date %d\r\n", event_id);
					else std::printf("\r\nTournaments simple id change end_date succes%d\r\n", event_id);
				}


				if (_tournament->sport_id >= MAX_SPORTS) { std::printf("ERROR DATA!\r\nstournament sport_id out of MAX_SPORTS in run simple%d\r\n", _tournament->sport_id); continue; }

				if (bsports_id[_tournament->sport_id] == nullptr) { std::printf("Sport not found in run simple. Run getSports. sport_id=%d\r\n", _tournament->sport_id); getSports(true); }



				if (PRINT == true) {
					std::printf("\r\n***************************************************\r\n");
					std::printf("Simple id: %d\r\n", event_id);
					std::printf("NAME:"); std::printf(_tournament->name);
					std::printf("\r\n");
				}

				//std::sprintf(socket_message_little, "\r\n***************************************************\r\n");
				/*
				std::strcat(socket_message_big, socket_message_little);
				std::sprintf(socket_message_little, "Simple id: %d\r\n", event_id);
				std::strcat(socket_message_big, socket_message_little);
				std::sprintf(socket_message_little, "NAME:");
				std::strcat(socket_message_big, socket_message_little);
				std::sprintf(socket_message_little, "\r\n");
				*/




				if (PRINT == true) {
					std::printf(bsports_id[_tournament->sport_id]->name); std::printf("\r\n");
				}
				//std::strcat(socket_message_big, bsports_id[_tournament->sport_id]->name);
				//std::strcat(socket_message_big, "\r\n");



				if (_tournament->category_id >= MAX_CATEGORIES) { std::printf("ERROR DATA!\r\ntournament category_id out of MAX_CATEGORIES in run simple %d\r\n", _tournament->category_id); continue; }
				if (bcategories_id[_tournament->category_id] == nullptr) {
					std::printf("Category not found. Run getTournament(). category_id=%d\r\n", _tournament->category_id);
					if (getTournament(bsimples_id[_tournament->simple_id], false, true) == -1);  continue;
				}
				bcategories_id[_tournament->category_id]->outrights = 1;
				if (PRINT == true) {
					std::printf(bcategories_id[_tournament->category_id]->name); std::printf("\r\n");
					std::printf("\r\n***************************************************\r\n");
				}
				////std::sprintf(socket_message_little, "\r\n***************************************************\r\n");
				//std::strcat(socket_message_big, bcategories_id[_tournament->category_id]->name);
				//std::strcat(socket_message_big, "\r\n\r\n***************************************************\r\n");




				xml_node<> * odds = doc.first_node()->first_node("odds");

				if (odds != nullptr) {
					betstop_reason = 0;
					if (odds->first_attribute("betstop_reason")) betstop_reason = atoi(odds->first_attribute("betstop_reason")->value());
					_line->tournament_id = 0;
					_line->event_id = 0;
					_line->simple_id = _tournament->simple_id;
					_line->season_id = 0;
					//_line->betstop_reason = betstop_reason;

					for (xml_node<> * market_node = odds->first_node("market"); market_node; market_node = market_node->next_sibling())
					{
						outcomeNameError = 0;
						if (market_node->first_attribute("next_betstop")) _line->next_betstop = atoi(market_node->first_attribute("next_betstop")->value());
						if (market_node->first_node("market_metadata") && market_node->first_node("market_metadata")->first_attribute("next_betstop")) _line->next_betstop = atoi(market_node->first_node("market_metadata")->first_attribute("next_betstop")->value());
						//printf("_line->next_betstop=%d\r\n", _line->next_betstop);


						if (market_node->first_attribute("favourite")) _line->favourite = atoi(market_node->first_attribute("favourite")->value());
						if (market_node->first_attribute("status")) _line->status = atoi(market_node->first_attribute("status")->value());
						if (market_node->first_attribute("id")) _line->market_id = atoi(market_node->first_attribute("id")->value());
						if (_line->market_id >= MAX_MARKETS) {
							std::printf("ERROR DATA!\r\nmarket id out of MAX_MARKETS in run%d\r\n", _line->market_id); continue;
						}
						if (bmarkets_id[_line->market_id] == nullptr) {
							std::printf("ERROR DATA!\r\nmarket id not found in run%d\r\n", _line->market_id); continue;
						};
						if (bmarkets_id[_line->market_id][0] == nullptr) {
							std::printf("ERROR DATA!\r\nmarket id 0 not found in run%d\r\n", _line->market_id); continue;
						};
						_line->variant = bmarkets_id[_line->market_id][0]->variant;
						_line->type = bmarkets_id[_line->market_id][0]->type;
						if (_line->specifier_number > 0) for (q = 0; q < _line->specifier_number; q++) {
							if (_line->specifier[q] != nullptr) delete[] _line->specifier[q]; _line->specifier[q] = nullptr;
							if (_line->specifier_value[q] != nullptr)  delete[] _line->specifier_value[q]; _line->specifier_value[q] = nullptr;
						}
						if (_line->specifier != nullptr) { delete[] _line->specifier; _line->specifier = nullptr; }
						if (_line->specifier_value != nullptr) { delete[] _line->specifier_value; _line->specifier_value = nullptr; }
						_line->specifier_number = 0;
						if (_line->extended_specifier_number > 0) for (q = 0; q < _line->extended_specifier_number; q++) {
							if (_line->extended_specifier[q] != nullptr) delete[] _line->extended_specifier[q];
							if (_line->extended_specifier_value[q] != nullptr)  delete[] _line->extended_specifier_value[q];
						}
						if (_line->extended_specifier != nullptr) { delete[] _line->extended_specifier; _line->extended_specifier = nullptr; }
						if (_line->extended_specifier_value != nullptr) { delete[] _line->extended_specifier_value; _line->extended_specifier_value = nullptr; }
						_line->extended_specifier_number = 0;
						if (market_node->first_attribute("specifiers")) {
							n = 0;
							m = market_node->first_attribute("specifiers")->value_size();
							for (q = 0; q < m; q++) {
								if (market_node->first_attribute("specifiers")->value()[q] == '=')
									index_equally[n] = q;

								if (market_node->first_attribute("specifiers")->value()[q] == '|') {
									index_separator[n] = q; n++;
								}

							}
							index_separator[n] = q; n++;




							_line->specifier_number = n;
							if (_line->specifier_number > 0) {
								_line->specifier_value = new char*[_line->specifier_number];
								_line->specifier = new char*[_line->specifier_number];


								for (q = 0; q < _line->specifier_number; q++) {
									if (q > 0) {
										_line->specifier[q] = new char[index_equally[q] - index_separator[q - 1]];
										strncpy(_line->specifier[q], (char*)((char*)market_node->first_attribute("specifiers")->value() + index_separator[q - 1]) + 1, index_equally[q] - index_separator[q - 1] - 1);
										_line->specifier[q][index_equally[q] - index_separator[q - 1] - 1] = 0;
									}
									else {
										_line->specifier[q] = new char[index_equally[q] + 1]; strncpy(_line->specifier[q], market_node->first_attribute("specifiers")->value(), index_equally[q]); _line->specifier[q][index_equally[q]] = 0;


									}

									_line->specifier_value[q] = new char[index_separator[q] - index_equally[q]];
									strncpy(_line->specifier_value[q], (char*)((char*)market_node->first_attribute("specifiers")->value() + index_equally[q]) + 1, index_separator[q] - index_equally[q] - 1);
									_line->specifier_value[q][index_separator[q] - index_equally[q] - 1] = 0;



								}
							}
						}
						if (market_node->first_attribute("extended_specifiers")) {
							n = 0;
							m = market_node->first_attribute("extended_specifiers")->value_size();
							for (q = 0; q < m; q++) {
								if (market_node->first_attribute("extended_specifiers")->value()[q] == '=')
									index_equally[n] = q;

								if (market_node->first_attribute("extended_specifiers")->value()[q] == '|') {
									index_separator[n] = q; n++;
								}

							}
							index_separator[n] = q; n++;



							_line->extended_specifier_number = n;
							if (_line->extended_specifier_number > 0) {
								_line->extended_specifier_value = new char*[_line->extended_specifier_number];
								_line->extended_specifier = new char*[_line->extended_specifier_number];


								for (q = 0; q < _line->extended_specifier_number; q++) {
									if (q > 0) {
										_line->extended_specifier[q] = new char[index_equally[q] - index_separator[q - 1]];
										strncpy(_line->extended_specifier[q], (char*)((char*)market_node->first_attribute("extended_specifiers")->value() + index_separator[q - 1]) + 1, index_equally[q] - index_separator[q - 1] - 1);
										_line->extended_specifier[q][index_equally[q] - index_separator[q - 1] - 1] = 0;
									}
									else {
										_line->extended_specifier[q] = new char[index_equally[q] + 1]; strncpy(_line->extended_specifier[q], market_node->first_attribute("extended_specifiers")->value(), index_equally[q]); _line->extended_specifier[q][index_equally[q]] = 0;


									}

									_line->extended_specifier_value[q] = new char[index_separator[q] - index_equally[q]];
									strncpy(_line->extended_specifier_value[q], (char*)((char*)market_node->first_attribute("extended_specifiers")->value() + index_equally[q]) + 1, index_separator[q] - index_equally[q] - 1);
									_line->extended_specifier_value[q][index_separator[q] - index_equally[q] - 1] = 0;
									//printf(_line->extended_specifier[q]);std::printf("\r\n");std::printf(_line->extended_specifier_value[q]);std::printf("\r\n");


								}
							}
						}


					outcomeNameError1:
						if (_line->variant > -1) {
							z = strlen(_line->specifier_value[_line->variant]) + 1; if (strcmp(_line->specifier[_line->variant], "variant") != 0) { std::printf(_line->specifier[_line->variant]); std::printf("\r\n"); }


							for (u = 0; u < bmax_markets_in[_line->market_id]; u++) if (bmarkets_id[_line->market_id][u] != nullptr && bmarkets_id[_line->market_id][u]->variable_text != nullptr && std::strcmp(_line->specifier_value[_line->variant], bmarkets_id[_line->market_id][u]->variable_text) == 0) break;
							if (outcomeNameError == 1 || u == bmax_markets_in[_line->market_id]) {
								std::printf("Variant market1 not found in run market_id=%d variant=", _line->market_id);  std::printf(_line->specifier_value[_line->variant]);  std::printf(" getVariantMarket\r\n"); if (getVariantMarket(bmarkets_id[_line->market_id][0], _line->specifier_value[_line->variant], true) == -1) { std::printf("variant market not found "); continue; }
								for (u = 0; u < bmax_markets_in[_line->market_id]; u++) if (bmarkets_id[_line->market_id][u] != nullptr && bmarkets_id[_line->market_id][u]->variable_text != nullptr && std::strcmp(_line->specifier_value[_line->variant], bmarkets_id[_line->market_id][u]->variable_text) == 0) break;
							}
							_market = bmarkets_id[_line->market_id][u];
							if (outcomeNameError == 1)outcomeNameError = 2;

							if (_line->type == 3) z = 16;
						}
						else { _market = bmarkets_id[_line->market_id][0]; if (_line->type == 0) z = 0; else if (_line->type == 1) z = 10; else if (_line->type == 2) z = 14; else if (_line->type == 3) z = 16; }
						outcome_number = 0;

						if (_line->outcome_number > 0) { for (int i = 0; i < _line->outcome_number; i++) if (_line->outcome_name[i] != nullptr) delete[] _line->outcome_name[i]; };
						_line->outcome_number = 0;

						if (_line->outcome_id != nullptr) delete[] _line->outcome_id; if (_line->outcome_active != nullptr) delete[] _line->outcome_active; if (_line->outcome_team != nullptr) delete[] _line->outcome_team; if (_line->outcome_odds != nullptr) delete[] _line->outcome_odds;
						if (_line->outcome_probabilities != nullptr) delete[] _line->outcome_probabilities; if (_line->outcome_name != nullptr) delete[] _line->outcome_name;
						_line->outcome_probabilities = nullptr; _line->outcome_name = nullptr; _line->outcome_id = nullptr; _line->outcome_odds = nullptr; _line->outcome_active = nullptr;
						_line->outcome_team = nullptr;


						if (_line->name != nullptr) delete[] _line->name;


						_line->name = new char[strlen(_market->name) + 1];
						std::strcpy(_line->name, _market->name);
						for (int i = 0; i < _line->specifier_number; i++) {
							if (i == _line->variant) continue;

							replace(_line->name, _line->specifier[i], _line->specifier_value[i], true);
						}
						if (bsimples_id[_line->simple_id]->name != nullptr) replace(_line->name, "$event", bsimples_id[_line->simple_id]->name, true);

						for (xml_node<> * outcome_node = market_node->first_node("outcome"); outcome_node; outcome_node = outcome_node->next_sibling()) {


							if (outcome_node->first_attribute("active")) outcome_active[outcome_number] = atoi(outcome_node->first_attribute("active")->value());
							else outcome_active[outcome_number] = 0;
							if (outcome_node->first_attribute("team")) outcome_team[outcome_number] = atoi(outcome_node->first_attribute("team")->value());
							else outcome_team[outcome_number] = 0;
							if (outcome_node->first_attribute("id")) {
								outcome_id[outcome_number] = atoi((char*)((char*)outcome_node->first_attribute("id")->value() + z));
								if (outcome_id[outcome_number] == 0 && z > 0) {
									outcome_id[outcome_number] = atoi(outcome_node->first_attribute("id")->value());
									if (outcome_id[outcome_number] > 0) outcome_team[outcome_number] = 3;
									else {
										std::printf("_line->type=%d line->market_id=%d  _tournament->type_radar=%d  _line->simple_id =%d \r\n", _line->type, _line->market_id, _tournament->type_radar, _line->simple_id); std::printf(outcome_node->first_attribute("id")->value());

									}
								}

							}
							else outcome_id[outcome_number] = 0;


							if (outcome_node->first_attribute("odds")) outcome_odds[outcome_number] = atof(outcome_node->first_attribute("odds")->value());
							else outcome_odds[outcome_number] = 0;
							if (outcome_node->first_attribute("probabilities")) outcome_probabilities[outcome_number] = atof(outcome_node->first_attribute("probabilities")->value());
							else outcome_probabilities[outcome_number] = 0;
							if (outcome_name[outcome_number] != nullptr) delete[] outcome_name[outcome_number]; outcome_name[outcome_number] = nullptr;
							if (outcome_node->first_attribute("name")) {
								outcome_name[outcome_number] = new char[strlen(outcome_node->first_attribute("name")->value()) + 1];
								std::strcpy(outcome_name[outcome_number], outcome_node->first_attribute("name")->value());

							}

							outcome_number++;

						}






						if (PRINT == true) {

							std::printf("\r\n"); std::printf(_line->name); std::printf("\r\n"); std::printf("------------------------------------------------------------------------------\r\n");
						}

						////std::sprintf(socket_message_little, "\r\n***************************************************\r\n");
						//std::strcat(socket_message_big, "\r\n");
						//std::strcat(socket_message_big, _line->name);
						//std::strcat(socket_message_big, "\r\n------------------------------------------------------------------------------\r\n");





						_line->outcome_number = outcome_number;
						if (_line->outcome_number > 0) {
							_line->outcome_name = new char*[_line->outcome_number];
							_line->outcome_id = new int[_line->outcome_number];
							_line->outcome_team = new int[_line->outcome_number];
							_line->outcome_active = new int[_line->outcome_number];
							_line->outcome_probabilities = new float[_line->outcome_number];
							_line->outcome_odds = new float[_line->outcome_number];






							for (int i = 0; i < _line->outcome_number; i++) {
								_line->outcome_name[i] = nullptr;
								_line->outcome_id[i] = outcome_id[i];
								_line->outcome_active[i] = outcome_active[i];
								_line->outcome_odds[i] = outcome_odds[i];
								_line->outcome_team[i] = outcome_team[i];
								_line->outcome_probabilities[i] = outcome_probabilities[i];


								if (_line->type == 0) {
									if (_line->outcome_id[i] == _market->outcome_id[i]) u = i;
									else
										for (u = 0; u < _market->outcome_number; u++) if (_line->outcome_id[i] == _market->outcome_id[u]) break;

									if (u < _market->outcome_number) {
										_line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
										std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);

									}
									else {
										std::printf("Eror. Outcome name not found. market_id=%d _line->outcome_id[i]=%d GoTo GetVarianMarket \r\n", _line->market_id, _line->outcome_id[i]);
										_line->outcome_name[i] = new char[2];
										std::strcpy(_line->outcome_name[i], " ");
										if (_market->variant > -1) printf("_market->variant=%s\r\n", _market->variable_text);
										if (outcomeNameError == 0) outcomeNameError = 1;


									}

									for (int j = 0; j < _line->specifier_number; j++) {
										if (j == _line->variant) continue;

										replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j], true);
									}

									if (bsimples_id[_line->simple_id]->name != nullptr) replace(_line->outcome_name[i], "$event", bsimples_id[_line->simple_id]->name, true);



									if (PRINT == true) {

										std::printf(_line->outcome_name[i]); std::printf("\t");
										std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
										std::printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									}
									////std::sprintf(socket_message_little, "\r\n***************************************************\r\n");
									/*
									std::strcat(socket_message_big, _line->outcome_name[i]);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
									std::strcat(socket_message_big, socket_message_little);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									std::strcat(socket_message_big, socket_message_little);*/




								}

								if (_line->type == 1) {
									if (_line->outcome_id[i] >= MAX_PLAYERS) {
										std::printf("ERROR in run. player_id out of MAX_PLAYERS. _line->outcome_id[i]=%d  _line->market_id=%d simple_id=%d\r\n", _line->outcome_id[i], _line->market_id, _line->simple_id);
										continue;

									}
									if (_line->outcome_team[i] != 3) {
										if (bplayers_id[_line->outcome_id[i]] == nullptr) {
											std::printf("Player2 id=%d not found in market id=%d in simple_id=%d  in run function . getPlayer\r\n", _line->outcome_id[i], _line->market_id, _line->simple_id);
											bplayers[bplayers_l].id = _line->outcome_id[i]; if (getPlayer(&bplayers[bplayers_l], true) == -1)
											{
												std::printf("error player id=%d  not found \r\n ", _line->outcome_id[i]); //continue;
												_line->outcome_name[i] = new char[2];
												std::strcpy(_line->outcome_name[i], " ");
											}
											else bplayers_l++;
										}

										if (_line->outcome_name[i] == nullptr) {
											_line->outcome_name[i] = new char[strlen(bplayers_id[_line->outcome_id[i]]->name) + 1];
											std::strcpy(_line->outcome_name[i], bplayers_id[_line->outcome_id[i]]->name);
										}

									}

									if (_line->outcome_team[i] == 3) {

										for (u = 0; u < _market->outcome_number; u++) if (_market->outcome_id[u] == _line->outcome_id[i]) break;
										if (u < _market->outcome_number) {
											_line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
											std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);

											for (int j = 0; j < _line->specifier_number; j++) {
												if (j == _line->variant) continue;
												replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j], true);
											}

											if (bsimples_id[_line->simple_id]->name != nullptr)	replace(_line->outcome_name[i], "$event", bsimples_id[_line->simple_id]->name);




										}
										else {
											_line->outcome_name[i] = new char[2];
											std::strcpy(_line->outcome_name[i], " ");
										}



									}





									if (PRINT == true) {



										std::printf(_line->outcome_name[i]); std::printf("\t");
										std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
										printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									}
									/*
									std::strcat(socket_message_big, _line->outcome_name[i]);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
									std::strcat(socket_message_big, socket_message_little);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									std::strcat(socket_message_big, socket_message_little);*/






								}

								if (_line->type == 2) {
									if (_line->outcome_team[i] != 3) {
										if (_line->outcome_id[i] >= MAX_COMPETITORS) {
											std::printf("ERROR in run. competitor_id out of MAX_COMPETITORS. _line->outcome_id[i]=%d  _line->market_id=%d simple_id=%d\r\n", _line->outcome_id[i], _line->market_id, _tournament->simple_id);
											continue;
										}
										if (bcompetitors_id[_line->outcome_id[i]] == nullptr) {
											std::printf("Competitor id=%d not found in market id=%d in tournament_simple_id=%d  in run simple. getTournament\r\n", _line->outcome_id[i], _line->market_id, _tournament->simple_id);
											if (getTournament(bsimples_id[_tournament->simple_id], false, true) == -1)
												std::printf("ERROR!\r\nTournaments not found in run simple %d \r\n", _tournament->simple_id);
										}

										if (bcompetitors_id[_line->outcome_id[i]] == nullptr) {
											std::printf("\r\nCompetitors id=%d not found in tournament simple_id=%d after getTournament . Run getCompetitor\r\n", _line->outcome_id[i], _tournament->simple_id);
											bcompetitors[bcompetitors_l].id = _line->outcome_id[i];
											if (getCompetitor(&bcompetitors[bcompetitors_l], true) == -1) {
												std::printf(" Error getCompetitor in run simple. line type= 2 id competitor=%d \r\n", _line->outcome_id[i]);
												_line->outcome_name[i] = new char[2];
												std::strcpy(_line->outcome_name[i], " ");
											}
											else bcompetitors_l++;
										}

										if (bcompetitors_id[_line->outcome_id[i]] != nullptr) { _line->outcome_name[i] = new char[strlen(bcompetitors_id[_line->outcome_id[i]]->name) + 1]; std::strcpy(_line->outcome_name[i], bcompetitors_id[_line->outcome_id[i]]->name); }

									}
									else
									{
										for (u = 0; u < _market->outcome_number; u++) if (_market->outcome_id[u] == _line->outcome_id[i]) break;
										if (u < _market->outcome_number) {
											_line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
											std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);
											for (int j = 0; j < _line->specifier_number; j++) {
												if (j == _line->variant) continue;
												replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j], true);
											}

											if (_tournament->name != nullptr) replace(_line->outcome_name[i], "$event", bsimples_id[_line->simple_id]->name, true);
										}
										else { _line->outcome_name[i] = new char[2]; std::strcpy(_line->outcome_name[i], " "); }
									}
									if (PRINT == true) {
										std::printf(_line->outcome_name[i]); std::printf("\t");
										std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
										printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									}
									/*
									std::strcat(socket_message_big, _line->outcome_name[i]);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
									std::strcat(socket_message_big, socket_message_little);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									std::strcat(socket_message_big, socket_message_little);*/




								}

								if (_line->type == 3 || _line->type == 4) {

									if (_line->outcome_id[i] == _market->outcome_id[i]) u = i;
									else
										for (u = 0; u < _market->outcome_number; u++) {


											if (_line->outcome_id[i] == _market->outcome_id[u]) break;
										}

									if (u < _market->outcome_number) {

										_line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
										std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);

									}
									else {
										std::printf("Eror. Outcome name not found. market_id=%d _line->outcome_id[i]=%d\r\n", _line->market_id, _line->outcome_id[i]);

										_line->outcome_name[i] = new char[2];
										std::strcpy(_line->outcome_name[i], " ");
										if (outcomeNameError == 0) outcomeNameError = 1;
										if (_market->variant > -1)
											printf("_market->variant=%s\r\n", _market->variable_text);

									}

									for (int j = 0; j < _line->specifier_number; j++) {
										if (j == _line->variant) continue;

										replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j], true);
									}

									if (_tournament->name) replace(_line->outcome_name[i], "$event", bsimples_id[_line->simple_id]->name, true);


									//if (_line->market_id == 188 || _line->market_id == 224 || _line->market_id == 485 || _line->market_id == 231 || _line->market_id == 65 || _line->market_id == 383 || _line->market_id == 66) 

									if (PRINT == true) {

										std::printf(_line->outcome_name[i]); std::printf("\t");
										std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
										printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									}
									/*
									std::strcat(socket_message_big, _line->outcome_name[i]);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
									std::strcat(socket_message_big, socket_message_little);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									std::strcat(socket_message_big, socket_message_little);*/
								}
							}


							if (outcomeNameError == 1 && _market->variant > -1) goto outcomeNameError1;
						}



						if (DEBUG_OUTPUT == true) printf("insertLine _line->type ==%d\r\n", _line->type);

						auto it = bcompound2line_index.find(_line ->getCompoundKey());
						if (DEBUG_OUTPUT == true) {
							printf(_line ->getCompoundKey().c_str());
							printf("\r\n");
						}
						if (it == bcompound2line_index.end()) {
							if (DEBUG_OUTPUT == true) printf("new line add");
							_line->id = blines_l;
							if (DEBUG_OUTPUT == true) printf("new line add1");
							blines[blines_l] = (*_line);
							blines_id[_line->id] = &blines[blines_l];
							if (DEBUG_OUTPUT == true) printf("new line add2");
							binsert_line(_line, blines_l);
							if (DEBUG_OUTPUT == true) printf("new line add3");
							blines_l++;
							bcategories_id[_tournament->category_id]->outrights_id.push_back(_line->id);
							if (DEBUG_OUTPUT == true) printf("new line add finish");

						}
						else {
							if (DEBUG_OUTPUT == true) printf("line update");
							_line->id = it->second;
							if (DEBUG_OUTPUT == true) printf("line update1");
							blines[it->second] = (*_line);
							if (DEBUG_OUTPUT == true) printf("line finish");

							//printf("Line Update\r\n");
						}









						if (DEBUG_OUTPUT == true) printf("end insertLine _line->type ==%d\r\n", _line->type);















					}
				}


			}
			if (type_radar == 3 || type_radar == 4) {

				if (event_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nsseason/race_tournament id out of MAX_TOURNAMENTS in run %d\r\n", event_id); continue; }
				if ((type_radar == 3 && (bseasons_id[event_id] == nullptr || bseasons_id[event_id]->id == 0)) || (type_radar == 4 && btournaments_id[event_id] == nullptr)) {
					std::printf("Tournament not found. Run getTournament(). season_id/race_tournament=%d\r\n", event_id);
					if (type_radar == 3) {
						btournaments[btournaments_l].id = 0;
						btournaments[btournaments_l].season_id = event_id;
						btournaments[btournaments_l].type_radar = 0;
						btournaments[btournaments_l].simple_id = 0;
					}

					if (type_radar == 4) {
						btournaments[btournaments_l].id = event_id;
						btournaments[btournaments_l].season_id = 0;
						btournaments[btournaments_l].type_radar = 0;
						btournaments[btournaments_l].simple_id = 0;
					}


					if (getTournament(&btournaments[btournaments_l], false, true) == -1) { std::printf("ERROR!\r\nTournaments season/race_tornament id not found in run season/race_tournaments %d\r\n", event_id); continue; }
					else btournaments_l++;
				}

				if (type_radar == 3) {
					if (bseasons_id[event_id] == nullptr) { std::printf("ERROR!\r\nTournaments season/race_tournament id not found after succes in getTournament run season/race_tornament %d type_radr\r\n", event_id, type_radar); continue; }
					_tournament = bseasons_id[event_id];
				} if (type_radar == 4) _tournament = btournaments_id[event_id];

				if (_tournament->end_date == 0) {
					if (getTournament(_tournament, false, true) == -1)  std::printf("ERROR!\r\nTournaments simple id not found in run simple for change end_date %d\r\n", event_id);
					else std::printf("\r\nTournaments simple id change end_date succes%d\r\n", event_id);
				}



				if (_tournament->sport_id >= MAX_SPORTS) { std::printf("ERROR DATA!\r\nstournament sport_id out of MAX_SPORTS in run season/race_tournaments%d\r\n", _tournament->sport_id); continue; }

				if (bsports_id[_tournament->sport_id] == nullptr) { std::printf("Sport not found in run season/race_tournaments. Run getSports. sport_id=%d\r\n", _tournament->sport_id); getSports(true); }






				if (PRINT == true) {
					std::printf("\r\n***************************************************\r\n");
					std::printf("Season id: %d\r\n", event_id);
					std::printf("Tournament id:%d\r\n", _tournament->id);
					std::printf("NAME:"); std::printf(_tournament->name);
					std::printf("\r\nSEASON:"); if (_tournament->season_name != nullptr) std::printf(_tournament->season_name); else std::printf(_tournament->name);
					std::printf("\r\n");
				}

				//std::strcat(socket_message_big, "\r\n***************************************************\r\n");
				/*
				std::sprintf(socket_message_little, "Season id: %d\r\n", event_id);
				std::strcat(socket_message_big, socket_message_little);
				std::sprintf(socket_message_little, "Tournament id:%d\r\n", _tournament->id);
				std::strcat(socket_message_big, socket_message_little);
				std::strcat(socket_message_big, "NAME:");
				std::strcat(socket_message_big, _tournament->name);
				std::strcat(socket_message_big, "\r\nSEASON:");
				if (_tournament->season_name != nullptr) std::strcat(socket_message_big, _tournament->season_name);
				else std::strcat(socket_message_big, _tournament->name);
				std::strcat(socket_message_big, "\r\n");*/



				if (PRINT == true) {
					std::printf(bsports_id[_tournament->sport_id]->name); std::printf("\r\n");
				}
				////std::strcat(socket_message_big, bsports_id[_tournament->sport_id]->name);
				////std::strcat(socket_message_big, "\r\n");



				if (_tournament->category_id >= MAX_CATEGORIES) { std::printf("ERROR DATA!\r\ntournament category_id out of MAX_CATEGORIES in run season/race_tournaments %d\r\n", _tournament->category_id); continue; }
				if (bcategories_id[_tournament->category_id] == nullptr) {
					std::printf("Category not found. Run getTournament(). category_id=%d\r\n", _tournament->category_id);
					if (getTournament(btournaments_id[_tournament->id], false, true) == -1);  continue;

				}
				bcategories_id[_tournament->category_id]->outrights = 1;
				if (PRINT == true) {
					std::printf(bcategories_id[_tournament->category_id]->name); std::printf("\r\n");
					std::printf("\r\n***************************************************\r\n");
				}

				////std::sprintf(socket_message_little, "Season id: %d\r\n", event_id);
				//std::strcat(socket_message_big, bcategories_id[_tournament->category_id]->name);
				//std::strcat(socket_message_big, "\r\n");





				xml_node<> * odds = doc.first_node()->first_node("odds");

				if (odds != nullptr) {
					betstop_reason = 0;

					if (odds->first_attribute("betstop_reason")) betstop_reason = atoi(odds->first_attribute("betstop_reason")->value());
					_line->tournament_id = _tournament->id;
					_line->event_id = 0;
					_line->simple_id = 0;
					if (type_radar == 3) _line->season_id = event_id;
					//_line->betstop_reason = betstop_reason;

					for (xml_node<> * market_node = odds->first_node("market"); market_node; market_node = market_node->next_sibling())
					{
						outcomeNameError = 0;
						if (market_node->first_attribute("next_betstop")) _line->next_betstop = atoi(market_node->first_attribute("next_betstop")->value());
						if (market_node->first_node("market_metadata") && market_node->first_node("market_metadata")->first_attribute("next_betstop")) _line->next_betstop = atoi(market_node->first_node("market_metadata")->first_attribute("next_betstop")->value());
						if (market_node->first_attribute("favourite")) _line->favourite = atoi(market_node->first_attribute("favourite")->value());
						if (market_node->first_attribute("status")) _line->status = atoi(market_node->first_attribute("status")->value());
						if (market_node->first_attribute("id")) _line->market_id = atoi(market_node->first_attribute("id")->value());
						if (_line->market_id >= MAX_MARKETS) {
							std::printf("ERROR DATA!\r\nmarket id out of MAX_MARKETS in run%d\r\n", _line->market_id); continue;
						}
						if (bmarkets_id[_line->market_id] == nullptr) {
							std::printf("ERROR DATA!\r\nmarket id not found in run%d\r\n", _line->market_id); continue;
						};
						if (bmarkets_id[_line->market_id][0] == nullptr) {
							std::printf("ERROR DATA!\r\nmarket id 0 not found in run%d\r\n", _line->market_id); continue;
						};
						_line->variant = bmarkets_id[_line->market_id][0]->variant;
						_line->type = bmarkets_id[_line->market_id][0]->type;
						if (_line->specifier_number > 0) for (q = 0; q < _line->specifier_number; q++) {
							if (_line->specifier[q] != nullptr) delete[] _line->specifier[q]; _line->specifier[q] = nullptr;;
							if (_line->specifier_value[q] != nullptr)  delete[] _line->specifier_value[q]; _line->specifier_value[q] = nullptr;
						}
						if (_line->specifier != nullptr) { delete[] _line->specifier; _line->specifier = nullptr; }
						if (_line->specifier_value != nullptr) { delete[] _line->specifier_value; _line->specifier_value = nullptr; }
						_line->specifier_number = 0;
						if (_line->extended_specifier_number > 0) for (q = 0; q < _line->extended_specifier_number; q++) {
							if (_line->extended_specifier[q] != nullptr) delete[] _line->extended_specifier[q];
							if (_line->extended_specifier_value[q] != nullptr)  delete[] _line->extended_specifier_value[q];
						}
						if (_line->extended_specifier != nullptr) { delete[] _line->extended_specifier; _line->extended_specifier = nullptr; }
						if (_line->extended_specifier_value != nullptr) { delete[] _line->extended_specifier_value; _line->extended_specifier_value = nullptr; }
						_line->extended_specifier_number = 0;
						if (market_node->first_attribute("specifiers")) {
							n = 0;
							m = market_node->first_attribute("specifiers")->value_size();
							for (q = 0; q < m; q++) {
								if (market_node->first_attribute("specifiers")->value()[q] == '=')
									index_equally[n] = q;

								if (market_node->first_attribute("specifiers")->value()[q] == '|') {
									index_separator[n] = q; n++;
								}

							}
							index_separator[n] = q; n++;




							_line->specifier_number = n;
							if (_line->specifier_number > 0) {
								_line->specifier_value = new char*[_line->specifier_number];
								_line->specifier = new char*[_line->specifier_number];


								for (q = 0; q < _line->specifier_number; q++) {
									if (q > 0) {
										_line->specifier[q] = new char[index_equally[q] - index_separator[q - 1]];
										strncpy(_line->specifier[q], (char*)((char*)market_node->first_attribute("specifiers")->value() + index_separator[q - 1]) + 1, index_equally[q] - index_separator[q - 1] - 1);
										_line->specifier[q][index_equally[q] - index_separator[q - 1] - 1] = 0;
									}
									else {
										_line->specifier[q] = new char[index_equally[q] + 1]; strncpy(_line->specifier[q], market_node->first_attribute("specifiers")->value(), index_equally[q]); _line->specifier[q][index_equally[q]] = 0;


									}

									_line->specifier_value[q] = new char[index_separator[q] - index_equally[q]];
									strncpy(_line->specifier_value[q], (char*)((char*)market_node->first_attribute("specifiers")->value() + index_equally[q]) + 1, index_separator[q] - index_equally[q] - 1);
									_line->specifier_value[q][index_separator[q] - index_equally[q] - 1] = 0;



								}
							}
						}
						if (market_node->first_attribute("extended_specifiers")) {
							n = 0;
							m = market_node->first_attribute("extended_specifiers")->value_size();
							for (q = 0; q < m; q++) {
								if (market_node->first_attribute("extended_specifiers")->value()[q] == '=')
									index_equally[n] = q;

								if (market_node->first_attribute("extended_specifiers")->value()[q] == '|') {
									index_separator[n] = q; n++;
								}

							}
							index_separator[n] = q; n++;



							_line->extended_specifier_number = n;
							if (_line->extended_specifier_number > 0) {
								_line->extended_specifier_value = new char*[_line->extended_specifier_number];
								_line->extended_specifier = new char*[_line->extended_specifier_number];


								for (q = 0; q < _line->extended_specifier_number; q++) {
									if (q > 0) {
										_line->extended_specifier[q] = new char[index_equally[q] - index_separator[q - 1]];
										strncpy(_line->extended_specifier[q], (char*)((char*)market_node->first_attribute("extended_specifiers")->value() + index_separator[q - 1]) + 1, index_equally[q] - index_separator[q - 1] - 1);
										_line->extended_specifier[q][index_equally[q] - index_separator[q - 1] - 1] = 0;
									}
									else {
										_line->extended_specifier[q] = new char[index_equally[q] + 1]; strncpy(_line->extended_specifier[q], market_node->first_attribute("extended_specifiers")->value(), index_equally[q]); _line->extended_specifier[q][index_equally[q]] = 0;


									}

									_line->extended_specifier_value[q] = new char[index_separator[q] - index_equally[q]];
									strncpy(_line->extended_specifier_value[q], (char*)((char*)market_node->first_attribute("extended_specifiers")->value() + index_equally[q]) + 1, index_separator[q] - index_equally[q] - 1);
									_line->extended_specifier_value[q][index_separator[q] - index_equally[q] - 1] = 0;
									//printf(_line->extended_specifier[q]);std::printf("\r\n");std::printf(_line->extended_specifier_value[q]);std::printf("\r\n");


								}
							}
						}




					outcomeNameError2:

						if (_line->variant > -1) {
							z = strlen(_line->specifier_value[_line->variant]) + 1; if (strcmp(_line->specifier[_line->variant], "variant") != 0) { std::printf(_line->specifier[_line->variant]); std::printf("\r\n"); }
							for (u = 0; u < bmax_markets_in[_line->market_id]; u++) if (bmarkets_id[_line->market_id][u] != nullptr && bmarkets_id[_line->market_id][u]->variable_text != nullptr && std::strcmp(_line->specifier_value[_line->variant], bmarkets_id[_line->market_id][u]->variable_text) == 0) break;
							if (outcomeNameError == 1 || u == bmax_markets_in[_line->market_id]) {
								std::printf("Variant market2 not found in run market_id=%d variant=", _line->market_id);  std::printf(_line->specifier_value[_line->variant]);  std::printf("  getVariantMarket\r\n"); if (getVariantMarket(bmarkets_id[_line->market_id][0], _line->specifier_value[_line->variant], true) == -1) { std::printf("variant market not found "); continue; }
								for (u = 0; u < bmax_markets_in[_line->market_id]; u++) if (bmarkets_id[_line->market_id][u] != nullptr && bmarkets_id[_line->market_id][u]->variable_text != nullptr && std::strcmp(_line->specifier_value[_line->variant], bmarkets_id[_line->market_id][u]->variable_text) == 0) break;
							}
							_market = bmarkets_id[_line->market_id][u];
							if (outcomeNameError == 1) outcomeNameError = 2;
							if (_line->type == 3) z = 16;
						}
						else { _market = bmarkets_id[_line->market_id][0]; if (_line->type == 0) z = 0; else if (_line->type == 1) z = 10; else if (_line->type == 2) z = 14; else if (_line->type == 3) z = 16; }
						outcome_number = 0;


						if (_line->outcome_number > 0) { for (int i = 0; i < _line->outcome_number; i++) if (_line->outcome_name[i] != nullptr) delete[] _line->outcome_name[i]; }; _line->outcome_number = 0;


						if (_line->outcome_id != nullptr) delete[] _line->outcome_id; if (_line->outcome_active != nullptr) delete[] _line->outcome_active; if (_line->outcome_team != nullptr) delete[] _line->outcome_team; if (_line->outcome_odds != nullptr) delete[] _line->outcome_odds;
						if (_line->outcome_probabilities != nullptr) delete[] _line->outcome_probabilities; if (_line->outcome_name != nullptr) delete[] _line->outcome_name;
						_line->outcome_probabilities = nullptr; _line->outcome_name = nullptr; _line->outcome_id = nullptr; _line->outcome_odds = nullptr; _line->outcome_active = nullptr;
						_line->outcome_team = nullptr;


						if (_line->name != nullptr) delete[] _line->name;


						_line->name = new char[strlen(_market->name) + 1];
						std::strcpy(_line->name, _market->name);
						for (int i = 0; i < _line->specifier_number; i++) {
							if (i == _line->variant) continue;

							replace(_line->name, _line->specifier[i], _line->specifier_value[i], true);
						}
						if (btournaments_id[_line->tournament_id]->season_name != nullptr) replace(_line->name, "$event", btournaments_id[_line->tournament_id]->season_name, true); else if (btournaments_id[_line->tournament_id]->name != nullptr) replace(_line->name, "$event", btournaments_id[_line->tournament_id]->name, true);



						for (xml_node<> * outcome_node = market_node->first_node("outcome"); outcome_node; outcome_node = outcome_node->next_sibling()) {


							if (outcome_node->first_attribute("active")) outcome_active[outcome_number] = atoi(outcome_node->first_attribute("active")->value());
							else outcome_active[outcome_number] = 0;
							if (outcome_node->first_attribute("team")) outcome_team[outcome_number] = atoi(outcome_node->first_attribute("team")->value());
							else outcome_team[outcome_number] = 0;
							if (outcome_node->first_attribute("id")) {
								outcome_id[outcome_number] = atoi((char*)((char*)outcome_node->first_attribute("id")->value() + z));
								if (outcome_id[outcome_number] == 0 && z > 0) {
									outcome_id[outcome_number] = atoi(outcome_node->first_attribute("id")->value());
									if (outcome_id[outcome_number] > 0) outcome_team[outcome_number] = 3;
									else {
										std::printf("_line->type=%d line->market_id=%d  _tournament->type_radar=%d  _line->tournament_id =%d \r\n", _line->type, _line->market_id, _tournament->type_radar, _line->tournament_id); std::printf(outcome_node->first_attribute("id")->value());

									}
								}

							}
							else outcome_id[outcome_number] = 0;


							if (outcome_node->first_attribute("odds")) outcome_odds[outcome_number] = atof(outcome_node->first_attribute("odds")->value());
							else outcome_odds[outcome_number] = 0;
							if (outcome_node->first_attribute("probabilities")) outcome_probabilities[outcome_number] = atof(outcome_node->first_attribute("probabilities")->value());
							else outcome_probabilities[outcome_number] = 0;
							if (outcome_name[outcome_number] != nullptr) delete[] outcome_name[outcome_number]; outcome_name[outcome_number] = nullptr;
							if (outcome_node->first_attribute("name")) {
								outcome_name[outcome_number] = new char[strlen(outcome_node->first_attribute("name")->value()) + 1];
								std::strcpy(outcome_name[outcome_number], outcome_node->first_attribute("name")->value());

							}

							outcome_number++;

						}






						if (PRINT == true) {

							std::printf("\r\n"); std::printf(_line->name); std::printf("\r\n"); std::printf("------------------------------------------------------------------------------\r\n");
						}


						////std::sprintf(socket_message_little, "Season id: %d\r\n", event_id);
						/*
						std::strcat(socket_message_big, "\r\n");
						std::strcat(socket_message_big, _line->name);
						std::strcat(socket_message_big, "\r\n");
						std::strcat(socket_message_big, "------------------------------------------------------------------------------\r\n");
						*/




						_line->outcome_number = outcome_number;
						if (_line->outcome_number > 0) {
							_line->outcome_name = new char*[_line->outcome_number];
							_line->outcome_id = new int[_line->outcome_number];
							_line->outcome_team = new int[_line->outcome_number];
							_line->outcome_active = new int[_line->outcome_number];
							_line->outcome_probabilities = new float[_line->outcome_number];
							_line->outcome_odds = new float[_line->outcome_number];







							for (int i = 0; i < _line->outcome_number; i++) {
								_line->outcome_name[i] = nullptr;
								_line->outcome_id[i] = outcome_id[i];
								_line->outcome_active[i] = outcome_active[i];
								_line->outcome_odds[i] = outcome_odds[i];
								_line->outcome_team[i] = outcome_team[i];
								_line->outcome_probabilities[i] = outcome_probabilities[i];


								if (_line->type == 0) {
									if (_line->outcome_id[i] == _market->outcome_id[i]) u = i;
									else
										for (u = 0; u < _market->outcome_number; u++) if (_line->outcome_id[i] == _market->outcome_id[u]) break;

									if (u < _market->outcome_number) {
										_line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
										std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);

									}
									else {
										std::printf("Eror. Outcome name not found. market_id=%d _line->outcome_id[i]=%d\r\n", _line->market_id, _line->outcome_id[i]);
										_line->outcome_name[i] = new char[2];
										std::strcpy(_line->outcome_name[i], " ");

										if (_market->variant > -1) printf("_market->variant=%s\r\n", _market->variable_text);
										if (outcomeNameError == 0) outcomeNameError = 1;

									}

									for (int j = 0; j < _line->specifier_number; j++) {
										if (j == _line->variant) continue;

										replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j], true);
									}
									if (btournaments_id[_line->tournament_id]->season_name != nullptr) replace(_line->outcome_name[i], "$event", btournaments_id[_line->tournament_id]->season_name, true); else if (btournaments_id[_line->tournament_id]->name != nullptr) replace(_line->outcome_name[i], "$event", btournaments_id[_line->tournament_id]->name, true);




									if (PRINT == true) {

										std::printf(_line->outcome_name[i]); std::printf("\t");
										std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
										std::printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									}
									/*
									std::strcat(socket_message_big, _line->outcome_name[i]);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
									std::strcat(socket_message_big, socket_message_little);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									std::strcat(socket_message_big, socket_message_little);
									*/





								}

								if (_line->type == 1) {
									if (_line->outcome_id[i] >= MAX_PLAYERS) {
										std::printf("ERROR in run. player_id out of MAX_PLAYERS. _line->outcome_id[i]=%d  _line->market_id=%d tournament_id=%d\r\n", _line->outcome_id[i], _line->market_id, _line->tournament_id);
										continue;

									}
									if (_line->outcome_team[i] != 3) {
										if (bplayers_id[_line->outcome_id[i]] == nullptr) {
											std::printf("Player3 id=%d not found in market id=%d in tournament_id=%d  in run function . getPlayer\r\n", _line->outcome_id[i], _line->market_id, _line->tournament_id);
											bplayers[bplayers_l].id = _line->outcome_id[i]; if (getPlayer(&bplayers[bplayers_l], true) == -1)
											{
												std::printf("error player id=%d  not found \r\n ", _line->outcome_id[i]); //continue;
												_line->outcome_name[i] = new char[2];
												std::strcpy(_line->outcome_name[i], " ");
											}
											else bplayers_l++;
										}

										if (_line->outcome_name[i] == nullptr  && bplayers_id[_line->outcome_id[i]]->full_name != nullptr) {
											_line->outcome_name[i] = new char[strlen(bplayers_id[_line->outcome_id[i]]->full_name) + 1];
											std::strcpy(_line->outcome_name[i], bplayers_id[_line->outcome_id[i]]->full_name);
										}
										else
											if (_line->outcome_name[i] == nullptr && bplayers_id[_line->outcome_id[i]]->name != nullptr) {
												_line->outcome_name[i] = new char[strlen(bplayers_id[_line->outcome_id[i]]->name) + 1];
												std::strcpy(_line->outcome_name[i], bplayers_id[_line->outcome_id[i]]->name);
											}

									}

									if (_line->outcome_team[i] == 3) {

										for (u = 0; u < _market->outcome_number; u++) if (_market->outcome_id[u] == _line->outcome_id[i]) break;
										if (u < _market->outcome_number) {
											_line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
											std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);

											for (int j = 0; j < _line->specifier_number; j++) {
												if (j == _line->variant) continue;
												replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j], true);
											}

											if (btournaments_id[_line->tournament_id]->season_name != nullptr)	replace(_line->outcome_name[i], "$event", btournaments_id[_line->tournament_id]->season_name, true); else if (btournaments_id[_line->tournament_id]->name != nullptr)	replace(_line->outcome_name[i], "$event", btournaments_id[_line->tournament_id]->name, true);

										}
										else {
											_line->outcome_name[i] = new char[2];
											std::strcpy(_line->outcome_name[i], " ");
										}



									}





									if (PRINT == true) {



										std::printf(_line->outcome_name[i]); std::printf("\t");
										std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
										printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									}

									/*std::strcat(socket_message_big, _line->outcome_name[i]);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
									std::strcat(socket_message_big, socket_message_little);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									std::strcat(socket_message_big, socket_message_little);

									*/




								}

								if (_line->type == 2) {
									if (_line->outcome_team[i] != 3) {
										if (_line->outcome_id[i] >= MAX_COMPETITORS) {
											std::printf("ERROR in run. competitor_id out of MAX_COMPETITORS. _line->outcome_id[i]=%d  _line->market_id=%d tournament_id=%d\r\n", _line->outcome_id[i], _line->market_id, _tournament->id);
											continue;
										}
										if (bcompetitors_id[_line->outcome_id[i]] == nullptr) {
											std::printf("Competitor id=%d not found in market id=%d in tournament_id=%d  in run season/race_tournament. getTournament\r\n", _line->outcome_id[i], _line->market_id, _tournament->id);
											if (getTournament(btournaments_id[_tournament->id], false, true) == -1)
												std::printf("ERROR!\r\nTournaments not found in run season/race_tournament %d \r\n", _tournament->id);
										}

										if (bcompetitors_id[_line->outcome_id[i]] == nullptr) {
											std::printf("\r\nCompetitors id=%d not found in tournament id=%d after getTournament . Run getCompetitor\r\n", _line->outcome_id[i], _tournament->id);
											bcompetitors[bcompetitors_l].id = _line->outcome_id[i];
											if (getCompetitor(&bcompetitors[bcompetitors_l], true) == -1) {
												std::printf(" Error getCompetitor in run season/race_tournamnet. line type= 2 id competitor=%d \r\n", _line->outcome_id[i]);
												_line->outcome_name[i] = new char[2];
												std::strcpy(_line->outcome_name[i], " ");
											}
											else bcompetitors_l++;
										}

										if (bcompetitors_id[_line->outcome_id[i]] != nullptr) { _line->outcome_name[i] = new char[strlen(bcompetitors_id[_line->outcome_id[i]]->name) + 1]; std::strcpy(_line->outcome_name[i], bcompetitors_id[_line->outcome_id[i]]->name); }

									}
									else
									{
										for (u = 0; u < _market->outcome_number; u++) if (_market->outcome_id[u] == _line->outcome_id[i]) break;
										if (u < _market->outcome_number) {
											_line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
											std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);
											for (int j = 0; j < _line->specifier_number; j++) {
												if (j == _line->variant) continue;
												replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j], true);
											}

											if (_tournament->season_name != nullptr) replace(_line->outcome_name[i], "$event", btournaments_id[_line->tournament_id]->season_name, true); else if (_tournament->name != nullptr) replace(_line->outcome_name[i], "$event", btournaments_id[_line->tournament_id]->name, true);
										}
										else { _line->outcome_name[i] = new char[2]; std::strcpy(_line->outcome_name[i], " "); }
									}
									if (PRINT == true) {
										std::printf(_line->outcome_name[i]); std::printf("\t");
										std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
										printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									}

									/*std::strcat(socket_message_big, _line->outcome_name[i]);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
									std::strcat(socket_message_big, socket_message_little);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									std::strcat(socket_message_big, socket_message_little);*/


								}

								if (_line->type == 3 || _line->type == 4) {

									if (_line->outcome_id[i] == _market->outcome_id[i]) u = i;
									else
										for (u = 0; u < _market->outcome_number; u++) {


											if (_line->outcome_id[i] == _market->outcome_id[u]) break;
										}

									if (u < _market->outcome_number) {

										_line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
										std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);

									}
									else {
										std::printf("Eror. Outcome name not found. market_id=%d _line->outcome_id[i]=%d\r\n", _line->market_id, _line->outcome_id[i]);
										_line->outcome_name[i] = new char[2];
										std::strcpy(_line->outcome_name[i], " ");

										if (_market->variant > -1)
											printf("_market->variant=%s\r\n", _market->variable_text);
										if (outcomeNameError == 0) outcomeNameError = 1;

									}

									for (int j = 0; j < _line->specifier_number; j++) {
										if (j == _line->variant) continue;

										replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j], true);
									}

									if (_tournament->season_name) replace(_line->outcome_name[i], "$event", btournaments_id[_line->tournament_id]->season_name, true); else if (_tournament->name) replace(_line->outcome_name[i], "$event", btournaments_id[_line->tournament_id]->name, true);


									//if (_line->market_id == 188 || _line->market_id == 224 || _line->market_id == 485 || _line->market_id == 231 || _line->market_id == 65 || _line->market_id == 383 || _line->market_id == 66) 

									if (PRINT == true) {

										std::printf(_line->outcome_name[i]); std::printf("\t");
										std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
										printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									}
									/*	std::strcat(socket_message_big, _line->outcome_name[i]);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
									std::strcat(socket_message_big, socket_message_little);
									std::strcat(socket_message_big, "\t");
									std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
									std::strcat(socket_message_big, socket_message_little);

									*/


								}


							}

							if (outcomeNameError == 1 && _market->variant > -1) goto outcomeNameError2;
						}


						if (DEBUG_OUTPUT == true) printf("insertLine _line->type ==%d\r\n", _line->type);
						auto it = bcompound2line_index.find(_line ->getCompoundKey());
						if (DEBUG_OUTPUT == true) {
							printf(_line ->getCompoundKey().c_str());
							printf("\r\n");
						}
						if (it == bcompound2line_index.end()) {
							if (DEBUG_OUTPUT == true) printf("new line add");
							_line->id = blines_l;
							if (DEBUG_OUTPUT == true) printf("new line add1");
							blines[blines_l] = (*_line);
							blines_id[_line->id] = &blines[blines_l];
							if (DEBUG_OUTPUT == true) printf("new line add2");
							binsert_line(_line, blines_l);
							if (DEBUG_OUTPUT == true) printf("new line add3");
							blines_l++;
							bcategories_id[_tournament->category_id]->outrights_id.push_back(_line->id);
							if (DEBUG_OUTPUT == true) printf("new line add finish");

						}
						else {
							if (DEBUG_OUTPUT == true) printf("line update");
							_line->id = it->second;
							if (DEBUG_OUTPUT == true) printf("line update1");
							blines[it->second] = (*_line);
							if (DEBUG_OUTPUT == true) printf("line finish");

							//printf("Line Update\r\n");
						}


						if (DEBUG_OUTPUT == true) printf("end insertLine _line->type ==%d\r\n", _line->type);








					}
				}

			}
			if (type_radar == 0 || type_radar == 1 || type_radar == 5) {
			
				if (bevents_id.find(key) == bevents_id.end()) {
					std::printf("Event not found. Run getFixture to get event_id=%d type_radar=%d\r\n", event_id, type_radar);
					bevents[bevents_l].id = event_id;
					bevents[bevents_l].type_radar = type_radar;
					if (getEventFixture(&bevents[bevents_l], true) == -1) { std::printf("ERROR!\r\n getEventFixture1 error return in run %d .\r\n", event_id); continue; }
					bevents_l++;

				}
				_event = bevents_id[key];
				if (_event->show == 0) {
					bevents_show[bevents_show_l] = _event; bevents_show_l++;
				}
				_event->show = 1;
			
				if (PRINT == true) {
					std::printf("\r\n***************************************************\r\n");
					std::printf("%d\r\n", _event->id);
					std::printf(_event->home_name); if (_event->away_name != nullptr) { std::printf(" - ");  std::printf(_event->away_name); }
					std::printf("\r\n");
				}

				//std::strcat(socket_message_big, "\r\n***************************************************\r\n");
				//std::sprintf(socket_message_little, "%d\r\n", _event->id);
				//std::strcat(socket_message_big, socket_message_little);
				//std::strcat(socket_message_big, _event->home_name);
				//if (_event->away_name != nullptr) {std::strcat(socket_message_big, " - ");  std::strcat(socket_message_big, _event->away_name);}

				if (_event->sport_id >= MAX_SPORTS) { std::printf("ERROR DATA!\r\nsevent sport_id out of MAX_SPORTS in run %d\r\n", _event->sport_id); continue; }
				if (bsports_id[_event->sport_id] == nullptr) { std::printf("Sport not found. Run getSports. sport_id=%d\r\n", _event->sport_id); getSports(true); }
				if (PRINT == true) {
					std::printf(bsports_id[_event->sport_id]->name); std::printf("\r\n");
				}
				//	std::strcat(socket_message_big, bsports_id[_event->sport_id]->name);
				//	std::strcat(socket_message_big, "\r\n");

				if (_event->type_radar < 2 && _event->tournament_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nsevent tournament_id out of MAX_TOURNAMENTS in run %d\r\n", _event->tournament_id); continue; }
				if (_event->type_radar == 2 && _event->simple_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nsevent tournament_id out of MAX_TOURNAMENTS in run %d\r\n", _event->simple_id); continue; }
				if (_event->type_radar == 0 && btournaments_id[_event->tournament_id] == nullptr) {
					std::printf("Tournament not found. Run getTournament(). tournament_id=%d\r\n", _event->tournament_id);
					btournaments[btournaments_l].id = _event->tournament_id;
					btournaments[btournaments_l].type_radar = _event->type_radar;
					if (getTournament(&btournaments[btournaments_l], true, false) == -1) { std::printf("ERROR!\r\nTournaments not found in run %d . Run getEventFixture\r\n", _event->tournament_id); if (getEventFixture(_event, true) == -1) { std::printf("ERROR!\r\n getEventFixture2 error return in run %d .\r\n", _event->id); continue; } }
					else btournaments_l++;


				}
				if (_event->type_radar == 2 && bsimples_id[_event->simple_id] == nullptr) {
					std::printf("Simple Tournament not found. Run getTournament(). bsimples_id=%d _event_id=%d\r\n ", _event->simple_id, _event->id);
					btournaments[btournaments_l].simple_id = _event->simple_id;
					btournaments[btournaments_l].id = 0;
					btournaments[btournaments_l].type_radar = _event->type_radar;
					if (getTournament(&btournaments[btournaments_l], true, false) == -1) { std::printf("ERROR!\r\nSimple Tournaments not found in run %d . Run getEventFixture\r\n", _event->tournament_id); if (getEventFixture(_event, true) == -1) { std::printf("ERROR!\r\n getEventFixture3 error return in run %d .\r\n", _event->id); continue; } }
					else btournaments_l++;


				}


				if (PRINT == true) {
					if (_event->type_radar == 0) std::printf(btournaments_id[_event->tournament_id]->name);
					if (_event->type_radar == 2) std::printf(bsimples_id[_event->simple_id]->name);
					std::printf("\r\n");
				}

				//if (_event->type_radar == 0) std::strcat(socket_message_big, btournaments_id[_event->tournament_id]->name);
				//if (_event->type_radar == 2) std::strcat(socket_message_big, bsimples_id[_event->simple_id]->name);
				//std::strcat(socket_message_big, "\r\n");







				if (_event->category_id >= MAX_CATEGORIES) { std::printf("ERROR DATA!\r\nsevent category_id out of MAX_CATEGORIES in run %d\r\n", _event->category_id); continue; }
				if (bcategories_id[_event->category_id] == nullptr) {
					std::printf("Category not found. Run getTournament(). category_id=%d\r\n", _event->category_id);
					if (_event->type_radar == 0) {
						if (getTournament(btournaments_id[_event->tournament_id], false, true) == -1) if (getEventFixture(_event, true) == -1) continue;;
					}
					if (_event->type_radar == 2) {
						if (getTournament(bsimples_id[_event->simple_id], false, true) == -1) if (getEventFixture(_event, true) == -1) continue;;
					}


				}
				if (PRINT == true) {
					std::printf(bcategories_id[_event->category_id]->name); std::printf("\r\n");
					std::printf("\r\n***************************************************\r\n");
				}
				//std::strcat(socket_message_big, bcategories_id[_event->category_id]->name);
				//std::strcat(socket_message_big, "\r\n\r\n***************************************************\r\n");




				if (doc.first_node()->first_attribute("timestamp")) _event->timestamp = atoi(doc.first_node()->first_attribute("timestamp")->value());

				xml_node<> * sport_event_status = doc.first_node()->first_node("sport_event_status");
				if (sport_event_status != nullptr) {

					xml_node<> * statistics = sport_event_status->first_node("statistics");

					if (statistics != nullptr) {

						if (statistics->first_node("yellow_cards")) {
							_event->home_yellowcards = atoi(statistics->first_node("yellow_cards")->first_attribute("home")->value());
							_event->away_yellowcards = atoi(statistics->first_node("yellow_cards")->first_attribute("away")->value());
						}

						if (statistics->first_node("red_cards")) {
							_event->home_redcards = atoi(statistics->first_node("red_cards")->first_attribute("home")->value());
							_event->away_redcards = atoi(statistics->first_node("red_cards")->first_attribute("away")->value());
						}
						if (statistics->first_node("yellow_red_cards")) {
							_event->home_yellow_red_cards = atoi(statistics->first_node("yellow_red_cards")->first_attribute("home")->value());
							_event->away_yellow_red_cards = atoi(statistics->first_node("yellow_red_cards")->first_attribute("away")->value());
						}

						if (statistics->first_node("corners")) {
							_event->home_corners = atoi(statistics->first_node("corners")->first_attribute("home")->value());
							_event->away_corners = atoi(statistics->first_node("corners")->first_attribute("away")->value());
						}

					}


					if (sport_event_status->first_attribute("status")) _event->status = atoi(sport_event_status->first_attribute("status")->value());
					if (sport_event_status->first_attribute("possession")) _event->possession = atoi(sport_event_status->first_attribute("possession")->value());
					if (sport_event_status->first_attribute("try")) _event->try_num = atoi(sport_event_status->first_attribute("try")->value());
					if (sport_event_status->first_attribute("throw")) _event->throw_num = atoi(sport_event_status->first_attribute("throw")->value());
					if (sport_event_status->first_attribute("delivery")) _event->delivery = atoi(sport_event_status->first_attribute("delivery")->value());
					if (sport_event_status->first_attribute("current_ct_team")) _event->delivery = atoi(sport_event_status->first_attribute("current_ct_team")->value());
					if (sport_event_status->first_attribute("yards")) _event->yards = atoi(sport_event_status->first_attribute("yards")->value());
					if (sport_event_status->first_attribute("innings")) _event->innings = atoi(sport_event_status->first_attribute("innings")->value());
					if (sport_event_status->first_attribute("over")) _event->over = atoi(sport_event_status->first_attribute("over")->value());
					if (sport_event_status->first_attribute("current_end")) _event->current_end = atoi(sport_event_status->first_attribute("current_end")->value());
					if (sport_event_status->first_attribute("position")) _event->position = atoi(sport_event_status->first_attribute("position")->value());
					if (sport_event_status->first_attribute("away_yellowcards"))
						_event->away_yellowcards = atoi(sport_event_status->first_attribute("away_yellowcards")->value());
					if (sport_event_status->first_attribute("home_yellowcards")) _event->home_yellowcards = atoi(sport_event_status->first_attribute("home_yellowcards")->value());
					if (sport_event_status->first_attribute("away_yellow_cards"))
						_event->away_yellowcards = atoi(sport_event_status->first_attribute("away_yellow_cards")->value());
					if (sport_event_status->first_attribute("home_yellow_cards"))
						_event->home_yellowcards = atoi(sport_event_status->first_attribute("home_yellow_cards")->value());
					if (sport_event_status->first_attribute("away_redcards")) _event->away_redcards = atoi(sport_event_status->first_attribute("away_redcards")->value());
					if (sport_event_status->first_attribute("home_redcards")) _event->home_redcards = atoi(sport_event_status->first_attribute("home_redcards")->value());
					if (sport_event_status->first_attribute("away_dismissals")) _event->away_dismissals = atoi(sport_event_status->first_attribute("away_dismissals")->value());
					if (sport_event_status->first_attribute("home_dismissals")) _event->home_dismissals = atoi(sport_event_status->first_attribute("home_dismissals")->value());
					if (sport_event_status->first_attribute("away_penalty_runs")) _event->away_penalty_runs = atoi(sport_event_status->first_attribute("away_penalty_runs")->value());
					if (sport_event_status->first_attribute("home_penalty_runs")) _event->home_penalty_runs = atoi(sport_event_status->first_attribute("home_penalty_runs")->value());
					if (sport_event_status->first_attribute("away_score")) _event->away_score = atof(sport_event_status->first_attribute("away_score")->value());
					if (sport_event_status->first_attribute("home_score")) _event->home_score = atof(sport_event_status->first_attribute("home_score")->value());
					if (sport_event_status->first_attribute("away_gamescore")) _event->away_gamescore = atoi(sport_event_status->first_attribute("away_gamescore")->value());
					if (sport_event_status->first_attribute("home_gamescore")) _event->home_gamescore = atoi(sport_event_status->first_attribute("home_gamescore")->value());
					if (sport_event_status->first_attribute("away_legscore")) _event->away_legscore = atoi(sport_event_status->first_attribute("away_legscore")->value());
					if (sport_event_status->first_attribute("home_legscore")) _event->home_legscore = atoi(sport_event_status->first_attribute("home_legscore")->value());
					if (sport_event_status->first_attribute("visit")) _event->visit = atoi(sport_event_status->first_attribute("visit")->value());
					if (sport_event_status->first_attribute("reporting")) _event->reporting = atoi(sport_event_status->first_attribute("reporting")->value());
					if (sport_event_status->first_attribute("remaining_reds")) _event->remaining_reds = atoi(sport_event_status->first_attribute("remaining_reds")->value());
					if (sport_event_status->first_attribute("match_status")) _event->match_status = atoi(sport_event_status->first_attribute("match_status")->value());
					if (sport_event_status->first_attribute("home_suspend")) _event->home_suspend = atoi(sport_event_status->first_attribute("home_suspend")->value());
					if (sport_event_status->first_attribute("away_suspend")) _event->away_suspend = atoi(sport_event_status->first_attribute("away_suspend")->value());
					if (sport_event_status->first_attribute("current_server")) _event->current_server = atoi(sport_event_status->first_attribute("current_server")->value());
					if (sport_event_status->first_attribute("winner_id")) _event->winner_id = atoi(sport_event_status->first_attribute("winner_id")->value());
					if (sport_event_status->first_attribute("home_batter")) _event->home_batter = atoi(sport_event_status->first_attribute("home_batter")->value());
					if (sport_event_status->first_attribute("away_batter")) _event->away_batter = atoi(sport_event_status->first_attribute("away_batter")->value());
					if (sport_event_status->first_attribute("away_remaining_bowls")) _event->away_remaining_bowls = atoi(sport_event_status->first_attribute("away_remaining_bowls")->value());
					if (sport_event_status->first_attribute("home_remaining_bowls")) _event->home_remaining_bowls = atoi(sport_event_status->first_attribute("home_remaining_bowls")->value());
					if (sport_event_status->first_attribute("outs")) _event->outs = atoi(sport_event_status->first_attribute("outs")->value());
					if (sport_event_status->first_attribute("strikes")) _event->strikes = atoi(sport_event_status->first_attribute("strikes")->value());
					if (sport_event_status->first_attribute("balls")) _event->balls = atoi(sport_event_status->first_attribute("balls")->value());
					if (sport_event_status->first_attribute("bases")) {
						if (_event->bases != nullptr) { delete[] _event->bases; _event->bases = nullptr; }
						_event->bases = new char[strlen(sport_event_status->first_attribute("bases")->value()) + 1];
						std::strcpy(_event->bases, sport_event_status->first_attribute("bases")->value());

					}




					if (sport_event_status->first_attribute("tiebreak") && sport_event_status->first_attribute("tiebreak")->value()[0] == 't' && sport_event_status->first_attribute("tiebreak")->value()[1] == 'r')  _event->tiebreak = 1;
					if (sport_event_status->first_attribute("tiebreak") && sport_event_status->first_attribute("tiebreak")->value()[0] == 'f' && sport_event_status->first_attribute("tiebreak")->value()[1] == 'a')  _event->tiebreak = 0;

					if (sport_event_status->first_attribute("expedite_mode") && sport_event_status->first_attribute("expedite_mode")->value()[0] == 't' && sport_event_status->first_attribute("expedite_mode")->value()[1] == 'r')  _event->expedite_mode = 1;
					if (sport_event_status->first_attribute("expedite_mode") && sport_event_status->first_attribute("expedite_mode")->value()[0] == 'f' && sport_event_status->first_attribute("expedite_mode")->value()[1] == 'a')  _event->expedite_mode = 0;




					xml_node<> * period_scores = sport_event_status->first_node("period_scores");

					j = 0;
					if (period_scores != nullptr) {


						for (xml_node<> * period_score = period_scores->first_node("period_score"); period_score; period_score = period_score->next_sibling())
						{
							if (j == 0)std::strcpy(set_scores, period_score->first_attribute("home_score")->value());
							if (j > 0) {
								std::strcat(set_scores, "-");
								std::strcat(set_scores, period_score->first_attribute("home_score")->value());
							}
							std::strcat(set_scores, ":");
							std::strcat(set_scores, period_score->first_attribute("away_score")->value());
							j++;
						}

						//printf(set_scores);
						//printf("\r\n");
						if (_event->set_scores != nullptr) { delete[] _event->set_scores; _event->set_scores = nullptr; }
						_event->set_scores = new char[strlen(set_scores) + 1];std::strcpy(_event->set_scores, set_scores);
					}




					xml_node<> * clock = sport_event_status->first_node("clock");
					if (clock != nullptr) {

						if (clock->first_attribute("stopped") && clock->first_attribute("stopped")->value()[0] == 't' && clock->first_attribute("stopped")->value()[1] == 'r')  _event->stopped = 1;

						if (clock->first_attribute("stopped") && clock->first_attribute("stopped")->value()[0] == 'f' && clock->first_attribute("stopped")->value()[1] == 'a')  _event->stopped = 0;

						if (clock->first_attribute("remaining_time_in_period")) {
							if (_event->remaining_time_in_period != nullptr) delete[] _event->remaining_time_in_period;
							_event->remaining_time_in_period = new char[strlen(clock->first_attribute("remaining_time_in_period")->value()) + 1];
							std::strcpy(_event->remaining_time_in_period, clock->first_attribute("remaining_time_in_period")->value());
						}
						else {
							if (_event->remaining_time_in_period != nullptr) {
								delete[] _event->remaining_time_in_period; _event->remaining_time_in_period = nullptr;
							}
							//_event->remaining_time_in_period = new char[1]; _event->remaining_time_in_period[0] = 0;


						}

						if (clock->first_attribute("stoppage_time")) {
							if (_event->stoppage_time != nullptr) delete[] _event->stoppage_time;
							_event->stoppage_time = new char[strlen(clock->first_attribute("stoppage_time")->value()) + 1];
							std::strcpy(_event->stoppage_time, clock->first_attribute("stoppage_time")->value());
						}
						else {

							if (_event->stoppage_time != nullptr) {
								delete[] _event->stoppage_time; _event->stoppage_time = nullptr;
							}
							//_event->stoppage_time = new char[1]; _event->stoppage_time[0] = 0;

						}


						if (clock->first_attribute("stoppage_time_announced")) {
							if (_event->stoppage_time_announced != nullptr) delete[] _event->stoppage_time_announced;
							_event->stoppage_time_announced = new char[strlen(clock->first_attribute("stoppage_time_announced")->value()) + 1];
							std::strcpy(_event->stoppage_time_announced, clock->first_attribute("stoppage_time_announced")->value());
						}
						else {
							if (_event->stoppage_time_announced != nullptr) {
								delete[] _event->stoppage_time_announced; _event->stoppage_time_announced = nullptr;
							}
							//_event->stoppage_time_announced = new char[1]; _event->stoppage_time_announced[0] = 0;
						}


						if (clock->first_attribute("remaining_time")) {
							if (_event->remaining_time != nullptr) delete[] _event->remaining_time;
							_event->remaining_time = new char[strlen(clock->first_attribute("remaining_time")->value()) + 1];
							std::strcpy(_event->remaining_time, clock->first_attribute("remaining_time")->value());
						}
						else {
							if (_event->remaining_time != nullptr) { delete[] _event->remaining_time; _event->remaining_time = nullptr; }
							//_event->remaining_time = new char[1]; _event->remaining_time[0] = 0;

						}


						if (clock->first_attribute("match_time")) {
							if (_event->match_time != nullptr) delete[] _event->match_time;
							_event->match_time = new char[strlen(clock->first_attribute("match_time")->value()) + 1];
							std::strcpy(_event->match_time, clock->first_attribute("match_time")->value());
						}
						else {

							if (_event->match_time != nullptr) {
								delete[] _event->match_time; _event->match_time = nullptr;
							}
							//_event->match_time = new char[1]; _event->match_time[0] = 0;			

						}


					}


				}

				//	if (_event->status > 0) PRINT= true; else PRINT= false;

				if (PRINT == true) {
					if (_event->set_scores != nullptr) { std::printf("set_scores="); std::printf(_event->set_scores); }
					if (_event->match_time != nullptr) { std::printf("match_time="); std::printf(_event->match_time); std::printf(" "); }
					if (_event->remaining_time != nullptr) { std::printf("remaining_time="); std::printf(_event->remaining_time); std::printf(" "); }
					if (_event->remaining_time_in_period != nullptr) { std::printf("remaining_time_in_period="); std::printf(_event->remaining_time_in_period); std::printf(" "); }
					if (_event->bases != nullptr) { std::printf("bases="); std::printf(_event->bases); std::printf(" "); }


					std::printf("stopped=%d ", _event->stopped);
					std::printf("period_length=%d ", _event->period_length);
					std::printf("numbers of set=%d ", _event->bo);
					std::printf("status=%d ", _event->status); std::printf("possession=%d ", _event->possession); std::printf("home_score=%g ", _event->away_score);
					std::printf("away_score=%g ", _event->away_score); std::printf("home_yellowcards=%d ", _event->home_yellowcards); std::printf("away_yellowcards=%d ", _event->away_yellowcards); std::printf("home_redcards=%d ", _event->home_redcards); std::printf("away_redcards=%d ", _event->away_redcards); std::printf("expedite_mode=%d ", _event->expedite_mode); std::printf("tiebreak=%d ", _event->tiebreak); std::printf("outs=%d ", _event->outs); std::printf("strikes=%d ", _event->strikes); std::printf("balls=%d ", _event->balls);  std::printf("home_remaining_bowls=%d ", _event->home_remaining_bowls);
					std::printf("away_remaining_bowls=%d ", _event->away_remaining_bowls); std::printf("home_batter=%d ", _event->home_batter); std::printf("away_batter=%d ", _event->away_batter); std::printf("winner_id=%d ", _event->winner_id); std::printf("home_suspend=%d ", _event->home_suspend); std::printf("away_suspend=%d ", _event->away_suspend); std::printf("match_status=%d ", _event->match_status); std::printf("remaining_reds=%d ", _event->remaining_reds); std::printf("reporting=%d ", _event->reporting); std::printf("position=%d ", _event->position); std::printf("home_gamescore=%d ", _event->home_gamescore); std::printf("away_gamescore=%d ", _event->away_gamescore); std::printf("visit=%d ", _event->visit); std::printf("home_dismissals=%d ", _event->home_dismissals); std::printf("away_dismissals=%d ", _event->away_dismissals); std::printf("home_penalty_runs=%d ", _event->home_penalty_runs);	std::printf("away_penalty_runs=%d ", _event->away_penalty_runs);
					std::printf("over=%d ", _event->over); std::printf("try_num=%d ", _event->try_num); std::printf("trow_num=%d ", _event->throw_num);
					std::printf("delivery=%d ", _event->delivery); std::printf("yards=%d ", _event->yards); std::printf("current_server=%d ", _event->current_server);
					std::printf("innings=%d ", _event->innings);
					std::printf("\r\n\r\n");
				}

				xml_node<> * odds = doc.first_node()->first_node("odds");








				if (odds != nullptr) {
					betstop_reason = 0;
					if (odds->first_attribute("betstop_reason")) betstop_reason = atoi(odds->first_attribute("betstop_reason")->value());
					//_line->betstop_reason = betstop_reason;
					_line->event_id = event_id;
					_line->tournament_id = 0;
					_line->simple_id = 0;
					_line->season_id = 0;
					for (xml_node<> * market_node = odds->first_node("market"); market_node; market_node = market_node->next_sibling())
					{
						if (DEBUG_OUTPUT == true) printf("start parse market\r\n");
						outcomeNameError = 0;
						if (market_node->first_attribute("next_betstop")) _line->next_betstop = atoi(market_node->first_attribute("next_betstop")->value());
						if (market_node->first_node("market_metadata") && market_node->first_node("market_metadata")->first_attribute("next_betstop")) _line->next_betstop = atoi(market_node->first_node("market_metadata")->first_attribute("next_betstop")->value());
						if (market_node->first_attribute("favourite")) _line->favourite = atoi(market_node->first_attribute("favourite")->value());
						if (market_node->first_attribute("status")) _line->status = atoi(market_node->first_attribute("status")->value());
						if (market_node->first_attribute("id")) _line->market_id = atoi(market_node->first_attribute("id")->value());

						//if (_line->market_id == 1) printf(" bmarkets_id[_line->market_id][0]->line_type=%d\r\n", bmarkets_id[_line->market_id][0]->line_type);
						if (_line->market_id >= MAX_MARKETS) {
							std::printf("ERROR DATA!\r\nmarket id out of MAX_MARKETS in run%d\r\n", _line->market_id); continue;
						}
						if (bmarkets_id[_line->market_id] == nullptr) {
							std::printf("ERROR DATA!\r\nmarket id not found in run%d\r\n", _line->market_id); continue;
						};
						if (bmarkets_id[_line->market_id][0] == nullptr) {
							std::printf("ERROR DATA!\r\nmarket id 0 not found in run%d\r\n", _line->market_id); continue;
						};
						_line->variant = bmarkets_id[_line->market_id][0]->variant;
						_line->type = bmarkets_id[_line->market_id][0]->type;
						if (_line->specifier_number > 0) for (q = 0; q < _line->specifier_number; q++) {
							if (_line->specifier[q] != nullptr) delete[] _line->specifier[q]; _line->specifier[q] = nullptr;
							if (_line->specifier_value[q] != nullptr)  delete[] _line->specifier_value[q]; _line->specifier_value[q] = nullptr;
						}
						if (_line->specifier != nullptr) { delete[] _line->specifier; _line->specifier = nullptr; }
						if (_line->specifier_value != nullptr) { delete[] _line->specifier_value; _line->specifier_value = nullptr; }
						_line->specifier_number = 0;
						if (_line->extended_specifier_number > 0) for (q = 0; q < _line->extended_specifier_number; q++) {
							if (_line->extended_specifier[q] != nullptr) delete[] _line->extended_specifier[q];
							if (_line->extended_specifier_value[q] != nullptr)  delete[] _line->extended_specifier_value[q];
						}
						if (_line->extended_specifier != nullptr) { delete[] _line->extended_specifier; _line->extended_specifier = nullptr; }
						if (_line->extended_specifier_value != nullptr) { delete[] _line->extended_specifier_value; _line->extended_specifier_value = nullptr; }
						_line->extended_specifier_number = 0;
						if (market_node->first_attribute("specifiers")) {
							n = 0;
							m = market_node->first_attribute("specifiers")->value_size();
							for (q = 0; q < m; q++) {
								if (market_node->first_attribute("specifiers")->value()[q] == '=')
									index_equally[n] = q;

								if (market_node->first_attribute("specifiers")->value()[q] == '|') {
									index_separator[n] = q; n++;
								}

							}
							index_separator[n] = q; n++;




							_line->specifier_number = n;
							if (_line->specifier_number > 0) {
								_line->specifier_value = new char*[_line->specifier_number];
								_line->specifier = new char*[_line->specifier_number];


								for (q = 0; q < _line->specifier_number; q++) {
									if (q > 0) {
										_line->specifier[q] = new char[index_equally[q] - index_separator[q - 1]];
										strncpy(_line->specifier[q], (char*)((char*)market_node->first_attribute("specifiers")->value() + index_separator[q - 1]) + 1, index_equally[q] - index_separator[q - 1] - 1);
										_line->specifier[q][index_equally[q] - index_separator[q - 1] - 1] = 0;
									}
									else {
										_line->specifier[q] = new char[index_equally[q] + 1]; strncpy(_line->specifier[q], market_node->first_attribute("specifiers")->value(), index_equally[q]); _line->specifier[q][index_equally[q]] = 0;


									}

									_line->specifier_value[q] = new char[index_separator[q] - index_equally[q]];
									strncpy(_line->specifier_value[q], (char*)((char*)market_node->first_attribute("specifiers")->value() + index_equally[q]) + 1, index_separator[q] - index_equally[q] - 1);
									_line->specifier_value[q][index_separator[q] - index_equally[q] - 1] = 0;



								}
							}
						}
						if (market_node->first_attribute("extended_specifiers")) {
							n = 0;
							m = market_node->first_attribute("extended_specifiers")->value_size();
							for (q = 0; q < m; q++) {
								if (market_node->first_attribute("extended_specifiers")->value()[q] == '=')
									index_equally[n] = q;

								if (market_node->first_attribute("extended_specifiers")->value()[q] == '|') {
									index_separator[n] = q; n++;
								}

							}
							index_separator[n] = q; n++;



							_line->extended_specifier_number = n;
							if (_line->extended_specifier_number > 0) {
								_line->extended_specifier_value = new char*[_line->extended_specifier_number];
								_line->extended_specifier = new char*[_line->extended_specifier_number];


								for (q = 0; q < _line->extended_specifier_number; q++) {
									if (q > 0) {
										_line->extended_specifier[q] = new char[index_equally[q] - index_separator[q - 1]];
										strncpy(_line->extended_specifier[q], (char*)((char*)market_node->first_attribute("extended_specifiers")->value() + index_separator[q - 1]) + 1, index_equally[q] - index_separator[q - 1] - 1);
										_line->extended_specifier[q][index_equally[q] - index_separator[q - 1] - 1] = 0;
									}
									else {
										_line->extended_specifier[q] = new char[index_equally[q] + 1]; strncpy(_line->extended_specifier[q], market_node->first_attribute("extended_specifiers")->value(), index_equally[q]); _line->extended_specifier[q][index_equally[q]] = 0;


									}

									_line->extended_specifier_value[q] = new char[index_separator[q] - index_equally[q]];
									strncpy(_line->extended_specifier_value[q], (char*)((char*)market_node->first_attribute("extended_specifiers")->value() + index_equally[q]) + 1, index_separator[q] - index_equally[q] - 1);
									_line->extended_specifier_value[q][index_separator[q] - index_equally[q] - 1] = 0;
									//printf(_line->extended_specifier[q]);std::printf("\r\n");std::printf(_line->extended_specifier_value[q]);std::printf("\r\n");


								}
							}
						}
					outcomeNameError3: if (_line->variant > -1 && _line->type != 4) {
						z = strlen(_line->specifier_value[_line->variant]) + 1; if (strcmp(_line->specifier[_line->variant], "variant") != 0) { std::printf(_line->specifier[_line->variant]); std::printf("\r\n"); }
						for (u = 0; u < bmax_markets_in[_line->market_id]; u++) if (bmarkets_id[_line->market_id][u] != nullptr && bmarkets_id[_line->market_id][u]->variable_text != nullptr && std::strcmp(_line->specifier_value[_line->variant], bmarkets_id[_line->market_id][u]->variable_text) == 0) break;
						if (outcomeNameError == 1 || u == bmax_markets_in[_line->market_id]) {
							std::printf("Variant market3 not found in run market_id=%d variant=", _line->market_id);  std::printf(_line->specifier_value[_line->variant]);  std::printf("  getVariantMarket\r\n"); if (getVariantMarket(bmarkets_id[_line->market_id][0], _line->specifier_value[_line->variant], true) == -1) { std::printf("variant market not found "); continue; }
							for (u = 0; u < bmax_markets_in[_line->market_id]; u++) if (bmarkets_id[_line->market_id][u] != nullptr && bmarkets_id[_line->market_id][u]->variable_text != nullptr && std::strcmp(_line->specifier_value[_line->variant], bmarkets_id[_line->market_id][u]->variable_text) == 0) break;
						}
						_market = bmarkets_id[_line->market_id][u];
						if (outcomeNameError == 1) outcomeNameError = 2;
						if (_line->type == 3) z = 16;
					}
									   else {
										   _market = markets_id[_line->market_id][0]; if (_line->type == 0) z = 0; else if (_line->type == 1) z = 10; else if (_line->type == 2) z = 14; else if (_line->type == 3) z = 16; else if (_line->type == 4) {
											   z = strlen(_line->specifier_value[_line->variant]) + 1;
											   int in_dot = 0;
											   for (int q = 0; q < z - 2; q++) {
												   if (_line->specifier_value[_line->variant][q] == ':') in_dot++;
												   if (in_dot == 3) {
													   props_player_id = atoi((char*)((char*)_line->specifier_value[_line->variant] + q + 1)); break;
												   }
											   }

											   if (props_player_id >= MAX_PLAYERS) {
												   printf("ERROR props_player_id out of MAX_PLAYERS props_player_id=%d\r\n", props_player_id); continue;
											   }

											   if (bplayers_id[props_player_id] == nullptr) {
												   std::printf("props_player_id=%d  not found . getPlayer\r\n ", props_player_id);
												   bplayers[bplayers_l].id = props_player_id; if (getPlayer(&bplayers[bplayers_l], true) == -1)
												   {
													   std::printf("error props_player_id=%d  in getPlayer bets process returned -1 \r\n ", props_player_id); continue;
												   }

												   else bplayers_l++;
											   }

										   }

									   }



									   outcome_number = 0;
									   if (DEBUG_OUTPUT == true) printf("start parse market2\r\n");

									   if (_line->outcome_number > 0) { for (int i = 0; i < _line->outcome_number; i++) if (_line->outcome_name[i] != nullptr) delete[] _line->outcome_name[i]; };
									   _line->outcome_number = 0;

									   if (_line->outcome_id != nullptr) delete[] _line->outcome_id; if (_line->outcome_active != nullptr) delete[] _line->outcome_active; if (_line->outcome_team != nullptr) delete[] _line->outcome_team; if (_line->outcome_odds != nullptr) delete[] _line->outcome_odds;
									   if (_line->outcome_probabilities != nullptr) delete[] _line->outcome_probabilities; if (_line->outcome_name != nullptr) delete[] _line->outcome_name;
									   _line->outcome_probabilities = nullptr; _line->outcome_name = nullptr; _line->outcome_id = nullptr; _line->outcome_odds = nullptr; _line->outcome_active = nullptr;
									   _line->outcome_team = nullptr;


									   if (DEBUG_OUTPUT == true) printf("start parse market4\r\n");
									   if (_line->name != nullptr) delete[] _line->name;
									   _line->name = new char[strlen(_market->name) + 1];
									   std::strcpy(_line->name, _market->name);
									   std::strcpy(_line->name, _market->name);

									   for (int i = 0; i < _line->specifier_number; i++) {
										   if (i == _line->variant) continue;

										   replace(_line->name, _line->specifier[i], _line->specifier_value[i], true);
									   }


									   replace(_line->name, "$competitor1", _event->home_name, true);
									   if (_event->away_name != nullptr) replace(_line->name, "$competitor2", _event->away_name, true);
									   if (_event->type_radar > 0) replace(_line->name, "$event", _event->home_name, true);



									   for (xml_node<> * outcome_node = market_node->first_node("outcome"); outcome_node; outcome_node = outcome_node->next_sibling()) {


										   if (outcome_node->first_attribute("active")) outcome_active[outcome_number] = atoi(outcome_node->first_attribute("active")->value());
										   else outcome_active[outcome_number] = 0;
										   if (outcome_node->first_attribute("team")) outcome_team[outcome_number] = atoi(outcome_node->first_attribute("team")->value());
										   else outcome_team[outcome_number] = 0;
										   if (outcome_node->first_attribute("id")) {
											   outcome_id[outcome_number] = atoi((char*)((char*)outcome_node->first_attribute("id")->value() + z));
											   if (outcome_id[outcome_number] == 0 && z > 0) {
												   outcome_id[outcome_number] = atoi(outcome_node->first_attribute("id")->value());
												   if (outcome_id[outcome_number] > 0) outcome_team[outcome_number] = 3;
												   else {
													   std::printf("_line->type=%d line->market_id=%d  _event->type_radar=%d  _line->event_id =%d \r\n", _line->type, _line->market_id, _event->type_radar, _line->event_id); std::printf(outcome_node->first_attribute("id")->value());

												   }
											   }

										   }
										   else outcome_id[outcome_number] = 0;


										   if (outcome_node->first_attribute("odds")) outcome_odds[outcome_number] = atof(outcome_node->first_attribute("odds")->value());
										   else outcome_odds[outcome_number] = 0;
										   if (outcome_node->first_attribute("probabilities")) outcome_probabilities[outcome_number] = atof(outcome_node->first_attribute("probabilities")->value());
										   else outcome_probabilities[outcome_number] = 0;
										   if (outcome_name[outcome_number] != nullptr) delete[] outcome_name[outcome_number]; outcome_name[outcome_number] = nullptr;
										   if (outcome_node->first_attribute("name")) {
											   outcome_name[outcome_number] = new char[strlen(outcome_node->first_attribute("name")->value()) + 1];
											   std::strcpy(outcome_name[outcome_number], outcome_node->first_attribute("name")->value());

										   }

										   outcome_number++;

									   }
									   if (DEBUG_OUTPUT == true) printf("start parse market3\r\n");





									   if (PRINT == true) {

										   std::printf("\r\n"); std::printf(_line->name); std::printf("\r\n"); std::printf("------------------------------------------------------------------------------\r\n");
									   }


									   /*std::strcat(socket_message_big, "\r\n");
									   std::strcat(socket_message_big, _line->name);
									   std::strcat(socket_message_big, "\r\n------------------------------------------------------------------------------\r\n");
									   */



									   _line->outcome_number = outcome_number;
									   if (_line->outcome_number > 0) {
										   _line->outcome_name = new char*[_line->outcome_number];
										   _line->outcome_id = new int[_line->outcome_number];
										   _line->outcome_team = new int[_line->outcome_number];
										   _line->outcome_active = new int[_line->outcome_number];
										   _line->outcome_probabilities = new float[_line->outcome_number];
										   _line->outcome_odds = new float[_line->outcome_number];
										   if (DEBUG_OUTPUT == true) printf("start parse market5 %d\r\n", _market->id);









										   for (int i = 0; i < _line->outcome_number; i++) {
											   _line->outcome_name[i] = nullptr;
											   _line->outcome_id[i] = outcome_id[i];
											   _line->outcome_active[i] = outcome_active[i];
											   _line->outcome_odds[i] = outcome_odds[i];
											   _line->outcome_team[i] = outcome_team[i];
											   _line->outcome_probabilities[i] = outcome_probabilities[i];


											   if (_line->type == 0) {
												   if (_line->outcome_id[i] == _market->outcome_id[i]) u = i;
												   else
													   for (u = 0; u < _market->outcome_number; u++) if (_line->outcome_id[i] == _market->outcome_id[u]) break;

												   if (u < _market->outcome_number) {
													   _line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
													   std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);

												   }
												   else {
													   std::printf("Eror. Outcome name not found. market_id=%d _line->outcome_id[i]=%d\r\n", _line->market_id, _line->outcome_id[i]);

													   _line->outcome_name[i] = new char[2];
													   std::strcpy(_line->outcome_name[i], " ");
													   if (_market->variant > -1) printf("_market->variant=%s\r\n", _market->variable_text);
													   if (outcomeNameError == 0) outcomeNameError = 1;


												   }

												   for (int j = 0; j < _line->specifier_number; j++) {
													   if (j == _line->variant) continue;

													   replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j], true);
												   }

												   replace(_line->outcome_name[i], "$competitor1", _event->home_name, true);
												   if (_event->away_name != nullptr) replace(_line->outcome_name[i], "$competitor2", _event->away_name, true);
												   if (_event->type_radar > 0) replace(_line->outcome_name[i], "$event", _event->home_name, true);



												   if (PRINT == true) {

													   std::printf(_line->outcome_name[i]); std::printf("\t");
													   std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
													   std::printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
												   }
												   /*std::strcat(socket_message_big, _line->outcome_name[i]);
												   std::strcat(socket_message_big, "\t");
												   std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
												   std::strcat(socket_message_big, socket_message_little);
												   std::strcat(socket_message_big, "\t");
												   std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
												   std::strcat(socket_message_big, socket_message_little);
												   */





											   }

											   if (_line->type == 1) {
												   if (_line->outcome_id[i] >= MAX_PLAYERS) {
													   std::printf("ERROR in run. player_id out of MAX_PLAYERS. _line->outcome_id[i]=%d  _line->market_id=%d event_id=%d\r\n", _line->outcome_id[i], _line->market_id, _line->event_id);
													   continue;

												   }

												   if (bplayers_id[_line->outcome_id[i]] == nullptr && _line->outcome_team[i] == 0) {
													   std::printf("Player4 id=%d not found in market id=%d in event_id=%d  in run function team 0 \r\n", _line->outcome_id[i], _line->market_id, _line->event_id);


													   if (getCompetitor(bcompetitors_id[_event->away_id], true) == -1) {
														   std::printf(" Error get bcompetitors away_id=%d \r\n", _event->away_id); //continue;
													   }

													   if (getCompetitor(bcompetitors_id[_event->home_id], true) == -1) {
														   std::printf(" Error get bcompetitors home_id=%d \r\n", _event->home_id); //continue;
													   }

													   if (bplayers_id[_line->outcome_id[i]] == nullptr) {
														   bplayers[bplayers_l].id = _line->outcome_id[i]; if (getPlayer(&bplayers[bplayers_l], true) == -1)
														   {
															   std::printf("error bplayer id=%d  not found \r\n ", _line->outcome_id[i]); //continue;
															   _line->outcome_team[i] = 1;
														   }
														   else    bplayers_l++;
													   }



												   }

												   if (bplayers_id[_line->outcome_id[i]] != nullptr && _line->outcome_team[i] == 0) {
													   if (bplayers_id[_line->outcome_id[i]]->competitor_id == _event->away_id) _line->outcome_team[i] = 2;
													   else if (bplayers_id[_line->outcome_id[i]]->competitor_id == _event->home_id) _line->outcome_team[i] = 1;  else {
														   printf("eror bcompetitor_id in bplayer  bplayer_id=%d  event_id=%d  home_id=%d  away_id=%d run getCompetitor\r\n", _line->outcome_id[i], _line->event_id, _event->home_id, _event->away_id);
														   if (getCompetitor(bcompetitors_id[_event->away_id], true) == -1) {
															   std::printf(" Error get bcompetitors away_id=%d \r\n", _event->away_id); //continue;
														   }

														   if (getCompetitor(bcompetitors_id[_event->home_id], true) == -1) {
															   std::printf(" Error get bcompetitors away_id=%d \r\n", _event->home_id); //continue;
														   }


														   if (bplayers_id[_line->outcome_id[i]]->competitor_id == _event->away_id) _line->outcome_team[i] = 2;
														   else  _line->outcome_team[i] = 1;
													   }
												   }



												   if (bplayers_id[_line->outcome_id[i]] == nullptr && _line->outcome_team[i] == 2) {
													   std::printf("Player4 id=%d not found in market id=%d in event_id=%d  in run function team 2 \r\n", _line->outcome_id[i], _line->market_id, _line->event_id);
													   if (_event->away_id >= MAX_COMPETITORS) {
														   std::printf("ERROR in run. away_id out of MAX_COMPETITORS. away_id=%d event_id=%d\r\n", _event->away_id, _line->event_id);
														   continue;
													   }

													   if (bcompetitors_id[_event->away_id] == nullptr) {
														   std::printf("Competitor id %d not found in team 2 run. getCompetitor\r\n", _event->away_id);
														   bcompetitors[bcompetitors_l].id = _event->away_id;
														   if (getCompetitor(&bcompetitors[bcompetitors_l], true) == -1) {
															   std::printf(" Error get competitors id=%d \r\n", _event->away_id); //continue;
														   }
														   else bcompetitors_l++;


													   }
												   }

												   if (bplayers_id[_line->outcome_id[i]] == nullptr && _line->outcome_team[i] == 1) {
													   std::printf("Player5 id=%d not found in market id=%d in event_id=%d  in run function team 1 \r\n", _line->outcome_id[i], _line->market_id, _line->event_id);
													   if (_event->home_id >= MAX_COMPETITORS) {
														   std::printf("ERROR in run. home_id out of MAX_COMPETITORS. home_id=%d event_id=%d\r\n", _event->home_id, _line->event_id);
														   continue;
													   }

													   if (bcompetitors_id[_event->home_id] == nullptr) {
														   std::printf("Competitor id %d not found in team 1 run. getCompetitor\r\n", _event->home_id);
														   bcompetitors[bcompetitors_l].id = _event->home_id;
														   if (getCompetitor(&bcompetitors[bcompetitors_l], true) == -1) {
															   std::printf(" Error get competitors id=%d \r\n", _event->home_id); //continue;
														   }
														   else bcompetitors_l++;


													   }
												   }


												   if (_line->outcome_team[i] < 3 && bplayers_id[_line->outcome_id[i]] == nullptr) {
													   std::printf("Player6 id=%d  not found in run after get competitor. getPlayer\r\n ", _line->outcome_id[i]);
													   bplayers[bplayers_l].id = _line->outcome_id[i]; if (getPlayer(&bplayers[bplayers_l], true) == -1)
													   {
														   std::printf("error player id=%d  not found \r\n ", _line->outcome_id[i]); //continue;
														   _line->outcome_name[i] = new char[2];
														   std::strcpy(_line->outcome_name[i], " ");
													   }
													   else bplayers_l++;
												   }

												   if (_line->outcome_team[i] < 3 && _line->outcome_name[i] == nullptr) {
													   if (_line->outcome_team[i] == 1) {
														   if (bplayers_id[_line->outcome_id[i]]->full_name != nullptr) {
															   _line->outcome_name[i] = new char[strlen(bplayers_id[_line->outcome_id[i]]->full_name) + strlen(_event->home_name) + 4];
															   std::strcpy(_line->outcome_name[i], bplayers_id[_line->outcome_id[i]]->full_name);
														   }
														   else {

															   _line->outcome_name[i] = new char[strlen(bplayers_id[_line->outcome_id[i]]->name) + strlen(_event->home_name) + 4];
															   std::strcpy(_line->outcome_name[i], bplayers_id[_line->outcome_id[i]]->name);
														   }



														   std::strcat(_line->outcome_name[i], " (");
														   std::strcat(_line->outcome_name[i], _event->home_name);
														   std::strcat(_line->outcome_name[i], ")");

													   }
													   if (_line->outcome_team[i] == 2) {

														   if (bplayers_id[_line->outcome_id[i]]->full_name != nullptr) {
															   if (_event->away_name != nullptr) _line->outcome_name[i] = new char[strlen(bplayers_id[_line->outcome_id[i]]->full_name) + strlen(_event->away_name) + 4]; else _line->outcome_name[i] = new char[strlen(bplayers_id[_line->outcome_id[i]]->full_name) + 1];
															   std::strcpy(_line->outcome_name[i], bplayers_id[_line->outcome_id[i]]->full_name);
														   }
														   else {
															   if (_event->away_name != nullptr) _line->outcome_name[i] = new char[strlen(bplayers_id[_line->outcome_id[i]]->name) + strlen(_event->away_name) + 4]; else _line->outcome_name[i] = new char[strlen(bplayers_id[_line->outcome_id[i]]->name) + 1];
															   std::strcpy(_line->outcome_name[i], bplayers_id[_line->outcome_id[i]]->name);
														   }


														   if (_event->away_name != nullptr) {
															   std::strcat(_line->outcome_name[i], " (");
															   std::strcat(_line->outcome_name[i], _event->away_name);
															   std::strcat(_line->outcome_name[i], ")");
														   }

													   }

												   }

												   if (_line->outcome_team[i] == 3) {

													   for (u = 0; u < _market->outcome_number; u++) if (_market->outcome_id[u] == _line->outcome_id[i]) break;
													   if (u < _market->outcome_number) {
														   _line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
														   std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);

														   for (int j = 0; j < _line->specifier_number; j++) {
															   if (j == _line->variant) continue;

															   replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j], true);
														   }

														   replace(_line->outcome_name[i], "$competitor1", _event->home_name, true);
														   replace(_line->outcome_name[i], "$competitor2", _event->away_name, true);
														   if (_event->type_radar > 0) replace(_line->outcome_name[i], "$event", _event->home_name, true);



													   }
													   else {
														   _line->outcome_name[i] = new char[2];
														   std::strcpy(_line->outcome_name[i], " ");
													   }



												   }





												   if (PRINT == true) {



													   std::printf(_line->outcome_name[i]); std::printf("\t");
													   std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
													   printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
												   }
												   /*
												   std::strcat(socket_message_big, _line->outcome_name[i]);
												   std::strcat(socket_message_big, "\t");
												   std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
												   std::strcat(socket_message_big, socket_message_little);
												   std::strcat(socket_message_big, "\t");
												   std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
												   std::strcat(socket_message_big, socket_message_little);


												   */

											   }

											   if (_line->type == 2) {
												   if (_line->outcome_team[i] != 3) {
													   if (_line->outcome_id[i] >= MAX_COMPETITORS) {
														   std::printf("ERROR in run. competitor_id out of MAX_COMPETITORS. _line->outcome_id[i]=%d  _line->market_id=%d event_id=%d\r\n", _line->outcome_id[i], _line->market_id, _line->event_id);
														   continue;
													   }
													   if (bcompetitors_id[_line->outcome_id[i]] == nullptr) {
														   std::printf("Competitor id=%d not found in market id=%d in event_id=%d  in run function. getTournament\r\n", _line->outcome_id[i], _line->market_id, _line->event_id);
														   //btournaments[btournaments_l].id = _event->tournament_id;
														   //btournaments[btournaments_l].type_radar = _event->type_radar;

														   if (_event->type_radar == 0 && getTournament(btournaments_id[_event->tournament_id], false, true) == -1)
															   std::printf("ERROR!\r\nTournaments not found in run %d \r\n", _event->tournament_id);

														   if (_event->type_radar == 2 && getTournament(bsimples_id[_event->simple_id], false, true) == -1)
															   std::printf("ERROR!\r\nSimples Tournaments not found in run %d \r\n", _event->simple_id);

													   }

													   if (bcompetitors_id[_line->outcome_id[i]] == nullptr) {
														   std::printf("\r\nCompetitors id=%d not found in tournament id=%d . Run getCompetitor\r\n", _line->outcome_id[i], _event->tournament_id);
														   bcompetitors[bcompetitors_l].id = _line->outcome_id[i];
														   if (getCompetitor(&bcompetitors[bcompetitors_l], true) == -1) {
															   std::printf(" Error get competitors in run function line type= 2 id=%d \r\n", _line->outcome_id[i]);
															   _line->outcome_name[i] = new char[2];
															   std::strcpy(_line->outcome_name[i], " ");
														   }
														   else bcompetitors_l++;
													   }

													   if (bcompetitors_id[_line->outcome_id[i]] != nullptr) { _line->outcome_name[i] = new char[strlen(bcompetitors_id[_line->outcome_id[i]]->name) + 1]; std::strcpy(_line->outcome_name[i], bcompetitors_id[_line->outcome_id[i]]->name); }

												   }
												   else
												   {
													   for (u = 0; u < _market->outcome_number; u++) if (_market->outcome_id[u] == _line->outcome_id[i]) break;
													   if (u < _market->outcome_number) {
														   _line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
														   std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);
														   for (int j = 0; j < _line->specifier_number; j++) {
															   if (j == _line->variant) continue;
															   replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j], true);
														   }
														   replace(_line->outcome_name[i], "$competitor1", _event->home_name, true);
														   replace(_line->outcome_name[i], "$competitor2", _event->away_name, true);
														   if (_event->type_radar > 0) replace(_line->outcome_name[i], "$event", _event->home_name, true);
													   }
													   else { _line->outcome_name[i] = new char[2]; std::strcpy(_line->outcome_name[i], " "); }
												   }
												   if (PRINT == true) {
													   std::printf(_line->outcome_name[i]); std::printf("\t");
													   std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
													   printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
												   }
												   /*
												   std::strcat(socket_message_big, _line->outcome_name[i]);
												   std::strcat(socket_message_big, "\t");
												   std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
												   std::strcat(socket_message_big, socket_message_little);
												   std::strcat(socket_message_big, "\t");
												   std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
												   std::strcat(socket_message_big, socket_message_little);
												   */

											   }

											   if (_line->type == 3) {

												   if (_line->outcome_id[i] == _market->outcome_id[i]) u = i;
												   else
													   for (u = 0; u < _market->outcome_number; u++) {


														   if (_line->outcome_id[i] == _market->outcome_id[u]) break;
													   }

												   if (u < _market->outcome_number) {

													   _line->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
													   std::strcpy(_line->outcome_name[i], _market->outcome_name[u]);

												   }
												   else {
													   std::printf("Eror. Outcome name not found. market_id=%d _line->outcome_id[i]=%d\r\n", _line->market_id, _line->outcome_id[i]);
													   _line->outcome_name[i] = new char[2];
													   std::strcpy(_line->outcome_name[i], " ");
													   if (_market->variant > -1) printf("_market->variant=%s\r\n", _market->variable_text);
													   if (outcomeNameError == 0) outcomeNameError = 1;
												   }

												   for (int j = 0; j < _line->specifier_number; j++) {
													   if (j == _line->variant) continue;

													   replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j], true);
												   }

												   replace(_line->outcome_name[i], "$competitor1", _event->home_name, true);
												   replace(_line->outcome_name[i], "$competitor2", _event->away_name, true);
												   if (_event->type_radar > 0) replace(_line->outcome_name[i], "$event", _event->home_name, true);


												   //if (_line->market_id == 188 || _line->market_id == 224 || _line->market_id == 485 || _line->market_id == 231 || _line->market_id == 65 || _line->market_id == 383 || _line->market_id == 66) 

												   if (PRINT == true) {

													   std::printf(_line->outcome_name[i]); std::printf("\t");
													   std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
													   printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
												   }
												   /*
												   std::strcat(socket_message_big, _line->outcome_name[i]);
												   std::strcat(socket_message_big, "\t");
												   std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
												   std::strcat(socket_message_big, socket_message_little);
												   std::strcat(socket_message_big, "\t");
												   std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
												   std::strcat(socket_message_big, socket_message_little);*/




											   }

											   if (_line->type == 4) {

												   if (_line->outcome_team[i] == 2) _line->outcome_name[i] = new char[strlen(bplayers_id[props_player_id]->full_name) + 14 + strlen(_event->away_name)];
												   else  _line->outcome_name[i] = new char[strlen(bplayers_id[props_player_id]->full_name) + 14 + strlen(_event->home_name)];

												  std::strcpy(_line->outcome_name[i], bplayers_id[props_player_id]->full_name);
												   //strcat(_line->outcome_name[i], " (");
												   //if (_line->outcome_team[i] == 2) strcat(_line->outcome_name[i], _event->away_name);
												   //else strcat(_line->outcome_name[i], _event->home_name);
												   //strcat(_line->outcome_name[i], ") ");
												   strcat(_line->outcome_name[i], " ");
												   _itoa(_line->outcome_id[i], buf, 10);
												   strcat(_line->outcome_name[i], buf);
												   strcat(_line->outcome_name[i], ".0+");


												   if (PRINT == true) {

													   std::printf(_line->outcome_name[i]); std::printf("\t");
													   std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
													   printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
												   }
												   /*
												   std::strcat(socket_message_big, _line->outcome_name[i]);
												   std::strcat(socket_message_big, "\t");
												   std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
												   std::strcat(socket_message_big, socket_message_little);
												   std::strcat(socket_message_big, "\t");
												   std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
												   std::strcat(socket_message_big, socket_message_little);*/




											   }



										   }



										   if (outcomeNameError == 1 && _market->variant > -1) goto outcomeNameError3;
									   }
									   if (DEBUG_OUTPUT == true) printf("start parse market6\r\n");

									   if (DEBUG_OUTPUT == true) printf("insertLine _line->type ==%d\r\n", _line->type);
									   if (DEBUG_OUTPUT == true) {
										   printf(_line ->getCompoundKey().c_str());
										   printf("\r\n");
									   }
									   auto it = bcompound2line_index.find(_line ->getCompoundKey());
									   if (DEBUG_OUTPUT == true) printf("auto it\r\n");

									   if (it == bcompound2line_index.end()) {
										   if (DEBUG_OUTPUT == true) printf("new line add ");
										   _line->id = blines_l;
										   if (DEBUG_OUTPUT == true) printf("new line add1 ");
										   blines[blines_l] = (*_line);
										   blines_id[_line->id] = &blines[blines_l];
										   if (DEBUG_OUTPUT == true) printf("new line add2 ");
										   binsert_line(_line, blines_l);
										   if (DEBUG_OUTPUT == true) printf("new line add3 ");
										   blines_l++;
										   if (DEBUG_OUTPUT == true) printf("new line add finish\r\n");

									   }
									   else {
										   if (DEBUG_OUTPUT == true) printf("line update");
										   _line->id = it->second;
										   if (DEBUG_OUTPUT == true) printf("line update1");
										   blines[it->second] = (*_line);
										   if (DEBUG_OUTPUT == true) printf("line finish\r\n");

										   //printf("Line Update\r\n");
									   }

									   if (DEBUG_OUTPUT == true) printf("end insertLine _line->type ==%d\r\n", _line->type);




					}
				}

				if (_event->status > 0) _event->bet_stop = 0;
				else  if (_event->status == 0 && _event->bet_stop == 1) {
					int active_lines_counter = 0;
					if (bevent2lines.find(_event->getCatKey()) == bevent2lines.end()) {}
					else for (unordered_set<int>::iterator it = bevent2lines[_event->getCatKey()]->begin(); it != bevent2lines[_event->getCatKey()]->end(); ++it)
						if (blines[*(it)].status == 1) active_lines_counter++;
					if (active_lines_counter > 0) _event->bet_stop = 0;

				}
			}

			if (DEBUG_OUTPUT == true) printf("end parse type_radar=%d\r\n", type_radar);


			//delete[] zip_message;










		}
		else if (std::strcmp("snapshot_complete", doc.first_node()->name()) == 0) {
			new_message_arrived = true;

		}
		else  if (std::strcmp("bet_settlement", doc.first_node()->name()) == 0 || std::strcmp("rollback_bet_settlement", doc.first_node()->name()) == 0
			|| std::strcmp("bet_cancel", doc.first_node()->name()) == 0 || std::strcmp("rollback_bet_cancel", doc.first_node()->name()) == 0)
		{
			if (std::strcmp("bet_settlement", doc.first_node()->name()) == 0) settlement_type = 0; else
				if (std::strcmp("rollback_bet_settlement", doc.first_node()->name()) == 0) settlement_type = 1; else
					if (std::strcmp("bet_cancel", doc.first_node()->name()) == 0) settlement_type = 2; else
						if (std::strcmp("rollback_bet_cancel", doc.first_node()->name()) == 0) settlement_type = 3;
			type_radar = 0;
			event_id = 0;
			if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:season:", 10) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 10)); type_radar = 3;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:match:", 9) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
				 type_radar = 0;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:simple_tournament:", 21) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 21)); type_radar = 2;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:race_tournament:", 19) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 19)); type_radar = 4;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:match:", 9) == 0) { event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9)); type_radar = 5;continue; }
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:season:", 10) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 10)); type_radar = 6; continue;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:tournament:", 14) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 14)); type_radar = 7; continue;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:stage:", 9) == 0)
			{
				type_radar = 1; event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
				key = "1" + string((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
				if (bevents_id.find(key) != bevents_id.end() && (event_id >= MAX_TOURNAMENTS || btournaments_id[event_id] == nullptr)) type_radar = 1;
				else if (bevents_id.find(key) == bevents_id.end() && event_id < MAX_TOURNAMENTS && btournaments_id[event_id] != nullptr) type_radar = 4;
				else if (bevents_id.find(key) == bevents_id.end() && (event_id >= MAX_TOURNAMENTS || btournaments_id[event_id] == nullptr)) {
					type_radar = -1;
					btournaments[btournaments_l].id = event_id;
					btournaments[btournaments_l].type_radar = 1;
					btournaments[btournaments_l].season_id = 0;
					btournaments[btournaments_l].simple_id = 0;
					if (event_id >= MAX_TOURNAMENTS || getTournament(&btournaments[btournaments_l], false, true) == -1) {

						btournaments[btournaments_l].id = 0; btournaments[btournaments_l].type_radar = 0;
						bevents[bevents_l].id = event_id; bevents[bevents_l].type_radar = 1;
						ret_fixture = getEventFixture(&bevents[bevents_l], true);
						if (ret_fixture == -1) {
							bevents[bevents_l].id = 0; bevents[bevents_l].type_radar = 0;
						}
						else { bevents_l++; type_radar = 1; }
					}
					else { type_radar = 4;  btournaments_l++; }
				}
				if (type_radar == -1) continue;
			}

			else { std::printf("Unknown type radar in bet_settlement_change =%s", (char*)doc.first_node()->first_attribute("event_id")->value()); continue; };
			//0 sr:match://1 sr:race_event: //2 sr:simple_tournament://3 sr:season://4:sr:race_tournament:
			key = to_string(type_radar) + to_string(event_id);
			_bet->type_radar = type_radar;
			_bet->key = key;
			//	printf("\r\n\r\n\r\nbet_settlement =\r\n\r\n\r\n%s\r\n\r\n\r\n", AMQP_message[(bprocess_index - 1) % AMQP_QUEUE]);


			if (event_id == 0) {
				std::printf("event_id in bet_settlement error=0\r\n"); std::printf(doc.first_node()->first_attribute("event_id")->value());
				continue;
			}

			if (doc.first_node()->first_attribute("certainy")) _bet->certainy = atoi(doc.first_node()->first_attribute("certainy")->value());
			if (doc.first_node()->first_attribute("timestamp")) _bet->timestamp = atoi(doc.first_node()->first_attribute("timestamp")->value()) * 1000;
			if (doc.first_node()->first_attribute("superceded_by")) _bet->superceded_by = atoi(doc.first_node()->first_attribute("superceded_by")->value());
			else _bet->superceded_by = 0;


			if (doc.first_node()->first_attribute("start_time")) {
				strcpy(buf, doc.first_node()->first_attribute("start_time")->value());
				st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
				sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

				tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
				tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
				start = mktime(&tm);
				_bet->start_time = (int)start;

			}
			else _bet->start_time = 0;

			if (doc.first_node()->first_attribute("end_time")) {
				strcpy(buf, doc.first_node()->first_attribute("end_time")->value());
				st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
				sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

				tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
				tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
				start = mktime(&tm);
				_bet->end_time = (int)start;

			}
			else _bet->end_time = 0;

			if (DEBUG_OUTPUT == true) printf("bet_settlement type_radar=%d  settlement_type=%d\r\n", type_radar, settlement_type);
			//printf("bet_settlement type_radar=%d  settlement_type=%d\r\n", type_radar, settlement_type);
			//printf("xml = %s\r\n", AMQP_message[(bprocess_index - 1) % AMQP_QUEUE]);
			//printf("bet_settlement type_radar=%d\r\n", type_radar);

			xml_node<> * outcomes = doc.first_node()->first_node("outcomes");
			if (outcomes == nullptr)  outcomes = doc.first_node();

			
			if (outcomes != nullptr) {
				_bet->tournament_id = 0;
				_bet->event_id = 0;
				_bet->simple_id = 0;
				

				if (type_radar == 2) _bet->simple_id = event_id;//simple_tournament
				if (type_radar == 3) if (event_id < MAX_TOURNAMENTS && seasons_id[event_id] != nullptr) _bet->tournament_id = seasons_id[event_id]->id;//season
				if (type_radar == 4)_bet->tournament_id = event_id;//race_tournament
				if (type_radar == 0 || type_radar == 1 || type_radar == 5) _bet->event_id = event_id;//sr:match sr:race_event
				
				for (xml_node<> * market_node = outcomes->first_node("market"); market_node; market_node = market_node->next_sibling())
				{
					settlementError = 0;
					if (market_node->first_attribute("void_reason")) _bet->void_reason = atoi(market_node->first_attribute("void_reason")->value());
					else _bet->void_reason = 0;
					if (market_node->first_attribute("id")) _bet->market_id = atoi(market_node->first_attribute("id")->value());
					if (_bet->market_id >= MAX_MARKETS) {
						std::printf("ERROR DATA!\r\nmarket id out of MAX_MARKETS in bet_settlement%d\r\n", _bet->market_id); continue;
					}
					if (bmarkets_id[_bet->market_id] == nullptr) {
						std::printf("ERROR DATA!\r\nmarket id not found in bet_settlement%d\r\n", _bet->market_id); continue;
					};
					if (bmarkets_id[_bet->market_id][0] == nullptr) {
						std::printf("ERROR DATA!\r\nmarket id 0 not found in bet_settlement%d\r\n", _bet->market_id); continue;
					};
					_bet->variant = bmarkets_id[_bet->market_id][0]->variant;
					_bet->type = bmarkets_id[_bet->market_id][0]->type;
					if (_bet->specifier_number > 0) for (q = 0; q < _bet->specifier_number; q++) {
						if (_bet->specifier[q] != nullptr) delete[] _bet->specifier[q]; _bet->specifier[q] = nullptr;
						if (_bet->specifier_value[q] != nullptr)  delete[] _bet->specifier_value[q]; _bet->specifier_value[q] = nullptr;
					}
					if (_bet->specifier != nullptr) { delete[] _bet->specifier; _bet->specifier = nullptr; }
					if (_bet->specifier_value != nullptr) { delete[] _bet->specifier_value; _bet->specifier_value = nullptr; }
					_bet->specifier_number = 0;
					if (_bet->extended_specifier_number > 0) for (q = 0; q < _bet->extended_specifier_number; q++) {
						if (_bet->extended_specifier[q] != nullptr) delete[] _bet->extended_specifier[q];
						if (_bet->extended_specifier_value[q] != nullptr)  delete[] _bet->extended_specifier_value[q];
					}
					if (_bet->extended_specifier != nullptr) { delete[] _bet->extended_specifier; _bet->extended_specifier = nullptr; }
					if (_bet->extended_specifier_value != nullptr) { delete[] _bet->extended_specifier_value; _bet->extended_specifier_value = nullptr; }
					_bet->extended_specifier_number = 0;
					if (market_node->first_attribute("specifiers")) {
						n = 0;
						m = market_node->first_attribute("specifiers")->value_size();
						for (q = 0; q < m; q++) {
							if (market_node->first_attribute("specifiers")->value()[q] == '=')
								index_equally[n] = q;

							if (market_node->first_attribute("specifiers")->value()[q] == '|') {
								index_separator[n] = q; n++;
							}

						}
						index_separator[n] = q; n++;

						_bet->specifier_number = n;
						if (_bet->specifier_number > 0) {
							_bet->specifier_value = new char*[_bet->specifier_number];
							_bet->specifier = new char*[_bet->specifier_number];


							for (q = 0; q < _bet->specifier_number; q++) {
								if (q > 0) {
									_bet->specifier[q] = new char[index_equally[q] - index_separator[q - 1]];
									strncpy(_bet->specifier[q], (char*)((char*)market_node->first_attribute("specifiers")->value() + index_separator[q - 1]) + 1, index_equally[q] - index_separator[q - 1] - 1);
									_bet->specifier[q][index_equally[q] - index_separator[q - 1] - 1] = 0;
								}
								else {
									_bet->specifier[q] = new char[index_equally[q] + 1]; strncpy(_bet->specifier[q], market_node->first_attribute("specifiers")->value(), index_equally[q]); _bet->specifier[q][index_equally[q]] = 0;


								}

								_bet->specifier_value[q] = new char[index_separator[q] - index_equally[q]];
								strncpy(_bet->specifier_value[q], (char*)((char*)market_node->first_attribute("specifiers")->value() + index_equally[q]) + 1, index_separator[q] - index_equally[q] - 1);
								_bet->specifier_value[q][index_separator[q] - index_equally[q] - 1] = 0;



							}
						}
					}
					if (market_node->first_attribute("extended_specifiers")) {
						n = 0;
						m = market_node->first_attribute("extended_specifiers")->value_size();
						for (q = 0; q < m; q++) {
							if (market_node->first_attribute("extended_specifiers")->value()[q] == '=')
								index_equally[n] = q;

							if (market_node->first_attribute("extended_specifiers")->value()[q] == '|') {
								index_separator[n] = q; n++;
							}

						}
						index_separator[n] = q; n++;



						_bet->extended_specifier_number = n;
						if (_bet->extended_specifier_number > 0) {
							_bet->extended_specifier_value = new char*[_bet->extended_specifier_number];
							_bet->extended_specifier = new char*[_bet->extended_specifier_number];


							for (q = 0; q < _bet->extended_specifier_number; q++) {
								if (q > 0) {
									_bet->extended_specifier[q] = new char[index_equally[q] - index_separator[q - 1]];
									strncpy(_bet->extended_specifier[q], (char*)((char*)market_node->first_attribute("extended_specifiers")->value() + index_separator[q - 1]) + 1, index_equally[q] - index_separator[q - 1] - 1);
									_bet->extended_specifier[q][index_equally[q] - index_separator[q - 1] - 1] = 0;
								}
								else {
									_bet->extended_specifier[q] = new char[index_equally[q] + 1]; strncpy(_bet->extended_specifier[q], market_node->first_attribute("extended_specifiers")->value(), index_equally[q]); _bet->extended_specifier[q][index_equally[q]] = 0;


								}

								_bet->extended_specifier_value[q] = new char[index_separator[q] - index_equally[q]];
								strncpy(_bet->extended_specifier_value[q], (char*)((char*)market_node->first_attribute("extended_specifiers")->value() + index_equally[q]) + 1, index_separator[q] - index_equally[q] - 1);
								_bet->extended_specifier_value[q][index_separator[q] - index_equally[q] - 1] = 0;
								//printf(_bet->extended_specifier[q]);std::printf("\r\n");std::printf(_bet->extended_specifier_value[q]);std::printf("\r\n");


							}
						}
					}






				settlementError1:
					if (_bet->variant > -1 && _bet->type != 4) {
						z = strlen(_bet->specifier_value[_bet->variant]) + 1; if (strcmp(_bet->specifier[_bet->variant], "variant") != 0) { std::printf(_bet->specifier[_bet->variant]); std::printf("\r\n"); }


						for (u = 0; u < bmax_markets_in[_bet->market_id]; u++) if (bmarkets_id[_bet->market_id][u] != nullptr && bmarkets_id[_bet->market_id][u]->variable_text != nullptr && std::strcmp(_bet->specifier_value[_bet->variant], bmarkets_id[_bet->market_id][u]->variable_text) == 0) break;
						if (settlementError == 1 || u == bmax_markets_in[_bet->market_id]) {
							std::printf("Variant market not found in bet_settlement. Market_id=%d variant=", _bet->market_id);  std::printf(_bet->specifier_value[_bet->variant]);  std::printf(" getVariantMarket\r\n"); if (getVariantMarket(bmarkets_id[_bet->market_id][0], _bet->specifier_value[_bet->variant], true, true) == -1) { std::printf("variant market not found "); continue; }
							for (u = 0; u < bmax_markets_in[_bet->market_id]; u++) if (bmarkets_id[_bet->market_id][u] != nullptr && bmarkets_id[_bet->market_id][u]->variable_text != nullptr && std::strcmp(_bet->specifier_value[_bet->variant], bmarkets_id[_bet->market_id][u]->variable_text) == 0) break;
						}
						_market = bmarkets_id[_bet->market_id][u];
						if (settlementError == 1) settlementError = 2;

						if (_bet->type == 3) z = 16;
					}
					else {
						_market = bmarkets_id[_bet->market_id][0]; if (_bet->type == 0) z = 0; else if (_bet->type == 1) z = 10; else if (_bet->type == 2) z = 14; else if (_bet->type == 3) z = 16;
						if (_bet->type == 4) {
							z = strlen(_bet->specifier_value[_bet->variant]) + 1;
							int in_dot = 0;
							for (int q = 0; q < z - 2; q++) {
								if (_bet->specifier_value[_bet->variant][q] == ':') in_dot++;
								if (in_dot == 3) {
									props_player_id = atoi((char*)((char*)_bet->specifier_value[_bet->variant] + q + 1)); break;
								}
							}

							if (props_player_id >= MAX_PLAYERS) {
								printf("ERROR props_player_id out of MAX_PLAYERS bet_settlement props_player_id=%d\r\n", props_player_id); continue;
							}

							if (bplayers_id[props_player_id] == nullptr) {
								std::printf("props_player_id=%d  not found . getPlayer\r\n ", props_player_id);
								bplayers[bplayers_l].id = props_player_id; if (getPlayer(&bplayers[bplayers_l], true) == -1)
								{
									std::printf("error props_player_id=%d  in getPlayer returned -1 \r\n ", props_player_id); continue;
								}

								else bplayers_l++;
							}

						}



					}


					if (_bet->outcome_number > 0) { for (int i = 0; i < _bet->outcome_number; i++) if (_bet->outcome_name[i] != nullptr) delete[] _bet->outcome_name[i]; };
					_bet->outcome_number = 0;

					if (_bet->outcome_result != nullptr) delete[] _bet->outcome_result; _bet->outcome_result = nullptr;
					if (_bet->outcome_dead_heat_factor != nullptr) delete[] _bet->outcome_dead_heat_factor; _bet->outcome_dead_heat_factor = nullptr;
					if (_bet->outcome_void_factor != nullptr)  delete[] _bet->outcome_void_factor; _bet->outcome_void_factor = nullptr;
					if (_bet->outcome_id != nullptr) delete[] _bet->outcome_id;  _bet->outcome_id = nullptr;
					if (_bet->outcome_active != nullptr) delete[] _bet->outcome_active; _bet->outcome_active = nullptr;
					if (_bet->outcome_team != nullptr) delete[] _bet->outcome_team; _bet->outcome_team = nullptr;
					if (_bet->outcome_odds != nullptr) delete[] _bet->outcome_odds; _bet->outcome_odds = nullptr;
					if (_bet->outcome_probabilities != nullptr) delete[] _bet->outcome_probabilities; _bet->outcome_probabilities = nullptr;
					if (_bet->outcome_name != nullptr) delete[] _bet->outcome_name; _bet->outcome_name = nullptr;
					if (_bet->name != nullptr) delete[] _bet->name;


					_bet->name = new char[strlen(_market->name) + 1];
					std::strcpy(_bet->name, _market->name);
					for (int i = 0; i < _bet->specifier_number; i++) {
						if (i == _bet->variant) continue;
						replace(_bet->name, _bet->specifier[i], _bet->specifier_value[i], true);
					}


					outcome_number = 0;
					for (xml_node<> * outcome_node = market_node->first_node("outcome"); outcome_node; outcome_node = outcome_node->next_sibling()) {
						outcome_team[outcome_number] = 0;
						outcome_active[outcome_number] = 0;
						outcome_odds[outcome_number] = 0;
						outcome_probabilities[outcome_number] = 0;
						if (outcome_node->first_attribute("result")) outcome_result[outcome_number] = atoi(outcome_node->first_attribute("result")->value());
						else outcome_result[outcome_number] = 0;
						if (outcome_node->first_attribute("void_factor")) {
							if (outcome_node->first_attribute("void_factor")->value()[0] == '0' && outcome_node->first_attribute("void_factor")->value()[1] == '.' && outcome_node->first_attribute("void_factor")->value()[3] == '5') outcome_void_factor[outcome_number] = 2;
							else if (outcome_node->first_attribute("void_factor")->value()[0] == '1') outcome_void_factor[outcome_number] = 1;
							else outcome_void_factor[outcome_number] = 0;
						}
						else outcome_void_factor[outcome_number] = 0;

						if (outcome_node->first_attribute("dead_heat_factor")) outcome_dead_heat_factor[outcome_number] = atoi(outcome_node->first_attribute("dead_heat_factor")->value());
						else outcome_dead_heat_factor[outcome_number] = 0;



						if (outcome_node->first_attribute("id")) {
							outcome_id[outcome_number] = atoi((char*)((char*)outcome_node->first_attribute("id")->value() + z));
							if (outcome_id[outcome_number] == 0 && z > 0) {
								outcome_id[outcome_number] = atoi(outcome_node->first_attribute("id")->value());
								if (outcome_id[outcome_number] > 0) outcome_team[outcome_number] = 3;
								else {
									std::printf("_bet->type=%d _bet->market_id=%d  _bet->type_radar=%d  \r\n", _bet->type, _bet->market_id, _bet->type_radar, _bet->type_radar); std::printf(outcome_node->first_attribute("id")->value());

								}
							}

						}
						else outcome_id[outcome_number] = 0;




						if (outcome_name[outcome_number] != nullptr) delete[] outcome_name[outcome_number];
						outcome_name[outcome_number] = nullptr;
						if (outcome_node->first_attribute("name")) {
							outcome_name[outcome_number] = new char[strlen(outcome_node->first_attribute("name")->value()) + 1];
							std::strcpy(outcome_name[outcome_number], outcome_node->first_attribute("name")->value());

						}

						outcome_number++;

					}
					//if (bsimples_id[_bet->simple_id]->name != nullptr) replace(_bet->name, "$event", bsimples_id[_bet->simple_id]->name, true);
					_bet->outcome_number = outcome_number;
					if (_bet->outcome_number > 0) {
						_bet->outcome_name = new char*[_bet->outcome_number];
						_bet->outcome_id = new int[_bet->outcome_number];
						_bet->outcome_result = new int[_bet->outcome_number];
						_bet->outcome_void_factor = new int[_bet->outcome_number];
						_bet->outcome_dead_heat_factor = new int[_bet->outcome_number];
						_bet->outcome_team = new int[_bet->outcome_number];
						_bet->outcome_active = new int[_bet->outcome_number];
						_bet->outcome_probabilities = new float[_bet->outcome_number];
						_bet->outcome_odds = new float[_bet->outcome_number];


						for (int i = 0; i < _bet->outcome_number; i++) {
							_bet->outcome_name[i] = nullptr;
							_bet->outcome_id[i] = outcome_id[i];
							_bet->outcome_active[i] = outcome_active[i];
							_bet->outcome_result[i] = outcome_result[i];
							_bet->outcome_void_factor[i] = outcome_void_factor[i];
							_bet->outcome_dead_heat_factor[i] = outcome_dead_heat_factor[i];
							_bet->outcome_odds[i] = outcome_odds[i];
							_bet->outcome_team[i] = outcome_team[i];
							_bet->outcome_probabilities[i] = outcome_probabilities[i];

							//	printf("_bet->outcome_number=%d _bet->type=%d\r\n", _bet->outcome_number, _bet->type);

							if (_bet->type == 0) {
								if (_bet->outcome_id[i] == _market->outcome_id[i]) u = i;
								else
									for (u = 0; u < _market->outcome_number; u++) if (_bet->outcome_id[i] == _market->outcome_id[u]) break;

								if (u < _market->outcome_number) {
									_bet->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
									std::strcpy(_bet->outcome_name[i], _market->outcome_name[u]);

								}
								else {
									std::printf("Eror. Outcome name not found. market_id=%d _bet->outcome_id[i]=%d GoTo GetVarianMarket \r\n", _bet->market_id, _bet->outcome_id[i]);
									_bet->outcome_name[i] = new char[2];
									std::strcpy(_bet->outcome_name[i], " ");
									if (_market->variant > -1) printf("_market->variant=%s\r\n", _market->variable_text);
									if (settlementError == 0) settlementError = 1;


								}

								for (int j = 0; j < _bet->specifier_number; j++) {
									if (j == _bet->variant) continue;

									replace(_bet->outcome_name[i], _bet->specifier[j], _bet->specifier_value[j], true);
								}

								//	 if (bsimples_id[_bet->simple_id]->name != nullptr) replace(_bet->outcome_name[i], "$event", bsimples_id[_bet->simple_id]->name, true);




							}
							if (_bet->type == 1) {
								if (_bet->outcome_id[i] >= MAX_PLAYERS) {
									std::printf("ERROR in run. player_id out of MAX_PLAYERS. _bet->outcome_id[i]=%d  _bet->market_id=%d \r\n", _bet->outcome_id[i], _bet->market_id);
									continue;

								}
								if (_bet->outcome_team[i] != 3) {
									if (bplayers_id[_bet->outcome_id[i]] == nullptr) {
										std::printf("Player2 id=%d not found in market id=%d  in bet_settlement . getPlayer\r\n", _bet->outcome_id[i], _bet->market_id);
										bplayers[bplayers_l].id = _bet->outcome_id[i]; if (getPlayer(&bplayers[bplayers_l], true) == -1)
										{
											std::printf("error player id=%d  not found \r\n ", _bet->outcome_id[i]); //continue;
											_bet->outcome_name[i] = new char[2];
											std::strcpy(_bet->outcome_name[i], " ");
										}
										else bplayers_l++;
									}

									if (_bet->outcome_name[i] == nullptr) {
										_bet->outcome_name[i] = new char[strlen(bplayers_id[_bet->outcome_id[i]]->name) + 1];
										std::strcpy(_bet->outcome_name[i], bplayers_id[_bet->outcome_id[i]]->name);
									}

								}
								if (_bet->outcome_team[i] == 3) {

									for (u = 0; u < _market->outcome_number; u++) if (_market->outcome_id[u] == _bet->outcome_id[i]) break;
									if (u < _market->outcome_number) {
										_bet->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
										std::strcpy(_bet->outcome_name[i], _market->outcome_name[u]);

										for (int j = 0; j < _bet->specifier_number; j++) {
											if (j == _bet->variant) continue;
											replace(_bet->outcome_name[i], _bet->specifier[j], _bet->specifier_value[j], true);
										}



									}
									else {
										_bet->outcome_name[i] = new char[2];
										std::strcpy(_bet->outcome_name[i], " ");
									}



								}

							}
							if (_bet->type == 2) {
								if (_bet->outcome_team[i] != 3) {
									if (_bet->outcome_id[i] >= MAX_COMPETITORS) {
										std::printf("ERROR in run. competitor_id out of MAX_COMPETITORS. _bet->outcome_id[i]=%d  _bet->market_id=%d \r\n", _bet->outcome_id[i], _bet->market_id, _tournament->simple_id);
										continue;
									}

									if (bcompetitors_id[_bet->outcome_id[i]] == nullptr) {
										std::printf("\r\nCompetitors id=%d not found in bet_settlement . Run getCompetitor\r\n", _bet->outcome_id[i]);
										bcompetitors[bcompetitors_l].id = _bet->outcome_id[i];
										if (getCompetitor(&bcompetitors[bcompetitors_l], true) == -1) {
											std::printf(" Error getCompetitor in bet_settlement. line type= 2 id competitor=%d \r\n", _bet->outcome_id[i]);
											_bet->outcome_name[i] = new char[2];
											std::strcpy(_bet->outcome_name[i], " ");
										}
										else bcompetitors_l++;
									}

									if (bcompetitors_id[_bet->outcome_id[i]] != nullptr) { _bet->outcome_name[i] = new char[strlen(bcompetitors_id[_bet->outcome_id[i]]->name) + 1]; std::strcpy(_bet->outcome_name[i], bcompetitors_id[_bet->outcome_id[i]]->name); }

								}
								else
								{
									for (u = 0; u < _market->outcome_number; u++) if (_market->outcome_id[u] == _bet->outcome_id[i]) break;
									if (u < _market->outcome_number) {
										_bet->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
										std::strcpy(_bet->outcome_name[i], _market->outcome_name[u]);
										for (int j = 0; j < _bet->specifier_number; j++) {
											if (j == _bet->variant) continue;
											replace(_bet->outcome_name[i], _bet->specifier[j], _bet->specifier_value[j], true);
										}


									}
									else { _bet->outcome_name[i] = new char[2]; std::strcpy(_bet->outcome_name[i], " "); }
								}



							}
							if (_bet->type == 3) {

								if (_bet->outcome_id[i] == _market->outcome_id[i]) u = i;
								else
									for (u = 0; u < _market->outcome_number; u++) {


										if (_bet->outcome_id[i] == _market->outcome_id[u]) break;
									}

								if (u < _market->outcome_number) {

									_bet->outcome_name[i] = new char[strlen(_market->outcome_name[u]) + 1];
									std::strcpy(_bet->outcome_name[i], _market->outcome_name[u]);

								}
								else {
									std::printf("Eror. Outcome name not found. market_id=%d _bet->outcome_id[i]=%d\r\n", _bet->market_id, _bet->outcome_id[i]);

									_bet->outcome_name[i] = new char[2];
									std::strcpy(_bet->outcome_name[i], " ");
									if (settlementError == 0) settlementError = 1;
									if (_market->variant > -1)
										printf("_market->variant=%s\r\n", _market->variable_text);

								}

								for (int j = 0; j < _bet->specifier_number; j++) {
									if (j == _bet->variant) continue;

									replace(_bet->outcome_name[i], _bet->specifier[j], _bet->specifier_value[j], true);
								}



							}
							if (_bet->type == 4) {

								_bet->outcome_name[i] = new char[strlen(bplayers_id[props_player_id]->full_name) + 10];
								strcpy(_bet->outcome_name[i], bplayers_id[props_player_id]->full_name);
								strcat(_bet->outcome_name[i], " ");
								_itoa(_bet->outcome_id[i], buf, 10);
								strcat(_bet->outcome_name[i], buf);
								strcat(_bet->outcome_name[i], ".0+");
							}



							if (PRINT == true) {
								printf("_bet->outcome_name[i]=%s\r\n", _bet->outcome_name[i]);
								printf("_bet->outcome_void_factor[i]=%d\r\n", _bet->outcome_void_factor[i]);
								printf("_bet->outcome_dead_heat_factor[i]=%d\r\n", _bet->outcome_dead_heat_factor[i]);
								printf("_bet->outcome_id[i]=%d\r\n", _bet->outcome_id[i]);
								printf("_bet->outcome_result[i]=%d\r\n", _bet->outcome_result[i]);
							}

						}


						if (settlementError == 1 && _market->variant > -1) goto settlementError1;
					}
					string bet_key = _bet->getCompoundKey();
					//printf("bet_key=%s\r\n", bet_key.c_str());

					if (bets.size() > 0) {
						if (bets.find(bet_key) == bets.end()) {}// printf("bet_settlement key=%s not found in clients bets\r\n", bet_key.c_str());
						else for (unordered_set<Bet*>::iterator bet_it = bets[bet_key].begin(); bet_it != bets[bet_key].end(); ++bet_it)
						{
							printf("bet_settlement key = %s found in clients bets clientkey=%s\r\n", bet_key.c_str(), (*bet_it)->getCompoundKey().c_str());

							calculationBet((*bet_it), _bet, settlement_type);







						}

					}


				}


			}


		}

		else  if (std::strcmp("bet_stop", doc.first_node()->name()) == 0) {
			//printf(doc.first_node()->name()); std::printf("\r\n");
			//printf("bet_stop = %s\r\n", AMQP_message[(bprocess_index - 1) % AMQP_QUEUE]);

			type_radar = 0;
			event_id = 0;
			type_radar = 0;
			event_id = 0;
			if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:season:", 10) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 10)); type_radar = 3;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:match:", 9) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9)); type_radar = 0;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:simple_tournament:", 21) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 21)); type_radar = 2;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:race_tournament:", 19) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 19)); type_radar = 4;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:match:", 9) == 0) { event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9)); type_radar = 5; continue; }
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:season:", 10) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 10)); type_radar = 6; continue;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:tournament:", 14) == 0)
			{
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 14)); type_radar = 7; continue;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:stage:", 9) == 0)
			{
				type_radar = 1; event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
				key ="1"+ string((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
				if (bevents_id.find(key) != bevents_id.end() && (event_id >= MAX_TOURNAMENTS || btournaments_id[event_id] == nullptr)) type_radar = 1;
				else if (bevents_id.find(key) == bevents_id.end() && event_id < MAX_TOURNAMENTS && btournaments_id[event_id] != nullptr) type_radar = 4;
				else if (bevents_id.find(key) == bevents_id.end() && (event_id >= MAX_TOURNAMENTS || btournaments_id[event_id] == nullptr)) {
					type_radar = -1;
					btournaments[btournaments_l].id = event_id;
					btournaments[btournaments_l].type_radar = 1;
					btournaments[btournaments_l].season_id = 0;
					btournaments[btournaments_l].simple_id = 0;
					if (event_id >= MAX_TOURNAMENTS || getTournament(&btournaments[btournaments_l], false, true) == -1) {

						btournaments[btournaments_l].id = 0; btournaments[btournaments_l].type_radar = 0;
						bevents[bevents_l].id = event_id; bevents[bevents_l].type_radar = 1;
						ret_fixture = getEventFixture(&bevents[bevents_l], true);
						if (ret_fixture == -1) {
							bevents[bevents_l].id = 0; bevents[bevents_l].type_radar = 0;
						}
						else { bevents_l++; type_radar = 1; }
					}
					else { type_radar = 4;  btournaments_l++; }
				}
				if (type_radar == -1) continue;
			}

			else { std::printf("Unknown type radar in bet_stop =%s", (char*)doc.first_node()->first_attribute("event_id")->value()); continue; };

			key = to_string(type_radar) + to_string(event_id);

			if (type_radar == 0 || type_radar == 1 || type_radar == 5 ) {
				if (bevents_id.find(key) == bevents_id.end()) {
					std::printf("Event not found in bet_stop. event_id=%d type_radar=%d\r\n", event_id, type_radar); continue;
				}
				_event = bevents_id[key];
				_event->bet_stop = 1;
				if (bevent2lines.find(_event->getCatKey()) == bevent2lines.end()) {}
				else for (unordered_set<int>::iterator it = bevent2lines[_event->getCatKey()]->begin(); it != bevent2lines[_event->getCatKey()]->end(); ++it) if (blines[*(it)].status == 1) blines[*(it)].status = -1;

			}

		}

		else {
			std::printf(doc.first_node()->name()); std::printf("\r\n");
		}



		doc.clear();


	}

	delete[] outcome_team;
	delete[] outcome_name;
	delete[] outcome_id;
	delete[] outcome_active;
	delete[] outcome_result;
	delete[] outcome_void_factor;
	delete[] outcome_dead_heat_factor;
	delete[] outcome_probabilities;
	delete[] outcome_odds;
	delete[] name;
	delete[] buf;
	delete[] maxbuf;
	if (reg_buf != nullptr) delete[] reg_buf;
	delete _line;
	delete _bet;
	//delete[] socket_message_big;
	//delete[] socket_message_little;
	delete[] buffer;
	printf("Exit BetsProcessThread");
	return 0;

}
DWORD WINAPI MTSPublishThread(LPVOID lparam) {
	rabbitmqssl_mts();
	printf("Exit MTSPublishThread");
	return 0;

}
DWORD WINAPI MTSConsumeThread(LPVOID lparam) {
	run_mts();
	printf("Exit MTSConsumeThread");
	return 0;

}


void GenerateBigStep() {
	int i = 0;
	int j = 0;
	int k = 0;
	vector<int> clientIDs;

	if (recovery_state != 0)  return;
	clientIDs.clear();
	clientIDs = server.getClientIDs();
	current_data_step_temp_1 = -1;
	current_data_step_temp_2 = -1;

	//if (!server.ws_clients_flag.test_and_set(std::memory_order_acquire)) {
	for (j = 0; j < STEP_QUEUE; j++) {
		if (array_data_step_1[j] != nullptr && j != current_data_step_1) {
			for (i = 0; i < clientIDs.size(); i++) {
				if (server.wsClients[clientIDs[i]] == nullptr || server.wsClients[clientIDs[i]]->timestamp > 0) continue;
				if (server.wsClients[clientIDs[i]]->step_buffer_1 == array_data_step_1[j])  break;
			}

			if (i == clientIDs.size()) { delete[] array_data_step_1[j]; array_data_step_1[j] = nullptr; }
		}

		if (array_data_step_2[j] != nullptr && j != current_data_step_2) {
			for (i = 0; i < clientIDs.size(); i++) {
				if (server.wsClients[clientIDs[i]] == nullptr) continue;
				if (server.wsClients[clientIDs[i]]->step_buffer_2 == array_data_step_2[j])  break;
			}

			if (i == clientIDs.size()) { delete[] array_data_step_2[j]; array_data_step_2[j] = nullptr; }
		}
	}

	//server.ws_clients_flag.clear(std::memory_order_release);
	//}


	for (j = 0; j < STEP_QUEUE; j++) {
		if (current_data_step_temp_1 >-1 && current_data_step_temp_2 >-1) break;
		if (current_data_step_temp_1 == -1 && array_data_step_1[j] == nullptr)  current_data_step_temp_1 = j;
		if (current_data_step_temp_2 == -1 && array_data_step_2[j] == nullptr)  current_data_step_temp_2 = j;

	}

	if (current_data_step_temp_1 == -1 || current_data_step_temp_2 == -1) {
		printf("error STEP_QUEUE\r\n"); return;
	}

	if (reload_step_1 == 1) {
		array_data_step_1[current_data_step_temp_1] = CreateStep_1(data_step_len_1[current_data_step_temp_1]);
		//printf("CreateStep_1-------------------------------------------- end\r\n");
		current_data_step_1 = current_data_step_temp_1;
		reload_step_1 = 0;
	}

	array_data_step_2[current_data_step_temp_2] = CreateStep_2(data_step_len_2[current_data_step_temp_2]);

	current_data_step_2 = current_data_step_temp_2;

	//Sleep(100);

	clientIDs.clear();



};
void writeInteger(char* buffer, size_t &offset, int data, int num) {
	memcpy(buffer + offset, &data, num);
	offset += num;
};
void writeString(char* buffer, size_t &offset, char* data) {
	int num = 0;
	if (data != nullptr) num = strlen(data);
	memcpy(buffer + offset, &num, 2);
	offset += 2;
	if (data != nullptr) {
		memcpy(buffer + offset, data, num);
		offset += num;
	}
};
/*
void writeDouble(char* buffer, size_t &offset, double data) {
memcpy(buffer + offset, &data, sizeof(double));
offset += sizeof(double);
};*/
void writeFloat(char* buffer, size_t &offset, float data) {
	int temp = (int)(data * 1000 + 0.5);
	memcpy(buffer + offset, &temp, 4);
	offset += 4;
};
void writeDouble(char* buffer, size_t &offset, double data) {
	int temp = (int)(data * 1000 + 0.5);
	memcpy(buffer + offset, &temp, 4);
	offset += 4;
};
int readInteger(char* buffer, size_t & offset, int* data, int num, size_t buffer_size) {
	if (offset + num > buffer_size) return -1;
	memcpy(data, buffer + offset, num);
	offset += num;
	return 0;
};
int readString(char* buffer, size_t &offset, char* &data, size_t buffer_size) {
	int num = 0;
	if (offset + 2 > buffer_size) return -1;
	memcpy(&num, buffer + offset, 2);
	offset += 2;
	if (offset + num > buffer_size) return -1;
	//if (data != nullptr) num = strlen(data);
	if (data != nullptr) delete[] data;
	data = new char[num + 1];
	memcpy(data, buffer + offset, num);
	data[num] = 0;
	offset += num;
	return 0;
};
/*
void readDouble(char* buffer, size_t &offset, float* data) {
memcpy(data,buffer + offset, sizeof(float));
offset += sizeof(float);
};
*/
int readDouble(char* buffer, size_t &offset, double* data, size_t buffer_size) {
	int temp = 0;
	if (offset + 4 > buffer_size) return -1;
	memcpy(&temp, buffer + offset, 4);
	offset += 4;
	*data = (double)(temp) / 1000;
	return 0;
};
/*void readDouble2(char* buffer, size_t &offset, double* data) {
memcpy(data, buffer + offset, sizeof(double));
offset += sizeof(double);
};*/
int GetMaxCompressedLen(int nLenSrc)
{
	int n16kBlocks = (nLenSrc + 16383) / 16384; // round up any fraction of a block
	return (nLenSrc + 6 + (n16kBlocks * 5));
}
int CompressData(const BYTE* abSrc, int nLenSrc, BYTE* abDst, int nLenDst)
{
	z_stream zInfo = { 0 };
	zInfo.total_in = zInfo.avail_in = nLenSrc;
	zInfo.total_out = zInfo.avail_out = nLenDst;
	zInfo.next_in = (BYTE*)abSrc;
	zInfo.next_out = abDst;

	int nErr, nRet = -1;
	//nErr = deflateInit(&zInfo, Z_DEFAULT_COMPRESSION); // zlib function
	nErr = deflateInit2(&zInfo, 2, Z_DEFLATED, 15, 8, Z_DEFAULT_STRATEGY);


	if (nErr == Z_OK) {
		nErr = deflate(&zInfo, Z_FINISH);              // zlib function
		if (nErr == Z_STREAM_END) {
			nRet = zInfo.total_out;
		}
	}
	deflateEnd(&zInfo);    // zlib function
	return(nRet);
}
int UncompressData(const BYTE* abSrc, int nLenSrc, BYTE* abDst, int nLenDst)
{
	z_stream zInfo = { 0 };
	zInfo.total_in = zInfo.avail_in = nLenSrc;
	zInfo.total_out = zInfo.avail_out = nLenDst;
	zInfo.next_in = (BYTE*)abSrc;
	zInfo.next_out = abDst;

	int nErr, nRet = -1;
	nErr = inflateInit(&zInfo);               // zlib function
	if (nErr == Z_OK) {
		nErr = inflate(&zInfo, Z_FINISH);     // zlib function
		if (nErr == Z_STREAM_END) {
			nRet = zInfo.total_out;
		}
	}
	inflateEnd(&zInfo);   // zlib function
	return(nRet); // -1 or len of output
}

string getTournamentKey(int line_type_radar, int id) {
	//0 sr:match://1 sr:race_event(sr:stage) //2 sr:simple_tournament://3 sr:tournamnet //4 sr:race_tournament://5 vf:match  6 //vf:tournament: 7 //sr:season: 8 //vf:season:



	return to_string(type_radar) + to_string(id);

}



int gzip(char* message, int messageLen, char* &zip_message, int step = 0) {
	if (messageLen == 0 || message == nullptr) return -1;
	int step_byte = 0;
	if (step > 0) step_byte = 2;
	char* step_message = new char[messageLen + step_byte + 1];
	memcpy(step_message + step_byte, message, messageLen);
	if (step> 0) memcpy(step_message, &step, 2);
	int tempLen = GetMaxCompressedLen(messageLen + 1 + step_byte);
	BYTE* zipped = new BYTE[tempLen];  // alloc dest buffer
	int zippedLen = CompressData((BYTE*)step_message, messageLen + 1 + step_byte, zipped, tempLen);
	if (zippedLen == -1) { printf("error gzip encoding\r\n"); delete[] zipped; return -1; }
	zip_message = new char[zippedLen + 1];
	memcpy(zip_message, zipped, zippedLen);
	delete[] zipped;
	delete[] step_message;
	return zippedLen;
}
int startRecovery() {
	if (REPLAY != 0) { recovery_state = 0; recovery_state_timestamp = 0; return 0; }
	char* recvbuf = new char[EXTRA];
	char* request_pre = new char[MAX_PATH];
	char* request_liveodds = new char[MAX_PATH];
	char* request_vf = new char[MAX_PATH];
	char* request_vbl = new char[MAX_PATH];
	char* request_vto = new char[MAX_PATH];
	char* timestamp_buf = new char[MAX_PATH];
	int result_pre = 0;
	int result_liveodds = 0;

	std::strcpy(request_pre, "/v1/pre/recovery/initiate_request?");
	std::strcpy(request_liveodds, "/v1/liveodds/recovery/initiate_request?");
	std::strcpy(request_vf, "/v1/vf/recovery/initiate_request?");
	std::strcpy(request_vbl, "/v1/vbl/recovery/initiate_request?");
	std::strcpy(request_vto, "/v1/vto/recovery/initiate_request?");

	if (recovery_timestamp > 0) {
		_i64toa(recovery_timestamp, timestamp_buf, 10); std::strcat(request_pre, "after="); std::strcat(request_pre, timestamp_buf); std::strcat(request_pre, "&"); std::strcat(request_liveodds, "after="); std::strcat(request_liveodds, timestamp_buf); std::strcat(request_liveodds, "&"); std::strcat(request_vf, "after="); std::strcat(request_vf, timestamp_buf); std::strcat(request_vf, "&"); std::strcat(request_vbl, "after="); std::strcat(request_vbl, timestamp_buf); std::strcat(request_vbl, "&");; std::strcat(request_vto, "after="); std::strcat(request_vto, timestamp_buf); std::strcat(request_vto, "&");

	};
	_i64toa(recovery_timestamp / 1000, timestamp_buf, 10);
	std::strcat(request_pre, "request_id="); std::strcat(request_pre, timestamp_buf);
	std::strcat(request_liveodds, "request_id="); std::strcat(request_liveodds, timestamp_buf);
	std::strcat(request_vf, "request_id="); std::strcat(request_vf, timestamp_buf);
	std::strcat(request_vbl, "request_id="); std::strcat(request_vbl, timestamp_buf);
	std::strcat(request_vto, "request_id="); std::strcat(request_vto, timestamp_buf);
    //while (httpsRequest("api.betradar.com", request, recvbuf, 1) == -1) Sleep(1000);
	if (recovery_timestamp > 0) result_liveodds = httpsRequest("api.betradar.com", request_liveodds, recvbuf, 1);
	result_pre = httpsRequest("api.betradar.com", request_pre, recvbuf, 1);
	if (result_pre > 0) std::printf("Start recovery pre recovery_timestamp=%s\r\n", request_pre);
	if (result_liveodds > 0) std::printf("Start recovery liveodds recovery_timestamp=%s\r\n", request_liveodds);
	if (VIRTUAL == 0) {
		httpsRequest("api.betradar.com", request_vf, recvbuf, 1);
		httpsRequest("api.betradar.com", request_vbl, recvbuf, 1);
		httpsRequest("api.betradar.com", request_vto, recvbuf, 1);
	}

	delete[] request_pre;
	delete[] request_liveodds;
	delete[] request_vf;
	delete[] request_vbl;
	delete[] request_vto;
	delete[] recvbuf;
	delete[] timestamp_buf;
	if (result_pre < 0 || result_liveodds < 0) return -1;
	if (recovery_timestamp == 0) recovery_state = 1; else recovery_state_timestamp = 1;
	return 0;

}
int addToReplayList(int event_id, int type_radar) {
	char* recvbuf = new char[EXTRA];
	char* request = new char[MAX_PATH];
	char* int_buf = new char[MAX_PATH];
	std::strcpy(request, "/v1/replay/events/");
	if (type_radar == 0) std::strcat(request, "sr:match:"); else
		if (type_radar == 1) std::strcat(request, "sr:race_event:"); else
			if (type_radar == 2) std::strcat(request, "sr:simple_tournament:"); else
				if (type_radar == 3) std::strcat(request, "sr:season:"); else
					if (type_radar == 4) std::strcat(request, "sr:race_tournament:");
	_itoa(event_id, int_buf, 10);
	std::strcat(request, int_buf);
	int result = httpsRequest("api.betradar.com", request, recvbuf, 2);
	printf("request=%s\r\n", request);
	printf("recvbuf=%s\r\n", recvbuf);
	delete[] request;
	delete[] recvbuf;
	delete[] int_buf;
	return result;
}
void getCategoriesTournaments() {
	reload_step_1 = 1;
	char* recvbuf = new char[EXTRA];
	char buf[MAX_PATH];
	while (httpsRequest("api.betradar.com", "/v1/sports/en/tournaments.xml", recvbuf, 0) == -1) Sleep(1000);
	if (recvbuf[0] == 0) return;
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;
	time_t start;
	SYSTEMTIME st;
	struct tm tm;
	std::memset(&st, 0, sizeof(st));
	std::memset(&tm, 0, sizeof(tm));

	//	using namespace std;
	int i = 0;
	int j = 0;
	int temp = 0;
	int temp2 = 0;// CATEGORIES_LENTGH;
				  //int* find = new int[CATEGORIES_LENTGH];
				  //for (i = 0; i < CATEGORIES_LENTGH; i++) find[i] = 0;
	for (i = 0; i < 1000; i++) if (recvbuf[i] == '\r' && recvbuf[i + 1] == '\n' && recvbuf[i + 2] == '\r' && recvbuf[i + 3] == '\n') break;
	doc.parse<0>((char*)((char*)recvbuf + i + 4));
	root_node = doc.first_node("tournaments");
	i = 0;
	for (xml_node<> * tournament_node = root_node->first_node("tournament"); tournament_node; tournament_node = tournament_node->next_sibling())
	{
		
		
		if (tournaments[i].name != nullptr) {
			delete[] tournaments[i].name; tournaments[i].name = nullptr;
		}
		if (tournament_node->first_attribute("name")) {
			tournaments[i].name = new char[strlen(tournament_node->first_attribute("name")->value()) + 1];
			std::strcpy(tournaments[i].name, tournament_node->first_attribute("name")->value());
		}




		if (strncmp(tournament_node->first_attribute("id")->value(), "sr:tournament:", 14) == 0) {
			tournaments[i].id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 14));
			tournaments[i].type_radar = 0;
		}
		else
			if (strncmp(tournament_node->first_attribute("id")->value(), "sr:simple_tournament:", 21) == 0) {
				tournaments[i].id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 21));
				tournaments[i].type_radar = 2;
			}
			else
				if (strncmp(tournament_node->first_attribute("id")->value(), "sr:stage:", 9) == 0) {
					tournaments[i].id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 9));
					tournaments[i].type_radar = 1;

				}
				else
					if (strncmp(tournament_node->first_attribute("id")->value(), "vf:tournament:", 14) == 0) {
						tournaments[i].id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 14));
						tournaments[i].type_radar = 3;
					}
					else {
						printf("ERROR in tournamnet value getCategoriesTournaments node =%s\r\n", tournament_node->first_attribute("id")->value());
						continue;
					};


	
		if (tournament_node->first_attribute("scheduled")) {

			strcpy(buf, tournament_node->first_attribute("scheduled")->value());
			st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
			sscanf(buf, "%d-%d-%dT%d:%d:%d", &st.wYear, &st.wMonth, &st.wDay, &st.wHour, st.wMinute, st.wSecond);

			tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
			tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
			start = mktime(&tm);
			tournaments[i].start_date = (int)start;


		}


		if (tournament_node->first_attribute("scheduled_end")) {

			strcpy(buf, tournament_node->first_attribute("scheduled_end")->value());
			st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
			sscanf(buf, "%d-%d-%dT%d:%d:%d", &st.wYear, &st.wMonth, &st.wDay, &st.wHour, st.wMinute, st.wSecond);

			tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
			tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
			start = mktime(&tm);
			tournaments[i].end_date = (int)start;


		}

		//printf("tournamentId=%d Name=%s", tournaments[i].id, tournaments[i].name);
		tournaments[i].category_id = atoi((char*)((char*)tournament_node->first_node("category")->first_attribute("id")->value() + 12));

		tournaments[i].sport_id = atoi((char*)((char*)tournament_node->first_node("sport")->first_attribute("id")->value() + 9));

		//printf("tournaments[i].id=%d\r\n", tournaments[i].id);
		

			if (tournaments[i].season_name != nullptr) {
				delete[] tournaments[i].season_name; tournaments[i].season_name = nullptr;
			}
			if (tournament_node->first_node("current_season")) {
				if (tournament_node->first_node("current_season")->first_attribute("name")) {
					tournaments[i].season_name = new char[strlen(tournament_node->first_node("current_season")->first_attribute("name")->value()) + 1];
					std::strcpy(tournaments[i].season_name, tournament_node->first_node("current_season")->first_attribute("name")->value());
				}

				tournaments[i].season_id = atoi((char*)((char*)tournament_node->first_node("current_season")->first_attribute("id")->value() + 10));

				if (tournament_node->first_node("current_season")->first_attribute("start_date")) {
					strcpy(buf, tournament_node->first_node("current_season")->first_attribute("start_date")->value());
					st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
					sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

					tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
					tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
					start = mktime(&tm);
					tournaments[i].start_date = (int)start;

				}

				if (tournament_node->first_node("current_season")->first_attribute("end_date")) {
					strcpy(buf, tournament_node->first_node("current_season")->first_attribute("end_date")->value());
					st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
					sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

					tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
					tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
					start = mktime(&tm);
					tournaments[i].end_date = (int)start;

				}


			}



		

		if (tournament_node->first_node("tournament_length")) {
			if (tournament_node->first_node("tournament_length")->first_attribute("start_date")) {
				strcpy(buf, tournament_node->first_node("tournament_length")->first_attribute("start_date")->value());
				st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
				sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

				tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
				tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
				start = mktime(&tm);
				tournaments[i].start_date = (int)start;

			}

			if (tournament_node->first_node("tournament_length")->first_attribute("end_date")) {
				strcpy(buf, tournament_node->first_node("tournament_length")->first_attribute("end_date")->value());
				st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
				sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

				tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
				tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
				start = mktime(&tm);
				tournaments[i].end_date = (int)start;

			}
		}




		



		if (tournaments[i].category_id >= MAX_CATEGORIES) {
			std::printf("ERROR DATA!\r\ncategory id out of MAX_CATEGORIES in getCategoryTournaments %d\r\n", tournaments[i].category_id); continue;
		}
		else if (categories_id[tournaments[i].category_id] == nullptr) {
			if (categories[j].name != nullptr) {
				delete[] categories[j].name; categories[j].name = nullptr;
			}
			if (tournament_node->first_node("category") && tournament_node->first_node("category")->first_attribute("name")) {
				categories[j].name = new char[strlen(tournament_node->first_node("category")->first_attribute("name")->value()) + 1];
				std::strcpy(categories[j].name, tournament_node->first_node("category")->first_attribute("name")->value());
			}

			categories[j].id = tournaments[i].category_id;
			categories[j].sport_id = tournaments[i].sport_id;
			categories_id[categories[j].id] = &categories[j];
			saveCategoryToDB(&categories[j]);
			j++;
		}

		
		
			tournaments_id[tournaments[i].getCatKey()] = &tournaments[i]; 
			if(tournaments[i].season_id > 0) seasons_id[tournaments[i].getSeasonKey()] = &tournaments[i];
			saveTournamentToDB(&tournaments[i]);
		i++;

		//cout << endl;
	}

	tournaments_l = i;
	categories_l = j;
	printf("Create tournament successful. Numbers of tournaments: %d\r\n", tournaments_l);
	printf("Create categories successful. Numbers of categories: %d\r\n", categories_l);
	delete[] recvbuf;
	doc.clear();

}
void getCategoriesTournamentsTranslate(int l) {
	reload_step_1 = 1;
	char* recvbuf = new char[EXTRA];
	char request[MAX_PATH];
	char buf[MAX_PATH];
	strcpy(request, "/v1/sports/");
	strcat(request, lang[l].c_str());
	strcat(request, "/tournaments.xml");
	while (httpsRequest("api.betradar.com", request, recvbuf, 0) == -1) Sleep(1000);
	if (recvbuf[0] == 0) return;
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;
	Tournament* tournament;
	Category * category;
	//	using namespace std;
	int i = 0;
	int j = 0;
	int temp = 0;
	int temp2 = 0;// CATEGORIES_LENTGH;
				  //int* find = new int[CATEGORIES_LENTGH];
				  //for (i = 0; i < CATEGORIES_LENTGH; i++) find[i] = 0;
	for (i = 0; i < 1000; i++) if (recvbuf[i] == '\r' && recvbuf[i + 1] == '\n' && recvbuf[i + 2] == '\r' && recvbuf[i + 3] == '\n') break;
	doc.parse<0>((char*)((char*)recvbuf + i + 4));
	root_node = doc.first_node("tournaments");
	i = 0;
	int id = 0;
	string key;
	int type_radar;

	for (xml_node<> * tournament_node = root_node->first_node("tournament"); tournament_node; tournament_node = tournament_node->next_sibling())
	{


		if (strncmp(tournament_node->first_attribute("id")->value(), "sr:tournament:", 14) == 0) {
			id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 14));
			type_radar = 0;
		}
		else
			if (strncmp(tournament_node->first_attribute("id")->value(), "sr:simple_tournament:", 21) == 0) {
			id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 21));
			type_radar = 2;
			}
			else
				if (strncmp(tournament_node->first_attribute("id")->value(), "sr:stage:", 9) == 0) {
			    id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 9));
		     	type_radar = 1;

				}
				else
					if (strncmp(tournament_node->first_attribute("id")->value(), "vf:tournament:", 14) == 0) {
			         id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 14));
					 type_radar = 3;
					}
					else {
						printf("ERROR in tournamnet value getCategoriesTournaments node =%s\r\n", tournament_node->first_attribute("id")->value());
						continue;
					};


					key = to_string(type_radar) + to_string(id);

					if (tournaments_id.find(key) == tournaments_id.end()) continue;
					tournament = tournaments_id[key];

		

		if (tournament_node->first_attribute("name") && tournament->translation_name[l] == nullptr) {
			//printf("tournament_node->first_attribute(name)->value()=%s\r\n", tournament_node->first_attribute("name")->value());
			tournament->translation_name[l] = new char[strlen(tournament_node->first_attribute("name")->value()) + 1];
			std::strcpy(tournament->translation_name[l], tournament_node->first_attribute("name")->value());
			if (l > 0 && tournament->name != nullptr && strcmp(tournament->translation_name[l], tournament->name) == 0)
			{
				delete[] tournament->translation_name[l];
				tournament->translation_name[l] = nullptr;
			}

		}


		temp = atoi((char*)((char*)tournament_node->first_node("category")->first_attribute("id")->value() + 12));




		if (tournament_node->first_node("current_season")) {
			if (tournament_node->first_node("current_season")->first_attribute("name") && tournament->translation_season_name[l] == nullptr) {
				tournament->translation_season_name[l] = new char[strlen(tournament_node->first_node("current_season")->first_attribute("name")->value()) + 1];
				std::strcpy(tournament->translation_season_name[l], tournament_node->first_node("current_season")->first_attribute("name")->value());

				if (l > 0 && tournament->season_name != nullptr && strcmp(tournament->translation_season_name[l], tournament->season_name) == 0)
				{
					delete[] tournament->translation_season_name[l];
					tournament->translation_season_name[l] = nullptr;
				}

			}




		}



		if (temp == 0 || temp >= MAX_CATEGORIES || categories_id[temp] == nullptr) {
			printf("id categories error=%d\r\n", temp); continue;
		}

		category = categories_id[temp];

		if (tournament_node->first_node("category") && tournament_node->first_node("category")->first_attribute("name") && category->translation_name[l] == nullptr) {
			category->translation_name[l] = new char[1000 + 1];
			std::strcpy(category->translation_name[l], tournament_node->first_node("category")->first_attribute("name")->value());
			if (l > 0 && category->name != nullptr && strcmp(category->translation_name[l], category->name) == 0) {
				//printf("category translate name delete\r\n");
				delete[] category->translation_name[l]; category->translation_name[l] = nullptr;
			}
		}





	}
	delete[] recvbuf;
	doc.clear();

}
void getSports(bool b) {
	reload_step_1 = 1;
	char* recvbuf = new char[EXTRA];
	while (httpsRequest("api.betradar.com", "/v1/sports/en/sports.xml", recvbuf, 0) == -1) Sleep(1000);
	if (recvbuf[0] == 0) while (httpsRequest("api.betradar.com", "/v1/sports/en/sports.xml", recvbuf, 0) == -1 || recvbuf[0] == 0) Sleep(1000);


	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;
	Sport** sports_id;
	Sport* sports;
	int* rsports_l;



	if (b == true) {
		sports_id = ::bsports_id;
		sports = ::bsports;
		rsports_l = &::bsports_l;
	}
	else {
		sports_id = ::sports_id;
		sports = ::sports;
		rsports_l = &::sports_l;
	}



	//using namespace std;
	int i = 0;
	for (i = 0; i < 1000; i++) if (recvbuf[i] == '\r' && recvbuf[i + 1] == '\n' && recvbuf[i + 2] == '\r' && recvbuf[i + 3] == '\n') break;
	doc.parse<0>((char*)((char*)recvbuf + i + 4));
	root_node = doc.first_node("sports");
	i = 0;

	for (xml_node<> * sport_node = root_node->first_node("sport"); sport_node; sport_node = sport_node->next_sibling())
	{
		std::strcpy(sports[i].name, sport_node->first_attribute("name")->value());
		sports[i].id = atoi((char*)((char*)sport_node->first_attribute("id")->value() + 9));


		//printf("sportId=%d Name=%s", sports[i].id, sports[i].name);
		if (sports[i].id < MAX_SPORTS) sports_id[sports[i].id] = &sports[i];
		else std::printf("ERROR DATA!\r\nsport id out of MAX_SPORTS in getSportss%d\r\n", sports[i].id);

		// printf("SportId=%d,SportName=%s\r\n", sports[i].id, sports[i].name);
		i++;
		//sport_node->first_attribute("name")->value();
		//cout << endl;
	}

	sports_l = i;
	doc.clear();
	delete[] recvbuf;
	printf("Create sports successful. Numbers of sports: %d\r\n", sports_l);

}
void getSportsTranslate(int l) {
	char* recvbuf = new char[EXTRA];
	char* request = new char[MAX_PATH];
	strcpy(request, "/v1/sports/");
	strcat(request, lang[l].c_str());
	strcat(request, "/sports.xml");
	while (httpsRequest("api.betradar.com", request, recvbuf, 0) == -1) Sleep(1000);
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;

	//using namespace std;
	int i = 0;
	for (i = 0; i < 1000; i++) if (recvbuf[i] == '\r' && recvbuf[i + 1] == '\n' && recvbuf[i + 2] == '\r' && recvbuf[i + 3] == '\n') break;
	doc.parse<0>((char*)((char*)recvbuf + i + 4));
	root_node = doc.first_node("sports");
	i = 0;

	for (xml_node<> * sport_node = root_node->first_node("sport"); sport_node; sport_node = sport_node->next_sibling())
	{
		int id = atoi((char*)((char*)sport_node->first_attribute("id")->value() + 9));
		if (id >= MAX_SPORTS || sports_id[id] == nullptr) continue;
		sports_id[id]->translation_name[l] = new char[strlen(sport_node->first_attribute("name")->value()) + 1];
		std::strcpy(sports_id[id]->translation_name[l], sport_node->first_attribute("name")->value());
		if (l > 0 && strcmp(sports_id[id]->translation_name[l], sports_id[id]->name) == 0) { delete[] sports_id[id]->translation_name[l]; sports_id[id]->translation_name[l] = nullptr; }

	}

	doc.clear();
	delete[] recvbuf;
	delete[] request;
	printf("Translate sports successful.language=%s\r\n", lang[l].c_str());

}
void getEvents(time_t sec, int days) {
	char buffer[MAX_PATH];
	char buf[MAX_PATH];
	time_t now_t = sec;
	time_t now = 0;
	time_t start;
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;
	//using namespace std;
	SYSTEMTIME st;
	struct tm tm;
	std::memset(&st, 0, sizeof(st));
	std::memset(&tm, 0, sizeof(tm));
	Tournament* _tournament;
	char* recvbuf = new char[EXTRA];
	int booked_num = 0;

	if (sec == 0)  time(&now_t); else days = 1;
	int i = 0;
	int k = 0;

	for (int j = 0; j < days; j++) {
		now = now_t + j * 24 * 60 * 60;
		strftime(buf, 80, "%Y-%m-%d", gmtime(&now));
		std::strcpy(buffer, "/v1/sports/en/schedules/");
		std::strcat(buffer, buf);
		std::strcat(buffer, "/schedule.xml");
		while (httpsRequest("api.betradar.com", buffer, recvbuf, 0) == -1) Sleep(1000);
		if (recvbuf[0] == 0) return;

		for (k = 0; k < 1000; k++) if (recvbuf[k] == '\r' && recvbuf[k + 1] == '\n' && recvbuf[k + 2] == '\r' && recvbuf[k + 3] == '\n') break;

		doc.parse<0>((char*)((char*)recvbuf + k + 4));
		root_node = doc.first_node("schedule");
		if (root_node == nullptr) continue;




		for (xml_node<> * event_node = root_node->first_node("sport_event"); event_node; event_node = event_node->next_sibling())
		{
			//printf("for\r\n");
			if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "vf:match:", 9) == 0)
			{
				events[i].id = atoi((char*)((char*)event_node->first_attribute("id")->value() + 9)); events[i].type_radar = 3;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:match:", 9) == 0)
			{
				events[i].id = atoi((char*)((char*)event_node->first_attribute("id")->value() + 9)); events[i].type_radar = 0;
			}
			else if (strncmp(doc.first_node()->first_attribute("event_id")->value(), "sr:stage:", 9) == 0)
			{
				events[i].id = atoi((char*)((char*)event_node->first_attribute("id")->value() + 9)); events[i].type_radar = 1;
			}
			else {
			printf("ERROR getEvents\r\n");
			printf("event_node=%s\r\n",event_node->first_attribute("id")->value());
			printf("\r\n"); continue;
			}

		
			if (event_node->first_attribute("status") != nullptr) {
				if (strcmp("live", event_node->first_attribute("status")->value()) == 0)  events[i].status = 1; else
					if (strcmp("closed", event_node->first_attribute("status")->value()) == 0)  events[i].status = 4; else
						if (strcmp("ended", event_node->first_attribute("status")->value()) == 0)  events[i].status = 3; else
							if (strcmp("not_started", event_node->first_attribute("status")->value()) == 0)  events[i].status = 0;
				if (strcmp("abandoned", event_node->first_attribute("status")->value()) == 0)  events[i].status = 5;
				if (strcmp("suspended", event_node->first_attribute("status")->value()) == 0)  events[i].status = 2;







			}


			strcpy(buf, event_node->first_attribute("id")->next_attribute()->value());
			sscanf(buf, "%d-%d-%dT%d:%d:%d", &st.wYear, &st.wMonth, &st.wDay, &st.wHour, &st.wMinute, &st.wSecond);
			tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
			tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
			start = mktime(&tm);
			events[i].start_time = (int)start;
			events[i].booked = 0;



			if (events[i].type_radar == 0 || events[i].type_radar == 3) {

				if (event_node->first_attribute("liveodds")) {
					strcpy(buf, event_node->first_attribute("liveodds")->value());
					if (buf[0] == 'b'&& buf[1] == 'o'&& buf[5] == 'd') events[i].booked = 1;
					if (buf[0] == 'b'&& buf[1] == 'o'&& buf[5] == 'b') events[i].booked = 2;
				}
                if (events[i].home_name != nullptr) {
					delete[] events[i].home_name; events[i].home_name = nullptr;
				}
				if (event_node->first_node("competitors")->first_node("competitor")->first_attribute("name")) {
					events[i].home_name = new char[strlen(event_node->first_node("competitors")->first_node("competitor")->first_attribute("name")->value()) + 1];
					std::strcpy(events[i].home_name, event_node->first_node("competitors")->first_node("competitor")->first_attribute("name")->value());
				}
                if (events[i].away_name != nullptr) { delete[] events[i].away_name; events[i].away_name = nullptr; }
				if (event_node->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("name")) {
					events[i].away_name = new char[strlen(event_node->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("name")->value()) + 1];
					std::strcpy(events[i].away_name, event_node->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("name")->value());
				}
				events[i].home_id = atoi((char*)((char*)event_node->first_node("competitors")->first_node("competitor")->first_attribute("id")->value() + 14));
				events[i].away_id = atoi((char*)((char*)event_node->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("id")->value() + 14));
				if (event_node->first_node("competitors")->first_node("competitor")->first_node("reference_ids") && event_node->first_node("competitors")->first_node("competitor")->first_attribute("id")->value()[3] == 'c')
					events[i].home_reference_id = atoi((char*)event_node->first_node("competitors")->first_node("competitor")->first_node("reference_ids")->first_node("reference_id")->first_attribute("value")->value()); else {
					events[i].home_reference_id = events[i].home_id; //events[i].home_id = 0;
				}
				if (event_node->first_node("competitors")->last_node("competitor")->first_node("reference_ids") && event_node->first_node("competitors")->last_node("competitor")->first_attribute("id")->value()[3] == 'c')
					events[i].away_reference_id = atoi((char*)event_node->first_node("competitors")->last_node("competitor")->first_node("reference_ids")->first_node("reference_id")->first_attribute("value")->value()); else {
					events[i].away_reference_id = events[i].away_id; //events[i].away_id = 0;
				}

				




			}
			else if (events[i].type_radar == 1) {
				if(event_node->first_node("parent")) events[i].parent_id = atoi((char*)((char*)event_node->first_node("parent")->first_attribute("id")->value() + 9));//sr:stage:
																																 // atoi((char*)((char*)event_node->first_node("parent")->first_attribute("id")->value() + 14));
				if (events[i].home_name != nullptr) {
					delete[] events[i].home_name; events[i].home_name = nullptr;
				}
				if (event_node->first_attribute("name")) {
					events[i].home_name = new char[strlen(event_node->first_attribute("name")->value()) + 1];
					std::strcpy(events[i].home_name, event_node->first_attribute("name")->value());
				}
				if (events[i].away_name != nullptr) {
					delete[] events[i].away_name; events[i].away_name = nullptr;
				}
				if (event_node->first_node("parent")->first_attribute("name")) {
					events[i].away_name = new char[strlen(event_node->first_node("parent")->first_attribute("name")->value()) + 1];
					std::strcpy(events[i].away_name, event_node->first_node("parent")->first_attribute("name")->value());
				}


			}




			if (event_node->first_node("tournament")) {

				if (strncmp(event_node->first_node("tournament")->first_attribute("id")->value(), "sr:tournament:", 14) == 0) {
					events[i].tournament_id = atoi((char*)((char*)event_node->first_node("tournament")->first_attribute("id")->value() + 14));
					events[i].type_radar = 0;
				}
				else
					if (strncmp(event_node->first_node("tournament")->first_attribute("id")->value(), "sr:simple_tournament:", 21) == 0) {
						events[i].tournament_id = atoi((char*)((char*)event_node->first_node("tournament")->first_attribute("id")->value() + 21));
						events[i].type_radar = 2;
					}
					else
						if (strncmp(event_node->first_node("tournament")->first_attribute("id")->value(), "sr:stage:", 9) == 0) {
							events[i].tournament_id = atoi((char*)((char*)event_node->first_node("tournament")->first_attribute("id")->value() + 9));
							events[i].type_radar = 1;

						}
						else 	
							if (strncmp(event_node->first_node("tournament")->first_attribute("id")->value(), "vf:tournament:", 14) == 0) {
							events[i].tournament_id = atoi((char*)((char*)event_node->first_node("tournament")->first_attribute("id")->value() + 14));
							events[i].type_radar = 3;
						}
						 else {
								printf("ERROR in tournamnet value getEvents node =%s\r\n", event_node->first_node("tournament")->first_attribute("id")->value());
								continue;
							};

			
			
			};
				
				
			if (events[i].tournament_id == 0 && events[i].parent_id > 0) {

				string event_key = to_string(events[i].parent_id);
				if (events_id.find(event_key) != events_id.end()) {
					events[i].tournament_id = events_id[event_key]->tournament_id;
					events[i].sport_id = events_id[event_key]->sport_id;
					events[i].category_id = events_id[event_key]->category_id;
				}
			}

				
				
				
			if (event_node->first_node("tournament")) {
				events[i].sport_id = atoi((char*)((char*)event_node->first_node("tournament")->first_node("sport")->first_attribute("id")->value() + 9));
				events[i].category_id = atoi((char*)((char*)event_node->first_node("tournament")->first_node("category")->first_attribute("id")->value() + 12));
			}
			if (events[i].category_id >= MAX_CATEGORIES) {
				std::printf("ERROR DATA!\r\ncategory id out of MAX_CATEGORIES in getEvents %d\r\n", events[i].category_id); continue;
			}
			else {
				if (categories_id[events[i].category_id] == nullptr) {
					categories_id[events[i].category_id] = &categories[categories_l];
					categories_l++;

				}
				categories_id[events[i].category_id]->id = events[i].category_id;
				categories_id[events[i].category_id]->sport_id = events[i].sport_id;

				if (categories_id[events[i].category_id]->name != nullptr) {
					delete[] categories_id[events[i].category_id]->name; categories_id[events[i].category_id]->name = nullptr;
				}

				categories_id[events[i].category_id]->name = new char[strlen(event_node->first_node("tournament")->first_node("category")->first_attribute("name")->value()) + 1];
				std::strcpy(categories_id[events[i].category_id]->name, event_node->first_node("tournament")->first_node("category")->first_attribute("name")->value());


			}
			

			string tournament_key = events[i].getTournamentKey();
		
				if (tournaments_id.find(tournament_key) == tournaments_id.end()) {
					tournaments_id[tournament_key] = &tournaments[tournaments_l];
					tournaments_l++;
				} 
				_tournament = tournaments_id[tournament_key];

				_tournament->type_radar = events[i].type_radar;
				_tournament->id = events[i].tournament_id;
				_tournament->category_id = events[i].category_id;
				_tournament->sport_id = events[i].sport_id;

				if (event_node->first_node("tournament") && event_node->first_node("tournament")->first_attribute("name")) {
					if (_tournament->name != nullptr) delete[] _tournament->name;
					_tournament->name = new char[strlen(event_node->first_node("tournament")->first_attribute("name")->value()) + 1];
					std::strcpy(_tournament->name, event_node->first_node("tournament")->first_attribute("name")->value());
				}


			if (event_node->first_node("season")) {

				if (_tournament->season_name != nullptr) { delete[] _tournament->season_name; _tournament->season_name = nullptr; }

				_tournament->season_name = new char[strlen(event_node->first_node("season")->first_attribute("name")->value()) + 1];
				std::strcpy(_tournament->season_name, event_node->first_node("season")->first_attribute("name")->value());
				
				_tournament->season_id = atoi((char*)((char*)event_node->first_node("season")->first_attribute("id")->value() + 10));
				seasons_id[_tournament->getSeasonKey()] = _tournament;



				if (event_node->first_node("season")->first_attribute("start_date")) {
					strcpy(buf, event_node->first_node("season")->first_attribute("start_date")->value());
					st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
					sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

					tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
					tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
					start = mktime(&tm);
					_tournament->start_date = (int)start;

				}

				if (event_node->first_node("season")->first_attribute("end_date")) {
					strcpy(buf, event_node->first_node("season")->first_attribute("end_date")->value());
					st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
					sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

					tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
					tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
					start = mktime(&tm);
					_tournament->end_date = (int)start;

				}

			}












			 events_id[events[i].getCatKey()] = &events[i]; 
			//&& events[i].start_time>time(nullptr)

			if (booking > 0 && events[i].booked == 2 && events[i].status == 0 && booked_num < booking) { postBooked(events[i].id); booked_num++; }
			//&& (events[i].sport_id == 1 || events[i].sport_id == 2 || events[i].sport_id == 4 || events[i].sport_id == 5 || events[i].sport_id == 12 || events[i].sport_id == 23 || events[i].sport_id == 6))
			i++;

		}
		doc.clear();
	}


	delete[] recvbuf;

	events_l = i;
	std::printf("Create events successful. Numbers of events: %d\r\n", events_l);



}
int getVariantMarket(Market* market, char* urn, bool b, bool a) {


	char buffer[MAX_PATH];
	char buf[MAX_PATH];
	int* outcome_id = new int[MAX_OUTCOME];
	char** outcome_name = new char*[MAX_OUTCOME];
	char* recvbuf = new char[EXTRA];
	Market* _market;
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;

	Market* markets;
	int* rmarkets_l;
	Market*** markets_id;
	int* max_markets_in;



	if (b == true) {
		markets = ::bmarkets;
		rmarkets_l = &::bmarkets_l;
		markets_id = ::bmarkets_id;
		max_markets_in = ::bmax_markets_in;



	}
	else {
		markets = ::markets;
		rmarkets_l = &::markets_l;
		markets_id = ::markets_id;
		max_markets_in = ::max_markets_in;
	}














	//using namespace std;
	int k = 0;
	int i = 0;
	int j = 0;
	int c = 0;
	for (i = 0; i < MAX_OUTCOME; i++) outcome_name[i] = new char[MAX_OUTCOME_NAME];

	if (market->type == 3 || market->type == 4) std::strcpy(buffer, "/v1/pre/descriptions/en/markets/");
	else if (urn[0] == 'l' && urn[1] == 'o' && urn[2] == ':') std::strcpy(buffer, "/v1/liveodds/descriptions/en/markets/");
	else  std::strcpy(buffer, "/v1/descriptions/en/markets/");

	_itoa(market->id, buf, 10);
	std::strcat(buffer, buf);
	std::strcat(buffer, "/variants/");
	std::strcat(buffer, urn);
	while (httpsRequest("api.betradar.com", buffer, recvbuf, 0) == -1) Sleep(1000);
	if (recvbuf[0] == 0) return -1;

	int recv_length = strlen(recvbuf) - 4; if (recv_length > 1000) recv_length = 1000; for (j = 0; j < recv_length; j++) if (recvbuf[j] == '\r' && recvbuf[j + 1] == '\n' && recvbuf[j + 2] == '\r' && recvbuf[j + 3] == '\n') break; if (j == recv_length) { delete[] recvbuf; return -1; }
	try { doc.parse<0>((char*)((char*)recvbuf + j + 4)); }
	catch (parse_error e) { cerr << "Fail. Parse error " << e.what() << endl; delete[] recvbuf; return -1; }

	j = 0;
	root_node = doc.first_node("market_descriptions");
	if (root_node == nullptr || root_node->first_node("market") == nullptr) {
		printf("market->type=%d market->id=%d\r\n", market->type, market->id);
		printf(urn);
		printf("\r\n");

		for (i = 0; i < MAX_OUTCOME; i++) delete[] outcome_name[i];
		delete[] outcome_name;
		delete[] outcome_id;
		delete[] recvbuf;
		doc.clear();
		return -1;
	}



	j = -1;



	for (i = 0; i < max_markets_in[market->id]; i++) {
		if (j == -1 && markets_id[market->id][i] == nullptr) j = i;
		if (markets_id[market->id][i] != nullptr && markets_id[market->id][i]->variable_text != nullptr && std::strcmp(urn, markets_id[market->id][i]->variable_text) == 0)
		{
			j = i; break;
		}
	}




	if (i == max_markets_in[market->id]) {
		if (j == -1) {
			j = max_markets_in[market->id];  max_markets_in[market->id]++;
		}
		markets_id[market->id][j] = &markets[*rmarkets_l];  (*rmarkets_l)++;


	}



	markets_id[market->id][j][0] = market[0];
	_market = markets_id[market->id][j];



	if ((_market->type == 3 || (_market->type == 0 && _market->variant>-1 && _market->variable_text != nullptr && _market->variable_text[0] == 'l' && _market->variable_text[1] == 'o' && _market->variable_text[2] == ':')) && root_node->first_node("market") && root_node->first_node("market")->first_attribute("name")) {
		if (_market->name != nullptr) delete[] _market->name;
		_market->name = new char[strlen(root_node->first_node("market")->first_attribute("name")->value()) + 1];
		std::strcpy(_market->name, root_node->first_node("market")->first_attribute("name")->value());
	}




	if (_market->variable_text != nullptr) delete[] _market->variable_text;
	_market->variable_text = new char[strlen(urn) + 1];
	std::strcpy(_market->variable_text, urn);
	_market->outcome_number = 0;


	if (root_node->first_node("market") && root_node->first_node("market")->first_node("outcomes")) for (xml_node<> * outcome_node = root_node->first_node("market")->first_node("outcomes")->first_node("outcome"); outcome_node; outcome_node = outcome_node->next_sibling()) {
		if (_market->type == 3) outcome_id[_market->outcome_number] = atoi((char*)((char*)outcome_node->first_attribute("id")->value() + 16));
		else outcome_id[_market->outcome_number] = atoi((char*)((char*)outcome_node->first_attribute("id")->value() + strlen(_market->variable_text) + 1));
		std::strcpy(outcome_name[_market->outcome_number], outcome_node->first_attribute("name")->value());
		_market->outcome_number++;

	}




	if (_market->outcome_number > 0) {
		_market->outcome_id = new int[_market->outcome_number];
		_market->outcome_name = new char*[_market->outcome_number];
		for (k = 0; k < _market->outcome_number; k++) {
			_market->outcome_name[k] = new char[strlen(outcome_name[k]) + 1];
			std::strcpy(_market->outcome_name[k], outcome_name[k]);
			_market->outcome_id[k] = outcome_id[k];
		}
	}



	if (b == false || a == true) saveMarketToDB(_market);


	for (i = 0; i < MAX_OUTCOME; i++) delete[] outcome_name[i];
	delete[] outcome_name;
	delete[] outcome_id;
	delete[] recvbuf;
	doc.clear();

	return 0;
}
int getVariantMarketTranslate(Market* market, int l) {


	if (market->variant == -1) return 0;
	//if (market->id == 534) return 0;
	//if (market->id == 535) return 0;
	//if (market->id == 559) return 0;
	if (market->variable_text == nullptr) return 0;
	char buffer[MAX_PATH];
	char buf[MAX_PATH];
	char* recvbuf = new char[EXTRA];
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;

	//printf("market->id = %d market->variable_text=%s\r\n", market->id, market->variable_text);

	//using namespace std;
	int k = 0;
	int i = 0;
	int j = 0;
	int c = 0;

	if (market->type == 3 || market->type == 4) {
		std::strcpy(buffer, "/v1/pre/descriptions/");
		std::strcat(buffer, lang[l].c_str());
		std::strcat(buffer, "/markets/");

	}
	else if (market->variable_text[0] == 'l' && market->variable_text[1] == 'o' && market->variable_text[2] == ':') {

		std::strcpy(buffer, "/v1/liveodds/descriptions/");
		std::strcat(buffer, lang[l].c_str());
		std::strcat(buffer, "/markets/");


	}
	else {
		std::strcpy(buffer, "/v1/descriptions/");
		std::strcat(buffer, lang[l].c_str());
		std::strcat(buffer, "/markets/");


	}

	_itoa(market->id, buf, 10);
	std::strcat(buffer, buf);
	std::strcat(buffer, "/variants/");
	std::strcat(buffer, market->variable_text);
	while (httpsRequest("api.betradar.com", buffer, recvbuf, 0) == -1) Sleep(1000);
	if (recvbuf[0] == 0) return -1;

	int recv_length = strlen(recvbuf) - 4; if (recv_length > 1000) recv_length = 1000; for (j = 0; j < recv_length; j++) if (recvbuf[j] == '\r' && recvbuf[j + 1] == '\n' && recvbuf[j + 2] == '\r' && recvbuf[j + 3] == '\n') break; if (j == recv_length) { delete[] recvbuf; return -1; }
	try { doc.parse<0>((char*)((char*)recvbuf + j + 4)); }
	catch (parse_error e) { cerr << "Fail. Parse error " << e.what() << endl; delete[] recvbuf; return -1; }
	j = 0;
	root_node = doc.first_node("market_descriptions");
	if (root_node == nullptr || root_node->first_node("market") == nullptr) {
		//	printf("market->type=%d market->id=%d\r\n", market->type, market->id);
		//	printf(market->variable_text);
		//		printf("\r\n");
		delete[] recvbuf;
		doc.clear();
		return -1;
	}



	if (root_node->first_node("market") && root_node->first_node("market")->first_attribute("name")) {
		market->translation_name[l] = new char[strlen(root_node->first_node("market")->first_attribute("name")->value()) + 1];
		std::strcpy(market->translation_name[l], root_node->first_node("market")->first_attribute("name")->value());
		if (l > 0 && market->name != nullptr && strcmp(market->translation_name[l], market->name) == 0) {
			delete[] market->translation_name[l];
			market->translation_name[l] = nullptr;
			delete[] recvbuf;
			doc.clear();
			return 0;
		}
	}



	int outcome_number = 0;
	if (market->outcome_number > 0) {
		market->translation_outcome_name[l] = new char*[market->outcome_number]; for (int m = 0; m < market->outcome_number; m++) market->translation_outcome_name[l]
			[m] = nullptr;
	}
	if (root_node->first_node("market") && root_node->first_node("market")->first_node("outcomes")) for (xml_node<> * outcome_node = root_node->first_node("market")->first_node("outcomes")->first_node("outcome"); outcome_node; outcome_node = outcome_node->next_sibling()) {
		if (outcome_number == market->outcome_number) break;
		market->translation_outcome_name[l][outcome_number] = new char[strlen(outcome_node->first_attribute("name")->value()) + 1];
		std::strcpy(market->translation_outcome_name[l][outcome_number], outcome_node->first_attribute("name")->value());
		outcome_number++;
	}



	delete[] recvbuf;
	doc.clear();
	return 0;
}
void getMarkets() {
	char* recvbuf = new char[EXTRA];
	char buffer[MAX_PATH];
	char* urn = new char[MAX_PATH];
	char buf[MAX_PATH];
	int* outcome_id = new int[MAX_OUTCOME];
	char** outcome_name = new char*[MAX_OUTCOME];
	char** specifier_name = new char*[MAX_PATH];
	char** specifier_description = new char*[MAX_PATH];
	int* specifier_type = new int[MAX_PATH];;//0 null //1 int //2 string 3://decimal 4//variable	
											 //char* recvbuf2 = new char[1000000];
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;
	//using namespace std;
	int k = 0;
	int i = 0;
	int j = 0;
	int u = 0;
	int v = 0;
	markets_l = 0;

	for (i = 0; i < MAX_OUTCOME; i++) 	outcome_name[i] = new char[MAX_OUTCOME_NAME];



	for (i = 0; i < MAX_PATH; i++) {
		specifier_description[i] = nullptr; specifier_name[i] = nullptr;
	}


	while (httpsRequest("api.betradar.com", "/v1/descriptions/en/markets.xml?include_mappings=true", recvbuf, 0) == -1) Sleep(1000);
	//httpsRequest("api.betradar.com", "/v1/descriptions/en/markets.xml?include_mappings=true", recvbuf2, 0);

	if (recvbuf[0] == 0) return;

	for (k = 0; k < 1000; k++) if (recvbuf[k] == '\r' && recvbuf[k + 1] == '\n' && recvbuf[k + 2] == '\r' && recvbuf[k + 3] == '\n') break;
	doc.parse<0>((char*)((char*)recvbuf + k + 4));
	root_node = doc.first_node("market_descriptions");
	if (root_node == nullptr) {
		for (int i = 0; i < MAX_PATH; i++) { if (specifier_name[i] != nullptr) delete[] specifier_name[i]; if (specifier_description[i] != nullptr) delete[] specifier_description[i]; }
		delete[] specifier_name;
		delete[] specifier_description;
		delete[] specifier_type;
		for (i = 0; i < MAX_OUTCOME; i++) delete[] outcome_name[i];
		delete[] outcome_name;
		delete[] outcome_id;
		delete[] recvbuf;
		delete[] urn;
		doc.clear();
		return;
	}




	for (xml_node<> * market_node = root_node->first_node("market"); market_node; market_node = market_node->next_sibling())
	{


		i = markets_l;
		markets[i].id = atoi(market_node->first_attribute("id")->value());
		//markets[i].site_id = markets[i].id * 10;
		if (markets[i].name != nullptr) delete[] markets[i].name;
		markets[i].name = new char[strlen(market_node->first_attribute("name")->value()) + 1];
		std::strcpy(markets[i].name, market_node->first_attribute("name")->value());
		if (market_node->first_attribute("includes_outcomes_of_type") != nullptr) {
			if (strcmp("sr:player", market_node->first_attribute("includes_outcomes_of_type")->value()) == 0)  markets[i].type = 1; else
				if (strcmp("sr:competitor", market_node->first_attribute("includes_outcomes_of_type")->value()) == 0)  markets[i].type = 2; else
					if (strcmp("pre:outcometext", market_node->first_attribute("includes_outcomes_of_type")->value()) == 0)  markets[i].type = 3;
					else markets[i].type = 0;
		}

		if (market_node->first_attribute("groups") != nullptr && strcmp("player_props", (char*)market_node->first_attribute("groups")->value() + 4) == 0) {
			markets[i].type = 4;

		}


		if (market_node->first_node("outcomes")) for (xml_node<> * outcome_node = market_node->first_node("outcomes")->first_node("outcome"); outcome_node; outcome_node = outcome_node->next_sibling()) {
			outcome_id[markets[i].outcome_number] = atoi(outcome_node->first_attribute("id")->value());

			std::strcpy(outcome_name[markets[i].outcome_number], outcome_node->first_attribute("name")->value());
			markets[i].outcome_number++;

		}


		if (markets[i].outcome_number > 0) {
			markets[i].outcome_id = new int[markets[i].outcome_number];
			markets[i].outcome_name = new char*[markets[i].outcome_number];
			for (k = 0; k < markets[i].outcome_number; k++) {
				markets[i].outcome_name[k] = new char[strlen(outcome_name[k]) + 1];
				std::strcpy(markets[i].outcome_name[k], outcome_name[k]);
				markets[i].outcome_id[k] = outcome_id[k];
			}




		}



		markets[i].specifier_number = 0;
		j = 0;
		markets[i].variant = -1;
		if (market_node->first_node("specifiers")) for (xml_node<> * specifier_node = market_node->first_node("specifiers")->first_node("specifier"); specifier_node; specifier_node = specifier_node->next_sibling()) {
			if (specifier_node->first_attribute("descritions")) {
				specifier_description[j] = new char[NAME_LENTGH]; std::strcpy(specifier_description[j], specifier_node->first_attribute("descritions")->value());
			}
			else specifier_description[j] = nullptr;

			if (specifier_node->first_attribute("name")) {
				specifier_name[j] = new char[NAME_LENTGH]; std::strcpy(specifier_name[j], specifier_node->first_attribute("name")->value());

			}
			else specifier_name[j] = nullptr;

			//0 null //1 int //2 string 3://decimal 4//variable	
			specifier_type[j] = 0;

			if (specifier_node->first_attribute("type") != nullptr) {

				if (strcmp("integer", specifier_node->first_attribute("type")->value()) == 0)  specifier_type[j] = 1; else
					if (strcmp("string", specifier_node->first_attribute("type")->value()) == 0)  specifier_type[j] = 2; else
						if (strcmp("decimal", specifier_node->first_attribute("type")->value()) == 0)  specifier_type[j] = 3; else
							if (strcmp("variable_text", specifier_node->first_attribute("type")->value()) == 0) {
								specifier_type[j] = 4; markets[i].variant = j;
							}
			}

			j++;
			markets[i].specifier_number++;

		}





		if (markets[i].specifier_number > 0) {
			markets[i].specifier_type = new int[markets[i].specifier_number];
			markets[i].specifier_name = new char*[markets[i].specifier_number];
			markets[i].specifier_description = new char*[markets[i].specifier_number];

			for (k = 0; k < markets[i].specifier_number; k++) {
				if (specifier_name[k] != nullptr) {
					markets[i].specifier_name[k] = new char[strlen(specifier_name[k]) + 1]; std::strcpy(markets[i].specifier_name[k], specifier_name[k]);
				}
				else markets[i].specifier_name[k] = nullptr;


				if (specifier_description[k] != nullptr) {
					markets[i].specifier_description[k] = new char[strlen(specifier_description[k]) + 1]; std::strcpy(markets[i].specifier_description[k], specifier_description[k]);
				}
				else markets[i].specifier_description[k] = nullptr;

				markets[i].specifier_type[k] = specifier_type[k];

			}





		}



		markets_l = i + 1;

		//printf("markets[i].id=%d\r\n", markets[i].id);

		if (markets[i].id == 219) markets[i].line_type = 1;// (Winner(incl.overtime) Basketball,American Football
		if (markets[i].id == 16) markets[i].line_type = 3;// (Handicap)	Soccer,Basketball,Aussie Rules,Futsal,Handball,Ice Hockey,Rugby
		if (markets[i].id == 1) markets[i].line_type = 2;// (1x2) Soccer,Basketball,American Football,Aussie Rules,Bandy,Baseball,Beach Soccer,Counter-Strike,Cricket,Darts,Field hockey,Floorball,Futsal,Handball,Ice Hockey,Pesapallo,Rugby,Snooker,Soccer Mythical,Waterpolo
		if (markets[i].id == 186) markets[i].line_type = 1;//Tennis, Athletics, Aussie Rules, Badminton, Beach Volley, Bowls, Boxing, Counter - Strike, Curling, Darts, Dota 2, ESport Call of Duty, ESport Overwatch, League of Legends, MMA, Snooker, Squash, StarCraft, Table Tennis, Volleyball
		if (markets[i].id == 610) markets[i].line_type = 2;// (1x2)	Amercian Football
		if (markets[i].id == 406) markets[i].line_type = 1;//Winner (incl. overtime and penalties) Handball,Ice Hockey
		if (markets[i].id == 2) markets[i].line_type = 1; //To qualify Soccer
		if (markets[i].id == 60) markets[i].line_type = 5;// 1st half - 1x2 Soccer,Basketball,American Football,Aussie Rules,Futsal,Handball,Rugby,Soccer Mythical
		if (markets[i].id == 83) markets[i].line_type = 5;// 2nd half - 1x2 Soccer,Basketball,American Football,Handball,Soccer Mythical
		if (markets[i].id == 113) markets[i].line_type = 2;// Overtime - 1x2 Soccer,Futsal,Ice Hockey
		if (markets[i].id == 119) markets[i].line_type = 5;//Overtime 1st half - 1x2  Soccer
														   //if (markets[i].id == 120) markets[i].line_type = 7;//Overtime 1st half - handicap Soccer
		if (markets[i].id == 123) markets[i].line_type = 7;//Penalty shootout - winner
		if (markets[i].id == 711) markets[i].line_type = 5;//{!inningnr} innings - 1x2 Cricket
		if (markets[i].id == 645) markets[i].line_type = 5;//{!inningnr} innings over {overnr} - 1x2 Cricket
		if (markets[i].id == 611) markets[i].line_type = 5;//{!quarternr} quarter - 1x2 (incl. overtime) Amercan Football valid for quartner=4
		if (markets[i].id == 223) markets[i].line_type = 3;//Handicap (incl. overtime) Basketball,American Football
		if (markets[i].id == 410) markets[i].line_type = 3;//Handicap (incl. overtime and penalties) Ice Hockey
		if (markets[i].id == 66) markets[i].line_type = 7;//1st half - handicap
		if (markets[i].id == 88) markets[i].line_type = 7;//2nd half - handicap
		if (markets[i].id == 460) markets[i].line_type = 7;//{!periodnr} period - handicap Ice Hockey
		if (markets[i].id == 303) markets[i].line_type = 7;//{!quarternr} quarter - handicap Basketball,American Football,Aussie Rules
		if (markets[i].id == 203) markets[i].line_type = 7;//{!setnr} set - game handicap Tennis

		if (markets[i].id == 527) markets[i].line_type = 7;//{!setnr} set - handicap  Bowls
		if (markets[i].id == 314) markets[i].line_type = 4;//Total sets - Bowls Darts
		if (markets[i].id == 315) markets[i].line_type = 5;//{!setnr} set - 1x2 Bowls
		if (markets[i].id == 188) markets[i].line_type = 3;//Set handicap Bowls
		if (markets[i].id == 493) markets[i].line_type = 3;//Frame handicap Snooker
		if (markets[i].id == 494) markets[i].line_type = 4;//Total handicap Snooker
		if (markets[i].id == 499) markets[i].line_type = 6;//{!framenr} frame - winner Snooker


		if (markets[i].id == 204) markets[i].line_type = 8;//{!setnr} set - total games  Tennis
		if (markets[i].id == 746) markets[i].line_type = 7;//{!inningnr} inning - handicap Baseball
		if (markets[i].id == 117) markets[i].line_type = 3;//Overtime - handicap Soccer,Handball
		if (markets[i].id == 120) markets[i].line_type = 7;//Overtime 1st half - handicap Soccer
		if (markets[i].id == 18) markets[i].line_type = 4;//Total Soccer,Futsal,Handball,Ice Hockey,Rugby,Soccer Mythical
		if (markets[i].id == 412) markets[i].line_type = 4;//Total (incl. overtime and penalties) Ice Hockey
		if (markets[i].id == 238) markets[i].line_type = 4;//Total points Badminton,Beach Volley,Squash,Table Tennis,Volleyball
		if (markets[i].id == 68) markets[i].line_type = 8;//1st half - total Soccer,Basketball,American Football,Futsal,Handball,Rugby,Soccer Mythical
		if (markets[i].id == 90) markets[i].line_type = 8;//2nd half - total Soccer,Soccer Mythical
		if (markets[i].id == 446) markets[i].line_type = 8;//{!periodnr} period - total Ice Hockey
		if (markets[i].id == 236) markets[i].line_type = 8;//{!quarternr} quarter - total Basketball,American Football,Aussie Rules
		if (markets[i].id == 310) markets[i].line_type = 8;//{!setnr} set - total points Beach Volley,Volleyball
		if (markets[i].id == 528) markets[i].line_type = 8;//{!setnr} set - total Bowls

		if (markets[i].id == 288) markets[i].line_type = 8;//{!inningnr} inning - total Baseball
		if (markets[i].id == 116) markets[i].line_type = 4;//Overtime - total Soccer,Futsal,Handball,Ice Hockey
		if (markets[i].id == 358) markets[i].line_type = 8;//1st over - total Cricket
		if (markets[i].id == 395) markets[i].line_type = 6;//{!mapnr} map - winner Dota 2,League of Legends,StarCraft
		if (markets[i].id == 330) markets[i].line_type = 6;//{!mapnr} map - winner (incl. overtime) Counter-Strike
		if (markets[i].id == 334) markets[i].line_type = 5;//{!mapnr} map - 1x2 Counter-Strike


		if (markets[i].id == 340) markets[i].line_type = 1;//Winner (incl. super over) Cricket
		if (markets[i].id == 251) markets[i].line_type = 1;// Winner (incl. extra innings) Baseball
														   //if (markets[k].id == 426) markets[k].line_type = 5;//{!periodnr} period 1x2 & winner (incl. overtime and penalties) Ice Hockey
														   //if (markets[k].id == 429) markets[k].line_type = 5;//{!periodnr} period 1x2 & 1x2 Ice Hockey
		if (markets[i].id == 443) markets[i].line_type = 5;//{!periodnr} period 1x2  Ice Hockey

		if (markets[i].id == 225) markets[i].line_type = 4;// Total (incl. overtime) Basketball
		if (markets[i].id == 501) markets[i].line_type = 8;//{!framenr} frame - total points Snooker
		if (markets[i].id == 500) markets[i].line_type = 7;//{!framenr} frame - handicap points Snooker
		if (markets[i].id == 527) markets[i].line_type = 7;//{!setnr} set - handicap Bowls
		if (markets[i].id == 226) markets[i].line_type = 4;//US total (incl. overtime) Basketball,American Football
		if (markets[i].id == 315) markets[i].line_type = 5;//{!setnr} set - 1x2 Bowls
		if (markets[i].id == 287) markets[i].line_type = 5;//{!inningnr} inning - 1x2 Baseball

		if (markets[i].id == 245) markets[i].line_type = 6;//{!gamenr} game - winner Badminton,Squash,Table Tennis
		if (markets[i].id == 235) markets[i].line_type = 5;//{!quarternr} quarter - 1x2 Basketball,American Football,Aussie Rules
														   //if (markets[i].id == 445) markets[i].line_type = 7;//{!periodnr} period - handicap {hcp} Ice Hockey
														   //if (markets[i].id == 446) markets[i].line_type = 8;//{!periodnr} period - total Ice Hockey
		if (markets[i].id == 246) markets[i].line_type = 7;//{!gamenr} game - point handicap Badminton,Squash,Table Tennis
		if (markets[i].id == 247) markets[i].line_type = 8;// {!gamenr} game - total points Badminton,Squash,Table Tennis
		if (markets[i].id == 460) markets[i].line_type = 7;//{!periodnr} period - handicap Ice Hockey
														   //if (markets[i].id == 254) markets[i].line_type = 3;//Handicap {hcp} (incl. extra innings) Baseball
		if (markets[i].id == 256) markets[i].line_type = 3;//Handicap (incl. extra innings) Baseball
		if (markets[i].id == 258) markets[i].line_type = 4;//Total (incl. extra innings) Baseball
		if (markets[i].id == 371) markets[i].line_type = 7;// {!setnr} set - leg handicap Darts
		if (markets[i].id == 372) markets[i].line_type = 8;// {!setnr} set - total legs Darts	

		if (markets[i].id == 605) markets[i].line_type = 8;//{!inningnr} innings - total Cricket
		if (markets[i].id == 189) markets[i].line_type = 4;//Total games Tennis
		if (markets[i].id == 237) markets[i].line_type = 3;//Point handicap Badminton,Beach Volley,Squash,Table Tennis,Volleyball
		if (markets[i].id == 538) markets[i].line_type = 2;//Head2head (1x2) Golf,Motorsport
		if (markets[i].id == 8) markets[i].line_type = 9;//{!goalnr} goal Soccer,Futsal,Ice Hockey
		if (markets[i].id == 62) markets[i].line_type = 10;//1st half - {!goalnr} goal Soccer,Futsal
		if (markets[i].id == 84) markets[i].line_type = 10;//2nd half - {!goalnr} goal Soccer,Futsal
		if (markets[i].id == 444) markets[i].line_type = 10;//{!periodnr} period - {!goalnr} goal Ice Hockey
															//if (markets[i].id == 245) markets[i].line_type = 10;//{!gamenr} game - winner Badminton,Squash,Table Tennis
		if (markets[i].id == 210) markets[i].line_type = 10;//{!setnr} set game{ gamenr } -winner Tennis
		if (markets[i].id == 125) markets[i].line_type = 10;//Penalty shootout - {!goalnr} goal Soccer,Futsal,Ice Hockey
		if (markets[i].id == 115) markets[i].line_type = 9;//Overtime - {!goalnr} goal Soccer,Futsal,Ice Hockey
		if (markets[i].id == 202) markets[i].line_type = 6;// {!setnr} set - winner	Tennis Beach Volley,Darts,Volleyball
		if (markets[i].id == 309) markets[i].line_type = 7;//{!setnr} set - point handicap Beach Volley,Volleyball
		if (markets[i].id == 29) markets[i].line_type = 11;//Both teams to score
		if (markets[i].id == 196) markets[i].line_type = 13;//Exact sets Tennis,Beach Volley,Volleyball

															//if (markets[i].id == 444) printf("line_type1=%\r\n", markets[i].line_type);

															//if (markets[i].id == 75) markets[i].line_type = 12;//1st half - both teams to score
															//if (markets[i].id == 29) markets[i].line_type = 11;//Both teams to score










		if (markets[i].variant >-1)
		{

			if (markets[i].id < MAX_MARKETS) {


				markets_id[markets[i].id] = new Market*[MAX_MARKETS_IN];
				for (int l = 0; l < MAX_MARKETS_IN; l++) markets_id[markets[i].id][l] = nullptr;
				markets_id[markets[i].id][0] = &markets[i];
				saveMarketToDB(&markets[i]);
			}
			else { std::printf("ERROR DATA!\r\nmarket id out of MAX_MARKETS in getMarkets%d\r\n", markets[i].id); continue; }

			if (market_node->first_node("mappings") && market_node->first_node("mappings")->first_node("mapping"))

				for (xml_node<> * mapping_node = market_node->first_node("mappings")->first_node("mapping"); mapping_node; mapping_node = mapping_node->next_sibling()) {



					if (mapping_node->first_attribute("valid_for")) {
						v = mapping_node->first_attribute("valid_for")->value_size();
						for (u = 0; u < v - 8; u++) if (mapping_node->first_attribute("valid_for")->value()[u] == 'v'&& mapping_node->first_attribute("valid_for")->value()[u + 1] == 'a'&& mapping_node->first_attribute("valid_for")->value()[u + 2] == 'r' && mapping_node->first_attribute("valid_for")->value()[u + 6] == 't'&& mapping_node->first_attribute("valid_for")->value()[u + 7] == '=') break;
						if (u == v - 8) continue;
						strcpy(urn, (char*)((char*)mapping_node->first_attribute("valid_for")->value()) + 8 + u);

						for (int i = 0; i < v - 8 - u; i++) if (urn[i] == '|') { urn[i] = 0; break; }

						getVariantMarket(&markets[i], urn);
					}
				}


		}
		else {
			if (markets[i].id < MAX_MARKETS) {
				markets_id[markets[markets_l - 1].id] = new Market*[1];
				markets_id[markets[markets_l - 1].id][0] = &markets[markets_l - 1];
				saveMarketToDB(&markets[markets_l - 1]);
			}
			else {
				std::printf("ERROR DATA!\r\nmarket id out of MAX_MARKETS in getMarkets%d\r\n", markets[i].id); continue;
			}

			//printf(markets_id[markets[markets_l - 1].id][0]->name);

			//printf("\r\n");
		}


	}


	std::printf("Load %d markets done.\r\n", markets_l);

	for (int i = 0; i < MAX_PATH; i++) { if (specifier_name[i] != nullptr) delete[] specifier_name[i]; if (specifier_description[i] != nullptr) delete[] specifier_description[i]; }
	delete[] specifier_name;
	delete[] specifier_description;
	delete[] specifier_type;
	for (i = 0; i < MAX_OUTCOME; i++) delete[] outcome_name[i];
	delete[] outcome_name;
	delete[] outcome_id;
	delete[] recvbuf;
	delete[] urn;
	doc.clear();

}
void getMarketsTranslate(int l) {
	char* recvbuf = new char[EXTRA];
	char buffer[MAX_PATH];
	char buf[MAX_PATH];
	char* request = new char[MAX_PATH];
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;
	Market* market;
	//using namespace std;
	int k = 0;
	int i = 0;
	int j = 0;
	int u = 0;
	int v = 0;

	std::strcpy(request, "/v1/descriptions/");
	std::strcat(request, lang[l].c_str());
	std::strcat(request, "/markets.xml?include_mappings=true");

	while (httpsRequest("api.betradar.com", request, recvbuf, 0) == -1) Sleep(1000);
	//httpsRequest("api.betradar.com", "/v1/descriptions/en/markets.xml?include_mappings=true", recvbuf2, 0);

	if (recvbuf[0] == 0) return;

	for (k = 0; k < 1000; k++) if (recvbuf[k] == '\r' && recvbuf[k + 1] == '\n' && recvbuf[k + 2] == '\r' && recvbuf[k + 3] == '\n') break;
	doc.parse<0>((char*)((char*)recvbuf + k + 4));
	root_node = doc.first_node("market_descriptions");
	if (root_node == nullptr) {
		delete[] recvbuf;
		delete[] request;
		doc.clear();
		return;
	}


	int id;

	for (xml_node<> * market_node = root_node->first_node("market"); market_node; market_node = market_node->next_sibling())
	{
		id = atoi(market_node->first_attribute("id")->value());
		if (markets_id[id] == nullptr || markets_id[id][0] == nullptr) continue;
		market = markets_id[id][0];
		market->translation_name[l] = new char[strlen(market_node->first_attribute("name")->value()) + 1];
		std::strcpy(market->translation_name[l], market_node->first_attribute("name")->value());
		if (l > 0 && market->name != nullptr && strcmp(market->translation_name[l], market->name) == 0)
		{
			delete[] market->translation_name[l];
			market->translation_name[l] = nullptr; continue;

		}



		int outcome_number = 0;

		if (market->outcome_number > 0) market->translation_outcome_name[l] = new char*[market->outcome_number];

		if (market_node->first_node("outcomes")) for (xml_node<> * outcome_node = market_node->first_node("outcomes")->first_node("outcome"); outcome_node; outcome_node = outcome_node->next_sibling()) {
			market->translation_outcome_name[l][outcome_number] = new char[strlen(outcome_node->first_attribute("name")->value()) + 1];
			std::strcpy(market->translation_outcome_name[l][outcome_number], outcome_node->first_attribute("name")->value());
			outcome_number++;
			if (outcome_number >= market->outcome_number) break;

		}





	}



	delete[] request;
	delete[] recvbuf;
	doc.clear();

}
int getPlayer(Player* player, bool b) {
	char* recvbuf = new char[EXTRA];
	char buf[20];
	char buffer[1024];
	_itoa(player->id, buf, 10);
	std::strcpy(buffer, "/v1/sports/en/players/sr:player:");
	std::strcat(buffer, buf);
	std::strcat(buffer, "/profile.xml");
	while (httpsRequest("api.betradar.com", buffer, recvbuf, 0) == -1) Sleep(1000);
	if (recvbuf[0] == 0) return -1;
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;
	SYSTEMTIME st;
	struct tm tm;
	time_t start;
	memset(&st, 0, sizeof(st));
	memset(&tm, 0, sizeof(tm));

	Player** players_id;


	if (b == true) {
		players_id = ::bplayers_id;

	}
	else {
		players_id = ::players_id;

	}

	using namespace std;
	int j = 0;

	int recv_length = strlen(recvbuf) - 4; if (recv_length > 1000) recv_length = 1000; for (j = 0; j < recv_length; j++) if (recvbuf[j] == '\r' && recvbuf[j + 1] == '\n' && recvbuf[j + 2] == '\r' && recvbuf[j + 3] == '\n') break; if (j == recv_length) { delete[] recvbuf; return -1; }

	//printf(((char*)((char*)recvbuf + j + 4)));
	try { doc.parse<0>((char*)((char*)recvbuf + j + 4)); }
	catch (parse_error e) { cerr << "Fail. Parse error " << e.what() << endl; delete[] recvbuf; return -1; }
	//printf(((char*)((char*)recvbuf + j + 4)));
	//printf("\r\n\r\n");
	root_node = doc.first_node("player_profile");
	if (root_node == nullptr) { delete[] recvbuf; doc.clear(); return -1; }
	xml_node<> * player_node = root_node->first_node("player"); if (player_node == nullptr) {
		delete[] recvbuf; doc.clear(); return -1;
	}

	if (player_node->first_attribute("date_of_birth")) {
		std::strcpy(buf, player_node->first_attribute("date_of_birth")->value());

		sscanf(buf, "%d-%d-%dT%d:%d:%d", &st.wYear, &st.wMonth, &st.wDay, &st.wHour, &st.wMinute, &st.wSecond);
		tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
		tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
		start = mktime(&tm);
		player->date_of_birth = (int)start;
	}
	if (player_node->first_attribute("name"))
	{
		if (player->name != nullptr) delete[] player->name; player->name = new char[strlen(player_node->first_attribute("name")->value()) + 1]; std::strcpy(player->name, player_node->first_attribute("name")->value());
		//std::printf("name_length=%d\r\n", strlen(player_node->first_attribute("name")->value()));
	}
	if (player_node->first_attribute("full_name"))
	{
		if (player->full_name != nullptr) delete[] player->full_name; player->full_name = new char[strlen(player_node->first_attribute("full_name")->value()) + 1]; std::strcpy(player->full_name, player_node->first_attribute("full_name")->value());

		//std::printf("full_name_length=%d\r\n", strlen(player_node->first_attribute("full_name")->value()));

	}
	if (player_node->first_attribute("nationality"))
	{
		if (player->nationality != nullptr) delete[] player->nationality; player->nationality = new char[strlen(player_node->first_attribute("nationality")->value()) + 1]; std::strcpy(player->nationality, player_node->first_attribute("nationality")->value());

		//std::printf("nationality_length=%d\r\n", strlen(player_node->first_attribute("nationality")->value()));
	}
	if (player_node->first_attribute("country_code"))
	{
		if (player->country_code != nullptr) delete[] player->country_code; player->country_code = new char[strlen(player_node->first_attribute("country_code")->value()) + 1]; std::strcpy(player->country_code, player_node->first_attribute("country_code")->value());
	}
	if (player_node->first_attribute("type"))
	{
		if (player->type != nullptr) delete[] player->type; player->type = new char[strlen(player_node->first_attribute("type")->value()) + 1]; std::strcpy(player->type, player_node->first_attribute("type")->value());
	}
	if (player_node->first_attribute("height"))
	{
		player->height = atoi(player_node->first_attribute("height")->value());
	}
	if (player_node->first_attribute("weight"))
	{
		player->height = atoi(player_node->first_attribute("weight")->value());
	}

	if (player->id >= MAX_PLAYERS) {
		std::printf("ERROR DATA!\r\nplayers id out of MAX_PLAYERS in getPlayer%d\r\n", player->id);

	}
	else if (players_id[player->id] == nullptr) players_id[player->id] = player;
	if (b == false) savePlayerToDB(player);
	doc.clear();
	delete[] recvbuf;
	return 0;
}
int getPlayerTranslate(Player* player, int l) {
	char* recvbuf = new char[EXTRA];
	char buf[20];
	char buffer[1024];
	_itoa(player->id, buf, 10);
	std::strcpy(buffer, "/v1/sports/");
	std::strcat(buffer, lang[l].c_str());
	std::strcat(buffer, "/players/sr:player:");
	std::strcat(buffer, buf);
	std::strcat(buffer, "/profile.xml");
	while (httpsRequest("api.betradar.com", buffer, recvbuf, 0) == -1) Sleep(1000);
	//printf(recvbuf);
	if (recvbuf[0] == 0) return -1;

	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;
	SYSTEMTIME st;
	struct tm tm;
	time_t start;
	memset(&st, 0, sizeof(st));
	memset(&tm, 0, sizeof(tm));

	using namespace std;
	int j = 0;
	int recv_length = strlen(recvbuf) - 4; if (recv_length > 1000) recv_length = 1000;	for (j = 0; j < recv_length; j++) if (recvbuf[j] == '\r' && recvbuf[j + 1] == '\n' && recvbuf[j + 2] == '\r' && recvbuf[j + 3] == '\n') break;
	if (j == recv_length || j < 5) { delete[] recvbuf; return -1; }
	try { doc.parse<0>((char*)((char*)recvbuf + j + 4)); }
	catch (parse_error e) { cerr << "Fail. Parse error " << e.what() << endl; delete[] recvbuf; return -1; }

	//printf(((char*)((char*)recvbuf + j + 4)));
	//printf("\r\n\r\n");
	root_node = doc.first_node("player_profile");

	if (root_node == nullptr) { delete[] recvbuf; doc.clear(); return -1; }
	xml_node<> * player_node = root_node->first_node("player"); if (player_node == nullptr) {
		delete[] recvbuf; doc.clear(); return -1;
	}


	if (player_node->first_attribute("name"))
	{
		player->translation_name[l] = new char[strlen(player_node->first_attribute("name")->value()) + 1];
		std::strcpy(player->translation_name[l], player_node->first_attribute("name")->value());
		if (l > 0 && player->name != nullptr && strcmp(player->translation_name[l], player->name) == 0)
		{
			delete[] player->translation_name[l]; player->translation_name[l] = nullptr;
		}

	}

	if (player_node->first_attribute("full_name"))
	{

		player->translation_full_name[l] = new char[strlen(player_node->first_attribute("full_name")->value()) + 1];
		std::strcpy(player->translation_full_name[l], player_node->first_attribute("full_name")->value());
		if (l > 0 && player->full_name != nullptr && strcmp(player->translation_full_name[l], player->full_name) == 0)
		{
			delete[] player->translation_full_name[l]; player->translation_full_name[l] = nullptr;
		}


	}
	if (player_node->first_attribute("nationality"))
	{

		player->translation_nationality[l] = new char[strlen(player_node->first_attribute("nationality")->value()) + 1];
		std::strcpy(player->translation_nationality[l], player_node->first_attribute("nationality")->value());
		if (l > 0 && player->nationality != nullptr && strcmp(player->translation_nationality[l], player->nationality) == 0)
		{
			delete[] player->translation_nationality[l]; player->translation_nationality[l] = nullptr;
		}


	}

	if (player_node->first_attribute("type"))
	{
		player->translation_type[l] = new char[strlen(player_node->first_attribute("type")->value()) + 1];
		std::strcpy(player->translation_type[l], player_node->first_attribute("type")->value());
		if (l > 0 && player->type != nullptr && strcmp(player->translation_type[l], player->type) == 0)
		{
			delete[] player->translation_type[l]; player->translation_type[l] = nullptr;
		}

	}

	doc.clear();
	delete[] recvbuf;
	return 0;

}
int getCompetitor(Competitor* competitor, bool b) {
	char* recvbuf = new char[EXTRA];
	Player* player = nullptr;
	char buf[20];
	char buffer[1024];
	_itoa(competitor->id, buf, 10);
	std::strcpy(buffer, "/v1/sports/en/competitors/sr:competitor:");
	std::strcat(buffer, buf);
	std::strcat(buffer, "/profile.xml");
	while (httpsRequest("api.betradar.com", buffer, recvbuf, 0) == -1) Sleep(1000);
	if (recvbuf[0] == 0) return -1;
	using namespace rapidxml;
	SYSTEMTIME st;
	struct tm tm;
	time_t start;
	memset(&st, 0, sizeof(st));
	memset(&tm, 0, sizeof(tm));

	//printf("getCompetitor1 competitor_id=%d b=%d\r\n",competitor->id, b);

	Player** players_id;
	Player* players;
	Competitor** competitors_id;
	int* rplayers_l;


	if (b == true) {
		competitors_id = ::bcompetitors_id;
		rplayers_l = &::bplayers_l;
		players_id = ::bplayers_id;
		players = ::bplayers;

	}
	else {
		competitors_id = ::competitors_id;
		rplayers_l = &::players_l;
		players_id = ::players_id;
		players = ::players;

	}

	//printf("getCompetitor2 competitor->id=%d b=%d *rplayers_l=%d bplayers_l=%d players_l=%d\r\n", competitor->id, b,  *rplayers_l, bplayers_l, players_l);


	xml_document<> doc;
	xml_node<> * root_node;
	int j = 0;
	int i = 0;

	int recv_length = strlen(recvbuf) - 4; if (recv_length > 1000) recv_length = 1000; for (j = 0; j < recv_length; j++) if (recvbuf[j] == '\r' && recvbuf[j + 1] == '\n' && recvbuf[j + 2] == '\r' && recvbuf[j + 3] == '\n') break; if (j == recv_length || j< 5) { delete[] recvbuf; return -1; }

	//printf(((char*)((char*)recvbuf + j + 4)));
	try { doc.parse<0>((char*)((char*)recvbuf + j + 4)); }
	catch (parse_error e) { cerr << "Fail. Parse error " << e.what() << endl; delete[] recvbuf; return -1; }



	//printf(((char*)((char*)recvbuf + j + 4)));
	//printf("\r\n\r\n");
	root_node = doc.first_node("competitor_profile");
	if (root_node == nullptr) { delete[] recvbuf;  doc.clear(); return -1; }
	xml_node<> * competitor_node = root_node->first_node("competitor"); if (competitor_node == nullptr) { delete[] recvbuf; doc.clear(); return -1; }




	if (competitor_node->first_attribute("name")) {
		if (competitor->name != nullptr) delete[] competitor->name; competitor->name = new char[strlen(competitor_node->first_attribute("name")->value()) + 1]; std::strcpy(competitor->name, competitor_node->first_attribute("name")->value());
	}

	if (competitor_node->first_attribute("country")) {
		if (competitor->country_name != nullptr) delete[] competitor->country_name; competitor->country_name = new char[strlen(competitor_node->first_attribute("country")->value()) + 1]; std::strcpy(competitor->country_name, competitor_node->first_attribute("country")->value());
	}

	if (competitor_node->first_node("sport") && competitor_node->first_node("sport")->first_attribute("id"))
	{
		competitor->sport_id = atoi((char*)((char*)competitor_node->first_node("sport")->first_attribute("id")->value() + 9));
	}


	if (competitor_node->first_node("category") && competitor_node->first_node("category")->first_attribute("id"))
	{
		competitor->category_id = atoi((char*)((char*)competitor_node->first_node("category")->first_attribute("id")->value() + 12));
	}


	if (competitor->id >= MAX_COMPETITORS) {
		std::printf("ERROR DATA!\r\ncompetitors id out of MAX_COMPETITORS in getCompetitors %d\r\n", competitor->id);
		delete[] recvbuf;  doc.clear(); return -1;
	}
	else  competitors_id[competitor->id] = competitor;

	//	std::printf("competitors_l=%d\r\n", competitors_l);

	//printf("getCompetitor3 competitor->id=%d b=%d *rplayers_l=%d bplayers_l=%d players_l=%d\r\n", competitor->id, b, *rplayers_l, bplayers_l, players_l);

	if (b == false) saveCompetitorToDB(competitor);

	//printf("getCompetitor4 competitor->id=%d b=%d *rplayers_l=%d bplayers_l=%d players_l=%d\r\n", competitor->id, b, *rplayers_l, bplayers_l, players_l);


	xml_node<> * manager_node = root_node->first_node("manager");
	if (manager_node) {


		int player_id = atoi((char*)((char*)manager_node->first_attribute("id")->value() + 10));


		if (player_id >= MAX_PLAYERS) {
			std::printf("ERROR DATA!\r\nplayers id out of MAX_PLAYERS in getCompetitor%d\r\n", player_id);
		}
		else {
			if (players_id[player_id] == nullptr) {
				players_id[player_id] = &players[*rplayers_l];
				(*rplayers_l)++;
			}
			player = players_id[player_id];
			player->id = player_id;

			player->competitor_id = competitor->id;
			player->manager = 1;


			if (manager_node->first_attribute("name"))
			{
				if (player->name != nullptr) delete[] player->name; player->name = new char[strlen(manager_node->first_attribute("name")->value()) + 1]; std::strcpy(player->name, manager_node->first_attribute("name")->value());
			}

			if (manager_node->first_attribute("nationality"))
			{
				if (player->nationality != nullptr) delete[] player->nationality; player->nationality = new char[strlen(manager_node->first_attribute("nationality")->value()) + 1]; std::strcpy(player->nationality, manager_node->first_attribute("nationality")->value());
			}
			if (b == false) savePlayerToDB(player);

		}

	}



	if (root_node->first_node("players"))
		for (xml_node<> * player_node = root_node->first_node("players")->first_node("player"); player_node; player_node = player_node->next_sibling())
		{
			int player_id = atoi((char*)((char*)player_node->first_attribute("id")->value() + 10));


			if (player_id >= MAX_PLAYERS) {
				std::printf("ERROR DATA!\r\nplayers id out of MAX_PLAYERS in getCompetitor%d\r\n", player_id); continue;
			}
			else if (players_id[player_id] == nullptr) {
				players_id[player_id] = &players[*rplayers_l];
				(*rplayers_l)++;
			}
			player = players_id[player_id];
			player->id = player_id;
			player->competitor_id = competitor->id;

			if (player_node->first_attribute("date_of_birth")) {
				std::strcpy(buf, player_node->first_attribute("date_of_birth")->value());

				sscanf(buf, "%d-%d-%dT%d:%d:%d", &st.wYear, &st.wMonth, &st.wDay, &st.wHour, &st.wMinute, &st.wSecond);
				tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
				tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
				start = mktime(&tm);
				player->date_of_birth = (int)start;
			}

			if (player_node->first_attribute("name"))
			{
				if (player->name != nullptr) delete[] player->name; player->name = new char[strlen(player_node->first_attribute("name")->value()) + 1]; std::strcpy(player->name, player_node->first_attribute("name")->value());
				//std::printf("name_length=%d\r\n", strlen(player_node->first_attribute("name")->value()));
			}

			if (player_node->first_attribute("full_name"))
			{
				if (player->full_name != nullptr) delete[] player->full_name; player->full_name = new char[strlen(player_node->first_attribute("full_name")->value()) + 1]; std::strcpy(player->full_name, player_node->first_attribute("full_name")->value());

				//std::printf("full_name_length=%d\r\n", strlen(player_node->first_attribute("full_name")->value()));

			}
			if (player_node->first_attribute("nationality"))
			{
				if (player->nationality != nullptr) delete[] player->nationality; player->nationality = new char[strlen(player_node->first_attribute("nationality")->value()) + 1]; std::strcpy(player->nationality, player_node->first_attribute("nationality")->value());

				//std::printf("nationality_length=%d\r\n", strlen(player_node->first_attribute("nationality")->value()));
			}
			if (player_node->first_attribute("country_code"))
			{
				if (player->country_code != nullptr) delete[] player->country_code; player->country_code = new char[strlen(player_node->first_attribute("country_code")->value()) + 1]; std::strcpy(player->country_code, player_node->first_attribute("country_code")->value());
			}
			if (player_node->first_attribute("type"))
			{
				if (player->type != nullptr) delete[] player->type; player->type = new char[strlen(player_node->first_attribute("type")->value()) + 1]; std::strcpy(player->type, player_node->first_attribute("type")->value());

			}
			if (player_node->first_attribute("height"))
			{
				player->height = atoi(player_node->first_attribute("height")->value());
			}
			if (player_node->first_attribute("jersey_number"))
			{
				player->number = atoi(player_node->first_attribute("jersey_number")->value());
			}
			if (player_node->first_attribute("weight"))
			{
				player->height = atoi(player_node->first_attribute("weight")->value());
			}

			//printf(" player->id=%d\r\n", player->id);
			//for (i = 0; i < players_l; i++) if (players[i].id == player->id) break;
			//players[i] = player[0]; if (i == players_l) players_l++;


			if (b == false) savePlayerToDB(player);

		}

	delete[] recvbuf;
	doc.clear();
	return 0;
}
int getCompetitorTranslate(Competitor* competitor, int l) {
	char* recvbuf = new char[EXTRA];
	char buf[20];
	char buffer[1024];
	_itoa(competitor->id, buf, 10);
	std::strcpy(buffer, "/v1/sports/");
	std::strcat(buffer, lang[l].c_str());
	std::strcat(buffer, "/competitors/sr:competitor:");
	std::strcat(buffer, buf);
	std::strcat(buffer, "/profile.xml");
	while (httpsRequest("api.betradar.com", buffer, recvbuf, 0) == -1) Sleep(1000);
	if (recvbuf[0] == 0) return -1;
	using namespace rapidxml;

	xml_document<> doc;
	xml_node<> * root_node;
	int j = 0;
	int i = 0;

	int recv_length = strlen(recvbuf) - 4; if (recv_length > 1000) recv_length = 1000; for (j = 0; j < recv_length; j++) if (recvbuf[j] == '\r' && recvbuf[j + 1] == '\n' && recvbuf[j + 2] == '\r' && recvbuf[j + 3] == '\n') break; if (j == recv_length || j< 5) { delete[] recvbuf; return -1; }
	//printf(((char*)((char*)recvbuf + j + 4)));
	try { doc.parse<0>((char*)((char*)recvbuf + j + 4)); }
	catch (parse_error e) { cerr << "Fail. Parse error " << e.what() << endl; delete[] recvbuf; return -1; }
	//printf(((char*)((char*)recvbuf + j + 4)));
	//printf("\r\n\r\n");
	root_node = doc.first_node("competitor_profile");
	if (root_node == nullptr) { delete[] recvbuf;  doc.clear(); return -1; }
	xml_node<> * competitor_node = root_node->first_node("competitor"); if (competitor_node == nullptr) { delete[] recvbuf; doc.clear(); return -1; }

	if (competitor_node->first_attribute("name")) {

		competitor->translation_name[l] = new char[strlen(competitor_node->first_attribute("name")->value()) + 1];
		std::strcpy(competitor->translation_name[l], competitor_node->first_attribute("name")->value());
		if (l > 0 && competitor->name != nullptr && strcmp(competitor->name, competitor->translation_name[l]) == 0)
		{
			delete[] competitor->translation_name[l]; competitor->translation_name[l] = nullptr;

		}
	}

	if (competitor_node->first_attribute("country")) {
		competitor->translation_country_name[l] = new char[strlen(competitor_node->first_attribute("country")->value()) + 1];
		std::strcpy(competitor->translation_country_name[l], competitor_node->first_attribute("country")->value());

		if (l > 0 && competitor->country_name != nullptr && strcmp(competitor->country_name, competitor->translation_country_name[l]) == 0)
		{
			delete[] competitor->translation_country_name[l]; competitor->translation_country_name[l] = nullptr;

		}
	}

	//printf("getCompetitor4 competitor->id=%d b=%d *rplayers_l=%d bplayers_l=%d players_l=%d\r\n", competitor->id, b, *rplayers_l, bplayers_l, players_l);


	delete[] recvbuf;
	doc.clear();
	return 0;
}
int getEventFixture(Event* event, bool b) {
	char buf[10];
	char buffer[8192];
	char* recvbuf = new char[EXTRA];
	//if (event->type_radar == 1) return;
	_itoa(event->id, buf, 10);
	if (event->type_radar == 0 || event->type_radar == 2) std::strcpy(buffer, "/v1/sports/en/sport_events/sr:match:");
	//else std::strcpy(buffer, "/v1/unified/betradar/en/sport_events/sr:stage:");
	else if (event->type_radar == 1 ) std::strcpy(buffer, "/v1/sports/en/sport_events/sr:stage:");
	else if (event->type_radar == 3) std::strcpy(buffer, "/v1/sports/en/sport_events/vf:match:");
	else { delete[] recvbuf;  return -1; };
	std::strcat(buffer, buf);
	std::strcat(buffer, "/fixture.xml");
	//printf("getEventFixture0=%s\r\n", buffer);
	//printf("start getEventFixture b=%d\r\n", b);
	//if (event->id != 13422295) return 0;
	while (httpsRequest("api.betradar.com", buffer, recvbuf, 0) == -1) Sleep(1000);
	//while (httpRequest("bsa-staging.betradar.com", buffer, recvbuf, 0) == -1) Sleep(1000);

	//printf(recvbuf);
	//printf("\r\n");

	//printf("event->id=%d event->type_radar=%d \r\n",event->id, event->type_radar);

	//printf("01 getEventFixture b=%d\r\n", b);
	if (recvbuf[0] == 0) { delete[] recvbuf;  return -1; }
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;
	SYSTEMTIME st;
	struct tm tm;
	time_t start;
	memset(&st, 0, sizeof(st));
	memset(&tm, 0, sizeof(tm));
	Category** categories_id;
	Category* categories;
	//Tournament** seasons_id;
	//Tournament** simples_id;
	//Tournament** tournaments_id;
	Tournament* tournaments;
	Tournament* _tournament;
	unordered_map<string, Tournament*>* rtournaments_id;
	unordered_map<string, Tournament*>* rseasons_id;
	//Event** events_id;
	unordered_map<string, Event*>* revents_id;
	int* rcategories_l;
	int* rtournaments_l;
	int ret_value = 0;
	int ret_fixture = 0;
	Competitor** competitors_id;
	Competitor* competitors;
	int* rcompetitors_l;

	//printf("02 getEventFixture b=%d\r\n", b);

	if (b == true) {
		categories_id = ::bcategories_id;
		categories = ::bcategories;
		rcategories_l = &::bcategories_l;
		revents_id = &::bevents_id;
		rtournaments_id = &::btournaments_id;
		tournaments = ::btournaments;
		rseasons_id = &::bseasons_id;
		//simples_id = ::bsimples_id;
		rtournaments_l = &::btournaments_l;
		competitors_id = ::bcompetitors_id;
		competitors = ::bcompetitors;
		rcompetitors_l = &::bcompetitors_l;
	}
	else {
		categories_id = ::categories_id;
		categories = ::categories;
		rcategories_l = &::categories_l;
		revents_id = &::events_id;
		rtournaments_id = &::tournaments_id;
		tournaments = ::tournaments;
		rseasons_id = &::seasons_id;
		//simples_id = ::simples_id;
		rtournaments_l = &::tournaments_l;
		competitors_id = ::competitors_id;
		competitors = ::competitors;
		rcompetitors_l = &::competitors_l;

	}

	//printf("1 getEventFixture b=%d\r\n", b);;
	using namespace std;
	int j = 0;
	int i = 0;
	int recv_length = strlen(recvbuf) - 4; if (recv_length > 1000) recv_length = 1000; for (j = 0; j < recv_length; j++) if (recvbuf[j] == '\r' && recvbuf[j + 1] == '\n' && recvbuf[j + 2] == '\r' && recvbuf[j + 3] == '\n') break; if (j == recv_length || j< 5) { delete[] recvbuf;  return -1; }
	try { doc.parse<0>((char*)((char*)recvbuf + j + 4)); }
	catch (parse_error e) { cerr << "Fail. Parse error " << e.what() << endl; delete[] recvbuf;  return -1; }

	//printf("getEventFixture01\r\n");
	root_node = doc.first_node("fixtures_fixture");
	if (!root_node || !root_node->first_node("fixture") || ! root_node->first_node("fixture")->first_node("tournament") || ! root_node->first_node("fixture")->first_node("tournament")->first_node("sport") || !root_node->first_node("fixture")->first_node("tournament")->first_node("category")) {
		delete[] recvbuf;  doc.clear(); //printf("getEventFixture end -1\r\n");  
		return -1;
	}


	//printf("2 getEventFixture b=%d\r\n", b);;
	if (root_node->first_node("fixture")->first_attribute("start_time")) {
		std::strcpy(buf, root_node->first_node("fixture")->first_attribute("start_time")->value());
		sscanf(buf, "%d-%d-%dT%d:%d:%d", &st.wYear, &st.wMonth, &st.wDay, &st.wHour, &st.wMinute, &st.wSecond);
		tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
		tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
		start = mktime(&tm);
		event->start_time = (int)start;
	}

	//printf("getEventFixture02\r\n");
	if (root_node->first_node("fixture")->first_attribute("next_live_time")) {
		std::strcpy(buf, root_node->first_node("fixture")->first_attribute("next_live_time")->value());
		sscanf(buf, "%d-%d-%dT%d:%d:%d", &st.wYear, &st.wMonth, &st.wDay, &st.wHour, &st.wMinute, &st.wSecond);
		tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
		tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
		start = mktime(&tm);
		event->next_live_time = (int)start;
	}
	//printf("3 getEventFixture b=%d\r\n", b);;


	if (event->type_radar == 1 && root_node->first_node("fixture")->first_attribute("scheduled_end")) {
		int x1;
		int x2;
		printf("scheduled_end\r\n");
		strcpy(buf, root_node->first_node("fixture")->first_attribute("scheduled_end")->value());
		st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
		sscanf(buf, "%d-%d-%dT%d:%d:%d+%d:%d", &st.wYear, &st.wMonth, &st.wDay, &st.wHour, &st.wMinute, &st.wSecond, &x1, &x2);

		tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
		tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
		start = mktime(&tm);
		event->start_time = (int)start;
		printf("event->start_time=%d\r\n", event->start_time);
	}

	//printf("getEventFixture03\r\n");

	if (root_node->first_node("fixture")->first_node("tournament") && root_node->first_node("fixture")->first_node("tournament")->first_attribute("id")) {

		if (strncmp(root_node->first_node("fixture")->first_node("tournament")->first_attribute("id")->value(), "sr:tournament:", 14) == 0) {
			event->tournament_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_attribute("id")->value() + 14));
			event->type_radar = 0;
		}
		else
			if (strncmp(root_node->first_node("fixture")->first_node("tournament")->first_attribute("id")->value(), "vf:tournament:", 14) == 0) {
				event->tournament_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_attribute("id")->value() + 14));
				event->type_radar = 3;
			}	
			else
			if (strncmp(root_node->first_node("fixture")->first_node("tournament")->first_attribute("id")->value(), "sr:simple_tournament:", 21) == 0) {
				event->tournament_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_attribute("id")->value() + 21));
				event->type_radar = 2;
			}
			else
					if (strncmp(root_node->first_node("fixture")->first_node("tournament")->first_attribute("id")->value(), "sr:stage:", 9) == 0) {
						event->tournament_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_attribute("id")->value() + 9));
						event->type_radar = 1;

					}
		event->sport_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_node("sport")->first_attribute("id")->value() + 9));
		event->category_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_node("category")->first_attribute("id")->value() + 12));


	}


	string key = event->getTournamentKey();
	
	

	
	if (event->type_radar == 1) {

		if (root_node->first_node("fixture")->first_attribute("type") && root_node->first_node("fixture")->first_attribute("type")->value()[0] == 'p')
			event->parent_id = -1;

		else if (root_node->first_node("fixture")->first_node("parent"))
			event->parent_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("parent")->first_attribute("id")->value() + 9));//sr:stage:
																																				//event->parent_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("parent")->first_attribute("id")->value() + 14));



		if (event->home_name != nullptr) { delete[] event->home_name; event->home_name = nullptr; }
		if (root_node->first_node("fixture")->first_attribute("name")) {
			event->home_name = new char[strlen(root_node->first_node("fixture")->first_attribute("name")->value()) + 1];
			std::strcpy(event->home_name, root_node->first_node("fixture")->first_attribute("name")->value());
		}

		if (event->away_name != nullptr) {
			delete[] event->away_name; event->away_name = nullptr;
		}

		if (event->parent_id != -1 && root_node->first_node("fixture")->first_node("parent") && root_node->first_node("fixture")->first_node("parent")->first_attribute("name")) {
			event->away_name = new char[strlen(root_node->first_node("fixture")->first_node("parent")->first_attribute("name")->value()) + 1];
			std::strcpy(event->away_name, root_node->first_node("fixture")->first_node("parent")->first_attribute("name")->value());
		}

	}


	if (event->type_radar == 0 || event->type_radar == 2 || event->type_radar == 3) {

		//printf("5 getEventFixture b=%d\r\n", b);;
		if (root_node->first_node("fixture")->first_attribute("liveodds")) {
			std::strcpy(buf, root_node->first_node("fixture")->first_attribute("liveodds")->value());
			if (buf[0] == 'b'&& buf[1] == 'o') event->booked = 1;
		}

		if (event->home_name != nullptr) { delete[] event->home_name; event->home_name = nullptr; }
		if (root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->first_attribute("name")) {
			event->home_name = new char[strlen(root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->first_attribute("name")->value()) + 1];
			std::strcpy(event->home_name, root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->first_attribute("name")->value());
		}

		//printf("6 getEventFixture b=%d\r\n", b);;
		if (event->away_name != nullptr) { delete[] event->away_name; event->away_name = nullptr; }
		if (root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("name")) {
			event->away_name = new char[strlen(root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("name")->value()) + 1];
			std::strcpy(event->away_name, root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("name")->value());
		}

		//printf("7 getEventFixture b=%d\r\n", b);;

		//printf("getEventFixture06\r\n");

		event->home_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->first_attribute("id")->value() + 14));
		event->away_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("id")->value() + 14));

		///	sr:competitor: or sr:simpleteam

		//printf("8 getEventFixture b=%d\r\n", b);
		if (event->type_radar == 0 || event->type_radar == 3) {//	sr:competitor:

			if (root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->first_attribute("id")->value()[3] == 'c') {

				if (event->home_id >= MAX_COMPETITORS)  std::printf("ERROR DATA!\r\nevent->home_id out of MAX_COMPETITORS in getEventFixture%d\r\n", event->home_id);
				else {
					if (competitors_id[event->home_id] == nullptr) {
						std::printf("\r\nCompetitors id=%d not found in getEventFixture . Run getCompetitor b=%d\r\n", event->home_id, b);
						competitors_id[event->home_id] = &competitors[*rcompetitors_l];
						competitors[*rcompetitors_l].id = event->home_id;
						if (getCompetitor(competitors_id[event->home_id], b) == -1)
							std::printf(" Error getCompetitor in getEventFixture id competitor=%d \r\n", event->home_id);
						else (*rcompetitors_l)++;
					}
					//else  getCompetitor(competitors_id[event->home_id], b);
				}
			}

			if (root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("id")->value()[3] == 'c') {

				if (event->away_id >= MAX_COMPETITORS)  std::printf("ERROR DATA!\r\nevent->away_id out of MAX_COMPETITORS in getEventFixture%d\r\n", event->away_id);
				else {
					if (competitors_id[event->away_id] == nullptr) {
						std::printf("\r\nCompetitors id=%d not found in getEventFixture . Run getCompetitor b=%d\r\n", event->away_id, b);
						competitors_id[event->home_id] = &competitors[*rcompetitors_l];
						competitors[*rcompetitors_l].id = event->away_id;
						if (getCompetitor(competitors_id[event->home_id], b) == -1)
							std::printf(" Error getCompetitor in getEventFixture id competitor=%d \r\n", event->away_id);
						else (*rcompetitors_l)++;
					}
					//else  getCompetitor(competitors_id[event->away_id], b);
				}

			}

		}

		//printf("9 getEventFixture b=%d\r\n", b);

		//printf("getEventFixture07\r\n");
		if (root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->first_node("reference_ids") && root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->first_attribute("id")->value()[3] == 'c')
			event->home_reference_id = atoi((char*)root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->first_node("reference_ids")->first_node("reference_id")->first_attribute("value")->value()); else {
			event->home_reference_id = event->home_id; //event->home_id = 0;
		}

		if (root_node->first_node("fixture")->first_node("competitors")->last_node("competitor")->first_node("reference_ids") && root_node->first_node("fixture")->first_node("competitors")->last_node("competitor")->first_attribute("id")->value()[3] == 'c')
			event->away_reference_id = atoi((char*)root_node->first_node("fixture")->first_node("competitors")->last_node("competitor")->first_node("reference_ids")->first_node("reference_id")->first_attribute("value")->value()); else {
			event->away_reference_id = event->away_id; //event->away_id = 0;
		}

	}


	
				if ((*rtournaments_id).find(key) == (*rtournaments_id).end()) {
					ret_value = 1;
					(*rtournaments_id)[key] = &tournaments[*rtournaments_l];
					_tournament = &tournaments[*rtournaments_l];
					_tournament->type_radar = event->type_radar;
					_tournament->id = event->tournament_id;
					(*rtournaments_l)++;
					if (getTournament(_tournament, false, b) != -1) ret_fixture = 1;
				}
				if (ret_fixture == 0) {
					_tournament = (*rtournaments_id)[key];
					_tournament->type_radar = event->type_radar;
					_tournament->id = event->tournament_id;
					_tournament->category_id = event->category_id;
					_tournament->sport_id = event->sport_id;

					if (_tournament->name != nullptr) delete[] _tournament->name;
					_tournament->name = new char[strlen(root_node->first_node("fixture")->first_node("tournament")->first_attribute("name")->value()) + 1];
					std::strcpy(_tournament->name, root_node->first_node("fixture")->first_node("tournament")->first_attribute("name")->value());
				}
		

				if (event->category_id >= MAX_CATEGORIES) {
					std::printf("ERROR DATA!\r\ncategory id out of MAX_CATEGORIES in getEventFixture %d\r\n", event->category_id); return -1; }
			else {
				if (categories_id[event->category_id] == nullptr) {
					i = (*rcategories_l); (*rcategories_l)++;
					categories_id[event->category_id] = &categories[i];

				}
				categories_id[event->category_id]->id = event->category_id;
				categories_id[event->category_id]->sport_id = event->sport_id;

				if (categories_id[event->category_id]->name != nullptr) { delete[] categories_id[event->category_id]->name; categories_id[event->category_id]->name = nullptr; }
				categories_id[event->category_id]->name = new char[strlen(root_node->first_node("fixture")->first_node("tournament")->first_node("category")->first_attribute("name")->value()) + 1];
				std::strcpy(categories_id[event->category_id]->name, root_node->first_node("fixture")->first_node("tournament")->first_node("category")->first_attribute("name")->value());

			}



		if (root_node->first_node("fixture")->first_node("season")) {
			if (_tournament->season_name != nullptr) { delete[] _tournament->season_name; _tournament->season_name = nullptr; }
			_tournament->season_name = new char[strlen(root_node->first_node("fixture")->first_node("season")->first_attribute("name")->value()) + 1];
			std::strcpy(_tournament->season_name, root_node->first_node("fixture")->first_node("season")->first_attribute("name")->value());
			
			
			_tournament->season_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("season")->first_attribute("id")->value() + 10));
		if(_tournament->season_id > 0) 	(*rseasons_id)[_tournament->getSeasonKey()] = _tournament;

		

			if (root_node->first_node("fixture")->first_node("season")->first_attribute("start_date")) {
				strcpy(buf, root_node->first_node("fixture")->first_node("season")->first_attribute("start_date")->value());
				st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
				sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

				tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
				tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
				start = mktime(&tm);
				_tournament->start_date = (int)start;

			}

			if (root_node->first_node("fixture")->first_node("season")->first_attribute("end_date")) {
				strcpy(buf, root_node->first_node("fixture")->first_node("season")->first_attribute("end_date")->value());
				st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
				sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

				tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
				tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
				start = mktime(&tm);
				_tournament->end_date = (int)start;

			}



		}

		//printf("12 getEventFixture b=%d\r\n", b);



	


		if (root_node && root_node->first_node("fixture") && root_node->first_node("fixture")->first_node("extra_info"))
			for (xml_node<> * info_node = root_node->first_node("fixture")->first_node("extra_info")->first_node("info"); info_node; info_node = info_node->next_sibling())
			{
				if (info_node->first_attribute("key")->value())

				if (strcmp("period_length", info_node->first_attribute("key")->value()) == 0) event->period_length = atoi(info_node->first_attribute("value")->value());
				if (strcmp("overtime_length", info_node->first_attribute("key")->value()) == 0)	event->overtime_length = atoi(info_node->first_attribute("value")->value());
				if (strcmp("austrian_district", info_node->first_attribute("key")->value()) == 0)	event->austrian_district = atoi(info_node->first_attribute("value")->value());
				if (strcmp("neutral_ground", info_node->first_attribute("key")->value()) == 0 && strcmp("true", info_node->first_attribute("key")->value()) == 0)event->neutral_ground = 1;


			}



		if (root_node && root_node->first_node("fixture") && root_node->first_node("fixture")->first_node("tv_channels")) {
			buffer[0] = 0;
			for (xml_node<> * tv_node = root_node->first_node("fixture")->first_node("tv_channels")->first_node("tv_channel"); tv_node; tv_node = tv_node->next_sibling())
			{
				strcat(buffer, tv_node->first_attribute("name")->value());
				strcat(buffer, "#");

			}
			if (event->tv_channels != nullptr) delete[] event->tv_channels;
			event->tv_channels = new char[strlen(buffer) + 1];
			std::strcpy(event->tv_channels, buffer);
			//printf(event->tv_channels);
		}

		if (event->venue != nullptr) {
			delete[] event->venue; event->venue = nullptr;
		}
		if (root_node && root_node->first_node("fixture") && root_node->first_node("fixture")->first_node("venue")) {
			buffer[0] = 0;
			if (root_node->first_node("fixture")->first_node("venue")->first_attribute("name")) { std::strcpy(buffer, root_node->first_node("fixture")->first_node("venue")->first_attribute("name")->value()); }
			std::strcat(buffer, " / ");


			if (root_node->first_node("fixture")->first_node("venue")->first_attribute("capacity")) {
				std::strcat(buffer, root_node->first_node("fixture")->first_node("venue")->first_attribute("capacity")->value());
				std::strcat(buffer, " / ");
			}
			if (root_node->first_node("fixture")->first_node("venue")->first_attribute("city_name"))
				std::strcat(buffer, root_node->first_node("fixture")->first_node("venue")->first_attribute("city_name")->value());


			event->venue = new char[strlen(buffer) + 1];
			std::strcpy(event->venue, buffer);
			//printf(event->venue);
		}

		if (event->delayed_description != nullptr) {
			delete[] event->delayed_description; event->delayed_description = nullptr;
		}

		//printf("10 getEventFixture b=%d\r\n", b);

		if (root_node && root_node->first_node("fixture") && root_node->first_node("fixture")->first_node("delayed_info")) {
			buffer[0] = 0;
			if (root_node->first_node("fixture")->first_node("delayed_info")->first_attribute("description")) {
				event->delayed_description = new char[strlen(root_node->first_node("fixture")->first_node("delayed_info")->first_attribute("description")->value()) + 1];
				std::strcpy(event->delayed_description, root_node->first_node("fixture")->first_node("delayed_info")->first_attribute("description")->value());
			}
			if (root_node->first_node("fixture")->first_node("delayed_info")->first_attribute("id"))
				event->delayed_id = atoi((char*)root_node->first_node("fixture")->first_node("delayed_info")->first_attribute("id"));

		}

		//printf("11 getEventFixture b=%d\r\n", b);

	





	delete[] recvbuf;

	//if (event->id < MAX_EVENTS)
	
	(*revents_id)[event->getCatKey()] = event; //else std::printf("ERROR DATA!\r\nevent id out of MAX_EVENTS in getEventFixture %d\r\n", event->id);
	

	if (event->bo == 0 && (event->sport_id == 5 || event->sport_id == 19)) getEventSummary(event);
	//printf("15 getEventFixture b=%d\r\n", b);


	if (event->type_radar == 1 && event->tournament_id == 0 && event->parent_id > 0){
		
		char* key = new char[48];
		_itoa(event->parent_id, key, 10);
		if ((*revents_id).find(key) != (*revents_id).end()) {
			event->tournament_id = (*revents_id)[key]->tournament_id;
			event->sport_id = (*revents_id)[key]->sport_id;
			event->category_id = (*revents_id)[key]->category_id;
		}
		delete[] key;
	}

	//printf("16 getEventFixture b=%d\r\n", b);

	if ( event->tournament_id == 0) { printf("event->tournament_id = 0 event->id=%d event->type_radar=%d  timestamp=%d\r\n", event->id, event->type_radar, timestamp() / 100); doc.clear();  return -1; }
	if (event->sport_id == 0) { doc.clear();  return -1; }
	if (event->category_id == 0) { doc.clear(); return -1; }

	
	if (b == false) {

		if (ret_value == 1) {

			saveTournamentToDB(_tournament);
			saveCategoryToDB(categories_id[event->category_id]);

		}
		saveEventToDB(event);

	}

	//printf("17 getEventFixture b=%d\r\n", b);

	doc.clear();
	return ret_value;
}
int get24HoursEventsFixture() {
	char* recvbuf = new char[EXTRA];
	while (httpsRequest("api.betradar.com", "/v1/sports/en/fixtures/changes.xml", recvbuf, 0) == -1) Sleep(1000);
	if (recvbuf[0] == 0) return -1;
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;
	int* event_id;
	int type_radar;
	//using namespace std;
	int i = 0;
	for (i = 0; i < 1000; i++) if (recvbuf[i] == '\r' && recvbuf[i + 1] == '\n' && recvbuf[i + 2] == '\r' && recvbuf[i + 3] == '\n') break;
	doc.parse<0>((char*)((char*)recvbuf + i + 4));
	root_node = doc.first_node("fixture_changes");

	for (xml_node<> * fixture_node = root_node->first_node("fixture_change"); fixture_node; fixture_node = fixture_node->next_sibling())
	{

		AMQP_message[rabbit_index%AMQP_QUEUE];
		std::strcpy(AMQP_message[rabbit_index%AMQP_QUEUE], "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?><fixture_change event_id=\"");
		std::strcat(AMQP_message[rabbit_index%AMQP_QUEUE], fixture_node->first_attribute("sport_event_id")->value());
		std::strcat(AMQP_message[rabbit_index%AMQP_QUEUE], "\"/>");
		rabbit_index++;
	}

	doc.clear();
	delete[] recvbuf;
	return 0;
}
int getEventSummary(Event* event) {
	char* recvbuf = new char[EXTRA];
	char buf[10];
	char buffer[1024];
	//if (event->type_radar == 1) return;
	_itoa(event->id, buf, 10);
	if (event->type_radar == 0) std::strcpy(buffer, "/v1/sports/en/sport_events/sr:match:");
	else std::strcpy(buffer, "/v1/sports/en/sport_events/sr:race_event:");
	std::strcat(buffer, buf);
	std::strcat(buffer, "/summary.xml");
	while (httpsRequest("api.betradar.com", buffer, recvbuf, 0) == -1) Sleep(1000);
	if (recvbuf[0] == 0) return -1;
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;
	int j = 0;
	int recv_length = strlen(recvbuf) - 4; if (recv_length > 1000) recv_length = 1000; for (j = 0; j < recv_length; j++) if (recvbuf[j] == '\r' && recvbuf[j + 1] == '\n' && recvbuf[j + 2] == '\r' && recvbuf[j + 3] == '\n') break; if (j == recv_length || j< 5) { delete[] recvbuf; return -1; }
	try { doc.parse<0>((char*)((char*)recvbuf + j + 4)); }
	catch (parse_error e) { cerr << "Fail. Parse error " << e.what() << endl; delete[] recvbuf; return -1; }

	root_node = doc.first_node("match_summary");
	if (root_node == nullptr) { delete[] recvbuf; doc.clear(); return -1; }

	if (root_node->first_node("sport_event_conditions") && root_node->first_node("sport_event_conditions")->first_attribute("match_mode"))
		event->bo = atoi((char*)((char*)root_node->first_node("sport_event_conditions")->first_attribute("match_mode")->value() + 2));
	delete[] recvbuf;
	doc.clear();
	return 0;

}
int getBetstops() {
	char* recvbuf = new char[EXTRA];
	while (httpsRequest("api.betradar.com", "/v1/descriptions/betstop_reasons.xml", recvbuf, 0) == -1) Sleep(1000);
	if (recvbuf[0] == 0) return -1;
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;

	//using namespace std;
	int j = 0;
	int i = 0;
	int recv_length = strlen(recvbuf) - 4; if (recv_length > 1000) recv_length = 1000; for (j = 0; j < recv_length; j++) if (recvbuf[j] == '\r' && recvbuf[j + 1] == '\n' && recvbuf[j + 2] == '\r' && recvbuf[j + 3] == '\n') break; if (j == recv_length || j< 5) { delete[] recvbuf; return -1; }
	try { doc.parse<0>((char*)((char*)recvbuf + j + 4)); }
	catch (parse_error e) { cerr << "Fail. Parse error " << e.what() << endl; delete[] recvbuf; return -1; }
	//printf(((char*)((char*)recvbuf + j + 4)));
	//printf("\r\n\r\n");
	root_node = doc.first_node("betstop_reasons_descriptions");
	if (root_node == nullptr) { delete[] recvbuf; doc.clear(); return -1; }
	betstops_l = 0;

	if (root_node->first_node("betstop_reason"))
		for (xml_node<> * betstop_reason = root_node->first_node("betstop_reason"); betstop_reason; betstop_reason = betstop_reason->next_sibling())
		{

			if (betstops[i].description != nullptr) {
				delete[] betstops[i].description; betstops[i].description = nullptr;
			}

			if (betstop_reason->first_attribute("description")) {

				betstops[i].description = new char[strlen(betstop_reason->first_attribute("description")->value()) + 1]; std::strcpy(betstops[i].description, betstop_reason->first_attribute("description")->value());
			}
			if (betstop_reason->first_attribute("id")) betstops[i].id = atoi(betstop_reason->first_attribute("id")->value());

			if (betstops[i].id < MAX_BETSTOPS) betstops_id[betstops[i].id] = &betstops[i];

			else   std::printf("ERROR DATA!\r\nbetstop id out of MAX_BETSTOPS in getBetstops %d\r\n", betstops[i].id);
			i++;

		}
	else { delete[] recvbuf; doc.clear(); return -1; }

	betstops_l = i;


	delete[] recvbuf;
	doc.clear();
	return 0;

}
int getVoidreasons() {
	char* recvbuf = new char[EXTRA];
	while (httpsRequest("api.betradar.com", "/v1/descriptions/void_reasons.xml", recvbuf, 0) == -1) Sleep(1000);
	if (recvbuf[0] == 0) return -1;
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;

	//using namespace std;
	int j = 0;
	int i = 0;
	int recv_length = strlen(recvbuf) - 4; if (recv_length > 1000) recv_length = 1000; for (j = 0; j < recv_length; j++) if (recvbuf[j] == '\r' && recvbuf[j + 1] == '\n' && recvbuf[j + 2] == '\r' && recvbuf[j + 3] == '\n') break; if (j == recv_length || j< 5) { delete[] recvbuf; return -1; }
	//printf(((char*)((char*)recvbuf + j + 4)));
	try { doc.parse<0>((char*)((char*)recvbuf + j + 4)); }
	catch (parse_error e) { cerr << "Fail. Parse error " << e.what() << endl; delete[] recvbuf; return -1; }
	//printf(((char*)((char*)recvbuf + j + 4)));
	//printf("\r\n\r\n");
	root_node = doc.first_node("void_reasons_descriptions");
	if (root_node == nullptr) { delete[] recvbuf; doc.clear(); return -1; }
	voidreasons_l = 0;

	if (root_node->first_node("void_reason"))
		for (xml_node<> * void_reason = root_node->first_node("	"); void_reason; void_reason = void_reason->next_sibling())
		{

			if (voidreasons[i].description != nullptr) {
				delete[] voidreasons[i].description; voidreasons[i].description = nullptr;
			}

			if (void_reason->first_attribute("description")) {

				voidreasons[i].description = new char[strlen(void_reason->first_attribute("description")->value()) + 1]; std::strcpy(voidreasons[i].description, void_reason->first_attribute("description")->value());
			}
			if (void_reason->first_attribute("id")) voidreasons[i].id = atoi(void_reason->first_attribute("id")->value());

			if (voidreasons[i].id < MAX_VOIDREASONS) voidreasons_id[voidreasons[i].id] = &voidreasons[i];

			else   std::printf("ERROR DATA!\r\nvoidreason id out of MAX_VOIDREASONS in getVoidreasons %d\r\n", voidreasons[i].id);
			i++;

		}
	else { delete[] recvbuf; doc.clear(); return -1; }

	voidreasons_l = i;


	delete[] recvbuf;
	doc.clear();
	return 0;

}
int getMatchstatus() {
	char* recvbuf = new char[EXTRA];
	while (httpsRequest("api.betradar.com", "/v1/descriptions/en/match_status.xml", recvbuf, 0) == -1) Sleep(1000);
	if (recvbuf[0] == 0) return -1;
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;

	//using namespace std;
	int j = 0;
	int i = 0;
	int recv_length = strlen(recvbuf) - 4; if (recv_length > 1000) recv_length = 1000; for (j = 0; j < recv_length; j++) if (recvbuf[j] == '\r' && recvbuf[j + 1] == '\n' && recvbuf[j + 2] == '\r' && recvbuf[j + 3] == '\n') break; if (j == recv_length || j< 5) { delete[] recvbuf; return -1; }
	//printf(((char*)((char*)recvbuf + j + 4)));
	try { doc.parse<0>((char*)((char*)recvbuf + j + 4)); }
	catch (parse_error e) { cerr << "Fail. Parse error " << e.what() << endl; delete[] recvbuf; return -1; }
	//printf(((char*)((char*)recvbuf + j + 4)));
	//printf("\r\n\r\n");
	root_node = doc.first_node("match_status_descriptions");
	if (root_node == nullptr) { delete[] recvbuf; doc.clear(); return -1; }
	matchstatus_l = 0;

	if (root_node->first_node("match_status"))
		for (xml_node<> * match_status = root_node->first_node("match_status"); match_status; match_status = match_status->next_sibling())
		{

			if (matchstatus[i].description != nullptr) {
				delete[] matchstatus[i].description; matchstatus[i].description = nullptr;
			}

			if (match_status->first_attribute("description")) {

				matchstatus[i].description = new char[strlen(match_status->first_attribute("description")->value()) + 1]; std::strcpy(matchstatus[i].description, match_status->first_attribute("description")->value());
			}
			if (match_status->first_attribute("id")) matchstatus[i].id = atoi(match_status->first_attribute("id")->value());

			if (matchstatus[i].id < MAX_MATCHSTATUS) matchstatus_id[matchstatus[i].id] = &matchstatus[i];

			else   std::printf("ERROR DATA!\r\nmatchstatus id out of MAX_MATCHSTATUS in getMathstatus %d\r\n", matchstatus[i].id);
			i++;

		}
	else { delete[] recvbuf; doc.clear(); return -1; }

	matchstatus_l = i;


	delete[] recvbuf;
	doc.clear();
	return 0;

}
int getTournament(Tournament* tournament, bool extended, bool b) {
	reload_step_1 = 1;
	char buf[MAX_PATH];
	char buffer[1024];
	char* recvbuf = new char[EXTRA];
	Competitor* competitor = nullptr;
	time_t start;
	SYSTEMTIME st;
	struct tm tm;
	std::memset(&st, 0, sizeof(st));
	std::memset(&tm, 0, sizeof(tm));
	Category** categories_id;
	//Tournament** seasons_id;
	//Tournament** simples_id;
	//Tournament** tournaments_id;
	unordered_map<string, Tournament*>* rtournaments_id;
	unordered_map<string, Tournament*>* rseasons_id;
	Competitor** competitors_id;
	Competitor* competitors;
	int* rcategories_l;
	int* rcompetitors_l;



	if (b == true) {
		categories_id = ::bcategories_id;
		rcategories_l = &::bcategories_l;
		//simples_id = ::bsimples_id;
		rseasons_id = &::bseasons_id;
		rtournaments_id = &::btournaments_id;
		competitors_id = ::bcompetitors_id;
		competitors = ::bcompetitors;
		rcompetitors_l = &::bcompetitors_l;
	}
	else {
		categories_id = ::categories_id;
		rcategories_l = &::categories_l;
		//simples_id = ::simples_id;
		rseasons_id = &::seasons_id;
		rtournaments_id = &::tournaments_id;
		competitors_id = ::competitors_id;
		competitors = ::competitors;
		rcompetitors_l = &::competitors_l;

	}


	if (tournament->id == 0 && tournament->season_id == 0) {
		delete[] recvbuf;  return -1;
	};



	if ((tournament->type_radar == 0 || tournament->type_radar == 3) && tournament->id == 0) _itoa(tournament->season_id, buf, 10);
	else  _itoa(tournament->id, buf, 10);


	std::strcpy(buffer, "/v1/sports/en/tournaments/");
	if (tournament->type_radar == 0 && tournament->id > 0) 	std::strcat(buffer, "sr:tournament:"); else
		if (tournament->type_radar == 1) 	std::strcat(buffer, "sr:race_tournament:"); else
			if (tournament->type_radar == 2) 	std::strcat(buffer, "sr:simple_tournament:"); else
				if (tournament->type_radar == 0 && tournament->id == 0) 	std::strcat(buffer, "sr:season:"); else 
					if (tournament->type_radar == 3 && tournament->id > 0) 	std::strcat(buffer, "vf:tournament:"); else 
					if (tournament->type_radar == 3 && tournament->season_id > 0) 	std::strcat(buffer, "vf:season:"); 
				else {
					delete[] recvbuf;  return -1;
				};



				std::strcat(buffer, buf);
				std::strcat(buffer, "/info.xml");
				while (httpsRequest("api.betradar.com", buffer, recvbuf, 0) == -1) Sleep(1000);
				if (recvbuf[0] == 0) return -1;
				using namespace rapidxml;
				xml_document<> doc;
				xml_node<> * root_node;
				int i = 0;
				int j = 0;
				int recv_length = strlen(recvbuf) - 4; if (recv_length > 1000) recv_length = 1000; for (j = 0; j < recv_length; j++) if (recvbuf[j] == '\r' && recvbuf[j + 1] == '\n' && recvbuf[j + 2] == '\r' && recvbuf[j + 3] == '\n') break; if (j == recv_length || j< 5) { delete[] recvbuf; return -1; }
				try { doc.parse<0>((char*)((char*)recvbuf + j + 4)); }
				catch (parse_error e) { cerr << "Fail. Parse error " << e.what() << endl; delete[] recvbuf; return -1; }
				root_node = doc.first_node("tournament_info");

				if (root_node == nullptr) {
					delete[] recvbuf;  doc.clear(); return -1;
				}



				xml_node<> * tournament_node = root_node->first_node("tournament"); if (tournament_node == nullptr) {
					delete[] recvbuf; doc.clear(); return -1;
				}
				if (tournament_node->first_attribute("id")) {
					if (tournament->type_radar == 0)  tournament->id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 14)); else
					if (tournament->type_radar == 1)  tournament->id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 9)); else //sr:stage:// tournament->id = atoi((char*)((chatournament_node->first_attribute("id")->value() + 19));
					if (tournament->type_radar == 2)  tournament->id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 21)); else
					if (tournament->type_radar == 3)  tournament->id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 14));

				}

				if (tournament->name != nullptr) {
					delete[] tournament->name; tournament->name = nullptr;
				}



				if (tournament_node->first_attribute("name")) {

					tournament->name = new char[strlen(tournament_node->first_attribute("name")->value()) + 1]; std::strcpy(tournament->name, tournament_node->first_attribute("name")->value());
				}
				if (tournament_node->first_node("sport")) tournament->sport_id = atoi((char*)((char*)tournament_node->first_node("sport")->first_attribute("id")->value() + 9));
				if (tournament_node->first_node("category")) tournament->category_id = atoi((char*)((char*)tournament_node->first_node("category")->first_attribute("id")->value() + 12));



				if (tournament->category_id < MAX_CATEGORIES) {
					if (tournament->category_id != 0 && categories_id[tournament->category_id] == nullptr) {
						categories_id[tournament->category_id] = &categories[*rcategories_l];
						(*rcategories_l)++;
					}



					categories_id[tournament->category_id]->id = tournament->category_id;
					categories_id[tournament->category_id]->sport_id = tournament->sport_id;
					if (categories_id[tournament->category_id]->name != nullptr) { delete[] categories_id[tournament->category_id]->name; categories_id[tournament->category_id]->name = nullptr; }
					if (tournament_node->first_node("category") && tournament_node->first_node("category")->first_attribute("name")) {
						categories_id[tournament->category_id]->name = new char[strlen(tournament_node->first_node("category")->first_attribute("name")->value()) + 1];
						std::strcpy(categories_id[tournament->category_id]->name, tournament_node->first_node("category")->first_attribute("name")->value());

					}



				}
				else std::printf("ERROR DATA!\r\ncategory id out of MAX_CATEGORIES in getTournament %d\r\n", tournament->category_id);


				if (tournament->season_name != nullptr) {
					delete[] tournament->season_name; tournament->season_name = nullptr;
				}


				int x1;
				int x2;

				if (tournament_node->first_attribute("scheduled")) {

					strcpy(buf, tournament_node->first_attribute("scheduled")->value());
					st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
					sscanf(buf, "%d-%d-%dT%d:%d:%d+%d:%d", &st.wYear, &st.wMonth, &st.wDay, &st.wHour, &st.wMinute, &st.wSecond, &x1, &x2);

					tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
					tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
					start = mktime(&tm);
					tournament->start_date = (int)start;


				}


				if (tournament_node->first_attribute("scheduled_end")) {

					strcpy(buf, tournament_node->first_attribute("scheduled_end")->value());
					st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
					sscanf(buf, "%d-%d-%dT%d:%d:%d+%d:%d", &st.wYear, &st.wMonth, &st.wDay, &st.wHour, &st.wMinute, &st.wSecond, &x1, &x2);

					tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
					tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
					start = mktime(&tm);
					tournament->end_date = (int)start;


				}


				if (tournament_node->first_node("current_season")) {
					tournament->season_name = new char[strlen(tournament_node->first_node("current_season")->first_attribute("name")->value()) + 1];
					std::strcpy(tournament->season_name, tournament_node->first_node("current_season")->first_attribute("name")->value());
					tournament->season_id = atoi((char*)((char*)tournament_node->first_node("current_season")->first_attribute("id")->value() + 10));

					if (tournament_node->first_node("current_season")->first_attribute("start_date")) {
						std::strcpy(buf, tournament_node->first_node("current_season")->first_attribute("start_date")->value());
						st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
						sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

						tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
						tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
						start = mktime(&tm);
						tournament->start_date = (int)start;

					}

					if (tournament_node->first_node("current_season")->first_attribute("end_date")) {
						std::strcpy(buf, tournament_node->first_node("current_season")->first_attribute("end_date")->value());
						st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
						sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

						tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
						tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
						start = mktime(&tm);
						tournament->end_date = (int)start;

					}

				}


				if (tournament_node->first_node("tournament_length")) {

					if (tournament_node->first_node("tournament_length")->first_attribute("start_date")) {
						std::strcpy(buf, tournament_node->first_node("tournament_length")->first_attribute("start_date")->value());
						st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
						sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

						tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
						tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
						start = mktime(&tm);
						tournament->start_date = (int)start;

					}

					if (tournament_node->first_node("tournament_length")->first_attribute("end_date")) {
						std::strcpy(buf, tournament_node->first_node("tournament_length")->first_attribute("end_date")->value());
						st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
						sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

						tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
						tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
						start = mktime(&tm);
						tournament->end_date = (int)start;

					}

				}

				(*rtournaments_id)[tournament->getCatKey()] = tournament;
				if (tournament->season_id > 0) 
				(*rseasons_id)[tournament->getSeasonKey()] = tournament;

		




				if (b == false) {
					saveTournamentToDB(tournament); saveCategoryToDB(categories_id[tournament->category_id]);
				}


				if (root_node->first_node("groups"))
					for (xml_node<> * group_node = root_node->first_node("groups")->first_node("group"); group_node; group_node = group_node->next_sibling())
						for (xml_node<> * competitor_node = group_node->first_node("competitor"); competitor_node; competitor_node = competitor_node->next_sibling())
						{
							int competitor_id = atoi((char*)((char*)competitor_node->first_attribute("id")->value() + 14));


							if (competitor_id >= MAX_COMPETITORS) { std::printf("ERROR DATA!\r\ncompetitors id out of MAX_COMPETITORS in getTournament%d\r\n", competitor_id); continue; }
							else  if (competitors_id[competitor_id] == nullptr) {
								competitors_id[competitor_id] = &competitors[*rcompetitors_l];
								(*rcompetitors_l)++;


							}
							competitor = competitors_id[competitor_id];
							competitor->id = competitor_id;
							competitor->category_id = tournament->category_id;
							competitor->sport_id = tournament->sport_id;


							//else competitors_id[competitor->id][0] = competitor[0];



							if (competitor->name != nullptr) { delete[] competitor->name; competitor->name = nullptr; }
							competitor->name = new char[strlen(competitor_node->first_attribute("name")->value()) + 1];
							std::strcpy(competitor->name, competitor_node->first_attribute("name")->value());


							if (competitor->country_name != nullptr) { delete[] competitor->country_name; competitor->country_name = nullptr; }



							if (competitor_node->first_attribute("country")) {
								//std::printf("vvvvvv\r\n");
								competitor->country_name = new char[strlen(competitor_node->first_attribute("country")->value()) + 1];
								//competitor->country_name = new char[strlen(competitor_node->first_attribute("country")->value()) + 1];
								std::strcpy(competitor->country_name, competitor_node->first_attribute("country")->value());

							}


							//	competitor->id = atoi((char*)((char*)competitor_node->first_attribute("id")->value() + 14));



							if (competitor_node->first_node("reference_ids") && competitor_node->first_node("reference_ids")->first_node("reference_id") && competitor_node->first_node("reference_ids")->first_node("reference_id")->first_attribute("value"))
								competitor->reference_id = atoi(competitor_node->first_node("reference_ids")->first_node("reference_id")->first_attribute("value")->value());


							//std::printf("competitor->reference_id=%d\r\n", competitor->reference_id);



							if (extended == false && b == false) saveCompetitorToDB(competitors_id[competitor->id]);
							if (extended == true) getCompetitor(competitors_id[competitor->id], b);

						}


				delete[] recvbuf;
				doc.clear();
				return 0;
};
int getTournamentTranslate(Tournament* tournament, int l) {
	char buf[MAX_PATH];
	char buffer[1024];
	char* recvbuf = new char[EXTRA];
	if (tournament->id == 0 && tournament->season_id == 0) {
		delete[] recvbuf;  return -1;
	};


	if (tournament->id == 0) _itoa(tournament->season_id, buf, 10);
	else _itoa(tournament->id, buf, 10);

	std::strcpy(buffer, "/v1/sports/");
	std::strcat(buffer, lang[l].c_str());
	std::strcat(buffer, "/tournaments/");
	if (tournament->type_radar == 0 && tournament->id > 0) 	std::strcat(buffer, "sr:tournament:"); else
		if (tournament->type_radar == 1) 	std::strcat(buffer, "sr:race_tournament:"); else
			if (tournament->type_radar == 2) 	std::strcat(buffer, "sr:simple_tournament:"); else
				if (tournament->type_radar == 0 && tournament->id == 0) 	std::strcat(buffer, "sr:season:"); else
					if (tournament->type_radar == 3 && tournament->id > 0) 	std::strcat(buffer, "vf:tournament:");  else
						if (tournament->type_radar == 3 && tournament->season_id > 0) 	std::strcat(buffer, "vf:season:");
				else {
					delete[] recvbuf;  return -1;
				};



				std::strcat(buffer, buf);
				std::strcat(buffer, "/info.xml");
				while (httpsRequest("api.betradar.com", buffer, recvbuf, 0) == -1) Sleep(1000);
				if (recvbuf[0] == 0) return -1;
				using namespace rapidxml;
				xml_document<> doc;
				xml_node<> * root_node;
				int i = 0;
				int j = 0;
				int recv_length = strlen(recvbuf) - 4; if (recv_length > 1000) recv_length = 1000; for (j = 0; j < recv_length; j++) if (recvbuf[j] == '\r' && recvbuf[j + 1] == '\n' && recvbuf[j + 2] == '\r' && recvbuf[j + 3] == '\n') break; if (j == recv_length || j< 5) { delete[] recvbuf; return -1; }
				try { doc.parse<0>((char*)((char*)recvbuf + j + 4)); }
				catch (parse_error e) { cerr << "Fail. Parse error " << e.what() << endl; delete[] recvbuf; return -1; }
				root_node = doc.first_node("tournament_info");

				if (root_node == nullptr) {
					delete[] recvbuf;  doc.clear(); return -1;
				}



				xml_node<> * tournament_node = root_node->first_node("tournament"); if (tournament_node == nullptr) {
					delete[] recvbuf; doc.clear(); return -1;
				}

				int id = 0;
				int simple_id = 0;
				if (tournament_node->first_attribute("id")) {
					if (tournament->type_radar == 0)  id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 14)); else
						if (tournament->type_radar == 1) id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 9)); else
							if (tournament->type_radar == 2)  id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 21)); else
								if (tournament->type_radar == 3)  id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 14));

				};



				if (tournament_node->first_attribute("name")) {
					tournament->translation_name[l] = new char[strlen(tournament_node->first_attribute("name")->value()) + 1]; std::strcpy(tournament->translation_name[l], tournament_node->first_attribute("name")->value());
					if (l > 0 && tournament->name != nullptr && strcmp(tournament->translation_name[l], tournament->name) == 0) {
						delete[] tournament->translation_name[l]; tournament->translation_name[l] = nullptr;
					}
				}



				;


				if (tournament_node->first_node("current_season")) {

					tournament->translation_season_name[l] = new char[strlen(tournament_node->first_node("current_season")->first_attribute("name")->value()) + 1];; std::strcpy(tournament->translation_season_name[l], tournament_node->first_node("current_season")->first_attribute("name")->value());
					if (l > 0 && tournament->season_name != nullptr && strcmp(tournament->translation_season_name[l], tournament->season_name) == 0) {
						delete[] tournament->translation_season_name[l]; tournament->translation_season_name[l] = nullptr;
					}


				}




				delete[] recvbuf;
				doc.clear();
				return 0;

};
void postBooked(int event_id) {
	char buf[10];
	char buffer[4096];
	char* recvbuf = new char[EXTRA];

	_itoa(event_id, buf, 10);
	std::strcpy(buffer, "/v1/liveodds/booking-calendar/events/sr:match:");
	std::strcat(buffer, buf);
	std::strcat(buffer, "/book");
	while (httpsRequest("api.betradar.com", buffer, recvbuf, 1) == -1) Sleep(1000);
	if (recvbuf[0] == 0) return;
	std::printf(recvbuf);
	delete[] recvbuf;
};
char** split(char* string, char* separator) {
	int i = 0;
	int j = 0;
	int k = 0;
	int number = 0;
	char** split_array = nullptr;
	int strlen_sep = strlen(separator);
	int strlen_str = strlen(string);
	if (strlen_str == 0) return nullptr;
	if (strlen_sep == 0) {
		split_array = new char*[1];
		split_array[0] = new char[strlen_str + 1];
		strcpy(split_array[0], string);
		return split_array;
	}

	int* index = new int[strlen_str];
	index[0] = 0;
	for (i = 0; i < strlen_str - strlen_sep; i++) {
		for (j = 0; j < strlen_sep; j++) if (string[i + j] != separator[j]) break;
		if (j < strlen_sep) continue;
		index[k + 1] = i;
		k++;
		i = i + (strlen_sep - 1);

	}

	index[k + 1] = strlen_str;

	if (k == 0) {
		delete[] index;
		split_array = new char*[1];
		split_array[0] = new char[strlen_str + 1];
		strcpy(split_array[0], string);
		return split_array;
	};

	split_array = new char*[k];
	for (i = 0; i < k + 1; i++) {
		if (index[i + 1] == index[i]) split_array[i] = nullptr;
		else {
			split_array[i] = new char[index[i + 1] - index[i] + 1];
			strncpy(split_array[i], (char*)((char*)string + index[i]), index[i + 1] - index[i]);
		}

	}

	return split_array;

};
void replace_competitor(char* & specifier_value) {
	if (specifier_value == nullptr || strlen(specifier_value) < 15) return;
	if (specifier_value[0] == 's' && specifier_value[1] == 'r'&& specifier_value[3] == 'c') {
		int competitor_id = atoi((char*)((char*)specifier_value + 14));

		if (competitor_id >= MAX_COMPETITORS) {
			return;
		}

		if (competitors_id[competitor_id] == nullptr) {
			return;
		}


		strcpy(specifier_value, competitors_id[competitor_id]->name);
		return;
	}

}
void replace_player(char* & specifier_value) {
	if (specifier_value == nullptr || strlen(specifier_value) < 11) return;
	if (specifier_value[0] == 's' && specifier_value[1] == 'r'&& specifier_value[3] == 'p') {
		int player_id = atoi((char*)((char*)specifier_value + 10));

		if (player_id >= MAX_PLAYERS) {
			return;
		}

		if (players_id[player_id] == nullptr) {
			return;
		}

		if (players_id[player_id]->full_name != nullptr)std::strcpy(specifier_value, players_id[player_id]->full_name);
		else std::strcpy(specifier_value, players_id[player_id]->name);
		return;
	}

}
void replace(char* &string, char* sub, char* value, bool b) {
	int i = 0;
	int j = 0;
	int l = 0;
	int k = 0;
	int r = 0;
	int id = 0;
	char buf[4];
	int sub_l;
	char* retValue = nullptr;
	int index1[20];
	int index2[20];
	int index3[20];
	char index_char1[20];
	char index_char2[20];
	int value_l = 0;
	int p = 0;

	Player** players_id;
	Player* players;
	Competitor** competitors_id;
	Competitor* competitors;
	int* rcompetitors_l;
	int* rplayers_l;


	if (b == true) {
		competitors_id = ::bcompetitors_id;
		competitors = ::bcompetitors;
		rplayers_l = &::bplayers_l;
		rcompetitors_l = &::bcompetitors_l;
		players_id = ::bplayers_id;
		players = ::bplayers;

	}
	else {
		competitors_id = ::competitors_id;
		competitors = ::competitors;
		rplayers_l = &::players_l;
		players_id = ::players_id;
		rcompetitors_l = &::competitors_l;
		players = ::players;

	}





	if (string == nullptr) return;
	if (value != nullptr) value_l = strlen(value);
	int string_l = strlen(string);
	if (string_l == 0) return;
	l = 0;
	sub_l = strlen(sub);
	if (sub_l == 0 || sub_l > string_l) return;

	for (i = 1; i < string_l - sub_l + 1; i++) {
		if (string[i - 1] != '{') continue;
		if (string[i] == '!' && string[i + 1] == '(') i = i + 2;
		else  if (string[i] == '!' || string[i] == '+' || string[i] == '-' || string[i] == '(' || string[i] == '%') i++;



		for (j = 0; j < sub_l; j++) if (string[j + i] != sub[j]) break;
		//printf((char*)((char*)string + i));

		if (j == sub_l) {

			index_char1[l] = string[i - 1];
			index_char2[l] = string[i + j];
			if (string[i + j] == '}') {
				if (string[i - 1] == '!' || string[i - 1] == '+' || string[i - 1] == '-' || string[i - 1] == '%') index1[l] = i - 2; else index1[l] = i - 1;
				index2[l] = i + sub_l + 1; l++; i = i + sub_l + 1;
			}
			else if (string[i + j + 2] == ')' && index_char2[l] == '+' || index_char2[l] == '-') {
				index3[l] = (int)string[i + j + 1] - 48;
				if (string[i - 2] == '!') index1[l] = i - 3; else index1[l] = i - 2; index2[l] = i + sub_l + 4; l++;
				i = i + sub_l + 4;

			}



		}

	}



	if (l == 0) return;
	index1[l] = -1;
	retValue = new char[string_l + 150 + l*(value_l - sub_l)];
	retValue[0] = 0;

	for (i = 0; i < 20; i++) {
		if (index1[i] == -1) break;
		if (i == 0)  strncat(retValue, string, index1[i]);
		else strncat(retValue, (char*)((char*)string + index2[i - 1]), index1[i] - index2[i - 1]);
		if (value_l > 0) {
			if ((index_char1[i] == '-' || index_char1[i] == '+') && value[0] != '-' && atof(value) == 0) {
				std::strcat(retValue, value);

			}
			else  if (index_char1[i] == '-' && value[0] == '-') {
				std::strcat(retValue, "+");  std::strcat(retValue, (char*)((char*)value + 1));
			}
			else if (index_char1[i] == '-' && value[0] != '-') {
				std::strcat(retValue, "-");  std::strcat(retValue, value);
			}
			else if (index_char1[i] == '+' && value[0] != '-') {
				std::strcat(retValue, "+");  std::strcat(retValue, value);
			}
			else if (index_char1[i] == '%' && value[0] == 's' && value[1] == 'r'&& value[3] == 'p') {

				id = atoi((char*)((char*)value + 10));



				if (id >= MAX_PLAYERS) {
					std::printf("\r\n ERROR in replace. player_id out of MAX_PLAYERS. player_id=%d\r\n", id);
					return;

				}
				if (players_id[id] == nullptr) {
					std::printf("Player1  not found in replace. player_id=%d . getPlayer\r\n", id);
					players[*rplayers_l].id = id; if (getPlayer(&players[*rplayers_l], b) == -1)
					{
						std::printf("error player id=%d  not found \r\n ", id); return;

					}
					else  (*rplayers_l)++;
				}

				if (players_id[id] != nullptr) {
					std::strcat(retValue, players_id[id]->name);

				}
				else return;




			}


			else if (index_char1[i] == '%' && value[0] == 's' && value[1] == 'r'&& value[3] == 'c') {
				id = atoi((char*)((char*)value + 14));

				if (id >= MAX_COMPETITORS) {
					std::printf("\r\n ERROR in replace. competitor_id out of MAX_COMPETITORS. competitor_id=%d\r\n", id);
					return;
				}


				if (competitors_id[id] == nullptr) {
					std::printf("\r\nCompetitors id=%d not found in replace . Run getCompetitor\r\n", id);
					competitors[*rcompetitors_l].id = id;
					if (getCompetitor(&competitors[*rcompetitors_l], b) == -1) {
						std::printf(" Error getCompetitor in replace.  id competitor=%d \r\n", id);
						return;
					}
					else (*rcompetitors_l)++;
				}



				if (competitors_id[id] != nullptr) std::strcat(retValue, competitors_id[id]->name);
				else return;




			}
			else if (index_char2[i] == '+') {
				r = atoi(value) + index3[i];
				_itoa(r, buf, 10);
				std::strcat(retValue, buf);
			}
			else if (index_char2[i] == '-') {
				r = atoi(value) - index3[i];
				_itoa(r, buf, 10);
				std::strcat(retValue, buf);
			}

			else {


				std::strcat(retValue, value);
			}


		}



	}
	std::strcat(retValue, (char*)((char*)string + index2[i - 1]));

	//printf(retValue);
	//std::strcpy(string, retValue);
	//printf(string);

	delete[] string;
	string = retValue;
}
void replace_substr(char* &string, char* sub, char* value) {
	int i = 0;
	int j = 0;
	int l = 0;
	int k = 0;
	int r = 0;
	int id = 0;
	char buf[4];
	int sub_l;
	char* retValue = nullptr;
	int index1[20];
	int index2[20];
	int value_l = 0;
	int p = 0;

	if (string == nullptr) return;
	if (value != nullptr) value_l = strlen(value);
	int string_l = strlen(string);
	if (string_l == 0) return;
	l = 0;
	sub_l = strlen(sub);
	if (sub_l == 0 || sub_l > string_l) return;

	for (i = 0; i < string_l - sub_l + 1; i++) {
		for (j = 0; j < sub_l; j++) if (string[j + i] != sub[j]) break;
		if (j == sub_l) {
			index1[l] = i;
			index2[l] = i + sub_l; l++; i = i + sub_l;
		}

	}


	if (l == 0) return;
	index1[l] = -1;
	retValue = new char[string_l + 1 + l*(value_l - sub_l)];
	retValue[0] = 0;

	for (i = 0; i < 20; i++) {
		if (index1[i] == -1) break;
		if (i == 0)  strncat(retValue, string, index1[i]);
		else strncat(retValue, (char*)((char*)string + index2[i - 1]), index1[i] - index2[i - 1]);
		if (value_l > 0) std::strcat(retValue, value);
	}
	std::strcat(retValue, (char*)((char*)string + index2[i - 1]));

	//printf(retValue);
	//std::strcpy(string, retValue);
	//printf(string);

	delete[] string;
	string = retValue;
}
void saveEventToDB(Event* event, bool translate) {
	if (WRITE_NEW_DATA_TO_MONGO && REPLAY == 0) {
		auto coll = db["events"];
		mongocxx::options::update* update = new mongocxx::options::update();
		update->upsert(true);

		try {

			coll.update_one(bsoncxx::builder::stream::document{} << "_id" << event->id << bsoncxx::builder::stream::finalize,
				bsoncxx::builder::stream::document {} << "$set" << buildEventDoc(event, translate) << bsoncxx::builder::stream::finalize, *update);
		}


		catch (const mongocxx::exception& e) {
			std::cout << "An exception occurred in update_one event: " << e.what() << std::endl;
		}

		delete update;


		// return;
	}


};
void loadEventsFromDB() {
	using namespace bsoncxx::builder;
	auto coll = db["events"];
	auto query_doc = stream::document{}
		<< "start_time" << stream::open_document << "$gte" << (time(nullptr) - 20 * 24 * 60 * 60)
		<< stream::close_document
		<< stream::finalize;
	mongocxx::cursor cursor = coll.find(query_doc.view());   // query is db.events.find({ start_time: {$gte: ...}})
	int i = 0;
	events_l = bevents_l = 0;
	for (auto doc : cursor) {
		// std::cout << bsoncxx::to_json(doc) << "\n";

		// int fields
		events[i].id = doc["_id"].get_int32();
		events[i].type_radar = doc["type_radar"].get_int32();
		events[i].sport_id = doc["sport_id"].get_int32();
		events[i].category_id = doc["category_id"].get_int32();
		if (events[i].type_radar == 2) {
			events[i].simple_id = doc["simple_id"].get_int32();
		}
		else {
			events[i].tournament_id = doc["tournament_id"].get_int32();
		}
		events[i].home_id = doc["home_id"].get_int32();
		events[i].home_reference_id = doc["home_reference_id"].get_int32();
		events[i].away_id = doc["away_id"].get_int32();
		events[i].away_reference_id = doc["away_reference_id"].get_int32();
		events[i].winner_id = doc["winner_id"].get_int32();
		events[i].bo = doc["bo"].get_int32();
		events[i].parent_id = doc["parent_id"].get_int32();
		events[i].start_time = doc["start_time"].get_int32();
		events[i].period_length = doc["period_length"].get_int32();
		events[i].overtime_length = doc["overtime_length"].get_int32();
		events[i].status = doc["status"].get_int32();
		events[i].timestamp = doc["timestamp"].get_int32();
		events[i].neutral_ground = doc["neutral_ground"].get_int32();
		events[i].austrian_district = doc["austrian_district"].get_int32();
		events[i].booked = doc["booked"].get_int32();
		events[i].delayed_id = doc["delayed_id"].get_int32();
		events[i].current_server = doc["current_server"].get_int32();
		events[i].next_live_time = doc["next_live_time"].get_int32();

		// string fields
		mongo_str_to_buffer(doc["home_name"], events[i].home_name);
		mongo_str_to_buffer(doc["away_name"], events[i].away_name);
		mongo_str_to_buffer(doc["delayed_description"], events[i].delayed_description);
		mongo_str_to_buffer(doc["venue"], events[i].venue);
		mongo_str_to_buffer(doc["tv_channels"], events[i].tv_channels);

		if (!doc["translations"]) {}
		else
			for (int l = 0; l < events[i].translation_num; l++) if (!doc["translations"][lang[l]]) {}
			else
			{
				if (!doc["translations"][lang[l]]["home_name"]) {}
				else mongo_str_to_buffer(doc["translations"][lang[l]]["home_name"], events[i].translation_home_name[l]);
				if (!doc["translations"][lang[l]]["away_name"]) {}
				else mongo_str_to_buffer(doc["translations"][lang[l]]["away_name"], events[i].translation_away_name[l]);
				if (!doc["translations"][lang[l]]["tv_channels"]) {}
				else mongo_str_to_buffer(doc["translations"][lang[l]]["tv_channels"], events[i].translation_tv_channels[l]);
			}

		bevents[i] = events[i];
		if (!(events[i].type_radar == 2 && events[i].simple_id == 0)) {
			events_id[events[i].getCatKey()] = &events[i];
			bevents_id[bevents[i].getCatKey()] = &bevents[i];
			i++;
		}

	}

	events_l = bevents_l = i;

	/*
	for (int i = 0; i < events_l; i++) {
	cout << events[i].id << ";" << events[i].home_name << "-" << events[i].away_name << ";"
	<< endl;
	}
	*/
	printf("Events loaded from Mongo succes. Number of loaded events: %d\r\n", events_l);
	return;


};
void processLoadedMarkets() {
	int j = 0;
	for (int k = 0; k < markets_l; k++) {
		if (markets[k].variant > -1 && markets_id[markets[k].id] == nullptr) {
			markets_id[markets[k].id] = new Market*[MAX_MARKETS_IN];
			bmarkets_id[bmarkets[k].id] = new Market*[MAX_MARKETS_IN];
			for (int l = 0; l < MAX_MARKETS_IN; l++)  markets_id[markets[k].id][l] = bmarkets_id[bmarkets[k].id][l] = nullptr;


		}

		if (markets[k].variant > -1 && markets[k].variable_text == nullptr) {
			markets_id[markets[k].id][0] = &markets[k]; bmarkets_id[bmarkets[k].id][0] = &bmarkets[k];
		}

		if (markets[k].variant > -1 && markets[k].variable_text != nullptr) {
			for (j = 1; j < max_markets_in[markets[k].id]; j++) {
				if (markets_id[markets[k].id][j] != nullptr && std::strcmp(markets[k].variable_text, markets_id[markets[k].id][j]->variable_text) == 0) break;
				if (markets_id[markets[k].id][j] == nullptr) {
					markets_id[markets[k].id][j] = &markets[k]; bmarkets_id[bmarkets[k].id][j] = &bmarkets[k]; break;
				}
			}



			if (j == max_markets_in[markets[k].id]) {
				markets_id[markets[k].id][j] = &markets[k]; max_markets_in[markets[k].id]++;
				bmarkets_id[bmarkets[k].id][j] = &bmarkets[k]; bmax_markets_in[bmarkets[k].id]++;
			}
		}


		if (markets[k].variant == -1 && markets_id[markets[k].id] == nullptr) {
			markets_id[markets[k].id] = new Market*[1]; markets_id[markets[k].id][0] = &markets[k];

			bmarkets_id[bmarkets[k].id] = new Market*[1]; bmarkets_id[bmarkets[k].id][0] = &bmarkets[k];
		}

		if (markets[k].id == 219) markets[k].line_type = 1;// (Winner(incl.overtime)
		if (markets[k].id == 16) markets[k].line_type = 3;// (Handicap)	
		if (markets[k].id == 1) markets[k].line_type = 2;// (1x2)	
		if (markets[k].id == 186) markets[k].line_type = 1; //Tennis, Athletics, Aussie Rules, Badminton, Beach Volley, Bowls, Boxing, Counter - Strike, Curling, Darts, Dota 2, ESport Call of Duty, ESport Overwatch, League of Legends, MMA, Snooker, Squash, StarCraft, Table Tennis, Volleyball
		if (markets[k].id == 610) markets[k].line_type = 2;// (1x2)	Amercian Football
		if (markets[k].id == 406) markets[k].line_type = 1;//Winner (incl. overtime and penalties) Handball,Ice Hockey
		if (markets[k].id == 2) markets[k].line_type = 1; //To qualify Soccer
		if (markets[k].id == 60) markets[k].line_type = 5;// 1st half - 1x2
		if (markets[k].id == 83) markets[k].line_type = 5;// 2nd half - 1x2
		if (markets[k].id == 113) markets[k].line_type = 2;// Overtime - 1x2
		if (markets[k].id == 119) markets[k].line_type = 5;//Overtime 1st half - 1x2
														   //if (markets[k].id == 120) markets[k].line_type = 7;//Overtime 1st half - handicap
		if (markets[k].id == 123) markets[k].line_type = 7;//Penalty shootout - winner
		if (markets[k].id == 711) markets[k].line_type = 5;//{!inningnr} innings - 1x2 cricket
		if (markets[k].id == 645) markets[k].line_type = 5;//{!inningnr} innings over {overnr} - 1x2
		if (markets[k].id == 611) markets[k].line_type = 5;//{!quarternr} quarter - 1x2 (incl. overtime) Amercan Football valid for quartner=4
		if (markets[k].id == 223) markets[k].line_type = 3;//Handicap (incl. overtime) Basketball,American Football
		if (markets[k].id == 410) markets[k].line_type = 3;//Handicap (incl. overtime and penalties) Ice Hockey
		if (markets[k].id == 66) markets[k].line_type = 7;//1st half - handicap
		if (markets[k].id == 88) markets[k].line_type = 7;//2nd half - handicap
		if (markets[k].id == 460) markets[k].line_type = 7;//{!periodnr} period - handicap Ice Hockey
		if (markets[k].id == 303) markets[k].line_type = 7;//{!quarternr} quarter - handicap Basketball,American Football,Aussie Rules
		if (markets[k].id == 203) markets[k].line_type = 7;//{!setnr} set - game handicap Tennis

		if (markets[k].id == 527) markets[k].line_type = 7;//{!setnr} set - handicap  Bowls
		if (markets[k].id == 314) markets[k].line_type = 4;//Total sets - Bowls Darts
		if (markets[k].id == 315) markets[k].line_type = 5;//{!setnr} set - 1x2 Bowls
		if (markets[k].id == 188) markets[k].line_type = 3;//Set handicap Bowls
		if (markets[k].id == 493) markets[k].line_type = 3;//Frame handicap Snooker
		if (markets[k].id == 494) markets[k].line_type = 4;// Total frames  Snooker
		if (markets[k].id == 499) markets[k].line_type = 6;//{!framenr} frame - winner Snooker

		if (markets[k].id == 204) markets[k].line_type = 8;//{!setnr} set - total games  Tennis
		if (markets[k].id == 746) markets[k].line_type = 7;//{!inningnr} inning - handicap Baseball
		if (markets[k].id == 117) markets[k].line_type = 3;//Overtime - handicap Soccer,Handball
		if (markets[k].id == 120) markets[k].line_type = 7;//Overtime 1st half - handicap Soccer
		if (markets[k].id == 18) markets[k].line_type = 4;//Total Soccer,Futsal,Handball,Ice Hockey,Rugby,Soccer Mythical
		if (markets[k].id == 238) markets[k].line_type = 4;//Total points Badminton,Beach Volley,Squash,Table Tennis,Volleyball
		if (markets[k].id == 412) markets[k].line_type = 4;//Total (incl. overtime and penalties) Ice Hockey
		if (markets[k].id == 68) markets[k].line_type = 8;//1st half - total Soccer,Basketball,American Football,Futsal,Handball,Rugby,Soccer Mythical
		if (markets[k].id == 90) markets[k].line_type = 8;//2nd half - total Soccer,Soccer Mythical
		if (markets[k].id == 446) markets[k].line_type = 8;//{!periodnr} period - total Ice Hockey
		if (markets[k].id == 236) markets[k].line_type = 8;//{!quarternr} quarter - total Basketball,American Football,Aussie Rules
		if (markets[k].id == 310) markets[k].line_type = 8;//{!setnr} set - total points Beach Volley,Volleyball
		if (markets[k].id == 528) markets[k].line_type = 8;//{!setnr} set - total Bowls
		if (markets[k].id == 288) markets[k].line_type = 8;//{!inningnr} inning - total Baseball
		if (markets[k].id == 116) markets[k].line_type = 4;//Overtime - total Soccer,Futsal,Handball,Ice Hockey
		if (markets[k].id == 358) markets[k].line_type = 8;//1st over - total Cricket
		if (markets[k].id == 395) markets[k].line_type = 6;//{!mapnr} map - winner Dota 2,League of Legends,StarCraft
		if (markets[k].id == 330) markets[k].line_type = 6;//{!mapnr} map - winner (incl. overtime) Counter-Strike
		if (markets[k].id == 334) markets[k].line_type = 5;//{!mapnr} map - 1x2 Counter-Strike


		if (markets[k].id == 340) markets[k].line_type = 1;//Winner (incl. super over) Cricket
		if (markets[k].id == 251) markets[k].line_type = 1;// Winner (incl. extra innings) Baseball
														   //if (markets[k].id == 426) markets[k].line_type = 5;//{!periodnr} period 1x2 & winner (incl. overtime and penalties) Ice Hockey
														   //if (markets[k].id == 429) markets[k].line_type = 5;//{!periodnr} period 1x2 & 1x2 Ice Hockey
		if (markets[k].id == 443) markets[k].line_type = 5;//{!periodnr} period 1x2  Ice Hockey
		if (markets[k].id == 225) markets[k].line_type = 4;// Total (incl. overtime) Basketball

		if (markets[k].id == 501) markets[k].line_type = 8;//{!framenr} frame - total points Snooker
		if (markets[k].id == 500) markets[k].line_type = 7;//{!framenr} frame - handicap points Snooker
		if (markets[k].id == 527) markets[k].line_type = 7;//{!setnr} set - handicap Bowls
		if (markets[k].id == 226) markets[k].line_type = 4;//US total (incl. overtime) Basketball,American Football
		if (markets[k].id == 315) markets[k].line_type = 5;//{!setnr} set - 1x2 Bowls
		if (markets[k].id == 287) markets[k].line_type = 5;//{!inningnr} inning - 1x2 Baseball
		if (markets[k].id == 245) markets[k].line_type = 6;//{!gamenr} game - winner Badminton,Squash,Table Tennis
		if (markets[k].id == 235) markets[k].line_type = 5;//{!quarternr} quarter - 1x2 Basketball,American Football,Aussie Rules
														   //if (markets[k].id == 445) markets[k].line_type = 7;//{!periodnr} period - handicap {hcp} Ice Hockey
														   //if (markets[k].id == 446) markets[k].line_type = 8;//{!periodnr} period - total Ice Hockey
		if (markets[k].id == 246) markets[k].line_type = 7;//{!gamenr} game - point handicap Badminton,Squash,Table Tennis
		if (markets[k].id == 247) markets[k].line_type = 8;// {!gamenr} game - total points Badminton,Squash,Table Tennis
		if (markets[k].id == 460) markets[k].line_type = 7;//{!periodnr} period - handicap Ice Hockey
														   //if (markets[k].id == 254) markets[k].line_type = 3;//Handicap {hcp} (incl. extra innings) Baseball
		if (markets[k].id == 256) markets[k].line_type = 3;//Handicap (incl. extra innings) Baseball
		if (markets[k].id == 258) markets[k].line_type = 4;//Total (incl. extra innings) Baseball
		if (markets[k].id == 371) markets[k].line_type = 7;// {!setnr} set - leg handicap Darts
		if (markets[k].id == 372) markets[k].line_type = 8;// {!setnr} set - total legs Darts	
		if (markets[k].id == 605) markets[k].line_type = 8;//{!inningnr} innings - total Cricket

		if (markets[k].id == 189) markets[k].line_type = 4;//Total games Tennis
		if (markets[k].id == 237) markets[k].line_type = 3;//Point handicap Badminton,Beach Volley,Squash,Table Tennis,Volleyball
		if (markets[k].id == 538) markets[k].line_type = 2;//Head2head (1x2) Golf,Motorsport
		if (markets[k].id == 8) markets[k].line_type = 9;//{!goalnr} goal Soccer,Futsal,Ice Hockey
		if (markets[k].id == 62) markets[k].line_type = 10;//1st half - {!goalnr} goal Soccer,Futsal
		if (markets[k].id == 84) markets[k].line_type = 10;//2nd half - {!goalnr} goal Soccer,Futsal
		if (markets[k].id == 444) markets[k].line_type = 10;//{!periodnr} period - {!goalnr} goal Ice Hockey
															//if (markets[k].id == 245) markets[k].line_type = 10;//{!gamenr} game - winner Badminton,Squash,Table Tennis
		if (markets[k].id == 210) markets[k].line_type = 10;//{!setnr} set game{ gamenr } -winner Tennis
		if (markets[k].id == 125) markets[k].line_type = 10;//Penalty shootout - {!goalnr} goal Soccer,Futsal,Ice Hockey
		if (markets[k].id == 115) markets[k].line_type = 9;//Overtime - {!goalnr} goal Soccer,Futsal,Ice Hockey
		if (markets[k].id == 202) markets[k].line_type = 6;// {!setnr} set - winner	Tennis Beach Volley,Darts,Volleyball
		if (markets[k].id == 309) markets[k].line_type = 7;//{!setnr} set - point handicap Beach Volley,Volleyball
		if (markets[k].id == 29) markets[k].line_type = 11;//Both teams to score
		if (markets[k].id == 196) markets[k].line_type = 13;//Exact sets Tennis,Beach Volley,Volleyball
	}
}
void saveMarketToDB(Market* market, bool translate) {

	if (WRITE_NEW_DATA_TO_MONGO && REPLAY == 0) {
		auto coll = db["markets"];
		//printf("WRITE_NEW_DATA_TO_MONGO=");
		//coll.insert_one(buildMarketDoc(market));

		string variable_text = market->variable_text == nullptr ? "" : market->variable_text;


		mongocxx::options::update* update = new mongocxx::options::update();
		update->upsert(true);

		try {
			//if (market->variant > -1 && market->variable_text != nullptr) 
			coll.update_one(bsoncxx::builder::stream::document{} << "market_id" << market->id << "variable_text" << variable_text << bsoncxx::builder::stream::finalize,
				bsoncxx::builder::stream::document{} << "$set" << buildMarketDoc(market, translate) << bsoncxx::builder::stream::finalize, *update);

			//else coll.update_one(bsoncxx::builder::stream::document{} << "market_id" << market->id << bsoncxx::builder::stream::finalize,
			//bsoncxx::builder::stream::document {} << "$set" << buildMarketDoc(market) << bsoncxx::builder::stream::finalize, *update);
		}


		catch (const mongocxx::exception& e) {
			std::cout << "An exception occurred in update_one market: " << e.what() << std::endl;
		}

		delete update;



		return;
	}

};


void deleteTournamentFromDB(Tournament* tournament) {

	if (WRITE_NEW_DATA_TO_MONGO && REPLAY == 0) {
		auto coll = db["tournaments"];


		try {
			//if (market->variant > -1 && market->variable_text != nullptr) 
			coll.delete_one(bsoncxx::builder::stream::document{} << "tournament_id" << tournament->id << "simple_id" << tournament->simple_id << bsoncxx::builder::stream::finalize);

			//else coll.update_one(bsoncxx::builder::stream::document{} << "market_id" << market->id << bsoncxx::builder::stream::finalize,
			//bsoncxx::builder::stream::document {} << "$set" << buildMarketDoc(market) << bsoncxx::builder::stream::finalize, *update);
		}


		catch (const mongocxx::exception& e) {
			std::cout << "An exception occurred in update_one market: " << e.what() << std::endl;
		}


		return;
	}



};


void deleteMarketFromDB(Market* market) {

	if (WRITE_NEW_DATA_TO_MONGO && REPLAY == 0) {
		auto coll = db["markets"];
		//printf("WRITE_NEW_DATA_TO_MONGO=");
		//coll.insert_one(buildMarketDoc(market));

		string variable_text = market->variable_text == nullptr ? "" : market->variable_text;


		try {
			//if (market->variant > -1 && market->variable_text != nullptr) 
			coll.delete_one(bsoncxx::builder::stream::document{} << "market_id" << market->id << "variable_text" << variable_text << bsoncxx::builder::stream::finalize);

			//else coll.update_one(bsoncxx::builder::stream::document{} << "market_id" << market->id << bsoncxx::builder::stream::finalize,
			//bsoncxx::builder::stream::document {} << "$set" << buildMarketDoc(market) << bsoncxx::builder::stream::finalize, *update);
		}


		catch (const mongocxx::exception& e) {
			std::cout << "An exception occurred in update_one market: " << e.what() << std::endl;
		}


		return;
	}

};
void loadMarketsFromDB() {
	auto coll = db["markets"];
	mongocxx::cursor cursor = coll.find(bsoncxx::builder::stream::document{} << bsoncxx::builder::stream::finalize);  // get all docs
	int i = 0;
	markets_l = bmarkets_l = 0;
	int outcome_index, specifier_index;
	for (auto doc : cursor) {
		// std::cout << bsoncxx::to_json(doc) << "\n";
		markets[i].id = doc["market_id"].get_int32();
		markets[i].type = doc["type"].get_int32();
		markets[i].variant = doc["variant"].get_int32();
		mongo_str_to_buffer(doc["name"], markets[i].name);
		// optional values
		// if (doc["variable_text"] == false) {
		mongo_str_to_buffer(doc["variable_text"], markets[i].variable_text);
		
		// outcomes array
		bsoncxx::document::element outcomes_elem = doc["outcomes"];
		bsoncxx::array::view outcomes{ outcomes_elem.get_array().value };

		if (outcomes.empty()) {
			markets[i].outcome_id = nullptr;
			markets[i].outcome_name = nullptr;
		}
		else {
			auto num_outcomes = std::distance(std::begin(outcomes), std::end(outcomes));
			markets[i].outcome_number = num_outcomes;
			markets[i].outcome_id = new int[markets[i].outcome_number];
			markets[i].outcome_name = new char*[markets[i].outcome_number];
			outcome_index = 0;
			for (auto elt : outcomes) {
				bsoncxx::document::view subdoc = elt.get_document().value;
				markets[i].outcome_id[outcome_index] = subdoc["id"].get_int32();
				markets[i].outcome_name[outcome_index] = nullptr;
				mongo_str_to_buffer(subdoc["name"], markets[i].outcome_name[outcome_index]);
				outcome_index++;
			}
		}



		if (!doc["translations"]) {}
		else
			for (int l = 0; l < markets[i].translation_num; l++) if (!doc["translations"][lang[l]]) {}
			else
			{
				if (!doc["translations"][lang[l]]["name"]) {}
				else mongo_str_to_buffer(doc["translations"][lang[l]]["name"], markets[i].translation_name[l]);
				if (!doc["translations"][lang[l]]["outcomes_name"]) {}
				else {
					int j = 0;
					markets[i].translation_outcome_name[l] = new char*[markets[i].outcome_number];
					bsoncxx::array::view outcomes_name{ doc["translations"][lang[l]]["outcomes_name"].get_array().value };
					for (auto elt : outcomes_name) {
						markets[i].translation_outcome_name[l][j] = nullptr;
						mongo_str_to_buffer(elt, markets[i].translation_outcome_name[l][j]); j++;
					}
					
				}

			}


		
		// specifiers array
		bsoncxx::document::element specifiers_elem = doc["specifiers"];
		bsoncxx::array::view specifiers{ specifiers_elem.get_array().value };
		

		if (specifiers.empty()) {
			markets[i].specifier_type = nullptr;
			markets[i].specifier_name = nullptr;
			markets[i].specifier_description = nullptr;
		}
		else {
			auto num_specifiers = std::distance(std::begin(specifiers), std::end(specifiers));
			markets[i].specifier_number = num_specifiers;
			markets[i].specifier_type = new int[markets[i].specifier_number];
			markets[i].specifier_name = new char*[markets[i].specifier_number];
			markets[i].specifier_description = new char*[markets[i].specifier_number];
			specifier_index = 0;
			for (auto elt : specifiers) {
				bsoncxx::document::view subdoc = elt.get_document().value;
				// std::cout << bsoncxx::to_json(subdoc) << "\n";
				markets[i].specifier_type[specifier_index] = subdoc["type"].get_int32();
				markets[i].specifier_name[specifier_index] = nullptr;
				mongo_str_to_buffer(subdoc["name"], markets[i].specifier_name[specifier_index]);
		
				if (subdoc["description"]) {
					markets[i].specifier_description[specifier_index] = nullptr;
					mongo_str_to_buffer(subdoc["description"], markets[i].specifier_description[specifier_index]);
				}
				else {
					markets[i].specifier_description[specifier_index] = nullptr;
				}
				specifier_index++;
			}
		}

		bmarkets[i] = markets[i];
		i++;


	}

	markets_l = bmarkets_l = i;
	// to test if loading was succesful. may be deleted in the future.
	/*
	for (int i = 0; i < markets_l; i++) {
	cout << markets[i].id << ";" << markets[i].name << ";" << markets[i].outcome_number << ";" << markets[i].specifier_number << endl;
	for (int k = 0; k < markets[i].outcome_number; k++) {
	cout << "\t" << markets[i].outcome_id[k] << ": " << markets[i].outcome_name[k] << endl;
	}
	for (int k = 0; k < markets[i].specifier_number; k++) {
	cout << "\t\t" << markets[i].specifier_name[k] << ": " << markets[i].specifier_type[k];
	if (markets[i].specifier_description[k] != nullptr) {
	cout << " :: " << markets[i].specifier_description[k];
	}
	cout << endl;
	}
	}
	*/
	processLoadedMarkets();
	printf("Markets loaded from Mongo succes. Number of loaded markets: %d\r\n", markets_l);
	return;
}
void saveTournamentToDB(Tournament* tournament, bool translate) {
	using namespace bsoncxx::builder::stream;
	if (WRITE_NEW_DATA_TO_MONGO && REPLAY == 0) {
		auto coll = db["tournaments"];
		//coll.insert_one(buildTournamentDoc(tournament));

		mongocxx::options::update* update = new mongocxx::options::update();
		update->upsert(true);

		try {
			coll.update_one(document{} << "tournament_id" << tournament->id << "simple_id" << tournament->simple_id << finalize,
				document{} << "$set" << buildTournamentDoc(tournament, translate) << finalize, *update);
		}


		catch (const mongocxx::exception& e) {
			std::cout << "An exception occurred in update_one tournament: " << e.what() << std::endl;
		}

		delete update;



		// return;
	}

};
void loadTournamentsFromDB() {
	//reload_step_1 = 1;
	auto coll = db["tournaments"];
	mongocxx::cursor cursor = coll.find(bsoncxx::builder::stream::document{} << bsoncxx::builder::stream::finalize);  // get all docs
	int i = 0;
	tournaments_l = btournaments_l = 0;
	for (auto doc : cursor) {
		// std::cout << bsoncxx::to_json(doc) << "\n";
		tournaments[i].id = doc["tournament_id"].get_int32();
		tournaments[i].type_radar = doc["type_radar"].get_int32();
		tournaments[i].simple_id = doc["simple_id"].get_int32();
		tournaments[i].season_id = doc["season_id"].get_int32();
		tournaments[i].sport_id = doc["sport_id"].get_int32();
		tournaments[i].category_id = doc["category_id"].get_int32();
		tournaments[i].sort = doc["sort"].get_int32();
		// optional values
		//if (doc["start_date"] == false) {
		tournaments[i].start_date = doc["start_date"].get_int32();
		//}
		//if (doc["end_date"] == false) {

		tournaments[i].end_date = doc["end_date"].get_int32();
		//}
		// string types
		mongo_str_to_buffer(doc["name"], tournaments[i].name);

		//if (doc["season_name"] == false) {
		mongo_str_to_buffer(doc["season_name"], tournaments[i].season_name);

		if (!doc["translations"]) {}
		else
			for (int l = 0; l < tournaments[i].translation_num; l++) if (!doc["translations"][lang[l]]) {}
			else
			{
				if (!doc["translations"][lang[l]]["name"]) {}
				else mongo_str_to_buffer(doc["translations"][lang[l]]["name"], tournaments[i].translation_name[l]);
				if (!doc["translations"][lang[l]]["season_name"]) {}
				else mongo_str_to_buffer(doc["translations"][lang[l]]["season_name"], tournaments[i].translation_season_name[l]);
			}

		//}
		btournaments[i] = tournaments[i];
		if (tournaments[i].id > 0) tournaments_id[tournaments[i].id] = &tournaments[i];
		if (tournaments[i].season_id > 0) seasons_id[tournaments[i].season_id] = &tournaments[i];
		if (tournaments[i].simple_id > 0) simples_id[tournaments[i].simple_id] = &tournaments[i];
		if (btournaments[i].id > 0) btournaments_id[btournaments[i].id] = &btournaments[i];
		if (btournaments[i].season_id > 0) bseasons_id[btournaments[i].season_id] = &btournaments[i];
		if (btournaments[i].simple_id > 0) bsimples_id[btournaments[i].simple_id] = &btournaments[i];



		i++;

	}

	tournaments_l = btournaments_l = i;
	/*
	for (int i = 0; i < tournaments_l; i++) {
	cout << tournaments[i].id << ":" << tournaments[i].name;
	if (tournaments[i].season_name != nullptr)
	cout << ":" << tournaments[i].season_name;
	cout << endl;
	}
	*/
	printf("Tournaments loaded from Mongo succes. Number of loaded tournaments: %d\r\n", tournaments_l);
	return;


};
void saveCategoryToDB(Category* category, bool translate) {
	if (WRITE_NEW_DATA_TO_MONGO && REPLAY == 0) {
		auto coll = db["categories"];
		//coll.insert_one(buildCategoryDoc(category));

		mongocxx::options::update* update = new mongocxx::options::update();
		update->upsert(true);

		try {
			coll.update_one(bsoncxx::builder::stream::document{} << "_id" << category->id << bsoncxx::builder::stream::finalize,
				bsoncxx::builder::stream::document{} << "$set" << buildCategoryDoc(category, translate) << bsoncxx::builder::stream::finalize, *update);
		}


		catch (const mongocxx::exception& e) {
			std::cout << "An exception occurred in update_one category: " << e.what() << std::endl;
		}

		delete update;


		// return;
	}

};
void loadCategoriesFromDB() {
	auto coll = db["categories"];
	mongocxx::cursor cursor = coll.find(bsoncxx::builder::stream::document{} << bsoncxx::builder::stream::finalize);  // get all docs
	int i = 0;
	categories_l = bcategories_l = 0;
	for (auto doc : cursor) {
		// std::cout << bsoncxx::to_json(doc) << "\n";
		categories[i].id = doc["_id"].get_int32();
		categories[i].sport_id = doc["sport_id"].get_int32();
		categories[i].sort = doc["sort"].get_int32();
		mongo_str_to_buffer(doc["name"], categories[i].name);


		if (!doc["translations"]) {}
		else {
			for (int l = 0; l < categories[i].translation_num; l++) if (!doc["translations"][lang[l]]) {}
			else { if (!doc["translations"][lang[l]]["name"]) {} else mongo_str_to_buffer(doc["translations"][lang[l]]["name"], categories[i].translation_name[l]); }

		}


		bcategories[i] = categories[i];
		categories_id[categories[i].id] = &categories[i];
		bcategories_id[bcategories[i].id] = &bcategories[i];
		i++;

	}
	categories_l = bcategories_l = i;
	/*
	for (int i = 0; i < categories_l; i++) {
	cout << categories[i].id << ";" << categories[i].name << ";" << categories[i].sort << ";"
	<< categories[i].sport_id << ";" << endl;
	}
	*/
	printf("Categories loaded from Mongo succes. Number of loaded categories: %d\r\n", categories_l);
	return;

};
void saveSportToDB(Sport* s, bool translate) {
	if (WRITE_NEW_DATA_TO_MONGO && REPLAY == 0) {
		auto coll = db["sports"];
		mongocxx::options::update* update = new mongocxx::options::update();
		update->upsert(true);

		try {
			coll.update_one(bsoncxx::builder::stream::document{} << "_id" << s->id << bsoncxx::builder::stream::finalize,
				bsoncxx::builder::stream::document{} << "$set" << buildSportDoc(s, translate) << bsoncxx::builder::stream::finalize, *update);
		}


		catch (const mongocxx::exception& e) {
			std::cout << "An exception occurred in update_one s: " << e.what() << std::endl;
		}

		delete update;



	}

};
void loadSportsFromDB() {
	reload_step_1 = 1;
	auto coll = db["sports"];
	mongocxx::cursor cursor = coll.find(bsoncxx::builder::stream::document{} << bsoncxx::builder::stream::finalize);  // get all docs
	int i = 0;
	sports_l = bsports_l = 0;
	for (auto doc : cursor) {
		// std::cout << bsoncxx::to_json(doc) << "\n";
		sports[i].id = doc["_id"].get_int32();
		sports[i].sort = doc["sort"].get_int32();
		mongo_str_to_buffer(doc["name"], sports[i].name);

		if (!doc["translations"]) {}
		else {
			for (int l = 0; l < sports[i].translation_num; l++) if (!doc["translations"][lang[l]]) {}
			else
			{
				if (!doc["translations"][lang[l]]["name"]) {}
				else mongo_str_to_buffer(doc["translations"][lang[l]]["name"], sports[i].translation_name[l]);
			}

		}

		bsports[i] = sports[i];
		sports_id[sports[i].id] = &sports[i];
		bsports_id[bsports[i].id] = &bsports[i];
		i++;

	}

	sports_l = bsports_l = i;

	printf("Sports loaded from Mongo succes. Number of loaded sports: %d\r\n", sports_l);
	return;

};
void saveCompetitorToDB(Competitor* competitor, bool translate) {
	if (WRITE_NEW_DATA_TO_MONGO && REPLAY == 0) {
		auto coll = db["competitors"];
		//coll.insert_one(buildCompetitorDoc(competitor));
		mongocxx::options::update* update = new mongocxx::options::update();
		update->upsert(true);

		//printf("saveCompetitorToDB=%d\r\n", competitor->id);

		try {
			coll.update_one(bsoncxx::builder::stream::document{} << "_id" << competitor->id << bsoncxx::builder::stream::finalize,
				bsoncxx::builder::stream::document{} << "$set" << buildCompetitorDoc(competitor, translate) << bsoncxx::builder::stream::finalize, *update);
		}


		catch (const mongocxx::exception& e) {
			std::cout << "An exception occurred in update_one competitor: " << e.what() << std::endl;
		}

		delete update;


		// return;
	}
};
void loadCompetitorsFromDB() {

	auto coll = db["competitors"];

	mongocxx::cursor cursor = coll.find(bsoncxx::builder::stream::document{} << bsoncxx::builder::stream::finalize);  // get all docs
	int i = 0;

	competitors_l = bcompetitors_l = 0;
	for (auto doc : cursor) {
		// std::cout << bsoncxx::to_json(doc) << "\n";
		competitors[i].id = doc["_id"].get_int32();
		competitors[i].sport_id = doc["sport_id"].get_int32();
		competitors[i].category_id = doc["category_id"].get_int32();
		competitors[i].reference_id = doc["reference_id"].get_int32();
		mongo_str_to_buffer(doc["name"], competitors[i].name);
		mongo_str_to_buffer(doc["country_name"], competitors[i].country_name);

		if (!doc["translations"]) {}
		else
			for (int l = 0; l < competitors[i].translation_num; l++) if (!doc["translations"][lang[l]]) {}
			else
			{
				if (!doc["translations"][lang[l]]["name"]) {}
				else   mongo_str_to_buffer(doc["translations"][lang[l]]["name"], competitors[i].translation_name[l]);
				if (!doc["translations"][lang[l]]["country_name"]) {}
				else mongo_str_to_buffer(doc["translations"][lang[l]]["country_name"], competitors[i].translation_country_name[l]);

			}
		bcompetitors[i] = competitors[i];
		competitors_id[competitors[i].id] = &competitors[i];
		bcompetitors_id[bcompetitors[i].id] = &bcompetitors[i];
		i++;

	}

	competitors_l = bcompetitors_l = i;
	/* for (int i = 0; i < competitors_l; i++) {
	if (competitors[i].country_name == nullptr) continue;
	cout << competitors[i].id << ":" << competitors[i].name << ":" << competitors[i].country_name << endl;
	} */

	printf("Competitors loaded from Mongo succes. Number of loaded competitors: %d\r\n", competitors_l);
	return;

};
void savePlayerToDB(Player* player, bool translate) {
	if (WRITE_NEW_DATA_TO_MONGO && REPLAY == 0) {
		auto coll = db["players"];
		//coll.insert_one(buildPlayerDoc(player));
		//printf("savePlayerToDB=%d\r\n", player->id);

		mongocxx::options::update* update = new mongocxx::options::update();
		update->upsert(true);

		try {
			coll.update_one(bsoncxx::builder::stream::document{} << "_id" << player->id << bsoncxx::builder::stream::finalize,
				bsoncxx::builder::stream::document{} << "$set" << buildPlayerDoc(player, translate) << bsoncxx::builder::stream::finalize, *update);
		}


		catch (const mongocxx::exception& e) {
			std::cout << "An exception occurred in update_one player: " << e.what() << std::endl;
		}

		delete update;
		// return;
	}

};
void loadPlayersFromDB() {

	auto coll = db["players"];
	mongocxx::cursor cursor = coll.find(bsoncxx::builder::stream::document{} << bsoncxx::builder::stream::finalize);  // get all docs
	int i = 0;
	players_l = bplayers_l = 0;
	for (auto doc : cursor) {
		// std::cout << bsoncxx::to_json(doc) << "\n";
		players[i].id = doc["_id"].get_int32();
		players[i].competitor_id = doc["competitor_id"].get_int32();
		players[i].number = doc["number"].get_int32();
		players[i].manager = doc["manager"].get_int32();
		players[i].date_of_birth = doc["date_of_birth"].get_int32();
		players[i].weight = doc["weight"].get_int32();
		players[i].height = doc["height"].get_int32();

		mongo_str_to_buffer(doc["name"], players[i].name);
		mongo_str_to_buffer(doc["full_name"], players[i].full_name);
		mongo_str_to_buffer(doc["nationality"], players[i].nationality);
		mongo_str_to_buffer(doc["type"], players[i].type);
		mongo_str_to_buffer(doc["country_code"], players[i].country_code);
		if (!doc["translations"]) {}
		else
			for (int l = 0; l < players[i].translation_num; l++) if (!doc["translations"][lang[l]]) {}
			else
			{
				if (!doc["translations"][lang[l]]["type"]) {}
				else mongo_str_to_buffer(doc["translations"][lang[l]]["type"], players[i].translation_type[l]);

				if (!doc["translations"][lang[l]]["name"]) {}
				else mongo_str_to_buffer(doc["translations"][lang[l]]["name"], players[i].translation_name[l]);

				if (!doc["translations"][lang[l]]["full_name"]) {}
				else mongo_str_to_buffer(doc["translations"][lang[l]]["full_name"], players[i].translation_full_name[l]);

				if (!doc["translations"][lang[l]]["nationality"]) {}
				else mongo_str_to_buffer(doc["translations"][lang[l]]["nationality"], players[i].translation_nationality[l]);

			}

		bplayers[i] = players[i];
		players_id[players[i].id] = &players[i];
		bplayers_id[bplayers[i].id] = &bplayers[i];
		i++;

	}

	players_l = bplayers_l = i;

	/*
	for (int i = 0; i < players_l; i++) {
	cout << players[i].id << ":" << players[i].name  << endl;
	}
	*/
	printf("Players loaded from Mongo succes. Number of loaded players: %d\r\n", players_l);
	return;


};
void loadClientsFromDB() {
	auto coll = db["clients"];
	using namespace bsoncxx::builder;
	/*	Client* c = new Client();
	c->client_id = 1011478;
	c->currency = Currency::USD;
	c->phone = "+905051872213";

	c->anonymous = 1;
	c->timezone = 3;
	c->email_newsletter = 1;
	updateClientToDB(c);*/


	mongocxx::cursor cursor = coll.find(bsoncxx::builder::stream::document{} << bsoncxx::builder::stream::finalize);  // get all docs
	for (auto doc : cursor) {
		Client* c = new Client();
		c->client_id = doc["_id"].get_int32();
		c->anonymous = doc["anonymous"].get_int32();
		if (c->anonymous == 0) {
			c->name = doc["name"].get_utf8().value.to_string();
			c->surname = doc["surname"].get_utf8().value.to_string();
			c->date_of_birth = doc["date_of_birth"].get_int32();
			c->country = doc["country"].get_utf8().value.to_string();
			c->region = doc["region"].get_utf8().value.to_string();
			c->city = doc["city"].get_utf8().value.to_string();
			c->country_id = doc["country_id"].get_int32();
			c->city_id = doc["city_id"].get_int32();
			c->region_id = doc["region_id"].get_int32();
			c->email = doc["email"].get_utf8().value.to_string();
			c->login = doc["login"].get_utf8().value.to_string();
			c->postal_code = doc["postal_code"].get_utf8().value.to_string();
			c->address = doc["address"].get_utf8().value.to_string();
		}


		c->phone = doc["phone"].get_utf8().value.to_string();
		c->email_newsletter = doc["email_newsletter"].get_int32(); //else c->email_newsletter = 0;
		c->currency = static_cast<Currency>((int)doc["currency"].get_int32());

		c->password = doc["password"].get_utf8().value.to_string();

		c->balance = doc["balance"].get_double();
		c->bets_amount = doc["bets_amount"].get_double();
		c->group = doc["group"].get_int32();
		c->language = doc["language"].get_int32();
		c->timezone = doc["timezone"].get_int32();
		c->last_timezone = doc["last_timezone"].get_int32();
		c->domain = doc["domain"].get_utf8().value.to_string();

		c->last_domain = doc["last_domain"].get_utf8().value.to_string();

		// outcomes array
		bsoncxx::document::element documents_elem = doc["documents"];
		bsoncxx::array::view documents{ documents_elem.get_array().value };

		if (documents.empty()) {

		}
		else {
			auto num_documents = std::distance(std::begin(documents), std::end(documents));
			c->documents_number = num_documents;
			c->documents_serial_number = new string[c->documents_number];
			c->documents_type = new int[c->documents_number];
			c->documents_verification_timestamp = new int[c->documents_number];
			int documents_index = 0;
			for (auto elt : documents) {
				bsoncxx::document::view subdoc = elt.get_document().value;
				c->documents_serial_number[documents_index] = subdoc["serial_number"].get_utf8().value.to_string();
				c->documents_type[documents_index] = subdoc["type"].get_int32();
				c->documents_verification_timestamp[documents_index] = subdoc["verification_timestamp"].get_int32();
				documents_index++;
			}
		}



		// insert into hash
		if (max_client_id < c->client_id) max_client_id = c->client_id;
		addClientToHash(c);
		//printf("login=%s  password=%s\r\n", c->login, c->password);


	}

	int index = 0;

	//for (auto it = client_id_hash.begin(); it != client_id_hash.end(); ++it) { it->second->balance = 100000; updateClientBalanceToDB(it->second); }


	/*coll.drop();
	for (auto it = client_id_hash.begin(); it != client_id_hash.end(); ++it) {
	index++;
	if (index == 100) {
	it->second->documents_number = 2;
	it->second->documents_serial_number = new string[it->second->documents_number];
	it->second->documents_type = new int[it->second->documents_number];
	it->second->documents_verification_timestamp = new int[it->second->documents_number];

	it->second->documents_serial_number[0] = "A: 320400923";
	it->second->documents_type[0] = 1;
	it->second->documents_verification_timestamp[0] = 0;

	it->second->documents_serial_number[1] = "bm:AXX 20400923";
	it->second->documents_type[1] = 2;
	it->second->documents_verification_timestamp[1] = 0;
	updateClientToDB(it->second);
	}

	if (index == 105) {
	it->second->documents_number = 3;
	it->second->documents_serial_number = new string[it->second->documents_number];
	it->second->documents_type = new int[it->second->documents_number];
	it->second->documents_verification_timestamp = new int[it->second->documents_number];

	it->second->documents_serial_number[0] = "ID:32442424244442";
	it->second->documents_type[0] = 1;
	it->second->documents_verification_timestamp[0] = 0;

	it->second->documents_serial_number[1] = "dm:1143543222222";
	it->second->documents_type[1] = 2;
	it->second->documents_verification_timestamp[1] = 0;

	it->second->documents_serial_number[2] = "22221341412332444";
	it->second->documents_type[2] = 3;
	it->second->documents_verification_timestamp[2] = 0;


	updateClientToDB(it->second);
	}


	if (index == 106) {
	it->second->documents_number = 3;
	it->second->documents_serial_number = new string[it->second->documents_number];
	it->second->documents_type = new int[it->second->documents_number];
	it->second->documents_verification_timestamp = new int[it->second->documents_number];

	it->second->documents_serial_number[0] = "SSSSSSSSSSSSSS";
	it->second->documents_type[0] = 1;
	it->second->documents_verification_timestamp[0] = 0;

	it->second->documents_serial_number[1] = "wwwwwwwwwwwww";
	it->second->documents_type[1] = 2;
	it->second->documents_verification_timestamp[1] = 0;

	it->second->documents_serial_number[2] = "222222222222222222";
	it->second->documents_type[2] = 3;
	it->second->documents_verification_timestamp[2] = 0;


	updateClientToDB(it->second);
	}


	}
	mongocxx::options::index index_opt{};
	index_opt.unique(false);
	coll.create_index(stream::document{} << "name" << 1 << "surname" << 1 << "date_of_birth" << 1 << stream::finalize, index_opt);
	coll.create_index(stream::document{} << "email" << 1 << stream::finalize, index_opt);
	coll.create_index(stream::document{} << "login" << 1 << stream::finalize, index_opt);
	index_opt.unique(true);
	coll.create_index(stream::document{} << "phone" << 1 << stream::finalize, index_opt);
	for (auto it = client_id_hash.begin(); it != client_id_hash.end(); ++it) updateClientToDB(it->second);
	for (auto it = client_id_hash.begin(); it != client_id_hash.end(); ++it) saveClientToDB(it->second);*/


	printf("Clients loaded from Mongo succes. Number of loaded clients: %d\r\n", client_id_hash.size());
}
size_t calcDecodeLength(const char* b64input) { //Calculates the length of a decoded string
	size_t len = strlen(b64input),
		padding = 0;

	if (b64input[len - 1] == '=' && b64input[len - 2] == '=') //last two chars are =
		padding = 2;
	else if (b64input[len - 1] == '=') //last char is =
		padding = 1;

	return (len * 3) / 4 - padding;
}
int Base64Decode(char* b64message, unsigned char** buffer, size_t* length) { //Decodes a base64 encoded string
	BIO *bio, *b64;

	int decodeLen = calcDecodeLength(b64message);
	*buffer = (unsigned char*)malloc(decodeLen + 1);
	(*buffer)[decodeLen] = '\0';

	bio = BIO_new_mem_buf(b64message, -1);
	b64 = BIO_new(BIO_f_base64());
	bio = BIO_push(b64, bio);

	BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Do not use newlines to flush buffer
	*length = BIO_read(bio, *buffer, strlen(b64message));
	assert(*length == decodeLen); //length should equal decodeLen, else something went horribly wrong
	BIO_free_all(bio);

	return (0); //success
}
void Base64Encode(const std::uint8_t* input, std::size_t inputLen, char*& output, std::size_t& outputLen)
{
	BIO* bio;
	BIO* b64;
	BUF_MEM* bufferPtr;

	b64 = BIO_new(BIO_f_base64());
	bio = BIO_new(BIO_s_mem());
	bio = BIO_push(b64, bio);

	BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
	BIO_write(bio, input, static_cast<int>(inputLen));
	BIO_flush(bio);
	BIO_get_mem_ptr(bio, std::addressof(bufferPtr));
	BIO_set_close(bio, BIO_NOCLOSE);

	output = bufferPtr->data;
	outputLen = bufferPtr->length;
	free(bufferPtr);

	BIO_free_all(bio);
};
char* CreateStep_1(int& len) {
	int i, j = 0;
	len = 0;
	char* buffer = new char[2097152];
	size_t offset = 0;
	size_t retry_offset = 0;
	int markets_length = 0;

	writeInteger(buffer, offset, 0, 1);//system request_id
	writeInteger(buffer, offset, sports_l, 2);
	for (i = 0; i < sports_l; i++) {
		writeInteger(buffer, offset, sports[i].id, 2);
		writeInteger(buffer, offset, sports[i].sort, 1);
		writeString(buffer, offset, sports[i].name);
	}
	writeInteger(buffer, offset, categories_l, 2);
	for (i = 0; i < categories_l; i++) {
		writeInteger(buffer, offset, categories[i].id, 2);
		writeInteger(buffer, offset, categories[i].sport_id, 2);
		writeInteger(buffer, offset, categories[i].sort, 2);
		writeInteger(buffer, offset, categories[i].outrights, 1);
		writeString(buffer, offset, categories[i].name);
	}
	writeInteger(buffer, offset, tournaments_l, 2);
	for (i = 0; i < tournaments_l; i++) {
		writeInteger(buffer, offset, tournaments[i].type_radar, 1);
		writeInteger(buffer, offset, tournaments[i].id, 4);
		writeInteger(buffer, offset, tournaments[i].season_id, 4);
		writeInteger(buffer, offset, tournaments[i].simple_id, 4);
		writeInteger(buffer, offset, tournaments[i].sport_id, 2);
		writeInteger(buffer, offset, tournaments[i].category_id, 2);
		writeInteger(buffer, offset, tournaments[i].sort, 2);
		writeString(buffer, offset, tournaments[i].name);
	}
	//writeInteger(buffer, offset, markets_l, 2);
	retry_offset = offset;
	offset += 2;
	for (i = 0; i < markets_l; i++) {
		if (markets[i].type > 2 && markets[i].variable_text != nullptr) continue;
		markets_length++;
		writeInteger(buffer, offset, markets[i].id, 2);
		writeInteger(buffer, offset, markets[i].type, 1);
		writeInteger(buffer, offset, markets[i].line_type, 1);
		writeString(buffer, offset, markets[i].name);
		writeInteger(buffer, offset, markets[i].variant, 1);
		if (markets[i].variant > -1) writeString(buffer, offset, markets[i].variable_text);
		//if(markets[i].variant>-1 && markets[i].variable_text!=nullptr)
		//writeString(buffer, offset, markets[i].variable_text);
		writeInteger(buffer, offset, markets[i].outcome_number, 2);
		for (j = 0; j < markets[i].outcome_number; j++) {
			writeInteger(buffer, offset, markets[i].outcome_id[j], 4);
			writeString(buffer, offset, markets[i].outcome_name[j]);
		}

		writeInteger(buffer, offset, markets[i].specifier_number, 1);
		for (j = 0; j < markets[i].specifier_number; j++) 	writeString(buffer, offset, markets[i].specifier_name[j]);

	}
	writeInteger(buffer, retry_offset, markets_length, 2);


	char* zip_message = nullptr;
	int zip_len = gzip(buffer, offset, zip_message, 1);
	delete[] buffer;
	if (zip_len < 1) return nullptr;
	char* encode_message = SendframeEncode(zip_message, zip_len, len);
	delete[] zip_message;
	return encode_message;

};
int create_step2_count = 0;
char* CreateStep_2(int& len) {
	int i, j, l, k = 0;
	int events_send_l = 0;
	int event_lines_l = 0;

	char* buffer = new char[LARGE];
	char* buffer_stop = new char[SMALL];
	char* specifier_value = new char[MAX_PATH];
	len = 0;
	size_t offset = 0;
	size_t retry_offset = 0;
	size_t t_offset = 0;
	char* zip_message = nullptr;
	int zip_len = 0;
	char* encode_message = nullptr;// = SendframeEncode(zip_message, zip_len, l
	int encode_message_len = 0;
	offset += 3;


	for (i = 0; i < events_show_l; i++) {
		if (events_show[i]->status == 4 || events_show[i]->status == 3) continue;
		if (events_show[i]->status == 0 && events_show[i]->bet_stop == 1) continue;
		if (events_show[i]->status == 0 && events_show[i]->start_time < time(nullptr) + 200) {

			events_show[i]->bet_stop = 1;
			if (create_step2_count > 0) {
				t_offset = 0;
				writeInteger(buffer_stop, t_offset, 0, 1);//sistem request_id
				writeInteger(buffer_stop, t_offset, events_show[i]->id, 4);
				zip_len = gzip(buffer_stop, t_offset, zip_message, 8);
				if (zip_len > 1)
				{
					encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
					radarMessageHandler(encode_message, encode_message_len);
					encode_message = nullptr;

				}
				delete[] zip_message;
				zip_message = nullptr;

			}
			create_step2_count = 1;
			continue;
		}

		events_send_l++;
		writeInteger(buffer, offset, 0, 1);
		writeInteger(buffer, offset, events_show[i]->id, 4);
		writeInteger(buffer, offset, events_show[i]->home_id, 4);
		writeInteger(buffer, offset, events_show[i]->away_id, 4);
		writeInteger(buffer, offset, events_show[i]->type_radar, 1);
		writeInteger(buffer, offset, events_show[i]->status, 1);
		writeInteger(buffer, offset, events_show[i]->sport_id, 2);
		writeInteger(buffer, offset, events_show[i]->category_id, 2);
		if (events_show[i]->type_radar < 2) writeInteger(buffer, offset, events_show[i]->tournament_id, 4);
		else writeInteger(buffer, offset, events_show[i]->simple_id, 4);

		writeInteger(buffer, offset, events_show[i]->start_time, 4);
		writeInteger(buffer, offset, events_show[i]->period_length, 1);
		writeInteger(buffer, offset, events_show[i]->overtime_length, 1);
		if (events_show[i]->sport_id == 5) writeInteger(buffer, offset, events_show[i]->bo, 1);
		writeString(buffer, offset, events_show[i]->home_name);
		writeString(buffer, offset, events_show[i]->away_name);
		writeString(buffer, offset, events_show[i]->tv_channels);
		if (events_show[i]->status == 0)  writeInteger(buffer, offset, events_show[i]->booked, 1);
		if (events_show[i]->status > 0) {

			writeInteger(buffer, offset, (int)(events_show[i]->home_score * 100), 2);
			writeInteger(buffer, offset, (int)(events_show[i]->away_score * 100), 2);


			writeString(buffer, offset, events_show[i]->set_scores);
			writeString(buffer, offset, events_show[i]->match_time);
			writeString(buffer, offset, events_show[i]->remaining_time);
			writeString(buffer, offset, events_show[i]->remaining_time_in_period);
			writeString(buffer, offset, matchstatus_id[events_show[i]->match_status]->description);
			writeInteger(buffer, offset, events_show[i]->stopped, 1);
			//writeInteger(buffer, offset, events_show[i]->stopped, 1); 
			if (events_show[i]->sport_id == 1) {
				writeInteger(buffer, offset, events_show[i]->home_redcards, 1);
				writeInteger(buffer, offset, events_show[i]->home_yellowcards, 1);
				writeInteger(buffer, offset, events_show[i]->away_redcards, 1);
				writeInteger(buffer, offset, events_show[i]->away_yellowcards, 1);
				writeString(buffer, offset, events_show[i]->stoppage_time);
				writeString(buffer, offset, events_show[i]->stoppage_time_announced);
				writeInteger(buffer, offset, events_show[i]->home_corners, 1);
				writeInteger(buffer, offset, events_show[i]->away_corners, 1);
				writeInteger(buffer, offset, events_show[i]->home_yellow_red_cards, 1);
				writeInteger(buffer, offset, events_show[i]->away_yellow_red_cards, 1);
			}

			if (events_show[i]->sport_id == 5) {
				writeInteger(buffer, offset, events_show[i]->home_gamescore, 1);
				writeInteger(buffer, offset, events_show[i]->away_gamescore, 1);
				writeInteger(buffer, offset, events_show[i]->tiebreak, 1);
			}

			if (events_show[i]->sport_id == 20) writeInteger(buffer, offset, events_show[i]->expedite_mode, 1);


			if (events_show[i]->sport_id == 4 || events_show[i]->sport_id == 6 || events_show[i]->sport_id == 29) {
				writeInteger(buffer, offset, events_show[i]->home_suspend, 1); writeInteger(buffer, offset, events_show[i]->away_suspend, 1);
			}


			if (events_show[i]->sport_id == 5 || events_show[i]->sport_id == 20 || events_show[i]->sport_id == 34 || events_show[i]->sport_id == 19 || events_show[i]->sport_id == 23 || events_show[i]->sport_id == 22 || events_show[i]->sport_id == 31)
				writeInteger(buffer, offset, events_show[i]->current_server, 1);


			if (events_show[i]->sport_id == 3) {
				writeInteger(buffer, offset, events_show[i]->home_batter, 1);
				writeInteger(buffer, offset, events_show[i]->away_batter, 1);
				writeInteger(buffer, offset, events_show[i]->outs, 1);
				writeInteger(buffer, offset, events_show[i]->balls, 1);
				writeInteger(buffer, offset, events_show[i]->strikes, 1);
				writeString(buffer, offset, events_show[i]->bases);
			}

			if (events_show[i]->sport_id == 16) {
				writeInteger(buffer, offset, events_show[i]->possession, 1);
				writeInteger(buffer, offset, events_show[i]->try_num, 1);
				writeInteger(buffer, offset, events_show[i]->yards, 1);
			}




			if (events_show[i]->sport_id == 19) {
				writeInteger(buffer, offset, events_show[i]->visit, 1);
				writeInteger(buffer, offset, events_show[i]->remaining_reds, 1);
			}


			if (events_show[i]->sport_id == 22) {
				writeInteger(buffer, offset, events_show[i]->home_legscore, 1);
				writeInteger(buffer, offset, events_show[i]->away_legscore, 1);
				writeInteger(buffer, offset, events_show[i]->throw_num, 1);
				writeInteger(buffer, offset, events_show[i]->visit, 1);
			}

			if (events_show[i]->sport_id == 32) {
				writeInteger(buffer, offset, events_show[i]->delivery, 1);
				writeInteger(buffer, offset, events_show[i]->home_remaining_bowls, 1);
				writeInteger(buffer, offset, events_show[i]->away_remaining_bowls, 1);
				writeInteger(buffer, offset, events_show[i]->current_end, 1);
			}

			if (events_show[i]->sport_id == 21) {
				writeInteger(buffer, offset, events_show[i]->home_dismissals, 1);
				writeInteger(buffer, offset, events_show[i]->away_dismissals, 1);
				writeInteger(buffer, offset, events_show[i]->home_penalty_runs, 1);
				writeInteger(buffer, offset, events_show[i]->away_penalty_runs, 1);
				writeInteger(buffer, offset, events_show[i]->innings, 1);
				writeInteger(buffer, offset, events_show[i]->over, 1);
				writeInteger(buffer, offset, events_show[i]->delivery, 1);

			}

			if (events_show[i]->sport_id == 0) writeInteger(buffer, offset, events_show[i]->current_ct_team, 1);

			writeInteger(buffer, offset, events_show[i]->position, 1);

		}



		if (event2lines.find(events_show[i]->getCatKey()) == event2lines.end()) {  writeInteger(buffer, offset, 0, 2); writeInteger(buffer, offset, 0, 2); continue; }
		//printf("events_show[i]->id=%d\r\n", events_show[i]->id);
		//if (events_show[i]->type_radar == 1) printf("events_show[i]->status=%d\r\n", events_show[i]->status);

		writeInteger(buffer, offset, event2lines[events_show[i]->getCatKey()]->size(), 2);

		event_lines_l = 0;
		retry_offset = offset;
		offset += 2;



		for (unordered_set<int>::iterator it = event2lines[events_show[i]->getCatKey()]->begin(); it != event2lines[events_show[i]->getCatKey()]->end(); ++it)
		{
			if (markets_id[lines[*(it)].market_id][0]->line_type == 0 && events_show[i]->status == 0) continue;
			if (lines[*(it)].status == 0 || lines[*(it)].status == -3) continue;
			event_lines_l++;
			writeInteger(buffer, offset, lines[*(it)].id, 4);
			//writeInteger(buffer, offset, lines[*(it)].betstop_reason, 1);
			writeInteger(buffer, offset, lines[*(it)].market_id, 2);
			writeInteger(buffer, offset, lines[*(it)].type, 1);
			writeInteger(buffer, offset, lines[*(it)].favourite, 1);
			if (events_show[i]->bet_stop == 1 && lines[*(it)].status == 1) writeInteger(buffer, offset, -1, 1); else
				writeInteger(buffer, offset, lines[*(it)].status, 1);
			if (lines[*(it)].type == 3) writeString(buffer, offset, lines[*(it)].name);

			//if (lines[*(it)].outcome_number == 0) printf("lines[*(it)].outcome_number=0 lines[*(it)].id=%d  lines[*(it)].market_id=%d\r\n", lines[*(it)].id, lines[*(it)].market_id);
			writeInteger(buffer, offset, lines[*(it)].outcome_number, 2);
			for (j = 0; j < lines[*(it)].outcome_number; j++) {
				writeInteger(buffer, offset, lines[*(it)].outcome_id[j], 4);
				writeInteger(buffer, offset, lines[*(it)].outcome_active[j], 1);
				if (lines[*(it)].type == 1 || lines[*(it)].type == 2 || lines[*(it)].type == 4) writeInteger(buffer, offset, lines[*(it)].outcome_team[j], 1);
				//if ((lines[*(it)].type == 1 || lines[*(it)].type == 2) && lines[*(it)].outcome_team[j] != 3)
				//if (lines[*(it)].type == 1 || lines[*(it)].type == 2 || lines[*(it)].type == 4)
				if (lines[*(it)].type > 0) writeString(buffer, offset, lines[*(it)].outcome_name[j]);

				//writeInteger(buffer, offset, (int)(lines[*(it)].outcome_odds[j] * 10000), 4);
				writeFloat(buffer, offset, lines[*(it)].outcome_odds[j]);
				if (PROBABILITIES == 1) writeInteger(buffer, offset, (int)(lines[*(it)].outcome_probabilities[j] * 100000 + 0.5), 4);

			}

			writeInteger(buffer, offset, lines[*(it)].specifier_number, 1);
			for (j = 0; j < lines[*(it)].specifier_number; j++) {
				if (lines[*(it)].market_id == 215 && j == 2) {
					strcpy(specifier_value, lines[*(it)].specifier_value[j]); replace_competitor(specifier_value);
					writeString(buffer, offset, specifier_value);
				}
				else 	if (lines[*(it)].market_id == 882 && j == 0) {
					strcpy(specifier_value, lines[*(it)].specifier_value[j]); replace_player(specifier_value);
					writeString(buffer, offset, specifier_value);
				}
				else 	writeString(buffer, offset, lines[*(it)].specifier_value[j]);


			}



		}

		writeInteger(buffer, retry_offset, event_lines_l, 2);

		k = k + event_lines_l;

	}
	retry_offset = 0;


	writeInteger(buffer, retry_offset, 0, 1); //system request_id = 0;
	writeInteger(buffer, retry_offset, events_send_l, 2);

	zip_message = nullptr;
	zip_len = gzip(buffer, offset, zip_message, 2);
	delete[] buffer;
	delete[] buffer_stop;
	delete[] specifier_value;
	if (zip_len < 1) return nullptr;
	encode_message = SendframeEncode(zip_message, zip_len, len);
	delete[] zip_message;
	return encode_message;

};
int getActiveNumLines(string key) {
	int active_lines_counter = 0;
	if (event2lines.find(key) == event2lines.end()) { return 0; }
	else for (unordered_set<int>::iterator it = event2lines[key]->begin(); it != event2lines[key]->end(); ++it)
		if (lines[*(it)].status == -1 || lines[*(it)].status == 1) active_lines_counter++;
	return active_lines_counter;

}
void CreatePlus_2(wsClient* wsclient) {
	//printf("CreatePlus_2\r\n");
	//server.wsClients[clientIDs[i]]
	int i, j, l, k = 0;
	int events_send_l = 0;
	int event_lines_l = 0;

	char* buffer = new char[LARGE];
	char* specifier_value = new char[MAX_PATH];
	int len = 0;
	size_t offset = 0;
	size_t retry_offset = 0;
	string event_key = wsclient->plus;
	Event* _event = nullptr;
	int event_id = 0;
	//printf("CreatePlus_2 server.wsClients[%d]->plus=%d\r\n", clientID, server.wsClients[clientID]->plus);

	//if (event_id >= MAX_EVENTS) { std::printf("ERROR DATA!\r\nsevent id out of MAX_EVENTS in CreatePlus_2 %d\r\n", event_id); delete[] buffer; client->plus_create = false; client->plus_send = false; return; }

	if (events_id.find(event_key) == events_id.end()) { std::printf("\r\nEvent key= %s not found in CreatePlus_2 \r\n", event_key); delete[] buffer; wsclient->plus_create = false; wsclient->plus_send = false; wsclient->plus = ""; return; }
	if (events_id[event_key]->show == 0) { std::printf("\r\nsEvent id= %d not show type in CreatePlus_2 %d\r\n", event_id); delete[] buffer; wsclient->plus_create = false; wsclient->plus_send = false; wsclient->plus = ""; return; }
	_event = events_id[event_key];
	event_id =_event->id;
	if (event2lines.find(event_key) == event2lines.end()) { std::printf("\r\nsEvent id= %d not lines for show  in CreatePlus_2 %d\r\n", event_id); delete[] buffer; wsclient->plus_create = false; wsclient->plus_send = false;  wsclient->plus = "";  return; }
	events_send_l = 1;
	writeInteger(buffer, offset, wsclient->plus_request_id, 1);
	writeInteger(buffer, offset, events_send_l, 2);
	writeInteger(buffer, offset, 5, 1); //5 response for rospis command
	writeInteger(buffer, offset, event_id, 4);
	//writeInteger(buffer, offset, event2lines[event_id]->size(), 2);
	event_lines_l = 0;
	retry_offset = offset;
	offset += 2;

	for (unordered_set<int>::iterator it = event2lines[event_key]->begin(); it != event2lines[event_key]->end(); ++it)
	{
		//if (markets_id[lines[*(it)].market_id][0]->line_type == 0 && events_show[i]->status == 0) continue;
		if (lines[*(it)].status == 0 || lines[*(it)].status == -3) continue;
		event_lines_l++;
		writeInteger(buffer, offset, lines[*(it)].id, 4);
		//writeInteger(buffer, offset, lines[*(it)].betstop_reason, 1);
		writeInteger(buffer, offset, lines[*(it)].market_id, 2);
		writeInteger(buffer, offset, lines[*(it)].type, 1);
		writeInteger(buffer, offset, lines[*(it)].favourite, 1);
		if (_event->bet_stop == 1 && lines[*(it)].status == 1) writeInteger(buffer, offset, -1, 1); else
			writeInteger(buffer, offset, lines[*(it)].status, 1);
		//if (lines[*(it)].outcome_number == 0) printf("lines[*(it)].outcome_number=0 lines[*(it)].id=%d  lines[*(it)].market_id=%d\r\n", lines[*(it)].id, lines[*(it)].market_id);
		if (lines[*(it)].type == 3) writeString(buffer, offset, lines[*(it)].name);
		writeInteger(buffer, offset, lines[*(it)].outcome_number, 2);
		for (j = 0; j < lines[*(it)].outcome_number; j++) {
			writeInteger(buffer, offset, lines[*(it)].outcome_id[j], 4);
			writeInteger(buffer, offset, lines[*(it)].outcome_active[j], 1);
			if (lines[*(it)].type == 1 || lines[*(it)].type == 2 || lines[*(it)].type == 4) writeInteger(buffer, offset, lines[*(it)].outcome_team[j], 1);
			//if ((lines[*(it)].type == 1 || lines[*(it)].type == 2) && lines[*(it)].outcome_team[j] != 3)
			//if (lines[*(it)].type == 1 || lines[*(it)].type == 2 || lines[*(it)].type == 4)
			if (lines[*(it)].type > 0) writeString(buffer, offset, lines[*(it)].outcome_name[j]);
			//writeInteger(buffer, offset, (int)(lines[*(it)].outcome_odds[j] * 10000), 4);
			writeFloat(buffer, offset, lines[*(it)].outcome_odds[j]);
			if (PROBABILITIES == 1) writeInteger(buffer, offset, (int)(lines[*(it)].outcome_probabilities[j] * 100000 + 0.5), 4);

		}

		writeInteger(buffer, offset, lines[*(it)].specifier_number, 1);
		//for (j = 0; j < lines[*(it)].specifier_number; j++) writeString(buffer, offset, lines[*(it)].specifier_value[j]);
		for (j = 0; j < lines[*(it)].specifier_number; j++) {
			if (lines[*(it)].market_id == 215 && j == 2) {
				strcpy(specifier_value, lines[*(it)].specifier_value[j]); replace_competitor(specifier_value);
				writeString(buffer, offset, specifier_value);
			}
			else 	if (lines[*(it)].market_id == 882 && j == 0) {
				strcpy(specifier_value, lines[*(it)].specifier_value[j]); replace_player(specifier_value);
				writeString(buffer, offset, specifier_value);
			}
			else 	writeString(buffer, offset, lines[*(it)].specifier_value[j]);


		}




	}

	writeInteger(buffer, retry_offset, event_lines_l, 2);

	if (event_lines_l == 0) { delete[] buffer; wsclient->plus_create = false; wsclient->plus = ""; wsclient->plus_send = false; return; }


	char* zip_message = nullptr;
	int zip_len = gzip(buffer, offset, zip_message, 2);
	delete[] buffer;
	if (zip_len < 1) return;
	char* encode_message = SendframeEncode(zip_message, zip_len, len);
	delete[] zip_message;
	delete[] specifier_value;
	wsclient->plus_message = encode_message;
	wsclient->plus_message_length = len;

	//printf("CreatePlus_2 client->plus_message_length=%d\r\n",client->plus_message_length);

	//printf("server.wsClients[clientID]->plus_message_length=%d\r\n", server.wsClients[clientID]->plus_message_length);

	wsclient->plus_send = true;
	wsclient->plus_create = false;


};
void CreateOutright_2(wsClient* client) {
	//printf("CreateOutright_2\r\n");
	//server.wsClients[clientIDs[i]]
	int i, j, l, k = 0;
	int events_send_l = 0;
	int event_lines_l = 0;
	int type_radar = 0;//2 simple //3 season
	Line* _line;
	char* buffer = new char[LARGE];
	char* specifier_value = new char[MAX_PATH];
	int len = 0;
	size_t offset = 0;
	size_t retry_offset = 0;
	int category_id = client->outright;
	int line_id = 0;

	//printf("CreateOutright_2 server.wsClients[%d]->outright=%d\r\n", clientID, server.wsClients[clientID]->outright);

	if (category_id >= MAX_CATEGORIES) { std::printf("ERROR DATA!\r\ncategory_id out of MAX_CATEGORIES in CreateOutright_2 %d\r\n", category_id); delete[] buffer; client->outright_create = false; client->outright_send = false; return; }
	if (categories_id[category_id] == nullptr) { std::printf("\r\ncategory_id= %d not found in CreateOutright_2\r\n", category_id);  delete[] buffer; client->outright_create = false; client->outright_send = false; return; }
	//if (categories_id[category_id]->show == 0) { std::printf("\r\nsEvent id= %d not show type in CreateOutright_2 %d\r\n", category_id); return; }
	//if (event2lines.find(category_id) == event2lines.end()) { std::printf("\r\nsEvent id= %d not lines for show  in CreateOutright_2 %d\r\n", category_id); return; }

	//	writeInteger(buffer, offset, 1, 2);
	//	writeInteger(buffer, offset, 100, 1);

	//writeInteger(buffer, offset, category_id, 4);
	//writeInteger(buffer, offset, event2lines[category_id]->size(), 2);

	event_lines_l = 0;
	retry_offset = offset;
	offset += 3;


	for (i = 0; i < categories_id[category_id]->outrights_id.size(); i++)
	{
		line_id = categories_id[category_id]->outrights_id[i];

		if (line_id >= MAX_LINES) {
			std::printf("ERROR DATA!\r\nline_id out of MAX_LINES in CreateOutright_2 %d\r\n", line_id); continue;
		}
		_line = lines_id[line_id];
		event_lines_l = 0;
		if (_line == nullptr) { std::printf("\r\nline_id= %d not found in CreateOutright_2\r\n", line_id);  continue; }
		if (_line->status == 0 || _line->status == -3)  continue;

		//if (_line->simple_id > 0) type_radar = 2; else type_radar = 3;
		writeInteger(buffer, offset, _line->type_radar, 1);
		if (_line->type_radar == 2) {
			writeInteger(buffer, offset, _line->simple_id, 4);
			writeInteger(buffer, offset, simples_id[_line->simple_id]->end_date, 4);
		}
		else {
			writeInteger(buffer, offset, _line->tournament_id, 4);
			writeInteger(buffer, offset, tournaments_id[_line->tournament_id]->end_date, 4);
		}
		//writeInteger(buffer, offset, _line->tournament_id, 4);
		event_lines_l++;
		events_send_l++;
		writeInteger(buffer, offset, event_lines_l, 2);
		writeInteger(buffer, offset, _line->id, 4);
		//writeInteger(buffer, offset, _line->betstop_reason, 1);
		//writeInteger(buffer, offset, _line->next_betstop, 4);
		writeInteger(buffer, offset, _line->market_id, 2);
		writeInteger(buffer, offset, _line->type, 1);
		writeInteger(buffer, offset, _line->favourite, 1);
		//if (events_show[i]->bet_stop == 1 && lines[*(it)].status == 0) writeInteger(buffer, offset, -1, 1); else
		writeInteger(buffer, offset, _line->status, 1);
		//if (_line->outcome_number == 0) printf("_line->outcome_number=0 _line->id=%d  _line->market_id=%d\r\n", _line->id, _line->market_id);
		if (_line->type == 3) writeString(buffer, offset, _line->name);
		writeInteger(buffer, offset, _line->outcome_number, 2);
		for (int j = 0; j < _line->outcome_number; j++) {
			writeInteger(buffer, offset, _line->outcome_id[j], 4);
			writeInteger(buffer, offset, _line->outcome_active[j], 1);
			if (_line->type == 1 || _line->type == 2 || _line->type == 4) writeInteger(buffer, offset, _line->outcome_team[j], 1);
			//if ((_line->type == 1 || _line->type == 2) && _line->outcome_team[j] != 3)
			//if (_line->type == 1 || _line->type == 2 || _line->type == 4) 
			if (_line->type > 0)  writeString(buffer, offset, _line->outcome_name[j]);
			//writeInteger(buffer, offset, (int)(_line->outcome_odds[j] * 10000), 4);
			writeFloat(buffer, offset, _line->outcome_odds[j]);
			if (PROBABILITIES == 1) writeInteger(buffer, offset, (int)(_line->outcome_probabilities[j] * 100000 + 0.5), 4);
		}

		writeInteger(buffer, offset, _line->specifier_number, 1);
		//for (int j = 0; j < _line->specifier_number; j++) writeString(buffer, offset, _line->specifier_value[j]);
		for (j = 0; j < _line->specifier_number; j++) {
			if (_line->market_id == 215 && j == 2) {
				strcpy(specifier_value, _line->specifier_value[j]); replace_competitor(specifier_value);
				writeString(buffer, offset, specifier_value);
			}
			else 	if (_line->market_id == 882 && j == 0) {
				strcpy(specifier_value, _line->specifier_value[j]); replace_player(specifier_value);
				writeString(buffer, offset, specifier_value);
			}
			else 	writeString(buffer, offset, _line->specifier_value[j]);


		}

	}

	writeInteger(buffer, retry_offset, client->outright_request_id, 1);
	writeInteger(buffer, retry_offset, events_send_l, 2);




	if (events_send_l == 0) { delete[] buffer; client->outright_create = false; client->outright_send = false; return; }
	char* zip_message = nullptr;
	int zip_len = gzip(buffer, offset, zip_message, 2);
	delete[] buffer;
	delete[] specifier_value;
	if (zip_len < 1) return;
	char* encode_message = SendframeEncode(zip_message, zip_len, len);
	delete[] zip_message;
	client->outright_message = encode_message;
	client->outright_message_length = len;

	//printf("CreateOutright_2 client->outright_message_length=%d\r\n",client->outright_message_length);

	//printf("server.wsClients[clientID]->outright_message_length=%d\r\n", server.wsClients[clientID]->outright_message_length);

	client->outright_send = true;
	client->outright_create = false;


};
char* SendframeEncode(char* message, int messageLen, int &totalLength) {
	char *buf = nullptr;
	unsigned char opcode = WS_OPCODE_BINARY;
	// set max payload length per frame
	int bufferSize = EXTRA;

	// work out amount of frames to send, based on $bufferSize
	int frameCount = ceil((float)messageLen / bufferSize);
	if (frameCount == 0)
		frameCount = 1;

	// set last frame variables
	int maxFrame = frameCount - 1;
	int lastframe_buffer_length = (messageLen % bufferSize) != 0 ? (messageLen % bufferSize) : (messageLen != 0 ? bufferSize : 0);

	// loop around all frames to send



	for (int i = 0; i < frameCount; i++) {
		// fetch fin, opcode and buffer length for frame
		unsigned char fin = i != maxFrame ? 0 : WS_FIN;
		opcode = i != 0 ? WS_OPCODE_CONTINUATION : opcode;

		size_t buffer_length = i != maxFrame ? bufferSize : lastframe_buffer_length;



		// set payload length variables for frame
		if (buffer_length <= 125) {
			// int payloadLength = buffer_length;
			totalLength = buffer_length + 2;
			buf = new char[totalLength];
			buf[0] = fin | opcode;
			buf[1] = buffer_length;
			memcpy(buf + 2, message, messageLen);
		}
		else if (buffer_length <= 65535) {
			// int payloadLength = WS_PAYLOAD_LENGTH_16;
			totalLength = buffer_length + 4;
			buf = new char[totalLength];
			buf[0] = fin | opcode;
			buf[1] = WS_PAYLOAD_LENGTH_16;
			buf[2] = buffer_length >> 8;
			buf[3] = buffer_length;
			memcpy(buf + 4, message, messageLen);
		}
		else {
			// int payloadLength = WS_PAYLOAD_LENGTH_63;
			totalLength = buffer_length + 10;
			buf = new char[totalLength];
			buf[0] = fin | opcode;
			buf[1] = WS_PAYLOAD_LENGTH_63;
			buf[2] = 0;
			buf[3] = 0;
			buf[4] = 0;
			buf[5] = 0;
			buf[6] = buffer_length >> 24;
			buf[7] = buffer_length >> 16;
			buf[8] = buffer_length >> 8;
			buf[9] = buffer_length;
			memcpy(buf + 10, message, messageLen);
		}

	}

	return buf;
};
int64_t timestamp() {
	time_t start;
	SYSTEMTIME st;
	struct tm tm;
	memset(&st, 0, sizeof(st));
	memset(&tm, 0, sizeof(tm));
	GetSystemTime(&st);

	tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
	tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
	start = mktime(&tm);
	return start * 1000 + st.wMilliseconds;




}
int DMYtoSeconds(int day, int month, int year) {
	time_t seconds;
	int sign = 1;
	if (year < 1970) { sign = -1; year = year + 70; }
	struct tm tm;
	memset(&tm, 0, sizeof(tm));
	tm.tm_year = year - 1900; // EDIT 2 : 1900's Offset as per comment
	tm.tm_mon = month;
	tm.tm_mday = day;	tm.tm_hour = 0;	tm.tm_min = 0;	tm.tm_sec = 0; tm.tm_isdst = -1;
	seconds = mktime(&tm);
	return sign * seconds;
}
void openHandler(int clientID) {
	ostringstream os;
	os << "Stranger " << clientID << " has joined.";
	char* zip_message = nullptr;
	int zip_len = gzip((char*)os.str().c_str(), os.str().size(), zip_message);
	if (zip_len < 1) return;

	vector<int> clientIDs = server.getClientIDs();
	for (int i = 0; i < clientIDs.size(); i++) {
		if (clientIDs[i] != clientID)
			server.wsSend(clientIDs[i], zip_message, zip_len);
	}
	delete[] zip_message;
	zip_message = nullptr;
	zip_len = gzip("Welcome!", 7, zip_message);
	if (zip_len < 1) return;
	server.wsSend(clientID, zip_message, zip_len);
	delete[] zip_message;

}
void closeHandler(int clientID) {

	ostringstream os;
	os << "Stranger " << clientID << " has leaved.";

	char* zip_message = nullptr;
	int zip_len = gzip((char*)os.str().c_str(), os.str().size(), zip_message);
	if (zip_len < 1) return;

	vector<int> clientIDs = server.getClientIDs();
	for (int i = 0; i < clientIDs.size(); i++) {
		if (clientIDs[i] != clientID)
			server.wsSend(clientIDs[i], zip_message, zip_len);
	}
	delete[] zip_message;
}
void messageHandler(int clientID, string data) {
	ostringstream os;
	os << "Stranger " << clientID << " says: " << data;
	char* zip_message = nullptr;
	int zip_len = gzip((char*)os.str().c_str(), os.str().size(), zip_message);
	if (zip_len < 1) return;


	vector<int> clientIDs = server.getClientIDs();
	for (int i = 0; i < clientIDs.size(); i++) {
		if (clientIDs[i] != clientID)
			server.wsSend(clientIDs[i], zip_message, zip_len);
	}
	delete[] zip_message;
}
void periodicHandler() {

	static time_t next = time(nullptr) + 10;
	time_t current = time(nullptr);
	if (current >= next) {
		ostringstream os;
		string timestring = ctime(&current);
		timestring = timestring.substr(0, timestring.size() - 1);
		os << timestring;
		char* zip_message = nullptr;
		int zip_len = gzip((char*)os.str().c_str(), os.str().size(), zip_message);
		if (zip_len < 1) return;

		vector<int> clientIDs = server.getClientIDs();
		for (int i = 0; i < clientIDs.size(); i++)
			server.wsSend(clientIDs[i], zip_message, zip_len);
		next = time(nullptr) + 10;
		delete[] zip_message;
	}
}
void radarMessageHandler(char* message, int messageLen) {
	vector<int> clientIDs = server.getClientIDs();
	for (int i = 0; i < clientIDs.size(); i++) {
		if (server.wsClients[clientIDs[i]]->init == 0) continue;
		server.wsSend(clientIDs[i], message, messageLen);
	}
}
int httpsServer() {
	WSADATA wsaData;
	int iResult = 0;
	X509*  cert;
	SSL_CTX *ctx;
	SSL *ssl;
	SOCKET ListenSocket = INVALID_SOCKET;
	sockaddr_in service;
	int recvbuflen = EXTRA;
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
	iResult = ::bind(ListenSocket, (SOCKADDR *)& service, sizeof(service));
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

		SOCKET clientSocket = accept(ListenSocket, nullptr, nullptr);
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
		if (cert != nullptr) {
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
		std::strcpy(sendBuf, sendHeader);
		std::strcpy(sendBuf1, sendBody1);
		std::strcat(sendBuf1, recvbuf);
		std::strcat(sendBuf1, sendBody2);
		_itoa(strlen(sendBuf1), sendBuf2, 10);
		std::strcat(sendBuf, sendBuf2);
		std::strcat(sendBuf, sendTail);
		std::strcat(sendBuf, sendBuf1);


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
atomic_int https_request_failed_counter = 0;
int httpsRequest(char* domain, char* path, char* recv, int mode) {
	https_request_failed_counter++;
	if (https_request_failed_counter > 2) {
		recv = new char[1];
		recv[0] = 0;
		https_request_failed_counter = 0; return 0;
	}

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
	int buflen = EXTRA;
	int readBytes = 0;

	//vps426791.ovh.net

	SSL_load_error_strings();
	SSL_library_init();
	OpenSSL_add_all_algorithms();

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) { wprintf(L"WSAStartup() failed with error: %d\n", iResult); https_request_status = -1; return -1; }


	remoteHost = gethostbyname(domain);
	if (remoteHost == nullptr) {
		dwError = WSAGetLastError(); if (dwError != 0) {
			if (dwError == WSAHOST_NOT_FOUND) { std::printf("Host not found\n");  WSACleanup(); https_request_status = -1; return -1; }
			else if (dwError == WSANO_DATA) { std::printf("No data record found\n");  WSACleanup(); https_request_status = -1; return -1; }
			else {
				printf("Function failed with error: %ld\n", dwError);
				https_request_status = -1; return -1;
			}
		}
	}
	/*else {
	printf("Function returned:\n");std::printf("\tOfficial name: %s\n", remoteHost->h_name);

	for (pAlias = remoteHost->h_aliases; *pAlias != 0; pAlias++) {
	printf("\tAlternate name #%d: %s\n", ++i, *pAlias);
	}std::printf("\tAddress type: ");


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
	if (sdkSocket == INVALID_SOCKET) { wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());   WSACleanup(); https_request_status = -1; return -1; }
	sdkService.sin_family = AF_INET;
	sdkService.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list));
	sdkService.sin_port = htons(443);
	iResult = connect(sdkSocket, (SOCKADDR *)& sdkService, sizeof(sdkService));

	if (iResult == SOCKET_ERROR) {
		wprintf(L"connect function failed with error: %ld\n", WSAGetLastError()); iResult = closesocket(sdkSocket);
		if (iResult == SOCKET_ERROR) wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());  WSACleanup();
		https_request_status = -1; return -1;
	}
	ctx = SSL_CTX_new(SSLv23_client_method()); ssl = SSL_new(ctx);
	if (!ssl) {
		wprintf(L"SSL creation error\n"); iResult = closesocket(sdkSocket); if (iResult == SOCKET_ERROR) wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
		WSACleanup(); https_request_status = -1; return -1;
	}
	SSL_set_fd(ssl, sdkSocket);
	iResult = SSL_connect(ssl);
	if (!iResult) {
		wprintf(L"SSL connect error\nretval: %d\n", iResult); iResult = closesocket(sdkSocket);
		if (iResult == SOCKET_ERROR) { SSL_CTX_free(ctx);  wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError()); WSACleanup(); return -1; }
		iResult = SSL_get_error(ssl, iResult); wprintf(L"SSL error: %d\n", iResult); https_request_status = -1; return -1;
	}

	//cert = SSL_get_peer_certificate(ssl);

	//str = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
	//printf("\t subject: %s\n", str);
	//OPENSSL_free(str);


	//str = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
	//printf("\t issuer: %s\n", str);
	//OPENSSL_free(str);


	//X509_free(cert);
	sendBuf = new char[1024];
	if (mode == 0)std::strcpy(sendBuf, "GET ");
	else if (mode == 1)std::strcpy(sendBuf, "POST ");
	else if (mode == 2)std::strcpy(sendBuf, "PUT ");
	else if (mode == 3)std::strcpy(sendBuf, "DELETE ");
	else std::strcpy(sendBuf, "GET ");
	strcat(sendBuf, path);
	strcat(sendBuf, " HTTP/1.0\nHost: ");
	strcat(sendBuf, domain);
	strcat(sendBuf, "\r\nx-access-token: ");
	strcat(sendBuf, TOKEN);
	strcat(sendBuf, "\r\nUser-Agent: Webclient\r\nAccept:*/*\r\n\r\n");
	iResult = SSL_write(ssl, sendBuf, strlen(sendBuf));


	do {

		iResult = SSL_read(ssl, (char*)recv + readBytes, buflen - readBytes);
		if (iResult > 0) {
			readBytes = readBytes + iResult;

		}

	} while (iResult > 0);
	recv[readBytes] = '\0';
	delete[] sendBuf;
	closesocket(sdkSocket);
	SSL_shutdown(ssl);
	SSL_free(ssl);
	SSL_CTX_free(ctx);

	WSACleanup();

	https_request_status = 0;
	https_request_failed_counter = 0;
	return readBytes;

};
int httpRequest(char* domain, char* path, char* recv_buf, int mode) {

	int iResult = 0;
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
	int buflen = EXTRA;
	int readBytes = 0;

	remoteHost = gethostbyname(domain);
	if (remoteHost == nullptr) {
		dwError = WSAGetLastError(); if (dwError != 0) {
			if (dwError == WSAHOST_NOT_FOUND) { std::printf("Host not found\n"); return -1; }
			else if (dwError == WSANO_DATA) { std::printf("No data record found\n");  return -1; }
			else {
				printf("Function failed with error: %ld\n", dwError);
				return -1;
			}
		}
	}


	sdkSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sdkSocket == INVALID_SOCKET) { wprintf(L"socket function failed with error: %ld\n", WSAGetLastError()); return -1; }
	sdkService.sin_family = AF_INET;
	sdkService.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list));
	sdkService.sin_port = htons(80);
	iResult = connect(sdkSocket, (SOCKADDR *)& sdkService, sizeof(sdkService));

	if (iResult == SOCKET_ERROR) {
		wprintf(L"connect function failed with error: %ld\n", WSAGetLastError()); iResult = closesocket(sdkSocket);
		if (iResult == SOCKET_ERROR) wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
		return -1;
	}

	sendBuf = new char[1024];
	if (mode == 0)std::strcpy(sendBuf, "GET ");
	else if (mode == 1)std::strcpy(sendBuf, "POST ");
	else if (mode == 2)std::strcpy(sendBuf, "PUT ");
	else if (mode == 3)std::strcpy(sendBuf, "DELETE ");
	else std::strcpy(sendBuf, "GET ");
	strcat(sendBuf, path);
	strcat(sendBuf, " HTTP/1.0\nHost: ");
	strcat(sendBuf, domain);
	strcat(sendBuf, "\r\nx-access-token: ");
	strcat(sendBuf, TOKEN);
	strcat(sendBuf, "\r\nUser-Agent: Webclient\r\nAccept:*/*\r\n\r\n");
	iResult = send(sdkSocket, sendBuf, strlen(sendBuf), 0);


	printf(sendBuf);

	do {

		iResult = recv(sdkSocket, (char*)recv_buf + readBytes, buflen - readBytes, 0);
		if (iResult > 0) {
			readBytes = readBytes + iResult;

		}

	} while (iResult > 0);
	recv_buf[readBytes] = '\0';
	delete[] sendBuf;
	closesocket(sdkSocket);
	return readBytes;

};
int httpsRequestExtern(char* domain, char* path, char* recv, int mode) {


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
	int buflen = EXTRA;
	int readBytes = 0;

	//vps426791.ovh.net

	SSL_load_error_strings();
	SSL_library_init();
	OpenSSL_add_all_algorithms();

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) { wprintf(L"WSAStartup() failed with error: %d\n", iResult);  return -1; }


	remoteHost = gethostbyname(domain);
	if (remoteHost == nullptr) {
		dwError = WSAGetLastError(); if (dwError != 0) {
			if (dwError == WSAHOST_NOT_FOUND) { std::printf("Host not found\n");  WSACleanup(); return -1; }
			else if (dwError == WSANO_DATA) { std::printf("No data record found\n");  WSACleanup(); return -1; }
			else {
				printf("Function failed with error: %ld\n", dwError);
				return -1;
			}
		}
	}

	sdkSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sdkSocket == INVALID_SOCKET) { wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());   WSACleanup();  return -1; }
	sdkService.sin_family = AF_INET;
	sdkService.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list));
	sdkService.sin_port = htons(443);
	iResult = connect(sdkSocket, (SOCKADDR *)& sdkService, sizeof(sdkService));

	if (iResult == SOCKET_ERROR) {
		wprintf(L"connect function failed with error: %ld\n", WSAGetLastError()); iResult = closesocket(sdkSocket);
		if (iResult == SOCKET_ERROR) wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());  WSACleanup();
		return -1;
	}
	ctx = SSL_CTX_new(SSLv23_client_method()); ssl = SSL_new(ctx);
	if (!ssl) {
		wprintf(L"SSL creation error\n"); iResult = closesocket(sdkSocket); if (iResult == SOCKET_ERROR) wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
		WSACleanup(); return -1;
	}
	SSL_set_fd(ssl, sdkSocket);
	iResult = SSL_connect(ssl);
	if (!iResult) {
		wprintf(L"SSL connect error\nretval: %d\n", iResult); iResult = closesocket(sdkSocket);
		if (iResult == SOCKET_ERROR) { SSL_CTX_free(ctx);  wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError()); WSACleanup(); return -1; }
		iResult = SSL_get_error(ssl, iResult); wprintf(L"SSL error: %d\n", iResult);  return -1;
	}


	sendBuf = new char[1024];
	if (mode == 0)std::strcpy(sendBuf, "GET ");
	else if (mode == 1)std::strcpy(sendBuf, "POST ");
	else if (mode == 2)std::strcpy(sendBuf, "PUT ");
	else if (mode == 3)std::strcpy(sendBuf, "DELETE ");
	else std::strcpy(sendBuf, "GET ");
	strcat(sendBuf, path);
	strcat(sendBuf, " HTTP/1.0\nHost: ");
	strcat(sendBuf, domain);
	strcat(sendBuf, "\r\nUser-Agent: Webclient\r\nAccept:*/*\r\n\r\n");
	iResult = SSL_write(ssl, sendBuf, strlen(sendBuf));


	do {

		iResult = SSL_read(ssl, (char*)recv + readBytes, buflen - readBytes);
		if (iResult > 0) {
			readBytes = readBytes + iResult;

		}

	} while (iResult > 0);
	recv[readBytes] = '\0';

	delete[] sendBuf;
	closesocket(sdkSocket);
	SSL_shutdown(ssl);
	SSL_free(ssl);
	SSL_CTX_free(ctx);

	WSACleanup();

	return readBytes;

};
uint64_t now_microseconds(void)
{
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	return (((uint64_t)ft.dwHighDateTime << 32) | (uint64_t)ft.dwLowDateTime)
		/ 10;
}
/*void microsleep(int usec)
{
Sleep(usec / 1000);
}*/
void die(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
	exit(1);
}
int die_on_error(int x, char const *context)
{
	if (x < 0) {
		fprintf(stderr, "%s: %s\n", context, amqp_error_string2(x));
		return -1;
		//exit(1);
	}

	return 0;
}
int die_on_amqp_error(amqp_rpc_reply_t x, char const *context)
{
	switch (x.reply_type) {
	case AMQP_RESPONSE_NORMAL:
		return 0;

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

	return -1;
	//exit(1);
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
	int run_count = run_num;
	run_num++;
	uint64_t start_time = now_microseconds();
	int received = 0;
	int previous_received = 0;
	uint64_t previous_report_time = start_time;
	uint64_t next_summary_time = start_time + SUMMARY_EVERY_US;
	amqp_frame_t frame;	uint64_t now;
	//printf("run_count=%d timestamp=%I64d\r\n", run_count, timestamp());
	//thread_timestamp = timestamp();

	for (;;) {
		amqp_rpc_reply_t ret;
		amqp_envelope_t envelope;
		now = now_microseconds();
		if (now > next_summary_time) {
			int countOverInterval = received - previous_received;
			double intervalRate = countOverInterval / ((now - previous_report_time) / 1000000.0);
			//printf("%d ms: Received %d - %d since last report (%d Hz)\n",(int)(now - start_time) / 1000, received, countOverInterval, (int)intervalRate);

			previous_received = received;
			previous_report_time = now;
			next_summary_time += SUMMARY_EVERY_US;
		}

		amqp_maybe_release_buffers(conn);
		ret = amqp_consume_message(conn, &envelope, nullptr, 0);

		//printf("run_count=%d +timestamp=%I64d\r\n", run_count, timestamp());

		if (envelope.message.body.len == 0) return;
		if (run_num > run_count + 1) return;

		memcpy(AMQP_message[rabbit_index%AMQP_QUEUE], envelope.message.body.bytes, envelope.message.body.len);
		if (envelope.message.body.len >= AMQP_BUFLEN) std::printf("ERROR rabbit!envelope.message.body.len=%d\r\n", envelope.message.body.len);
		AMQP_message[rabbit_index%AMQP_QUEUE][envelope.message.body.len] = 0;
		rabbit_index++;


		//printf("rabbit_index=%d\r\n", rabbit_index);
		//printf("run 4\r\n");

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
	amqp_connection_state_t conn;
	//amqp_connection_state_t conn;
	amqp_socket_t *socket;
	char const *hostname;
	int port, status;
	char const *exchange;
	char *bindingkey;
	amqp_bytes_t queuename;


	/*	if (argc < 3) {
	fprintf(stderr, "Usage: amqps_consumer host port "
	"[cacert.pem [verifypeer] [verifyhostname] [key.pem cert.pem]]\n");
	return 1;
	}*/


	if (REPLAY == 0) hostname = "mq.betradar.com";// argv[1];
	else hostname = "replaymq.betradar.com";// argv[1];
	port = 5671;//atoi(argv[2]);
	exchange = "unifiedfeed";// "amq.direct"; /* argv[3]; */
	bindingkey = "#"; /* argv[4]; */
	conn = amqp_new_connection();
	socket = amqp_ssl_socket_new(conn);
	if (!socket) {
		printf("Error creating SSL/TLS socket rabbitmqssl()");
		return;
		//die("creating SSL/TLS socket");
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
		printf("Error opening SSL / TLS connection rabbitmqssl()");
		return;
		//die("opening SSL/TLS connection");
	}

	if (die_on_amqp_error(amqp_login(conn, UOF_URL, 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, TOKEN, ""),
		"Logging in") == -1) return;



	amqp_channel_open(conn, 1);

	if (die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel") == -1) return;

	{
		amqp_queue_declare_ok_t *r = amqp_queue_declare(conn, 1, amqp_empty_bytes, 0, 0, 0, 1,
			amqp_empty_table);
		die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring queue");
		queuename = amqp_bytes_malloc_dup(r->queue);

		//printf("%d", queuename.len);

		if (queuename.bytes == nullptr) {
			fprintf(stderr, "Out of memory while copying queue name");
			return;
		}
	}

	amqp_queue_bind(conn, 1, queuename, amqp_cstring_bytes(exchange), amqp_cstring_bytes(bindingkey),
		amqp_empty_table);
	if (die_on_amqp_error(amqp_get_rpc_reply(conn), "Binding queue") == -1) return;

	amqp_basic_consume(conn, 1, queuename, amqp_empty_bytes, 0, 1, 0, amqp_empty_table);
	if (die_on_amqp_error(amqp_get_rpc_reply(conn), "Consuming") == -1) return;

	run(conn);

	//die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel rabbitmqssl");
	//die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection rabbitmqssl");
	die_on_error(amqp_destroy_connection(conn), "Ending connection");

	return;
}
static void send_batch(amqp_connection_state_t conn, char const *queue_name, int rate_limit, int message_count)
{
	uint64_t start_time = now_microseconds();
	int i;
	int sent = 0;
	int previous_sent = 0;
	uint64_t previous_report_time = start_time;
	uint64_t next_summary_time = start_time + SUMMARY_EVERY_US;

	char message[256];
	amqp_bytes_t message_bytes;

	for (i = 0; i < (int)sizeof(message); i++) {
		message[i] = i & 0xff;
	}

	message_bytes.len = sizeof(message);
	message_bytes.bytes = message;

	for (i = 0; i < message_count; i++) {
		uint64_t now = now_microseconds();

		die_on_error(amqp_basic_publish(conn,
			1,
			amqp_cstring_bytes("amq.direct"),
			amqp_cstring_bytes(queue_name),
			0,
			0,
			nullptr,
			message_bytes),
			"Publishing");
		sent++;
		if (now > next_summary_time) {
			int countOverInterval = sent - previous_sent;
			double intervalRate = countOverInterval / ((now - previous_report_time) / 1000000.0);
			printf("%d ms: Sent %d - %d since last report (%d Hz)\n",
				(int)(now - start_time) / 1000, sent, countOverInterval, (int)intervalRate);

			previous_sent = sent;
			previous_report_time = now;
			next_summary_time += SUMMARY_EVERY_US;
		}

		while (((i * 1000000.0) / (now - start_time)) > rate_limit) {
			Sleep(2000);
			now = now_microseconds();
		}
	}

	{
		uint64_t stop_time = now_microseconds();
		int total_delta = (int)(stop_time - start_time);

		printf("PRODUCER - Message count: %d\n", message_count);
		printf("Total time, milliseconds: %d\n", total_delta / 1000);
		printf("Overall messages-per-second: %g\n", (message_count / (total_delta / 1000000.0)));
	}
}
static void run_mts()
{//char const *exchangetype[] = { "fanout","topic","topic" ,"topic" ,"topic" };
	char const *hostname;
	int port, status;
	int run_mts_num_consume = run_mts_num % 10;
	string queuename[] = { "-Submit-Node", "-Control-Node", "-Confirm-Node", "-Reply-Node", "-Ack" };
	for (int i = 0; i < 4; i++) if (i < 3)	queuename[i] = MTS_NAME + queuename[i] + to_string(run_mts_num_consume);
	else queuename[i] = MTS_NAME + queuename[i];

	amqp_socket_t *socket;
	amqp_connection_state_t conn;
	string  routingkey[5];
	routingkey[0] = "Node" + to_string(run_mts_num_consume) + ".ticket.confirm";
	routingkey[1] = "ack.ticket";
	routingkey[2] = "Node" + to_string(run_mts_num_consume) + ".cancel.confirm";
	routingkey[3] = "cancel";
	routingkey[4] = "ack.cancel";
	amqp_bytes_t amqp_queuename;
	amqp_bytes_t amqp_queuename_cancel;
	string exchange[] = { "-Submit", "-Control", "-Confirm", "-Reply", "-Ack" };
	for (int i = 0; i < 5; i++) exchange[i] = MTS_NAME + exchange[i];



	wsClient* wsclient = nullptr;
	vector<int> clientIDs;
	char* publish_buf = new char[8192];
	char* time_buf = new char[65];

	hostname = MTS_HOSTNAME;// argv[1];
	port = 5671;//atoi(argv[2]);

	conn = amqp_new_connection();
	socket = amqp_ssl_socket_new(conn);
	if (!socket) {
		printf("Error creating SSL/TLS socket rabbitmqssl_mts()");
		mts_error[run_mts_num_consume] = 1;
		return;
		//die("creating SSL/TLS socket");
	}
	amqp_ssl_socket_set_verify_peer(socket, 0);
	amqp_ssl_socket_set_verify_hostname(socket, 0);


	status = amqp_socket_open(socket, hostname, port);



	if (status) {
		printf("Error opening SSL / TLS connection rabbitmqssl_mts()");
		mts_error[run_mts_num_consume] = 1;
		return;
		//die("opening SSL/TLS connection");

	}



	if (die_on_amqp_error(amqp_login(conn, MTS_URL, 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, MTS_NAME, MTS_TOKEN),
		"Logging in") == -1) {
		mts_error[run_mts_num_consume] = 1; return;
	}


	amqp_channel_open(conn, 1);
	amqp_confirm_select(conn, 1);

	amqp_channel_open(conn, 2);
	amqp_confirm_select(conn, 2);

	if (die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel") == -1) {
		mts_error[run_mts_num_consume] = 1; return;
	}

	/*for (int i = 0; i < 5; i++) {
	amqp_exchange_declare(conn, 1, amqp_cstring_bytes(exchange[i]), amqp_cstring_bytes(exchangetype[i]),
	0, 1, 0, 0, amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring exchange");
	}
	*/


	amqp_queue_declare_ok_t *r = amqp_queue_declare(conn, 2, amqp_cstring_bytes(queuename[2].c_str()), 0, 1, 0, 1,
		amqp_empty_table);
	if (die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring queue") == -1) {
		mts_error[run_mts_num_consume] = 1; return;
	}
	amqp_queuename = amqp_bytes_malloc_dup(r->queue);

	//printf((char*)queuename.bytes);



	if (amqp_queuename.bytes == nullptr) {
		fprintf(stderr, "Out of memory while copying queue name");
		mts_error[run_mts_num_consume] = 1;
		return;
	}


	amqp_queue_bind(conn, 2,
		amqp_cstring_bytes(queuename[2].c_str()),
		amqp_cstring_bytes(exchange[2].c_str()),
		amqp_cstring_bytes(routingkey[0].c_str()),
		amqp_empty_table);
	if (die_on_amqp_error(amqp_get_rpc_reply(conn), "Binding queue") == -1) {
		mts_error[run_mts_num_consume] = 1; return;
	}


	amqp_queue_declare_ok_t *rc = amqp_queue_declare(conn, 1, amqp_cstring_bytes(queuename[3].c_str()), 0, 1, 0, 1,
		amqp_empty_table);
	if (die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring queue") == -1) {
		mts_error[run_mts_num_consume] = 1; return;
	}
	amqp_queuename_cancel = amqp_bytes_malloc_dup(rc->queue);
	//printf((char*)queuename.bytes);



	if (amqp_queuename_cancel.bytes == nullptr) {
		fprintf(stderr, "Out of memory while copying queue name");
		mts_error[run_mts_num_consume] = 1;
		return;
	}


	amqp_queue_bind(conn, 1,
		amqp_cstring_bytes(queuename[3].c_str()),
		amqp_cstring_bytes(exchange[3].c_str()),
		amqp_cstring_bytes(routingkey[2].c_str()),
		amqp_empty_table);
	if (die_on_amqp_error(amqp_get_rpc_reply(conn), "Binding queue") == -1) {
		mts_error[run_mts_num_consume] = 1; return;
	}





	/*



	amqp_queue_unbind(conn, 1,
	amqp_cstring_bytes(queue),
	amqp_cstring_bytes(exchange),
	amqp_cstring_bytes(bindingkey),
	amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Unbinding");



	die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel");

	{
	amqp_queue_declare_ok_t *r = amqp_queue_declare(conn, 1, amqp_empty_bytes, 0, 0, 0, 1,
	amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring queue");
	queuename = amqp_bytes_malloc_dup(r->queue);



	if (queuename.bytes == nullptr) {
	fprintf(stderr, "Out of memory while copying queue name");
	return;
	}
	}
	*/

	/*	amqp_queue_bind(conn, 1, queuename, amqp_cstring_bytes(exchange[0]), amqp_cstring_bytes(bindingkey),
	amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Binding queue");
	*/

	amqp_basic_consume(conn, 2, amqp_cstring_bytes(queuename[2].c_str()), amqp_empty_bytes, 0, 0, 0, amqp_empty_table);  //0,1,0 no_ack
	if (die_on_amqp_error(amqp_get_rpc_reply(conn), "Consuming") == 1) {
		mts_error[run_mts_num_consume] = 1; return;
	}

	amqp_basic_consume(conn, 1, amqp_cstring_bytes(queuename[3].c_str()), amqp_empty_bytes, 0, 0, 0, amqp_empty_table);  //0,1,0 no_ack
	if (die_on_amqp_error(amqp_get_rpc_reply(conn), "Consuming") == 1) {
		mts_error[run_mts_num_consume] = 1; return;
	}

	//std:printf("run_mts\r\n");
	uint64_t start_time = now_microseconds();
	int received = 0;
	int previous_received = 0;
	uint64_t previous_report_time = start_time;
	uint64_t next_summary_time = start_time + SUMMARY_EVERY_US;
	amqp_frame_t frame;	uint64_t now;
	int res;
	using namespace rapidjson;
	Document document;
	char* document_message = new char[SMALL];
	char* acknowledgment = new char[SMALL];
	char* int_buf = new char[65];
	struct timeval timeout;
	timeout.tv_sec = 10;
	timeout.tv_usec = 0;

	int mts_count = 0;
	int heartbeat = time(nullptr);
	mts_disconnect++;

	for (;;) {


		/*
		if (recovery_state == 0) {

		clientIDs.clear();
		clientIDs = server.getClientIDs();

		for (int i = 0; i < clientIDs.size(); i++) {
		if (run_mts_num_consume != run_mts_num % 10)  break;
		if (mts_error[run_mts_num_consume] == 1)  break;

		if (server.wsClients[clientIDs[i]] == nullptr || server.wsClients[clientIDs[i]]->timestamp > 0)  continue;
		wsclient = server.wsClients[clientIDs[i]];

		if (wsclient->mts_process == 2 && wsclient->ticket_process == true && time(nullptr) - wsclient->tickets[0]->timestamp / 1000 > 15) {
		for (int j = 0; j < wsclient->tickets_number; j++) {
		Ticket* ticket = wsclient->tickets[j];
		if (ticket->accept_code < 0) continue;
		amqp_basic_properties_t props;
		props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG | AMQP_BASIC_HEADERS_FLAG;// | AMQP_BASIC_REPLY_TO_FLAG;
		props.content_type = amqp_cstring_bytes("application/json");
		//props.reply_to = amqp_bytes_malloc_dup(reply_to_queue);

		//props.headers = "replyRoutingKey:\"Node3.ticket.confirm\"";
		//amqp_table_t *table = &props.headers;
		//props.headers.num_entries = 1;
		//props.headers.entries = calloc(props.headers.num_entries, sizeof(amqp_table_entry_t));
		amqp_table_entry_t entries[1];
		amqp_table_t table;


		entries[0].key = amqp_cstring_bytes("replyRoutingKey");
		entries[0].value.kind = AMQP_FIELD_KIND_UTF8;
		entries[0].value.value.bytes = amqp_cstring_bytes(routingkey[2].c_str());
		table.num_entries = 1;
		table.entries = entries;

		qsort(table.entries, table.num_entries, sizeof(amqp_table_entry_t),
		&amqp_table_entry_cmp);
		props.headers = table;

		//amqp_cstring_bytes("replyRoutingKey:\"Node3.ticket.confirm\"");
		props.delivery_mode = 1; // persistent delivery mode

		_i64toa(timestamp(), time_buf, 10);
		strcpy(publish_buf, "{ \"timestampUtc\": ");
		strcat(publish_buf, time_buf);
		strcat(publish_buf, ", \"ticketId\" :\"");
		strcat(publish_buf, ticket->mts_id.c_str());
		strcat(publish_buf, "\", sender\": { \"bookmakerId\": 19751 }, \"code\": 102, \"version\": \"2.1\" }");

		printf(publish_buf);


		if (die_on_error(amqp_basic_publish(conn, 1, amqp_cstring_bytes(exchange[1]), amqp_cstring_bytes("cancel"), 0, 0, &props, amqp_cstring_bytes(publish_buf)), "Publishing") == -1) { mts_error[run_mts_num_consume] = 1; break; }
		ticket->accept_code = -102;
		}

		wsclient->mts_process = 3;
		}

		if (mts_error[run_mts_num_consume] == 1)  break;




		}

		}
		*/
		amqp_frame_t hb;
		hb.channel = 0;
		hb.frame_type = AMQP_FRAME_HEARTBEAT;

		if (time(nullptr) - heartbeat > 30) {
			heartbeat = time(nullptr);
			int err;
			if ((err = amqp_send_frame(conn, &hb)))
			{
				const char* errstr = amqp_error_string(err);
				printf("Error read thread is: %s %d\n", errstr, err);
				mts_error[run_mts_num_consume] = 1;
				break;
			}
			//printf("Heartbeat read thread sent\n");
		}


		amqp_rpc_reply_t ret;
		amqp_envelope_t envelope;
		now = now_microseconds();
		if (now > next_summary_time) {
			int countOverInterval = received - previous_received;
			double intervalRate = countOverInterval / ((now - previous_report_time) / 1000000.0);
			//printf("%d ms: Received %d - %d since last report (%d Hz)\n",(int)(now - start_time) / 1000, received, countOverInterval, (int)intervalRate);

			previous_received = received;
			previous_report_time = now;
			next_summary_time += SUMMARY_EVERY_US;
		}


		amqp_maybe_release_buffers(conn);
		ret = amqp_consume_message(conn, &envelope, &timeout, 0);
		//ret = amqp_consume_message(conn, &envelope, nullptr, 0);
		if (mts_error[run_mts_num_consume] == 1) break;
		if (run_mts_num_consume != run_mts_num % 10) break;


		//	printf("Delivery %u, exchange %.*s routingkey %.*s\n", (unsigned)envelope.delivery_tag, 	(int)envelope.exchange.len, (char *)envelope.exchange.bytes,(int)envelope.routing_key.len, (char *)envelope.routing_key.bytes);



		if (ret.reply.id == AMQP_BASIC_GET_OK_METHOD)
		{
			amqp_basic_get_ok_t * d = (amqp_basic_get_ok_t *)
				ret.reply.decoded;
			//	printf("Message of type %s on queue %s delivery tag %ld.\n", (char *) d->routing_key.bytes, queuename, d->delivery_tag);
		}



		if (envelope.message.properties._flags & AMQP_BASIC_CONTENT_TYPE_FLAG) {
			//printf("Content-type: %.*s\n",	(int)envelope.message.properties.content_type.len, (char *)envelope.message.properties.content_type.bytes);
		}
		//printf("\n");
		if (envelope.message.body.len > 0) {
			//((char*)envelope.message.body.bytes)[envelope.message.body.len] = 0;
			//printf((char*)envelope.message.body.bytes);
			//	printf("\r\n");

			res = amqp_basic_ack(conn, envelope.channel, envelope.delivery_tag, 0);
			if (AMQP_STATUS_OK != res) {
				fprintf(stderr, "Failed ack: %s\n", amqp_error_string2(res));
			}



			if (envelope.channel == 2) {
				strncpy(document_message, ((char*)envelope.message.body.bytes), envelope.message.body.len);
				document_message[envelope.message.body.len] = 0;
				//	printf(document_message);
				//	printf("\r\n");
				//		printf("\r\n");
				document.Clear();
				document.Parse(document_message);
				if (document.HasParseError()) { printf("error parse json envelope\r\n"); continue; }
				if (document.IsObject() == 0) { printf("error parse json envelope\r\n"); continue; }

				if (document.HasMember("result") == 0) { printf("error parse json envelope.  result member not found\r\n"); continue; }
				if (document["result"].IsObject() == 0 || document["result"].HasMember("ticketId") == 0 || document["result"]["ticketId"].IsString() == 0 || document["result"].HasMember("status") == 0) { printf("error parse json envelope.  ticketIdt member \r\n"); continue; }


				string ticketid = document["result"]["ticketId"].GetString();
				string ticket_status = document["result"]["status"].GetString();

				int p1 = ticketid.find("s");
				int p2 = ticketid.find("r");
				int socket = atoi(ticketid.substr(p1 + 1, p2 - p1).c_str());
				if (server.socketIDmap.find(socket) == server.socketIDmap.end()) { printf("mts ticketid not found in socket map \r\n"); continue; }
				wsClient* wsclient = server.wsClients[server.socketIDmap[socket]];
				if (wsclient->mts_process == 3 || wsclient->mts_process == 0) { printf("errer response to wsclient->mts_process=%d\r\n", wsclient->mts_process); continue; }
				int change_mts_process_status = 0;
				for (int i = 0; i < wsclient->tickets_number; i++) {
					int alternative_process = 0;
					Ticket* ticket = wsclient->tickets[i];
					//if (ticket->alternative_stake > 0) alternative = true;
					if (time(nullptr) - ticket->timestamp / 1000 > 10) { change_mts_process_status++; continue; }
					if (ticket->accept_code < 0) continue;
					if (ticket->mts == 1) continue;

					if (ticket->mts_id == ticketid) {

						if (document["result"].HasMember("reason") == 0 || document["result"]["reason"].HasMember("message") == 0 || document["result"]["reason"].HasMember("code") == 0)
						{
							printf("error parse ticket response\r\n");
							ticket->accept_code = -10;
							ticket->alternative_count = 0;

						}
						else {
							string message = document["result"]["reason"]["message"].GetString();
							//int accept_code = document["result"]["reason"]["code"].GetInt();
							if (ticket->mts_message != nullptr) delete[] ticket->mts_message;
							ticket->mts_message = new char[message.length() + 1];
							strcpy(ticket->mts_message, message.c_str());


							if (ticket->alternative == true && ticket->alternative_count < 4 && document["result"].HasMember("betDetails") != 0 && document["result"]["betDetails"].IsArray() != 0 && document["result"]["betDetails"].GetArray().Size() > 0 && document["result"]["betDetails"].GetArray()[0].HasMember("alternativeStake") != 0 && document["result"]["betDetails"].GetArray()[0]["alternativeStake"].HasMember("stake") != 0)
							{

								ticket->alternative_stake = document["result"]["betDetails"].GetArray()[0]["alternativeStake"]["stake"].GetInt();
								ticket->alternative_count++;
								ticket->mts = 0;
								ticket->accept_code = 0;
								alternative_process = 1;
								change_mts_process_status++;


							}
							else if (ticket->alternative == true && ticket->alternative_count < 4 && document["result"].HasMember("betDetails") != 0 && document["result"]["betDetails"].IsArray() != 0 && document["result"]["betDetails"].GetArray().Size() > 0 && document["result"]["betDetails"].GetArray()[0].HasMember("reoffer") != 0 && document["result"]["betDetails"].GetArray()[0]["reoffer"].HasMember("stake") != 0)
							{

								ticket->alternative_stake = document["result"]["betDetails"].GetArray()[0]["reoffer"]["stake"].GetInt();
								ticket->alternative_count++;
								alternative_process = 2;
								ticket->mts = 0;
								ticket->accept_code = 0;
								change_mts_process_status++;


							}

							else {

								ticket->accept_code = document["result"]["reason"]["code"].GetInt();
								if (ticket->accept_code != 1024 && ticket->accept_code > 0) ticket->accept_code = -ticket->accept_code;
								if (ticket->accept_code == 0) ticket->accept_code = -10;

								ticket->mts = 1;
								ticket->alternative_count = 0;
							}



							amqp_basic_properties_t props;
							props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;// | AMQP_BASIC_HEADERS_FLAG;// | AMQP_BASIC_REPLY_TO_FLAG;
							props.content_type = amqp_cstring_bytes("application/json");
							props.delivery_mode = 1;

							strcpy(acknowledgment, " { \"sender\": { \"bookmakerId\": ");
							_itoa(BOOKMAKERID, int_buf, 10);
							strcat(acknowledgment, int_buf);
							strcat(acknowledgment, " }, \"ticketId\": \"");
							strcat(acknowledgment, ticketid.c_str());
							strcat(acknowledgment, "\", \"ticketStatus\": \"");
							strcat(acknowledgment, ticket_status.c_str());
							strcat(acknowledgment, "\", \"code\": 830, \"message\": \"\", \"timestampUtc\": ");
							_i64toa(timestamp(), int_buf, 10);
							strcat(acknowledgment, int_buf);
							strcat(acknowledgment, ", \"version\": \"2.1\"}");

							//printf("acknowledgment = %s\r\n", acknowledgment);


							if (die_on_error(amqp_basic_publish(conn, 2, amqp_cstring_bytes(exchange[4].c_str()), amqp_cstring_bytes(routingkey[1].c_str()), 0, 0, &props, amqp_cstring_bytes(acknowledgment)), "Publishing") == -1) {

								mts_error[run_mts_num_consume] = 1;
								die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
								die_on_amqp_error(amqp_channel_close(conn, 2, AMQP_REPLY_SUCCESS), "Closing channel");
								die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
								die_on_error(amqp_destroy_connection(conn), "Ending connection");
								delete[] acknowledgment;
								delete[] int_buf;
								printf("acknowledgment publish error\r\n");
								return;
							}


							if (alternative_process > 0) ticket->alternative_process = alternative_process;
						}
						continue;
					}

					change_mts_process_status++;
				}



				if (change_mts_process_status == 0) {
					wsclient->mts_process = 3;
				}

				//printf("wsclient->mts_process=%d \r\n", wsclient->mts_process);

			}
			if (envelope.channel == 1) {
				strncpy(document_message, ((char*)envelope.message.body.bytes), envelope.message.body.len);
				document_message[envelope.message.body.len] = 0;
				document.Clear();
				document.Parse(document_message);
				if (document.HasParseError()) { printf("error parse json envelope\r\n"); continue; }
				if (document.IsObject() == 0) { printf("error parse json envelope\r\n"); continue; }
				if (document.HasMember("result") == 0) { printf("error parse json envelope.  result member not found\r\n"); continue; }
				if (document["result"].IsObject() == 0 || document["result"].HasMember("ticketId") == 0 || document["result"]["ticketId"].IsString() == 0 || document["result"].HasMember("status") == 0) { printf("error parse json envelope.  ticketIdt member \r\n"); continue; }
				string ticketid = document["result"]["ticketId"].GetString();
				string ticket_status = document["result"]["status"].GetString();
				int accept_code = document["result"]["reason"]["code"].GetInt();
				if (accept_code != 1024) {
					if (tickets_oam.find(ticketid) == tickets_oam.end()) printf("error! mts_ticket_cancellation_response has no tickets in oam tickets map\r\n");
					else {
						tickets_contact_oam[tickets_contact_oam_count % MAX_OAM] = tickets_oam[ticketid];
						tickets_contact_oam_count++;
						//processNewTicket(tickets_oam[ticketid]); 


					}
				}

				amqp_basic_properties_t props;
				props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;// | AMQP_BASIC_HEADERS_FLAG;// | AMQP_BASIC_REPLY_TO_FLAG;
				props.content_type = amqp_cstring_bytes("application/json");
				props.delivery_mode = 1;

				strcpy(acknowledgment, " { \"sender\": { \"bookmakerId\": ");
				_itoa(BOOKMAKERID, int_buf, 10);
				strcat(acknowledgment, int_buf);
				strcat(acknowledgment, " }, \"ticketId\": \"");
				strcat(acknowledgment, ticketid.c_str());
				strcat(acknowledgment, "\", \"ticketStatus\": \"");
				//strcat(acknowledgment, ticket_status.c_str());
				if (accept_code == 1024) strcat(acknowledgment, "cancelled"); else  strcat(acknowledgment, "not_cancelled");
				strcat(acknowledgment, "\", \"code\": 830, \"message\": \"\", \"timestampUtc\": ");
				_i64toa(timestamp(), int_buf, 10);
				strcat(acknowledgment, int_buf);
				strcat(acknowledgment, ", \"version\": \"2.1\"}");

				//printf("acknowledgment=%s\r\n", acknowledgment);

				if (die_on_error(amqp_basic_publish(conn, 2, amqp_cstring_bytes(exchange[4].c_str()), amqp_cstring_bytes(routingkey[4].c_str()), 0, 0, &props, amqp_cstring_bytes(acknowledgment)), "Publishing") == -1) {

					mts_error[run_mts_num_consume] = 1;
					die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
					die_on_amqp_error(amqp_channel_close(conn, 2, AMQP_REPLY_SUCCESS), "Closing channel");																						   //if (
					die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
					die_on_error(amqp_destroy_connection(conn), "Ending connection");
					delete[] acknowledgment;
					delete[] int_buf;
					printf("acknowledgment publish error\r\n");
					return;
				}





			}


		}

		if (AMQP_RESPONSE_NORMAL != ret.reply_type) {
			if (AMQP_RESPONSE_LIBRARY_EXCEPTION == ret.reply_type &&
				AMQP_STATUS_UNEXPECTED_STATE == ret.library_error) {
				if (AMQP_STATUS_OK != amqp_simple_wait_frame(conn, &frame)) {
					printf("AMQP_STATUS_OK return\n");
					mts_error[run_mts_num_consume] = 1;
					die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
					die_on_amqp_error(amqp_channel_close(conn, 2, AMQP_REPLY_SUCCESS), "Closing channel");
					die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
					die_on_error(amqp_destroy_connection(conn), "Ending connection");
					delete[] acknowledgment;
					delete[] int_buf;
					return;
				}

				if (AMQP_FRAME_METHOD == frame.frame_type) {
					switch (frame.payload.method.id) {
					case AMQP_BASIC_ACK_METHOD:
						//	printf("AMQP_BASIC_ACK_METHOD\r\n");

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

							printf("AMQP_RESPONSE_NORMAL return\n");
							mts_error[run_mts_num_consume] = 1;
							die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
							die_on_amqp_error(amqp_channel_close(conn, 2, AMQP_REPLY_SUCCESS), "Closing channel");
							die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
							die_on_error(amqp_destroy_connection(conn), "Ending connection");
							delete[] acknowledgment;
							delete[] int_buf;
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

						printf("AMQP_CHANNEL_CLOSE_METHOD return\n");
						//break;
						mts_error[run_mts_num_consume] = 1;
						//if (
						die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
						die_on_amqp_error(amqp_channel_close(conn, 2, AMQP_REPLY_SUCCESS), "Closing channel");
						die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
						die_on_error(amqp_destroy_connection(conn), "Ending connection");
						delete[] acknowledgment;
						delete[] int_buf;
						return;

					case AMQP_CONNECTION_CLOSE_METHOD:
						/* a connection.close method happens when a connection exception occurs,
						* this can happen by trying to use a channel that isn't open for example.
						*
						* In this case the whole connection must be restarted.
						*/
						printf("AMQP_CONNECTION_CLOSE_METHOD return\n");
						mts_error[run_mts_num_consume] = 1;
						die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
						die_on_amqp_error(amqp_channel_close(conn, 2, AMQP_REPLY_SUCCESS), "Closing channel");
						die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
						die_on_error(amqp_destroy_connection(conn), "Ending connection");
						delete[] acknowledgment;
						delete[] int_buf;
						return;

					default:
						fprintf(stderr, "An unexpected method was received %u\n", frame.payload.method.id);

						mts_error[run_mts_num_consume] = 1;

						die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
						die_on_amqp_error(amqp_channel_close(conn, 2, AMQP_REPLY_SUCCESS), "Closing channel");
						die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
						die_on_error(amqp_destroy_connection(conn), "Ending connection");
						delete[] acknowledgment;
						delete[] int_buf;
						return;
					}
				}
			}

		}
		else {
			//printf("amqp_destroy_envelope\r\n");
			amqp_destroy_envelope(&envelope);
			//printf("amqp_destroy_envelope end\r\n");

		}


		received++;
	}


	//if (
	die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
	die_on_amqp_error(amqp_channel_close(conn, 2, AMQP_REPLY_SUCCESS), "Closing channel");
	die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
	die_on_error(amqp_destroy_connection(conn), "Ending connection");
	delete[] acknowledgment;
	delete[] int_buf;
	return;

}
void rabbitmqssl_mts() {
	char const *hostname;
	int port, status;
	//int run_mts_num_consume = run_mts_num % 10;
	int run_mts_num_publish = run_mts_num % 10;
	string queuename[] = { "-Submit-Node", "-Control-Node", "-Confirm-Node", "-Reply-Node", "-Ack" };
	for (int i = 0; i < 4; i++) if (i < 3)	queuename[i] = MTS_NAME + queuename[i] + to_string(run_mts_num_publish);
	else queuename[i] = MTS_NAME + queuename[i];

	amqp_socket_t *socket;
	amqp_connection_state_t conn;
	string  routingkey[5];
	routingkey[0] = "Node" + to_string(run_mts_num_publish) + ".ticket.confirm";
	routingkey[1] = "ack.ticket";
	routingkey[2] = "Node" + to_string(run_mts_num_publish) + ".cancel.confirm";
	routingkey[3] = "cancel";
	routingkey[4] = "ack.cancel";
	string exchange[] = { "-Submit", "-Control", "-Confirm", "-Reply", "-Ack" };
	for (int i = 0; i < 5; i++) exchange[i] = MTS_NAME + exchange[i];



	Client* client = nullptr;
	wsClient* wsclient = nullptr;
	vector<int> clientIDs;
	char* publish_buf = new char[8192];
	char* time_buf = new char[65];

	hostname = MTS_HOSTNAME; // argv[1];
	port = 5671;//atoi(argv[2]);

	conn = amqp_new_connection();
	socket = amqp_ssl_socket_new(conn);
	if (!socket) {
		printf("Error creating SSL/TLS socket rabbitmqssl_mts()");
		mts_error[run_mts_num_publish] = 1;
		return;
		//die("creating SSL/TLS socket");
	}
	amqp_ssl_socket_set_verify_peer(socket, 0);
	amqp_ssl_socket_set_verify_hostname(socket, 0);


	status = amqp_socket_open(socket, hostname, port);



	if (status) {
		printf("Error opening SSL / TLS connection rabbitmqssl_mts()");
		mts_error[run_mts_num_publish] = 1;
		return;
		//die("opening SSL/TLS connection");

	}



	if (die_on_amqp_error(amqp_login(conn, MTS_URL, 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, MTS_NAME, MTS_TOKEN),
		"Logging in") == -1) {
		mts_error[run_mts_num_publish] = 1;
		return;
	}


	amqp_channel_open(conn, 1);
	amqp_confirm_select(conn, 1);


	if (die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel") == -1) { mts_error[run_mts_num_publish] = 1; return; }

	/*for (int i = 0; i < 5; i++) {
	amqp_exchange_declare(conn, 1, amqp_cstring_bytes(exchange[i]), amqp_cstring_bytes(exchangetype[i]),
	0, 1, 0, 0, amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring exchange");
	}
	*/

	/*
	amqp_queue_declare_ok_t *r = amqp_queue_declare(conn, 1, amqp_cstring_bytes(queuename[2]), 0, 1, 0, 0,
	amqp_empty_table);
	if (die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring queue") ==-1) return;
	amqp_queuename = amqp_bytes_malloc_dup(r->queue);
	//printf((char*)queuename.bytes);



	if (amqp_queuename.bytes == nullptr) {
	fprintf(stderr, "Out of memory while copying queue name");
	return;
	}


	amqp_queue_bind(conn, 1,
	amqp_cstring_bytes(queuename[2]),
	amqp_cstring_bytes(exchange[2]),
	amqp_cstring_bytes(bindingkey),
	amqp_empty_table);
	if (die_on_amqp_error(amqp_get_rpc_reply(conn), "Binding queue") == -1) return;

	*/



	/*



	amqp_queue_unbind(conn, 1,
	amqp_cstring_bytes(queue),
	amqp_cstring_bytes(exchange),
	amqp_cstring_bytes(bindingkey),
	amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Unbinding");



	die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel");

	{
	amqp_queue_declare_ok_t *r = amqp_queue_declare(conn, 1, amqp_empty_bytes, 0, 0, 0, 1,
	amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring queue");
	queuename = amqp_bytes_malloc_dup(r->queue);



	if (queuename.bytes == nullptr) {
	fprintf(stderr, "Out of memory while copying queue name");
	return;
	}
	}
	*/

	/*	amqp_queue_bind(conn, 1, queuename, amqp_cstring_bytes(exchange[0]), amqp_cstring_bytes(bindingkey),
	amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Binding queue");
	*/

	//	amqp_basic_consume(conn, 1, amqp_cstring_bytes(queuename[2]), amqp_empty_bytes, 0, 0, 0, amqp_empty_table);  //0,1,0 no_ack
	//	if(die_on_amqp_error(amqp_get_rpc_reply(conn), "Consuming") == 1) return;


	int mts_count = 0;
	int heartbeat = time(nullptr);
	mts_disconnect++;
	for (;;) {

		amqp_frame_t hb;
		hb.channel = 0;
		hb.frame_type = AMQP_FRAME_HEARTBEAT;

		if (time(nullptr) - heartbeat > 30) {
			heartbeat = time(nullptr);
			int err;
			if ((err = amqp_send_frame(conn, &hb)))
			{
				const char* errstr = amqp_error_string(err);
				printf("Error send thread is: %s %d\n", errstr, err);
				mts_error[run_mts_num_publish] = 1;
				break;
			}
			//printf("Heartbeat send thread sent\n");
		}

		//amqp_get_heartbeat(amqp_connection_state_t state);

		if (recovery_state == 0) {

			clientIDs.clear();
			clientIDs = server.getClientIDs();


			for (int i = 0; i < clientIDs.size(); i++) {
				if (run_mts_num_publish != run_mts_num % 10)  break;
				if (mts_error[run_mts_num_publish] == 1)  break;

				if (server.wsClients[clientIDs[i]] == nullptr || server.wsClients[clientIDs[i]]->timestamp > 0)  continue;
				wsclient = server.wsClients[clientIDs[i]];
				if (wsclient->mts_process == 1 && wsclient->ticket_process == true) {
					for (int j = 0; j < wsclient->tickets_number; j++) {
						Ticket* ticket = wsclient->tickets[j];
						string alternative_mts_id;
						if (ticket->accept_code < 0) continue;
						if (ticket->mts == 1) continue;
						if (wsclient->mts_send_process == 1 && ticket->alternative_process == 0) continue;
						if (ticket->alternative_process > 0) {
							alternative_mts_id = ticket->mts_id;
							ticket->stake = (double)(ticket->alternative_stake) / 10000;
							ticket->alternative_stake = 0;
							ticket->timestamp = timestamp();
							ticket->generateId(wsclient->socket, USER, j);

						}

						amqp_basic_properties_t props;
						props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG | AMQP_BASIC_HEADERS_FLAG;// | AMQP_BASIC_REPLY_TO_FLAG;
						props.content_type = amqp_cstring_bytes("application/json");
						//props.reply_to = amqp_bytes_malloc_dup(reply_to_queue);

						//props.headers = "replyRoutingKey:\"Node3.ticket.confirm\"";
						//amqp_table_t *table = &props.headers;
						//props.headers.num_entries = 1;
						//props.headers.entries = calloc(props.headers.num_entries, sizeof(amqp_table_entry_t));
						amqp_table_entry_t entries[1];
						amqp_table_t table;


						entries[0].key = amqp_cstring_bytes("replyRoutingKey");
						entries[0].value.kind = AMQP_FIELD_KIND_UTF8;
						entries[0].value.value.bytes = amqp_cstring_bytes(routingkey[0].c_str());

						table.num_entries = 1;
						table.entries = entries;

						qsort(table.entries, table.num_entries, sizeof(amqp_table_entry_t),
							&amqp_table_entry_cmp);
						props.headers = table;

						//amqp_cstring_bytes("replyRoutingKey:\"Node3.ticket.confirm\"");
						props.delivery_mode = 1; // persistent delivery mode 


						_i64toa(ticket->timestamp, time_buf, 10);
						strcpy(publish_buf, "{ \"version\": \"2.1\", \"timestampUtc\": ");
						strcat(publish_buf, time_buf);
						strcat(publish_buf, ", \"ticketId\": \"");
						strcat(publish_buf, ticket->mts_id.c_str());
						if (ticket->alternative_process == 2) {
							strcat(publish_buf, "\", \"reofferRefId\": \"");
							strcat(publish_buf, alternative_mts_id.c_str());
						}
						if (ticket->alternative_process == 1) {
							strcat(publish_buf, "\", \"altStakeRefId\": \"");
							strcat(publish_buf, alternative_mts_id.c_str());
						}
						strcat(publish_buf, "\", \"sender\": { \"currency\": \"");
						strcat(publish_buf, currency_name[ticket->currency - 1].c_str());
						strcat(publish_buf, "\", \"terminalId\":\"\"");
						strcat(publish_buf, ", \"channel\": \"");
						if (ticket->device == 0) strcat(publish_buf, "internet");
						else strcat(publish_buf, "mobile");
						strcat(publish_buf, "\", \"shopId\": null, \"bookmakerId\": ");
						_itoa(BOOKMAKERID, time_buf, 10);
						strcat(publish_buf, time_buf);
						strcat(publish_buf, ", \"endCustomer\": { \"ip\": \"");
						strcat(publish_buf, ticket->domain.c_str());
						strcat(publish_buf, "\", \"languageId\": \"");
						strcat(publish_buf, lang[ticket->language].c_str());
						strcat(publish_buf, "\", \"deviceId\": \"PC\", \"id\": \"");
						_itoa(wsclient->client_id, time_buf, 10);
						strcat(publish_buf, time_buf);
						strcat(publish_buf, "\", \"confidence\": 10000 }, \"limitId\": 903 }, \"selections\": [");
						for (int l = 0; l < ticket->bets_number; l++) {
							Bet* bet = ticket->bets[l];
							strcat(publish_buf, "{ \"eventId\": ");
							switch (bet->type_radar) {
							case 0://sr:match
								_itoa(bet->event_id, time_buf, 10);
								strcat(publish_buf, time_buf);
								break;
							case 1://sr:race_event
								strcat(publish_buf, "\"sr:stage:");
								_itoa(bet->event_id, time_buf, 10);
								strcat(publish_buf, time_buf);
								strcat(publish_buf, "\"");
								break;
							case 2://sr:simple_tournament
								strcat(publish_buf, "\"sr:simple_tournament:");
								_itoa(bet->simple_id, time_buf, 10);
								strcat(publish_buf, time_buf);
								strcat(publish_buf, "\"");
								break;
							case 3://sr:season
								strcat(publish_buf, "\"sr:season:");
								_itoa(bet->season_id, time_buf, 10);
								strcat(publish_buf, time_buf);
								strcat(publish_buf, "\"");
								break;
							case 4: //sr:race_tournament
								strcat(publish_buf, "\"sr:race_tournament:");
								_itoa(bet->tournament_id, time_buf, 10);
								strcat(publish_buf, time_buf);
								strcat(publish_buf, "\"");
								break;
							}


							if (bet->type < 2 && bet->event_match_status > 0) strcat(publish_buf, ", \"id\": \"uof:1/sr:sport:"); else strcat(publish_buf, ", \"id\": \"uof:3/sr:sport:");
							_itoa(bet->sport_id, time_buf, 10);
							strcat(publish_buf, time_buf);
							strcat(publish_buf, "/");
							_itoa(bet->market_id, time_buf, 10);
							strcat(publish_buf, time_buf);
							strcat(publish_buf, "/");
							switch (bet->type) {
							case 0:
								if (bet->variant > -1) { strcat(publish_buf, bet->specifier_value[bet->variant]); strcat(publish_buf, ":"); }
								break;
							case 1:
								strcat(publish_buf, "sr:player:");
								break;
							case 2:
								strcat(publish_buf, "sr:competitor:");
								break;
							case 3:
								strcat(publish_buf, "pre:outcometext:");
								break;
							case 4:
								if (bet->variant > -1) { strcat(publish_buf, bet->specifier_value[bet->variant]); strcat(publish_buf, ":"); }
								break;



							}

							_itoa(bet->outcome_id[bet->selected_outcome_id], time_buf, 10);
							strcat(publish_buf, time_buf);

							int k = 0;
							for (k = 0; k < bet->specifier_number; k++) {
								if (k == 0)  strcat(publish_buf, "?");  else strcat(publish_buf, "&");
								strcat(publish_buf, bet->specifier[k]);
								strcat(publish_buf, "=");
								strcat(publish_buf, bet->specifier_value[k]);
							}

							if (bet->type_radar < 1 && bet->event_status > 0 && bet->market_id != 215) {
								if (k > 0) strcat(publish_buf, "&$score=");
								else strcat(publish_buf, "?$score=");
								strcat(publish_buf, bet->event_score);
							}

							strcat(publish_buf, "\", \"odds\": ");
							_itoa((int)(bet->accept_odd * 10000 + 0.5), time_buf, 10);
							strcat(publish_buf, time_buf);
							if (l < ticket->bets_number - 1) strcat(publish_buf, "}, ");
							else strcat(publish_buf, " } ");

						}
						strcat(publish_buf, "], \"bets\": [{ \"id\": \"");
						strcat(publish_buf, ticket->mts_id.c_str());
						if (ticket->alternative_process == 2) {
							strcat(publish_buf, "\", \"reofferRefId\": \"");
							strcat(publish_buf, alternative_mts_id.c_str());
						}
						if (ticket->alternative_process == 1) {
							strcat(publish_buf, "\", \"altStakeRefId\": \"");
							strcat(publish_buf, alternative_mts_id.c_str());
						}


						strcat(publish_buf, "\", \"selectionRefs\": [");
						for (int l = 0; l < ticket->bets_number; l++) {
							strcat(publish_buf, "{ \"selectionIndex\": ");
							_itoa(l, time_buf, 10);
							strcat(publish_buf, time_buf);
							strcat(publish_buf, ", \"banker\": false }");
							if (l < ticket->bets_number - 1) strcat(publish_buf, ", ");
						}

						strcat(publish_buf, "], \"selectedSystems\": [");
						if (ticket->type == 1) _itoa(1, time_buf, 10);
						else if (ticket->type == 2) _itoa(ticket->bets_number, time_buf, 10);
						else _itoa(ticket->system_selected, time_buf, 10);
						strcat(publish_buf, time_buf);
						strcat(publish_buf, "], \"stake\": { \"value\": ");


						//snprintf(time_buf, sizeof(time_buf), "%f", ticket->stake);
						//sprintf(time_buf, "%g", ticket->stake);
						_itoa((int)(ticket->stake * 10000 + 0.5), time_buf, 10);


						strcat(publish_buf, time_buf);
						strcat(publish_buf, ", \"type\": \"total\" } }] }");
						//printf(publish_buf);
						//	printf("\r\n");
						//	printf("\r\n");


						/*	HANDLE File = CreateFile(string("C://Betradar//Sports//mts"+ to_string(mts_count)+ ".json").c_str(), GENERIC_WRITE, 0, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
						DWORD l = SetFilePointer(File, 0, 0, FILE_BEGIN);
						//printf(name);
						//printf("\r\n");
						//printf("message length= %d\r\n", strlen(AMQP_message[(process_index-1)%AMQP_QUEUE]));
						WriteFile(File, publish_buf, strlen(publish_buf), &l, nullptr);
						CloseHandle(File);*/

						if (ticket->alternative_process > 0) ticket->alternative_process = 0;

						if (die_on_error(amqp_basic_publish(conn, 1, amqp_cstring_bytes(exchange[0].c_str()), amqp_cstring_bytes(routingkey[0].c_str()), 0, 0, &props, amqp_cstring_bytes(publish_buf)), "Publishing") == -1) { mts_error[run_mts_num_publish] = 1; break; }


						//countsend++;


					}
					if (mts_error[run_mts_num_publish] == 1)  break; else  wsclient->mts_send_process = 1;

				}
				if (wsclient->mts_process == 1 && wsclient->ticket_process == true) {
					int change_mts_process_status = 1;
					for (int j = 0; j < wsclient->tickets_number; j++) {
						Ticket* ticket = wsclient->tickets[j];
						if (ticket->accept_code < 0) continue;
						if (ticket->mts == 1) continue;
						if (time(nullptr) - ticket->timestamp / 1000 < 11) { change_mts_process_status = 2; continue; }
						ticket->accept_code = -102;
						ticket->contact_oam = 1;
						tickets_oam[ticket->mts_id] = ticket;
						if (change_mts_process_status == 1) change_mts_process_status = 0;
						amqp_basic_properties_t props;
						props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG | AMQP_BASIC_HEADERS_FLAG;// | AMQP_BASIC_REPLY_TO_FLAG;
						props.content_type = amqp_cstring_bytes("application/json");
						//props.reply_to = amqp_bytes_malloc_dup(reply_to_queue);

						//props.headers = "replyRoutingKey:\"Node3.ticket.confirm\"";
						//amqp_table_t *table = &props.headers;
						//props.headers.num_entries = 1;
						//props.headers.entries = calloc(props.headers.num_entries, sizeof(amqp_table_entry_t));
						amqp_table_entry_t entries[1];
						amqp_table_t table;


						entries[0].key = amqp_cstring_bytes("replyRoutingKey");
						entries[0].value.kind = AMQP_FIELD_KIND_UTF8;
						entries[0].value.value.bytes = amqp_cstring_bytes(routingkey[2].c_str());
						table.num_entries = 1;
						table.entries = entries;

						qsort(table.entries, table.num_entries, sizeof(amqp_table_entry_t),
							&amqp_table_entry_cmp);
						props.headers = table;

						//amqp_cstring_bytes("replyRoutingKey:\"Node3.ticket.confirm\"");
						props.delivery_mode = 1; // persistent delivery mode 

						_i64toa(timestamp(), time_buf, 10);
						strcpy(publish_buf, "{ \"timestampUtc\": ");
						strcat(publish_buf, time_buf);
						strcat(publish_buf, ", \"ticketId\" :\"");
						strcat(publish_buf, ticket->mts_id.c_str());
						strcat(publish_buf, "\", \"sender\": { \"bookmakerId\": ");
						_itoa(BOOKMAKERID, time_buf, 10);
						strcat(publish_buf, time_buf);
						strcat(publish_buf, " }, \"code\": 102, \"version\": \"2.1\" }");
						//	printf(publish_buf);
						//	printf("\r\n");

						if (die_on_error(amqp_basic_publish(conn, 1, amqp_cstring_bytes(exchange[1].c_str()), amqp_cstring_bytes(routingkey[3].c_str()), 0, 0, &props, amqp_cstring_bytes(publish_buf)), "Publishing") == -1) { mts_error[run_mts_num_publish] = 1; break; }

					}



					if (change_mts_process_status == 0) {
						wsclient->mts_process = 3;
					}
				}

				if (mts_error[run_mts_num_publish] == 1)  break;




			}

		}
		else Sleep(1000);

		if (run_mts_num_publish != run_mts_num % 10)  break;
		if (mts_error[run_mts_num_publish] == 1) break;

	}

	die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
	die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
	die_on_error(amqp_destroy_connection(conn), "Ending connection");

	return;
}


