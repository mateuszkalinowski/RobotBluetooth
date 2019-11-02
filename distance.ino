void measure_distance ()
{
  digitalWrite(Trig, LOW);        //ustawienie stanu wysokiego na 2 uS - impuls inicjalizujacy - patrz dokumentacja
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);       //ustawienie stanu wysokiego na 10 uS - impuls inicjalizujacy - patrz dokumentacja
  delayMicroseconds(15);
  digitalWrite(Trig, LOW);
  digitalWrite(Echo, HIGH); 
  return_time = pulseIn(Echo, HIGH);
  distance = return_time / 58;                //szerokość odbitego impulsu w uS podzielone przez 58 to odleglosc w cm - patrz dokumentacja
}
