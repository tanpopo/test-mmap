#include    <stdio.h>
#include    <fcntl.h>
#include    <sys/types.h>
#include    <unistd.h>
#include    <sys/mman.h>

/*
ref:
http://www.ncad.co.jp/~komata/c-kouza20.htm
*/
#define NUMBER (10000)

typedef char SSS;

void main()
{
  int   fd;
  char  c;
  long  psize,size;
  SSS   *ptr;
  char  buf[512];
  int   i;

  printf("start ...\n");
  if((fd=open("MapFile0",O_RDWR|O_CREAT,0666))==-1){
    perror("open");
    return;
  }
  printf("open file success!\n");

  #ifdef BSD
  psize=getpagesize();
  #else
  psize=sysconf(_SC_PAGE_SIZE);
  #endif
  printf("get page size success! size=%ld\n", psize);
  size=(NUMBER*sizeof(SSS)/psize+1)*psize;
  printf("size=%ld\n", size);

  /* seek to the end of file and write zero*/
  if(lseek(fd,size,SEEK_SET)<0){
    perror("lseek");
    return;
  }
  printf("seek file success!\n");

  if(read(fd,&c,sizeof(char))==-1){
    c='\0';
  }
  printf("read file success!\n");

  if(write(fd,&c,sizeof(char))==-1){
    perror("write");
    return;
  }
  printf("write file success!\n");

  //map
  ptr=(SSS *)mmap(0,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
  if((int)ptr==-1){
    perror("mmap");
    return;
  }
  printf("mmap success!\n");

/*  for(i=0;i<NUMBER;i++){*/
  for(i=0;i<1;i++){
    strcpy(&ptr[i], (const char*)'a');
  }
  printf("strcpy success!\n");

  msync(ptr,size,MS_SYNC);
  printf("msync success!\n");

  if(munmap(ptr,size)==-1){
    perror("munmap");
  }

  close(fd);

  printf("completed!\n");

}
