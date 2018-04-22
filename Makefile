CXX = g++

CXXFLAGS = -g -std=c++11 -MMD -Wall -I src -D USE_VARINT

#OBJ = $(patsubst %.cc,%.o,$(wildcard src/*.cc))
OBJ = src/fst.o src/utils.o

TEST = test/varint-test

TOOL = tools/fst-init tools/fst-info tools/fst-to-dot \
       tools/transition-id-to-pdf

all: $(TEST) $(TOOL) $(OBJ)

test: $(TEST)
	@for x in $(TEST); do \
		printf "Running $$x ..."; \
		./$$x;  \
		if [ $$? -ne 0 ]; then \
			echo "... Fail $$x"; \
		else \
			echo "... Success $$x"; \
		fi \
	done

check:
	for file in src/*.h src/*.cc test/*.cc tools/*.cc; do \
		echo $$file; \
        cpplint --filter=-build/header_guard,-readability/check,-build/include_subdir $$file; \
	done

test/%: test/%.cc $(OBJ)
	$(CXX) $< $(OBJ) $(CXXFLAGS) -o $@

tools/%: tools/%.cc $(OBJ)
	$(CXX) $< $(OBJ) $(CXXFLAGS) -o $@

.PHONY: clean

clean:
	rm -rf $(OBJ); rm -rf $(TEST)

-include */*.d
