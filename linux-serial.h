#ifndef LINUXSERIAL_H
#define LINUXSERIAL_H

#include "Stream.h"
#include "arduino-serial-lib.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>


class LinuxSerial : public  Stream {

 private:
	int _fd;
	char  buf[2];
 int c;
 
 public:
        int begin(int baud,const char * _ttyname = "/tmp/ttysocat0") {
            c = -1;
            _fd = serialport_init(_ttyname,  baud);
            return _fd >0;
        };
        int end() { return serialport_close(_fd);};
        int available()  {
            if (c != -1) {
                return true;
            } else {
                 c = LinuxSerial::read();
                 return c != -1;
                }
            };
        int read() {
            int r;
            if (c == -1) {
                if (serialport_read_until(_fd, buf, '\0', 1,1)>0){ 
                    return (uint8_t)buf[0];
                }
                else
                    return -1;
                } else {
                    r = c;
                    c = -1;
                    return r;
                }
                
            //r = c !=-1 ? c: serialport_read_until(_fd, buf, '\0', 1,1) >=0 ? buf[0] :-1;
            //c =-1;
            //return r;
            }; 
        size_t write(uint8_t b ){
            return  (serialport_writebyte(_fd, b) >=0);
            };
        int peek() {
            return available() ? c : -1;
        } ;
        size_t write(const uint8_t * data, int len) {
		int l = 0;
		uint8_t *p = (uint8_t*)data;
		while(l < len){
			if (!this->write(*(p++))) 
				break;
			l++;
		}
		return (size_t)l;
	 };
        void flush() {serialport_flush(_fd);};
};







#endif
