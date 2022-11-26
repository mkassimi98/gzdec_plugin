#include <gst/gst.h>
#include <zlib.h>
#include <string.h>

/* unit of decoding. 256k is the best as zlib said. */
#define CHUNK (1024 * 256)

struct ll_buffer {
  guchar *data;
  gulong len;
  struct ll_buffer *next;
};

gint init_decoder (void);
void deinit_decoder (void);
gint decode_message (const guchar * srcmsg, const gint srclen, guchar ** outmsg, gulong * outlen);
