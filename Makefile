TARGET = wanderfern

CC = gcc
CFLAGS = -std=c2x -Werror -Wall -Wextra  -Wshadow -Wconversion -Wformat=2 -Wcast-align     \
         -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls \
		 -Wundef -Wfloat-equal -Wpointer-arith -Wswitch-default -Wswitch-enum -Winit-self  \
		 -Wlogical-op -Wbad-function-cast -Wcast-qual -Wnested-externs -Wstrict-overflow=5 \
		 -O0 -g -D_DEFAULT_SOURCE -fmacro-prefix-map=$(pwd)=./
LDFLAGS = -lm
ifeq ($(OS),Windows_NT)
	CFLAGS += -I/mingw64/include
	LDFLAGS += -L/mingw64/lib -lglfw3 -lglew32 -lopengl32 -lgdi32
else
	LDFLAGS += -lglfw -lGL -lGLU -lGLEW
endif
BUILDDIR = build

ifeq ($(BUILD),release)
    CFLAGS += -O3 -DNDEBUG
endif

INCLUDE = include       \
          include/scene \
          3rdparty/stb
SRC = src/main.c            \
      src/scene/main_menu.c \
      src/scene/scene.c     \
      src/camera.c          \
      src/vec.c             \
      src/player_ctl.c      \
      src/terrain.c         \
      src/gl.c              \
      src/sprite.c          \
      src/transform.c       \
      src/mat.c             \
      src/shader.c          \
      src/texture.c         \
      src/stb_image_impl.c  \
      src/cube.c            \
      src/plant.c           \
      src/mem.c             \
      src/rect.c
OBJ = $(patsubst %.c,$(BUILDDIR)/%.c.o,$(SRC))

CFLAGS += $(addprefix -I, $(INCLUDE))

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo "[build] Link target: $@"
	@$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

$(BUILDDIR)/%.c.o: %.c
	@echo "[build] Compile $(@F)"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $^ -o $@

$(BUILDDIR)/src/stb_image_impl.c.o: src/stb_image_impl.c
	@echo "[build] Compile $(@F) (custom rules)"
	@mkdir -p $(@D)
	@$(CC) -I 3rdparty/stb -c $^ -o $@

clean:
	@rm -rf $(OBJ) $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run
