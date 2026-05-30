CC      = gcc
CFLAGS  = -ansi -pedantic -g -D_GNU_SOURCE
LDFLAGS = -lm

COMMON_OBJS = ds.o

SERVER_OBJS = $(COMMON_OBJS) \
              user.o user_hash.o user_mng.o \
              group.o group_hash.o group_mng.o \
              free_mc_ip_queue.o \
              server_net.o server_mng.o \
              server_main.o

CLIENT_OBJS = $(COMMON_OBJS) \
              client_net.o client_groups_mng.o \
              client_mng.o ui.o \
              client_main.o

ALL = server client mc_sender mc_receiver

.PHONY: all clean

all: $(ALL)

server: $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

client: $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

mc_sender: ds.o mc_sender.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

mc_receiver: ds.o mc_receiver.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(ALL)