CXX := g++ -std=c++11 #-ggdb

ALL := metropolis processEnergies createLattice error_over_binning corr_over_dt eval_Cv

compile: ${ALL}

metropolis: src/main.cpp src/metropolis.o src/particle.o
	${CXX} -o $@ $^

src/%.o: src/%.cpp src/%.h src/constants.h
	${CXX} -c $< -o $@

src/%.o: src/%.cpp src/constants.h
	${CXX} -c $< -o $@

%: src/%.cpp
	${CXX} $< -o $@

.PHONY: clean nuke
clean:
	rm -rf src/*~ src/*.o

nuke: clean
	rm -rf ${ALL}
