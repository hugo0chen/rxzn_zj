#include "msp430f2272.h"
#include "timer_a.h"
#include "define.h"

#define TIME_STEP 10

ulong _local_time_tick;

ulong _local_tickime(void){
	return _local_time_tick;	
}

bool timeout(ulong last_time, ulong ms){
	if(_local_time_tick >  last_time)
		return (bool)((_local_time_tick - last_time) > ms);
	else	
		return (bool)((last_time - _local_time_tick) > ms);
}

#define MAX_SCHD_ITEMS 4

struct SchdItem {	
	ulong timeout_microsecond;
	SchdCallback callback;
};

struct SchdItem _schd_items[MAX_SCHD_ITEMS] = {{0,0},{0,0},{0,0},{0,0}};
int _schd_last_microsecond = 0;

int Schd_After_Int(ulong microsecond, SchdCallback callback) {
	int idx = 0;
	for (idx = 0; idx < MAX_SCHD_ITEMS; ++idx) {
		if (_schd_items[idx].timeout_microsecond == 0) {
			_schd_items[idx].timeout_microsecond = _schd_last_microsecond
					+ microsecond;
			_schd_items[idx].callback = callback;			
			return 1;
		}
	}
	return 0;
}

void Schd_Run(ulong current_microsecond) {
	int idx = 0;
	_schd_last_microsecond = current_microsecond;

	for (idx = 0; idx < MAX_SCHD_ITEMS; ++idx) {
		if (_schd_items[idx].timeout_microsecond > 0){
			if((current_microsecond - _schd_items[idx].timeout_microsecond) > 0) {
				_schd_items[idx].callback();
				_schd_items[idx].timeout_microsecond = 0;
			}
		}
	}
}
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A(void){
	if(_local_time_tick > 0xFFFFFF10)
		_local_time_tick = 0;
	_local_time_tick += TIME_STEP;
	Schd_Run(_local_time_tick);
}



