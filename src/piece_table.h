#ifndef PIECE_TABLE_H_INCLUDED
#define PIECE_TABLE_H_INCLUDED
#include <stddef.h>
#define BUF_SZ 1024

typedef enum buffer_type { ORIGINAL_TEXT, ADDITIONAL_TEXT } BufferType_t;

typedef struct piece {
  BufferType_t buffer_type;
  int start_index_in_buffer;
  int length_in_buffer;
} Piece_t;

typedef struct piece_table {
  // char original_text[BUF_SZ];
  char *original_text;
  char additional_text[BUF_SZ];
  Piece_t pieces[BUF_SZ];
  int pieces_count;
} PieceTable_t;

PieceTable_t *PieceTable_create();

void PieceTable_delete_table(PieceTable_t *deleting_piece_table);

char PieceTable_index(PieceTable_t *piece_table, int index);

void PieceTable_insert(PieceTable_t *piece_table, int offset,
                       char *additional_fragment);

void PieceTable_delete(PieceTable_t *piece_table, int start_position,
                       int length);

void PieceTable_set_original_text(PieceTable_t *piece_table,
                                  char *new_original_text,
                                  size_t original_text_size);

#endif