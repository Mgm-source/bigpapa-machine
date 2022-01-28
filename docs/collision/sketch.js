'use strict';

const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");
let shape = [];

document.addEventListener("DOMContentLoaded", () => {

  shape.push(new Circle(500, 320, 1, 0, 3));
  shape.push(new Circle(0, 300, 1, 0, 3));

  window.requestAnimationFrame(draw);

})

function draw() {

  ctx.clearRect(0, 0, canvas.width, canvas.height);

  for (let k = 0; k < shape.length; k++) {
    shape[k].update();
  }

  for (let i = 0; i < shape.length; i++) {

    for (let j = 0; j < shape.length; j++) {

      if (i != j) {

        shape[i].coll(shape[j]);

      }
    }

    shape[i].wallColl();

  }

  window.requestAnimationFrame(draw);
}

class Shape {
  w = 40;
  h = 40;
  speed = 1;

  type = null;

  constructor(x, y, vx, vy, m) {
    this.x = x;
    this.y = y;
    this.vx = vx;
    this.vy = vy;
    this.m = m;

  }

  display() { }

  wallColl() {

    if (this.type == "rectangle") {

      if (this.y < 0) {
        this.vy = Math.abs(this.vy);
      }

      if (this.y > canvas.height - this.h) {
        this.vy = -this.vy;
      }

      if (this.x < 0) {
        this.vx = Math.abs(this.vx);
      }

      if (this.x > canvas.width - this.w) {
        this.vx = -this.vx;
      }

    }

    if (this.type == "circle") {

      if (this.y < this.w) {
        this.vy = Math.abs(this.vy);
      }

      if (this.y > canvas.height - this.w) {
        this.vy = -this.vy;
      }

      if (this.x < this.w) {
        this.vx = Math.abs(this.vx);
      }

      if (this.x > canvas.width - this.w) {
        this.vx = -this.vx;
      }

    }

  }

  coll(other) {

    if (this.type == 'rectangle') {

      if (other.type == 'rectangle') {

        const distanceX = other.x - this.x;
        const distanceY = other.y - this.y;

        if (distanceX > -other.w && distanceX < other.w && distanceY > -other.h && distanceY < other.h) {

          this.elastic(other);

        }

      }

    }

    if (this.type == 'circle') {

      if (other.type == 'circle') {

        const angle = Math.atan2(other.y - this.y, other.x - this.x) * 180 / Math.PI;

        if (Math.abs(((other.x - this.x) ** 2) + ((other.y - this.y) ** 2)) < ((this.r + other.r) ** 2)) {

          this.elastic(other);

        }
      }

      if (other.type == 'rectangle') {

        const distanceX = other.x - this.x;
        const distanceY = other.y - this.y;

        const angle = Math.atan2(other.y + (other.h / 2) - this.y, other.x + (other.w / 2) - this.x) * 180 / Math.PI;

        let nAngle = null;

        if ((distanceX < (this.r + other.w) / 4 && distanceX > -(this.r + other.w - this.r / 4) && distanceY <= (this.r + other.h) / 4 && distanceY > -(this.r + other.w - this.r / 4)) || distanceX > - (this.r + other.w) && distanceX < (this.r) && distanceY > -(this.r + other.h) && distanceY <= (this.r)) {

          if (angle < 60 && angle > 30) {
            nAngle = 45 * Math.PI / 180
          }

          if (angle > -30 && angle < 30) {
            nAngle = 0;
          }

          if (angle > -60 && angle < -30) {
            nAngle = -45 * Math.PI / 180
          }

          if (angle < 150 && angle > 120) {
            nAngle = 135 * Math.PI / 180
          }

          if (angle <= 180 && angle > 150 || angle >= -180 && angle < -150) {
            nAngle = 180 * Math.PI / 180;
          }

          if (angle > -150 && angle < -120) {
            nAngle = -135 * Math.PI / 180
          }
          if (angle < -60 && angle > -120) {
            nAngle = -90 * Math.PI / 180
          }

          if (angle > 60 && angle < 120) {
            nAngle = 90 * Math.PI / 180
          }

          this.vx = Math.cos(nAngle);
          this.vy = Math.sin(nAngle);

          other.vx = -Math.cos(nAngle)
          other.vy = -Math.sin(nAngle)

          this.elastic(other)
          console.log(nAngle);
        }
      }

    }

  }

  elastic(other) {

    const oldvx = this.vx;
    const oldvy = this.vy;

    if (this.m == other.m) {

      this.vx = other.vx
      this.vy = other.vy

      other.vx = oldvx;
      other.vy = oldvy;

    }

    else {

      this.vx = ((this.m - other.m) / (this.m + other.m)) * this.vx + ((2 * other.m) / (this.m + other.m)) * other.vx;
      this.vy = ((this.m - other.m) / (this.m + other.m)) * this.vy + ((2 * other.m) / (this.m + other.m)) * other.vy;

      other.vx = ((other.m - this.m) / (other.m + this.m)) * other.vx + ((2 * this.m) / (other.m + this.m)) * oldvx;
      other.vy = ((other.m - this.m) / (other.m + this.m)) * other.vy + ((2 * this.m) / (other.m + this.m)) * oldvy;

    }

    this.move();
    other.move();

  }

  move() {
    this.x += this.vx * this.speed;
    this.y += this.vy * this.speed;

  }

  update() {
    this.move();
    this.display();
  }

}

class Rectangle extends Shape {

  type = 'rectangle';

  display() {

    ctx.fillStyle = 'green';
    ctx.fillRect(this.x, this.y, this.w, this.h);

  }

}

class Circle extends Shape {

  type = 'circle';
  r = this.w / 2;

  display() {

    ctx.beginPath();
    ctx.fillStyle = 'red';
    ctx.arc(this.x, this.y, this.r, 0, 2 * Math.PI);
    ctx.fill();

  }

}

  // move(x,y){
  //   if(x != undefined && x > 0 || y != undefined && y > 0){
  //     this.x = x;
  //     this.y = y;
  //   }
  // }
