SRCS :=
SRCS += main.c
SRCS += ulisp.c
OBJS := $(SRCS:.c=.o)
DEPS := $(SRCS:.c=.d)

CFLAGS :=
CFLAGS += -g
CFLAGS += -O
CFLAGS += -MD
#CFLAGS += -Wall
#CFLAGS += -Werror

LIBS :=
LIBS += -lm

TARGET := ulisp

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

clean:
	$(RM) $(OBJS) $(DEPS)

nuke: clean
	$(RM) $(TARGET)

-include $(DEPS)
