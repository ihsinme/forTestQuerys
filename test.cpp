#define NULL (0)
typedef unsigned long size_t;
typedef struct {} FILE;
FILE *ef;
void *malloc(size_t size);
size_t strlen(const char *str);
char * strcpy( char * destptr, const char * srcptr );
void free(void *ptr);
unsigned long copy_from_user (void * to, void * from, unsigned long n);
int fread(char *buf, int size, int count, FILE *fp);
int getSize3();
int getLen3(char *s);
FILE *getFile();
int getSize2()
{
  int m;
  m = getSize3();
  if (m<0)  return 0;
  return m;
}

int getSize1()
{
  int m;
  m = getSize3();
  if (m<0) m=0;
  return m;
}
int getLen4() {
  char c[1];
  ef = getFile();
  fread(c, 1, 1, ef);
  return (int)*c;
}
int getLen2()
{
  char str[4] = {(char)0xff, (char)0xff, (char)0xff, (char)0xff};
  ef = getFile();
  fread(str, 1, 4, ef);
  return getLen3(str);
}
void getLen1(int * len)
{
  *len = getLen2();
}
void goodTest1()
{
  char *ptr;
  int len = 10;
  ptr = (char *)malloc(len); // GOOD
  if(ptr) {
	 ptr[len-1] = 0;
	 free(ptr);
  }
}
void goodTest2(int a,int b)
{
  char *ptr; 
  int len = a+b;
  ptr = (char *)malloc(len); // GOOD
  if(ptr) {
	 ptr[len-1] = 0;
	 free(ptr);
  }
}
void goodTest3()
{
  char *ptr;
  int len ;
  len = 10;
  ptr = (char *)malloc(len); // GOOD
  if(ptr) {
	 ptr[len-1] = 0;
	 free(ptr);
  }
}
void goodTest4(int a,int b)
{
  char *ptr;
  int len;
  len = a+b;
  ptr = (char *)malloc(len); // GOOD
  if(ptr) {
	 ptr[len-1] = 0;
	 free(ptr);
  }
}
void goodTest5(int len)
{
  char *ptr;
  if(len == 0)
    return;
  ptr = (char *)malloc(len); // GOOD
  if(ptr) {
	 ptr[len-1] = 0;
	 free(ptr);
  }
}
void goodTest6(int len)
{
  char *ptr;
  if(len < 1)
    return;
  ptr = (char *)malloc(len); // GOOD
  if(ptr) {
	 ptr[len-1] = 0;
	 free(ptr);
  }
}
void goodTest7(int len)
{
  char *ptr = NULL;
  if (len < 1 || !(ptr = (char *)malloc(len))) // GOOD
    return;
	 ptr[len-1] = 0;
	 free(ptr);
}
void goodTest8(char * str)
{
	char *ptr = NULL;
	int len;
  
	if ((len = getSize2()) <= 1) len = 0;
  	else {
      	ptr = (char *)malloc(len);
      	strcpy(ptr, str); 
      	free(ptr);
  	}
}

void badTest1(int len)
{
  char *ptr;
  ptr = (char *)malloc(len); // BAD
  if(ptr) {
    ptr[len-1] = 0;
    free(ptr);
  }
}
void badTest2(int len,char buf[])
{
  char *ptr;
  ptr = (char *)malloc(len); // BAD
  if(ptr) {
    copy_from_user(ptr, buf, len);
    ptr[len-1] = 0;
    free(ptr);
  }
}
void badTest3(int len,char buf[])
{
  char *ptr;
   ptr = (char *)malloc(len); // BAD
  if(ptr) {
    copy_from_user(ptr, buf, len);
    strlen(ptr);
    free(ptr);
  }
}
void badTest4(char buf[],FILE *f1)
{
  char *ptr;
  int len;
  getLen1(&len);
  if (len > 256 || !(ptr = (char *)malloc(len))) // BAD
    return;
  if(fread(ptr, 1, len, f1) != len) {
    free(ptr);
    return;
  }
  if(ptr) {
    copy_from_user(ptr, buf, len);
    ptr[len-1] = 0;
    free(ptr);
  }
}
void badTest5(char buf[],FILE *f1)
{
  char *ptr;
  int len;
  len = getLen4();
  if (len > 256 || !(ptr = (char *)malloc(len))) // BAD
    return;
  if(fread(ptr, 1, len, f1) != len) {
    free(ptr);
    return;
  }
  if(ptr) {
    copy_from_user(ptr, buf, len);
    ptr[len-1] = 0;
    free(ptr);
  }
}
void badTest6(char buf[],FILE *f1)
{
  char *ptr;
  int len;
  len = getSize1();
  if (len > 256 || !(ptr = (char *)malloc(len))) // BAD
    return;
  if(fread(ptr, 1, len, f1) != len) {
    free(ptr);
    return;
  }
  if(ptr) {
    copy_from_user(ptr, buf, len);
    ptr[len-1] = 0;
    free(ptr);
  }
}
void badTest7(char buf[],FILE *f1)
{
  char *ptr;
  int len;
  len = getSize2();
  if (len > 256 || !(ptr = (char *)malloc(len))) // BAD
    return;
  if(fread(ptr, 1, len, f1) != len) {
    free(ptr);
    return;
  }
  if(ptr) {
    copy_from_user(ptr, buf, len);
    ptr[len-1] = 0;
    free(ptr);
  }
}


int memcmp(const void *buf1, const void *buf2, size_t count);
int strncmp( const void * string1, const void * string2, size_t num );
size_t strlen( unsigned char * string );

int mymemcmp(const void *buf1, const void *buf2, size_t count)
{
    return memcmp(buf1, buf2, count);
}
int mystrncmp( const void * string1, const void * string2, size_t num )
{
    return strncmp(string1, string2, num);
}
int mymemcmp1(const void *buf1, size_t count,const void *buf2)
{
    return memcmp(buf1, buf2, count);
}
int mystrncmp1(size_t num, const void * string1, const void * string2 )
{
    return strncmp(string1, string2, num);
}


int nbadTest1(unsigned char *pass,unsigned char*sec,int met){
  int ret=0;
  int len;
  len = strlen(sec);
  switch(met){
    case 1:
      ret = memcmp(pass, pass, len); // BAD
      break;
    case 2:
      ret = strncmp(pass, pass, len); // BAD
      break;
    default:
      ret = 1;
  }
    return ret;
}

int nbadTest1o(unsigned char *pass,unsigned char*sec,int met){
  int ret=0;
  int len;
  len = strlen(sec);
  switch(met){
    case 1:
      ret = mymemcmp(pass, pass, len); // BAD
      break;
    case 2:
      ret = mystrncmp(pass, pass, len); // BAD
      break;
    default:
      ret = 1;
  }
    return ret;
}
int nbadTest1o1(unsigned char *pass,unsigned char*sec,int met){
  int ret=0;
  int len;
  len = strlen(sec);
  switch(met){
    case 1:
      ret = mymemcmp1(pass, len, pass); // BAD
      break;
    case 2:
      ret = mystrncmp1(len, pass, pass); // BAD
      break;
    default:
      ret = 1;
  }
    return ret;
}
int ngoodTest1(unsigned char *pass,unsigned char*sec,int met){
  int ret=0;
  int len;
  len = strlen(sec);
  switch(met){
    case 1:
      ret = memcmp(sec, pass, len); // GOOD
      break;
    case 2:
      ret = strncmp(sec, pass, len); // GOOD
      break;
    default:
      ret = 1;
  }
    return ret;
}
void abort(void);
void exit (int state);
namespace std
{
	int exit(int state);
}
[[noreturn]] void nbadTest2(int i) { // BAD
  if (i > 0)
    throw "error";
  else if(i<0) exit(0);
}
[[noreturn]] void ngoodTest2(int i) { // GOOD
  if (i > 0)
    throw "error";
  else exit(0);
}
[[noreturn]] void ngoodTest2a(int i) { // GOOD
  if (i > 0)
    throw "error";
  else std::exit(0);
}

int main(void)
{
/* */
return 0;
}
