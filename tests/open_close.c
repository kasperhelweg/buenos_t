/*
 * Userland helloworld
 */

#include "tests/lib.h"

static const size_t BUFFER_SIZE = 20;
static int open_files[10];


void print_open_files( void )
{
  int i = 0;

  syscall_list( open_files );
  puts("Open files for current process: [ ");  
  do {
    printf("%d, ", open_files[i]);
    i++;
  } while( i < 10 );  
  puts("]\n");
}

int test_open_file( const char* file )
{
  int open_file_rv;
  
  puts("\n---Opening file---\n");
  open_file_rv = syscall_open( file );
  
  return open_file_rv;
}

int test_close_file( int file )
{
  int close_file_rv;
   
  puts("\n---Closing file---\n");
  close_file_rv = syscall_close( file );
  
  return close_file_rv;
}


int test_read_file(char* read, int file, int position )
{
  read[0] = '\0';
  syscall_seek( file, position );

  puts("\n---Reading from file---\n");  
  return syscall_read( file, read, BUFFER_SIZE ); 
}

int test_write_file(char* write, int file, int position)
{
  puts("\n---writing to file---\n");  
  syscall_seek( file, position );
  return syscall_write( file, write, strlen(write) );
}


int main( void )
{
  int count, open_file_rv, close_file_rv;

  const char* file_fail = "[root]file_fail";

  heap_init( );
  
  char* read = (char*)malloc(BUFFER_SIZE); 
    
  puts("\n---Filesystem operations---\n");
 
  /***** TEST CREATE / OPEN / WRITE / READ / CLOSE / DELETE - SUCCESS *****/
  /***********************************************************************/
  
  /* CREATE FILE */
  puts("\n---Creating file---\n");
  const char* file = "[root]file";
  printf( "create file says: %d\n", syscall_create( file, 20) );

  /* OPEN FILE */
  /* try to open file - should return a valid filehandle */
  open_file_rv = test_open_file( file );
  printf("open_file says: %d\n", open_file_rv);
  
  /* print the files open for current process - should include the newly opened file */
  print_open_files( );
  
  /* WRITE TO FILE */
  count = test_write_file("Hello write!\n", open_file_rv, 0);
  printf("bytes written: %d\n", count);
  
  /* READ FROM FILE */
  /* should print the file content */
  count = test_read_file(read, open_file_rv, 0);
  printf("Chars read: %d\n", count);
  printf("Text read: %s", read);
  
  /* CLOSE FILE */
  /* try to close empty file- should return 0 */
  close_file_rv = test_close_file( open_file_rv );
  printf("close says: %d\n", close_file_rv);
  
  /* print the files open for current process - should be in initial state */
  print_open_files( );
  
  /* DELETE FILE */
  puts("\n---Deleting file---\n");
  printf("delete file says: %d\n", syscall_delete( file ));

  /***** TEST OPEN / CLOSE / READ - FAIL *****/
  /***********************************************************************/
  
  /* OPEN FILE */
  /* try to open empty file - should return file not found ( -5 ) */
  open_file_rv = test_open_file( file_fail );
  printf("open_file says: %d\n", open_file_rv);

  /* READ FROM FILE */
  /* should be -11 */
  count = test_read_file( read, open_file_rv, 0 );
  printf("Chars read: %d\n", count);
  printf("Text read: %s", read);
  
  puts("\n");
  
  /* CLOSE FILE */
  /* try to close empty file - should return file not open ( -11 ) */
  close_file_rv = test_close_file( open_file_rv );
  printf("close says: %d\n", close_file_rv);
  /***********************************************************************/


  puts("\n");
  syscall_exit(2);
  return 0;
}
