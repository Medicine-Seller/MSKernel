
#ifndef Logger_H
#define Logger_H

#define LOG(x, ...) DbgPrintEx(0,0,"[MSKernel] " x,__VA_ARGS__)
#define LOGF(x, ...) DbgPrintEx(0,0,"[MSKernel] %s::" x, __FUNCTION__ ,__VA_ARGS__)
#define LOGL(x, ...) DbgPrintEx(0,0,"[MSKernel] %s :" x, __LINE__, __VA_ARGS__)

#endif