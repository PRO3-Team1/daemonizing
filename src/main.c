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



int main(int argc, char* argv[]) {
	daemon_init("daemonizing");

	tserver_init("localhost", 3490);
	tserver_listen();
	while (1) {

	}

	daemon_stop(0);

}
