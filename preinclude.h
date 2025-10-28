#define padding_insert(x, y) x ## y
#define padding_define(x, y) padding_insert(x, y)
#define private_padding(size) private: \
    unsigned char padding_define(__pad_, __LINE__)[size];
#define padding(size) private_padding(size) \
    public:

#define resolve_displacement32(address, opcode_length) address + shared::memory->read<int>(address + opcode_length) + opcode_length + sizeof(int)

// From handleapi.h
#define invalid_handle ((handle)(long long)-1)

#ifdef _MSC_VER
    #if _MSC_VER >= 1200
        #define inlined __forceinline
    #else
        #define inlined __inline
    #endif
#else
    #ifdef __cplusplus
        #define inlined inline
    #else
        #define inlined
    #endif
#endif

typedef void* ptr;
typedef ptr handle;
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long dword;
typedef unsigned long long qword;
typedef dword pid_t;
typedef size_t qword;
typedef const char* cstr;
