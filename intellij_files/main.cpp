#include "../CrosswalkController.h"
#include "../Scheduler.h"


int main() {

    CrosswalkController controller(1,2,3,4,5);
    controller.buttonPressed();

    while(1) {
        Scheduler::run();
    }

    return 0;
}