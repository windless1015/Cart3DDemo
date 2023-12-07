#ifndef CART3D_MATH_CPUTIMER_H
#define CART3D_MATH_CPUTIMER_H

#include <Cart3DCommonDefine.h>
#include <chrono>
#include <string>

namespace Cart3D
{
	class CART3D_COMMON_CLASS CPUTimer
	{
	public:
		CPUTimer(const std::string& name="defaultname");
		~CPUTimer();
	public:
		CPUTimer(const CPUTimer &) = delete;
		CPUTimer & operator =(const CPUTimer &) = delete;
		CPUTimer(CPUTimer &&) = delete;
		CPUTimer & operator =(CPUTimer &&) = delete;
	public:
		void restart(const std::string& name);
		void restart();
		//报告当前运行时间
		void report();
		void report(const std::string& name);
		//报告并重新计时
		void report_restart();
		void report_restart(const std::string& name);
		//使用流动名报告
		void stop(const std::string& name);
	public:
		/** 返回当前经历了多少纳秒*/
		double elapsed_nano_second();
		/** 返回当前经历了多少秒*/
		double elapsed_second();
		/** 返回当前经历了多少分钟*/
		double elapsed_min();
		/** 返回当前经历了多少毫秒*/
		double elapsed_mill_second();
	public:
		std::chrono::duration<double, std::ratio<1>> seconds_passed() const;
		std::chrono::duration<double, std::milli> millisec_passed() const;
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> start_;
		std::string name_;
	};
#define CD_TIMER CPUTimer ___timer____(__FUNCTION__)
#define CD_TIMER_NAME(name) CPUTimer ___timer____(name)
}



#endif // ! CART3D_MATH_CPUTIMER_H
