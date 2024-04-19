#ifndef MAPPING_HPP
#define MAPPING_HPP

#include "globals.cpp"

// This class will be used to map index to value in the number system.
//
// Example for binary (MSB at right):
// map(1, 3) -> 4
//
// Table:
// 4 2 1
// 1 0 0
#include <cstring>
class Mapping {
	private:
		char oldInput[256] = {0};

	public:
		virtual char* name() = 0;
		virtual int map(char character, int index, int length) = 0;

		virtual ~Mapping() = default;

		virtual void Update() {
			if (strcmp(globals::input, this->oldInput)) {
				globals::output = 0;

				for (int i = 0; i < (int)strlen(globals::input); i++) {
					globals::output += this->map(globals::input[i], i, strlen(globals::input));
				}

				strcpy(this->oldInput, globals::input);
			}
		}
};

		/* void Update() override { */
		/* 	if (strcmp(this->input, this->oldInput)) { */
		/* 		this->output = 0; */

		/* 		for (int i = 0; i < (int)strlen(this->input); i++) { */
		/* 			this->output += this->map(this->input[i], i, strlen(this->input)); */
		/* 		} */

		/* 		strcpy(this->oldInput, this->input); */

		/* 		INFO("Recomputed decimal from binary.\n"); */
		/* 	} */
		/* } */

		/* void Render() override { */
		/* 	ImGui::Begin("Binary"); */
		/* 	ImGui::InputText("Input", this->input, IM_ARRAYSIZE(this->input)); */
		/* 	ImGui::Text("Output: %d", this->output); */
		/* 	ImGui::End(); */
		/* } */

#endif
