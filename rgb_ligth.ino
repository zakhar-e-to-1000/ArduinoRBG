#include<math.h>

int pin_x =  A0;
int pin_y =  A1;
int xValue;
int yValue;

int pin_red = 6;
int pin_green = 5;
int pin_blue = 3;
struct Vector{
  double x;
  double y;
};

Vector green_vec;
Vector red_vec;
Vector blue_vec;



void setup() {
  Serial.begin(19200);
  pinMode(pin_red, OUTPUT);
  pinMode(pin_green, OUTPUT);
  pinMode(pin_blue, OUTPUT);
  digitalWrite(pin_red, LOW);
  digitalWrite(pin_blue, LOW);
  digitalWrite(pin_green, LOW);

  green_vec.x = 0;
  green_vec.y = 1;

  red_vec.x = -cos(M_PI/6);
  red_vec.y = -0.5;

  blue_vec.x = cos(M_PI/6);
  blue_vec.y = -0.5;
}
Vector get_vector(int x, int y){
  double dx = (double)x-511;
  double dy = (double)y-511;
  Vector r;
  r.x = dx;
  r.y = dy;
  return r;
}

double len(Vector v1){
  return sqrt(v1.x*v1.x+v1.y*v1.y);
}

double vec_cos(Vector a, Vector b){
  double prod = a.x*b.x + a.y*b.y;
  prod /= len(a)*len(b);
  return prod;
}
void loop() {
  int x = analogRead(pin_x);
  int y = analogRead(pin_y);
  Vector vec = get_vector(x, y);
  double cos_green = vec_cos(vec, green_vec);
  double cos_red = vec_cos(vec, red_vec);
  double cos_blue = vec_cos(vec, blue_vec);
  if(cos_green>0){
    //write LOW instead to enable Satoru Gojo's Hollow Purple
    digitalWrite(pin_green, HIGH);
  } else{
    digitalWrite(pin_green, LOW);
  }
  if(cos_red>0){
    digitalWrite(pin_red, HIGH);
  }else{
    digitalWrite(pin_red, LOW);
  }
  if(cos_blue>0){
    digitalWrite(pin_blue, HIGH);
  } else{
    digitalWrite(pin_blue, LOW);
  }
  Serial.println(red_vec.x);
  Serial.println(red_vec.y);
  Serial.println(cos_red);
  Serial.println(cos_blue);
  Serial.println(cos_green);
  Serial.println("");
  delay(100);
}