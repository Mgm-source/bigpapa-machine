class Spawn extends HolderObject
{

  Spawn()
  {
    type = 3;
    x = width+2;
    y = height+50;
    dx = 0;
    dy = 0;
  }

  void show()
  {
    fill(100);
    ellipse(x, y, 100, 100);
  }

  void act()
  {
if(frameCount % 500 == 1){
      enemyList.add(new Enemy(25, 25));
      enemycounter++;
}



  }

  void straightWave (int zombx)
  {
    x = zombx;
    if (frameCount % 1 == 0)
    {
      enemyList.add(new Enemy(25, 25));
      enemycounter++;
    }
  }
  void randomWave()
  {
    x = (int) random(50, width-50);

    if (frameCount % 20 == 0)
    {
      enemyList.add(new Enemy(25, 25));
      enemycounter++;
      enemyList.add(new Enemy(25, 25));
      enemycounter++;
    }
  }


  boolean killed()
  {
    return false;
  }
}
