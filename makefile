TARGET = wanderfern

CC = gcc
CFLAGS = -std=c2x -Werror -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wformat=2 \
         -Wcast-align -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations \
         -Wredundant-decls -Wundef -Wfloat-equal -Wpointer-arith -Wswitch-default \
         -Wswitch-enum -Winit-self -Wlogical-op -Wbad-function-cast \
         -Wcast-qual -Wnested-externs -Wstrict-overflow=5 -O0 -g -Iinclude -D_DEFAULT_SOURCE \
		 -fmacro-prefix-map=$(pwd)=./
LDFLAGS = -lm
ifeq ($(OS),Windows_NT)
	CFLAGS += -I/mingw64/include
	LDFLAGS += -L/mingw64/lib -lglfw3 -lglew32 -lopengl32 -lgdi32
else
	LDFLAGS += -lglfw -lGL -lm
endif
BUILDDIR = build

ifeq ($(BUILD),release)
    CFLAGS += -O3 -DNDEBUG
endif

SRC = src/main.c
OBJ = $(SRC:=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo "[build] Link target: $@"
	@$(CC) $(CFLAGS) -o $@ $(addprefix $(BUILDDIR)/,$+) $(LDFLAGS)

%.c.o :: %.c
	@echo "[build] Compile $(@F)"
	@mkdir -p $(BUILDDIR)/$(@D)
	@$(CC) $(CFLAGS) -c $< -o $(BUILDDIR)/$@

clean:
	@rm -f $(OBJ) $(TARGET)

run: all
	@$(BUILDDIR)/$(TARGET)

.PHONY: all clean run
