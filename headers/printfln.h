#include <stdarg.h>

int printfln(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int ret = vprintf(format, ap);
    va_end(ap);
    puts("");
    return ret;
}
