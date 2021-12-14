CC=g++
CPPFLAGS= -std=c++11 -Wall -I $(INCDIR)
EXEC=program3
DEBUG=debug

OBJDIR=./obj
OBJ=$(addprefix $(OBJDIR)/,Simulator.o FIFO_Sim.o LRU_Sim.o OPT_Sim.o main.o)
CURSED_OBJ=$(addprefix $(OBJDIR)/, Simulator.o FIFO_Sim.o)
DEBUG_OBJ= $(addprefix $(OBJDIR)/, Simulator_debug.o FIFO_Sim_debug.o LRU_Sim_debug.o OPT_Sim_debug.o main_debug.o)

INCDIR=./inc
INC=$(addprefix $(INCDIR)/,Simulator.h FIFO_Sim.h LRU_Sim.h OPT_Sim.h)

SRCDIR=./src
SRC=$(addprefix $(SRCDIR)/,Simulator.cpp FIFO_Sim.cpp LRU_Sim.cpp OPT_Sim.cpp main.cpp)


$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CPPFLAGS)

$(DEBUG): $(DEBUG_OBJ)
	$(CC) -g -o $@ $^ $(CPPFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(addprefix $(INCDIR)/,%.h Simulator.h)
	$(CC) -c -o $@ $< $(CPPFLAGS)

$(OBJDIR)/%_debug.o: $(SRCDIR)/%.cpp $(addprefix $(INCDIR)/,%.h Simulator.h)
	$(CC) -c -g -o $@ $< $(CPPFLAGS)

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(INC)
	$(CC) -c -o $@ $< $(CPPFLAGS)

$(OBJDIR)/main_debug.o: $(SRCDIR)/main.cpp $(INC)
	$(CC) -g -c -o $@ $< $(CPPFLAGS)


run: $(EXEC) runSims.sh
	sh runSims.sh
	
.PHONY: clean rmcsv cleanO

rmcsv:
	rm -f *.csv

cleanO:
	rm -f $(EXEC) debug $(OBJDIR)/*.o
clean:
	rm -f $(EXEC) debug $(OBJDIR)/*.o *.csv


