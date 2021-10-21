#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <initializer_list>
#include <assert.h>
#include <sstream>
#include <sstream>
#include <mutex>
#include "plog/Log.h"
#include "plog/Appenders/ConsoleAppender.h"

namespace sandcraft {
#ifndef NDEBUG
	#ifndef __EMSCRIPTEN__
		#define LOG_GLOBAL_STR(x) LOG(plog::verbose) << x
		#define LOG_DEBUG_STR(x) LOG(plog::debug) << x
		#define LOG_INFO_STR(x) LOG(plog::info) << x
		#define LOG_WARN_STR(x) LOG(plog::warning) << x
		#define LOG_ERR_STR(x) LOG(plog::error) << "\033[1;31m" << x << "\033[0m"
		#define LOG_FATAL_STR(x) LOG(plog::fatal) << "\033[1;31m" << x << "\033[0m"
		#define LOG_GLOBAL_MSG(msg,x) LOG(plog::verbose) << msg << ": " << x
		#define LOG_DEBUG_MSG(msg,x) LOG(plog::debug) << msg << ": " << x
		#define LOG_INFO_MSG(msg,x) LOG(plog::info) << msg << ": " << x
		#define LOG_WARN_MSG(msg,x) LOG(plog::warning) << msg << ": " << x
		#define LOG_ERR_MSG(msg,x) LOG(plog::error) << msg << ": " << "\033[1;31m" << x << "\033[0m"
		#define LOG_FATAL_MSG(msg,x) LOG(plog::fatal) << msg << ": " << "\033[1;31m" << x << "\033[0m"
		#define LOG_GLOBAL(x) LOG(plog::verbose) << x
		#define LOG_DEBUG(x) LOG(plog::debug) << x
		#define LOG_INFO(x) LOG(plog::info) << x
		#define LOG_WARN(x) LOG(plog::warning) << x
		#define LOG_ERR(x) LOG(plog::error) << "\033[1;31m" << x << "\033[0m"
		#define LOG_FATAL(x) LOG(plog::fatal) << "\033[1;31m" << x << "\033[0m"
	#else
		#define LOG_GLOBAL_STR(x) LOG(plog::verbose) << x
		#define LOG_DEBUG_STR(x) LOG(plog::debug) << x
		#define LOG_INFO_STR(x) LOG(plog::info) << x
		#define LOG_WARN_STR(x) LOG(plog::warning) << x
		#define LOG_ERR_STR(x) LOG(plog::error) << x
		#define LOG_FATAL_STR(x) LOG(plog::fatal) << x
		#define LOG_GLOBAL_MSG(msg,x) LOG(plog::verbose) << msg << ": " << x
		#define LOG_DEBUG_MSG(msg,x) LOG(plog::debug) << msg << ": " << x
		#define LOG_INFO_MSG(msg,x) LOG(plog::info) << msg << ": " << x
		#define LOG_WARN_MSG(msg,x) LOG(plog::warning) << msg << ": " << x
		#define LOG_ERR_MSG(msg,x) LOG(plog::error) << msg << ": " << x
		#define LOG_FATAL_MSG(msg,x) LOG(plog::fatal) << msg << ": " << x
		#define LOG_GLOBAL(x) LOG(plog::verbose) << x
		#define LOG_DEBUG(x) LOG(plog::debug) << x
		#define LOG_INFO(x) LOG(plog::info) << x
		#define LOG_WARN(x) LOG(plog::warning) << x
		#define LOG_ERR(x) LOG(plog::error) << x
		#define LOG_FATAL(x) LOG(plog::fatal) << x
	#endif
#else
	#define LOG_GLOBAL_STR(x)
	#define LOG_DEBUG_STR(x)
	#define LOG_INFO_STR(x)
	#define LOG_WARN_STR(x)
	#define LOG_ERR_STR(x) LOG(plog::error) << "\033[1;31m" << x << "\033[0m"
	#define LOG_FATAL_STR(x) LOG(plog::fatal) << "\033[1;31m" << x << "\033[0m"
	#define LOG_GLOBAL_MSG(msg,x)
	#define LOG_DEBUG_MSG(msg,x)
	#define LOG_INFO_MSG(msg,x)
	#define LOG_WARN_MSG(msg,x)
	#define LOG_ERR_MSG(msg,x) LOG(plog::error) << msg << ": " << "\033[1;31m" << x << "\033[0m"
	#define LOG_FATAL_MSG(msg,x) LOG(plog::fatal) << msg << ": " << "\033[1;31m" << x << "\033[0m"
	#define LOG_GLOBAL(x)
	#define LOG_DEBUG(x)
	#define LOG_INFO(x)
	#define LOG_WARN(x)
	#define LOG_ERR(x) LOG(plog::error) << "\033[1;31m" << x << "\033[0m"
	#define LOG_FATAL(x) LOG(plog::fatal) << "\033[1;31m" << x << "\033[0m"
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#endif
#ifdef __clang__
#pragma clang diagnostic pop
#endif
  using std::string;

  enum LogLevel {
    L_FATAL = 0,
    L_ERROR = 1,
    L_WARNING = 2,
    L_INFO = 3,
    L_DEBUG = 4,
    L_GLOBAL = 5
  };

  class Logger {
  private:
    Logger(const LogLevel l);
    static Logger* instance_;
    LogLevel level_;
  public:

    static void init(const LogLevel l);
    static Logger& getInstance();
    static LogLevel getLevel();
    static void registerThread(const string& name);
    static void removeThread();


    void error(const string& title, const string& msg = "") {
    	if(msg.empty())
    		LOG_ERR_STR(title);
    	else
    		LOG_ERR_MSG(title, msg);
    }

    void warn(const string& title, const string& msg = "") {
    	if(msg.empty())
    		LOG_WARN_STR(title);
    	else
    		LOG_WARN_MSG(title, msg);
    }
    void debug(const string& title, const string& msg = "") {
    	if(msg.empty())
    		LOG_DEBUG_STR(title);
    	else
    		LOG_DEBUG_MSG(title, msg);
    }

    void info(const string& title, const string& msg = "") {
    	if(msg.empty())
    		LOG_INFO_STR(title);
    	else
    		LOG_INFO_MSG(title, msg);
    }

    void syntax_error(const string& title, const string& msg = "") {
    	if(msg.empty())
    		LOG_ERR_STR(title);
    	else
    		LOG_ERR_MSG(title, msg);
    }
  };

  void log_error(const string& title, const string& msg = "");
  void log_warn(const string& title, const string& msg = "");
  void log_debug(const string& title, const string& msg = "");
  void log_info(const string& title, const string& msg = "");
}

#endif /* LOGGER_H_ */
