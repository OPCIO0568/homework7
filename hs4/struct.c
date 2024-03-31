#include <stdio.h>
struct student1 { //구조체 선언
    char lastName; //문자형 변수 선언
    int studentId; //int형 변수 선언
    char grade; //문자형 변수 선언
};

typedef struct { //구조체 선언
    char lastName; //문자형 변수 선언
    int studentId; //int형 변수 선언
    char grade; //문자형 변수 선언
} student2; //구조체 이름 선언

int main() {
    printf("[----- [kimgeonwoo] [2021041010] -----]\n");
    
    struct student1 st1 = {'A', 100, 'A'}; //구조체 변수 st1선언 및 lastName, studentId, grade에 값 넣어줌
    printf("st1.lastName = %c\n", st1.lastName); //st1.lastName 출력
    printf("st1.studentId = %d\n", st1.studentId); //st1.studentId 출력
    printf("st1.grade = %c\n", st1.grade); //st1.grade 출력
    student2 st2 = {'B', 200, 'B'}; //구조체 변수 st2선언 및 lastName, studentId, grade에 값 넣어줌
    printf("\nst2.lastName = %c\n", st2.lastName); //st2.lastName 출력
    printf("st2.studentId = %d\n", st2.studentId); //st2.studentId 출력
    printf("st2.grade = %c\n", st2.grade); //st2.grade 출력
    student2 st3; //구조체 변수 st3선언
    st3 = st2; //st3에 st2값 대입
    printf("\nst3.lastName = %c\n", st3.lastName); //st3.lastName 출력
    printf("st3.studentId = %d\n", st3.studentId); //st3.studentId 출력
    printf("st3.grade = %c\n", st3.grade); //st3.grade 출력

    /* equality test */
    if((st3.lastName == st2.lastName) && (st3.studentId == st2.studentId) && (st3.grade == st2.grade)  ) //st3와 st2의 값 각각 대조
    printf("equal\n"); //같으면 equal 출력
    else
    printf("not equal\n"); //다르면 not equal 출력
    return 0;
}