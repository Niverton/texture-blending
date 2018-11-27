#pragma once

#include <exception>
#include <string>
#include <utility>

class RTException : public std::exception {
public:
  explicit RTException(std::string message) : content{std::move(message)} {}

  const char *what() const noexcept override { return content.c_str(); }

protected:
  std::string content;
};
