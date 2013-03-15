/*
 * Userland helloworld
 */

#include "tests/lib.h"

static const size_t BUFFER_SIZE = 20;

int main(void)
{
  /* should try to open file */
  /* int* open_files; */
  int open_file_rv, close_file_rv;
  const char* file = "[root]file";
  /* const char* file_empty = "[root]empty_file"; */
  const char* file_fail = "[root]file_fail";

  char *read;
  int count;

  heap_init( );
 
  puts("---Filesystem operations---\n");
  /***** TEST OPEN / CLOSE / READ - SUCCESS *****/
  /* try to open empty file */
  open_file_rv = syscall_open( file );
  printf("open_file says: %d\n", open_file_rv);
  
  puts("---Reading from file---\n");
  read = (char*)malloc(BUFFER_SIZE);
  count = syscall_read( open_file_rv, read, BUFFER_SIZE );
  printf("Chars read: %d\n", count);
  printf("Text read: %s", read);
   
  /* try to close empty file */
  close_file_rv = syscall_close( open_file_rv );
  printf("close says: %d\n", close_file_rv);

  /*****  *****/

  /***** TEST OPEN AND CLOSE - FAIL *****/
  /* try to open empty file */
  open_file_rv = syscall_open( file_fail );
  printf("open_file says: %d\n", open_file_rv);

  /* try to close empty file */
  close_file_rv = syscall_close( 3 );
  printf("close says: %d\n", close_file_rv);

  syscall_exit(2);
  return 0;
}
