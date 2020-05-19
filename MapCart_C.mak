#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#


WORKDIR = %cd%

CC = gcc.exe
CXX = g++.exe
AR = ar.exe
LD = g++.exe
WINDRES = windres.exe

INC = 
CFLAGS = -Wall
RESINC = 
LIBDIR = 
LIB = 
LDFLAGS = 

INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -g
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj\\Debug
DEP_DEBUG = 
OUT_DEBUG = bin\\Debug\\MapCart_C.exe

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj\\Release
DEP_RELEASE = 
OUT_RELEASE = bin\\Release\\MapCart_C.exe

OBJ_DEBUG = $(OBJDIR_DEBUG)\\src\\MapCart.o $(OBJDIR_DEBUG)\\tests\\CreateMap.o $(OBJDIR_DEBUG)\\tests\\Test_MapCart.o

OBJ_RELEASE = $(OBJDIR_RELEASE)\\src\\MapCart.o $(OBJDIR_RELEASE)\\tests\\CreateMap.o $(OBJDIR_RELEASE)\\tests\\Test_MapCart.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	cmd /c if not exist bin\\Debug md bin\\Debug
	cmd /c if not exist $(OBJDIR_DEBUG)\\src md $(OBJDIR_DEBUG)\\src
	cmd /c if not exist $(OBJDIR_DEBUG)\\tests md $(OBJDIR_DEBUG)\\tests

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)\\src\\MapCart.o: src\\MapCart.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src\\MapCart.cpp -o $(OBJDIR_DEBUG)\\src\\MapCart.o

$(OBJDIR_DEBUG)\\tests\\CreateMap.o: tests\\CreateMap.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c tests\\CreateMap.cpp -o $(OBJDIR_DEBUG)\\tests\\CreateMap.o

$(OBJDIR_DEBUG)\\tests\\Test_MapCart.o: tests\\Test_MapCart.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c tests\\Test_MapCart.cpp -o $(OBJDIR_DEBUG)\\tests\\Test_MapCart.o

clean_debug: 
	cmd /c del /f $(OBJ_DEBUG) $(OUT_DEBUG)
	cmd /c rd bin\\Debug
	cmd /c rd $(OBJDIR_DEBUG)\\src
	cmd /c rd $(OBJDIR_DEBUG)\\tests

before_release: 
	cmd /c if not exist bin\\Release md bin\\Release
	cmd /c if not exist $(OBJDIR_RELEASE)\\src md $(OBJDIR_RELEASE)\\src
	cmd /c if not exist $(OBJDIR_RELEASE)\\tests md $(OBJDIR_RELEASE)\\tests

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)\\src\\MapCart.o: src\\MapCart.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\MapCart.cpp -o $(OBJDIR_RELEASE)\\src\\MapCart.o

$(OBJDIR_RELEASE)\\tests\\CreateMap.o: tests\\CreateMap.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c tests\\CreateMap.cpp -o $(OBJDIR_RELEASE)\\tests\\CreateMap.o

$(OBJDIR_RELEASE)\\tests\\Test_MapCart.o: tests\\Test_MapCart.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c tests\\Test_MapCart.cpp -o $(OBJDIR_RELEASE)\\tests\\Test_MapCart.o

clean_release: 
	cmd /c del /f $(OBJ_RELEASE) $(OUT_RELEASE)
	cmd /c rd bin\\Release
	cmd /c rd $(OBJDIR_RELEASE)\\src
	cmd /c rd $(OBJDIR_RELEASE)\\tests

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

