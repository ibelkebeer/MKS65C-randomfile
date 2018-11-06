#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

unsigned int randGen(){
  unsigned int* num = malloc(sizeof(unsigned int));
  int y = open("/dev/random", O_RDONLY);
  read(y, num, 4);
  close(y);
  int x = *num;
  free(num);
  return x;
}

int main(){
  unsigned int* ary = malloc(10 * sizeof(unsigned int));
  unsigned int* ary2 = malloc(10 * sizeof(unsigned int));
  int i;
  for(i = 0; i < 10; i ++){
    ary[i] = randGen();
  }
  printf("Array values:\n");
  for(i = 0; i < 10; i ++){
    printf("%d\n", ary[i]);
  }
  int y = open("file.txt", O_WRONLY | O_CREAT, 0644);
  if(y == -1){
    printf("Error opening file");
  }
  if(write(y, ary, 10 * sizeof(unsigned int)) == -1){
    printf("Error writing to file");
  }
  close(y);
  y = open("file.txt", O_RDONLY);
  if(read(y, ary2, 10 * sizeof(unsigned int)) == -1){
    printf("Error reading file");
  }
  close(y);
  printf("Array values copied:\n");
  for(i = 0; i < 10; i ++){
    printf("%d\n", ary2[i]);
  }
  return 0;
}
