/*!
 * Fighting Sumo Robot.
 * @file sumo_robot
 * @brief Code for knocking down or taking out the enemy robot at the dojo.
 *
 * @author Gallegos Diego Cristian Ricardo - 318114723.
 * @version 2.0 
 * @date 05/16/2023
 */
const int INFRARED_ONE = A5;
const int INFRARED_TWO = A6;
const int INFRARED_THREE = A7;

const int ECHO = 2;
const int TRIGGER = 4;

const int MOTOR_L_ONE = 11;
const int MOTOR_L_TWO = 5;

const int MOTOR_R_ONE = 10;
const int MOTOR_R_TWO = 6; 

const int COLOR = 300; // Represents the intensity range for what is considered as black color [0, 300].
                       // For the white color in a range [301, 1024].
const long RADIO = 40; // Robot's enemy detection radius (40 cm) around the robot where it can detect the presence of enemies.
const int WAIT_TIME = 5000; // Waiting time before starting the fight (5 seconds).

void setup()
{
  Serial.begin(9600);
  pinMode(INFRARED_ONE, INPUT);
  pinMode(INFRARED_TWO, INPUT);
  pinMode(INFRARED_THREE, INPUT);
  pinMode(MOTOR_L_ONE, OUTPUT);
  pinMode(MOTOR_R_ONE, OUTPUT);
  pinMode(MOTOR_L_TWO, OUTPUT);
  pinMode(MOTOR_R_TWO, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIGGER, OUTPUT);

  digitalWrite(TRIGGER, LOW);
  delay(WAIT_TIME); 
}

void loop()
{
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  long time = pulseIn(ECHO, HIGH); 
  long distance = time / 59;
  if (analogRead(INFRARED_ONE) < COLOR && analogRead(INFRARED_TWO) < COLOR && analogRead(INFRARED_THREE) < COLOR)
  { // Black color detected by all infrared sensors. No risk of leaving the dojo.
    if (distance <= RADIO)
    { // The enemy robot is in front.
      toAccelerateForward();
    }
    else
    { // The robot turns to find the enemy robot.
      toTurn();
    }
  }
  else
  { // Some infrared sensors detected the color white.
    if (distance <= RADIO)
    { // The enemy gets out of the dojo.
      toStop();
    }
    else
    { // At risk of leaving the dojo.
      toAccelerateBackward();
    }
  }
}

/*!
 * @brief The robot moves forward.
 *
 * This function controls the robot's forward movement.
 */
void toAccelerateForward()
{
  digitalWrite(MOTOR_R_ONE, HIGH);
  digitalWrite(MOTOR_L_TWO, LOW);
  digitalWrite(MOTOR_L_ONE, HIGH);
  digitalWrite(MOTOR_R_TWO, LOW);
}

/*!
 * @brief The robot moves backward.
 *
 * This function controls the robot's backward movement.
 */
void toAccelerateBackward()
{
  digitalWrite(MOTOR_R_ONE, LOW);
  digitalWrite(MOTOR_L_TWO, HIGH);
  digitalWrite(MOTOR_L_ONE, LOW);
  digitalWrite(MOTOR_R_TWO, HIGH);
  delay(250);
}

/*!
 * @brief The robot turns.
 *
 * This function controls the robot's turning motion, allowing it to turn in a direction.
 */
void toTurn()
{
  digitalWrite(MOTOR_R_ONE, LOW);
  digitalWrite(MOTOR_L_TWO, HIGH);
  digitalWrite(MOTOR_L_ONE, HIGH);
  digitalWrite(MOTOR_R_TWO, LOW);
}

/*!
 * @brief The robot stops moving.
 *
 * This function stops the robot by turning off all motors.
 */
void toStop()
{
  digitalWrite(MOTOR_R_ONE, LOW);
  digitalWrite(MOTOR_L_TWO, LOW);
  digitalWrite(MOTOR_L_ONE, LOW);
  digitalWrite(MOTOR_R_TWO, LOW);
}