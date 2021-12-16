#include "MultiValueHashTable.h"
#include "Jerry.h"
#include <string.h>


int main(int argc, char *argv[])
{
	int numberofchar = 0;
	int numberOfplanets = atoi(argv[1]);
	FILE *fptr;
	if ((fptr = fopen(argv[2],"r")) == NULL){
		printf("Error reading file \n");
		exit(1);
	}
	else{
		planet **planets = (planet**) calloc(numberOfplanets , sizeof(planet*));
		if(planets == NULL){
			printf("Memory Problem");
			exit(1);
		}
		LinkedList jerries = createLinkedList((CopyFunction) copyJerry, (FreeFunction) deleteJerry, (EqualFunction) equalJerry,
				(EqualFunction) equalJerryKey, (PrintFunction) printJerry);
		char str[300];
		char **planetinfo = (char**) calloc(4,sizeof(char*));
		if(planetinfo == NULL){
			printf("Memory Problem");
			exit(1);
		}
		char **jerryinfo = (char**) calloc(4,sizeof(char*));
		if(jerryinfo == NULL){
			printf("Memory Problem");
			exit(1);
		}
		char **PCinfo = (char**) calloc(2,sizeof(char*));
		if(PCinfo == NULL){
			printf("Memory Problem");
			exit(1);
		}

		while(fscanf(fptr,"%s",str) == 1){
			if(strcmp("Planets",str) == 0){
				for (int i = 0; i < numberOfplanets; i++){
					fscanf(fptr,"%s",str);
					char *token = strtok(str,",");
					planetinfo[0] = strdup(token); // planet name
					token = strtok(NULL,",");
					planetinfo[1] = strdup(token); // planet x
					token = strtok(NULL,",");
					planetinfo[2] = strdup(token); // planet y
					token = strtok(NULL,",");
					planetinfo[3] = strdup(token); // planet z
					token = strtok(NULL,",");
					planets[i] = initplanet(planetinfo[0],strtod(planetinfo[1],NULL),strtod(planetinfo[2],NULL),strtod(planetinfo[3],NULL));
					for (int i = 0; i < 4; i++){
						free(planetinfo[i]);
					}
				}
			}
			if(strcmp("Jerries",str) == 0){
				while(fscanf(fptr,"%s",str) == 1){

					char *token = strtok(str,",");
					jerryinfo[0] = strdup(token);   //jerry name
					token = strtok(NULL,",");
					jerryinfo[1] = strdup(token);   //jerry dimension name
					token = strtok(NULL,",");
					jerryinfo[2] = strdup(token);   //jerry planet origin
					token = strtok(NULL,",");
					jerryinfo[3] = strdup(token);   //jerry happiness
					Origin *Orig = NULL;
					for (int k = 0; k < numberOfplanets; k++) {
						if (strcmp(planets[k]->name,jerryinfo[2]) == 0){
							Orig = (Origin*) initOrigin(planets[k] , jerryinfo[1]);
						}
					}
					appendNode(jerries, initJerry(jerryinfo[0],atoi(jerryinfo[3]), Orig));
					char temp = fgetc(fptr); // first time to get the '\n' in the end of the row
					temp = fgetc(fptr);
					while (temp == (int) '\t'){ // second time to check if the next char is '\t'
						fscanf(fptr,"%s",str);
						char *token = strtok(str,":");
						PCinfo[0] = strdup(token); // PC Name
						token = strtok(NULL,",");
						PCinfo[1] = strdup(token);  // PC value
						addPC(getDatatByIndex(jerries, getLengthList(jerries)), PCinfo[0], strtod(PCinfo[1],NULL));
						temp = fgetc(fptr);
						temp = fgetc(fptr);
						for (int i = 0; i < 2; i++){
							free(PCinfo[i]);
						}
						numberofchar+=1;
					}
					ungetc(temp,fptr);
					for (int i = 0; i < 4; i++){
						free(jerryinfo[i]);
					}
				}
			}
		}

		fclose(fptr);
		free(planetinfo);
		free(jerryinfo);
		free(PCinfo);

		bool IsPrime(int n){
			if(n<=1){return false;}
			if(n<=3){return true;}
			if(n%2==0||n%3==0){return false;}
			for(int i = 5;i*i<=n;i=i+6)
			{
				if(n%i==0||n%(i+2)==0){return false;}
			}
			return true;
		}

		int GoePrime(int n){
			if(IsPrime(n)){return n;}
			if(n<=1){return 2;}
			int prime = n;
			bool found = false;
			while(!found)
			{
				prime++;
				if(IsPrime(prime))
				{
					found = true;
				}
			}
			return prime;
		}


		hashTable JerryHt = createHashTable((CopyFunction)copyJerryId,(FreeFunction) deleteJerryId,(PrintFunction) printJerryId,
				(CopyFunction)getJerryPointer,(FreeFunction) deleteJerryPointer,(PrintFunction) printJerry, (EqualFunction) equalJerryId,
				(TransformIntoNumberFunction) JerryIdHashFunc,(int) GoePrime(getLengthList(jerries)));

		MultiValueHashTable PcMvht = createMultiValueHashTable((CopyFunction)copyPcName,(FreeFunction) deletePcName, (PrintFunction)printPcName,
				(CopyFunction)getJerryPointer, (FreeFunction)deleteJerryPointer, (PrintFunction)printJerry, (EqualFunction)equalPcName,
				(EqualFunction)equalJerry, (EqualFunction)equalJerryKey, (TransformIntoNumberFunction) PcNameHashFunc,(int) GoePrime(numberofchar));



		for(int i=1; i < getLengthList(jerries) + 1; i++){
			Jerry* currJerry = getDatatByIndex(jerries, i);
			addToHashTable(JerryHt, currJerry->id, currJerry);
			if(currJerry->char_num > 0){
				for(int j=0; j < currJerry->char_num; j++){
					addToMultiValueHashTable(PcMvht, currJerry->ph_char[j]->name, currJerry);
				}
			}
		}

		char jerryid[300];
		char planetName[300];
		char dimension[300];
		planet *planet;
		int happiness;
		char pcName[300];
		float pcVal;
		Jerry *tempJerry;
		Jerry *mostJerry;
		LinkedList Jerrylist;
		char  ch[300];
		int cho = 0;


		   while(  cho != 9 ) {
			  printf("Welcome Rick, what are your Jerry's needs today ? \n");
			  printf("1 : Take this Jerry away from me \n");
			  printf("2 : I think I remember something about my Jerry \n");
			  printf("3 : Oh wait. That can't be right \n");
			  printf("4 : I guess I will take back my Jerry now \n");
			  printf("5 : I can't find my Jerry. Just give me a similar one \n");
			  printf("6 : I lost a bet. Give me your saddest Jerry \n");
			  printf("7 : Show me what you got \n");
			  printf("8 : Let the Jerries play \n");
			  printf("9 : I had enough. Close this place \n");
			  scanf("%s", ch );
			  if (strlen(ch) > 1){
				  cho = 0;
			  }
			  cho = atoi(ch);
			  switch( cho ){

			  	  case 1:  /* Take this Jerry away from me */
			  		  printf("What is your Jerry's ID ? \n");
			  		  scanf("%s" , jerryid);
			  		  if(lookupInHashTable(JerryHt,jerryid) != NULL){
			  			  printf("Rick did you forgot ? you already left him here ! \n");
			  			  break;
			  		  }
			  		  printf("What planet is your Jerry from ? \n");
			  		  scanf("%s" , planetName);
			  		  planet = findPlanet(planets, numberOfplanets, planetName);
			  		  if(planet == NULL){
			  			  printf("%s is not a known planet ! \n" , planetName);
			  			  break;
			  		  }
			  		  printf("What is your Jerry's dimension ? \n");
			  		  scanf("%s" , dimension);
			  		  printf("How happy is your Jerry now ? \n");
			  		  scanf("%d" , &happiness);

			  		  tempJerry =  initJerry( jerryid, happiness, initOrigin(planet ,dimension));
			  		  appendNode(jerries, tempJerry);
			  		  addToHashTable(JerryHt, tempJerry->id, tempJerry);
			  		  printJerry(tempJerry);
			  		  break;


				  case 2:  /* I think I remember something about my Jerry */
					  printf("What is your Jerry's ID ? \n");
					  scanf("%s" , jerryid);
					  tempJerry = lookupInHashTable(JerryHt, jerryid);
					  if(tempJerry == NULL){
						  printf("Rick this Jerry is not in the daycare ! \n");
						  break;
					  }
					  printf("What physical characteristic can you add to Jerry - %s ? \n", jerryid);
					  scanf("%s", pcName);
					  if(checkPC(tempJerry, pcName) == true){
						  printf("The information about his %s already available to the daycare ! \n", pcName);
						  break;
					  }
					  printf("What is the value of his %s ? \n", pcName);
					  scanf("%f", &pcVal);
					  addPC(tempJerry, pcName, pcVal);
					  addToMultiValueHashTable(PcMvht, pcName, tempJerry);
					  displayMultiValueHashElementsByKey(PcMvht, pcName);
					  break;


				  case 3:  /* Oh wait. That can't be right */
					  printf("What is your Jerry's ID ? \n");
					  scanf("%s" , jerryid);
					  tempJerry = lookupInHashTable(JerryHt, jerryid);
					  if(tempJerry == NULL){
						  printf("Rick this Jerry is not in the daycare ! \n");
						  break;
					  }
					  printf("What physical characteristic do you want to remove from Jerry - %s ? \n", jerryid);
					  scanf("%s", pcName);
					  if(checkPC(tempJerry, pcName) == false){
						  printf("The information about his %s not available to the daycare ! \n", pcName);
						  break;
					  }
					  removeFromMultiValueHashTable(PcMvht, pcName, tempJerry);
					  removePC(tempJerry,pcName);
					  printJerry(tempJerry);
					  break;


				  case 4:  /* I guess I will take back my Jerry now */
					  printf("What is your Jerry's ID ? \n");
					  scanf("%s" , jerryid);
					  tempJerry = lookupInHashTable(JerryHt, jerryid);
					  if(tempJerry == NULL){
						  printf("Rick this Jerry is not in the daycare ! \n");
						  break;
					  }
					  for(int i=0; i<tempJerry->char_num;i++){
						  removeFromMultiValueHashTable(PcMvht, tempJerry->ph_char[i]->name, tempJerry);
					  }
					  removeFromHashTable(JerryHt, tempJerry->id);
					  deleteNode(jerries, tempJerry);
					  printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
					  break;





				  case 5: /* I can't find my Jerry. Just give me a similar one */
			  		  printf("What do you remember about your Jerry ? \n");
					  scanf("%s" , pcName);
					  Jerrylist = lookupInMultiValueHashTable(PcMvht, pcName);
					  if(Jerrylist == NULL){
						  printf("Rick we can not help you - we do not know any Jerry's %s ! \n", pcName);
						  break;
					  }
			  		  printf("What do you remember about the value of his %s ? \n", pcName);
					  scanf("%f" , &pcVal);
			  		  mostJerry = getDatatByIndex(Jerrylist, 1);
			  		  for(int i=2; i < getLengthList(Jerrylist) + 1; i++){
			  			  tempJerry = getDatatByIndex(Jerrylist, i);
			  			  if( fabs(getJerryPcVal(tempJerry, pcName) - pcVal) < fabs(getJerryPcVal(mostJerry, pcName) - pcVal) ){
			  				  mostJerry = tempJerry;
			  			  }
			  		  }

			  		  printf("Rick this is the most suitable Jerry we found : \n");
			  		  printJerry(mostJerry);
					  for(int i=0; i<mostJerry->char_num; i++){
						  removeFromMultiValueHashTable(PcMvht, mostJerry->ph_char[i]->name, mostJerry);
					  }

					  removeFromHashTable(JerryHt, mostJerry->id);
					  deleteNode(jerries, mostJerry);
					  printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
					  break;






				  case 6:  /* – I lost a bet. Give me your saddest Jerry */
			  		  if(getLengthList(jerries) == 0){
			  			printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
			  			break;
			  		  }
			  		  mostJerry = getDatatByIndex(jerries, 1);
			  		  for(int i=2; i < getLengthList(jerries) + 1; i++){
			  			  tempJerry = getDatatByIndex(jerries, i);
			  			  if(tempJerry->happiness < mostJerry->happiness){
			  				mostJerry = tempJerry;
			  			  }
			  		  }
			  		  printf("Rick this is the most suitable Jerry we found : \n");
			  		  printJerry(mostJerry);
					  for(int i=0; i<mostJerry->char_num; i++){
						  removeFromMultiValueHashTable(PcMvht, mostJerry->ph_char[i]->name, mostJerry);
					  }
					  removeFromHashTable(JerryHt, mostJerry->id);
					  deleteNode(jerries, mostJerry);
					  printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
					  break;


				  case 7:  /* – Show me what you got */
					   while(  cho == 7 ) {
						  printf("What information do you want to know ? \n");
						  printf("1 : All Jerries \n");
						  printf("2 : All Jerries by physical characteristics \n");
						  printf("3 : All known planets \n");
						  scanf("%s", ch );
						  if (strlen(ch) > 1){
							  cho = 0;
						  }
						  cho = atoi(ch);
						  switch( cho ){
						  	  case 1: /* – All Jerries */
						  		  if(getLengthList(jerries) == 0){
						  			printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
						  			break;
						  		  }
						  		  displayList(jerries);
						  		  break;



						  	  case 2: /* – All Jerries by physical characteristics */
						  		  printf("What physical characteristics ? \n");
								  scanf("%s" , pcName);
								  if(lookupInMultiValueHashTable(PcMvht, pcName) == NULL){
									  printf("Rick we can not help you - we do not know any Jerry's %s ! \n", pcName);
									  break;
								  }
								  displayMultiValueHashElementsByKey(PcMvht, pcName);
								  break;



						  	  case 3: /* – All known planets */
						  		  for(int i=0; i<numberOfplanets;i++){
						  			  printplanet(planets[i]);
						  		  }
						  		  break;


						  	  default:
						  		  printf("Rick this option is not known to the daycare ! \n");
						  		  break;
						  }



					   }
					  break;

				  case 8: /*  Let the Jerries play   */
			  		  if(getLengthList(jerries) == 0){
			  			printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
			  			break;
			  		  }
					   while(  cho == 8 ) {
						  printf("What activity do you want the Jerries to partake in ? \n");
						  printf("1 : Interact with fake Beth \n");
						  printf("2 : Play golf \n");
						  printf("3 : Adjust the picture settings on the TV \n");
						  scanf("%s", ch );
						  if (strlen(ch) > 1){
							  cho = 0;
						  }
						  cho = atoi(ch);
						  switch( cho ){
						  	  case 1: /* – All Jerries */
						  		  for(int i=1; i < getLengthList(jerries) + 1; i++){
						  			  tempJerry = getDatatByIndex(jerries, i);
						  			  if(tempJerry->happiness < 20){
						  				  if(tempJerry->happiness < 6){
						  					  tempJerry->happiness = 0;
						  				  }
						  				  else{
						  					  tempJerry->happiness -= 5;
						  				  }
						  			  }
						  			  else{
						  				  if(tempJerry->happiness > 84){
						  					  tempJerry->happiness = 100;
						  				  }
						  				  else{
						  					  tempJerry->happiness += 15;
						  				  }
						  			  }
						  		  }
						  		  printf("The activity is now over ! \n");
						  		  displayList(jerries);
						  		  break;



						  	  case 2: /* – All Jerries by physical characteristics */
						  		  for(int i=1; i < getLengthList(jerries) + 1; i++){
						  			  tempJerry = getDatatByIndex(jerries, i);
						  			  if(tempJerry->happiness < 50){
						  				  if(tempJerry->happiness < 11){
						  					  tempJerry->happiness = 0;
						  				  }
						  				  else{
						  					  tempJerry->happiness -= 10;
						  				  }
						  			  }
						  			  else{
						  				  if(tempJerry->happiness > 89){
						  					  tempJerry->happiness = 100;
						  				  }
						  				  else{
						  					  tempJerry->happiness += 10;
						  				  }
						  			  }
						  		  }
						  		  printf("The activity is now over ! \n");
						  		  displayList(jerries);
								  break;



						  	  case 3: /* – All known planets */
						  		  for(int i=1; i < getLengthList(jerries) + 1; i++){
						  			  tempJerry = getDatatByIndex(jerries, i);
						  			  if(tempJerry->happiness > 79){
										  tempJerry->happiness = 100;
						  			  }
									  else{
										  tempJerry->happiness += 20;
									  }
								  }
						  		  printf("The activity is now over ! \n");
						  		  displayList(jerries);
						  		  break;


						  	  default:
						  		 printf("Rick this option is not known to the daycare ! \n");
						  		 break;
						  }
					   }
					   break;


				  case 9: /* I had enough. Close this place */



					  for(int i = 0; i < numberOfplanets; i++){
						  deleteplanet(planets[i]);
					  }
					  destroyMultiValueHashTable(PcMvht);
					  destroyHashTable(JerryHt);
					  destroyList(jerries);
					  free(planets);
					  printf("The daycare is now clean and close ! \n");
					  break;


				  default:
					  printf("Rick this option is not known to the daycare ! \n");
					  break;
			  }
		   }
	}
}

