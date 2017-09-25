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
 @brief ��ָ���������ûص�������ͬʱЯ��ע��ʱ�����
 @param microsecond ��ʱ������
 @param p �ص�ʱ�Ĳ���
 @return 1=add one item, 0=no item added
 */
int Schd_After(ulong microsecond, SchdCallback callback, union SchdParameter p);

/*
 @brief ��ָ���������ûص�������ͬʱЯ��ע��ʱ�����
 @param microsecond ��ʱ������
 @param value �ص�ʱ�Ĳ���������ֵ
 @return 1=add one item, 0=no item added
 */
int Schd_After_Int(ulong microsecond, SchdCallback callback, int value);

/*
 @brief ���е�����
 @param current_microsecond ��ǰ������
 */
void Schd_Run(ulong current_microsecond);


#endif /*TIMER_A_H_*/
