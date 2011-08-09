#include <iostream>
#include "dps.h"

int main(int argc, char** argv)
{
	dps::DPS dps;

        int port = 0;
        if(argc < 2)
        {
            std::cout << "No port given - attempting to open /dev/ttyS0..." << std::endl;
	    port = dps.openComPort("/dev/ttyS0");
        }
        else
        {
            std::cout << "Attempting to open port " << argv[1] << " ..." << std::endl;
	    port = dps.openComPort(argv[1]);
        }

        if(port == -1)
        {
           std::cout << "Error - could not open port!" << std::endl;
           return -1;
        }
        else
           std::cout << "OK." << std::endl;
        dps.the_file_stream.open("dps.txt");

	
	for(uint i = 0 ; i < 10000 ; i++)
	{

	  dps.prevChar = dps.currChar;
	  dps.currChar = dps.getCharFromPort();
	  //std::cerr << dps.currChar;
	  dps.the_file_stream << dps.currChar;
	  dps.the_file_stream.flush();

	  dps.readBuffer.push_back(dps.currChar);

	  if(dps.prevChar == 'D' && dps.currChar == 'P')
	  {
	    if(!dps.receivedFirstTimeStamp)
	    {
	      dps.readBuffer.clear();
	      dps.receivedFirstTimeStamp = true;
	    }
	    else
	    {
	      if(!dps.receivedSecondTimeStamp)
	      dps.receivedSecondTimeStamp = true;
	      else
	      {
		dps::PressureReading pr;
		//std::cerr << "now getting curr speeds from this string:\n\n" << dps.readBuffer << "\n\n this was the string\n";
		dps.getPressureFromString(dps.readBuffer, pr);
		//std::cerr << dps.readBuffer << std::endl;
		dps.printPressure(pr);
		//_dps_speeds.write(speeds);
		//CvMat img = dps.getSpeedVis(speeds);
		//cvShowImage("DVL", &img);
	      }
	    }
	  }
	  
	}
	
	return 0;
}
