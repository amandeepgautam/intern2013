TARGET	=	exec

CC	=	g++
CPPFLAGS= 	-Wall -ansi -g
LINKER	=	g++ -o
LFLAGS	= 	-I. -lm -lpthread

BINDIR	=	bin
OBJDIR	=	obj
SRCDIR	=	src
INTERFACE =	interface

PROGRAMSOURCES 	:= 	$(wildcard $(SRCDIR)/*.cpp)
PROGRAMINTERFACE:=	$(wildcard $(INTERFACE)/*.h)
OBJECTS 	:= 	$(PROGRAMSOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET)	: 	$(OBJECTS)
	$(LINKER) $@ $(LFLAGS) $(OBJECTS)

#pull the dependencies to the .o files
-include $(OBJECTS:.o=.d)

# '@' sign makes sure that commands are not echod at stdout.
#the -o $@ says to put the output of the compilation in the file named on the left side of the :.
#the $< is the first item in the dependencies list. Basically the name of the .c file which is to be compiled.
#The stem with which an implicit rule matches. If the target is dir/a.foo.b and the target pattern is a.%.b then the stem is dir/foo.
$(OBJECTS)		:	$(OBJDIR)/%.o :$(SRCDIR)/%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@ $(STD)
	$(CC) $(CPPFLAGS) -MM $< > $(OBJDIR)/$*.d
	@mv -f $(OBJDIR)/$*.d $(OBJDIR)/$*.d.tmp
	@sed -e 's|.*:|$(OBJDIR)/$*.o:|' < $(OBJDIR)/$*.d.tmp > $(OBJDIR)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(OBJDIR)/$*.d.tmp | fmt -1 | \
	 sed -e 's/^ *//' -e 's/$$/:/' >> $(OBJDIR)/$*.d
	@rm -f $(OBJDIR)/$*.d.tmp

.PHONY	: 	run
run		:
	./$(BINDIR)/$(TARGET) ${TYPE} ${INP_FILE} ${OUT_FILE} ${GRD_TRUTH}

print:
	@echo $(OBJECTS)
