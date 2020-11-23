// Programming_Assignment_5_MCST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include "AMGraph.h"

int main()
{
    std::cout << "Cameron Burkholder - Lab 5: Minimum Cost Spanning Tree" << std::endl;

    std::unique_ptr<AMGraph> graph = std::make_unique<AMGraph>("input.graph");
    graph->print();
    graph->write("output.graph");
}
