//
// Created by ChenLiji on 2022/1/15.
//

#ifndef _RUN_STATISTIC_H_
#define _RUN_STATISTIC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <sys/time.h>
#include <stdint.h>
#include <stddef.h>

inline uint64_t Get_Time_us()
{
  uint64_t time;
  struct timeval tv = { 0 };
  gettimeofday(&tv, NULL);
  time = (uint64_t)(tv.tv_sec * 1000000 + tv.tv_usec);
  return time;
}

typedef struct
{
	uint64_t start_time;
	uint64_t end_time;
}Time_Statistic_TypeDef;

extern Time_Statistic_TypeDef time_statistic;

#ifdef __cplusplus
}
#endif

#endif //_RUN_STATISTIC_H_
