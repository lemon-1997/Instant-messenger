CREATE TABLE users
(
  user_name varchar(20) NOT NULL,
  user_password varchar(20) NOT NULL,
  PRIMARY KEY(user_name)
)

 
insert into users (name, password)
    values ('001', '123');
