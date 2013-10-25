#ifndef CONSTS_H
#define CONSTS_H

#include <QString>

const QString separator = "#";

namespace Consts {
const QString noPort = "NO_PORT";
}

namespace GloveConsts {
const int numberOfSensors = 1;
const int header = 882111924;
const int initializationNumber =719731018;
}

namespace SensorsConsts {
const int min = 0;
const int max = 1023;
}

namespace HandConsts {
const int numberOfMotors = 1;
const int motorMinValue = 0;
const int motorMaxValue = 180;
const int startMotorValue = motorMaxValue;
const int header = 789123;
}

#endif // CONSTS_H
