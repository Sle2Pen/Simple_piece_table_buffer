#include "piece_table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char PieceTable_index(PieceTable_t *piece_table, int index) {
  char result_char = 0;
  int index_not_found = 1;
  Piece_t *current_piece = NULL;
  BufferType_t result_buffer_type;
  int pieces_count = 0;
  int pieces_length = 0;
  int previous_pieces_length = 0;
  int buffer_relative_index = 0;

  pieces_count = piece_table->pieces_count;

  for (int i = 0; i < pieces_count && index_not_found; i++) {
    previous_pieces_length = pieces_length;

    current_piece = &piece_table->pieces[i];
    pieces_length += current_piece->length_in_buffer;

    result_buffer_type = current_piece->buffer_type;

    if (pieces_length > index)
      index_not_found = 0;
  }

  if (!index_not_found) {
    buffer_relative_index = index - previous_pieces_length;

    switch (result_buffer_type) {
    case ORIGINAL_TEXT:
      result_char =
          piece_table->original_text[current_piece->start_index_in_buffer +
                                     buffer_relative_index];
      break;
    case ADDITIONAL_TEXT:
      result_char =
          piece_table->additional_text[current_piece->start_index_in_buffer +
                                       buffer_relative_index];
      break;
    }
  }

  return result_char;
}

void PieceTable_insert(PieceTable_t *piece_table, int offset,
                       char *additional_fragment) {
  Piece_t *pieces = NULL;
  Piece_t *current_piece = NULL;
  BufferType_t result_buffer_type = ADDITIONAL_TEXT;

  int pieces_count = 0;
  int pieces_length = 0;
  int previous_pieces_length = 0;
  int buffer_relative_index = 0;

  int index_not_found = 1;

  int piece_position = 0;
  int additional_text_index = 0;
  size_t additional_fragment_size = 0;

  int current_piece_length = 0;

  additional_fragment_size = strlen(additional_fragment);
  additional_text_index = (int)strlen(piece_table->additional_text);

  pieces = piece_table->pieces;

  pieces_count = piece_table->pieces_count;

  for (int i = 0; i < pieces_count && index_not_found; i++) {
    previous_pieces_length = pieces_length;

    current_piece = &piece_table->pieces[i];
    pieces_length += current_piece->length_in_buffer;

    if (pieces_length > offset) {
      index_not_found = 0;
      piece_position = i;
    }
  }

  // first:
  strncpy(piece_table->additional_text + additional_text_index,
          additional_fragment, additional_fragment_size);

  // second:
  // insertion in 0 position
  if (!index_not_found) {
    buffer_relative_index = offset - previous_pieces_length;

    printf("piece position is %d buffer relative index is %d\n\n",
           piece_position, buffer_relative_index);

    if (!buffer_relative_index) {
      pieces_count++;

      for (int i = pieces_count - 1; i >= piece_position; i--)
        pieces[i] = pieces[i - 1];

      pieces[piece_position].start_index_in_buffer = additional_text_index;
      pieces[piece_position].length_in_buffer = additional_fragment_size;
      pieces[piece_position].buffer_type = result_buffer_type;

      piece_table->pieces_count = pieces_count;

      // shift additional buffer
    } else {
      current_piece = &pieces[piece_position];
      printf("\ninside piece\n");

      pieces_count += 2;

      for (int i = pieces_count - 1; i > piece_position; i--)
        pieces[i] = pieces[i - 2];

      piece_table->pieces_count = pieces_count;

      int source_piece_length = current_piece->length_in_buffer;

      current_piece_length = buffer_relative_index;
      // current_piece->start_index_in_buffer=buffer_relative_index;
      current_piece->length_in_buffer = current_piece_length;

      current_piece_length = additional_fragment_size;
      pieces[piece_position + 1].start_index_in_buffer = additional_text_index;
      pieces[piece_position + 1].length_in_buffer = current_piece_length;
      pieces[piece_position + 1].buffer_type = result_buffer_type;

      current_piece_length = source_piece_length - buffer_relative_index;
      pieces[piece_position + 2].start_index_in_buffer =
          buffer_relative_index + current_piece->start_index_in_buffer;
      pieces[piece_position + 2].length_in_buffer = current_piece_length;
      pieces[piece_position + 2].buffer_type = current_piece->buffer_type;
    }
  } else {
    //мб тут как раз проверку на значение индекса сделать
    //т.е. если он больше длины таблицы кусочков, то возвращать
    // fprintf(stderror,"%s","index out of range");
    pieces[pieces_count].start_index_in_buffer = additional_text_index;
    pieces[pieces_count].length_in_buffer = additional_fragment_size;
    pieces[pieces_count].buffer_type = result_buffer_type;

    pieces_count++;

    piece_table->pieces_count = pieces_count;
  }
}

void PieceTable_delete(PieceTable_t *piece_table, int start_position,
                       int length) {
  if (piece_table && start_position && length) {
  }
}

void PieceTable_set_original_text(PieceTable_t *piece_table,
                                  char *new_original_text,
                                  size_t original_text_size) {
  piece_table->original_text = new_original_text;

  piece_table->pieces[0].start_index_in_buffer = 0;
  piece_table->pieces[0].length_in_buffer = original_text_size - 1;
  piece_table->pieces[0].buffer_type = ORIGINAL_TEXT;
  piece_table->pieces_count++;
}

PieceTable_t *PieceTable_create() {
  PieceTable_t *result_piece_table = NULL;
  size_t piece_table_size = 0;

  piece_table_size = sizeof(PieceTable_t);

  result_piece_table = malloc(piece_table_size);

  memset(result_piece_table->additional_text, '\0', BUF_SZ);

  return result_piece_table;
}

void PieceTable_delete_table(PieceTable_t *deleting_piece_table) {
  free(deleting_piece_table);
}
