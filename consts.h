#ifndef CONSTS_H
#define CONSTS_H

#include <QString>

const QString separator = "#";

namespace GloveConsts {
const int numberOfSensors = 5;
const int header = 123456;
}

namespace SensorsConsts {
const int min = 0;
const int max = 1023;
}

namespace HandConsts {
const int numberOfMotors = 6;
const int motorMinValue = 0;
const int motorMaxValue = 180;
const int startMotorValue = motorMaxValue;
const int header = 789123;
}

#endif // CONSTS_H
