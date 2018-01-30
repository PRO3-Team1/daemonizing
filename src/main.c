/**
 ============================================================================
 Name        : main.c
 Author      : Tobias & Jens
 Version     : 1.0
 Copyright   : None
 Date 		 : 30/1-2018
 Description : Starts as a daemon and opens a multithreaded server.
 ============================================================================
 *
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
