#ifndef TRACK_DEF_H
#define TRACK_DEF_H
#define NOT_FOUND (-1)

typedef struct
{
	char* name;
	char* artist;
	char* category;
	float length;
	char* album;
	int num;
} Track;

#endif
