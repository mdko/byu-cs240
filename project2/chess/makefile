################################################################################
# CS 240 Chess Project Makefile
#
# INSTRUCTIONS: This is a starting makefile for the chess project. You are to 
# keep this up-to-date as you add source files. In addition to keeping it 
# up-to-date with new files you create, you need to make the following changes 
# to this makefile:
# 
#	- compile the object files associated with the View into a shared library, 
#	- add pseudo-targets for the different run modes (namely "runhh", "runhc",
#		"runch", and "runcc"),
#	- add a "test" pseudo-target (you will probably want to make a new executable
#		for this with its own main method),
#	- add a "lib" pseudo-target,
#	- edit the command associated with the memcheck pseudo-target (i.e.,
#		the valgrind command. See the note above it for details).
# 
# NOTES: 
# 1. All the code for the GUI side of this project is provided for you. As a 
# result, there are some things in this makefile which you do not need to alter.
# Such items will be clearly marked with comments.
# 2. Out-of-the-box, without making any changes to this initial makefile, 
# running "make run" will compile the code and bring up an empty GUI. 
################################################################################

 
############### --- BEGIN UNTOUCHABLE SECTION - Do Not Edit --- ################
# Macros for GUI libraries.
GTKMM = gtkmm-2.4
SIGC = sigc++-2.0
LIBGLADE = libglademm-2.4

# TODO Re-phrase: CFLAGS are the -I values needed to compile files using the 
# GTKMM, SIGC, and LIBGLADE libraries
CFLAGS = `pkg-config $(GTKMM) $(SIGC) $(LIBGLADE) --cflags`
# TODO Re-phrase: LIBS are the paths to the static libraries for GTKMM, SIGC,
# and LIBGLADE needed for linking
LIBS   = `pkg-config $(GTKMM) $(SIGC) $(LIBGLADE) --libs`
####################### --- END UNTOUCHABLE SECTION --- ########################


# TODO Re-phrase: Macros for directory tree locations
MODEL_SRC = model/src/
MODEL_INC = model/inc/
MODEL_OBJ = model/obj/
VIEW_SRC = view/src/
VIEW_INC = view/inc/
VIEW_OBJ = view/obj/
CONT_SRC = controller/src/
CONT_INC = controller/inc/
CONT_OBJ = controller/obj/
UTILS_SRC = utils/src/
UTILS_INC = utils/inc/
UTILS_OBJ = utils/obj/
LIB_FILE = lib/libchessgui.so			# shared library file (ADDED)
LIB_UTILS_FILE = lib/libcs240utils.a	# static utils library file, from project 1 (ADDED)
EXE = bin/chess							# normal executable
TEST_EXE = bin/test						# test executable (ADDED)
MEXE = bin/mchess						# executable for memory testing
# Uncomment to search for path to shared libary file
LD_PATH = export LD_LIBRARY_PATH=./lib;

HH = 0									# human v human (ADDED)
HC = 1									# human v computer (ADDED)
CH = 2									# computer v human (ADDED)
CC = 3									# computer v computer (ADDED)

# Macros for compilation flags
INCLUDES = -I$(MODEL_INC) -I$(VIEW_INC) -I$(CONT_INC) -I$(UTILS_INC)
DEBUG = -g # Uncomment this if you want to compile with debug info

# Uncomment the flag on this next line to turn off the logging messages from the
# GUI
LOG_FLAG = '-DLOG_LEVEL_HIDE_MASK=(G_LOG_LEVEL_DEBUG|G_LOG_LEVEL_INFO)'


# There are two different main.o files. One is for memory testing.
MAIN_O = $(CONT_OBJ)main.o
MEMMAIN_O = $(CONT_OBJ)memcheck_main.o
TEST_O = $(CONT_OBJ)test.o		# (ADDED)

# This macro should be used to store all of the object files created 
# from *your* source files
MY_OBJS =  $(CONT_OBJ)ChessController.o \
	  $(CONT_OBJ)HumanPlayer.o \
	  $(CONT_OBJ)ComputerPlayer.o \
	  $(MODEL_OBJ)ChessGame.o \
	  $(MODEL_OBJ)MoveHistory.o \
	  $(MODEL_OBJ)Move.o \
	  $(MODEL_OBJ)ChessBoard.o \
	  $(MODEL_OBJ)BoardPosition.o \
	  $(MODEL_OBJ)King.o \
	  $(MODEL_OBJ)Queen.o \
	  $(MODEL_OBJ)Rook.o \
	  $(MODEL_OBJ)Bishop.o \
	  $(MODEL_OBJ)Knight.o \
	  $(MODEL_OBJ)Pawn.o \
	  $(MODEL_OBJ)XMLHandler.o
	  
# These are obj's for static cs240utils library (ADDED)
LIB_UTILS_OBJS = $(UTILS_OBJ)StringUtil.o \
	  $(UTILS_OBJ)URLInputStream.o \
	  $(UTILS_OBJ)FileInputStream.o \
	  $(UTILS_OBJ)HTTPInputStream.o \
	  $(UTILS_OBJ)CommandRunner.o \
	  $(UTILS_OBJ)FileSystem.o \
	  $(UTILS_OBJ)HTMLToken.o \
	  $(UTILS_OBJ)HTMLTokenizer.o

# These are all the object files that go into the shared library
LIB_OBJS = $(VIEW_OBJ)ChessView.o \
      $(VIEW_OBJ)ChessGuiBoardCell.o \
      $(VIEW_OBJ)ChessGuiBoard.o \
      $(VIEW_OBJ)ChessGui.o \
      $(VIEW_OBJ)ChessGuiImages.o \
      $(VIEW_OBJ)SelectDialog.o



################################################################################
# Pseudo-targets

runhh: $(EXE)
	$(LD_PATH) $(EXE) $(HH)
	
runhc: $(EXE)
	$(LD_PATH) $(EXE) $(HC)
	
runch: $(EXE)
	$(LD_PATH) $(EXE) $(CH)
	
runcc: $(EXE)
	$(LD_PATH) $(EXE) $(CC)

test: $(TEST_EXE)
	$(LD_PATH) $(TEST_EXE)
	
lib: $(LIB_FILE)

bin: $(EXE)

# Run the executable for memory testing
# Instructions: Edit the command below so that it runs the  
# memory-check executable in Human-Human mode (i.e., add necessary command  
# line arguments to the end of valgrind the command below).	
memcheck: $(MEXE)
	$(LD_PATH) valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 --show-reachable=yes --suppressions=string.supp $(MEXE) $(HH)

# Clean removes all of the .o files, libraries, and executables
clean:
	@rm -f $(MODEL_OBJ)*.o
	@rm -f $(VIEW_OBJ)*.o
	@rm -f $(CONT_OBJ)*.o
	@rm -f $(UTILS_OBJ)*.o			# (ADDED)
	@rm -f lib/$(LIB_FILE)			# (ADDED)
	@rm -f lib/$(LIB_UTILS_FILE)	# (ADDED)
	@rm -f $(EXE)
	@rm -f $(MEXE)
	@rm -f $(TEST_EXE)				# (ADDED)


################################################################################
# Targets for executables and main object files

# Explanation: There are two different executables, with two different main 
# object files, because main.cpp needs to be built differently depending on 
# whether you are doing memory testing or not. This is because the GTK library,
# and other GUI tools, have memory leaks that we cannot figure out how to 
# suppress. Therefore, when building an executable for memory testing, we use a
# macro (MEMCHECK) to tell the compiler to not include the code that builds the
# GUI. So when we check for memory leaks during passoff, we don't have to use
# the GUI.

# Main executable
# Note: Once you have added the ability to make a library out of the View files, 
# the executable should be dependent on, and link in the library file, not the 
# .o files! That means, instead of linking in $(LIB_OBJS) below, you should link
# in the actual library file.
$(EXE): $(MAIN_O) $(MY_OBJS) $(LIB_FILE) $(LIB_UTILS_FILE)
	@# Re-link executable. Again, this should link the library file, not the .o's
	g++ $(INCLUDES) -o $(EXE) -Llib $(MAIN_O) $(MY_OBJS) -lchessgui -lcs240utils $(CFLAGS) $(LIBS)
	chmod ugo+x $(EXE)

# Executable for memory testing
$(MEXE): $(MEMMAIN_O) $(MY_OBJS) $(LIB_FILE) $(LIB_UTILS_FILE)
	@# Re-link executable. Again, this should link the library file, not the .o's
	g++ $(INCLUDES) -o $(MEXE) -Llib $(MEMMAIN_O) $(MY_OBJS) -lchessgui -lcs240utils $(CFLAGS) $(LIBS)
	chmod ugo+x $(MEXE)
	
# Executable for running unit tests (ADDED)
$(TEST_EXE): $(TEST_O) $(MY_OBJS) $(LIB_FILE) $(LIB_UTILS_FILE)
	g++ $(INCLUDES) -o $(TEST_EXE) -Llib $(TEST_O) $(MY_OBJS) -lchessgui -lcs240utils $(CFLAGS) $(LIBS)

# Main object file
$(MAIN_O): $(CONT_SRC)main.cpp $(VIEW_INC)ChessGuiImages.h $(VIEW_INC)ChessView.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(MAIN_O) -c $(LOG_FLAG) $(CONT_SRC)main.cpp

# Main .o for memory testing
$(MEMMAIN_O): $(CONT_SRC)main.cpp $(VIEW_INC)ChessGuiImages.h $(VIEW_INC)ChessView.h
	g++ -DMEMCHECK $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(MEMMAIN_O) -c $(LOG_FLAG) $(CONT_SRC)main.cpp

# Main for unit testing (ADDED)
$(TEST_O): $(CONT_SRC)test.cpp $(VIEW_INC)ChessGuiImages.h $(VIEW_INC)ChessView.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(TEST_O) -c $(LOG_FLAG) $(CONT_SRC)test.cpp



################################################################################
# Targets for YOUR object files... (ADDED)

$(CONT_OBJ)ChessController.o: $(CONT_SRC)ChessController.cpp $(CONT_INC)ChessController.h $(CONT_INC)IChessController.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(CONT_OBJ)ChessController.o -c $(LOG_FLAG) $(CONT_SRC)ChessController.cpp

$(CONT_OBJ)HumanPlayer.o: $(CONT_SRC)HumanPlayer.cpp $(CONT_INC)HumanPlayer.h $(CONT_INC)IChessPlayer.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(CONT_OBJ)HumanPlayer.o -c $(LOG_FLAG) $(CONT_SRC)HumanPlayer.cpp

$(CONT_OBJ)ComputerPlayer.o: $(CONT_SRC)ComputerPlayer.cpp $(CONT_INC)ComputerPlayer.h $(CONT_INC)IChessPlayer.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(CONT_OBJ)ComputerPlayer.o -c $(LOG_FLAG) $(CONT_SRC)ComputerPlayer.cpp
	
$(MODEL_OBJ)ChessGame.o: $(MODEL_SRC)ChessGame.cpp $(MODEL_INC)ChessGame.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(MODEL_OBJ)ChessGame.o -c $(LOG_FLAG) $(MODEL_SRC)ChessGame.cpp
	
$(MODEL_OBJ)MoveHistory.o: $(MODEL_SRC)MoveHistory.cpp $(MODEL_INC)MoveHistory.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(MODEL_OBJ)MoveHistory.o -c $(LOG_FLAG) $(MODEL_SRC)MoveHistory.cpp
	
$(MODEL_OBJ)Move.o: $(MODEL_SRC)Move.cpp $(MODEL_INC)Move.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(MODEL_OBJ)Move.o -c $(LOG_FLAG) $(MODEL_SRC)Move.cpp

$(MODEL_OBJ)ChessBoard.o: $(MODEL_SRC)ChessBoard.cpp $(MODEL_INC)ChessBoard.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(MODEL_OBJ)ChessBoard.o -c $(LOG_FLAG) $(MODEL_SRC)ChessBoard.cpp
	
$(MODEL_OBJ)BoardPosition.o: $(MODEL_SRC)BoardPosition.cpp $(MODEL_INC)BoardPosition.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(MODEL_OBJ)BoardPosition.o -c $(LOG_FLAG) $(MODEL_SRC)BoardPosition.cpp
	
$(MODEL_OBJ)King.o: $(MODEL_SRC)King.cpp $(MODEL_INC)King.h $(MODEL_INC)IChessPiece.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(MODEL_OBJ)King.o -c $(LOG_FLAG) $(MODEL_SRC)King.cpp
	
$(MODEL_OBJ)Queen.o: $(MODEL_SRC)Queen.cpp $(MODEL_INC)Queen.h $(MODEL_INC)IChessPiece.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(MODEL_OBJ)Queen.o -c $(LOG_FLAG) $(MODEL_SRC)Queen.cpp
	
$(MODEL_OBJ)Rook.o: $(MODEL_SRC)Rook.cpp $(MODEL_INC)Rook.h $(MODEL_INC)IChessPiece.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(MODEL_OBJ)Rook.o -c $(LOG_FLAG) $(MODEL_SRC)Rook.cpp
	
$(MODEL_OBJ)Bishop.o: $(MODEL_SRC)Bishop.cpp $(MODEL_INC)Bishop.h $(MODEL_INC)IChessPiece.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(MODEL_OBJ)Bishop.o -c $(LOG_FLAG) $(MODEL_SRC)Bishop.cpp
	
$(MODEL_OBJ)Knight.o: $(MODEL_SRC)Knight.cpp $(MODEL_INC)Knight.h $(MODEL_INC)IChessPiece.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(MODEL_OBJ)Knight.o -c $(LOG_FLAG) $(MODEL_SRC)Knight.cpp
	
$(MODEL_OBJ)Pawn.o: $(MODEL_SRC)Pawn.cpp $(MODEL_INC)Pawn.h $(MODEL_INC)IChessPiece.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(MODEL_OBJ)Pawn.o -c $(LOG_FLAG) $(MODEL_SRC)Pawn.cpp
	
$(MODEL_OBJ)XMLHandler.o: $(MODEL_SRC)XMLHandler.cpp $(MODEL_INC)XMLHandler.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(MODEL_OBJ)XMLHandler.o -c $(LOG_FLAG) $(MODEL_SRC)XMLHandler.cpp


################################################################################
# creates a static library file (.a file) for cs240utils (ADDED)

$(LIB_UTILS_FILE): $(LIB_UTILS_OBJS)
	ar r $(LIB_UTILS_FILE) $(LIB_UTILS_OBJS)	
	
$(UTILS_OBJ)StringUtil.o: $(UTILS_SRC)StringUtil.cpp $(UTILS_INC)StringUtil.h
	g++ -o $(UTILS_OBJ)StringUtil.o -c -Iutils/inc $(UTILS_SRC)StringUtil.cpp
	
$(UTILS_OBJ)URLInputStream.o: $(UTILS_SRC)URLInputStream.cpp $(UTILS_INC)URLInputStream.h $(UTILS_INC)StringUtil.h \
							   $(UTILS_INC)CS240Exception.h $(UTILS_INC)HTTPInputStream.h $(UTILS_INC)FileInputStream.h \
								$(UTILS_INC)InputStream.h
	g++ -o $(UTILS_OBJ)URLInputStream.o -c -Iutils/inc $(UTILS_SRC)URLInputStream.cpp

$(UTILS_OBJ)FileInputStream.o: $(UTILS_SRC)FileInputStream.cpp $(UTILS_INC)FileInputStream.h $(UTILS_INC)CS240Exception.h
	g++ -o $(UTILS_OBJ)FileInputStream.o -c -Iutils/inc $(UTILS_SRC)FileInputStream.cpp

$(UTILS_OBJ)HTTPInputStream.o: $(UTILS_SRC)HTTPInputStream.cpp $(UTILS_INC)HTTPInputStream.h $(UTILS_INC)CS240Exception.h \
								$(UTILS_INC)StringUtil.h
	g++ -o $(UTILS_OBJ)HTTPInputStream.o -c -Iutils/inc $(UTILS_SRC)HTTPInputStream.cpp 

$(UTILS_OBJ)CommandRunner.o: $(UTILS_SRC)CommandRunner.cpp $(UTILS_INC)CommandRunner.h $(UTILS_INC)CS240Exception.h \
								$(UTILS_INC)StringUtil.h
	g++ -o $(UTILS_OBJ)CommandRunner.o -c -Iutils/inc $(UTILS_SRC)CommandRunner.cpp
	
$(UTILS_OBJ)FileSystem.o: $(UTILS_SRC)FileSystem.cpp $(UTILS_INC)FileSystem.h $(UTILS_INC)CS240Exception.h \
							$(UTILS_INC)UnitTest.h
	g++ -o $(UTILS_OBJ)FileSystem.o -c -Iutils/inc $(UTILS_SRC)FileSystem.cpp

$(UTILS_OBJ)HTMLToken.o: $(UTILS_SRC)HTMLToken.cpp $(UTILS_INC)HTMLToken.h
	g++ -o $(UTILS_OBJ)HTMLToken.o -c -Iutils/inc $(UTILS_SRC)HTMLToken.cpp
	
$(UTILS_OBJ)HTMLTokenizer.o: $(UTILS_SRC)HTMLTokenizer.cpp $(UTILS_INC)HTMLTokenizer.h
	g++ -o $(UTILS_OBJ)HTMLTokenizer.o -c -Iutils/inc $(UTILS_SRC)HTMLTokenizer.cpp
	


################################################################################
# Targets for GUI-related object files
# Instructions: These will have to be recompiled as position-independent code, 
# so that they can be put into a shared library.

#(ADDED)
$(LIB_FILE): $(LIB_OBJS)
	g++ -shared -o $(LIB_FILE) $(LIB_OBJS)

$(VIEW_OBJ)ChessView.o: $(VIEW_SRC)ChessView.cpp $(VIEW_INC)SelectDialog.h $(VIEW_INC)ChessView.h $(CONT_INC)IChessController.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)ChessView.o -c -fPIC $(LOG_FLAG) $(VIEW_SRC)ChessView.cpp

$(VIEW_OBJ)ChessGuiBoardCell.o: $(VIEW_SRC)ChessGuiBoardCell.cpp $(VIEW_INC)ChessGuiBoardCell.h $(VIEW_INC)ChessGuiImages.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)ChessGuiBoardCell.o -c -fPIC $(VIEW_SRC)ChessGuiBoardCell.cpp

$(VIEW_OBJ)ChessGuiBoard.o: $(VIEW_SRC)ChessGuiBoard.cpp $(VIEW_INC)ChessGuiBoard.h $(VIEW_INC)ChessGui.h $(VIEW_INC)ChessGuiImages.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)ChessGuiBoard.o -c -fPIC $(VIEW_SRC)ChessGuiBoard.cpp

$(VIEW_OBJ)ChessGui.o: $(VIEW_SRC)ChessGui.cpp $(VIEW_INC)ChessGui.h $(VIEW_INC)ChessGuiImages.h $(VIEW_INC)SelectDialog.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)ChessGui.o -c -fPIC $(VIEW_SRC)ChessGui.cpp

$(VIEW_OBJ)ChessGuiImages.o: $(VIEW_SRC)ChessGuiImages.cpp $(VIEW_INC)ChessGuiImages.h $(VIEW_INC)Inline.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)ChessGuiImages.o -c -fPIC $(VIEW_SRC)ChessGuiImages.cpp

$(VIEW_OBJ)SelectDialog.o: $(VIEW_SRC)SelectDialog.cpp
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)SelectDialog.o -c -fPIC $(VIEW_SRC)SelectDialog.cpp

