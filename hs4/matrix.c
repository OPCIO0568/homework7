#include<stdio.h>
#include<stdlib.h>

int print_matrix(int** M, int x, int y); //행렬을 출력하는 함수
int addition_matrix(int** M, int** N, int x, int y); //행렬의 덧셈을 하는 함수
int subtraction_matrix(int** M, int** N, int x, int y); //행렬의 뺄셈을 하는 함수
int transpose_matrix(int** M, int x, int y); //전치행렬을 구하는 하는 함수
int multiply_matrix(int** M, int** N, int x, int y);//행렬의 곱셈을 하는 함수
int free_matrix(int** M, int x); //동적할당 해제 함수

int main(){

    int x,y; 

    scanf("%d %d",&y,&x); //x y 값을 받아온다

    int** A=(int**)malloc(x*sizeof(int)); //행렬 A를 동적할당한다
    for(int i=0;i<x;i++){
        A[i]=(int*)malloc(y*sizeof(int));
    }

    int** B=(int**)malloc(x*sizeof(int)); //행렬 B를 동적할당한다
    for(int i=0;i<x;i++){
        B[i]=(int*)malloc(y*sizeof(int));
    }

    for(int i=0;i<x;i++){ //행렬 A에 랜덤값을 넣는다
        for(int j=0;j<y;j++){
            A[i][j]=rand()%9+1;
        }
    }
    for(int i=0;i<x;i++){ //행렬 B에 랜덤값을 넣는다
        for(int j=0;j<y;j++){
            B[i][j]=rand()%9+1;
        }
    }

    printf("[----- [KIMGEONWOO] [2021041010] -----]\n");

    print_matrix(A,x,y); //행렬 A를 출력한다
    printf("\n");
    print_matrix(B,x,y); //행렬 B를 출력한다
    printf("\n");


    addition_matrix(A,B,x,y);
    printf("\n");
    subtraction_matrix(A,B,x,y);
    printf("\n");
    transpose_matrix(A,x,y);
    printf("\n");
    multiply_matrix(A,B,x,y);
    printf("\n");


    free_matrix(A,x);
    free_matrix(B,x);   

    return 0;

}


int print_matrix(int** M, int x, int y){
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            printf("%2d ", M[i][j]); //행렬 M[i][j]를 출력한다
        }
        printf("\n");
    }

    return 0;

}

int free_matrix(int** M, int x){
    
    for(int i=0;i<x;i++){
        free(M[i]); //행렬 M[i]를 해제한다
    }
    free(M); //행렬 M을 해제한다

    return 0;

}

int addition_matrix(int** M, int** N, int x, int y){

    for(int i = 0 ; i < x ; i++){
        for(int j = 0 ; j < y ; j++){
            printf("%2d ", M[i][j] + N[i][j]); //행렬 M[i][j]와 N[i][j]를 더한 값을 출력한다
        }
        printf("\n");
    }

    return 0;

}

int subtraction_matrix(int** M, int** N, int x, int y){

    for(int i = 0 ; i < x ; i++){
        for(int j = 0 ; j < y ; j++){
            printf("%2d ", M[i][j] - N[i][j]); //행렬 M[i][j]와 N[i][j]를 뺀 값을 출력한다
        }
        printf("\n");
    }

    return 0;

}

int transpose_matrix(int** M, int x, int y){

    if(x!=y){ //x와 y가 같지 않으면 계산이 되지않아 0을 반환한다.
        return 0;
    }

    for(int i = 0 ; i < x ; i++){
        for(int j = 0 ; j < y ; j++){
            printf("%2d ", M[j][i]); //행렬 M의 전치행렬을 출력한다.
        }
        printf("\n");
    }

    return 0;

}

int multiply_matrix(int** M, int** N, int x, int y){

    if(x!=y){ //x와 y가 같지 않으면 계산이 되지않아 0을 반환한다.
        return 0;
    }

    int** C=(int**)malloc(x*sizeof(int)); //행렬 C를 동적할당한다.
    for(int i=0;i<x;i++){
        C[i]=(int*)malloc(y*sizeof(int));
    }

    int temp = 0;
    //x = 3, y = 3 인경우
    for(int i = 0 ; i < x ; i++){
        for(int j = 0 ; j < y ; j++){
            for(int k = 0 ; k < y ; k++){
                temp += M[i][k] * N[k][j]; //C[0][0]일때 temp에 A[0][0] * B[0][0] + A[0][1] * B[1][0] + A[0][2] * B[2][0]
            }
            C[i][j] = temp; //행렬 c[0][0]에 temp값을 넣는다.
            temp = 0; //temp값을 초기화한다.
        }
    }


    for(int i = 0 ; i < x ; i++){ //행렬 C를 출력한다.
        for(int j = 0 ; j < y ; j++){
            printf("%3d ", C[i][j]);
        }
        printf("\n");
    }

    free_matrix(C,x); //행렬 C를 해제한다.

    return 0;
}