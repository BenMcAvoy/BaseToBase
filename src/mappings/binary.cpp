#include "../mapping.hpp"
#include "../logging.hpp"
#include <cstring>

class Binary: public Mapping {
	public:
		Binary() { INFO("Binary mapping created\n") }

		char* name() override {
			return (char*)"Binary";
		}

		int map(char character, int index, int length) override {
			int doubleCount = length - index - 1;
			int toAdd = 1 << doubleCount;

			if (character == '1' && toAdd != 0)
				return toAdd;

			return 0;
		}
};

