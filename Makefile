SRCS := Game.cpp Main.cpp Object.cpp Player.cpp Starship.cpp Universe.cpp resource.cpp
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

FRAMEWORKS := -F Frameworks
CXXFLAGS := -g $(FRAMEWORKS) -std=c++11
LDFLAGS := $(FRAMEWORKS) \
	-framework sfml-audio -framework sfml-graphics \
	-framework sfml-system -framework sfml-window \
	-Xlinker -rpath -Xlinker @loader_path/Frameworks \
	-Xlinker -rpath -Xlinker @executable_path/Frameworks

starship-graphics: $(OBJS) Makefile
	c++ $(OBJS) -o starship-graphics $(LDFLAGS)

clean:
	rm -f starship-graphics $(OBJS)

.PHONY: clean
