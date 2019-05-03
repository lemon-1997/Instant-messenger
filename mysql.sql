CREATE TABLE users
(
  user_name varchar(20) NOT NULL,
  user_password varchar(20) NOT NULL,
  PRIMARY KEY(user_name)
)

 
alter table users add column (user_cfd varchar(2));
