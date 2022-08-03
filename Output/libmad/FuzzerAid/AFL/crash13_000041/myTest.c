#include "he_layer3.h"
int mad_layer_III(struct mad_stream *stream, struct mad_frame *frame) {
  int *header = &frame->header;
  unsigned int nch, priv_bitlen, next_md_begin = 0, si_len, data_bitlen, md_len,
                                 frame_space, frame_used, frame_free;
  struct sideinfo si;
  if (stream->main_data == 0) {
    stream->main_data = malloc(MAD_BUFFER_MDLEN);
  }
  md_len = si.main_data_begin + frame_space - next_md_begin;
  if (si.main_data_begin == 0)
    ;
  else {
    if (si.main_data_begin > stream->md_len) {
      if (md_len > si.main_data_begin) {
        memcpy(*stream->main_data + stream->md_len,
               mad_bit_nextbyte(&stream->ptr),
               frame_used = md_len - si.main_data_begin);
      }
    }
  }
}
void mad_bit_init(struct mad_bitptr *bitptr, unsigned char const *byte) {
  bitptr->byte = byte;
}
unsigned long mad_bit_read(struct mad_bitptr *bitptr, unsigned int len) {
  register unsigned long value;
  if (len < bitptr->left) {
    value = (bitptr->cache & (1 << bitptr->left) - 1) >> bitptr->left - len;
    return value;
  }
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
    goto fail;
  mad_timer_set(&header->duration, 0, 32 * MAD_NSBSAMPLES(header),
                header->samplerate);
  return 0;
fail:
  return -1;
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
    while (1) {
      if (mad_frame_decode(frame, stream) == -1)
        ;
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
  decoder->sync = malloc(sizeof *decoder->sync);
  result = run(decoder);
}
