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
	void _exit(int i) { this->end();}
 
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
        int peek() {
            return available() ? c : -1;
        } ;

        size_t write(uint8_t b ){
#ifdef SERIALPORTDEBUG
            printf("linux-serial write %x\n",b);
#endif
            return  (serialport_writebyte(_fd, b) >=0);
            };

        size_t write(const uint8_t * data, size_t len) {

        	uint8_t * _data = (uint8_t*)data;
        	size_t  written = len;
       	 len=0;
        	while(written){
          		len++;
          		uint8_t c = *(_data);
           		while(true) {
            			if (this->write(c))
                			break;
            			this->flush();
            		} // Check for ready?
           		written--; 
           		if (written)
                		(_data++);
        	}
		return (size_t)len;
	 };
        void flush() {serialport_flush(_fd);};
};







#endif
