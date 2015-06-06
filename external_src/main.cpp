#include "CrosswalkController.h"





void runScheduler(int count) {
    for (int i=0; i<count; i++) {
        Scheduler::run();
    }
}



int main() {

    CrosswalkController controller(1,2,3,4,5);

    controller.on();
    runScheduler(100000);
    controller.buttonPressed();
    runScheduler(100000);
    controller.night();
    runScheduler(100000);
    controller.off();
    runScheduler(100000);

    return 0;
}


