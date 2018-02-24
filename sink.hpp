#ifndef SINK_HPP
#define SINK_HPP

#include "node.hpp"
#include "audioDatum.hpp"

class Sink : public Node {
	protected:
		audioDatum* input;
	public:
		void setInput(audioDatum*);
};

#endif
