ArrayList<Bounce> balls = new ArrayList<Bounce>();
void setup()
{
  size(500, 500);
  balls.add(new Bounce(235, 0, 3, 0, 3.0));
  balls.add(new Bounce(100, 0, 1, 3, 4.0));
}

void draw()
{
  background(255);
  for (int i = 0; i<balls.size(); i++) {
    balls.get(i).update();
    for (int j = 0; j<balls.size(); j++) {
      if (i != j) {
        balls.get(i).ballcoll(balls.get(j));
      }
    }
  }
}
