#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>

#include "serial.h"

int Quit = 0;

static int quit(int yes)
{
    Quit = yes;
    if (Quit) {
        exit(0);
    }
}

static int stdio_begin(int baud)
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    return 0;
}

static int stdio_available(void)
{
    int r;
    fd_set rfds;
    struct timespec to;

    quit(feof(stdin));
    to.tv_sec = 0;
    to.tv_nsec = 0;
    FD_SET(STDIN_FILENO, &rfds);
    r = pselect(STDIN_FILENO+1, &rfds, NULL, NULL, &to, NULL);
    return (1 == r);
}

static int stdio_read(void)
{
    int c;

    quit(feof(stdin));
    c = fgetc(stdin);
    return c;
}

static int stdio_write(int c)
{
    quit(feof(stdin));
    fputc(c, stdout);
    return 0;
}

static int stdio_ok(void)
{
    quit(feof(stdin));
    return 1;
}

struct serial Serial = {
    .begin = stdio_begin,
    .available = stdio_available,
    .read = stdio_read,
    .write = stdio_write,
    .ok = stdio_ok,
};

void setup (void);
void loop (void);


int main(int argc, char *argv[])
{
    setup();
    while (!Quit) {
        loop();
    }
    return 0;
}
