basic_prog = "\
pri \"expr_test:\"\n\
i = 2 < 1\n\
i = i * i\n\
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
    pri \"smal\"\n\
    while 1\n\
    endwh \n\
    pri \"inner_endwh\"\n\
endwh \n\
while i > 2 \n\
    pri i\n\
    priNL \n\
    i = i - 1\n\
endwh \n\
pri \"prim\"\n\
b = 2 \n\
div = 2 \n\
flag = 0 \n\
while b < 100 \n\
    flag = 1 \n\
    div = 2 \n\
    while div < b / 2 \n\
        if ( b / div ) * div == b \n\
        flag = 0 \n\
        endif \n\
    div = div + 1 \n\
endwh \n\
if flag \n\
pri b \n\
priNL \n\
endif \n\
b = b + 1\n\
endwh \n\
pri \"prim_end\"\n\
"

#关键字编号
keyword = {\
"$NL"  : 0,\
","   : 1,\
"pri" : 2,\
"if"  : 3,\
"endif"  : 4,\
"while"  : 5,\
"endwh"  : 6,\
"priNL" :  7,\
"priSP" :  8,\
}

#运算符编号
op = {
"=" : 0+80,\
"+" : 1+80,\
"-" : 2+80,\
"*" : 3+80,\
"/" : 4+80,\
"(" : 5+80,\
")" : 6+80,\
">" : 7+80,\
"<" : 8+80,\
"==" : 9+80,\
}

#其他符号编号
misc_op = {
"var" : 0+160,\
"const_L": 1+160,\
"const_H": 2+160,\
"str"  : 3+160,\
"const_int" : 4+160,\
}

#成分划分与标注
basic_prog = basic_prog.replace("\n", " $NL ")
basic_prog = basic_prog.split(" ")
print("代码拆分：", basic_prog)

def add_prog_code(code_name, code_type, prog_code):
    prog_code.append([code_name, code_type])
    return

#计算标注优先级后的算式
def expr_labeled(expr_list, max_prior):
    #计算表达式
    for i in range(0, max_prior):
        index = 0
        
        #print(expr_list, max_prior - i)
        
        while True:
            #寻找当前优先级对应的运算
            #优先计算高优先级
            index = 0
            for expr_str in expr_list:
                if(expr_str[2] == max_prior - i):
                    break
                index += 1

            #当前优先级无对应运算符
            if (index == len(expr_list)):
                break

            #获取运算数
            num_A = 0
            num_B = 0
            if (index == 0):  #运算符出现在表达式开头
                num_A = 0
            elif (expr_list[index][1] == misc_op["var"]):  #变量
                var_index = expr_list[index][0]
                num_A = var_list[var_index][1]
            else :  #常量
                num_A = expr_list[index - 1][0]
                    
            if (index == len(expr_list) - 1):   #运算符出现在表达式结尾
                print("运算符出现在表达式结尾")
                num_B = 0
            elif (expr_list[index][1] == misc_op["var"]):  #变量
                var_index = expr_list[index][0]
                num_B = var_list[var_index][1]
            else :  #常量
                num_B = expr_list[index + 1][0]

            #计算结果
            result = 0
            if (expr_list[index][1] == op["*"]):
                result = num_A * num_B
            elif (expr_list[index][1] == op["/"]):
                result = num_A / num_B
                result =int(result)
            elif (expr_list[index][1] == op["+"]):
                result = num_A + num_B
            elif (expr_list[index][1] == op["-"]):
                result = num_A - num_B
            elif (expr_list[index][1] == op[">"]):
                if num_A > num_B :
                    result = 1
                else :
                    result = 0
            elif (expr_list[index][1] == op["<"]):
                if num_A < num_B :
                    result = 1
                else :
                    result = 0
            elif (expr_list[index][1] == op["=="]):
                if num_A == num_B :
                    result = 1
                else :
                    result = 0    

            #运算符与表达式替换为结果
            expr_list.pop(index-1)
            expr_list.pop(index-1)
            expr_list[index-1] =  [result, misc_op["const_int"], 0]

    return expr_list

#表达式计算
def expr(expression):
    #print("expr", expression)
    
    #表达式重新编号
    expr_list = []  #第一列保存符号，第二列保存符号类型，第三列保存优先级
    bracket_num = 0  #记录小括号数量
    const_L_value = 0

    #标注运算优先级
    for expr_str in expression:
        if (expr_str == [op["("], op["("]]):
            bracket_num += 5
        elif (expr_str == [op[")"], op[")"]]):
            bracket_num -= 5
        #比较优先级为1 + 5 * 括号数
        elif (expr_str in [[op[">"], op[">"]], [op["<"], op["<"]], [op["=="], op["=="]]]):
            expr_list.append([expr_str[0], expr_str[1], 1 + bracket_num])
        #加法优先级为2 + 5 * 括号数
        elif (expr_str in [[op["+"], op["+"]], [op["-"], op["-"]]]):
            expr_list.append([expr_str[0], expr_str[1], 2 + bracket_num])
        #乘法优先级为3 + 5 * 括号数
        elif (expr_str in [[op["*"], op["*"]], [op["/"], op["/"]]]):
            expr_list.append([expr_str[0], expr_str[1], 3 + bracket_num])
        #常数低八位
        elif (expr_str[1] == misc_op["const_L"]):
            const_L_value = expr_str[0]
        #常数优先级为0
        elif (expr_str[1] == misc_op["const_H"]):
            value = const_L_value + expr_str[0] * 256
            expr_list.append([value, misc_op["const_int"], 0])
        #变量优先级为0
        elif (expr_str[1] in [misc_op["var"], misc_op["var"]]):
            var_index = expr_str[0]
            expr_list.append([var_list[var_index][1], misc_op["const_int"], 0])
            
    #计算最大优先级
    max_prior = 0
    for expr_str in expr_list:
        if (max_prior < expr_str[2]):
            max_prior = expr_str[2]

    #反复计算表达式，直到只剩下一个常数
    expr_list = expr_labeled(expr_list, max_prior)

    return expr_list[0][0]


index = 0
prog_code = []
var_list = []
for index in range(len(basic_prog)):
    code_name = 0  #代码字符名称
    code_type = 0  #代码字符类型

    code_str = basic_prog[index]

    
    #空字符
    if  code_str =="" :
        pass
    #关键字
    elif  code_str in keyword :
        add_prog_code(keyword[code_str], keyword[code_str], prog_code)
    #运算符
    elif  code_str in op :
        add_prog_code(op[code_str], op[code_str], prog_code)
    #常量
    elif  code_str[0] in ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"] :
        #八位计算机，将常数拆成两部分存储
        code_name = int(code_str) & 255
        code_type = misc_op["const_L"]
        prog_code.append([code_name, code_type])
        code_name = int(code_str) & (255 * 256)
        code_name = int(code_name / 256)
        code_type = misc_op["const_H"]
        prog_code.append([code_name, code_type])
    #检测字符串开头
    elif  code_str[0] == "\"" :
        #字符串中间不能有空格
        #字符串拆解存储
        for str_char in code_str[1: ]:
            prog_code.append([str_char, misc_op["str"]])

    #变量
    else :
        #变量默认16位，初始值为0
        var_init_value = 0
        
        #判断变量是否定义过
        if  not ([code_str, 0] in var_list) :
            #检查变量定义是否合法
            #定义变量必须另起一行，在该行第一个单词声明变量
            if  index != 0 and basic_prog[index-1] != '$NL' :
                print("变量", code_str, "未定义\n")
            else:
                #加入变量列表
                var_list.append([code_str, var_init_value])
            
        code_name = var_list.index([code_str, var_init_value])
        code_type = misc_op["var"]
        prog_code.append([code_name, code_type])

print("变量列表：", var_list)
print("成分标注：", prog_code, " 长度:", len(prog_code),"\n\n")


#标记if  endwh  while对应的endif while  endwh的索引
index = 0
index_ = 0
keyword_count = 0
while True:
    if keyword["if"] == prog_code[index][1]:
        index_ = index 
        while True:
            index_ += 1

            #处理if嵌套
            if prog_code[index_][1] == keyword["if"] :
                keyword_count += 1

            if index_ >= len(prog_code) :
                print("错误，找不到与if对应的endif")
            elif prog_code[index_][1] == keyword["endif"] and keyword_count == 0:
                prog_code[index][0] = index_
                #print(index_)
                break
            elif prog_code[index_][1] == keyword["endif"] and keyword_count != 0:
                keyword_count -= 1

    elif keyword["while"] == prog_code[index][1]:
        index_ = index 
        while True:
            index_ += 1

            #处理while嵌套
            if prog_code[index_][1] == keyword["while"] :
                keyword_count += 1

            if index_ >= len(prog_code) :
                print("错误，找不到与while对应的endwh")
            elif prog_code[index_][1] == keyword["endwh"] and keyword_count == 0:
                prog_code[index][0] = index_
                break
            elif prog_code[index_][1] == keyword["endwh"] and keyword_count != 0:
                keyword_count -= 1

    elif keyword["endwh"] == prog_code[index][1]:
        index_ = index 
        while True:
            index_ -= 1

            #处理endwh嵌套
            if prog_code[index_][1] == keyword["endwh"] :
                keyword_count += 1

            if index_ < 0:
                print("错误，找不到与endwh对应的while")
            elif prog_code[index_][1] == keyword["while"] and keyword_count == 0:
                prog_code[index][0] = index_ - 1
                #print(index_)
                break
            elif prog_code[index_][1] == keyword["while"] and keyword_count != 0:
                keyword_count -= 1

    index += 1
    if index >= len(prog_code) :
        break
        


#代码运行
index = 0
code_line = []
line_count = 0
while True:
    code_slice = prog_code[index]

    #读取一行代码
    if  code_slice[1] != keyword["$NL"] :   #未读完一行
        code_line.append(code_slice)
    else :   #读完一行
        #空语句
        if  len(code_line) == 0 :
            pass
        #赋值语句
        elif  [op["="], op["="]] in code_line :
            #表达式合法性判断
            if  code_line[0][1] != misc_op["var"] :
                print("错误！表达式只能给变量赋值")
            elif  code_line[1] != [op["="], op["="]] :
                print("错误！表达式等号位置错误")
            
            #计算表达式的值
            value = expr(code_line[2: ])

            #赋值
            var_index = code_line[0][0]
            var_list[var_index][1] = value
        #打印语句
        elif  [keyword["pri"], keyword["pri"]] in code_line :
            if (code_line[1][1] != misc_op["str"]):
                #计算表达式的值
                value = expr(code_line[1: ])

                #打印
                print(value, end="")
            else :
                for str_char in code_line[1: ]:
                    #打印
                    print(str_char[0], end="")
        #if语句
        elif keyword["if"] == code_line[0][1]:
            #计算判断式的值
            value = expr(code_line[1: ])

            if value == 1 :
                pass
            else :
                #print("index: ", index)
                index = code_line[0][0]
                #print("index: ", index)

        #while语句
        elif keyword["while"] == code_line[0][1] :
            #计算判断式的值
            value = expr(code_line[1: ])

            if value == 1 :
                pass
            else :
                #print("index: ", index)
                index = code_line[0][0] 
                #print("index: ", index)

        #endwh语句
        elif keyword["endwh"] == code_line[0][1] :
            index = code_line[0][0]

        #priNL语句
        elif keyword["priNL"] == code_line[0][1] :
            print("")  #换行

        #priSP语句
        elif keyword["priSP"] == code_line[0][1] :
            print(" ", end="")
        
        #程序结束
        if index >= len(prog_code) - 1 :
            break

        code_line = []

    index += 1
            
        
        
    





