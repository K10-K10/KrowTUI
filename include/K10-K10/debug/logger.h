#ifndef INCLUDE_DEBUG_LOGGER_H_
#define INCLUDE_DEBUG_LOGGER_H_

#include <cstdint>
#include <string>
#include <vector>

namespace __krow__ {

#ifdef ENABLE_LOGGER

#include <fstream>
#include <mutex>

class logger {
 public:
  enum class log_type : std::uint8_t { success, failed, error, info };
  struct log_value {
    unsigned int id;
    log_type type;
    std::string message;
    bool operator==(const log_value& arg) const {
      return (this->type == arg.type) && (this->message == arg.message);
    }
  };

  logger() = delete;

  static void set_log_file(const std::string& filename) {
    std::lock_guard<std::mutex> lock(mtx);
    log_file_path = filename;
  }

  static void add_log(log_type type_, const std::string& message) {
    std::lock_guard<std::mutex> lock(mtx);
    logs.push_back({id++, type_, message});

    std::ofstream ofs(log_file_path, std::ios::app);
    if (ofs.is_open()) {
      ofs << "[" << (id - 1) << "] ";
      switch (type_) {
        case log_type::success:
          ofs << "[SUCCESS] ";
          break;
        case log_type::failed:
          ofs << "[FAILED]  ";
          break;
        case log_type::error:
          ofs << "[ERROR]   ";
          break;
        case log_type::info:
          ofs << "[INFO]   ";
          break;
      }
      ofs << message << "\n";
    }
  }

  static std::vector<log_value> get_logs() {
    std::lock_guard<std::mutex> lock(mtx);
    return logs;
  }

  static void clear_logs() {
    std::lock_guard<std::mutex> lock(mtx);
    logs.clear();
    id = 1;
    std::ofstream ofs(log_file_path, std::ios::trunc);
    ofs.close();
  }

 private:
  inline static unsigned int id = 1;
  inline static std::vector<log_value> logs;
  inline static std::mutex mtx;
  inline static std::string log_file_path = "debug.log";
};

#else
class logger {
 public:
  enum class log_type : std::uint8_t { success, failed, error, info };
  struct log_value {
    unsigned int id;
    log_type type;
    std::string message;
    bool operator==(const log_value& v) const { return true; }
  };

  logger() = delete;

  static void set_log_file(const std::string& filename) {}
  static void add_log(log_type type_, const std::string& message) {}
  static std::vector<log_value> get_logs() { return {}; }
  static void clear_logs() {}
};

#endif

}  // namespace __krow__

#endif
