CC = cc
CFLAGS = -Wall -Wextra -O2

TARGET = confectionery

SRCS = main.c

OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install:
	install -m 755 $(TARGET) /usr/local/bin/$(TARGET)

test:
	sh tests/test_basic.sh
	sh tests/test_preset.sh
	sh tests/test_validation.sh
	sh tests/test_cli.sh

clean:
	rm -f $(OBJS) $(TARGET)
