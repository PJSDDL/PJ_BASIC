#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BASIC.h"


char basic_prog[] = "\
pri \"expr_test:\"\n\
var i\n\
i = 9230\n\
pri i + 1 \n\
i = 2 < 1 \n\
i = i * i \n\
i = i + 2 * (1 + ( 3 + 4 ) * 5 + 1 * 1 - 2 + ( 4 - 2 ) * ( 10 - 9 ) )\n\
pri i\n\
pri \"expr_test_end:\"\n\
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
pri \"if_test_end:\"\n\
pri \"while_test:\"\n\
while i < 2 \n\
    pri \"small\"\n\
    while 1\n\
    endwh \n\
    pri \"inner_endwh\"\n\
endwh \n\
pri \"while_test_end:\"\n\
while i > 2 \n\
    pri i \n\
    i = i - 1 \n\
endwh \n\
pri \"prim \"\n\
var b \n\
var div \n\
var flag \n\
b = 2 \n\
div = 2 \n\
flag = 0 \n\
while b < 100 \n\
    flag = 1 \n\
    div = 2 \n\
    while div < b / 2 + 1 \n\
        if int ( b / div ) * div == b \n\
            flag = 0 \n\
        endif \n\
        div = div + 1\n\
    endwh \n\
    if flag \n\
    pri \"b:\", b, \"\n\" \n\
    endif \n\
    b = b + 1 \n\
endwh \n\
pri \"prim_end\"\n\
";


/*
char basic_prog[] = "\
pri \"t: \" , 21.13 , 5 / 2 , int ( 5 / 2 ) \n\
";
*/

/*
//if-endif测试
char basic_prog[] = "\
var flag \n\
flag =  - 3 \n\
if flag > 1\n\
    pri flag \n\
    if flag > 2\n\
        pri flag \n\
    endif \n\
endif \n\
";
*/

/*
//while-endwh测试
char basic_prog[] = "\
var flag \n\
flag = 11 \n\
while flag > 1 \n\
    pri flag \n\
endwh \n\
";
*/

/*
//子函数测试
char basic_prog[] = "\
var i\n\
i = 1\n\
i = i + 2 * ( 1 + ( 3 + 4 ) * 5 + 1 * 1 - 2 + ( 4 - 2 ) * ( 10 - 9 ) )\n\
call 1\n\
pri \"func_test\n\"  \n\
pri \"var\" 0 \": i = \" i \n\
while 1 \n\
endwh \n\
func 1\n\
i = i + 1\n\
ret \n\
";
*/

//数组读写测试
/*
char basic_prog[] = "\
var i\n\
i = 100 \n\
var addr \n\
addr = 4 \n\
write 3 3 \n\
read i 3 \n\
pri i  \n\
write addr 321 \n\
read i addr \n\
pri i  \n\
";*/
//

LIST lists;
VARLISTS varLists;
int mem[MEM_SIZE];

int main()
{
    //C语言质数计算
    int b=2, div=2, flag=0;
    while (b < 10000)
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

    //分词测试
    u32 index = 0;
    printf("%d\n", key_in("if i > 10", &index));
    index = 12;
    printf("%d\n", key_in("if i > 10 \n endif", &index));

    printf("code_len: %d\n", strlen(basic_prog));
    parser(basic_prog, &lists, &varLists);
    index_match(basic_prog, &lists);
    //pri_var(&varLists);
    //list_print(&lists);
    //pri_parser(&lists, &varLists, 0, lists.index);
    printf("\n-----BASIC RUN-----\n");
    basic_run(&lists, &varLists, mem);

    /*
    for (u32 *i = &lists_test; ; i++)
    {
        printf("%d\n", *i);
    }*/

    return 0;
}
