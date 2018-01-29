#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

#include "daemon.h"

/**
 * Sig handler
 */
void sig_handler(int signo) {
	if (signo == SIGTERM) {
		syslog(LOG_INFO, "Received SIGTERM. Aborting.");
		daemon_stop();
	}

}

/**
 * Turn this process into a daemon and detach stdin, stdout and stderr
 * Starts a syslog session with the given process name
 */
void daemon_init(char *process_name) {
	pid_t process_id = 0;
	pid_t sid = 0;

	// Create child process
	process_id = fork();

	openlog(process_name, 0, LOG_USER);

	// Indication of fork() failure
	if (process_id < 0) {
		syslog(LOG_INFO, "%s", "fork failed!");
		// Return failure in exit status
		daemon_stop(1);
	}

	// PARENT PROCESS. Need to kill it.
	if (process_id > 0) {
		syslog(LOG_INFO, "process_id of child process %d", process_id);
		printf("Daemon started: PID %d\n", process_id);
		daemon_stop(1);
	}


	//unmask the file mode
	umask(0);

	//set new session
	sid = setsid();

	if (sid < 0) {
		// Return failure
		daemon_stop(1);
	}

	// Change the current working directory to root.
	chdir("/");

	// Close stdin. stdout and stderr
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	syslog(LOG_INFO, "STDIN, STDOUT, and STDERR closed.");

	if (signal(SIGTERM, sig_handler) == SIG_ERR) {
		syslog(LOG_ERR,"Can't catch SIGTERM");
	}
}

void daemon_stop(int exit_code) {
	syslog(LOG_INFO, "Stopping daemon");
	syslog(LOG_INFO, "Exit code: %d", exit_code);
	closelog();
	exit(exit_code);
}
