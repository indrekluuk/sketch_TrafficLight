#include "../CrosswalkController.h"





void runScheduler(int count) {
    for (int i=0; i<count; i++) {
        Scheduler::run();
    }
}



int main() {

    CrosswalkController controller(1,2,3,4,5);

    controller.on();
    runScheduler(1000);
    controller.buttonPressed();
    runScheduler(1000);
    controller.night();
    runScheduler(1000);
    controller.off();
    runScheduler(1000);

    return 0;
}


