.PHONY: all clean run shaders

# Config
ASSEMBLY := metal_app
BIN_DIR := bin
SHADER_DIR := Metal C/shaders
CC := clang

INCLUDE_FLAGS := -I"Metal C" -I"Metal C/Metal" -I"Metal C/Metal/MTFoundation" -I"Metal C/Metal/MTQuartzCore" -I"Metal C/Platform"
COMPILER_FLAGS := -Wall -Wextra -g -O0 -fno-objc-arc
LDFLAGS := -lobjc -framework Foundation -framework QuartzCore -framework Cocoa -framework Metal

all: shaders
	@mkdir -p $(BIN_DIR)
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_FLAGS) \
		"Metal C/main.c" \
		"Metal C/Platform/macos/platform_macos.m" \
		"Metal C/Platform/macos/ApplicationDelegate.m" \
		"Metal C/Platform/macos/ContentView.m" \
		"Metal C/Platform/macos/WindowDelegate.m" \
		$(LDFLAGS) -o $(BIN_DIR)/$(ASSEMBLY)

# Compile Metal shaders
shaders:
	@mkdir -p $(BIN_DIR)
	@echo "Compiling shaders..."
	xcrun metal -c "$(SHADER_DIR)/shaders.metal" -o $(BIN_DIR)/shaders.air
	xcrun metal -c "$(SHADER_DIR)/gizmo_shader.metal" -o $(BIN_DIR)/gizmo_shader.air
	xcrun metallib $(BIN_DIR)/shaders.air $(BIN_DIR)/gizmo_shader.air -o $(BIN_DIR)/default.metallib
	@echo "Shaders compiled: $(BIN_DIR)/default.metallib"

run: all
	./$(BIN_DIR)/$(ASSEMBLY)

clean:
	@rm -rf $(BIN_DIR)
