#define u8 unsigned char
#define u32 unsigned int
#define LIST_LEN 500
#define MAX_EXPR_LEN 40
#define MAX_VAR_NUM  60
#define MAX_VAR_LEN  6
#define MAX_FUN_STACK 10
#define MEM_SIZE 200

//关键字、运算符与分隔符等
//关键字枚举：换行，逗号，pri，if，endif，while，endwh, " ", var，func，call，ret, read, write
enum KEY {NL, DOT, PRI, IF, ENDIF, WHILE, ENDWH, SPACE, VAR, FUNC, CALL, RET, READ, WRITE};
//运算符枚举：=，+，-，*，/，(，), int，>，<，==
enum OPS {EQ = 80, ADD, MINUS, MUX, DIV, LB, RB, INT, BIGER, SMALLER, IFEQ, OPS_END};
//其他标识符号
enum MISC {TYPEVAR = 160, CONST, STR};

//一个两列N行的LIST，模拟PYTHON中的LIST
typedef struct lists
{
    u32  list[LIST_LEN][2];
    u32  index;
    u32  MAX_LEN;
} LIST;

//存储表达式
typedef struct expr_lists
{
    float  list[MAX_EXPR_LEN][2];
    u32  index;
    u32  MAX_LEN;
} EXPR_LIST;

//变量列表
typedef struct varLists
{
    u8  var_name[MAX_VAR_NUM][MAX_VAR_LEN];
    float  var_value[MAX_VAR_NUM];
    u32  var_num;
} VARLISTS;

//以下函数模拟PYTHON的LIST
void list_init(LIST *lists);
void list_append(LIST *lists, u32 a, u32 b);
void expr_list_append(EXPR_LIST *lists, u32 a, u32 b);
void expr_list_pop(EXPR_LIST *lists, u32 a);
void list_print(LIST *lists);


//判断字符串A的index处是否以字符串B开头
u8 str_eq(char *A, u32 index, char *B);
//判断字符串A的index处，是否有关键字
int key_in(char *A, u32 *index);
//判断字符串A的index处，是否有运算符
int op_in(char *A, u32 *index);
//判断字符串A的index处，是否有其他符号
int miscop_in(char *A, u32 *index, LIST *lists, VARLISTS *varLists, int line_num);
//获得变量名字
void get_var_name(char *code_str, VARLISTS *varLists, u32 *index, int line_num);
//检查词语是否是变量，若是则获得变量编号
int var_name_in(char *code_str, VARLISTS *varLists, u32 *index, int line_num);
//打印变量信息
void pri_var(VARLISTS *varLists);
//计算一行代码中，最后一个元素的index
u32 find_end_index(LIST *lists, u32 start);


//分词
int parser(char *code_str, LIST *lists, VARLISTS *varLists);
//打印字符串index后的15个字符
void pr_n15_char(char *code_str, u32 index);

//计算对应符号的位置
void index_match(LIST *lists);

//表达式计算器
float expr(VARLISTS *varLists, LIST *lists, u32 expr_start, u32 expr_end);
//运行器
int basic_run(LIST *lists, VARLISTS *varLists, int mem[]);


//打印分词后的结果
void pri_parser(LIST *lists, VARLISTS *varLists, u32 index_start, u32 index_end);


//异常处理
u32 err_handle(u8 err, int line_num);
//异常处理
u32 expr_err(LIST *lists, VARLISTS *varLists, u8 err, int index);

//
