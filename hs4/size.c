#include<stdio.h>
#include<stdlib.h>
void main()
{
int **x;
printf("[----- [kimgeonwoo] [2021041010] -----]\n");
printf("sizeof(x) = %lu\n", sizeof(x)); //int형 포인터 포인터 크기의 출력 주소값
printf("sizeof(*x) = %lu\n", sizeof(*x)); //이중포인터여서 포인터의 크기값 출력
printf("sizeof(**x) = %lu\n", sizeof(**x)); //두번 접근했기때문에 주소값이 아닌int형 변수의 크기값 출력
}
