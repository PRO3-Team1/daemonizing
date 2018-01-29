/*
 ============================================================================
 Name        : daemonizing.c
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



int main(int argc, char* argv[]) {
	daemon_init("daemonizing");
	while (1) {
		//Dont block context switches, let the process sleep for some time
		sleep(1);
		syslog(LOG_INFO,"Logging info....");

		// Implement and call some function that does core work for this daemon.
	}

	daemon_stop();

}
