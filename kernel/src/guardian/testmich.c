#include <stdio.h>

static int test(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j){
  printf("Hallo %d,%d,%d,%d,%d,%d,%d,%d,%d,%d",a,b,c,d,e,f,g,h,i,j);
}

int main(int argc, char *argv){
  test(1,2,3,4,5,6,7,8,9,10);
}
