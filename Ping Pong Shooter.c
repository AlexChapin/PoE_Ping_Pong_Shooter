#pragma config(Sensor, dgtl1,  Up,             sensorTouch)
#pragma config(Sensor, dgtl2,  Down,           sensorTouch)
#pragma config(Sensor, dgtl3,  ShootTrigger,   sensorTouch)
#pragma config(Sensor, dgtl4,  PivotEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  FlywheelEncoder, sensorQuadEncoder)
#pragma config(Motor,  port1,           Pivot,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           LeftFly,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           RightFly,      tmotorVex393_MC29, openLoop)


// Variables //
int SetpointSelector = 1;
int TargetPose = 10;
int lastquad = 0;
const float QuadCountsPerSetpointStep = 7.5; //Experiment To Discover 10 Degree
const int FastSpeedUp = -25;
const int FastSpeedDown = 18;
const int SlowSpeedUp = -10;
const int SlowSpeedDown = 7;
const int MaxSetpoint = 8;
const int MinSetpoint = 1;

const float DelayTimeButtonDebounce = .01; //Seconds
const int FlywheelShootSpeed = 127;
const float TargetFlywheelSpeed = 20; //Degrees Per Second
const float ShootLoopTime = .05; //Seconds

// Motor Driving Loop //
task PivotControl(){
while (true){
	TargetPose = SetpointSelector * QuadCountsPerSetpointStep;
	if ((SensorValue(PivotEncoder) - TargetPose)>4){
		startMotor(Pivot,FastSpeedDown);
		}
	if ((SensorValue(PivotEncoder) - TargetPose)<-4){
		startMotor(Pivot,FastSpeedUp);
		}
	if ((SensorValue(PivotEncoder) - TargetPose)>.5 &&(SensorValue(PivotEncoder) - TargetPose)<4){
		startMotor(Pivot,SlowSpeedDown);
		}
	if ((SensorValue(PivotEncoder) - TargetPose)<-.5 &&(SensorValue(PivotEncoder) - TargetPose)>-4){
		startMotor(Pivot,SlowSpeedUp);
		}
	if (SensorValue(PivotEncoder) - TargetPose<.5 && SensorValue(PivotEncoder) - TargetPose>-.5){
		stopMotor(Pivot);
		}
}
}

// Setpoint Adjustment Logic //
task PositionLogic(){
while (true){
	if(SensorValue(Up)){
		if(SetpointSelector<=(MaxSetpoint-1)){
			SetpointSelector++;
			}
		while (SensorValue(Up)){
			wait(DelayTimeButtonDebounce);}
			}
	if(SensorValue(Down)){
		if(SetpointSelector>=(MinSetpoint+2)){
			SetpointSelector = SetpointSelector - 1;
			}
		while (SensorValue(Down)){
			wait(DelayTimeButtonDebounce);}
			}
}
}
// Shooting Speed Control Loop //
task ShootControl(){
	slaveMotor(LeftFly,RightFly);
	while (true){
		if(SensorValue(ShootTrigger)){
			startMotor(RightFly, FlywheelShootSpeed);
			if (abs(SensorValue(FlywheelEncoder)-lastquad)>TargetFlywheelSpeed){
				//Shoot Ball//
			}
			wait(ShootLoopTime);
			SensorValue(FlywheelEncoder) = lastquad;
		}

		if(SensorValue(ShootTrigger)==0){
			stopMotor(RightFly);
			}

	}
}



task main() {
	startTask(PivotControl);
	startTask(PositionLogic);
	startTask(ShootControl);
}