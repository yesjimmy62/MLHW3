
GCC=g++
GCCFLAG:=-Iheader -Ieigen -O0 -Wall -g
EXECUTABLE:=RNN
OBJ_PATH=Object

CC_FILE:= Main_RNN.cpp Load_Data.cpp

vpath %.cpp src

OBJ := ${CC_FILE:.cpp=.o}

${EXECUTABLE} : ${patsubst %, ${OBJ_PATH}/%, ${OBJ}}
		$(GCC) $(GCCFLAG) $^ -o $@
#		mv $(EXECUTABLE) .

${OBJ_PATH}/%.o : %.cpp
		$(GCC) $(GCCFLAG) -o $@ -c $^

run : $(EXECUTABLE)
		./$(EXECUTABLE) 

clean:
		$(RM) -rf *.o $(EXECUTABLE)
		$(RM) -f ${OBJ_PATH}/*
