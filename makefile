all:json

json:json.cc
	g++ $< -o $@ -g -std=c++03
