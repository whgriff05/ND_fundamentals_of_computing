CC = gcc
CFLAGS = -Wall
LIB = -lX11 -lm
INC = 


UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	GFX = gfx
endif
ifeq ($(UNAME_S), Darwin)
	GFX = gfx_mac_arm
	INC += -I/opt/X11/include/
	LIB += -L/opt/X11/lib/
endif

FUNC = projectfunc
MAIN = project
EXEC = project




$(EXEC): $(FUNC).o $(MAIN).o
	$(CC) $(FUNC).o $(MAIN).o $(GFX).o $(CFLAGS) $(LIB) -o $(EXEC)

$(FUNC).o: $(FUNC).c $(FUNC).h
	$(CC) -c $(FUNC).c $(CFLAGS) $(INC) -o $(FUNC).o

$(MAIN).o: $(MAIN).c $(FUNC).h
	$(CC) -c $(MAIN).c $(CFLAGS) $(INC) -o $(MAIN).o

clean:
	rm $(FUNC).o $(MAIN).o
	rm $(EXEC)
