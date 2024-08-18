#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BASIC.h"

void list_init(LIST *lists)
{
    lists->index = 0;
    lists->MAX_LEN = LIST_LEN;
}

//向列表第一列末尾添加a，向第二列末尾添加b
void list_append(LIST *lists, u32 a, u32 b)
{
    lists->list[lists->index][0] = a;
    lists->list[lists->index][1] = b;
    lists->index++;

    if (lists->index >= lists->MAX_LEN)
    {
        err_handle(1, "list_append_out_mem",-1);
    }
}

//向列表第一列末尾添加a，向第二列末尾添加b
void expr_list_append(EXPR_LIST *lists, u32 a, u32 b)
{
    lists->list[lists->index][0] = a;
    lists->list[lists->index][1] = b;
    lists->index++;

    if (lists->index >= lists->MAX_LEN)
    {
        err_handle(1, "list_append_out_mem",-1);
    }
}

//删除列表第a行的两个数
void expr_list_pop(EXPR_LIST *lists, u32 a)
{
    u32 i;
    if (lists->index == 0)
    {
        err_handle(1, "list_pop_out_mem", -1);
    }

    for (i = a; i + 1 < lists->index; i++)
    {
        lists->list[i][0] = lists->list[i + 1][0];
        lists->list[i][1] = lists->list[i + 1][1];
    }

    lists->index--;
}

//打印list
void list_print(LIST *lists)
{
    u32 i,a,b;

    printf("\n");
    for (i = 0; i < lists->index; i++)
    {
        a = lists->list[i][0];
        b = lists->list[i][1];

        printf("[%u, %u]\n", a, b);
    }
    printf("\n");
}

//判断字符串A的index处是否以字符串B开头
u8 str_eq(char *A, u32 index, char *B)
{
    u8 flag = 1;
    u8 len = strlen(B);
    u32 i;

    for (i = index; i < len + index; i++)
    {
        if (A[i] != B[i - index])
        {
            flag = 0;
            break;
        }
    }

    return flag;
}

//判断字符串A的index处，是否有关键字
//如果有关键字，index自增以跳过关键词
int key_in(char *A, u32 *index)
{
    //enum KEY {NL, DOT, PRI, IF, ENDIF, WHILE, ENDWH, SPACE, VAR, FUNC, CALL, RET, RE, WR};
    if (str_eq(A, *index, "\r\n"))
    {
        *index += 1;
        return 0;
    }
    if (str_eq(A, *index, "\n"))
    {
        *index += 1;
        return 0;
    }
    if (str_eq(A, *index, ","))
    {
        *index += 1;
        return 1;
    }
    if (str_eq(A, *index, "pri"))
    {
        *index += 3;
        return 2;
    }
    if (str_eq(A, *index, "if"))
    {
        *index += 2;
        return 3;
    }
    if (str_eq(A, *index, "endif"))
    {
        *index += 5;
        return 4;
    }
    if (str_eq(A, *index, "while"))
    {
        *index += 5;
        return 5;
    }
    if (str_eq(A, *index, "endwh"))
    {
        *index += 5;
        return 6;
    }
    if (str_eq(A, *index, " "))
    {
        *index += 1;
        return 7;
    }
    if (str_eq(A, *index, "\t"))
    {
        *index += 1;
        return 7;
    }
    if (str_eq(A, *index, "var"))
    {
        *index += 3;
        return 8;
    }
    if (str_eq(A, *index, "func"))
    {
        *index += 4;
        return 9;
    }
    if (str_eq(A, *index, "call"))
    {
        *index += 4;
        return 10;
    }
    if (str_eq(A, *index, "ret"))
    {
        *index += 4;
        return 11;
    }
    if (str_eq(A, *index, "read"))
    {
        *index += 4;
        return 12;
    }
    if (str_eq(A, *index, "write"))
    {
        *index += 5;
        return 13;
    }

    return -1;
}

//判断字符串A的index处，是否有运算符
//如果有运算符，index自增以跳过关键词
int op_in(char *A, u32 *index)
{
    //enum OPS {EQ = 80, ADD, MIN, MUX, DIV, LB, RB, BIGER, SMALLER, IFEQ};
    if (str_eq(A, *index, "=="))
    {
        *index += 2;
        return 89;
    }
    else if (str_eq(A, *index, "="))
    {
        *index += 1;
        return 80;
    }
    else if (str_eq(A, *index, "+"))
    {
        *index += 1;
        return 81;
    }
    else if (str_eq(A, *index, "-"))
    {
        *index += 1;
        return 82;
    }
    else if (str_eq(A, *index, "*"))
    {
        *index += 1;
        return 83;
    }
    else if (str_eq(A, *index, "/"))
    {
        *index += 1;
        return 84;
    }
    else if (str_eq(A, *index, "("))
    {
        *index += 1;
        return 85;
    }
    else if (str_eq(A, *index, ")"))
    {
        *index += 1;
        return 86;
    }
    else if (str_eq(A, *index, ">"))
    {
        *index += 1;
        return 87;
    }
    else if (str_eq(A, *index, "<"))
    {
        *index += 1;
        return 88;
    }

    return -1;
}

//判断字符串A的index处，是否有其他符号
//如果有，index自增以跳过关键词，并将这些符号存入code_list
int miscop_in(char *A, u32 *index, LIST *lists, VARLISTS *varLists)
{
    long num;

    //MISC {TYPEVAR = 160, CONST_INT, STR};
    //以0~9开头的符号为数字
    if ((A[*index] >= 48) & (A[*index] <= 57))
    {
        //计算数字值
        num = A[*index] - 48;
        *index += 1;

        while ((A[*index] >= 48) & (A[*index] <= 57))
        {
            num = num * 10 + A[*index] - 48;
            *index += 1;
        }

        if ((num > 2147483647) | (num < -2147483648))
        {
            err_handle(2, A, *index);
        }

        list_append(lists, (u32)num, 161);

        return 161;
    }
    //以"开头的符号为字符串
    else if (A[*index] == '"')
    {
        *index += 1;
        while (A[*index] != '"')
        {
            list_append(lists, A[*index], 162);
            *index += 1;
        }
        *index += 1;

        return 162;
    }
    //将变量替换为代号
    else
    {
        int var_index = var_name_in(A, varLists, index);
        if (var_index >= 0)
        {
            *index += strlen(varLists->var_name[var_index]) + 1;
            list_append(lists, var_index, 160);
            return 160;
        }
    }


    return -1;
}

//获得变量的名字
void get_var_name(char *code_str, VARLISTS *varLists, u32 *index)
{
    u8 str_index;

    do
    {
        *index += 1;
    }
    while(code_str[*index] == ' ');  //跳过空格

    str_index = 0;

    do
    {
        varLists->var_name[varLists->var_num][str_index] = code_str[*index];
        printf("                %d_%c", code_str[*index], code_str[*index]);
        *index += 1;
        str_index++;
        if (str_index >= MAX_VAR_LEN - 1)
        {
            err_handle(3, code_str, *index);
        }
    }
    while((code_str[*index] != ' ') & (code_str[*index] != '\r')
            & (code_str[*index] != '\n'));  //读取字符直到有空格或换行
    varLists->var_name[varLists->var_num][str_index] = '\0';
    *index += 1;
    varLists->var_num += 1;

    if (varLists->var_num >= MAX_VAR_NUM)
    {
        err_handle(4, code_str, *index);
    }
}

//检查词语是否是变量，若是则获得变量编号
int var_name_in(char *code_str, VARLISTS *varLists, u32 *index)
{
    u8 str_index = 0;
    u32 var_index;

    char str[20];

    if (*index >= strlen(code_str))
    {
        return -1;
    }

    while(code_str[str_index + *index] != ' ')  //读取字符直到有空格
    {
        str[str_index] = code_str[str_index + *index];
        str_index++;

        if (str_index >= 20)
        {
            err_handle(3, code_str, *index);
        }
    }
    str[str_index] = '\0';

    var_index = 0;
    while (1)
    {
        //查找变量列表中是否有该变量
        if (var_index >= varLists->var_num)
        {
            return -1;
        }

        if (strcmp(str, varLists->var_name[var_index]) == 0)
        {
            return var_index;
        }
        var_index++;
    }
}

//打印变量信息
void pri_var(VARLISTS *varLists)
{
    u8 i;
    printf("\n");
    for (i = 0; i < varLists->var_num; i++)
    {
        printf("var_name:%s\n", varLists->var_name[i]);
    }
    printf("\n");
}

//计算一行代码中，最后一个元素的index
u32 find_end_index(LIST *lists, u32 start)
{
    u32 expr_end_index;

    for (expr_end_index = start; ; expr_end_index++)
    {
        enum KEY keywords = NL;
        if (lists->list[expr_end_index][1] == keywords)
        {
            return expr_end_index;
        }
    }
}

//打印字符串index后的15个字符
void pr_n15_char(char *code_str, u32 index)
{
    u8 ind = 0;
    printf("index: %u\n", index);
    printf("str:\n");
    for (ind = 0; ind < 15; ind++)
    {
        if (index+ind >= strlen(code_str))
        {
            break;
        }
        printf("%c", code_str[index+ind]);
    }
    printf("\n");
}

//分词器
void parser(char *code_str, LIST *lists, VARLISTS *varLists)
{
    u32 max_index = strlen(code_str);
    u32 index = 0;
    u32 line_num = 0;
    int key_in_num,op_in_num,miscop_in_num;

    //初始化代码序列
    list_init(lists);
    varLists->var_num = 0;

    while (1)
    {
        //pr_n15_char(code_str, index);

        //识别关键字
        key_in_num = key_in(code_str, &index);
        if (key_in_num >= 0)
        {
            if (key_in_num == 7)  //跳过空格
            {
                continue;
            }
            else if (key_in_num == 8)  //定义新变量
            {
                get_var_name(code_str, varLists, &index);
                continue;
            }

            list_append(lists, key_in_num, key_in_num);

            continue;
        }

        //识别操作符
        op_in_num = op_in(code_str, &index);
        if (op_in_num > 0)
        {
            list_append(lists, op_in_num, op_in_num);
            continue;
        }

        //识别其他类型标识符
        miscop_in_num = miscop_in(code_str, &index, lists, varLists);
        if (miscop_in_num > 0)
        {
            continue;
        }

        index += 1;
        //代码读完
        if (index >= max_index)
        {
            break;
        }

        err_handle(6, code_str, index);

    }
}

//计算对应符号的位置
//if对应endif while对应endwh endwh对应while   call add对应 func add
void index_match(char *code_str, LIST *lists)
{
    u32 index = 0;
    u32 index_ = 0;
    u8 keycount = 0;

    enum KEY keywords;

    while(1)
    {
        keywords = IF;
        if (lists->list[index][1] == keywords)
        {
            //处理if的对应符号
            index_ = index;
            while(1)
            {
                index_ += 1;

                //处理if嵌套
                keywords = IF;
                if (lists->list[index_][1] == keywords)
                {
                    keycount += 1;
                }

                keywords = ENDIF;
                if (index_ >= lists->index)
                {
                    err_handle(7, code_str, index);
                    return;
                }
                else if ((lists->list[index_][1] == keywords) & (keycount == 0))
                {
                    //保存if对应的endif的index
                    lists->list[index][0] = index_;
                    //print(index_)
                    break;
                }

                else if ((lists->list[index_][1] == keywords) & (keycount != 0))
                {
                    keycount -= 1;
                }
            }
        }

        keywords = WHILE;
        if (lists->list[index][1] == keywords)
        {
            //处理while的对应符号
            index_ = index;
            while(1)
            {
                index_ += 1;

                //处理while嵌套
                keywords = WHILE;
                if (lists->list[index_][1] == keywords)
                {
                    keycount += 1;
                }

                keywords = ENDWH;
                if (index_ >= lists->index)
                {
                    err_handle(8, code_str, index);
                    return;
                }
                else if ((lists->list[index_][1] == keywords) & (keycount == 0))
                {
                    //保存while对应的endif的index
                    lists->list[index][0] = index_ + 1;
                    //print(index_)
                    break;
                }

                else if ((lists->list[index_][1] == keywords) & (keycount != 0))
                {
                    keycount -= 1;
                }
            }
        }

        keywords = ENDWH;
        if (lists->list[index][1] == keywords)
        {
            //处理endwh的对应符号
            index_ = index;
            while(1)
            {
                index_ -= 1;

                //处理endwh嵌套
                keywords = ENDWH;
                if (lists->list[index_][1] == keywords)
                {
                    keycount += 1;
                }

                keywords = WHILE;
                if (index_ >= lists->index)
                {
                    err_handle(9, code_str, index);
                    return;
                }
                else if ((lists->list[index_][1] == keywords) & (keycount == 0))
                {
                    //保存if对应的endif的index
                    lists->list[index][0] = index_ - 1;
                    //print(index_)
                    break;
                }

                else if ((lists->list[index_][1] == keywords) & (keycount != 0))
                {
                    keycount -= 1;
                }
            }
        }

        keywords = CALL;
        if (lists->list[index][1] == keywords)
        {
            //处理call的对应符号
            u32 func_name = lists->list[index+1][0];
            u32 i;
            enum MISC misc;

            keywords = FUNC;
            //遍历代码，寻找对应的func
            for (i = 0; ; i++)
            {
                if (lists->list[i][1] == keywords)
                {
                    i++;

                    misc = CONST_INT;
                    if ((lists->list[i][1] == misc) & (lists->list[i][0] == func_name))
                    {
                        lists->list[index][0] = i + 1;
                        break;
                    }
                    else if (lists->list[i][1] != misc)
                    {
                        err_handle(11, code_str, index);
                    }
                }

                if (i >= lists->index)
                {
                    err_handle(12, code_str, index);
                    break;
                }
            }
        }

        keywords = FUNC;
        if (lists->list[index][1] == keywords)
        {
            //处理func的对应符号
            index_ = index;
            while(1)
            {
                index_ += 1;

                keywords = RET;
                if (index_ >= lists->index)
                {
                    err_handle(13, code_str, index);
                    return;
                }
                else if ((lists->list[index_][1] == keywords))
                {
                    //保存func对应的ret的index
                    lists->list[index][0] = index_ + 1;
                    //print(index_)
                    break;
                }
            }
        }

        index += 1;
        if (index >= lists->index)
        {
            break;
        }
    }
}

//表达式计算器
int expr(VARLISTS *varLists, LIST *lists, u32 expr_start, u32 expr_end)
{
    enum OPS ops, ops2, ops3;
    enum MISC misc_op, misc_op2;
    u32 i;
    u8 op;
    char bracket_num;
    u8 max_priority;
    long expr_value;
    u32 index;
    u32 ind;
    u32 priority;
    int num_A;
    int num_B;

    //标注优先级
    EXPR_LIST expr_list;   //创建LIST保存对应的符号优先级
    expr_list.index = 0;
    expr_list.MAX_LEN = MAX_EXPR_LEN;
    bracket_num = 0;   //记录小括号数量

    for (i = expr_start; i < expr_end; i++)
    {
        op = lists->list[i][1];

        ops = LB;
        if (op == ops)
        {
            bracket_num += 5;
            if (bracket_num > 120)  //小括号最多嵌套14层
            {
                expr_err(lists, varLists, 0, i);
            }
            continue;
        }

        ops = RB;
        if (op == ops)
        {
            bracket_num -= 5;

            if (bracket_num < 0)
            {
                expr_err(lists, varLists, 1, i);
            }
            continue;
        }

        ops = BIGER;
        ops2 = SMALLER;
        ops3 = IFEQ;
        //比较运算优先级为1 + 5 * 括号数
        if ((op == ops)|(op == ops2)|(op == ops3))
        {
            expr_list_append(&expr_list, op, 1 + bracket_num);
            continue;
        }

        ops = ADD;
        ops2 = MINUS;
        //加法优先级为2 + 5 * 括号数
        if ((op == ops)|(op == ops2))
        {
            expr_list_append(&expr_list, op, 2 + bracket_num);
            continue;
        }

        ops = MUX;
        ops2 = DIV;
        //乘法优先级为3 + 5 * 括号数
        if ((op == ops)|(op == ops2))
        {
            expr_list_append(&expr_list, op, 3 + bracket_num);
            continue;
        }

        misc_op = CONST_INT;
        //常数优先级为0
        if (misc_op == op)
        {
            u32 var_name = lists->list[i][0];
            expr_list_append(&expr_list, (int)var_name, 0);
            continue;
        }

        misc_op = TYPEVAR;
        //变量优先级为0
        if (misc_op == op)
        {
            u32 var_name = lists->list[i][0];
            int var_value = varLists->var_value[var_name];
            expr_list_append(&expr_list, var_value, 0);
            continue;
        }

        expr_err(lists, varLists, 2, i);
    }

    max_priority = 0;
    for (i = 0; i < expr_list.index; i++)
    {
        if (max_priority < expr_list.list[i][1])
        {
            max_priority = expr_list.list[i][1];
        }
    }
    //printf("max_priority %d\n", max_priority);

    for (priority = 0; priority < max_priority; priority++)
    {
        index = 0;

        while(1)
        {
            //寻找当前优先级对应的运算，优先计算高优先级
            index = 0;
            for (ind = 0; ind < expr_list.index; ind++)
            {
                if (expr_list.list[ind][1] == max_priority - priority)
                {
                    break;
                }
                index += 1;
            }

            //当前优先级无对应运算符
            if (index == expr_list.index)
            {
                break;
            }

            //打印计算过程
            /*
            printf("\n");
            for (u8 i = 0; i < expr_list.index; i++)
            {
                printf("%d ", expr_list.list[i][0]);
                printf("%d \n", expr_list.list[i][1]);
            }
            printf("\n");
            */

            if (index == 0)     //运算符出现在表达式开头
            {
                num_A = 0;
                expr_err(lists, varLists, 3, index);
            }
            else      //变量与常量
            {
                num_A = (int)expr_list.list[index - 1][0];
            }

            if (index == expr_list.index - 1)     //运算符出现在表达式结尾
            {
                num_B = 0;
                expr_err(lists, varLists, 3, index);
            }
            else      //变量与常量
            {
                num_B = (int)expr_list.list[index + 1][0];
            }
            //printf("A:%d B:%d \n\n", num_A, num_B);


            op = expr_list.list[index][0];
            //enum OPS {EQ = 80, ADD, MINUS, MUX, DIV, LB, RB, BIGER, SMALLER, IFEQ};
            if (op == 83)   //乘
            {
                expr_value = num_A * num_B;
            }
            else if (op == 84)  //除
            {
                expr_value = num_A / num_B;
            }
            else if (op == 81)  //加
            {
                expr_value = num_A + num_B;
            }
            else if (op == 82)  //减
            {
                expr_value = num_A - num_B;
            }
            else if (op == 87)
            {
                expr_value = num_A > num_B;
            }
            else if (op == 88)
            {
                expr_value = num_A < num_B;
            }
            else if (op == 89)
            {
                expr_value = (num_A == num_B);
            }

            if ((expr_value > 2147483647) | (expr_value < -2147483648))
            {
                expr_err(lists, varLists, 4, index);
            }

            //运算符与表达式替换为结果
            expr_list_pop(&expr_list, index-1);
            expr_list_pop(&expr_list, index-1);
            expr_list.list[index-1][0] = (int)expr_value;
            expr_list.list[index-1][1] = 0;
        }
    }

    return expr_list.list[0][0];
}

//打印分词后的结果
void pri_parser(LIST *lists, VARLISTS *varLists, u32 index_start, u32 index_end)
{
    u32 ind;
    u32 word_name, word_type;

    for (ind = index_start; ind < index_end; ind ++)
    {
        word_name = lists->list[ind][0];
        word_type = lists->list[ind][1];

        //printf("%u %u \n", word_name, word_type);
        printf("index=%u  ", ind);

        //enum KEY {NL, DOT, PRI, IF, ENDIF, WHILE, ENDWH, SPACE, VAR};
        if (word_type == 0)
        {
            printf("NL    NL\n");
        }
        else if (word_type == 1)
        {
            printf(",     ,\n");
        }
        else if (word_type == 2)
        {
            printf("pri   pri\n");
        }
        else if (word_type == 3)
        {
            printf("%d", word_name);
            printf("    if\n");
        }
        else if (word_type == 4)
        {
            printf("endif endif\n");
        }
        else if (word_type == 5)
        {
            printf("%d", word_name);
            printf("     while\n");
        }
        else if (word_type == 6)
        {
            printf("%d", word_name);
            printf("     endwh\n");
        }
        else if (word_type == 7)
        {
            printf("space space\n");
        }
        else if (word_type == 8)
        {
            printf("var   var\n");
        }
        else if (word_type == 9)
        {
            printf("%d", word_name);
            printf("   func\n");
        }
        else if (word_type == 10)
        {
            printf("%d", word_name);
            printf("    call\n");
        }
        else if (word_type == 11)
        {
            printf("ret   ret\n");
        }
        else if (word_type == 12)
        {
            printf("read  read\n");
        }
        else if (word_type == 13)
        {
            printf("write write\n");
        }

        //enum OPS {EQ = 80, ADD, MIN, MUX, DIV, LB, RB, BIGER, SMALLER, IFEQ};
        if (word_type == 80)
        {
            printf("=     =\n");
        }
        else if (word_type == 81)
        {
            printf("+     +\n");
        }
        else if (word_type == 82)
        {
            printf("-     -\n");
        }
        else if (word_type == 83)
        {
            printf("*     *\n");
        }
        else if (word_type == 84)
        {
            printf("/     /\n");
        }
        else if (word_type == 85)
        {
            printf("(     (\n");
        }
        else if (word_type == 86)
        {
            printf(")     )\n");
        }
        else if (word_type == 87)
        {
            printf(">     >\n");
        }
        else if (word_type == 88)
        {
            printf("<     <\n");
        }
        else if (word_type == 88)
        {
            printf("==   ==\n");
        }

        //enum MISC {TYPEVAR = 160, CONST_INT, STR};
        if (word_type == 160)
        {
            printf("%s   ", varLists->var_name[word_name]);
            printf("var_name\n");
        }
        else if (word_type == 161)
        {
            printf("%u   ", word_name);
            printf("const\n");
        }
        else if (word_type == 162)
        {
            printf("%c   ", (char)word_name);
            printf("char\n");
        }
    }
}

void basic_run(LIST *lists, VARLISTS *varLists, int mem[])
{
    enum KEY keywords;
    enum OPS ops;
    enum MISC misc_op;

    u32 index = 0;
    u8 op;
    u32 num;
	u32 var_name;

    //函数调用栈
    u32 func_stack[MAX_FUN_STACK];
    u32 func_stack_index = 0;

    while(1)
    {
        if (index >= lists->index)
        {
            break;  //  程序执行完
        }
        op = lists->list[index][1];
        num = lists->list[index][0];   //printf("index: %d\n", index);

        keywords = NL;
        if (op == keywords)
        {
            index++;
            continue;
        }

        keywords = PRI;
        //pri指令可以打印整数、变量、字符串，暂不支持表达式打印
        if (op == keywords)
        {
            while(1)
            {
                index++;
                op = lists->list[index][1];
                num = lists->list[index][0];

                misc_op = CONST_INT;
                if (op == misc_op)
                {
                    printf("%d ", (int)num);     //打印整数
                    continue;
                }

                misc_op = TYPEVAR;
                if (op == TYPEVAR)
                {
                    printf("%d ", (int)varLists->var_value[num]);     //打印变量的值
                    continue;
                }

                misc_op = STR;
                if (op == misc_op)
                {
                    printf("%c", num);     //打印字符
                    continue;
                }

                keywords = NL;
                if (op == keywords)
                {
                    break;
                }
            }

            index++;
            continue;
        }

        misc_op = TYPEVAR;
        //以变量开头的语句为赋值语句
        if (op == misc_op)
        {
            //寻找赋值语句结尾
            u32 expr_end_index = find_end_index(lists, index+2);

            int value = expr(varLists, lists, index + 2, expr_end_index);

            ops = EQ;
            if (lists->list[index + 1][1] != ops)
            {
                printf("\nindex:%d err: should be \"=\" \n", index);
            }

            //赋值
            varLists->var_value[num] = value;

            //表达式读完，跳过index
            index = expr_end_index + 1;

            continue;
        }

        keywords = WHILE;
        if (op == keywords)
        {
            u32 expr_end_index = find_end_index(lists, index+1);

            int value = expr(varLists, lists, index+1, expr_end_index);

            if (value == 1)
            {
                //表达式读完，跳过index，执行下一条语句
                index = expr_end_index + 1;
            }
            else
            {
                index = num;
            }

            continue;
        }

        keywords = ENDWH;
        if (op == keywords)
        {
            //跳到while
            index = num;
            continue;
        }

        keywords = IF;
        if (op == keywords)
        {
            u32 expr_end_index = find_end_index(lists, index+1);

            int value = expr(varLists, lists, index+1, expr_end_index);

            if (value == 1)
            {
                //表达式读完，跳过index，执行下一条语句
                index = expr_end_index + 1;
            }
            else
            {
                index = num;
            }

            continue;
        }

        //函数只能通过CALL调用，不能直接执行
        keywords = FUNC;
        if (op == keywords)
        {
            //跳转
            index = num;

            continue;
        }

        keywords = CALL;
        if (op == keywords)
        {
            //索引压栈
            func_stack[func_stack_index] = index + 2;
            func_stack_index++;

            //跳转
            index = num;

            continue;
        }

        keywords = RET;
        if (op == keywords)
        {
            //索引出栈

            func_stack_index--;
            index = func_stack[func_stack_index];

            continue;
        }

        keywords = READ;
        if (op == keywords)
        {
            u32 address;
            int num;

            //获得读取地址
            index += 2;
            address = lists->list[index][0];
            op = lists->list[index][1];
            //若是变量，则读取变量值
            misc_op = TYPEVAR;
            if (op == TYPEVAR)
            {
                address = varLists->var_value[address];
            }

            //读取mem
            if (address >= MEM_SIZE)
            {
                printf("mem read out of range\n");
            }
            num = mem[address];

            //赋值给变量或内存地址
            index--;
            var_name = lists->list[index][0];
            op = lists->list[index][1];
            //操作数是变量，将读取结果保存到变量中
            misc_op = TYPEVAR;
            if (op == TYPEVAR)
            {
                varLists->var_value[var_name] = num;
                index += 2;
                continue;
            }
            //操作数是常数，将读取结果保存到mem数组中
            misc_op = CONST_INT;
            if (op == CONST_INT)
            {
                mem[var_name] = num;
                index += 2;
                continue;
            }
        }

        keywords = WRITE;
        if (op == keywords)
        {
            u32 address;
            int num;

            //获得操作数
            index += 2;
            num = lists->list[index][0];
            op = lists->list[index][1];
            //若是变量，则读取变量值
            misc_op = TYPEVAR;
            if (op == TYPEVAR)
            {
                num = varLists->var_value[num];
            }

            //获取写入地址并写入
            index--;
            var_name = lists->list[index][0];
            op = lists->list[index][1];
            //地址是变量，以变量的值为目的地址
            misc_op = TYPEVAR;
            if (op == TYPEVAR)
            {
                address = varLists->var_value[var_name];
                index += 2;
            }
            //地址是常数，以常数为目的地址
            misc_op = CONST_INT;
            if (op == CONST_INT)
            {
                address = var_name;
                index += 2;
            }

            //写入mem
            if (address >= MEM_SIZE)
            {
                printf("mem read out of range\n");
            }
            mem[address] = num;
        }

        index += 1;
    }
}

u32 err_handle(u8 err, char *code_str, int index)
{
    printf("\n");
    switch(err)
    {
    case 1:
        printf("list out of index\n");
        break;
    case 2:
        printf("num too big\n");
        break;
    case 3:
        printf("name too long\n");
        break;
    case 4:
        printf("too many vars\n");
        break;
    case 5:
        printf("unrecognized var\n");
        break;
    case 6:
        printf("unrecognized word\n");
        break;
    case 7:
        printf("can't find endif\n");
        break;
    case 8:
        printf("can't find endwh\n");
        break;
    case 9:
        printf("can't find while\n");
        break;
    case 10:
        printf("func name too big\n");
        break;
    case 11:
        printf("func name should be num\n");
        break;
    case 12:
        printf("no   func\n");
        break;
    case 13:
        printf("should be \"=\"\n");
        break;
    case 14:
        printf("func no ret\"=\"\n");
        break;
    }

    printf("err char:%c at ", code_str[index]);
    pr_n15_char(code_str, index-1);

    return index;
}

u32 expr_err(LIST *lists, VARLISTS *varLists, u8 err, int index)
{
    u32 start, end;

    printf("expr err:\n");
    switch(err)
    {
    case 0:
        printf("too many \"(\"\n");
        break;
    case 1:
        printf("\")\" and \"(\" don't match\n");
        break;
    case 2:
        printf("unrecognized op\n");
        break;
    case 3:
        printf("op no const\n");
        break;
    case 4:
        printf("value too big\n");
        break;
    }

    printf("at:\n");

    if (index - 3 > 0)
    {
        start = index - 3;
    }
    else
    {
        start = 0;
    }

    if (index + 4 < lists->index)
    {
        end = index + 4;
    }
    else
    {
        end = lists->index;
    }

    pri_parser(lists, varLists, start, end);

    return 1;
}

