//demo on using sa_sigaction for IPC
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>

int flag = 1;
//handler which takes 3 parameters bcos we are using sa_sigaction
static void hdl (int sig, siginfo_t *siginfo, void *context) {
  printf("Sending PID: %ld, UID: %ld\n",
        (long)siginfo->si_pid, (long)siginfo->si_uid);
  flag = 0;
}

int main(int argc, char* argv[]) {
  struct sigaction act;

  memset(&act, '\0', sizeof(act));

  //use the sa_sigaction field bcos the handles has two additional parameters
  //hdl contains a siginfo_t and void pointer, see the function prototype
  act.sa_sigaction = &hdl;

  //The SA_SIGINFO flag tells sigaction() to use the sa_sigaction field, not sa_handler
  act.sa_flags = SA_SIGINFO;
  if(sigaction(SIGINT, &act, NULL) < 0) {
    perror("sigaction");
    return 1;
  }

  while(flag)
    sleep(3);
    return 0;
}
