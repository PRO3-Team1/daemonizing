/*
 ============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include <syslog.h>


#include "daemon.h"
#include "tserver.h"


int main(int argc, char* argv[]) {
	daemon_init("daemonizing");

	tserver_init("localhost", "3490");
	while (1) {
		sleep(1);
		printf("logging..\n");
	}

	daemon_stop(0);

}
