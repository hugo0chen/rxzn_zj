#ifndef TIMER_A_H_
#define TIMER_A_H_
#include "define.h"


union SchdParameter {
	void* ptr;
	int intvalue;
	float floatvalue;
	char chars[32];
};

typedef void (*SchdCallback)(union SchdParameter);
ulong _local_tickime(void);
bool timeout(ulong last_time, ulong ms);
/*
 @brief 在指定毫秒后调用回调函数，同时携带注册时的入参
 @param microsecond 延时毫秒数
 @param p 回调时的参数
 @return 1=add one item, 0=no item added
 */
int Schd_After(ulong microsecond, SchdCallback callback, union SchdParameter p);

/*
 @brief 在指定毫秒后调用回调函数，同时携带注册时的入参
 @param microsecond 延时毫秒数
 @param value 回调时的参数，整数值
 @return 1=add one item, 0=no item added
 */
int Schd_After_Int(ulong microsecond, SchdCallback callback, int value);

/*
 @brief 运行调度器
 @param current_microsecond 当前毫秒数
 */
void Schd_Run(ulong current_microsecond);


#endif /*TIMER_A_H_*/
