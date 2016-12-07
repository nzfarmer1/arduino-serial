#include "linux-serial.h"
#include <stdio.h>

LinuxSerial l;
const char * message = "What the fuck";

int main(int argc, char **argv){
	if (!l.begin(9600))
		return 0;
	while(1){
		if (l.available()){
		int j = l.read();
		if (j >0){
			printf("%c",j);
			fflush(stdout);
			}
		if (j == '?')
			//l.write((uint8_t)'c');
			l.write((uint8_t*)message,13);
		}
	}

return 0;
}
