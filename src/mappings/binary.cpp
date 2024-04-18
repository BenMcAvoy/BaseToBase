#include "../mapping.hpp"
#include "../logging.hpp"
#include "imgui.h"
#include <cstring>

class Binary: public Mapping {
	private:
		char oldInput[256];
		char input[256];
		int output;

	public:
		Binary() { INFO("Binary mapping created\n") }

		int map(char character, int index, int length) override {
			int doubleCount = length - index - 1;
			int toAdd = 1 << doubleCount;

			if (character == '1' && toAdd != 0)
				return toAdd;

			return 0;
		}

		void Update() override {
			if (strcmp(this->input, this->oldInput)) {
				this->output = 0;

				for (int i = 0; i < (int)strlen(this->input); i++) {
					this->output += this->map(this->input[i], i, strlen(this->input));
				}

				strcpy(this->oldInput, this->input);

				INFO("Recomputed decimal from binary.\n");
			}
		}

		void Render() override {
			ImGui::Begin("Binary");
			ImGui::InputText("Input", this->input, IM_ARRAYSIZE(this->input));
			ImGui::Text("Output: %d", this->output);
			ImGui::End();
		}
};

