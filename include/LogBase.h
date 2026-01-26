#pragma once

// [Tag] File.c:00 `function()`: TEXTEXTTEXTEXT!!!
#define LOG_PREFIX "[%s] %s:%d: `%s()`: "

#define puti(p_line) \
	printf(LOG_PREFIX "%s\n", "inf", __FILE_NAME__, __LINE__, __func__, p_line)

#define pute(p_line) \
	fprintf(stderr, LOG_PREFIX "%s\n", "ERR", __FILE_NAME__, __LINE__, __func__, p_line)

#define printi(p_format, ...) \
	printf(LOG_PREFIX p_format, "inf", __FILE_NAME__, __LINE__, __func__, __VA_ARGS__)

#define printe(p_format, ...) \
	fprintf(stderr, LOG_PREFIX p_format, "ERR", __FILE_NAME__, __LINE__, __func__, __VA_ARGS__)
