/** THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
 * BY HAND!!
 *
 * Generated by lcm-gen
 **/

#include <stdint.h>
#include <stdlib.h>
#include <lcm/lcm_coretypes.h>
#include <lcm/lcm.h>

#ifndef _fau_coordinate_t_h
#define _fau_coordinate_t_h

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _fau_coordinate_t fau_coordinate_t;
struct _fau_coordinate_t
{
    int16_t    mode;
    int16_t    count;
    float      *traject;
};

fau_coordinate_t   *fau_coordinate_t_copy(const fau_coordinate_t *p);
void fau_coordinate_t_destroy(fau_coordinate_t *p);

typedef struct _fau_coordinate_t_subscription_t fau_coordinate_t_subscription_t;
typedef void(*fau_coordinate_t_handler_t)(const lcm_recv_buf_t *rbuf,
             const char *channel, const fau_coordinate_t *msg, void *user);

int fau_coordinate_t_publish(lcm_t *lcm, const char *channel, const fau_coordinate_t *p);
fau_coordinate_t_subscription_t* fau_coordinate_t_subscribe(lcm_t *lcm, const char *channel, fau_coordinate_t_handler_t f, void *userdata);
int fau_coordinate_t_unsubscribe(lcm_t *lcm, fau_coordinate_t_subscription_t* hid);
int fau_coordinate_t_subscription_set_queue_capacity(fau_coordinate_t_subscription_t* subs,
                              int num_messages);


int  fau_coordinate_t_encode(void *buf, int offset, int maxlen, const fau_coordinate_t *p);
int  fau_coordinate_t_decode(const void *buf, int offset, int maxlen, fau_coordinate_t *p);
int  fau_coordinate_t_decode_cleanup(fau_coordinate_t *p);
int  fau_coordinate_t_encoded_size(const fau_coordinate_t *p);

// LCM support functions. Users should not call these
int64_t __fau_coordinate_t_get_hash(void);
int64_t __fau_coordinate_t_hash_recursive(const __lcm_hash_ptr *p);
int     __fau_coordinate_t_encode_array(void *buf, int offset, int maxlen, const fau_coordinate_t *p, int elements);
int     __fau_coordinate_t_decode_array(const void *buf, int offset, int maxlen, fau_coordinate_t *p, int elements);
int     __fau_coordinate_t_decode_array_cleanup(fau_coordinate_t *p, int elements);
int     __fau_coordinate_t_encoded_array_size(const fau_coordinate_t *p, int elements);
int     __fau_coordinate_t_clone_array(const fau_coordinate_t *p, fau_coordinate_t *q, int elements);

#ifdef __cplusplus
}
#endif

#endif
