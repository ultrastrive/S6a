CC = gcc
CFLAGS = -Wall -Wswitch $(shell  mysql_config --cflags)
LIBS = -lfdproto -lfdcore $(shell mysql_config --libs)

BIN = ssix_a
OBJS = test.o init.o dict_init.o request.o msg.o serv.o ans_cb.o

$(BIN):: $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS) $(LIBS)

test.o:: interf_ssix.h
init.o:: internal_ssix.h
dict_init.o:: internal_ssix.h
request.o:: internal_ssix.h 
msg.o:: internal_ssix.h 
serv.o:: internal_ssix.h
ans_cb.o::internal_ssix.h	

clean::
	/bin/rm -f *~ *.o
