#ifndef _ROS_rosserial_arduino_Sensors_h
#define _ROS_rosserial_arduino_Sensors_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rosserial_arduino
{

  class Sensors : public ros::Msg
  {
    public:
      int32_t laser[6];
      float IMU[9];

    Sensors():
      laser(),
      IMU()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 6; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_laseri;
      u_laseri.real = this->laser[i];
      *(outbuffer + offset + 0) = (u_laseri.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_laseri.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_laseri.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_laseri.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->laser[i]);
      }
      for( uint32_t i = 0; i < 9; i++){
      union {
        float real;
        uint32_t base;
      } u_IMUi;
      u_IMUi.real = this->IMU[i];
      *(outbuffer + offset + 0) = (u_IMUi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_IMUi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_IMUi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_IMUi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->IMU[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 6; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_laseri;
      u_laseri.base = 0;
      u_laseri.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_laseri.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_laseri.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_laseri.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->laser[i] = u_laseri.real;
      offset += sizeof(this->laser[i]);
      }
      for( uint32_t i = 0; i < 9; i++){
      union {
        float real;
        uint32_t base;
      } u_IMUi;
      u_IMUi.base = 0;
      u_IMUi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_IMUi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_IMUi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_IMUi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->IMU[i] = u_IMUi.real;
      offset += sizeof(this->IMU[i]);
      }
     return offset;
    }

    const char * getType(){ return "rosserial_arduino/Sensors"; };
    const char * getMD5(){ return "56c991a6af25c6567fa4cc133378b992"; };

  };

}
#endif
