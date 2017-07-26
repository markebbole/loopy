#include "LoopyNode.h"

#include <iostream>

bool LoopyNode::allInputsReady()
{
    for (size_t i = 0; i < inputConnections.size(); ++i) {
        if (outputIterations == 0 && !inputConnections[i].enforceOnFirstRun) {
            continue;
        }

        if (inputs.count(inputNameMapping[inputConnections[i].inputNode->outputKey]) == 0) {
            return false;
        }
    }

    return true;
}

void LoopyNode::addInput(InputConnection ic)
{
    inputConnections.push_back(ic);
    // Make this node an outputReceiver of the node at the other end of the InputConnection.
    // This is kind of ugly and I'm sure there's a more elegant way to set things up but it works.
    ic.inputNode->outputReceivers.push_back(this);
    // An InputConnection has a desired parameterName that will be used in this node's LoopyFunction.
    // We have to store this translation in inputNameMapping.
    inputNameMapping[ic.inputNode->outputKey] = ic.parameterName;
}

void LoopyNode::inputReady(LoopyNode* node)
{
    if (inputConnections.size() == 0) {
        std::cout << "You're notifying a node without any input connections that some input is ready! Bad!" << std::endl;
        exit(1);
    }
    // Translate the node's outputKey to the parameterName specified in the corresponding InputConnection.
    inputs[inputNameMapping[node->outputKey]] = node;

    // If all input nodes are ready then call this node's LoopyFunction and store the output.
    // Then notify all nodes that have this node as an InputConnection that output is ready.
    if (allInputsReady()) {
        output = processFn(inputs);
        inputs.clear();
        notifyReceivers();
    }
}

void LoopyNode::notifyReceivers()
{
    outputIterations ++;
    for (size_t i = 0; i < outputReceivers.size(); ++i) {
        outputReceivers[i]->inputReady(this);
    }
}
