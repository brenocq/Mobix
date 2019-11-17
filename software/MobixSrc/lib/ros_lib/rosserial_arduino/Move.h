#ifndef _ROS_rosserial_arduino_Move_h
#define _ROS_rosserial_arduino_Move_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rosserial_arduino
{

  class Move : public ros::Msg
  {
    public:
      float vel[2];
      typedef float _time_type;
      _time_type time;

    Move():
      vel(),
      time(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 2; i++){
      union {
        float real;
        uint32_t base;
      } u_veli;
      u_veli.real = this->vel[i];
      *(outbuffer + offset + 0) = (u_veli.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_veli.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_veli.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_veli.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->vel[i]);
      }
      union {
        float real;
        uint32_t base;
      } u_time;
      u_time.real = this->time;
      *(outbuffer + offset + 0) = (u_time.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_time.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_time.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_time.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 2; i++){
      union {
        float real;
        uint32_t base;
      } u_veli;
      u_veli.base = 0;
      u_veli.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_veli.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_veli.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_veli.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->vel[i] = u_veli.real;
      offset += sizeof(this->vel[i]);
      }
      union {
        float real;
        uint32_t base;
      } u_time;
      u_time.base = 0;
      u_time.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_time.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_time.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_time.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->time = u_time.real;
      offset += sizeof(this->time);
     return offset;
    }

    const char * getType(){ return "rosserial_arduino/Move"; };
    const char * getMD5(){ return "636357bd9e8164bd16b6d25b1a3fd768"; };

  };

}
#endif
