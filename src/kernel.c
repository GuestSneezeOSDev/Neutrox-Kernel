#include <stdint.h>
#include <stddef.h>

#define KERNEL_STACK_SIZE 8192

extern void load_initramfs(void);
extern int execve(const char *filename, char *const argv[], char *const envp[]);
extern void switch_to_user_mode(void);
extern void panic(const char *message);
extern void printf(const char *format, ...);

void vga_puts(const char *str) {
    volatile char *video = (volatile char*)0xB8000;
    while (*str) {
        *video++ = *str++;
        *video++ = 0x07; 
    }
}

void kernel_main() {
    vga_puts("Kernel started...\n");

    load_initramfs();

    const char *argv[] = {"/sbin/init", NULL};
    const char *envp[] = {"HOME=/", "PATH=/bin:/sbin", NULL};

    int ret = execve("/sbin/init", (char *const *)argv, (char *const *)envp);
    if (ret < 0) {
        panic("Failed to exec /sbin/init");
    }

    while (1) {
        __asm__ __volatile__("hlt");
    }
}


void panic(const char *message) {
    vga_puts("PANIC: ");
    vga_puts(message);
    while (1) {
        __asm__ __volatile__("hlt");
    }
}

int execve(const char *filename, char *const argv[], char *const envp[]) {
    switch_to_user_mode();  
    return -1; 
}

void load_initramfs() {
    vga_puts("Initramfs loaded...\n");
}

void switch_to_user_mode() {
    __asm__ __volatile__(
        "cli;"
        "mov $0x23, %ax;"
        "mov %ax, %ds;"
        "mov %ax, %es;"
        "mov %ax, %fs;"
        "mov %ax, %gs;"
        "mov %esp, %eax;"
        "pushl $0x23;"  // User mode data segment selector
        "pushl %eax;"   // Stack pointer
        "pushf;"        
        "pop %eax;"
        "or $0x200, %eax;" 
        "push %eax;"
        "pushl $0x1B;"  
        "push $1f;"     
        "iret;"
        "1:"  
    );
}
