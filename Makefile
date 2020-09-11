make:
	g++ -w -std=c++14 -Wfatal-errors \
	./src/*.cpp \
	-o game \
	-I"./lib/lua" \
	-L"./lib/lua" \
	-llua \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2_mixer;

debug:
	g++ -g -w -std=c++14 -Wfatal-errors \
	./src/*.cpp \
	-o game \
	-I"./lib/lua" \
	-L"./lib/lua" \
	-llua \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2_mixer;

clean:
	rm ./game;

run:
	./game;

build_and_run:
	g++ -w -std=c++14 -Wfatal-errors \
	./src/*.cpp \
	-o game \
#	-I"./lib/lua" \
#	-L"./lib/lua" \
#	-llua \
	-lSDL2; # \
#	-lSDL2_image \
#	-lSDL2_ttf \
#	-lSDL2_mixer \
	&& ./game;
