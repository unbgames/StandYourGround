#--------------------------
#--------------------------
# SOs
#--------------------------
#--------------------------

#-------------
# LINUX
COMPILER = g++
RMDIR = rm -rdf
RM = rm -f
DEP_FLAGS = -M -MT $@ -MT $(BIN_PATH)/$(*F).o -MP -MF $@
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm
INC_PATHS = -I$(INC_PATH) $(addprefix -I,$(SDL_INC_PATH))

FLAGS = -std=c++11 -Wall -pedantic -Wextra -Wno-unused-parameter -Werror=init-self
DFLAGS = -ggdb3 -O0 -DDEBUG
RFLAGS = -O3 -mtune=native

INC_PATH = include
SRC_PATH = src
BIN_PATH = bin
DEP_PATH = dep

CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
INC_FILES = $(wildcard $(INC_PATH)/*.h)
FILE_NAMES = $(sort $(notdir $(CPP_FILES:.cpp=)) $(notdir $(INC_FILES:.h)))
DEP_FILES = $(addprefix $(DEP_PATH)/,$(addsuffix .d,$(FILE_NAMES)))
OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))

EXEC = JOGO

#-------------
# WINDOWS
ifeq ($(OS), Windows_NT)
	RMDIR = rd /s /q
	RM = del /q

	SDL_PATHS = C:/SDL2/x86_64-w64-mingw32 C:/Tools/msys64/mingw64
	SDL_INC_PATH += $(addsuffix /include,$(SDL_PATHS))
	LINK_PATH += $(addprefix -L,$(addsuffix /lib,$(SDL_PATHS)))
	FLAGS += -mwindows
	DFLAGS += -mconsole
	LIBS := -lmingw32 -lSDL2main $(LIBS)

	EXEC := $(EXEC).exe
else
	UNAME_S := $(shell uname -s)

#-------------
# OSX
	ifeq ($(UNAME_S), Darwin)
		LIBS = -lm -framework SDL2 -framework SDL2_image -framework SDL2-mixer -framework -SDL2lSDL_ttf
	endif
endif

#--------------------------
#--------------------------
# REGRAS
#--------------------------
#--------------------------

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(COMPILER) -o $@ $^ $(LINK_PATH) $(LIBS) $(FLAGS)

$(BIN_PATH)/%.o: $(DEP_PATH)/%.d | folders
	$(COMPILER) $(INC_PATHS) $(addprefix $(SRC_PATH)/,$(notdir $(<:.d=.cpp))) -c $(FLAGS) -o $@

$(DEP_PATH)/%.d: $(SRC_PATH)/%.cpp | folders
	$(COMPILER) $(INC_PATHS) $< $(DEP_FLAGS) $(FLAGS)


clean:
	-$(RMDIR) $(DEP_PATH)
	-$(RMDIR) $(BIN_PATH)
	-$(RM) $(EXEC)

#--------------------------
#--------------------------
# EXTRAS
#--------------------------
#--------------------------

.PRECIOUS: $(DEP_FILES)
.PHONY: release debug clean folders help
.SECONDEXPANSION:
-include $$(DEP_FILES)

release: FLAGS += $(RFLAGS)
release: $(EXEC)

debug: FLAGS += $(DFLAGS)
debug: $(EXEC)

folders:
ifeq ($(OS), Windows_NT)
	@if NOT exist $(DEP_PATH)( mkdir $(DEP_PATH) )
	@if NOT exist $(BIN_PATH)( mkdir $(BIN_PATH) )
	@if NOT exist $(INC_PATH)( mkdir $(INC_PATH) )
	@if NOT exist $(SRC_PATH)( mkdir $(SRC_PATH) )
else
	@mkdir -p $(DEP_PATH) $(BIN_PATH) $(INC_PATH) $(SRC_PATH)
endif
