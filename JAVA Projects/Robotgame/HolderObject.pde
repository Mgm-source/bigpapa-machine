abstract class HolderObject
{
  int hp, w, h, frames, type, moveSpeed;
  float x, y, dx, dy;
  int timing = 10;

  static final String ROBOT_RSIDE = "rs_";
  static final String ROBOT_LSIDE = "rls_";
  static final String ROBOT_FORWARD = "rsf_";
  static final String ROBOT_BACKWARD = "rwb_";

  PImage[] robot_RS = new PImage[2];
  PImage[] robot_LS = new PImage[2];
  PImage[] robot_F = new PImage[3];
  PImage[] robot_B = new PImage[3];

  HolderObject()
  {
  }
  void show()
  {

    if (dx == 0 && dy ==0) {
      pushMatrix();
      imageMode(CENTER);
      image(robot_F[0], x, y);
      popMatrix();
    }

    if (dy > 0 && dx == 0) {
      frames = 3;
      pushMatrix();
      imageMode(CENTER);
      image(robot_F[frameCount/timing%frames], x, y);
      popMatrix();
    }

    if (dy < 0 && dx == 0) {
      frames = 3;
      pushMatrix();
      imageMode(CENTER);
      image(robot_B[frameCount/timing%frames], x, y);
      popMatrix();
    }

    if (dx > 0) {
      frames = 2;
      pushMatrix();
      imageMode(CENTER);
      image(robot_RS[frameCount/timing%frames], x, y);
      popMatrix();
    }

    if (dx < 0) {
      frames = 2;
      pushMatrix();
      imageMode(CENTER);
      image(robot_LS[frameCount/timing%frames], x, y);
      popMatrix();
    }
  }
  void act()
  {
  }

  void checkmove(ArrayList<cell> board) {

    float temp_x = x;
    float temp_y = y;

    temp_x += dx;
    temp_y += dy;

    if (!board.get(test.findCell(temp_x, temp_y)).isWalkable()) {
      dx = 0;
      dy = 0;
    }

    x += dx;
    y += dy;

    dx = 0;
    dy = 0;
  }


  void wrdCollision() {
    if (x < w/2) {
      x = w/2;
    }
    if (x > width-w/2) {
      x = width-w/2;
    }

    if (y < h/2) {
      y = h/2;
    }

    if (y > height-h/2) {
      y = height-h/2;
    }
  }

  void objCollision(HolderObject obj)
  {
  }

  boolean killed()
  {
    return false;
  }

  int setType(int number) {
    type = number;
    return type;
  }

  int getType () {
    return type;
  }
}
