#ifndef __COMMON_H__
#define __COMMON_H__

#define CLOG_TAG 	"client"
#define SLOG_TAG 	"server"
#define CLOGE(fmt, ...) \
	fprintf(stderr, "%s: %d: " fmt, CLOG_TAG, __LINE__,  ## __VA_ARGS__)

#define SLOGE(fmt, ...) \
	fprintf(stderr, "%s: %d: " fmt, SLOG_TAG, __LINE__,  ## __VA_ARGS__)

#define LOGI(fmt, ...)

#endif /* __COMMON_H__ */
