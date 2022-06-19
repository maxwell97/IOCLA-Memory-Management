// implementarea structurilor utilizate

typedef unsigned int uint;
typedef unsigned char uchar;

typedef struct head {
    uchar type;
    uint len;
} head;

typedef struct data_structure {
    head *header;
    void *data;
} data_structure;