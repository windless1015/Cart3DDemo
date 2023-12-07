#ifndef CART3D_LOGGER_H
#define CART3D_LOGGER_H

#include <Cart3DCommonDefine.h>
#include <spdlog/spdlog.h>


namespace Cart3D
{
    class CART3D_COMMON_CLASS Logger
    {
	public:
		friend struct InitLogger;
    private:
        static bool init_logger(std::string path,
			std::string filename = "cart3dlog.dat",
			bool app = false);

    public:
        static std::shared_ptr<spdlog::logger> file_logger;
        static std::shared_ptr<spdlog::logger> console_logger;
    private:
        static bool is_init_logger;
    };

#define flogger Logger::file_logger
#define clogger Logger::console_logger

}



#endif