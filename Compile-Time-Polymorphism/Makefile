CXX = g++ 
CXXFLAGS = -std=c++20

const-cast: const-cast.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean-const-cast:
	rm const-cast

generic-mean-linux: generic-mean.cpp
	g++ -std=c++2a $^ -o $@ -fconcepts

generic-mean-apple: generic-mean.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean-generic-mean:
	rm generic-mean

simple-unique-pointer: simple-unique-pointer.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

type-traits: type-traits.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@


