#ifndef SOURCE_HPP
#define SOURCE_HPP

#include "node.hpp"
#include "audioDatum.hpp"

class Source : public Node {
	protected:
		// audioDatum sound;

	public:
		audioDatum sound;
		// gives pointer to node's result. May be invalid. Essentially a 'noodle'
		// which can be plugged into another node's input
		audioDatum* getOutput(void); 

		// void Update();
};

#endif
