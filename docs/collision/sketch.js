let balls = [];

function setup() {
  createCanvas(500, 500);
  balls.push(new Bounce(0, 435, 0, -6, 5));
  balls.push(new Bounce(0, 0, 1, 4, 3));
  balls.push(new Bounce(200, 235, 2, 6, 10));
  balls.push(new Bounce(300, 435, 1, 4, 3));
}

function draw() {

  background(255);
  
  for (let i = 0; i < balls.length; i++) {

    balls[i].update();

    for (let j = 0; j < balls.length; j++) {
      if (balls[j] != balls[i]) {
        balls[i].ballcoll(balls[j]);
      }
    }
  }

}

class Bounce {

  imgWidth;
  imgHeight;

  // constructor 
  constructor(x, y, vx, vy, m) {
    this.x = x;
    this.y = this.y;
    this.vx = vx;
    this.vy = vy;
    this.y = y;
    this.m = m;

    this.greenball = loadImage('greencircle.png');
    this.blueball = loadImage('bluecircle.png');
    this.redball = loadImage('redcircle.png');
    this.orangeball = loadImage('orangecircle.png');
  }

  display() {


    if (this.vx < 0 && this.vy < 0 || this.vx < 0 && this.vy > 0) {
      //moving left up and down 
      image(this.blueball, this.x, this.y);
      this.imgWidth = this.blueball.width;
      this.imgHeight = this.blueball.height;
    }

    if (this.vx > 0 && this.vy < 0 || this.vx > 0 && this.vy > 0) {
      //moving right up and down
      image(this.redball, this.x, this.y);
      this.imgWidth = this.redball.width;
      this.imgHeight = this.redball.height;
    }

    if (this.vx > 0 && this.vy == 0 || this.vx < 0 && this.vy == 0 || this.vy > 0 && this.vx == 0 || this.vy < 0 && this.vx == 0) {
      // moving the cardinal directions
      image(this.greenball, this.x, this.y);
      this.imgWidth = this.greenball.width;
      this.imgHeight = this.greenball.height;
    }

    if (this.vx == 0 && this.vy == 0) {
      // ball not moving
      image(this.orangeball, this.x, this.y);
      this.imgWidth = this.greenball.width;
      this.imgHeight = this.greenball.height;
    }

  }

  // this.redball width 
  wallColl() {

    if (this.y < 0) {
      this.y = 0;
      this.vy = this.vy * -1; // switch to this.moving downwards
    }

    if (this.y >= height - this.imgHeight) {
      this.y = height - this.imgHeight;
      this.vy = this.vy * -1;
    }

    if (this.x < 0) {
      this.x = 0;
      this.vx = this.vx * -1; // switch to this.moving right
    }

    if (this.x >= width - this.imgWidth) {
      this.x = width - this.imgWidth;
      this.vx = this.vx * - 1;
    }
  }

  move() {
    this.x += this.vx * 1;
    this.y += this.vy * 1;
  }


  ballcoll(other) {

    if (this.x < (other.x + other.imgWidth) && (this.x + this.imgWidth) > other.x && this.y < (other.y + other.imgHeight) && (this.y + this.imgHeight) > other.y) {
      // athis.xis aligned collision dection
      let phi = (atan2(this.y - other.y, this.x - other.x) * 180 / PI) * 2;

      let oldvx = this.vx;
      let oldvy = this.vy;




      if (this.m == other.m) 
      {

        this.vx = other.vx;
        other.vx = oldvx;

        this.vy = other.vy;
        other.vy = oldvy;
      }

      else {

        let tvx = ((this.m - other.m) / (this.m + other.m)) * this.vx + ((2 * other.m) / (this.m + other.m)) * other.vx;
        let tvx2 = ((other.m - this.m) / (other.m + this.m)) * other.vx + ((2 * this.m) / (other.m + this.m)) * this.vx;

        let tvy = ((this.m - other.m) / (this.m + other.m)) * this.vy + ((2 * other.m) / (this.m + other.m)) * other.vy;
        let tvy2 = ((other.m - this.m) / (other.m + this.m)) * other.vy + ((2 * this.m) / (other.m + this.m)) * this.vy;


        this.vx = tvx;
        other.vx = tvx2;

        this.vy = tvy;
        other.vy = tvy2;


      }

      this.move();
      other.move();

    }
  }

  update() {

    this.display();
    this.move();
    this.wallColl();
  }
}
