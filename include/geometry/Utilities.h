#pragma once

#include <geometry/Geometry.h>
#include <ios>
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

    static std::vector<Segment2D> randomVectorSegment2D(int size, double lower, double upper) {

        std::vector<Segment2D> segments;
        for(int i = 0; i < size; i++){

            double range = upper - lower;

            double x_1 = (rand() % (int) range) + lower;
            double y_1 = (rand() % (int) range) + lower;
            double x_2 = (rand() % (int) range) + lower;
            double y_2 = (rand() % (int) range) + lower;

            Point2D p1 = Point2D(x_1, y_1);
            Point2D p2 = Point2D(x_2, y_2);

            Segment2D s = p1 < p2 ? Segment2D(p1,p2) : Segment2D(p2,p1);
            segments.push_back(s);
        }

        return segments;
    }

    static void saveSegment2DonFile(char * filename , std::vector<Segment2D> segments) {

        std::ofstream out(filename, std::ios::trunc);
        for(Segment2D s : segments) {
            out << s.start.x << " " << s.start.y << " " << s.end.x << " " << s.end.y << std::endl;
        }

        out.close();
    }
}