#include "LoopyGraphState.h"
#include <fstream>

void LoopyGraphState::readGraphFromFile(string filename)
{
    cout << filename << endl;
    ifstream i(filename);
    json j;
    i >> j;
    parseJson(j);
    parseInputs(j);
}

void LoopyGraphState::destroyAll()
{
    for(std::map<string, LoopyNode*>::iterator iter = allNodes.begin(); iter != allNodes.end(); ++iter) {
        delete iter->second;
    }

    allNodes.clear();
    inputNodes.clear();
    output = NULL;
}

void LoopyGraphState::parseJson(json& j)
{
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        string k = it.key();
        if (k == "output") {
            continue;
        }
        json o = it.value();
        string type = o["type"];

        if (type == "AdditionNode") {
            allNodes[k] = new AdditionNode();
        }
        if (type == "AdditionModNode") {
            allNodes[k] = new AdditionModNode();
        }
        if (type == "SubtractionNode") {
            allNodes[k] = new SubtractionNode();
        }
        if (type == "DivideNode") {
            allNodes[k] = new DivideNode();
        }
        if (type == "MultiplyNode") {
            allNodes[k] = new MultiplyNode();
        }
        if (type == "ScaleNode") {
            allNodes[k] = new ScaleNode();
        }
        if (type == "TranslateNode") {
            allNodes[k] = new TranslateNode();
        }
        if (type == "RotateNode") {
            allNodes[k] = new RotateNode();
        }
        if (type == "SpeckledNoiseNode") {
            allNodes[k] = new SpeckledNoiseNode();
        }
        if (type == "SineNode") {
            allNodes[k] = new SineNode();
        }
        if (type == "CircleNode") {
            allNodes[k] = new CircleNode();
        }
        if (type == "ClearImageNode") {
            allNodes[k] = new ClearImageNode();
            inputNodes.push_back((LoopyInputNode*)allNodes[k]);
        }
        if (type == "ImageNode") {
            allNodes[k] = new ImageNode();
            inputNodes.push_back((LoopyInputNode*)allNodes[k]);
        }


        allNodes[k]->setFunctionInputs(o["params"]);
    }

    output = allNodes[j["output"]];
}

void LoopyGraphState::parseInputs(json& j) {
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        if (it.key() == "output") {
            continue;
        }
        LoopyNode *n = allNodes[it.key()];

        for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2) {
            string k = it2.key();
            if (k != "type" && k != "params") {
                string val = it2.value();
                // weak vs not weak
                if (val.at(0) == '-') {
                    n->addInput(allNodes[val.substr(1)], k, false);
                } else {
                    LoopyNode* con = allNodes[val];
                    n->addInput(allNodes[val], k, true);
                }
            }
        }
    }
}
