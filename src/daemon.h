/**
 ============================================================================
 Name        : daemon.h
 Author      : Tobias & Jens
 Version     : 1.0
 Copyright   : None
 Date 		 : 30/1-2018
 Description : Change the process to a daemon and prepares syslog
 ============================================================================
 *
 */

#ifndef DAEMON_H_
#define DAEMON_H_

void daemon_init(char *process_name);
void daemon_stop(unsigned int exit_code);


#endif /* DAEMON_H_ */
