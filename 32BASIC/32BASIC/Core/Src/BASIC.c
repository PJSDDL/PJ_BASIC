#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BASIC.h"

u8 error_code = 0;

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
        error_code = err_handle(1, -1);
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
        error_code = err_handle(1, -1);
    }
}

//删除列表第a行的两个数
void expr_list_pop(EXPR_LIST *lists, u32 a)
{
    if (lists->index == 0)
    {
        error_code = err_handle(1, -1);
    }

    for (u32 i = a; i + 1 < lists->index; i++)
    {
        lists->list[i][0] = lists->list[i + 1][0];
        lists->list[i][1] = lists->list[i + 1][1];
    }

    lists->index--;
}

//打印list
void list_print(LIST *lists)
{
    printf("\n");
    for (u32 i = 0; i < lists->index; i++)
    {
        u32 a = lists->list[i][0];
        u32 b = lists->list[i][1];

        printf("[%u, %u]\n", a, b);
    }
    printf("\n");
}

//判断字符串A的index处是否以字符串B开头
u8 str_eq(char *A, u32 index, char *B)
{
    u8 flag = 1;
    u8 len = strlen(B);

    for (u32 i = index; i < len + index; i++)
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
    //enum KEY {NL, DOT, PRI, IF, ENDIF, WHILE, ENDWH,
    // SPACE, VAR, FUNC, CALL, RET, RE, WR, INT};
    if (str_eq(A, *index, "\n"))
    {
        *index += 1;
        return NL;
    }
    if (str_eq(A, *index, ","))
    {
        *index += 1;
        return DOT;
    }
    if (str_eq(A, *index, "pri"))
    {
        *index += 3;
        return PRI;
    }
    if (str_eq(A, *index, "if"))
    {
        *index += 2;
        return IF;
    }
    if (str_eq(A, *index, "endif"))
    {
        *index += 5;
        return ENDIF;
    }
    if (str_eq(A, *index, "while"))
    {
        *index += 5;
        return WHILE;
    }
    if (str_eq(A, *index, "endwh"))
    {
        *index += 5;
        return ENDWH;
    }
    if (str_eq(A, *index, " "))
    {
        *index += 1;
        return SPACE;
    }
    if (str_eq(A, *index, "\t"))
    {
        *index += 1;
        return SPACE;
    }
    if (str_eq(A, *index, "var"))
    {
        *index += 3;
        return VAR;
    }
    if (str_eq(A, *index, "func"))
    {
        *index += 4;
        return FUNC;
    }
    if (str_eq(A, *index, "call"))
    {
        *index += 4;
        return CALL;
    }
    if (str_eq(A, *index, "ret"))
    {
        *index += 4;
        return RET;
    }
    if (str_eq(A, *index, "read"))
    {
        *index += 4;
        return READ;
    }
    if (str_eq(A, *index, "write"))
    {
        *index += 5;
        return WRITE;
    }

    return -1;
}

//判断字符串A的index处，是否有运算符
//如果有运算符，index自增以跳过关键词
int op_in(char *A, u32 *index)
{
    //enum OPS {EQ = 80, ADD, MINUS, MUX, DIV, LB, RB, BIGER, SMALLER, IFEQ};
    if (str_eq(A, *index, "=="))
    {
        *index += 2;
        return IFEQ;
    }
    else if (str_eq(A, *index, "="))
    {
        *index += 1;
        return EQ;
    }
    else if (str_eq(A, *index, "+"))
    {
        *index += 1;
        return ADD;
    }
    else if (str_eq(A, *index, "-"))
    {
        *index += 1;
        return MINUS;
    }
    else if (str_eq(A, *index, "*"))
    {
        *index += 1;
        return MUX;
    }
    else if (str_eq(A, *index, "/"))
    {
        *index += 1;
        return DIV;
    }
    else if (str_eq(A, *index, "("))
    {
        *index += 1;
        return LB;
    }
    else if (str_eq(A, *index, ")"))
    {
        *index += 1;
        return RB;
    }
    else if (str_eq(A, *index, ">"))
    {
        *index += 1;
        return BIGER;
    }
    else if (str_eq(A, *index, "<"))
    {
        *index += 1;
        return SMALLER;
    }
    else if (str_eq(A, *index, "int"))
    {
        *index += 3;
        return INT;
    }

    return -1;
}

//判断字符串A的index处，是否有其他符号
//如果有，index自增以跳过关键词，并将这些符号存入code_list
int miscop_in(char *A, u32 *index, LIST *lists, VARLISTS *varLists, int line_num)
{
    //enum MISC {TYPEVAR = 160, CONST_INT, STR};
    //以0~9开头的符号为数字
    if ((A[*index] >= 48) & (A[*index] <= 57))
    {
        //计算数字值
        float num = A[*index] - 48;
        *index += 1;

        u8 flag_decimal_point = 0; //检测是否遇到了小数点
        float bit_count = 0.1;

        while (((A[*index] >= '0') & (A[*index] <= '9')) | (A[*index] == '.'))
        {
            if (A[*index] == '.')
            {
                flag_decimal_point = 1;
            }
            else
            {
                if (flag_decimal_point == 0)
                {
                    num = num * 10 + A[*index] - '0';
                }
                else
                {
                    num = num + (A[*index] - '0') * bit_count;
                    bit_count *= 0.1;
                }
            }


            *index += 1;
        }

        if ((num > 2147483647) | (num < -2147483648))
        {
            error_code = err_handle(2, line_num);
        }

        //float以u32形式存储
        u32 *temp = (u32*)&num;
        list_append(lists, *temp, CONST);

        return CONST;
    }
    //以"开头的符号为字符串
    else if (A[*index] == '"')
    {
        *index += 1;
        while (A[*index] != '"')
        {
            list_append(lists, A[*index], STR);
            *index += 1;
        }
        *index += 1;

        return STR;
    }
    //其他字符串为变量
    //变量替换为代号
    else
    {
        int var_index = var_name_in(A, varLists, index, line_num);
        //printf("%d", var_index);
        if (var_index >= 0)
        {
            *index += strlen(varLists->var_name[var_index]);
            list_append(lists, var_index, TYPEVAR);
            return TYPEVAR;
        }
    }


    return -1;
}

//获得变量名称，并分配变量编号
void get_var_name(char *code_str, VARLISTS *varLists, u32 *index, int line_num)
{
    do
    {
        *index += 1;
    }
    while(code_str[*index] == ' ');  //跳过空格

    u8 str_index = 0;

    do
    {
        varLists->var_name[varLists->var_num][str_index] = code_str[*index];
        //printf("%d_%c", code_str[*index], code_str[*index]);
        *index += 1;
        str_index++;
        if (str_index >= MAX_VAR_LEN)
        {
            error_code = err_handle(3, line_num);
        }
    }
    while((code_str[*index] != ' ') & (code_str[*index] != '\r')
            & (code_str[*index] != '\n'));  //读取字符直到有空格或换行
    varLists->var_name[varLists->var_num][str_index] = '\0';
    *index += 1;
    varLists->var_num += 1;

    if (varLists->var_num >= MAX_VAR_NUM)
    {
        error_code = err_handle(4, line_num);
    }
}

//检查词语是否是变量，若是则计算变量编号
int var_name_in(char *code_str, VARLISTS *varLists, u32 *index, int line_num)
{
    u8 str_index = 0;
    char str[MAX_VAR_LEN];

    if (*index >= strlen(code_str))
    {
        return -1;
    }

    while (code_str[str_index + *index] >= 'a' &
            code_str[str_index + *index] <= 'z' )  //读取字符直到有逗号、空格、换行或右括号
    {
        str[str_index] = code_str[str_index + *index];
        str_index++;

        if (str_index >= MAX_VAR_LEN)
        {
            error_code = err_handle(3, line_num);
        }
    }
    str[str_index] = '\0';

    u32 var_index = 0;
    while (1)
    {
        //查找变量列表中是否有该变量
        if (var_index >= varLists->var_num)
        {
            return -1;
        }

        //printf("%s %s ,", str, varLists->var_name[var_index]);

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
    printf("\n");
    for (u8 i = 0; i < varLists->var_num; i++)
    {
        printf("var_name:%s\n", varLists->var_name[i]);
    }
    printf("\n");
}

//计算一行代码中，最后一个元素的index
u32 find_end_index(LIST *lists, u32 start)
{
    for (u32 expr_end_index = start; ; expr_end_index++)
    {
        if (lists->list[expr_end_index][1] == NL)
        {
            return expr_end_index;
        }

        if (lists->list[expr_end_index][1] == DOT)
        {
            return expr_end_index;
        }

        if (expr_end_index - start >= MAX_EXPR_LEN)
        {
            return 0;
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
int parser(char *code_str, LIST *lists, VARLISTS *varLists)
{
    u32 max_index = strlen(code_str);
    u32 index = 0;
    u32 line_num = 1;

    //初始化代码序列
    list_init(lists);
    varLists->var_num = 0;

    while (1)
    {
        //pr_n15_char(code_str, index);

        //识别关键字
        int key_in_num = key_in(code_str, &index);
        if (key_in_num >= 0)
        {
            if (key_in_num == SPACE)  //忽略空格
            {
                continue;
            }
            else if (key_in_num == NL) //计算行号
            {
                line_num++;
            }
            else if (key_in_num == VAR)  //不是关键字则定义新变量
            {
                get_var_name(code_str, varLists, &index, line_num + 1);
                continue;
            }

            list_append(lists, key_in_num, key_in_num);

            continue;
        }

        //识别运算符
        int op_in_num = op_in(code_str, &index);
        if (op_in_num > 0)
        {
            list_append(lists, op_in_num, op_in_num);
            continue;
        }

        //识别其他类型标识符
        int miscop_in_num =
            miscop_in(code_str, &index, lists, varLists, line_num + 1);
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

        error_code = err_handle(6, line_num + 1);

        return error_code;

    }
}

//计算对应符号的位置
//if对应endif while对应endwh endwh对应while   call add对应 func add
void index_match(LIST *lists)
{
    u32 index = 0;
    u32 index_ = 0;
    u8 keycount = 0;
    int line_num = 1;

    enum KEY keywords;

    while(1)
    {
        if (lists->list[index][1] == NL) //计算行号
        {
            line_num++;
        }

        if (lists->list[index][1] == IF)
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
                    error_code = err_handle(7, line_num + 1);
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
                    error_code = err_handle(8, line_num + 1);
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
                    error_code = err_handle(9, line_num + 1);
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

            keywords = FUNC;
            //遍历代码，寻找对应的func
            for (u32 i = 0; ; i++)
            {
                if (lists->list[i][1] == keywords)
                {
                    i++;

                    enum MISC misc = CONST;
                    if ((lists->list[i][1] == misc) & (lists->list[i][0] == func_name))
                    {
                        lists->list[index][0] = i + 1;
                        break;
                    }
                    else if (lists->list[i][1] != misc)
                    {
                        error_code = err_handle(11, line_num + 1);
                    }
                }

                if (i >= lists->index)
                {
                    error_code = err_handle(12, line_num + 1);
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
                    error_code = err_handle(13, line_num + 1);
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
float expr(VARLISTS *varLists, LIST *lists, u32 expr_start, u32 expr_end)
{
    enum OPS ops, ops2, ops3;
    enum MISC misc_op, misc_op2;

    //标注优先级
    EXPR_LIST expr_list;   //创建LIST保存对应的符号优先级
    expr_list.index = 0;
    expr_list.MAX_LEN = MAX_EXPR_LEN;
    char bracket_num = 0;   //记录小括号数量

    //计算运算符号优先级
    for (u32 i = expr_start; i < expr_end; i++)
    {
        u8 op = lists->list[i][1];

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

        ops = INT;
        //单目运算优先级为4 + 5 * 括号数
        if ((op == ops) )
        {
            expr_list_append(&expr_list, op, 4 + bracket_num);
            continue;
        }

        misc_op = CONST;
        //常数优先级为0
        if (misc_op == op)
        {
            u32 var_name = lists->list[i][0];
            float var_value = *(float*)&var_name;
            expr_list_append(&expr_list, var_value, 0);
            continue;
        }

        misc_op = TYPEVAR;
        //变量优先级为0
        if (misc_op == op)
        {
            u32 var_name = lists->list[i][0];
            float var_value = varLists->var_value[var_name];
            expr_list_append(&expr_list, var_value, 0);
            continue;
        }

        expr_err(lists, varLists, 2, i);
    }

    u8 max_priority = 0;
    for (u32 i = 0; i < expr_list.index; i++)
    {
        if (max_priority < expr_list.list[i][1])
        {
            max_priority = expr_list.list[i][1];
        }
    }
    //printf("max_priority %d\n", max_priority);

    for (u32 priority = 0; priority < max_priority; priority++)
    {
        u32 index = 0;

        while(1)
        {
            //寻找当前优先级对应的运算，优先计算高优先级
            index = 0;
            for (u32 ind = 0; ind < expr_list.index; ind++)
            {
                if (expr_list.list[ind][1] == max_priority - priority)
                {
                    break;
                }
                index += 1;
            }

            //打印计算过程
            //#define debug_print_calcu
#ifdef debug_print_calcu
            printf("\n");
            for (u8 i = 0; i < expr_list.index; i++)
            {
                printf("%f ", expr_list.list[i][0]);
                printf("%.1f\n", expr_list.list[i][1]);
            }
            printf("\n");
#endif


            //当前优先级无对应运算符
            if (index == expr_list.index)
            {
                break;
            }

            float num_A;
            if (index == 0)     //运算符出现在表达式开头
            {
                num_A = 0;
                //expr_err(lists, varLists, 3, index);
            }
            else      //变量与常量
            {
                num_A = expr_list.list[index - 1][0];
            }

            float num_B;
            if (index == expr_list.index - 1)     //运算符出现在表达式结尾
            {
                num_B = 0;
                expr_err(lists, varLists, 3, index);
            }
            else      //变量与常量
            {
                num_B = expr_list.list[index + 1][0];
            }
            //printf("A:%d B:%d \n\n", num_A, num_B);

            float expr_value;
            u8 is_Binocular_operators = 1;  //双目运算符与单目运算符有不同处理逻辑

            u8 op = expr_list.list[index][0];

            if (op == MUX)   //乘
            {
                expr_value = num_A * num_B;
            }
            else if (op == DIV)  //除
            {
                expr_value = num_A / num_B;
            }
            else if (op == ADD)  //加
            {
                expr_value = num_A + num_B;
            }
            else if (op == MINUS)  //减
            {
                expr_value = num_A - num_B;
            }
            else if (op == INT)  //取整
            {
                expr_value = (int)num_B;
                is_Binocular_operators = 0;
            }
            else if (op == BIGER)  //大于
            {
                expr_value = num_A > num_B;
            }
            else if (op == SMALLER)  //小于
            {
                expr_value = num_A < num_B;
            }
            else if (op == IFEQ)  //等于
            {
                if (abs(num_A - num_B) < 1e-5)
                {
                    expr_value = 1;
                }
                else
                {
                    expr_value = 0;
                }
            }

            if ((expr_value > 2147483647) | (expr_value < -2147483648))
            {
                expr_err(lists, varLists, 4, index);
            }

            //运算符与表达式替换为结果
            if (is_Binocular_operators)
            {
                expr_list_pop(&expr_list, index-1);
                expr_list_pop(&expr_list, index-1);
                expr_list.list[index-1][0] = expr_value;
                expr_list.list[index-1][1] = 0;
            }
            else
            {
                expr_list_pop(&expr_list, index);
                expr_list.list[index][0] = expr_value;
            }
        }
    }

    //printf("e:%f\n", expr_list.list[0][0]);

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
        printf("%u  ", ind);

        //enum KEY {NL, DOT, PRI, IF, ENDIF, WHILE, ENDWH, SPACE, VAR};
        if (word_type == NL)
        {
            printf("NL    NL\n");
        }
        else if (word_type == DOT)
        {
            printf(",     ,\n");
        }
        else if (word_type == PRI)
        {
            printf("pri   pri\n");
        }
        else if (word_type == IF)
        {
            printf("%d", word_name);
            printf("    if\n");
        }
        else if (word_type == ENDIF)
        {
            printf("endif endif\n");
        }
        else if (word_type == WHILE)
        {
            printf("%d", word_name);
            printf("     while\n");
        }
        else if (word_type == ENDWH)
        {
            printf("%d", word_name);
            printf("     endwh\n");
        }
        else if (word_type == SPACE)
        {
            printf("space space\n");
        }
        else if (word_type == VAR)
        {
            printf("var   var\n");
        }
        else if (word_type == FUNC)
        {
            printf("%d", word_name);
            printf("   func\n");
        }
        else if (word_type == CALL)
        {
            printf("%d", word_name);
            printf("    call\n");
        }
        else if (word_type == RET)
        {
            printf("ret   ret\n");
        }
        else if (word_type == READ)
        {
            printf("read  read\n");
        }
        else if (word_type == WRITE)
        {
            printf("write write\n");
        }

        //enum OPS {EQ = 80, ADD, MINUX, MUX, DIV, LB, RB, INT, BIGER, SMALLER, IFEQ};
        if (word_type == EQ)
        {
            printf("=     =\n");
        }
        else if (word_type == ADD)
        {
            printf("+     +\n");
        }
        else if (word_type == MINUS)
        {
            printf("-     -\n");
        }
        else if (word_type == MUX)
        {
            printf("*     *\n");
        }
        else if (word_type == DIV)
        {
            printf("/     /\n");
        }
        else if (word_type == LB)
        {
            printf("(     (\n");
        }
        else if (word_type == RB)
        {
            printf(")     )\n");
        }
        else if (word_type == INT)
        {
            printf("int     int\n");
        }
        else if (word_type == BIGER)
        {
            printf(">     >\n");
        }
        else if (word_type == SMALLER)
        {
            printf("<     <\n");
        }
        else if (word_type == IFEQ)
        {
            printf("==   ==\n");
        }

        //enum MISC {TYPEVAR = 160, CONST, STR};
        if (word_type == TYPEVAR)
        {
            printf("%s   ", varLists->var_name[word_name]);
            printf("var_name\n");
        }
        else if (word_type == CONST)
        {
            printf("%f   ", *(float*)&word_name);
            printf("const\n");
        }
        else if (word_type == STR)
        {
            printf("%c   ", (char)word_name);
            printf("char\n");
        }
    }
}

int basic_run(LIST *lists, VARLISTS *varLists, int mem[])
{
    enum KEY keywords;
    enum OPS ops;
    enum MISC misc_op;

    u32 index = 0;
    u8 op, op_;
    u32 num, num_;

    //函数调用栈
    u32 func_stack[MAX_FUN_STACK];
    u32 func_stack_index = 0;

    while(1)
    {
        if(error_code)
        {
            return -1;
        }

        if (index >= lists->index)
        {
            return 1;  //  程序执行完
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
        //pri指令可以打印数、变量、字符串，暂不支持表达式打印
        if (op == keywords)
        {
            while(1)
            {
                index++;
                op = lists->list[index][1];
                num = lists->list[index][0];
                op_ = lists->list[index+1][1];
                num_ = lists->list[index+1][0];

                if (op == NL)
                {
                    break;
                }

                if (op == DOT)
                {
                    continue;
                }

                //判断是否是表达式
                if ((op_ >= EQ & op_ <= OPS_END) | (op >= EQ & op <= OPS_END))
                {
                    //寻找赋值语句结尾
                    u32 expr_end_index = find_end_index(lists, index);

                    //printf("\n\n\ns %d %d ", index, expr_end_index);
                    //pri_parser(lists, varLists, index, expr_end_index + 1);

                    float value = expr(varLists, lists, index, expr_end_index);

                    printf("%f ", value);

                    index = expr_end_index - 1;

                    continue;
                }

                if (op == CONST)
                {
                    float *temp = (float*)&num;
                    printf("%f ", *temp);     //打印数
                    continue;
                }

                if (op == TYPEVAR)
                {
                    float *temp = (float*)&(varLists->var_value[num]);
                    printf("%f ", *temp);     //打印变量的值
                    continue;
                }

                if (op == STR)
                {
                    printf("%c", num);     //打印字符
                    continue;
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

            float value = expr(varLists, lists, index + 2, expr_end_index);

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
            if (op == misc_op)
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
            u32 var_name = lists->list[index][0];
            op = lists->list[index][1];
            //操作数是变量，将读取结果保存到变量中
            misc_op = TYPEVAR;
            if (op == misc_op)
            {
                varLists->var_value[var_name] = num;
                index += 2;
                continue;
            }
            //操作数是常数，将读取结果保存到mem数组中
            misc_op = CONST;
            if (op == misc_op)
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
            if (op == misc_op)
            {
                num = varLists->var_value[num];
            }

            //获取写入地址并写入
            index--;
            u32 var_name = lists->list[index][0];
            op = lists->list[index][1];
            //地址是变量，以变量的值为目的地址
            misc_op = TYPEVAR;
            if (op == misc_op)
            {
                address = varLists->var_value[var_name];
                index += 2;
            }
            //地址是常数，以常数为目的地址
            misc_op = CONST;
            if (op == misc_op)
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

u32 err_handle(u8 err, int line_num)
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

    printf("at line: %d\n", line_num);

    return 1;
}

u32 expr_err(LIST *lists, VARLISTS *varLists, u8 err, int index)
{
    printf("\nexpr err:\n");
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
    u32 start, end;

    if (index - 4 > 0)
    {
        start = index - 4;
    }
    else
    {
        start = 0;
    }

    if (index + 0 < lists->index)
    {
        end = index + 0;
    }
    else
    {
        end = lists->index;
    }

    pri_parser(lists, varLists, start, end);

    error_code = 1;

    return 1;
}

