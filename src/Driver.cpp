#include "Driver.hpp"

namespace dps_desertstar_ssp1
{

    Driver::Driver(double variance):
    iodrivers_base::Driver(DESERTSTAR_BUFFER_SIZE,false)
    {
        depth.invalidate();
        depth.cov_position(2,2) = variance;
    }

    void Driver::process(){
        int cnt = readPacket(buffer, DESERTSTAR_BUFFER_SIZE, m_read_timeout);
        //Got a complete package
        if(cnt == 20){
            //Escaping the string to make sure sscanf works properly
            buffer[21] = 0;
            unsigned int checksum; //Not needed but we etract it here for maybe later use
            float unknown; //Unknown field so far seems to be 0.0 always
            float value;
            if(sscanf((char*)buffer,"$YXDPT,%f,%f*%02X",&value,&unknown,&checksum)){
                depth.position[2] = (-value+1)*10;
                for(std::list<Interface*>::iterator it = handler.begin(); it != handler.end(); it++){
                    (*it)->newDepthData(depth);
                }
            }else if(sscanf((char*)buffer,"$YXTMP,%f,%f*%02X",&value,&unknown,&checksum)){
                for(std::list<Interface*>::iterator it = handler.begin(); it != handler.end(); it++){
                    (*it)->newTemperatureData(value);
                }
            }
        }
        
    }

    void Driver::updateVaricance(double variance){
        depth.cov_position(2,2) = variance;
    }

    void Driver::registerHandler(Interface *interface){
        handler.push_back(interface);
    }

    void Driver::unregisterHandler(Interface *interface){
        handler.remove(interface);
    }

    int Driver::extractPacket(uint8_t const* buffer, size_t buffer_size) const{
        unsigned int pos = 0;

        //Searcing for the start-sign
        while(buffer[pos] != '$' && pos < buffer_size){
            pos++;
        }
        //skipping invalid chars from fron
        if(pos != 0){
            return -pos;
        }
        uint8_t checksum = 0;

        //Currently all packages seems to have 20 bytes
        if(buffer_size < 20){
            //So we are not complete yet
            return 0;
        }

        //Checksum is build between first and 16th field
        for(unsigned int i=1;i<16;i++){
            checksum^=buffer[i];
        }
	

        //Creating a hex-representation out of this (more easy instead of chreating value out of string)
        char sign[3];
        sprintf(sign,"%02X",checksum);
        //Checksum match
        if(memcmp(sign,buffer+17,2) == 0){
            //Successfull returning here the buffer
            return 20;
        }
        
        //Checksum failed returning one char, the next bytes are skipped by the next iteration of this method
        return -1;
    }

}
