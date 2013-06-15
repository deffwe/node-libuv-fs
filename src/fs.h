#ifndef FS_H
#define FS_H

#include "v8.h"
#include "node.h"
#include "req_wrap.h"

using namespace v8;

using node::ReqWrap;

class FSRequestWrap: public ReqWrap<uv_fs_t> {
    public:
        FSRequestWrap(const char * syscall): syscall_(syscall) {

        }

        const char * syscall() {
            return syscall_;
        }
    private:
        const char * syscall_;
};

#define FS_SYNC_CALL(name, path, ...) \
    uv_fs_t * req = (uv_fs_t *) malloc(sizeof(uv_fs_t)); \
    int result = uv_fs_##name(uv_default_loop(), req, __VA_ARGS__, NULL); \
    if (result < 0) { \
        int code = uv_last_error(uv_default_loop()).code; \
        return ThrowException(UVException(code, #name, "", path)); \
    }

#define THROW_ERROR(message) \
    ThrowException(Exception::Error(String::New(message)));

#define THROW_TYPE_ERROR(message) \
    ThrowException(Exception::TypeError(String::New(message)));

Handle<Value> Open(const Arguments &args);
Handle<Value> Read(const Arguments &args);
Handle<Value> Close(const Arguments &args);

#endif
