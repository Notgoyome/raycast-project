//
// Created by Guillaume Tran on 08/05/2024.
//

#include "Triangle.hpp"


extern "C" ray::INode *create(std::map<std::string, std::string>& properties)
{
    ray::Triangle *triangle = new ray::Triangle();
    if (properties.find("p1") != properties.end() && properties.find("p2") != properties.end() && properties.find("p3") != properties.end()) {
        triangle->setPoint(StringToPoint3D(properties["p1"]),
                           StringToPoint3D(properties["p2"]),
                           StringToPoint3D(properties["p3"]));
        return triangle;
    }
    throw ray::NodeError("Triangle: missing p1, p2 or p3 attribute", "Triangle.cpp");

}