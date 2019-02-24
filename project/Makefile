LEXYACC_DIR = lexyacc-code
BUILD_DIR = build
BIN_DIR = bin

all: $(BIN_DIR)/calc3i.exe

$(BIN_DIR)/calc3i.exe: $(LEXYACC_DIR)/calc3i.c lexyacc_stuff
        cp $(LEXYACC_DIR)/calc3i.c $(BUILD_DIR)
        gcc $(BUILD_DIR)/y.tab.o $(BUILD_DIR)/lex.yy.o $(BUILD_DIR)/calc3i.c -o $(BIN_DIR)/calc3i.exe

lexyacc_stuff:
	bison -y -d $(LEXYACC_DIR)/calc3.y -o $(BUILD_DIR)/y.tab.c
	flex -o $(BUILD_DIR)/lex.yy.c $(LEXYACC_DIR)/calc3.l
	cp $(LEXYACC_DIR)/calc3.h $(BUILD_DIR)/calc3.h
	gcc -c $(BUILD_DIR)/y.tab.c -o $(BUILD_DIR)/y.tab.o
	gcc -c $(BUILD_DIR)/lex.yy.c -o $(BUILD_DIR)/lex.yy.o

clean:
	rm $(BUILD_DIR)/*
	rm $(BIN_DIR)/*
