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
    Piece_t *current_piece=NULL;
    BufferType_t result_buffer_type;
    int pieces_count=0;
    int pieces_length=0;
    int previous_pieces_length=0;
    int buffer_relative_index=0;
    //int result_index=0;

    pieces=piece_table->pieces;
    pieces_count=piece_table->pieces_count;

    for(int i=0;i<pieces_count && index_not_found;i++){
        previous_pieces_length=pieces_length;

        current_piece=&piece_table->pieces[i];
        pieces_length+=current_piece->length_in_buffer;

        result_buffer_type=current_piece->buffer_type;

        if(pieces_length>index)
            index_not_found=0;
    }

    if(!index_not_found){
        buffer_relative_index=index-previous_pieces_length;

        switch(result_buffer_type){
            case ORIGINAL_TEXT:
                result_char=piece_table->original_text[current_piece->start_index_in_buffer+buffer_relative_index];
            break;
            case ADDITIONAL_TEXT:
                result_char=piece_table->additional_text[current_piece->start_index_in_buffer+buffer_relative_index];
            break;
        }
    }

    return result_char;
}



void PieceTable_insert(PieceTable_t *piece_table,int offset,char* additional_fragment){
    Piece_t *pieces=NULL;
    Piece_t *current_piece=NULL;
    BufferType_t result_buffer_type=ADDITIONAL_TEXT;
    
    int pieces_count=0;
    int pieces_length=0;
    int previous_pieces_length=0;
    int buffer_relative_index=0;
    
    int index_not_found=1;

    int piece_position=0;
    int additional_text_index=0;
    size_t additional_fragment_size=0;

    int current_piece_length=0;

    additional_fragment_size=strlen(additional_fragment);
    additional_text_index=(int)strlen(piece_table->additional_text);

    pieces=piece_table->pieces;
    
    pieces_count=piece_table->pieces_count;

    for(int i=0;i<pieces_count && index_not_found;i++){
        previous_pieces_length=pieces_length;

        current_piece=&piece_table->pieces[i];
        pieces_length+=current_piece->length_in_buffer;

        //result_buffer_type=current_piece->buffer_type;

        if(pieces_length>offset){
            index_not_found=0;
            piece_position=i;
        }
    }

    //first:
    strncpy(piece_table->additional_text+additional_text_index,additional_fragment,additional_fragment_size);

    //second:
    //insertion in 0 position
    if(!index_not_found){
        buffer_relative_index=offset-previous_pieces_length;
        
        printf("piece position is %d buffer relative index is %d\n\n",piece_position,buffer_relative_index);




        if(!buffer_relative_index){
            pieces_count++;

            for(int i=pieces_count-1;i>=piece_position;i--)
                pieces[i]=pieces[i-1];

            pieces[piece_position].start_index_in_buffer=additional_text_index;
            pieces[piece_position].length_in_buffer=additional_fragment_size;
            pieces[piece_position].buffer_type=result_buffer_type;
            

            piece_table->pieces_count=pieces_count;

            //shift additional buffer
        }
        else{
            current_piece=&pieces[piece_position];
            printf("\ninside piece\n");

            pieces_count+=2;

            for(int i=pieces_count-1;i>piece_position;i--)
                pieces[i]=pieces[i-2];

            piece_table->pieces_count=pieces_count;

            int source_piece_length=current_piece->length_in_buffer;


            current_piece_length=buffer_relative_index;
            //current_piece->start_index_in_buffer=buffer_relative_index;
            current_piece->length_in_buffer=current_piece_length;

            current_piece_length=additional_fragment_size;
            pieces[piece_position+1].start_index_in_buffer=additional_text_index;
            pieces[piece_position+1].length_in_buffer=current_piece_length;
            pieces[piece_position+1].buffer_type=result_buffer_type;

            current_piece_length=source_piece_length-buffer_relative_index;
            pieces[piece_position+2].start_index_in_buffer=buffer_relative_index;
            pieces[piece_position+2].length_in_buffer=current_piece_length;
            
        }

        // printf("additional fragment metrics:\n\tstart index = %d\n\tsize = %ld\n",additional_text_index,additional_fragment_size);
        // printf("additional buffer : %s\npieces count = %d\n",piece_table->additional_text,piece_table->pieces_count);
    }
    else{
        //мб тут как раз проверку на значение индекса сделать
        //т.е. если он больше длины таблицы кусочков, то возвращать 
        //fprintf(stderror,"%s","index out of range");
            pieces[pieces_count].start_index_in_buffer=additional_text_index;
            pieces[pieces_count].length_in_buffer=additional_fragment_size;
            pieces[pieces_count].buffer_type=result_buffer_type;
            
            pieces_count++;

            piece_table->pieces_count=pieces_count;
    }
}

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
    char *inserted_in_start_string=". And Hello, from piece table!";
    int offset=27;
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

    printf("Before:\n");
    for(int i=0; i< piece_table->pieces_count;i++)
                printf("piece %d info:\n\tbuffer type is %s\n\tstart position is %d\n\tlength is %d\n\n",i,(piece_table->pieces[i].buffer_type==ORIGINAL_TEXT)?"original":"additional",piece_table->pieces[i].start_index_in_buffer,piece_table->pieces[i].length_in_buffer);

    for(int i=0; i<piece_table->pieces_count;i++)
        piece_table_length+=piece_table->pieces[i].length_in_buffer;

    printf("Original text\t:\t\"%s\"\nAdditional text\t:\t\"%s\"\ntext length = %d\nResult text\t:\t\"",piece_table->original_text,piece_table->additional_text,piece_table_length);

    for(int i=0;i<piece_table_length;i++)
        putchar(PieceTable_index(piece_table,i));

    printf("\"\n\n");

    PieceTable_insert(piece_table,offset,inserted_in_start_string);

    piece_table_length=0;
    for(int i=0; i<piece_table->pieces_count;i++)
        piece_table_length+=piece_table->pieces[i].length_in_buffer;

    printf("After: piece table length = %d\n",piece_table_length);
    for(int i=0; i< piece_table->pieces_count;i++)
    printf("piece %d info:\n\tbuffer type is %s\n\tstart position is %d\n\tlength is %d\n\n",i,(piece_table->pieces[i].buffer_type==ORIGINAL_TEXT)?"original":"additional",piece_table->pieces[i].start_index_in_buffer,piece_table->pieces[i].length_in_buffer);

    printf("\n\nAfter insertion\t:\t\"");
    for(int i=0;i<piece_table_length;i++)
        putchar(PieceTable_index(piece_table,i));

    printf("\"\n\n");

    PieceTable_delete_table(piece_table);
    
    return 0;
}