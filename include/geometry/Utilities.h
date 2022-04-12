#pragma once

#include <geometry/Geometry.h>
#include <fstream>
#include <string>
#include <time.h>
#include <vector>

namespace geometry {
    
    static std::vector<Point2D> loadPoint2DFromFile(const char* filename) {
        std::vector<Point2D> points;
        std::ifstream file_in(filename);

        std::string line;
        while(std::getline(file_in, line))
        {
            std::stringstream iss(line);
            float x, y;
            if (!(iss >> x >> y)) { break; } 

            points.push_back(Point2D(x,y));
        }

        return points;
    }

    static std::vector<Segment2D> loadSegment2DFromFile(const char* filename) {
        std::vector<Segment2D> segments;
        std::ifstream file_in(filename);

        std::string line;
        while(std::getline(file_in, line))
        {
            std::stringstream iss(line);
            double start_x, start_y;
            double end_x, end_y;
            if (!(iss >> start_x >> start_y >> end_x >> end_y )) { break; } 

            segments.push_back(Segment2D(Point2D(start_x,start_y),Point2D(end_x,end_y)));
        }

        return segments;
    }

    static std::vector<Segment2D> randomVectorSegment2D(int size) {

        std::vector<Segment2D> segments;
        for(int i = 0; i < size; i++){
            double start_x = rand() % 600;
            double start_y = rand() % 600;
            double end_x =  rand() % 600; 
            double end_y = rand() % 600;

            segments.push_back(Segment2D(Point2D(start_x,start_y),Point2D(end_x,end_y)));
        }

        return segments;
    }
}