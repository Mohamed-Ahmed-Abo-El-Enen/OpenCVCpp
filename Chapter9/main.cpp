#include "header/CamShiftTracker.hpp"
#include "header/ColoredObjectTracker.hpp"
#include "header/FarnebackTracker.hpp"
#include "header/GoodFeaturesToTrack.hpp"
#include "header/HarrisCornersTracker.hpp"
#include "header/LucasKanadeTracker.hpp"


int main(int argc, char* argv[])
{
    // CamShiftTracker(argc, argv);
    // ColoredObjectTracker(argc, argv);
    // FarnebackTracker(argc, argv);
    // GoodFeaturesToTrack(argc, argv);
    // HarrisCornersTracker(argc, argv);
    LucasKanadeTracker(argc, argv);
}