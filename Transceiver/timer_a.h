#ifndef TIMER_A_H_
#define TIMER_A_H_
#include "define.h"

typedef void (*SchdCallback)(void);
ulong _local_tickime(void);
bool timeout(ulong last_time, ulong ms);

/*
 @brief 在指定毫秒后调用回调函数，同时携带注册时的入参
 @param microsecond 延时毫秒数
 @param value 回调时的参数，整数值
 @return 1=add one item, 0=no item added
 */
int Schd_After_Int(ulong microsecond, SchdCallback callback);

/*
 @brief 运行调度器
 @param current_microsecond 当前毫秒数
 */
void Schd_Run(ulong current_microsecond);


#endif /*TIMER_A_H_*/
