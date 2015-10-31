#ifndef PRINT_WAIT_STATUS_H
#define PRINT_WAIT_STATUS_H

void printWaitStatus(const char *msg,int status);

void printWaitIdSigInfo(const siginfo_t *infop);
#endif