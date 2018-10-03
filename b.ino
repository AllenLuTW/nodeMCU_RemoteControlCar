const int LeftA = 8;   //�]�w���䨮�����}��,�ܼ�:LeftA  , �}��:8
const int LeftB = 9;   //�]�w���䨮�����}��,�ܼ�:LeftB  , �}��:9
const int RightA = 10; //�]�w�k�䨮�����}��,�ܼ�:RightA , �}��:10 
const int RightB = 11; //�]�w�k�䨮�����}��,�ܼ�:RightA , �}��:11

const int TrigPin = 2; //�]�w�W���i�o�X�W�v���}��,�ܼ�:TrigPin , �}��:2
const int EchoPin = 3; //�]�w�W���i�����W�v���}��,�ܼ�:EchoPin , �}��:3
float CM_Value; //�]�w�ܼ�:CM_Value,�W���i�����쪺�Z��

//�o�̥u���}���ɤ~�|����,�u�|����@��
//======�}�l======
void setup()
{
  Serial.begin(9600);
  pinMode(RightA, OUTPUT);   //�ŧi�k�䨮�����}��RightA(10)����X�}��
  pinMode(RightB, OUTPUT);   //�ŧi�k�䨮�����}��RightB(11)����X�}��
  pinMode(LeftA, OUTPUT);    //�ŧi���䨮�����}��LeftA(8)����X�}��
  pinMode(LeftB, OUTPUT);    //�ŧi���䨮�����}��LeftB(9)����X�}��

  pinMode(TrigPin, OUTPUT);  //�ŧi�W���i���}��TrigPin(2)����X�}��
  pinMode(EchoPin, INPUT);   //�ŧi�W���i���}��EchoPin(3)����X�}��

  delay(5000); //����5��,�t�άO�H�@�����,1��=1000�@��,�ҥH5000�@��N�O5��
}
//======����======

//�q���O�}������,�|�@�����Ƴo�̪��{��,��������
//======�}�l======
void loop()
{
  //�@�}�l�����o�W���i�����쪺�Z��
  //getCM() �O�Ƶ{��, distance �O�ܼ�
  int distance = getCM(); 

  if (distance < 15) //�p�G�����쪺�Z���O15�����H�U�N����U�C�{��
  {
    Stop();      //����Stop()���Ƶ{��,�D�n�O����F���ʧ@
    delay(100);  //��100�@��
    Back();      //����Back()���Ƶ{��,�D�n�O�����l��h
    delay(1000); //��1��(1000�@��)
    Right();     //����Right()���Ƶ{��,�D�n�O�����l�k��
    delay(1000); //��1��(1000�@��)
    Forward();   //����Forwar()���Ƶ{��,�D�n�O�����l�e�i
  }
  else //�_�h�N����U�C�{��
  {
    Forward(); //����Forwar()���Ƶ{��,�D�n�O�����l�e�i 
  }
}
//======����======

//���o�W���i������e���ê�����Z��
int getCM()
{
  digitalWrite(TrigPin, LOW);  //������TrigPin�}��
  delayMicroseconds(2);	       //��2�@��	
  digitalWrite(TrigPin, HIGH); //�}��TrigPin�}��,�o�X���W�n
  delayMicroseconds(10);       //��10�@��	
  digitalWrite(TrigPin, LOW);  //����TrigPin�}��

  //�}��EchoPin�}��åB���oTrigPin�o�X���W�n�Ǧ^�Ӫ��ɶ�
  //�ҥH�ثeCM_Value�����e�O�s��ɶ�
  CM_Value = pulseIn(EchoPin, HIGH);

  //�p��Z��, �Z��=�t�v*�ɶ�
  //���]���h�^,�ҥH�n��2
  //�p�⧹��CM_Value�����e�N�O�Z��(���O:����)
  CM_Value = CM_Value * 34 / 1000 / 2;

  //��Z���Ǧ^�h
  return CM_Value;
}

//��h
void Back()
{
  //�⥪�䨮���@���u�]�w�����q��,�t�@���u�]�w���C�q��
  //�o�˨����N�|��,�p�G�Ⱚ�q��M�C�q��մ�,�h�����N�|���t�@��V���

  digitalWrite(LeftA, LOW);   //�⥪�䨮����LeftA(8)�}��]�w�C�q��
  digitalWrite(LeftB, HIGH);  //�⥪�䨮����LeftB(9)�}��]�w���q��

  digitalWrite(RightA, LOW);  //��k�䨮����RightA(10)�}��]�w�C�q��
  digitalWrite(RightB, HIGH); //��k�䨮����RightB(11)�}��]�w�C�q��
}

//�e�i
void Forward()
{
  digitalWrite(LeftA, HIGH);
  digitalWrite(LeftB, LOW);

  digitalWrite(RightA, HIGH);
  digitalWrite(RightB, LOW);
}

//����
void Left()
{
  digitalWrite(LeftA, HIGH);
  digitalWrite(LeftB, LOW);

  digitalWrite(RightA, LOW);
  digitalWrite(RightB, HIGH);
}

//�k��
void Right()
{
  digitalWrite(LeftA, LOW);
  digitalWrite(LeftB, HIGH);

  digitalWrite(RightA, HIGH);
  digitalWrite(RightB, LOW);
}

//����
void Stop()
{
  //��Ҧ��������]�w���C�q��,�����N���|��ʤF
  //�]�i�H��Ҧ������]�w�����q��,�h�����]���|���
  digitalWrite(LeftA, LOW);
  digitalWrite(LeftB, LOW);
  
  digitalWrite(RightA, LOW);
  digitalWrite(RightB, LOW);
}
