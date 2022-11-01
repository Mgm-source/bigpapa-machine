Drop schema if exists gamehub;
  
Create schema if not exists gamehub;

create table if not exists gamehub.user (
username varchar(11) not null primary key,
password varchar (32) not null
);

create table if not exists gamehub.game (
id int not null auto_increment primary key,
name varchar(255),
duration int
);

create table if not exists gamehub.conf (
id int not null auto_increment primary key,
title varchar(255),
description varchar(255),
slug varchar(100),
image varchar(255),
maintenance boolean
);

create table if not exists gamehub.record (
id int not null auto_increment primary key,
username varchar(11) not null,
game_id int not null,
foreign key (username) references user(username) on delete cascade,
foreign key (game_id) references game(id) on delete cascade,
score int
);