#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RAND_MAX 14

PrintConsole topScreen, bottomScreen;

void win() {
	consoleSelect(&bottomScreen);
	printf("\x1b[12;14HYou have won!");
	printf("\x1b[14;15H> Play again");
	printf("\x1b[16;15H  Select mode");
	printf("\x1b[18;18H  Quit");
}

void lose() {
	consoleSelect(&bottomScreen);
	printf("\x1b[12;14HYou have lost!");
	printf("\x1b[14;15H> Play again");
	printf("\x1b[16;15H  Select mode");
	printf("\x1b[18;18H  Quit");
}

void draw() {
	consoleSelect(&bottomScreen);
	printf("\x1b[12;15HIt's a draw!");
	printf("\x1b[14;15H> Play again");
	printf("\x1b[16;15H  Select mode");
	printf("\x1b[18;18H  Quit");
}

int truerand(int max) {
	srand (time(NULL));
	int num = (rand() % max) + 1;
	return num;
}

int main(int argc, char **argv) {
    gfxInitDefault();
	
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);
	
	select:
	
	consoleSelect(&topScreen);
	printf("\x1b[14;15H\x1b[33mRock, Paper, Scissors!\x1b[0m");
	printf("\x1b[16;6HYou can quit anytime by pressing \x1b[36mSTART\x1b[0m.\n");
	
	consoleSelect(&bottomScreen);
	printf("\x1b[13;14HSelect a mode:");
	printf("\x1b[15;16H> Classic");
	printf("\x1b[17;15H  Expansion");
	
	int choice = 1;
	
    while(aptMainLoop()) {
        gspWaitForVBlank();
        hidScanInput();

        if(hidKeysDown() & KEY_START) {
        	gfxExit();
    		return 0;
		}
        
        else if(hidKeysDown() & KEY_DOWN) {
        	consoleSelect(&bottomScreen);
			if (choice < 2) 
				++choice;
			printf("\x1b[15;16H ");
			printf("\x1b[17;15H ");
			printf("\x1b[%d;%dH>", 2*choice+13, 17-choice);
		}
		
		else if(hidKeysDown() & KEY_UP) {
			if (choice > 1) 
				--choice;
			printf("\x1b[15;16H ");
			printf("\x1b[17;15H ");
			printf("\x1b[%d;%dH>", 2*choice+13, 17-choice);
		}
		
		else if(hidKeysDown() & KEY_A) {
			consoleInit(GFX_TOP, &topScreen);
			consoleInit(GFX_BOTTOM, &bottomScreen);
			
			if (choice == 1) {
				break;
			}
			else if (choice == 2) {
				goto rpsls;
			}
		}

        gfxFlushBuffers();
        gfxSwapBuffers();
    }
    
    rps:
    
	consoleSelect(&topScreen);
	printf("\x1b[15;13HChoices of CPU are random.");
	
	consoleSelect(&bottomScreen);
	printf("\x1b[12;14HMake a choice:");
	printf("\x1b[14;17H> Rock");
	printf("\x1b[16;17H  Paper");
	printf("\x1b[18;16H  Scissors");
	
	int cpuchoice = truerand(3);
	choice = 1;
	
	while(aptMainLoop()) {
        gspWaitForVBlank();
        hidScanInput();

        if(hidKeysDown() & KEY_START) {
        	gfxExit();
    		return 0;
		}
        
        else if(hidKeysDown() & KEY_DOWN) {
        	consoleSelect(&bottomScreen);
			if (choice < 3) 
				++choice;
			printf("\x1b[14;17H ");
			printf("\x1b[16;17H ");
			printf("\x1b[18;16H ");
			printf("\x1b[%d;%dH>", 2*choice+12, 17-choice/3);
		}
		
		else if(hidKeysDown() & KEY_UP) {
			consoleSelect(&bottomScreen);
			if (choice > 1) 
				--choice;
			printf("\x1b[14;17H ");
			printf("\x1b[16;17H ");
			printf("\x1b[18;16H ");
			printf("\x1b[%d;%dH>", 2*choice+12, 17-choice/3);
		}
		
		else if(hidKeysDown() & KEY_A) {
			consoleInit(GFX_TOP, &topScreen);
			consoleInit(GFX_BOTTOM, &bottomScreen);
			
			cpuchoice = truerand(3);
			
			consoleSelect(&topScreen);
			printf("\x1b[12;21HYou chose:");
			printf("\x1b[16;21HCPU chose:");
			printf("\x1b[18;%dH\x1b[36m",25-cpuchoice);
			if (cpuchoice == 1) printf("ROCK\x1b[0m");
			if (cpuchoice == 2) printf("PAPER\x1b[0m");
			if (cpuchoice == 3) printf("SCISSORS\x1b[0m");
			printf("\x1b[14;%dH\x1b[32m",25-choice);
			
			if (choice == 1) {
				printf("ROCK\x1b[0m");
				if (cpuchoice == 1) draw();
				if (cpuchoice == 2) lose();
				if (cpuchoice == 3) win();
			}
			else if (choice == 2) {
				printf("PAPER\x1b[0m");
				if (cpuchoice == 1) win();
				if (cpuchoice == 2) draw();
				if (cpuchoice == 3) lose();
			}
			else if (choice == 3) {
				printf("SCISSORS\x1b[0m");
				if (cpuchoice == 1) lose();
				if (cpuchoice == 2) win();
				if (cpuchoice == 3) draw();
			}
			break;
		}

        gfxFlushBuffers();
        gfxSwapBuffers();
    }
    
    choice = 1;
    
    while(aptMainLoop()) {
        gspWaitForVBlank();
        hidScanInput();

        if(hidKeysDown() & KEY_START) {
        	gfxExit();
    		return 0;
		}
        
        else if(hidKeysDown() & KEY_DOWN) {
        	consoleSelect(&bottomScreen);
			if (choice < 3) 
				++choice;
			printf("\x1b[14;15H ");
			printf("\x1b[16;15H ");
			printf("\x1b[18;18H ");
			printf("\x1b[%d;%dH>", 2*choice+12, 15+(choice/3)*3);
		}
		
		else if(hidKeysDown() & KEY_UP) {
			consoleSelect(&bottomScreen);
			if (choice > 1) 
				--choice;
			printf("\x1b[14;15H ");
			printf("\x1b[16;15H ");
			printf("\x1b[18;18H ");
			printf("\x1b[%d;%dH>", 2*choice+12, 15+(choice/3)*3);
		}
		
		else if(hidKeysDown() & KEY_A) {
			consoleInit(GFX_TOP, &topScreen);
			consoleInit(GFX_BOTTOM, &bottomScreen);
			
			if (choice == 1) {
				goto rps;
			}
			else if (choice == 2) {
				goto select;
			}
			else if (choice == 3) {
				gfxExit();
    			return 0;
			}
		}
		
		gfxFlushBuffers();
        gfxSwapBuffers();
    }
    
    rpsls:
    	
    consoleSelect(&topScreen);
	printf("\x1b[6;16H\x1b[31mScissors\x1b[0m cuts \x1b[32mPaper\x1b[0m;");
	printf("\x1b[8;17H\x1b[32mPaper\x1b[0m covers \x1b[33mRock\x1b[0m.");
	printf("\x1b[10;16H\x1b[33mRock\x1b[0m crushes \x1b[35mLizard\x1b[0m;");
	printf("\x1b[12;16H\x1b[35mLizard\x1b[0m poisons \x1b[36mSpock\x1b[0m.");
	printf("\x1b[14;15H\x1b[36mSpock\x1b[0m smashes \x1b[31mScissors\x1b[0m;");
	printf("\x1b[16;12H\x1b[31mScissors\x1b[0m decapitates \x1b[35mLizard\x1b[0m.");
	printf("\x1b[18;17H\x1b[35mLizard\x1b[0m eats \x1b[32mPaper\x1b[0m;");
	printf("\x1b[20;15H\x1b[32mPaper\x1b[0m disproves \x1b[36mSpock\x1b[0m.");
	printf("\x1b[22;16H\x1b[36mSpock\x1b[0m vaporizes \x1b[33mRock\x1b[0m;");
	printf("\x1b[24;15H\x1b[33mRock\x1b[0m crushes \x1b[31mScissors\x1b[0m.");
	
	consoleSelect(&bottomScreen);
	printf("\x1b[10;14HMake a choice:");
	printf("\x1b[12;17H> Rock");
	printf("\x1b[14;17H  Paper");
	printf("\x1b[16;16H  Scissors");
	printf("\x1b[18;17H  Lizard");
	printf("\x1b[20;17H  Spock");
	
	int cpurpsls = truerand(5);
	choice = 1;
	
	while(aptMainLoop()) {
        gspWaitForVBlank();
        hidScanInput();

        if(hidKeysDown() & KEY_START) {
        	gfxExit();
    		return 0;
		}
        
        else if(hidKeysDown() & KEY_DOWN) {
        	consoleSelect(&bottomScreen);
			if (choice < 5) 
				++choice;
			printf("\x1b[12;17H ");
			printf("\x1b[14;17H ");
			printf("\x1b[16;16H ");
			printf("\x1b[18;17H ");
			printf("\x1b[20;17H ");
			printf("\x1b[%d;%dH>", 2*choice+10, 17-choice/3+choice/4);
		}
		
		else if(hidKeysDown() & KEY_UP) {
			consoleSelect(&bottomScreen);
			if (choice > 1) 
				--choice;
			printf("\x1b[12;17H ");
			printf("\x1b[14;17H ");
			printf("\x1b[16;16H ");
			printf("\x1b[18;17H ");
			printf("\x1b[20;17H ");
			printf("\x1b[%d;%dH>", 2*choice+10, 17-choice/3+choice/4);
		}
		
		else if(hidKeysDown() & KEY_A) {
			consoleInit(GFX_TOP, &topScreen);
			consoleInit(GFX_BOTTOM, &bottomScreen);
			
			cpurpsls = truerand(5);
			
			consoleSelect(&topScreen);
			printf("\x1b[12;21HYou chose:");
			printf("\x1b[16;21HCPU chose:");
			printf("\x1b[18;%dH\x1b[36m",25-cpurpsls+(cpurpsls/4)*(cpurpsls-2));
			if (cpurpsls == 1) printf("ROCK\x1b[0m");
			if (cpurpsls == 2) printf("PAPER\x1b[0m");
			if (cpurpsls == 3) printf("SCISSORS\x1b[0m");
			if (cpurpsls == 4) printf("LIZARD\x1b[0m");
			if (cpurpsls == 5) printf("SPOCK\x1b[0m");
			printf("\x1b[14;%dH\x1b[32m",25-choice+(choice/4)*(choice-2));
			
			if (choice == 1) {
				printf("ROCK\x1b[0m");
				if (cpurpsls == 1) draw();
				if (cpurpsls == 2) lose();
				if (cpurpsls == 3) win();
				if (cpurpsls == 4) win();
				if (cpurpsls == 5) lose();
			}
			else if (choice == 2) {
				printf("PAPER\x1b[0m");
				if (cpurpsls == 1) win();
				if (cpurpsls == 2) draw();
				if (cpurpsls == 3) lose();
				if (cpurpsls == 4) lose();
				if (cpurpsls == 5) win();
			}
			else if (choice == 3) {
				printf("SCISSORS\x1b[0m");
				if (cpurpsls == 1) lose();
				if (cpurpsls == 2) win();
				if (cpurpsls == 3) draw();
				if (cpurpsls == 4) win();
				if (cpurpsls == 5) lose();
			}
			else if (choice == 4) {
				printf("LIZARD\x1b[0m");
				if (cpurpsls == 1) lose();
				if (cpurpsls == 2) win();
				if (cpurpsls == 3) lose();
				if (cpurpsls == 4) draw();
				if (cpurpsls == 5) win();
			}
			else if (choice == 5) {
				printf("SPOCK\x1b[0m");
				if (cpurpsls == 1) win();
				if (cpurpsls == 2) lose();
				if (cpurpsls == 3) win();
				if (cpurpsls == 4) lose();
				if (cpurpsls == 5) draw();
			}
			break;
		}

        gfxFlushBuffers();
        gfxSwapBuffers();
    }
    
    choice = 1;
    
    while(aptMainLoop()) {
        gspWaitForVBlank();
        hidScanInput();

        if(hidKeysDown() & KEY_START) {
        	gfxExit();
    		return 0;
		}
        
        else if(hidKeysDown() & KEY_DOWN) {
        	consoleSelect(&bottomScreen);
			if (choice < 3) 
				++choice;
			printf("\x1b[14;15H ");
			printf("\x1b[16;15H ");
			printf("\x1b[18;18H ");
			printf("\x1b[%d;%dH>", 2*choice+12, 15+(choice/3)*3);
		}
		
		else if(hidKeysDown() & KEY_UP) {
			consoleSelect(&bottomScreen);
			if (choice > 1) 
				--choice;
			printf("\x1b[14;15H ");
			printf("\x1b[16;15H ");
			printf("\x1b[18;18H ");
			printf("\x1b[%d;%dH>", 2*choice+12, 15+(choice/3)*3);
		}
		
		else if(hidKeysDown() & KEY_A) {
			consoleInit(GFX_TOP, &topScreen);
			consoleInit(GFX_BOTTOM, &bottomScreen);
			
			if (choice == 1) {
				goto rpsls;
			}
			else if (choice == 2) {
				goto select;
			}
			else if (choice == 3) {
				gfxExit();
    			return 0;
			}
		}
		
		gfxFlushBuffers();
        gfxSwapBuffers();
    }
}
