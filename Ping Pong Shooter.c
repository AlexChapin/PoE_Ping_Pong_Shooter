#pragma config(Sensor, dgtl1,  Up,             sensorTouch)
#pragma config(Sensor, dgtl2,  Down,           sensorTouch)
#pragma config(Sensor, dgtl3,  ShootTrigger,   sensorTouch)
#pragma config(Sensor, dgtl4,  PivotEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl12, Indicate,       sensorLEDtoVCC)
#pragma config(Motor,  port1,           Pivot,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           Shoot,         tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
int SetpointSelector = 1;
int TargetPose = 10;



task main() {
while (true){
TargetPose = SetpointSelector * 7.5;
if ((SensorValue(PivotEncoder) - TargetPose)>4){startMotor(Pivot,25);}
if ((SensorValue(PivotEncoder) - TargetPose)<-4){startMotor(Pivot,-18);}
if ((SensorValue(PivotEncoder) - TargetPose)>.5 &&(SensorValue(PivotEncoder) - TargetPose)<4){startMotor(Pivot,10);}
if ((SensorValue(PivotEncoder) - TargetPose)<-.5 &&(SensorValue(PivotEncoder) - TargetPose)>-4){startMotor(Pivot,-7);}
if (SensorValue(PivotEncoder)- TargetPose<.5 && SensorValue(PivotEncoder) - TargetPose>-.5){stopMotor(Pivot);}
if(SensorValue(ShootTrigger)){
	startMotor(Shoot, 127);}
if(SensorValue(ShootTrigger)==0){
	stopMotor(Shoot);}

if(SensorValue(Up)){
	if(SetpointSelector<=7){
		SetpointSelector = SetpointSelector +1;}
while (SensorValue(Up)){
wait(.01);}}

if(SensorValue(Down)){
	if(SetpointSelector>=2){
		SetpointSelector = SetpointSelector -1;}
while (SensorValue(Down)){
wait(.01);}}

}
}
