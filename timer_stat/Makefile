##################################################################
# sample
#
##################################################################

CC = gcc
CFLAGS = -g -Wall

INC = -I$(SUNDB_HOME)/include
LFLAGS = -L$(SUNDB_HOME)/lib

LIB = -lsundbesql -lpthread -ldl -lm -lrt
ifeq ($(CSMODE), 1)
    LIB += -lsundbc
else
    ifeq ($(MIXMODE), 1)
        LIB += -lsundb
    else
        LIB += -lsundba
    endif
endif

GPEC = gpec
GPECFLAGS = 
#GPECFLAGS = --unsafe-null --no-prompt

BINS = seq_test

ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), all)
TARGET = $(MAKECMDGOALS)
OBJECT = $(TARGET).o
C_SRC  = $(TARGET).c
endif
endif

##################################################################
# implicit rules
##################################################################
.SUFFIXES: .gc .c .o

.gc.c:
	$(GPEC) $(GPECFLAGS) $^

.c.o:
	$(CC) $(CFLAGS) -c $(INC) $^

##################################################################
# build rules
##################################################################
NoTarget :
	@echo "Syntax : make {all | sample_name | clean}"
	@echo "sample_name is one of '$(BINS)'"

all :
	for target in $(BINS); do \
		$(MAKE) $$target;     \
	done

$(OBJECT) : $(C_SRC)
$(TARGET) : $(OBJECT)
	$(CC) -o $@ $^ $(LFLAGS) $(LIB)

clean :
	rm -rf $(BINS) *.o *.c *~ core
