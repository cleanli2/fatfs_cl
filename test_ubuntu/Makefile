export CC = gcc           

TARGET = fatfstest
INC_FLAGS= -I../source
C_SRC= \
m.c \
../source/diskio.c \
../source/ff.c \
../source/ffsystem.c \
../source/ffunicode.c


C_OBJ=$(C_SRC:%.c=%.o)

CFLAGS =  -W -Wall $(INC_FLAGS) 

all:$(C_OBJ)
	$(CC) $(C_OBJ) -o $(TARGET)

$(C_OBJ):%.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm $(C_OBJ)
