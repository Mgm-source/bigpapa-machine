let shape = [];

function setup() {
  createCanvas(600, 600);
  shape.push(new Rectangle(500, 150, 1, 0, 3));
  shape.push(new Rectangle(500, 250, 1, 0, 3));
  shape.push(new Circle(220, 140, 1, 0, 3));
  shape.push(new Circle(140, 200, 0, 1, 3));
}

function draw() {

  //shape[1].move(mouseX,mouseY);

  background(255);

  for (let i = 0; i < shape.length; i++) {

    for (let j = 0; j < shape.length; j++) {
      if (shape[j] != shape[i]) {
        shape[i].coll(shape[j]);
      }
    }
    shape[i].update();
  }

}

class Shape {
  w = 40;
  h = 40;
  speed = 1;

  type = null;

  constructor(x, y, vx, vy, m) {
    this.x = x;
    this.y = this.y;
    this.vx = vx;
    this.vy = vy;
    this.y = y;
    this.m = m;

  }

  display() {}

  wallColl() {

    if (this.type == "rectangle") {

      if (this.y < 0) {
        this.vy = this.vy * -1;
      }

      if (this.y >= height - this.h) {
        this.vy = this.vy * -1;
      }

      if (this.x < 0) {
        this.vx = this.vx * -1;
      }

      if (this.x >= width - this.w) {
        this.vx = this.vx * - 1;
      }

  }

    if (this.type == "circle") {

      if (this.y < this.w) {
        this.vy = this.vy * -1;
      }

      if (this.y > height - this.w) {
        this.vy = this.vy * -1;
      }

      if (this.x < this.w) {
        this.vx = this.vx * -1;
      }

      if (this.x >= width - this.w) {
        this.vx = this.vx * - 1;
      }

    }
  
}

  coll(other) {

    if (this.type == 'rectangle' && other.type == 'rectangle') {

      if (this.x < (other.x + other.w) && (this.x + this.w) > other.x && this.y < (other.y + other.h) && (this.y + this.h) > other.y) {

        this.elastic(other);

      }
    }

    if (this.type == 'circle' && other.type == 'circle') {

      if (Math.abs(((other.x - this.x) ** 2) + ((other.y - this.y) ** 2)) < ((this.w + other.w) ** 2)) {

        this.elastic(other);

      }
    }

    if (this.type == 'circle' && other.type == 'rectangle') {

      const distanceX = other.x - this.x;
      const distanceY = other.y - this.y;

      const angle = atan2(other.y + (other.h / 2) - this.y, other.x + (other.w / 2) - this.x) * 180 / PI;

      if ((distanceX < (this.w + other.w) / 4 && distanceX > -(this.w + other.w - this.w / 4) && distanceY <= (this.w + other.h) / 4 && distanceY > -(this.w + other.w - this.w / 4)) || distanceX > - (this.w + other.w) && distanceX < (this.w) && distanceY > -(this.w + other.h) && distanceY <= (this.w)) {

        let nAngle;

        if (angle < 60 && angle > 30) {
          nAngle = 45 * PI / 180
          console.log("top left");
        }

        if (angle > -30 && angle < 30) {
          nAngle = 0 * PI / 180;
          console.log("left side");
        }

        if (angle > -60 && angle < -30) {
          nAngle = -45 * PI / 180
          console.log("bottom left");
        }

        if (angle < 150 && angle > 120) {
          nAngle = 135 * PI / 180
          console.log("top right");
        }

        if (angle <= 180 && angle > 150 || angle >= -180 && angle < -150) {
          nAngle = 180 * PI / 180;
          console.log("right side");
        }

        if (angle > -150 && angle < -120) {
          nAngle = -135 * PI / 180
          console.log("bottom rigt");
        }
        if (angle < -60 && angle > -120) {
          nAngle = -90 * PI / 180
          console.log("bottom");
        }

        if (angle > 60 && angle < 120) {
          nAngle = 90 * PI / 180
          console.log("top");
        }

        this.vx = Math.cos(nAngle);
        this.vy = Math.sin(nAngle);

        other.vx = -Math.cos(nAngle)
        other.vy = -Math.sin(nAngle)

        this.elastic(other)
      }

      // if(distanceX < (other.w + this.w) && distanceX >= 0 && distanceY < (other.h + this.w) && distanceY >= 0){

      //   console.log(angle,"far",distanceX,distanceY); not as robust as the other condition

      // }

    }

  }

  elastic(other) {

    const oldvx = this.vx;
    const oldvy = this.vy;

    if (this.m == other.m) {

      this.vx = other.vx;
      other.vx = oldvx;

      this.vy = other.vy;
      other.vy = oldvy;
    }

    else {

      this.vx = ((this.m - other.m) / (this.m + other.m)) * this.vx + ((2 * other.m) / (this.m + other.m)) * other.vx;
      other.vx = ((other.m - this.m) / (other.m + this.m)) * other.vx + ((2 * this.m) / (other.m + this.m)) * this.vx;

      this.vy = ((this.m - other.m) / (this.m + other.m)) * this.vy + ((2 * other.m) / (this.m + other.m)) * other.vy;
      other.vy = ((other.m - this.m) / (other.m + this.m)) * other.vy + ((2 * this.m) / (other.m + this.m)) * this.vy;

    }

  }

  move() {
    this.x += this.vx * this.speed;
    this.y += this.vy * this.speed;

  }

  update() {

    this.move();
    this.wallColl();
    this.display();

  }
}

class Rectangle extends Shape {

  type = 'rectangle';

  display() {

    if (this.vx < 0 && this.vy < 0 || this.vx < 0 && this.vy > 0) {
      fill('red');
      rect(this.x, this.y, this.w, this.h);
    }

    if (this.vx > 0 && this.vy < 0 || this.vx > 0 && this.vy > 0) {
      fill('blue');
      rect(this.x, this.y, this.w, this.h);
    }

    if (this.vx > 0 && this.vy == 0 || this.vx < 0 && this.vy == 0 || this.vy > 0 && this.vx == 0 || this.vy < 0 && this.vx == 0) {
      fill('green')
      rect(this.x, this.y, this.w, this.h);
    }

    if (this.vx == 0 && this.vy == 0) {
      fill(255);
      rect(this.x, this.y, this.w, this.h);
    }

  }

}

class Circle extends Shape {

  type = 'circle';

  w = this.w / 2;

  display() {

    if (this.vx < 0 && this.vy < 0 || this.vx < 0 && this.vy > 0) {
      fill('red');
      circle(this.x, this.y, this.h);
    }

    if (this.vx > 0 && this.vy < 0 || this.vx > 0 && this.vy > 0) {
      fill('blue');
      circle(this.x, this.y, this.h);
    }

    if (this.vx > 0 && this.vy == 0 || this.vx < 0 && this.vy == 0 || this.vy > 0 && this.vx == 0 || this.vy < 0 && this.vx == 0) {
      fill('green')
      circle(this.x, this.y, this.h);
    }

    if (this.vx == 0 && this.vy == 0) {
      fill(255);
      circle(this.x, this.y, this.h);
    }

  }

}

  // move(x,y){
  //   if(x != undefined && x > 0 || y != undefined && y > 0){
  //     this.x = x;
  //     this.y = y;
  //   }
  // }
