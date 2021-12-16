#include "Jerry.h"
#include <ctype.h>

Jerry* initJerry( char *id, int happiness, Origin *origin){
	Jerry* J = (Jerry*)malloc(sizeof(Jerry));
	if(J == NULL){
		printf("Memory Problem");
		exit(1);
	}
	J->id = (char *) malloc(strlen(id)+1);
	if(J->id == NULL){
		printf("Memory Problem");
		exit(1);
	}
	strcpy(J->id,id);
	J->happiness = happiness;
	J->origin = origin;
	J->ph_char = NULL;
	J->char_num = 0;
	return J;
}
status deleteJerryPointer(Jerry *J){
	return success;
}

Jerry* getJerryPointer(Jerry *J){
	return J;
}

status deleteJerry(Jerry *J){
	if (J == NULL){
		return failure;
	}
	else{
		if (J->char_num != 0){
			int temp = J->char_num;
			for(int i = 0; i < temp; i++){
				removePC(J, J->ph_char[0]->name);
			}
		}
		deleteOrigin(J->origin);
		free(J->id);
		free(J);
		return success;
	}
}

Jerry* copyJerry(Jerry *J){
	if(J == NULL){
		return NULL;
	}
	Jerry* newJerry = (Jerry*)malloc(sizeof(Jerry));
	if(newJerry == NULL){
		printf("Memory Problem");
		exit(1);
	}
	*newJerry = (Jerry) *J;
	return newJerry;
}

bool equalJerry(Jerry *J1, Jerry *J2){
	if(J1 == NULL || J2 == NULL){
		return false;
	}
	if(strcmp(J1->id,J2->id) == 0){
		return true;
	}
	return false;
}

bool equalJerryKey(Jerry *J, char *JerryId){
	if(J == NULL || JerryId == NULL){
		return false;
	}
	if(strcmp(J->id,JerryId) == 0){
		return true;
	}
	return false;
}


planet* initplanet( char *name, float x, float y, float z){
	planet* P = (planet*)malloc(sizeof(planet));
	if(P == NULL){
		printf("Memory Problem");
		exit(1);
	}
	P->name = (char *) malloc(strlen(name)+1);
	if(P->name == NULL){
		printf("Memory Problem");
		exit(1);
	}
	strcpy(P->name,name);
	P->x = x;
	P->y = y;
	P->z = z;
	return P;
}

status deleteplanet(planet *P){
	if (P == NULL){
		return failure;
	}
	free(P->name);
	free(P);
	return success;
}

planet* findPlanet(planet **planets, int size, char *planet){
	if(planets == NULL){
		return NULL;
	}
	for(int i=0; i<size; i++){
		if(strcmp(planets[i]->name,planet) == 0){
			return planets[i];
		}
	}
	return NULL;
}

PhysicalCharacteristics* initPhysicalCharacteristics(char *name,  float val){
	PhysicalCharacteristics* PC = (PhysicalCharacteristics*) malloc(sizeof(PhysicalCharacteristics));
	if(PC == NULL){
		printf("Memory Problem");
		exit(1);
	}
	PC->val = val;
	PC->name = (char *) malloc(strlen(name)+1);
	if(PC->name == NULL){
		printf("Memory Problem");
		exit(1);
	}
	strcpy(PC->name,name);
	return PC;
}

Origin* initOrigin(planet *home_planet ,char *dim_name){
	Origin* O = (Origin*)malloc(sizeof(Origin));
	if(O == NULL){
		printf("Memory Problem");
		exit(1);
	}
	O->dim_name = (char *) malloc(strlen(dim_name)+1);
	if(O->dim_name == NULL){
		printf("Memory Problem");
		exit(1);
	}
	strcpy(O->dim_name,dim_name);
	O->home_planet = home_planet;
	return O;
}

status deleteOrigin(Origin *O){
	if (O == NULL){
		return failure;
	}
	free(O->dim_name);
	free(O);
	return success;
}


bool checkPC(Jerry *J, char *PC_name){
	for (int i = 0; i < J->char_num; i++){
		if (strcmp(J->ph_char[i]->name,PC_name) == 0){
			return true;
		}
	}
	return false;
}

status addPC(Jerry *J, char *PC_name,  float PC_val){
	if (J == NULL){
		return failure;
	}
	else if (J->char_num == 0){
		J->ph_char = (PhysicalCharacteristics**) malloc(sizeof(PhysicalCharacteristics*));
		if(J->ph_char == NULL){
			printf("Memory Problem");
			exit(1);
		}
		J->ph_char[0] = initPhysicalCharacteristics(PC_name, PC_val);
		J->char_num = 1;
		return success;
	}
	else if (checkPC(J,PC_name) == true){
		return failure;
	}
	else{
		J->char_num +=1;
		J->ph_char = (PhysicalCharacteristics**) realloc(J->ph_char, ((J->char_num) * sizeof(PhysicalCharacteristics*)));
		if(J->ph_char == NULL){
			printf("Memory Problem");
			exit(1);
		}
		J->ph_char[J->char_num-1] = initPhysicalCharacteristics(PC_name, PC_val);
		return success;
		}
	}


status removePC(Jerry* J,char *PC_name){
	if (J == NULL){
		return failure;
	}
	else if (checkPC(J,PC_name) == false){
		return failure;
	}
	else{
		PhysicalCharacteristics* temp;
		for (int i = 0; i < J->char_num; i++){
			if (strcmp(J->ph_char[i]->name,PC_name) == 0){
				temp = J->ph_char[i];
				for (int j = i; j < J->char_num - 1; j++){
					J->ph_char[j] = J->ph_char[j+1];
				}
				free(temp->name);
				free(temp);
				J->char_num -=1;
				J->ph_char = (PhysicalCharacteristics**) realloc(J->ph_char, (J->char_num) * sizeof(PhysicalCharacteristics*));
				if(J->ph_char == NULL && J->char_num != 0){
					printf("Memory Problem");
					exit(1);
				}
				break;
			}
		}

		return success;
	}
}



status printplanet(planet* P){
	if (P == NULL){
		return failure;
		}
	printf("Planet : %s (%0.2f,%0.2f,%0.2f) \n", P->name , P->x , P->y, P->z);
	return success;
}

status printJerry(Jerry* J){
	if (J == NULL){
		return failure;
	}
	printf("Jerry , ID - %s : \n", J->id);
	printf("Happiness level : %d \n", J->happiness);
	printf("Origin : %s \n", J->origin->dim_name);
	printplanet(J->origin->home_planet);
	if (J->ph_char != NULL){
		printf("Jerry's physical Characteristics available : \n\t");
		for (int i = 0; i < J->char_num; i++){
			if (i == J->char_num - 1){
				printf("%s : %0.2f \n", J->ph_char[i]->name, J->ph_char[i]->val);
			}
			else{
				printf("%s : %0.2f , ", J->ph_char[i]->name, J->ph_char[i]->val);
				}
			}
	}
	return success;
}

float getJerryPcVal(Jerry* J, char *PC_name){
	for (int i = 0; i < J->char_num; i++){
		if (strcmp(J->ph_char[i]->name,PC_name) == 0){
			return (float) J->ph_char[i]->val;
		}
	}
	return -1;
}




int PcNameHashFunc(char *PcName1){
	int res = 0;
	int j = 0;
	while (PcName1[j]) {
		res += (int) PcName1[j];
		j += 1;
	}
	return res;
}


int JerryIdHashFunc(char* JerryId){
	int res = 0;
	int j = 0;
	while (JerryId[j]) {
		res += (int) JerryId[j];
		j += 1;
	}
	return res;
}

status printJerryId(char* JerryId){
	if (JerryId == NULL){
		return failure;
	}
	printf("%s \n",JerryId);
	return success;
}

char* copyJerryId(char* JerryId){
	if (JerryId == NULL){
		return NULL;
	}
	char* newStr = (char *) malloc(strlen(JerryId)+1);
	if(newStr == NULL){
		printf("Memory Problem");
		exit(1);
	}
	strcpy(newStr, JerryId);
	return newStr;
}

status deleteJerryId(char* JerryId){
	if (JerryId == NULL){
		return failure;
	}
	free(JerryId);
	return success;
}

bool equalJerryId(char* JerryId1, char* JerryId2){
	if (JerryId1 == NULL || JerryId2 == NULL){
		return false;
	}
	if(strcmp(JerryId1,JerryId2) == 0){
		return true;
	}
	return false;
}

status printPcName(char *PcName){
	if (PcName == NULL){
		return failure;
	}
	printf("%s : \n",PcName);
	return success;
}

char* copyPcName(char *PcName){
	if (PcName == NULL){
		return NULL;
	}
	char* newStr = (char *) malloc(strlen(PcName)+1);
	if(newStr == NULL){
		printf("Memory Problem");
		exit(1);
	}
	strcpy(newStr, PcName);
	return newStr;
}

status deletePcName(char *PcName){
	if (PcName == NULL){
		return failure;
	}
	free(PcName);
	return success;
}

bool equalPcName(char *PcName1, char *PcName2){
	if (PcName1 == NULL || PcName2 == NULL){
		return false;
	}
	if(strcmp(PcName1,PcName2) == 0){
		return true;
	}
	return false;
}

