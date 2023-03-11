#pragma once
#include "yaml-cpp/yaml.h"

class TestA
{
public:
    int x;
};

namespace YAML
{
    template <>
    struct convert<TestA>
    {
        static Node encode(const TestA &rhs)
        {
            Node node;
            node.push_back(rhs.x);
            return node;
        }

        static bool decode(const Node &node, TestA &rhs)
        {
            if (!node.IsSequence())
            {
                return false;
            }

            rhs.x = node[0].as<int>();
            return true;
        }
    };
}