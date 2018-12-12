#ifndef _SERIAL_H_
#define _SERIAL_H_

struct serial {
    int (*begin)( int baud);
    int (*available)(void);
    int (*read)(void);
    int (*write)(int);
    int (*ok)(void);
};


#endif /* _SERIAL_H_ */
