#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void print_george() {    // 每隔一秒鐘印出一次 George 的函數
  while (1) {    
    printf("George\n");    
    sleep(1);    
  }    
}    

void print_mary() {     // 每隔2秒鐘印出一次 Mary 的函數
  while (1) {    
    printf("Mary\n");    
    sleep(2);    
  }    
}    

int main() {     // 主程式開始
  pid_t pid1, pid2;

  pid1 = fork();    // 創建第一個子進程
  if (pid1 < 0) {
    perror("Fork failed for George");
    exit(1);
  }
  if (pid1 == 0) {   // 子進程1執行 print_george
    print_george();
    exit(0);
  }

  pid2 = fork();    // 創建第二個子進程
  if (pid2 < 0) {
    perror("Fork failed for Mary");
    exit(1);
  }
  if (pid2 == 0) {   // 子進程2執行 print_mary
    print_mary();
    exit(0);
  }

  // 主進程每隔一秒鐘就印出分隔行
  while (1) {     
    printf("----------------\n");    
    sleep(1);     
  }    

  // 等待子進程結束（實際上此處永遠不會到達，因為主進程無限循環）
  wait(NULL);
  wait(NULL);

  return 0;    
}
