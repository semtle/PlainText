#include <QTest>

#include "application.h"

#include "test_container.h"
#include "test_crashes.h"
#include "test_serialization.h"
#include "test_visualevents.h"


int main(int argc, char *argv[]) {

    Application application(argc, argv);

    SerializationTest test1;
    ContainerTest test2;
    CrashesTest test3;
    VisualEventsTest test4;

    //QTest::qExec(&test1);
    //QTest::qExec(&test2);
    //QTest::qExec(&test3);
    QTest::qExec(&test4);

    return 0;
}