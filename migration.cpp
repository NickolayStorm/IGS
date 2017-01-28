#include "migration.h"

Migration::Migration(std::shared_ptr<Shape*> from,
                     std::shared_ptr<Shape*> to,
                     int stepCount){
    from_ = from;
    to_ = to;
    if ( (*from)->getUVCounts() != (*to)->getUVCounts())
    {
        std::terminate();
    }
    uCount = (*from)->getUVCounts().first;
    vCount = (*from)->getUVCounts().second;
    remainingSteps_ = stepCount;
    computeMigrations(stepCount);
}

void Migration::computeMigrations(int stepCount){
    // Points without any mapping
    auto identity = [](const Point &arg){
        return arg;
    };

    auto pointsFrom = (*from_)->makePoints(identity);
    auto pointsTo   = (*to_)  ->makePoints(identity);
    migrations_.reserve(pointsFrom.size());

    for(Point &p : pointsFrom){
        float min_distance = std::numeric_limits<float>::max();
        auto iter = pointsTo.begin();
        auto min_pos = iter;
        for(; iter != pointsTo.end(); ++ iter){
            Point& oth = *iter;
            float distance = p.distance(oth);
            if(distance < min_distance){
                min_pos = iter;
                min_distance = distance;
            }
        }
        Point moveVec = (*iter - p) / stepCount;
        pointsTo.erase(iter);
        Migrations m = {
                 p,
                 moveVec
        };
        migrations_.push_back(m);
    }
}

void Migration::step(){
    for(auto& m : migrations_){
        m.current_ = m.current_ + m.vectorOfMove_;
    }
    --remainingSteps_;
}

std::vector<Point>
Migration::makePoints(std::function<Point (const Point&)> mapping){

    std::vector<Point> points;
    points.reserve(migrations_.size());

    std::transform(migrations_.begin(), migrations_.end(),
                   points.begin(),
                   [&](Migrations& m){ return mapping(m.current_); });

    return points;
}
