#include <iostream>
#include <dps_desertstar_ssp1/Driver.hpp>

class MyHandler : public dps_desertstar_ssp1::Interface{
public:
    MyHandler(){
    }

    void newDepthData(const base::samples::RigidBodyState &depth){
        std::cout << "Got new Depth: " << depth.position[2] << std::endl;
    }

    void newTemperatureData(const double &temperature){
        std::cout << "Got new Teperature " << temperature << std::endl;
    }

};


int main(int argc, char** argv)
{
	if(argc != 2){
            std::cerr << "Please enter device to open" << std::endl;
            return -1;
        }
        dps_desertstar_ssp1::Driver driver;
        if(!driver.openSerial(argv[1], 4800)){
            std::cerr << "The device " << argv[1] << " cannot be opened" << std::endl;
            return -1;
        }
        
        MyHandler handler;
        driver.registerHandler(&handler);

        while(1){
            driver.process();
            sleep(0.01);
        }

	return 0;
}
