#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "timers.h"

struct TimerInfo *timers = NULL;

/**
* Function timer_add
* Adds a timer to execute a specified callback at a specified time.
* @param time_t timestamp the time to execute the callback
* @param TimerCallback callback the callback to execute
* @param void *state a pointer to a variable containing state information
*                    needed by the callback
*/
struct TimerInfo *timer_add(time_t timestamp, TimerCallback callback, void *state)
{
    struct TimerInfo *newti = malloc(sizeof(struct TimerInfo));
    struct TimerInfo *ti = NULL;

    assert(newti != NULL);

    newti->ti_timestamp = timestamp;
    newti->ti_callback = callback;
    newti->ti_state = state;
    newti->ti_next = NULL;
    newti->ti_prev = NULL;

    if (timers == NULL)
    {
        timers = newti;
        return newti;
    }

    for (ti = timers; ti; ti = ti->ti_next)
    {
        if (ti->ti_timestamp > newti->ti_timestamp)
        {
            if (ti->ti_prev == NULL)
                timers = newti;
            else
                ti->ti_prev->ti_next = newti;
            newti->ti_prev = ti->ti_prev;
            newti->ti_next = ti;
            ti->ti_prev = newti;
            return newti;
        }

        if (ti->ti_next == NULL)
        {
            ti->ti_next = newti;
            newti->ti_prev = ti;
            return newti;
        }
    }

    return NULL;
}

/**
* Function timer_del
* Removes a timer from the timer queue.
* @param struct TimerInfo *timer the timer to remove.
*/
void timer_del(struct TimerInfo *timer)
{
    assert(timer != NULL);

    if (timer->ti_prev == NULL)
        timers = timer->ti_next;
    else
        timer->ti_prev->ti_next = timer->ti_next;
    if (timer->ti_next != NULL)
        timer->ti_next->ti_prev = timer->ti_prev;

    free(timer);
}

/**
* Function timer_next
* Returns the next timer to execute after executing any expired timers.
* @return the next timer to execute
*/
struct TimerInfo *timer_next()
{
    struct TimerInfo *ti = NULL;
    struct TimerInfo *ti_next = NULL;
	time_t now = time(NULL);

    for (ti = timers; ti; ti = ti_next)
    {
        if (ti == NULL)
            break;

        ti_next = ti->ti_next;

        if (ti->ti_timestamp <= now)
        {
            ti->ti_callback(ti);
            timer_del(ti);
        }
    }

    return timers;
}
