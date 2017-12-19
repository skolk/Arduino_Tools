#define ENC_1_A A0
#define ENC_1_B A1

#define ENC_2_A A2
#define ENC_2_B A3

int encoder_1_value = 0;
int encoder_2_value = 0;

static int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

void setup() {
/* Setup encoder pins as inputs */
pinMode(ENC_1_A, INPUT);
digitalWrite(ENC_1_A, HIGH);
pinMode(ENC_1_B, INPUT);
digitalWrite(ENC_1_B, HIGH);

/* Setup encoder pins as inputs */
pinMode(ENC_2_A, INPUT);
digitalWrite(ENC_2_A, HIGH);
pinMode(ENC_2_B, INPUT);
digitalWrite(ENC_2_B, HIGH);

Serial.begin (9600);
Serial.println('************ Start *************');
}

/* returns change in encoder state (-1,0,1) */
int8_t read_encoder1() {
static uint8_t old_AB = 0;

old_AB <<= 2;
old_AB |= ((digitalRead(ENC_1_B))?(1<<1):0) | ((digitalRead(ENC_1_A))?(1<<0):0);
return ( enc_states[( old_AB & 0x0f )]);
}

/* returns change in encoder state (-1,0,1) */
int8_t read_encoder2() {
static uint8_t old_AB = 0;

old_AB <<= 2;
old_AB |= ((digitalRead(ENC_2_B))?(1<<1):0) | ((digitalRead(ENC_2_A))?(1<<0):0);
return ( enc_states[( old_AB & 0x0f )]);
}

void loop() {
int8_t encoderdata1;
int8_t encoderdata2;

encoderdata1 = read_encoder1();
if ( encoderdata1 ) {
encoder_1_value += encoderdata1;
Serial.print("Encoder 1: ");
Serial.println(encoder_1_value);
}

encoderdata2 = read_encoder2();
if ( encoderdata2 ) {
encoder_2_value += encoderdata2;
Serial.print("Encoder 2: ");
Serial.println(encoder_2_value);
}

}
