#include <REGX52.H>

#include"delay.h"
#include"main.h"


#if (FREQ_OSC == 12000000)
	void delay( unsigned int t)
	{
		unsigned int x, y;
		for(x=0;x<t;x++)
		{
			for(y=0;y<123;y++);
		}
	}
#elif (FREQ_OSC == 11059200)
	void delay( unsigned int t)
	   {
		unsigned int x, y;
		for(x=0;x<t;x++)
		{
			for(y=0;y<113;y++);
		}
	}

#elif (FREQ_OSC == 800000)
	void delay( unsigned int t)
	  {
		unsigned int x, y;
		for(x=0;x<t;x++)
		{
			for(y=0;y<218;y++);
		}
	}
#else
	#error "Khong co ham delay nao tuong ung"
#endif													