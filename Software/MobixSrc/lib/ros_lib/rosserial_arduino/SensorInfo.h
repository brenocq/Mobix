#ifndef _ROS_rosserial_arduino_SensorInfo_h
#define _ROS_rosserial_arduino_SensorInfo_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rosserial_arduino
{

  class SensorInfo : public ros::Msg
  {
    public:
      typedef float _laser_type;
      _laser_type laser;

    SensorInfo():
      laser(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_laser;
      u_laser.real = this->laser;
      *(outbuffer + offset + 0) = (u_laser.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_laser.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_laser.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_laser.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->laser);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_laser;
      u_laser.base = 0;
      u_laser.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_laser.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_laser.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_laser.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->laser = u_laser.real;
      offset += sizeof(this->laser);
     return offset;
    }

    const char * getType(){ return "rosserial_arduino/SensorInfo"; };
    const char * getMD5(){ return "b02f3093f1692c71f4bf1dbe480e9554"; };

  };

}
#endif
