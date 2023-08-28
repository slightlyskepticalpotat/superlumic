CFLAGS=-fPIE -fstack-protector-all -D_FORTIFY_SOURCE=2 -fdebug-prefix-map=OLD=NEW -O3 -Wall -fpermissive
LDFLAGS=-Wl,-z,now -Wl,-z,relro,-lssl,-lcrypto

superlumic:
	g++ *.hpp
	g++ $(CFLAGS) *.cpp -o superlumic $(LDFLAGS)
