import processing.javafx.*;
boolean wkey, skey, akey, dkey, xkey, click, start, canfire;
ArrayList<Bullet> projectileList;
ArrayList<Enemy> enemyList;
ArrayList<HolderObject> removeList;
int gamemode, kills, enemycounter, gunRemoved, EnemyRemoved;
board test;

Player player;
Spawn spawner;

void setup()
{
  size(1000, 1000);
  player = new Player();
  spawner = new Spawn();
  test = new board(20, 20);
  //test.createBoard();
  test.importBoard("data/mapData.json");

  projectileList = new ArrayList<Bullet>();
  enemyList = new ArrayList<Enemy>();
  removeList = new ArrayList<HolderObject>();
}


void draw()
{
  background(255);
  test.drawBoard();
  //test.editBoard();
  test.showEdit();

  fill(0);
  textSize(50);
  text("Zombies Alive:"+(enemycounter-kills), 0, 50);
  text("Zombie Kills:"+kills, 0, 100);
  text("frame Rate:"+frameRate, 0, 150);
  text("Bullets removed from memory:"+gunRemoved, 0, 200);
  text("Zombies removed from memory:"+EnemyRemoved, 0, 250);

  spawner.show();
  spawner.act();

  player.act();
  player.show();

  player.checkmove(test.getBoard());


  player.wrdCollision();
  if (player.killed()) { //<>//

    noLoop();
  }

  for (Bullet bullet : projectileList) {

    bullet.act();
    bullet.show();
    bullet.wrdCollision(test.getBoard());
  }

  for (Enemy Enemy : enemyList) {

    Enemy.act();
    Enemy.show();
    player.objCollision(Enemy);
    Enemy.checkmove(test.getBoard());

    for (Bullet bullet : projectileList) {

      bullet.objCollision(Enemy);
    }

    if (Enemy.killed()) {

      removeList.add(Enemy);

      kills = kills + 1;
    }
  }

  for (Bullet bullet : projectileList) {

    if (bullet.killed()) {
      removeList.add(bullet);
    }
  }

  for (HolderObject remove : removeList) {

    if (remove.getType() == 2) {

      enemyList.remove(remove);
      EnemyRemoved = EnemyRemoved + 1;
    }

    if (remove.getType() == 1) {

      projectileList.remove(remove);
      gunRemoved = gunRemoved + 1;
    }
  }

  removeList.clear();
}
void keyPressed()
{
  if (key == 'w'|| key == 'W') wkey = true;
  if (key == 's'|| key == 'S') skey = true;
  if (key == 'a'|| key == 'A') akey = true;
  if (key == 'd'|| key == 'D') dkey = true;
  if (key == 'x'|| key == 'X') xkey = true;

  if (keyCode == ENTER || keyCode == RETURN)
  {
    if (!looping)
    {
      //test.updateBoard();
      //test.generateJsonMap();
      //test.saveJsonMap();

      loop();
    } else
    {
      noLoop();
    }

    start = true;
  }
}

void keyReleased()
{
  if (key == 'w'||key == 'W') wkey = false;
  if (key == 's'||key == 'S') skey = false;
  if (key == 'a'||key == 'A') akey = false;
  if (key == 'd'||key == 'D') dkey = false;
}

void mousePressed()
{
  if (mouseButton == LEFT) click =  true;
}
void mouseReleased()
{
  if (mouseButton == LEFT) click = false;
}
