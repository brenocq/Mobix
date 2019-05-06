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
      uint32_t laser_length;
      typedef int32_t _laser_type;
      _laser_type st_laser;
      _laser_type * laser;
      uint32_t IMU_length;
      typedef float _IMU_type;
      _IMU_type st_IMU;
      _IMU_type * IMU;
      uint32_t IRReceiver_length;
      typedef int32_t _IRReceiver_type;
      _IRReceiver_type st_IRReceiver;
      _IRReceiver_type * IRReceiver;

    Sensors():
      laser_length(0), laser(NULL),
      IMU_length(0), IMU(NULL),
      IRReceiver_length(0), IRReceiver(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->laser_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->laser_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->laser_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->laser_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->laser_length);
      for( uint32_t i = 0; i < laser_length; i++){
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
      *(outbuffer + offset + 0) = (this->IMU_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->IMU_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->IMU_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->IMU_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->IMU_length);
      for( uint32_t i = 0; i < IMU_length; i++){
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
      *(outbuffer + offset + 0) = (this->IRReceiver_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->IRReceiver_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->IRReceiver_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->IRReceiver_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->IRReceiver_length);
      for( uint32_t i = 0; i < IRReceiver_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_IRReceiveri;
      u_IRReceiveri.real = this->IRReceiver[i];
      *(outbuffer + offset + 0) = (u_IRReceiveri.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_IRReceiveri.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_IRReceiveri.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_IRReceiveri.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->IRReceiver[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t laser_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      laser_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      laser_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      laser_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->laser_length);
      if(laser_lengthT > laser_length)
        this->laser = (int32_t*)realloc(this->laser, laser_lengthT * sizeof(int32_t));
      laser_length = laser_lengthT;
      for( uint32_t i = 0; i < laser_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_laser;
      u_st_laser.base = 0;
      u_st_laser.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_laser.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_laser.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_laser.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_laser = u_st_laser.real;
      offset += sizeof(this->st_laser);
        memcpy( &(this->laser[i]), &(this->st_laser), sizeof(int32_t));
      }
      uint32_t IMU_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      IMU_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      IMU_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      IMU_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->IMU_length);
      if(IMU_lengthT > IMU_length)
        this->IMU = (float*)realloc(this->IMU, IMU_lengthT * sizeof(float));
      IMU_length = IMU_lengthT;
      for( uint32_t i = 0; i < IMU_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_IMU;
      u_st_IMU.base = 0;
      u_st_IMU.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_IMU.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_IMU.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_IMU.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_IMU = u_st_IMU.real;
      offset += sizeof(this->st_IMU);
        memcpy( &(this->IMU[i]), &(this->st_IMU), sizeof(float));
      }
      uint32_t IRReceiver_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      IRReceiver_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      IRReceiver_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      IRReceiver_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->IRReceiver_length);
      if(IRReceiver_lengthT > IRReceiver_length)
        this->IRReceiver = (int32_t*)realloc(this->IRReceiver, IRReceiver_lengthT * sizeof(int32_t));
      IRReceiver_length = IRReceiver_lengthT;
      for( uint32_t i = 0; i < IRReceiver_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_IRReceiver;
      u_st_IRReceiver.base = 0;
      u_st_IRReceiver.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_IRReceiver.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_IRReceiver.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_IRReceiver.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_IRReceiver = u_st_IRReceiver.real;
      offset += sizeof(this->st_IRReceiver);
        memcpy( &(this->IRReceiver[i]), &(this->st_IRReceiver), sizeof(int32_t));
      }
     return offset;
    }

    const char * getType(){ return "rosserial_arduino/Sensors"; };
    const char * getMD5(){ return "4a783ba88292007d232f848dc33ea4e9"; };

  };

}
#endif
