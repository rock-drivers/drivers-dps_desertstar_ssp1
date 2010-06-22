#ifndef DPS_TYPES_H
#define DPS_TYPES_H

#include <stdint.h>

namespace dps {

 struct PressureReading
      {
	double pressure;
	uint64_t timestamp;
      };

       

}

#endif