MAIN	= main
MODULES	= columns deleteHelpers operations print tables tuples variables tests


# defino reglas
.PHONY	= all run clean

# detalles del compilador
CC		= g++
CCFLAGS	= -Wall -Werror -I$(HDIR) -g -DNDEBUG

# defino variables
OBJECTS	= $(ODIR)/$(MAIN).o $(ODIR)/$(MODULES).o
HDIR	= include
CPPDIR	= src
ODIR	= obj

# compilar
all: $(ODIR)/columns.o $(ODIR)/deleteHelpers.o $(ODIR)/operations.o $(ODIR)/print.o $(ODIR)/tables.o $(ODIR)/tuples.o $(ODIR)/variables.o $(ODIR)/tests.o $(MAIN).o
	$(CC) $(CCFLAGS) -o $(MAIN) $^
	@echo "Compilado: ok"

# ejecutar lo compilado
run: $(MAIN).o
	./$(MAIN)

# compilo el main
$(ODIR)/$(MAIN).o: $(ODIR)/columns.o $(ODIR)/deleteHelpers.o $(ODIR)/operations.o $(ODIR)/print.o $(ODIR)/tables.o $(ODIR)/tuples.o $(ODIR)/variables.o $(ODIR)/tests.o $(MAIN).cpp
	$(CC) $(CCFLAGS) -c $(MAIN).cpp $(ODIR)/columns.o $(ODIR)/deleteHelpers.o $(ODIR)/operations.o $(ODIR)/print.o $(ODIR)/tables.o $(ODIR)/tuples.o $(ODIR)/variables.o $(ODIR)/tests.o -o $@

# compilo los modulos
$(ODIR)/columns.o: $(HDIR)/columns.h $(CPPDIR)/columns.cpp
	$(CC) $(CCFLAGS) -c $(CPPDIR)/columns.cpp -o $@
	
$(ODIR)/deleteHelpers.o: $(HDIR)/deleteHelpers.h $(CPPDIR)/deleteHelpers.cpp
	$(CC) $(CCFLAGS) -c $(CPPDIR)/deleteHelpers.cpp -o $@
	
$(ODIR)/print.o: $(HDIR)/print.h $(CPPDIR)/print.cpp
	$(CC) $(CCFLAGS) -c $(CPPDIR)/print.cpp -o $@
	
$(ODIR)/operations.o: $(HDIR)/operations.h $(CPPDIR)/operations.cpp
	$(CC) $(CCFLAGS) -c $(CPPDIR)/operations.cpp -o $@
	
$(ODIR)/tables.o: $(HDIR)/tables.h $(CPPDIR)/tables.cpp
	$(CC) $(CCFLAGS) -c $(CPPDIR)/tables.cpp -o $@
	
$(ODIR)/tuples.o: $(HDIR)/tuples.h $(CPPDIR)/tuples.cpp
	$(CC) $(CCFLAGS) -c $(CPPDIR)/tuples.cpp -o $@
	
$(ODIR)/variables.o: $(HDIR)/variables.h $(CPPDIR)/variables.cpp
	$(CC) $(CCFLAGS) -c $(CPPDIR)/variables.cpp -o $@

$(ODIR)/tests.o: $(HDIR)/tests.h $(CPPDIR)/tests.cpp
	$(CC) $(CCFLAGS) -c $(CPPDIR)/tests.cpp -o $@

# elimino lo generado
clean:
	rm -f main $(ODIR)/*.o *.o
	@echo "Borrado: ok"