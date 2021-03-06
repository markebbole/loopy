#include "LoopyNode.h"

#include <iostream>

#include "LoopyNodeExceptions.h"

int LoopyNode::nextId = 0;

bool LoopyNode::allInputsReady()
{
    for (size_t i = 0; i < inputConnections.size(); ++i) {
        if (outputIterations == 0 && !inputConnections[i].enforceOnFirstRun) {
            continue;
        }
        vector<string> nameMappings = inputNameMapping[inputConnections[i].inputNode->outputKey];

        // We only have to check the first mapped name since if that one exists then all the others do, too.
        if (inputs.count(nameMappings[0]) == 0) {
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
    inputNameMapping[ic.inputNode->outputKey].push_back(ic.parameterName);
}

void LoopyNode::inputReady(LoopyNode* node)
{
    if (inputConnections.size() == 0) {
        std::cout << "You're notifying a node without any input connections that some input is ready! Bad!" << std::endl;
        exit(1);
    }
    // Translate the node's outputKey to the parameterName specified in the corresponding InputConnection.
    vector<string> mappedNames = inputNameMapping[node->outputKey];
    for (auto it = mappedNames.begin(); it != mappedNames.end(); ++it) {
        inputs[*it] = node;
    }

    // If all input nodes are ready then call this node's LoopyFunction and store the output.
    // Then notify all nodes that have this node as an InputConnection that output is ready.
    if (allInputsReady()) {
        try {
            output = process(inputs);
        } catch(exception& ex) {
            std::cout << ex.what() << std::endl;
            exit(1);
        }
        inputs.clear();
        notifyReceivers();
    }
}

LoopyNode::~LoopyNode() {
}

void LoopyNode::notifyReceivers()
{
    outputIterations ++;
    for (size_t i = 0; i < outputReceivers.size(); ++i) {
        outputReceivers[i]->inputReady(this);
    }
}

float LoopyNode::getFloatParam(string paramName)
{
    if (inputs.count(paramName) == 0) {
        throw MissingRequiredParameterException(paramName);
    }

    LoopyNode* parameterNode = inputs[paramName];
    float v = parameterNode->getOutput().at<float>(0, 0);
    return v;
}

float LoopyNode::getFloatParam(string paramName, float defaultValue)
{
    if (inputs.count(paramName) == 0) {
        return defaultValue;
    }

    return getFloatParam(paramName);
}

int LoopyNode::getIntParam(string paramName)
{
    int v = (int)floor(getFloatParam(paramName));
    return v;
}

int LoopyNode::getIntParam(string paramName, int defaultValue)
{
    if (inputs.count(paramName) == 0) {
        return defaultValue;
    }

    return getIntParam(paramName);
}

bool LoopyNode::getBoolParam(string paramName)
{
    int v = getIntParam(paramName);
    return v != 0;
}

bool LoopyNode::getBoolParam(string paramName, bool defaultValue)
{
    if (inputs.count(paramName) == 0) {
        return defaultValue;
    }

    return getBoolParam(paramName);
}
