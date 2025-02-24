ifeq ($(OS),Windows_NT)
	UNAME := Windows
else
	UNAME := $(shell uname)
endif

files := testgame.cpp game.cpp scene.cpp inputs.cpp rendering.cpp main.cpp 
obj_dir := obj
compiled := $(files:%.cpp=$(obj_dir)/%.o)
CXX := g++

ifeq ($(UNAME), Linux)
CXXFLAGS := -w -O2 -lSDL2 -lSDL2_image
endif

ifeq ($(UNAME), Windows)
CXXFLAGS := -static-libgcc -static-libstdc++ -mwindows -w -O2 -lSDL2 -lSDL2_image
endif


all: ./l
	
./l: $(compiled)
	$(CXX) $(compiled) $(CXXFLAGS) -o $@

$(obj_dir)/%.o: %.cpp | $(obj_dir)
	$(CXX) -c $< -o $@

$(obj_dir):
	mkdir $(obj_dir)

touch:
	touch *.cpp




ifeq ($(UNAME), Linux)

clean:
	rm -f $(compiled) ./l
	rm -rf $(obj_dir)

endif
ifeq ($(UNAME), Windows)

clean:
	rmdir /s /q $(obj_dir)

endif