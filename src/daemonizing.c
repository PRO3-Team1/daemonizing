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
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include<signal.h>
#include <syslog.h>

void sig_handler(int signo) {
	if (signo == SIGTERM) {
		syslog(LOG_INFO, "%s", "Received SIGTERM. Aborting.");
	}
	exit(0);
}

int main(int argc, char* argv[]) {
	pid_t process_id = 0;
	pid_t sid = 0;

	// Create child process
	process_id = fork();

	openlog("daemonizing.c", 0, LOG_USER);

	// Indication of fork() failure
	if (process_id < 0) {
		syslog(LOG_INFO, "%s", "fork failed!");
		// Return failure in exit status
		exit(1);
	}

	// PARENT PROCESS. Need to kill it.
	if (process_id > 0) {
		syslog(LOG_INFO, "process_id of child process %d", process_id);
		exit(0);
	}

	//unmask the file mode
	umask(0);

	//set new session
	sid = setsid();

	if (sid < 0) {
		// Return failure
		exit(1);
	}

	// Change the current working directory to root.
	chdir("/");

	// Close stdin. stdout and stderr
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	syslog(LOG_INFO, "%s", "IN, OUT, and error closed.");

	if (signal(SIGTERM, sig_handler) == SIG_ERR) {
		syslog(LOG_INFO, "%s", "Can't catch SIGTERM");
	}
	while (1) {
		//Dont block context switches, let the process sleep for some time
		sleep(1);
		syslog(LOG_INFO, "%s", "Logging info....");

		// Implement and call some function that does core work for this daemon.
	}
	closelog();
	return (0);
}
