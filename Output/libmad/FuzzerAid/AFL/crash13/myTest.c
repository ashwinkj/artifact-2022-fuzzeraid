#include "he_layer3.h"
int mad_layer_III(struct mad_stream *stream, struct mad_frame *frame) {
  unsigned int nch, priv_bitlen, next_md_begin = 0;
  unsigned int si_len, data_bitlen, md_len;
  unsigned int frame_space, frame_used, frame_free;
  struct sideinfo si;
  if (stream->main_data == 0) {
    stream->main_data = malloc(MAD_BUFFER_MDLEN);
    if (stream->main_data == 0) {
    }
  }
  md_len = si.main_data_begin + frame_space - next_md_begin;
  if (si.main_data_begin == 0) {
    if (si.main_data_begin > stream->md_len) {
    } else {
      if (md_len > si.main_data_begin) {
        assert(stream->md_len + md_len - si.main_data_begin <=
               MAD_BUFFER_MDLEN);
        memcpy(*stream->main_data + stream->md_len,
               mad_bit_nextbyte(&stream->ptr),
               frame_used = md_len - si.main_data_begin);
      }
    }
  };
}
#include "he_frame.h"
int mad_frame_decode(struct mad_frame *frame, struct mad_stream *stream) {
  if (!(frame->header.flags & MAD_FLAG_INCOMPLETE) &&
      mad_header_decode(&frame->header, stream) == -1)
    goto fail;
  if (decoder_table[frame->header.layer - 1](stream, frame) == -1)
  fail:
    stream->anc_bitlen = 0;
}
int mad_header_decode(struct mad_header *header, struct mad_stream *stream) {
  if (decode_header(header, stream) == -1)
    mad_timer_set(&header->duration, 0, 32 * MAD_NSBSAMPLES(header),
                  header->samplerate);
}
int decode_header(struct mad_header *header, struct mad_stream *stream) {
  header->layer = 4 - mad_bit_read(&stream->ptr, 2);
}
#include "he_decoder.h"
int run_sync(struct mad_decoder *decoder) {
  struct mad_stream *stream;
  int *frame;
  stream = &decoder->sync->stream;
  frame = &decoder->sync->frame;
  mad_stream_init(stream);
  mad_frame_init(frame);
  do {
    switch (decoder->input_func(decoder->cb_data, stream))
      ;
    while (1) {
      if (mad_frame_decode(frame, stream) == -1) {
      }
    }
  } while (stream->error == MAD_ERROR_BUFLEN);
}
int mad_decoder_run(struct mad_decoder *decoder, enum mad_decoder_mode mode) {
  int result;
  int (*run)(struct mad_decoder *) = 0;
  switch (decoder->mode = mode) {
  case MAD_DECODER_MODE_SYNC:
    run = run_sync;
  }
  if (run == 0)
    return -1;
  decoder->sync = malloc(sizeof *decoder->sync);
  result = run(decoder);
}
