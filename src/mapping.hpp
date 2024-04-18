#ifndef MAPPING_HPP
#define MAPPING_HPP

// This class will be used to map index to value in the number system.
//
// Example for binary (MSB at right):
// map(1, 3) -> 4
//
// Table:
// 4 2 1
// 1 0 0
class Mapping {
	public:
		virtual int map(char character, int index, int length) = 0;

		virtual void Update() = 0;
		virtual void Render() = 0;

		virtual ~Mapping() = default;
};

#endif
