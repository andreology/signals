// a demo on how fork spawn's processes
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_COUNT 10

void childProcess(void);
void parentProcess(void);

void main(void) {
  pid_t pid;

  pid = fork();

  if(pid ==0)
    childProcess();
  else if (pid > 0)
    parentProcess();
  else {
    printf("fork() failed!\n");
    return 1;
  }

  return 0;
}

void childProcess(void) {
  int i = 0;

  for(i = 1;i <= MAX_COUNT; i++)
    printf("  This line is from the child, value: %d\n", i);

  printf("  Child Process is done.\n");
}

void parentProcess(void) {
  int i = 0;

  for(i = 1;i <= MAX_COUNT; i++)
    printf("  This line is from the parent, value: %d\n", i);

  printf("  Parent Process is done.\n");
}
