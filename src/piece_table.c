#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct piece_table{
    char* original_text;
    int length;
    int pieces_count;
} PieceTable_t;

// Функция для создания piece table
PieceTable_t* PieceTable_create(const char *initial_text) {
    PieceTable_t *result_piece_table = NULL;
    char *text=NULL;
    size_t piece_table_size=0;
    size_t initial_text_size=0;

    piece_table_size=sizeof(PieceTable_t);
    initial_text_size=strlen(initial_text);
    initial_text_size++;
    
    result_piece_table=malloc(piece_table_size);

    result_piece_table->pieces_count=0;

    text=(char*)malloc(initial_text_size);

    memset(text,'\0',initial_text_size);

    initial_text_size--;

    for(int i=0;i<(int)initial_text_size;i++)
        text[i]=initial_text[i];

    text[initial_text_size]='\0';

    result_piece_table->original_text=text;
    result_piece_table->length =strlen(initial_text);

    return result_piece_table;
}

void PieceTable_delete(PieceTable_t* deleting_piece_table){
    free(deleting_piece_table);
}

int main() {
    PieceTable_t *piece_table=PieceTable_create("Hello, world!\n");

    for(int i=0; i<(int) piece_table->length;i++)
        putchar(piece_table->original_text[i]);

    PieceTable_delete(piece_table);
    
    return 0;
}