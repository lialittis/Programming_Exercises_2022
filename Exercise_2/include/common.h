#ifndef __COMMON_H__
#define __COMMON_H__

#define LOG_TAG 	"hash-service"
#define LOGE(fmt, ...) \
	fprintf(stderr, "%s: %d: " fmt, LOG_TAG, __LINE__,  ## __VA_ARGS__)

#define LOGI(fmt, ...)

#endif /* __COMMON_H__ */
