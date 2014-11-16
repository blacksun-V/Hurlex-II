/*
 * =====================================================================================
 *
 *       Filename:  syscall.c
 *
 *    Description:  系统调用相关
 *
 *        Version:  1.0
 *        Created:  2014年11月16日 12时19分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
 *        Company:  Alibaba-Inc Aliyun
 *
 * =====================================================================================
 */

#include <types.h>
#include <debug.h>
#include <intr/intr.h>

#include "syscall.h"

static int sys_test(uint32_t args[])
{
        int errno = (int)args[0];

        printk_color(rc_black, rc_light_brown, "\n\tsys_test run here!\n");

        return errno;
}

static int sys_exit(uint32_t args[])
{
        int errno = (int)args[0];

        return errno;
}

static int sys_fork(uint32_t args[])
{
        int errno = (int)args[0];

        return errno;
}

static int sys_read(uint32_t args[])
{
        int errno = (int)args[0];

        return errno;
}

static int sys_write(uint32_t args[])
{
        int errno = (int)args[0];

        return errno;
}

static int sys_open(uint32_t args[])
{
        int errno = (int)args[0];

        return errno;
}

static int sys_close(uint32_t args[])
{
        int errno = (int)args[0];

        return errno;
}

static int sys_getpid(uint32_t args[])
{
        int errno = (int)args[0];

        return errno;
}

// 系统调用函数指针数组
static int (*syscalls[])(uint32_t args[]) = {
        [SYS_test] = sys_test,
        [SYS_exit] = sys_exit,
        [SYS_fork] = sys_fork,
        [SYS_read] = sys_read,
        [SYS_write] = sys_write,
        [SYS_open] = sys_open,
        [SYS_close] = sys_close,
        [SYS_getpid] = sys_getpid
};

void syscall_handler(pt_regs_t *regs)
{
        uint32_t args[5];
        
        int sysno = regs->eax;
        if (sysno >= 0 && sysno <= SYSCALL_MAX) {
                if (syscalls[sysno]) {
                        // 系统调用寄存器传参规范
                        args[0] = regs->ebx;
                        args[1] = regs->ecx;
                        args[2] = regs->edx;
                        args[3] = regs->esi;
                        args[4] = regs->edi;
                        // 返回值由 eax 寄存器带回
                        regs->eax = syscalls[sysno](args);
                }
        }
}

