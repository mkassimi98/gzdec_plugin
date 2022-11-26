#include "zlibdec.h"

z_stream stream;

gint
init_decoder (void)
{
  gint ret;

  /* allocate inflate state */
  stream.zalloc = Z_NULL;
  stream.zfree = Z_NULL;
  stream.opaque = Z_NULL;
  stream.avail_in = 0;
  stream.next_in = Z_NULL;

  ret = inflateInit2 (&stream, 16 + MAX_WBITS);

  return ret;
}

void
deinit_decoder (void)
{
  /* clean up and return */
  (void)inflateEnd(&stream);
}

gint
decode_message (const guchar * srcmsg, const gint srclen, guchar ** outmsg, gulong * outlen)
{
  gint ret;
  guchar inbuffer[CHUNK];
  guchar outbuffer[CHUNK];
  gulong processed;
  struct ll_buffer *outdata, *head;
  guchar *srcidx = (guchar *)srcmsg;
  gint remainder = srclen;

  outdata = g_malloc0 (sizeof(struct ll_buffer));
  head = outdata;

  do {
    memset (inbuffer, 0, CHUNK);
    if (remainder >= CHUNK) {
        remainder -= CHUNK;
        stream.avail_in = CHUNK;
        memcpy (inbuffer, srcidx, CHUNK);
        srcidx += CHUNK;
    }
    else {
        stream.avail_in = remainder;
        memcpy (inbuffer, srcidx, remainder);
        remainder = 0;
    }

    if (stream.avail_in == 0)
      break;
    stream.next_in = inbuffer;

    do {
      outdata->data = g_malloc0 (CHUNK);

      stream.avail_out = CHUNK;
      stream.next_out = outbuffer;
      ret = inflate (&stream, Z_NO_FLUSH);
      switch (ret) {
      case Z_NEED_DICT:
        ret = Z_DATA_ERROR;
      case Z_DATA_ERROR:
      case Z_MEM_ERROR:
      case Z_STREAM_ERROR:
        (void)inflateEnd(&stream);
        return ret;
      }
      processed = CHUNK - stream.avail_out;
      memcpy (outdata->data + outdata->len, outbuffer, processed);
      outdata->len += processed;
      *outlen += processed;

      if (stream.avail_out == 0) {
        outdata->next = g_malloc0 (sizeof(struct ll_buffer));
        outdata = outdata->next;
      }

    } while (stream.avail_out == 0);

    if (ret != Z_STREAM_END) {
      outdata->next = g_malloc0 (sizeof(struct ll_buffer));
      outdata = outdata->next;
    }
  } while (ret != Z_STREAM_END);

  outdata = head;
  *outmsg = g_malloc0 (*outlen);

  gulong outmsgidx = 0;

  while (outdata) {
    memcpy (*outmsg + outmsgidx, outdata->data, outdata->len);

    outmsgidx += outdata->len;
    g_free (outdata->data);

    struct ll_buffer *temp = outdata;
    outdata = outdata->next;
    g_free (temp);
  }

  return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

