CFLAGS=-fPIE -fstack-protector-all -D_FORTIFY_SOURCE=2
LDFLAGS=-Wl,-z,now -Wl,-z,relro

superlumic:
	g++ *.hpp
	g++ $(CFLAGS) *.cpp -o superlumic $(LDFLAGS)
