all: thanoi

thanoi: thanoi.cpp
	g++ -std=gnu++17 -o $@ $<

clean:
	rm -f thanoi
