#ifndef __AXIS_H__ 
#define __AXIS_H__

#include <WProgram.h>
#include "configuration.h"
#include "Tonokip_Firmware.h"

class Axis
{
  public:
	bool direction;
	float destination;
	float current;
	unsigned long interval;
	float feedrate;
	float steps_per_unit;
	float max_length;
  float max_feedrate;
  int homing_dir;

	bool relative;
	
	bool acceleration_enabled;
	bool accelerating;
	bool decelerating;

	int step_pin;
	int dir_pin;
	bool dir_inverted;
	int enable_pin;
	bool enable_inverted;
	int min_pin;
	int max_pin;
	
	Axis(int step_pin, int dir_pin, int enable_pin, int min_pin, int max_pin, 
       float steps_per_unit, bool enable_inverted, bool dir_inverted, float max_length,
       float max_feedrate, int homing_dir);

	void enable();
	void disable();
	void do_step();
  void home();
	unsigned long get_time_for_move(float feedrate);
	float set_time_for_move(unsigned long tfm);
	void precomputemove();
	bool is_moving();
	void set_target(float target);

	unsigned long steps_to_take;
	unsigned long steps_remaining;
	unsigned long steps_done;
	unsigned long lastinterval;
#ifdef EXP_ACCELERATION
  void setup_accel();
  void precompute_accel(unsigned long interval,unsigned int delta);
  unsigned long recompute_accel(unsigned long timediff, unsigned long interval);
  float full_velocity_units;
  float min_units_per_second;
  float min_constant_speed_units;
  unsigned long long_full_velocity_units;
  unsigned long max_interval;
  unsigned long min_constant_speed_steps;
  unsigned long virtual_full_velocity_steps;
  unsigned long full_velocity_steps;
  unsigned long full_interval;
  unsigned int steps_acceleration_check;
#else // not EXP
#ifdef RAMP_ACCELERATION
  void setup_accel();
  void precompute_accel(unsigned long interval,unsigned int delta);
  unsigned long recompute_accel(unsigned long timediff, unsigned long interval);
  unsigned long max_interval;
  unsigned long steps_per_sqr_second;
  unsigned long plateau_steps;
  float plateau_time;
  long full_interval;
  long max_speed_steps_per_second;
  long min_speed_steps_per_second;
  unsigned long start_move_micros;
#else // no acceleration
  void setup_accel() { return; };
  void precompute_accel(unsigned long interval,unsigned int delta) { return; };
  unsigned long recompute_accel(unsigned long timediff, unsigned long interval) { return interval; };
#endif // RAMP_ACCELERATION
#endif // EXP_ACCELERATION

  
};

#endif // __AXIS_H__
