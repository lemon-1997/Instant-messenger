CREATE TABLE users
(
  user_name varchar(20) NOT NULL,
  user_password varchar(20) NOT NULL,
  PRIMARY KEY(user_name)
);

 
alter table users add column (user_cfd varchar(2));


CREATE TABLE friends
(
  user_name varchar(20) NOT NULL,
  friend_1 varchar(20) ,
  friend_2 varchar(20) ,
  friend_3 varchar(20) ,
  friend_4 varchar(20) ,
  friend_5 varchar(20) ,
  friend_6 varchar(20) ,
  friend_7 varchar(20) ,
  friend_8 varchar(20) ,
  friend_9 varchar(20) ,
  friend_10 varchar(20) ,
  PRIMARY KEY(user_name)
);
