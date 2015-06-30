#ifndef ENCRYPT_H
#define ENCRYPT_H
#include <openssl/aes.h>

#define MAX_PACKET_LEN 1024*20

/* @ Copyright from: http://stackoverflow.com/questions/3141860/aes-ctr-256-encryption-mode-of-operation-on-openssl */
struct ctr_state {
    /* ivec[0..7] is the IV, ivec[8..15] is the big-endian counter */
    unsigned char ivec[16];  
    unsigned int num;
    unsigned char ecount[16];
};

void init_ctr(struct ctr_state *state, const unsigned char iv[8])
{
    /* aes_ctr128_encrypt requires 'num' and 'ecount' set to zero on the
     * first call. */
    state->num = 0;
    memset(state->ecount, 0, 16);

    /* Initialise counter in 'ivec' to 0 */
    memset(state->ivec + 8, 0, 8);

    /* Copy IV into 'ivec' */
    memcpy(state->ivec, iv, 8);
}
/* end of Copyright */


#endif
