#include "BASIC.h"
#include "STC8.H"
#include <stdio.h>
#include <string.h>

char basic_prog[] = "\
pri \"expr_test:\"\n\
var i\n\
i = 9230\n\
i = 2 < 1 \n\
i = i * i \n\
i = i + 2 * ( 1 + ( 3 + 4 ) * 5 + 1 * 1 - 2 + ( 4 - 2 ) * ( 10 - 9 ) )\n\
pri i\n\
pri \"test_end:\"\n\
pri \"if_test:\"\n\
if i > 2\n\
    pri \"big\"\n\
endif \n\
if i < 2\n\
    pri \"smal\"\n\
    if i \n\
        pri \"inner_if\"\n\
    endif \n\
    pri \"inner_endif\"\n\
endif \n\
pri \"test_end:\"\n\
pri \"while_test:\"\n\
while i < 2 \n\
    pri \"small\"\n\
    while 1\n\
    endwh \n\
    pri \"inner_endwh\"\n\
endwh \n\
while i > 2 \n\
    pri i \n\
    i = i - 1 \n\
endwh \n\
pri \"prim\"\n\
var b \n\
var div \n\
var flag \n\
b = 2 \n\
div = 2 \n\
flag = 0 \n\
while b < 10000 \n\
    flag = 1 \n\
    div = 2 \n\
    while div < b / 2 + 1 \n\
        if ( b / div ) * div == b \n\
        flag = 0 \n\
        endif \n\
        div = div + 1\n\
    endwh \n\
    if flag \n\
    pri b \n\
    endif \n\
    b = b + 1 \n\
endwh \n\
pri \"prim_end\"\n\
\0\
";

void UartInit(void)		//19200bps@24.000MHz
{
    PCON &= 0x7F;		//�����ʲ�����
    SCON = 0x50;		//8λ����,�ɱ䲨����
    AUXR |= 0x40;		//��ʱ��ʱ��1Tģʽ
    AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
    TMOD &= 0x0F;		//���ö�ʱ��ģʽ
    TMOD |= 0x20;		//���ö�ʱ��ģʽ
    TL1 = 0xD9;		//���ö�ʱ��ʼֵ
    TH1 = 0xD9;		//���ö�ʱ����ֵ
    ET1 = 0;		//��ֹ��ʱ��%d�ж�
    TR1 = 1;		//��ʱ��1��ʼ��ʱ

    TI = 1;
}

char putchar(char c)
{
    SBUF = c;
    while(!TI);
    TI = 0;
	
	return c;
}

LIST lists;
VARLISTS varLists;
int mem[MEM_SIZE];
u8 RxTemp;
u8 volatile RxStop = 0;
u32 RxCount = 0;
char RxBuf[2048];
/* USER CODE END 0 */

int main(void)
{
    int b=2, div=2, flag=0;
    RxTemp = 0;
    RxStop = 0;
    RxCount = 0;
	
	UartInit();

    while (b < 100)
    {
        flag = 1;
        div = 2;
        while (div < b/2 + 1)
        {
            if ((b/div) * div == b)
            {
                flag = 0;
            }
            div++;
        }

        if (flag)
        {
            printf("%d ", b);
        }

        b++;
    }

    while (1)
    {
        printf("HELLOW\r\n");

        //if(RxStop == 1)
        {
            RxStop = 0;

            printf("%s\n", basic_prog);
            printf("code_len: %d\n", strlen(basic_prog));
            parser(basic_prog, &lists, &varLists);
            index_match(basic_prog, &lists);
            //pri_var(&varLists);
            //list_print(&lists);
            pri_parser(&lists, &varLists, 0, lists.index);
            printf("\n-----BASIC RUN-----\n");
            basic_run(&lists, &varLists, mem);

        }
		
		while (1);
    }
    
}
