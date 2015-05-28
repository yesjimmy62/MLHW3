
GCC=g++
GCCFLAG:=-Iheader -Ieigen -O2 -Wall -g
EXECUTABLE_TRAIN:=RNN_TRAIN
EXECUTABLE_PREDICT:=RNN_PREDICT
OBJ_PATH=Object

CC_FILE:= Main_RNN.cpp Main_Predict.cpp Load_Data.cpp HW3_MakingAnswers.cpp

TRAIN_OBJ := Main_RNN.o Load_Data.o HW3_MakingAnswers.o
PREDICT_OBJ := Main_Predict.o Load_Data.o
vpath %.cpp src

OBJ := ${CC_FILE:.cpp=.o}

all: ${EXECUTABLE_TRAIN} ${EXECUTABLE_PREDICT}

${EXECUTABLE_TRAIN} : ${patsubst %, ${OBJ_PATH}/%, ${TRAIN_OBJ}}
		$(GCC) $(GCCFLAG) $^ -o $@
#		mv $(EXECUTABLE_TRAIN) .

${EXECUTABLE_PREDICT} : ${patsubst %, ${OBJ_PATH}/%, ${PREDICT_OBJ}}
		$(GCC) $(GCCFLAG) $^ -o $@
#		mv $(EXECUTABLE_PREDICT) .

${OBJ_PATH}/%.o : %.cpp
		$(GCC) $(GCCFLAG) -o $@ -c $^

run : $(EXECUTABLE)
		./$(EXECUTABLE) 

clean:
		$(RM) -rf *.o $(EXECUTABLE_TRAIN) $(EXECUTABLE_PREDICT)
		$(RM) -f ${OBJ_PATH}/*

input:
	$(GCC) -g src/make_input.cpp -o make_input
	./make_input input
test:
	$(GCC) -g src/make_input.cpp -o make_input
	./make_input test
guess:
	$(GCC) -g src/make_input.cpp -o make_input
	./make_input guess
