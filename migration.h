#ifndef MIGRATION_H
#define MIGRATION_H
#include "shape.h"
#include <memory>
#include <vector>

class Migration : public Shape
{
    std::shared_ptr<Shape*> from_;
    std::shared_ptr<Shape*> to_;
    struct Migrations{
        Point current_;
        Point vectorOfMove_;
    };
    unsigned remainingSteps_;
    void computeMigrations(int);
    void func(){}
    std::vector<Migrations> migrations_;
public:
    std::vector<Point>
    makePoints(std::function<Point (const Point&)> mapping);
    inline bool isFinished(){ return remainingSteps_ == 0; }
    inline std::shared_ptr<Shape*> getShapeTo(){ return to_; }

    Migration(std::shared_ptr<Shape*> from,
              std::shared_ptr<Shape*> to,
              int stepCount);
    void step();
};

#endif // MIGRATION_H
