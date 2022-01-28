class Particle extends HolderObject
{
  Particle(float x, float y)
  {
    this.x = x;
    this.y = y;
    w = 5;
    h = 5;
  }

  void show()
  {
    fill(423, 12, 32, hp);
    rect(x, y, w, h);
  }

  void act()
  {
    x=x+dx;
    y=y+dy;

    hp = hp-10;
  }

  boolean killed()
  {
    return hp<=0;
  }
}
