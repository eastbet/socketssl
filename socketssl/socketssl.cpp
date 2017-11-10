
#define WIN32_LEAN_AND_MEAN
#undef _UNICODE
#undef UNICODE



#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <mutex>
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
#include <amqp_ssl_socket.h>
#include <amqp_framing.h>
#include <unordered_map>
#include <unordered_set>
#include <atomic>

#define ZLIB_WINAPI   // actually actually needed (for linkage)

#pragma comment(lib, "zlibwapi.lib") // for access to the DLL

int GetMaxCompressedLen(int);
int CompressData(const BYTE* , int , BYTE* , int );
int UncompressData(const BYTE* , int , BYTE* , int);
int gzip(char*, int, char* &, int);
int64_t timestamp();






#define WEBSOCKET_H

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


#define WS_STATUS_NORMAL_CLOSE             1000
#define WS_STATUS_GONE_AWAY                1001
#define WS_STATUS_PROTOCOL_ERROR           1002
#define WS_STATUS_UNSUPPORTED_MESSAGE_TYPE 1003
#define WS_STATUS_MESSAGE_TOO_BIG          1004

#define WS_STATUS_TIMEOUT 3000

#define WS_TIMEOUT_RECV 10
#define WS_TIMEOUT_PONG 5
#define CERTF  "/passionbet.crt"
#define KEYF  "/passionbet.key"
#define MAX_PATH 255
#define DEFAULT_BUFLEN 67108864
#define SEND_BUFLEN 16777216
#define MEDIUM_BUFLEN 4096
#define PLAYERS_LENTGH 300000
#define COMPETITORS_LENTGH 150000
#define NAME_LENTGH 127
#define MAX_OUTCOME 500
#define MAX_OUTCOME_NAME 64
#define SPORTS_LENTGH 200
#define BETSTOPS_LENTGH 200
#define MATCHSTATUS_LENTGH 1000
#define TOURNAMENTS_LENTGH 10000
#define EVENTS_LENTGH 100000
#define LINES_LENTGH 10000000
#define CATEGORIES_LENTGH 10000
#define SUMMARY_EVERY_US 1000000
#define MARKETS_LENGTH 3000	
//#define MAX_EVENTS 25000000
#define MAX_EVENTS 20000000
#define MAX_LINES 10000000

#define MAX_TOURNAMENTS 1000000
#define MAX_CATEGORIES 10000
#define MAX_COMPETITORS 1000000
#define MAX_PLAYERS 10000000
#define MAX_SPORTS 1000
#define MAX_MARKETS 10000
#define MAX_MARKETS_IN 2000
#define MAX_BETSTOPS 200
#define MAX_MATCHSTATUS 1000
#define QUEUE_LENGTH 2000
#define STEP_QUEUE 100
#define AMQP_QUEUE 5000
#define AMQP_BUFLEN 131072//;262144;
#pragma pack(push, 8)
//#pragma pack(pop)

HANDLE hThread1;
DWORD dwThreadID1;
DWORD ExitCode1;
DWORD WINAPI BetradarGetThread(LPVOID);

HANDLE hThread2;
DWORD dwThreadID2;
DWORD ExitCode2;
DWORD WINAPI BetradarProcessThread(LPVOID);

HANDLE hThread3;
DWORD dwThreadID3;
DWORD ExitCode3;
DWORD WINAPI MTSGetThread(LPVOID);


HANDLE hThread4;
DWORD dwThreadID4;
DWORD ExitCode4;
DWORD WINAPI startRecoveryThread(LPVOID);


int recovery_state = -1;
void GenerateBigStep();
int* data_step_len_1 = new int[STEP_QUEUE];
int* data_step_len_2 = new int[STEP_QUEUE];
char** array_data_step_1 = new char*[STEP_QUEUE];
char** array_data_step_2 = new char*[STEP_QUEUE]; 
char** AMQP_message = new char* [AMQP_QUEUE];
atomic_int64_t process_index = 0;
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
	std::strcpy(name, rhs.name);
}
Sport::Sport() {
	id = 0;
	sort = 0;
	name = new char[NAME_LENTGH];
};
class Player {
public:
	Player();
	~Player() {
		if (name != NULL) delete[] name; if (full_name != NULL) delete[] full_name; if (type != NULL) delete[] type; if (nationality != NULL) delete[] nationality;
		if (country_code != NULL) delete[] country_code;
	};
	int id;
	char *name;
	int date_of_birth;
	int height;
	int weight;
	char* full_name;
	char* type;
	char* nationality;
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
	if (name != NULL) {
		delete[] name; name = NULL;
	}
	if (rhs.name != NULL) {
		i = strlen(rhs.name) + 1;
		name = new char[i]; std::strcpy(name, rhs.name);
	}


	if (full_name != NULL) {
		delete[] full_name; full_name = NULL;
	}
	if (rhs.full_name != NULL) {
		i = strlen(rhs.full_name) + 1;
		full_name = new char[i]; std::strcpy(full_name, rhs.full_name);
	}


	if (type != NULL) {
		delete[] type; type = NULL;
	}
	if (rhs.type != NULL) {
		i = strlen(rhs.type) + 1;
		type = new char[i]; std::strcpy(type, rhs.type);
	}


	if (nationality != NULL) {
		delete[] nationality; nationality = NULL;
	}
	if (rhs.nationality != NULL) {
		i = strlen(rhs.nationality) + 1;
		nationality = new char[i]; std::strcpy(nationality, rhs.nationality);
	}


	if (country_code != NULL) {
		delete[] country_code; country_code = NULL;
	}
	if (rhs.country_code != NULL) {
		i = strlen(rhs.country_code) + 1;
		country_code = new char[i]; std::strcpy(country_code, rhs.country_code);
	}



}
Player::Player() {
	id = 0;
	name = NULL;
	date_of_birth = 0;
	height = 0;
	weight = 0;
	full_name = NULL;
	type = NULL;
	nationality = NULL;
	country_code = NULL;
	competitor_id = 0;
	manager = 0;
	number = 0;
};
class Competitor {
public:
	Competitor();
	~Competitor() {
		if (name != NULL) delete[] name; if (country_name != NULL) delete[] country_name;
	};
	int id;
	int sport_id;
	int category_id;
	char *name;
	char *country_name;
	int super_id;
	void operator = (const Competitor&);
};
void Competitor:: operator = (const Competitor & rhs) {
	int i = 0;
	if (this == &rhs) return;
	id = rhs.id;
	sport_id = rhs.sport_id;
	if (rhs.super_id != 0) super_id = rhs.super_id;

	category_id = rhs.category_id;
	if (name != NULL) {
		delete[] name; name = NULL;
	}
	if (rhs.name != NULL) {
		i = strlen(rhs.name) + 1;
		name = new char[i]; std::strcpy(name, rhs.name);
	}

	if (country_name != NULL) {
		delete[] country_name; country_name = NULL;
	}
	if (rhs.country_name != NULL) {
		i = strlen(rhs.country_name) + 1;
		country_name = new char[i]; std::strcpy(country_name, rhs.country_name);
	}

}
Competitor::Competitor() {
	id = 0;
	name = NULL;
	category_id = 0;
	sport_id = 0;
	country_name = NULL;
	super_id = 0;
};
class Tournament {
public:
	Tournament();
	~Tournament() { if (name != NULL) delete[] name; if (season_name != NULL) delete[] season_name; };
	int id;
	int season_id;
	int simple_id;
	int type_radar = 0;//0 sr:tournament //1 sr:race_tournament: //2 sr:simple_tournament: 
	int sport_id;
	int category_id;
	int sort;
	char *name;
	char *season_name;
	int start_date;
	int end_date;
	void operator = (const Tournament&);
};
void Tournament:: operator = (const Tournament & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	season_id = rhs.season_id;
	simple_id = rhs.simple_id;
	start_date=rhs.start_date;
	end_date=rhs.end_date;
	category_id = rhs.category_id;
	sport_id = rhs.sport_id;
	sort = rhs.sort;
	type_radar = rhs.type_radar;
	if (name != NULL) {
		delete[] name; name = NULL;
	}
	if (rhs.name != NULL) {
		name = new char[strlen(rhs.name) + 1];
		std::strcpy(name, rhs.name);
	}

	if (season_name != NULL) {
		delete[] season_name; season_name = NULL;
	}
	if (rhs.season_name != NULL) {
		season_name = new char[strlen(rhs.season_name) + 1];
		std::strcpy(season_name, rhs.season_name);
	}

}
Tournament::Tournament() {
	id = 0;
	type_radar = 0;
	category_id = 0;
	sport_id = 0;
	sort = 0;
	simple_id = 0;
	season_id = 0;
	start_date = 0;
	end_date = 0;
	name = NULL;
	season_name = NULL;
};
class Category {
public:
	Category();
	~Category() { if (name != NULL) delete[] name; outrights_id.clear();
	};
	int id;
	int sport_id;
	int sort;
	int outrights;
	vector<int> outrights_id;
	char *name;
	void operator = (const Category&);
};
void Category:: operator = (const Category & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	sport_id = rhs.sport_id;
	sort = rhs.sort;
	outrights = rhs.outrights;
	if (name != NULL) {
		delete[] name; name = NULL;
	}
	if (rhs.name != NULL) {
		name = new char[strlen(rhs.name) + 1];
		std::strcpy(name, rhs.name);
	}
}
Category::Category() {
	id = 0;
	sport_id = 0;
	sort = 0;
	outrights = 0;
	name = nullptr;
};
class Event {
public:
	Event();
	~Event() {
		if (home_name != NULL) delete[] home_name; if (tv_channels != NULL) delete[] tv_channels; if (venue != NULL) delete[] venue; if (away_name != NULL) delete[] away_name;
		if (set_scores != NULL) delete[] set_scores;  if (match_time != NULL) delete[] match_time; if (remaining_time != NULL) delete[] remaining_time; if (remaining_time_in_period != NULL) delete[] remaining_time_in_period; if (bases!= NULL) delete[] bases;
		if (stoppage_time != NULL) delete[] stoppage_time; if (stoppage_time_announced != NULL) delete[] stoppage_time_announced; if (delayed_description != NULL) delete[] delayed_description;
	};

	
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
	int home_super_id = 0;
	int away_super_id = 0;
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
	char *home_name;
	char *away_name;
	char* delayed_description;
	int timestamp;
	int start_time;
	int next_live_time;
	int neutral_ground;
	int period_length;
	int overtime_length;
	int austrian_district;
	int booked;
	int type_radar;//0 tournament//1 race tournament//2 simple tournament
	int parent_id;
	int delayed_id;
	

	void operator = (const Event&);

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
	home_super_id = rhs.home_super_id;
	away_super_id = rhs.away_super_id;
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

	if (tv_channels != NULL) {
		delete[] tv_channels; tv_channels = NULL;
	}
	if (rhs.tv_channels != NULL) {
		tv_channels = new char[strlen(rhs.tv_channels) + 1];
		std::strcpy(tv_channels, rhs.tv_channels);
	}

	if (delayed_description != NULL) {
		delete[] delayed_description; delayed_description = NULL;
	}
	if (rhs.delayed_description != NULL) {
		delayed_description = new char[strlen(rhs.delayed_description) + 1];
		std::strcpy(delayed_description, rhs.delayed_description);
	}
	if (venue != NULL) {
		delete[] venue; venue = NULL;
	}
	if (rhs.venue != NULL) {
		venue = new char[strlen(rhs.venue) + 1];
		std::strcpy(venue, rhs.venue);
	}

	if (set_scores != NULL) {
		delete[] set_scores; set_scores = NULL;
	}
	if (rhs.set_scores != NULL) {
		set_scores = new char[strlen(rhs.set_scores) + 1];
		std::strcpy(set_scores, rhs.set_scores);
	}

	if (bases != NULL) {
		delete[] bases; bases = NULL;
	}
	if (rhs.bases != NULL) {
		bases = new char[strlen(rhs.bases) + 1];
		std::strcpy(bases, rhs.bases);
	}

	
	if (match_time != NULL) {
		delete[] match_time; match_time = NULL;
	}
	if (rhs.match_time != NULL) {
		match_time = new char[strlen(rhs.match_time) + 1];
		std::strcpy(match_time, rhs.match_time);
	}

	if (stoppage_time != NULL) {
		delete[] stoppage_time; stoppage_time = NULL;
	}
	if (rhs.stoppage_time != NULL) {
		stoppage_time = new char[strlen(rhs.stoppage_time) + 1];
		std::strcpy(stoppage_time, rhs.stoppage_time);
	}

	if (stoppage_time_announced != NULL) {
		delete[] stoppage_time_announced; stoppage_time_announced = NULL;
	}
	if (rhs.stoppage_time_announced != NULL) {
		stoppage_time_announced = new char[strlen(rhs.stoppage_time_announced) + 1];
		std::strcpy(stoppage_time_announced, rhs.stoppage_time_announced);
	}





	if (remaining_time != NULL) {
		delete[] remaining_time; remaining_time = NULL;
	}
	if (rhs.remaining_time != NULL) {
		remaining_time = new char[strlen(rhs.remaining_time) + 1];
		std::strcpy(remaining_time, rhs.remaining_time);
	}

	if (remaining_time_in_period != NULL) {
		delete[] remaining_time_in_period; remaining_time_in_period = NULL;
	}
	if (rhs.remaining_time_in_period != NULL) {
		remaining_time_in_period = new char[strlen(rhs.remaining_time_in_period) + 1];
		std::strcpy(remaining_time_in_period, rhs.remaining_time_in_period);
	}

	
	if (away_name != NULL) {
		delete[] away_name; away_name = NULL;
	}
	if (rhs.away_name != NULL) {
		away_name = new char[strlen(rhs.away_name) + 1];
		std::strcpy(away_name, rhs.away_name);
	}


	if (home_name != NULL) {
		delete[] home_name; home_name = NULL;
	}
	if (rhs.home_name != NULL) {
		home_name = new char[strlen(rhs.home_name) + 1];
		std::strcpy(home_name, rhs.home_name);
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
}
Event::Event() {
	id = 0;
	bo = 0;
	sport_id = 0;
	position = 0;
	category_id = 0;
	tournament_id = 0;
	away_name = NULL;// new char[NAME_LENTGH];
	home_name = NULL;// new char[NAME_LENTGH];
	status = -1; //0(not started) / 1(live) / 2(suspended) /	3(ended) / 4(closed) / abandoned - only one of these 6 is possible
	show = 0;
	reporting = 0;//
	home_score = 0;
	away_score = 0;
	home_gamescore = 0;
	away_gamescore = 0;
	away_super_id = 0;
	home_super_id = 0;
	away_id = 0;
	home_id = 0;
	bases = NULL;
	set_scores = NULL;// new char[MAX_PATH];
	match_status = 0;// new char[64];
	match_time = NULL;// new char[16];
	remaining_time = NULL;// new char[16];
	remaining_time_in_period = NULL;// new char[16];
	stoppage_time = NULL;
	stoppage_time_announced = NULL;
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
	tv_channels = NULL;
	venue = NULL;
	delayed_id = 0;
	delayed_description = NULL;

};
class Market {
public:
	Market();
	~Market() {
		if (name != NULL) delete[] name; if (outcome_number > 0) { for (int i = 0; i < outcome_number; i++) if (outcome_name[i] != NULL) delete[] outcome_name[i]; };
		if (outcome_id != NULL) delete[] outcome_id; if (outcome_name != NULL) delete[] outcome_name;

		if (specifier_number > 0) { for (int i = 0; i < specifier_number; i++) if (specifier_name[i] != NULL) delete[] specifier_name[i]; for (int i = 0; i < specifier_number; i++) if (specifier_description[i] != NULL) delete[] specifier_description[i]; } if (specifier_type != NULL) delete[] specifier_type; if (specifier_name != NULL) delete[] specifier_name;
		if (specifier_description != NULL) delete[] specifier_description; if (variable_text != NULL) delete[] variable_text;
	};

	int id;
	//int site_id;
	char* variable_text;
	int variant;
	int type;//0 -normal//1-sr:player//2-sr:competitor//3 pre:outcometext//4 liveodds:outcometext
	int line_type;//ID_TIP_EVENT SITE
	char* name;
	int outcome_number;
	char** outcome_name;
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

	for (int i = 0; i < outcome_number; i++) if (outcome_name[i] != NULL) {delete[] outcome_name[i]; outcome_name[i] = NULL;}
	if (outcome_name != NULL) { delete[] outcome_name; outcome_name = NULL; }
	if (outcome_id != NULL) { delete[] outcome_id; outcome_id = NULL; }

	if (variable_text != NULL) {
		delete[] variable_text; variable_text = NULL;
	}
	if (rhs.variable_text != NULL) {
		variable_text = new char[strlen(rhs.variable_text) + 1];
		std::strcpy(variable_text, rhs.variable_text);
	}

	outcome_number = rhs.outcome_number;
	type = rhs.type;
	line_type = rhs.line_type;
	variant = rhs.variant;
	if (name != NULL) {
		delete[] name; name = NULL;
	}
	if (rhs.name != NULL) {
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

	if (name != NULL) {
		delete[] name; name = NULL;
	}
	if (rhs.name != NULL) {
		name = new char[strlen(rhs.name) + 1];
		std::strcpy(name, rhs.name);
	}

	for (int i = 0; i < specifier_number; i++) { if (specifier_name[i] != NULL) { delete[] specifier_name[i]; specifier_name[i] = NULL; } if (specifier_description[i] != NULL) { delete[] specifier_description[i]; specifier_description[i] = NULL; } }
	if (specifier_name != NULL) { delete[] specifier_name; specifier_name = NULL; }
	if (specifier_description != NULL) { delete[] specifier_description; specifier_description = NULL; }
	if (specifier_type != NULL) {
		delete[] specifier_type; specifier_type = NULL;
	}


	specifier_number = rhs.specifier_number;
	std::strcpy(name, rhs.name);
	specifier_name = new char*[specifier_number];
	specifier_description = new char*[specifier_number];
	specifier_type = new int[specifier_number];


	for (int i = 0; i < specifier_number; i++) {
		if (rhs.specifier_name[i] != NULL) {
			specifier_name[i] = new char[strlen(rhs.specifier_name[i]) + 1]; std::strcpy(specifier_name[i], rhs.specifier_name[i]);
		}
		else specifier_name[i] = NULL;
		if (rhs.specifier_description[i] != NULL) { specifier_description[i] = new char[strlen(rhs.specifier_description[i]) + 1]; std::strcpy(specifier_description[i], rhs.specifier_description[i]); }
		else specifier_description[i] = NULL;


		specifier_type[i] = rhs.specifier_type[i];
	}


}
Market::Market() {
	id = 0;
	type = 0;
	line_type = 0;
	variant = -1;
	name = NULL;
	outcome_number = 0;
	outcome_id = NULL;
	outcome_name = NULL;
	specifier_name = NULL;
	specifier_description = NULL;
	specifier_type = NULL;
	specifier_number = 0;
	variable_text = NULL;


};
class Line {
public:
	Line();
	~Line() {
		
		if (name != NULL) delete[] name;  if (outcome_number > 0) { for (int i = 0; i < outcome_number; i++) if (outcome_name[i] != NULL) delete[] outcome_name[i]; };
		
		if (outcome_id != NULL) delete[] outcome_id; if (outcome_active != NULL) delete[] outcome_active; if (outcome_team != NULL) delete[] outcome_team; if (outcome_odds != NULL) delete[] outcome_odds;
		
		if (outcome_probabilities != NULL) delete[] outcome_probabilities; if (outcome_name != NULL) delete[] outcome_name;
		
		if (specifier_number > 0) { for (int i = 0; i < specifier_number; i++) { if (specifier[i] != NULL) delete[] specifier[i];  if (specifier_value[i] != NULL) delete[] specifier_value[i];} }
	

		if (extended_specifier_number > 0) { for (int i = 0; i < extended_specifier_number; i++) { if (extended_specifier[i] != NULL) delete[] extended_specifier[i];  if (extended_specifier_value[i] != NULL) delete[] extended_specifier_value[i];  } }
	
		if (specifier != NULL) delete[] specifier; if (specifier_value != NULL) delete[] specifier_value;
		if (extended_specifier != NULL) delete[] extended_specifier; if (extended_specifier_value != NULL) delete[] extended_specifier_value;
	
		
	};


	int id;
	int betstop_reason;
	int tournament_id;
	int simple_id;
	int market_id;
	int event_id;
	int team;
	int status; //0 (inactive)// 1 (active) //-1(suspended) //- 3 (cleared, settled) //- 4 (cancelled)	//handed_over(-2)
	int favourite;
	int type;//0 -normal//1-sr:player//2-sr:competitor//3 pre:outcometext
	int variant;
	char* name;
	int outcome_number;
	char** outcome_name;
	Market* market;
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
	string getCompoundKey();
};
void Line:: operator = (const Line & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	betstop_reason=rhs.betstop_reason;
	market_id = rhs.market_id;
	event_id = rhs.event_id;
	status = rhs.status;
	favourite = rhs.favourite;
	type = rhs.type;
	tournament_id = rhs.tournament_id;
	variant = rhs.variant;
	market = rhs.market;
	simple_id = rhs.simple_id;
	next_betstop = rhs.next_betstop;
	for (int i = 0; i < outcome_number; i++) if (outcome_name[i] != NULL) delete[] outcome_name[i];
	if (outcome_name != NULL) { delete[] outcome_name; outcome_name = NULL; }
	if (outcome_id != NULL) { delete[] outcome_id; outcome_id = NULL; }
	if (outcome_active != NULL) { delete[] outcome_active; outcome_active = NULL; }
	if (outcome_team != NULL) { delete[] outcome_team; outcome_team = NULL; }
	if (outcome_probabilities != NULL) { delete[] outcome_probabilities; outcome_probabilities = NULL; }
	if (outcome_odds != NULL) { delete[] outcome_odds; outcome_odds = NULL; }


	outcome_number = rhs.outcome_number;
	type = rhs.type;
	if (name != NULL) {
		delete[] name; name = NULL;
	}
	if (rhs.name != NULL) {
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

	if (name != NULL) {
		delete[] name; name = NULL;
	}
	if (rhs.name != NULL) {
		name = new char[strlen(rhs.name) + 1];
		std::strcpy(name, rhs.name);
	}

	for (int i = 0; i < specifier_number; i++) { if (specifier[i] != NULL) delete[] specifier[i]; if (specifier_value[i] != NULL) delete[] specifier_value[i]; }
	if (specifier != NULL) { delete[] specifier; specifier = NULL; }
	if (specifier_value != NULL) { delete[] specifier_value; specifier_value = NULL; }
	


	specifier_number = rhs.specifier_number;
	std::strcpy(name, rhs.name);
	specifier = new char*[specifier_number];
	specifier_value = new char*[specifier_number];

	for (int i = 0; i < specifier_number; i++) {
		if (rhs.specifier[i] != NULL) {
			specifier[i] = new char[strlen(rhs.specifier[i]) + 1]; std::strcpy(specifier[i], rhs.specifier[i]);}
		else specifier[i] = NULL;
		if (rhs.specifier_value[i] != NULL) {specifier_value[i] = new char[strlen(rhs.specifier_value[i]) + 1]; std::strcpy(specifier_value[i], rhs.specifier_value[i]); }
		else specifier_value[i] = NULL;		
	}


	extended_specifier_number = rhs.extended_specifier_number;
	std::strcpy(name, rhs.name);
	extended_specifier = new char*[extended_specifier_number];
	extended_specifier_value = new char*[extended_specifier_number];

	for (int i = 0; i < extended_specifier_number; i++) {
		if (rhs.extended_specifier[i] != NULL) {
			extended_specifier[i] = new char[strlen(rhs.extended_specifier[i]) + 1]; std::strcpy(extended_specifier[i], rhs.extended_specifier[i]);
		}
		else extended_specifier[i] = NULL;
		if (rhs.extended_specifier_value[i] != NULL) { extended_specifier_value[i] = new char[strlen(rhs.extended_specifier_value[i]) + 1]; std::strcpy(extended_specifier_value[i], rhs.extended_specifier_value[i]); }
		else extended_specifier_value[i] = NULL;
	}


}
Line::Line() {
	id = 0;
	betstop_reason=0;
    tournament_id = 0;
	event_id = 0;
	status = 0;
	favourite = 0;
	type = 0;
	market=NULL;
	variant = -1;
	name = NULL;
	outcome_number = 0;
	outcome_id = NULL;
	outcome_active = NULL;
	outcome_team = NULL;
	outcome_name = NULL;
	outcome_probabilities = NULL;
	outcome_odds = NULL;
	specifier = NULL;
	extended_specifier = NULL;
	specifier_value = NULL;
	extended_specifier_value = NULL;
	specifier_number = 0;
	extended_specifier_number = 0;
	next_betstop = 0;
	simple_id = 0;
	

};
string Line::getCatKey() {
	if (event_id > 0) {
		return "e" + to_string(event_id);
	}
	else if (tournament_id > 0) {
		return "t" + to_string(tournament_id);
	}
	else if (simple_id > 0) {
		return "s" + to_string(simple_id);
	}
	else {
		cout << "Something wrong with this line: " << name << endl;
		return "";
	}
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
	~Betstop() { if (description != NULL) delete[] description;  };
	int id;
	char *description;
	void operator = (const Betstop&);
};
void Betstop:: operator = (const Betstop & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	if (description != NULL) {
		delete[] description; description = NULL;
	}
	if (rhs.description != NULL) {
		description = new char[strlen(rhs.description) + 1];
		std::strcpy(description, rhs.description);
	}

	
}
Betstop::Betstop() {
	id = 0;
	description = NULL;
};
class Matchstatus {
public:
	Matchstatus();
	~Matchstatus() { if (description != NULL) delete[] description; };
	int id;
	char *description;
	void operator = (const Matchstatus&);
};
void Matchstatus:: operator = (const Matchstatus & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	if (description != NULL) {
		delete[] description; description = NULL;
	}
	if (rhs.description != NULL) {
		description = new char[strlen(rhs.description) + 1];
		std::strcpy(description, rhs.description);
	}


}
Matchstatus::Matchstatus() {
	id = 0;
	description = NULL;
};

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
int competitors_l= 0;
Betstop* betstops = new Betstop[BETSTOPS_LENTGH];
int betstops_l = 0;
Matchstatus* matchstatus = new Matchstatus[MATCHSTATUS_LENTGH];
int matchstatus_l = 0;


int i = 0;

Event** events_id = new Event*[MAX_EVENTS];
Event** events_show = new Event*[MAX_EVENTS];
int events_show_l = 0;
Line** lines_id = new Line*[MAX_LINES];
Tournament** tournaments_id = new Tournament*[MAX_TOURNAMENTS];
Tournament** seasons_id = new Tournament*[MAX_TOURNAMENTS];
Tournament** simples_id = new Tournament*[MAX_TOURNAMENTS];
Category** categories_id = new Category*[MAX_CATEGORIES];
Sport** sports_id = new Sport*[MAX_SPORTS];
Competitor** competitors_id = new Competitor*[MAX_COMPETITORS];
Player** players_id = new Player*[MAX_PLAYERS];
Market*** markets_id = new Market**[MAX_MARKETS];
Betstop** betstops_id = new Betstop*[MAX_BETSTOPS];
Matchstatus** matchstatus_id = new Matchstatus*[MAX_MATCHSTATUS];
int *max_markets_in = new int[MAX_MARKETS];


class wsClient {
public:
	wsClient(int _socket, SSL* _ssl, in_addr _addr) {
		socket = _socket;
		ssl = _ssl;
		message_buffer.clear();
		ready_state = WS_READY_STATE_CONNECTING;
		last_recv_time = time(NULL);
		ping_sent_time = 0;
		close_status = 0;
		addr = _addr;
		frame_payload_data_length = 0;
		frame_bytes_read = 0;
		frame_buffer.clear();
		message_opcode = 0;
		message_buffer_length = 0;
		message_queue = new char*[QUEUE_LENGTH];
		message_queue_length = new int[QUEUE_LENGTH];
		for (int i = 0; i < QUEUE_LENGTH; i++) { message_queue[i] = nullptr; message_queue_length[i] = 0; }
		message_ping = nullptr;
		message_pong = nullptr;
		message_close = nullptr;
		message_ping_length = 0;
		message_pong_length = 0;
		message_close_length = 0;
		plus_message_length = 0;
		outright_message_length = 0;
		outright = 0;
		outright_create = false;
		outright_send = false;
		outright_message = nullptr;
		plus = 0;
		handshake_message = nullptr;
		plus_message = nullptr;
		last_message_queue = 0;
		last_message_queue_socket = 0;
		step_buffer_1 = nullptr;
		step_buffer_2 = nullptr;
		current1 = -1;
		current2 = -1;
		step_buffer_len_2 = -1;
		step_buffer_len_1 = -1;
		plus_create = false;
		plus_send = false;
		timestamp = 0;
		
		//flag = 0;

	}
	~wsClient() {
		for (int i = 0; i < QUEUE_LENGTH; i++)  if (message_queue[i] != nullptr) delete[] message_queue[i];
		delete[] message_queue; delete[] message_queue_length;
		if (message_ping != nullptr) delete[] message_ping;  if (message_pong != nullptr) delete[] message_pong;
		if (message_close != nullptr) delete[] message_close;
		if (handshake_message != nullptr) delete[] handshake_message;
		if (plus_message != nullptr) delete[] plus_message;
		if (outright_message != nullptr) delete[] outright_message;
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
	atomic_int64_t last_message_queue;
	atomic_int64_t last_message_queue_socket;
	int plus;
	std::atomic<bool> plus_create;
	std::atomic<bool> plus_send;
	atomic_int64_t timestamp;


	char* message_ping;
	char* message_pong;
	char* message_close;
	int message_ping_length;
	int message_pong_length;
	int message_close_length;
	int plus_message_length;
	char* handshake_message;
	char* plus_message;
	char* step_buffer_1;
	char* step_buffer_2;
	int step_buffer_len_1;
	int step_buffer_len_2;
	int current1;
	int current2;
	int outright_message_length;
	int outright = 0;
	std::atomic<bool> outright_create;
	std::atomic<bool> outright_send;
	char* outright_message;


	//int flag;
	//std::mutex mutex;





};
class webSocket {
public:
	webSocket() {
		callOnOpen = NULL;
		callOnClose = NULL;
		callOnMessage = NULL;
		callPeriodic = NULL;
	}

	void setOpenHandler(defaultCallback callback);
	void setCloseHandler(defaultCallback callback);
	void setMessageHandler(messageCallback callback);
	void setPeriodicHandler(nullCallback callback);
	void startServer(int port);
	void stopServer();
	bool wsSend(int clientID, char* message, size_t messageLen, bool binary = true);
	void wsClose(int clientID);
	vector<int> getClientIDs();
	string getClientIP(int clientID);
	vector<wsClient *> wsClients;
	//vector<atomic_flag*> wsFlags;
	//atomic_flag ws_clients_flag = ATOMIC_FLAG_INIT;
	map<int, int> socketIDmap;

private:

	fd_set r_fds;
	fd_set w_fds;
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
	bool wsBuildClientFrame(int clientID, char *buffer, int bufferLength);
	bool wsProcessClientHandshake(int clientID, char *buffer);
	bool wsProcessClient(int clientID, char *buffer, int bufferLength);
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



DWORD WINAPI pushClientMessageThread(LPVOID lparam);

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
		if (pIPAddrTable == NULL) {
			std::printf("Memory allocation failed for GetIpAddrTable\n");
			return;
		}
	}
	// Make a second call to GetIpAddrTable to get the
	// actual data we want
	if ((dwRetVal = GetIpAddrTable(pIPAddrTable, &dwSize, 0)) != NO_ERROR) {
		printf("GetIpAddrTable failed with error %d\n", dwRetVal);
		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dwRetVal, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),       // Default language
			(LPTSTR)& lpMsgBuf, 0, NULL)) {
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
		pIPAddrTable = NULL;
	}


}
vector<int> webSocket::getClientIDs() {
	vector<int> clientIDs;
	for (int i = 0; i < wsClients.size(); i++) {
		if (wsClients[i] != NULL && wsClients[i]->timestamp == 0)
			clientIDs.push_back(i);
	}

	return clientIDs;
}
string webSocket::getClientIP(int clientID) {
	return string(inet_ntoa(wsClients[clientID]->addr));
}
void webSocket::wsCheckIdleClients() {
	
	time_t current = time(NULL);
	for (int i = 0; i < wsClients.size(); i++) {
		if (wsClients[i] != NULL && wsClients[i]->timestamp == 0 && wsClients[i]->ready_state != WS_READY_STATE_CLOSED && wsClients[i]->ready_state != WS_READY_STATE_CLOSING) {
			if (wsClients[i]->ping_sent_time != 0) {
				if (difftime(current, wsClients[i]->ping_sent_time) >= WS_TIMEOUT_PONG) {
					wsSendClientClose(i, WS_STATUS_TIMEOUT);
					//wsRemoveClient(i);
				}
			}
			else if (difftime(current, wsClients[i]->last_recv_time) != WS_TIMEOUT_RECV) {
				if (wsClients[i]->ready_state != WS_READY_STATE_CONNECTING) {
					wsClients[i]->ping_sent_time = time(NULL);
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
		return true;

	// fetch message length


	char *buf = nullptr;
	size_t totalLength;

	if (opcode == WS_OPCODE_PING || opcode == WS_OPCODE_PONG || opcode == WS_OPCODE_CLOSE) {

		// set max payload length per frame
		int bufferSize = DEFAULT_BUFLEN;

		// work out amount of frames to send, based on $bufferSize
		int frameCount = ceil((float)messageLen / bufferSize);
		if (frameCount == 0)
			frameCount = 1;

		// set last frame variables
		int maxFrame = frameCount - 1;
		int lastframe_bufferLength = (messageLen % bufferSize) != 0 ? (messageLen % bufferSize) : (messageLen != 0 ? bufferSize : 0);

		// loop around all frames to send



		for (int i = 0; i < frameCount; i++) {
			// fetch fin, opcode and buffer length for frame
			unsigned char fin = i != maxFrame ? 0 : WS_FIN;
			opcode = i != 0 ? WS_OPCODE_CONTINUATION : opcode;

			size_t bufferLength = i != maxFrame ? bufferSize : lastframe_bufferLength;



			// set payload length variables for frame
			if (bufferLength <= 125) {
				// int payloadLength = bufferLength;
				totalLength = bufferLength + 2;
				buf = new char[totalLength];
				buf[0] = fin | opcode;
				buf[1] = bufferLength;
				memcpy(buf + 2, message, messageLen);
			}
			else if (bufferLength <= 65535) {
				// int payloadLength = WS_PAYLOAD_LENGTH_16;
				totalLength = bufferLength + 4;
				buf = new char[totalLength];
				buf[0] = fin | opcode;
				buf[1] = WS_PAYLOAD_LENGTH_16;
				buf[2] = bufferLength >> 8;
				buf[3] = bufferLength;
				memcpy(buf + 4, message, messageLen);
			}
			else {
				// int payloadLength = WS_PAYLOAD_LENGTH_63;
				totalLength = bufferLength + 10;
				buf = new char[totalLength];
				buf[0] = fin | opcode;
				buf[1] = WS_PAYLOAD_LENGTH_63;
				buf[2] = 0;
				buf[3] = 0;
				buf[4] = 0;
				buf[5] = 0;
				buf[6] = bufferLength >> 24;
				buf[7] = bufferLength >> 16;
				buf[8] = bufferLength >> 8;
				buf[9] = bufferLength;
				memcpy(buf + 10, message, messageLen);
			}

		}

		if (opcode == WS_OPCODE_PING) { if (wsClients[clientID]->message_ping != nullptr) delete[] wsClients[clientID]->message_ping; wsClients[clientID]->message_ping = buf; wsClients[clientID]->message_ping_length = totalLength; }
		else
			if (opcode == WS_OPCODE_PONG) { if (wsClients[clientID]->message_pong != nullptr) delete[] wsClients[clientID]->message_pong; wsClients[clientID]->message_pong = buf; wsClients[clientID]->message_pong_length = totalLength; }
			else
				if (opcode == WS_OPCODE_CLOSE) { if (wsClients[clientID]->message_close != nullptr) delete[] wsClients[clientID]->message_close; wsClients[clientID]->message_close = buf; wsClients[clientID]->message_close_length = totalLength; }

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
	int bufferSize = DEFAULT_BUFLEN;

	// work out amount of frames to send, based on $bufferSize
	int frameCount = ceil((float)messageLength / bufferSize);
	if (frameCount == 0)
		frameCount = 1;

	// set last frame variables
	int maxFrame = frameCount - 1;
	int lastframe_bufferLength = (messageLength % bufferSize) != 0 ? (messageLength % bufferSize) : (messageLength != 0 ? bufferSize : 0);

	// loop around all frames to send

	if (writeBuffer != nullptr) delete[] writeBuffer;
	writeBuffer = nullptr;


	for (int i = 0; i < frameCount; i++) {
		// fetch fin, opcode and buffer length for frame
		unsigned char fin = i != maxFrame ? 0 : WS_FIN;
		opcode = i != 0 ? WS_OPCODE_CONTINUATION : opcode;

		size_t bufferLength = i != maxFrame ? bufferSize : lastframe_bufferLength;

		//size_t totalLength;

		// set payload length variables for frame
		if (bufferLength <= 125) {
			// int payloadLength = bufferLength;
			writeBufferLen = bufferLength + 2;
			writeBuffer = new char[writeBufferLen];
			writeBuffer[0] = fin | opcode;
			writeBuffer[1] = bufferLength;
			memcpy(writeBuffer + 2, message, messageLength);
		}
		else if (bufferLength <= 65535) {
			// int payloadLength = WS_PAYLOAD_LENGTH_16;
			writeBufferLen = bufferLength + 4;
			writeBuffer = new char[writeBufferLen];
			writeBuffer[0] = fin | opcode;
			writeBuffer[1] = WS_PAYLOAD_LENGTH_16;
			writeBuffer[2] = bufferLength >> 8;
			writeBuffer[3] = bufferLength;
			memcpy(writeBuffer + 4, message, messageLength);
		}
		else {
			// int payloadLength = WS_PAYLOAD_LENGTH_63;
			writeBufferLen = bufferLength + 10;
			writeBuffer = new char[writeBufferLen];
			writeBuffer[0] = fin | opcode;
			writeBuffer[1] = WS_PAYLOAD_LENGTH_63;
			writeBuffer[2] = 0;
			writeBuffer[3] = 0;
			writeBuffer[4] = 0;
			writeBuffer[5] = 0;
			writeBuffer[6] = bufferLength >> 24;
			writeBuffer[7] = bufferLength >> 16;
			writeBuffer[8] = bufferLength >> 8;
			writeBuffer[9] = bufferLength;
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
	if (wsClients[clientID]->timestamp > 0 ||wsClients[clientID]->ready_state == WS_READY_STATE_CLOSING || wsClients[clientID]->ready_state == WS_READY_STATE_CLOSED)
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
	
	//if (callOnClose != NULL)
		//callOnClose(clientID);

	wsClient *client = wsClients[clientID];
	if (client->timestamp > 0) return;
	// fetch close status (which could be false), and call wsOnClose
	//int64_t closeStatus = wsClients[clientID]->close_status;
	//int64_t flag = 0;
	//
	//SSL_shutdown(client->ssl);
	//SSL_CTX_free(client->ssl);
	//while (ws_clients_flag.test_and_set(std::memory_order_acquire));
	client->timestamp = timestamp();
	FD_CLR(client->socket, &r_fds);
	FD_CLR(client->socket, &w_fds);
	closesocket(client->socket);
	SSL_set_shutdown(client->ssl, SSL_RECEIVED_SHUTDOWN);
	SSL_free(client->ssl);
	socketIDmap.erase(client->socket);
	//wsClients[clientID] = NULL;
	//delete client;
	//ws_clients_flag.clear(std::memory_order_release);
}
void webSocket::wsDeleteClient(int clientID) {
wsClient *client = wsClients[clientID];
	wsClients[clientID] = NULL;
	delete client;
	//ws_clients_flag.clear(std::memory_order_release);
}
bool webSocket::wsProcessClientMessage(int clientID, unsigned char opcode, string data, int dataLength) {
	wsClient *client = wsClients[clientID];
	// check opcodes

	if (opcode == WS_OPCODE_PING) {
		// received ping message
		return wsSendClientMessage(clientID, WS_OPCODE_PONG, (char*)data.c_str(), data.size());
	}
	else if (opcode == WS_OPCODE_PONG) {
		// received pong message (it's valid if the server did not send a ping request for this pong message)
		if (client->ping_sent_time != 0) {
			client->ping_sent_time = 0;
		}
	}
	else if (opcode == WS_OPCODE_CLOSE) {
		// received close message
		if (client->ready_state == WS_READY_STATE_CLOSING) {
			// the server already sent a close frame to the client, this is the client's close frame reply
			// (no need to send another close frame to the client)
			client->ready_state = WS_READY_STATE_CLOSED;
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
		//if(data.substr(0, dataLength)=="recovery" ) hThread4 = CreateThread(NULL, 0, &startRecoveryThread, 0, THREAD_TERMINATE, &dwThreadID4);
		//if (callOnMessage != NULL)	callOnMessage(clientID, data.substr(0, dataLength));
		if (data.substr(0, 7) == "rospis@") {
			int event_id = atoi(data.substr(7, dataLength).c_str());
			if (event_id != 0 && event_id < MAX_EVENTS && events_id[event_id] != nullptr && client->plus_send == false && client->plus_create == false) {
				client->plus = event_id; client->plus_create = true;


			}

		}


		if (data.substr(0, 9) == "outright@") {
			
			int category_id = atoi(data.substr(9, dataLength).c_str());
			if (category_id != 0 && category_id<MAX_CATEGORIES && categories_id[category_id] != nullptr && client->outright_send == false && client->outright_create == false) { client->outright = category_id; client->outright_create = true; }

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
	client->last_recv_time = time(NULL);

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
			if (wsClients[clientID] != NULL) {
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
bool webSocket::wsBuildClientFrame(int clientID, char *buffer, int bufferLength) {
	wsClient *client = wsClients[clientID];
	// increase number of bytes read for the frame, and join buffer onto end of the frame buffer
	client->frame_bytes_read += bufferLength;
	client->frame_buffer.append(buffer, bufferLength);

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
			if (wsClients[clientID] != NULL) {
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
	// fetch headers and request line
	/*string buf(buffer);
	size_t sep = buf.find("\r\n\r\n");
	if (sep == string::npos)
	return false;

	string headers = buf.substr(0, sep);

	string request = headers.substr(0, headers.find("\r\n"));
	if (request.size() == 0)
	return false;

	string part;
	part = request.substr(0, request.find(" "));
	if (part.compare("GET") != 0 && part.compare("get") != 0 && part.compare("Get") != 0)
	return false;

	part = request.substr(request.rfind("/") + 1);
	if (atof(part.c_str()) < 1.1)
	return false;

	string host;
	string ws_key;
	string ws_version;
	headers = headers.substr(headers.find("\r\n") + 2);
	while (headers.size() > 0) {
	request = headers.substr(0, headers.find("\r\n"));
	if (request.find(":") != string::npos) {
	string key = request.substr(0, request.find(":"));
	if (key.find_first_not_of(" ") != string::npos)
	key = key.substr(key.find_first_not_of(" "));
	if (key.find_last_not_of(" ") != string::npos)
	key = key.substr(0, key.find_last_not_of(" ") + 1);

	string value = request.substr(request.find(":") + 1);
	if (value.find_first_not_of(" ") != string::npos)
	value = value.substr(value.find_first_not_of(" "));
	if (value.find_last_not_of(" ") != string::npos)
	value = value.substr(0, value.find_last_not_of(" ") + 1);

	if (key.compare("Host") == 0) {
	host = value;
	}
	else if (key.compare("Sec-WebSocket-Key") == 0) {
	ws_key = value;
	}
	else if (key.compare("Sec-WebSocket-Version") == 0) {
	ws_version = value;
	}
	}
	if (headers.find("\r\n") == string::npos)
	break;
	headers = headers.substr(headers.find("\r\n") + 2);
	}


	unsigned char* decode_key = NULL;
	size_t key_l;

	Base64Decode((char*) ws_key.c_str(), &decode_key, &key_l);


	if (host.size() == 0)
	return false;

	if (ws_key.size() == 0 || key_l != 16)
	return false;

	if (ws_version.size() == 0 || atoi(ws_version.c_str()) < 7)
	return false;

	unsigned char hash[20];
	ws_key.append("258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
	SHA1((unsigned char *)ws_key.c_str(), ws_key.size(), hash);
	//string encoded_hash = base64_encode(hash, 20);
	char* encoded_key = NULL;

	Base64Encode((unsigned char*)hash, 20, &encoded_key);
	string encoded_hash(encoded_key);


	string message = "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: ";
	message.append(encoded_hash);
	message.append("\r\n\r\n");

	int socket = wsClients[clientID]->socket;
	SSL* ssl = wsClients[clientID]->ssl;

	int left = message.size();*/



	bool findHandshake = false;
	uint32_t index = 0;
	char handshakeTest[] = "Sec-WebSocket-Key: ";
	char* handshakeHash = new char[120];
	char* handshakeBuffer = new char[MAX_PATH];
	char* base64EncodeOutput = NULL;
	//ZeroMemory(base64_hash, sizeof(base64_hash));
	int handshakeTestLen = strlen(handshakeTest);
	unsigned char* digest = new unsigned char[SHA_DIGEST_LENGTH];
	int bufferLen = strlen(buffer);

	for (int i = 0; i < bufferLen - handshakeTestLen - 20; i++)
		if (strncmp((char*)((char*)buffer + i), handshakeTest, handshakeTestLen) == 0)
		{
			for (int j = 0; j < 100; j++) if (buffer[j + i + handshakeTestLen] == '\r' && buffer[j + i + handshakeTestLen + 1] == '\n')
			{
				strncpy(handshakeHash, (char*)((char*)buffer + i + handshakeTestLen), j);
				handshakeHash[j] = 0;
				//strcpy(handshakeHash, "lpRgKO1IAsqpPeIgIIbpfA==");

				strcat(handshakeHash, "258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
				findHandshake = true;
				//	printf(handshakeHash);
				//printf("\r\n");
				break;
			}


			break;
		}



	size_t handshakelen = 0;
	if (findHandshake == true) {
		SHA1((unsigned char*)handshakeHash, strlen(handshakeHash), digest);
		//printf("Output (sha1): %d\n", strlen(digest));
		Base64Encode(digest, 20, base64EncodeOutput, handshakelen);
		base64EncodeOutput[handshakelen] = 0;
		// printf("Output (base64): %s\r\n", base64EncodeOutput);
		//printf("handshakelen: %d\r\n", handshakelen);
	}


	strcpy(handshakeBuffer, "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: ");
	strcat(handshakeBuffer, base64EncodeOutput);
	strcat(handshakeBuffer, "\r\n\r\n");
	//printf(handshakeBuffer);




	wsClients[clientID]->handshake_message = handshakeBuffer;// new char[left];
	delete[] digest;
	delete[] base64EncodeOutput;
	delete[] handshakeHash;
	//wsClients[clientID]->handshake_message = new char[left];
	//strcpy(wsClients[clientID]->handshake_message, message.c_str());

	//printf(wsClients[clientID]->handshake_message);
	//printf("\r\n");

	//int sent = SSL_write(ssl, message.c_str(), message.size());
	//if (sent == false) return false;

	/*
	do {
	//int sent = send(socket, message.c_str(), message.size(), 0);
	int sent = SSL_write(ssl, message.c_str(), message.size());


	if (sent == false) return false;

	left -= sent;
	if (sent > 0)
	message = message.substr(sent);
	} while (left > 0);
	*/

	return true;
}
bool webSocket::wsProcessClient(int clientID, char *buffer, int bufferLength) {

	bool result;

	if (clientID >= wsClients.size() || wsClients[clientID] == NULL)
		return false;

	if (wsClients[clientID]->ready_state == WS_READY_STATE_OPEN) {
		// handshake completed

		result = wsBuildClientFrame(clientID, buffer, bufferLength);

	}
	else if (wsClients[clientID]->ready_state == WS_READY_STATE_CONNECTING) {
		// handshake not completed

		result = wsProcessClientHandshake(clientID, buffer);
		/*	if (result) {
		if (callOnOpen != NULL)
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
		if (wsClients[i] != NULL && wsClients[i]->timestamp > 0 && wsClients[i]->timestamp + 100000 < current_time)
			wsDeleteClient(i);
		if (wsClients[i] == NULL)
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
	//while (ws_clients_flag.test_and_set(std::memory_order_acquire));

	if (clientID >= wsClients.size()) {

		wsClients.push_back(newClient);

	}
	else {
		wsClients[clientID] = newClient;
	}
	socketIDmap[socket] = clientID;
	//ws_clients_flag.clear(std::memory_order_release);
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
	char buf[MEDIUM_BUFLEN];
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
	int writeopcode = 0;
	fd_set read_fds;
	fd_set write_fds;
	FD_ZERO(&r_fds);
	FD_ZERO(&w_fds);
	FD_SET(ListenSocket, &r_fds);
	FD_SET(ListenSocket, &w_fds);
	FD_ZERO(&read_fds);
	FD_ZERO(&write_fds);
	//std::printf(" ListenSocket=%d\r\n", ListenSocket);
	struct timeval timeout;
	time_t nextPingTime = time(NULL) + 20;

	while (FD_ISSET(ListenSocket, &r_fds) || FD_ISSET(ListenSocket, &w_fds)) {
		read_fds = r_fds;
		write_fds = w_fds;
		timeout.tv_sec = 0;
		timeout.tv_usec = 100;
		//if (select(fdmax + 1, &read_fds, NULL, NULL, &timeout) > 0) 

		//printf("---------------------------------------\r\n");
		/*
		for (int j = 0; j < STEP_QUEUE; j++) {

		if (array_data_step_1[j] != nullptr && j != current_data_step_1 && j != current_data_step_temp_1) {

		for (i = 0; i <= fdmax; i++) {
		if (socketIDmap.size() == 0) continue;
		if (socketIDmap.find(i) != socketIDmap.end()) continue;
		if (wsClients[socketIDmap[i]] == NULL) continue;
		if (wsClients[socketIDmap[i]]->step_buffer_1 != nullptr) printf("NONULLPTR1\r\n");
		if (wsClients[socketIDmap[i]]->step_buffer_1 == array_data_step_1[j]) { printf("j1=%d\r\n", j); printf("BRAEK1\r\n"); printf("current_data_step_1=%d current_data_step_temp_1=%d\r\n", current_data_step_1, current_data_step_temp_1); break; }
		}

		if (i > fdmax) {

		if (j != current_data_step_1 && j != current_data_step_temp_1) { printf("j1=%d\r\n", j); printf("DELETE1\r\n"); printf("current_data_step_1=%d current_data_step_temp_1=%d\r\n", current_data_step_1, current_data_step_temp_1); delete[] array_data_step_1[j]; array_data_step_1[j] = nullptr;
		}

		}
		}

		if (array_data_step_2[j] != nullptr  && j != current_data_step_2 && j != current_data_step_temp_2) {

		for (i = 0; i <= fdmax; i++) {
		if (socketIDmap.size() == 0) continue;
		if (socketIDmap.find(i) != socketIDmap.end()) continue;
		if (wsClients[socketIDmap[i]] == NULL) continue;
		if (wsClients[socketIDmap[i]]->step_buffer_2 != nullptr) printf("NONULLPTR2\r\n");
		if (wsClients[socketIDmap[i]]->step_buffer_2 == array_data_step_2[j]) { printf("j2=%d\r\n", j); printf("BRAEK2\r\n"); printf("current_data_step_2=%d current_data_step_temp_2=%d\r\n", current_data_step_2, current_data_step_temp_2); break; }
		}

		if (i > fdmax) {
		if (j != current_data_step_2 && j != current_data_step_temp_2) {
		printf("j2=%d\r\n", j);  printf("DELETE2\r\n"); printf("current_data_step_2=%d current_data_step_temp_2=%d\r\n", current_data_step_2, current_data_step_temp_2);
		delete[] array_data_step_2[j]; array_data_step_2[j] = nullptr;
		}

		}
		}
		}



		*/

		if (select(fdmax + 1, &read_fds, &write_fds, NULL, &timeout) != SOCKET_ERROR)
		{






			for (int i = 0; i <= fdmax; i++) {

				//|| (socketIDmap.find(i) != socketIDmap.end() &&SSL_pending(wsClients[socketIDmap[i]]->ssl))
				if (FD_ISSET(i, &read_fds) && recovery_state == 0) {
				

					if (i == ListenSocket) {

						socklen_t addrlen = sizeof(cli_addr);
						int ClientSocket = accept(ListenSocket, (struct sockaddr*)&cli_addr, &addrlen);
						if (ClientSocket != INVALID_SOCKET) {
							/* add new client */
							ssl = SSL_new(ctx);
							SSL_set_fd(ssl, ClientSocket);
							SSL_set_accept_state(ssl);

/*							cert = SSL_get_peer_certificate(ssl);
							if (cert != NULL) {
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

							//printf("wsClients[%d]->ready_state=%d nbytes=%d ssl_error=%d\r\n", socketIDmap[i], wsClients[socketIDmap[i]]->ready_state, nbytes, SSL_get_error(ssl, nbytes));

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
									const char* error_str = ERR_error_string(error, NULL);
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
									
									std::printf("could not SSL_read (returned -1)\n");

									/*long error = ERR_get_error();
									const char* error_str = ERR_error_string(error, NULL);
									std::printf("could not SSL_read (returned -1) %s\n", error_str);
									delete[] error_str;*/

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




				if (FD_ISSET(i, &write_fds) && recovery_state == 0) {
				
					if (i == ListenSocket) {
						/**/
					}
					else {

						if (socketIDmap.find(i) != socketIDmap.end()) {
							writeopcode = 0;


							int nbytes = 0;
							if (wsClients[socketIDmap[i]]->message_close != nullptr) {
								writeopcode = 2;
								nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->message_close, wsClients[socketIDmap[i]]->message_close_length);

							}
							else if (wsClients[socketIDmap[i]]->ready_state == WS_READY_STATE_CONNECTING &&wsClients[socketIDmap[i]]->handshake_message != nullptr) {
								writeopcode = 1;

								nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->handshake_message, strlen(wsClients[socketIDmap[i]]->handshake_message));

							}

							else if (wsClients[socketIDmap[i]]->step_buffer_len_1 == -1 && wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CONNECTING) {
								if (current_data_step_1 != -1) {
									writeopcode = 6;
									current =current_data_step_1.load();
									wsClients[socketIDmap[i]]->step_buffer_1 = array_data_step_1[current];
									wsClients[socketIDmap[i]]->step_buffer_len_1 = data_step_len_1[current];


									nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->step_buffer_1, wsClients[socketIDmap[i]]->step_buffer_len_1);
								}


							}
							else if (wsClients[socketIDmap[i]]->step_buffer_len_1 > 0 && wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CONNECTING) {
								writeopcode = 6;
								nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->step_buffer_1, wsClients[socketIDmap[i]]->step_buffer_len_1);
							}
							else if (wsClients[socketIDmap[i]]->step_buffer_len_2 == -1 && wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CONNECTING) {
								if (current_data_step_2 != -1) {
									writeopcode = 7;
									current = current_data_step_2.load();
									wsClients[socketIDmap[i]]->step_buffer_2 = array_data_step_2[current];
									wsClients[socketIDmap[i]]->step_buffer_len_2 = data_step_len_2[current];
									nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->step_buffer_2, wsClients[socketIDmap[i]]->step_buffer_len_2);
								}


							}
							else if (wsClients[socketIDmap[i]]->step_buffer_len_2 > 0 && wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CONNECTING) {
								writeopcode = 7;
								nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->step_buffer_2, wsClients[socketIDmap[i]]->step_buffer_len_2);
							}
							else if (wsClients[socketIDmap[i]]->plus_send == true && wsClients[socketIDmap[i]]->plus_create == false && wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CONNECTING) {
								writeopcode = 8;
								nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->plus_message, wsClients[socketIDmap[i]]->plus_message_length);
							}
							else if (wsClients[socketIDmap[i]]->outright_send == true && wsClients[socketIDmap[i]]->outright_create == false && wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CONNECTING) {
								writeopcode = 9;
								nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->outright_message, wsClients[socketIDmap[i]]->outright_message_length);
							}
							else if (wsClients[socketIDmap[i]]->last_message_queue > wsClients[socketIDmap[i]]->last_message_queue_socket && wsClients[socketIDmap[i]]->ready_state != WS_READY_STATE_CONNECTING) {
								writeopcode = 5;
								nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->message_queue[wsClients[socketIDmap[i]]->last_message_queue_socket % QUEUE_LENGTH], wsClients[socketIDmap[i]]->message_queue_length[wsClients[socketIDmap[i]]->last_message_queue_socket % QUEUE_LENGTH]);
							}
							else if (wsClients[socketIDmap[i]]->message_pong != nullptr) {
								writeopcode = 3;
								nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->message_pong, wsClients[socketIDmap[i]]->message_pong_length);

							}
							else if (wsClients[socketIDmap[i]]->message_ping != nullptr) {
								writeopcode = 4;
								nbytes = SSL_write(wsClients[socketIDmap[i]]->ssl, wsClients[socketIDmap[i]]->message_ping, wsClients[socketIDmap[i]]->message_ping_length);

							}

							if (writeopcode == 0) continue;

							//printf("wsClients[%d]->ready_state=%d last_message_queue=%d last_message_queue_socket=%d nbytes=%d writeopcode=%d ssl_error=%d\r\n", socketIDmap[i], wsClients[socketIDmap[i]]->ready_state, wsClients[socketIDmap[i]]->last_message_queue % QUEUE_LENGTH, wsClients[socketIDmap[i]]->last_message_queue_socket % QUEUE_LENGTH, nbytes, writeopcode, SSL_get_error(ssl, nbytes));


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
									const char* error_str = ERR_error_string(error, NULL);
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
									if (writeopcode == 5 || writeopcode == 6 || writeopcode == 7 || writeopcode == 8 || writeopcode == 9 || writeopcode == 1) continue;


								}
								/*
								if (writeopcode != 5 && writeopcode != 6 && writeopcode != 7 && writeopcode != 8 && writeopcode != 9) {
									long error = ERR_get_error();
									const char* error_str = ERR_error_string(error, NULL);
									//std::printf("could not SSL_write (returned -1): %s\n", error_str);
									delete[] error_str;
								
								}*/
								



							}


							if (nbytes < 0) {
								
								if (writeopcode == 2)
									wsRemoveClient(socketIDmap[i]);
								else {
									wsSendClientClose(socketIDmap[i], WS_STATUS_PROTOCOL_ERROR);
								}
								//wsClients[socketIDmap[i]]->flag = false;

							}
							else if (nbytes == 0) {
								if (writeopcode == 2) wsRemoveClient(socketIDmap[i]);
								else {
									wsSendClientClose(socketIDmap[i], WS_STATUS_PROTOCOL_ERROR);
								}

								//wsClients[socketIDmap[i]]->flag = false;

							}
							else {

								if (writeopcode == 1) {
									wsClients[socketIDmap[i]]->ready_state = WS_READY_STATE_OPEN;
									delete[] wsClients[socketIDmap[i]]->handshake_message;
									wsClients[socketIDmap[i]]->handshake_message = nullptr;
									if (current_data_step_1 != -1) {
										current = current_data_step_1.load();
										wsClients[socketIDmap[i]]->step_buffer_1 = array_data_step_1[current];
										wsClients[socketIDmap[i]]->step_buffer_len_1 = data_step_len_1[current];
									}
									if (callOnOpen != NULL) callOnOpen(socketIDmap[i]);
								}

								if (writeopcode == 2) {
									delete[] wsClients[socketIDmap[i]]->message_close; wsClients[socketIDmap[i]]->message_close = nullptr;
									wsClients[socketIDmap[i]]->message_close_length = 0;
									wsRemoveClient(socketIDmap[i]);

								}

								if (writeopcode == 3) {
									delete[] wsClients[socketIDmap[i]]->message_pong; wsClients[socketIDmap[i]]->message_pong = nullptr;
									wsClients[socketIDmap[i]]->message_pong_length = 0;

								}
								if (writeopcode == 4) {
									delete[] wsClients[socketIDmap[i]]->message_ping; wsClients[socketIDmap[i]]->message_ping = nullptr;
									wsClients[socketIDmap[i]]->message_ping_length = 0;

								}


								if (writeopcode == 5) {
									if (wsClients[socketIDmap[i]]->message_queue[wsClients[socketIDmap[i]]->last_message_queue_socket % QUEUE_LENGTH] != nullptr)
										delete[] wsClients[socketIDmap[i]]->message_queue[wsClients[socketIDmap[i]]->last_message_queue_socket % QUEUE_LENGTH];
									wsClients[socketIDmap[i]]->message_queue[wsClients[socketIDmap[i]]->last_message_queue_socket % QUEUE_LENGTH] = nullptr;
									wsClients[socketIDmap[i]]->message_queue_length[wsClients[socketIDmap[i]]->last_message_queue_socket % QUEUE_LENGTH] = 0;
									wsClients[socketIDmap[i]]->last_message_queue_socket++;
								}

								if (writeopcode == 6) {
									wsClients[socketIDmap[i]]->step_buffer_1 = nullptr;
									wsClients[socketIDmap[i]]->step_buffer_len_1 = 0;
									if (current_data_step_2 != -1) {
										current = current_data_step_2.load();
										wsClients[socketIDmap[i]]->step_buffer_2 = array_data_step_2[current];
										wsClients[socketIDmap[i]]->step_buffer_len_2 = data_step_len_2[current];
									}

								}

								if (writeopcode == 7) {
									wsClients[socketIDmap[i]]->step_buffer_2 = nullptr;
									wsClients[socketIDmap[i]]->step_buffer_len_2 = 0;
								}

								if (writeopcode == 8) {
									//printf("wsClients[%d]->plus=%d clean\r\n", socketIDmap[i], wsClients[socketIDmap[i]]->plus);
									if (wsClients[socketIDmap[i]]->plus_message != nullptr) delete[] wsClients[socketIDmap[i]]->plus_message;
									wsClients[socketIDmap[i]]->plus = 0;
									wsClients[socketIDmap[i]]->plus_message = nullptr;
									wsClients[socketIDmap[i]]->plus_message_length = 0;
									wsClients[socketIDmap[i]]->plus_send = false;

								}

								if (writeopcode == 9) {
									//printf("wsClients[%d]->outright=%d clean\r\n", socketIDmap[i], wsClients[socketIDmap[i]]->outright);
									if (wsClients[socketIDmap[i]]->outright_message != nullptr) delete[] wsClients[socketIDmap[i]]->outright_message;
									wsClients[socketIDmap[i]]->outright = 0;
									wsClients[socketIDmap[i]]->outright_message = nullptr;
									wsClients[socketIDmap[i]]->outright_message_length = 0;
									wsClients[socketIDmap[i]]->outright_send = false;

								}

















							}


						}
					}
				
}

			}
		}


		if (time(NULL) >= nextPingTime) {
			wsCheckIdleClients();
			nextPingTime = time(NULL) + 20;
		}

		if (callPeriodic != NULL)
			callPeriodic();
	}


}
void webSocket::stopServer() {
	for (int i = 0; i < wsClients.size(); i++) {
		if (wsClients[i] != NULL) {
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



void writeInteger(char*, size_t &, int , int);
void writeString(char*, size_t &, char*);
void writeDouble(char*, size_t &, double);
void writeFloat(char*, size_t &, float);

char* CreateStep_1(int&);
char* CreateStep_2(int&);
void CreatePlus_2(wsClient*);
void CreateOutright_2(wsClient*);
void getSports();
void getEvents(time_t,int);
void getCategoriesTournaments();
int getTournament(Tournament*, bool);
int getEventFixture(Event*);
int getEventSummary(Event*);
void startRecovery();
void getMarkets();
void postBooked(int);
int getPlayer(Player*);
int getCompetitor(Competitor*);
int getBetstops();
int getMatchstatus();
int getVariantMarkets(Market*, char*);
int httpsRequest(char*, char*, char*, int);
int httpsServer();
char** split(char*, char*);
void replace(char* &,char*, char*);
void replace_substr(char* &, char*, char*);
void saveEventToFile(Event*);
void loadEventsFromFiles();
void saveMarketToFile(Market*);
void loadMarketsFromFiles();
void saveTournamentToFile(Tournament*);
void loadTournamentsFromFiles();
void saveCategoryToFile(Category*);
void loadCategoriesFromFiles();
void saveCompetitorToFile(Competitor*);
void loadCompetitorsFromFiles();
void savePlayerToFile(Player*);
void loadPlayersFromFiles();
char* SendframeEncode(char*,int,int &);
void openHandler(int);
void closeHandler(int);
void messageHandler(int,string );
void radarMessageHandler(char*,int);
void periodicHandler();
void die(const char *, ...);
void die_on_error(int, char const*);
void die_on_amqp_error(amqp_rpc_reply_t, char const *);
void amqp_dump(void const *, size_t);
uint64_t now_microseconds(void);
//void microsleep(int);
void rabbitmqssl();
static void run(amqp_connection_state_t);

void rabbitmqssl_mts();
static void run_mts(amqp_connection_state_t);
static void send_batch(amqp_connection_state_t , char const *, int, int );
static int rows_eq(int *, int *);
static void dump_row(long, int, int *);
webSocket server;



// izzet: Reverse Lookup hash tables for Line objects

// we supply an id (market,event,tournament or simple) and return all the lines. so key is an int (id) and values is a vector of Line object ptrs.

typedef unordered_map<int, unordered_set<int>*> id2lines_index;
enum LineCat { LC_EVENT, LC_TOURN, LC_SIMPLE };

void test_delete();
void delete_line(Line &);
void delete_line_cat(int, LineCat);

id2lines_index market2lines;   // lookup based on market_id
							   // lookups based on event_id | tournament_id | simple_id
id2lines_index event2lines;
id2lines_index tourn2lines;
id2lines_index simple2lines;

unordered_map<string, int> compound2line_index;    // (event_id | tournament_id | simple_id) + market_id + specifiers_value


												   // whenever a new Line is created call this function to update reverse lookup tables
void insert_line(Line& line, const int line_index) {
	bool debug_output = false;
	int cat_id;
	string compound_key;
	string cat_name;

	// hash table for case1: market_id. for all Line categories we update market2lines
	const int market_id = line.market_id;
	auto it = market2lines.find(market_id);   // market_id is the key
	if (it == market2lines.end()) {   // key not found, we are seeing this market_id the first time.
		market2lines[market_id] = new unordered_set<int>();  // so create an empty vector
	}
	market2lines[market_id]->insert(line_index);   // insert new line's index to the set

												   // now let's determine the category and the related lookup tables that will be updated
	id2lines_index* cat2lines;
	if (line.event_id > 0) {
		cat_id = line.event_id;
		cat_name = "EVENT";
		cat2lines = &event2lines;
		//if (rand() % 100 != 0) debug_output = false;   // only output 1/100 of these lines
	}
	else if (line.tournament_id > 0) {
		cat_id = line.tournament_id;
		cat_name = "TOURNAMENT";
		cat2lines = &tourn2lines;
	}
	else if (line.simple_id > 0) {
		cat_id = line.simple_id;
		cat_name = "SIMPLE";
		cat2lines = &simple2lines;
	}
	else {
		cout << "Something wrong with this line: " << line.name << endl;
		return;
	}

	// update hash table for cases 2,3,4:  event, tournament or simple
	auto cat_it = cat2lines->find(cat_id);   // cat_id is the key
	if (cat_it == cat2lines->end()) {   // key not found, we are seeing this cat_id the first time.
		(*cat2lines)[cat_id] = new unordered_set<int>();  // so create an empty set
	}
	(*cat2lines)[cat_id]->insert(line_index);   // insert new line to the set
	
	/*if (debug_output) {
		cout << "New line for " << cat_name << "=" << cat_id << endl;
		cout << "\tTotal lines: " << (*cat2lines)[cat_id]->size() << endl;
	}*/

	// update hash table for cases 5,6,7:  market_id + (event_id | tournament_id | simple_id) + specifiers_value 
	// let's first build our key

	compound_key = line.getCompoundKey();
	compound2line_index[compound_key] = line_index;   // insert new line's index as value
	/*
	if (debug_output) {
		cout << "\t" << "Key for " << line.name << ": " << compound_key << endl;
	}


	if (line.tournament_id > 0) {  // let's pause for checking
		cout << "Finally a tournament related line. Hit enter to continue ...";
		getchar();
	}
	
	if ((lines_l + 1) % 50 == 0) {
		cout << "TOTAL LINES = " << (lines_l + 1) << endl;
	}
	if ((lines_l + 1) % 1000 == 0) {
		test_delete();
		cout << "Hit enter to continue..." << endl;
		// getchar();
	}
	*/

	return;
}
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
	id2lines_index* cat2lines;
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
						   // cat2lines[cat_id] = NULL;
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
	id2lines_index* cat2lines;
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

int reload_step_1 = 1;
int booking = 0;
//std::mutex _mutex;





int main() {
	/*
	loadCompetitorsFromFiles();

	HANDLE File;
	DWORD l = 0;
	char buf[20];
	int i = 0;
	char file_path[MAX_PATH];
	char https_path[MAX_PATH];
	char* recvbuf = new char[DEFAULT_BUFLEN];
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

	File = CreateFile(file_path, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	l = SetFilePointer(File, 0, 0, FILE_BEGIN);

	for (i = 0; i < len - 4; i++) if (recvbuf[i] == '\r' && recvbuf[i + 1] == '\n' && recvbuf[i + 2] == '\r' && recvbuf[i + 3] == '\n') break;
	
	WriteFile(File, ((char*)((char*)recvbuf + i + 4)), (len - i - 4), &l, NULL);
	CloseHandle(File);

}

	delete recvbuf;
	return 0;

*/	



	for (int i = 0; i < MAX_EVENTS; i++) events_id[i] = NULL;
	for (int i = 0; i < MAX_EVENTS; i++) events_show[i] = NULL;
	for (int i = 0; i < MAX_LINES; i++) lines_id[i] = NULL;
	for (int i = 0; i < MAX_TOURNAMENTS; i++) tournaments_id[i] = NULL;
	for (int i = 0; i < MAX_TOURNAMENTS; i++) seasons_id[i] = NULL;
	for (int i = 0; i < MAX_TOURNAMENTS; i++) simples_id[i] = NULL;
	for (int i = 0; i < MAX_CATEGORIES; i++) categories_id[i] = NULL;
	for (int i = 0; i < MAX_SPORTS; i++) sports_id[i] = NULL;
	for (int i = 0; i < MAX_COMPETITORS; i++) competitors_id[i] = NULL;
	for (int i = 0; i < MAX_PLAYERS; i++) players_id[i] = NULL;
	for (int i = 0; i < MAX_MARKETS; i++) markets_id[i] = NULL;
	for (int i = 0; i < MAX_MARKETS; i++) max_markets_in[i] = 2;
	for (int i = 0; i < MAX_BETSTOPS; i++) betstops_id[i] = NULL;
	for (int i = 0; i < MAX_MATCHSTATUS; i++) matchstatus_id[i] = NULL;
	for (int j = 0; j < STEP_QUEUE; j++) {
		array_data_step_2[j] = nullptr;
		array_data_step_1[j] = nullptr;
		data_step_len_1[j] = 0;
		data_step_len_2[j] = 0;
	}
	for (int j = 0; j < AMQP_QUEUE; j++) AMQP_message[j] = new char[AMQP_BUFLEN];
	





using namespace std;
timestamp();
hThread1 = CreateThread(NULL, 16777216, &BetradarGetThread, 0, THREAD_TERMINATE, &dwThreadID1);
hThread2 = CreateThread(NULL, 16777216, &BetradarProcessThread, 0, THREAD_TERMINATE, &dwThreadID2);
//hThread3 = CreateThread(NULL, 16777216, &MTSGetThread, 0, THREAD_TERMINATE, &dwThreadID3);

int port = 1443;

//server.setOpenHandler(openHandler);
//server.setCloseHandler(closeHandler);
//server.setMessageHandler(messageHandler);
//server.setPeriodicHandler(periodicHandler);

//while (port == 1443) Sleep(1);
server.startServer(port);

return 0;

	
}
DWORD WINAPI BetradarGetThread(LPVOID lparam) {

	bool full_data = false;
	//int recvbuflen = DEFAULT_BUFLEN;
	//recvbuf = new char[DEFAULT_BUFLEN];


	getSports();

	if (getBetstops() != -1) std::printf("Load betstops success. Numbers of betstops : %d\r\n", betstops_l);
	if (getMatchstatus() != -1) std::printf("Load matchstatus success. Numbers of matchstatus : %d\r\n", matchstatus_l);


	if (booking > 0) {
		getEvents(0, 10);
		return 0;
	}


	if (full_data == false) {
		//getMarkets();
		//getEvents(0, 10);
		//return 0;
		loadMarketsFromFiles();
		loadCategoriesFromFiles();
		loadTournamentsFromFiles();
		loadEventsFromFiles();
		loadCompetitorsFromFiles();
		loadPlayersFromFiles();

	}


	if (full_data == true) {
		getMarkets();
		getCategoriesTournaments();
		getEvents(0, 180);
		for (int i = 0; i < tournaments_l; i++) saveTournamentToFile(&tournaments[i]);
		for (int i = 0; i < categories_l; i++) saveCategoryToFile(&categories[i]);
		for (int i = 0; i < events_l; i++) 	getEventFixture(&events[i]);
		for (int i = 0; i < tournaments_l; i++) getTournament(&tournaments[i], true);

	}

	//CreateStep_1();

	startRecovery();
	rabbitmqssl();
	//sdkSocket();
	//httpsServer();
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
	//char* maxbuf = nullptr;// new char[AMQP_BUFLEN];
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
	bool print = false;
	bool debug_output = false;
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
	int* outcome_team = new int[500];
	float* outcome_probabilities = new float[500];
	float* outcome_odds = new float[500];
	for (int i = 0; i < 500; i++) outcome_name[i] = NULL;
	Line* _line = new Line();
	char* socket_message_big = new char[145000];
	char* buffer = new char[145000];
	size_t offset = 0;
	size_t retry_offset = 0;
	int event_lines_l = 0;
	char* zip_message = nullptr;
	int zip_len = 0;
	char* encode_message;// = SendframeEncode(zip_message, zip_len, len);
	int encode_message_len = 0;
	char* socket_message_little = new char[4096];
	int outcomeNameError = 0;
	bool new_message_arrived = false;
	vector<int> clientIDs;
	
	for (;;) {
		
		
		if (recovery_state == 0) {
			
			if (new_message_arrived == true) GenerateBigStep(); 		
			//if (!server.ws_clients_flag.test_and_set(std::memory_order_acquire)) {
				clientIDs.clear();
				clientIDs = server.getClientIDs();
				for (i = 0; i < clientIDs.size(); i++) {
					if (server.wsClients[clientIDs[i]] == NULL || server.wsClients[clientIDs[i]]->timestamp > 0)  continue;
					if (server.wsClients[clientIDs[i]]->plus_create == true && server.wsClients[clientIDs[i]]->plus_send == false)
					CreatePlus_2(server.wsClients[clientIDs[i]]);
					if (server.wsClients[clientIDs[i]]->outright_create == true && server.wsClients[clientIDs[i]]->outright_send == false)
				    CreateOutright_2(server.wsClients[clientIDs[i]]);
					
					
				}
			
			
				//server.ws_clients_flag.clear(std::memory_order_release);}


		}


		//int p2 = timestamp();
		//p2 = p2 - p1;
		//printf("GenerateBigStep=%dms\r\n",p2);

		status = 0;
		//printf("process 1\r\n");
		//while (amqp_lock_flag.test_and_set(std::memory_order_acquire));
		//printf("process 2\r\n");
		//if (amqp_empty_flag == true) { //printf("process 3\r\n");  
		//amqp_lock_flag.clear(std::memory_order_release); new_message_arrived = false; continue; }
		//std::strncpy(maxbuf, AMQP_message, AMQP_message_len);
		//maxbuf = AMQP_message[process_index];
		//printf("process 4\r\n");
		//amqp_empty_flag = true;
		//maxbuf[AMQP_message_len] = 0;
		//amqp_lock_flag.clear(std::memory_order_release);
		//new_message_arrived = true;
		//printf("process 5\r\n");
		
		socket_message_big[0] = 0;
		offset = 0;
		if (process_index >= rabbit_index) { new_message_arrived = false; continue; }
		if(debug_output==true) printf("process_index=%d\r\n", process_index);
		if (debug_output == true) printf("rabbit_index=%d\r\n", rabbit_index);

		//printf("process_index=%d\r\n", process_index);
		new_message_arrived = true;
		if (debug_output == true) printf("doc.parse<0>\r\n");
		doc.parse<0>(AMQP_message[process_index%AMQP_QUEUE]);
		if (debug_output == true) printf("doc.parse<0> end length=%d\r\n", strlen(AMQP_message[process_index%AMQP_QUEUE]));
		process_index++;
		//new_message_arrived = false;

		if (doc.first_node() == NULL) {
			if (debug_output == true) printf("doc null\r\n");
			new_message_arrived = false; continue;
		}
		//new_message_arrived = true;




		if (std::strcmp("fixture_change", doc.first_node()->name()) == 0) {
			if (debug_output == true) printf("fixture_change\r\n");
			type_radar = 0;
			event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
			if (event_id == 0) { event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 10)); type_radar = 3; }
			if (event_id == 0) { event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 14)); type_radar = 1; }
			if (event_id == 0) { event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 21)); type_radar = 2; }

			
			if (debug_output == true) printf("fixture_change type_radar=%d\r\n", type_radar);

			if (type_radar == 2) {
				if (event_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nssimple id out of MAX_TOURNAMENTS in run fixture_change %d\r\n", event_id); continue; }
				if (simples_id[event_id] == NULL) {
					std::printf("Simple tournament not found. Run getTournament(). simple_id=%d\r\n", event_id);
					tournaments[tournaments_l].id = 0;
					tournaments[tournaments_l].simple_id = event_id;
					tournaments[tournaments_l].type_radar = 2;
					if (getTournament(&tournaments[tournaments_l], false) == -1) { std::printf("ERROR!\r\nTournaments simple id not found in run fixture change simple %d\r\n", event_id); continue; }
					tournaments_l++;

				}
				else if (getTournament(simples_id[event_id], false) == -1) { std::printf("ERROR!\r\nTournaments simple id not found in run fixture %d\r\n", event_id); continue; }
				std::printf("fixture_change succes for tournamnet simple id=%d\r\n", event_id);


			}
			if (type_radar == 3) {
				if (event_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nsseason id out of MAX_TOURNAMENTS in run fixture change %d\r\n", event_id); continue; }
				if (seasons_id[event_id] == NULL) {
					std::printf("Tournament not found in run fixture change. Run getTournament(). season_id=%d\r\n", event_id);
					tournaments[tournaments_l].id = 0;
					tournaments[tournaments_l].season_id = event_id;
					tournaments[tournaments_l].type_radar = 0;
					if (getTournament(&tournaments[tournaments_l], false) == -1) { std::printf("ERROR!\r\nTournament season id not found in run %d\r\n", event_id); continue; }
					else {
						if (seasons_id[event_id] == NULL) {
							std::printf("ERROR!\r\nTournament season id not found after succes in getTournament run %d\r\n", event_id);

							continue;
						}
						tournaments_l++; std::printf("fixture_change succes for tournamnet season id=%d\r\n", event_id);
					}
				}
				else if (getTournament(seasons_id[event_id], false) == -1) { std::printf("ERROR!\r\n getTournament in fixture_change season id =%d\r\n", event_id); continue; }

				std::printf("fixture_change succes for tournamnet season id=%d\r\n", event_id);

			}
			if (type_radar < 2) {
				if (event_id >= MAX_EVENTS) { std::printf("ERROR DATA!\r\nsevent id out of MAX_EVENTS in run %d\r\n", event_id); continue; }
				if (events_id[event_id] == NULL) {
					std::printf("Event not found in fixture_change. %d\r\n", event_id);
					k = events_l; events_l++;
					events[k].id = event_id; events[k].type_radar = type_radar;
					events_id[event_id] = &events[k];
				}
				if (getEventFixture(events_id[event_id]) == -1) { std::printf("fixtur_change error. %d\r\n", event_id); continue; }
				std::printf("fixture_change success. event_id=%d \r\n", event_id);

				if (recovery_state == 0) {
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
					writeInteger(buffer, offset, _event->start_time + 4 * 3600, 4);
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

					if (event2lines.find(_event->id) == event2lines.end()) writeInteger(buffer, offset, 0, 2);
					else writeInteger(buffer, offset, event2lines[_event->id]->size(), 2);
					//retry_offset = offset;
					//offset += 2;
					event_lines_l = 0;
					writeInteger(buffer, offset, event_lines_l, 2);
			

					if (debug_output == true) printf("fixture radarmessagehandler\r\n");

					zip_len = gzip(buffer, offset, zip_message, 2);
					//delete[] buffer;
					if (zip_len > 1)
					{
						encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
						//while (server.ws_clients_flag.test_and_set(std::memory_order_acquire));
						radarMessageHandler(encode_message, encode_message_len);
					
						//server.ws_clients_flag.clear(std::memory_order_release);
						//printf("encode_message_len=%d\r\n", encode_message_len);
						delete[] encode_message;
						encode_message = nullptr;

					}
					delete[] zip_message;
					zip_message = nullptr;
					if (debug_output == true) printf("fixture end radarmessagehandler\r\n");




	}








			}

		}
		else

			if (std::strcmp("odds_change", doc.first_node()->name()) == 0) {
				type_radar = 0;
				event_id = 0;
				
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
				//if (event_id > 0 && doc.first_node()->first_attribute("event_id")->value()[3] == 's') printf(doc.first_node()->first_attribute("event_id")->value());
	
				if (event_id == 0) { event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 10)); type_radar = 3; }
				if (event_id == 0) { event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 14)); type_radar = 1; }
				if (event_id == 0) { event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 21)); type_radar = 2; }
				//2  sr:simple_tournament:
				//0  sr:match:
		        //3  sr:season:  
				//1  sr:race_event:  

				if (event_id == 0) {
					std::printf("event_id error=0\r\n"); std::printf(doc.first_node()->first_attribute("event_id")->value());
					continue;
				}
				
				if (debug_output == true) printf("odds_change type_radar=%d\r\n", type_radar);
	
				if (type_radar == 2) {
				
					if (event_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nssimple id out of MAX_TOURNAMENTS in run odds_change %d\r\n", event_id); continue; }
					if (simples_id[event_id] == NULL) {
						std::printf("Simple tournament not found. Run getTournament(). simple_id=%d\r\n", event_id);
						tournaments[tournaments_l].id = 0;
						tournaments[tournaments_l].simple_id = event_id;
						tournaments[tournaments_l].type_radar = 2;
						if (getTournament(&tournaments[tournaments_l], false) == -1) { std::printf("ERROR!\r\nTournaments simple id not found in run simple %d\r\n", event_id); continue; }
						tournaments_l++;

					}

					if (simples_id[event_id] == NULL) { std::printf("ERROR!\r\nTournaments simple id not found after succes in getTournament run simple %d\r\n", event_id); continue; }
                    _tournament = simples_id[event_id];

					if (_tournament->end_date == 0) { if (getTournament(_tournament, false) == -1)  std::printf("ERROR!\r\nTournaments simple id not found in run simple for change end_date %d\r\n", event_id); 
					else std::printf("\r\nTournaments simple id change end_date succes%d\r\n", event_id);}


					if (_tournament->sport_id >= MAX_SPORTS) { std::printf("ERROR DATA!\r\nstournament sport_id out of MAX_SPORTS in run simple%d\r\n", _tournament->sport_id); continue; }

					if (sports_id[_tournament->sport_id] == NULL) { std::printf("Sport not found in run simple. Run getSports. sport_id=%d\r\n", _tournament->sport_id); getSports(); }

					if (recovery_state == 0) {
						writeInteger(buffer, offset, 1, 2);
						writeInteger(buffer, offset, type_radar, 1);
						writeInteger(buffer, offset, event_id, 4);
						writeInteger(buffer, offset, _tournament->end_date + 4 * 3600, 4);
						retry_offset = offset;
						offset += 2;
						event_lines_l = 0;
					}

					if (print == true) {
						std::printf("\r\n***************************************************\r\n");
						std::printf("Simple id: %d\r\n", event_id);
						std::printf("NAME:"); std::printf(_tournament->name);
						std::printf("\r\n");
					}
					std::sprintf(socket_message_little, "\r\n***************************************************\r\n");
					std::strcat(socket_message_big, socket_message_little);
					std::sprintf(socket_message_little, "Simple id: %d\r\n", event_id);
					std::strcat(socket_message_big, socket_message_little);
					std::sprintf(socket_message_little, "NAME:");
					std::strcat(socket_message_big, socket_message_little);
					std::sprintf(socket_message_little, "\r\n");





					if (print == true) {
						std::printf(sports_id[_tournament->sport_id]->name); std::printf("\r\n");
					}
					std::strcat(socket_message_big, sports_id[_tournament->sport_id]->name);
					std::strcat(socket_message_big, "\r\n");



					if (_tournament->category_id >= MAX_CATEGORIES) { std::printf("ERROR DATA!\r\ntournament category_id out of MAX_CATEGORIES in run simple %d\r\n", _tournament->category_id); continue; }
					if (categories_id[_tournament->category_id] == NULL) {
						std::printf("Category not found. Run getTournament(). category_id=%d\r\n", _tournament->category_id);
						if (getTournament(simples_id[_tournament->simple_id], false) == -1);  continue;
					}
					categories_id[_tournament->category_id]->outrights = 1;
					if (print == true) {
						std::printf(categories_id[_tournament->category_id]->name); std::printf("\r\n");
						std::printf("\r\n***************************************************\r\n");
					}
					//std::sprintf(socket_message_little, "\r\n***************************************************\r\n");
					std::strcat(socket_message_big, categories_id[_tournament->category_id]->name);
					std::strcat(socket_message_big, "\r\n\r\n***************************************************\r\n");




					xml_node<> * odds = doc.first_node()->first_node("odds");

					if (odds != NULL) {
						betstop_reason = 0;
						if (odds->first_attribute("betstop_reason")) betstop_reason = atoi(odds->first_attribute("betstop_reason")->value());
						_line->tournament_id = 0;
						_line->event_id = 0;
						_line->simple_id = _tournament->simple_id;
						_line->betstop_reason = betstop_reason;

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
							if (markets_id[_line->market_id] == NULL) {
								std::printf("ERROR DATA!\r\nmarket id not found in run%d\r\n", _line->market_id); continue;
							};
							if (markets_id[_line->market_id][0] == NULL) {
								std::printf("ERROR DATA!\r\nmarket id 0 not found in run%d\r\n", _line->market_id); continue;
							};
							_line->variant = markets_id[_line->market_id][0]->variant;
							_line->type = markets_id[_line->market_id][0]->type;
							if (_line->specifier_number > 0) for (q = 0; q < _line->specifier_number; q++) {
								if (_line->specifier[q] != NULL) delete[] _line->specifier[q]; _line->specifier[q] = NULL;
								if (_line->specifier_value[q] != NULL)  delete[] _line->specifier_value[q]; _line->specifier_value[q] = NULL;
							}
							if (_line->specifier != NULL) { delete[] _line->specifier; _line->specifier = NULL; }
							if (_line->specifier_value != NULL) { delete[] _line->specifier_value; _line->specifier_value = NULL; }
							_line->specifier_number = 0;
							if (_line->extended_specifier_number > 0) for (q = 0; q < _line->extended_specifier_number; q++) {
								if (_line->extended_specifier[q] != NULL) delete[] _line->extended_specifier[q];
								if (_line->extended_specifier_value[q] != NULL)  delete[] _line->extended_specifier_value[q];
							}
							if (_line->extended_specifier != NULL) { delete[] _line->extended_specifier; _line->extended_specifier = NULL; }
							if (_line->extended_specifier_value != NULL) { delete[] _line->extended_specifier_value; _line->extended_specifier_value = NULL; }
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


								for (u = 0; u < max_markets_in[_line->market_id]; u++) if (markets_id[_line->market_id][u] != NULL && markets_id[_line->market_id][u]->variable_text != NULL && std::strcmp(_line->specifier_value[_line->variant], markets_id[_line->market_id][u]->variable_text) == 0) break;
								if (outcomeNameError == 1 || u == max_markets_in[_line->market_id]) {
									std::printf("Variant market1 not found in run market_id=%d variant=", _line->market_id);  std::printf(_line->specifier_value[_line->variant]);  std::printf(" getVariantMarkets\r\n"); if (getVariantMarkets(markets_id[_line->market_id][0], _line->specifier_value[_line->variant]) == -1) { std::printf("variant market not found "); continue; }
									for (u = 0; u < max_markets_in[_line->market_id]; u++) if (markets_id[_line->market_id][u] != NULL && markets_id[_line->market_id][u]->variable_text != NULL && std::strcmp(_line->specifier_value[_line->variant], markets_id[_line->market_id][u]->variable_text) == 0) break;
								}
								_line->market = markets_id[_line->market_id][u];
								if (outcomeNameError == 1)outcomeNameError = 2;

								if (_line->type == 3) z = 16;
							}
							else { _line->market = markets_id[_line->market_id][0]; if (_line->type == 0) z = 0; else if (_line->type == 1) z = 10; else if (_line->type == 2) z = 14; else if (_line->type == 3) z = 16; }
							outcome_number = 0;

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
								if (outcome_name[outcome_number] != NULL) delete[] outcome_name[outcome_number]; outcome_name[outcome_number] = NULL;
								if (outcome_node->first_attribute("name")) {
									outcome_name[outcome_number] = new char[strlen(outcome_node->first_attribute("name")->value()) + 1];
									std::strcpy(outcome_name[outcome_number], outcome_node->first_attribute("name")->value());

								}

								outcome_number++;

							}




							if (_line->outcome_number > 0) { for (int i = 0; i < _line->outcome_number; i++) if (_line->outcome_name[i] != NULL) delete[] _line->outcome_name[i]; };


							if (_line->outcome_id != NULL) delete[] _line->outcome_id; if (_line->outcome_active != NULL) delete[] _line->outcome_active; if (_line->outcome_team != NULL) delete[] _line->outcome_team; if (_line->outcome_odds != NULL) delete[] _line->outcome_odds;
							if (_line->outcome_probabilities != NULL) delete[] _line->outcome_probabilities; if (_line->outcome_name != NULL) delete[] _line->outcome_name;
							_line->outcome_probabilities = NULL; _line->outcome_name = NULL; _line->outcome_id = NULL; _line->outcome_odds = NULL; _line->outcome_active = NULL;
							_line->outcome_team = NULL;



							_line->outcome_number = outcome_number;
							if (_line->outcome_number > 0) {
								_line->outcome_name = new char*[_line->outcome_number];
								_line->outcome_id = new int[_line->outcome_number];
								_line->outcome_team = new int[_line->outcome_number];
								_line->outcome_active = new int[_line->outcome_number];
								_line->outcome_probabilities = new float[_line->outcome_number];
								_line->outcome_odds = new float[_line->outcome_number];


								if (_line->name != NULL) delete[] _line->name;


								_line->name = new char[strlen(_line->market->name) + 1];
								std::strcpy(_line->name, _line->market->name);
								for (int i = 0; i < _line->specifier_number; i++) {
									if (i == _line->variant) continue;

									replace(_line->name, _line->specifier[i], _line->specifier_value[i]);
								}
								if (simples_id[_line->simple_id]->name != NULL) replace(_line->name, "$event", simples_id[_line->simple_id]->name);


								if (print == true) {

									std::printf("\r\n"); std::printf(_line->name); std::printf("\r\n"); std::printf("------------------------------------------------------------------------------\r\n");
								}

								//std::sprintf(socket_message_little, "\r\n***************************************************\r\n");
								std::strcat(socket_message_big, "\r\n");
								std::strcat(socket_message_big, _line->name);
								std::strcat(socket_message_big, "\r\n------------------------------------------------------------------------------\r\n");






								for (int i = 0; i < _line->outcome_number; i++) {
									_line->outcome_name[i] = NULL;
									_line->outcome_id[i] = outcome_id[i];
									_line->outcome_active[i] = outcome_active[i];
									_line->outcome_odds[i] = outcome_odds[i];
									_line->outcome_team[i] = outcome_team[i];
									_line->outcome_probabilities[i] = outcome_probabilities[i];


									if (_line->type == 0) {
										if (_line->outcome_id[i] == _line->market->outcome_id[i]) u = i;
										else
											for (u = 0; u < _line->market->outcome_number; u++) if (_line->outcome_id[i] == _line->market->outcome_id[u]) break;

										if (u < _line->market->outcome_number) {
											_line->outcome_name[i] = new char[strlen(_line->market->outcome_name[u]) + 1];
											std::strcpy(_line->outcome_name[i], _line->market->outcome_name[u]);

										}
										else {
											std::printf("Eror. Outcome name not found. market_id=%d _line->outcome_id[i]=%d GoTo GetVarianMarket \r\n", _line->market_id, _line->outcome_id[i]);
											_line->outcome_name[i] = new char[2];
											std::strcpy(_line->outcome_name[i], " ");
											if (_line->market->variant > -1) printf("_line->market->variant=%s\r\n", _line->market->variable_text);
											if (outcomeNameError == 0) outcomeNameError = 1;


										}

										for (int j = 0; j < _line->specifier_number; j++) {
											if (j == _line->variant) continue;

											replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
										}

										if (simples_id[_line->simple_id]->name != NULL) replace(_line->outcome_name[i], "$event", simples_id[_line->simple_id]->name);



										if (print == true) {

											std::printf(_line->outcome_name[i]); std::printf("\t");
											std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
											std::printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
										}
										//std::sprintf(socket_message_little, "\r\n***************************************************\r\n");
										std::strcat(socket_message_big, _line->outcome_name[i]);
										std::strcat(socket_message_big, "\t");
										std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
										std::strcat(socket_message_big, socket_message_little);
										std::strcat(socket_message_big, "\t");
										std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
										std::strcat(socket_message_big, socket_message_little);




									}

									if (_line->type == 1) {
										if (_line->outcome_id[i] >= MAX_PLAYERS) {
											std::printf("ERROR in run. player_id out of MAX_PLAYERS. _line->outcome_id[i]=%d  _line->market_id=%d simple_id=%d\r\n", _line->outcome_id[i], _line->market_id, _line->simple_id);
											continue;

										}
										if (_line->outcome_team[i] != 3) {
											if (players_id[_line->outcome_id[i]] == NULL) {
												std::printf("Player2 id=%d not found in market id=%d in simple_id=%d  in run function . getPlayer\r\n", _line->outcome_id[i], _line->market_id, _line->simple_id);
												players[players_l].id = _line->outcome_id[i]; if (getPlayer(&players[players_l]) == -1)
												{
													std::printf("error player id=%d  not found \r\n ", _line->outcome_id[i]); //continue;
													_line->outcome_name[i] = new char[2];
													std::strcpy(_line->outcome_name[i], " ");
												}
												else players_l++;
											}

											if (_line->outcome_name[i] == NULL) {
												_line->outcome_name[i] = new char[strlen(players_id[_line->outcome_id[i]]->name) + 1];
												std::strcpy(_line->outcome_name[i], players_id[_line->outcome_id[i]]->name);
											}

										}

										if (_line->outcome_team[i] == 3) {

											for (u = 0; u < _line->market->outcome_number; u++) if (_line->market->outcome_id[u] == _line->outcome_id[i]) break;
											if (u < _line->market->outcome_number) {
												_line->outcome_name[i] = new char[strlen(_line->market->outcome_name[u]) + 1];
												std::strcpy(_line->outcome_name[i], _line->market->outcome_name[u]);

												for (int j = 0; j < _line->specifier_number; j++) {
													if (j == _line->variant) continue;
													replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
												}

												if (simples_id[_line->simple_id]->name != NULL)	replace(_line->outcome_name[i], "$event", simples_id[_line->simple_id]->name);




											}
											else {
												_line->outcome_name[i] = new char[2];
												std::strcpy(_line->outcome_name[i], " ");
											}



										}





										if (print == true) {



											std::printf(_line->outcome_name[i]); std::printf("\t");
											std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
											printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
										}

										std::strcat(socket_message_big, _line->outcome_name[i]);
										std::strcat(socket_message_big, "\t");
										std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
										std::strcat(socket_message_big, socket_message_little);
										std::strcat(socket_message_big, "\t");
										std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
										std::strcat(socket_message_big, socket_message_little);






									}

									if (_line->type == 2) {
										if (_line->outcome_team[i] != 3) {
											if (_line->outcome_id[i] >= MAX_COMPETITORS) {
												std::printf("ERROR in run. competitor_id out of MAX_COMPETITORS. _line->outcome_id[i]=%d  _line->market_id=%d simple_id=%d\r\n", _line->outcome_id[i], _line->market_id, _tournament->simple_id);
												continue;
											}
											if (competitors_id[_line->outcome_id[i]] == NULL) {
												std::printf("Competitor id=%d not found in market id=%d in tournament_simple_id=%d  in run simple. getTournament\r\n", _line->outcome_id[i], _line->market_id, _tournament->simple_id);
												if (getTournament(simples_id[_tournament->simple_id], false) == -1)
													std::printf("ERROR!\r\nTournaments not found in run simple %d \r\n", _tournament->simple_id);
											}

											if (competitors_id[_line->outcome_id[i]] == NULL) {
												std::printf("\r\nCompetitors id=%d not found in tournament simple_id=%d after getTournament . Run getCompetitor\r\n", _line->outcome_id[i], _tournament->simple_id);
												competitors[competitors_l].id = _line->outcome_id[i];
												if (getCompetitor(&competitors[competitors_l]) == -1) {
													std::printf(" Error getCompetitor in run season. line type= 2 id competitor=%d \r\n", _line->outcome_id[i]);
													_line->outcome_name[i] = new char[2];
													std::strcpy(_line->outcome_name[i], " ");
												}
												else competitors_l++;
											}

											if (competitors_id[_line->outcome_id[i]] != NULL) { _line->outcome_name[i] = new char[strlen(competitors_id[_line->outcome_id[i]]->name) + 1]; std::strcpy(_line->outcome_name[i], competitors_id[_line->outcome_id[i]]->name); }

										}
										else
										{
											for (u = 0; u < _line->market->outcome_number; u++) if (_line->market->outcome_id[u] == _line->outcome_id[i]) break;
											if (u < _line->market->outcome_number) {
												_line->outcome_name[i] = new char[strlen(_line->market->outcome_name[u]) + 1];
												std::strcpy(_line->outcome_name[i], _line->market->outcome_name[u]);
												for (int j = 0; j < _line->specifier_number; j++) {
													if (j == _line->variant) continue;
													replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
												}

												if (_tournament->name != NULL) replace(_line->outcome_name[i], "$event", simples_id[_line->simple_id]->name);
											}
											else { _line->outcome_name[i] = new char[2]; std::strcpy(_line->outcome_name[i], " "); }
										}
										if (print == true) {
											std::printf(_line->outcome_name[i]); std::printf("\t");
											std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
											printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
										}

										std::strcat(socket_message_big, _line->outcome_name[i]);
										std::strcat(socket_message_big, "\t");
										std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
										std::strcat(socket_message_big, socket_message_little);
										std::strcat(socket_message_big, "\t");
										std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
										std::strcat(socket_message_big, socket_message_little);




									}

									if (_line->type == 3) {

										if (_line->outcome_id[i] == _line->market->outcome_id[i]) u = i;
										else
											for (u = 0; u < _line->market->outcome_number; u++) {


												if (_line->outcome_id[i] == _line->market->outcome_id[u]) break;
											}

										if (u < _line->market->outcome_number) {

											_line->outcome_name[i] = new char[strlen(_line->market->outcome_name[u]) + 1];
											std::strcpy(_line->outcome_name[i], _line->market->outcome_name[u]);

										}
										else {
											std::printf("Eror. Outcome name not found. market_id=%d _line->outcome_id[i]=%d\r\n", _line->market_id, _line->outcome_id[i]);

											_line->outcome_name[i] = new char[2];
											std::strcpy(_line->outcome_name[i], " ");
											if (outcomeNameError == 0) outcomeNameError = 1;
											if (_line->market->variant > -1)
												printf("_line->market->variant=%s\r\n", _line->market->variable_text);

										}

										for (int j = 0; j < _line->specifier_number; j++) {
											if (j == _line->variant) continue;

											replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
										}

										if (_tournament->name) replace(_line->outcome_name[i], "$event", simples_id[_line->simple_id]->name);


										//if (_line->market_id == 188 || _line->market_id == 224 || _line->market_id == 485 || _line->market_id == 231 || _line->market_id == 65 || _line->market_id == 383 || _line->market_id == 66) 

										if (print == true) {

											std::printf(_line->outcome_name[i]); std::printf("\t");
											std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
											printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
										}
										std::strcat(socket_message_big, _line->outcome_name[i]);
										std::strcat(socket_message_big, "\t");
										std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
										std::strcat(socket_message_big, socket_message_little);
										std::strcat(socket_message_big, "\t");
										std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
										std::strcat(socket_message_big, socket_message_little);
									}
								}


								if (outcomeNameError == 1 && _line->market->variant > -1) goto outcomeNameError1;
							}



							if (debug_output == true) printf("insertLine _line->type ==%d\r\n", _line->type);

							auto it = compound2line_index.find(_line[0].getCompoundKey());
							if (debug_output == true) {
								printf(_line[0].getCompoundKey().c_str());
								printf("\r\n");
							}
							if (it == compound2line_index.end()) {
								if (debug_output == true) printf("new line add");
								_line[0].id = lines_l;
								if (debug_output == true) printf("new line add1");
								lines[lines_l] = _line[0];
								lines_id[_line[0].id] = &lines[lines_l];
								if (debug_output == true) printf("new line add2");
								insert_line(_line[0], lines_l);
								if (debug_output == true) printf("new line add3");
								lines_l++;
								categories_id[_tournament->category_id]->outrights_id.push_back(_line[0].id);
								if (debug_output == true) printf("new line add finish");

							}
							else {
								if (debug_output == true) printf("line update");
								_line[0].id = it->second;
								if (debug_output == true) printf("line update1");
								lines[it->second] = _line[0];
								if (debug_output == true) printf("line finish");

								//printf("Line Update\r\n");
							}









							if (debug_output == true) printf("end insertLine _line->type ==%d\r\n", _line->type);

							if (recovery_state == 0) {

								if (debug_output == true) printf("write buffer data\r\n");

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
								writeInteger(buffer, offset, _line->outcome_number, 2);
								for (int j = 0; j < _line->outcome_number; j++) {
									writeInteger(buffer, offset, _line->outcome_id[j], 2);
									writeInteger(buffer, offset, _line->outcome_active[j], 1);
									if (_line->type == 1 || _line->type == 2) writeInteger(buffer, offset, _line->outcome_team[j], 1);
									if ((_line->type == 1 || _line->type == 2) && _line->outcome_team[j] != 3)
										writeString(buffer, offset, _line->outcome_name[j]);
									writeInteger(buffer, offset, (int)(_line->outcome_odds[j] * 100), 4);
								}

								writeInteger(buffer, offset, _line->specifier_number, 1);
								for (int j = 0; j < _line->specifier_number; j++) writeString(buffer, offset, _line->specifier_value[j]);


								if (debug_output == true) printf("end write buffer data\r\n");
							}













						}
					}
					if (recovery_state == 0) writeInteger(buffer, retry_offset, event_lines_l, 2);

				}
				if (type_radar == 3) {
			
					if (event_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nsseason id out of MAX_TOURNAMENTS in run %d\r\n", event_id); continue; }
					if (seasons_id[event_id] == NULL) {
						std::printf("Tournament not found. Run getTournament(). season_id=%d\r\n", event_id);
						tournaments[tournaments_l].id = 0;
						tournaments[tournaments_l].season_id = event_id;
						tournaments[tournaments_l].type_radar = 0;
						if (getTournament(&tournaments[tournaments_l], false) == -1) { std::printf("ERROR!\r\nTournaments season id not found in run season %d\r\n", event_id); continue; }
						else tournaments_l++;
					}
					if (seasons_id[event_id] == NULL) { std::printf("ERROR!\r\nTournaments season id not found after succes in getTournament run season %d\r\n", event_id); continue; }
					_tournament = seasons_id[event_id];

					if (_tournament->sport_id >= MAX_SPORTS) { std::printf("ERROR DATA!\r\nstournament sport_id out of MAX_SPORTS in run season%d\r\n", _tournament->sport_id); continue; }

					if (sports_id[_tournament->sport_id] == NULL) { std::printf("Sport not found in run season. Run getSports. sport_id=%d\r\n", _tournament->sport_id); getSports(); }


					if (recovery_state == 0) {
						writeInteger(buffer, offset, 1, 2);
						writeInteger(buffer, offset, type_radar, 1);
						writeInteger(buffer, offset, _tournament->id, 4);
						writeInteger(buffer, offset, _tournament->end_date + 4 * 3600, 4);
						retry_offset = offset;
						offset += 2;
						event_lines_l = 0;
					}



					if (print == true) {
						std::printf("\r\n***************************************************\r\n");
						std::printf("Season id: %d\r\n", event_id);
						std::printf("Tournament id:%d\r\n", _tournament->id);
						std::printf("NAME:"); std::printf(_tournament->name);
						std::printf("\r\nSEASON:"); if (_tournament->season_name != NULL) std::printf(_tournament->season_name); else std::printf(_tournament->name);
						std::printf("\r\n");
					}

					std::strcat(socket_message_big, "\r\n***************************************************\r\n");
					std::sprintf(socket_message_little, "Season id: %d\r\n", event_id);
					std::strcat(socket_message_big, socket_message_little);
					std::sprintf(socket_message_little, "Tournament id:%d\r\n", _tournament->id);
					std::strcat(socket_message_big, socket_message_little);
					std::strcat(socket_message_big, "NAME:");
					std::strcat(socket_message_big, _tournament->name);
					std::strcat(socket_message_big, "\r\nSEASON:");
					if (_tournament->season_name != NULL) std::strcat(socket_message_big, _tournament->season_name);
					else std::strcat(socket_message_big, _tournament->name);
					std::strcat(socket_message_big, "\r\n");



					if (print == true) {
						std::printf(sports_id[_tournament->sport_id]->name); std::printf("\r\n");
					}
					std::strcat(socket_message_big, sports_id[_tournament->sport_id]->name);
					std::strcat(socket_message_big, "\r\n");



					if (_tournament->category_id >= MAX_CATEGORIES) { std::printf("ERROR DATA!\r\ntournament category_id out of MAX_CATEGORIES in run season %d\r\n", _tournament->category_id); continue; }
					if (categories_id[_tournament->category_id] == NULL) {
						std::printf("Category not found. Run getTournament(). category_id=%d\r\n", _tournament->category_id);
						if (getTournament(tournaments_id[_tournament->id], false) == -1);  continue;
						
					}
					categories_id[_tournament->category_id]->outrights = 1;
					if (print == true) {
						std::printf(categories_id[_tournament->category_id]->name); std::printf("\r\n");
						std::printf("\r\n***************************************************\r\n");
					}

					//std::sprintf(socket_message_little, "Season id: %d\r\n", event_id);
					std::strcat(socket_message_big, categories_id[_tournament->category_id]->name);
					std::strcat(socket_message_big, "\r\n");





					xml_node<> * odds = doc.first_node()->first_node("odds");

					if (odds != NULL) {
						betstop_reason = 0;

						if (odds->first_attribute("betstop_reason")) betstop_reason = atoi(odds->first_attribute("betstop_reason")->value());
						_line->tournament_id = _tournament->id;
						_line->event_id = 0;
						_line->simple_id = 0;
						_line->betstop_reason = betstop_reason;

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
							if (markets_id[_line->market_id] == NULL) {
								std::printf("ERROR DATA!\r\nmarket id not found in run%d\r\n", _line->market_id); continue;
							};
							if (markets_id[_line->market_id][0] == NULL) {
								std::printf("ERROR DATA!\r\nmarket id 0 not found in run%d\r\n", _line->market_id); continue;
							};
							_line->variant = markets_id[_line->market_id][0]->variant;
							_line->type = markets_id[_line->market_id][0]->type;
							if (_line->specifier_number > 0) for (q = 0; q < _line->specifier_number; q++) {
								if (_line->specifier[q] != NULL) delete[] _line->specifier[q]; _line->specifier[q] = NULL;;
								if (_line->specifier_value[q] != NULL)  delete[] _line->specifier_value[q]; _line->specifier_value[q] = NULL;
							}
							if (_line->specifier != NULL) { delete[] _line->specifier; _line->specifier = NULL; }
							if (_line->specifier_value != NULL) { delete[] _line->specifier_value; _line->specifier_value = NULL; }
							_line->specifier_number = 0;
							if (_line->extended_specifier_number > 0) for (q = 0; q < _line->extended_specifier_number; q++) {
								if (_line->extended_specifier[q] != NULL) delete[] _line->extended_specifier[q];
								if (_line->extended_specifier_value[q] != NULL)  delete[] _line->extended_specifier_value[q];
							}
							if (_line->extended_specifier != NULL) { delete[] _line->extended_specifier; _line->extended_specifier = NULL; }
							if (_line->extended_specifier_value != NULL) { delete[] _line->extended_specifier_value; _line->extended_specifier_value = NULL; }
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
						outcomeNameError2:	if (_line->variant > -1) {
							z = strlen(_line->specifier_value[_line->variant]) + 1; if (strcmp(_line->specifier[_line->variant], "variant") != 0) { std::printf(_line->specifier[_line->variant]); std::printf("\r\n"); }
							for (u = 0; u < max_markets_in[_line->market_id]; u++) if (markets_id[_line->market_id][u] != NULL && markets_id[_line->market_id][u]->variable_text != NULL && std::strcmp(_line->specifier_value[_line->variant], markets_id[_line->market_id][u]->variable_text) == 0) break;
							if (outcomeNameError == 1 || u == max_markets_in[_line->market_id]) {
								std::printf("Variant market2 not found in run market_id=%d variant=", _line->market_id);  std::printf(_line->specifier_value[_line->variant]);  std::printf("  getVariantMarkets\r\n"); if (getVariantMarkets(markets_id[_line->market_id][0], _line->specifier_value[_line->variant]) == -1) { std::printf("variant market not found "); continue; }
								for (u = 0; u < max_markets_in[_line->market_id]; u++) if (markets_id[_line->market_id][u] != NULL && markets_id[_line->market_id][u]->variable_text != NULL && std::strcmp(_line->specifier_value[_line->variant], markets_id[_line->market_id][u]->variable_text) == 0) break;
							}
							_line->market = markets_id[_line->market_id][u];
							if (outcomeNameError == 1) outcomeNameError = 2;
							if (_line->type == 3) z = 16;
						}
											else { _line->market = markets_id[_line->market_id][0]; if (_line->type == 0) z = 0; else if (_line->type == 1) z = 10; else if (_line->type == 2) z = 14; else if (_line->type == 3) z = 16; }
											outcome_number = 0;

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
												if (outcome_name[outcome_number] != NULL) delete[] outcome_name[outcome_number]; outcome_name[outcome_number] = NULL;
												if (outcome_node->first_attribute("name")) {
													outcome_name[outcome_number] = new char[strlen(outcome_node->first_attribute("name")->value()) + 1];
													std::strcpy(outcome_name[outcome_number], outcome_node->first_attribute("name")->value());

												}

												outcome_number++;

											}




											if (_line->outcome_number > 0) { for (int i = 0; i < _line->outcome_number; i++) if (_line->outcome_name[i] != NULL) delete[] _line->outcome_name[i]; };


											if (_line->outcome_id != NULL) delete[] _line->outcome_id; if (_line->outcome_active != NULL) delete[] _line->outcome_active; if (_line->outcome_team != NULL) delete[] _line->outcome_team; if (_line->outcome_odds != NULL) delete[] _line->outcome_odds;
											if (_line->outcome_probabilities != NULL) delete[] _line->outcome_probabilities; if (_line->outcome_name != NULL) delete[] _line->outcome_name;
											_line->outcome_probabilities = NULL; _line->outcome_name = NULL; _line->outcome_id = NULL; _line->outcome_odds = NULL; _line->outcome_active = NULL;
											_line->outcome_team = NULL;



											_line->outcome_number = outcome_number;
											if (_line->outcome_number > 0) {
												_line->outcome_name = new char*[_line->outcome_number];
												_line->outcome_id = new int[_line->outcome_number];
												_line->outcome_team = new int[_line->outcome_number];
												_line->outcome_active = new int[_line->outcome_number];
												_line->outcome_probabilities = new float[_line->outcome_number];
												_line->outcome_odds = new float[_line->outcome_number];


												if (_line->name != NULL) delete[] _line->name;


												_line->name = new char[strlen(_line->market->name) + 1];
												std::strcpy(_line->name, _line->market->name);
												for (int i = 0; i < _line->specifier_number; i++) {
													if (i == _line->variant) continue;

													replace(_line->name, _line->specifier[i], _line->specifier_value[i]);
												}
												if (tournaments_id[_line->tournament_id]->season_name != NULL) replace(_line->name, "$event", tournaments_id[_line->tournament_id]->season_name);


												if (print == true) {

													std::printf("\r\n"); std::printf(_line->name); std::printf("\r\n"); std::printf("------------------------------------------------------------------------------\r\n");
												}


												//std::sprintf(socket_message_little, "Season id: %d\r\n", event_id);
												std::strcat(socket_message_big, "\r\n");
												std::strcat(socket_message_big, _line->name);
												std::strcat(socket_message_big, "\r\n");
												std::strcat(socket_message_big, "------------------------------------------------------------------------------\r\n");







												for (int i = 0; i < _line->outcome_number; i++) {
													_line->outcome_name[i] = NULL;
													_line->outcome_id[i] = outcome_id[i];
													_line->outcome_active[i] = outcome_active[i];
													_line->outcome_odds[i] = outcome_odds[i];
													_line->outcome_team[i] = outcome_team[i];
													_line->outcome_probabilities[i] = outcome_probabilities[i];


													if (_line->type == 0) {
														if (_line->outcome_id[i] == _line->market->outcome_id[i]) u = i;
														else
															for (u = 0; u < _line->market->outcome_number; u++) if (_line->outcome_id[i] == _line->market->outcome_id[u]) break;

														if (u < _line->market->outcome_number) {
															_line->outcome_name[i] = new char[strlen(_line->market->outcome_name[u]) + 1];
															std::strcpy(_line->outcome_name[i], _line->market->outcome_name[u]);

														}
														else {
															std::printf("Eror. Outcome name not found. market_id=%d _line->outcome_id[i]=%d\r\n", _line->market_id, _line->outcome_id[i]);
															_line->outcome_name[i] = new char[2];
															std::strcpy(_line->outcome_name[i], " ");

															if (_line->market->variant > -1) printf("_line->market->variant=%s\r\n", _line->market->variable_text);
															if (outcomeNameError == 0) outcomeNameError = 1;

														}

														for (int j = 0; j < _line->specifier_number; j++) {
															if (j == _line->variant) continue;

															replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
														}
														if (tournaments_id[_line->tournament_id]->season_name != NULL) replace(_line->outcome_name[i], "$event", tournaments_id[_line->tournament_id]->season_name);



														if (print == true) {

															std::printf(_line->outcome_name[i]); std::printf("\t");
															std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
															std::printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
														}

														std::strcat(socket_message_big, _line->outcome_name[i]);
														std::strcat(socket_message_big, "\t");
														std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
														std::strcat(socket_message_big, socket_message_little);
														std::strcat(socket_message_big, "\t");
														std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
														std::strcat(socket_message_big, socket_message_little);






													}

													if (_line->type == 1) {
														if (_line->outcome_id[i] >= MAX_PLAYERS) {
															std::printf("ERROR in run. player_id out of MAX_PLAYERS. _line->outcome_id[i]=%d  _line->market_id=%d tournament_id=%d\r\n", _line->outcome_id[i], _line->market_id, _line->tournament_id);
															continue;

														}
														if (_line->outcome_team[i] != 3) {
															if (players_id[_line->outcome_id[i]] == NULL) {
																std::printf("Player3 id=%d not found in market id=%d in tournament_id=%d  in run function . getPlayer\r\n", _line->outcome_id[i], _line->market_id, _line->tournament_id);
																players[players_l].id = _line->outcome_id[i]; if (getPlayer(&players[players_l]) == -1)
																{
																	std::printf("error player id=%d  not found \r\n ", _line->outcome_id[i]); //continue;
																	_line->outcome_name[i] = new char[2];
																	std::strcpy(_line->outcome_name[i], " ");
																}
																else players_l++;
															}

															if (_line->outcome_name[i] == NULL) {
																_line->outcome_name[i] = new char[strlen(players_id[_line->outcome_id[i]]->name) + 1];
																std::strcpy(_line->outcome_name[i], players_id[_line->outcome_id[i]]->name);
															}

														}

														if (_line->outcome_team[i] == 3) {

															for (u = 0; u < _line->market->outcome_number; u++) if (_line->market->outcome_id[u] == _line->outcome_id[i]) break;
															if (u < _line->market->outcome_number) {
																_line->outcome_name[i] = new char[strlen(_line->market->outcome_name[u]) + 1];
																std::strcpy(_line->outcome_name[i], _line->market->outcome_name[u]);

																for (int j = 0; j < _line->specifier_number; j++) {
																	if (j == _line->variant) continue;
																	replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
																}

																if (tournaments_id[_line->tournament_id]->season_name != NULL)	replace(_line->outcome_name[i], "$event", tournaments_id[_line->tournament_id]->season_name);

															}
															else {
																_line->outcome_name[i] = new char[2];
																std::strcpy(_line->outcome_name[i], " ");
															}



														}





														if (print == true) {



															std::printf(_line->outcome_name[i]); std::printf("\t");
															std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
															printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
														}

														std::strcat(socket_message_big, _line->outcome_name[i]);
														std::strcat(socket_message_big, "\t");
														std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
														std::strcat(socket_message_big, socket_message_little);
														std::strcat(socket_message_big, "\t");
														std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
														std::strcat(socket_message_big, socket_message_little);






													}

													if (_line->type == 2) {
														if (_line->outcome_team[i] != 3) {
															if (_line->outcome_id[i] >= MAX_COMPETITORS) {
																std::printf("ERROR in run. competitor_id out of MAX_COMPETITORS. _line->outcome_id[i]=%d  _line->market_id=%d tournament_id=%d\r\n", _line->outcome_id[i], _line->market_id, _tournament->id);
																continue;
															}
															if (competitors_id[_line->outcome_id[i]] == NULL) {
																std::printf("Competitor id=%d not found in market id=%d in tournament_id=%d  in run season. getTournament\r\n", _line->outcome_id[i], _line->market_id, _tournament->id);
																if (getTournament(tournaments_id[_tournament->id], false) == -1)
																	std::printf("ERROR!\r\nTournaments not found in run season %d \r\n", _tournament->id);
															}

															if (competitors_id[_line->outcome_id[i]] == NULL) {
																std::printf("\r\nCompetitors id=%d not found in tournament id=%d after getTournament . Run getCompetitor\r\n", _line->outcome_id[i], _tournament->id);
																competitors[competitors_l].id = _line->outcome_id[i];
																if (getCompetitor(&competitors[competitors_l]) == -1) {
																	std::printf(" Error getCompetitor in run season. line type= 2 id competitor=%d \r\n", _line->outcome_id[i]);
																	_line->outcome_name[i] = new char[2];
																	std::strcpy(_line->outcome_name[i], " ");
																}
																else competitors_l++;
															}

															if (competitors_id[_line->outcome_id[i]] != NULL) { _line->outcome_name[i] = new char[strlen(competitors_id[_line->outcome_id[i]]->name) + 1]; std::strcpy(_line->outcome_name[i], competitors_id[_line->outcome_id[i]]->name); }

														}
														else
														{
															for (u = 0; u < _line->market->outcome_number; u++) if (_line->market->outcome_id[u] == _line->outcome_id[i]) break;
															if (u < _line->market->outcome_number) {
																_line->outcome_name[i] = new char[strlen(_line->market->outcome_name[u]) + 1];
																std::strcpy(_line->outcome_name[i], _line->market->outcome_name[u]);
																for (int j = 0; j < _line->specifier_number; j++) {
																	if (j == _line->variant) continue;
																	replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
																}

																if (_tournament->season_name != NULL) replace(_line->outcome_name[i], "$event", tournaments_id[_line->tournament_id]->season_name);
															}
															else { _line->outcome_name[i] = new char[2]; std::strcpy(_line->outcome_name[i], " "); }
														}
														if (print == true) {
															std::printf(_line->outcome_name[i]); std::printf("\t");
															std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
															printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
														}

														std::strcat(socket_message_big, _line->outcome_name[i]);
														std::strcat(socket_message_big, "\t");
														std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
														std::strcat(socket_message_big, socket_message_little);
														std::strcat(socket_message_big, "\t");
														std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
														std::strcat(socket_message_big, socket_message_little);


													}

													if (_line->type == 3) {

														if (_line->outcome_id[i] == _line->market->outcome_id[i]) u = i;
														else
															for (u = 0; u < _line->market->outcome_number; u++) {


																if (_line->outcome_id[i] == _line->market->outcome_id[u]) break;
															}

														if (u < _line->market->outcome_number) {

															_line->outcome_name[i] = new char[strlen(_line->market->outcome_name[u]) + 1];
															std::strcpy(_line->outcome_name[i], _line->market->outcome_name[u]);

														}
														else {
															std::printf("Eror. Outcome name not found. market_id=%d _line->outcome_id[i]=%d\r\n", _line->market_id, _line->outcome_id[i]);
															_line->outcome_name[i] = new char[2];
															std::strcpy(_line->outcome_name[i], " ");

															if (_line->market->variant > -1)
																printf("_line->market->variant=%s\r\n", _line->market->variable_text);
															if (outcomeNameError == 0) outcomeNameError = 1;

														}

														for (int j = 0; j < _line->specifier_number; j++) {
															if (j == _line->variant) continue;

															replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
														}

														if (_tournament->season_name) replace(_line->outcome_name[i], "$event", tournaments_id[_line->tournament_id]->season_name);


														//if (_line->market_id == 188 || _line->market_id == 224 || _line->market_id == 485 || _line->market_id == 231 || _line->market_id == 65 || _line->market_id == 383 || _line->market_id == 66) 

														if (print == true) {

															std::printf(_line->outcome_name[i]); std::printf("\t");
															std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
															printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
														}
														std::strcat(socket_message_big, _line->outcome_name[i]);
														std::strcat(socket_message_big, "\t");
														std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
														std::strcat(socket_message_big, socket_message_little);
														std::strcat(socket_message_big, "\t");
														std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
														std::strcat(socket_message_big, socket_message_little);




													}


												}

												if (outcomeNameError == 1 && _line->market->variant > -1) goto outcomeNameError2;
											}


											if (debug_output == true) printf("insertLine _line->type ==%d\r\n", _line->type);
											auto it = compound2line_index.find(_line[0].getCompoundKey());
											if (debug_output == true) {
												printf(_line[0].getCompoundKey().c_str());
												printf("\r\n");
											}
											if (it == compound2line_index.end()) {
												if (debug_output == true) printf("new line add");
												_line[0].id = lines_l;
												if (debug_output == true) printf("new line add1");
												lines[lines_l] = _line[0];
												lines_id[_line[0].id] = &lines[lines_l];
												if (debug_output == true) printf("new line add2");
												insert_line(_line[0], lines_l);
												if (debug_output == true) printf("new line add3");
												lines_l++;
												categories_id[_tournament->category_id]->outrights_id.push_back(_line[0].id);
												if (debug_output == true) printf("new line add finish");

											}
											else {
												if (debug_output == true) printf("line update");
												_line[0].id = it->second;
												if (debug_output == true) printf("line update1");
												lines[it->second] = _line[0];
												if (debug_output == true) printf("line finish");

												//printf("Line Update\r\n");
											}


											if (debug_output == true) printf("end insertLine _line->type ==%d\r\n", _line->type);

											if (recovery_state == 0) {

												if (debug_output == true) printf("write buffer data\r\n");

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
												writeInteger(buffer, offset, _line->outcome_number, 2);
												for (int j = 0; j < _line->outcome_number; j++) {
													writeInteger(buffer, offset, _line->outcome_id[j], 2);
													writeInteger(buffer, offset, _line->outcome_active[j], 1);
													if (_line->type == 1 || _line->type == 2) writeInteger(buffer, offset, _line->outcome_team[j], 1);
													if ((_line->type == 1 || _line->type == 2) && _line->outcome_team[j] != 3)
														writeString(buffer, offset, _line->outcome_name[j]);

													writeInteger(buffer, offset, (int)(_line->outcome_odds[j] * 100), 4);
												}

												writeInteger(buffer, offset, _line->specifier_number, 1);
												for (int j = 0; j < _line->specifier_number; j++) writeString(buffer, offset, _line->specifier_value[j]);

												if (debug_output == true) printf("end write buffer data\r\n");

											}






						}
					}
					if (recovery_state == 0) writeInteger(buffer, retry_offset, event_lines_l, 2);
				}
				if (type_radar < 2) {
					if (event_id >= MAX_EVENTS) { std::printf("ERROR DATA!\r\nsevent id out of MAX_EVENTS in run %d\r\n", event_id); continue; }
					if (events_id[event_id] == NULL) {
						std::printf("Event not found. Run getFixture to get event_id=%d type_radar=%d\r\n", event_id, type_radar);
						events[events_l].id = event_id;
						events[events_l].type_radar = type_radar;
						if (getEventFixture(&events[events_l]) == -1) { std::printf("ERROR!\r\n getEventFixture1 error return in run %d .\r\n", event_id); continue; }
						events_l++;

					}
					_event = events_id[event_id];
					if (_event->show == 0) {
						events_show[events_show_l] = _event; events_show_l++;
					}
					_event->show = 1;


					if (print == true) {
						std::printf("\r\n***************************************************\r\n");
						std::printf("%d\r\n", _event->id);
						std::printf(_event->home_name); if (_event->away_name != NULL) { std::printf(" - ");  std::printf(_event->away_name); }
						std::printf("\r\n");
					}

					std::strcat(socket_message_big, "\r\n***************************************************\r\n");
					std::sprintf(socket_message_little, "%d\r\n", _event->id);
					std::strcat(socket_message_big, socket_message_little);
					std::strcat(socket_message_big, _event->home_name);
					if (_event->away_name != NULL) {
						std::strcat(socket_message_big, " - ");  std::strcat(socket_message_big, _event->away_name);



					}
					if (_event->sport_id >= MAX_SPORTS) { std::printf("ERROR DATA!\r\nsevent sport_id out of MAX_SPORTS in run %d\r\n", _event->sport_id); continue; }
					if (sports_id[_event->sport_id] == NULL) { std::printf("Sport not found. Run getSports. sport_id=%d\r\n", _event->sport_id); getSports(); }
					if (print == true) {
						std::printf(sports_id[_event->sport_id]->name); std::printf("\r\n");
					}
					std::strcat(socket_message_big, sports_id[_event->sport_id]->name);
					std::strcat(socket_message_big, "\r\n");

					if (_event->type_radar < 2 && _event->tournament_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nsevent tournament_id out of MAX_TOURNAMENTS in run %d\r\n", _event->tournament_id); continue; }
					if (_event->type_radar == 2 && _event->simple_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nsevent tournament_id out of MAX_TOURNAMENTS in run %d\r\n", _event->simple_id); continue; }
					if (_event->type_radar == 0 && tournaments_id[_event->tournament_id] == NULL) {
						std::printf("Tournament not found. Run getTournament(). tournament_id=%d\r\n", _event->tournament_id);
						tournaments[tournaments_l].id = _event->tournament_id;
						tournaments[tournaments_l].type_radar = _event->type_radar;
						if (getTournament(&tournaments[tournaments_l], true) == -1) { std::printf("ERROR!\r\nTournaments not found in run %d . Run getEventFixture\r\n", _event->tournament_id); if (getEventFixture(_event) == -1) { std::printf("ERROR!\r\n getEventFixture2 error return in run %d .\r\n", _event->id); continue; } }
						else tournaments_l++;


					}
					if (_event->type_radar == 2 && simples_id[_event->simple_id] == NULL) {
						std::printf("Simple Tournament not found. Run getTournament(). simples_id=%d _event_id=%d\r\n ", _event->simple_id, _event->id);
						tournaments[tournaments_l].simple_id = _event->simple_id;
						tournaments[tournaments_l].id = 0;
						tournaments[tournaments_l].type_radar = _event->type_radar;
						if (getTournament(&tournaments[tournaments_l], true) == -1) { std::printf("ERROR!\r\nSimple Tournaments not found in run %d . Run getEventFixture\r\n", _event->tournament_id); if (getEventFixture(_event) == -1) { std::printf("ERROR!\r\n getEventFixture3 error return in run %d .\r\n", _event->id); continue; } }
						else tournaments_l++;


					}


					if (print == true) {
						if (_event->type_radar == 0) std::printf(tournaments_id[_event->tournament_id]->name);
						if (_event->type_radar == 2) std::printf(simples_id[_event->simple_id]->name);
						std::printf("\r\n");
					}

					if (_event->type_radar == 0) std::strcat(socket_message_big, tournaments_id[_event->tournament_id]->name);
					if (_event->type_radar == 2) std::strcat(socket_message_big, simples_id[_event->simple_id]->name);
					std::strcat(socket_message_big, "\r\n");







					if (_event->category_id >= MAX_CATEGORIES) { std::printf("ERROR DATA!\r\nsevent category_id out of MAX_CATEGORIES in run %d\r\n", _event->category_id); continue; }
					if (categories_id[_event->category_id] == NULL) {
						std::printf("Category not found. Run getTournament(). category_id=%d\r\n", _event->category_id);
						if (_event->type_radar == 0) {
							if (getTournament(tournaments_id[_event->tournament_id], false) == -1) if (getEventFixture(_event) == -1) continue;;
						}
						if (_event->type_radar == 2) {
							if (getTournament(simples_id[_event->simple_id], false) == -1) if (getEventFixture(_event) == -1) continue;;
						}


					}
					if (print == true) {
						std::printf(categories_id[_event->category_id]->name); std::printf("\r\n");
						std::printf("\r\n***************************************************\r\n");
					}
					std::strcat(socket_message_big, categories_id[_event->category_id]->name);
					std::strcat(socket_message_big, "\r\n\r\n***************************************************\r\n");




					if (doc.first_node()->first_attribute("timestamp")) _event->timestamp = atoi(doc.first_node()->first_attribute("timestamp")->value());

					xml_node<> * sport_event_status = doc.first_node()->first_node("sport_event_status");
					if (sport_event_status != NULL) {

						xml_node<> * statistics = sport_event_status->first_node("statistics");

						if (statistics != NULL) {

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
							if (_event->bases != NULL) { delete[] _event->bases; _event->bases = NULL; }
							_event->bases = new char[strlen(sport_event_status->first_attribute("bases")->value()) + 1];
							std::strcpy(_event->bases, sport_event_status->first_attribute("bases")->value());

						}




						if (sport_event_status->first_attribute("tiebreak") && sport_event_status->first_attribute("tiebreak")->value()[0] == 't' && sport_event_status->first_attribute("tiebreak")->value()[1] == 'r')  _event->tiebreak = 1;
						if (sport_event_status->first_attribute("tiebreak") && sport_event_status->first_attribute("tiebreak")->value()[0] == 'f' && sport_event_status->first_attribute("tiebreak")->value()[1] == 'a')  _event->tiebreak = 0;

						if (sport_event_status->first_attribute("expedite_mode") && sport_event_status->first_attribute("expedite_mode")->value()[0] == 't' && sport_event_status->first_attribute("expedite_mode")->value()[1] == 'r')  _event->expedite_mode = 1;
						if (sport_event_status->first_attribute("expedite_mode") && sport_event_status->first_attribute("expedite_mode")->value()[0] == 'f' && sport_event_status->first_attribute("expedite_mode")->value()[1] == 'a')  _event->expedite_mode = 0;




						xml_node<> * period_scores = sport_event_status->first_node("period_scores");

						j = 0;
						if (period_scores != NULL) {


							for (xml_node<> * period_score = period_scores->first_node("period_score"); period_score; period_score = period_score->next_sibling())
							{
								if (j == 0) strcpy(set_scores, period_score->first_attribute("home_score")->value());
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
							if (_event->set_scores != NULL) { delete[] _event->set_scores; _event->set_scores = NULL; }
							_event->set_scores = new char[strlen(set_scores) + 1]; strcpy(_event->set_scores, set_scores);
						}




						xml_node<> * clock = sport_event_status->first_node("clock");
						if (clock != NULL) {

							if (clock->first_attribute("stopped") && clock->first_attribute("stopped")->value()[0] == 't' && clock->first_attribute("stopped")->value()[1] == 'r')  _event->stopped = 1;

							if (clock->first_attribute("stopped") && clock->first_attribute("stopped")->value()[0] == 'f' && clock->first_attribute("stopped")->value()[1] == 'a')  _event->stopped = 0;

							if (clock->first_attribute("remaining_time_in_period")) {
								if (_event->remaining_time_in_period != NULL) delete[] _event->remaining_time_in_period;
								_event->remaining_time_in_period = new char[strlen(clock->first_attribute("remaining_time_in_period")->value()) + 1];
								std::strcpy(_event->remaining_time_in_period, clock->first_attribute("remaining_time_in_period")->value());
							}

							if (clock->first_attribute("stoppage_time")) {
								if (_event->stoppage_time != NULL) delete[] _event->stoppage_time;
								_event->stoppage_time = new char[strlen(clock->first_attribute("stoppage_time")->value()) + 1];
								std::strcpy(_event->stoppage_time, clock->first_attribute("stoppage_time")->value());
							}
							if (clock->first_attribute("stoppage_time_announced")) {
								if (_event->stoppage_time_announced != NULL) delete[] _event->stoppage_time_announced;
								_event->stoppage_time_announced = new char[strlen(clock->first_attribute("stoppage_time_announced")->value()) + 1];
								std::strcpy(_event->stoppage_time_announced, clock->first_attribute("stoppage_time_announced")->value());
							}


							if (clock->first_attribute("remaining_time")) {
								if (_event->remaining_time != NULL) delete[] _event->remaining_time;
								_event->remaining_time = new char[strlen(clock->first_attribute("remaining_time")->value()) + 1];
								std::strcpy(_event->remaining_time, clock->first_attribute("remaining_time")->value());
							}

							if (clock->first_attribute("match_time")) {
								if (_event->match_time != NULL) delete[] _event->match_time;
								_event->match_time = new char[strlen(clock->first_attribute("match_time")->value()) + 1];
								std::strcpy(_event->match_time, clock->first_attribute("match_time")->value());
							}


						}


					}

					//	if (_event->status > 0) print = true; else print = false;

					if (print == true) {
						if (_event->set_scores != NULL) { std::printf("set_scores="); std::printf(_event->set_scores); }
						if (_event->match_time != NULL) { std::printf("match_time="); std::printf(_event->match_time); std::printf(" "); }
						if (_event->remaining_time != NULL) { std::printf("remaining_time="); std::printf(_event->remaining_time); std::printf(" "); }
						if (_event->remaining_time_in_period != NULL) { std::printf("remaining_time_in_period="); std::printf(_event->remaining_time_in_period); std::printf(" "); }
						if (_event->bases != NULL) { std::printf("bases="); std::printf(_event->bases); std::printf(" "); }


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
						writeInteger(buffer, offset, _event->start_time + 4 * 3600, 4);
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

						if (event2lines.find(_event->id) == event2lines.end()) writeInteger(buffer, offset, 0, 2);
						else writeInteger(buffer, offset, event2lines[_event->id]->size(), 2);
						retry_offset = offset;
						offset += 2;
						event_lines_l = 0;
					}





					if (odds != NULL) {
						betstop_reason = 0;
						if (odds->first_attribute("betstop_reason")) betstop_reason = atoi(odds->first_attribute("betstop_reason")->value());
						_line->betstop_reason = betstop_reason;
						_line->event_id = event_id;
						_line->tournament_id = 0;
						_line->simple_id = 0;
						for (xml_node<> * market_node = odds->first_node("market"); market_node; market_node = market_node->next_sibling())
						{
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
							if (markets_id[_line->market_id] == NULL) {
								std::printf("ERROR DATA!\r\nmarket id not found in run%d\r\n", _line->market_id); continue;
							};
							if (markets_id[_line->market_id][0] == NULL) {
								std::printf("ERROR DATA!\r\nmarket id 0 not found in run%d\r\n", _line->market_id); continue;
							};
							_line->variant = markets_id[_line->market_id][0]->variant;
							_line->type = markets_id[_line->market_id][0]->type;
							if (_line->specifier_number > 0) for (q = 0; q < _line->specifier_number; q++) {
								if (_line->specifier[q] != NULL) delete[] _line->specifier[q]; _line->specifier[q] = NULL;
								if (_line->specifier_value[q] != NULL)  delete[] _line->specifier_value[q]; _line->specifier_value[q] = NULL;
							}
							if (_line->specifier != NULL) { delete[] _line->specifier; _line->specifier = NULL; }
							if (_line->specifier_value != NULL) { delete[] _line->specifier_value; _line->specifier_value = NULL; }
							_line->specifier_number = 0;
							if (_line->extended_specifier_number > 0) for (q = 0; q < _line->extended_specifier_number; q++) {
								if (_line->extended_specifier[q] != NULL) delete[] _line->extended_specifier[q];
								if (_line->extended_specifier_value[q] != NULL)  delete[] _line->extended_specifier_value[q];
							}
							if (_line->extended_specifier != NULL) { delete[] _line->extended_specifier; _line->extended_specifier = NULL; }
							if (_line->extended_specifier_value != NULL) { delete[] _line->extended_specifier_value; _line->extended_specifier_value = NULL; }
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
						outcomeNameError3: if (_line->variant > -1) {
							z = strlen(_line->specifier_value[_line->variant]) + 1; if (strcmp(_line->specifier[_line->variant], "variant") != 0) { std::printf(_line->specifier[_line->variant]); std::printf("\r\n"); }
							for (u = 0; u < max_markets_in[_line->market_id]; u++) if (markets_id[_line->market_id][u] != NULL && markets_id[_line->market_id][u]->variable_text != NULL && std::strcmp(_line->specifier_value[_line->variant], markets_id[_line->market_id][u]->variable_text) == 0) break;
							if (outcomeNameError == 1 || u == max_markets_in[_line->market_id]) {
								std::printf("Variant market3 not found in run market_id=%d variant=", _line->market_id);  std::printf(_line->specifier_value[_line->variant]);  std::printf("  getVariantMarkets\r\n"); if (getVariantMarkets(markets_id[_line->market_id][0], _line->specifier_value[_line->variant]) == -1) { std::printf("variant market not found "); continue; }
								for (u = 0; u < max_markets_in[_line->market_id]; u++) if (markets_id[_line->market_id][u] != NULL && markets_id[_line->market_id][u]->variable_text != NULL && std::strcmp(_line->specifier_value[_line->variant], markets_id[_line->market_id][u]->variable_text) == 0) break;
							}
							_line->market = markets_id[_line->market_id][u];
							if (outcomeNameError == 1) outcomeNameError = 2;
							if (_line->type == 3) z = 16;
						}
										   else { _line->market = markets_id[_line->market_id][0]; if (_line->type == 0) z = 0; else if (_line->type == 1) z = 10; else if (_line->type == 2) z = 14; else if (_line->type == 3) z = 16; }
										   outcome_number = 0;

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
											   if (outcome_name[outcome_number] != NULL) delete[] outcome_name[outcome_number]; outcome_name[outcome_number] = NULL;
											   if (outcome_node->first_attribute("name")) {
												   outcome_name[outcome_number] = new char[strlen(outcome_node->first_attribute("name")->value()) + 1];
												   std::strcpy(outcome_name[outcome_number], outcome_node->first_attribute("name")->value());

											   }

											   outcome_number++;

										   }




										   if (_line->outcome_number > 0) { for (int i = 0; i < _line->outcome_number; i++) if (_line->outcome_name[i] != NULL) delete[] _line->outcome_name[i]; };


										   if (_line->outcome_id != NULL) delete[] _line->outcome_id; if (_line->outcome_active != NULL) delete[] _line->outcome_active; if (_line->outcome_team != NULL) delete[] _line->outcome_team; if (_line->outcome_odds != NULL) delete[] _line->outcome_odds;
										   if (_line->outcome_probabilities != NULL) delete[] _line->outcome_probabilities; if (_line->outcome_name != NULL) delete[] _line->outcome_name;
										   _line->outcome_probabilities = NULL; _line->outcome_name = NULL; _line->outcome_id = NULL; _line->outcome_odds = NULL; _line->outcome_active = NULL;
										   _line->outcome_team = NULL;



										   _line->outcome_number = outcome_number;
										   if (_line->outcome_number > 0) {
											   _line->outcome_name = new char*[_line->outcome_number];
											   _line->outcome_id = new int[_line->outcome_number];
											   _line->outcome_team = new int[_line->outcome_number];
											   _line->outcome_active = new int[_line->outcome_number];
											   _line->outcome_probabilities = new float[_line->outcome_number];
											   _line->outcome_odds = new float[_line->outcome_number];


											   if (_line->name != NULL) delete[] _line->name;


											   _line->name = new char[strlen(_line->market->name) + 1];
											   std::strcpy(_line->name, _line->market->name);
											   for (int i = 0; i < _line->specifier_number; i++) {
												   if (i == _line->variant) continue;

												   replace(_line->name, _line->specifier[i], _line->specifier_value[i]);
											   }

											   replace(_line->name, "$competitor1", events_id[_line->event_id]->home_name);
											   if (_event->away_name != NULL) replace(_line->name, "$competitor2", events_id[_line->event_id]->away_name);
											   if (_event->type_radar > 0) replace(_line->name, "$event", events_id[_line->event_id]->home_name);


											   if (print == true) {

												   std::printf("\r\n"); std::printf(_line->name); std::printf("\r\n"); std::printf("------------------------------------------------------------------------------\r\n");
											   }

											   std::strcat(socket_message_big, "\r\n");
											   std::strcat(socket_message_big, _line->name);
											   std::strcat(socket_message_big, "\r\n------------------------------------------------------------------------------\r\n");








											   for (int i = 0; i < _line->outcome_number; i++) {
												   _line->outcome_name[i] = NULL;
												   _line->outcome_id[i] = outcome_id[i];
												   _line->outcome_active[i] = outcome_active[i];
												   _line->outcome_odds[i] = outcome_odds[i];
												   _line->outcome_team[i] = outcome_team[i];
												   _line->outcome_probabilities[i] = outcome_probabilities[i];


												   if (_line->type == 0) {
													   if (_line->outcome_id[i] == _line->market->outcome_id[i]) u = i;
													   else
														   for (u = 0; u < _line->market->outcome_number; u++) if (_line->outcome_id[i] == _line->market->outcome_id[u]) break;

													   if (u < _line->market->outcome_number) {
														   _line->outcome_name[i] = new char[strlen(_line->market->outcome_name[u]) + 1];
														   std::strcpy(_line->outcome_name[i], _line->market->outcome_name[u]);

													   }
													   else {
														   std::printf("Eror. Outcome name not found. market_id=%d _line->outcome_id[i]=%d\r\n", _line->market_id, _line->outcome_id[i]);

														   _line->outcome_name[i] = new char[2];
														   std::strcpy(_line->outcome_name[i], " ");
														   if (_line->market->variant > -1) printf("_line->market->variant=%s\r\n", _line->market->variable_text);
														   if (outcomeNameError == 0) outcomeNameError = 1;


													   }

													   for (int j = 0; j < _line->specifier_number; j++) {
														   if (j == _line->variant) continue;

														   replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
													   }

													   replace(_line->outcome_name[i], "$competitor1", events_id[_line->event_id]->home_name);
													   if (_event->away_name != NULL) replace(_line->outcome_name[i], "$competitor2", events_id[_line->event_id]->away_name);
													   if (_event->type_radar > 0) replace(_line->outcome_name[i], "$event", events_id[_line->event_id]->home_name);



													   if (print == true) {

														   std::printf(_line->outcome_name[i]); std::printf("\t");
														   std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
														   std::printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
													   }
													   std::strcat(socket_message_big, _line->outcome_name[i]);
													   std::strcat(socket_message_big, "\t");
													   std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
													   std::strcat(socket_message_big, socket_message_little);
													   std::strcat(socket_message_big, "\t");
													   std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
													   std::strcat(socket_message_big, socket_message_little);






												   }

												   if (_line->type == 1) {
													   if (_line->outcome_id[i] >= MAX_PLAYERS) {
														   std::printf("ERROR in run. player_id out of MAX_PLAYERS. _line->outcome_id[i]=%d  _line->market_id=%d event_id=%d\r\n", _line->outcome_id[i], _line->market_id, _line->event_id);
														   continue;

													   }

													   if (players_id[_line->outcome_id[i]] == NULL && _line->outcome_team[i] == 2) {
														   std::printf("Player4 id=%d not found in market id=%d in event_id=%d  in run function team 2 \r\n", _line->outcome_id[i], _line->market_id, _line->event_id);
														   if (events_id[_line->event_id]->away_id >= MAX_COMPETITORS) {
															   std::printf("ERROR in run. away_id out of MAX_COMPETITORS. away_id=%d event_id=%d\r\n", events_id[_line->event_id]->away_id, _line->event_id);
															   continue;
														   }

														   if (competitors_id[events_id[_line->event_id]->away_id] == NULL) {
															   std::printf("Competitor id %d not found in team 2 run. getCompetitor\r\n", events_id[_line->event_id]->away_id);
															   competitors[competitors_l].id = events_id[_line->event_id]->away_id;
															   if (getCompetitor(&competitors[competitors_l]) == -1) {
																   std::printf(" Error get competitors id=%d \r\n", events_id[_line->event_id]->away_id); //continue;
															   }
															   else competitors_l++;


														   }
													   }

													   if (players_id[_line->outcome_id[i]] == NULL && _line->outcome_team[i] == 1) {
														   std::printf("Player5 id=%d not found in market id=%d in event_id=%d  in run function team 1 \r\n", _line->outcome_id[i], _line->market_id, _line->event_id);
														   if (events_id[_line->event_id]->away_id >= MAX_COMPETITORS) {
															   std::printf("ERROR in run. home_id out of MAX_COMPETITORS. home_id=%d event_id=%d\r\n", events_id[_line->event_id]->home_id, _line->event_id);
															   continue;
														   }

														   if (competitors_id[events_id[_line->event_id]->home_id] == NULL) {
															   std::printf("Competitor id %d not found in team 1 run. getCompetitor\r\n", events_id[_line->event_id]->home_id);
															   competitors[competitors_l].id = events_id[_line->event_id]->home_id;
															   if (getCompetitor(&competitors[competitors_l]) == -1) {
																   std::printf(" Error get competitors id=%d \r\n", events_id[_line->event_id]->home_id); //continue;
															   }
															   else competitors_l++;


														   }
													   }


													   if (_line->outcome_team[i] < 3 && players_id[_line->outcome_id[i]] == NULL) {
														   std::printf("Player6 id=%d  not found in run after get competitor. getPlayer\r\n ", _line->outcome_id[i]);
														   players[players_l].id = _line->outcome_id[i]; if (getPlayer(&players[players_l]) == -1)
														   {
															   std::printf("error player id=%d  not found \r\n ", _line->outcome_id[i]); //continue;
															   _line->outcome_name[i] = new char[2];
															   std::strcpy(_line->outcome_name[i], " ");
														   }
														   else players_l++;
													   }

													   if (_line->outcome_team[i] < 3 && _line->outcome_name[i] == NULL) {
														   if (_line->outcome_team[i] == 1) {
															   _line->outcome_name[i] = new char[strlen(players_id[_line->outcome_id[i]]->name) + strlen(_event->home_name) + 4];
															   std::strcpy(_line->outcome_name[i], players_id[_line->outcome_id[i]]->name);
															   std::strcat(_line->outcome_name[i], " (");
															   std::strcat(_line->outcome_name[i], _event->home_name);
															   std::strcat(_line->outcome_name[i], ")");

														   }
														   if (_line->outcome_team[i] == 2) {
															   if (_event->away_name != NULL) _line->outcome_name[i] = new char[strlen(players_id[_line->outcome_id[i]]->name) + strlen(_event->away_name) + 4]; else _line->outcome_name[i] = new char[strlen(players_id[_line->outcome_id[i]]->name) + 1];
															   std::strcpy(_line->outcome_name[i], players_id[_line->outcome_id[i]]->name);
															   if (_event->away_name != NULL) {
																   std::strcat(_line->outcome_name[i], " (");
																   std::strcat(_line->outcome_name[i], _event->away_name);
																   std::strcat(_line->outcome_name[i], ")");
															   }

														   }

													   }

													   if (_line->outcome_team[i] == 3) {

														   for (u = 0; u < _line->market->outcome_number; u++) if (_line->market->outcome_id[u] == _line->outcome_id[i]) break;
														   if (u < _line->market->outcome_number) {
															   _line->outcome_name[i] = new char[strlen(_line->market->outcome_name[u]) + 1];
															   std::strcpy(_line->outcome_name[i], _line->market->outcome_name[u]);

															   for (int j = 0; j < _line->specifier_number; j++) {
																   if (j == _line->variant) continue;

																   replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
															   }

															   replace(_line->outcome_name[i], "$competitor1", events_id[_line->event_id]->home_name);
															   replace(_line->outcome_name[i], "$competitor2", events_id[_line->event_id]->away_name);
															   if (_event->type_radar > 0) replace(_line->outcome_name[i], "$event", events_id[_line->event_id]->home_name);



														   }
														   else {
															   _line->outcome_name[i] = new char[2];
															   std::strcpy(_line->outcome_name[i], " ");
														   }



													   }





													   if (print == true) {



														   std::printf(_line->outcome_name[i]); std::printf("\t");
														   std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
														   printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
													   }
													   std::strcat(socket_message_big, _line->outcome_name[i]);
													   std::strcat(socket_message_big, "\t");
													   std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
													   std::strcat(socket_message_big, socket_message_little);
													   std::strcat(socket_message_big, "\t");
													   std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
													   std::strcat(socket_message_big, socket_message_little);




												   }

												   if (_line->type == 2) {
													   if (_line->outcome_team[i] != 3) {
														   if (_line->outcome_id[i] >= MAX_COMPETITORS) {
															   std::printf("ERROR in run. competitor_id out of MAX_COMPETITORS. _line->outcome_id[i]=%d  _line->market_id=%d event_id=%d\r\n", _line->outcome_id[i], _line->market_id, _line->event_id);
															   continue;
														   }
														   if (competitors_id[_line->outcome_id[i]] == NULL) {
															   std::printf("Competitor id=%d not found in market id=%d in event_id=%d  in run function. getTournament\r\n", _line->outcome_id[i], _line->market_id, _line->event_id);
															   //tournaments[tournaments_l].id = _event->tournament_id;
															   //tournaments[tournaments_l].type_radar = _event->type_radar;

															   if (_event->type_radar == 0 && getTournament(tournaments_id[_event->tournament_id], false) == -1)
																   std::printf("ERROR!\r\nTournaments not found in run %d \r\n", _event->tournament_id);

															   if (_event->type_radar == 2 && getTournament(simples_id[_event->simple_id], false) == -1)
																   std::printf("ERROR!\r\nSimples Tournaments not found in run %d \r\n", _event->simple_id);

														   }

														   if (competitors_id[_line->outcome_id[i]] == NULL) {
															   std::printf("\r\nCompetitors id=%d not found in tournament id=%d . Run getCompetitor\r\n", _line->outcome_id[i], _event->tournament_id);
															   competitors[competitors_l].id = _line->outcome_id[i];
															   if (getCompetitor(&competitors[competitors_l]) == -1) {
																   std::printf(" Error get competitors in run function line type= 2 id=%d \r\n", _line->outcome_id[i]);
																   _line->outcome_name[i] = new char[2];
																   std::strcpy(_line->outcome_name[i], " ");
															   }
															   else competitors_l++;
														   }

														   if (competitors_id[_line->outcome_id[i]] != NULL) { _line->outcome_name[i] = new char[strlen(competitors_id[_line->outcome_id[i]]->name) + 1]; std::strcpy(_line->outcome_name[i], competitors_id[_line->outcome_id[i]]->name); }

													   }
													   else
													   {
														   for (u = 0; u < _line->market->outcome_number; u++) if (_line->market->outcome_id[u] == _line->outcome_id[i]) break;
														   if (u < _line->market->outcome_number) {
															   _line->outcome_name[i] = new char[strlen(_line->market->outcome_name[u]) + 1];
															   std::strcpy(_line->outcome_name[i], _line->market->outcome_name[u]);
															   for (int j = 0; j < _line->specifier_number; j++) {
																   if (j == _line->variant) continue;
																   replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
															   }
															   replace(_line->outcome_name[i], "$competitor1", events_id[_line->event_id]->home_name);
															   replace(_line->outcome_name[i], "$competitor2", events_id[_line->event_id]->away_name);
															   if (_event->type_radar > 0) replace(_line->outcome_name[i], "$event", events_id[_line->event_id]->home_name);
														   }
														   else { _line->outcome_name[i] = new char[2]; std::strcpy(_line->outcome_name[i], " "); }
													   }
													   if (print == true) {
														   std::printf(_line->outcome_name[i]); std::printf("\t");
														   std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
														   printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
													   }
													   std::strcat(socket_message_big, _line->outcome_name[i]);
													   std::strcat(socket_message_big, "\t");
													   std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
													   std::strcat(socket_message_big, socket_message_little);
													   std::strcat(socket_message_big, "\t");
													   std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
													   std::strcat(socket_message_big, socket_message_little);

												   }

												   if (_line->type == 3) {

													   if (_line->outcome_id[i] == _line->market->outcome_id[i]) u = i;
													   else
														   for (u = 0; u < _line->market->outcome_number; u++) {


															   if (_line->outcome_id[i] == _line->market->outcome_id[u]) break;
														   }

													   if (u < _line->market->outcome_number) {

														   _line->outcome_name[i] = new char[strlen(_line->market->outcome_name[u]) + 1];
														   std::strcpy(_line->outcome_name[i], _line->market->outcome_name[u]);

													   }
													   else {
														   std::printf("Eror. Outcome name not found. market_id=%d _line->outcome_id[i]=%d\r\n", _line->market_id, _line->outcome_id[i]);
														   _line->outcome_name[i] = new char[2];
														   std::strcpy(_line->outcome_name[i], " ");
														   if (_line->market->variant > -1) printf("_line->market->variant=%s\r\n", _line->market->variable_text);
														   if (outcomeNameError == 0) outcomeNameError = 1;
													   }

													   for (int j = 0; j < _line->specifier_number; j++) {
														   if (j == _line->variant) continue;

														   replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
													   }

													   replace(_line->outcome_name[i], "$competitor1", events_id[_line->event_id]->home_name);
													   replace(_line->outcome_name[i], "$competitor2", events_id[_line->event_id]->away_name);
													   if (_event->type_radar > 0) replace(_line->outcome_name[i], "$event", events_id[_line->event_id]->home_name);


													   //if (_line->market_id == 188 || _line->market_id == 224 || _line->market_id == 485 || _line->market_id == 231 || _line->market_id == 65 || _line->market_id == 383 || _line->market_id == 66) 

													   if (print == true) {

														   std::printf(_line->outcome_name[i]); std::printf("\t");
														   std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
														   printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
													   }
													   std::strcat(socket_message_big, _line->outcome_name[i]);
													   std::strcat(socket_message_big, "\t");
													   std::sprintf(socket_message_little, "odds=%g", _line->outcome_odds[i]);
													   std::strcat(socket_message_big, socket_message_little);
													   std::strcat(socket_message_big, "\t");
													   std::sprintf(socket_message_little, "probabilitie=%g\r\n", _line->outcome_probabilities[i]);
													   std::strcat(socket_message_big, socket_message_little);




												   }


											   }



											   if (outcomeNameError == 1 && _line->market->variant > -1) goto outcomeNameError3;
										   }

										   if (debug_output == true) printf("insertLine _line->type ==%d\r\n", _line->type);
										   if (debug_output == true) {
											   printf(_line[0].getCompoundKey().c_str());
											   printf("\r\n");
										   }
										   auto it = compound2line_index.find(_line[0].getCompoundKey());
										   if (debug_output == true) printf("auto it\r\n");
										
										   if (it == compound2line_index.end()) {
											   if (debug_output == true) printf("new line add ");
											   _line[0].id = lines_l;
											   if (debug_output == true) printf("new line add1 ");
											   lines[lines_l] = _line[0];
											   lines_id[_line[0].id] = &lines[lines_l];
											   if (debug_output == true) printf("new line add2 ");
											   insert_line(_line[0], lines_l);
											   if (debug_output == true) printf("new line add3 ");
											   lines_l++;
											   if (debug_output == true) printf("new line add finish\r\n");

										   }
										   else {
											   if (debug_output == true) printf("line update");
											   _line[0].id = it->second;
											   if (debug_output == true) printf("line update1");
											   lines[it->second] = _line[0];
											   if (debug_output == true) printf("line finish\r\n");

											   //printf("Line Update\r\n");
										   }

										   if (debug_output == true) printf("end insertLine _line->type ==%d\r\n", _line->type);

										   if (recovery_state == 0) {

											   if (debug_output == true) printf("write buffer data\r\n");

											   //if (markets_id[_line->market_id][0]->line_type == 0 && events[i].status == 0) continue;
											   //if (_line->status == 0 || _line->status == -3) continue;
											   event_lines_l++;
											   writeInteger(buffer, offset, _line->id, 4);
											   //writeInteger(buffer, offset, _line->betstop_reason, 1);
											   writeInteger(buffer, offset, _line->market_id, 2);
											   writeInteger(buffer, offset, _line->type, 1);
											   writeInteger(buffer, offset, _line->favourite, 1);
											   writeInteger(buffer, offset, _line->status, 1);
											   //if (_line->outcome_number == 0) printf("_line->outcome_number=0 _line->id=%d  _line->market_id=%d\r\n", _line->id, _line->market_id);
											   writeInteger(buffer, offset, _line->outcome_number, 2);
											   for (int j = 0; j < _line->outcome_number; j++) {
												   writeInteger(buffer, offset, _line->outcome_id[j], 2);
												   writeInteger(buffer, offset, _line->outcome_active[j], 1);
												   if (_line->type == 1 || _line->type == 2) writeInteger(buffer, offset, _line->outcome_team[j], 1);
												   if ((_line->type == 1 || _line->type == 2) && _line->outcome_team[j] != 3)
													   writeString(buffer, offset, _line->outcome_name[j]);
												   writeInteger(buffer, offset, (int)(_line->outcome_odds[j] * 100), 4);
											   }

											   writeInteger(buffer, offset, _line->specifier_number, 1);
											   for (int j = 0; j < _line->specifier_number; j++) writeString(buffer, offset, _line->specifier_value[j]);

											   if (debug_output == true) printf("end write buffer data\r\n");

										   }


						}
					}
					if (recovery_state == 0) writeInteger(buffer, retry_offset, event_lines_l, 2);

				}

				if (debug_output == true) printf("end parse type_radar=%d\r\n", type_radar);

				if (recovery_state == 0) {
					if (debug_output == true) printf("radarmessagehandler\r\n");

					zip_len = gzip(buffer, offset, zip_message, 2);
					//delete[] buffer;
					if (zip_len > 1)
					{
						encode_message = SendframeEncode(zip_message, zip_len, encode_message_len);
						//while (server.ws_clients_flag.test_and_set(std::memory_order_acquire));
						radarMessageHandler(encode_message, encode_message_len);
						//server.ws_clients_flag.clear(std::memory_order_release);
						//printf("encode_message_len=%d\r\n", encode_message_len);
				    	delete[] encode_message;
						encode_message = nullptr;


					}
					delete[] zip_message;
					zip_message = nullptr;
					if (debug_output == true) printf("end radarmessagehandler\r\n");
				}
				//delete[] zip_message;










			}
			else {
				if (std::strcmp("snapshot_complete", doc.first_node()->name()) == 0) { recovery_state = 0; new_message_arrived = true; }
				printf(doc.first_node()->name()); std::printf("\r\n");
			}

			doc.clear();
			

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

			/*
			if (i < 100 && status == 1 && (_event->away_yellowcards>0 || _event->away_redcards>0 || _event->home_yellowcards>0 || _event->home_redcards>0)) {
			i++;std::strcpy(name, "C://unifeed");
			_itoa(i, buf, 10);
			strcat(name, buf);
			strcat(name, ".xml");
			DeleteFile(name);
			File = CreateFile(name, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			l = SetFilePointer(File, 0, 0, FILE_BEGIN);
			printf(name);
			printf("\r\n");
			printf("message length= %d\r\n", envelope.message.body.len);
			WriteFile(File, envelope.message.body.bytes, envelope.message.body.len, &l, NULL);
			CloseHandle(File);
			}

			*/
			//WriteFile(File, "<endmessage></endmessage>", strlen("<endmessage></endmessage>"), &l, NULL);

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
//delete[] maxbuf;
delete[] socket_message_big;
delete[] socket_message_little;
delete[] buffer;
clientIDs.clear();
return 0;
	
}
DWORD WINAPI MTSGetThread(LPVOID lparam) {
	rabbitmqssl_mts();
	
	//sdkSocket();
	//httpsServer();
	return 0;

}
void GenerateBigStep() {
int i = 0;
int j = 0;
int k = 0;



vector<int> clientIDs;



if (recovery_state != 0)  return;
	//clientIDs.clear();
	clientIDs = server.getClientIDs();
	current_data_step_temp_1 = -1;
	current_data_step_temp_2 = -1;
	
	//if (!server.ws_clients_flag.test_and_set(std::memory_order_acquire)) {
		for (j = 0; j < STEP_QUEUE; j++) {
			if (array_data_step_1[j] != nullptr && j != current_data_step_1) {
				for (i = 0; i < clientIDs.size(); i++) {
					if (server.wsClients[clientIDs[i]] == NULL || server.wsClients[clientIDs[i]]->timestamp > 0) continue;
					if (server.wsClients[clientIDs[i]]->step_buffer_1 == array_data_step_1[j])  break;
				}

				if (i == clientIDs.size()) { delete[] array_data_step_1[j]; array_data_step_1[j] = nullptr; }
			}

			if (array_data_step_2[j] != nullptr && j != current_data_step_2) {
				for (i = 0; i < clientIDs.size(); i++) {
					if (server.wsClients[clientIDs[i]] == NULL) continue;
					if (server.wsClients[clientIDs[i]]->step_buffer_2 == array_data_step_2[j])  break;
				}

				if (i == clientIDs.size()) { delete[] array_data_step_2[j]; array_data_step_2[j] = nullptr; }
			}
		}
		
		//server.ws_clients_flag.clear(std::memory_order_release);
	//}


	for (j = 0; j < STEP_QUEUE; j++) {
		if (current_data_step_temp_1 >-1 && current_data_step_temp_2 >-1 ) break;
        if (current_data_step_temp_1 == -1 && array_data_step_1[j] == nullptr)  current_data_step_temp_1 = j; 
		if (current_data_step_temp_2 == -1 && array_data_step_2[j] == nullptr)  current_data_step_temp_2 = j; 

	}
	
	if (current_data_step_temp_1 == -1 || current_data_step_temp_2 == -1) {
		printf("error STEP_QUEUE\r\n"); return;
	}

	//printf("CreateStep_1--------------------------------------------\r\n");
	if (reload_step_1 == 1) {
		array_data_step_1[current_data_step_temp_1] = CreateStep_1(data_step_len_1[current_data_step_temp_1]);
		//printf("CreateStep_1-------------------------------------------- end\r\n");
		current_data_step_1 = current_data_step_temp_1;
		reload_step_1 = 0;
	}
	//printf("CreateStep_2--------------------------------------------\r\n");
	array_data_step_2[current_data_step_temp_2] = CreateStep_2(data_step_len_2[current_data_step_temp_2]);
	//printf("CreateStep_2 --------------------------------------------end\r\n");
	current_data_step_2 = current_data_step_temp_2;

	//Sleep(100);

	clientIDs.clear();



};
DWORD WINAPI pushClientMessageThread(LPVOID lparam) {
	char* param = (char*)lparam;
	int clientID = (int)param[0];
	if (clientID >= server.wsClients.size())return 0;
	if (server.wsClients[clientID] == NULL) return 0;
	int messageLen = (int)param[1];
	char* message = param + 2;
	//printf("pushClientMessageThread=%d\r\n", clientID);
	//while (server.wsClients[clientID]->flag == 1) Sleep(0);
	//printf("FlagpushClientMessageThread=%d\r\n", clientID);
	//server.wsClients[clientID]->flag = 1;
	/*server.wsClients[clientID]->mutex.lock();
	memcpy(server.wsClients[clientID]->message_queue + server.wsClients[clientID]->message_queue_length, message, messageLen);
	server.wsClients[clientID]->message_queue_length = server.wsClients[clientID]->message_queue_length + messageLen;
	server.wsClients[clientID]->mutex.unlock();*/
	//server.wsClients[clientID]->flag = 0;
	//printf("ExitClientMessageThread=%d\r\n", clientID);
	return 0;
}
DWORD WINAPI startRecoveryThread(LPVOID) { startRecovery(); return 0; }
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
void writeDouble(char* buffer, size_t &offset, double data) {
	memcpy(buffer + offset, &data, sizeof(double));

};
void writeFloat(char* buffer, size_t &offset, float data) {
	memcpy(buffer + offset, &data, sizeof(float));

};
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
int gzip(char* message, int messageLen, char* &zip_message, int step = 0) {
	if (messageLen == 0 || message == nullptr) return -1;
	int step_byte = 0;
	if (step > 0) step_byte = 2;
	char* step_message = new char[messageLen + step_byte+1];
    memcpy(step_message + step_byte, message, messageLen);
    if (step> 0) memcpy(step_message, &step, 2);
	int tempLen = GetMaxCompressedLen(messageLen + 1+ step_byte);
	BYTE* zipped = new BYTE[tempLen];  // alloc dest buffer
	int zippedLen = CompressData((BYTE*)step_message, messageLen + 1 + step_byte, zipped, tempLen);
	if (zippedLen == -1) { printf("error gzip encoding\r\n"); delete[] zipped; return -1; }
	zip_message = new char[zippedLen+1];
	memcpy(zip_message, zipped, zippedLen);
	delete[] zipped;
	delete[] step_message;
	return zippedLen;
}
void startRecovery() {
	if (recovery_state == 1) return;
	recovery_state = 1;
	char* recvbuf = new char[DEFAULT_BUFLEN];
	while (httpsRequest("api.betradar.com", "/v1/pre/recovery/initiate_request?request_id=2", recvbuf, 1)==-1) Sleep(1000);
	//printf(recvbuf);
	delete[] recvbuf;
	std::printf("Start recovery\r\n");


}
void getCategoriesTournaments() {
	reload_step_1 = 1;
	char* recvbuf = new char[DEFAULT_BUFLEN];
	char buf[MAX_PATH];
	while (httpsRequest("api.betradar.com", "/v1/sports/en/tournaments.xml", recvbuf, 0) == -1) Sleep(1000);
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
		tournaments[i].type_radar = 0;

		if (tournaments[i].name != NULL) {
			delete[] tournaments[i].name; tournaments[i].name = NULL;
		}
		if (tournament_node->first_attribute("name")) {
			tournaments[i].name = new char[strlen(tournament_node->first_attribute("name")->value()) + 1];
			std::strcpy(tournaments[i].name, tournament_node->first_attribute("name")->value());
		}

		tournaments[i].id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 14));
		if (tournaments[i].id == 0) {
			tournaments[i].id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 19));
			if (tournaments[i].id > 0)	tournaments[i].type_radar = 1;
			else {
				tournaments[i].id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 21));
				if (tournaments[i].id > 0) {
					tournaments[i].type_radar = 2; tournaments[i].simple_id = tournaments[i].id;  tournaments[i].id = 0;
				}
				else {
					tournaments[i].id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 10));
					if (tournaments[i].id > 0) tournaments[i].type_radar = 3;
				}
			}
		}
	


		//printf("tournamentId=%d Name=%s", tournaments[i].id, tournaments[i].name);
		temp = atoi((char*)((char*)tournament_node->first_node("category")->first_attribute("id")->value() + 12));

		temp2 = atoi((char*)((char*)tournament_node->first_node("sport")->first_attribute("id")->value() + 9));

		//printf("tournaments[i].id=%d\r\n", tournaments[i].id);
		if (tournaments[i].type_radar == 0) {

			if (tournaments[i].season_name != NULL) {
				delete[] tournaments[i].season_name; tournaments[i].season_name = NULL;
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








		if (temp >= MAX_CATEGORIES) std::printf("ERROR DATA!\r\ncategory id out of MAX_CATEGORIES in getCategoryTournaments %d\r\n", temp);
		else if (categories_id[temp] == NULL) {
			if (categories[j].name != NULL) {
				delete[] categories[j].name; categories[j].name = NULL;
			}
			if (tournament_node->first_node("category") && tournament_node->first_node("category")->first_attribute("name")) {
				categories[j].name = new char[strlen(tournament_node->first_node("category")->first_attribute("name")->value()) + 1];
				std::strcpy(categories[j].name, tournament_node->first_node("category")->first_attribute("name")->value());
			}

			categories[j].id = temp;
			categories[j].sport_id = temp2;
			categories_id[temp] = &categories[j];
			
			j++;
		}
		
		tournaments[i].sport_id = temp2;
		tournaments[i].category_id = temp;

		if(tournaments[i].type_radar == 2) {
			if (tournaments[i].simple_id < MAX_TOURNAMENTS) simples_id[tournaments[i].simple_id] = &tournaments[i]; else std::printf("ERROR DATA!\r\ntournament simple_id out of MAX_TOURNAMANETS in getCanegoryTournaments %d\r\n", tournaments[i].simple_id);
			
		} else {
			if (tournaments[i].id < MAX_TOURNAMENTS) tournaments_id[tournaments[i].id] = &tournaments[i]; else std::printf("ERROR DATA!\r\ntournament id out of MAX_TOURNAMANETS in getCanegoryTournaments %d\r\n", tournaments[i].id);
			if (tournaments[i].season_id > 0) {
				if (tournaments[i].season_id < MAX_TOURNAMENTS) seasons_id[tournaments[i].season_id] = &tournaments[i]; else std::printf("ERROR DATA!\r\ntournament season_id out of MAX_TOURNAMANETS in getCanegoryTournaments %d\r\n", tournaments[i].season_id);
			}
		}


		//printf("tournamentId=%d Name=%s tournamentIdSport=%d tournamentIdCategory=%d", tournaments[i].id, tournaments[i].name, tournaments[i].sport_id, tournaments[i].category_id);
		//cout << endl;
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
void getSports() {
	reload_step_1 = 1;
	char* recvbuf = new char[DEFAULT_BUFLEN];
	while(httpsRequest("api.betradar.com", "/v1/sports/en/sports.xml", recvbuf, 0)==-1) Sleep(1000);
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
void getEvents(time_t sec,int days) {
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
	char* recvbuf = new char[DEFAULT_BUFLEN];
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

		for (k = 0; k < 1000; k++) if (recvbuf[k] == '\r' && recvbuf[k + 1] == '\n' && recvbuf[k + 2] == '\r' && recvbuf[k + 3] == '\n') break;

		doc.parse<0>((char*)((char*)recvbuf + k + 4));
		root_node = doc.first_node("schedule");
		if (root_node == NULL) continue;

		
		for (xml_node<> * event_node = root_node->first_node("sport_event"); event_node; event_node = event_node->next_sibling())
		{
			//printf("for\r\n");
			events[i].id = atoi((char*)((char*)event_node->first_attribute("id")->value() + 9));
			if (events[i].id == 0) {
				events[i].id = atoi((char*)((char*)event_node->first_attribute("id")->value() + 14));
				events[i].type_radar = 1;
			}

			if (events[i].id == 0) {
			
				printf("EROR\r\n");
				printf(event_node->first_attribute("id")->value());
				printf("\r\n");
			
			}



			if (event_node->first_attribute("status") != NULL)	{
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

			if (events[i].type_radar == 0) {

				strcpy(buf, event_node->first_attribute("liveodds")->value());
				if (buf[0] == 'b'&& buf[1] == 'o'&& buf[5] == 'd') events[i].booked = 1;
				if (buf[0] == 'b'&& buf[1] == 'o'&& buf[5] == 'b') events[i].booked = 2; 

				
				
	



				if (events[i].home_name != NULL) {
					delete[] events[i].home_name; events[i].home_name = NULL;
				}
				if (event_node->first_node("competitors")->first_node("competitor")->first_attribute("name")) {
					events[i].home_name = new char[strlen(event_node->first_node("competitors")->first_node("competitor")->first_attribute("name")->value()) + 1];
					std::strcpy(events[i].home_name, event_node->first_node("competitors")->first_node("competitor")->first_attribute("name")->value());
				}


				if (events[i].away_name != NULL) { delete[] events[i].away_name; events[i].away_name = NULL; }
				if (event_node->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("name")) {
					events[i].away_name = new char[strlen(event_node->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("name")->value()) + 1];
					std::strcpy(events[i].away_name, event_node->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("name")->value());
				}


				events[i].home_id = atoi((char*)((char*)event_node->first_node("competitors")->first_node("competitor")->first_attribute("id")->value() + 14));
				events[i].away_id = atoi((char*)((char*)event_node->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("id")->value() + 14));

				if (event_node->first_node("competitors")->first_node("competitor")->first_attribute("id")->value()[3] == 'c')
					events[i].home_super_id = atoi((char*)event_node->first_node("competitors")->first_node("competitor")->first_node("reference_ids")->first_node("reference_id")->first_attribute("value")->value()); else {
					events[i].home_super_id = events[i].home_id; events[i].home_id = 0;
				}

				if (event_node->first_node("competitors")->last_node("competitor")->first_attribute("id")->value()[3] == 'c')
					events[i].away_super_id = atoi((char*)event_node->first_node("competitors")->last_node("competitor")->first_node("reference_ids")->first_node("reference_id")->first_attribute("value")->value()); else {
					events[i].away_super_id = events[i].away_id; events[i].away_id = 0;
				}

				events[i].tournament_id = atoi((char*)((char*)event_node->first_node("tournament")->first_attribute("id")->value() + 14));
				if (events[i].tournament_id == 0) {
					events[i].simple_id = atoi((char*)((char*)event_node->first_node("tournament")->first_attribute("id")->value() + 21));
					events[i].type_radar = 2;
				} else events[i].type_radar = 0;

				events[i].sport_id = atoi((char*)((char*)event_node->first_node("tournament")->first_node("sport")->first_attribute("id")->value() + 9));
				events[i].category_id = atoi((char*)((char*)event_node->first_node("tournament")->first_node("category")->first_attribute("id")->value() + 12));





				if (events[i].category_id >= MAX_CATEGORIES) std::printf("ERROR DATA!\r\ncategory id out of MAX_CATEGORIES in getEvents %d\r\n", events[i].category_id);
				else {
					if (categories_id[events[i].category_id] == NULL) {
						categories_id[events[i].category_id] = &categories[categories_l];
						categories_l++;

					}
					categories_id[events[i].category_id]->id = events[i].category_id;
					categories_id[events[i].category_id]->sport_id = events[i].sport_id;

					if (categories_id[events[i].category_id]->name != NULL) {
						delete[] categories_id[events[i].category_id]->name; categories_id[events[i].category_id]->name = NULL;}

					categories_id[events[i].category_id]->name = new char[strlen(event_node->first_node("tournament")->first_node("category")->first_attribute("name")->value()) + 1];
					std::strcpy(categories_id[events[i].category_id]->name, event_node->first_node("tournament")->first_node("category")->first_attribute("name")->value());

				
				}
















				if (events[i].tournament_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\ntournament id out of MAX_TOURNAMENTS in getEvents %d\r\n", events[i].tournament_id); continue; }

				if (events[i].type_radar == 0) {
					if (tournaments_id[events[i].tournament_id] == NULL) {
						tournaments_id[events[i].tournament_id] = &tournaments[tournaments_l];
						tournaments_l++;
					}


					tournaments_id[events[i].tournament_id]->type_radar = events[i].type_radar;
					tournaments_id[events[i].tournament_id]->id = events[i].tournament_id;
					tournaments_id[events[i].tournament_id]->category_id = events[i].category_id;
					tournaments_id[events[i].tournament_id]->sport_id = events[i].sport_id;

					if (tournaments_id[events[i].tournament_id]->name != NULL) delete[] tournaments_id[events[i].tournament_id]->name;
					tournaments_id[events[i].tournament_id]->name = new char[strlen(event_node->first_node("tournament")->first_attribute("name")->value()) + 1];
					std::strcpy(tournaments_id[events[i].tournament_id]->name, event_node->first_node("tournament")->first_attribute("name")->value());
				}

					
				if (events[i].type_radar == 2) {
					if (simples_id[events[i].simple_id] == NULL) {
						simples_id[events[i].simple_id] = &tournaments[tournaments_l];
						tournaments_l++;
					}


					simples_id[events[i].simple_id]->type_radar = events[i].type_radar;
					simples_id[events[i].simple_id]->id = 0;
					simples_id[events[i].simple_id]->simple_id = events[i].simple_id;
					simples_id[events[i].simple_id]->category_id = events[i].category_id;
					simples_id[events[i].simple_id]->sport_id = events[i].sport_id;

					if (simples_id[events[i].simple_id]->name != NULL) delete[] simples_id[events[i].simple_id]->name;
					simples_id[events[i].simple_id]->name = new char[strlen(event_node->first_node("tournament")->first_attribute("name")->value()) + 1];
					std::strcpy(simples_id[events[i].simple_id]->name, event_node->first_node("tournament")->first_attribute("name")->value());
				}


					

					if (event_node->first_node("season") && events[i].type_radar==0) {
						
						if (tournaments_id[events[i].tournament_id]->season_name != NULL) { delete[] tournaments_id[events[i].tournament_id]->season_name; tournaments_id[events[i].tournament_id]->season_name = NULL; }
						
						tournaments_id[events[i].tournament_id]->season_name = new char[strlen(event_node->first_node("season")->first_attribute("name")->value()) + 1];
						std::strcpy(tournaments_id[events[i].tournament_id]->season_name, event_node->first_node("season")->first_attribute("name")->value());

						
						tournaments_id[events[i].tournament_id]->season_id = atoi((char*)((char*)event_node->first_node("season")->first_attribute("id")->value() + 10));
						seasons_id[tournaments_id[events[i].tournament_id]->season_id] = tournaments_id[events[i].tournament_id];
					

						if (tournaments_id[events[i].tournament_id]->season_id > 0) {
							if (tournaments_id[events[i].tournament_id]->season_id < MAX_TOURNAMENTS) seasons_id[tournaments_id[events[i].tournament_id]->season_id] = tournaments_id[events[i].tournament_id]; else std::printf("ERROR DATA!\r\ntournament season_id out of MAX_TOURNAMANETS in getEvents %d\r\n", tournaments_id[events[i].tournament_id]->season_id);
						}



						if (event_node->first_node("season")->first_attribute("start_date")) {
							strcpy(buf, event_node->first_node("season")->first_attribute("start_date")->value());
							st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
							sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

							tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
							tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
							start = mktime(&tm);
							tournaments_id[events[i].tournament_id]->start_date = (int)start;

						}

						if (event_node->first_node("season")->first_attribute("end_date")) {
							strcpy(buf, event_node->first_node("season")->first_attribute("end_date")->value());
							st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
							sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

							tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
							tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
							start = mktime(&tm);
							tournaments_id[events[i].tournament_id]->end_date = (int)start;

						}

					}

				
			
			
			
			}
			else {
				events[i].parent_id = atoi((char*)((char*)event_node->first_node("parent")->first_attribute("id")->value() + 14));

				if (events[i].home_name != NULL) {
					delete[] events[i].home_name; events[i].home_name = NULL;
				}
				if (event_node->first_attribute("name")) {
					events[i].home_name = new char[strlen(event_node->first_attribute("name")->value()) + 1];
					std::strcpy(events[i].home_name, event_node->first_attribute("name")->value());
				}

				if (events[i].away_name != NULL) {
					delete[] events[i].away_name; events[i].away_name = NULL;
				}
				if (event_node->first_node("parent")->first_attribute("name")) {
					events[i].away_name = new char[strlen(event_node->first_node("parent")->first_attribute("name")->value()) + 1];
					std::strcpy(events[i].away_name, event_node->first_node("parent")->first_attribute("name")->value());
				}




				if (event_node->first_node("tournament"))
				{
					events[i].tournament_id = atoi((char*)((char*)event_node->first_node("tournament")->first_attribute("id")->value() + 19));
					events[i].sport_id = atoi((char*)((char*)event_node->first_node("tournament")->first_node("sport")->first_attribute("id")->value() + 9));
					events[i].category_id = atoi((char*)((char*)event_node->first_node("tournament")->first_node("category")->first_attribute("id")->value() + 12));


					if (events[i].category_id >= MAX_CATEGORIES) std::printf("ERROR DATA!\r\ncategory id out of MAX_CATEGORIES in getEvents %d\r\n", events[i].category_id);
					else {
						if (categories_id[events[i].category_id] == NULL) {
							categories_id[events[i].category_id] = &categories[categories_l];
							categories_l++;

						}
						categories_id[events[i].category_id]->id = events[i].category_id;
						categories_id[events[i].category_id]->sport_id = events[i].sport_id;

						if (categories_id[events[i].category_id]->name != NULL) {
							delete[] categories_id[events[i].category_id]->name; categories_id[events[i].category_id]->name = NULL;
						}

						categories_id[events[i].category_id]->name = new char[strlen(event_node->first_node("tournament")->first_node("category")->first_attribute("name")->value()) + 1];
						std::strcpy(categories_id[events[i].category_id]->name, event_node->first_node("tournament")->first_node("category")->first_attribute("name")->value());


					}



					if (events[i].tournament_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\ntournament id out of MAX_TOURNAMENTS in getEvents %d\r\n", events[i].tournament_id); continue; }
					if (tournaments_id[events[i].tournament_id] == NULL) {
						tournaments_id[events[i].tournament_id] = &tournaments[tournaments_l];
						tournaments_l++;
					}


					tournaments_id[events[i].tournament_id]->type_radar = events[i].type_radar;
					tournaments_id[events[i].tournament_id]->id = events[i].tournament_id;
					tournaments_id[events[i].tournament_id]->category_id = events[i].category_id;
					tournaments_id[events[i].tournament_id]->sport_id = events[i].sport_id;

					if (tournaments_id[events[i].tournament_id]->name != NULL) delete[] tournaments_id[events[i].tournament_id]->name;
					tournaments_id[events[i].tournament_id]->name = new char[strlen(event_node->first_node("tournament")->first_attribute("name")->value()) + 1];
					std::strcpy(tournaments_id[events[i].tournament_id]->name, event_node->first_node("tournament")->first_attribute("name")->value());


				}
			
				if (events[i].tournament_id == 0 && events[i].parent_id > 0 && events_id[events[i].parent_id] != NULL) {
					events[i].tournament_id = events_id[events[i].parent_id]->tournament_id;
					events[i].sport_id = events_id[events[i].parent_id]->sport_id;
					events[i].category_id = events_id[events[i].parent_id]->category_id;
				}
			
			}

			if(events[i].id<MAX_EVENTS) events_id[events[i].id] = &events[i]; else std::printf("ERROR DATA!\r\nevent id out of MAX_EVENTS in getEvents%d\r\n", events[i].id);
			//&& events[i].start_time>time(nullptr)
		if (booking > 0 && events[i].booked == 2 &&events[i].status == 0 && booked_num < booking) {postBooked(events[i].id); booked_num++;}
		//&& (events[i].sport_id == 1 || events[i].sport_id == 2 || events[i].sport_id == 4 || events[i].sport_id == 5 || events[i].sport_id == 12 || events[i].sport_id == 23 || events[i].sport_id == 6))
			i++;

		}
		doc.clear();
	}


	delete[] recvbuf;

	events_l = i;
	std::printf("Create events successful. Numbers of events: %d\r\n", events_l);



}
int getVariantMarkets(Market* market, char* urn) {

	char buffer[MAX_PATH];
	char buf[MAX_PATH];
	int* outcome_id = new int[MAX_OUTCOME];
	char** outcome_name = new char*[MAX_OUTCOME];
	char* recvbuf = new char[DEFAULT_BUFLEN];
	Market* _market;
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;
	//using namespace std;
	int k = 0;
	int i = 0;
	int j = 0;
	int c = 0;
	for (i = 0; i < MAX_OUTCOME; i++) outcome_name[i] = new char[MAX_OUTCOME_NAME];

	if(market->type==3) std::strcpy(buffer, "/v1/pre/descriptions/en/markets/");
	else if (urn[0]=='l' && urn[1] == 'o' && urn[2] == ':') std::strcpy(buffer, "/v1/liveodds/descriptions/en/markets/");
	else  std::strcpy(buffer, "/v1/descriptions/en/markets/"); 
	
	_itoa(market->id, buf, 10);
	std::strcat(buffer, buf);
	std::strcat(buffer, "/variants/");
	std::strcat(buffer, urn);
	while (httpsRequest("api.betradar.com", buffer, recvbuf, 0) == -1) Sleep(1000);

	for (k = 0; k < 1000; k++) if (recvbuf[k] == '\r' && recvbuf[k + 1] == '\n' && recvbuf[k + 2] == '\r' && recvbuf[k + 3] == '\n') break;
	doc.parse<0>((char*)((char*)recvbuf + k + 4));
	root_node = doc.first_node("market_descriptions");
	if (root_node == NULL || root_node->first_node("market")==NULL) {
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
		if (j == -1 && markets_id[market->id][i] == NULL) j = i;
		if (markets_id[market->id][i] != NULL && markets_id[market->id][i]->variable_text != NULL && std::strcmp(urn, markets_id[market->id][i]->variable_text) == 0)
		{
			j = i; break;
		}
}
	
	


	if (i == max_markets_in[market->id]) {
		if (j == -1) { j = max_markets_in[market->id];  max_markets_in[market->id]++;
		}
	     markets_id[market->id][j] = &markets[markets_l];  markets_l++;


}


	   markets_id[market->id][j][0] = market[0];
	  _market = markets_id[market->id][j];

	
	  if ((_market->type == 3 ||( _market->type ==0 && _market->variant>-1 && _market->variable_text != NULL && _market->variable_text[0] == 'l' && _market->variable_text[1] == 'o' && _market->variable_text[2] == ':')) && root_node->first_node("market") && root_node->first_node("market")->first_attribute("name")) {
		  if (_market->name != NULL) delete[] _market->name;
		  _market->name = new char[strlen(root_node->first_node("market")->first_attribute("name")->value()) + 1];
		  std::strcpy(_market->name, root_node->first_node("market")->first_attribute("name")->value());
		  	  }

	

	if (_market->variable_text != NULL) delete[] _market->variable_text;
	_market->variable_text = new char[strlen(urn) + 1];
	std::strcpy(_market->variable_text, urn);
	_market->outcome_number = 0;


	if (root_node->first_node("market") && root_node->first_node("market")->first_node("outcomes")) for (xml_node<> * outcome_node = root_node->first_node("market")->first_node("outcomes")->first_node("outcome"); outcome_node; outcome_node = outcome_node->next_sibling()) {
		if(_market->type==3) outcome_id[_market->outcome_number] = atoi((char*)((char*)outcome_node->first_attribute("id")->value() + 16));
			else outcome_id[_market->outcome_number] = atoi((char*)((char*)outcome_node->first_attribute("id")->value() + strlen(_market->variable_text)+1));
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

	saveMarketToFile(_market);

	for (i = 0; i < MAX_OUTCOME; i++) delete[] outcome_name[i];
	delete[] outcome_name;
	delete[] outcome_id;
	delete[] recvbuf;
	doc.clear();
	return 0;
}
void getMarkets() {
	char* recvbuf = new char[DEFAULT_BUFLEN];
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
		specifier_description[i] = NULL; specifier_name[i] = NULL;
	}


	while (httpsRequest("api.betradar.com", "/v1/descriptions/en/markets.xml?include_mappings=true", recvbuf, 0) == -1) Sleep(1000);
	//httpsRequest("api.betradar.com", "/v1/descriptions/en/markets.xml?include_mappings=true", recvbuf2, 0);


	for (k = 0; k < 1000; k++) if (recvbuf[k] == '\r' && recvbuf[k + 1] == '\n' && recvbuf[k + 2] == '\r' && recvbuf[k + 3] == '\n') break;
	doc.parse<0>((char*)((char*)recvbuf + k + 4));
	root_node = doc.first_node("market_descriptions");
	if (root_node == NULL) {
		for (int i = 0; i < MAX_PATH; i++) { if (specifier_name[i] != NULL) delete[] specifier_name[i]; if (specifier_description[i] != NULL) delete[] specifier_description[i]; }
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
		if (markets[i].name != NULL) delete[] markets[i].name;
		markets[i].name = new char[strlen(market_node->first_attribute("name")->value()) + 1];
		std::strcpy(markets[i].name, market_node->first_attribute("name")->value());
		if (market_node->first_attribute("includes_outcomes_of_type") != NULL) {
			if (strcmp("sr:player", market_node->first_attribute("includes_outcomes_of_type")->value()) == 0)  markets[i].type = 1; else
				if (strcmp("sr:competitor", market_node->first_attribute("includes_outcomes_of_type")->value()) == 0)  markets[i].type = 2;else
			if (strcmp("pre:outcometext", market_node->first_attribute("includes_outcomes_of_type")->value()) == 0)  markets[i].type = 3;
			else markets[i].type = 4;
		}


		markets[i].outcome_number = 0;

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
			else specifier_description[j] = NULL;

			if (specifier_node->first_attribute("name")) {
				specifier_name[j] = new char[NAME_LENTGH]; std::strcpy(specifier_name[j], specifier_node->first_attribute("name")->value());

			}
			else specifier_name[j] = NULL;

			//0 null //1 int //2 string 3://decimal 4//variable	
			specifier_type[j] = 0;
			
			if (specifier_node->first_attribute("type") != NULL) {
		
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
				if (specifier_name[k] != NULL) {
					markets[i].specifier_name[k] = new char[strlen(specifier_name[k]) + 1]; std::strcpy(markets[i].specifier_name[k], specifier_name[k]);
				}
				else markets[i].specifier_name[k] = NULL;


				if (specifier_description[k] != NULL) {
					markets[i].specifier_description[k] = new char[strlen(specifier_description[k]) + 1]; std::strcpy(markets[i].specifier_description[k], specifier_description[k]);
				}
				else markets[i].specifier_description[k] = NULL;

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
		if (markets[i].id == 60) markets[i].line_type = 5;// 1st half - 1x2 Soccer,Basketball,American Football,Aussie Rules,Futsal,Handball,Rugby,Soccer Mythical
		if (markets[i].id == 83) markets[i].line_type = 5;// 2nd half - 1x2 Soccer,Basketball,American Football,Handball,Soccer Mythical
		if (markets[i].id == 113) markets[i].line_type = 5;// Overtime - 1x2 Soccer,Futsal,Ice Hockey
		if (markets[i].id == 119) markets[i].line_type = 5;//Overtime 1st half - 1x2  Soccer
		if (markets[i].id == 120) markets[i].line_type = 7;//Overtime 1st half - handicap Soccer
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
		if (markets[i].id == 117) markets[i].line_type = 7;//Overtime - handicap Soccer,Handball
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
		if (markets[i].id == 116) markets[i].line_type = 8;//Overtime - total Soccer,Futsal,Handball,Ice Hockey
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
    	if (markets[i].id == 115) markets[i].line_type = 10;//Overtime - {!goalnr} goal Soccer,Futsal,Ice Hockey
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
				for (int l = 0; l < MAX_MARKETS_IN; l++) markets_id[markets[i].id][l] = NULL;
				markets_id[markets[i].id][0] = &markets[i];
				saveMarketToFile(&markets[i]);
			}
			else { std::printf("ERROR DATA!\r\nmarket id out of MAX_MARKETS in getMarkets%d\r\n", markets[i].id); continue; }
			
			if (market_node->first_node("mappings") && market_node->first_node("mappings")->first_node("mapping"))
						
			for (xml_node<> * mapping_node = market_node->first_node("mappings")->first_node("mapping"); mapping_node; mapping_node = mapping_node->next_sibling())	{
				
			

				if (mapping_node->first_attribute("valid_for")) {
					v = mapping_node->first_attribute("valid_for")->value_size();
					for (u = 0; u < v-8; u++) if (mapping_node->first_attribute("valid_for")->value()[u] == 'v'&& mapping_node->first_attribute("valid_for")->value()[u + 1] == 'a'&& mapping_node->first_attribute("valid_for")->value()[u + 2] == 'r' && mapping_node->first_attribute("valid_for")->value()[u + 6] == 't'&& mapping_node->first_attribute("valid_for")->value()[u + 7] == '=') break;
					if (u == v - 8) continue;
					strcpy(urn, (char*)((char*)mapping_node->first_attribute("valid_for")->value()) + 8+u);
					
					for (int i = 0; i < v - 8 - u; i++) if (urn[i] == '|') { urn[i] = 0; break; }
			
				getVariantMarkets(&markets[i], urn);
		    	}
            }
			
		
		}
		else {
			if (markets[i].id < MAX_MARKETS) {
			markets_id[markets[markets_l - 1].id] = new Market*[1];
			markets_id[markets[markets_l - 1].id][0] = &markets[markets_l - 1];
			saveMarketToFile(&markets[markets_l - 1]);
		}
			else {
				std::printf("ERROR DATA!\r\nmarket id out of MAX_MARKETS in getMarkets%d\r\n", markets[i].id); continue;
			}
			
			//printf(markets_id[markets[markets_l - 1].id][0]->name);

			//printf("\r\n");
		}


	}


	std::printf("Load %d markets done.\r\n", markets_l);

	for (int i = 0; i < MAX_PATH; i++) { if (specifier_name[i] != NULL) delete[] specifier_name[i]; if (specifier_description[i] != NULL) delete[] specifier_description[i]; }
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
int getPlayer(Player* player) {
	char* recvbuf = new char[DEFAULT_BUFLEN];
	char buf[20];
	char buffer[1024];
	_itoa(player->id, buf, 10);
	std::strcpy(buffer, "/v1/sports/en/players/sr:player:");
	std::strcat(buffer, buf);
	std::strcat(buffer, "/profile.xml");
	while (httpsRequest("api.betradar.com", buffer, recvbuf, 0) == -1) Sleep(1000);
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

	for (j = 0; j < 1000; j++) if (recvbuf[j] == '\r' && recvbuf[j + 1] == '\n' && recvbuf[j + 2] == '\r' && recvbuf[j + 3] == '\n') break;
	//printf(((char*)((char*)recvbuf + j + 4)));
	doc.parse<0>((char*)((char*)recvbuf + j + 4));
	//printf(((char*)((char*)recvbuf + j + 4)));
	//printf("\r\n\r\n");
	root_node = doc.first_node("player_profile");
	if (root_node == NULL) { delete[] recvbuf; doc.clear(); return -1; }
	xml_node<> * player_node = root_node->first_node("player"); if (player_node == NULL) {
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
		if (player->name != NULL) delete[] player->name; player->name = new char[strlen(player_node->first_attribute("name")->value()) + 1]; std::strcpy(player->name, player_node->first_attribute("name")->value());
		//std::printf("name_length=%d\r\n", strlen(player_node->first_attribute("name")->value()));
	}
	if (player_node->first_attribute("full_name"))
	{
		if (player->full_name != NULL) delete[] player->full_name; player->full_name = new char[strlen(player_node->first_attribute("full_name")->value()) + 1]; std::strcpy(player->full_name, player_node->first_attribute("full_name")->value());

		//std::printf("full_name_length=%d\r\n", strlen(player_node->first_attribute("full_name")->value()));

	}
	if (player_node->first_attribute("nationality"))
	{
		if (player->nationality != NULL) delete[] player->nationality; player->nationality = new char[strlen(player_node->first_attribute("nationality")->value()) + 1]; std::strcpy(player->nationality, player_node->first_attribute("nationality")->value());

		//std::printf("nationality_length=%d\r\n", strlen(player_node->first_attribute("nationality")->value()));
	}
	if (player_node->first_attribute("country_code"))
	{
		if (player->country_code != NULL) delete[] player->country_code; player->country_code = new char[strlen(player_node->first_attribute("country_code")->value()) + 1]; std::strcpy(player->country_code, player_node->first_attribute("country_code")->value());
	}
	if (player_node->first_attribute("type"))
	{
		if (player->type != NULL) delete[] player->type; player->type = new char[strlen(player_node->first_attribute("type")->value()) + 1]; std::strcpy(player->type, player_node->first_attribute("type")->value());
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
	else if (players_id[player->id] == NULL) players_id[player->id] = player;
	savePlayerToFile(player);
	doc.clear();
	delete[] recvbuf;
	return 0;
}
int getCompetitor(Competitor* competitor) {
	char* recvbuf = new char[DEFAULT_BUFLEN];
	Player* player = new Player();
	char buf[20];
	char buffer[1024];
	_itoa(competitor->id, buf, 10);
	std::strcpy(buffer, "/v1/sports/en/competitors/sr:competitor:");
	std::strcat(buffer, buf);
	std::strcat(buffer, "/profile.xml");
	while (httpsRequest("api.betradar.com", buffer, recvbuf, 0) == -1) Sleep(1000);
	using namespace rapidxml;
	SYSTEMTIME st;
	struct tm tm;
	time_t start;
	memset(&st, 0, sizeof(st));
	memset(&tm, 0, sizeof(tm));
	xml_document<> doc;
	xml_node<> * root_node;
	int j = 0;
	int i = 0;

	for (j = 0; j < 1000; j++) if (recvbuf[j] == '\r' && recvbuf[j + 1] == '\n' && recvbuf[j + 2] == '\r' && recvbuf[j + 3] == '\n') break;
	//printf(((char*)((char*)recvbuf + j + 4)));
	doc.parse<0>((char*)((char*)recvbuf + j + 4));
	//printf(((char*)((char*)recvbuf + j + 4)));
	//printf("\r\n\r\n");
	root_node = doc.first_node("competitor_profile");
	if (root_node == NULL) { delete[] recvbuf; delete player; doc.clear(); return -1; }
	xml_node<> * competitor_node = root_node->first_node("competitor"); if (competitor_node == NULL) { delete[] recvbuf; delete player; doc.clear(); return -1; }


	

	if (competitor_node->first_attribute("name")) {
		if (competitor->name != NULL) delete[] competitor->name; competitor->name = new char[strlen(competitor_node->first_attribute("name")->value()) + 1]; std::strcpy(competitor->name, competitor_node->first_attribute("name")->value());
	}
	
	if (competitor_node->first_attribute("country")) {
		if (competitor->country_name != NULL) delete[] competitor->country_name; competitor->country_name = new char[strlen(competitor_node->first_attribute("country")->value()) + 1]; std::strcpy(competitor->country_name, competitor_node->first_attribute("country")->value());
	}

	if (competitor_node->first_node("sport") && competitor_node->first_node("sport")->first_attribute("id"))
	{
		competitor->sport_id = atoi((char*)((char*)competitor_node->first_node("sport")->first_attribute("id")->value() + 9));
	}
	

	if (competitor_node->first_node("category") && competitor_node->first_node("category")->first_attribute("id"))
	{
		competitor->category_id = atoi((char*)((char*)competitor_node->first_node("category")->first_attribute("id")->value() + 12));
	}
	

	if (competitor->id >= MAX_COMPETITORS)  {std::printf("ERROR DATA!\r\ncompetitors id out of MAX_COMPETITORS in getCompetitors %d\r\n", competitor->id); 
	 delete[] recvbuf; delete player; doc.clear(); return -1; } else  competitors_id[competitor->id] = competitor;
		
//	std::printf("competitors_l=%d\r\n", competitors_l);

	 saveCompetitorToFile(competitor);


	xml_node<> * manager_node = root_node->first_node("manager");
	if (manager_node) {
		player->competitor_id = competitor->id;
		player->manager = 1;
		player->id = atoi((char*)((char*)manager_node->first_attribute("id")->value() + 10));
		if (manager_node->first_attribute("name"))
		{
			if (player->name != NULL) delete[] player->name; player->name = new char[strlen(manager_node->first_attribute("name")->value()) + 1]; std::strcpy(player->name, manager_node->first_attribute("name")->value());
		}

		if (manager_node->first_attribute("nationality"))
		{
			if (player->nationality != NULL) delete[] player->nationality; player->nationality = new char[strlen(manager_node->first_attribute("nationality")->value()) + 1]; std::strcpy(player->nationality, manager_node->first_attribute("nationality")->value());
		}

		//for (i = 0; i < players_l; i++) if (players[i].id == player->id) break;
		//players[i] = player[0]; if (i == players_l) players_l++;

		if (player->id >= MAX_PLAYERS) {
			std::printf("ERROR DATA!\r\nplayers id out of MAX_PLAYERS in getCompetitor%d\r\n", player->id);
		}
		else if (players_id[player->id] == NULL) {
			players[players_l] = player[0];
			players_id[player->id] = &players[players_l];
			players_l++;
		}
		else players_id[player->id][0] = player[0];


	}

	

	if (root_node->first_node("players"))
		for (xml_node<> * player_node = root_node->first_node("players")->first_node("player"); player_node; player_node = player_node->next_sibling())
		{
			player->competitor_id = competitor->id;

			player->id = atoi((char*)((char*)player_node->first_attribute("id")->value() + 10));
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
				if (player->name != NULL) delete[] player->name; player->name = new char[strlen(player_node->first_attribute("name")->value()) + 1]; std::strcpy(player->name, player_node->first_attribute("name")->value());
				//std::printf("name_length=%d\r\n", strlen(player_node->first_attribute("name")->value()));
			}
		
			if (player_node->first_attribute("full_name"))
			{
				if (player->full_name != NULL) delete[] player->full_name; player->full_name = new char[strlen(player_node->first_attribute("full_name")->value()) + 1]; std::strcpy(player->full_name, player_node->first_attribute("full_name")->value());

				//std::printf("full_name_length=%d\r\n", strlen(player_node->first_attribute("full_name")->value()));

			}
			if (player_node->first_attribute("nationality"))
			{
				if (player->nationality != NULL) delete[] player->nationality; player->nationality = new char[strlen(player_node->first_attribute("nationality")->value()) + 1]; std::strcpy(player->nationality, player_node->first_attribute("nationality")->value());

				//std::printf("nationality_length=%d\r\n", strlen(player_node->first_attribute("nationality")->value()));
			}
			if (player_node->first_attribute("country_code"))
			{
				if (player->country_code != NULL) delete[] player->country_code; player->country_code = new char[strlen(player_node->first_attribute("country_code")->value()) + 1]; std::strcpy(player->country_code, player_node->first_attribute("country_code")->value());
			}
			if (player_node->first_attribute("type"))
			{
				if (player->type != NULL) delete[] player->type; player->type = new char[strlen(player_node->first_attribute("type")->value()) + 1]; std::strcpy(player->type, player_node->first_attribute("type")->value());

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
			
		
			if (player->id >= MAX_PLAYERS) {
				std::printf("ERROR DATA!\r\nplayers id out of MAX_PLAYERS in getCompetitor%d\r\n", player->id); continue;
			}
			else if (players_id[player->id] == NULL) {
				players[players_l] = player[0];
			    players_id[player->id] = &players[players_l];
				players_l++;
			}
			else players_id[player->id][0] = player[0];
		
			


			savePlayerToFile(player);

		}



	delete player;
	delete[] recvbuf;
	doc.clear();
	return 0;
}
int getEventFixture(Event* event) {
	char buf[10];
	char buffer[4096];
	char* recvbuf = new char[DEFAULT_BUFLEN];
	//if (event->type_radar == 1) return;
	_itoa(event->id, buf, 10);
	if (event->type_radar == 0|| event->type_radar == 2) std::strcpy(buffer, "/v1/sports/en/sport_events/sr:match:");
	else std::strcpy(buffer, "/v1/sports/en/sport_events/sr:race_event:");
	std::strcat(buffer, buf);
	
	std::strcat(buffer, "/fixture.xml");
	while (httpsRequest("api.betradar.com", buffer, recvbuf, 0) == -1) Sleep(1000); 
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
	int i=0;
	for (j = 0; j < 1000; j++) if (recvbuf[j] == '\r' && recvbuf[j + 1] == '\n' && recvbuf[j + 2] == '\r' && recvbuf[j + 3] == '\n') break;
	doc.parse<0>((char*)((char*)recvbuf + j + 4));

	
	root_node = doc.first_node("fixtures_fixture");
	if (root_node == NULL) { delete[] recvbuf; doc.clear(); return -1; }
	if (root_node->first_node("fixture")->first_attribute("start_time")) {
		std::strcpy(buf, root_node->first_node("fixture")->first_attribute("start_time")->value());
		sscanf(buf, "%d-%d-%dT%d:%d:%d", &st.wYear, &st.wMonth, &st.wDay, &st.wHour, &st.wMinute, &st.wSecond);
		tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
		tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
		start = mktime(&tm);
		event->start_time = (int)start;
	}
	
	if (root_node->first_node("fixture")->first_attribute("next_live_time")) {
		std::strcpy(buf, root_node->first_node("fixture")->first_attribute("next_live_time")->value());
		sscanf(buf, "%d-%d-%dT%d:%d:%d", &st.wYear, &st.wMonth, &st.wDay, &st.wHour, &st.wMinute, &st.wSecond);
		tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
		tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
		start = mktime(&tm);
		event->next_live_time = (int)start;
	}

	
	

	if (event->type_radar == 1) {

		if (root_node->first_node("fixture")->first_attribute("type") && root_node->first_node("fixture")->first_attribute("type")->value()[0] == 'p') 
		 event->parent_id = -1;
		
		else if	(root_node->first_node("fixture")->first_node("parent")) event->parent_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("parent")->first_attribute("id")->value() + 14));



		if (event->home_name != NULL) { delete[] event->home_name; event->home_name = NULL; }
		if (root_node->first_node("fixture")->first_attribute("name")) {
			event->home_name = new char[strlen(root_node->first_node("fixture")->first_attribute("name")->value()) + 1];
			std::strcpy(event->home_name, root_node->first_node("fixture")->first_attribute("name")->value());
		}

		if (event->away_name != NULL) {
			delete[] event->away_name; event->away_name = NULL;
		}
		
		if (event->parent_id != -1 && root_node->first_node("fixture")->first_node("parent") && root_node->first_node("fixture")->first_node("parent")->first_attribute("name")) {
			event->away_name = new char[strlen(root_node->first_node("fixture")->first_node("parent")->first_attribute("name")->value()) + 1];
			std::strcpy(event->away_name, root_node->first_node("fixture")->first_node("parent")->first_attribute("name")->value());
		}



		if (root_node->first_node("fixture")->first_node("tournament"))
		{
			event->tournament_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_attribute("id")->value() + 19));
			event->sport_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_node("sport")->first_attribute("id")->value() + 9));
			event->category_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_node("category")->first_attribute("id")->value() + 12));



			if (event->tournament_id >= MAX_TOURNAMENTS) std::printf("ERROR DATA!\r\ntournament id out of MAX_TOURNAMENTS in getEventFixture %d\r\n", event->tournament_id);
			else {
				if (tournaments_id[event->tournament_id] == NULL) {
					tournaments_id[event->tournament_id] = &tournaments[tournaments_l];
					tournaments_l++;
				}

				tournaments_id[event->tournament_id]->type_radar = event->type_radar;
				tournaments_id[event->tournament_id]->id = event->tournament_id;
				tournaments_id[event->tournament_id]->category_id = event->category_id;
				tournaments_id[event->tournament_id]->sport_id = event->sport_id;

				if (tournaments_id[event->tournament_id]->name != NULL) delete[] tournaments_id[event->tournament_id]->name;
				tournaments_id[event->tournament_id]->name = new char[strlen(root_node->first_node("fixture")->first_node("tournament")->first_attribute("name")->value()) + 1];
				std::strcpy(tournaments_id[event->tournament_id]->name, root_node->first_node("fixture")->first_node("tournament")->first_attribute("name")->value());
			}




			if (event->category_id >= MAX_CATEGORIES) std::printf("ERROR DATA!\r\ncategory id out of MAX_CATEGORIES in getEventFixture %d\r\n", event->category_id);
			else {
				if (categories_id[event->category_id] == NULL) {
					i = categories_l; categories_l++;
					categories_id[event->category_id] = &categories[i];

				}
				categories_id[event->category_id]->id = event->category_id;
				categories_id[event->category_id]->sport_id = event->sport_id;

				if (categories_id[event->category_id]->name != NULL) { delete[] categories_id[event->category_id]->name; categories_id[event->category_id]->name = NULL; }
				categories_id[event->category_id]->name = new char[strlen(root_node->first_node("fixture")->first_node("tournament")->first_node("category")->first_attribute("name")->value()) + 1];
				std::strcpy(categories_id[event->category_id]->name, root_node->first_node("fixture")->first_node("tournament")->first_node("category")->first_attribute("name")->value());

			}









		}
	}
	if (event->type_radar == 0 || event->type_radar == 2) {
		if (root_node->first_node("fixture")->first_attribute("liveodds")) {
			std::strcpy(buf, root_node->first_node("fixture")->first_attribute("liveodds")->value());
			if (buf[0] == 'b'&& buf[1] == 'o') event->booked = 1;
		}

		if (event->home_name != NULL) { delete[] event->home_name; event->home_name = NULL; }
		if (root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->first_attribute("name")) {
			event->home_name = new char[strlen(root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->first_attribute("name")->value()) + 1];
			std::strcpy(event->home_name, root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->first_attribute("name")->value());
		}

		if (event->away_name != NULL) { delete[] event->away_name; event->away_name = NULL; }
		if (root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("name")) {
			event->away_name = new char[strlen(root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("name")->value()) + 1];
			std::strcpy(event->away_name, root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("name")->value());
		}




		event->home_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->first_attribute("id")->value() + 14));
		event->away_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("id")->value() + 14));

		if (root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->first_attribute("id")->value()[3] == 'c')
			event->home_super_id = atoi((char*)root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->first_node("reference_ids")->first_node("reference_id")->first_attribute("value")->value()); else {
			event->home_super_id = event->home_id; event->home_id = 0;
		}

		if (root_node->first_node("fixture")->first_node("competitors")->last_node("competitor")->first_attribute("id")->value()[3] == 'c')
			event->away_super_id = atoi((char*)root_node->first_node("fixture")->first_node("competitors")->last_node("competitor")->first_node("reference_ids")->first_node("reference_id")->first_attribute("value")->value()); else {
			event->away_super_id = event->away_id; event->away_id = 0;
		}

		event->tournament_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_attribute("id")->value() + 14));
		if (event->tournament_id == 0) { event->simple_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_attribute("id")->value() + 21)); event->type_radar = 2; } else  event->type_radar = 0;

		event->sport_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_node("sport")->first_attribute("id")->value() + 9));
		event->category_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_node("category")->first_attribute("id")->value() + 12));



		
		if (event->tournament_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\ntournament id out of MAX_TOURNAMENTS in getEventFixture %d\r\n", event->tournament_id); 
		delete[] recvbuf; doc.clear(); return -1;
		}
			else {
				if (event->type_radar == 0) {

					if (tournaments_id[event->tournament_id] == NULL) {
						tournaments_id[event->tournament_id] = &tournaments[tournaments_l];
						tournaments_l++;
					}

					tournaments_id[event->tournament_id]->type_radar = event->type_radar;
					tournaments_id[event->tournament_id]->id = event->tournament_id;
					tournaments_id[event->tournament_id]->category_id = event->category_id;
					tournaments_id[event->tournament_id]->sport_id = event->sport_id;

					if (tournaments_id[event->tournament_id]->name != NULL) delete[] tournaments_id[event->tournament_id]->name;
					tournaments_id[event->tournament_id]->name = new char[strlen(root_node->first_node("fixture")->first_node("tournament")->first_attribute("name")->value()) + 1];
					std::strcpy(tournaments_id[event->tournament_id]->name, root_node->first_node("fixture")->first_node("tournament")->first_attribute("name")->value());
				}
			
				if (event->type_radar == 2) {

					if (simples_id[event->simple_id] == NULL) {
						simples_id[event->simple_id] = &tournaments[tournaments_l];
						tournaments_l++;
					}

					simples_id[event->simple_id]->type_radar = event->type_radar;
					simples_id[event->simple_id]->id = 0;
					simples_id[event->simple_id]->simple_id = event->simple_id;
					simples_id[event->simple_id]->category_id = event->category_id;
					simples_id[event->simple_id]->sport_id = event->sport_id;

					if (simples_id[event->simple_id]->name != NULL) delete[] simples_id[event->simple_id]->name;
					simples_id[event->simple_id]->name = new char[strlen(root_node->first_node("fixture")->first_node("tournament")->first_attribute("name")->value()) + 1];
					std::strcpy(simples_id[event->simple_id]->name, root_node->first_node("fixture")->first_node("tournament")->first_attribute("name")->value());
				}
			
			
			
			}



		
				if (root_node->first_node("fixture")->first_node("tournament")->first_node("season") && event->type_radar == 0) {
					if (tournaments_id[event->tournament_id]->season_name != NULL) { delete[] tournaments_id[event->tournament_id]->season_name; tournaments_id[event->tournament_id]->season_name = NULL; }
					tournaments_id[event->tournament_id]->season_name = new char[strlen(root_node->first_node("fixture")->first_node("tournament")->first_node("season")->first_attribute("name")->value()) + 1];
					std::strcpy(tournaments_id[event->tournament_id]->season_name, root_node->first_node("fixture")->first_node("tournament")->first_node("season")->first_attribute("name")->value());



					tournaments_id[event->tournament_id]->season_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_node("season")->first_attribute("id")->value() + 10));
					seasons_id[tournaments_id[event->tournament_id]->season_id] = tournaments_id[event->tournament_id];


					if (tournaments_id[event->tournament_id]->season_id > 0) {
						if (tournaments_id[event->tournament_id]->season_id < MAX_TOURNAMENTS) seasons_id[tournaments_id[event->tournament_id]->season_id] = tournaments_id[event->tournament_id]; else std::printf("ERROR DATA!\r\ntournament season_id out of MAX_TOURNAMANETS in getEventFixture %d\r\n", tournaments_id[event->tournament_id]->season_id);
					}



					if (root_node->first_node("fixture")->first_node("tournament")->first_node("season")->first_attribute("start_date")) {
						strcpy(buf, root_node->first_node("fixture")->first_node("tournament")->first_node("season")->first_attribute("start_date")->value());
						st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
						sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

						tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
						tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
						start = mktime(&tm);
						tournaments_id[event->tournament_id]->start_date = (int)start;

					}

					if (root_node->first_node("fixture")->first_node("tournament")->first_node("season")->first_attribute("end_date")) {
						strcpy(buf, root_node->first_node("fixture")->first_node("tournament")->first_node("season")->first_attribute("end_date")->value());
						st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
						sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

						tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
						tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
						start = mktime(&tm);
						tournaments_id[event->tournament_id]->end_date = (int)start;

					}



				}


			
			if (event->category_id >= MAX_CATEGORIES) std::printf("ERROR DATA!\r\ncategory id out of MAX_CATEGORIES in getEventFixture %d\r\n", event->category_id);
			else {
				if (categories_id[event->category_id] == NULL) {
					i = categories_l; categories_l++;
					categories_id[event->category_id] = &categories[i];
					
				}
				categories_id[event->category_id]->id = event->category_id;
				categories_id[event->category_id]->sport_id = event->sport_id;

				if (categories_id[event->category_id]->name != NULL) { delete[] categories_id[event->category_id]->name; categories_id[event->category_id]->name = NULL; }
				categories_id[event->category_id]->name = new char[strlen(root_node->first_node("fixture")->first_node("tournament")->first_node("category")->first_attribute("name")->value()) + 1];
				std::strcpy(categories_id[event->category_id]->name, root_node->first_node("fixture")->first_node("tournament")->first_node("category")->first_attribute("name")->value());

			}



		
		
		

		
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
			if (event->tv_channels != NULL) delete[] event->tv_channels;
			event->tv_channels = new char[strlen(buffer) + 1];
			std::strcpy(event->tv_channels, buffer);
			//printf(event->tv_channels);
		}

		if (event->venue != NULL) {
			delete[] event->venue; event->venue = NULL;
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

		if (event->delayed_description != NULL) {
			delete[] event->delayed_description; event->delayed_description = NULL;
		}
	
		if (root_node && root_node->first_node("fixture") && root_node->first_node("fixture")->first_node("delayed_info")) {
			buffer[0] = 0;
			if (root_node->first_node("fixture")->first_node("delayed_info")->first_attribute("description")) { 
				event->delayed_description = new char[strlen(root_node->first_node("fixture")->first_node("delayed_info")->first_attribute("description")->value()) + 1];
			std::strcpy(event->delayed_description, root_node->first_node("fixture")->first_node("delayed_info")->first_attribute("description")->value()); }
			if (root_node->first_node("fixture")->first_node("delayed_info")->first_attribute("id"))
				event->delayed_id = atoi((char*)root_node->first_node("fixture")->first_node("delayed_info")->first_attribute("id"));

		}


}


	delete[] recvbuf;
	if (event->id<MAX_EVENTS) events_id[event->id] = event; else std::printf("ERROR DATA!\r\nevent id out of MAX_EVENTS in getEventFixture %d\r\n", event->id);
	if (event->bo == 0 && (event->sport_id == 5 || event->sport_id == 19)) getEventSummary(event);
	
	
	if (event->type_radar == 1 && event->tournament_id == 0 && event->parent_id > 0 && events_id[event->parent_id] != NULL) {
		event->tournament_id = events_id[event->parent_id]->tournament_id;
		event->sport_id = events_id[event->parent_id]->sport_id;
		event->category_id = events_id[event->parent_id]->category_id;
	}

	if(event->type_radar == 2) saveTournamentToFile(simples_id[event->simple_id]);
	else saveTournamentToFile(tournaments_id[event->tournament_id]);
	saveCategoryToFile(categories_id[event->category_id]);
	saveEventToFile(event);
	doc.clear();
	return 0;
}
int getEventSummary(Event* event) {
	char* recvbuf = new char[DEFAULT_BUFLEN];
	char buf[10];
	char buffer[1024];
	//if (event->type_radar == 1) return;
	_itoa(event->id, buf, 10);
	if (event->type_radar == 0) std::strcpy(buffer, "/v1/sports/en/sport_events/sr:match:");
	else std::strcpy(buffer, "/v1/sports/en/sport_events/sr:race_event:");
	std::strcat(buffer, buf);
	std::strcat(buffer, "/summary.xml");
	while (httpsRequest("api.betradar.com", buffer, recvbuf, 0) == -1) Sleep(1000);
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;
	int j = 0;
	for (j = 0; j < 1000; j++) if (recvbuf[j] == '\r' && recvbuf[j + 1] == '\n' && recvbuf[j + 2] == '\r' && recvbuf[j + 3] == '\n') break;
	doc.parse<0>((char*)((char*)recvbuf + j + 4));

	root_node = doc.first_node("match_summary");
	if (root_node == NULL) { delete[] recvbuf; doc.clear(); return -1; }

	if (root_node->first_node("sport_event_conditions") && root_node->first_node("sport_event_conditions")->first_attribute("match_mode"))
		event->bo = atoi((char*)((char*)root_node->first_node("sport_event_conditions")->first_attribute("match_mode")->value() + 2));
	delete[] recvbuf;
	doc.clear();
	return 0;

}
int getBetstops() {
	char* recvbuf = new char[DEFAULT_BUFLEN];
	while (httpsRequest("api.betradar.com", "/v1/descriptions/betstop_reasons.xml", recvbuf, 0) == -1) Sleep(1000);
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;

	//using namespace std;
	int j = 0;
	int i = 0;
	for (j = 0; j < 1000; j++) if (recvbuf[j] == '\r' && recvbuf[j + 1] == '\n' && recvbuf[j + 2] == '\r' && recvbuf[j + 3] == '\n') break;
	//printf(((char*)((char*)recvbuf + j + 4)));
	doc.parse<0>((char*)((char*)recvbuf + j + 4));
	//printf(((char*)((char*)recvbuf + j + 4)));
	//printf("\r\n\r\n");
	root_node = doc.first_node("betstop_reasons_descriptions");
	if (root_node == NULL) { delete[] recvbuf; doc.clear(); return -1; }
	betstops_l = 0;

	if (root_node->first_node("betstop_reason"))
		for (xml_node<> * betstop_reason = root_node->first_node("betstop_reason"); betstop_reason; betstop_reason = betstop_reason->next_sibling())
		{

			if (betstops[i].description != NULL) {
				delete[] betstops[i].description; betstops[i].description = NULL;
			}

			if (betstop_reason->first_attribute("description")) {

				betstops[i].description = new char[strlen(betstop_reason->first_attribute("description")->value()) + 1]; std::strcpy(betstops[i].description, betstop_reason->first_attribute("description")->value());
			}
			if (betstop_reason->first_attribute("id")) betstops[i].id = atoi(betstop_reason->first_attribute("id")->value());

			if (betstops[i].id < MAX_BETSTOPS) betstops_id[betstops[i].id] = &betstops[i];

			else   std::printf("ERROR DATA!\r\nbetstop id out of MAX_BETSTOPS in getBetstops %d\r\n", betstops[i].id);
			i++;
		
		} else { delete[] recvbuf; doc.clear(); return -1; }
	
		betstops_l = i;
		
	
	delete[] recvbuf;
	doc.clear();
	return 0;

}
int getMatchstatus() {
	char* recvbuf = new char[DEFAULT_BUFLEN];
	while (httpsRequest("api.betradar.com", "/v1/descriptions/en/match_status.xml", recvbuf, 0) == -1) Sleep(1000);
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;

	//using namespace std;
	int j = 0;
	int i = 0;
	for (j = 0; j < 1000; j++) if (recvbuf[j] == '\r' && recvbuf[j + 1] == '\n' && recvbuf[j + 2] == '\r' && recvbuf[j + 3] == '\n') break;
	//printf(((char*)((char*)recvbuf + j + 4)));
	doc.parse<0>((char*)((char*)recvbuf + j + 4));
	//printf(((char*)((char*)recvbuf + j + 4)));
	//printf("\r\n\r\n");
	root_node = doc.first_node("match_status_descriptions");
	if (root_node == NULL) { delete[] recvbuf; doc.clear(); return -1; }
	matchstatus_l = 0;

	if (root_node->first_node("match_status"))
		for (xml_node<> * match_status = root_node->first_node("match_status"); match_status; match_status = match_status->next_sibling())
		{

			if (matchstatus[i].description != NULL) {
				delete[] matchstatus[i].description; matchstatus[i].description = NULL;
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
int getTournament(Tournament* tournament, bool extended) {
	reload_step_1 = 1;
	char buf[MAX_PATH];
	char buffer[1024];
	char* recvbuf = new char[DEFAULT_BUFLEN];
	Competitor* competitor = new Competitor();
	time_t start;
	SYSTEMTIME st;
	struct tm tm;
	std::memset(&st, 0, sizeof(st));
	std::memset(&tm, 0, sizeof(tm));


	
	if(tournament->id ==0 && tournament->season_id == 0 && tournament->simple_id == 0) {
		delete[] recvbuf; delete competitor;  return -1;
	};


	
	if (tournament->type_radar == 0 && tournament->id == 0) _itoa(tournament->season_id, buf, 10);
	else if (tournament->type_radar == 2 && tournament->id == 0) _itoa(tournament->simple_id, buf, 10);
	else _itoa(tournament->id, buf, 10);
	

	std::strcpy(buffer, "/v1/sports/en/tournaments/");
	if (tournament->type_radar == 0 && tournament->id >0) 	std::strcat(buffer, "sr:tournament:"); else
		if (tournament->type_radar == 1) 	std::strcat(buffer, "sr:race_tournament:"); else
			if (tournament->type_radar == 2) 	std::strcat(buffer, "sr:simple_tournament:"); else
				if (tournament->type_radar == 0 && tournament->id == 0) 	std::strcat(buffer, "sr:season:");
				else {
					delete[] recvbuf; delete competitor; return -1;
				};
				
				std::strcat(buffer, buf);
				std::strcat(buffer, "/info.xml");
				while (httpsRequest("api.betradar.com", buffer, recvbuf, 0) == -1) Sleep(1000);
				using namespace rapidxml;
				xml_document<> doc;
				xml_node<> * root_node;
				int i = 0;
				int j = 0;
				for (j = 0; j < 1000; j++) if (recvbuf[j] == '\r' && recvbuf[j + 1] == '\n' && recvbuf[j + 2] == '\r' && recvbuf[j + 3] == '\n') break;
				doc.parse<0>((char*)((char*)recvbuf + j + 4));
				root_node = doc.first_node("tournament_info");
				if (root_node == NULL) {
					delete[] recvbuf; delete competitor; doc.clear(); return -1;
				}
				xml_node<> * tournament_node = root_node->first_node("tournament"); if (tournament_node == NULL) {
					delete[] recvbuf; delete competitor; doc.clear(); return -1;
				}
				if (tournament_node->first_attribute("id")) {
					if (tournament->type_radar == 0)  tournament->id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 14));else 
				   if (tournament->type_radar == 1)  tournament->id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 19));
					if (tournament->type_radar == 2)  tournament->simple_id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 21));
				}

				if (tournament->name != NULL) {
					delete[] tournament->name; tournament->name = NULL;
				}

				

				if (tournament_node->first_attribute("name")) {

					tournament->name = new char[strlen(tournament_node->first_attribute("name")->value()) + 1]; std::strcpy(tournament->name, tournament_node->first_attribute("name")->value());
				}
				if (tournament_node->first_node("sport")) tournament->sport_id = atoi((char*)((char*)tournament_node->first_node("sport")->first_attribute("id")->value() + 9));
				if (tournament_node->first_node("category")) tournament->category_id = atoi((char*)((char*)tournament_node->first_node("category")->first_attribute("id")->value() + 12));

				

				if (tournament->category_id < MAX_CATEGORIES) {
					if (tournament->category_id != 0 && categories_id[tournament->category_id] == NULL) {
						categories_id[tournament->category_id] = &categories[categories_l];
						categories_l++;
					}
				               		
						
						
					    categories_id[tournament->category_id]->id = tournament->category_id;
						categories_id[tournament->category_id]->sport_id = tournament->sport_id;
						if (categories_id[tournament->category_id]->name != NULL) { delete[] categories_id[tournament->category_id]->name; categories_id[tournament->category_id]->name = NULL; }
						if (tournament_node->first_node("category") && tournament_node->first_node("category")->first_attribute("name")) {
							categories_id[tournament->category_id]->name = new char[strlen(tournament_node->first_node("category")->first_attribute("name")->value()) + 1];
							std::strcpy(categories_id[tournament->category_id]->name, tournament_node->first_node("category")->first_attribute("name")->value());

						}
						
					

				}
				else std::printf("ERROR DATA!\r\ncategory id out of MAX_CATEGORIES in getTournament %d\r\n", tournament->category_id);
				
				

				if (tournament->season_name != NULL) {
					delete[] tournament->season_name; tournament->season_name = NULL;
				}

				

				if (tournament_node->first_node("current_season")) {
					tournament->season_name = new char[strlen(tournament_node->first_node("current_season")->first_attribute("name")->value()) + 1];
					std::strcpy(tournament->season_name, tournament_node->first_node("current_season")->first_attribute("name")->value());
					tournament->season_id = atoi((char*)((char*)tournament_node->first_node("current_season")->first_attribute("id")->value() + 10));

					if (tournament_node->first_node("current_season")->first_attribute("start_date")) {
						strcpy(buf, tournament_node->first_node("current_season")->first_attribute("start_date")->value());
						st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
						sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

						tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
						tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
						start = mktime(&tm);
						tournament->start_date = (int)start;

					}
					
					if (tournament_node->first_node("current_season")->first_attribute("end_date")) {
						strcpy(buf, tournament_node->first_node("current_season")->first_attribute("end_date")->value());
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
						strcpy(buf, tournament_node->first_node("tournament_length")->first_attribute("start_date")->value());
						st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
						sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

						tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
						tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
						start = mktime(&tm);
						tournament->start_date = (int)start;

					}

					if (tournament_node->first_node("tournament_length")->first_attribute("end_date")) {
						strcpy(buf, tournament_node->first_node("tournament_length")->first_attribute("end_date")->value());
						st.wHour = 0, st.wMinute = 0, st.wSecond = 0;
						sscanf(buf, "%d-%d-%d", &st.wYear, &st.wMonth, &st.wDay);

						tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
						tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
						start = mktime(&tm);
						tournament->end_date = (int)start;

					}

				}

				
				if (tournament->type_radar == 2) {
					 simples_id[tournament->simple_id] = tournament;
						
				} else {
					if (tournament->id < MAX_TOURNAMENTS) tournaments_id[tournament->id] = tournament;
					else {
						std::printf("ERROR DATA!\r\ntournament id out of MAX_TOURNAMANETS in getTournaments %d\r\n", tournament->id); delete[] recvbuf; delete competitor; doc.clear(); return -1;
					}

					if (tournament->season_id > 0) {
						if (tournament->season_id < MAX_TOURNAMENTS) seasons_id[tournament->season_id] = tournament; else { std::printf("ERROR DATA!\r\ntournament season_id out of MAX_TOURNAMANETS in getTournaments %d\r\n", tournament->season_id); delete[] recvbuf; delete competitor; doc.clear(); return -1; }
					}

				}

				competitor->category_id = tournament->category_id;
				competitor->sport_id = tournament->sport_id;
				saveTournamentToFile(tournament);
				saveCategoryToFile(categories_id[tournament->category_id]);
				

				if (root_node->first_node("groups"))
					for (xml_node<> * group_node = root_node->first_node("groups")->first_node("group"); group_node; group_node = group_node->next_sibling())
						for (xml_node<> * competitor_node = group_node->first_node("competitor"); competitor_node; competitor_node = competitor_node->next_sibling())
						{
							

							if (competitor->name != NULL) { delete[] competitor->name; competitor->name = NULL; }
							competitor->name = new char[strlen(competitor_node->first_attribute("name")->value()) + 1];
							std::strcpy(competitor->name, competitor_node->first_attribute("name")->value());
							

							if (competitor->country_name != NULL) { delete[] competitor->country_name; competitor->country_name = NULL; }

							

							if (competitor_node->first_attribute("country")) {
								//std::printf("vvvvvv\r\n");
								competitor->country_name = new char[strlen(competitor_node->first_attribute("country")->value())+1];
								//competitor->country_name = new char[strlen(competitor_node->first_attribute("country")->value()) + 1];
								std::strcpy(competitor->country_name, competitor_node->first_attribute("country")->value());

							}
							

							competitor->id = atoi((char*)((char*)competitor_node->first_attribute("id")->value() + 14));
							

						
							if (competitor_node->first_node("reference_ids") && competitor_node->first_node("reference_ids")->first_node("reference_id") && competitor_node->first_node("reference_ids")->first_node("reference_id")->first_attribute("value"))
							competitor->super_id = atoi(competitor_node->first_node("reference_ids")->first_node("reference_id")->first_attribute("value")->value());


							//std::printf("competitor->super_id=%d\r\n", competitor->super_id);
							

							if (competitor->id >= MAX_COMPETITORS) { std::printf("ERROR DATA!\r\ncompetitors id out of MAX_COMPETITORS in getTournament%d\r\n", competitor->id); continue; }
							else  if (competitors_id[competitor->id] == NULL) {
								competitors[competitors_l] = competitor[0];
								competitors_id[competitor->id] = &competitors[competitors_l];
								competitors_l++;
								
								
							}
							else competitors_id[competitor->id][0] = competitor[0];
							if (extended == false) saveCompetitorToFile(competitors_id[competitor->id]);
							if (extended == true) getCompetitor(competitors_id[competitor->id]);










						}

			

				delete competitor;
				delete[] recvbuf;
				doc.clear();
				return 0;
};
void postBooked(int event_id) {
	char buf[10];
	char buffer[4096];
	char* recvbuf = new char[DEFAULT_BUFLEN];
	
	_itoa(event_id, buf, 10);
	std::strcpy(buffer, "/v1/liveodds/booking-calendar/events/sr:match:");
	std::strcat(buffer, buf);
	std::strcat(buffer, "/book");
	while (httpsRequest("api.betradar.com", buffer, recvbuf, 1) == -1) Sleep(1000);
	std::printf(recvbuf);
	delete[] recvbuf;
};
char** split(char* string, char* separator) {
int i = 0;
int j = 0;
int k = 0;
int number = 0;
char** split_array = NULL;
int strlen_sep = strlen(separator);
int strlen_str= strlen(string);
if (strlen_str == 0) return NULL;
if (strlen_sep == 0 ) {
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
	index[k+1] = i;
	k++;
	i = i + (strlen_sep-1);

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
for (i = 0; i < k+1; i++) {
if (index[i + 1] == index[i]) split_array[i] = NULL;
else {
	split_array[i] = new char[index[i + 1] - index[i]+1];
	strncpy(split_array[i], (char*)((char*)string + index[i]), index[i + 1] - index[i]);
}

}

return split_array;

};
 void replace(char* &string, char* sub, char* value) {
	 int i = 0;
	 int j = 0;
	 int l = 0;
	 int k = 0;
	 int r = 0;
	 int id = 0;
	 char buf[4];
	 int sub_l;
	 char* retValue=NULL;
	 int index1[20];
	 int index2[20];
	 int index3[20];
	 char index_char1[20];
	 char index_char2[20];
	 int value_l = 0;
	 int p = 0;

	 if (string == NULL) return;
	 if(value !=NULL) value_l = strlen(value);
	 int string_l = strlen(string);
	 if (string_l == 0) return;
	  	 l = 0;
	     sub_l = strlen(sub); 
		 if (sub_l == 0 || sub_l > string_l) return;
	 
		 for (i = 1; i < string_l - sub_l+1; i++) {
			 if (string[i - 1] != '{') continue;
			 if (string[i] == '!' && string[i + 1] == '(') i=i+2;
			 else  if (string[i] == '!' || string[i] == '+' || string[i] == '-' || string[i] == '(' || string[i] == '%') i ++;

			
					 
		 for (j = 0; j < sub_l; j++) if (string[j + i] != sub[j]) break;
		 //printf((char*)((char*)string + i));

		 if (j == sub_l) {
			
			 index_char1[l] = string[i - 1];
			 index_char2[l] = string[i + j];
			 if(string[i + j] == '}') {
			 if (string[i - 1] == '!'|| string[i - 1] == '+' || string[i - 1] == '-' || string[i - 1] == '%') index1[l] = i - 2; else index1[l] = i - 1;
			 index2[l] = i + sub_l + 1; l++; i = i + sub_l + 1;
			 }
			 else if(string[i+j+2] == ')' && index_char2[l] == '+'|| index_char2[l] == '-'){
				 index3[l] =(int) string[i + j + 1]-48;
				 if (string[i - 2] == '!') index1[l] = i - 3; else index1[l] = i - 2; index2[l] = i + sub_l + 4; l++;
				 i = i + sub_l + 4;
				 
			 }
            
		 
		 
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
					 if (players_id[id] == NULL) {
						 std::printf("Player1  not found in replace. player_id=%d . getPlayer\r\n", id);
						 players[players_l].id = id; if (getPlayer(&players[players_l]) == -1)
						 {
							 std::printf("error player id=%d  not found \r\n ", id); return;

						 }
						 else  players_l++;
					 }

					 if (players_id[id] != NULL) std::strcat(retValue, players_id[id]->name);
					 else return;
					 

				 
			 
		 }


				 else if (index_char1[i] == '%' && value[0] == 's' && value[1] == 'r'&& value[3] == 'c') {

					 id = atoi((char*)((char*)value + 14));

				

					 if (id >= MAX_COMPETITORS) {
						 std::printf("\r\n ERROR in replace. competitor_id out of MAX_COMPETITORS. competitor_id=%d\r\n", id);
						 return;

					 }
					 

					 if (competitors_id[id] == NULL) {
						 std::printf("\r\nCompetitors id=%d not found in replace . Run getCompetitor\r\n", id);
						 competitors[competitors_l].id =id;
						 if (getCompetitor(&competitors[competitors_l]) == -1) {
							 std::printf(" Error getCompetitor in replace.  id competitor=%d \r\n", id);
							 return;
						 }
						 else competitors_l++;
					 }



					 if (competitors_id[id] != NULL) std::strcat(retValue, competitors_id[id]->name);
					 else return;




				 }
		 else if (index_char2[i] == '+') {
			  r = atoi(value) + index3[i];
			 _itoa(r,buf, 10);
			 std::strcat(retValue, buf);
		 }
		 else if (index_char2[i] == '-') {
			  r = atoi(value) - index3[i];
			 _itoa(r, buf, 10);
			 std::strcat(retValue, buf);
		 }

		 else { 
			 
		
			 std::strcat(retValue, value); }
	 
	 
	 }
	 


	 }
		 std::strcat(retValue, (char*)((char*)string + index2[i - 1]));

	 //printf(retValue);
	// strcpy(string, retValue);
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
	char* retValue = NULL;
	int index1[20];
	int index2[20];
	int value_l = 0;
	int p = 0;

	if (string == NULL) return;
	if (value != NULL) value_l = strlen(value);
	int string_l = strlen(string);
	if (string_l == 0) return;
	l = 0;
	sub_l = strlen(sub);
	if (sub_l == 0 || sub_l > string_l) return;

	for (i = 0; i < string_l - sub_l + 1; i++) {
		for (j = 0; j < sub_l; j++) if (string[j + i] != sub[j]) break;
		if (j == sub_l) {
                index1[l] = i ;
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
	// strcpy(string, retValue);
	//printf(string);

	delete[] string;
	string = retValue;
}
void saveEventToFile(Event* event) {
	HANDLE File;
	DWORD l = 0;
	char buf[20];
	int i = 0;
	char file_path[MAX_PATH];
    std::strcpy(file_path, "C://Betradar//Events//");
	_itoa(event->id, buf, 10);
	strcat(file_path, buf);
	File = CreateFile(file_path, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	l = SetFilePointer(File, 0, 0, FILE_BEGIN);
	WriteFile(File, &event->id, sizeof(int), &l, NULL);
	WriteFile(File, &event->type_radar, sizeof(int), &l, NULL);
	WriteFile(File, &event->sport_id, sizeof(int), &l, NULL);
	WriteFile(File, &event->category_id, sizeof(int), &l, NULL);
	if(event->type_radar==2) WriteFile(File, &event->simple_id, sizeof(int), &l, NULL);
	else WriteFile(File, &event->tournament_id, sizeof(int), &l, NULL);
	WriteFile(File, &event->home_id, sizeof(int), &l, NULL);
	WriteFile(File, &event->away_id, sizeof(int), &l, NULL);
	WriteFile(File, &event->home_super_id, sizeof(int), &l, NULL);
	WriteFile(File, &event->away_super_id, sizeof(int), &l, NULL);
	WriteFile(File, &event->winner_id, sizeof(int), &l, NULL);
	WriteFile(File, &event->bo, sizeof(int), &l, NULL);
	WriteFile(File, &event->parent_id, sizeof(int), &l, NULL);
	WriteFile(File, &event->start_time, sizeof(int), &l, NULL);
	WriteFile(File, &event->period_length, sizeof(int), &l, NULL);
	WriteFile(File, &event->overtime_length, sizeof(int), &l, NULL);
	WriteFile(File, &event->status, sizeof(int), &l, NULL);
	WriteFile(File, &event->timestamp, sizeof(int), &l, NULL);
	WriteFile(File, &event->neutral_ground, sizeof(int), &l, NULL);
	WriteFile(File, &event->austrian_district, sizeof(int), &l, NULL);
	WriteFile(File, &event->booked, sizeof(int), &l, NULL);
	WriteFile(File, &event->austrian_district, sizeof(int), &l, NULL);
	WriteFile(File, &event->delayed_id, sizeof(int), &l, NULL);
	WriteFile(File, &event->current_server, sizeof(int), &l, NULL);
	WriteFile(File, &event->next_live_time, sizeof(int), &l, NULL);
	if (event->home_name != NULL) i = strlen(event->home_name) + 1; else i = 0;
	WriteFile(File, &i, sizeof(int), &l, NULL);
	if(i>0) WriteFile(File, event->home_name, i, &l, NULL);
	if (event->away_name != NULL) i = strlen(event->away_name) + 1; else i = 0;
	WriteFile(File, &i, sizeof(int), &l, NULL);
	if (i>0) WriteFile(File, event->away_name, i, &l, NULL);
	if (event->delayed_description != NULL) i = strlen(event->delayed_description) + 1; else i = 0;
	WriteFile(File, &i, sizeof(int), &l, NULL);
	if (i>0) WriteFile(File, event->delayed_description, i, &l, NULL);
	if (event->venue != NULL) i = strlen(event->venue) + 1; else i = 0;
	WriteFile(File, &i, sizeof(int), &l, NULL);
	if (i>0) WriteFile(File, event->venue, i, &l, NULL);
	if (event->tv_channels != NULL) i = strlen(event->tv_channels) + 1; else i = 0;
	WriteFile(File, &i, sizeof(int), &l, NULL);
	if (i>0) WriteFile(File, event->tv_channels, i, &l, NULL);

	SetEndOfFile(File);
	CloseHandle(File);

};
void loadEventsFromFiles() {
	HANDLE File;
	DWORD l = 0;
	WIN32_FIND_DATA Fd;
	HANDLE Hd;
	char buf[20];
	int i = 0;
	int j = 0;
	int error_data = 0;
	char file_path[MAX_PATH];
	char folder_path[MAX_PATH];
	char find_path[MAX_PATH];
	std::strcpy(folder_path, "C://Betradar//Events//");
	std::strcpy(find_path, "C://Betradar//Events//*.*");

	Hd = FindFirstFile(find_path, &Fd);
	if (INVALID_HANDLE_VALUE == Hd) {
		FindClose(Hd);
		std::printf("Events files not found");
		return;
	};




	do {
		if (Fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) continue;
		std::strcpy(file_path, folder_path); strcat(file_path, Fd.cFileName);
		File = CreateFile(file_path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		error_data = 0;
		l = SetFilePointer(File, 0, 0, FILE_BEGIN);
		ReadFile(File, &events[i].id, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].type_radar, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].sport_id, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].category_id, sizeof(int), &l, NULL);
		if (events[i].type_radar == 2) { 
		ReadFile(File, &events[i].simple_id, sizeof(int), &l, NULL); 
		}
		else ReadFile(File, &events[i].tournament_id, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].home_id, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].away_id, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].home_super_id, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].away_super_id, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].winner_id, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].bo, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].parent_id, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].start_time, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].period_length, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].overtime_length, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].status, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].timestamp, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].neutral_ground, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].austrian_district, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].booked, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].austrian_district, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].delayed_id, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].current_server, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].next_live_time, sizeof(int), &l, NULL);

		if (events[i].home_name != NULL) { delete[] events[i].home_name; events[i].home_name = NULL; }
		ReadFile(File, &j, sizeof(int), &l, NULL);
		if (j > 0) {
			events[i].home_name = new char[j];
			ReadFile(File, events[i].home_name, j, &l, NULL);
		}


		if (events[i].away_name != NULL) { delete[] events[i].away_name; events[i].away_name = NULL; }
		ReadFile(File, &j, sizeof(int), &l, NULL);
		if (j > 0) {
			events[i].away_name = new char[j];
			ReadFile(File, events[i].away_name, j, &l, NULL);
		}


		if (events[i].delayed_description != NULL) { delete[] events[i].delayed_description; events[i].delayed_description = NULL; }
		ReadFile(File, &j, sizeof(int), &l, NULL);
		if (j > 0) {
			events[i].delayed_description = new char[j];
			ReadFile(File, events[i].delayed_description, j, &l, NULL);
		}


		if (events[i].venue != NULL) { delete[] events[i].venue; events[i].venue = NULL; }
		ReadFile(File, &j, sizeof(int), &l, NULL);
		if (j > 0) {
			events[i].venue = new char[j];
			ReadFile(File, events[i].venue, j, &l, NULL);
		}



		if (events[i].tv_channels != NULL) { delete[] events[i].tv_channels; events[i].tv_channels = NULL; }
		ReadFile(File, &j, sizeof(int), &l, NULL);
		if (j > 0) {
			events[i].tv_channels = new char[j];
			ReadFile(File, events[i].tv_channels, j, &l, NULL);
		}
		CloseHandle(File);

		if (events[i].type_radar == 2 && events[i].simple_id == 0) error_data = 1;
		
		if (events[i].start_time > time(nullptr) - 24 * 60 * 60 && error_data == 0) { events_id[events[i].id] = &events[i];  i++; }
		else DeleteFile(file_path);
		events_l = i;

	} while (FindNextFile(Hd, &Fd));

	FindClose(Hd);
	std::printf("Events loaded from data files succes. Number of loaded events is %d\r\n", events_l);


};
void saveMarketToFile(Market* market) {
	HANDLE File;
	DWORD l = 0;
	char buf[20];
	char* variable_text = new char[MAX_PATH];
	int i = 0;
	int j = 0;
	char file_path[MAX_PATH];
	std::strcpy(file_path, "C://Betradar//Markets//");
	_itoa(market->id, buf, 10);
	strcat(file_path, buf);
	if (market->variable_text != NULL) { strcat(file_path, "_"); strcpy(variable_text, market->variable_text); 
	replace_substr(variable_text, ":", "_"); strcat(file_path, variable_text);  }
	
	File = CreateFile(file_path, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == File) {
		std::printf("ERROR Save Market.");
		std::printf(file_path);std::printf("\r\n");

	}

	l = SetFilePointer(File, 0, 0, FILE_BEGIN);
	//WriteFile(File, file_path, strlen(file_path)+1, &l, NULL);
	//WriteFile(File, event->home_name, strlen(event->home_name)+1, &l, NULL);
	WriteFile(File, &market->id, sizeof(int), &l, NULL);
	WriteFile(File, &market->variant, sizeof(int), &l, NULL);
	WriteFile(File, &market->type, sizeof(int), &l, NULL);
	WriteFile(File, &market->specifier_number, sizeof(int), &l, NULL);
	WriteFile(File, &market->outcome_number, sizeof(int), &l, NULL);
    if (market->name != NULL) i = strlen(market->name) + 1; else i = 0;
	WriteFile(File, &i, sizeof(int), &l, NULL);
	if (i>0) WriteFile(File, market->name, i, &l, NULL);
	
	if (market->variable_text != NULL) i = strlen(market->variable_text) + 1; else i = 0;
	WriteFile(File, &i, sizeof(int), &l, NULL);
	if (i>0) WriteFile(File, market->variable_text, i, &l, NULL);

	
	for (j = 0; j < market->outcome_number; j++) {
		WriteFile(File, &market->outcome_id[j], sizeof(int), &l, NULL);
		if (market->outcome_name[j] != NULL) i = strlen(market->outcome_name[j]) + 1; else i = 0;
		WriteFile(File, &i, sizeof(int), &l, NULL);
		if (i>0) WriteFile(File, market->outcome_name[j], i, &l, NULL);
}

	for (j = 0; j < market->specifier_number; j++) {
		WriteFile(File, &market->specifier_type[j], sizeof(int), &l, NULL);
		if (market->specifier_name[j] != NULL) i = strlen(market->specifier_name[j]) + 1; else i = 0;
		WriteFile(File, &i, sizeof(int), &l, NULL);
		if (i>0) WriteFile(File, market->specifier_name[j], i, &l, NULL);
		if (market->specifier_description[j] != NULL) i = strlen(market->specifier_description[j]) + 1; else i = 0;
		WriteFile(File, &i, sizeof(int), &l, NULL);
		if (i>0) WriteFile(File, market->specifier_description[j], i, &l, NULL);
	};

	SetEndOfFile(File);
	CloseHandle(File);
	delete[] variable_text;

};
void loadMarketsFromFiles() {
	HANDLE File;
	DWORD l = 0;
	WIN32_FIND_DATA Fd;
	HANDLE Hd;
	char buf[20];
	int i = 0;
	int j = 0;
	int k = 0;
	char file_path[MAX_PATH];
	char folder_path[MAX_PATH];
	char find_path[MAX_PATH];
	std::strcpy(folder_path, "C://Betradar//Markets//");
	std::strcpy(find_path, "C://Betradar//Markets//*.*");
	
	Hd = FindFirstFile(find_path, &Fd);
	if (INVALID_HANDLE_VALUE == Hd) {
		FindClose(Hd);
		std::printf("Markets files not found");
		return;
	};

	
	do {
		if (Fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) continue;
		std::strcpy(file_path, folder_path); strcat(file_path, Fd.cFileName);
		File = CreateFile(file_path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		l = SetFilePointer(File, 0, 0, FILE_BEGIN);
		//ReadFile(File, file_path, strlen(file_path)+1, &l, NULL);
		//ReadFile(File, event->home_name, strlen(event->home_name)+1, &l, NULL);
		ReadFile(File, &markets[k].id, sizeof(int), &l, NULL);
		ReadFile(File, &markets[k].variant, sizeof(int), &l, NULL);
		ReadFile(File, &markets[k].type, sizeof(int), &l, NULL);
		ReadFile(File, &markets[k].specifier_number, sizeof(int), &l, NULL);
		ReadFile(File, &markets[k].outcome_number, sizeof(int), &l, NULL);

		if (markets[k].name != NULL) { delete[] markets[k].name; markets[k].name = NULL; }
		ReadFile(File, &i, sizeof(int), &l, NULL);
		if (i > 0) { markets[k].name = new char[i]; ReadFile(File, markets[k].name, i, &l, NULL); }

		if (markets[k].variable_text != NULL) { delete[] markets[k].variable_text; markets[k].variable_text = NULL; }
		ReadFile(File, &i, sizeof(int), &l, NULL);
		if (i > 0) { markets[k].variable_text = new char[i]; ReadFile(File, markets[k].variable_text, i, &l, NULL); }


		markets[k].outcome_id = new int[markets[k].outcome_number];
		markets[k].outcome_name = new char*[markets[k].outcome_number];

		for (j = 0; j < markets[k].outcome_number; j++) {
			ReadFile(File, &markets[k].outcome_id[j], sizeof(int), &l, NULL);
			//if (markets[k].outcome_name[j] != NULL) { delete[] markets[k].outcome_name[j]; markets[k].outcome_name[j] = NULL; }
			ReadFile(File, &i, sizeof(int), &l, NULL);
			if (i > 0) { markets[k].outcome_name[j] = new char[i]; ReadFile(File, markets[k].outcome_name[j], i, &l, NULL); }
			else markets[k].outcome_name[j] = NULL;

		}

		if (markets[k].specifier_number > 0) {
		markets[k].specifier_type = new int[markets[k].specifier_number];
		markets[k].specifier_name = new char*[markets[k].specifier_number];
		markets[k].specifier_description = new char*[markets[k].specifier_number];
	}

		for (j = 0; j < markets[k].specifier_number; j++) {
			ReadFile(File, &markets[k].specifier_type[j], sizeof(int), &l, NULL);
			//if (markets[k].specifier_name[j] != NULL) { delete[] markets[k].specifier_name[j]; markets[k].specifier_name[j] = NULL; }
			ReadFile(File, &i, sizeof(int), &l, NULL);
			if (i > 0) { markets[k].specifier_name[j] = new char[i]; ReadFile(File, markets[k].specifier_name[j], i, &l, NULL); 
			}
			else  markets[k].specifier_name[j] = NULL;
			//if (markets[k].specifier_description[j] != NULL) { delete[] markets[k].specifier_description[j]; markets[k].specifier_description[j] = NULL; }
			ReadFile(File, &i, sizeof(int), &l, NULL);
			if (i > 0) { markets[k].specifier_description[j] = new char[i]; ReadFile(File, markets[k].specifier_description[j], i, &l, NULL); }
			else  markets[k].specifier_description[j] = NULL;

		};
		

		
		if (markets[k].variant > -1 && markets_id[markets[k].id] == NULL) {
			markets_id[markets[k].id] = new Market*[MAX_MARKETS_IN];
			for (int l = 0; l < MAX_MARKETS_IN; l++) markets_id[markets[k].id][l] = NULL;
		}
		
		if (markets[k].variant > -1 && markets[k].variable_text == NULL) markets_id[markets[k].id][0] = &markets[k];
		
		if (markets[k].variant > -1 && markets[k].variable_text != NULL) {
			for (j = 1; j < max_markets_in[markets[k].id]; j++) {
				if (markets_id[markets[k].id][j] != NULL && std::strcmp(markets[k].variable_text, markets_id[markets[k].id][j]->variable_text) == 0) break;
				if (markets_id[markets[k].id][j] == NULL) {
					markets_id[markets[k].id][j] = &markets[k]; break;
				} }

		
		
			if (j == max_markets_in[markets[k].id]) {
				markets_id[markets[k].id][j] = &markets[k]; max_markets_in[markets[k].id]++;
			}}

		
		if (markets[k].variant == -1 && markets_id[markets[k].id] == NULL) { markets_id[markets[k].id] = new Market*[1]; markets_id[markets[k].id][0] = &markets[k]; }
		
		if (markets[k].id == 219) markets[k].line_type = 1;// (Winner(incl.overtime)
		if (markets[k].id == 16) markets[k].line_type = 3;// (Handicap)	
		if (markets[k].id == 1) markets[k].line_type = 2;// (1x2)	
		if (markets[k].id == 186) markets[k].line_type = 1; //Tennis, Athletics, Aussie Rules, Badminton, Beach Volley, Bowls, Boxing, Counter - Strike, Curling, Darts, Dota 2, ESport Call of Duty, ESport Overwatch, League of Legends, MMA, Snooker, Squash, StarCraft, Table Tennis, Volleyball
		if (markets[k].id == 610) markets[k].line_type = 2;// (1x2)	Amercian Football
		if (markets[k].id == 406) markets[k].line_type = 1;//Winner (incl. overtime and penalties)
		if (markets[k].id == 60) markets[k].line_type = 5;// 1st half - 1x2
		if (markets[k].id == 83) markets[k].line_type = 5;// 2nd half - 1x2
		if (markets[k].id == 113) markets[k].line_type = 5;// Overtime - 1x2
		if (markets[k].id == 119) markets[k].line_type = 5;//Overtime 1st half - 1x2
		if (markets[k].id == 120) markets[k].line_type = 7;//Overtime 1st half - handicap
		if (markets[k].id == 123) markets[k].line_type = 7;//Penalty shootout - winner
		if (markets[k].id == 711) markets[k].line_type = 5;//{!inningnr} innings - 1x2 cricket
		if (markets[k].id == 645) markets[k].line_type = 5;//{!inningnr} innings over {overnr} - 1x2
		if (markets[k].id == 611) markets[k].line_type = 5;//{!quarternr} quarter - 1x2 (incl. overtime) Amercan Football valid for quartner=4
		if (markets[k].id == 223) markets[k].line_type = 3;//Handicap (incl. overtime) Basketball,American Football
		if (markets[k].id == 410) markets[k].line_type = 3;//Handicap (incl. overtime and penalties) Ice Hockey
		if (markets[k].id == 66) markets[k].line_type = 7;//1st half - handicap
		if (markets[k].id == 88) markets[k].line_type = 7;//2nd half - handicap
		if (markets[k].id == 88) markets[k].line_type = 7;//2nd half - handicap
		if (markets[k].id == 460) markets[k].line_type = 7;//{!periodnr} period - handicap Ice Hockey
		if (markets[k].id == 303) markets[k].line_type = 7;//{!quarternr} quarter - handicap Basketball,American Football,Aussie Rules
		if (markets[k].id == 203) markets[k].line_type = 7;//{!setnr} set - game handicap Tennis

		if (markets[k].id == 527) markets[k].line_type = 7;//{!setnr} set - handicap  Bowls
		if (markets[k].id == 314) markets[k].line_type = 4;//Total sets - Bowls Darts
		if (markets[k].id == 315) markets[k].line_type = 5;//{!setnr} set - 1x2 Bowls
		if (markets[k].id == 188) markets[k].line_type = 3;//Set handicap Bowls
		if (markets[k].id == 493) markets[k].line_type = 3;//Frame handicap Snooker
		if (markets[k].id == 494) markets[k].line_type = 4;//Total handicap Snooker
		if (markets[k].id == 499) markets[k].line_type = 6;//{!framenr} frame - winner Snooker

		if (markets[k].id == 204) markets[k].line_type = 8;//{!setnr} set - total games  Tennis
		if (markets[k].id == 746) markets[k].line_type = 7;//{!inningnr} inning - handicap Baseball
		if (markets[k].id == 117) markets[k].line_type = 7;//Overtime - handicap Soccer,Handball
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
		if (markets[k].id == 116) markets[k].line_type = 8;//Overtime - total Soccer,Futsal,Handball,Ice Hockey
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
		if (markets[k].id == 115) markets[k].line_type = 10;//Overtime - {!goalnr} goal Soccer,Futsal,Ice Hockey
		if (markets[k].id == 202) markets[k].line_type = 6;// {!setnr} set - winner	Tennis Beach Volley,Darts,Volleyball
		if (markets[k].id == 309) markets[k].line_type = 7;//{!setnr} set - point handicap Beach Volley,Volleyball
		if (markets[k].id == 29) markets[k].line_type = 11;//Both teams to score
		if (markets[k].id == 196) markets[k].line_type = 13;//Exact sets Tennis,Beach Volley,Volleyball

		

		k++;
		markets_l = k;


		CloseHandle(File);


	} while (FindNextFile(Hd, &Fd));
	
	FindClose(Hd);

	std::printf("Markets loaded from data files succes. Number of loaded markets is %d\r\n", markets_l);
}
void saveTournamentToFile(Tournament* tournament) {
	reload_step_1 = 1;
	HANDLE File;
	DWORD l = 0;
	char buf[20];
	int i = 0;
	char file_path[MAX_PATH];
	std::strcpy(file_path, "C://Betradar//Tournaments//");
	if (tournament->type_radar == 2) { _itoa(tournament->simple_id, buf, 10); std::strcat(file_path, "Simple//");}
	if (tournament->type_radar == 1) { _itoa(tournament->id, buf, 10); std::strcat(file_path, "Race//"); }
	if (tournament->type_radar == 0) { _itoa(tournament->id, buf, 10); std::strcat(file_path, "Championships//"); }
	strcat(file_path, buf);
	File = CreateFile(file_path, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	l = SetFilePointer(File, 0, 0, FILE_BEGIN);
	WriteFile(File, &tournament->id, sizeof(int), &l, NULL);
	WriteFile(File, &tournament->type_radar, sizeof(int), &l, NULL);
	WriteFile(File, &tournament->simple_id, sizeof(int), &l, NULL);
	WriteFile(File, &tournament->season_id, sizeof(int), &l, NULL);
	WriteFile(File, &tournament->sport_id, sizeof(int), &l, NULL);
	WriteFile(File, &tournament->category_id, sizeof(int), &l, NULL);
	WriteFile(File, &tournament->sort, sizeof(int), &l, NULL);
	WriteFile(File, &tournament->start_date, sizeof(int), &l, NULL);
	WriteFile(File, &tournament->end_date, sizeof(int), &l, NULL);

	
	if (tournament->name != NULL) i = strlen(tournament->name) + 1; else i = 0;
	WriteFile(File, &i, sizeof(int), &l, NULL);
	if (i>0) WriteFile(File, tournament->name, i, &l, NULL);

	if (tournament->season_name != NULL) i = strlen(tournament->season_name) + 1; else i = 0;
	WriteFile(File, &i, sizeof(int), &l, NULL);
	if (i>0) WriteFile(File, tournament->season_name, i, &l, NULL);

	SetEndOfFile(File);
	CloseHandle(File);

};
void loadTournamentsFromFiles() {
	reload_step_1 = 1;
	HANDLE File;
	DWORD l = 0;
	WIN32_FIND_DATA Fd;
	HANDLE Hd;
	char buf[20];
	int i = 0;
	int j = 0;
	int k = 0;
	char file_path[MAX_PATH];
	char folder_path[MAX_PATH];
	char find_path[MAX_PATH];
	tournaments_l = 0;
	for (k = 0; k < 3; k++) {

		i = tournaments_l;

		if (k == 0) {
			std::strcpy(folder_path, "C://Betradar//Tournaments//Championships//");
			std::strcpy(find_path, "C://Betradar//Tournaments//Championships//*.*");
		}

		if (k == 1) {
			std::strcpy(folder_path, "C://Betradar//Tournaments//Race//");
			std::strcpy(find_path, "C://Betradar//Tournaments//Race//*.*");
		}
		if (k == 2) {
			std::strcpy(folder_path, "C://Betradar//Tournaments//Simple//");
			std::strcpy(find_path, "C://Betradar//Tournaments//Simple//*.*");
		}


		Hd = FindFirstFile(find_path, &Fd);
		if (INVALID_HANDLE_VALUE == Hd) {
			FindClose(Hd);
			std::printf("Tournaments files not found");
			return;
		};




		do {
			if (Fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) continue;
			std::strcpy(file_path, folder_path); strcat(file_path, Fd.cFileName);
			File = CreateFile(file_path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			l = SetFilePointer(File, 0, 0, FILE_BEGIN);
			ReadFile(File, &tournaments[i].id, sizeof(int), &l, NULL);
			ReadFile(File, &tournaments[i].type_radar, sizeof(int), &l, NULL);
			ReadFile(File, &tournaments[i].simple_id, sizeof(int), &l, NULL);
			ReadFile(File, &tournaments[i].season_id, sizeof(int), &l, NULL);
			ReadFile(File, &tournaments[i].sport_id, sizeof(int), &l, NULL);
			ReadFile(File, &tournaments[i].category_id, sizeof(int), &l, NULL);
			ReadFile(File, &tournaments[i].sort, sizeof(int), &l, NULL);
			ReadFile(File, &tournaments[i].start_date, sizeof(int), &l, NULL);
			ReadFile(File, &tournaments[i].end_date, sizeof(int), &l, NULL);


			if (tournaments[i].name != NULL) { delete[] tournaments[i].name; tournaments[i].name = NULL; }
			ReadFile(File, &j, sizeof(int), &l, NULL);
			if (j > 0) {
				tournaments[i].name = new char[j];
				ReadFile(File, tournaments[i].name, j, &l, NULL);
			}

			if (tournaments[i].season_name != NULL) { delete[] tournaments[i].season_name; tournaments[i].season_name = NULL; }
			ReadFile(File, &j, sizeof(int), &l, NULL);
			if (j > 0) {
				tournaments[i].season_name = new char[j];
				ReadFile(File, tournaments[i].season_name, j, &l, NULL);
			}

			CloseHandle(File);
			if (tournaments[i].id > 0) tournaments_id[tournaments[i].id] = &tournaments[i];
			if (tournaments[i].season_id > 0) seasons_id[tournaments[i].season_id] = &tournaments[i];
			if (tournaments[i].simple_id > 0) simples_id[tournaments[i].simple_id] = &tournaments[i];

			i++;
			tournaments_l = i;

		} while (FindNextFile(Hd, &Fd));
		FindClose(Hd);
	}
	  
		std::printf("Tournaments loaded from data files succes. Number of loaded tournaments is %d\r\n", tournaments_l);

	
};;
void saveCategoryToFile(Category* category) {
	reload_step_1 = 1;
	HANDLE File;
	DWORD l = 0;
	char buf[20];
	int i = 0;
	char file_path[MAX_PATH];
	std::strcpy(file_path, "C://Betradar//Categories//");
   _itoa(category->id, buf, 10); 
	strcat(file_path, buf);
	File = CreateFile(file_path, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	l = SetFilePointer(File, 0, 0, FILE_BEGIN);
	WriteFile(File, &category->id, sizeof(int), &l, NULL);
	WriteFile(File, &category->sport_id, sizeof(int), &l, NULL);
	WriteFile(File, &category->sort, sizeof(int), &l, NULL);
	if (category->name != NULL) i = strlen(category->name) + 1; else i = 0;
	WriteFile(File, &i, sizeof(int), &l, NULL);
	if (i>0) WriteFile(File, category->name, i, &l, NULL);
	
	SetEndOfFile(File);
	CloseHandle(File);

};
void loadCategoriesFromFiles() {
	reload_step_1 = 1;
	HANDLE File;
	DWORD l = 0;
	WIN32_FIND_DATA Fd;
	HANDLE Hd;
	char buf[20];
	int i = 0;
	int j = 0;
	int k = 0;
	categories_l=0;
	char file_path[MAX_PATH];
	char folder_path[MAX_PATH];
	char find_path[MAX_PATH];
		i = categories_l;
			std::strcpy(folder_path, "C://Betradar//Categories//");
			std::strcpy(find_path, "C://Betradar//Categories//*.*");
		
		Hd = FindFirstFile(find_path, &Fd);
		if (INVALID_HANDLE_VALUE == Hd) {
			FindClose(Hd);
			std::printf("Categories files not found");
			return;
		};


		do {
			if (Fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) continue;
			std::strcpy(file_path, folder_path); strcat(file_path, Fd.cFileName);
			File = CreateFile(file_path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			l = SetFilePointer(File, 0, 0, FILE_BEGIN);
			ReadFile(File, &categories[i].id, sizeof(int), &l, NULL);
			ReadFile(File, &categories[i].sport_id, sizeof(int), &l, NULL);
			ReadFile(File, &categories[i].sort, sizeof(int), &l, NULL);
			

			if (categories[i].name != NULL) { delete[] categories[i].name; categories[i].name = NULL; }
			ReadFile(File, &j, sizeof(int), &l, NULL);
			if (j > 0) {
				categories[i].name = new char[j];
				ReadFile(File, categories[i].name, j, &l, NULL);
			}

			
			CloseHandle(File);
		    categories_id[categories[i].id] = &categories[i];
			
			i++;
			categories_l = i;

		} while (FindNextFile(Hd, &Fd));
		FindClose(Hd);


		std::printf("Categories loaded from data files succes. Number of loaded categories is %d\r\n", categories_l);

	
};
void saveCompetitorToFile(Competitor* competitor) {
	HANDLE File;
	DWORD l = 0;
	char buf[20];
	int i = 0;
	char file_path[MAX_PATH];
	std::strcpy(file_path, "C://Betradar//Competitors//");
	_itoa(competitor->id, buf, 10);
	strcat(file_path, buf);
	File = CreateFile(file_path, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	l = SetFilePointer(File, 0, 0, FILE_BEGIN);
	WriteFile(File, &competitor->id, sizeof(int), &l, NULL);
	WriteFile(File, &competitor->sport_id, sizeof(int), &l, NULL);
	WriteFile(File, &competitor->category_id, sizeof(int), &l, NULL);
	WriteFile(File, &competitor->super_id, sizeof(int), &l, NULL);
	if (competitor->name != NULL) i = strlen(competitor->name) + 1; else i = 0;
	WriteFile(File, &i, sizeof(int), &l, NULL);
	if (i>0) WriteFile(File, competitor->name, i, &l, NULL);
	if (competitor->country_name != NULL) i = strlen(competitor->country_name) + 1; else i = 0;
	WriteFile(File, &i, sizeof(int), &l, NULL);
	if (i>0) WriteFile(File, competitor->country_name, i, &l, NULL);
    SetEndOfFile(File);
	CloseHandle(File);

};
void loadCompetitorsFromFiles() {
	HANDLE File;
	DWORD l = 0;
	WIN32_FIND_DATA Fd;
	HANDLE Hd;
	char buf[20];
	int i = 0;
	int j = 0;
	int k = 0;
	competitors_l = 0;
	char file_path[MAX_PATH];
	char folder_path[MAX_PATH];
	char find_path[MAX_PATH];
	i = competitors_l;
	std::strcpy(folder_path, "C://Betradar//Competitors//");
	std::strcpy(find_path, "C://Betradar//Competitors//*.*");

	Hd = FindFirstFile(find_path, &Fd);
	if (INVALID_HANDLE_VALUE == Hd) {
		FindClose(Hd);
		std::printf("Competitors files not found");
		return;
	};


	do {
		if (Fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) continue;
		std::strcpy(file_path, folder_path); strcat(file_path, Fd.cFileName);
		File = CreateFile(file_path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		l = SetFilePointer(File, 0, 0, FILE_BEGIN);
		ReadFile(File, &competitors[i].id, sizeof(int), &l, NULL);
		ReadFile(File, &competitors[i].sport_id, sizeof(int), &l, NULL);
		ReadFile(File, &competitors[i].category_id, sizeof(int), &l, NULL);
		ReadFile(File, &competitors[i].super_id, sizeof(int), &l, NULL);

		if (competitors[i].name != NULL) { delete[] competitors[i].name; competitors[i].name = NULL; }
		ReadFile(File, &j, sizeof(int), &l, NULL);
		if (j > 0) {
			competitors[i].name = new char[j];
			ReadFile(File, competitors[i].name, j, &l, NULL);
		}


		if (competitors[i].country_name != NULL) { delete[] competitors[i].country_name; competitors[i].country_name = NULL; }
		ReadFile(File, &j, sizeof(int), &l, NULL);
		if (j > 0) {
			competitors[i].country_name = new char[j];
			ReadFile(File, competitors[i].country_name, j, &l, NULL);
		}


		CloseHandle(File);
		competitors_id[competitors[i].id] = &competitors[i];

		i++;
		competitors_l = i;

	} while (FindNextFile(Hd, &Fd));
	FindClose(Hd);


	std::printf("Competitors loaded from data files succes. Number of loaded competitors is %d\r\n", competitors_l);


};
void savePlayerToFile(Player* player) {
	HANDLE File;
	DWORD l = 0;
	char buf[20];
	int i = 0;
	char file_path[MAX_PATH];
	std::strcpy(file_path, "C://Betradar//Players//");
	_itoa(player->id, buf, 10);
	strcat(file_path, buf);
	File = CreateFile(file_path, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	l = SetFilePointer(File, 0, 0, FILE_BEGIN);
	WriteFile(File, &player->id, sizeof(int), &l, NULL);
	WriteFile(File, &player->competitor_id, sizeof(int), &l, NULL);
	WriteFile(File, &player->number, sizeof(int), &l, NULL);
	WriteFile(File, &player->manager, sizeof(int), &l, NULL);
	WriteFile(File, &player->date_of_birth, sizeof(int), &l, NULL);
	WriteFile(File, &player->height, sizeof(int), &l, NULL);
	WriteFile(File, &player->weight, sizeof(int), &l, NULL);

	if (player->name != NULL) i = strlen(player->name) + 1; else i = 0;
	WriteFile(File, &i, sizeof(int), &l, NULL);
	if (i>0) WriteFile(File, player->name, i, &l, NULL);

	if (player->full_name != NULL) i = strlen(player->full_name) + 1; else i = 0;
	WriteFile(File, &i, sizeof(int), &l, NULL);
	if (i>0) WriteFile(File, player->full_name, i, &l, NULL);

	if (player->nationality != NULL) i = strlen(player->nationality) + 1; else i = 0;
	WriteFile(File, &i, sizeof(int), &l, NULL);
	if (i>0) WriteFile(File, player->nationality, i, &l, NULL);

	if (player->type != NULL) i = strlen(player->type) + 1; else i = 0;
	WriteFile(File, &i, sizeof(int), &l, NULL);
	if (i>0) WriteFile(File, player->type, i, &l, NULL);

	if (player->country_code != NULL) i = strlen(player->country_code) + 1; else i = 0;
	WriteFile(File, &i, sizeof(int), &l, NULL);
	if (i>0) WriteFile(File, player->country_code, i, &l, NULL);


	SetEndOfFile(File);
	CloseHandle(File);

};
void loadPlayersFromFiles() {
	HANDLE File;
	DWORD l = 0;
	WIN32_FIND_DATA Fd;
	HANDLE Hd;
	char buf[20];
	int i = 0;
	int j = 0;
	int k = 0;
	players_l = 0;
	char file_path[MAX_PATH];
	char folder_path[MAX_PATH];
	char find_path[MAX_PATH];
	i = players_l;
	std::strcpy(folder_path, "C://Betradar//Players//");
	std::strcpy(find_path, "C://Betradar//Players//*.*");

	Hd = FindFirstFile(find_path, &Fd);
	if (INVALID_HANDLE_VALUE == Hd) {
		FindClose(Hd);
		std::printf("Players files not found");
		return;
	};


	do {
		if (Fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) continue;
		std::strcpy(file_path, folder_path); strcat(file_path, Fd.cFileName);
		File = CreateFile(file_path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		l = SetFilePointer(File, 0, 0, FILE_BEGIN);
		ReadFile(File, &players[i].id, sizeof(int), &l, NULL);
		ReadFile(File, &players[i].competitor_id, sizeof(int), &l, NULL);
		ReadFile(File, &players[i].number, sizeof(int), &l, NULL);
		ReadFile(File, &players[i].manager, sizeof(int), &l, NULL);
		ReadFile(File, &players[i].date_of_birth, sizeof(int), &l, NULL);
		ReadFile(File, &players[i].height, sizeof(int), &l, NULL);
		ReadFile(File, &players[i].weight, sizeof(int), &l, NULL);

		if (players[i].name != NULL) { delete[] players[i].name; players[i].name = NULL; }
		ReadFile(File, &j, sizeof(int), &l, NULL);
		if (j > 0) {
			players[i].name = new char[j];
			ReadFile(File, players[i].name, j, &l, NULL);
		}


		if (players[i].full_name != NULL) { delete[] players[i].full_name; players[i].full_name = NULL; }
		ReadFile(File, &j, sizeof(int), &l, NULL);
		if (j > 0) {
			players[i].full_name = new char[j];
			ReadFile(File, players[i].full_name, j, &l, NULL);
		}

		if (players[i].nationality != NULL) { delete[] players[i].nationality; players[i].nationality = NULL; }
		ReadFile(File, &j, sizeof(int), &l, NULL);
		if (j > 0) {
			players[i].nationality = new char[j];
			ReadFile(File, players[i].nationality, j, &l, NULL);

		}

		if (players[i].type != NULL) { delete[] players[i].type; players[i].type = NULL; }
		ReadFile(File, &j, sizeof(int), &l, NULL);
		if (j > 0) {
			players[i].type = new char[j];
			ReadFile(File, players[i].type, j, &l, NULL);

		}

		if (players[i].country_code != NULL) { delete[] players[i].country_code; players[i].country_code = NULL; }
		ReadFile(File, &j, sizeof(int), &l, NULL);
		if (j > 0) {
			players[i].country_code = new char[j];
			ReadFile(File, players[i].country_code, j, &l, NULL);

		}


		CloseHandle(File);
		players_id[players[i].id] = &players[i];

		i++;
		players_l = i;

	} while (FindNextFile(Hd, &Fd));
	FindClose(Hd);


	std::printf("Players loaded from data files succes. Number of loaded players is %d\r\n", players_l);


};
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
int i,j = 0;
len = 0;
char* buffer = new char[2097152];
size_t offset = 0;
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
	writeInteger(buffer, offset, tournaments[i].season_id,4);
	writeInteger(buffer, offset, tournaments[i].simple_id, 4);
	writeInteger(buffer, offset, tournaments[i].sport_id, 2);
	writeInteger(buffer, offset, tournaments[i].category_id, 2);
	writeInteger(buffer, offset, tournaments[i].sort, 2);
	writeString(buffer, offset, tournaments[i].name);
}
writeInteger(buffer, offset, markets_l, 2);
for (i = 0; i < markets_l; i++) {
	writeInteger(buffer, offset, markets[i].id, 2);
	writeInteger(buffer, offset, markets[i].type, 1);
	writeInteger(buffer, offset, markets[i].line_type, 1);
	writeString(buffer, offset, markets[i].name);
	writeInteger(buffer, offset, markets[i].variant, 1);
	if(markets[i].variant>-1) writeString(buffer, offset, markets[i].variable_text);
	//if(markets[i].variant>-1 && markets[i].variable_text!=nullptr)
	//writeString(buffer, offset, markets[i].variable_text);
	writeInteger(buffer, offset, markets[i].outcome_number, 2);
	for (j = 0; j < markets[i].outcome_number; j++) {
		writeInteger(buffer, offset, markets[i].outcome_id[j], 2);
		writeString(buffer, offset, markets[i].outcome_name[j]);
	}

	writeInteger(buffer, offset, markets[i].specifier_number, 1);
	for (j = 0; j < markets[i].specifier_number; j++) 	writeString(buffer, offset, markets[i].specifier_name[j]);
		
}
char* zip_message = nullptr;
int zip_len = gzip(buffer, offset, zip_message,1);
delete[] buffer;
if(zip_len < 1) return nullptr;
char* encode_message = SendframeEncode(zip_message, zip_len, len);
delete[] zip_message;
return encode_message;

};
char* CreateStep_2(int& len) {
	int i, j, l, k = 0;
	int events_send_l = 0;
	int event_lines_l = 0;

	char* buffer = new char[SEND_BUFLEN];
	len = 0;
	size_t offset = 0;
	size_t retry_offset = 0;
	
	offset += 2;
	
	//printf("events_show_l=%d\r\n", events_show_l);

	for (i = 0; i < events_show_l; i++) {
		if (events_show[i]->status == 4 || events_show[i]->status == 3) continue;
		events_send_l++;
		writeInteger(buffer, offset, 0, 1);
		writeInteger(buffer, offset, events_show[i]->id, 4);
		writeInteger(buffer, offset, events_show[i]->home_id, 4);
		writeInteger(buffer, offset, events_show[i]->away_id, 4);
		writeInteger(buffer, offset, events_show[i]->type_radar, 1);
		writeInteger(buffer, offset, events_show[i]->status, 1);
		writeInteger(buffer, offset, events_show[i]->sport_id, 2);
		writeInteger(buffer, offset, events_show[i]->category_id, 2);
		if (events_show[i]->type_radar<2) writeInteger(buffer, offset, events_show[i]->tournament_id, 4);
		else writeInteger(buffer, offset, events_show[i]->simple_id, 4);
		writeInteger(buffer, offset, events_show[i]->start_time + 4 * 3600, 4);
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



		if (event2lines.find(events_show[i]->id) == event2lines.end()) { writeInteger(buffer, offset, 0, 2); writeInteger(buffer, offset, 0, 2); continue; }

		writeInteger(buffer, offset, event2lines[events_show[i]->id]->size(), 2);

		event_lines_l = 0;
		retry_offset = offset;
		offset += 2;



		for (unordered_set<int>::iterator it = event2lines[events_show[i]->id]->begin(); it != event2lines[events_show[i]->id]->end(); ++it)
		{
			if (markets_id[lines[*(it)].market_id][0]->line_type == 0 && events_show[i]->status == 0) continue;
			if (lines[*(it)].status == 0 || lines[*(it)].status == -3) continue;
			event_lines_l++;
			writeInteger(buffer, offset, lines[*(it)].id, 4);
			//writeInteger(buffer, offset, lines[*(it)].betstop_reason, 1);
			writeInteger(buffer, offset, lines[*(it)].market_id, 2);
			writeInteger(buffer, offset, lines[*(it)].type, 1);
			writeInteger(buffer, offset, lines[*(it)].favourite, 1);
			writeInteger(buffer, offset, lines[*(it)].status, 1);
			//if (lines[*(it)].outcome_number == 0) printf("lines[*(it)].outcome_number=0 lines[*(it)].id=%d  lines[*(it)].market_id=%d\r\n", lines[*(it)].id, lines[*(it)].market_id);
			writeInteger(buffer, offset, lines[*(it)].outcome_number, 2);
			for (j = 0; j < lines[*(it)].outcome_number; j++) {
				writeInteger(buffer, offset, lines[*(it)].outcome_id[j], 2);
				writeInteger(buffer, offset, lines[*(it)].outcome_active[j], 1);
				if (lines[*(it)].type == 1 || lines[*(it)].type == 2) writeInteger(buffer, offset, lines[*(it)].outcome_team[j], 1);
				if((lines[*(it)].type==1|| lines[*(it)].type == 2) && lines[*(it)].outcome_team[j]!=3)
					writeString(buffer, offset, lines[*(it)].outcome_name[j]);
				writeInteger(buffer, offset, (int)(lines[*(it)].outcome_odds[j] * 100), 4);

			}

			writeInteger(buffer, offset, lines[*(it)].specifier_number, 1);
			for (j = 0; j < lines[*(it)].specifier_number; j++)
				writeString(buffer, offset, lines[*(it)].specifier_value[j]);




		}

		writeInteger(buffer, retry_offset, event_lines_l, 2);

		k = k + event_lines_l;

	}
retry_offset = 0;


writeInteger(buffer, retry_offset, events_send_l, 2);

	char* zip_message = nullptr;
	int zip_len = gzip(buffer, offset, zip_message, 2);
	delete[] buffer;
	if (zip_len < 1) return nullptr;
	char* encode_message = SendframeEncode(zip_message, zip_len, len);
	delete[] zip_message;
	return encode_message;

};
void CreatePlus_2(wsClient* client) {
	//printf("CreatePlus_2\r\n");
	//server.wsClients[clientIDs[i]]
	int i, j, l, k = 0;
	int events_send_l = 0;
	int event_lines_l = 0;

	char* buffer = new char[SEND_BUFLEN];
	int len = 0;
	size_t offset = 0;
	size_t retry_offset = 0;
	int event_id = client->plus;
	
	//printf("CreatePlus_2 server.wsClients[%d]->plus=%d\r\n", clientID, server.wsClients[clientID]->plus);

	if (event_id >= MAX_EVENTS) { std::printf("ERROR DATA!\r\nsevent id out of MAX_EVENTS in CreatePlus_2 %d\r\n", event_id); delete[] buffer; client->plus_create = false; client->plus_send = false; return; }
	if(events_id[event_id]==nullptr) { std::printf("\r\nEvent id= %d not found in CreatePlus_2 \r\n", event_id); delete[] buffer; client->plus_create = false; client->plus_send = false; return; }
	if (events_id[event_id]->show == 0) { std::printf("\r\nsEvent id= %d not show type in CreatePlus_2 %d\r\n", event_id); delete[] buffer; client->plus_create = false; client->plus_send = false; return; }
	if (event2lines.find(event_id) == event2lines.end()) { std::printf("\r\nsEvent id= %d not lines for show  in CreatePlus_2 %d\r\n", event_id); delete[] buffer; client->plus_create = false; client->plus_send = false; return; }
	events_send_l = 1;
	writeInteger(buffer, offset, events_send_l, 2);
	writeInteger(buffer, offset, 4, 1); //4 response for rospis command
	writeInteger(buffer, offset, event_id, 4);
	//writeInteger(buffer, offset, event2lines[event_id]->size(), 2);
	event_lines_l = 0;
	retry_offset = offset;
	offset += 2;

	for (unordered_set<int>::iterator it = event2lines[event_id]->begin(); it != event2lines[event_id]->end(); ++it)
		{
			//if (markets_id[lines[*(it)].market_id][0]->line_type == 0 && events_show[i]->status == 0) continue;
			if (lines[*(it)].status == 0 || lines[*(it)].status == -3) continue;
			event_lines_l++;
			writeInteger(buffer, offset, lines[*(it)].id, 4);
			//writeInteger(buffer, offset, lines[*(it)].betstop_reason, 1);
			writeInteger(buffer, offset, lines[*(it)].market_id, 2);
			writeInteger(buffer, offset, lines[*(it)].type, 1);
			writeInteger(buffer, offset, lines[*(it)].favourite, 1);
			writeInteger(buffer, offset, lines[*(it)].status, 1);
			//if (lines[*(it)].outcome_number == 0) printf("lines[*(it)].outcome_number=0 lines[*(it)].id=%d  lines[*(it)].market_id=%d\r\n", lines[*(it)].id, lines[*(it)].market_id);
			writeInteger(buffer, offset, lines[*(it)].outcome_number, 2);
			for (j = 0; j < lines[*(it)].outcome_number; j++) {
				writeInteger(buffer, offset, lines[*(it)].outcome_id[j], 2);
				writeInteger(buffer, offset, lines[*(it)].outcome_active[j], 1);
				if (lines[*(it)].type == 1 || lines[*(it)].type == 2) writeInteger(buffer, offset, lines[*(it)].outcome_team[j], 1);
				if ((lines[*(it)].type == 1 || lines[*(it)].type == 2) && lines[*(it)].outcome_team[j] != 3)
					writeString(buffer, offset, lines[*(it)].outcome_name[j]);
				writeInteger(buffer, offset, (int)(lines[*(it)].outcome_odds[j] * 100), 4);

			}

			writeInteger(buffer, offset, lines[*(it)].specifier_number, 1);
			for (j = 0; j < lines[*(it)].specifier_number; j++)
				writeString(buffer, offset, lines[*(it)].specifier_value[j]);




		}

		writeInteger(buffer, retry_offset, event_lines_l, 2);

		if (event_lines_l == 0) { delete[] buffer; client->plus_create = false; client->plus_send = false; return; }

	
	char* zip_message = nullptr;
	int zip_len = gzip(buffer, offset, zip_message, 2);
	delete[] buffer;
	if (zip_len < 1) return;
	char* encode_message = SendframeEncode(zip_message, zip_len, len);
	delete[] zip_message;
	client->plus_message = encode_message;
	client->plus_message_length = len;

	//printf("CreatePlus_2 client->plus_message_length=%d\r\n",client->plus_message_length);

	//printf("server.wsClients[clientID]->plus_message_length=%d\r\n", server.wsClients[clientID]->plus_message_length);
	
	client->plus_send = true;
	client->plus_create = false;
	

};
void CreateOutright_2(wsClient* client) {
	//printf("CreateOutright_2\r\n");
	//server.wsClients[clientIDs[i]]
	int i, j, l, k = 0;
	int events_send_l = 0;
	int event_lines_l = 0;
	int type_radar = 0;//2 simple //3 season
	Line* _line;
	char* buffer = new char[SEND_BUFLEN];
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
	offset += 2;
	

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
		
		if (_line->simple_id > 0) type_radar = 2; else type_radar = 3;
		writeInteger(buffer, offset, type_radar, 1);
		if (type_radar == 2) { writeInteger(buffer, offset, _line->simple_id, 4); 
		writeInteger(buffer, offset, simples_id[_line->simple_id]->end_date+ 4 * 3600, 4);
		}
		else { writeInteger(buffer, offset, _line->tournament_id, 4); 
		writeInteger(buffer, offset, tournaments_id[_line->tournament_id]->end_date + 4 * 3600, 4);
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
		writeInteger(buffer, offset, _line->status, 1);
		//if (_line->outcome_number == 0) printf("_line->outcome_number=0 _line->id=%d  _line->market_id=%d\r\n", _line->id, _line->market_id);
		writeInteger(buffer, offset, _line->outcome_number, 2);
		for (int j = 0; j < _line->outcome_number; j++) {
			writeInteger(buffer, offset, _line->outcome_id[j], 2);
			writeInteger(buffer, offset, _line->outcome_active[j], 1);
			if (_line->type == 1 || _line->type == 2) writeInteger(buffer, offset, _line->outcome_team[j], 1);
			if ((_line->type == 1 || _line->type == 2) && _line->outcome_team[j] != 3)
				writeString(buffer, offset, _line->outcome_name[j]);
			writeInteger(buffer, offset, (int)(_line->outcome_odds[j] * 100), 4);
		}

		writeInteger(buffer, offset, _line->specifier_number, 1);
		for (int j = 0; j < _line->specifier_number; j++) writeString(buffer, offset, _line->specifier_value[j]);
	}

	writeInteger(buffer, retry_offset, events_send_l, 2);




if (events_send_l == 0) { delete[] buffer; client->outright_create = false; client->outright_send = false; return; }
	char* zip_message = nullptr;
	int zip_len = gzip(buffer, offset, zip_message, 2);
	delete[] buffer;
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
	int bufferSize = DEFAULT_BUFLEN;

	// work out amount of frames to send, based on $bufferSize
	int frameCount = ceil((float)messageLen / bufferSize);
	if (frameCount == 0)
		frameCount = 1;

	// set last frame variables
	int maxFrame = frameCount - 1;
	int lastframe_bufferLength = (messageLen % bufferSize) != 0 ? (messageLen % bufferSize) : (messageLen != 0 ? bufferSize : 0);

	// loop around all frames to send



	for (int i = 0; i < frameCount; i++) {
		// fetch fin, opcode and buffer length for frame
		unsigned char fin = i != maxFrame ? 0 : WS_FIN;
		opcode = i != 0 ? WS_OPCODE_CONTINUATION : opcode;

		size_t bufferLength = i != maxFrame ? bufferSize : lastframe_bufferLength;



		// set payload length variables for frame
		if (bufferLength <= 125) {
			// int payloadLength = bufferLength;
			totalLength = bufferLength + 2;
			buf = new char[totalLength];
			buf[0] = fin | opcode;
			buf[1] = bufferLength;
			memcpy(buf + 2, message, messageLen);
		}
		else if (bufferLength <= 65535) {
			// int payloadLength = WS_PAYLOAD_LENGTH_16;
			totalLength = bufferLength + 4;
			buf = new char[totalLength];
			buf[0] = fin | opcode;
			buf[1] = WS_PAYLOAD_LENGTH_16;
			buf[2] = bufferLength >> 8;
			buf[3] = bufferLength;
			memcpy(buf + 4, message, messageLen);
		}
		else {
			// int payloadLength = WS_PAYLOAD_LENGTH_63;
			totalLength = bufferLength + 10;
			buf = new char[totalLength];
			buf[0] = fin | opcode;
			buf[1] = WS_PAYLOAD_LENGTH_63;
			buf[2] = 0;
			buf[3] = 0;
			buf[4] = 0;
			buf[5] = 0;
			buf[6] = bufferLength >> 24;
			buf[7] = bufferLength >> 16;
			buf[8] = bufferLength >> 8;
			buf[9] = bufferLength;
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
void openHandler(int clientID) {
	ostringstream os;
	os << "Stranger " << clientID << " has joined.";
    char* zip_message = nullptr;
	int zip_len=gzip((char*)os.str().c_str(), os.str().size(), zip_message);
	if (zip_len < 1) return;

	vector<int> clientIDs = server.getClientIDs();
	for (int i = 0; i < clientIDs.size(); i++) {
		if (clientIDs[i] != clientID)
			server.wsSend(clientIDs[i], zip_message, zip_len);
	}
	delete[] zip_message;
	zip_message = nullptr;
	zip_len=gzip("Welcome!", 7, zip_message);
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
	
	static time_t next = time(NULL) + 10;
	time_t current = time(NULL);
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
		next = time(NULL) + 10;
		delete[] zip_message;
	}
}
void radarMessageHandler(char* message, int messageLen) {
vector<int> clientIDs = server.getClientIDs();
for (int i = 0; i < clientIDs.size(); i++) 	server.wsSend(clientIDs[i], message, messageLen);
}

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
	iResult =::bind(ListenSocket, (SOCKADDR *)& service, sizeof(service));
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
			if (dwError == WSAHOST_NOT_FOUND) {std::printf("Host not found\n");  WSACleanup(); return -1; }
			else if (dwError == WSANO_DATA) {std::printf("No data record found\n");  WSACleanup(); return -1; }
			else {
				printf("Function failed with error: %ld\n", dwError);
				return -1;
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
	if (sdkSocket == INVALID_SOCKET) { wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());   WSACleanup(); return -1; }
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
		iResult = SSL_get_error(ssl, iResult); wprintf(L"SSL error: %d\n", iResult); return -1;
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
	if (mode == 0) strcpy(sendBuf, "GET ");
	else strcpy(sendBuf, "POST ");
	strcat(sendBuf, path);
	strcat(sendBuf, " HTTP/1.0\nHost: ");
	strcat(sendBuf, domain);
	strcat(sendBuf, "\r\nx-access-token: YaNJ9uwq8GHe953XQD\r\nUser-Agent: Webclient\r\nAccept:*/*\r\n\r\n");
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
	DWORD l = 0;
	amqp_frame_t frame;	uint64_t now;
		
	

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
		ret = amqp_consume_message(conn, &envelope, NULL, 0);
		
		memcpy(AMQP_message[rabbit_index%AMQP_QUEUE], envelope.message.body.bytes, envelope.message.body.len);
		if (envelope.message.body.len >= AMQP_BUFLEN) printf("ERROR rabbit!envelope.message.body.len=%d\r\n", envelope.message.body.len);
		AMQP_message[rabbit_index%AMQP_QUEUE][envelope.message.body.len] = 0;
		rabbit_index++;
		//printf("2rabbit_index=%d\r\n", rabbit_index);
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
	char const *hostname;
	int port, status;
	char const *exchange;
	char *bindingkey;
	amqp_socket_t *socket;
	amqp_connection_state_t conn;
	amqp_bytes_t queuename;


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
			NULL,
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
static void run_mts(amqp_connection_state_t conn)
{
	uint64_t start_time = now_microseconds();
	int received = 0;
	int previous_received = 0;
	uint64_t previous_report_time = start_time;
	uint64_t next_summary_time = start_time + SUMMARY_EVERY_US;
	DWORD l = 0;
	amqp_frame_t frame;	uint64_t now;



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
		ret = amqp_consume_message(conn, &envelope, NULL, 0);
		printf("run_mts");
		printf((char*)envelope.message.body.bytes);

		//memcpy(AMQP_message[rabbit_index%AMQP_QUEUE], envelope.message.body.bytes, envelope.message.body.len);
		//if (envelope.message.body.len >= AMQP_BUFLEN) printf("ERROR rabbit!envelope.message.body.len=%d\r\n", envelope.message.body.len);
		//AMQP_message[rabbit_index%AMQP_QUEUE][envelope.message.body.len] = 0;
		//rabbit_index++;
		//printf("2rabbit_index=%d\r\n", rabbit_index);
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
void rabbitmqssl_mts() {
	char const *hostname;
	int port, status;
	char const *queuename = "passionbettest_19751-Confirm-Node1";
	char const *bindingkey= "Node1.ticket.confirm";
	char const *exchangetype[] = { "fanout","topic","topic" ,"topic" ,"topic" };
	amqp_socket_t *socket;
	amqp_connection_state_t conn;
	char*  routingkey []= { "Node1.ticket.confirm", "passionbettest_19751-Control", "passionbettest_19751-Confirm", "passionbettest_19751-Reply", "passionbettest_19751-Ack"
	}; ;
	amqp_bytes_t amqp_queuename;
	char* username = "passionbettest_19751";
	char const *exchange[] = { "passionbettest_19751-Submit", "passionbettest_19751-Control", "passionbettest_19751-Confirm", "passionbettest_19751-Reply", "passionbettest_19751-Ack"
	};


	hostname = "integration-mts.betradar.com";// argv[1];
	port = 5671;//atoi(argv[2]);
	
	conn = amqp_new_connection();
	socket = amqp_ssl_socket_new(conn);
	if (!socket) {
		die("creating SSL/TLS socket");
	}
	amqp_ssl_socket_set_verify_peer(socket, 0);
	amqp_ssl_socket_set_verify_hostname(socket, 0);
	

	status = amqp_socket_open(socket, hostname, port);



	if (status) {
		die("opening SSL/TLS connection");
		
	}



	die_on_amqp_error(amqp_login(conn, "/passionbettest_19751", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "passionbettest_19751","7IdKP1jwq1"),
		"Logging in");





	amqp_channel_open(conn, 1);
	



	die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel");

	/*for (int i = 0; i < 5; i++) {
		amqp_exchange_declare(conn, 1, amqp_cstring_bytes(exchange[i]), amqp_cstring_bytes(exchangetype[i]),
			0, 1, 0, 0, amqp_empty_table);
		die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring exchange");
	}
	*/

	amqp_queue_declare_ok_t *r = amqp_queue_declare(conn, 1, amqp_cstring_bytes("passionbettest_19751-Confirm-Node1"), 0, 1, 0, 0,
		amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring queue");
	amqp_queuename = amqp_bytes_malloc_dup(r->queue);
	//printf((char*)queuename.bytes);



	if (amqp_queuename.bytes == NULL) {
		fprintf(stderr, "Out of memory while copying queue name");
		return;
	}


	amqp_queue_bind(conn, 1,
		amqp_cstring_bytes(queuename),
		amqp_cstring_bytes(exchange[2]),
		amqp_cstring_bytes(bindingkey),
		amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Binding queue");
	


	/*
	
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel");

	{ 
		amqp_queue_declare_ok_t *r = amqp_queue_declare(conn, 1, amqp_empty_bytes, 0, 0, 0, 1,
			amqp_empty_table);
		die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring queue");
		queuename = amqp_bytes_malloc_dup(r->queue);

		

		if (queuename.bytes == NULL) {
			fprintf(stderr, "Out of memory while copying queue name");
			return;
		}
	}
	*/
	
/*	amqp_queue_bind(conn, 1, queuename, amqp_cstring_bytes(exchange[0]), amqp_cstring_bytes(bindingkey),
		amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Binding queue");
	*/
	
	amqp_basic_consume(conn, 1, amqp_cstring_bytes(queuename), amqp_empty_bytes, 0, 1, 0, amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Consuming");

	


	{
		amqp_basic_properties_t props;
		props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG | AMQP_BASIC_HEADERS_FLAG;;
		props.content_type = amqp_cstring_bytes("application/json");
		//props.headers = "replyRoutingKey:\"Node1.ticket.confirm\"";
		//amqp_table_t *table = &props.headers;
		//props.headers.num_entries = 1;
		//props.headers.entries = calloc(props.headers.num_entries, sizeof(amqp_table_entry_t));
		amqp_table_entry_t entries[1];
		amqp_table_t table;


		entries[0].key = amqp_cstring_bytes("replyRoutingKey");
		entries[0].value.kind = AMQP_FIELD_KIND_UTF8;
		entries[0].value.value.bytes = amqp_cstring_bytes("Node1.ticket.confirm");
		
		table.num_entries = 1;
		table.entries = entries;

		qsort(table.entries, table.num_entries, sizeof(amqp_table_entry_t),
			&amqp_table_entry_cmp);
		props.headers = table;


		//amqp_cstring_bytes("replyRoutingKey:\"Node1.ticket.confirm\"");
		props.delivery_mode = 2; /* persistent delivery mode */
		die_on_error(amqp_basic_publish(conn,
			1,
			amqp_cstring_bytes(exchange[0]),
			amqp_cstring_bytes("Node1.ticket.confirm"),
			0,
			0,
			&props,
			amqp_cstring_bytes("{ \"version\": \"2.0\", \"timestampUtc\": 1486541079460, \"ticketId\": \"MTS_Test_20171109_080435391\", \"sender\": { \"currency\": \"EUR\", \"terminalId\": \"Tallinn-1\", \"channel\": \"internet\", \"shopId\": null, \"bookmakerId\": \"19751\", \"endCustomer\": { \"ip\": \"127.0.0.1\", \"languageId\": \"EN\", \"deviceId\": \"1234test\", \"id\": \"1234test\", \"confidence\": 10000 }, \"limitId\": 903 }, \"selections\": [{ \"eventId\": 11050343, \"id\": \"lcoo:42/1/*/X\", \"odds\": 28700 }], \"bets\": [{ \"id\": \"MTS_Test_20171109_080435391_bet_0\", \"selectionRefs\": [{ \"selectionIndex\": 0, \"banker\": false }], \"selectedSystems\": [1], \"stake\": { \"value\": 10000, \"type\": \"total\" } }] }")),
			"Publishing");
	}

	run_mts(conn);

	die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
	die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
	die_on_error(amqp_destroy_connection(conn), "Ending connection");

	return;
}














