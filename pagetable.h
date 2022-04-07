#define TABLE_SIZE 32   
typedef struct pageEntry{
    int valid;
    int frameNumber;
    int reference;
}pageEntry;

pageEntry * initialize();

void enterAddress(pageEntry *pageTable,u_int32_t enter_address);