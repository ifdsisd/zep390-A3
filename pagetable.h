#define TABLE_SIZE 32   
#include <sys/types.h>
typedef struct pageEntry{
    u_int32_t valid;
    u_int32_t frameNumber;
    u_int32_t reference;
}pageEntry;

pageEntry * initialize();

u_int32_t lowestRef(pageEntry * table,u_int32_t length,u_int32_t page_num);

u_int32_t updateRef();
u_int32_t currentRef();

