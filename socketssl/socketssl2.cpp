// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//
//openssl req - x509 - newkey rsa : 4096 - sha256 - nodes - keyout example.key - out example.crt - subj "/CN=localhost" - days 365

/*
#ifndef UNICODE
#define UNICODE
#endif
*/
#undef _UNICODE
#undef UNICODE


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
#include <conio.h>
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
#include <ctime>

#ifndef librabbitmq_examples_utils_h
#define librabbitmq_examples_utils_h
#endif

//#define CERTF  "/cert.pem"
//#define KEYF  "/key.pem"
#define CERTF  "/passionbet.crt"
#define KEYF  "/passionbet.key"
#define MAX_PATH 255
#define DEFAULT_BUFLEN 67108864
#define NAME_LENTGH 127
#define SPORT_LENTGH 200
#define TOURNAMENT_LENTGH 10000
#define EVENT_LENTGH 10000
#define CATEGORY_LENTGH 10000
#define SUMMARY_EVERY_US 1000000
#define MARKET_LENGTH 3000
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
	~Tournament() { delete[] name; delete[] seasonName;};
	int id;
	int race = 0;
	int idSport;
	int idCategory;
	int sort;
	char *name;
	char *seasonName;
	void operator = (const Tournament&);
};
void Tournament:: operator = (const Tournament & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	idCategory = rhs.idCategory;
	idSport = rhs.idSport;
	sort = rhs.sort;
	race = rhs.race;
	strcpy(name, rhs.name);
	strcpy(seasonName, rhs.seasonName);
}
Tournament::Tournament() {
	id = 0;
	race = 0;
	idCategory = 0;
	idSport = 0;
	sort = 0;
	name = new char[NAME_LENTGH];
	seasonName = new char[NAME_LENTGH];
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
class Event {
public:
	Event();
	~Event() {
		delete[] home_name; if (tv_channels != NULL) delete[] tv_channels; if (venue != NULL) delete[] venue; delete[] away_name; delete[] set_scores; delete[] match_status; delete[] match_time; delete[] remaining_time; delete[] remaining_time; delete[] remaining_time_in_period; delete[] game_score;  delete[] leg_score;
	};
	int id;
	int sport_id;
	int category_id;
	int tournament_id;
	int home_id;
	int away_id;
	int home_superid = 0;
	int away_superid = 0;
	int status; //0(not started) / 1(live) / 2(suspended) /	3(ended) / 4(closed) / abandoned - only one of these 6 is possible
	int reporting;//
	int home_score;
	int away_score;
	char* set_scores;
	char* match_status;
	char* match_time;
	char* remaining_time;
	char* venue;
	char* remaining_time_in_period;
	int clock_stopped;
	int home_yellowcards;
	int away_yellowcards;
	int home_redcards;
	int away_redcards;
	int server;
	char* game_score;
	int tiebreak;
	int expedite;
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
	char* leg_score;
	int throw_num;
	int delivery;
	int home_remainingbowls;
	int away_remainingbowls;
	int current_end;
	int home_dismissal;
	int away_dismissals;
	int home_penaltyruns;
	int away_penaltyruns;
	int innings;
	int over;
	char *home_name;
	char *away_name;
	int timestamp;
	int neutral_ground;
	int period_length;
	int overtime_length;
	int austrian_district;
	int booked;
	int race;
	int parent_id;
	void operator = (const Event&);

};
void Event:: operator = (const Event & rhs) {
	if (this == &rhs) return;
	id=rhs.id;
	home_id = rhs.home_id;
	away_id = rhs.away_id;
	home_superid = rhs.home_superid;
	away_superid = rhs.away_superid;
	status=rhs.status; //0(not started) / 1(live) / 2(suspended) /	3(ended) / 4(closed) / abandoned - only one of these 6 is possible
	reporting=rhs.reporting;//
	home_score=rhs.home_score;
	away_score=rhs.away_score;
	if (tv_channels != NULL) delete[] tv_channels;
	if (rhs.tv_channels != NULL) {
		tv_channels = new char[strlen(rhs.tv_channels)+1];
		strcpy(tv_channels, rhs.tv_channels);
	}

	if (venue != NULL) delete[] venue;
	if (rhs.venue != NULL) {
		venue = new char[strlen(rhs.venue)+1];
		strcpy(venue, rhs.venue);
	}

	strcpy(set_scores,rhs.set_scores);
	strcpy(match_status,rhs.match_status);
	strcpy(match_time, rhs.match_time);
	strcpy(remaining_time,rhs.remaining_time);
	strcpy(remaining_time_in_period,rhs.remaining_time_in_period);
	clock_stopped=rhs.clock_stopped;
	home_yellowcards=rhs.home_yellowcards;
	away_yellowcards= rhs.away_yellowcards;
	home_redcards = rhs.home_redcards;
	away_redcards=rhs.away_redcards;
	server=rhs.server;
	strcpy(game_score,rhs.game_score);
	tiebreak=rhs.tiebreak;
	expedite=rhs.expedite;
	home_suspend=rhs.home_suspend;
	away_suspend=rhs.away_suspend;
	strikes=rhs.strikes;
	balls=rhs.balls;
    outs=rhs.outs;
	home_batter=rhs.home_batter;
	away_batter = rhs.away_batter;
	possession=rhs.possession;
	try_num=rhs.try_num;
	yards=rhs.yards;
	visit=rhs.visit;
	strcpy(leg_score,rhs.leg_score);
	throw_num=rhs.throw_num;
	delivery=rhs.delivery;
	home_remainingbowls=rhs.home_remainingbowls;
	away_remainingbowls=rhs.away_remainingbowls;
	current_end=rhs.current_end;
	home_dismissal=rhs.home_dismissal;
	away_dismissals=rhs.away_dismissals;
	home_penaltyruns=rhs.home_penaltyruns;
	away_penaltyruns=rhs.away_penaltyruns;
	innings=rhs.innings;
	over=rhs.over;
	booked = rhs.booked;
	timestamp = rhs.timestamp;
	strcpy(away_name,rhs.away_name);
	strcpy(home_name, rhs.home_name);
	race = rhs.race;
	parent_id =rhs.parent_id;
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
	sport_id = 0;
	category_id = 0;
	tournament_id = 0;
	away_name = new char[NAME_LENTGH];
	home_name = new char[NAME_LENTGH];
	int status=-1; //0(not started) / 1(live) / 2(suspended) /	3(ended) / 4(closed) / abandoned - only one of these 6 is possible
	reporting=0;//
	home_score=0;
	away_score=0;
	away_superid = 0;
	home_superid = 0;
	away_id = 0;
	home_id = 0;
	set_scores=new char[MAX_PATH];
	match_status=new char[64];
	match_time = new char[16];
	remaining_time = new char[16];
	remaining_time_in_period = new char[16];
	clock_stopped = 0;;
	home_yellowcards = 0;;
	away_yellowcards=0;
	home_redcards=0;
	away_redcards=0;
	server=0;
	game_score=new char[16];
    tiebreak=0;
	expedite=0;
	home_suspend=0;
	away_suspend=0;
	strikes=0;
	balls=0;
	outs=0;
	home_batter=0;
	away_batter=0;
	possession=0;
	try_num=0;
	yards=0;
	visit=0;
	leg_score=new char[16];
	throw_num=0;
    delivery=0;
	home_remainingbowls=0;
	away_remainingbowls=0;
	current_end=0;
	home_dismissal=0;
	away_dismissals=0;
	home_penaltyruns=0;
	away_penaltyruns=0;
	innings=0;
	over=0;
	timestamp = 0;
	neutral_ground=0;
	period_length=0;
	overtime_length=0;
	austrian_district=0;
	booked = 0;
	race = 0;
	parent_id = 0;
	tv_channels = NULL;
	venue = NULL;
	
};
class Market {
public:
	Market();
	~Market() {
		delete[] name; for (int j = 0; j < outcomeArrayNumber; j++) {
			if (outcomeNumber[j] > 0) { for (int i = 0; i < outcomeNumber[j]; i++) if (outcomeName[j][i] != NULL) delete[] outcomeName[j][i]; }; if (outcomeName[j] != NULL) delete[] outcomeName[j]; if (outcomeId[j] != NULL) delete[] outcomeId[j]; if (outcomeVariantText[j] != NULL) delete[] outcomeVariantText[j];}
		if (outcomeId != NULL) delete[] outcomeId;
		if (outcomeNumber != NULL) delete[] outcomeNumber;
		if (outcomeVariantText != NULL) delete[] outcomeVariantText;
		if (outcomeName != NULL) delete[] outcomeName;
		if (outcomeNumber != NULL) delete[] outcomeNumber;
		
		if (specifierNumber > 0) { for (int i = 0; i < specifierNumber; i++) if (specifierName[i] != NULL) delete[] specifierName[i]; for (int i = 0; i < specifierNumber; i++) if (specifierDescription[i] != NULL) delete[] specifierDescription[i]; if (specifierType != NULL) delete[] specifierType; delete[] specifierName; }
	};

	int id;
	int map;
	int type;//0 -normal//1-sr:player//2-sr:competitor//3 pre:outcometext
	char* name;
	int outcomeArrayNumber;
	int* outcomeNumber;
	char** outcomeVariantText;
	char*** outcomeName;
	int** outcomeId;
	char** specifierName;
	char** specifierDescription;
	int* specifierType;//0 null //1 int //2 string 3://decimal 4//variable	
	int specifierNumber;
	int status;
	void operator = (const Market&);
};
void Market:: operator = (const Market & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	map = rhs.map;
	for (int j = 0; j < outcomeArrayNumber; j++) {
		if (outcomeNumber[j] > 0) { for (int i = 0; i < outcomeNumber[j]; i++) if (outcomeName[j][i] != NULL) delete[] outcomeName[j][i]; }; if (outcomeName[j] != NULL) delete[] outcomeName[j]; if (outcomeId[j] != NULL) delete[] outcomeId[j]; if (outcomeVariantText[j] != NULL) delete[] outcomeVariantText[j];
	}
	if (outcomeId != NULL) delete[] outcomeId;
	if (outcomeNumber != NULL) delete[] outcomeNumber;
	if (outcomeVariantText != NULL) delete[] outcomeVariantText;
	if (outcomeName != NULL) delete[] outcomeName;
	if (outcomeNumber != NULL) delete[] outcomeNumber;



	outcomeArrayNumber = rhs.outcomeArrayNumber;
	if (outcomeId != NULL) delete[] outcomeId;
	if (outcomeName != NULL) delete[] outcomeName;
	if (outcomeNumber != NULL) delete[] outcomeNumber;
 	outcomeNumber = new int[outcomeArrayNumber];
	outcomeName = new char**[outcomeArrayNumber];
	outcomeId = new int*[outcomeArrayNumber];
	for (j = 0; j < outcomeArrayNumber; j++)

	outcomeNumber = rhs.outcomeNumber;
	status = rhs.status;
	type = rhs.type;
	strcpy(name, rhs.name);
	outcomeName = new char*[outcomeNumber];
	outcomeId = new int[outcomeNumber];
	
	for (int i = 0; i < outcomeNumber; i++) {
	outcomeName[i] = new char[NAME_LENTGH];
	strcpy(outcomeName[i], rhs.outcomeName[i]);
	outcomeId[i] = rhs.outcomeId[i];
	}

	strcpy(name, rhs.name);

	for (int i = 0; i < specifierNumber; i++) if (specifierName[i] != NULL) delete[] specifierName[i];
	if (specifierName != NULL) delete[]specifierName;
	for (int i = 0; i < specifierNumber; i++) if (specifierDescription[i] != NULL) delete[] specifierDescription[i];
	if (specifierDescription != NULL) delete[]specifierDescription;
	
	specifierNumber = rhs.specifierNumber;
	strcpy(name, rhs.name);
	specifierName = new char*[specifierNumber];
	specifierDescription = new char*[specifierNumber];
	specifierType = new int[specifierNumber];

	for (int i = 0; i < specifierNumber; i++) {
		specifierName[i] = new char[NAME_LENTGH];
		specifierDescription[i] = new char[NAME_LENTGH];
		strcpy(specifierName[i], rhs.specifierName[i]);
		strcpy(specifierDescription[i], rhs.specifierDescription[i]);
		specifierType[i] = rhs.specifierType[i];
	}


}
Market::Market() {
	id = 0;
	map = 0;
	name = new char[NAME_LENTGH];
	outcomeNumber = 0;
	outcomeId = NULL;
	outcomeName = NULL;
	specifierName=NULL;
	specifierDescription = NULL;
	specifierType=NULL;
	specifierNumber = 0;
	


};

char**map = new char*[MAX_PATH];
Event* events = new Event[EVENT_LENTGH];
int events_l = 0;

Sport* sports = new Sport[SPORT_LENTGH];
int sports_l = 0;
Tournament* tournaments = new Tournament[TOURNAMENT_LENTGH];
int tournaments_l = 0;
Category* categories = new Category[CATEGORY_LENTGH];
int categories_l = 0;
Market* markets = new Market[MARKET_LENGTH];
void getSports();
void getEvents(time_t);
void getCategoriesTournaments();
void eventFixture(Event*);
void startRecovery();
void getMarkets();

int httpsRequest(char*, char*, char*, int);
int httpsServer();
void sdkSocket();


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
{  //char* domain = "api.betradar.com";
	//char* path = "/v1/sports/en/sports.xml";//" / v1 / sports / en / tournaments.xml";
	int recvbuflen = DEFAULT_BUFLEN; 
	recvbuf = new char[DEFAULT_BUFLEN];
	//sdkSocket();
	/*Event* test = new Event();
	test->id = 294465;
	test->race = 1;
	eventFixture(test);*/

	getSports();
	getCategoriesTournaments();
	//for (int i = 0; i < EVENT_LENTGH; i++)
   // events[i].status = -1;
	//events_l = 0;
	getEvents(0);

	//for (int i = 0; i < events_l; i++) eventFixture(&events[i]);
	
	startRecovery();
	//httpsRequest(domain, path, recvbuf, 0);
	rabbitmqssl();
	//sdkSocket();
	//httpsServer();
	return 0;
}


void startRecovery() {
	httpsRequest("api.betradar.com", "/v1/pre/recovery/initiate_request?request_id=1", recvbuf, 1);
	//printf(recvbuf);
	printf("Start recovery\r\n");


}
void getCategoriesTournaments() {
	httpsRequest("api.betradar.com", "/v1/sports/en/tournaments.xml", recvbuf, 0);
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;
//	using namespace std;
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
		if (tournaments[i].id == 0) {
			tournaments[i].id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 19)); 
			if(tournaments[i].id > 0)	tournaments[i].race = 1;
			else { tournaments[i].id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 21)); tournaments[i].race = 2;
			}
		}


		//printf("tournamentId=%d Name=%s", tournaments[i].id, tournaments[i].name);
		temp = atoi((char*)((char*)tournament_node->first_node("category")->first_attribute("id")->value() + 12));
		temp2 = atoi((char*)((char*)tournament_node->first_node("sport")->first_attribute("id")->value() + 9));
		
		//printf("tournaments[i].id=%d\r\n", tournaments[i].id);
		if(tournaments[i].race==0) strcpy(tournaments[i].seasonName, tournament_node->first_node("current_season")->first_attribute("name")->value());


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
void getSports() {
httpsRequest("api.betradar.com", "/v1/sports/en/sports.xml", recvbuf, 0);
using namespace rapidxml;
xml_document<> doc;
xml_node<> * root_node;
//using namespace std;
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
void getEvents(time_t sec) {
	int days = 1;
	char buffer[MAX_PATH];
	char buf[MAX_PATH];
	time_t now = sec;
	time_t start;
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;
	//using namespace std;
	SYSTEMTIME st;
	struct tm tm;
	memset(&st, 0, sizeof(st));
	memset(&tm, 0, sizeof(tm));

	if (sec == 0) { days = 200; time(&now); }
	int i = 0;
	int k = 0;
	
	for (int j = 0; j < days; j++) {

		now = now + j * 24 * 60 * 60;
		strftime(buf, 80, "%Y-%m-%d", gmtime(&now));
		strcpy(buffer, "/v1/sports/en/schedules/");
		strcat(buffer, buf);
		strcat(buffer, "/schedule.xml");
		httpsRequest("api.betradar.com", buffer, recvbuf, 0);
	    for (k = 0; k < 1000; k++) if (recvbuf[k] == '\r' && recvbuf[k + 1] == '\n' && recvbuf[k + 2] == '\r' && recvbuf[k + 3] == '\n') break;
		      
		doc.parse<0>((char*)((char*)recvbuf + k + 4));
		root_node = doc.first_node("schedule");
		if (root_node == NULL) continue;
				

		for (xml_node<> * event_node = root_node->first_node("sport_event"); event_node; event_node = event_node->next_sibling())
		{
			events[i].id = atoi((char*)((char*)event_node->first_attribute("id")->value() + 9));
			if (events[i].id == 0) {
				events[i].id = atoi((char*)((char*)event_node->first_attribute("id")->value() + 14));
				events[i].race = 1; }

			//if (events[i].race == 1) printf("eventid=%d\r\n", events[i].id);
		
			

			if (event_node->first_attribute("status") != NULL) {
				if (strcmp("live", event_node->first_attribute("status")->value()) == 0)  events[i].status = 1; else
					if (strcmp("closed", event_node->first_attribute("status")->value()) == 0)  events[i].status = 4; else
						if (strcmp("ended", event_node->first_attribute("status")->value()) == 0)  events[i].status = 3; else
							if (strcmp("not_started", event_node->first_attribute("status")->value()) == 0)  events[i].status = 0;
				                if (strcmp("abandoned", event_node->first_attribute("status")->value()) == 0)  events[i].status = 5;
								   if (strcmp("suspended", event_node->first_attribute("status")->value()) == 0)  events[i].status = 2;
								   		
			
			




			}

			//event_node->first_attribute("scheduled")->value()[17] = '0';

		

			//printf("fff");

			//if(event_node->first_attribute("scheduled")!=NULL)  printf("s%d=",(int)event_node->first_attribute("sheduled")->value_size());

			
			strcpy(buf, event_node->first_attribute("id")->next_attribute()->value());
			sscanf(buf, "%d-%d-%dT%d:%d:%d",&st.wYear,&st.wMonth,&st.wDay,&st.wHour,&st.wMinute, &st.wSecond);
			tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
			tm.tm_mon = st.wMonth - 1;tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
			start = mktime(&tm); 
			events[i].timestamp = (int)start;
		    //printf("timestamp=%d\r\n", events[i].timestamp);
			//strftime(buf, 80, "%Y-%m-%d", gmtime(&start));
			//printf(buf);;
			//printf("\r\n");

			//events[i].status = 0;
			events[i].booked = 0;
			
			if (events[i].race == 0) {
				strcpy(buf, event_node->first_attribute("liveodds")->value());
				if (buf[0] == 'b'&& buf[1] == 'o') events[i].booked = 1;
				strcpy(events[i].home_name, event_node->first_node("competitors")->first_node("competitor")->first_attribute("name")->value());
				strcpy(events[i].away_name, event_node->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("name")->value());
				events[i].home_id = atoi((char*)((char*)event_node->first_node("competitors")->first_node("competitor")->first_attribute("id")->value() + 14));
				events[i].away_id = atoi((char*)((char*)event_node->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("id")->value() + 14));
				
				if (event_node->first_node("competitors")->first_node("competitor")->first_attribute("id")->value()[3] == 'c')
					events[i].home_superid = atoi((char*)event_node->first_node("competitors")->first_node("competitor")->first_node("reference_ids")->first_node("reference_id")->first_attribute("value")->value()); else { events[i].home_superid = events[i].home_id; events[i].home_id = 0;
				}
					
				if (event_node->first_node("competitors")->last_node("competitor")->first_attribute("id")->value()[3] == 'c')
					events[i].away_superid = atoi((char*)event_node->first_node("competitors")->last_node("competitor")->first_node("reference_ids")->first_node("reference_id")->first_attribute("value")->value()); else {
					events[i].away_superid = events[i].away_id; events[i].away_id = 0;
				}
					
				events[i].tournament_id = atoi((char*)((char*)event_node->first_node("tournament")->first_attribute("id")->value() + 15));
				if(events[i].tournament_id==0) events[i].tournament_id = atoi((char*)((char*)event_node->first_node("tournament")->first_attribute("id")->value() + 21));
				events[i].sport_id = atoi((char*)((char*)event_node->first_node("tournament")->first_node("sport")->first_attribute("id")->value() + 9));
				events[i].category_id = atoi((char*)((char*)event_node->first_node("tournament")->first_node("category")->first_attribute("id")->value() + 12));
			
			}
			else {
				events[i].parent_id = atoi((char*)((char*)event_node->first_node("parent")->first_attribute("id")->value() + 19));
				strcpy(events[i].home_name, event_node->first_attribute("name")->value());
				strcpy(events[i].away_name, event_node->first_node("parent")->first_attribute("name")->value());
				if (event_node->first_node("tournament"))
				{
					events[i].tournament_id = atoi((char*)((char*)event_node->first_node("tournament")->first_attribute("id")->value() + 19));
					events[i].sport_id = atoi((char*)((char*)event_node->first_node("tournament")->first_node("sport")->first_attribute("id")->value() + 9));
					events[i].category_id = atoi((char*)((char*)event_node->first_node("tournament")->first_node("category")->first_attribute("id")->value() + 12));
				}
			}
								
			//printf("\r\n\r\n");
			//printf("tour=%d  sport=%d  cat=%d       ", events[i].tournament_id, events[i].sport_id, events[i].category_id);



			i++;
				
			}
						
			
					//	printf("%d\r\n", i);
						//printf("cicle end");
	}
		
	

	events_l = i;
	printf("Create events successful. Number of events: %d\r\n", events_l);


	
}
void getMarkets() {
	char buffer[MAX_PATH];
	char buf[MAX_PATH];
	int* outcomeId = new int[MAX_PATH];
	char** outcomeName = new char*[MAX_PATH];
	char** specifierName = new char*[MAX_PATH];
	char** specifierDescription= new char*[MAX_PATH];
	int* specifierType = new int[MAX_PATH];;//0 null //1 int //2 string 3://decimal 4//variable	
	


	using namespace rapidxml;
	xml_document<> doc;
	xml_node<> * root_node;
	//using namespace std;
	int k = 0;
	int i = 0;
	int j = 0;
	for (i = 0; i < NAME_LENTGH; i++) outcomeName[i] = new char[NAME_LENTGH];
	
	httpsRequest("api.betradar.com", "/v1/descriptions/ru/markets.xml?include_mappings=true", recvbuf, 0);
	for (k = 0; k < 1000; k++) if (recvbuf[k] == '\r' && recvbuf[k + 1] == '\n' && recvbuf[k + 2] == '\r' && recvbuf[k + 3] == '\n') break;
	doc.parse<0>((char*)((char*)recvbuf + k + 4));
	root_node = doc.first_node("market_descriptions");
	if (root_node == NULL) return;


	for (xml_node<> * market_node = root_node->first_node("market"); market_node; market_node = market_node->next_sibling())
	{
		markets[i].id = atoi(market_node->first_attribute("id")->value());
		std::strcpy(markets[i].name, market_node->first_attribute("name")->value());
		if (market_node->first_attribute("includes_outcomes_of_type") != NULL) {
			if (strcmp("sr:player", market_node->first_attribute("includes_outcomes_of_type")->value()) == 0)  markets[i].type = 1; else
				if (strcmp("sr:competitor", market_node->first_attribute("includes_outcomes_of_type")->value()) == 0)  markets[i].type = 2;
			       if (strcmp("pre:outcometext", market_node->first_attribute("includes_outcomes_of_type")->value()) == 0)  markets[i].type = 3;
				else markets[i].type = 4;
		}

		markets[i].outcomeNumber = 0;
		j = 0;
		if (market_node->first_node("outcomes")) for (xml_node<> * outcome_node = market_node->first_node("outcomes")->first_node("outcome"); outcome_node; outcome_node = outcome_node->next_sibling()) {
			outcomeId[j] = atoi(outcome_node->first_attribute("id")->value());
			std::strcpy(outcomeName[j], outcome_node->first_attribute("name")->value());
			markets[i].outcomeNumber++;

		}

		if (markets[i].outcomeNumber > 0) {
			markets[i].outcomeId = new int[markets[i].outcomeNumber];
			markets[i].outcomeName = new char*[markets[i].outcomeNumber];
			for (k = 0; k < markets[i].outcomeNumber; k++) {
				markets[i].outcomeName[k] = new char[NAME_LENTGH];
				std::strcpy(markets[i].outcomeName[k], outcomeName[k]);
				markets[i].outcomeId[k] = outcomeId[k];
			}

			


			}



		markets[i].specifierNumber = 0;
		j = 0;
		if (market_node->first_node("specifiers")) for (xml_node<> * specifier_node = market_node->first_node("specifiers")->first_node("specifier"); specifier_node; specifier_node = specifier_node->next_sibling()) {
			if (specifier_node->first_attribute("descritions")) {
				specifierDescription[j] = new char[NAME_LENTGH]; std::strcpy(specifierDescription[j], specifier_node->first_attribute("descritions")->value());
			}
			if (specifier_node->first_attribute("name")) {
				specifierName[j] = new char[NAME_LENTGH]; std::strcpy(specifierName[j], specifier_node->first_attribute("name")->value());
				}
			 
			 //0 null //1 int //2 string 3://decimal 4//variable	
			 specifierType[j] = 0;
			 if (specifier_node->first_attribute("type") != NULL) {
				 if (strcmp("integer", specifier_node->first_attribute("type")->value()) == 0)  specifierType[j] = 1; else
					 if (strcmp("string", specifier_node->first_attribute("type")->value()) == 0)  specifierType[j] = 2; else
						 if (strcmp("decimal", specifier_node->first_attribute("type")->value()) == 0)  specifierType[j] = 3; else
							 if (strcmp("variable_text", specifier_node->first_attribute("type")->value()) == 0)  specifierType[j] = 4; 
			 }

			  
			 markets[i].specifierNumber++;

		}

		if (markets[i].specifierNumber > 0) {
			markets[i].specifierType = new int[markets[i].specifierNumber];
			markets[i].specifierName = new char*[markets[i].specifierNumber];
			markets[i].specifierDescription = new char*[markets[i].specifierNumber];

			for (k = 0; k < markets[i].specifierNumber; k++) {
				if (specifierName[k] != NULL) { markets[i].specifierName[k] = new char[NAME_LENTGH]; std::strcpy(markets[i].specifierName[k], specifierName[k]); }
				if (specifierDescription[k] != NULL) { markets[i].specifierDescription[k] = new char[NAME_LENTGH]; std::strcpy(markets[i].specifierDescription[k], specifierDescription[k]); }	markets[i].specifierType[k] = specifierType[k];
			}




		}



















		}


			if (events[i].id == 0) {
				events[i].id = atoi((char*)((char*)event_node->first_attribute("id")->value() + 14));
				events[i].race = 1;
			}

			//if (events[i].race == 1) printf("eventid=%d\r\n", events[i].id);



			if (event_node->first_attribute("status") != NULL) {
				if (strcmp("live", event_node->first_attribute("status")->value()) == 0)  events[i].status = 1; else
					if (strcmp("closed", event_node->first_attribute("status")->value()) == 0)  events[i].status = 4; else
						if (strcmp("ended", event_node->first_attribute("status")->value()) == 0)  events[i].status = 3; else
							if (strcmp("not_started", event_node->first_attribute("status")->value()) == 0)  events[i].status = 0;
				if (strcmp("abandoned", event_node->first_attribute("status")->value()) == 0)  events[i].status = 5;
				if (strcmp("suspended", event_node->first_attribute("status")->value()) == 0)  events[i].status = 2;







			}

			//event_node->first_attribute("scheduled")->value()[17] = '0';



			//printf("fff");

			//if(event_node->first_attribute("scheduled")!=NULL)  printf("s%d=",(int)event_node->first_attribute("sheduled")->value_size());


			strcpy(buf, event_node->first_attribute("id")->next_attribute()->value());
			sscanf(buf, "%d-%d-%dT%d:%d:%d", &st.wYear, &st.wMonth, &st.wDay, &st.wHour, &st.wMinute, &st.wSecond);
			tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
			tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
			start = mktime(&tm);
			events[i].timestamp = (int)start;
			//printf("timestamp=%d\r\n", events[i].timestamp);
			//strftime(buf, 80, "%Y-%m-%d", gmtime(&start));
			//printf(buf);;
			//printf("\r\n");

			//events[i].status = 0;
			events[i].booked = 0;

			if (events[i].race == 0) {
				strcpy(buf, event_node->first_attribute("liveodds")->value());
				if (buf[0] == 'b'&& buf[1] == 'o') events[i].booked = 1;
				strcpy(events[i].home_name, event_node->first_node("competitors")->first_node("competitor")->first_attribute("name")->value());
				strcpy(events[i].away_name, event_node->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("name")->value());
				events[i].home_id = atoi((char*)((char*)event_node->first_node("competitors")->first_node("competitor")->first_attribute("id")->value() + 14));
				events[i].away_id = atoi((char*)((char*)event_node->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("id")->value() + 14));

				if (event_node->first_node("competitors")->first_node("competitor")->first_attribute("id")->value()[3] == 'c')
					events[i].home_superid = atoi((char*)event_node->first_node("competitors")->first_node("competitor")->first_node("reference_ids")->first_node("reference_id")->first_attribute("value")->value()); else {
					events[i].home_superid = events[i].home_id; events[i].home_id = 0;
				}

				if (event_node->first_node("competitors")->last_node("competitor")->first_attribute("id")->value()[3] == 'c')
					events[i].away_superid = atoi((char*)event_node->first_node("competitors")->last_node("competitor")->first_node("reference_ids")->first_node("reference_id")->first_attribute("value")->value()); else {
					events[i].away_superid = events[i].away_id; events[i].away_id = 0;
				}

				events[i].tournament_id = atoi((char*)((char*)event_node->first_node("tournament")->first_attribute("id")->value() + 15));
				if (events[i].tournament_id == 0) events[i].tournament_id = atoi((char*)((char*)event_node->first_node("tournament")->first_attribute("id")->value() + 21));
				events[i].sport_id = atoi((char*)((char*)event_node->first_node("tournament")->first_node("sport")->first_attribute("id")->value() + 9));
				events[i].category_id = atoi((char*)((char*)event_node->first_node("tournament")->first_node("category")->first_attribute("id")->value() + 12));

			}
			else {
				events[i].parent_id = atoi((char*)((char*)event_node->first_node("parent")->first_attribute("id")->value() + 19));
				strcpy(events[i].home_name, event_node->first_attribute("name")->value());
				strcpy(events[i].away_name, event_node->first_node("parent")->first_attribute("name")->value());
				if (event_node->first_node("tournament"))
				{
					events[i].tournament_id = atoi((char*)((char*)event_node->first_node("tournament")->first_attribute("id")->value() + 19));
					events[i].sport_id = atoi((char*)((char*)event_node->first_node("tournament")->first_node("sport")->first_attribute("id")->value() + 9));
					events[i].category_id = atoi((char*)((char*)event_node->first_node("tournament")->first_node("category")->first_attribute("id")->value() + 12));
				}
			}

			//printf("\r\n\r\n");
			//printf("tour=%d  sport=%d  cat=%d       ", events[i].tournament_id, events[i].sport_id, events[i].category_id);



			i++;

		}


		//	printf("%d\r\n", i);
		//printf("cicle end");
	



	events_l = i;
	printf("Create events successful. Number of events: %d\r\n", events_l);



}
void eventFixture(Event* event) {
	char buf[10];
	char buffer[1024];
	//if (event->race == 1) return;
	_itoa(event->id, buf, 10);
	if(event->race==0) strcpy(buffer, "/v1/sports/en/sport_events/sr:match:");
	else strcpy(buffer, "/v1/sports/en/sport_events/sr:race_event:");
	strcat(buffer, buf);
	strcat(buffer, "/fixture.xml");
	httpsRequest("api.betradar.com", buffer, recvbuf, 0);
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
	root_node = doc.first_node("fixtures_fixture");
	if (root_node == NULL) return;
	strcpy(buf, root_node->first_node("fixture")->first_attribute("start_time")->value());
	sscanf(buf, "%d-%d-%dT%d:%d:%d", &st.wYear, &st.wMonth, &st.wDay, &st.wHour, &st.wMinute, &st.wSecond);
	tm.tm_year = st.wYear - 1900; // EDIT 2 : 1900's Offset as per comment
	tm.tm_mon = st.wMonth - 1; tm.tm_mday = st.wDay;	tm.tm_hour = st.wHour;	tm.tm_min = st.wMinute;	tm.tm_sec = st.wSecond; tm.tm_isdst = -1; // Edit 2: Added as per comment
	start = mktime(&tm);
	event->timestamp = (int)start;
	

	if (event->race == 1) {
		event->parent_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("parent")->first_attribute("id")->value() + 19));
		strcpy(event->home_name, root_node->first_node("fixture")->first_attribute("name")->value());
		strcpy(event->away_name, root_node->first_node("fixture")->first_node("parent")->first_attribute("name")->value());
		if (root_node->first_node("fixture")->first_node("tournament"))
		{
    		event->tournament_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_attribute("id")->value() + 19));
			event->sport_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_node("sport")->first_attribute("id")->value() + 9));
			event->category_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_node("category")->first_attribute("id")->value() + 12));
		}
	}









	if (event->race == 0) {
		strcpy(buf, root_node->first_node("fixture")->first_attribute("liveodds")->value());
		if (buf[0] == 'b'&& buf[1] == 'o') event->booked = 1;
		strcpy(event->home_name, root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->first_attribute("name")->value());
		strcpy(event->away_name, root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("name")->value());
		event->home_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->first_attribute("id")->value() + 14));
		event->away_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->next_sibling()->first_attribute("id")->value() + 14));

		if (root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->first_attribute("id")->value()[3] == 'c')
			event->home_superid = atoi((char*)root_node->first_node("fixture")->first_node("competitors")->first_node("competitor")->first_node("reference_ids")->first_node("reference_id")->first_attribute("value")->value()); else {
			event->home_superid = event->home_id; event->home_id = 0;
		}

		if (root_node->first_node("fixture")->first_node("competitors")->last_node("competitor")->first_attribute("id")->value()[3] == 'c')
			event->away_superid = atoi((char*)root_node->first_node("fixture")->first_node("competitors")->last_node("competitor")->first_node("reference_ids")->first_node("reference_id")->first_attribute("value")->value()); else {
			event->away_superid = event->away_id; event->away_id = 0;
		}

		event->tournament_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_attribute("id")->value() + 15));
		if (event->tournament_id == 0) event->tournament_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_attribute("id")->value() + 21));
		event->sport_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_node("sport")->first_attribute("id")->value() + 9));
		event->category_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_node("category")->first_attribute("id")->value() + 12));





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
			strcpy(event->tv_channels, buffer);
			//printf(event->tv_channels);
		}



		if (root_node && root_node->first_node("fixture") && root_node->first_node("fixture")->first_node("venue")) {
			buffer[0] = 0;
			if (root_node->first_node("fixture")->first_node("venue")->first_attribute("name")) { strcpy(buffer, root_node->first_node("fixture")->first_node("venue")->first_attribute("name")->value()); }
			strcat(buffer, " / ");

			if (root_node->first_node("fixture")->first_node("venue")->first_attribute("capacity")) {
				strcat(buffer, root_node->first_node("fixture")->first_node("venue")->first_attribute("capacity")->value());
				strcat(buffer, " / ");
			}
			if (root_node->first_node("fixture")->first_node("venue")->first_attribute("city_name"))
				strcat(buffer, root_node->first_node("fixture")->first_node("venue")->first_attribute("city_name")->value());
			event->venue = new char[strlen(buffer) + 1];
			strcpy(event->venue, buffer);
			//printf(event->venue);
		}
	}


	
	//if (event->sport_id == 5) printf("period_legth=%d\r\n", event->period_length);

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
	using namespace rapidxml;
	using namespace std;
	xml_document<> doc;
	xml_node<> * root_node;

	uint64_t start_time = now_microseconds();
	int received = 0;
	int previous_received = 0;
	uint64_t previous_report_time = start_time;
	uint64_t next_summary_time = start_time + SUMMARY_EVERY_US;
	HANDLE File;
	DWORD l = 0;
	amqp_frame_t frame;
	uint64_t now;
	char* name = new char[MAX_PATH];
	char* buf = new char[MAX_PATH];

	int i = 0;

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
		//envelope.message.body.bytes
		
		if (envelope.message.body.len > 50000) {
			i++;
			strcpy(name, "D://unifeed");
			_itoa(i, buf, 10);
			strcat(name, buf);
			strcat(name, ".xml");
			DeleteFile(name);
			File = CreateFile(name, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			l = SetFilePointer(File, 0, 0, FILE_BEGIN);
			printf("message length= %d\r\n", envelope.message.body.len);
			WriteFile(File, envelope.message.body.bytes, envelope.message.body.len, &l, NULL);
			CloseHandle(File);
		}
		//WriteFile(File, "<endmessage></endmessage>", strlen("<endmessage></endmessage>"), &l, NULL);

		if (i > 50) return;
		
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
	CloseHandle(File);
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
		return;
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
		return;
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











