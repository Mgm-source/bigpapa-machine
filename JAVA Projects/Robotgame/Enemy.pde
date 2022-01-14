class Enemy extends HolderObject
{
  float diffX;
  float diffY;

  Enemy(float x, float y)
  {
    this.x = x;
    this.y = y;

    type = 2;
    hp = 10;
    moveSpeed = 1;
    h = 50;
    w = 50;

    for (int i=0; i<robot_RS.length; i++)
    {
      (robot_RS[i] = loadImage("enemy/"+ROBOT_RSIDE+i+".png")).resize(w, h);
    }
    for (int i=0; i<robot_LS.length; i++)
    {
      (robot_LS[i] = loadImage("enemy/"+ROBOT_LSIDE+i+".png")).resize(w, h);
    }

    for (int i=0; i<robot_F.length; i++)
    {
      (robot_F[i] = loadImage("enemy/"+ROBOT_FORWARD+i+".png")).resize(w, h);
    }

    for (int i=0; i<robot_B.length; i++)
    {
      (robot_B[i] = loadImage("enemy/"+ROBOT_BACKWARD+i+".png")).resize(w, h);
    }
  }

  void act()
  {

    diffX = player.x - x;
    diffY = player.y - y;

    if (abs(diffX) > 0)
    {

      if (x > player.x) {
        dx =  moveSpeed * -1;
      }
      if (x < player.x) {
        dx = moveSpeed;
      }
    } else if (abs(diffY) > 0) {

      if (y > player.y) {
        dy = moveSpeed * -1;
      }
      if (y < player.y) {
        dy = moveSpeed;
      }
    }
  }

  void objCollision(HolderObject obj)
  {
    if (hit(x, y, w, h, obj.x, obj.y, obj.w, obj.h))
    {
      hp = hp - 10;
      obj.hp = 0;
    }
  }

  boolean killed()
  {
    return hp<=0;
  }
}
