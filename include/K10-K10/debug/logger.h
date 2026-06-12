#ifndef INCLUDE_DEBUG_LOGGER_H_
#define INCLUDE_DEBUG_LOGGER_H_

#include <cstdint>
#include <mutex>
#include <string>
#include <vector>

namespace __terminal__ {

#ifdef ENABLE_LOGGER
class logger {
 public:
  enum class log_type : std::uint8_t { success, failed, error };
  struct log_value {
    unsigned int id;
    log_type type_;
    std::string message;
  };

  logger() = delete;

  static void add_log(log_type type_, const std::string& message) {
    std::lock_guard<std::mutex> lock(mtx);
    logs.push_back({id++, type_, message});
  }

  static std::vector<log_value> get_logs() {
    std::lock_guard<std::mutex> lock(mtx);
    return logs;
  }

  static void clear_logs() {
    std::lock_guard<std::mutex> lock(mtx);
    logs.clear();
    id = 1;
  }

 private:
  inline static unsigned int id = 1;
  inline static std::vector<log_value> logs;
  inline static std::mutex mtx;
};

#else
class logger {
 public:
  enum class log_type : std::uint8_t { success, failed, error };
  struct log_value {
    unsigned int id;
    log_type type_;
    std::string message;
  };

  logger() = delete;

  static void add_log(log_type type_, const std::string& message) {}

  static std::vector<log_value> get_logs() { return {}; }

  static void clear_logs() {}
};

#endif

}  // namespace __terminal__

#endif
