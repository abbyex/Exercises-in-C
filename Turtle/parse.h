#define MAXMOVES 1000
#define MAXNUMSIZE 20
#define strsame(A,B) (strcmp(A, B)==0) /* SOURCE: Neill's 01's example*/
#define ERROR(PHRASE) {fprintf(stderr, "Fatal Error, %s. Occured in %s, line %d\n", PHRASE, __FILE__, __LINE__); exit(EXIT_FAILURE); }
#define MISSING(PHRASE) {fprintf(stderr, "Missing %s. Occured in %s, line %d\n", PHRASE, __FILE__, __LINE__); exit(EXIT_FAILURE); }
/* SOURCE: Adapted from Neill's 01's example*/

struct prog{
char words[MAXMOVES][MAXNUMSIZE];
int counter;
int loops;
};
typedef struct prog prog;

typedef enum bool {false, true} bool;

void main_instr(prog *p);
void* instr_list(prog *p);
bool instr(prog *p);
void init_struct(prog *p);

bool var(prog* p);
bool num(prog *p);
bool varnum(prog *p);
bool do_loop(prog* p);
bool set_loop(prog *p);
bool polish(prog *p);
bool op_func(prog *p);

bool is_decimal(prog *p);
bool is_negative(prog *p);

bool is_instr(prog* p);
bool is_num(prog* p);
bool is_start_bracket(prog* p);
bool is_end_bracket(prog* p);
bool is_letter(prog* p);
bool is_lower(prog *p);
