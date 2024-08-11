#define u8 unsigned char
#define u32 unsigned int
#define LIST_LEN 500
#define MAX_EXPR_LEN 40
#define MAX_VAR_NUM  120
#define MAX_VAR_LEN  15
#define MAX_FUN_STACK 10
#define MEM_SIZE 200

//�ؼ��֡��������ָ�����
//�ؼ���ö�٣����У����ţ�pri��if��endif��while��endwh, " ", var��func��call��ret, read, write
enum KEY {NL, DOT, PRI, IF, ENDIF, WHILE, ENDWH, SPACE, VAR, FUNC, CALL, RET, READ, WRITE};
//�����ö�٣�=��+��-��*��/��(��)��>��<��==
enum OPS {EQ = 80, ADD, MINUS, MUX, DIV, LB, RB, BIGER, SMALLER, IFEQ};
//������ʶ����
enum MISC {TYPEVAR = 160, CONST_INT, STR};

//һ������N�е�LIST��ģ��PYTHON�е�LIST
typedef struct lists
{
    u32  list[LIST_LEN][2];
    u32  index;
    u32  MAX_LEN;
} LIST;

//�洢���ʽ
typedef struct expr_lists
{
    u32  list[MAX_EXPR_LEN][2];
    u32  index;
    u32  MAX_LEN;
} EXPR_LIST;

//�����б�
typedef struct varLists
{
    u8  var_name[MAX_VAR_NUM][MAX_VAR_LEN];
    int  var_value[MAX_VAR_NUM];
    u32  var_num;
} VARLISTS;

//���º���ģ��PYTHON��LIST
void list_init(LIST *lists);
void list_append(LIST *lists, u32 a, u32 b);
void expr_list_append(EXPR_LIST *lists, u32 a, u32 b);
void expr_list_pop(EXPR_LIST *lists, u32 a);
void list_print(LIST *lists);


//�ж��ַ���A��index���Ƿ����ַ���B��ͷ
u8 str_eq(char *A, u32 index, char *B);
//�ж��ַ���A��index�����Ƿ��йؼ���
int key_in(char *A, u32 *index);
//�ж��ַ���A��index�����Ƿ��������
int op_in(char *A, u32 *index);
//�ж��ַ���A��index�����Ƿ�����������
int miscop_in(char *A, u32 *index, LIST *lists, VARLISTS *varLists);
//��ñ�������
void get_var_name(char *code_str, VARLISTS *varLists, u32 *index);
//�������Ƿ��Ǳ������������ñ������
int var_name_in(char *code_str, VARLISTS *varLists, u32 *index);
//��ӡ������Ϣ
void pri_var(VARLISTS *varLists);
//����һ�д����У����һ��Ԫ�ص�index
u32 find_end_index(LIST *lists, u32 start);


//�ִ�
void parser(char *code_str, LIST *lists, VARLISTS *varLists);
//��ӡ�ַ���index���15���ַ�
void pr_n15_char(char *code_str, u32 index);
//�����Ӧ���ŵ�λ��
void index_match(char *code_str, LIST *lists);
//���ʽ������
int expr(VARLISTS *varLists, LIST *lists, u32 expr_start, u32 expr_end);
//������
void basic_run(LIST *lists, VARLISTS *varLists, int mem[]);


//��ӡ�ִʺ�Ľ��
void pri_parser(LIST *lists, VARLISTS *varLists, u32 index_start, u32 index_end);


//�쳣����
u32 err_handle(u8 err, char *code_str, int index);
//�쳣����
u32 expr_err(LIST *lists, VARLISTS *varLists, u8 err, int index);
