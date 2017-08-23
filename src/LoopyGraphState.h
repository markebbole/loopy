#ifndef NODE_CONSTRUCTOR_HANDLER
#define NODE_CONSTRUCTOR_HANDLER

#include "LoopyNode.h"
#include "LoopyInputNode.h"
#include "BasicLoopyNodes.h"
#include "LinearTransformations.h"

#include <string>
#include <map>
#include <vector>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class LoopyGraphState
{

    void parseJson(json& j);
    void parseInputs(json& j);
    void parseParams(LoopyNode* node, json& paramObject);
    void setupNumberNodeWithInput(float input, LoopyNode* parentNode, string paramName);
    void destroyAutoGeneratedInputNodes();
public:
    map<string, LoopyNode*> allNodes;
    vector<LoopyInputNode*> inputNodes;
    vector<LoopyInputNode*> autoGeneratedInputNodes;
    LoopyNode* output;

    LoopyGraphState() {}

    void readGraphFromFile(string filename);

    void destroyAll();

    void setAllInputsReady()
    {
        for (size_t i = 0; i < autoGeneratedInputNodes.size(); ++i) {
            autoGeneratedInputNodes[i]->setReady();
        }

        for (size_t i = 0; i < inputNodes.size(); ++i) {
            inputNodes[i]->setReady();
        }
    }

}; 

#endif
