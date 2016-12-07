#include "linux-serial.h"
#include <stdio.h>

LinuxSerial l;

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
		}
	}

return 0;
}
