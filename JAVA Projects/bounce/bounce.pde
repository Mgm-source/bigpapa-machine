// note to self processing when working with float make sure you add the decimal point otherwise the variable is interpreted as an integar
class Bounce
{
  float x;
  float y;
  float vx;
  float vy;
  float m;
  PImage redball, blueball, greenball, orangeball;
  int imgWidth;
  int imgHeight;

  // constructor
  Bounce(float x, float y, float vx, float vy, float m)
  {
    this.x = x;
    this.y = y;
    this.vx = vx;
    this.vy = vy;
    this.m = m;

    greenball = loadImage("greencircle.png");
    blueball= loadImage("bluecircle.png");
    redball= loadImage("redcircle.png");
    orangeball=loadImage("orangecircle.png");
  }

  void update()
  {
    move();
    display();
    wallColl();
  }


  void display() {

    if (vx < 0 && vy < 0 || vx < 0 && vy > 0) {
      //moving left up and down
      image(blueball, x, y);
      imgWidth = blueball.width;
      imgHeight = blueball.height;
    }

    if (vx > 0 && vy < 0 || vx > 0 && vy > 0) {
      //moving right up and down
      image(redball, x, y);
      imgWidth = redball.width;
      imgHeight = redball.height;
    }

    if (vx > 0 && vy == 0 || vx < 0 && vy == 0 || vy > 0 && vx == 0 || vy < 0 && vx == 0) {
      // moving the cardinal directions
      image(greenball, x, y);
      imgWidth = greenball.width;
      imgHeight = greenball.height;
    }

    if (vx == 0 && vy == 0) {
      // ball not moving
      image(orangeball, x, y);
      imgWidth = greenball.width;
      imgHeight = greenball.height;
    }
  }
  // redball width
  void wallColl()
  {

    if (y < 0) {
      y=0;
      vy= vy * -1; // switch to moving downwards
    }

    if (y >= height-imgHeight) {
      y = height-imgHeight;
      vy=vy * -1;
    }

    if (x < 0) {
      x = 0;
      vx=vx * -1; // switch to moving right
    }

    if (x >= width-imgWidth) {
      x = width-imgWidth;
      vx=vx * -1;
    }
  }

  void move()
  {
    x += vx;
    y += vy;
  }


  void ballcoll(Bounce other) {

    if ( x < (other.x+other.imgWidth) && (x+imgWidth) > other.x && y < (other.y+other.imgHeight) && (y+imgHeight) > other.y ) {
      // axis aligned collision dection

      float old_vx = vx;

      if (m == other.m ) {
        vx = other.vx;
        other.vx = old_vx;
      } else {

        float new_vx =  ((m - other.m) / (m + other.m)) * vx  +  ((2 * other.m) / (m + other.m)) * other.vx ;
        float new_othervx = ((other.m - m) / (other.m + m)) * other.vx  +  ((2 * m) / (other.m + m)) * vx;

        float new_vy =  ((m - other.m) / (m + other.m)) * vy  +  ((2 * other.m) / (m + other.m)) * other.vy ;
        float new_othervy = ((other.m - m) / (other.m + m)) * other.vy  +  ((2 * m) / (other.m + m)) * vy;

        vx = new_vx;
        other.vx = new_othervx;

        vy = new_vy;
        other.vy = new_othervy;
      }

      move();
      other.move();
    }
  }
}
