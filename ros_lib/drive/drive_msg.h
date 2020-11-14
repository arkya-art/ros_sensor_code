#ifndef _ROS_drive_drive_msg_h
#define _ROS_drive_drive_msg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace drive
{

  class drive_msg : public ros::Msg
  {
    public:
      typedef float _lpwm_type;
      _lpwm_type lpwm;
      typedef float _rpwm_type;
      _rpwm_type rpwm;
      typedef bool _ldir_type;
      _ldir_type ldir;
      typedef bool _rdir_type;
      _rdir_type rdir;

    drive_msg():
      lpwm(0),
      rpwm(0),
      ldir(0),
      rdir(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_lpwm;
      u_lpwm.real = this->lpwm;
      *(outbuffer + offset + 0) = (u_lpwm.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_lpwm.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_lpwm.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_lpwm.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->lpwm);
      union {
        float real;
        uint32_t base;
      } u_rpwm;
      u_rpwm.real = this->rpwm;
      *(outbuffer + offset + 0) = (u_rpwm.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rpwm.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rpwm.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rpwm.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rpwm);
      union {
        bool real;
        uint8_t base;
      } u_ldir;
      u_ldir.real = this->ldir;
      *(outbuffer + offset + 0) = (u_ldir.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->ldir);
      union {
        bool real;
        uint8_t base;
      } u_rdir;
      u_rdir.real = this->rdir;
      *(outbuffer + offset + 0) = (u_rdir.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->rdir);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_lpwm;
      u_lpwm.base = 0;
      u_lpwm.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_lpwm.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_lpwm.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_lpwm.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->lpwm = u_lpwm.real;
      offset += sizeof(this->lpwm);
      union {
        float real;
        uint32_t base;
      } u_rpwm;
      u_rpwm.base = 0;
      u_rpwm.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rpwm.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_rpwm.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_rpwm.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->rpwm = u_rpwm.real;
      offset += sizeof(this->rpwm);
      union {
        bool real;
        uint8_t base;
      } u_ldir;
      u_ldir.base = 0;
      u_ldir.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->ldir = u_ldir.real;
      offset += sizeof(this->ldir);
      union {
        bool real;
        uint8_t base;
      } u_rdir;
      u_rdir.base = 0;
      u_rdir.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->rdir = u_rdir.real;
      offset += sizeof(this->rdir);
     return offset;
    }

    const char * getType(){ return "drive/drive_msg"; };
    const char * getMD5(){ return "cd6cc8391cf8ed5c17ddaea47e1dc9b4"; };

  };

}
#endif
