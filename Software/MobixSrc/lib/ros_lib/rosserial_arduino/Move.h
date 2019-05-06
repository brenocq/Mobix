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
      uint32_t vel_length;
      typedef float _vel_type;
      _vel_type st_vel;
      _vel_type * vel;
      typedef float _time_type;
      _time_type time;

    Move():
      vel_length(0), vel(NULL),
      time(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->vel_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->vel_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->vel_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->vel_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->vel_length);
      for( uint32_t i = 0; i < vel_length; i++){
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
      uint32_t vel_lengthT = ((uint32_t) (*(inbuffer + offset)));
      vel_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      vel_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      vel_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->vel_length);
      if(vel_lengthT > vel_length)
        this->vel = (float*)realloc(this->vel, vel_lengthT * sizeof(float));
      vel_length = vel_lengthT;
      for( uint32_t i = 0; i < vel_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_vel;
      u_st_vel.base = 0;
      u_st_vel.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_vel.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_vel.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_vel.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_vel = u_st_vel.real;
      offset += sizeof(this->st_vel);
        memcpy( &(this->vel[i]), &(this->st_vel), sizeof(float));
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
    const char * getMD5(){ return "0b6068eb99ee71bef896eeefe86c9553"; };

  };

}
#endif
