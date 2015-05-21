#ifndef _timers_h
#define _timers_h

#include <time.h>

struct TimerInfo;

typedef void (*TimerCallback)(struct TimerInfo *);

struct TimerInfo
{
    struct TimerInfo *ti_next;
    struct TimerInfo *ti_prev;
    time_t            ti_timestamp;
    TimerCallback     ti_callback;
    void             *ti_state;
};

struct TimerInfo *timer_add(time_t timestamp, TimerCallback callback, void *state);
void timer_del(struct TimerInfo *timer);
struct TimerInfo *timer_next();

#endif /* _timers_h */
