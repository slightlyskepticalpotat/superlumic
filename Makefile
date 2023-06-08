CFLAGS=-fPIE -fstack-protector-all -D_FORTIFY_SOURCE=2 -fdebug-prefix-map=OLD=NEW -O3 -Wall
LDFLAGS=-Wl,-z,now -Wl,-z,relro

superlumic:
	g++ *.hpp
	g++ $(CFLAGS) *.cpp -o superlumic $(LDFLAGS)
