#ifndef _DESERTSTAR_DRIVER_HPP_
#define _DESERTSTAR_DRIVER_HPP_

#include <iostream>
#include <iodrivers_base/Driver.hpp>
#include <base/samples/RigidBodyState.hpp>
#include <list>

//Arbitarry large number to fit the message
#define DESERTSTAR_BUFFER_SIZE 512 

namespace dps_desertstar_ssp1
{
        class Interface{
            public:
                virtual void newDepthData(const base::samples::RigidBodyState &depth)=0;
                virtual void newTemperatureData(const double &temperature)=0;
        };

	class Driver : public iodrivers_base::Driver 
	{
		public:
                    Driver(const double variance =  0.0216505327374);
                    void process();
                    void updateVaricance(double variance);
                    void registerHandler(Interface *interface);
                    void unregisterHandler(Interface *interface);
                    virtual int extractPacket(uint8_t const* buffer, size_t buffer_size) const;
                protected:
                    base::samples::RigidBodyState depth;
                    std::list<Interface*> handler;
                    uint8_t buffer[DESERTSTAR_BUFFER_SIZE];
                     
	};

} // end namespace dps_desertstar_ssp1

#endif 
