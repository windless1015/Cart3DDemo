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
		//���浱ǰ����ʱ��
		void report();
		void report(const std::string& name);
		//���沢���¼�ʱ
		void report_restart();
		void report_restart(const std::string& name);
		//ʹ������������
		void stop(const std::string& name);
	public:
		/** ���ص�ǰ�����˶�������*/
		double elapsed_nano_second();
		/** ���ص�ǰ�����˶�����*/
		double elapsed_second();
		/** ���ص�ǰ�����˶��ٷ���*/
		double elapsed_min();
		/** ���ص�ǰ�����˶��ٺ���*/
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
