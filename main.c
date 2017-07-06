// Dolengewicz, Okoro
// EE443 HW1

#include "DSP_Config.h"


#define LEFT 0
#define RIGHT 1

double outputGain = 1;
double inputGain = 1;
double decay = .8; //
int ii = 0;
short delayVal = 0;
int GUI_Out;
int GUI_Out_Input;
short delayTrue = 0;
int bufferSize = 1600;
int audioBuffer[1600];

int switchState = 0;
int ss = 0;


int main()

{
	// initialize DSP board
	DSP_Init();
	// call StartUp for application specific code
	// defined in each application directory
	StartUp();

	for(ii = 0;ii < bufferSize;ii++) {
		audioBuffer[ii] = 0;
	}

	while(1) {

		switchState = ReadSwitches();
		ss = switchState;

		if(switchState % 2 == 1){
			delayVal = 0;
	    }
		else if(ss == 0)  	delayVal = 100;
		else if(ss == 8)  	delayVal = 200;
		else if(ss == 4)  	delayVal = 300;
		else if(ss == 12) 	delayVal = 400;
		else if(ss == 2)  	delayVal = 500;
		else if(ss == 10) 	delayVal = 600;
		else if(ss == 6)  	delayVal = 700;
		else if(ss == 14) 	delayVal = 800;

		WriteLEDs(switchState);

	}
}

