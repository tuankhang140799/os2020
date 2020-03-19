#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main(){
  int pid1, pid2;
  printf("Main before fork()\n");
  pid1 = fork();
  if(pid1 == 0){
    printf("\tThe first child process running \"ps -ef\"\n");
    char* args[] = {"/bin/ps", "-ef", NULL};
    if(execvp("/bin/ps", args) < 0){
      printf("Execution failed \"ps -ef\"\n");
    }
  }
  else {
    waitpid(pid1, NULL, 0);
    printf("Parent after fork, child is %d\n\tContinue to create another child\n", pid1);
    pid2 = fork();
    if(pid2 == 0){
      printf("\tThe second child process running \"free -h\"\n");
      char* args[] = {"/usr/bin/free", "-h", NULL};
      if(execvp("/usr/bin/free", args) < 0){
        printf("Execution failed \"free -h\"\n");
      }
    }
    else {
      printf("This is parent after 2 forks, second child process is %d\nNothing to do more.\n", pid2);
      waitpid(pid2, NULL, 0);
    }
  }
  return 0;
}
