class Bullet extends HolderObject
{

  Bullet(float x, float y, float dx, float dy)
  {
    type = 1;
    hp = 50;
    w = 10;
    h = 10;
    
    this.x = x;
    this.y = y;
   
    this.dx = 20*dx;
    this.dy = 20*dy;
  }

  void show()
  {

    //hd yoyo line
    //line(x+mouseX, y+mouseY, player.x, player.y);
    fill(423, 121, 12);
    ellipse(x, y, w, h);

  }

  void act()
  {
    x=x+dx;
    y=y+dy;
  }

  void objCollision(HolderObject obj) {

    if (hit(x, y, w, h, obj.x, obj.y, obj.w, obj.h))
    {
      hp = hp-10;
      obj.hp = 0;
    }
  }

  void wrdCollision(ArrayList<cell> board) {

    if ( (x+dx < w/2 || x+dx > width || y+dy < h/2 || y+dy > height-h/2) )
    {
      hp = -1;
    }
    
    if (!board.get(test.findCell(x, y)).isWalkable()){
      hp = -1;
    }
  }

  boolean killed()
  {
    return  hp<=0;
  }
}
