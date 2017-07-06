// Dolengewicz, Okoro
// EE443 HW1


#include "DSP_Config.h" 
  
// Data is received as 2 16-bit words (left/right) packed into one
// 32-bit word.  The union allows the data to be accessed as a single 
// entity when transferring to and from the serial port, but still be 
// able to manipulate the left and right channels independently.

#define LEFT  0
#define RIGHT 1

volatile union {
	Uint32 UINT;
	Int16 Channel[2];
} CodecDataIn, CodecDataOut;

extern double outputGain;
extern double inputGain;
extern double decay;
extern int bufferSize;
extern int ii;
extern short delayVal;
extern int GUI_Out;
extern int GUI_Out_Input;
extern int audioBuffer[1600];
/* add any global variables here */

int delayIndex = 0;

interrupt void Codec_ISR()
{                    

 	if(CheckForOverrun())					// overrun error occurred (i.e. halted DSP)
		return;								// so serial port is reset to recover

   	CodecDataIn.UINT = ReadCodecData(); // get input data samples
   	GUI_Out_Input = CodecDataIn.Channel[LEFT];

  	if(delayVal == 0) {
  		CodecDataOut.Channel[RIGHT] = 0;
  		CodecDataOut.Channel[LEFT]  = CodecDataIn.Channel[LEFT];
  		audioBuffer[ii] = 0;
  		ii = (ii + 1);
  		if(ii > bufferSize)	ii = 0;
  	}
  	else{
  		delayIndex = ii - delayVal;
  		if (delayIndex < 0)  delayIndex = delayIndex + bufferSize;

  		audioBuffer[ii] = (CodecDataIn.Channel[LEFT] >> 1) + decay*audioBuffer[delayIndex];

  		CodecDataOut.Channel[RIGHT] = 0;
  		CodecDataOut.Channel[LEFT]  = outputGain*audioBuffer[ii];

  		ii = (ii + 1);
  		if(ii > bufferSize)	ii = 0;

  	}
  	GUI_Out = CodecDataOut.Channel[LEFT];
  	WriteCodecData(CodecDataOut.UINT);
}

