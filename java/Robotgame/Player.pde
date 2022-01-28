class Player extends HolderObject
{

  Player()
  {
    type = 0;
    x = 150;
    y = 150;
    w = 50;
    h = 50;
    hp = 1;
    moveSpeed = 5;

    for (int i=0; i<robot_RS.length; i++)
    {
      (robot_RS[i] = loadImage("robot/"+ROBOT_RSIDE+i+".png")).resize(w, h);
    }
    for (int i=0; i<robot_LS.length; i++)
    {
      (robot_LS[i] = loadImage("robot/"+ROBOT_LSIDE+i+".png")).resize(w, h);
    }
    for (int i=0; i<robot_F.length; i++)
    {
      (robot_F[i] = loadImage("robot/"+ROBOT_FORWARD+i+".png")).resize(w, h);
    }
    for (int i=0; i<robot_B.length; i++)
    {
      (robot_B[i] = loadImage("robot/"+ROBOT_BACKWARD+i+".png")).resize(w, h);
    }
  }

  void act()
  {
    float angle = atan2(mouseY-y, mouseX-x);
    float ax = cos(angle);
    float ay = sin(angle);

    if (click)
    {

      projectileList.add(new Bullet(x, y, ax, ay));
      click = false;
    }


    if (wkey)
    {
      dy = moveSpeed * - 1;
    } else if (dkey)
    {
      dx = moveSpeed;
    } else if (skey)
    {
      dy =moveSpeed;
    } else if (akey)
    {
      dx =moveSpeed * - 1;;
    }

  }

  void objCollision(HolderObject obj)
  {
    if (hit(x, y, h, h, obj.x, obj.y, obj.h, obj.h))
    {
      hp = hp-1;
      obj.hp = 0;
    }
  }


  boolean killed()
  {
    return hp<= 0;
  }
}
