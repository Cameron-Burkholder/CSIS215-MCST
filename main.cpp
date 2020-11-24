// Programming_Assignment_5_MCST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include "AMGraph.h"

int main()
{
    std::cout << "Cameron Burkholder - Lab 5: Minimum Cost Spanning Tree" << std::endl;

    std::unique_ptr<AMGraph> graph = std::make_unique<AMGraph>("input.graph");
    graph->print(false);
    graph->write("output.graph");
    AMGraph* mcst1 = graph->MCST(0);
    AMGraph* mcst2 = graph->MCST(4);
    AMGraph* mcst3 = graph->MCST(2);

    mcst1->write("mcst1.graph");
    mcst2->write("mcst2.graph");
    mcst3->write("mcst3.graph");
}
