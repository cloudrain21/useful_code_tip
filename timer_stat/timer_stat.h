/*******************************************************************************
 * Copyright 2012, OnmirSoft Corporation or its subsidiaries.
 * All rights reserved.
 ******************************************************************************/

/*******************************************************************************
 * $Id$
 *
 * Description :
 *   Timer Statistics Library
 ******************************************************************************/
#ifndef __O_TIMER_STAT_H__
#define __O_TIMER_STAT_H__

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MIN_SECTION_COUNT   1
#define MAX_SECTION_COUNT   20


#define UNIT_DEFAULT     0    
enum unit_type
{
    UNIT_MICRO    = UNIT_DEFAULT,
    UNIT_SEC,
    UNIT_MILI,
    UNIT_NANO
};

typedef struct timer_stat
{
    int             mUnitType;     /* 단위 (SEC, MILI, MICRO, NANO) */
    double          mSum;          /* 전체 시간 합계 - 단위에 따른 시간 */

    int             mBegin;        /* 통계를 보여줄 시간구간의 시작 값 */
    int             mInterval;     /* 통계를 보여줄 시간구간의 간격 */
    int             mSectionCount; /* 몇 개의 시간구간으로 보여줄 것인가 */

    struct timespec mStartTimer;
    struct timespec mEndTimer;

    char          * mTime;
} HTIMER;


HTIMER * init_timer( int, int, int, int );
int start_timer( HTIMER * );
int start_timer2( HTIMER * aTimer, struct timespec * aStart );
int end_timer( HTIMER * );
int elapse_timer( HTIMER *, int );
int final_timer( HTIMER * timer );
int sleep_micro(long usec);


#endif  /* __O_TIMER_STAT_H__ */
