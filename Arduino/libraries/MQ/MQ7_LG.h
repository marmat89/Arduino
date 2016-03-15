
/*
  MQ7_LG.h - Library for MQ7 Monoxide Gas Sensor v1.3 hardware.
  Created by Laurent Gibergues, January 21, 2015
  Released into the public domain.
  Hardware v1.3 need modification : see documentation please
  
*/


#ifndef MQ7_LG_h
#define MQ7_LG_h

#include <inttypes.h>



class MQ7_LG {
public :
  MQ7_LG(uint8_t VRLPin, uint8_t HeaterCtrlPin, int8_t DOutPin = -1, int8_t HeaterVoltagePin = -1);
  void init();
  void run();
  int read();
  float getVRL();
  int getDOut();
  float getHeaterVoltage();
  typedef enum states {HIGH_HEATING = 0, LOW_HEATING} state_t;
  
private :
  int  _ppmCO;
  uint8_t _VRLPin;
  uint8_t _heaterCtrlPin;
  int8_t _DOutPin;
  int8_t _heaterVoltagePin;
  bool _HeaterVoltageIsConnected;
  bool _DOutIsConnected;
  state_t _state;
  unsigned long _prevTime;

  //functions
  int toPpm(float VRL);
  
  // Specifics data
  const static unsigned long HIGH_HEATING_TIME = 60 * 1000L;    // ms
  const static unsigned long LOW_HEATING_TIME = 90 * 1000L;     // ms
  const static unsigned RL = 10000;              // Ohms
  const static unsigned R0 = 2000;               // Ohms
  const static float    VCC_HEATER = 5.29;       // Volts
  const static float    COEF_A = -1.6;          // See MQ7 documentation :
  const static float    CONSTANT_B = 100;        // log(ppmCO) = COEF_A * log(Rs/R0) + log(CONSTANT_B)
};

#endif