all:json

json:json.cc
	clang++ $< -o $@ -std=c++03
