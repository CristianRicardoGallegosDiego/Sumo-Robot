/**
  Proyecto robot de pelea.
  @file RobotSumo
  @brief Codigo para derribar o sacar al robot enemigo del dojo.

  @author Gallegos Diego Cristian Ricardo.
  @version 1.0 
  @date 16/05/2023
 */
const int INFRARROJO_UNO = A5;
const int INFRARROJO_DOS = A6;
const int INFRARROJO_TRES = A7;

const int ECHO = 2;
const int TRIGGER = 4;

const int MOTOR_I_UNO = 11;
const int MOTOR_I_DOS = 5;

const int MOTOR_D_UNO = 10;
const int MOTOR_D_DOS = 6; 

const int COLOR = 700; // Consideramos al color blanco en un rango [0, 700] 
                        // y al color negro en un rango de [701, 1024]
const long RADIO = 50; // Radio a la redonda del robot, son 50 cm que el robot alcanza a detectar enemigos a la redonda.
const int TIEMPO_ESPERA = 5000; // El robot tiene 5 segundos para iniciar a pelear.

void setup()
{
  Serial.begin(9600);
  pinMode(INFRARROJO_UNO, INPUT);
  pinMode(INFRARROJO_DOS, INPUT);
  pinMode(INFRARROJO_TRES, INPUT);
  pinMode(MOTOR_I_UNO, OUTPUT);
  pinMode(MOTOR_D_UNO, OUTPUT);
  pinMode(MOTOR_I_DOS, OUTPUT);
  pinMode(MOTOR_D_DOS, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIGGER, OUTPUT);
  digitalWrite(TRIGGER, LOW); // Inicializacion de apagado del ultrasonico.
  delay(TIEMPO_ESPERA); 
}

void loop()
{
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  long tiempo = pulseIn(ECHO, HIGH); 
  long distancia = tiempo / 59;
  if (analogRead(INFRARROJO_UNO) > COLOR || analogRead(INFRARROJO_DOS) > COLOR 
    || analogRead(INFRARROJO_TRES) > COLOR)
    { // Detectamos color negro con algun sensor infrarrojo. Sin peligro de salirnos del dojo.
    if (distancia <= RADIO)
    { // El robot enemigo este enfrente.
      acelerarEnFrente();
    }
    else
    { // Giramos para encontrar el robot enemigo.
      girarDerecha();
    }
  }
  else
  { // Los sensores infrarrojos dectectaron color blanco.
    if (distancia <= RADIO)
    { // El enemigo salio del dojo.
      detenerse();
    }
    else
    { // En peligro de salirnos.
      acelerarAtras();
    }
  }
}

/**
 @brief movemos al robot a hacia enfrente.

 Logramos mover el robot a hacia enfrente dandole la misma direccion a ambos motores.
 */
void acelerarEnFrente()
{
  direccionarMotor(MOTOR_I_UNO, MOTOR_I_DOS, HIGH, LOW);
  direccionarMotor(MOTOR_D_UNO, MOTOR_D_DOS, HIGH, LOW);
}

/**
 @brief movemos al robot a hacia atras.

 Logramos mover el robot a hacia atras dandole la misma direccion a ambos motores.
 */
void acelerarAtras()
{
  direccionarMotor(MOTOR_I_UNO, MOTOR_I_DOS, LOW, HIGH);
  direccionarMotor(MOTOR_D_UNO, MOTOR_D_DOS, LOW, HIGH);
}

/**
 @brief a hace girar al robot a hacia la derecha viendo al robot a desde la parte trasera, es decir el robot
  gira a nuestra mano derecha.

 Logramos mover el robot a hacia la derecha logrando que un motor acelere a hacia adelante y el otro este apagado.
 */
void girarDerecha()
{
  direccionarMotor(MOTOR_I_UNO, MOTOR_I_DOS, LOW, LOW);
  direccionarMotor(MOTOR_D_UNO, MOTOR_D_DOS, HIGH, LOW);
}

/**
 @brief paramos o detenemos al robot.

 Logramos detener al robot apagando a ambos motores.
 */
void detenerse()
{
  direccionarMotor(MOTOR_I_UNO, MOTOR_I_DOS, LOW, LOW);
  direccionarMotor(MOTOR_D_UNO, MOTOR_D_DOS, LOW, LOW);
}

/**
  @brief Mueve en motor en distintas formar.

  A hacemos mover en una direccion al motor o apagaralo, pasamos como parametro los 2 pines que corresponden al motor
  y dependiendo de la senhal digital a hacemos mover en una direccion al motor.

  @param motorUnoUno es el pin digital Izquierdo/Derecho al cual corresponde al motor.
  @param motorUnoDos es el pin digital Izquiero/Derecho al cual corresponde al motor.
  @param senalDigUno sea HIGH o LOW le daremos esa senhal al pin que corresponde al motorUnoUno. 
  @param senalDigDos sea HIGH o LOW le daremos ese senhal al pin que corresponde al motorUnoDos.
 */
void direccionarMotor(int motorUnoUno, int motorUnoDos, int senalDigUno, int senalDigDos)
{
  digitalWrite(motorUnoUno, senalDigUno);
  digitalWrite(motorUnoDos, senalDigDos);
}