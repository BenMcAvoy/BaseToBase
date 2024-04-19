#include "../mapping.hpp"
#include "../logging.hpp"
#include <cmath>
#include <cstring>

class Hexadecimal: public Mapping {
	public:
		Hexadecimal() { INFO("Hexadecimal mapping created\n") }

		char* name() override {
			return (char*)"Hexadecimal";
		}

		int map(char character, int index, int length) override {
			int characterValue = 0;

			if (character >= '0' && character <= '9') {
				characterValue = character - '0';
			} else if ((character >= 'a' && character <= 'f') || (character >= 'A' && character <= 'F')) {
				characterValue = character - (character >= 'a' ? 'a' : 'A') + 10;
			}

			int power = length - index - 1;
			return characterValue * pow(16, power);

			return characterValue;
		}
};

