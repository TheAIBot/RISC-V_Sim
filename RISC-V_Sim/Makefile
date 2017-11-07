
OBJS = RISCVSim.o Processor.o Instruction.o InstructionDecode.o InstructionEncode.o InstructionType.o Register.o TestEncodeDecode.o TestInstructions.o
LIBS = -lm 
CFLAGS = -Wall -g
#CFLAGS = -Wall -O2 -flto -march=native

all: solver

%.o: %.cpp
	g++ -std=c++17 ${CFLAGS} -c $<

solver: ${OBJS}
	g++ -std=c++17 ${CFLAGS} ${OBJS} ${LIBS} -o RISC_V_Sim
	
clean:
	rm -f ${OBJS} RISC_V_Sim