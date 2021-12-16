#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Defs.h"

#ifndef SRC_JERRY_H_
#define SRC_JERRY_H_

typedef struct planet_t{
	char *name;
	float  x,y,z;
}planet;

typedef struct Origin_t{
	planet *home_planet;
	char *dim_name;
}Origin;

typedef struct PhysicalCharacteristics_t{
	char *name;
	float val;
}PhysicalCharacteristics;

typedef struct Jerry_t{
	char *id;
	int  happiness;
	Origin *origin;
	PhysicalCharacteristics **ph_char;
	int char_num;
}Jerry;

Jerry* initJerry( char *id, int happiness, Origin *origin);
Jerry* copyJerry(Jerry *J);
bool equalJerry(Jerry *J1, Jerry *J2);
bool equalJerryKey(Jerry *J, char *JerryId);
status deleteJerry(Jerry *J);
status printJerry(Jerry* J);
status deleteJerryPointer(Jerry *J);
Jerry* getJerryPointer(Jerry *J);

status printJerryId(char *JerryId);
char* copyJerryId(char *JerryId);
status deleteJerryId(char *JerryId);
bool equalJerryId(char *JerryId1, char *JerryId2);
int JerryIdHashFunc(char* JerryId);

planet* initplanet( char *name, float x, float y, float z);
status deleteplanet(planet *p);
status printplanet(planet *P);
planet* findPlanet(planet **planets, int size, char *planet);

Origin* initOrigin(planet *home_planet ,char *dim_name);
status deleteOrigin(Origin *O);

PhysicalCharacteristics* initPhysicalCharacteristics(char *name,  float val);
bool checkPC(Jerry*, char *PC_name);
status addPC(Jerry*,char *PC_name,  float PC_val);
status removePC(Jerry*,char *PC_name);
float getJerryPcVal(Jerry*, char *PC_name);

status printPcName(char *PcName);
char* copyPcName(char *PcName);
status deletePcName(char *PcName);
bool equalPcName(char *PcName1, char *PcName2);
int PcNameHashFunc(char *PcName1);


#endif /* SRC_JERRY_H_ */
