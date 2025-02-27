// Copyright (c) 2021 Solari di Udine S.p.A
// Licensed under the Apache License, Version 2.0

#include <sys/time.h>

#include <stdarg.h>
#include <iostream>
#include <LoggerStdout.hpp>

namespace verificaC19Sdk {

void LoggerStdout::error(const std::string& format, ...) const {
	va_list args1;
	va_start(args1, format);
	log(ERROR, format, args1);
	va_end(args1);
}

void LoggerStdout::info(const std::string& format, ...) const {
	if (m_level < INFO) return;
	va_list args1;
	va_start(args1, format);
	log(INFO, format, args1);
	va_end(args1);
}

void LoggerStdout::debug(const std::string& format, ...) const {
	va_list args1;
	va_start(args1, format);
	log(DEBUG, format, args1);
	va_end(args1);
}

void LoggerStdout::log(LogLevel level, const std::string& format, va_list ap) const {
	if (m_level < level) return;
	//Time
	struct timeval rawtime;
	gettimeofday(&rawtime, NULL);
	struct tm* info=localtime(&rawtime.tv_sec);
	char buffer[80];
	strftime(buffer, sizeof(buffer), "%d/%m %H:%M:%S", info);
	std::cout << std::string(buffer);
	std::printf(".%03ld: ", rawtime.tv_usec / 1000);
	std::vprintf(format.c_str(), ap);
	std::cout << std::endl;
}

} // namespace verificaC19Sdk

void* LoggerStdout_c_create(LogLevel level) {
	return new verificaC19Sdk::LoggerStdout(level);
}

void LoggerStdout_c_release(const void* logger) {
	verificaC19Sdk::LoggerStdout* this_ = (verificaC19Sdk::LoggerStdout*)logger;
	delete this_;
}

void LoggerStdout_c_error(const void* logger, const char* format, ...) {
	verificaC19Sdk::LoggerStdout* this_ = (verificaC19Sdk::LoggerStdout*)logger;
	va_list args1;
	va_start(args1, format);
	this_->log(ERROR, std::string(format), args1);
	va_end(args1);
}

void LoggerStdout_c_info(const void* logger, const char* format, ...) {
	verificaC19Sdk::LoggerStdout* this_ = (verificaC19Sdk::LoggerStdout*)logger;
	va_list args1;
	va_start(args1, format);
	this_->log(INFO, std::string(format), args1);
	va_end(args1);
}

void LoggerStdout_c_debug(const void* logger, const char* format, ...) {
	verificaC19Sdk::LoggerStdout* this_ = (verificaC19Sdk::LoggerStdout*)logger;
	va_list args1;
	va_start(args1, format);
	this_->log(DEBUG, std::string(format), args1);
	va_end(args1);
}
