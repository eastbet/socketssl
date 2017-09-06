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
#define MAX_EVENTS 13000000
#define MAX_LINES 100000

#define MAX_TOURNAMENTS 1000000
#define MAX_CATEGORIES 10000
#define MAX_COMPETITORS 1000000
#define MAX_PLAYERS 10000000
#define MAX_SPORTS 1000
#define MAX_MARKETS 10000
#define MAX_MARKETS_IN 2000
#define MAX_BETSTOPS 200
#define MAX_MATCHSTATUS 1000
// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

char* recvbuf;
  


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
	int race = 0;
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
	race = rhs.race;
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
	race = 0;
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
	~Category() { if (name != NULL) delete[] name; };
	int id;
	int sport_id;
	int sort;
	char *name;
	void operator = (const Category&);
};
void Category:: operator = (const Category & rhs) {
	if (this == &rhs) return;
	id = rhs.id;
	sport_id = rhs.sport_id;
	sort = rhs.sort;
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
	name = NULL;
};
class Event {
public:
	Event();
	~Event() {
		if (home_name != NULL) delete[] home_name; if (tv_channels != NULL) delete[] tv_channels; if (venue != NULL) delete[] venue; if (away_name != NULL) delete[] away_name;
		if (set_scores != NULL) delete[] set_scores;  if (match_time != NULL) delete[] match_time; if (remaining_time != NULL) delete[] remaining_time; if (remaining_time_in_period != NULL) delete[] remaining_time_in_period; if (game_score != NULL) delete[] game_score; if (leg_score != NULL) delete[] leg_score; if (bases!= NULL) delete[] bases;
		if (stoppage_time != NULL) delete[] stoppage_time; if (delayed_description != NULL) delete[] delayed_description;
	};

	
	int id;
	int position;
	int bo;
	int sport_id;
	int category_id;
	int tournament_id;
	int home_id;
	int away_id;
	int winner_id;
	int home_super_id = 0;
	int away_super_id = 0;
	int status; //0(not started) / 1(live) / 2(suspended) /	3(ended) / 4(closed) / abandoned - only one of these 6 is possible
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
	int stopped;
	int home_yellowcards;
	int away_yellowcards;
	int home_redcards;
	int away_redcards;
	int remaining_reds;
	int current_server;
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
	int race;
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
	winner_id = rhs.winner_id;
	away_id = rhs.away_id;
	home_super_id = rhs.home_super_id;
	away_super_id = rhs.away_super_id;
	status = rhs.status; //0(not started) / 1(live) / 2(suspended) /	3(ended) / 4(closed) / abandoned - only one of these 6 is possible
	reporting = rhs.reporting;//
	home_score = rhs.home_score;
	away_score = rhs.away_score;
	delayed_id = rhs.delayed_id;
	home_gamescore = rhs.home_gamescore;
	away_gamescore = rhs.away_gamescore;
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

	if (game_score != NULL) {
		delete[] game_score; game_score = NULL;
	}
	if (rhs.game_score != NULL) {
		game_score = new char[strlen(rhs.game_score) + 1];
		std::strcpy(game_score, rhs.game_score);
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


	if (leg_score != NULL) {
		delete[] leg_score; leg_score = NULL;
	}
	if (rhs.leg_score != NULL) {
		leg_score = new char[strlen(rhs.leg_score) + 1];
		std::strcpy(leg_score, rhs.leg_score);
	}

	stopped = rhs.stopped;
	home_yellowcards = rhs.home_yellowcards;
	away_yellowcards = rhs.away_yellowcards;
	home_redcards = rhs.home_redcards;
	away_redcards = rhs.away_redcards;
	remaining_reds = rhs.remaining_reds;
	current_server = rhs.current_server;
	tiebreak = rhs.tiebreak;
	expedite = rhs.expedite;
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
	race = rhs.race;
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
	int status = -1; //0(not started) / 1(live) / 2(suspended) /	3(ended) / 4(closed) / abandoned - only one of these 6 is possible
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
	remaining_reds = 0;
	stopped = 0;;
	winner_id = 0;
	home_yellowcards = 0;;
	away_yellowcards = 0;
	home_redcards = 0;
	away_redcards = 0;
	current_server = 0;
	game_score = NULL;// new char[16];
	tiebreak = 0;
	expedite = 0;
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
	leg_score = NULL;// new char[16];
	throw_num = 0;
	delivery = 0;
	home_remaining_bowls = 0;
	away_remaining_bowls = 0;
	current_end = 0;
	home_dismissals = 0;
	away_dismissals = 0;
	home_penalty_runs = 0;
	away_penalty_runs = 0;
	innings = 0;
	over = 0;
	timestamp = 0;
	start_time = 0;
	next_live_time = 0;
	neutral_ground = 0;
	period_length = 0;
	overtime_length = 0;
	austrian_district = 0;
	booked = 0;
	race = 0;
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
	int type;//0 -normal//1-sr:player//2-sr:competitor//3 pre:outcometext
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
		if (name != NULL) delete[] name; if (outcome_number > 0) { for (int i = 0; i < outcome_number; i++) if (outcome_name[i] != NULL) delete[] outcome_name[i]; };
		if (outcome_id != NULL) delete[] outcome_id; if (outcome_active != NULL) delete[] outcome_active; if (outcome_team != NULL) delete[] outcome_team; if (outcome_odds != NULL) delete[] outcome_odds;
		if (outcome_probabilities != NULL) delete[] outcome_probabilities; if (outcome_name != NULL) delete[] outcome_name;
		if (specifier_number > 0) { for (int i = 0; i < specifier_number; i++) { if (specifier[i] != NULL) delete[] specifier[i];  if (specifier_value[i] != NULL) delete[] specifier_value[i]; if (specifier_value[i] != NULL) delete[] specifier_value[i];} }

		if (extended_specifier_number > 0) { for (int i = 0; i < extended_specifier_number; i++) { if (extended_specifier[i] != NULL) delete[] extended_specifier[i];  if (extended_specifier_value[i] != NULL) delete[] extended_specifier_value[i]; if (extended_specifier_value[i] != NULL) delete[] extended_specifier_value[i]; } }
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
	int status;
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
void sdkSocket();
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
	bool fullData = false;
	int recvbuflen = DEFAULT_BUFLEN;
	recvbuf = new char[DEFAULT_BUFLEN];
	for (int i = 0; i <MAX_EVENTS; i++) events_id[i] = NULL;
	for (int i = 0; i <MAX_LINES; i++) lines_id[i] = NULL;
	for (int i = 0; i <MAX_TOURNAMENTS; i++) tournaments_id[i] = NULL;
	for (int i = 0; i <MAX_TOURNAMENTS; i++) seasons_id[i] = NULL;
	for (int i = 0; i <MAX_TOURNAMENTS; i++) simples_id[i] = NULL;
	for (int i = 0; i <MAX_CATEGORIES; i++) categories_id[i] = NULL;
	for (int i = 0; i <MAX_SPORTS; i++) sports_id[i] = NULL;
	for (int i = 0; i <MAX_COMPETITORS; i++) competitors_id[i] = NULL;
	for (int i = 0; i <MAX_PLAYERS; i++) players_id[i] = NULL;
	for (int i = 0; i <MAX_MARKETS; i++) markets_id[i] = NULL;
	for (int i = 0; i <MAX_MARKETS; i++) max_markets_in[i] = 2;
	for (int i = 0; i <MAX_BETSTOPS; i++) betstops_id[i] = NULL;
	for (int i = 0; i <MAX_MATCHSTATUS; i++) matchstatus_id[i] = NULL;

	getSports();
    
	if(getBetstops()!=-1) std::printf("Load betstops success. Numbers of betstops : %d\r\n", betstops_l);
	if(getMatchstatus()!=-1) std::printf("Load matchstatus success. Numbers of matchstatus : %d\r\n", matchstatus_l);
	if (fullData == false) {
	loadMarketsFromFiles();
	loadCategoriesFromFiles(); 
	loadTournamentsFromFiles();
	loadEventsFromFiles();
	loadCompetitorsFromFiles();
	loadPlayersFromFiles();

}
	

	if (fullData == true) {
		getMarkets(); 
		getCategoriesTournaments();
		getEvents(0, 120);
		for (int i = 0; i < tournaments_l; i++) saveTournamentToFile(&tournaments[i]);
		for (int i = 0; i < categories_l; i++) saveCategoryToFile(&categories[i]);
		for (int i = 0; i < events_l; i++) 	getEventFixture(&events[i]);
		for (int i = 0; i < tournaments_l; i++) getTournament(&tournaments[i],true);

	}


startRecovery();
rabbitmqssl();
	//sdkSocket();
	//httpsServer();
	return 0;
}


void startRecovery() {
	char* recvbuf = new char[DEFAULT_BUFLEN];
	while (httpsRequest("api.betradar.com", "/v1/pre/recovery/initiate_request?request_id=2", recvbuf, 1)==-1) Sleep(1000);
	//printf(recvbuf);
	delete[] recvbuf;
	std::printf("Start recovery\r\n");


}
void getCategoriesTournaments() {
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
		tournaments[i].race = 0;

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
			if (tournaments[i].id > 0)	tournaments[i].race = 1;
			else {
				tournaments[i].id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 21));
				if (tournaments[i].id > 0) tournaments[i].race = 2;
				else {
					tournaments[i].id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 10));
					if (tournaments[i].id > 0) tournaments[i].race = 3;
				}
			}
		}
	


		//printf("tournamentId=%d Name=%s", tournaments[i].id, tournaments[i].name);
		temp = atoi((char*)((char*)tournament_node->first_node("category")->first_attribute("id")->value() + 12));

		temp2 = atoi((char*)((char*)tournament_node->first_node("sport")->first_attribute("id")->value() + 9));

		//printf("tournaments[i].id=%d\r\n", tournaments[i].id);
		if (tournaments[i].race == 0) {

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

		if (temp >= MAX_CATEGORIES) std::printf("ERROR DATA!\r\ncategory id out of MAX_CATEGORIES in getCanegoryTournaments %d\r\n", temp);
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
		
		if (tournaments[i].id < MAX_TOURNAMENTS) tournaments_id[tournaments[i].id] = &tournaments[i]; else std::printf("ERROR DATA!\r\ntournament id out of MAX_TOURNAMANETS in getCanegoryTournaments %d\r\n", tournaments[i].id);
		if (tournaments[i].season_id >0) {
			if (tournaments[i].season_id < MAX_TOURNAMENTS) seasons_id[tournaments[i].season_id] = &tournaments[i]; else std::printf("ERROR DATA!\r\ntournament season_id out of MAX_TOURNAMANETS in getCanegoryTournaments %d\r\n", tournaments[i].season_id);
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

}
void getSports() {
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
		i++;
		//sport_node->first_attribute("name")->value();
		//cout << endl;
	}

	sports_l = i;
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
				events[i].race = 1;
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

			if (events[i].race == 0) {

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
					events[i].tournament_id = atoi((char*)((char*)event_node->first_node("tournament")->first_attribute("id")->value() + 21));
					events[i].race = 2;
				} else events[i].race = 0;

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

				if (events[i].race == 0) {
					if (tournaments_id[events[i].tournament_id] == NULL) {
						tournaments_id[events[i].tournament_id] = &tournaments[tournaments_l];
						tournaments_l++;
					}


					tournaments_id[events[i].tournament_id]->race = events[i].race;
					tournaments_id[events[i].tournament_id]->id = events[i].tournament_id;
					tournaments_id[events[i].tournament_id]->category_id = events[i].category_id;
					tournaments_id[events[i].tournament_id]->sport_id = events[i].sport_id;

					if (tournaments_id[events[i].tournament_id]->name != NULL) delete[] tournaments_id[events[i].tournament_id]->name;
					tournaments_id[events[i].tournament_id]->name = new char[strlen(event_node->first_node("tournament")->first_attribute("name")->value()) + 1];
					std::strcpy(tournaments_id[events[i].tournament_id]->name, event_node->first_node("tournament")->first_attribute("name")->value());
				}

					
				if (events[i].race == 2) {
					if (simples_id[events[i].tournament_id] == NULL) {
						simples_id[events[i].tournament_id] = &tournaments[tournaments_l];
						tournaments_l++;
					}


					simples_id[events[i].tournament_id]->race = events[i].race;
					simples_id[events[i].tournament_id]->id = 0;
					simples_id[events[i].tournament_id]->simple_id = events[i].tournament_id;
					simples_id[events[i].tournament_id]->category_id = events[i].category_id;
					simples_id[events[i].tournament_id]->sport_id = events[i].sport_id;

					if (simples_id[events[i].tournament_id]->name != NULL) delete[] simples_id[events[i].tournament_id]->name;
					simples_id[events[i].tournament_id]->name = new char[strlen(event_node->first_node("tournament")->first_attribute("name")->value()) + 1];
					std::strcpy(simples_id[events[i].tournament_id]->name, event_node->first_node("tournament")->first_attribute("name")->value());
				}


					

					if (event_node->first_node("season") && events[i].race==0) {
						
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
				events[i].parent_id = atoi((char*)((char*)event_node->first_node("parent")->first_attribute("id")->value() + 19));

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


					tournaments_id[events[i].tournament_id]->race = events[i].race;
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
			
	//	if ((events[i].booked == 2 && booked_num<20 && events[i].start_time>time(nullptr)) && (events[i].sport_id == 21 || events[i].sport_id == 1)) {postBooked(events[i].id); booked_num++;}

			i++;

		}

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
	else std::strcpy(buffer, "/v1/descriptions/en/markets/");
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

	
	  if (_market->type == 3 && root_node->first_node("market") && root_node->first_node("market")->first_attribute("name")) {
		  if (_market->name != NULL) delete[] _market->name;
		  _market->name = new char[strlen(root_node->first_node("market")->first_attribute("name")->value()) + 1];
		  std::strcpy(_market->name, root_node->first_node("market")->first_attribute("name")->value());
		  	  }

	

	if (_market->variable_text != NULL) delete[] _market->variable_text;
	_market->variable_text = new char[strlen(urn) + 1];
	std::strcpy(_market->variable_text, urn);
	_market->outcome_number = 0;


	if (root_node->first_node("market") && root_node->first_node("market")->first_node("outcomes")) for (xml_node<> * outcome_node = root_node->first_node("market")->first_node("outcomes")->first_node("outcome"); outcome_node; outcome_node = outcome_node->next_sibling()) {
		if(_market->type==3)outcome_id[_market->outcome_number] = atoi((char*)((char*)outcome_node->first_attribute("id")->value() + 16));
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
	if (root_node == NULL) { delete[] recvbuf; return -1; }
	xml_node<> * player_node = root_node->first_node("player"); if (player_node == NULL) {
		delete[] recvbuf; return -1;
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
	if (root_node == NULL) { delete[] recvbuf; delete player; return -1; }
	xml_node<> * competitor_node = root_node->first_node("competitor"); if (competitor_node == NULL) { delete[] recvbuf; delete player; return -1; }


	

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
	 delete[] recvbuf; delete player; return -1; } else  competitors_id[competitor->id] = competitor;
		
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
	return 0;
}
int getEventFixture(Event* event) {
	char buf[10];
	char buffer[4096];
	char* recvbuf = new char[DEFAULT_BUFLEN];
	//if (event->race == 1) return;
	_itoa(event->id, buf, 10);
	if (event->race == 0|| event->race == 2) std::strcpy(buffer, "/v1/sports/en/sport_events/sr:match:");
	else std::strcpy(buffer, "/v1/sports/en/sport_events/sr:race_event:");
	std::strcat(buffer, buf);
	std::strcat(buffer, "/fixture.xml");
	while(httpsRequest("api.betradar.com", buffer, recvbuf, 0)==-1) Sleep(1000);
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
	if (root_node == NULL) { delete[] recvbuf; return -1; }
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

	
	

	if (event->race == 1) {

		if (root_node->first_node("fixture")->first_attribute("type") && root_node->first_node("fixture")->first_attribute("type")->value()[0] == 'p') 
		 event->parent_id = -1;
		
		else if	(root_node->first_node("fixture")->first_node("parent")) event->parent_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("parent")->first_attribute("id")->value() + 19));



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

				tournaments_id[event->tournament_id]->race = event->race;
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
	if (event->race == 0 || event->race == 2) {
		std::strcpy(buf, root_node->first_node("fixture")->first_attribute("liveodds")->value());
		if (buf[0] == 'b'&& buf[1] == 'o') event->booked = 1;

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
		if (event->tournament_id == 0) { event->tournament_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_attribute("id")->value() + 21)); event->race = 2; } else  event->race = 0;

		event->sport_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_node("sport")->first_attribute("id")->value() + 9));
		event->category_id = atoi((char*)((char*)root_node->first_node("fixture")->first_node("tournament")->first_node("category")->first_attribute("id")->value() + 12));



		
		if (event->tournament_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\ntournament id out of MAX_TOURNAMENTS in getEventFixture %d\r\n", event->tournament_id); 
		delete[] recvbuf; return -1;
		}
			else {
				if (event->race == 0) {

					if (tournaments_id[event->tournament_id] == NULL) {
						tournaments_id[event->tournament_id] = &tournaments[tournaments_l];
						tournaments_l++;
					}

					tournaments_id[event->tournament_id]->race = event->race;
					tournaments_id[event->tournament_id]->id = event->tournament_id;
					tournaments_id[event->tournament_id]->category_id = event->category_id;
					tournaments_id[event->tournament_id]->sport_id = event->sport_id;

					if (tournaments_id[event->tournament_id]->name != NULL) delete[] tournaments_id[event->tournament_id]->name;
					tournaments_id[event->tournament_id]->name = new char[strlen(root_node->first_node("fixture")->first_node("tournament")->first_attribute("name")->value()) + 1];
					std::strcpy(tournaments_id[event->tournament_id]->name, root_node->first_node("fixture")->first_node("tournament")->first_attribute("name")->value());
				}
			
				if (event->race == 2) {

					if (simples_id[event->tournament_id] == NULL) {
						simples_id[event->tournament_id] = &tournaments[tournaments_l];
						tournaments_l++;
					}

					simples_id[event->tournament_id]->race = event->race;
					simples_id[event->tournament_id]->id = 0;
					simples_id[event->tournament_id]->simple_id = event->tournament_id;
					simples_id[event->tournament_id]->category_id = event->category_id;
					simples_id[event->tournament_id]->sport_id = event->sport_id;

					if (simples_id[event->tournament_id]->name != NULL) delete[] simples_id[event->tournament_id]->name;
					simples_id[event->tournament_id]->name = new char[strlen(root_node->first_node("fixture")->first_node("tournament")->first_attribute("name")->value()) + 1];
					std::strcpy(simples_id[event->tournament_id]->name, root_node->first_node("fixture")->first_node("tournament")->first_attribute("name")->value());
				}
			
			
			
			}



		
				if (root_node->first_node("fixture")->first_node("tournament")->first_node("season") && event->race == 0) {
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
	
	
	if (event->race == 1 && event->tournament_id == 0 && event->parent_id > 0 && events_id[event->parent_id] != NULL) {
		event->tournament_id = events_id[event->parent_id]->tournament_id;
		event->sport_id = events_id[event->parent_id]->sport_id;
		event->category_id = events_id[event->parent_id]->category_id;
	}

	if(event->race == 2) saveTournamentToFile(simples_id[event->tournament_id]);
	else saveTournamentToFile(tournaments_id[event->tournament_id]);
	saveCategoryToFile(categories_id[event->category_id]);
	saveEventToFile(event);

	return 0;
}
int getEventSummary(Event* event) {
	char* recvbuf = new char[DEFAULT_BUFLEN];
	char buf[10];
	char buffer[1024];
	//if (event->race == 1) return;
	_itoa(event->id, buf, 10);
	if (event->race == 0) std::strcpy(buffer, "/v1/sports/en/sport_events/sr:match:");
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
	if (root_node == NULL) { delete[] recvbuf; return -1; }

	if (root_node->first_node("sport_event_conditions") && root_node->first_node("sport_event_conditions")->first_attribute("match_mode"))
		event->bo = atoi((char*)((char*)root_node->first_node("sport_event_conditions")->first_attribute("match_mode")->value() + 2));
	delete[] recvbuf;
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
	if (root_node == NULL) { delete[] recvbuf; return -1; }
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
		
		} else { delete[] recvbuf; return -1; }
	
		betstops_l = i;
		
	
	delete[] recvbuf;
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
	if (root_node == NULL) { delete[] recvbuf; return -1; }
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
	else { delete[] recvbuf; return -1; }

	matchstatus_l = i;


	delete[] recvbuf;
	return 0;

}
int getTournament(Tournament* tournament, bool extended) {
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
		delete[] recvbuf; delete competitor; return -1;
	};


	
	if (tournament->race == 0 && tournament->id == 0) _itoa(tournament->season_id, buf, 10);
	else if (tournament->race == 2 && tournament->id == 0) _itoa(tournament->simple_id, buf, 10);
	else _itoa(tournament->id, buf, 10);
	

	std::strcpy(buffer, "/v1/sports/en/tournaments/");
	if (tournament->race == 0 && tournament->id >0) 	std::strcat(buffer, "sr:tournament:"); else
		if (tournament->race == 1) 	std::strcat(buffer, "sr:race_tournament:"); else
			if (tournament->race == 2) 	std::strcat(buffer, "sr:simple_tournament:"); else
				if (tournament->race == 0 && tournament->id == 0) 	std::strcat(buffer, "sr:season:");
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
					delete[] recvbuf; delete competitor; return -1;
				}
				xml_node<> * tournament_node = root_node->first_node("tournament"); if (tournament_node == NULL) {
					delete[] recvbuf; delete competitor; return -1;
				}
				if (tournament_node->first_attribute("id")) {
					if (tournament->race == 0)  tournament->id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 14));else 
				   if (tournament->race == 1)  tournament->id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 19));
					if (tournament->race == 2)  tournament->simple_id = atoi((char*)((char*)tournament_node->first_attribute("id")->value() + 21));
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
				
				if (tournament->race == 2) {
					 simples_id[tournament->simple_id] = tournament;
						
				} else {
					if (tournament->id < MAX_TOURNAMENTS) tournaments_id[tournament->id] = tournament;
					else {
						std::printf("ERROR DATA!\r\ntournament id out of MAX_TOURNAMANETS in getTournaments %d\r\n", tournament->id); delete[] recvbuf; delete competitor; return -1;
					}

					if (tournament->season_id > 0) {
						if (tournament->season_id < MAX_TOURNAMENTS) seasons_id[tournament->season_id] = tournament; else { std::printf("ERROR DATA!\r\ntournament season_id out of MAX_TOURNAMANETS in getTournaments %d\r\n", tournament->season_id); delete[] recvbuf; delete competitor; return -1; }
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
				 else if (index_char1[i] == '%' && value[0] == 's' && value[1] == 'r') {
					 id = atoi((char*)((char*)value + 10));

					 if (id >= MAX_PLAYERS) {
						 std::printf("\r\n ERROR in replace. player_id out of MAX_PLAYERS. player_id=%d\r\n", id);
						 return;

					 }
					 if (players_id[id] == NULL) {
						 std::printf("Player id=%d not found in replace. player_id=%d . getPlayer\r\n", id);
						 players[players_l].id = id; if (getPlayer(&players[players_l]) == -1)
						 {
							 std::printf("error player id=%d  not found \r\n ", id); return;

						 }
						 else  players_l++;
					 }

					 if (players_id[id] != NULL) std::strcat(retValue, players_id[id]->name);
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
    std::strcpy(file_path, "D://Betradar//Events//");
	_itoa(event->id, buf, 10);
	strcat(file_path, buf);
	File = CreateFile(file_path, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	l = SetFilePointer(File, 0, 0, FILE_BEGIN);
	WriteFile(File, &event->id, sizeof(int), &l, NULL);
	WriteFile(File, &event->race, sizeof(int), &l, NULL);
	WriteFile(File, &event->sport_id, sizeof(int), &l, NULL);
	WriteFile(File, &event->category_id, sizeof(int), &l, NULL);
	WriteFile(File, &event->tournament_id, sizeof(int), &l, NULL);
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
	char file_path[MAX_PATH];
	char folder_path[MAX_PATH];
	char find_path[MAX_PATH];
	std::strcpy(folder_path, "D://Betradar//Events//");
	std::strcpy(find_path, "D://Betradar//Events//*.*");

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
		l = SetFilePointer(File, 0, 0, FILE_BEGIN);
		ReadFile(File, &events[i].id, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].race, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].sport_id, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].category_id, sizeof(int), &l, NULL);
		ReadFile(File, &events[i].tournament_id, sizeof(int), &l, NULL);
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
		events_id[events[i].id] = &events[i];
		if (events[i].start_time>time(nullptr) - 24 * 60 * 60) i++;
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
	std::strcpy(file_path, "D://Betradar//Markets//");
	_itoa(market->id, buf, 10);
	strcat(file_path, buf);
	if (market->variable_text != NULL) { strcat(file_path, "_"); strcpy(variable_text, market->variable_text); 
	replace_substr(variable_text, ":", "_"); strcat(file_path, variable_text);  }
	
	File = CreateFile(file_path, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == File) {
		printf("ERROR Save Market.");
		printf(file_path); printf("\r\n");

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
	std::strcpy(folder_path, "D://Betradar//Markets//");
	std::strcpy(find_path, "D://Betradar//Markets//*.*");
	
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
			
			
		

		k++;
		markets_l = k;





	} while (FindNextFile(Hd, &Fd));
	
	FindClose(Hd);

	std::printf("Markets loaded from data files succes. Number of loaded markets is %d\r\n", markets_l);
}
void saveTournamentToFile(Tournament* tournament) {
	HANDLE File;
	DWORD l = 0;
	char buf[20];
	int i = 0;
	char file_path[MAX_PATH];
	std::strcpy(file_path, "D://Betradar//Tournaments//");
	if (tournament->race == 2) { _itoa(tournament->simple_id, buf, 10); std::strcat(file_path, "Simple//");}
	if (tournament->race == 1) { _itoa(tournament->id, buf, 10); std::strcat(file_path, "Race//"); }
	if (tournament->race == 0) { _itoa(tournament->id, buf, 10); std::strcat(file_path, "Championships//"); }
	strcat(file_path, buf);
	File = CreateFile(file_path, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	l = SetFilePointer(File, 0, 0, FILE_BEGIN);
	WriteFile(File, &tournament->id, sizeof(int), &l, NULL);
	WriteFile(File, &tournament->race, sizeof(int), &l, NULL);
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
			std::strcpy(folder_path, "D://Betradar//Tournaments//Championships//");
			std::strcpy(find_path, "D://Betradar//Tournaments//Championships//*.*");
		}

		if (k == 1) {
			std::strcpy(folder_path, "D://Betradar//Tournaments//Race//");
			std::strcpy(find_path, "D://Betradar//Tournaments//Race//*.*");
		}
		if (k == 2) {
			std::strcpy(folder_path, "D://Betradar//Tournaments//Simple//");
			std::strcpy(find_path, "D://Betradar//Tournaments//Simple//*.*");
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
			ReadFile(File, &tournaments[i].race, sizeof(int), &l, NULL);
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
	HANDLE File;
	DWORD l = 0;
	char buf[20];
	int i = 0;
	char file_path[MAX_PATH];
	std::strcpy(file_path, "D://Betradar//Categories//");
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
			std::strcpy(folder_path, "D://Betradar//Categories//");
			std::strcpy(find_path, "D://Betradar//Categories//*.*");
		
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
	std::strcpy(file_path, "D://Betradar//Competitors//");
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
	std::strcpy(folder_path, "D://Betradar//Competitors//");
	std::strcpy(find_path, "D://Betradar//Competitors//*.*");

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
	std::strcpy(file_path, "D://Betradar//Players//");
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
	std::strcpy(folder_path, "D://Betradar//Players//");
	std::strcpy(find_path, "D://Betradar//Players//*.*");

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
		if (iResult == SOCKET_ERROR) wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());  WSACleanup(); 
		return -1;
	}
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
			recv[readBytes] = '\0';
		}
	} while (iResult > 0);

	//printf("fff4444444");
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
	char set_scores[1024];
	char* maxbuf = new char[1000000];
	Event* _event=new Event();
	Tournament* _tournament;
	int i = 0;
	int k = 0;
	int j = 0;
	int m = 0;
	int n = 0;
	int q = 0;
	int z = 0;
	int u = 0;
	bool print = true;
	int event_id = 0;
	int race = 0;
	int status = 0;
	int betstop_reason = 0;
	int index_separator[100];
	int index_equally[100];
	int outcome_number;
	char** outcome_name=new char*[500];
	int* outcome_id=new int[500];
	int* outcome_active=new int[500];
	int* outcome_team = new int[500];
	float* outcome_probabilities=new float[500];
	float* outcome_odds=new float[500];
	for (int i = 0; i < 500; i++) outcome_name[i] = NULL;
	Line* _line = new Line();



	for (;;) {
		amqp_rpc_reply_t ret;
		amqp_envelope_t envelope;



		status = 0;
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


	std::strncpy(maxbuf, ((char*)(envelope.message.body.bytes)), envelope.message.body.len);
		maxbuf[envelope.message.body.len] = 0;
		
		doc.parse<0>(maxbuf);
		if (doc.first_node() == NULL) continue;



		if (std::strcmp("fixture_change", doc.first_node()->name()) == 0) {

			 race = 0;
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
				if (event_id == 0) { event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 10)); race = 3; }
				if (event_id == 0) {event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 14)); race = 1;}
				if (event_id == 0) { event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 21)); race = 2; }

				if (race == 2) {
					if (event_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nssimple id out of MAX_TOURNAMENTS in run fixture_change %d\r\n", event_id); continue; }
					if (simples_id[event_id] == NULL) {
						std::printf("Simple tournament not found. Run getTournament(). simple_id=%d\r\n", event_id);
						tournaments[tournaments_l].id = 0;
						tournaments[tournaments_l].simple_id = event_id;
						tournaments[tournaments_l].race = 2;
						if (getTournament(&tournaments[tournaments_l], false) == -1) { std::printf("ERROR!\r\nTournaments simple id not found in run fixture change simple %d\r\n", event_id); continue; }
						tournaments_l++;

					}
					else if (getTournament(simples_id[event_id], false) == -1) { std::printf("ERROR!\r\nTournaments simple id not found in run fixture %d\r\n", event_id); continue; }
					std::printf("fixture_change succes for tournamnet simple id=%d\r\n", event_id);


				}
				if (race == 3) {
					if (event_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nsseason id out of MAX_TOURNAMENTS in run fixture change %d\r\n", event_id); continue; }
					if (seasons_id[event_id] == NULL) {
						std::printf("Tournament not found in run fixture change. Run getTournament(). season_id=%d\r\n", event_id);
						tournaments[tournaments_l].id = 0;
						tournaments[tournaments_l].season_id = event_id;
						tournaments[tournaments_l].race = 0;
						if (getTournament(&tournaments[tournaments_l], false) == -1) { std::printf("ERROR!\r\nTournaments season id not found in run %d\r\n", event_id); continue; }
						else {
							if (seasons_id[event_id] == NULL) { std::printf("ERROR!\r\nTournaments season id not found after succes in getTournament run %d\r\n", event_id); continue; }
							tournaments_l++; std::printf("fixture_change succes for tournamnet season id=%d\r\n",event_id);
						}
						} else if (getTournament(seasons_id[event_id], false) == -1) { std::printf("ERROR!\r\n getTournament in fixture_change season id =%d\r\n", event_id); continue; }

						std::printf("fixture_change succes for tournamnet season id=%d\r\n", event_id);
					
					}
				if (race < 2) {
					if (event_id >= MAX_EVENTS) { std::printf("ERROR DATA!\r\nsevent id out of MAX_EVENTS in run %d\r\n", event_id); continue; }
					if (events_id[event_id] == NULL) {
						std::printf("Event not found in fixture_change. %d\r\n", event_id);
						k = events_l; events_l++;
						events[k].id = event_id; events[k].race = race;
						events_id[event_id] = &events[k];
					}
					if (getEventFixture(events_id[event_id]) == -1) { std::printf("fixtur_change error. %d\r\n", event_id); continue; }
					std::printf("fixture_change success. %d\r\n");

				}
			
			}
		else 

			if (std::strcmp("odds_change", doc.first_node()->name()) == 0) {
				race = 0;
				event_id = 0;
				event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 9));
				if (event_id == 0) { event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 10)); race = 3; }
				if (event_id == 0) { event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 14)); race = 1; }
				if (event_id == 0) { event_id = atoi((char*)((char*)doc.first_node()->first_attribute("event_id")->value() + 21)); race = 2; }
				if (event_id == 0) { std::printf("event_id error=0\r\n"); std::printf(doc.first_node()->first_attribute("event_id")->value()); 
				continue;
				}

				
				if (race == 2) {
					
					if (event_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nssimple id out of MAX_TOURNAMENTS in run odds_change %d\r\n", event_id); continue; }
					if (simples_id[event_id] == NULL) {
						std::printf("Simple tournament not found. Run getTournament(). simple_id=%d\r\n", event_id);
						tournaments[tournaments_l].id = 0;
						tournaments[tournaments_l].simple_id = event_id;
						tournaments[tournaments_l].race = 2;
						if (getTournament(&tournaments[tournaments_l], false) == -1) { std::printf("ERROR!\r\nTournaments simple id not found in run simple %d\r\n", event_id); continue; }
					     tournaments_l++;
											
					}

					if (simples_id[event_id] == NULL) { std::printf("ERROR!\r\nTournaments simple id not found after succes in getTournament run simple %d\r\n", event_id); continue; }
					_tournament = simples_id[event_id];


						if (_tournament->sport_id >= MAX_SPORTS) { std::printf("ERROR DATA!\r\nstournament sport_id out of MAX_SPORTS in run simple%d\r\n", _tournament->sport_id); continue; }

						if (sports_id[_tournament->sport_id] == NULL) { std::printf("Sport not found in run simple. Run getSports. sport_id=%d\r\n", _tournament->sport_id); getSports(); }


						if (print == true) {
							std::printf("\r\n***************************************************\r\n");
							std::printf("Simple id: %d\r\n", event_id);
							std::printf("NAME:"); std::printf(_tournament->name);
							std::printf("\r\n");
						}

						if (print == true) {
							std::printf(sports_id[_tournament->sport_id]->name); std::printf("\r\n");
						}


						if (_tournament->category_id >= MAX_CATEGORIES) { std::printf("ERROR DATA!\r\ntournament category_id out of MAX_CATEGORIES in run simple %d\r\n", _tournament->category_id); continue; }
						if (categories_id[_tournament->category_id] == NULL) {
							std::printf("Category not found. Run getTournament(). category_id=%d\r\n", _tournament->category_id);
							if (getTournament(simples_id[_tournament->simple_id], false) == -1);  continue;;
						}
						if (print == true) {
							std::printf(categories_id[_tournament->category_id]->name); std::printf("\r\n");
							std::printf("\r\n***************************************************\r\n");
						}


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
								if (market_node->first_attribute("next_betstop")) _line->next_betstop = atoi(market_node->first_attribute("next_betstop")->value());
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
									if (_line->specifier[q] != NULL) delete[] _line->specifier[q];
									if (_line->specifier_value[q] != NULL)  delete[] _line->specifier_value[q];
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
											//printf(_line->extended_specifier[q]); printf("\r\n"); printf(_line->extended_specifier_value[q]); printf("\r\n");


										}
									}
								}
								if (_line->variant > -1) {
									z = strlen(_line->specifier_value[_line->variant]) + 1; if (strcmp(_line->specifier[_line->variant], "variant") != 0) { std::printf(_line->specifier[_line->variant]); std::printf("\r\n"); }
									for (u = 0; u < max_markets_in[_line->market_id]; u++) if (markets_id[_line->market_id][u] != NULL && markets_id[_line->market_id][u]->variable_text != NULL && std::strcmp(_line->specifier_value[_line->variant], markets_id[_line->market_id][u]->variable_text) == 0) break;
									if (u == max_markets_in[_line->market_id]) {
										std::printf("Variant market not found in run market_id=%d variant=", _line->market_id);  std::printf(_line->specifier_value[_line->variant]);  std::printf("  getVariantMarkets\r\n"); if (getVariantMarkets(markets_id[_line->market_id][0], _line->specifier_value[_line->variant]) == -1) { std::printf("variant market not found "); continue; }
										for (u = 0; u < max_markets_in[_line->market_id]; u++) if (markets_id[_line->market_id][u] != NULL && markets_id[_line->market_id][u]->variable_text != NULL && std::strcmp(_line->specifier_value[_line->variant], markets_id[_line->market_id][u]->variable_text) == 0) break;
									}
									_line->market = markets_id[_line->market_id][u];
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
												std::printf("_line->type=%d line->market_id=%d  _tournament->race=%d  _line->simple_id =%d \r\n", _line->type, _line->market_id, _tournament->race, _line->simple_id); std::printf(outcome_node->first_attribute("id")->value());

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



										}

										if (_line->type == 1) {
											if (_line->outcome_id[i] >= MAX_PLAYERS) {
												std::printf("ERROR in run. player_id out of MAX_PLAYERS. _line->outcome_id[i]=%d  _line->market_id=%d simple_id=%d\r\n", _line->outcome_id[i], _line->market_id, _line->simple_id);
												continue;

											}
											if (_line->outcome_team[i] != 3) {
												if (players_id[_line->outcome_id[i]] == NULL) {
													std::printf("Player id=%d not found in market id=%d in simple_id=%d  in run function . getPlayer\r\n", _line->outcome_id[i], _line->market_id, _line->simple_id);
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



										}


									}





								}


							}
						}














					}
				if (race == 3) {
					if(event_id>=MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nsseason id out of MAX_TOURNAMENTS in run %d\r\n", event_id); continue; }
					if (seasons_id[event_id] == NULL) {
						std::printf("Tournament not found. Run getTournament(). season_id=%d\r\n", event_id);
						tournaments[tournaments_l].id = 0;
						tournaments[tournaments_l].season_id = event_id;
						tournaments[tournaments_l].race = 0;
						if (getTournament(&tournaments[tournaments_l], false) == -1) { std::printf("ERROR!\r\nTournaments season id not found in run season %d\r\n", event_id); continue; }
						else tournaments_l++;
					}
						if (seasons_id[event_id] == NULL) { std::printf("ERROR!\r\nTournaments season id not found after succes in getTournament run season %d\r\n", event_id); continue; }
						_tournament = seasons_id[event_id];

						if (_tournament->sport_id >= MAX_SPORTS) { std::printf("ERROR DATA!\r\nstournament sport_id out of MAX_SPORTS in run season%d\r\n", _tournament->sport_id); continue; }
						
						if (sports_id[_tournament->sport_id] == NULL) { std::printf("Sport not found in run season. Run getSports. sport_id=%d\r\n", _tournament->sport_id); getSports(); }


						if (print == true) {
							std::printf("\r\n***************************************************\r\n");
							std::printf("Season id: %d\r\n",event_id);
							std::printf("Tournament id:%d\r\n", _tournament->id);
							std::printf("NAME:"); std::printf(_tournament->name); 
							std::printf("\r\nSEASON:"); std::printf(_tournament->season_name);
							std::printf("\r\n");
						}

						if (print == true) {
							std::printf(sports_id[_tournament->sport_id]->name); std::printf("\r\n");
						}


						if (_tournament->category_id >= MAX_CATEGORIES) { std::printf("ERROR DATA!\r\ntournament category_id out of MAX_CATEGORIES in run season %d\r\n", _tournament->category_id); continue; }
						if (categories_id[_tournament->category_id] == NULL) {
							std::printf("Category not found. Run getTournament(). category_id=%d\r\n", _tournament->category_id);
							if (getTournament(tournaments_id[_tournament->id], false) == -1);  continue;;
						}
						if (print == true) {
							std::printf(categories_id[_tournament->category_id]->name); std::printf("\r\n");
							std::printf("\r\n***************************************************\r\n");
						}


						xml_node<> * odds = doc.first_node()->first_node("odds");
						
						if (odds != NULL) {
							betstop_reason=0;

							if (odds->first_attribute("betstop_reason")) betstop_reason = atoi(odds->first_attribute("betstop_reason")->value());
							_line->tournament_id = _tournament->id;
							_line->event_id = 0;
							_line->simple_id = 0;
							_line->betstop_reason = betstop_reason;

							for (xml_node<> * market_node = odds->first_node("market"); market_node; market_node = market_node->next_sibling())
							{
								if (market_node->first_attribute("next_betstop")) _line->next_betstop = atoi(market_node->first_attribute("next_betstop")->value());
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
									if (_line->specifier[q] != NULL) delete[] _line->specifier[q];
									if (_line->specifier_value[q] != NULL)  delete[] _line->specifier_value[q];
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
											//printf(_line->extended_specifier[q]); printf("\r\n"); printf(_line->extended_specifier_value[q]); printf("\r\n");


										}
									}
								}
								if (_line->variant > -1) {
									z = strlen(_line->specifier_value[_line->variant]) + 1; if (strcmp(_line->specifier[_line->variant], "variant") != 0) { std::printf(_line->specifier[_line->variant]); std::printf("\r\n"); }
									for (u = 0; u < max_markets_in[_line->market_id]; u++) if (markets_id[_line->market_id][u] != NULL && markets_id[_line->market_id][u]->variable_text != NULL && std::strcmp(_line->specifier_value[_line->variant], markets_id[_line->market_id][u]->variable_text) == 0) break;
									if (u == max_markets_in[_line->market_id]) {
										std::printf("Variant market not found in run market_id=%d variant=", _line->market_id);  std::printf(_line->specifier_value[_line->variant]);  std::printf("  getVariantMarkets\r\n"); if (getVariantMarkets(markets_id[_line->market_id][0], _line->specifier_value[_line->variant]) == -1) { std::printf("variant market not found "); continue; }
										for (u = 0; u < max_markets_in[_line->market_id]; u++) if (markets_id[_line->market_id][u] != NULL && markets_id[_line->market_id][u]->variable_text != NULL && std::strcmp(_line->specifier_value[_line->variant], markets_id[_line->market_id][u]->variable_text) == 0) break;
									}
									_line->market = markets_id[_line->market_id][u];
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
												std::printf("_line->type=%d line->market_id=%d  _tournament->race=%d  _line->tournament_id =%d \r\n", _line->type, _line->market_id, _tournament->race, _line->tournament_id); std::printf(outcome_node->first_attribute("id")->value());

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
											}

											for (int j = 0; j < _line->specifier_number; j++) {
												if (j == _line->variant) continue;

												replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
											}
                                           if(tournaments_id[_line->tournament_id]->season_name !=NULL) replace(_line->outcome_name[i], "$event", tournaments_id[_line->tournament_id]->season_name);



											if (print == true) {

												std::printf(_line->outcome_name[i]); std::printf("\t");
												std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
												std::printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
											}



										}

										if (_line->type == 1) {
											if (_line->outcome_id[i] >= MAX_PLAYERS) {
												std::printf("ERROR in run. player_id out of MAX_PLAYERS. _line->outcome_id[i]=%d  _line->market_id=%d tournament_id=%d\r\n", _line->outcome_id[i], _line->market_id, _line->tournament_id);
												continue;

											}
											if(_line->outcome_team[i] != 3){
											if (players_id[_line->outcome_id[i]] == NULL) {
												std::printf("Player id=%d not found in market id=%d in tournament_id=%d  in run function . getPlayer\r\n", _line->outcome_id[i], _line->market_id, _line->tournament_id);
												players[players_l].id = _line->outcome_id[i]; if (getPlayer(&players[players_l]) == -1)
												{
													std::printf("error player id=%d  not found \r\n ", _line->outcome_id[i]); //continue;
													_line->outcome_name[i] = new char[2];
													std::strcpy(_line->outcome_name[i], " ");
												} else players_l++;
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

											if(tournaments_id[_line->tournament_id]->season_name!=NULL)	replace(_line->outcome_name[i], "$event", tournaments_id[_line->tournament_id]->season_name);
											
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
													
													if (_tournament->season_name!=NULL) replace(_line->outcome_name[i], "$event", tournaments_id[_line->tournament_id]->season_name);
												}
												else { _line->outcome_name[i] = new char[2]; std::strcpy(_line->outcome_name[i], " "); }
											}
											if (print == true) {
												std::printf(_line->outcome_name[i]); std::printf("\t");
												std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
												printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
											}
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



										}


									}





								}


							}
						}
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				}
				if (race < 2) {
					if (event_id >= MAX_EVENTS) { std::printf("ERROR DATA!\r\nsevent id out of MAX_EVENTS in run %d\r\n", event_id); continue; }
					if (events_id[event_id] == NULL) {
						std::printf("Event not found. Run getFixture to get event_id=%d race=%d\r\n", event_id, race);
						events[events_l].id = event_id;
						events[events_l].race = race; 
						if (getEventFixture(&events[events_l]) == -1) { std::printf("ERROR!\r\n getEventFixture error return in run %d .\r\n", event_id); continue; }
						events_l++;

					}

					_event = events_id[event_id];


					if (print == true) {
						std::printf("\r\n***************************************************\r\n");
						std::printf("%d\r\n", _event->id);
						std::printf(_event->home_name); if (_event->away_name != NULL) { std::printf(" - ");  std::printf(_event->away_name); }
						std::printf("\r\n");
					}
					if (_event->sport_id >= MAX_SPORTS) { std::printf("ERROR DATA!\r\nsevent sport_id out of MAX_SPORTS in run %d\r\n", _event->sport_id); continue; }
					if (sports_id[_event->sport_id] == NULL) { std::printf("Sport not found. Run getSports. sport_id=%d\r\n", _event->sport_id); getSports(); }
					if (print == true) {
						std::printf(sports_id[_event->sport_id]->name); std::printf("\r\n");
					}
					if (_event->tournament_id >= MAX_TOURNAMENTS) { std::printf("ERROR DATA!\r\nsevent tournament_id out of MAX_TOURNAMENTS in run %d\r\n", _event->tournament_id); continue; }
					if (_event->race==0 && tournaments_id[_event->tournament_id] == NULL) {
						std::printf("Tournament not found. Run getTournament(). tournament_id=%d\r\n", _event->tournament_id);
						tournaments[tournaments_l].id = _event->tournament_id;
						tournaments[tournaments_l].race = _event->race;
						if (getTournament(&tournaments[tournaments_l], true) == -1) { std::printf("ERROR!\r\nTournaments not found in run %d . Run getEventFixture\r\n", _event->tournament_id); if (getEventFixture(_event) == -1) { std::printf("ERROR!\r\n getEventFixture error return in run %d .\r\n", _event->id); continue; } }
						else tournaments_l++;


					}
					if (_event->race == 2 && simples_id[_event->tournament_id] == NULL) {
						std::printf("Simple Tournament not found. Run getTournament(). simples_id=%d\r\n", _event->tournament_id);
						tournaments[tournaments_l].simple_id = _event->tournament_id;
						tournaments[tournaments_l].id = 0;
						tournaments[tournaments_l].race = _event->race;
						if (getTournament(&tournaments[tournaments_l], true) == -1) { std::printf("ERROR!\r\nSimple Tournaments not found in run %d . Run getEventFixture\r\n", _event->tournament_id); if (getEventFixture(_event) == -1) { std::printf("ERROR!\r\n getEventFixture error return in run %d .\r\n", _event->id); continue; } }
						else tournaments_l++;


					}


					if (print == true) {
						if(_event->race==0) std::printf(tournaments_id[_event->tournament_id]->name);
						if (_event->race == 2) std::printf(simples_id[_event->tournament_id]->name);
						std::printf("\r\n");
					}

					if (_event->category_id >= MAX_CATEGORIES) { std::printf("ERROR DATA!\r\nsevent category_id out of MAX_CATEGORIES in run %d\r\n", _event->category_id); continue; }
					if (categories_id[_event->category_id] == NULL) {
						std::printf("Category not found. Run getTournament(). category_id=%d\r\n", _event->category_id);
						if (_event->race == 0) {
							if (getTournament(tournaments_id[_event->tournament_id], false) == -1) if (getEventFixture(_event) == -1) continue;;
						}
						if (_event->race == 2) {
							if (getTournament(simples_id[_event->tournament_id], false) == -1) if (getEventFixture(_event) == -1) continue;;
						}


					}
					if (print == true) {
						std::printf(categories_id[_event->category_id]->name); std::printf("\r\n");
						std::printf("\r\n***************************************************\r\n");
					}

					if (doc.first_node()->first_attribute("timestamp")) _event->timestamp = atoi(doc.first_node()->first_attribute("timestamp")->value());

					xml_node<> * sport_event_status = doc.first_node()->first_node("sport_event_status");
					if (sport_event_status != NULL) {
						if (sport_event_status->first_attribute("status")) _event->status = atoi(sport_event_status->first_attribute("status")->value());
						if (sport_event_status->first_attribute("possession")) _event->possession = atoi(sport_event_status->first_attribute("possession")->value());
						if (sport_event_status->first_attribute("try")) _event->try_num = atoi(sport_event_status->first_attribute("try")->value());
						if (sport_event_status->first_attribute("throw")) _event->throw_num = atoi(sport_event_status->first_attribute("throw")->value());
						if (sport_event_status->first_attribute("delivery")) _event->delivery = atoi(sport_event_status->first_attribute("delivery")->value());
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

						if (sport_event_status->first_attribute("expedite_mode") && sport_event_status->first_attribute("expedite_mode")->value()[0] == 't' && sport_event_status->first_attribute("expedite_mode")->value()[1] == 'r')  _event->expedite = 1;
						if (sport_event_status->first_attribute("expedite_mode") && sport_event_status->first_attribute("expedite_mode")->value()[0] == 'f' && sport_event_status->first_attribute("expedite_mode")->value()[1] == 'a')  _event->expedite = 0;




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
						std::printf("away_score=%g ", _event->away_score); std::printf("home_yellowcards=%d ", _event->home_yellowcards); std::printf("away_yellowcards=%d ", _event->away_yellowcards); std::printf("home_redcards=%d ", _event->home_redcards); std::printf("away_redcards=%d ", _event->away_redcards); std::printf("expedite_mode=%d ", _event->expedite); std::printf("tiebreak=%d ", _event->tiebreak); std::printf("outs=%d ", _event->outs); std::printf("strikes=%d ", _event->strikes); std::printf("balls=%d ", _event->balls);  std::printf("home_remaining_bowls=%d ", _event->home_remaining_bowls);
						std::printf("away_remaining_bowls=%d ", _event->away_remaining_bowls); std::printf("home_batter=%d ", _event->home_batter); std::printf("awway_batter=%d ", _event->away_batter); std::printf("winner_id=%d ", _event->winner_id); std::printf("home_suspend=%d ", _event->home_suspend); std::printf("away_suspend=%d ", _event->away_suspend); std::printf("match_status=%d ", _event->match_status); std::printf("remaining_reds=%d ", _event->remaining_reds); std::printf("reporting=%d ", _event->reporting); std::printf("position=%d ", _event->position); std::printf("home_gamescore=%d ", _event->home_gamescore); std::printf("away_gamescore=%d ", _event->away_gamescore); std::printf("visit=%d ", _event->visit); std::printf("home_dismissals=%d ", _event->home_dismissals); std::printf("away_dismissals=%d ", _event->away_dismissals); std::printf("home_penalty_runs=%d ", _event->home_penalty_runs);	std::printf("away_penalty_runs=%d ", _event->away_penalty_runs);
						std::printf("over=%d ", _event->over); std::printf("try_num=%d ", _event->try_num); std::printf("trow_num=%d ", _event->throw_num);
						std::printf("delivery=%d ", _event->delivery); std::printf("yards=%d ", _event->yards); std::printf("current_server=%d ", _event->current_server);
						std::printf("innings=%d ", _event->innings);
						std::printf("\r\n\r\n");
					}

					xml_node<> * odds = doc.first_node()->first_node("odds");



					if (odds != NULL) {
						betstop_reason = 0;
						if (odds->first_attribute("betstop_reason")) betstop_reason = atoi(odds->first_attribute("betstop_reason")->value());
						_line->betstop_reason = betstop_reason;
						_line->event_id = event_id;
						_line->tournament_id = 0;
						_line->simple_id = 0;
						for (xml_node<> * market_node = odds->first_node("market"); market_node; market_node = market_node->next_sibling())
						{
							if (market_node->first_attribute("next_betstop")) _line->next_betstop = atoi(market_node->first_attribute("next_betstop")->value());
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
								if (_line->specifier[q] != NULL) delete[] _line->specifier[q];
								if (_line->specifier_value[q] != NULL)  delete[] _line->specifier_value[q];
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
										//printf(_line->extended_specifier[q]); printf("\r\n"); printf(_line->extended_specifier_value[q]); printf("\r\n");


									}
								}
							}
							if (_line->variant > -1) {
								z = strlen(_line->specifier_value[_line->variant]) + 1; if (strcmp(_line->specifier[_line->variant], "variant") != 0) { std::printf(_line->specifier[_line->variant]); std::printf("\r\n"); }
								for (u = 0; u < max_markets_in[_line->market_id]; u++) if (markets_id[_line->market_id][u] != NULL && markets_id[_line->market_id][u]->variable_text != NULL && std::strcmp(_line->specifier_value[_line->variant], markets_id[_line->market_id][u]->variable_text) == 0) break;
								if (u == max_markets_in[_line->market_id]) {
									std::printf("Variant market not found in run market_id=%d variant=", _line->market_id);  std::printf(_line->specifier_value[_line->variant]);  std::printf("  getVariantMarkets\r\n"); if (getVariantMarkets(markets_id[_line->market_id][0], _line->specifier_value[_line->variant]) == -1) { std::printf("variant market not found "); continue; }
									for (u = 0; u < max_markets_in[_line->market_id]; u++) if (markets_id[_line->market_id][u] != NULL && markets_id[_line->market_id][u]->variable_text != NULL && std::strcmp(_line->specifier_value[_line->variant], markets_id[_line->market_id][u]->variable_text) == 0) break;
								}
								_line->market = markets_id[_line->market_id][u];
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
											std::printf("_line->type=%d line->market_id=%d  _event->race=%d  _line->event_id =%d \r\n", _line->type, _line->market_id, _event->race, _line->event_id); std::printf(outcome_node->first_attribute("id")->value());

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
								if (_event->race > 0) replace(_line->name, "$event", events_id[_line->event_id]->home_name);


								if (print == true) {

									std::printf("\r\n"); std::printf(_line->name); std::printf("\r\n"); std::printf("------------------------------------------------------------------------------\r\n");
								}





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
										}

										for (int j = 0; j < _line->specifier_number; j++) {
											if (j == _line->variant) continue;

											replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
										}

										replace(_line->outcome_name[i], "$competitor1", events_id[_line->event_id]->home_name);
										if (_event->away_name != NULL) replace(_line->outcome_name[i], "$competitor2", events_id[_line->event_id]->away_name);
										if (_event->race > 0) replace(_line->outcome_name[i], "$event", events_id[_line->event_id]->home_name);



										if (print == true) {

											std::printf(_line->outcome_name[i]); std::printf("\t");
											std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
											std::printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
										}



									}

									if (_line->type == 1) {
										if (_line->outcome_id[i] >= MAX_PLAYERS) {
											std::printf("ERROR in run. player_id out of MAX_PLAYERS. _line->outcome_id[i]=%d  _line->market_id=%d event_id=%d\r\n", _line->outcome_id[i], _line->market_id, _line->event_id);
											continue;

										}

										if (players_id[_line->outcome_id[i]] == NULL && _line->outcome_team[i] == 2) {
											std::printf("Player id=%d not found in market id=%d in event_id=%d  in run function team 2 \r\n", _line->outcome_id[i], _line->market_id, _line->event_id);
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
											std::printf("Player id=%d not found in market id=%d in event_id=%d  in run function team 1 \r\n", _line->outcome_id[i], _line->market_id, _line->event_id);
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
											std::printf("Player id=%d  not found in run after get competitor. getPlayer\r\n ", _line->outcome_id[i]);
											players[players_l].id = _line->outcome_id[i]; if (getPlayer(&players[players_l]) == -1)
											{
												std::printf("error player id=%d  not found \r\n ", _line->outcome_id[i]); //continue;
												_line->outcome_name[i] = new char[2];
												std::strcpy(_line->outcome_name[i], " ");
											} else players_l++;
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
												if (_event->race > 0) replace(_line->outcome_name[i], "$event", events_id[_line->event_id]->home_name);



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
												//tournaments[tournaments_l].race = _event->race;
											
												if (_event->race == 0 && getTournament(tournaments_id[_event->tournament_id], false) == -1)
													std::printf("ERROR!\r\nTournaments not found in run %d \r\n", _event->tournament_id);
											
												if (_event->race == 2 && getTournament(simples_id[_event->tournament_id], false) == -1)
													std::printf("ERROR!\r\nSimples Tournaments not found in run %d \r\n", _event->tournament_id);
											
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
												if (_event->race > 0) replace(_line->outcome_name[i], "$event", events_id[_line->event_id]->home_name);
											}
											else { _line->outcome_name[i] = new char[2]; std::strcpy(_line->outcome_name[i], " "); }
										}
										if (print == true) {
											std::printf(_line->outcome_name[i]); std::printf("\t");
											std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
											printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
										}
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
										}

										for (int j = 0; j < _line->specifier_number; j++) {
											if (j == _line->variant) continue;

											replace(_line->outcome_name[i], _line->specifier[j], _line->specifier_value[j]);
										}

										replace(_line->outcome_name[i], "$competitor1", events_id[_line->event_id]->home_name);
										replace(_line->outcome_name[i], "$competitor2", events_id[_line->event_id]->away_name);
										if (_event->race > 0) replace(_line->outcome_name[i], "$event", events_id[_line->event_id]->home_name);


										//if (_line->market_id == 188 || _line->market_id == 224 || _line->market_id == 485 || _line->market_id == 231 || _line->market_id == 65 || _line->market_id == 383 || _line->market_id == 66) 

										if (print == true) {

											std::printf(_line->outcome_name[i]); std::printf("\t");
											std::printf("odds=%g", _line->outcome_odds[i]); std::printf("  \t");
											printf("probabilitie=%g\r\n", _line->outcome_probabilities[i]);
										}



									}


								}





							}


						}
					}
				}

}
		
		
		
		else {
			printf(doc.first_node()->name()); printf("\r\n");
		}

		



		
		root_node = doc.first_node("odds_change");
		if (root_node && root_node->first_node("sport_event_status") && root_node->first_node("sport_event_status")->first_attribute("status")) {
		
		//	printf(root_node->first_node("sport_event_status")->first_attribute("status")->value());

		status=atoi(root_node->first_node("sport_event_status")->first_attribute("status")->value());
			
		}


		
		//if (i < 100 && _event->sport_id == 21 && (envelope.message.body.len > 8000 || status == 1))


		if (i < 100 && status == 1 && (_event->away_yellowcards>0 || _event->away_redcards>0 || _event->home_yellowcards>0 || _event->home_redcards>0)) {
			i++;std::strcpy(name, "D://unifeed");
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
		//WriteFile(File, "<endmessage></endmessage>", strlen("<endmessage></endmessage>"), &l, NULL);

		//if (i > 50) return;

		//if(i<4) printf((char*)envelope.message.body.bytes);
		//i++;

		

		if (AMQP_RESPONSE_NORMAL != ret.reply_type) {
			if (AMQP_RESPONSE_LIBRARY_EXCEPTION == ret.reply_type &&
				AMQP_STATUS_UNEXPECTED_STATE == ret.library_error) {
				if (AMQP_STATUS_OK != amqp_simple_wait_frame(conn, &frame)) {
					
					delete[] outcome_name;
					delete[] outcome_id;
					delete[] outcome_active;
					delete[] outcome_team;
					delete[] outcome_probabilities;
					delete[] outcome_odds;
					delete[] name;
					delete[] buf;
					delete[] maxbuf;

					
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
							delete[] outcome_team;
							delete[] outcome_name;
							delete[] outcome_id;
							delete[] outcome_active;
							delete[] outcome_probabilities;
							delete[] outcome_odds;
							delete[] name;
							delete[] buf;
							delete[] maxbuf;
							
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

						delete[] outcome_team;
						delete[] outcome_name;
						delete[] outcome_id;
						delete[] outcome_active;
						delete[] outcome_probabilities ;
						delete[] outcome_odds;
						delete[] name;
						delete[] buf;
						delete[] maxbuf;

						return;

					case AMQP_CONNECTION_CLOSE_METHOD:
						/* a connection.close method happens when a connection exception occurs,
						* this can happen by trying to use a channel that isn't open for example.
						*
						* In this case the whole connection must be restarted.
						*/
						delete[] outcome_team;
						delete[] outcome_name;
						delete[] outcome_id;
						delete[] outcome_active;
						delete[] outcome_probabilities;
						delete[] outcome_odds;
						delete[] name;
						delete[] buf;
						delete[] maxbuf;


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











