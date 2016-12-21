#include "Stream.h"
#include "arduino-serial-lib.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

/**
* Crude wrapper for arduino-serial-lib to enable development
* of streams based arduino code within linux env.`
*
**/


const char *  _ttyname = "/tmp/ttysocat0"; // Change as required. See socat.sh

class LinuxSerial : public  Stream {

 protected:
	int fd;
	char  buf[2];
 public:
        int begin(int baud) { fd =  serialport_init(_ttyname,  baud); return fd >0;};
        int end() { return serialport_close(fd);};
	int available() {return pread(fd,buf,1,0); } ;
        int read() {return serialport_read_until(fd, buf, '\0', 1,1) >=0 ? buf[0] :-1;}; 
        size_t write(uint8_t b ){return  (serialport_writebyte(fd, b) >=0);};
	int peek() {int l = pread(fd,buf,1,0); return l>=0? buf[0]:-1;} ;
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
        void flush() {serialport_flush(fd);};
};
