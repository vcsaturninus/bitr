CFLAGS:= -g -Wall -Wpedantic -std=c99 -Werror -O3
C_LIB_FLAGS:= -fPIC -shared
C_SRC:= src/bitr.c 
LUA_SRC:= src/luabitr.c
CPPFLAGS:=-Isrc

# tests
TESTS_DIR:=tests/
C_TESTS_SRC:=tests.c
C_TESTS_OUT:=tests
LUA_TESTS:=tests.lua

C_LIB:= bitr.so
LUA_LIB:= luabitr.so
VALGRIND_REPORT:= valgrind.txt
OUT_DIR:=out



.PHONY: all clean

all: clean paths compile tests

paths:
	mkdir -p $(OUT_DIR)

compile: build_clib build_lualib build_ctests

build_clib:
	$(CC) $(CFLAGS) $(C_LIB_FLAGS) $(CPPFLAGS) $(C_SRC) -o $(OUT_DIR)/$(C_LIB)

build_lualib:
	$(CC) $(CFLAGS) $(C_LIB_FLAGS) $(CPPFLAGS) -llua5.3 $(C_SRC) $(LUA_SRC) -o $(OUT_DIR)/$(LUA_LIB)

build_ctests:
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TESTS_DIR)/$(C_TESTS_SRC) $(C_SRC) -o $(OUT_DIR)/$(C_TESTS_OUT)

tests: compile run_ctests run_luatests

run_ctests: build_clib build_ctests
	@./$(OUT_DIR)/$(C_TESTS_OUT)

run_luatests: build_lualib 
	@./$(TESTS_DIR)/$(LUA_TESTS)

clean: 
	rm -rf $(OUT_DIR) $(VALGRIND_REPORT)

grind: clean compile 
	valgrind --leak-check=full --show-leak-kinds=all \
        --track-origins=yes --verbose \
        --log-file=$(VALGRIND_REPORT) \
        ./$(OUT_DIR)/$(C_TESTS_OUT)


