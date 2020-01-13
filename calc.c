//J Barrett Chesebrough
//ECE 209-051
//Six function Calculator for two inputs
//Test in EOS linux. (note: needs -lm to compile.) 

#include <stdio.h>
#include <math.h>

int main(){

char command=' '; 									//stores character commands
double EARLIER=0.0;									//first input
double LATER=0.0; 									//second input
double tmp;											//placeholder variable for storing numerical inputs, swapping, and computation
double tmp2;										//placeholder variable, only used for magnitude computation
double mag;											//stores sum of squared values for magnitude computation
int status;											//variable used to delineate character and double inputs
int pwr;											//counter variable used to increment exponentiation command


	while(command!='q'){										//quit condition
		status = scanf("%lf",&tmp);
		if(status==1){
			//printf("getting a number");
			EARLIER=LATER;
			LATER=tmp;											//getting a double
			}
		else{
			//printf("getting a character"); 					//getting a command
			if(EOF==scanf("%c",&command)){
				command='q';
				}
			else{												//command processing
				//printf("char else, %d",command);		
				if(command=='p'){								//print
					printf("%.3lf\n",EARLIER);	
					printf("%.3lf\n",LATER);
					}
				else if(command=='a'){							//addition
					LATER=LATER+EARLIER;
					printf("=%.3lf\n",LATER);
					}
				else if(command=='s'){							//subtraction
					LATER=LATER-EARLIER;
					printf("=%.3lf\n",LATER);
					}
				else if(command=='x'){							//multiplication
					LATER=LATER*EARLIER;
					printf("=%.3lf\n",LATER);
					}
				else if(command=='^'){							//exponentiation
					tmp=LATER;
					for(pwr=1;pwr<EARLIER;pwr++){
						LATER*=tmp;
						}
					printf("=%.3lf\n",LATER);
					}
				else if(command=='d'){							//division
					if(EARLIER != 0){
						LATER=LATER/EARLIER;
						printf("=%.3lf\n",LATER);
						}
					else printf("ERROR: Dividing by 0.");
					}
				else if(command=='w'){							//swap
					tmp=LATER;
					LATER=EARLIER;
					EARLIER=tmp;
					}	
				else if(command=='c'){							//clear
					LATER=0.0;
					EARLIER=0.0;
					}
				else if(command=='m'){							//magnitude
					tmp=EARLIER*EARLIER;
					tmp2=LATER*LATER;
					mag=tmp+tmp2;
					LATER=sqrt(mag);
					printf("=%.3lf\n",LATER);
					}
				else if(command=='b'){
					EARLIER=sqrt(EARLIER);
					LATER=sqrt(LATER);
					printf("=%.3lf\n",EARLIER);
					printf("=%.3lf\n",LATER);
					}	
				
				else if(command=='h'){							//help
					printf("Command Menu:\n");
					printf("'x': multiplication, LATER=LATER*EARLIER\n");
					printf("'d': division, LATER=LATER/EARLIER\n");
					printf("'a': addition, LATER=LATER+EARLIER\n");
					printf("'s': subtraction, LATER=LATER-EARLIER\n");
					printf("'^': exponentiation, LATER=LATER^EARLIER (note: '^'=/= bitwise XOR in this case)\n");
					printf("'m': magnitude, LATER=sqrt(LATER^2+EARLIER^2) (note: uses <math.h> library)\n");
					printf("'w': swap, swap values of LATER and EARLIER\n");
					printf("'c': clear, sets LATER and EARLIER to 0.0\n");
					printf("'p': print, prints values of EARLIER and LATER to output\n");
					printf("'h': help, prints help menu. (what you are currently reading)\n");
					printf("'q': quit, prints EARLIER and LATER to output then ends program.\n");
					}
				else{	//unsupported character entry
					 if(command!='q') printf("The operator %c is not supported.\n",command); 
					}
				}		
			}	
		}	
	printf("%.3lf\n",EARLIER);
	printf("%.3lf\n",LATER);
return 0;
}