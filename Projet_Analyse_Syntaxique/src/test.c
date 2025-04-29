#include<stdio.h>

char q(void){
  return 97;
}
int main(int argc, char const *argv[])
{
  int main;
	int a = 0;
  a = a + 3;
  a;
  printf("Nombre a %d\n",a);
	return 0;
}

/*
test.c:4:9: error: ‘a’ undeclared (first use in this function)
    4 |         a = b;
      |         ^
test.c:4:9: note: each undeclared identifier is reported only once for each function it appears in
test.c:4:13: error: ‘b’ undeclared (first use in this function)
    4 |         a = b;
      |             ^
test.c:5:9: error: ‘c’ undeclared (first use in this function)
    5 |         c = 3;
      |         ^
test.c:7:13: error: implicit declaration of function ‘add’ [-Wimplicit-function-declaration]
    7 |         a = add(12,1);
      |             ^~~
test.c:8:9: error: implicit declaration of function ‘prout’ [-Wimplicit-function-declaration]
    8 |         prout("eerr");
      |         ^~~~~



test.c: In function ‘main’:
test.c:4:9: error: ‘a’ undeclared (first use in this function)
    4 |         a = b;
      |         ^
test.c:4:9: note: each undeclared identifier is reported only once for each function it appears in
test.c:4:13: error: ‘b’ undeclared (first use in this function)
    4 |         a = b;
      |             ^
test.c:5:9: error: ‘c’ undeclared (first use in this function)
    5 |         c = 3;
      |         ^
test.c:7:7: error: implicit declaration of function ‘sub’ [-Wimplicit-function-declaration]
    7 |   c = sub(12,5);
      |       ^~~
test.c:8:17: error: implicit declaration of function ‘add’ [-Wimplicit-function-declaration]
    8 |         a = a + add(12,1);
      |                 ^~~
test.c:9:9: error: implicit declaration of function ‘prout’ [-Wimplicit-function-declaration]
    9 |         prout("eerr");
      |         ^~~~~
*/