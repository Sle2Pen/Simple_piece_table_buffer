#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SZ 1024

typedef enum buffer_type{
    ORIGINAL_TEXT,
    ADDITIONAL_TEXT
}BufferType_t;

typedef struct piece{
    BufferType_t buffer_type;
    int start_index_in_buffer;
    int length_in_buffer;
}Piece_t;

typedef struct piece_table{
    char original_text[BUF_SZ];
    char additional_text[BUF_SZ];
    Piece_t pieces[BUF_SZ];
    int pieces_count;
}PieceTable_t;

char PieceTable_index(PieceTable_t *piece_table,int index){
    char result_char=0;
    int index_not_found=1;
    Piece_t *pieces=NULL;
    Piece_t *piece=NULL;
    int pieces_count=0;

    pieces=piece_table->pieces;
    pieces_count=piece_table->pieces_count;

    // for(int i=0;i<pieces_count && index_not_found;i++){
    //     if(pieces[i].length)
    // }

    return result_char;
}

// void PieceTable_insert(PieceTable_t *piece_table,int offset,char* additional_fragment){
//     char* additional_text=NULL;
//     Piece_t *additional_piece=NULL;

//     size_t additional_fragment_size=0;
//     int new_pieces_count=0;

//     additional_fragment_size=strlen(additional_fragment);

//     new_pieces_count=*piece_table->pieces_count;
//     additional_text=piece_table->additional_text;
//     additional_piece=&piece_table->pieces[new_pieces_count];

//     additional_piece.buffer_type=ADDITIONAL_TEXT;

//     new_pieces_count++;

//     *piece_table->pieces_count=new_pieces_count;
// }

void PieceTable_delete(){

}

void PieceTable_set_original_text(PieceTable_t *piece_table,char* new_original_text){
    for(int i=0;i<BUF_SZ && new_original_text[i];i++)
    piece_table->original_text[i]=new_original_text[i];
}

PieceTable_t* PieceTable_create() {
    PieceTable_t *result_piece_table = NULL;
    size_t piece_table_size=0;

    piece_table_size=sizeof(PieceTable_t);

    result_piece_table=malloc(piece_table_size);

    memset(result_piece_table->original_text,'\0',BUF_SZ);

    memset(result_piece_table->additional_text,'\0',BUF_SZ);

    return result_piece_table;
}



void PieceTable_delete_table(PieceTable_t* deleting_piece_table){
    free(deleting_piece_table);
}

int main() {
    char *original_string="ipsum sit amet";
    char *additional_string="Lorem deletedtext dolor";
    PieceTable_t *piece_table=NULL;
    Piece_t *current_piece=NULL;
    int piece_table_length=0;
    
    piece_table=PieceTable_create();

    PieceTable_set_original_text(piece_table,original_string);

    strncat(piece_table->additional_text,additional_string,strlen(additional_string));

    current_piece=&piece_table->pieces[0];
    current_piece->buffer_type=ADDITIONAL_TEXT;
    current_piece->start_index_in_buffer=0;
    current_piece->length_in_buffer=6;

    current_piece=&piece_table->pieces[1];
    current_piece->buffer_type=ORIGINAL_TEXT;
    current_piece->start_index_in_buffer=0;
    current_piece->length_in_buffer=5;

    current_piece=&piece_table->pieces[2];
    current_piece->buffer_type=ADDITIONAL_TEXT;
    current_piece->start_index_in_buffer=17;
    current_piece->length_in_buffer=6;

    current_piece=&piece_table->pieces[3];
    current_piece->buffer_type=ORIGINAL_TEXT;
    current_piece->start_index_in_buffer=5;
    current_piece->length_in_buffer=9;

    piece_table->pieces_count=4;

    for(int i=0; i<piece_table->pieces_count;i++)
        piece_table_length+=piece_table->pieces[i].length_in_buffer;

    printf("Original text : \"%s\"\nAdditional text : \"%s\"\ntext length = %d\n",piece_table->original_text,piece_table->additional_text,piece_table_length);

    for(int i=0;i<piece_table_length;i++)
        PieceTable_index(piece_table,i);

    PieceTable_delete_table(piece_table);
    
    return 0;
}