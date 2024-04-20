/** 
 * postfix.c
 *
 * School of Computer Science, 
 * Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command;

	printf("[----- [김건우] [2021041010] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1) 
        return '\0'; 
    else {
    	x = postfixStack[postfixStackTop--]; 
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x; 
}

int evalPop()
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--]; 
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
    char *exp = infixExp;
    char x;

    postfixStackTop = -1;
    postfixExp[0] = '\0';

    while (*exp != '\0')
    {
        x = *exp;
        if (getToken(x) == operand)  // x가 피연산자이면
        {	
            charCat(&x); // x를 postfixExp에 추가
        }
        else if (x == '(') // x가 '('이면
        {
            postfixPush(x); // x를 postfixStack에 push
        }
        else if (x == ')') // x가 ')'이면
        {
            while (postfixStackTop != -1 && postfixStack[postfixStackTop] != '(') // postfixStack의 top이 '('가 아닐 때까지
            {
                charCat(&postfixStack[postfixStackTop]); // postfixStack의 top을 postfixExp에 추가
                postfixPop(); // postfixStack의 top을 pop 한다
            }
            postfixPop(); // '('를 pop 한다
        }
        else 
        {
            while (postfixStackTop != -1 && getPriority(x) <= getPriority(postfixStack[postfixStackTop])) // x의 우선순위가 postfixStack의 top보다 작거나 같을 때까지
            {
                charCat(&postfixStack[postfixStackTop]); // postfixStack의 top을 postfixExp에 추가
                postfixPop(); // postfixStack의 top을 pop 한다
            }
            postfixPush(x); // x를 postfixStack에 push 한다
        }
        exp++; // 다음 문자로 이동
    }

    // Append remaining operators in the stack to postfix expression
    while (postfixStackTop != -1)
    {
        charCat(&postfixStack[postfixStackTop]);
        postfixPop();
    }

    printf("Postfix : %s\n", postfixExp);
}
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()
{
	/* postfixExp, evalStack을 이용한 계산 */
	char *exp = postfixExp; 
	char x;
	int a, b;
	while(*exp != '\0') 
	{
		x = *exp; // x에 exp의 문자를 저장
		if(getToken(x) == operand) // x가 피연산자이면
			evalPush(x - '0'); // x를 숫자로 변환하여 evalStack에 push
		else
		{
			b = evalPop(); // evalStack의 top을 pop하여 b에 저장
			a = evalPop(); // evalStack의 top을 pop하여 a에 저장
			switch(x) // x에 따라 계산
			{
				case '+':
					evalPush(a + b);
					break;
				case '-':
					evalPush(a - b);
					break;
				case '*':
					evalPush(a * b);
					break;
				case '/':
					evalPush(a / b);
					break;
			}
		}	
		exp++; // 다음 문자로 이동
	}
	evalResult = evalPop(); // evalStack의 top을 pop하여 evalResult에 저장
	printf("Eval result = %d\n", evalResult); // evalResult 출력
}	

